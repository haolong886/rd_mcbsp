#ifndef _RD_BUF_LIB_H
#define _RD_BUF_LIB_H


#define FALSE -1
#define TRUE 0


//typedef int valuetype;
struct dma_buffer_info {
	unsigned int dma_buffer_block_index;
	size_t dma_buffer_block_size; //size is based on byte
	size_t dma_buffer_valid_size; //valid data size in block, based on byte
	unsigned int dma_buffer_head;
	unsigned int dma_buffer_tail;
	unsigned int dma_buffer_block_lock;
	unsigned int have_no_buffer;	//0x1: have no buffer to dma 
									//0x0: have buffer to dma
};
typedef struct node
{
    struct dma_buffer_info *data;
    struct node *next;
}q_node;
typedef struct read_node
{
    struct dma_buffer_info data;
    struct r_node *next;
}r_node;   
typedef struct
{
    q_node *font, *rear;
}sdma_buffer_queue;
typedef struct
{
    r_node *font, *rear;
}read_buffer_queue;

typedef struct
{
    q_node *font, *rear, *head;
}loop_buffer_t;


//reset buffer tail and valid size
void reset_dma_buffer_info(struct dma_buffer_info *dma_buffer);

void copy_buf_info(struct dma_buffer_info *buf_to, struct dma_buffer_info * buf_from) ;

void print_dma_buf_info(struct dma_buffer_info *dma_buffer); 

loop_buffer_t *init_loop_buffer(void);
int is_empty_loop_buffer(loop_buffer_t *q);

void put_loop_buffer(loop_buffer_t *q, struct dma_buffer_info *x);
int get_loop_buffer(loop_buffer_t *q, struct dma_buffer_info **x);
int get_loop_buffer_num(loop_buffer_t *q);
void print_loop_buffer(loop_buffer_t *q);
void distroy_loop_buffer(loop_buffer_t *q);

#endif
