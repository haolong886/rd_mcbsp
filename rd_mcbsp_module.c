/* 
add introduce
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

#include <linux/fs.h>

#include <linux/irq.h>
#include <plat/irqs.h>
//dma
#include <plat/dma.h>
//copy from user
#include <asm/uaccess.h> 

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
//gpio request
#include <asm-generic/gpio.h>


#include "rd_mcbsp_reg.h"
#include "rd_prcm_reg.h"
#include "rd_ctl_reg.h"
#include "rd_reg_op.h"
#include "rd_mcbsp_lib.h"
#include "rd_dma_reg.h"
#include "rd_dma_lib.h"
#include "rd_buf_lib.h"
#include "rd_gpio_i2c.h"

#define MCBSP_DEBUG

#ifdef MCBSP_DEBUG
#define MCSBP_DBG(...)			(printk(KERN_INFO __VA_ARGS__))
#else
#define MCSBP_DBG(...)
#endif

#define MCBSP_ERR_MSG(...)		(printk(KERN_ERR __VA_ARGS__))

#define VER								"v0.15"

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

//---------------------------ioctrl cmd-------------------------------------------
#define MCBSP_IOC_MAGIC 				'k'
//cmd of setting dma destination addr
#define MCBSP_IOC_SET_DMA_DES 			_IOW(MCBSP_IOC_MAGIC, 1, unsigned int*) 
//cmd of start mcbsp and dma
#define MCBSP_IOC_MCBSPDMA_START   		_IO(MCBSP_IOC_MAGIC, 2)
//cmd of stop mcbsp and dma
#define MCBSP_IOC_MCBSPDMA_STOP    		_IO(MCBSP_IOC_MAGIC, 3)
//cmd of restart mcbsp and dma after has buffer to dma
#define MCBSP_IOC_DMA_RESTART   		_IO(MCBSP_IOC_MAGIC, 4)
//cmd of getting fpga reg status
#define GET_REG_STATUS 					_IOWR(MCBSP_IOC_MAGIC, 5, unsigned int*) 
//cmd of setting fpga reg
#define SET_REG 						_IOW(MCBSP_IOC_MAGIC, 6, unsigned int*) 
//cmd to complete mcbsp and dma configure
#define MCBSP_IOC_MCBSPDMA_COMPLETE		_IO(MCBSP_IOC_MAGIC, 7)
//cmd to destroy loop buffer and init a new loop buffer link
#define MCBSP_IOC_RESET_BUFFER			_IO(MCBSP_IOC_MAGIC, 8)

//@@@@@@@@@@@@@@add more cmd to here@@@@@@@@@@@@@@@@@@@@@@@

#define MCBSP_IOC_MAXNR 				10 //max number of cmd
//--------------------------------------------------------------------------------

#define MY_MCBSP  						MCBSP1
#define MCBSP_MAJOR 					30


#define MCBSP_BASE_ADDR					mcbsp_devp->mcbsp_base_addr
#define DMA_BASE_ADDR					mcbsp_devp->dma_base_addr
//mcbsp register API
#define MCBSP_OUTL(offSet, value)		OUT_REGL(offSet + MCBSP_BASE_ADDR, value)
#define MCBSP_INL(offSet)				IN_REGL(offSet + MCBSP_BASE_ADDR)
#define MCBSP_SETBIT(dest, mask)		SETBIT_REGL(dest + MCBSP_BASE_ADDR,mask)
#define MCBSP_CLRBIT(dest, mask)        CLRBIT_REGL(dest + MCBSP_BASE_ADDR,mask)

//dma register API
#define DMA_OUTL(offSet, value)			OUT_REGL(offSet + DMA_BASE_ADDR, value)
#define DMA_INL(offSet)					IN_REGL(offSet + DMA_BASE_ADDR)
#define DMA_SETBIT(dest, mask)			SETBIT_REGL(dest + DMA_BASE_ADDR, mask)
#define DMA_CLRBIT(dest, mask)			CLRBIT_REGL(dest + DMA_BASE_ADDR, mask)

#define CHAN_N                          2
//global args
int mcbsp_major = MCBSP_MAJOR;			//major device number
struct mcbsp_dev *mcbsp_devp;	//



//mcbsp device struct
struct mcbsp_dev 
{
	struct cdev cdev;                                   //character device struct
	int chan[CHAN_N];                                   //allocated dma channel
	unsigned int mcbsp_base_addr;                       //McBSP register base address after ioremap
	unsigned int dma_base_addr;                         //DMA register base address after ioremap
	unsigned int fclk_addr;                             //McBSP function clock address after ioremap
	unsigned int iclk_addr;                             //McBSP interface clock address after ioremap
	unsigned int control_general_base;                  //control register base address after ioremap
	unsigned int fclk_core_addr;                        //core function clock address after ioremap
	unsigned int pad_base;                              //SoC pad base address after ioremap
	struct dma_buffer_info *current_buffer_info;        //reserved
	struct fasync_struct *fasync_queue;                 //file async struct
	struct class *mcbsp_class;                          //device class struct
	unsigned int devno;                                 //device No.
	loop_buffer_t *loop_buffer;                         //dma buffer info put in this loop link table
	unsigned int opened;                                //to avoid openning this device before another process released
	unsigned int dma_des_ready_flag;
};


static int mcbsp_setup_dev(struct mcbsp_dev *devp, unsigned int devno) 
{
    int chan_num = 0;
	//ioremap mcbsp io base addr to virtual addr
	devp->mcbsp_base_addr 		= (unsigned int)ioremap(MY_MCBSP, SZ_4K);
	devp->fclk_addr 			= (unsigned int)ioremap(CM_CLKSEL1_PLL, SZ_4K);
	devp->iclk_addr 			= (unsigned int)ioremap(CM_ICLKEN1_CORE, SZ_4K);
	devp->control_general_base 	= (unsigned int)ioremap(GENERAL_BASE, SZ_4K);
	devp->fclk_core_addr 		= (unsigned int)ioremap(CM_FCLKEN1_CORE, SZ_4K);
	devp->pad_base 				= (unsigned int)ioremap(PADCONFS_BASE, SZ_4K);
	//init dma register base addr
 	mcbsp_devp->dma_base_addr = (unsigned int)dma_base_addr_init();

    //request 4 DMA channels
    for (chan_num = 0; chan_num < CHAN_N; chan_num++)
    {
    	if(omap_request_dma(11, "mcbsp_dma", NULL, NULL, &devp->chan[chan_num]) < 0)
    	{
    		MCBSP_ERR_MSG("[MCBSP SETUP DEV]: channel cann't request\n");
            for (; chan_num >=0; chan_num--)
            {
                omap_free_dma(devp->chan[chan_num]);
            }
            return -1;
    	}
    }	
    //system omap DMA init as all channel request interrupt at SDMA_IRQ_L0
	//in order to avoid spurious DMA irq, we disable allocated channel irq at SDMA_IRQ_L0
	for (chan_num = 0; chan_num < CHAN_N; chan_num++)
    {
        DMA_CLRBIT(DMA_IRQENABLE_L0, (1 << devp->chan[chan_num]));
    }   
    
	//store mcbsp device number
	devp->devno = devno;
    
	//initialize open count
	mcbsp_devp->opened = 0;

	//initialize dma ready flag
	mcbsp_devp->dma_des_ready_flag = 0;
    
	return 0;
}


//-----------------
static irqreturn_t dma_irq_handler(int irq, void *dev_id) {
//    MCSBP_DBG("time1 = %u ms\n", jiffies_to_msecs(jiffies));
	unsigned int event, val, dma_irq;
    int chan_num = 0;
	struct mcbsp_dev *devp = dev_id;
    
	val = DMA_INL(DMA_IRQSTATUS_L1);
	if (0 == val) {
		if (printk_ratelimit())
			printk(KERN_WARNING "Spurious McBSP_DMA IRQ\n");
		return IRQ_HANDLED;
	}
    
	dma_irq = DMA_INL(DMA_IRQSTATUS_L1);
    for (chan_num = 0; chan_num < CHAN_N; chan_num++)
    {
//        MCSBP_DBG("for loop %d times\n", chan_num);
    	if(dma_irq & (1 << devp->chan[chan_num]))
    	{
    		event = DMA_INL(DMA_CSRi + devp->chan[chan_num] * 0x60);
    		//send async signal to app
    		kill_fasync(&devp->fasync_queue,SIGIO,POLL_IN);
//added for test by haolong, 2012/04/12			
//			if (printk_ratelimit()) 	//avoid exhausting cpu time
//			{	   
//				MCBSP_ERR_MSG("[DMA IRQ]: send signal!\n");
//			}
//--------------------------------			
    		//clear SDMA IRQ 
    		DMA_SETBIT(DMA_CSRi + devp->chan[chan_num] * 0x60, DMA_BLOCK_IE);
    		DMA_SETBIT(DMA_IRQSTATUS_L1, (1 << devp->chan[chan_num]));
//            MCSBP_DBG("channel %d\n", devp->chan[chan_num]);
    	}
    }
//    MCSBP_DBG("time2 = %u ms\n", jiffies_to_msecs(jiffies));
	return IRQ_HANDLED;
}

//this dma init not set dma destination addr
//before call ioctl(start), we must call ioctl(set_dma_des) to set dma destination addr
static int dma_init(struct mcbsp_dev *devp) 
{
	int result, chan_num;

    
	//set global para
	DMA_OUTL(DMA_GCR, 0x11020);
	//set OCP
	DMA_OUTL(DMA_OCP_SYSCONFIG, 
	        DMA_NO_STANDBY | DMA_ICLK_NO_OFF | DMA_FCLK_NO_OFF | DMA_EMUFREE | DMA_NO_IDLE | DMA_NO_AUTOIDLE);
    for (chan_num = 0; chan_num < CHAN_N; chan_num++)
    {  
        //reset dma
        dmaDisableChannel(devp->chan[chan_num]);
        //clear DMA received element count
        DMA_OUTL(DMA_CCENi + devp->chan[chan_num] * 0x60, 0); //
        //configure allocated 4 DMA channels
        dmaSetCsdp(devp->chan[chan_num],               //channel to configure
                    SRC_LITTLE_ENDIAN,      //source little endian
                    SRC_ENDIAN_ADAPT,       //
                    DST_LITTLE_ENDIAN,      //destination little endian
                    DST_ENDIAN_ADAPT,       //
                    WRITE_POSTED,           //write with posting
//                    WRITE_NON_POSTED,
                    DST_NO_BURST,           //disable bursting on the write port
                    DST_UNPACKED,           //destination receives with no pack
                    SRC_NO_BURST,           //disable bursting on the read port
                    SRC_UNPACKED,           //source receives with no pack
                    SCALAR_32BITS);         //32bit data
        dmaSetCcr(devp->chan[chan_num], 
                    HIGH_WR_PRIORITY,       //write with high priority
                    EN_BUFF,                //enable buffering
                    TRG_SRC,                //DMA request is triggered by source
                    NO_PREFETCH,            //disable prefetch mode
                    DIS_SUPER,              //disable supervisor mode
                    DIS_TRANS_COPY,         //disable transparent copy
                    DIS_CONST_FILL,         //disable constant fill
                    DST_AMODE_POST_INC,     //post-increase addressing mode on the write port of channel
                    SRC_AMODE_CONST,        //constant addressing mode on the read port of channel
                    DIS_SUSPEND,            //channel suspend disable
                    DIS_CHANNEL,            //disable channel
                    HIGH_RD_PRIORITY,       //read with high priority
                    TRANS_FRAME,            //frame synchronization
                    DMA_MCBSP1_DMA_RX );    //channel sync by mcbsp1 rx
    	//clear allocated channel interrupt status register
    	DMA_OUTL(DMA_CSRi + devp->chan[chan_num] * 0x60, 0xffffffff);
        //clear allocated dma channel irq status on SDMA_IRQ_L1
        DMA_SETBIT(DMA_IRQSTATUS_L1, (1 << mcbsp_devp->chan[chan_num]));  
        //enable allocated dma channel irq at SDMA_IRQ_L1   
        DMA_SETBIT(DMA_IRQENABLE_L1, (1 << mcbsp_devp->chan[chan_num]));
        //enable interupt events on channel11
        DMA_OUTL(DMA_CICRi + devp->chan[chan_num] * 0x60, DMA_BLOCK_IE);
    }
	
	//loop all DMA channels
	for (chan_num = 0; chan_num < CHAN_N - 1; chan_num++)
    {   
	    dmaSetChannelLink(devp->chan[chan_num], devp->chan[chan_num + 1], EN_CHAN_LINK);
    }
	dmaSetChannelLink(devp->chan[chan_num], devp->chan[0], EN_CHAN_LINK);
	  
	//enable SDMA_IRQ_L1  to mpu irq
	if((result = request_irq(INT_24XX_SDMA_IRQ1, &dma_irq_handler, 0, "mcbsp_sdma", devp))) 
	{
		MCBSP_ERR_MSG("mcbsp: could not allocate IRQ%d\n", INT_24XX_SDMA_IRQ1);
		return result; 
	}
	
	return 0;
}

static irqreturn_t mcbsp_irq_handler(int irq, void *dev_id)
{
	unsigned int event;
	//close mcbsp irq
	MCBSP_OUTL(MCBSPLP_IRQENABLE_REG, 0);
	event = MCBSP_INL(MCBSPLP_IRQSTATUS_REG);
    
	if(event & IRQENABLE_RSYNCERREN)
	{
		//clear irq
		MCBSP_SETBIT(MCBSPLP_IRQSTATUS_REG, IRQENABLE_RSYNCERREN);       
		if (printk_ratelimit())     //avoid exhausting cpu time
        {      
		    MCBSP_ERR_MSG("[MCBSP IRQ]: receive frame error\n");
        }
	}
	else if(event & IRQENABLE_XSYNCERREN)
	{
		//clear irq
		MCBSP_SETBIT(MCBSPLP_IRQSTATUS_REG, IRQENABLE_XSYNCERREN);
		if (printk_ratelimit())     //avoid exhausting cpu time
        {      
		    MCBSP_ERR_MSG("[MCBSP IRQ]: send frame error\n");
        }
	}
	else if(event & IRQSTATUS_ROVFLSTAT)
	{
		//clear irq
		MCBSP_SETBIT(MCBSPLP_IRQSTATUS_REG, IRQSTATUS_ROVFLSTAT);        
		if (printk_ratelimit())     //avoid exhausting cpu time
        {      
		    MCBSP_ERR_MSG("[MCBSP IRQ]: receive buffer overflow\n");
        }
	}
	//open mcbsp irq
	MCBSP_OUTL(MCBSPLP_IRQENABLE_REG, IRQSTATUS_ROVFLSTAT | IRQENABLE_XSYNCERREN | IRQENABLE_RSYNCERREN);
	return IRQ_HANDLED;
}

static int mcbsp_enable_irq(struct mcbsp_dev *devp, unsigned int irq)
{
	int result;
	//enable MCBSP1_IRQ  to mpu irq
	if((result = request_irq(MCBSP1_IRQ, &mcbsp_irq_handler, 0, "mcbsp_irq", devp))) 
	{
		MCBSP_ERR_MSG("[mcbsp enable irq]: could not allocate IRQ%d\n", MCBSP1_IRQ);
		return result; 
	}
	//clear irq
	MCBSP_SETBIT(MCBSPLP_IRQSTATUS_REG, irq);
	//enable irq
	MCBSP_OUTL(MCBSPLP_IRQENABLE_REG, irq);
	return 0;
}

void mcbsp_disable_irq(struct mcbsp_dev *devp, unsigned int irq)
{
	//free irq
	free_irq(MCBSP1_IRQ, devp);
	//disable irq
	MCBSP_CLRBIT(MCBSPLP_IRQENABLE_REG, irq);
	//clear irq
	MCBSP_SETBIT(MCBSPLP_IRQSTATUS_REG, irq);
}


static int mcbsp_open(struct inode *inode, struct file *filp)
{
	
	struct mcbsp_dev *devp;
	devp = container_of(inode->i_cdev, struct mcbsp_dev, cdev);//get device struct point
	filp->private_data = devp;
    
	//avoid 2 and more app open mcbsp
	devp->opened++;
	if(1 != devp->opened)
	{
		MCSBP_DBG("[McBSP OPEN]:McBSP is in use!!!\n");
		return -1;
	}
    
	//initialize dma
	dma_init(devp);
    
    //init loop_buffer
	devp->loop_buffer = init_loop_buffer(); 
    
	//request mcbsp irq, enable send sync frame error and receive sync frame error interrupt events
	mcbsp_enable_irq(devp, IRQSTATUS_ROVFLSTAT | IRQENABLE_XSYNCERREN | IRQENABLE_RSYNCERREN);
    
	MCSBP_DBG("[MCBSP OPEN]: McBSP opened\n");
	return 0;
}

static int mcbsp_fasync(int mcbsp_fd, struct file *filp,int mode)
{	
	struct mcbsp_dev *devp = filp->private_data;
	return fasync_helper(mcbsp_fd,filp,mode,&devp->fasync_queue);
}

static int mcbsp_release(struct inode *inode, struct file *filep)
{
	
	struct mcbsp_dev *devp = filep->private_data;
    int chan_num;
	//reset mcbsp and dma
    mcbspReset(MCBSP_BASE_ADDR, 1);

    //disable all channel
    for (chan_num = 0; chan_num < CHAN_N; chan_num++)
    {         
        dmaDisableChannel(devp->chan[chan_num]);
    }
    
	//remove fasync event
	mcbsp_fasync(-1,filep,0);

	//free loop buffer
	distroy_loop_buffer(devp->loop_buffer);
    
	//free dma irq
	free_irq(INT_24XX_SDMA_IRQ1, devp);
    
	//free mcbsp irq
	mcbsp_disable_irq(devp, IRQSTATUS_ROVFLSTAT | IRQENABLE_XSYNCERREN | IRQENABLE_RSYNCERREN);
    
	//reset open count
	devp->opened = 0;
	MCSBP_DBG("[MCBSP RELEASE]: McBSP closed\n");
	return 0;
}

static ssize_t mcbsp_read(struct file *filep, unsigned int *buf, size_t count, loff_t *f_pos)
{
	//printk("Reading...\n");
//	struct mcbsp_dev *devp = filep->private_data;
//	unsigned int reg_status;
//	reg_status = receive_data(GPIO_CLKX, GPIO_DX);
//	printk(KERN_INFO "[mcbsp read]: reg_status = 0x%x\n", reg_status);
//	//copy buffer struct to user
//	if( copy_to_user(buf, &reg_status, sizeof(unsigned int)) ) {
//		printk(KERN_NOTICE "Error in copy to user\n");
//		return -EFAULT;
//	}
//	return count;
	return -EFAULT;
}


static ssize_t mcbsp_write(struct file *filep, 
							  const unsigned int *user_buf, 
							  size_t size, 
							  loff_t *f_pos)
{

	u8 *kernel_buff;
	
	//kmalloc memory for kernel buffer and initialize it
	kernel_buff = kmalloc(size, GFP_KERNEL);
	//reset buffer
	memset(kernel_buff, 0, size);
	if( copy_from_user(kernel_buff, user_buf, size) ) {
		MCBSP_ERR_MSG("Error in copy from user\n");
		return -EFAULT;
	}
	
	//send table
	if(write_table2fpga(kernel_buff, size) < 0)
	{
		MCBSP_ERR_MSG("[MCBSP_WRITE]: write LUT to FPGA error\n");
		return -1;
	}
	
	//free kernel buffer
	kfree(kernel_buff);
	return size;

}


//mcbsp ioctrl
static int mcbsp_ioctrl(struct inode *inodep, struct file *filep, unsigned int cmd, unsigned long *arg)
{
	struct mcbsp_dev *devp = filep->private_data;
//	printk(KERN_INFO "cmd = 0x%x", cmd);
	struct dma_buffer_info *buf_info_p;
	unsigned int fifo_data;
    int chan_num = 0;
	u16 reg_info;	//[6:0] = addr, [7] = R/W bit, R bit will be set in get_reg()
	u16 data;	//[7:0] = reg data, [14:8] = reg addr, [15] = R/W bit, W bit will be set in set_reg()
	//add code to check cmd
	//------------------
	//------------------
	switch(cmd) 
	{
		//get dma buffer info
		case MCBSP_IOC_SET_DMA_DES:
        {
			MCSBP_DBG("[MCBSP IOCTL]: MCBSP_IOC_SET_DMA_DES\n");
			//kmalloc buffer info struct
			buf_info_p = kmalloc(sizeof(struct dma_buffer_info), GFP_KERNEL);
			if(!buf_info_p) {
				MCBSP_ERR_MSG("[MCBSP IOCTL MCBSP_IOC_SET_DMA_DES]:kmalloc error\n");
				return -ENOMEM;
			}
			memset(buf_info_p, 0, sizeof(struct dma_buffer_info));
			//copy buffer info struct from user space
			if( copy_from_user(buf_info_p, (struct dma_buffer_info *)arg, sizeof(struct dma_buffer_info)) ) {
				MCBSP_ERR_MSG("[MCBSP IOCTL MCBSP_IOC_SET_DMA_DES]:copy from user error\n");
				return -EFAULT;
			}
			//reset buffer valid size to 0
			reset_dma_buffer_info(buf_info_p);

			//check buffer size
			if(0 == buf_info_p->dma_buffer_block_size)
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL MCBSP_IOC_SET_DMA_DES]:\nbuffer from user space error, buffer size = 0\n");
				return -1;
			}
			if(buf_info_p->dma_buffer_block_size % 256)
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL MCBSP_IOC_SET_DMA_DES]:\nbuffer from user space error, buffer size %% 256 != 0\n");
				return -1;
			}
			if(buf_info_p->dma_buffer_head < 0x80000000)
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL MCBSP_IOC_SET_DMA_DES]:\nbuffer from user space error,\ndma_buffer_head = 0x%x,\ndma_buffer_head < 0x80000000\n",
									buf_info_p->dma_buffer_head);
				return -1;
			}

			print_dma_buf_info(buf_info_p);
			//put dma buffer info struct into buffer queue
			put_loop_buffer(devp->loop_buffer, buf_info_p);
			break;
        }
		
		//after initializing loop buffer link table, use MCBSP_IOC_MCBSPDMA_COMPLETE to configure DMA channel
		case MCBSP_IOC_MCBSPDMA_COMPLETE:
        {
			MCSBP_DBG("[MCBSP IOCTL]: MCBSP_IOC_MCBSPDMA_COMPLETE\n");

			//check if there are two buffer in loop_buffer
			if(2 != get_loop_buffer_num(devp->loop_buffer))
			{
				MCSBP_DBG("[MCBSP IOCTL MCBSP_IOC_MCBSPDMA_COMPLETE]: error, loop_buffer has %d buffer,\nplease set two buffer\n", 
					get_loop_buffer_num(devp->loop_buffer));
				return -1;

			}

            for (chan_num = 0; chan_num < CHAN_N; chan_num++)
            {
                //get buffer struct from loop_buffer link table
    			get_loop_buffer(devp->loop_buffer, &buf_info_p);
                //configure DMA channel 1 and 2 transfer arguments
    			MCSBP_DBG("[MCBSP IOCTL MCBSP_IOC_MCBSPDMA_COMPLETE]: set channel %d des to buffer %d\n", 
    			        devp->chan[chan_num],
    			        buf_info_p->dma_buffer_block_index);
    			dmaConfigTransfer(devp->chan[chan_num],				                //DMA channel
    								DMA_WORDS_PER_FRAME,			                //DMA words per frame
    								buf_info_p->dma_buffer_block_size / 256,        //DMA frames per block
    								(MY_MCBSP+MCBSPLP_DRR_REG), 	                //source address
    								buf_info_p->dma_buffer_head,	                //destination address
    								1,								                //channel source element index
    								0,								                //channel source frame index
    								1,								                //channel destination element index
    								0); 							                //channel destination frame index
            }

			//set ready flag, check it before MCBSP_IOC_MCBSPDMA_START
			devp->dma_des_ready_flag = 1;
			break;
        }
		
        //use this cmd to start McBSP transfer
		case MCBSP_IOC_MCBSPDMA_START:
        {
			MCSBP_DBG("[MCBSP IOCTL]: MCBSP_IOC_MCBSPDMA_START\n");
			if(devp->dma_des_ready_flag == 0)
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL MCBSP_IOC_MCBSPDMA_START]:\nerror, didn't call MCBSP_IOC_MCBSPDMA_COMPLETE, cann't start\n");
				return -1;
			}
			
			//start DMA
			dmaEnableChannel(devp->chan[0]);
			//enable mcbsp
			mcbspRemoveResetRx(MCBSP_BASE_ADDR);
			//delay 500us
//			udelay(500);  //500us
			break;
        }  
        
		//use this cmd to stop McBSP transfer, discard data remain in McBSP receive FIFO	
		case MCBSP_IOC_MCBSPDMA_STOP:
        {
			MCSBP_DBG("[MCBSP IOCTL]: MCBSP_IOC_MCBSPDMA_STOP\n");
			fifo_data = MCBSP_INL(MCBSPLP_RBUFFSTAT_REG);
//			printk("[MCBSP IOCTL MCBSP_IOC_MCBSPDMA_STOP]: before fifo data = %d\n", fifo_data);
			mcbspResetRx(MCBSP_BASE_ADDR);

            //disable all channel
			for (chan_num = 0; chan_num < CHAN_N; chan_num++)
            {         
    			dmaDisableChannel(devp->chan[chan_num]);
            }
			//must re-configure channel loop, otherwise channel will not be loop
            //loop all DMA channels
            for (chan_num = 0; chan_num < CHAN_N - 1; chan_num++)
            {   
                dmaSetChannelLink(devp->chan[chan_num], devp->chan[chan_num + 1], EN_CHAN_LINK);
            }
            dmaSetChannelLink(devp->chan[chan_num], devp->chan[0], EN_CHAN_LINK);
			
			fifo_data = MCBSP_INL(MCBSPLP_RBUFFSTAT_REG);
//			printk("[MCBSP IOCTL MCBSP_IOC_MCBSPDMA_STOP]: after fifo data = %d\n", fifo_data);
			break;
        }

        case MCBSP_IOC_RESET_BUFFER:
        {
			MCSBP_DBG("[MCBSP IOCTL]: MCBSP_IOC_RESET_BUFFER\n");
            //free loop buffer
            distroy_loop_buffer(devp->loop_buffer);
            //init loop_buffer
            devp->loop_buffer = init_loop_buffer(); 
			//reset dma ready flag
			devp->dma_des_ready_flag = 0;
			break;
        }
        
        /*read FPGA register status
                  FPGA register address comes from "arg"
                  FPGA register status also returned through "arg"
              */
		case GET_REG_STATUS:
        {
			MCSBP_DBG("[MCBSP IOCTL]:GET_REG_STATUS\n");
            
            //get FPGA register address from user space
			if( copy_from_user(&reg_info, (u16 *)arg, sizeof(u16)) ) 
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL GET_REG_STATUS]:Copy from user error\n");
				return -EFAULT;
			}

			//read fpga register status
			if(get_reg(&reg_info) < 0)
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL GET_REG_STATUS]:Read reg status from FPGA error\n");
				return -EFAULT;
			}
			MCSBP_DBG("[MCBSP IOCTL GET_REG_STATUS]:Read from FPGA completed, reg status = 0x%x\n", reg_info);
			
			//return read register status to user space through pointer "arg"
			if( copy_to_user((u16 *)arg, &reg_info, sizeof(u16)) )
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL GET_REG_STATUS]:Error in copy to user\n");
				return -EFAULT;
			}
			break;
        }   
        
		/*set FPGA register*/	
		case SET_REG:
        {
			MCSBP_DBG("[MCBSP IOCTL]:SET_REG\n");
			if( copy_from_user(&data, (u16 *)arg, sizeof(u16)) ) 
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL SET_REG]:Copy from user error\n");
				return -EFAULT;
			}
			//set reg
			if(set_reg(data) < 0)
			{
				MCBSP_ERR_MSG("[MCBSP IOCTL SET_REG]:Set reg error\n");
				return -EFAULT;
			}
			break;
        }  
        
		case MCBSP_IOC_DMA_RESTART:
            //add codes
		default:
			MCBSP_ERR_MSG("[MCBSP IOCTL]:CMD fault\n");
			return -EINVAL;
	}
	return 0;
}



//mcbsp operations
static const struct file_operations mcbsp_fops =
{
	.owner		= THIS_MODULE,
	.open 		= mcbsp_open,
	.release 	= mcbsp_release,
	.read 		= mcbsp_read,
	.write		= mcbsp_write,
	.ioctl 		= mcbsp_ioctrl,
	.fasync 	= mcbsp_fasync,
};


//setup mcbsp cdev
static int mcbsp_setup_cdev(struct mcbsp_dev *dev, int index)
{
    int err;
	int devno = MKDEV(mcbsp_major, index);
	cdev_init(&dev->cdev, &mcbsp_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &mcbsp_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if(err) {
		MCBSP_ERR_MSG("Error %d adding MCBSP%d", err, index);
		return -1;
	}
	return 0;
}

static void mcbsp_reg_init(struct mcbsp_dev *devp)
{
    // Select clock sources and switch on Switch on the clocks
    CLRBIT_REGL(devp->fclk_addr, CM_CLKSEL1_PLL_SOURCE_96M);

    //enable iclk
    SETBIT_REGL(devp->iclk_addr, CM_ICLKEN1_CORE_EN_MCBSP1);

    //select clks source as internal fclk
    CLRBIT_REGL(CONTROL_DEVCONF0 + devp->control_general_base, CONTROL_DEVCONF0_MCBSP1_CLKS);

    //enable fclk
    SETBIT_REGL(devp->fclk_core_addr, CM_FCLKEN1_CORE_EN_MCBSP1);

    // reset module
    mcbspReset(MCBSP_BASE_ADDR, 1);  

    // Sets McBSP1 to 6 pin mode. 
    CLRBIT_REGL(CONTROL_DEVCONF0 + devp->control_general_base, CONTROL_DEVCONF0_MCBSP1_CLKR);
    CLRBIT_REGL(CONTROL_DEVCONF0 + devp->control_general_base, CONTROL_DEVCONF0_MCBSP1_FSR);   

    // Configure transmitter and receiver
    mcbspSetRxMode( MCBSP_BASE_ADDR,            //use mcbsp1
                  CLK_EXTERNAL,       //rx clk comes from external
                  CLKR_SAMPLE_FALL,   //clk sampled at fall edge
                  SYNC_EXTERNAL,      //frame sync signal comes from external
                  SYNC_ACTIVE_HIGH,   //frame sync signal active high
                  FULL_CYCLE);        //full cycle
                 
    // Set up frames
    mcbspRxFrameSetup(MCBSP_BASE_ADDR,          //use mcbsp1
                  SINGLE_PHASE,           //Rx single phase
                  MSB_FIRST,              //Rx MSB
                  DELAY_1BIT,             //Rx delay 1bit
                  MCBSP_WORDS_PER_FRAME,  //configure Rx words per frame
                  MCBSP_BITS_PER_WORD,    //configure Rx bytes per word
                  MCBSP_WORDS_PER_FRAME,  //configure Rx words per frame
                  MCBSP_BITS_PER_WORD,    //configure Rx bytes per word
                  RIGHT_JUST_ZERO);       //Right-justify and zero-fill MSBs in DRR

    // Program the Sample Rate generator  
    mcbspSetupSrg(MCBSP_BASE_ADDR, CLKS, CLKS_RISE, SRG_FREE, MCBSP_FRAME_PERIOD, 1, MCBSP_CLKDV);

    // Configure the loopback 
    mcbspLoopback(MCBSP_BASE_ADDR, NO_LOOPBACK);

    // Set the buffer thresholds
    mcbspSetRxThresh(MCBSP_BASE_ADDR, MCBSP_THRSHOLD_RX);
    mcbspSetTxThresh(MCBSP_BASE_ADDR, MCBSP_THRSHOLD_TX);
    mcbspDisableTxDma(MCBSP_BASE_ADDR);
    mcbspEnableRxDma(MCBSP_BASE_ADDR);
    // Delay to allow settings to sync
    udelay(500);  //500us
    //set dx as general purpose output, clkx gpio, fsx gpio
    MCBSP_SETBIT(MCBSPLP_PCR_REG, 0x2000);  
}

static void pad_init(struct mcbsp_dev *devp)
{
	// Configure the fsr, clkr, dr, clks pins
	OUT_REGL(CONTROL_PADCONF_MCBSP1_CLKR	 + devp->pad_base, 0x01000100);  	// [31:16] = mcbsp1_fsr [15:0] = mcbsp1_clkr
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_DX	 + devp->pad_base, 0xFFFF0000);	// [31:16] = mcbsp1_dr
	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_DX	 + devp->pad_base, 0x01000000);
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS	 + devp->pad_base, 0xFFFF);		//[15:0] =mcbsp_clks
	SETBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS	 + devp->pad_base, 0x0100);
	/*configure the fsx, clkx, dx pins as gpio with input/output enable, 
	pullup but not enable(can't input anything if pullup enable)*/
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS	 + devp->pad_base, 0xFFFF0000);	//[31:16] =mcbsp1_fsx, input enable, mode4-gpio
	SETBIT_REGL(CONTROL_PADCONF_MCBSP_CLKS	 + devp->pad_base, 0x01140000);
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_CLKX	 + devp->pad_base, 0xFFFF);   	//[15:0] = mcbsp1_clkx, input enable, mode4-gpio
	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_CLKX	 + devp->pad_base, 0x0114);  
	CLRBIT_REGL(CONTROL_PADCONF_MCBSP1_DX	 + devp->pad_base, 0x0000FFFF);	//[15:0] = mcbsp1_dx, input enable, mode4-gpio158
	SETBIT_REGL(CONTROL_PADCONF_MCBSP1_DX	 + devp->pad_base, 0x00000114);
	
	CLRBIT_REGL(CONTROL_PADCONF_I2C3_SDA	 + devp->pad_base, 0xFFFF0000);
	SETBIT_REGL(CONTROL_PADCONF_I2C3_SDA	 + devp->pad_base, 0x01140000); 	//[31:16] = mode4-gpio170
}

static int gpio_i2c_init(void)
{
    int result;
	//request gpio161 as i2c sda
	if((result = gpio_request(GPIO_DX, "gpio_dx")) < 0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:gpio GPIO_DX can not be request\n");
		goto fail_request_gpio161;
	}
	//request gpio162 as i2c sck
	if((result = gpio_request(GPIO_CLKX, "gpio_clkx")) < 0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:gpio GPIO_CLKX can not be request\n");
		goto fail_request_gpio162;
	}
	//request gpio158 to control sda direction
	if((result = gpio_request(GPIO_DIR, "gpio_dir")) < 0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:gpio GPIO_DIR can not be request\n");
		goto fail_request_gpio158;
	}
	
	//set GPIO_CLKX as output, and output 1
	if((result = gpio_direction_output(GPIO_CLKX, 1)) <0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:gpio %d can't set as output\n", GPIO_CLKX);
		goto fail_set_gpio;
	}
	//set GPIO_DX as output, and output 1
	if((result = gpio_direction_output(GPIO_DX, 1)) <0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:gpio %d can't set as output\n", GPIO_DX);
		goto fail_set_gpio;
	}
	//set GPIO_DIR as output, and output 1
	if((result = gpio_direction_output(GPIO_DIR, 1)) <0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:gpio %d can't set as output\n", GPIO_DIR);
		goto fail_set_gpio;
	}
    return 0;

    //error handler
	fail_set_gpio:
				gpio_free(GPIO_DIR);
	fail_request_gpio158:
				gpio_free(GPIO_CLKX);
	fail_request_gpio162:
				gpio_free(GPIO_DX);
	fail_request_gpio161:
                return -1;
}
static int mcbsp_init(void)
{
	
  
	int result, chan_num;

     /*request device number and register device*/
	dev_t devno = MKDEV(mcbsp_major, 0);
	if(mcbsp_major) {
		result = register_chrdev_region(devno, 1, "mcbsp");
	}
	else {
		result = alloc_chrdev_region(&devno, 0, 1, "mcbsp");
		mcbsp_major = MAJOR(devno);
	}
	if(result < 0) {
		MCBSP_ERR_MSG("[MCBSP INIT]:Error in allc mcbsp_major\n");
		return result;
	}
	 
	//alloc mcbsp device struct
	mcbsp_devp = kmalloc(sizeof(struct mcbsp_dev), GFP_KERNEL);
	if(!mcbsp_devp) {
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(mcbsp_devp, 0, sizeof(struct mcbsp_dev));
	 			 
	//setup cdev struct
	result = mcbsp_setup_cdev(mcbsp_devp, 0);
	if(result < 0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]: setup cdev struct error\n");
		goto fail_setup_cdev;
	}
	
	//setup mcbsp dev
	result = mcbsp_setup_dev(mcbsp_devp, devno);
	if(result < 0)
	{
		MCBSP_ERR_MSG("[MCBSP INIT]: setup dev struct error\n");
		goto fail_setup_dev;
	}

	//create device node
	mcbsp_devp->mcbsp_class = class_create(THIS_MODULE, "haolong_mcbsp_class");
	if(IS_ERR(mcbsp_devp->mcbsp_class))
	{
		MCBSP_ERR_MSG("[MCBSP INIT]:failed in creating class.\n");
		result = (int)mcbsp_devp->mcbsp_class;
		goto fail_create_class;
	}
	device_create(mcbsp_devp->mcbsp_class, NULL, devno, NULL, "mcbsp");
	
    //configure mcbsp
    mcbsp_reg_init(mcbsp_devp);

    //configure pad
    pad_init(mcbsp_devp);

    //request and configure gpio_i2c
    result = gpio_i2c_init();
	if(result < 0)
    {
        goto fail_gpio_i2c;
    }   
    
	MCSBP_DBG("[MCBSP INIT]:McBSP loaded, Version %s\n", VER);

	return 0;
	
	//error process
	fail_gpio_i2c:
				device_destroy(mcbsp_devp->mcbsp_class, mcbsp_devp->devno);
				class_destroy(mcbsp_devp->mcbsp_class);
	fail_create_class:
                for (chan_num =0; chan_num < CHAN_N; chan_num++)
                {
				    omap_free_dma(mcbsp_devp->chan[chan_num]);
                }
	fail_setup_dev:
				cdev_del(&mcbsp_devp->cdev);
	fail_setup_cdev:
				kfree(mcbsp_devp);
	fail_malloc: 
  			   	unregister_chrdev_region(devno, 1);
               	return result;
}  

static void mcbsp_exit(void)
{
    int chan_num;
	mcbspReset(MCBSP_BASE_ADDR, 1);
    mcbspDisableRxDma(MCBSP_BASE_ADDR);

    //disable all channel
    for (chan_num = 0; chan_num < CHAN_N; chan_num++)
    {         
        dmaDisableChannel(mcbsp_devp->chan[chan_num]);
        //restore dma channel irq to system initial configure
        //clear allocated dma channel irq status on SDMA_IRQ_L0
        DMA_SETBIT(DMA_IRQSTATUS_L0, (1 << mcbsp_devp->chan[chan_num]));  
        //enable allocated dma channel irq at SDMA_IRQ_L0   
        DMA_SETBIT(DMA_IRQENABLE_L0, (1 << mcbsp_devp->chan[chan_num]));
        //free dma channel
        omap_free_dma(mcbsp_devp->chan[chan_num]);
    }

	//free ioremap
	iounmap((void __iomem *)mcbsp_devp->control_general_base);
	iounmap((void __iomem *)mcbsp_devp->dma_base_addr);
	iounmap((void __iomem *)mcbsp_devp->fclk_addr);
	iounmap((void __iomem *)mcbsp_devp->fclk_core_addr);
	iounmap((void __iomem *)mcbsp_devp->iclk_addr);
	iounmap((void __iomem *)mcbsp_devp->mcbsp_base_addr);
	iounmap((void __iomem *)mcbsp_devp->pad_base);

	//free device class
	device_destroy(mcbsp_devp->mcbsp_class, mcbsp_devp->devno);
	class_destroy(mcbsp_devp->mcbsp_class);

	//delete mcbsp cdev
	cdev_del(&mcbsp_devp->cdev);
	//omap_free_dma(mcbsp_devp->chan);

	//free mcbsp struct
	kfree(mcbsp_devp);

	//free device number
	unregister_chrdev_region(MKDEV(mcbsp_major, 0), 1);

	//free gpio
	gpio_free(GPIO_DX);
	gpio_free(GPIO_CLKX);
	gpio_free(GPIO_DIR);
    MCSBP_DBG("[MCBSP EXIT]:McBSP unloaded!\n");
}
MODULE_AUTHOR("haolong");
MODULE_LICENSE("GPL");
module_init(mcbsp_init);
module_exit(mcbsp_exit);
