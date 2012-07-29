/* 
Program to demonstrate MCBSP traffic with received data utilizing DMA.

MCBSP is setup to transmit 4 frames with each frame containing 4 8 bit words.
Transmit data is manually (no DMA) written to the DXR register.
Received data will be transferred via DMA in to 1 of 3 rotating buffers 
(RXBUFF1, RXBUFF2, and RXBUFF3).

The McBSP is configured with the digital loopback enabled.  

V1.00

//11.14 disable tx, and tx pins

*/
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include<linux/vmalloc.h>
//#include <plat/mcbsp.h>
#include<linux/errno.h>
#include<linux/mm.h>
#include<linux/cdev.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/wait.h>
#include <linux/completion.h>
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/slab.h>
//#include <plat/dma.h>
//#include <plat/mcbsp.h>
#include <asm/uaccess.h>
//#include "../mach-omap2/cm-regbits-34xx.h"
#include <linux/fs.h>

#include <linux/irq.h>
#include <plat/irqs.h>
#include <plat/dma.h>

#include <asm/io.h>
#include <linux/dma-mapping.h>
//mmap
//signal
#include <asm/signal.h>
#include <asm-generic/siginfo.h>
//memcpy
#include <linux/string.h>
//ioctl
#include <linux/ioctl.h>
//wait queue
#include <linux/sched.h>
//time
#include <linux/jiffies.h>
//work queue
#include <linux/workqueue.h>
#include <asm/cacheflush.h>
#include "MCBSP.h"
#include "PRCM.h"
#include "CONTROL.h"
#include "operations.h"
#include "mcbsp_lib.h"
#include "DMA.h"
#include "dma_lib.h"
#include "sdma_buffer_queue.h"
#include "gpio.h"
//switch on debug mode 
#define WRITE_DEBUG
//#define NULL (void *)0

#define MY_MCBSP  						MCBSP1
#define MCBSP_MAJOR 					30

#define DMA_BUFFER_BLOCK_NUM 			2  //dma buffer block num

//mcbsp configure
#define MCBSP_WORDS_PER_FRAME 			1
//---------
#define MCBSP_BITS_PER_WORD				WORD_32BITS //refer to MCBSP_BITS_PER_WORD_DE
#define MCBSP_BITS_PER_WORD_DE			32	//refer to MCBSP_BITS_PER_WORD
//---------
#define MCBSP_FRAME_PERIOD				( MCBSP_BITS_PER_WORD * MCBSP_WORDS_PER_FRAME )
#define MCBSP_CLKDV						200

#define MCBSP_THRSHOLD_RX				64 //------------------------------------
#define MCBSP_THRSHOLD_TX				16 

//dma configure
#define DMA_WORDS_PER_FRAME				MCBSP_THRSHOLD_RX
#define DMA_BYTES_PER_WORD				( MCBSP_BITS_PER_WORD_DE / 8 )
#define DMA_BYTES_PER_FRAME				( DMA_WORDS_PER_FRAME * DMA_BYTES_PER_WORD)
//4 is 1KB, trigle dma interrupt every 36KB, this value is 16bit(64k)
#define DMA_FRAME_PER_BLOCK				(4 * 36)

//ioctrl
#define MCBSP_IOC_MAGIC 				'k'
//cmd of setting dma destination addr
#define MCBSP_IOC_SET_DMA_DES 			_IOW(MCBSP_IOC_MAGIC, 1, unsigned int*) 
//cmd of start mcbsp and dma
#define MCBSP_IOC_MCBSPDMA_START   		_IO(MCBSP_IOC_MAGIC, 2)
//cmd of stop mcbsp and dma
#define MCBSP_IOC_MCBSPDMA_STOP    		_IO(MCBSP_IOC_MAGIC, 3)
//cmd of restart mcbsp and dma after has buffer to dma
#define MCBSP_IOC_DMA_RESTART   		_IO(MCBSP_IOC_MAGIC, 4)

//add more cmd to here
#define MCBSP_IOC_MAXNR 				10 //max number of cmd

//----
//extern void print_sdma_buffer_queue(sdma_buffer_queue q);

int mcbsp_major = MCBSP_MAJOR;
volatile struct mcbsp_dev *mcbsp_devp;
static int count =0; //interrupt count, add in interrupt, reset when app exit in mcbsp_release
unsigned int dma_buffer_virt_head[2];


/*
struct dma_buffer_info {
	unsigned int dma_buffer_block_index;
	size_t dma_buffer_block_size; //size is based on byte
	size_t dma_buffer_valid_size; //valid data size in block, based on byte
	unsigned int dma_buffer_head;
	unsigned int dma_buffer_tail;
	unsigned int dma_buffer_block_lock;
};
*/
static int set_dma_buffer_info(struct dma_buffer_info *dma_buffer,
									unsigned int dma_buffer_block_index,
									size_t dma_buffer_block_size,
									unsigned int dma_buffer_head,
									unsigned int dma_buffer_tail,
									unsigned int dma_buffer_block_lock) 
{
	dma_buffer->dma_buffer_block_index = dma_buffer_block_index;
	dma_buffer->dma_buffer_block_lock = dma_buffer_block_lock;
	dma_buffer->dma_buffer_head = dma_buffer_head;
	dma_buffer->dma_buffer_tail = dma_buffer_tail;
	dma_buffer->dma_buffer_block_size = dma_buffer_block_size;
	//dma_buffer->dma_buffer_valid_size = dma_buffer_tail - dma_buffer_head;
	return 0;
}

//reset buffer tail and valid size
static void reset_dma_buffer_info(struct dma_buffer_info *dma_buffer) {
	dma_buffer->dma_buffer_tail = dma_buffer->dma_buffer_head;
	dma_buffer->dma_buffer_valid_size = 0;
	dma_buffer->have_no_buffer = 0;
}

static int set_dma_buf_info_point(struct dma_buffer_info * buf_to, 
							struct dma_buffer_info * buf_from) {
	//get block num from user space
	unsigned block_index = buf_from->dma_buffer_block_index; 
	if(DMA_BUFFER_BLOCK_NUM <= block_index) {
		printk(KERN_ERR "set dma buffer info error: block_index should small than %d", DMA_BUFFER_BLOCK_NUM);
		return -1;
	}
	else {
		
		dma_buffer_virt_head[buf_from->dma_buffer_block_index] = ioremap_nocache(buf_from->dma_buffer_head, SZ_4K);
		//copy to dma buffer info struct according to block num
		memcpy(&buf_to[block_index], buf_from, sizeof(struct dma_buffer_info));
	}
	return block_index;
}

void copy_buf_info(struct dma_buffer_info *buf_to, struct dma_buffer_info * buf_from) 
{
	memcpy(buf_to, buf_from, sizeof(struct dma_buffer_info));
}

void print_dma_buf_info(struct dma_buffer_info *dma_buffer) 
{
	printk("block_index = %d\n", dma_buffer->dma_buffer_block_index);
	printk("head = 0x%x\n", dma_buffer->dma_buffer_head);
	printk("tail = 0x%x\n", dma_buffer->dma_buffer_tail);
	printk("block_lock = 0x%x\n", dma_buffer->dma_buffer_block_lock);
	printk("block size = 0x%x\n", dma_buffer->dma_buffer_block_size);
	printk("valid data size = 0x%x\n", dma_buffer->dma_buffer_valid_size);
	printk("have no buffer = 0x%x\n", dma_buffer->have_no_buffer);
}

//mcbsp device struct
struct mcbsp_dev 
{
	struct cdev cdev;
	unsigned int chan; //enabled channel
	volatile unsigned int sdma_block_complete;
	//volatile unsigned int RXBUFF1[16]; //destination buffer
	unsigned int * RXBUFF1;
	//single-----
	//dma_addr_t RXBUFF1;
	//dma_addr_t dma_buffer;
	//---------
	dma_addr_t *dma_buffer;
	volatile unsigned int RXBUFF2[16];
	volatile unsigned int RXBUFF3[16];
	struct dma_buffer_info dma_buffer_info_array[DMA_BUFFER_BLOCK_NUM];
	struct dma_buffer_info current_buffer_info;
	struct dma_buffer_info fasync_read_buffer_info;
	unsigned int current_dma_block_index;  // block num whick is currently RD&WR by DMA channel 
	unsigned int fasync_read_block_index;  //avoid to lock current_dma_block_index which will be changed in interrupt handler
	struct fasync_struct *fasync_queue;
	wait_queue_head_t wait_q;
	unsigned int wait_q_flag;
	struct class *mcbsp_class;
	unsigned int devno;
	sdma_buffer_queue *buffer_queue;
	read_buffer_queue *read_queue;
	struct work_struct sdma_wq;
	//unsigned int valid_buffer[];
};

void sdma_do_work(struct work_struct *data) {
	printk(KERN_INFO "[sdma_do_work]");
	DECLARE_WAITQUEUE(wait, current);				/*declear wait*/
	add_wait_queue(&mcbsp_devp->wait_q, &wait);		/*add  the wait queue*/
	__set_current_state(TASK_INTERRUPTIBLE);
	mcbsp_devp->wait_q_flag = 1;
	printk(KERN_INFO "[sdma_do_work]");
	if(is_empty_sdma_buffer_queue(mcbsp_devp->buffer_queue)) {
		schedule();
	}
	printk(KERN_INFO "[sdma_do_work]:work queue wake up\n");
	mcbsp_devp->wait_q_flag = 0;
	struct dma_buffer_info *buf_info_p;
	if(get_sdma_buffer(mcbsp_devp->buffer_queue, &buf_info_p) == 0) {
		printk(KERN_ERR "[sdma_do_work]:sdma buffer is empty\n");
		return;
	}
	dmaConfigTransfer(mcbsp_devp->chan, 
						DMA_WORDS_PER_FRAME, 
						DMA_FRAME_PER_BLOCK, 
						(MY_MCBSP+MCBSPLP_DRR_REG), 
						buf_info_p->dma_buffer_head, 
						1, 
						0, 
						1, 
						0);
	copy_buf_info(&mcbsp_devp->fasync_read_buffer_info, &mcbsp_devp->current_buffer_info);
	copy_buf_info(&mcbsp_devp->current_buffer_info, buf_info_p);
	dmaEnableChannel(mcbsp_devp->chan);
	remove_wait_queue(&mcbsp_devp->wait_q, &wait);
	set_current_state(TASK_RUNNING);
}

static void mcbsp_setup_dev(struct mcbsp_dev *devp, unsigned int devno) {
//add dma_request
//--------------
//--------------
	devp->chan = CHAN11;
	devp->devno = devno;
	//devp->dma_buffer_info_array[0].dma_buffer_head = DMA_DES_ADDR;
}


static void mcbsp_dma_buffer_lock_check(struct mcbsp_dma_buffer_info *mcbsp_dma_buffer_info_p){
	//check dma buffer block lock bit
}
//-----------------
static irqreturn_t dma_irq_handler(int irq, void *dev_id) {
	unsigned int i, event;
	struct mcbsp_dev *devp = dev_id;
	struct dma_buffer_info *buf_info_p;
//close dma irq
//CLRBIT_REGL(DMA_CICRi + devp->chan * 0x60, DMA_FRAME_IE);
	event = IN_REGL(DMA_CSRi + devp->chan * 0x60);
	printk(KERN_INFO "@@@@@@@[DMA irq]: count = %d\n", count);
	//add count
	count++;
//confirm IRQ
//------------------------------------------
//------------------------------------------
//add codes to confirm IRQ source and events
//-----------------------------------------
	//count = block_size/(bytes per frame) indicate buffer is full
	unsigned int current_block_index = devp->current_buffer_info.dma_buffer_block_index;
	unsigned int current_block_size = devp->current_buffer_info.dma_buffer_block_size;
	
	//sync dma buffer tail
	devp->current_buffer_info.dma_buffer_tail = IN_REGL(DMA_CDACi + devp->chan * 0x60);
	devp->current_buffer_info.dma_buffer_valid_size = devp->current_buffer_info.dma_buffer_tail - devp->current_buffer_info.dma_buffer_head;
	//printk(KERN_INFO "@@@@@@@[DMA irq]: valid size = 0x%x", devp->current_buffer_info.dma_buffer_valid_size);
	//check if buffer queue is empty
	if(get_sdma_buffer(devp->buffer_queue, &buf_info_p) == 0) 
	{
		//set no buffer flag
		devp->current_buffer_info.have_no_buffer = 1;
		//put read buffer into FIFO
		put_read_buffer(devp->read_queue, &devp->current_buffer_info);
		//send async signal to app
		kill_fasync(&devp->fasync_queue,SIGIO,POLL_IN);
		
		//clear SDMA IRQ 
		SETBIT_REGL(DMA_CSRi + devp->chan * 0x60, event);
		SETBIT_REGL(DMA_IRQSTATUS_L1, 1<<(devp->chan));
		OUT_REGL(DMA_CDACi + mcbsp_devp->chan * 0x60, 0); //clear current destination addr
		OUT_REGL(DMA_CCENi + mcbsp_devp->chan * 0x60, 0); //clear received element counter
		OUT_REGL(DMA_CCFNi + mcbsp_devp->chan * 0x60, 0); //clear received flame counter
		//disable dma and irq, send resend cmd to sender
		//disable dma irq events
		OUT_REGL(DMA_CICRi + devp->chan * 0x60, 0);
		//disable DMA L1 irq
		CLRBIT_REGL(DMA_IRQENABLE_L1, 1 << devp->chan);
		
		printk(KERN_INFO "@@@@@@@[DMA irq]: there has no buffer\n");
		return IRQ_HANDLED;
	}
	//send async signal to app
	kill_fasync(&devp->fasync_queue,SIGIO,POLL_IN);
	put_read_buffer(devp->read_queue, &devp->current_buffer_info);
	//update current buffer info
	copy_buf_info(&devp->current_buffer_info, buf_info_p);
	//kfree(buf_info_p);
	dmaConfigTransfer(devp->chan, 									//DMA channel
						DMA_WORDS_PER_FRAME, 						//DMA words per frame
						DMA_FRAME_PER_BLOCK, 						//DMA frames per block
						(MY_MCBSP+MCBSPLP_DRR_REG), 				//channel source address
						devp->current_buffer_info.dma_buffer_head, 	//channel destination address
						1, 											//channel source element index
						0, 											//channel source frame index
						1, 											//channel destination element index
						0);											//channel destination frame index
	//clear SDMA IRQ 
	SETBIT_REGL(DMA_CSRi + devp->chan * 0x60, event);
	SETBIT_REGL(DMA_IRQSTATUS_L1, 1<<(devp->chan));
	OUT_REGL(DMA_CDACi + mcbsp_devp->chan * 0x60, 0); //clear current destination addr
	OUT_REGL(DMA_CCENi + mcbsp_devp->chan * 0x60, 0); //clear received element counter
	OUT_REGL(DMA_CCFNi + mcbsp_devp->chan * 0x60, 0); //clear received flame counter
//enable interupt events on channel
//OUT_REGL(DMA_CICRi + devp->chan * 0x60, DMA_FRAME_IE);
	//enable channel
	dmaEnableChannel(devp->chan);
	return IRQ_HANDLED;
}
//-----------------------------

//this dma init not set dma destination addr
//before call ioctl(start), we must call ioctl(set_dma_des) to set dma destination addr
static void dma_init(struct mcbsp_dev *devp) 
{
	int result;
	//reset dma
	dmaDisableChannel(devp->chan);
	//set global para
	OUT_REGL(DMA_GCR, 0x11020);
	//set OCP
	OUT_REGL(DMA_OCP_SYSCONFIG, 0x1028);
	OUT_REGL(DMA_CDACi + devp->chan * 0x60, 0); //clear destination addr
	OUT_REGL(DMA_CCENi + devp->chan * 0x60, 0); //clear destination addr
	dmaSetCsdp(devp->chan, 				//channel to configure
				SRC_LITTLE_ENDIAN, 		//source little endian
				SRC_ENDIAN_ADAPT, 		//
				DST_LITTLE_ENDIAN, 		//destination little endian
				DST_ENDIAN_ADAPT, 		//
				WRITE_POSTED, 			//write with posting
				DST_NO_BURST, 			//disable bursting on the write port
				DST_UNPACKED, 			//destination receives with no pack
				SRC_NO_BURST, 			//disable bursting on the read port
				SRC_UNPACKED, 			//source receives with no pack
				SCALAR_32BITS);			//32bit data
	dmaSetCcr(devp->chan, 
				HIGH_WR_PRIORITY, 		//write with high priority
				EN_BUFF, 				//enable buffering
				TRG_SRC, 				//DMA request is triggered by source
				NO_PREFETCH, 			//disable prefetch mode
				DIS_SUPER, 				//disable supervisor mode
				DIS_TRANS_COPY, 		//disable transparent copy
				DIS_CONST_FILL, 		//disable constant fill
				DST_AMODE_POST_INC, 	//post-increase addressing mode on the write port of channel
				SRC_AMODE_CONST, 		//constant addressing mode on the read port of channel
				DIS_SUSPEND, 			//channel suspend disable
				DIS_CHANNEL, 			//disable channel
				HIGH_RD_PRIORITY, 		//read with high priority
				TRANS_FRAME, 			//frame synchronization
				DMA_MCBSP1_DMA_RX );	//channel sync by mcbsp1 rx
	//clear CSRi
	OUT_REGL(DMA_CSRi + devp->chan * 0x60, 0xffffffff);
	
	//clear irqstatus_L1
	OUT_REGL(DMA_IRQSTATUS_L1, 0xffffffff);  
	  
	//enable channel irq on SDMA_IRQ_L1
	SETBIT_REGL(DMA_IRQENABLE_L1, 1 << devp->chan);
	  
	//enable interupt events on channel
//-------------------	OUT_REGL(DMA_CICRi + devp->chan * 0x60, DMA_FRAME_IE);
	OUT_REGL(DMA_CICRi + devp->chan * 0x60, DMA_BLOCK_IE);
	//enable SDMA_IRQ_L1  to mpu irq
	if((result = request_irq(INT_24XX_SDMA_IRQ1, &dma_irq_handler, 0, "mcbsp_sdma", devp))) 
	{
		printk(KERN_ERR "mcbsp: could not allocate IRQ%d\n", INT_24XX_SDMA_IRQ1);
		return result; 
	}
	return 0;
}

static irqreturn_t mcbsp_irq_handler(int irq, void *dev_id)
{
	unsigned int event;
	//close mcbsp irq
	OUT_REGL(MCBSPLP_IRQENABLE_REG + MY_MCBSP, 0);
	event = IN_REGL(MCBSPLP_IRQSTATUS_REG + MY_MCBSP);
	printk(KERN_INFO "######[mcbsp irq]: event = 0x%x", event);
	if(event & IRQENABLE_RSYNCERREN)
	{
		//clear irq
		SETBIT_REGL(MCBSPLP_IRQSTATUS_REG + MY_MCBSP, IRQENABLE_RSYNCERREN);
		printk(KERN_INFO "######[mcbsp irq]: receive frame error\n");
	}
	else if(event & IRQENABLE_XSYNCERREN)
	{
		//clear irq
		SETBIT_REGL(MCBSPLP_IRQSTATUS_REG + MY_MCBSP, IRQENABLE_XSYNCERREN);
		printk(KERN_INFO "######[mcbsp irq]: send frame error\n");
	}
	else if(event & IRQSTATUS_ROVFLSTAT)
	{
		//clear irq
		SETBIT_REGL(MCBSPLP_IRQSTATUS_REG + MY_MCBSP, IRQSTATUS_ROVFLSTAT);
		printk(KERN_INFO "######[mcbsp irq]: receive buffer overflow\n");
	}
	//open mcbsp irq
	OUT_REGL(MCBSPLP_IRQENABLE_REG + MY_MCBSP, IRQSTATUS_ROVFLSTAT | IRQENABLE_XSYNCERREN | IRQENABLE_RSYNCERREN);
	return IRQ_HANDLED;
}

static int mcbsp_enable_irq(struct mcbsp_dev *devp, unsigned int irq)
{
	int result;
	//enable MCBSP1_IRQ  to mpu irq
	if((result = request_irq(MCBSP1_IRQ, &mcbsp_irq_handler, 0, "mcbsp_irq", devp))) 
	{
		printk(KERN_ERR "[mcbsp enable irq]: could not allocate IRQ%d\n", MCBSP1_IRQ);
		return result; 
	}
	//clear irq
	SETBIT_REGL(MCBSPLP_IRQSTATUS_REG + MY_MCBSP, irq);
	//enable irq
	OUT_REGL(MCBSPLP_IRQENABLE_REG + MY_MCBSP, irq);
	return 0;
}


static int mcbsp_open(struct inode *inode, struct file *filp)
{
	
	struct mcbsp_dev *devp;
	devp = container_of(inode->i_cdev, struct mcbsp_dev, cdev);//get device struct point
	filp->private_data = devp;
	dma_init(devp);//initialize dma
	devp->buffer_queue = init_sdma_buffer_queue(); //init buffer_queue
	devp->read_queue = init_read_buffer_queue(); //init read_queue
	//request mcbsp irq, enable send sync frame error and receive sync frame error interrupt events
	mcbsp_enable_irq(devp, IRQSTATUS_ROVFLSTAT | IRQENABLE_XSYNCERREN | IRQENABLE_RSYNCERREN);
	printk("mcbsp open\n");
	return 0;
}

static int mcbsp_fasync(int mcbsp_fd, struct file *filp,int mode)
{	
	struct mcbsp_dev *devp = filp->private_data;
	return fasync_helper(mcbsp_fd,filp,mode,&devp->fasync_queue);
}

static int mcbsp_release(struct inode *inode, struct file *filep)
{
//------------------
//add codes to reset mcbsp and dma
//------------------
	struct mcbsp_dev *devp = filep->private_data;
	free_irq(INT_24XX_SDMA_IRQ1, devp);
	//remove fasync event
	mcbsp_fasync(-1,filep,0);
	//reset interrupt count
	count = 0;
	//add codes to reset mcbsp_devp
	printk("mcbsp closed\n");
	return 0;
}

static ssize_t mcbsp_read(struct file *filep, unsigned int *buf, size_t count, loff_t *f_pos)
{
	//printk("Reading...\n");
	struct mcbsp_dev *devp = filep->private_data;
	struct dma_buffer_info *read_info;
	unsigned int fasync_block_index = devp->fasync_read_block_index;
	//add init dma_buffer_info code
	//set_dma_buffer_info(devp->dma_buffer_info_array, 1, 64, 0x80000000, 0x80000040, 1);
	//test---------------------
	read_info = (struct dma_buffer_info *)kmalloc(sizeof(struct dma_buffer_info), GFP_KERNEL);
	memset(read_info, 0, sizeof(struct dma_buffer_info));
	get_read_buffer(devp->read_queue, read_info);
	//copy buffer struct to user
	if( copy_to_user(buf, read_info, count) ) {
		printk(KERN_NOTICE "Error in copy to user\n");
		return -EFAULT;
	}
	//free
	kfree(read_info);
	return count;
}


static ssize_t mcbsp_write(struct file *filep, 
							  const unsigned int *user_buf, 
							  size_t size, 
							  loff_t *f_pos)
{

	printk(KERN_INFO "write size = %d" , size);	
  	unsigned int loop = 0;
	unsigned int count = size/4;	
	unsigned int *kernel_buff;
	//kmalloc memory for kernel buffer and initialize it
	kernel_buff = (unsigned int *)kmalloc(size, GFP_KERNEL);
	//reset buffer
	memset(kernel_buff, 0, size);
	if( copy_from_user(kernel_buff, user_buf, size) ) {
		printk(KERN_NOTICE "Error in copy from user\n");
		return -EFAULT;
	}
	//send data
    for (loop=0; loop<count; loop++)
    {
      mcbspDataPut(MY_MCBSP, kernel_buff[loop]);
	  //while (mcbspTxBuffStat(MY_MCBSP) < 128);
      while (mcbspTxBuffStat(MY_MCBSP) > 0);
    }
	//free kernel buffer
	kfree(kernel_buff);
	printk(KERN_INFO "writing completed\n");
	return count;

}


//mcbsp ioctrl
static int mcbsp_ioctrl(struct inode *inodep, struct file *filep, unsigned int cmd, unsigned long *arg)
{
	struct mcbsp_dev *devp = filep->private_data;
	printk(KERN_INFO "cmd = 0x%x", cmd);
	struct dma_buffer_info *buf_info_p;
	//add code to check cmd
	//------------------
	//------------------
	switch(cmd) {
		//set dma buffer args
		case MCBSP_IOC_SET_DMA_DES:
			printk(KERN_INFO "INTO IOCTL SET DMA DES\n");
			unsigned int block_index;
			//kmalloc buffer info struct
			buf_info_p = kmalloc(sizeof(struct dma_buffer_info), GFP_KERNEL);
			if(!buf_info_p) {
				printk(KERN_ERR "ioctrl kmalloc error\n");
				return -ENOMEM;
			}
			memset(buf_info_p, 0, sizeof(struct dma_buffer_info));
			//copy buffer info struct from user space
			if( copy_from_user(buf_info_p, (struct dma_buffer_info *)arg, sizeof(struct dma_buffer_info)) ) {
				printk(KERN_NOTICE "[IOCTL MCBSP_IOC_SET_DMA_DES] copy from user error\n");
				return -EFAULT;
			}
			//reset buffer valid size to 0
			reset_dma_buffer_info(buf_info_p);
			//put dma buffer info struct into buffer queue
			put_sdma_buffer(devp->buffer_queue, buf_info_p);
			break;
			
		//-----------------
		//start DMA and Mcbsp
		case MCBSP_IOC_MCBSPDMA_START:
			//test code--------------------------
			printk(KERN_INFO "INTO IOCTL START");
			print_sdma_buffer_queue(devp->buffer_queue);
			get_sdma_buffer(devp->buffer_queue, &buf_info_p);
			
			dmaConfigTransfer(devp->chan, 						//DMA channel
								DMA_WORDS_PER_FRAME, 			//DMA words per frame
								DMA_FRAME_PER_BLOCK, 			//DMA frames per block
								(MY_MCBSP+MCBSPLP_DRR_REG), 	//source address
								buf_info_p->dma_buffer_head, 	//destination address
								1, 								//channel source element index
								0, 								//channel source frame index
								1, 								//channel destination element index
								0);								//channel destination frame index
								
			//set current buffer info
			copy_buf_info(&devp->current_buffer_info, buf_info_p);
			kfree(buf_info_p);
			//start DMA
			dmaEnableChannel(devp->chan);
			//start mcbsp
			mcbspRemoveResetSrg(MY_MCBSP);
			mcbspRemoveResetFsg(MY_MCBSP);
			mcbspRemoveResetRx(MY_MCBSP);
			mcbspRemoveResetTx(MY_MCBSP);
			//delay 500us
			udelay(500);  //500us
			break;
			
		case MCBSP_IOC_MCBSPDMA_STOP:
			mcbspReset(MY_MCBSP, 1);
			dmaDisableChannel(devp->chan);
			break;
			
		case MCBSP_IOC_DMA_RESTART:
			//enable channel irq on SDMA_IRQ_L1
			SETBIT_REGL(DMA_IRQENABLE_L1, 1 << devp->chan);
			//enable interupt events on channel
//-------------------			OUT_REGL(DMA_CICRi + devp->chan * 0x60, 0x8);
			OUT_REGL(DMA_CICRi + devp->chan * 0x60, DMA_BLOCK_IE);
			//start DMA
			dmaEnableChannel(devp->chan);
			break;
			
		default:
//			printk(KERN_INFO "[ioctl]:CMD fault\n");
			return -EINVAL;
	}
	return 0;
}



//mcbsp operations
static const struct file_operations mcbsp_fops =
{
	.owner = THIS_MODULE,
	.open = mcbsp_open,
	.release = mcbsp_release,
	.read = mcbsp_read,
	.write = mcbsp_write,
	.ioctl = mcbsp_ioctrl,
	.fasync = mcbsp_fasync,
};


//setup mcbsp cdev
static void mcbsp_setup_cdev(struct mcbsp_dev *dev, int index)
{
	
	dmaDisableChannel(mcbsp_devp->chan);
    int err, devno = MKDEV(mcbsp_major, index);
	cdev_init(&dev->cdev, &mcbsp_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &mcbsp_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if(err) {
		printk(KERN_NOTICE "Error %d adding MCBSP%d", err, index);
	}
	
}


static int mcbsp_init(void)
{
	
  
	int result;
	unsigned int loop;
	  
	int status;
	dev_t devno = MKDEV(mcbsp_major, 0);
	if(mcbsp_major) {
		result = register_chrdev_region(devno, 1, "mcbsp");
	}
	else {
		result = alloc_chrdev_region(&devno, 0, 1, "mcbsp");
		mcbsp_major = MAJOR(devno);
	}
	if(result < 0) {
		printk(KERN_NOTICE "Error in allc mcbsp_major\n");
		return result;
	}
	 
	//alloc mcbsp device 
	mcbsp_devp = kmalloc(sizeof(struct mcbsp_dev), GFP_KERNEL);
	if(!mcbsp_devp) {
		result = -ENOMEM;
		goto fail_malloc2;
	}
	memset(mcbsp_devp, 0, sizeof(struct mcbsp_dev));
	 
	//coherent-----------------------------------
	//alloc coherent buffer
	mcbsp_devp->dma_buffer = kmalloc(sizeof(dma_addr_t), GFP_KERNEL);
	memset(mcbsp_devp->dma_buffer, 0, sizeof(dma_addr_t));
	mcbsp_devp->RXBUFF1 = dma_alloc_coherent(NULL, 64, mcbsp_devp->dma_buffer, GFP_DMA);
	if(*(mcbsp_devp->dma_buffer) == NULL) {
		printk(KERN_ERR "dma_alloc_cohrent");
		goto fail_malloc1;
	}
			 
	//setup cdev struct
	mcbsp_setup_cdev(mcbsp_devp, 0);
	//setup mcbsp dev
	mcbsp_setup_dev(mcbsp_devp, devno);
	
	//create device node
	mcbsp_devp->mcbsp_class = class_create(THIS_MODULE, "haolong_mcbsp_class");
	if(IS_ERR(mcbsp_devp->mcbsp_class))
	{
		printk("[INIT]: failed in creating class.\n");
		return -1;
	}
	device_create(mcbsp_devp->mcbsp_class, NULL, devno, NULL, "mcbsp");
	//work queue
	INIT_WORK(&mcbsp_devp->sdma_wq, sdma_do_work);
	//wait queue
	init_waitqueue_head(&mcbsp_devp->wait_q);
	mcbsp_devp->wait_q_flag = 0;
 	
	///////////////////////////////////////MCBSP PART//////////////////////////////////////////////

	// Select clock sources and switch on Switch on the clocks
	cmEnableClock96M(); 
	mcbspEnableIclk(MY_MCBSP);
	mcbspSelectClksSource(MY_MCBSP, INTERNAL_FCLK);
	mcbspEnableFclk(MY_MCBSP);
  
	// reset module
	mcbspReset(MY_MCBSP, 1);  
  
	//mcbspSet4Pin(MY_MCBSP);  // Sets McBSP1 to 4 pin mode. 
	mcbspSet6Pin(MY_MCBSP);  // Sets McBSP1 to 6 pin mode. 
  
	// Configure transmitter and receiver
	mcbspSetRxMode( MY_MCBSP, 			//use mcbsp1
					CLK_EXTERNAL, 		//rx clk comes from external
					CLKR_SAMPLE_FALL, 	//clk sampled at fall edge
					SYNC_EXTERNAL, 		//frame sync signal comes from external
					SYNC_ACTIVE_HIGH, 	//frame sync signal active high
					FULL_CYCLE);  		//full cycle
	mcbspSetTxMode( MY_MCBSP, 			//use mcbsp1
					CLK_INTERNAL, 		//tx clk generate from internal(SRG)
					CLKX_DRIVE_RISE,  	//clk sampled at rise edge
					SYNC_INTERNAL, 		//frame sync signal generate from internal(SRG)
					SYNC_ACTIVE_HIGH, 	//frame sync signal active high
					HALF_CYCLE, 		//half cycle
					DXENA_OFF, 			//dx enabler is off---------------------------------------
					XCLK_FREE, 			//external clk gating disable
					FSX_GATED);			//Transmit frame-sync signal (FSX) is generated when transmit buffer is not empty.
  // Set up frames
	mcbspRxFrameSetup(MY_MCBSP, 			//use mcbsp1
					SINGLE_PHASE, 			//Rx single phase
  					MSB_FIRST, 				//Rx MSB
  					DELAY_1BIT, 			//Rx delay 1bit
  					MCBSP_WORDS_PER_FRAME, 	//configure Rx words per frame
  					MCBSP_BITS_PER_WORD, 	//configure Rx bytes per word
  					MCBSP_WORDS_PER_FRAME, 	//configure Rx words per frame
  					MCBSP_BITS_PER_WORD, 	//configure Rx bytes per word
  					RIGHT_JUST_ZERO); 		//Right-justify and zero-fill MSBs in DRR
	mcbspTxFrameSetup(MY_MCBSP, 			//use mcbsp1
  					SINGLE_PHASE, 			//Tx single phase
  					MSB_FIRST, 				//Tx MSB
  					DELAY_1BIT, 			//Tx delay 1bit
  					MCBSP_WORDS_PER_FRAME, 	//configure Tx words per frame
  					MCBSP_BITS_PER_WORD, 	//configure Tx bytes per word
  					MCBSP_WORDS_PER_FRAME, 	//configure Tx words per frame
  					MCBSP_BITS_PER_WORD);	//configure Tx bytes per word
	// Program the Sample Rate generator  
	mcbspSetupSrg(MY_MCBSP, CLKS, CLKS_RISE, SRG_FREE, MCBSP_FRAME_PERIOD, 1, MCBSP_CLKDV);
	printk(KERN_INFO "[INIT]: MCBSPLP_SRGR2_REG = 0x%x", IN_REGL(MCBSPLP_SRGR2_REG + MY_MCBSP));
  
	// Configure the loopback 
	mcbspLoopback(MY_MCBSP, NO_LOOPBACK);

	// Set the buffer thresholds
	mcbspSetRxThresh(MY_MCBSP, MCBSP_THRSHOLD_RX);
//	mcbspSetTxThresh(MY_MCBSP, MCBSP_THRSHOLD_TX);
	mcbspDisableTxDma(MY_MCBSP);
	mcbspEnableRxDma(MY_MCBSP);
	// Delay to allow settings to sync
	udelay(500);  //500us
	
	
//	SETBIT_REGL(MCBSPLP_PCR_REG + MY_MCBSP, 0x2000); 	//set dx as general purpose output, clkx gpio, fsx gpio
//	// Configure the pins
//	OUT_REGL(CONTROL_PADCONF_MCBSP1_CLKR, 0x01000100);  // 31:16 = mcbsp1_fsr         15:0 = mcbsp1_clkr
//	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_DX, 0xFFFF0000);	// 31:16 = mcbsp1_dr
//	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_DX, 0x01000000);
//	CLRBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS, 0xFFFF);	//15:0 =mcbsp_clks
//	SETBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS, 0x0100);
//	
//	CLRBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS, 0xFFFF);	//31:16 =mcbsp1_fsx, input enable, mode4-gpio
//	SETBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS, 0x0114);
//	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_CLKX, 0xFFFF);   // 15:0 = mcbsp1_clkx, input enable, mode4-gpio
//	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_CLKX, 0x0114);  
//	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_DX, 0x0000FFFF);	// 15:0 = mcbsp1_dx, input enable, mode4-gpio
//	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_DX, 0x00000114);

//	OUT_REGL(0x49058034, 0);
//	printk(KERN_INFO "GPIO5_OE = 0x%x", IN_REGL(0x49056034));
//	OUT_REGL(0x4905803c, 0x0);
//	printk(KERN_INFO "GPIO5_DATAOUT = 0x%x", IN_REGL(0x4905603c));
	// Configure the pins
	OUT_REGL(CONTROL_PADCONF_MCBSP1_CLKR, 0x01180118);  // 31:16 = mcbsp1_fsr, input enable, pullup         15:0 = mcbsp1_clkr, input enable, pullup
	OUT_REGL(CONTROL_PADCONF_MCBSP1_DX, 0x01180000);	// 31:16 = mcbsp1_dr          15:0 = mcbsp1_dx                    
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_CLKX, 0xFFFF);   // 31:16 = uart3_cts_rctx     15:0 = mcbsp1_clkx
	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_CLKX, 0x0000);   // 31:16 = uart3_cts_rctx     15:0 = mcbsp1_clkx
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS, 0xFFFF);   // 31:16 = uart3_cts_rctx     15:0 = mcbsp1_clkx
	SETBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS, 0x0118);   // 31:16 = uart3_cts_rctx     15:0 = mcbsp1_clkx
	printk(KERN_NOTICE "hello mcbsp!!\n");
	return 0;
	fail_malloc1:  
  				//kfree(mcbsp_devp->RXBUFF1);
  				kfree(mcbsp_devp->dma_buffer);
	  			kfree(mcbsp_devp);
	fail_malloc2: 
  			   unregister_chrdev_region(devno, 1);
               return result;
}  

static void mcbsp_exit(void)
{
	mcbspReset(MY_MCBSP, 1);
    mcbspDisableRxDma(MY_MCBSP);
	mcbspDisableFclk(MY_MCBSP);
	mcbspDisableIclk(MY_MCBSP);
	cmDisableClock96M();
	device_destroy(mcbsp_devp->mcbsp_class, mcbsp_devp->devno);
	class_destroy(mcbsp_devp->mcbsp_class);
	cdev_del(&mcbsp_devp->cdev);
	//omap_free_dma(mcbsp_devp->chan);
	dma_free_coherent(NULL, 64, mcbsp_devp->RXBUFF1, mcbsp_devp->dma_buffer);
	kfree(mcbsp_devp->dma_buffer);
	kfree(mcbsp_devp);
	unregister_chrdev_region(MKDEV(mcbsp_major, 0), 1);
    printk(KERN_INFO "goodbye mcbsp\n");
}
MODULE_AUTHOR("haolong");
MODULE_LICENSE("GPL");
module_init(mcbsp_init);
module_exit(mcbsp_exit);
