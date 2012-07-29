/* McBSP Function Library Header File
 * 
 * Version 0.03  (Still under development/debug)
 *
 * Function library to support quick low level configuration testing.
 *
 */



//Prototypes
//
#ifndef _RD_MCBSP_LIB_H
#define _RD_MCBSP_LIB_H
void cmEnableClock96M(void);  // to be moved?
void cmDisableClock96M(void); // to be moved?


void mcbspReset(unsigned int ulModule, unsigned char ulBlock); 
void mcbspSetTxMode(unsigned int ulModule, unsigned char ulCLKXM, unsigned char ulCLKXP, unsigned char ulFSXM, unsigned char ulFSXP, unsigned char ulCYCLE, unsigned char ulDXENAMode, unsigned char ulEXTCLKGATE, unsigned char ulFSGM);
void mcbspSetRxMode(unsigned int ulModule, unsigned char ulCLKRM, unsigned char ulCLKRP, unsigned char ulFSRM, unsigned char ulFSRP, unsigned char ulCYCLE);
void mcbspRxFrameSetup(unsigned int ulModule, unsigned char ulRPHASE, unsigned char ulRREVERSE, unsigned char ulRDATDLY, unsigned char ulRFRLEN1, unsigned char ulRWDLEN1, unsigned char ulRFRLEN2, unsigned char ulRWDLEN2, unsigned char ulRJUST);
void mcbspTxFrameSetup(unsigned int ulModule, unsigned char ulXPHASE, unsigned char ulXREVERSE, unsigned char ulXDATDLY, unsigned char ulXFRLEN1, unsigned char ulXWDLEN1, unsigned char ulXFRLEN2, unsigned char ulXWDLEN2); 
void mcbspSetupSrg(unsigned int ulModule, unsigned char ulSource, unsigned char ulCLKSP, unsigned char ulGSYNC,  unsigned int ulFPER, unsigned char ulFWID, unsigned char ulCLKGDV);
void mcbspEnableFclk(unsigned int ulModule);
void mcbspDisableFclk(unsigned int ulModule);
void mcbspEnableIclk(unsigned int ulModule);
void mcbspDisableIclk(unsigned int ulModule); 
void mcbspSelectClksSource(unsigned int ulModule, unsigned char ulSource);
void mcbspSet6Pin(unsigned int ulModule);
void mcbspSet4Pin(unsigned int ulModule);

void mcbspRemoveResetSrg(unsigned int ulModule);
void mcbspResetSrg(unsigned int ulModule);
void mcbspRemoveResetRx(unsigned int ulModule);
void mcbspResetRx(unsigned int ulModule);
void mcbspRemoveResetTx(unsigned int ulModule);
void mcbspResetTx(unsigned int ulModule);
void mcbspRemoveResetFsg(unsigned int ulModule);
void mcbspResetFsg(unsigned int ulModule);

void mcbspEnableTx(unsigned int ulModule);
void mcbspDisableTx(unsigned int ulModule);
void mcbspEnableRx(unsigned int ulModule);
void mcbspDisableRx(unsigned int ulModule);
void mcbspLoopback(unsigned int ulModule, unsigned char ulMode);
void mcbspDataPut(unsigned int ulModule, unsigned int ulData);
void mcbspDataGet(unsigned int ulModule, unsigned int *pulData);
void mcbspSetRxThresh(unsigned int ulModule, unsigned int ulThreshold);
void mcbspSetTxThresh(unsigned int ulModule, unsigned int ulThreshold);
void mcbspEnableTxDma(unsigned int ulModule);
void mcbspDisableTxDma(unsigned int ulModule);
void mcbspEnableRxDma(unsigned int ulModule);
void mcbspDisableRxDma(unsigned int ulModule);
unsigned int mcbspTxBuffStat(unsigned int ulModule);
unsigned int mcbspRxBuffStat(unsigned int ulModule);


unsigned char mcbspDataPutNoBlock(unsigned int ulModule, unsigned int ulData);
unsigned char mcbspDataGetNoBlock(unsigned int ulModule, unsigned int *pulData);
void mcbsp_receive_start(unsigned int ulModule);
void mcbsp_receive_stop(unsigned int ulModule);

// General defines
# define MCBSP1           MCBSP1_REG_BASE
# define MCBSP2           MCBSP2_REG_BASE
# define MCBSP3           MCBSP3_REG_BASE
# define MCBSP4           MCBSP4_REG_BASE
# define MCBSP5           MCBSP5_REG_BASE

// mcbspSelectClksSource parameters
#define  MCBSP_CLKS_PIN   1     // Set external mcbsp_clks pin as CLKS source
#define  INTERNAL_FCLK    0     // Set intern FCLK as CLKS source


// mcbspRxFrameSetup & mcbspTxFrameSetup parameters
#define SINGLE_PHASE      0
#define DUAL_PHASE        0
#define RIGHT_JUST_ZERO   0
#define RIGHT_JUST_SIGN   1
#define LEFT_JUST_ZERO    2
#define MSB_FIRST         0
#define LSB_FIRST         1
#define DELAY_0BIT        0
#define DELAY_1BIT        1
#define DELAY_2BIT        2
#define WORD_8BITS        0
#define WORD_12BITS       1        
#define WORD_16BITS       2 
#define WORD_20BITS       3 
#define WORD_24BITS       4 
#define WORD_32BITS       5 


// mcbspSelectSrgClockSource parameters
#define CLKS             0
#define CLKI             1
#define CLKR             2
#define CLKX             3
#define CLKS_RISE        0
#define CLKS_FALL        1
#define SRG_FREE         0
#define SRG_SYNC         1


// mcbspSetTxMode & mcbspSetRxMode parameters
#define CLK_EXTERNAL         0
#define CLK_INTERNAL         1
#define SYNC_EXTERNAL        0
#define SYNC_INTERNAL        1
#define SYNC_ACTIVE_HIGH     0
#define SYNC_ACTIVE_LOW      1
#define CLKX_DRIVE_RISE      0
#define CLKX_DRIVE_FALL      1
#define CLKR_SAMPLE_RISE     1
#define CLKR_SAMPLE_FALL     0
#define FULL_CYCLE           1
#define HALF_CYCLE           0
#define DXENA_OFF            0
#define DXENA_DLY1           1
#define DXENA_DLY2           2
#define DXENA_DLY3           3
#define DXENA_DLY4           4
#define XCLK_GATED           1
#define XCLK_FREE            0
#define FSX_GATED            0
#define FSX_FREE             1

// mcbspLoopback parameters
#define NO_LOOPBACK          0
#define DIGITAL_LOOPBACK     1
#define ANALOG_LOOPBACK      2

#endif
