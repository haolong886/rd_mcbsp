/* 

Register definitions for OMAP & AM MCBSP Module.

Version x.xx - Under construction 

*/
#ifndef _RD_MCBSP_REG_H
#define _RD_MCBSP_REG_H

// Base addresses

#define MCBSP1_REG_BASE          0x48074000      
#define MCBSP5_REG_BASE          0x48096000      
#define MCBSP2_REG_BASE          0x49022000      
#define MCBSP3_REG_BASE          0x49024000      
#define MCBSP4_REG_BASE          0x49026000      
#define SIDETONE_MCBSP2_REG_BASE 0x49028000      
#define SIDETONE_MCBSP3_REG_BASE 0x4902A000      

#define MCBSP1_IRQ				16
// Module Offsets:

// MCBSP general
#define MCBSPLP_DRR_REG       (0x00000000)
#define MCBSPLP_DXR_REG       (0x00000008) 
#define MCBSPLP_SPCR2_REG     (0x00000010) 
#define MCBSPLP_SPCR1_REG     (0x00000014) 
#define MCBSPLP_RCR2_REG      (0x00000018) 
#define MCBSPLP_RCR1_REG      (0x0000001C) 
#define MCBSPLP_XCR2_REG      (0x00000020) 
#define MCBSPLP_XCR1_REG      (0x00000024) 
#define MCBSPLP_SRGR2_REG     (0x00000028) 
#define MCBSPLP_SRGR1_REG     (0x0000002C) 
#define MCBSPLP_MCR2_REG      (0x00000030) 
#define MCBSPLP_MCR1_REG      (0x00000034) 
#define MCBSPLP_RCERA_REG     (0x00000038) 
#define MCBSPLP_RCERB_REG     (0x0000003C) 
#define MCBSPLP_XCERA_REG     (0x00000040) 
#define MCBSPLP_XCERB_REG     (0x00000044) 
#define MCBSPLP_PCR_REG       (0x00000048) 
#define MCBSPLP_RCERC_REG     (0x0000004C) 
#define MCBSPLP_RCERD_REG     (0x00000050) 
#define MCBSPLP_XCERC_REG     (0x00000054) 
#define MCBSPLP_XCERD_REG     (0x00000058) 
#define MCBSPLP_RCERE_REG     (0x0000005C) 
#define MCBSPLP_RCERF_REG     (0x00000060) 
#define MCBSPLP_XCERE_REG     (0x00000064) 
#define MCBSPLP_XCERF_REG     (0x00000068) 
#define MCBSPLP_RCERG_REG     (0x0000006C) 
#define MCBSPLP_RCERH_REG     (0x00000070) 
#define MCBSPLP_XCERG_REG     (0x00000074) 
#define MCBSPLP_XCERH_REG     (0x00000078) 
#define MCBSPLP_RINTCLR_REG   (0x00000080) 
#define MCBSPLP_XINTCLR_REG   (0x00000084) 
#define MCBSPLP_ROVFLCLR_REG  (0x00000088) 
#define MCBSPLP_SYSCONFIG_REG (0x0000008C) 
#define MCBSPLP_THRSH2_REG    (0x00000090) 
#define MCBSPLP_THRSH1_REG    (0x00000094) 
#define MCBSPLP_IRQSTATUS_REG (0x000000A0) 
#define MCBSPLP_IRQENABLE_REG (0x000000A4) 
#define MCBSPLP_WAKEUPEN_REG  (0x000000A8) 
#define MCBSPLP_XCCR_REG      (0x000000AC) 
#define MCBSPLP_RCCR_REG      (0x000000B0) 
#define MCBSPLP_XBUFFSTAT_REG (0x000000B4)
#define MCBSPLP_RBUFFSTAT_REG (0x000000B8)
#define MCBSPLP_SSELCR_REG    (0x000000BC) 
#define MCBSPLP_STATUS_REG    (0x000000C0)



// MCBSPLP_SPCR2_REG
#define SPCR2_FREE       (0x0200)
#define SPCR2_SOFT       (0x0100)
#define SPCR2_FRST       (0x0080)
#define SPCR2_GRST       (0x0040)
#define SPCR2_XINTM_1    (0x0020)
#define SPCR2_XINTM_0    (0x0010)
#define SPCR2_XSYNCERR   (0x0008)
#define SPCR2_XEMPTY     (0x0004)
#define SPCR2_XRDY       (0x0002)
#define SPCR2_XRST       (0x0001)

// MCBSPLP_SPCR1_REG
#define SPCR1_ALB        (0x8000)
#define SPCR1_RJUST_1    (0x4000)
#define SPCR1_RJUST_0    (0x2000)
#define SPCR1_DXENA      (0x0080)
#define SPCR1_RINTM_1    (0x0020)
#define SPCR1_RINTM_0    (0x0010)
#define SPCR1_RSYNCERR   (0x0008)
#define SPCR1_RFULL      (0x0004)
#define SPCR1_RRDY       (0x0002)
#define SPCR1_RRST       (0x0001)


// MCBSPLP_RCR2_REG
#define RCR2_RPHASE     (0x8000)
#define RCR2_RFRLEN2_6  (0x4000)
#define RCR2_RFRLEN2_5  (0x2000)
#define RCR2_RFRLEN2_4  (0x1000)
#define RCR2_RFRLEN2_3  (0x0800)
#define RCR2_RFRLEN2_2  (0x0400)
#define RCR2_RFRLEN2_1  (0x0200)
#define RCR2_RFRLEN2_0  (0x0100)
#define RCR2_RWDLEN2_2  (0x0080)
#define RCR2_RWDLEN2_1  (0x0040)
#define RCR2_RWDLEN2_0  (0x0020)
#define RCR2_RREVERSE_1 (0x0010)
#define RCR2_RREVERSE_0 (0x0008)
#define RCR2_RDATDLY_1  (0x0002)
#define RCR2_RDATDLY_0  (0x0001)




// MCBSPLP_RCR1_REG
#define RCR1_RFRLEN1_6  (0x4000)
#define RCR1_RFRLEN1_5  (0x2000)
#define RCR1_RFRLEN1_4  (0x1000)
#define RCR1_RFRLEN1_3  (0x0800)
#define RCR1_RFRLEN1_2  (0x0400)
#define RCR1_RFRLEN1_1  (0x0200)
#define RCR1_RFRLEN1_0  (0x0100)
#define RCR1_RWDLEN1_2  (0x0080)
#define RCR1_RWDLEN1_1  (0x0040)
#define RCR1_RWDLEN1_0  (0x0020)

// MCBSPLP_XCR2_REG
#define XCR2_XPHASE     (0x8000)
#define XCR2_XFRLEN2_6  (0x4000)
#define XCR2_XFRLEN2_5  (0x2000)
#define XCR2_XFRLEN2_4  (0x1000)
#define XCR2_XFRLEN2_3  (0x0800)
#define XCR2_XFRLEN2_2  (0x0400)
#define XCR2_XFRLEN2_1  (0x0200)
#define XCR2_XFRLEN2_0  (0x0100)
#define XCR2_XWDLEN2_2  (0x0080)
#define XCR2_XWDLEN2_1  (0x0040)
#define XCR2_XWDLEN2_0  (0x0020)
#define XCR2_XREVERSE_1 (0x0010)
#define XCR2_XREVERSE_0 (0x0008)
#define XCR2_XDATDLY_1  (0x0002)
#define XCR2_XDATDLY_0  (0x0001)

// MCBSPLP_XCR1_REG
#define XCR1_XFRLEN1_6  (0x4000)
#define XCR1_XFRLEN1_5  (0x2000)
#define XCR1_XFRLEN1_4  (0x1000)
#define XCR1_XFRLEN1_3  (0x0800)
#define XCR1_XFRLEN1_2  (0x0400)
#define XCR1_XFRLEN1_1  (0x0200)
#define XCR1_XFRLEN1_0  (0x0100)
#define XCR1_XWDLEN1_2  (0x0080)
#define XCR1_XWDLEN1_1  (0x0040)
#define XCR1_XWDLEN1_0  (0x0020)


// MCBSPLP_SRGR2_REG
#define SRGR2_GSYNC     (0x8000)
#define SRGR2_CLKSP     (0x4000)
#define SRGR2_CLKSM     (0x2000)
#define SRGR2_FSGM      (0x1000)
#define SRGR2_FPER_b    (0x0800)
#define SRGR2_FPER_a    (0x0400)
#define SRGR2_FPER_9    (0x0200)
#define SRGR2_FPER_8    (0x0100)
#define SRGR2_FPER_7    (0x0080)
#define SRGR2_FPER_6    (0x0040)
#define SRGR2_FPER_5    (0x0020)
#define SRGR2_FPER_4    (0x0010)
#define SRGR2_FPER_3    (0x0008)
#define SRGR2_FPER_2    (0x0004)
#define SRGR2_FPER_1    (0x0002)
#define SRGR2_FPER_0    (0x0001)
#define SRGR2_FPER_MASK (0xFFF)
#define SRGR2_FPER_BIT  (0)

// MCBSPLP_SRGR1_REG
#define SRGR1_FWID_7     (0x8000)
#define SRGR1_FWID_6     (0x4000)
#define SRGR1_FWID_5     (0x2000)
#define SRGR1_FWID_4     (0x1000)
#define SRGR1_FWID_3     (0x0800)
#define SRGR1_FWID_2     (0x0400)
#define SRGR1_FWID_1     (0x0200)
#define SRGR1_FWID_0     (0x0100)
#define SRGR1_CLKGDV_7   (0x0080)
#define SRGR1_CLKGDV_6   (0x0040)
#define SRGR1_CLKGDV_5   (0x0020)
#define SRGR1_CLKGDV_4   (0x0010)
#define SRGR1_CLKGDV_3   (0x0008)
#define SRGR1_CLKGDV_2   (0x0004)
#define SRGR1_CLKGDV_1   (0x0002)
#define SRGR1_CLKGDV_0   (0x0001)
#define SRGR1_FWID_MASK  (0xFF00)
#define SRGR1_CLKGDV_MASK (0x00FF)
#define SRGR1_FWID_BIT   (8)
#define SRGR1_CLKGDV_BIT (0)




// MCBSPLP_MCR2_REG
#define MCR2_XMCME      (0x0200)
#define MCR2_XPBBLK_1   (0x0100)
#define MCR2_XPBBLK_0   (0x0080)
#define MCR2_XPABLK_1   (0x0040)
#define MCR2_XPABLK_0   (0x0020)
#define MCR2_XMCM_1     (0x0002)
#define MCR2_XMCM_0     (0x0001)

// MCBSPLP_MCR1_REG
#define MCR1_RMCME      (0x0200)
#define MCR1_RPBBLK_1   (0x0100)
#define MCR1_RPBBLK_0   (0x0080)
#define MCR1_RPABLK_1   (0x0040)
#define MCR1_RPABLK_0   (0x0020)
#define MCR1_RMCM       (0x0001)

// MCBSPLP_RCERA_REG
#define RCERA_F    (0x8000)
#define RCERA_E    (0x4000)
#define RCERA_D    (0x2000)
#define RCERA_C    (0x1000)
#define RCERA_B    (0x0800)
#define RCERA_A    (0x0400)
#define RCERA_9    (0x0200)
#define RCERA_8    (0x0100)
#define RCERA_7    (0x0080)
#define RCERA_6    (0x0040)
#define RCERA_5    (0x0020)
#define RCERA_4    (0x0010)
#define RCERA_3    (0x0008)
#define RCERA_2    (0x0004)
#define RCERA_1    (0x0002)
#define RCERA_0    (0x0001)

// MCBSPLP_RCERB_REG
#define RCERB_F    (0x8000)
#define RCERB_E    (0x4000)
#define RCERB_D    (0x2000)
#define RCERB_C    (0x1000)
#define RCERB_B    (0x0800)
#define RCERB_A    (0x0400)
#define RCERB_9    (0x0200)
#define RCERB_8    (0x0100)
#define RCERB_7    (0x0080)
#define RCERB_6    (0x0040)
#define RCERB_5    (0x0020)
#define RCERB_4    (0x0010)
#define RCERB_3    (0x0008)
#define RCERB_2    (0x0004)
#define RCERB_1    (0x0002)
#define RCERB_0    (0x0001)

// MCBSPLP_XCERA_REG
#define XCERA_F    (0x8000)
#define XCERA_E    (0x4000)
#define XCERA_D    (0x2000)
#define XCERA_C    (0x1000)
#define XCERA_B    (0x0800)
#define XCERA_A    (0x0400)
#define XCERA_9    (0x0200)
#define XCERA_8    (0x0100)
#define XCERA_7    (0x0080)
#define XCERA_6    (0x0040)
#define XCERA_5    (0x0020)
#define XCERA_4    (0x0010)
#define XCERA_3    (0x0008)
#define XCERA_2    (0x0004)
#define XCERA_1    (0x0002)
#define XCERA_0    (0x0001)

// MCBSPLP_XCERB_REG
#define XCERB_F    (0x8000)
#define XCERB_E    (0x4000)
#define XCERB_D    (0x2000)
#define XCERB_C    (0x1000)
#define XCERB_B    (0x0800)
#define XCERB_A    (0x0400)
#define XCERB_9    (0x0200)
#define XCERB_8    (0x0100)
#define XCERB_7    (0x0080)
#define XCERB_6    (0x0040)
#define XCERB_5    (0x0020)
#define XCERB_4    (0x0010)
#define XCERB_3    (0x0008)
#define XCERB_2    (0x0004)
#define XCERB_1    (0x0002)
#define XCERB_0    (0x0001)

// MCBSPLP_PCR_REG
#define PCR_IDLE_EN    (0x4000)
#define PCR_XIOEN      (0x2000)
#define PCR_RIOEN      (0x1000)
#define PCR_FSXM       (0x0800)
#define PCR_FSRM       (0x0400)
#define PCR_CLKXM      (0x0200)
#define PCR_CLKRM      (0x0100)
#define PCR_SCLKME     (0x0080)
#define PCR_CLKS_STAT  (0x0040)
#define PCR_DX_STAT    (0x0020)
#define PCR_DR_STAT    (0x0010)
#define PCR_FSXP       (0x0008)
#define PCR_FSRP       (0x0004)
#define PCR_CLKXP      (0x0002)
#define PCR_CLKRP      (0x0001)

// MCBSPLP_RCERC_REG
#define RCERC_F    (0x8000)
#define RCERC_E    (0x4000)
#define RCERC_D    (0x2000)
#define RCERC_C    (0x1000)
#define RCERC_B    (0x0800)
#define RCERC_A    (0x0400)
#define RCERC_9    (0x0200)
#define RCERC_8    (0x0100)
#define RCERC_7    (0x0080)
#define RCERC_6    (0x0040)
#define RCERC_5    (0x0020)
#define RCERC_4    (0x0010)
#define RCERC_3    (0x0008)
#define RCERC_2    (0x0004)
#define RCERC_1    (0x0002)
#define RCERC_0    (0x0001)

// MCBSPLP_RCERD_REG
#define RCERD_F    (0x8000)
#define RCERD_E    (0x4000)
#define RCERD_D    (0x2000)
#define RCERD_C    (0x1000)
#define RCERD_B    (0x0800)
#define RCERD_A    (0x0400)
#define RCERD_9    (0x0200)
#define RCERD_8    (0x0100)
#define RCERD_7    (0x0080)
#define RCERD_6    (0x0040)
#define RCERD_5    (0x0020)
#define RCERD_4    (0x0010)
#define RCERD_3    (0x0008)
#define RCERD_2    (0x0004)
#define RCERD_1    (0x0002)
#define RCERD_0    (0x0001)

// MCBSPLP_XCERC_REG
#define XCERC_F    (0x8000)
#define XCERC_E    (0x4000)
#define XCERC_D    (0x2000)
#define XCERC_C    (0x1000)
#define XCERC_B    (0x0800)
#define XCERC_A    (0x0400)
#define XCERC_9    (0x0200)
#define XCERC_8    (0x0100)
#define XCERC_7    (0x0080)
#define XCERC_6    (0x0040)
#define XCERC_5    (0x0020)
#define XCERC_4    (0x0010)
#define XCERC_3    (0x0008)
#define XCERC_2    (0x0004)
#define XCERC_1    (0x0002)
#define XCERC_0    (0x0001)

// MCBSPLP_XCERD_REG
#define XCERD_F    (0x8000)
#define XCERD_E    (0x4000)
#define XCERD_D    (0x2000)
#define XCERD_C    (0x1000)
#define XCERD_B    (0x0800)
#define XCERD_A    (0x0400)
#define XCERD_9    (0x0200)
#define XCERD_8    (0x0100)
#define XCERD_7    (0x0080)
#define XCERD_6    (0x0040)
#define XCERD_5    (0x0020)
#define XCERD_4    (0x0010)
#define XCERD_3    (0x0008)
#define XCERD_2    (0x0004)
#define XCERD_1    (0x0002)
#define XCERD_0    (0x0001)

// MCBSPLP_RCERE_REG
#define RCERE_F    (0x8000)
#define RCERE_E    (0x4000)
#define RCERE_D    (0x2000)
#define RCERE_C    (0x1000)
#define RCERE_B    (0x0800)
#define RCERE_A    (0x0400)
#define RCERE_9    (0x0200)
#define RCERE_8    (0x0100)
#define RCERE_7    (0x0080)
#define RCERE_6    (0x0040)
#define RCERE_5    (0x0020)
#define RCERE_4    (0x0010)
#define RCERE_3    (0x0008)
#define RCERE_2    (0x0004)
#define RCERE_1    (0x0002)
#define RCERE_0    (0x0001)

// MCBSPLP_RCERF_REG
#define RCERF_F    (0x8000)
#define RCERF_E    (0x4000)
#define RCERF_D    (0x2000)
#define RCERF_C    (0x1000)
#define RCERF_B    (0x0800)
#define RCERF_A    (0x0400)
#define RCERF_9    (0x0200)
#define RCERF_8    (0x0100)
#define RCERF_7    (0x0080)
#define RCERF_6    (0x0040)
#define RCERF_5    (0x0020)
#define RCERF_4    (0x0010)
#define RCERF_3    (0x0008)
#define RCERF_2    (0x0004)
#define RCERF_1    (0x0002)
#define RCERF_0    (0x0001)

// MCBSPLP_XCERE_REG
#define XCERE_F    (0x8000)
#define XCERE_E    (0x4000)
#define XCERE_D    (0x2000)
#define XCERE_C    (0x1000)
#define XCERE_B    (0x0800)
#define XCERE_A    (0x0400)
#define XCERE_9    (0x0200)
#define XCERE_8    (0x0100)
#define XCERE_7    (0x0080)
#define XCERE_6    (0x0040)
#define XCERE_5    (0x0020)
#define XCERE_4    (0x0010)
#define XCERE_3    (0x0008)
#define XCERE_2    (0x0004)
#define XCERE_1    (0x0002)
#define XCERE_0    (0x0001)

// MCBSPLP_XCERF_REG
#define XCERF_F    (0x8000)
#define XCERF_E    (0x4000)
#define XCERF_D    (0x2000)
#define XCERF_C    (0x1000)
#define XCERF_B    (0x0800)
#define XCERF_A    (0x0400)
#define XCERF_9    (0x0200)
#define XCERF_8    (0x0100)
#define XCERF_7    (0x0080)
#define XCERF_6    (0x0040)
#define XCERF_5    (0x0020)
#define XCERF_4    (0x0010)
#define XCERF_3    (0x0008)
#define XCERF_2    (0x0004)
#define XCERF_1    (0x0002)
#define XCERF_0    (0x0001)

// MCBSPLP_RCERG_REG
#define RCERG_F    (0x8000)
#define RCERG_E    (0x4000)
#define RCERG_D    (0x2000)
#define RCERG_C    (0x1000)
#define RCERG_B    (0x0800)
#define RCERG_A    (0x0400)
#define RCERG_9    (0x0200)
#define RCERG_8    (0x0100)
#define RCERG_7    (0x0080)
#define RCERG_6    (0x0040)
#define RCERG_5    (0x0020)
#define RCERG_4    (0x0010)
#define RCERG_3    (0x0008)
#define RCERG_2    (0x0004)
#define RCERG_1    (0x0002)
#define RCERG_0    (0x0001)

// MCBSPLP_RCERH_REG
#define RCERH_F    (0x8000)
#define RCERH_E    (0x4000)
#define RCERH_D    (0x2000)
#define RCERH_C    (0x1000)
#define RCERH_B    (0x0800)
#define RCERH_A    (0x0400)
#define RCERH_9    (0x0200)
#define RCERH_8    (0x0100)
#define RCERH_7    (0x0080)
#define RCERH_6    (0x0040)
#define RCERH_5    (0x0020)
#define RCERH_4    (0x0010)
#define RCERH_3    (0x0008)
#define RCERH_2    (0x0004)
#define RCERH_1    (0x0002)
#define RCERH_0    (0x0001)

// MCBSPLP_XCERG_REG
#define XCERG_F    (0x8000)
#define XCERG_E    (0x4000)
#define XCERG_D    (0x2000)
#define XCERG_C    (0x1000)
#define XCERG_B    (0x0800)
#define XCERG_A    (0x0400)
#define XCERG_9    (0x0200)
#define XCERG_8    (0x0100)
#define XCERG_7    (0x0080)
#define XCERG_6    (0x0040)
#define XCERG_5    (0x0020)
#define XCERG_4    (0x0010)
#define XCERG_3    (0x0008)
#define XCERG_2    (0x0004)
#define XCERG_1    (0x0002)
#define XCERG_0    (0x0001)

// MCBSPLP_XCERH_REG
#define XCERH_F    (0x8000)
#define XCERH_E    (0x4000)
#define XCERH_D    (0x2000)
#define XCERH_C    (0x1000)
#define XCERH_B    (0x0800)
#define XCERH_A    (0x0400)
#define XCERH_9    (0x0200)
#define XCERH_8    (0x0100)
#define XCERH_7    (0x0080)
#define XCERH_6    (0x0040)
#define XCERH_5    (0x0020)
#define XCERH_4    (0x0010)
#define XCERH_3    (0x0008)
#define XCERH_2    (0x0004)
#define XCERH_1    (0x0002)
#define XCERH_0    (0x0001)

// MCBSPLP_RINTCLR
   // NO BIT DEFINITIONS

// MCBSPLP_XINTCLR
   // NO BIT DEFINITIONS

// MCBSPLP_ROVFLCLR
   // NO BIT DEFINITIONS





// MCBSPLP_SYSCONFIG_REG
#define SYSCONFIG_CLOCKACTIVITY_1 (0x0200)
#define SYSCONFIG_CLOCKACTIVITY_0 (0x0100)
#define SYSCONFIG_SIDLEMODE_1     (0x0010)
#define SYSCONFIG_SIDLEMODE_0     (0x0008)
#define SYSCONFIG_ENAWAKEUP       (0x0004)
#define SYSCONFIG_SOFTRESET       (0x0002)

// MCBSPLP_THRSH2_REG
#define THRSH2_A    (0x0400)
#define THRSH2_9    (0x0200)
#define THRSH2_8    (0x0100)
#define THRSH2_7    (0x0080)
#define THRSH2_6    (0x0040)
#define THRSH2_5    (0x0020)
#define THRSH2_4    (0x0010)
#define THRSH2_3    (0x0008)
#define THRSH2_2    (0x0004)
#define THRSH2_1    (0x0002)
#define THRSH2_0    (0x0001)

// MCBSPLP_THRSH1_REG
#define THRSH1_A    (0x0400)
#define THRSH1_9    (0x0200)
#define THRSH1_8    (0x0100)
#define THRSH1_7    (0x0080)
#define THRSH1_6    (0x0040)
#define THRSH1_5    (0x0020)
#define THRSH1_4    (0x0010)
#define THRSH1_3    (0x0008)
#define THRSH1_2    (0x0004)
#define THRSH1_1    (0x0002)
#define THRSH1_0    (0x0001)


// MCBSPLP_IRQSTATUS_REG
#define IRQSTATUS_XEMPTYEOF  (0x4000)
#define IRQSTATUS_XOVFLSTAT  (0x1000)
#define IRQSTATUS_XUNDFLSTAT (0x0800)
#define IRQSTATUS_XRDY       (0x0400)
#define IRQSTATUS_XEOF       (0x0200)
#define IRQSTATUS_XFSX       (0x0100)
#define IRQSTATUS_XSYNCERR   (0x0080)
#define IRQSTATUS_ROVFLSTAT  (0x0020)
#define IRQSTATUS_RUNDFLSTAT (0x0010)
#define IRQSTATUS_RRDY       (0x0008)
#define IRQSTATUS_REOF       (0x0004)
#define IRQSTATUS_RFSR       (0x0002)
#define IRQSTATUS_RSYNCERR   (0x0001)

// MCBSPLP_IRQENABLE_REG
#define IRQENABLE_XEMPTYEOFEN  (0x4000)
#define IRQENABLE_XOVFLSTATEN  (0x1000)
#define IRQENABLE_XUNDFLSTATEN (0x0800)
#define IRQENABLE_XRDYEN       (0x0400)
#define IRQENABLE_XEOFEN       (0x0200)
#define IRQENABLE_XFSXEN       (0x0100)
#define IRQENABLE_XSYNCERREN   (0x0080)
#define IRQENABLE_ROVFLSTATEN  (0x0020)
#define IRQENABLE_RUNDFLSTATEN (0x0010)
#define IRQENABLE_RRDYEN       (0x0008)
#define IRQENABLE_REOFEN       (0x0004)
#define IRQENABLE_RFSREN       (0x0002)
#define IRQENABLE_RSYNCERREN   (0x0001)

// MCBSPLP_WAKEUPEN_REG
#define WAKEUPEN_XEMPTYEOFEN  (0x4000)
#define WAKEUPEN_XRDYEN       (0x0400)
#define WAKEUPEN_XEOFEN       (0x0200)
#define WAKEUPEN_XFSXEN       (0x0100)
#define WAKEUPEN_XSYNCERREN   (0x0080)
#define WAKEUPEN_RRDYEN       (0x0008)
#define WAKEUPEN_REOFEN       (0x0004)
#define WAKEUPEN_RFSREN       (0x0002)
#define WAKEUPEN_RSYNCERREN   (0x0001)

// MCBSPLP_XCCR_REG
#define XCCR_EXTCLKGATE       (0x8000)
#define XCCR_PPCONECT         (0x4000)
#define XCCR_DXENDLY_1        (0x2000)
#define XCCR_DXENDLY_0        (0x1000)
#define XCCR_XFULL_CYCLE      (0x0800)
#define XCCR_DLB              (0x0020)
#define XCCR_XDMAEN           (0x0008)
#define XCCR_XDISABLE         (0x0001)


// MCBSPLP_RCCR_REG
#define RCCR_RFULL_CYCLE      (0x0800)
#define RCCR_RDMAEN           (0x0008)
#define RCCR_RDISABLE         (0x0001)


// MCBSPLP_XBUFFSTAT_REG
// McBSP2 has 11 bits [10:0]
// Others only have 8 bits [7:0] - TBC
#define XBUFFSTAT_A           (0x0200)
#define XBUFFSTAT_8           (0x0100)
#define XBUFFSTAT_7           (0x0080)
#define XBUFFSTAT_6           (0x0040)
#define XBUFFSTAT_5           (0x0020)
#define XBUFFSTAT_4           (0x0010)
#define XBUFFSTAT_3           (0x0008)
#define XBUFFSTAT_2           (0x0004)
#define XBUFFSTAT_1           (0x0002)
#define XBUFFSTAT_0           (0x0001)

// MCBSPLP_RBUFFSTAT_REG
// McBSP2 has 11 bits [10:0]
// Others only have 8 bits [7:0] - TBC
#define RBUFFSTAT_A           (0x0200)
#define RBUFFSTAT_8           (0x0100)
#define RBUFFSTAT_7           (0x0080)
#define RBUFFSTAT_6           (0x0040)
#define RBUFFSTAT_5           (0x0020)
#define RBUFFSTAT_4           (0x0010)
#define RBUFFSTAT_3           (0x0008)
#define RBUFFSTAT_2           (0x0004)
#define RBUFFSTAT_1           (0x0002)
#define RBUFFSTAT_0           (0x0001)


// MCBSPLP_SSELCR_REG
#define SSELCR_SIDETONE       (0x0400)
#define SSELCR_OCH1ASSIGN_2   (0x0200)
#define SSELCR_OCH1ASSIGN_1   (0x0100)
#define SSELCR_OCH1ASSIGN_0   (0x0080)
#define SSELCR_OCH0ASSIGN_2   (0x0040)
#define SSELCR_OCH0ASSIGN_1   (0x0020)
#define SSELCR_OCH0ASSIGN_0   (0x0010)
#define SSELCR_ICH1ASSIGN_1   (0x0008)
#define SSELCR_ICH1ASSIGN_0   (0x0004)
#define SSELCR_ICH0ASSIGN_1   (0x0002)
#define SSELCR_ICH0ASSIGN_0   (0x0001)


// MCBSPLP_STATUS_REG
#define STATUS_CLKMUXSTATUS   (0x0001)

// MCBSPLP_ST_SYSCONFIG_REG
#define ST_SYSCONFIG_AUTOIDLE (0x0001)


// MCBSPLP_ST_IRQSTATUS_REG
#define ST_IRQSTATUS_OVRRERROR (0x0001)

// MCBSPLP_ST_IRQENABLE_REG
#define ST_IRQENABLE_OVRRERROREN (0x0001)

// MCBSPLP_ST_SGAINCR_REG
#define ST_GAINCR_CH1GAIN_F   (0x80000000)
#define ST_GAINCR_CH1GAIN_E   (0x40000000)
#define ST_GAINCR_CH1GAIN_D   (0x20000000)
#define ST_GAINCR_CH1GAIN_C   (0x10000000)
#define ST_GAINCR_CH1GAIN_B   (0x08000000)
#define ST_GAINCR_CH1GAIN_A   (0x04000000)
#define ST_GAINCR_CH1GAIN_9   (0x02000000)
#define ST_GAINCR_CH1GAIN_8   (0x01000000)
#define ST_GAINCR_CH1GAIN_7   (0x00800000)
#define ST_GAINCR_CH1GAIN_6   (0x00400000)
#define ST_GAINCR_CH1GAIN_5   (0x00200000)
#define ST_GAINCR_CH1GAIN_4   (0x00100000)
#define ST_GAINCR_CH1GAIN_3   (0x00080000)
#define ST_GAINCR_CH1GAIN_2   (0x00040000)
#define ST_GAINCR_CH1GAIN_1   (0x00020000)
#define ST_GAINCR_CH1GAIN_0   (0x00010000)
#define ST_GAINCR_CH0GAIN_F       (0x8000)
#define ST_GAINCR_CH0GAIN_E       (0x4000)
#define ST_GAINCR_CH0GAIN_D       (0x2000)
#define ST_GAINCR_CH0GAIN_C       (0x1000)
#define ST_GAINCR_CH0GAIN_B       (0x0800)
#define ST_GAINCR_CH0GAIN_A       (0x0400)
#define ST_GAINCR_CH0GAIN_9       (0x0200)
#define ST_GAINCR_CH0GAIN_8       (0x0100)
#define ST_GAINCR_CH0GAIN_7       (0x0080)
#define ST_GAINCR_CH0GAIN_6       (0x0040)
#define ST_GAINCR_CH0GAIN_5       (0x0020)
#define ST_GAINCR_CH0GAIN_4       (0x0010)
#define ST_GAINCR_CH0GAIN_3       (0x0008)
#define ST_GAINCR_CH0GAIN_2       (0x0004)
#define ST_GAINCR_CH0GAIN_1       (0x0002)
#define ST_GAINCR_CH0GAIN_0       (0x0001)

// MCBSPLP_ST_SFIRCR_REG
#define ST_SFIRCR_FIRCOEFF_f  (0x8000)
#define ST_SFIRCR_FIRCOEFF_e  (0x4000)
#define ST_SFIRCR_FIRCOEFF_d  (0x2000)
#define ST_SFIRCR_FIRCOEFF_c  (0x1000)
#define ST_SFIRCR_FIRCOEFF_b  (0x0800)
#define ST_SFIRCR_FIRCOEFF_a  (0x0400)
#define ST_SFIRCR_FIRCOEFF_9  (0x0200)
#define ST_SFIRCR_FIRCOEFF_8  (0x0100)
#define ST_SFIRCR_FIRCOEFF_7  (0x0080)
#define ST_SFIRCR_FIRCOEFF_6  (0x0040)
#define ST_SFIRCR_FIRCOEFF_5  (0x0020)
#define ST_SFIRCR_FIRCOEFF_4  (0x0010)
#define ST_SFIRCR_FIRCOEFF_3  (0x0008)
#define ST_SFIRCR_FIRCOEFF_2  (0x0004)
#define ST_SFIRCR_FIRCOEFF_1  (0x0002)
#define ST_SFIRCR_FIRCOEFF_0  (0x0001)

// MCBSPLP_STSELCR_REG
#define STSELCR_COEFFWRDONE   (0x0004)
#define STSELCR_COEFFWREN     (0x0002)
#define STSELCR_SIDETONEEN    (0x0001)



// MCBSP1
#define MCBSP1_DRR       (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000000))
#define MCBSP1_DXR       (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000008)) 
#define MCBSP1_SPCR2     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000010)) 
#define MCBSP1_SPCR1     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000014)) 
#define MCBSP1_RCR2      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000018)) 
#define MCBSP1_RCR1      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000001C)) 
#define MCBSP1_XCR2      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000020)) 
#define MCBSP1_XCR1      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000024)) 
#define MCBSP1_SRGR2     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000028)) 
#define MCBSP1_SRGR1     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000002C)) 
#define MCBSP1_MCR2      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000030)) 
#define MCBSP1_MCR1      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000034)) 
#define MCBSP1_RCERA     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000038)) 
#define MCBSP1_RCERB     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000003C)) 
#define MCBSP1_XCERA     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000040)) 
#define MCBSP1_XCERB     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000044)) 
#define MCBSP1_PCR       (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000048)) 
#define MCBSP1_RCERC     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000004C)) 
#define MCBSP1_RCERD     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000050)) 
#define MCBSP1_XCERC     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000054)) 
#define MCBSP1_XCERD     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000058)) 
#define MCBSP1_RCERE     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000005C)) 
#define MCBSP1_RCERF     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000060)) 
#define MCBSP1_XCERE     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000064)) 
#define MCBSP1_XCERF     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000068)) 
#define MCBSP1_RCERG     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000006C)) 
#define MCBSP1_RCERH     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000070)) 
#define MCBSP1_XCERG     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000074)) 
#define MCBSP1_XCERH     (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000078)) 
#define MCBSP1_RINTCLR   (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000080)) 
#define MCBSP1_XINTCLR   (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000084)) 
#define MCBSP1_ROVFLCLR  (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000088)) 
#define MCBSP1_SYSCONFIG (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x0000008C)) 
#define MCBSP1_THRSH2    (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000090)) 
#define MCBSP1_THRSH1    (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x00000094)) 
#define MCBSP1_IRQSTATUS (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000A0)) 
#define MCBSP1_IRQENABLE (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000A4)) 
#define MCBSP1_WAKEUPEN  (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000A8)) 
#define MCBSP1_XCCR      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000AC)) 
#define MCBSP1_RCCR      (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000B0)) 
#define MCBSP1_XBUFFSTAT (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000B4))
#define MCBSP1_RBUFFSTAT (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000B8))
#define MCBSP1_SSELCR    (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000BC)) 
#define MCBSP1_STATUS    (*(volatile uint32_t*)(MCBSP1_REG_BASE + 0x000000C0))


// MCBSP 5
#define MCBSP5_DRR       (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000000))
#define MCBSP5_DXR       (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000008)) 
#define MCBSP5_SPCR2     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000010)) 
#define MCBSP5_SPCR1     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000014)) 
#define MCBSP5_RCR2      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000018)) 
#define MCBSP5_RCR1      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000001C)) 
#define MCBSP5_XCR2      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000020)) 
#define MCBSP5_XCR1      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000024)) 
#define MCBSP5_SRGR2     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000028)) 
#define MCBSP5_SRGR1     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000002C)) 
#define MCBSP5_MCR2      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000030)) 
#define MCBSP5_MCR1      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000034)) 
#define MCBSP5_RCERA     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000038)) 
#define MCBSP5_RCERB     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000003C)) 
#define MCBSP5_XCERA     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000040)) 
#define MCBSP5_XCERB     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000044)) 
#define MCBSP5_PCR       (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000048)) 
#define MCBSP5_RCERC     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000004C)) 
#define MCBSP5_RCERD     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000050)) 
#define MCBSP5_XCERC     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000054)) 
#define MCBSP5_XCERD     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000058)) 
#define MCBSP5_RCERE     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000005C)) 
#define MCBSP5_RCERF     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000060)) 
#define MCBSP5_XCERE     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000064)) 
#define MCBSP5_XCERF     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000068)) 
#define MCBSP5_RCERG     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000006C)) 
#define MCBSP5_RCERH     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000070)) 
#define MCBSP5_XCERG     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000074)) 
#define MCBSP5_XCERH     (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000078)) 
#define MCBSP5_RINTCLR   (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000080)) 
#define MCBSP5_XINTCLR   (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000084)) 
#define MCBSP5_ROVFLCLR  (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000088)) 
#define MCBSP5_SYSCONFIG (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x0000008C)) 
#define MCBSP5_THRSH2    (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000090)) 
#define MCBSP5_THRSH1    (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x00000094)) 
#define MCBSP5_IRQSTATUS (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000A0)) 
#define MCBSP5_IRQENABLE (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000A4)) 
#define MCBSP5_WAKEUPEN  (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000A8)) 
#define MCBSP5_XCCR      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000AC)) 
#define MCBSP5_RCCR      (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000B0)) 
#define MCBSP5_XBUFFSTAT (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000B4))
#define MCBSP5_RBUFFSTAT (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000B8))
#define MCBSP5_SSELCR    (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000BC)) 
#define MCBSP5_STATUS    (*(volatile uint32_t*)(MCBSP5_REG_BASE + 0x000000C0))

// MCBSP 2
#define MCBSP2_DRR       (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000000))
#define MCBSP2_DXR       (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000008)) 
#define MCBSP2_SPCR2     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000010)) 
#define MCBSP2_SPCR1     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000014)) 
#define MCBSP2_RCR2      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000018)) 
#define MCBSP2_RCR1      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000001C)) 
#define MCBSP2_XCR2      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000020)) 
#define MCBSP2_XCR1      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000024)) 
#define MCBSP2_SRGR2     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000028)) 
#define MCBSP2_SRGR1     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000002C)) 
#define MCBSP2_MCR2      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000030)) 
#define MCBSP2_MCR1      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000034)) 
#define MCBSP2_RCERA     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000038)) 
#define MCBSP2_RCERB     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000003C)) 
#define MCBSP2_XCERA     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000040)) 
#define MCBSP2_XCERB     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000044)) 
#define MCBSP2_PCR       (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000048)) 
#define MCBSP2_RCERC     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000004C)) 
#define MCBSP2_RCERD     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000050)) 
#define MCBSP2_XCERC     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000054)) 
#define MCBSP2_XCERD     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000058)) 
#define MCBSP2_RCERE     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000005C)) 
#define MCBSP2_RCERF     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000060)) 
#define MCBSP2_XCERE     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000064)) 
#define MCBSP2_XCERF     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000068)) 
#define MCBSP2_RCERG     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000006C)) 
#define MCBSP2_RCERH     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000070)) 
#define MCBSP2_XCERG     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000074)) 
#define MCBSP2_XCERH     (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000078)) 
#define MCBSP2_RINTCLR   (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000080)) 
#define MCBSP2_XINTCLR   (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000084)) 
#define MCBSP2_ROVFLCLR  (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000088)) 
#define MCBSP2_SYSCONFIG (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x0000008C)) 
#define MCBSP2_THRSH2    (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000090)) 
#define MCBSP2_THRSH1    (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x00000094)) 
#define MCBSP2_IRQSTATUS (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000A0)) 
#define MCBSP2_IRQENABLE (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000A4)) 
#define MCBSP2_WAKEUPEN  (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000A8)) 
#define MCBSP2_XCCR      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000AC)) 
#define MCBSP2_RCCR      (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000B0)) 
#define MCBSP2_XBUFFSTAT (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000B4))
#define MCBSP2_RBUFFSTAT (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000B8))
#define MCBSP2_SSELCR    (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000BC)) 
#define MCBSP2_STATUS    (*(volatile uint32_t*)(MCBSP2_REG_BASE + 0x000000C0))

//MCBSP 3
#define MCBSP3_DRR       (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000000))
#define MCBSP3_DXR       (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000008)) 
#define MCBSP3_SPCR2     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000010)) 
#define MCBSP3_SPCR1     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000014)) 
#define MCBSP3_RCR2      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000018)) 
#define MCBSP3_RCR1      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000001C)) 
#define MCBSP3_XCR2      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000020)) 
#define MCBSP3_XCR1      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000024)) 
#define MCBSP3_SRGR2     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000028)) 
#define MCBSP3_SRGR1     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000002C)) 
#define MCBSP3_MCR2      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000030)) 
#define MCBSP3_MCR1      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000034)) 
#define MCBSP3_RCERA     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000038)) 
#define MCBSP3_RCERB     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000003C)) 
#define MCBSP3_XCERA     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000040)) 
#define MCBSP3_XCERB     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000044)) 
#define MCBSP3_PCR       (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000048)) 
#define MCBSP3_RCERC     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000004C)) 
#define MCBSP3_RCERD     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000050)) 
#define MCBSP3_XCERC     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000054)) 
#define MCBSP3_XCERD     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000058)) 
#define MCBSP3_RCERE     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000005C)) 
#define MCBSP3_RCERF     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000060)) 
#define MCBSP3_XCERE     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000064)) 
#define MCBSP3_XCERF     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000068)) 
#define MCBSP3_RCERG     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000006C)) 
#define MCBSP3_RCERH     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000070)) 
#define MCBSP3_XCERG     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000074)) 
#define MCBSP3_XCERH     (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000078)) 
#define MCBSP3_RINTCLR   (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000080)) 
#define MCBSP3_XINTCLR   (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000084)) 
#define MCBSP3_ROVFLCLR  (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000088)) 
#define MCBSP3_SYSCONFIG (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x0000008C)) 
#define MCBSP3_THRSH2    (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000090)) 
#define MCBSP3_THRSH1    (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x00000094)) 
#define MCBSP3_IRQSTATUS (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000A0)) 
#define MCBSP3_IRQENABLE (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000A4)) 
#define MCBSP3_WAKEUPEN  (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000A8)) 
#define MCBSP3_XCCR      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000AC)) 
#define MCBSP3_RCCR      (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000B0)) 
#define MCBSP3_XBUFFSTAT (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000B4))
#define MCBSP3_RBUFFSTAT (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000B8))
#define MCBSP3_SSELCR    (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000BC)) 
#define MCBSP3_STATUS    (*(volatile uint32_t*)(MCBSP3_REG_BASE + 0x000000C0))


//MCBSP 4
#define MCBSP4_DRR       (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000000))
#define MCBSP4_DXR       (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000008)) 
#define MCBSP4_SPCR2     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000010)) 
#define MCBSP4_SPCR1     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000014)) 
#define MCBSP4_RCR2      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000018)) 
#define MCBSP4_RCR1      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000001C)) 
#define MCBSP4_XCR2      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000020)) 
#define MCBSP4_XCR1      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000024)) 
#define MCBSP4_SRGR2     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000028)) 
#define MCBSP4_SRGR1     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000002C)) 
#define MCBSP4_MCR2      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000030)) 
#define MCBSP4_MCR1      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000034)) 
#define MCBSP4_RCERA     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000038)) 
#define MCBSP4_RCERB     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000003C)) 
#define MCBSP4_XCERA     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000040)) 
#define MCBSP4_XCERB     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000044)) 
#define MCBSP4_PCR       (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000048)) 
#define MCBSP4_RCERC     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000004C)) 
#define MCBSP4_RCERD     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000050)) 
#define MCBSP4_XCERC     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000054)) 
#define MCBSP4_XCERD     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000058)) 
#define MCBSP4_RCERE     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000005C)) 
#define MCBSP4_RCERF     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000060)) 
#define MCBSP4_XCERE     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000064)) 
#define MCBSP4_XCERF     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000068)) 
#define MCBSP4_RCERG     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000006C)) 
#define MCBSP4_RCERH     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000070)) 
#define MCBSP4_XCERG     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000074)) 
#define MCBSP4_XCERH     (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000078)) 
#define MCBSP4_RINTCLR   (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000080)) 
#define MCBSP4_XINTCLR   (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000084)) 
#define MCBSP4_ROVFLCLR  (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000088)) 
#define MCBSP4_SYSCONFIG (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x0000008C)) 
#define MCBSP4_THRSH2    (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000090)) 
#define MCBSP4_THRSH1    (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x00000094)) 
#define MCBSP4_IRQSTATUS (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000A0)) 
#define MCBSP4_IRQENABLE (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000A4)) 
#define MCBSP4_WAKEUPEN  (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000A8)) 
#define MCBSP4_XCCR      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000AC)) 
#define MCBSP4_RCCR      (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000B0)) 
#define MCBSP4_XBUFFSTAT (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000B4))
#define MCBSP4_RBUFFSTAT (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000B8))
#define MCBSP4_SSELCR    (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000BC)) 
#define MCBSP4_STATUS    (*(volatile uint32_t*)(MCBSP4_REG_BASE + 0x000000C0))

//SIDETONE_MCBSP2
#define MCBSP2_ST_SYSCONFIG      (*(volatile uint32_t*)(SIDETONE_MCBSP2_REG_BASE + 0x00000010)) 
#define MCBSP2_ST_IRQSTATUS      (*(volatile uint32_t*)(SIDETONE_MCBSP2_REG_BASE + 0x00000018)) 
#define MCBSP2_ST_IRQENABLE      (*(volatile uint32_t*)(SIDETONE_MCBSP2_REG_BASE + 0x0000001C)) 
#define MCBSP2_ST_SGAINCR        (*(volatile uint32_t*)(SIDETONE_MCBSP2_REG_BASE + 0x00000024)) 
#define MCBSP2_ST_SFIRCR         (*(volatile uint32_t*)(SIDETONE_MCBSP2_REG_BASE + 0x00000028)) 
#define MCBSP2_ST_SSELCR         (*(volatile uint32_t*)(SIDETONE_MCBSP2_REG_BASE + 0x0000002C)) 
                                                
//SIDETONE_MCBSP3                               
#define MCBSP3_ST_SYSCONFIG      (*(volatile uint32_t*)(SIDETONE_MCBSP3_REG_BASE + 0x00000010)) 
#define MCBSP3_ST_IRQSTATUS      (*(volatile uint32_t*)(SIDETONE_MCBSP3_REG_BASE + 0x00000018)) 
#define MCBSP3_ST_IRQENABLE      (*(volatile uint32_t*)(SIDETONE_MCBSP3_REG_BASE + 0x0000001C)) 
#define MCBSP3_ST_SGAINCR        (*(volatile uint32_t*)(SIDETONE_MCBSP3_REG_BASE + 0x00000024)) 
#define MCBSP3_ST_SFIRCR         (*(volatile uint32_t*)(SIDETONE_MCBSP3_REG_BASE + 0x00000028)) 
#define MCBSP3_ST_SSELCR         (*(volatile uint32_t*)(SIDETONE_MCBSP3_REG_BASE + 0x0000002C)) 


#define mcbspEnableIclk_1   SETBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP1) 
#define mcbspEnableIclk_2   SETBIT_REGL(CM_ICLKEN_PER,   CM_ICLKEN_PER_EN_MCBSP2);
#define mcbspEnableIclk_3   SETBIT_REGL(CM_ICLKEN_PER,   CM_ICLKEN_PER_EN_MCBSP3);
#define mcbspEnableIclk_4   SETBIT_REGL(CM_ICLKEN_PER,   CM_ICLKEN_PER_EN_MCBSP4);
#define mcbspEnableIclk_5   SETBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP5)

#define mcbspDisableIclk_1  CLRBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP1) 
#define mcbspDisableIclk_2  CLRBIT_REGL(CM_ICLKEN_PER,   CM_ICLKEN_PER_EN_MCBSP2);
#define mcbspDisableIclk_3  CLRBIT_REGL(CM_ICLKEN_PER,   CM_ICLKEN_PER_EN_MCBSP3);
#define mcbspDisableIclk_4  CLRBIT_REGL(CM_ICLKEN_PER,   CM_ICLKEN_PER_EN_MCBSP4);
#define mcbspDisableIclk_5  CLRBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP5)

#define mcbspEnableFclk_1   SETBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP1) 
#define mcbspEnableFclk_2   SETBIT_REGL(CM_FCLKEN_PER,   CM_FCLKEN_PER_EN_MCBSP2);
#define mcbspEnableFclk_3   SETBIT_REGL(CM_FCLKEN_PER,   CM_FCLKEN_PER_EN_MCBSP3);
#define mcbspEnableFclk_4   SETBIT_REGL(CM_FCLKEN_PER,   CM_FCLKEN_PER_EN_MCBSP4);
#define mcbspEnableFclk_5   SETBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP5)

#define mcbspDisableFclk_1  CLRBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP1) 
#define mcbspDisableFclk_2  CLRBIT_REGL(CM_FCLKEN_PER,   CM_FCLKEN_PER_EN_MCBSP2);
#define mcbspDisableFclk_3  CLRBIT_REGL(CM_FCLKEN_PER,   CM_FCLKEN_PER_EN_MCBSP3);
#define mcbspDisableFclk_4  CLRBIT_REGL(CM_FCLKEN_PER,   CM_FCLKEN_PER_EN_MCBSP4);
#define mcbspDisableFclk_5  CLRBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP5)

#define mcbspSelectClksSourceFclk_1 CLRBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKS);
#define mcbspSelectClksSourceFclk_2 CLRBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP2_CLKS);
#define mcbspSelectClksSourceFclk_3 CLRBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP3_CLKS);
#define mcbspSelectClksSourceFclk_4 CLRBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP4_CLKS);
#define mcbspSelectClksSourceFclk_5 CLRBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP5_CLKS);

#define mcbspSelectClksSourceClks_1 SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKS);
#define mcbspSelectClksSourceClks_2 SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP2_CLKS);
#define mcbspSelectClksSourceClks_3 SETBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP3_CLKS);
#define mcbspSelectClksSourceClks_4 SETBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP4_CLKS);
#define mcbspSelectClksSourceClks_5 SETBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP5_CLKS);





/*                                                 
const PIN_CONFIG  mcbsp_clks_pin_mux[] =
{
      { CONTROL_PADCONF_mcbsp_clks,    MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp_clks
};


const PIN_CONFIG  mcbsp1_pin_mux_master[] =
{
      { CONTROL_PADCONF_mcbsp_clks_HI, MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp1_fsx
      { CONTROL_PADCONF_mcbsp1_clkx,   MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp1_clkx
      { CONTROL_PADCONF_mcbsp1_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_dr
      { CONTROL_PADCONF_mcbsp1_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp1_dx
};
const PIN_CONFIG  mcbsp1_pin_mux_master_6pin[] =
{
      { CONTROL_PADCONF_mcbsp1_clkr_HI,MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp1_fsr
      { CONTROL_PADCONF_mcbsp1_clkr,   MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp1_clkr
      { CONTROL_PADCONF_mcbsp_clks_HI, MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp1_fsx
      { CONTROL_PADCONF_mcbsp1_clkx,   MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp1_clkx
      { CONTROL_PADCONF_mcbsp1_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_dr
      { CONTROL_PADCONF_mcbsp1_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp1_dx
};
const PIN_CONFIG  mcbsp1_pin_mux_rx_master_6pin[] =
{
      { CONTROL_PADCONF_mcbsp1_clkr_HI,MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_fsr
      { CONTROL_PADCONF_mcbsp1_clkr,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_clkr
      { CONTROL_PADCONF_mcbsp_clks_HI, MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_fsx
      { CONTROL_PADCONF_mcbsp1_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_clkx
      { CONTROL_PADCONF_mcbsp1_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_dr
      { CONTROL_PADCONF_mcbsp1_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp1_dx
};
const PIN_CONFIG  mcbsp1_pin_mux_slave[] =
{
      { CONTROL_PADCONF_mcbsp_clks_HI, MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_fsx
      { CONTROL_PADCONF_mcbsp1_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_clkx
      { CONTROL_PADCONF_mcbsp1_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_dr
      { CONTROL_PADCONF_mcbsp1_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp1_dx
};
const PIN_CONFIG  mcbsp1_pin_mux_slave_6pin[] =
{
      { CONTROL_PADCONF_mcbsp1_clkr_HI,MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_fsr
      { CONTROL_PADCONF_mcbsp1_clkr,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_clkr
      { CONTROL_PADCONF_mcbsp_clks_HI, MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_fsx
      { CONTROL_PADCONF_mcbsp1_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_clkx
      { CONTROL_PADCONF_mcbsp1_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp1_dr
      { CONTROL_PADCONF_mcbsp1_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp1_dx
};
const PIN_CONFIG  mcbsp2_pin_mux_master[] =
{
      { CONTROL_PADCONF_mcbsp2_fsx_HI, MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp2_clkx
      { CONTROL_PADCONF_mcbsp2_fsx,    MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp2_fsx
      { CONTROL_PADCONF_mcbsp2_dr_HI,  MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp2_dx
      { CONTROL_PADCONF_mcbsp2_dr,     MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN } // mcbsp2_dr
};
const PIN_CONFIG  mcbsp2_pin_mux_slave[] =
{
      { CONTROL_PADCONF_mcbsp2_fsx_HI, MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp2_clkx
      { CONTROL_PADCONF_mcbsp2_fsx,    MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp2_fsx
      { CONTROL_PADCONF_mcbsp2_dr_HI,  MODE0, PUPD_DIS, PULL_DOWN            },// mcbsp2_dx
      { CONTROL_PADCONF_mcbsp2_dr,     MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN } // mcbsp2_dr
};
const PIN_CONFIG  mcbsp3_pin_mux_master[] =
{
      { CONTROL_PADCONF_mcbsp3_clkx_HI,MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp3_fsx
      { CONTROL_PADCONF_mcbsp3_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp3_clkx
      { CONTROL_PADCONF_mcbsp3_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp3_dr
      { CONTROL_PADCONF_mcbsp3_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp3_dx
};
const PIN_CONFIG  mcbsp3_pin_mux_slave[] =
{
      { CONTROL_PADCONF_mcbsp3_clkx_HI,MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp3_fsx
      { CONTROL_PADCONF_mcbsp3_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp3_clkx
      { CONTROL_PADCONF_mcbsp3_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp3_dr
      { CONTROL_PADCONF_mcbsp3_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp3_dx
};
const PIN_CONFIG  mcbsp4_pin_mux_master[] =
{
      { CONTROL_PADCONF_mcbsp4_clkx_HI,MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp4_dr
      { CONTROL_PADCONF_mcbsp4_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp4_clkx
      { CONTROL_PADCONF_mcbsp4_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp4_fsx
      { CONTROL_PADCONF_mcbsp4_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp4_dx
};
const PIN_CONFIG  mcbsp4_pin_mux_slave[] =
{
      { CONTROL_PADCONF_mcbsp4_clkx_HI,MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp4_fsx
      { CONTROL_PADCONF_mcbsp4_clkx,   MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp4_clkx
      { CONTROL_PADCONF_mcbsp4_dx_HI,  MODE0, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp4_dr
      { CONTROL_PADCONF_mcbsp4_dx,     MODE0, PUPD_DIS, PULL_DOWN            } // mcbsp4_dx
};
const PIN_CONFIG  mcbsp5_pin_mux_master[] =
{
      { CONTROL_PADCONF_etk_clk_HI,    MODE1, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp5_clkx
      { CONTROL_PADCONF_etk_d4,        MODE1, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp5_dr
      { CONTROL_PADCONF_etk_d4_HI,     MODE1, PUPD_DIS, PULL_DOWN | INPUT_EN           },// mcbsp5_fsx
      { CONTROL_PADCONF_etk_d6,        MODE1, PUPD_DIS, PULL_DOWN            } // mcbsp5_dx
};
const PIN_CONFIG  mcbsp5_pin_mux_slave[] =
{
      { CONTROL_PADCONF_etk_clk_HI,    MODE1, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp5_clkx
      { CONTROL_PADCONF_etk_d4,        MODE1, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp5_dr
      { CONTROL_PADCONF_etk_d4_HI,     MODE1, PUPD_DIS, PULL_DOWN | INPUT_EN },// mcbsp5_fsx
      { CONTROL_PADCONF_etk_d6,        MODE1, PUPD_DIS, PULL_DOWN            } // mcbsp5_dx
};

*/

#endif
                                                
