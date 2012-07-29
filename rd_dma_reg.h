#ifndef _RD_DMA_REG_H
#define _RD_DMA_REG_H
/* 

Register definitions for OMAP35x DMA module

Version 0.01

*/
#define DMA_IRQ_CHAN11			(1 << 11)
#define DMA_BASE                  0x48056000
#define DMA_REVISION             (0x00000000)               
#define DMA_IRQSTATUS_L0         (0x00000008)       // 0x00000008 + (j * 0x4)  
#define DMA_IRQSTATUS_L1         (0x00000008 + 0x4)       // 0x00000008 + (j * 0x4)  
#define DMA_IRQSTATUS_L2         (0x00000008 + 0x4 * 2)       // 0x00000008 + (j * 0x4)  
#define DMA_IRQSTATUS_L3         (0x00000008 + 0x4 * 3)       // 0x00000008 + (j * 0x4)  

#define DMA_IRQENABLE_L0         (0x00000018)       // 0x00000018 + (j * 0x4)  
#define DMA_IRQENABLE_L1         (0x00000018 + 0x4)       // 0x00000018 + (j * 0x4)  
#define DMA_IRQENABLE_L2         (0x00000018 + 0x4 * 2)       // 0x00000018 + (j * 0x4)  
#define DMA_IRQENABLE_L3         (0x00000018 + 0x4 * 3)       // 0x00000018 + (j * 0x4)  

#define DMA_SYSSTATUS            (0x00000028)                    
#define DMA_OCP_SYSCONFIG        (0x0000002C)                    
#define DMA_CAPS_0               (0x00000064)                    
#define DMA_CAPS_2               (0x0000006C)                    
#define DMA_CAPS_3               (0x00000070)                    
#define DMA_CAPS_4               (0x00000074)                    
#define DMA_GCR                  (0x00000078)                    
#define DMA_CCRi                 (0x00000080)       // 0x00000080 + (i * 0x60) 
#define DMA_CLNK_CTRLi           (0x00000084)       // 0x00000084 + (i * 0x60) 
#define DMA_CICRi                (0x00000088)       // 0x00000088 + (i * 0x60) 
#define DMA_CSR11                 (0x0000008C + 11 * 0x60)       // 0x0000008C + (i * 0x60) 
#define DMA_CSRi                 (0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
//#define DMA_CSRi                 (DMA_BASE + 0x0000008C)       // 0x0000008C + (i * 0x60) 
#define DMA_CSDPi                (0x00000090)       // 0x00000090 + (i * 0x60) 
#define DMA_CENi                 (0x00000094)       // 0x00000094 + (i * 0x60) 
#define DMA_CFNi                 (0x00000098)       // 0x00000098 + (i * 0x60) 
#define DMA_CSSAi                (0x0000009C)       // 0x0000009C + (i * 0x60) 
#define DMA_CDSAi                (0x000000A0)       // 0x000000A0 + (i * 0x60) 
#define DMA_CSEIi                (0x000000A4)       // 0x000000A4 + (i * 0x60) 
#define DMA_CSFIi                (0x000000A8)       // 0x000000A8 + (i * 0x60) 
#define DMA_CDEIi                (0x000000AC)       // 0x000000AC + (i * 0x60) 
#define DMA_CDFIi                (0x000000B0)       // 0x000000B0 + (i * 0x60) 
#define DMA_CSACi                (0x000000B4)       // 0x000000B4 + (i * 0x60) 
#define DMA_CDACi                (0x000000B8)       // 0x000000B8 + (i * 0x60) 
#define DMA_CCENi                (0x000000BC)       // 0x000000BC + (i * 0x60) 
#define DMA_CCFNi                (0x000000C0)       // 0x000000C0 + (i * 0x60) 
#define DMA_COLORi               (0x000000C4)       // 0x000000C4 + (i * 0x60) 
#define DMA_CDPi				 (0x000000D0)
#define DMA_CNDPi				 (0x000000D4)
#define DMA_CCDNi				 (0x000000D8)
// SYSCONFIG bit defines
#define DMA_NO_STANDBY                (0x1 << 12)
#define DMA_ICLK_NO_OFF               (0x200)   //  9
#define DMA_FCLK_NO_OFF               (0x100)   //  8
#define DMA_EMUFREE                   (0x20)   //  5
#define DMA_NO_IDLE                   (0x1 << 3)
#define DMA_NO_AUTOIDLE               (0x0)

// CSDP Bit defines
#define CSDP_SRC_ENDIAN            (0x200000)
#define CSDP_SRC_ENDIAN_LOCK       (0x100000)
#define CSDP_DST_ENDIAN             (0x80000)
#define CSDP_DST_ENDIAN_LOCK        (0x40000)
#define CSDP_WRITE_MODE_1           (0x20000)
#define CSDP_WRITE_MODE_0           (0x10000)
#define CSDP_DST_BURST_EN_1          (0x8000)
#define CSDP_DST_BURST_EN_0          (0x4000)
#define CSDP_DST_PACKED              (0x2000)
#define CSDP_SRC_BURST_EN_1           (0x100)
#define CSDP_SRC_BURST_EN_0            (0x80)
#define CSDP_SRC_PACKED                (0x40)
#define CSDP_DATA_TYPE_1                (0x2)
#define CSDP_DATA_TYPE_0                (0x1) 

//CCR bit defines
#define CCR_WRITE_PRIORITY           (0x4000000)   // 26
#define CCR_BUFFERING_DISABLE        (0x2000000)   // 25
#define CCR_SEL_SRC_DST_SYNC         (0x1000000)   // 24
#define CCR_PREFETCH                  (0x800000)   // 23
#define CCR_SUPERVISOR                (0x400000)   // 22
#define CCR_SYNCHRO_CONROL_UPPER_1    (0x100000)   // 20
#define CCR_SYNCHRO_CONROL_UPPER_0     (0x80000)   // 19
#define CCR_BS                         (0x40000)   // 18
#define CCR_TRANSPARENT_COPY_ENABLE    (0x20000)   // 17
#define CCR_CONST_FILL_ENABLE          (0x10000)   // 16
#define CCR_DST_AMODE_1                 (0x8000)   // 15
#define CCR_DST_AMODE_0                 (0x4000)   // 14
#define CCR_SRC_AMODE_1                 (0x2000)   // 13
#define CCR_SRC_AMODE_0                 (0x1000)   // 12
#define CCR_WR_ACTIVE                    (0x400)   // 10
#define CCR_RD_ACTIVE                    (0x200)   //  9
#define CCR_SUSPEND_SENSITIVE            (0x100)   //  8
#define CCR_ENABLE                        (0x80)   //  7
#define CCR_READ_PRIORITY                 (0x40)   //  6
#define CCR_FS                            (0x20)   //  5
#define CCR_SYNCHRO_CONTROL_4             (0x10)   //  4
#define CCR_SYNCHRO_CONTROL_3              (0x8)   //  3
#define CCR_SYNCHRO_CONTROL_2              (0x4)   //  2
#define CCR_SYNCHRO_CONTROL_1              (0x2)   //  1
#define CCR_SYNCHRO_CONTROL_0              (0x1)   //  0

// CLNK_CTRL
#define CLNK_CTRL_ENABLE_LNK                (0x8000)   // 15
#define CLNK_CTRL_NEXTLCH_ID_4                (0x10)   //  4
#define CLNK_CTRL_NEXTLCH_ID_3                 (0x8)   //  3
#define CLNK_CTRL_NEXTLCH_ID_2                 (0x4)   //  2
#define CLNK_CTRL_NEXTLCH_ID_1                 (0x2)   //  1
#define CLNK_CTRL_NEXTLCH_ID_0                 (0x1)   //  0


#define DMA_FRAME_IE                 (0x8)   // 3
#define DMA_BLOCK_IE					(0x20)


/*  template for register bits
#define DMA_          (0x80000000)   // 31
#define DMA_          (0x40000000)   // 30
#define DMA_          (0x20000000)   // 29
#define DMA_          (0x10000000)   // 28
#define DMA_           (0x8000000)   // 27
#define DMA_           (0x4000000)   // 26
#define DMA_           (0x2000000)   // 25
#define DMA_           (0x1000000)   // 24
#define DMA_            (0x800000)   // 23
#define DMA_            (0x400000)   // 22
#define DMA_            (0x200000)   // 21
#define DMA_            (0x100000)   // 20
#define DMA_             (0x80000)   // 19
#define DMA_             (0x40000)   // 18
#define DMA_             (0x20000)   // 17
#define DMA_             (0x10000)   // 16
#define DMA_              (0x8000)   // 15
#define DMA_              (0x4000)   // 14
#define DMA_              (0x2000)   // 13
#define DMA_              (0x1000)   // 12
#define DMA_               (0x800)   // 11
#define DMA_               (0x400)   // 10
#define DMA_               (0x200)   //  9
#define DMA_               (0x100)   //  8
#define DMA_                (0x80)   //  7
#define DMA_                (0x40)   //  6
#define DMA_                (0x20)   //  5
#define DMA_                (0x10)   //  4
#define DMA_                 (0x8)   //  3
#define DMA_                 (0x4)   //  2
#define DMA_                 (0x2)   //  1
#define DMA_                 (0x1)   //  0
*/          

#endif
