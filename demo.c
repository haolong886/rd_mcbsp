#include<stdio.h>
#include<sys/signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEBUG_16
//#define DEBUG_32

#ifdef DEBUG_16
#define TX_NUM_BYTES 64
#endif
#ifdef DEBUG_32
#define TX_NUM_BYTES 128
#endif
#define TX_NUM (TX_NUM_BYTES/4)
//ioctrl
#define MCBSP_IOC_MAGIC 'k'

#define MCBSP_IOC_SET_DMA_DES _IOW(MCBSP_IOC_MAGIC, 1, unsigned int*) 	 //cmd of setting dma destination addr
#define MCBSP_IOC_MCBSPDMA_START   _IO(MCBSP_IOC_MAGIC, 2) 				 //cmd of start mcbsp and dma
#define MCBSP_IOC_MCBSPDMA_STOP    _IO(MCBSP_IOC_MAGIC, 3)				 //cmd of stop mcbsp and dma
#define MCBSP_IOC_DMA_RESTART   _IO(MCBSP_IOC_MAGIC, 4)

//add more cmd to here
#define MCBSP_IOC_MAXNR 10 //max number of cmd

//----
#define BUFFER_NUM 3

int mcbsp_fd;

struct dma_buffer_info {
	unsigned int dma_buffer_block_index;
	size_t dma_buffer_block_size; //size is based on byte
	size_t dma_buffer_valid_size; //valid data size in block, based on byte
	unsigned int dma_buffer_head;
	unsigned int dma_buffer_tail;
	unsigned int dma_buffer_block_lock;
	unsigned int have_no_buffer;
};
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

unsigned int dma_complete_handler() {
	printf("dma complete!!\n");
	struct dma_buffer_info *dma_buffer;
	dma_buffer = malloc(sizeof(struct dma_buffer_info));
	if(!dma_buffer) {
		  return -1;
	}
	memset(dma_buffer, 0, sizeof(struct dma_buffer_info));
	if(read(mcbsp_fd, dma_buffer, sizeof(struct dma_buffer_info)) < 0) {
		printf("read from mcbsp error\n");
		return -1;
	}
	printf("block_index = %d\n", dma_buffer->dma_buffer_block_index);
	printf("head = 0x%x\n", dma_buffer->dma_buffer_head);
	printf("tail = 0x%x\n", dma_buffer->dma_buffer_tail);
	printf("block_lock = 0x%x\n", dma_buffer->dma_buffer_block_lock);
	printf("block size = 0x%x\n", dma_buffer->dma_buffer_block_size);
	printf("valid data size = 0x%x\n", dma_buffer->dma_buffer_valid_size);
	printf("have no buffer = 0x%x\n", dma_buffer->have_no_buffer);
	free(dma_buffer);
	return 0;
}


int main(void) {
	int write_no, i,j=0, n=0;

	unsigned int buffer[TX_NUM] = {0x10000000,0x10000001,0x10000002,0x10000003,0x10000004,0x10000005,0x10000006,0x10000007,0x10000008,0x10000009,0x1000000a,0x1000000b,0x1000000c,0x1000000d,0x1000000e,0x1000000f};


	struct dma_buffer_info dma_buf_info[BUFFER_NUM];
	//dma_buf_info = malloc(sizeof(struct dma_buffer_info));
	if(!dma_buf_info) {
		printf("malloc struct dma_buffer_info error");
		return -1;
	}
		
	if((mcbsp_fd = open("/dev/mcbsp", O_RDWR)) < 0) {
		printf("open mcbsp error\n");
		return -1;
	}
	//test ioctl
	set_dma_buffer_info(dma_buf_info, 0, 64*12, 0x899f8000, 0x80000090, 1);
	set_dma_buffer_info(&dma_buf_info[1], 1, 64*12, 0x899fd000, 0x8a000040, 1);
	set_dma_buffer_info(&dma_buf_info[2], 2, 64*12, 0x899fc000, 0x8a000040, 1);
	//before ioctl MCBSP_IOC_MCBSPDMA_START, 
	//user must call ioctl MCBSP_IOC_SET_DMA_DES to set dma destination addr
	if(ioctl(mcbsp_fd, MCBSP_IOC_SET_DMA_DES, (unsigned long *)dma_buf_info) < 0) {
		printf("ioctl MCBSP_IOC_SET_DMA_DES error\n");
		return -1;
	}
	if(ioctl(mcbsp_fd, MCBSP_IOC_SET_DMA_DES, (unsigned long *)&dma_buf_info[1]) < 0) {
		printf("ioctl MCBSP_IOC_SET_DMA_DES error\n");
		return -1;
	}
	if(ioctl(mcbsp_fd, MCBSP_IOC_SET_DMA_DES, (unsigned long *)&dma_buf_info[2]) < 0) {
		printf("ioctl MCBSP_IOC_SET_DMA_DES error\n");
		return -1;
	}
	printf("ioctl MCBSP_IOC_MCBSPDMA_START");
	if(ioctl(mcbsp_fd, MCBSP_IOC_MCBSPDMA_START, NULL) < 0) {
		printf("ioctl MCBSP_IOC_MCBSPDMA_START error\n");
		return -1;
	}
	//set signal SIGIO handler
	signal(SIGIO,dma_complete_handler);
	//set mcbsp fasync
	fcntl(mcbsp_fd,F_SETOWN,getpid());
	int flags = fcntl(mcbsp_fd,F_GETFL);
	fcntl(mcbsp_fd,F_SETFL,flags | FASYNC);
	//------------------------
	while(1){
		printf("demo into while");
		n++;
/*
		if(3 == n) {
			ioctl(mcbsp_fd, MCBSP_IOC_SET_DMA_DES, (unsigned long *)dma_buf_info);
		}
*/
		getchar();

		
		for(j=0; j<1; j++) {


			for(i=0; i<TX_NUM; i++) {

				buffer[i] += 16; 


			}
			if((write_no = write(mcbsp_fd, buffer, TX_NUM_BYTES)) < 0) {
				printf("write mcbsp error\n");
				return -1;
			}
		}
	}
//	while(1);
	//printf("read number = %d\n", read_no);
/*
	for(i=0; i<16; i++) {
		printf("read buffer = 0x%x\n", buffer[i]);
	}
	i=1000;
	while(i--);
*/
	close(mcbsp_fd);

}
