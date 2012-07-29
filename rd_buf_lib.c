#include <linux/slab.h>

#include "rd_buf_lib.h"


//static int set_dma_buffer_info(struct dma_buffer_info *dma_buffer,
//									unsigned int dma_buffer_block_index,
//									size_t dma_buffer_block_size,
//									unsigned int dma_buffer_head,
//									unsigned int dma_buffer_tail,
//									unsigned int dma_buffer_block_lock) 
//{
//	dma_buffer->dma_buffer_block_index = dma_buffer_block_index;
//	dma_buffer->dma_buffer_block_lock = dma_buffer_block_lock;
//	dma_buffer->dma_buffer_head = dma_buffer_head;
//	dma_buffer->dma_buffer_tail = dma_buffer_tail;
//	dma_buffer->dma_buffer_block_size = dma_buffer_block_size;
//	//dma_buffer->dma_buffer_valid_size = dma_buffer_tail - dma_buffer_head;
//	return 0;
//}

//reset buffer tail and valid size
void reset_dma_buffer_info(struct dma_buffer_info *dma_buffer) {
	dma_buffer->dma_buffer_tail = dma_buffer->dma_buffer_head;
	dma_buffer->dma_buffer_valid_size = 0;
	dma_buffer->have_no_buffer = 0;
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



//sdma_buffer_queue * init_sdma_buffer_queue()
//{
//    sdma_buffer_queue *q;
//    q_node *p;
//    q = (sdma_buffer_queue*)kmalloc(sizeof(sdma_buffer_queue), GFP_KERNEL);    
//    p = (q_node*)kmalloc(sizeof(q_node), GFP_KERNEL);  
//    p->next = NULL;
//    
//    q->font = q->rear = p;
//    return q;
//}


//read_buffer_queue * init_read_buffer_queue()
//{
//    read_buffer_queue *q;
//    r_node *p;
//    q = (read_buffer_queue*)kmalloc(sizeof(read_buffer_queue), GFP_KERNEL);    
//    p = (r_node*)kmalloc(sizeof(r_node), GFP_KERNEL);  
//    p->next = NULL;
//    
//    q->font = q->rear = p;
//    return q;
//}

//int is_empty_sdma_buffer_queue(sdma_buffer_queue *q)
//{
//    if(q->font != q->rear)  return 0;
//    else    return 1;
//}
//int is_empty_read_buffer_queue(read_buffer_queue *q)
//{
//    if(q->font != q->rear)  return 0;
//    else    return 1;
//}

//void put_sdma_buffer(sdma_buffer_queue *q, struct dma_buffer_info *x)
//{
//    q_node *p = (q_node *)kmalloc(sizeof(q_node), GFP_KERNEL);  
//    p->data = x;
//    p->next = NULL;
//    q->rear->next = p;
//    q->rear = p;
//}


//void put_read_buffer(read_buffer_queue *q, struct dma_buffer_info *x)
//{
//    r_node *p = (r_node *)kmalloc(sizeof(r_node), GFP_KERNEL);  
//    copy_buf_info(&p->data, x);
//    p->next = NULL;
//    q->rear->next = p;
//    q->rear = p;
//}

//int get_sdma_buffer(sdma_buffer_queue *q, struct dma_buffer_info **x)
//{
//    if(is_empty_sdma_buffer_queue(q)) return 0;   
//    else{
//        q_node *p = q->font->next;
//        *x = p->data;
//        q->font->next = p->next;
//        kfree(p);
//        if (q->font->next == NULL)
//            q->rear = q->font;

//        return 1;
//    }
//}

//int get_read_buffer(read_buffer_queue *q, struct dma_buffer_info *x)
//{
//    if(is_empty_read_buffer_queue(q)) return 0;   
//    else
//	{
//        r_node *p = q->font->next;
//        copy_buf_info(x, &p->data);
//        q->font->next = p->next;
//        kfree(p);
//        if (q->font->next == NULL)
//            q->rear = q->font;

//        return 1;
//    }
//}
//int print_sdma_buffer_queue(sdma_buffer_queue *q) {
//	printk(KERN_INFO "print buffer queue\n");
//	if(is_empty_sdma_buffer_queue(q)) 
//	{
//		printk(KERN_INFO "buffer queue is empty\n");
//		return -1;
//	}
//	q_node *p = q->font->next;
//	print_dma_buf_info(p->data);
//	p = p->next;
//	while(p != NULL) 
//	{
//		printk(KERN_INFO "print queue while\n");
//		print_dma_buf_info(p->data);
//		p = p->next;
//	}
//	return 0;
//}

loop_buffer_t *init_loop_buffer(void)
{
    loop_buffer_t *q;
    q_node *p;
    q = (loop_buffer_t*)kmalloc(sizeof(loop_buffer_t), GFP_KERNEL);    
    p = (q_node*)kmalloc(sizeof(q_node), GFP_KERNEL);  
    p->next = NULL;
    q->head = NULL;
    q->font = q->rear = p;
    return q;
}
int is_empty_loop_buffer(loop_buffer_t *q)
{
    if(NULL == q->head)  
		return 1;
    else    
		return 0;
}

void put_loop_buffer(loop_buffer_t *q, struct dma_buffer_info *x)
{
    q_node *p = (q_node *)kmalloc(sizeof(q_node), GFP_KERNEL);  
    p->data = x;
	if(NULL == q->head)
	{
		q->head = p;
	}
    p->next = q->head;
	//printf("q->head->next = %d\n", q->head->next);
    q->rear->next = p;
    q->rear = p;
}
int get_loop_buffer(loop_buffer_t *q, struct dma_buffer_info **x)
{
    q_node *p = q->font->next;
	if(is_empty_loop_buffer(q))
		return FALSE;
    *x = p->data;
    q->font->next = p->next;
    return TRUE;
}
int get_loop_buffer_num(loop_buffer_t *q)
{
	int n=0;
	q_node *p;
	if(NULL == q->head) 
		return 0;
	p = q->head;
	while(p->next != q->head)
	{
		n++;
		p = p->next;
	}
	return n+1;
}
void print_loop_buffer(loop_buffer_t *q)
{
	int n = get_loop_buffer_num(q);
	q_node *p1 = q->head->next;
	q_node *p2;
	print_dma_buf_info(q->head->data);
	for(; n>1; n--)
	{
		p2 = p1->next;
		print_dma_buf_info(p1->data);
		p1 = p2;
	}
}
void distroy_loop_buffer(loop_buffer_t *q)
{
	int n = get_loop_buffer_num(q);
	if(0 != n)
	{
		q_node *p1 = q->head->next;	//must be placed here, else will let kernel panic
		q_node *p2;
		kfree(q->head);
		for(; n>1; n--)
		{
			p2 = p1->next;
			kfree(p1);
			p1 = p2;
		}
	}
	kfree(q->font);
	kfree(q);
}

