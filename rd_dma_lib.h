/*

Header file for dma_utils

V1.00

*/
#ifndef _RD_DMA_LIB_H
#define _RD_DMA_LIB_H

void __iomem *dma_base_addr_init(void);


///////////////////////////////////////////////////////////
//Prototypes
//
void dmaSetCsdp(unsigned char ulChan,                    // Channel to configure 
                unsigned char ulSrcEndian,               // Channel source endianness control
                unsigned char ulSrcEndianLock,           // Source endianness Lock
                unsigned char ulDstEndian,               // Channel destination endianness control
                unsigned char ulDstEndianLock,           // Destination endianness Lock
                unsigned char ulWriteMode,               // Used to enable writing mode without posting or with posting
                unsigned char ulDstBurstEn,              // Used to enable bursting on the Write Port. Smaller burst size than the programmed burst size is also allowed
                unsigned char ulDstPacked,               // Destination receives packed data
                unsigned char ulSrcBurstEn,              // Used to enable bursting on the Read Port. Smaller burst size than the programmed burst size is also allowed
                unsigned char ulSrcPacked,               // Source provides packed data.
                unsigned char ulDataType                 // Defines the type of the data moved in the channel.
                );


void dmaSetCcr(unsigned char ulChan,                     // Channel to configure 
               unsigned char ulWritePriority,            // Channel priority on the Write side
               unsigned char ulBufferingDisable,         // This bit allows to disable the default buffering 
                                                         //    functionality when transfer is source synchronized
               unsigned char ulSelSrcDstSync,            // Specifies that element, packet, frame or block transfer 
                                                         //    (depending on CCR.bs and CCR.fs) is triggered by the 
                                                         //    source or the destination on the DMA request
               unsigned char ulPrefetch,                 // Enables the prefetch mode
               unsigned char ulSupervisor,               // Enables the supervisor mode
               unsigned char ulTransparentCopyEnable,    // Transparent copy enable
               unsigned char ulConstFillEnable,          // Constant fill enable
               unsigned char ulDstAmode,                 // Selects the addressing mode on the Write Port of a channel
               unsigned char ulSrcAmode,                 // Selects the addressing mode on the Read Port of a channel
               unsigned char ulSuspendSensitive,         // Logical channel suspend enable bit
               unsigned char ulEnable,                   // Logical channel enable. It is SW responsibility to clear the
                                                         //    CSR register and the IRQSTATUS bit for the different
                                                         //    interrupt lines before enabling the channe
               unsigned char ulReadPriority,             // Channel priority on the read side
               unsigned char ulTransType,                // Frame/block synchronization (BS+FS)
                                                         //    This determines how the DMA request is serviced in a 
                                                         //    synchronized transfer
               unsigned char ulSynchroControl            // Channel synchronization control (all 7 bits)
               );
void dmaConfigTransfer(unsigned char ulChan,             // Channel to configure 
                       unsigned int  ulCen,              // Number of elements within a frame (unsigned) to transfer
                       unsigned int  ulCfn,              // Number of frames within the block to be transferred
                       unsigned int  ulCssa,             // 32 bits of the source start address
                       unsigned int  ulCdsa,             // 32 bits of the destination start address
                       unsigned int  ulCsel,             // Channel Source Element Index (Signed)
                       unsigned int  ulCsfl,             // Channel Source Frame Index (Signed) or 16-bit Packet size
                       unsigned int  ulCdel,             // Channel Destination Element Index (Signed)
                       unsigned int  ulCdfl              // Channel Destination Frame Index (Signed) or 16-bit Packet size
                       );

void dmaSetChannelLink(unsigned char ulChan,             // Channel to configure 
                       unsigned char ulNextchId ,        // Channel link target
                       unsigned char ulEnableLink        // Enable/Disable link          
                       );
void dmaSetSourceAddress(unsigned char ulChan,           // Channel to configure 
                         unsigned int  ulCssa            // 32 bits of the source start address
                         );
void dmaSetDestinationAddress(unsigned char ulChan,      // Channel to configure 
                              unsigned int  ulCdsa       // 32 bits of the destination start address
                              );
void dmaEnableChannel(unsigned char ulChan);
void dmaDisableChannel(unsigned char ulChan);
void dmaEnableLink(unsigned char ulChan);
void dmaDisableLink(unsigned char ulChan);














// Define the channels
#define CHAN0      0
#define CHAN1      1
#define CHAN2      2
#define CHAN3      3
#define CHAN4      4
#define CHAN5      5
#define CHAN6      6
#define CHAN7      7
#define CHAN8      8
#define CHAN9      9
#define CHAN0      0
#define CHAN11    11
#define CHAN12    12
#define CHAN13    13
#define CHAN14    14
#define CHAN15    15
#define CHAN16    16
#define CHAN17    17
#define CHAN18    18
#define CHAN19    19
#define CHAN20    20
#define CHAN21    21
#define CHAN22    22
#define CHAN23    23
#define CHAN24    24
#define CHAN25    25
#define CHAN26    26
#define CHAN27    27
#define CHAN28    28
#define CHAN29    29
#define CHAN30    30
#define CHAN31    31


// CCR defines
#define LOW_WR_PRIORITY               0
#define HIGH_WR_PRIORITY              1
#define EN_BUFF                       0 
#define DIS_BUFF                      1 
#define TRG_DEST                      0 
#define TRG_SRC                       1 
#define NO_PREFETCH                   0
#define PREFETCH                      1
#define DIS_SUPER                     0
#define EN_SUPER                      1
#define DIS_SECURE                    0
#define EN_SECURE                     1
#define EN_TRANS_COPY                 1
#define DIS_TRANS_COPY                0
#define DIS_CONST_FILL                0 
#define EN_CONST_FILL                 1 
#define DST_AMODE_CONST               0 
#define DST_AMODE_POST_INC            1 
#define DST_AMODE_SINGLE_INDEX        2 
#define DST_AMODE_DOUBLE_INDEX        3 
#define SRC_AMODE_CONST               0 
#define SRC_AMODE_POST_INC            1 
#define SRC_AMODE_SINGLE_INDEX        2 
#define SRC_AMODE_DOUBLE_INDEX        3 
#define DIS_SUSPEND                   0 
#define EN_SUSPEND                    1
#define EN_CHANNEL                    1  
#define DIS_CHANNEL                   0
#define LOW_RD_PRIORITY               0
#define HIGH_RD_PRIORITY              1
#define TRANS_ELEM                    0  // BS=0 FS=0
#define TRANS_FRAME                   1  // BS=0 FS=1
#define TRANS_BLOCK                   2  // BS=1 FS=0
#define TRANS_PACKET                  3  // BS=1 FS=1

// CSDP defines
#define SRC_LITTLE_ENDIAN             0
#define SRC_BIG_ENDIAN                1 
#define SRC_ENDIAN_ADAPT              0
#define SRC_ENDIAN_LOCK               1
#define DST_LITTLE_ENDIAN             0
#define DST_BIG_ENDIAN                1 
#define DST_ENDIAN_ADAPT              0
#define DST_ENDIAN_LOCK               1
#define WRITE_NON_POSTED              0
#define WRITE_POSTED                  1
#define WRITE_LAST_POSTED             2
#define DST_NO_BURST                  0  
#define DST_MODE1_BURST               1
#define DST_MODE2_BURST               2
#define DST_MODE3_BURST               3
#define DST_UNPACKED                  0
#define DST_PACKED                    1
#define SRC_NO_BURST                  0  
#define SRC_MODE1_BURST               1
#define SRC_MODE2_BURST               2
#define SRC_MODE3_BURST               3
#define SRC_UNPACKED                  0
#define SRC_PACKED                    1
#define SCALAR_8BITS                  0
#define SCALAR_16BITS                 1
#define SCALAR_32BITS                 2

// CLNK_CTRL defines
#define DIS_CHAN_LINK                 0
#define EN_CHAN_LINK                  1

// DMA requests
#define DMA_SYS_DMA_REQ0              1        //  External DMA request 0 (system expansion)
#define DMA_SYS_DMA_REQ1              2        //  External DMA request 1 (system expansion)
#define DMA_GPMC_DMA                  3        //  GPMC request from prefetch engine
#define DMA_DSS_LINE_TRIGGER          5        //  Display subsystemframe update request
#define DMA_SYS_DMA_REQ2              6        //  External DMA request 2 (system expansion)
#define DMA_AES_1_DMA_TX              8        //  AES crypto-acceleratortransmit request
#define DMA_AES_1_DMA_RX              9        //  AES crypto-acceleratorreceive request
#define DMA_DES_1_DMA_TX             10        //  DES/3DES crypto-acceleratortransmit request
#define DMA_DES_1_DMA_RX             11        //  DES/3DES crypto-acceleratorreceive request
#define DMA_SHA2MD5_DMA_RX           12        //  SHA2-/MD5 crypto-acceleratorreceive request
#define DMA_SPI3_DMA_TX0             14        //  McSPI module 3transmit request channel 0
#define DMA_SPI3_DMA_RX0             15        //  McSPI module 3receive request channel 0
#define DMA_MCBSP3_DMA_TX            16        //  MCBSP module 3transmit request
#define DMA_MCBSP3_DMA_RX            17        //  MCBSP module 3receive request
#define DMA_MCBSP4_DMA_TX            18        //  MCBSP module 4transmit request
#define DMA_MCBSP4_DMA_RX            19        //  MCBSP module 4receive request
#define DMA_MCBSP5_DMA_TX            20        //  MCBSP module 5transmit request
#define DMA_MCBSP5_DMA_RX            21        //  MCBSP module 5receive request
#define DMA_SPI3_DMA_TX1             22        //  McSPI module 3transmit request channel 1
#define DMA_SPI3_DMA_RX1             23        //  McSPI module 3receive request channel 1
#define DMA_I2C3_DMA_TX              24        //  I2C module 3transmit request
#define DMA_I2C3_DMA_RX              25        //  I2C module 3receive request
#define DMA_I2C1_DMA_TX              26        //  I2C module 1transmit request
#define DMA_I2C1_DMA_RX              27        //  I2C module 1receive request
#define DMA_I2C2_DMA_TX              28        //  I2C module 2transmit request
#define DMA_I2C2_DMA_RX              29        //  I2C module 2receive request
#define DMA_MCBSP1_DMA_TX            30        //  MCBSP module 1transmit request
#define DMA_MCBSP1_DMA_RX            31        //  MCBSP module 1receive request
#define DMA_MCBSP2_DMA_TX            32        //  MCBSP module 2transmit request
#define DMA_MCBSP2_DMA_RX            33        //  MCBSP module 2receive request
#define DMA_SPI1_DMA_TX0             34        //  McSPI module 1transmit request channel 0
#define DMA_SPI1_DMA_RX0             35        //  McSPI module 1receive request channel 0
#define DMA_SPI1_DMA_TX1             36        //  McSPI module 1transmit request channel 1
#define DMA_SPI1_DMA_RX1             37        //  McSPI module 1receive request channel 1
#define DMA_SPI1_DMA_TX2             38        //  McSPI module 1transmit request channel 2
#define DMA_SPI1_DMA_RX2             39        //  McSPI module 1receive request channel 2
#define DMA_SPI1_DMA_TX3             40        //  McSPI module 1transmit request channel 3
#define DMA_SPI1_DMA_RX3             41        //  McSPI module 1receive request channel 3
#define DMA_SPI2_DMA_TX0             42        //  McSPI module 2transmit request channel 0
#define DMA_SPI2_DMA_RX0             43        //  McSPI module 2receive request channel 0
#define DMA_SPI2_DMA_TX1             44        //  McSPI module 2transmit request channel 1
#define DMA_SPI2_DMA_RX1             45        //  McSPI module 2receive request channel 1
#define DMA_MMC2_DMA_TX              46        //  MMC/SD2 transmit request
#define DMA_MMC2_DMA_RX              47        //  MMC/SD2 receive request
#define DMA_UART1_DMA_TX             48        //  UART module 1transmit request
#define DMA_UART1_DMA_RX             49        //  UART module 1receive request
#define DMA_UART2_DMA_TX             50        //  UART module 2transmit request
#define DMA_UART2_DMA_RX             51        //  UART module 2receive request
#define DMA_UART3_DMA_TX             52        //  UART module 3transmit request
#define DMA_UART3_DMA_RX             53        //  UART module 3receive request
#define DMA_MMC1_DMA_TX              60        //  MMC/SD1 transmit request
#define DMA_MMC1_DMA_RX              61        //  MMC/SD1 receive request
#define DMA_MS_DMA                   62        //  MS-PRO request
#define DMA_SYS_DMA_REQ3             63        //  External DMA request 3 (system expansion)
#define DMA_AES_2_DMA_TX             64        //  AES crypto-accelerator 2transmit request
#define DMA_AES_2_DMA_RX             65        //  AES crypto-accelerator 2receive request
#define DMA_DES_2_DMA_TX             66        //  DES/3DES crypto-accelerator 2transmit request
#define DMA_DES_2_DMA_RX             67        //  DES/3DES crypto-accelerator 2receive request
#define DMA_SHA1MD5_DMA_RX           68        //  SHA1/MD5 crypto-accelerator 2receive request
#define DMA_SPI4_DMA_TX0             69        //  McSPI module 4transmit request channel 0
#define DMA_SPI4_DMA_RX0             70        //  McSPI module 4receive request channel 0
#define DMA_MMC3_DMA_TX              76        //  MMC/SD3 transmit request
#define DMA_MMC3_DMA_RX              77        //  MMC/SD3 receive request

#endif
