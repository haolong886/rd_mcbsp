/* 

Register definitions for AM35x PRCM module

Version 0.01

*/
#ifndef _RD_PRCM_REG_H
#define _RD_PRCM_REG_H

// OCP_System_Reg_CM Register Mapping
#define CM_REVISION                0x48004800
#define CM_SYSCONFIG               0x48004810


// MPU_CM Register Mapping
#define CM_CLKEN_PLL_MPU           0x48004904
#define CM_IDLEST_MPU              0x48004920
#define CM_IDLEST_PLL_MPU          0x48004924
#define CM_AUTOIDLE_PLL_MPU        0x48004934
#define CM_CLKSEL1_PLL_MPU         0x48004940
#define CM_CLKSEL2_PLL_MPU         0x48004944
#define CM_CLKSTCTRL_MPU           0x48004948
#define CM_CLKSTST_MPU             0x4800494C

// CORE_CM Register Mapping
#define CM_FCLKEN1_CORE            0x48004A00
#define CM_FCLKEN3_CORE            0x48004A08
#define CM_ICLKEN1_CORE            0x48004A10
#define CM_ICLKEN2_CORE            0x48004A14
#define CM_ICLKEN3_CORE            0x48004A18
#define CM_IDLEST1_CORE            0x48004A20
#define CM_IDLEST2_CORE            0x48004A24
#define CM_IDLEST3_CORE            0x48004A28
#define CM_AUTOIDLE1_CORE          0x48004A30
#define CM_AUTOIDLE2_CORE          0x48004A34
#define CM_AUTOIDLE3_CORE          0x48004A38
#define CM_CLKSEL_CORE             0x48004A40
#define CM_CLKSTCTRL_CORE          0x48004A48
#define CM_CLKSTST_CORE            0x48004A4C

// SGX_CM Register Mapping
#define CM_FCLKEN_SGX              0x48004B00
#define CM_ICLKEN_SGX              0x48004B10
#define CM_IDLEST_SGX              0x48004B20
#define CM_CLKSEL_SGX              0x48004B40
#define CM_SLEEPDEP_SGX            0x48004B44
#define CM_CLKSTCTRL_SGX           0x48004B48
#define CM_CLKSTST_SGX             0x48004B4C

// WKUP_CM Register Mapping
#define CM_FCLKEN_WKUP             0x48004C00
#define CM_ICLKEN_WKUP             0x48004C10
#define CM_IDLEST_WKUP             0x48004C20
#define CM_AUTOIDLE_WKUP           0x48004C30
#define CM_CLKSEL_WKUP             0x48004C40

// Clock_Control_Reg_CM Register Mapping
#define CM_CLKEN_PLL               0x48004D00
#define CM_CLKEN2_PLL              0x48004D04
#define CM_IDLEST_CKGEN            0x48004D20
#define CM_IDLEST2_CKGEN           0x48004D24

// Clock_Control_Reg_CM Register Mapping
#define CM_AUTOIDLE_PLL            0x48004D30
#define CM_AUTOIDLE2_PLL           0x48004D34
#define CM_CLKSEL1_PLL             0x48004D40
#define CM_CLKSEL2_PLL             0x48004D44
#define CM_CLKSEL3_PLL             0x48004D48
#define CM_CLKSEL4_PLL             0x48004D4C
#define CM_CLKSEL5_PLL             0x48004D50
#define CM_CLKOUT_CTRL             0x48004D70

// DSS_CM Register Mapping
#define CM_FCLKEN_DSS              0x48004E00
#define CM_ICLKEN_DSS              0x48004E10
#define CM_IDLEST_DSS              0x48004E20
#define CM_AUTOIDLE_DSS            0x48004E30
#define CM_CLKSEL_DSS              0x48004E40
#define CM_SLEEPDEP_DSS            0x48004E44
#define CM_CLKSTCTRL_DSS           0x48004E48
#define CM_CLKSTST_DSS             0x48004E4C

//PER_CM Register Mapping
#define CM_FCLKEN_PER              0x48005000
#define CM_ICLKEN_PER              0x48005010
#define CM_IDLEST_PER              0x48005020
#define CM_AUTOIDLE_PER            0x48005030
#define CM_CLKSEL_PER              0x48005040
#define CM_SLEEPDEP_PER            0x48005044
#define CM_CLKSTCTRL_PER           0x48005048
#define CM_CLKSTST_PER             0x4800504C

// EMU_CM Register Mapping
#define CM_CLKSEL1_EMU             0x48005140
#define CM_CLKSTCTRL_EMU           0x48005148
#define CM_CLKSTST_EMU             0x4800514C
#define CM_CLKSEL2_EMU             0x48005150
#define CM_CLKSEL3_EMU             0x48005154

// Global_Reg_CM Register Mapping
#define CM_POLCTRL                 0x4800529C

// NEON_CM Register Mapping
#define CM_IDLEST_NEON             0x48005320
#define CM_CLKSTCTRL_NEON          0x48005348

// USBHOST_CM Register Mapping
#define CM_FCLKEN_USBHOST          0x48005400
#define CM_ICLKEN_USBHOST          0x48005410
#define CM_IDLEST_USBHOST          0x48005420
#define CM_AUTOIDLE_USBHOST        0x48005430
#define CM_SLEEPDEP_USBHOST        0x48005444
#define CM_CLKSTCTRL_USBHOST       0x48005448
#define CM_CLKSTST_USBHOST         0x4800544C




/////////////////////////////////////////////////
//
// Register bit definitions
//
//


// CM_CLKSEL1_PLL bit masks
#define CM_CLKSEL1_PLL_CORE_DPLL_CLKOUT_DIV_0 (0xF8000000) 
#define CM_CLKSEL1_PLL_CORE_DPLL_MULT_0        (0x3FF0000) 
#define CM_CLKSEL1_PLL_CORE_DPLL_DIV_0            (0x7F00) 
#define CM_CLKSEL1_PLL_SOURCE_96M                   (0x40)
#define CM_CLKSEL1_PLL_SOURCE_54M                   (0x20)
#define CM_CLKSEL1_PLL_SOURCE_48M                    (0x8)
// CM_CLKSEL1_PLL bit positions 
//#define CM_CLKSEL1_PLL_CORE_DPLL_CLKOUT_DIV (27) 
//#define CM_CLKSEL1_PLL_CORE_DPLL_MULT       (16) 
//#define CM_CLKSEL1_PLL_CORE_DPLL_DIV         (8) 
//#define CM_CLKSEL1_PLL_SOURCE_96M            (6)
//#define CM_CLKSEL1_PLL_SOURCE_54M            (5)
//#define CM_CLKSEL1_PLL_SOURCE_48M            (3)


// CM_FCLKEN1_CORE bits
#define CM_FCLKEN1_CORE_EN_MMC3   (0x40000000)
#define CM_FCLKEN1_CORE_EN_MMC2    (0x2000000)
#define CM_FCLKEN1_CORE_EN_MMC1    (0x1000000)
#define CM_FCLKEN1_CORE_EN_HDQ      (0x400000)
#define CM_FCLKEN1_CORE_EN_MCSPI4   (0x200000)
#define CM_FCLKEN1_CORE_EN_MCSPI3   (0x100000)
#define CM_FCLKEN1_CORE_EN_MCSPI2    (0x80000)
#define CM_FCLKEN1_CORE_EN_MCSPI1    (0x40000)
#define CM_FCLKEN1_CORE_EN_I2C3      (0x20000)
#define CM_FCLKEN1_CORE_EN_I2C2      (0x10000)
#define CM_FCLKEN1_CORE_EN_I2C1       (0x8000)
#define CM_FCLKEN1_CORE_EN_UART2      (0x4000)
#define CM_FCLKEN1_CORE_EN_UART1      (0x2000)
#define CM_FCLKEN1_CORE_EN_GPT11      (0x1000)
#define CM_FCLKEN1_CORE_EN_GPT10       (0x800)
#define CM_FCLKEN1_CORE_EN_MCBSP5      (0x400)
#define CM_FCLKEN1_CORE_EN_MCBSP1      (0x200)


// CM_ICLKEN1_CORE bits
#define CM_ICLKEN1_CORE_EN_MMC3   (0x40000000)
#define CM_ICLKEN1_CORE_AES2      (0x10000000)
#define CM_ICLKEN1_CORE_SHA12      (0x8000000)
#define CM_ICLKEN1_CORE_DES2       (0x4000000)
#define CM_ICLKEN1_CORE_EN_MMC2    (0x2000000)
#define CM_ICLKEN1_CORE_EN_MMC1    (0x1000000)
#define CM_ICLKEN1_CORE_UART4       (0x800000)
#define CM_ICLKEN1_CORE_EN_HDQ      (0x400000)
#define CM_ICLKEN1_CORE_EN_MCSPI4   (0x200000)
#define CM_ICLKEN1_CORE_EN_MCSPI3   (0x100000)
#define CM_ICLKEN1_CORE_EN_MCSPI2    (0x80000)
#define CM_ICLKEN1_CORE_EN_MCSPI1    (0x40000)
#define CM_ICLKEN1_CORE_EN_I2C3      (0x20000)
#define CM_ICLKEN1_CORE_EN_I2C2      (0x10000)
#define CM_ICLKEN1_CORE_EN_I2C1       (0x8000)
#define CM_ICLKEN1_CORE_EN_UART2      (0x4000)
#define CM_ICLKEN1_CORE_EN_UART1      (0x2000)
#define CM_ICLKEN1_CORE_EN_GPT11      (0x1000)
#define CM_ICLKEN1_CORE_EN_GPT10       (0x800)
#define CM_ICLKEN1_CORE_EN_MCBSP5      (0x400)
#define CM_ICLKEN1_CORE_EN_MCBSP1      (0x200)
#define CM_ICLKEN1_CORE_EN_SCMCTRL      (0x40)
#define CM_ICLKEN1_CORE_IPSS            (0x10)
#define CM_ICLKEN1_CORE_SDRC             (0x2)

// CM_FCLKEN_PER bits
#define CM_FCLKEN_PER_EN_GPIO6     (0x20000)
#define CM_FCLKEN_PER_EN_GPIO5     (0x10000)
#define CM_FCLKEN_PER_EN_GPIO4      (0x8000)
#define CM_FCLKEN_PER_EN_GPIO3      (0x4000)
#define CM_FCLKEN_PER_EN_GPIO2      (0x2000)
#define CM_FCLKEN_PER_EN_WDT3       (0x1000)
#define CM_FCLKEN_PER_EN_UART3       (0x800)
#define CM_FCLKEN_PER_EN_GPT9        (0x400)
#define CM_FCLKEN_PER_EN_GPT8        (0x200)
#define CM_FCLKEN_PER_EN_GPT7        (0x100)
#define CM_FCLKEN_PER_EN_GPT6         (0x80)
#define CM_FCLKEN_PER_EN_GPT5         (0x40)
#define CM_FCLKEN_PER_EN_GPT4         (0x20)
#define CM_FCLKEN_PER_EN_GPT3         (0x10)
#define CM_FCLKEN_PER_EN_GPT2          (0x8)
#define CM_FCLKEN_PER_EN_MCBSP4        (0x4)
#define CM_FCLKEN_PER_EN_MCBSP3        (0x2)
#define CM_FCLKEN_PER_EN_MCBSP2        (0x1) 

// CM_ICLKEN_PER bits
#define CM_ICLKEN_PER_EN_GPIO6     (0x20000)
#define CM_ICLKEN_PER_EN_GPIO5     (0x10000)
#define CM_ICLKEN_PER_EN_GPIO4      (0x8000)
#define CM_ICLKEN_PER_EN_GPIO3      (0x4000)
#define CM_ICLKEN_PER_EN_GPIO2      (0x2000)
#define CM_ICLKEN_PER_EN_WDT3       (0x1000)
#define CM_ICLKEN_PER_EN_UART3       (0x800)
#define CM_ICLKEN_PER_EN_GPT9        (0x400)
#define CM_ICLKEN_PER_EN_GPT8        (0x200)
#define CM_ICLKEN_PER_EN_GPT7        (0x100)
#define CM_ICLKEN_PER_EN_GPT6         (0x80)
#define CM_ICLKEN_PER_EN_GPT5         (0x40)
#define CM_ICLKEN_PER_EN_GPT4         (0x20)
#define CM_ICLKEN_PER_EN_GPT3         (0x10)
#define CM_ICLKEN_PER_EN_GPT2          (0x8)
#define CM_ICLKEN_PER_EN_MCBSP4        (0x4)
#define CM_ICLKEN_PER_EN_MCBSP3        (0x2)
#define CM_ICLKEN_PER_EN_MCBSP2        (0x1) 


/*  template for register bits
#define CM_FCLKEN_PER_          (0x80000000)
#define CM_FCLKEN_PER_          (0x40000000)
#define CM_FCLKEN_PER_          (0x20000000)
#define CM_FCLKEN_PER_          (0x10000000)
#define CM_FCLKEN_PER_           (0x8000000)
#define CM_FCLKEN_PER_           (0x4000000)
#define CM_FCLKEN_PER_           (0x2000000)
#define CM_FCLKEN_PER_           (0x1000000)
#define CM_FCLKEN_PER_            (0x800000)
#define CM_FCLKEN_PER_            (0x400000)
#define CM_FCLKEN_PER_            (0x200000)
#define CM_FCLKEN_PER_            (0x100000)
#define CM_FCLKEN_PER_             (0x80000)
#define CM_FCLKEN_PER_             (0x40000)
#define CM_FCLKEN_PER_             (0x20000)
#define CM_FCLKEN_PER_             (0x10000)
#define CM_FCLKEN_PER_              (0x8000)
#define CM_FCLKEN_PER_              (0x4000)
#define CM_FCLKEN_PER_              (0x2000)
#define CM_FCLKEN_PER_              (0x1000)
#define CM_FCLKEN_PER_               (0x800)
#define CM_FCLKEN_PER_               (0x400)
#define CM_FCLKEN_PER_               (0x200)
#define CM_FCLKEN_PER_               (0x100)
#define CM_FCLKEN_PER_                (0x80)
#define CM_FCLKEN_PER_                (0x40)
#define CM_FCLKEN_PER_                (0x20)
#define CM_FCLKEN_PER_                (0x10)
#define CM_FCLKEN_PER_                 (0x8)
#define CM_FCLKEN_PER_                 (0x4)
#define CM_FCLKEN_PER_                 (0x2)
#define CM_FCLKEN_PER_                 (0x1) 
*/ 

#endif
