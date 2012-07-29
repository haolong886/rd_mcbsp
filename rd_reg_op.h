/* 

Register operations 

Version 0.01 Under Construction

*/
#ifndef _RD_REG_OP_H
#define _RD_REG_OP_H

#include <asm/byteorder.h>
#include <asm/page.h>
#include <linux/types.h>
#include <linux/mm.h>          /* Get struct page {...} */
#include <linux/io.h>

#define IN_REGL(offSet)          __raw_readl(offSet) 
#define IN_REGB(offSet)          __raw_readb(offSet) 
#define OUT_REGL(offSet, value)  __raw_writel(value, offSet)
#define OUT_REGB(offSet, value)	 __raw_writeb(value, offSet)
#define BUFFER_FLAG_IN(offset)   __raw_readl(offset)
#define SETBIT_REGL(dest, mask)  (OUT_REGL((dest), IN_REGL((dest)) | (mask)))
#define CLRBIT_REGL(dest, mask)  (OUT_REGL((dest), IN_REGL((dest)) & ~(mask)))
#define TGLBIT_REGL(dest, mask)  (OUT_REGL((dest), IN_REGL((dest)) ^ (mask)))
#define CHKBIT_REGL(dest, mask)  (IN_REGL((dest)) & (mask))

#endif
