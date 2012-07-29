/* DMA Function Library Source File
 * 
 * Version 0.01  (Still under development/debug)
 *
 * Function library to support quick low level configuration testing.
 *
 */
#include <linux/io.h>

#include "rd_reg_op.h"
#include "rd_dma_lib.h"
#include "rd_dma_reg.h"

#define SZ_4K	0x00001000
void __iomem *dma_base_addr;

void __iomem *dma_base_addr_init(void)
{
	dma_base_addr = ioremap(DMA_BASE, SZ_4K);
	return dma_base_addr;
}

/////////////////////////////////////////////////////////////
// Set Channel Source Destination Parameters 
//
void dmaSetCsdp(  unsigned char ulChan,             // Channel to configure 
                  unsigned char ulSrcEndian,        // Channel source endianness control
                  unsigned char ulSrcEndianLock,    // Source endianness Lock
                  unsigned char ulDstEndian,        // Channel destination endianness control
                  unsigned char ulDstEndianLock,    // Destination endianness Lock
                  unsigned char ulWriteMode,        // Used to enable writing mode without posting or with posting
                  unsigned char ulDstBurstEn,       // Used to enable bursting on the Write Port. Smaller burst size than the programmed burst size is also allowed
                  unsigned char ulDstPacked,        // Destination receives packed data
                  unsigned char ulSrcBurstEn,       // Used to enable bursting on the Read Port. Smaller burst size than the programmed burst size is also allowed
                  unsigned char ulSrcPacked,        // Source provides packed data.
                  unsigned char ulDataType          // Defines the type of the data moved in the channel.
                  )
{
    OUT_REGL(DMA_CSDPi + dma_base_addr + (ulChan * 0x60),    (ulSrcEndian     << 21) +
	                                         (ulSrcEndianLock << 20) +
	                                         (ulDstEndian     << 19) +
	                                         (ulDstEndianLock << 18) +
	                                         (ulWriteMode     << 16) +
	                                         (ulDstBurstEn    << 14) + 
	                                         (ulDstPacked     << 13) +
	                                         (ulSrcBurstEn    <<  7) +
	                                         (ulSrcPacked     <<  6) +
	                                         (ulDataType      <<  0)); 
}
               	
                
/////////////////////////////////////////////////////////////
// Set Channel Control Register  Parameters 
//
// Note: Channel is disabled by default.
// 
void dmaSetCcr(   unsigned char ulChan,                    // Channel to configure 
                  unsigned char ulWritePriority,           // Channel priority on the Write side
                  unsigned char ulBufferingDisable,        // This bit allows to disable the default buffering 
                                                           //    functionality when transfer is source synchronized
                  unsigned char ulSelSrcDstSync,           // Specifies that element, packet, frame or block transfer 
                                                           //    (depending on CCR.bs and CCR.fs) is triggered by the 
                                                           //    source or the destination on the DMA request
                  unsigned char ulPrefetch,                // Enables the prefetch mode
                  unsigned char ulSupervisor,              // Enables the supervisor mode
                  unsigned char ulTransparentCopyEnable,   // Transparent copy enable
                  unsigned char ulConstFillEnable,         // Constant fill enable
                  unsigned char ulDstAmode,                // Selects the addressing mode on the Write Port of a channel
                  unsigned char ulSrcAmode,                // Selects the addressing mode on the Read Port of a channel
                  unsigned char ulSuspendSensitive,        // Logical channel suspend enable bit
                  unsigned char ulEnable,                  // Logical channel enable. It is SW responsibility to clear the
                                                           //    CSR register and the IRQSTATUS bit for the different
                                                           //    interrupt lines before enabling the channe
                  unsigned char ulReadPriority,            // Channel priority on the read side
                  unsigned char ulTransType,               // Frame/block synchronization (BS+FS)
                                                           //    This determines how the DMA request is serviced in a 
                                                           //    synchronized transfer
                  unsigned char ulSynchroControl           // Channel synchronization control (all 7 bits)
                  )
{
   unsigned char  bs, fs, synchroControlUpper, synchroControl;

    bs = (ulTransType & 0x2)>>1;                           // bit1=BS, bit0=FS
    fs = (ulTransType & 0x1);
    synchroControlUpper = ((ulSynchroControl + 1) & 0x60) >> 5;  // Add 1 as per TRM
    synchroControl      = ((ulSynchroControl + 1) & 0x1F);       // Add 1 as per TRM
    OUT_REGL(DMA_CCRi + dma_base_addr + (ulChan * 0x60),    (ulWritePriority         << 26) +
	                                        (ulBufferingDisable      << 25) +
	                                        (ulSelSrcDstSync         << 24) +
	                                        (ulPrefetch              << 23) +
	                                        (ulSupervisor            << 22) +
	                                        (synchroControlUpper     << 19) +
	                                        (bs                      << 18) +
	                                        (ulTransparentCopyEnable << 17) +
	                                        (ulConstFillEnable       << 16) +
	                                        (ulDstAmode              << 14) +
	                                        (ulSrcAmode              << 12) +
	                                        (ulSuspendSensitive      <<  8) +
	                                        (ulEnable                <<  7) +
	                                        (ulReadPriority          <<  6) +
	                                        (fs                      <<  5) +
	                                        (synchroControl          <<  0));
}


/////////////////////////////////////////////////////////////
// Setup transfer size
void dmaConfigTransfer(unsigned char ulChan,             // Channel to configure 
                       unsigned int  ulCen,              // Number of elements within a frame (unsigned) to transfer
                       unsigned int  ulCfn,              // Number of frames within the block to be transferred
                       unsigned int  ulCssa,             // 32 bits of the source start address
                       unsigned int  ulCdsa,             // 32 bits of the destination start address
                       unsigned int  ulCsei,             // Channel Source Element Index (Signed)
                       unsigned int  ulCsfi,             // Channel Source Frame Index (Signed) or 16-bit Packet size
                       unsigned int  ulCdei,             // Channel Destination Element Index (Signed)
                       unsigned int  ulCdfi              // Channel Destination Frame Index (Signed) or 16-bit Packet size
                       )
{
	OUT_REGL(DMA_CENi + dma_base_addr  + (ulChan * 0x60), ulCen);        // Number of elements within a frame (unsigned) to transfer
	OUT_REGL(DMA_CFNi + dma_base_addr  + (ulChan * 0x60), ulCfn);        // Number of frames within the block to be transferred
	OUT_REGL(DMA_CSSAi + dma_base_addr + (ulChan * 0x60), ulCssa);       // 32 bits of the source start address
	OUT_REGL(DMA_CDSAi + dma_base_addr + (ulChan * 0x60), ulCdsa);       // 32 bits of the destination start address
	OUT_REGL(DMA_CSEIi + dma_base_addr + (ulChan * 0x60), ulCsei);       // Channel source element index
	OUT_REGL(DMA_CSFIi + dma_base_addr + (ulChan * 0x60), ulCsfi);       // Channel source frame index value if source address is 
	                                                     // in RW 16BIT_PKT_ELNT_NBR double index mode. 
	                                                     // Or if fs=bs=1 and DMA_CCR[SEL_SRC_DST_SYNC]=1; the bit 
	                                                     // field [15:0] gives the number of element in packet. 
	                                                     // The field [31:16] is unused for the packet size.
	OUT_REGL(DMA_CDEIi + dma_base_addr + (ulChan * 0x60), ulCdei);       // Channel destination element index	                                        	                                         
	OUT_REGL(DMA_CDFIi + dma_base_addr + (ulChan * 0x60), ulCdfi);       // Channel destination frame index value if destination  
	                                                     // address is in double index mode. 
	                                                     // Or if fs=bs=1 and DMA_CCR[SEL_SRC_DST_SYNC]=1; the bit 
	                                                     // field [15:0] gives the number of element in packet. 
	                                                     // The field [31:16] is unused for the packet size.
}                       



/////////////////////////////////////////////////////////////
// Set channel link
void dmaSetChannelLink(unsigned char ulChan,             // Channel to configure 
                       unsigned char ulNextchId ,        // Channel link target
                       unsigned char ulEnableLink        // Enable/Disable link          
                       )
{
    CLRBIT_REGL(DMA_CLNK_CTRLi + dma_base_addr + (ulChan * 0x60), 0x1F);        // Clear NEXTLCH_ID field 
	SETBIT_REGL(DMA_CLNK_CTRLi + dma_base_addr + (ulChan * 0x60), (ulEnableLink << 15) + ulNextchId);  // Configure channel Linking
}                       



/////////////////////////////////////////////////////////////
//
void dmaSetSourceAddress(unsigned char ulChan,           // Channel to configure 
                         unsigned int  ulCssa            // 32 bits of the source start address
                         )
{
	OUT_REGL(DMA_CSSAi + dma_base_addr + (ulChan * 0x60), ulCssa);       // 32 bits of the source start address
}

                         
/////////////////////////////////////////////////////////////
// 
void dmaSetDestinationAddress(unsigned char ulChan,     // Channel to configure 
                              unsigned int  ulCdsa      // 32 bits of the destination start address
                              )
{
	OUT_REGL(DMA_CDSAi + dma_base_addr + (ulChan * 0x60), ulCdsa);      // 32 bits of the destination start address
}

/////////////////////////////////////////////////////////////
// Enable DMA channel
void dmaEnableChannel(unsigned char ulChan){
   SETBIT_REGL(DMA_CCRi + dma_base_addr + (ulChan * 0x60), CCR_ENABLE); // Disable channel
}

/////////////////////////////////////////////////////////////
// Disable DMA channel
void dmaDisableChannel(unsigned char ulChan)
{
    CLRBIT_REGL(DMA_CCRi + dma_base_addr + (ulChan * 0x60), CCR_ENABLE); // Disable channel
}

/////////////////////////////////////////////////////////////
// Enable DMA channel
void dmaEnableLink(unsigned char ulChan)
{
    SETBIT_REGL(DMA_CLNK_CTRLi + dma_base_addr + (ulChan * 0x60), CLNK_CTRL_ENABLE_LNK);  // Enable channel linking
}

/////////////////////////////////////////////////////////////
// Disable DMA channel
void dmaDisableLink(unsigned char ulChan)
{
    CLRBIT_REGL(DMA_CLNK_CTRLi + dma_base_addr + (ulChan * 0x60), CLNK_CTRL_ENABLE_LNK);  // disable channel linking
}

