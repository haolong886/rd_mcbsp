/* 

Register definitions for OMAP & AM CONTROL Module.

Version x.xx - Under construction 

*/

#ifndef _RD_CTL_REG_H
#define _RD_CTL_REG_H

// Base addresse
#define INTERFACE_BASE                              (0x48002000)
#define PADCONFS_BASE                               (0x48002030)
#define GENERAL_BASE                                (0x48002270)
#define MEM_WKUP_BASE                               (0x48002600)
#define PADCONFS_WKUP_BASE                          (0x48002A00)
#define GENERAL_WKUP_BASE                           (0x48002A60)

// INTERFACE registers
#define CONTROL_REVISION                            (INTERFACE_BASE + 0x00000000)
#define CONTROL_SYSCONFIG                           (INTERFACE_BASE + 0x00000010)

// PADCONFS registers
#define CONTROL_PADCONF_SDRC_D0                     (0x00000000) //PADCONFS_BASE
#define CONTROL_PADCONF_SDRC_D2                     (0x00000004)
#define CONTROL_PADCONF_SDRC_D4                     (0x00000008)
#define CONTROL_PADCONF_SDRC_D6                     (0x0000000C)
#define CONTROL_PADCONF_SDRC_D8                     (0x00000010)
#define CONTROL_PADCONF_SDRC_D10                    (0x00000014)
#define CONTROL_PADCONF_SDRC_D12                    (0x00000018)
#define CONTROL_PADCONF_SDRC_D14                    (0x0000001C)
#define CONTROL_PADCONF_SDRC_D16                    (0x00000020)
#define CONTROL_PADCONF_SDRC_D18                    (0x00000024)
#define CONTROL_PADCONF_SDRC_D20                    (0x00000028)
#define CONTROL_PADCONF_SDRC_D22                    (0x0000002C)
#define CONTROL_PADCONF_SDRC_D24                    (0x00000030)
#define CONTROL_PADCONF_SDRC_D26                    (0x00000034)
#define CONTROL_PADCONF_SDRC_D28                    (0x00000038)
#define CONTROL_PADCONF_SDRC_D30                    (0x0000003C)
#define CONTROL_PADCONF_SDRC_CLK                    (0x00000040)
#define CONTROL_PADCONF_SDRC_CKE1                   (0x00000230)
#define CONTROL_PADCONF_SDRC_DQS1                   (0x00000044)
#define CONTROL_PADCONF_SDRC_DQS3                   (0x00000048)
#define CONTROL_PADCONF_GPMC_A2                     (0x0000004C)
#define CONTROL_PADCONF_GPMC_A4                     (0x00000050)
#define CONTROL_PADCONF_GPMC_A6                     (0x00000054)
#define CONTROL_PADCONF_GPMC_A8                     (0x00000058)
#define CONTROL_PADCONF_GPMC_A10                    (0x0000005C)
#define CONTROL_PADCONF_GPMC_D1                     (0x00000060)
#define CONTROL_PADCONF_GPMC_D3                     (0x00000064)
#define CONTROL_PADCONF_GPMC_D5                     (0x00000068)
#define CONTROL_PADCONF_GPMC_D7                     (0x0000006C)
#define CONTROL_PADCONF_GPMC_D9                     (0x00000070)
#define CONTROL_PADCONF_GPMC_D11                    (0x00000074)
#define CONTROL_PADCONF_GPMC_D13                    (0x00000078)
#define CONTROL_PADCONF_GPMC_D15                    (0x0000007C)
#define CONTROL_PADCONF_GPMC_NCS1                   (0x00000080)
#define CONTROL_PADCONF_GPMC_NCS3                   (0x00000084)
#define CONTROL_PADCONF_GPMC_NCS5                   (0x00000088)
#define CONTROL_PADCONF_GPMC_NCS7                   (0x0000008C)
#define CONTROL_PADCONF_GPMC_NADV_ALE               (0x00000090)
#define CONTROL_PADCONF_GPMC_NWE                    (0x00000094)
#define CONTROL_PADCONF_GPMC_NBE1                   (0x00000098)
#define CONTROL_PADCONF_GPMC_WAIT0                  (0x0000009C)
#define CONTROL_PADCONF_GPMC_WAIT2                  (0x000000A0)
#define CONTROL_PADCONF_DSS_PCLK                    (0x000000A4)
#define CONTROL_PADCONF_DSS_VSYNC                   (0x000000A8)
#define CONTROL_PADCONF_DSS_DATA0                   (0x000000AC)
#define CONTROL_PADCONF_DSS_DATA2                   (0x000000B0)
#define CONTROL_PADCONF_DSS_DATA4                   (0x000000B4)
#define CONTROL_PADCONF_DSS_DATA6                   (0x000000B8)
#define CONTROL_PADCONF_DSS_DATA8                   (0x000000BC)
#define CONTROL_PADCONF_DSS_DATA10                  (0x000000C0)
#define CONTROL_PADCONF_DSS_DATA12                  (0x000000C4)
#define CONTROL_PADCONF_DSS_DATA14                  (0x000000C8)
#define CONTROL_PADCONF_DSS_DATA16                  (0x000000CC)
#define CONTROL_PADCONF_DSS_DATA18                  (0x000000D0)
#define CONTROL_PADCONF_DSS_DATA20                  (0x000000D4)
#define CONTROL_PADCONF_DSS_DATA22                  (0x000000D8)
#define CONTROL_PADCONF_MCBSP2_FSX                  (0x0000010C)
#define CONTROL_PADCONF_MCBSP2_DR                   (0x00000110)
#define CONTROL_PADCONF_MMC1_CLK                    (0x00000114)
#define CONTROL_PADCONF_MMC1_DAT0                   (0x00000118)
#define CONTROL_PADCONF_MMC1_DAT2                   (0x0000011C)
#define CONTROL_PADCONF_MMC1_DAT4                   (0x00000120)
#define CONTROL_PADCONF_MMC1_DAT6                   (0x00000124)
#define CONTROL_PADCONF_MMC2_CLK                    (0x00000128)
#define CONTROL_PADCONF_MMC2_DAT0                   (0x0000012C)
#define CONTROL_PADCONF_MMC2_DAT2                   (0x00000130)
#define CONTROL_PADCONF_MMC2_DAT4                   (0x00000134)
#define CONTROL_PADCONF_MMC2_DAT6                   (0x00000138)
#define CONTROL_PADCONF_MCBSP3_DX                   (0x0000013C)
#define CONTROL_PADCONF_MCBSP3_CLKX                 (0x00000140)
#define CONTROL_PADCONF_UART2_CTS                   (0x00000144)
#define CONTROL_PADCONF_UART2_TX                    (0x00000148)
#define CONTROL_PADCONF_UART1_TX                    (0x0000014C)
#define CONTROL_PADCONF_UART1_CTS                   (0x00000150)
#define CONTROL_PADCONF_MCBSP4_CLKX                 (0x00000154)
#define CONTROL_PADCONF_MCBSP4_DX                   (0x00000158)
#define CONTROL_PADCONF_MCBSP1_CLKR                 (0x0000015C)
#define CONTROL_PADCONF_MCBSP1_DX                   (0x00000160)
#define CONTROL_PADCONF_MCBSP_CLKS                  (0x00000164)
#define CONTROL_PADCONF_MCBSP1_CLKX                 (0x00000168)
#define CONTROL_PADCONF_UART3_RTS_SD                (0x0000016C)
#define CONTROL_PADCONF_UART3_TX_IRTX               (0x00000170)
#define CONTROL_PADCONF_I2C1_SCL                    (0x00000188)
#define CONTROL_PADCONF_I2C1_SDA                    (0x0000018C)
#define CONTROL_PADCONF_I2C2_SDA                    (0x00000190)
#define CONTROL_PADCONF_I2C3_SDA                    (0x00000194)
#define CONTROL_PADCONF_MCSPI1_CLK                  (0x00000198)
#define CONTROL_PADCONF_MCSPI1_SOMI                 (0x0000019C)
#define CONTROL_PADCONF_MCSPI1_CS1                  (0x000001A0)
#define CONTROL_PADCONF_MCSPI1_CS3                  (0x000001A4)
#define CONTROL_PADCONF_MCSPI2_SIMO                 (0x000001A8)
#define CONTROL_PADCONF_MCSPI2_CS0                  (0x000001AC)
#define CONTROL_PADCONF_SYS_NIRQ                    (0x000001B0)
#define CONTROL_PADCONF_ETK_CLK                     (0x000005D8)
#define CONTROL_PADCONF_ETK_D0                      (0x000005DC)
#define CONTROL_PADCONF_ETK_D2                      (0x000005E0)
#define CONTROL_PADCONF_ETK_D4                      (0x000005E4)
#define CONTROL_PADCONF_ETK_D6                      (0x000005E8)
#define CONTROL_PADCONF_ETK_D8                      (0x000005EC)
#define CONTROL_PADCONF_ETK_D10                     (0x000005F0)
#define CONTROL_PADCONF_ETK_D12                     (0x000005F4)
#define CONTROL_PADCONF_ETK_D14                     (0x000005F8)
#define CONTROL_PADCONF_CCDC_PCLK                   (0x000001B4)
#define CONTROL_PADCONF_CCDC_HD                     (0x000001B8)
#define CONTROL_PADCONF_CCDC_WEN                    (0x000001BC)
#define CONTROL_PADCONF_CCDC_DATA1                  (0x000001C0)
#define CONTROL_PADCONF_CCDC_DATA3                  (0x000001C4)
#define CONTROL_PADCONF_CCDC_DATA5                  (0x000001C8)
#define CONTROL_PADCONF_CCDC_DATA7                  (0x000001CC)
#define CONTROL_PADCONF_RMII_MDIO_CLK               (0x000001D0)
#define CONTROL_PADCONF_RMII_RXD1                   (0x000001D4)
#define CONTROL_PADCONF_RMII_RXER                   (0x000001D8)
#define CONTROL_PADCONF_RMII_TXD1                   (0x000001DC)
#define CONTROL_PADCONF_RMII_50MHZ_CLK              (0x000001E0)
#define CONTROL_PADCONF_HECC1_TXD                   (0x000001E4)
#define CONTROL_PADCONF_SYS_BOOT7                   (0x000001E8)
#define CONTROL_PADCONF_SDRC_DQS1N                  (0x000001EC)
#define CONTROL_PADCONF_SDRC_DQS3N                  (0x000001F0)
#define CONTROL_PADCONF_SDRC_STRBEN_DLY1            (0x000001F4)
#define CONTROL_PADCONF_SDRC_CKE                    (0x00000230)

// General registers
//#define CONTROL_PADCONF_OFF                         (GENERAL_BASE + 0x00000000)
#define CONTROL_DEVCONF0                            (0x00000004)
//#define CONTROL_MEM_DFTRW0                          (GENERAL_BASE + 0x00000008)
//#define CONTROL_MEM_DFTRW1                          (GENERAL_BASE + 0x0000000C)
//#define CONTROL_MSUSPENDMUX_0                       (GENERAL_BASE + 0x00000020)
//#define CONTROL_MSUSPENDMUX_1                       (GENERAL_BASE + 0x00000024)
//#define CONTROL_MSUSPENDMUX_2                       (GENERAL_BASE + 0x00000028)
//#define CONTROL_MSUSPENDMUX_3                       (GENERAL_BASE + 0x0000002C)
//#define CONTROL_MSUSPENDMUX_4                       (GENERAL_BASE + 0x00000030)
//#define CONTROL_MSUSPENDMUX_5                       (GENERAL_BASE + 0x00000034)
//#define CONTROL_MSUSPENDMUX_6                       (GENERAL_BASE + 0x00000038)
//#define CONTROL_SEC_CTRL                            (GENERAL_BASE + 0x00000040)
#define CONTROL_DEVCONF1                            (0x00000068)
//#define CONTROL_SEC_STATUS                          (GENERAL_BASE + 0x00000070)
//#define CONTROL_SEC_ERR_STATUS                      (GENERAL_BASE + 0x00000074)
//#define CONTROL_SEC_ERR_STATUS_DEBUG                (GENERAL_BASE + 0x00000078)
//#define CONTROL_STATUS                              (GENERAL_BASE + 0x00000080)   
//#define CONTROL_GENERAL_PURPOSE_STATUS              (GENERAL_BASE + 0x00000084)   
//#define CONTROL_RPUB_KEY_H_0                        (GENERAL_BASE + 0x00000090)   
//#define CONTROL_RPUB_KEY_H_1                        (GENERAL_BASE + 0x00000094)   
//#define CONTROL_RPUB_KEY_H_2                        (GENERAL_BASE + 0x00000098)   
//#define CONTROL_RPUB_KEY_H_3                        (GENERAL_BASE + 0x0000009C)   
//#define CONTROL_RPUB_KEY_H_4                        (GENERAL_BASE + 0x000000A0)   
//#define CONTROL_RAND_KEY_0                          (GENERAL_BASE + 0x000000A8)   
//#define CONTROL_RAND_KEY_1                          (GENERAL_BASE + 0x000000AC)   
//#define CONTROL_RAND_KEY_2                          (GENERAL_BASE + 0x000000B0)   
//#define CONTROL_RAND_KEY_3                          (GENERAL_BASE + 0x000000B4)   
//#define CONTROL_CUST_KEY_0                          (GENERAL_BASE + 0x000000B8)   
//#define CONTROL_CUST_KEY_1                          (GENERAL_BASE + 0x000000BC)   
//#define CONTROL_CUST_KEY_2                          (GENERAL_BASE + 0x000000C0)   
//#define CONTROL_CUST_KEY_3                          (GENERAL_BASE + 0x000000C4)   
//#define CONTROL_USB_CONF_0                          (GENERAL_BASE + 0x00000100)   
//#define CONTROL_USB_CONF_1                          (GENERAL_BASE + 0x00000104)   
//#define CONTROL_FUSE_EMAC_LSB                       (GENERAL_BASE + 0x00000110)   
//#define CONTROL_FUSE_EMAC_MSB                       (GENERAL_BASE + 0x00000114)   
//#define CONTROL_FUSE_SR                             (GENERAL_BASE + 0x00000130)   
//#define CONTROL_CEK_0                               (GENERAL_BASE + 0x00000134)   
//#define CONTROL_CEK_1                               (GENERAL_BASE + 0x00000138)   
//#define CONTROL_CEK_2                               (GENERAL_BASE + 0x0000013C)   
//#define CONTROL_CEK_3                               (GENERAL_BASE + 0x00000140)   
//#define CONTROL_MSV_0                               (GENERAL_BASE + 0x00000144)   
//#define CONTROL_CEK_BCH_0                           (GENERAL_BASE + 0x00000148)   
//#define CONTROL_CEK_BCH_1                           (GENERAL_BASE + 0x0000014C)   
//#define CONTROL_CEK_BCH_2                           (GENERAL_BASE + 0x00000150)   
//#define CONTROL_CEK_BCH_3                           (GENERAL_BASE + 0x00000154)   
//#define CONTROL_CEK_BCH_4                           (GENERAL_BASE + 0x00000158)   
//#define CONTROL_MSV_BCH_0                           (GENERAL_BASE + 0x0000015C)   
//#define CONTROL_MSV_BCH_1                           (GENERAL_BASE + 0x00000160)   
//#define CONTROL_SWRV_0                              (GENERAL_BASE + 0x00000164)   
//#define CONTROL_SWRV_1                              (GENERAL_BASE + 0x00000168)   
//#define CONTROL_SWRV_2                              (GENERAL_BASE + 0x0000016C)   
//#define CONTROL_SWRV_3                              (GENERAL_BASE + 0x00000170)   
//#define CONTROL_SWRV_4                              (GENERAL_BASE + 0x00000174)   
//#define CONTROL_DEBOBS_0                            (GENERAL_BASE + 0x000001B0)   
//#define CONTROL_DEBOBS_1                            (GENERAL_BASE + 0x000001B4)   
//#define CONTROL_DEBOBS_2                            (GENERAL_BASE + 0x000001B8)   
//#define CONTROL_DEBOBS_3                            (GENERAL_BASE + 0x000001BC)   
//#define CONTROL_DEBOBS_4                            (GENERAL_BASE + 0x000001C0)   
//#define CONTROL_DEBOBS_5                            (GENERAL_BASE + 0x000001C4)   
//#define CONTROL_DEBOBS_6                            (GENERAL_BASE + 0x000001C8)   
//#define CONTROL_DEBOBS_7                            (GENERAL_BASE + 0x000001CC)   
//#define CONTROL_DEBOBS_8                            (GENERAL_BASE + 0x000001D0)   
//#define CONTROL_WKUP_CTRL                           (GENERAL_BASE + 0x00000A5C)   
//#define CONTROL_DSS_DPLL_SPREADING                  (GENERAL_BASE + 0x000001E0)   
//#define CONTROL_CORE_DPLL_SPREADING                 (GENERAL_BASE + 0x000001E4)   
//#define CONTROL_PER_DPLL_SPREADING                  (GENERAL_BASE + 0x000001E8)   
//#define CONTROL_USBHOST_DPLL_SPREADING              (GENERAL_BASE + 0x000001EC)   
//#define CONTROL_DPF_OCM_RAM_FW_ADDR_MATCH           (GENERAL_BASE + 0x00000228)   
//#define CONTROL_DPF_OCM_RAM_FW_REQINFO              (GENERAL_BASE + 0x0000022C)   
//#define CONTROL_DPF_OCM_RAM_FW_WR                   (GENERAL_BASE + 0x00000230)   
//#define CONTROL_DPF_REGION4_GPMC_FW_ADDR_MATCH      (GENERAL_BASE + 0x00000234)   
//#define CONTROL_DPF_REGION4_GPMC_FW_REQINFO         (GENERAL_BASE + 0x00000238)   
//#define CONTROL_DPF_REGION4_GPMC_FW_WR              (GENERAL_BASE + 0x0000023C)   
//#define CONTROL_APE_FW_DEFAULT_SECURE_LOCK          (GENERAL_BASE + 0x0000024C)   
//#define CONTROL_OCMROM_SECURE_DEBUG                 (GENERAL_BASE + 0x00000250)   
//#define CONTROL_EXT_SEC_CONTROL                     (GENERAL_BASE + 0x00000264)   
//#define CONTROL_DEVCONF2                            (GENERAL_BASE + 0x00000310)   
//#define CONTROL_DEVCONF3                            (GENERAL_BASE + 0x00000314)   
//#define CONTROL_CBA_PRIORITY                        (GENERAL_BASE + 0x0000031C)   
//#define CONTROL_LVL_INTR_CLEAR                      (GENERAL_BASE + 0x00000320)   
//#define CONTROL_IP_SW_RESET                         (GENERAL_BASE + 0x00000324)   
//#define CONTROL_IPSS_CLK_CTRL                       (GENERAL_BASE + 0x00000328)   
//#define CONTROL_IDCODE                              (GENERAL_BASE + 0x00307F94)   

// MEM_WKUP registers
//#define CONTROL_SAVE_RESTORE_MEM                    (MEM_WKUP_BASE + 0x00000000)

// PADCONFS_WKUP registers
//#define CONTROL_PADCONF_I2C4_SCL                    (PADCONFS_WKUP_BASE + 0x00000000)   
//#define CONTROL_PADCONF_SYS_32K                     (PADCONFS_WKUP_BASE + 0x00000004)   
//#define CONTROL_PADCONF_SYS_NRESWARM                (PADCONFS_WKUP_BASE + 0x00000008)   
//#define CONTROL_PADCONF_SYS_BOOT1                   (PADCONFS_WKUP_BASE + 0x0000000C)   
//#define CONTROL_PADCONF_SYS_BOOT3                   (PADCONFS_WKUP_BASE + 0x00000010)   
//#define CONTROL_PADCONF_SYS_BOOT5                   (PADCONFS_WKUP_BASE + 0x00000014)   
//#define CONTROL_PADCONF_SYS_OFF_MODE                (PADCONFS_WKUP_BASE + 0x00000018)   
//#define CONTROL_PADCONF_JTAG_NTRST                  (PADCONFS_WKUP_BASE + 0x0000001C)   
//#define CONTROL_PADCONF_JTAG_TMS_TMSC               (PADCONFS_WKUP_BASE + 0x00000020)   
//#define CONTROL_PADCONF_JTAG_EMU0                   (PADCONFS_WKUP_BASE + 0x00000024)   
//#define CONTROL_PADCONF_JTAG_RTCK                   (PADCONFS_WKUP_BASE + 0x0000004C)   
//#define CONTROL_PADCONF_JTAG_TDO                    (PADCONFS_WKUP_BASE + 0x00000050)   

// GENERAL_WKUP registers
//#define CONTROL_SEC_TAP                             (CONTROL_BASE + 0x00000000)   
//#define CONTROL_SEC_EMU                             (CONTROL_BASE + 0x00000004)   
//#define CONTROL_WKUP_DEBOBS_0                       (CONTROL_BASE + 0x00000008)   
//#define CONTROL_WKUP_DEBOBS_1                       (CONTROL_BASE + 0x0000000C)   
//#define CONTROL_WKUP_DEBOBS_2                       (CONTROL_BASE + 0x00000010)   
//#define CONTROL_WKUP_DEBOBS_3                       (CONTROL_BASE + 0x00000014)   
//#define CONTROL_WKUP_DEBOBS_4                       (CONTROL_BASE + 0x00000018)   
//#define CONTROL_SEC_DAP                             (CONTROL_BASE + 0x0000001C)   


// CONTROL_DEVCONF0 Bits
#define CONTROL_DEVCONF0_MCBSP2_CLKS     (0x40)
#define CONTROL_DEVCONF0_MCBSP1_FSR      (0x10)
#define CONTROL_DEVCONF0_MCBSP1_CLKR     (0x8)
#define CONTROL_DEVCONF0_MCBSP1_CLKS     (0x4)
#define CONTROL_DEVCONF0_SENSDMAREQ1     (0x2)
#define CONTROL_DEVCONF0_SENSDMAREQ0     (0x1) 


// CONTROL_DEVCONF1 Bits
#define CONTROL_DEVCONF1_TVACEN         (0x800)
#define CONTROL_DEVCONF1_MPUFORCEWRNP   (0x200)
#define CONTROL_DEVCONF1_SENSDMAREQ3    (0x100)
#define CONTROL_DEVCONF1_SENSDMAREQ2     (0x80)
#define CONTROL_DEVCONF1_MMCSDIO2ADPCLKISEL (0x40)
#define CONTROL_DEVCONF1_MCBSP5_CLKS     (0x10)
#define CONTROL_DEVCONF1_MCBSP4_CLKS      (0x4)
#define CONTROL_DEVCONF1_MCBSP3_CLKS      (0x1) 







#define PULL_ENABLE_MASK                  (0x8)
#define PULL_UP_MASK                      (0x10)

#define MODE0                 (00)
#define MODE1                 (01)
#define MODE2                 (02)
#define MODE3                 (03)
#define MODE4                 (04)
#define MODE5                 (05)
#define MODE6                 (06)
#define MODE7                 (07)
#define MODE_SAFE             MODE7

#define PUPD_EN               (01)
#define PUPD_DIS              (00)

#define PULL_UP               (01)
#define PULL_DOWN             (00)
#define INPUT_EN              (02)
#define INPUT_DIS             (00)

#endif
