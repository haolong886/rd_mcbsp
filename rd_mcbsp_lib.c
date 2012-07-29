/* McBSP Function Library Source File
 * 
 * Version 0.03  (Still under development/debug)
 *
 * Function library to support quick low level configuration testing.
 *
 */

#include "rd_mcbsp_reg.h"
#include "rd_prcm_reg.h"
#include "rd_ctl_reg.h"
#include "rd_reg_op.h"
#include "rd_mcbsp_lib.h"




/////////////////////////////////////////////////////////////
// Enable the 96M_FCLK 
//
void cmEnableClock96M(void) 
{
	// Enables the 96M_FCLK clock
	//SETBIT_REGL(CM_CLKSEL1_PLL, CM_CLKSEL1_PLL_SOURCE_96M);
	CLRBIT_REGL(CM_CLKSEL1_PLL, CM_CLKSEL1_PLL_SOURCE_96M);
}

/////////////////////////////////////////////////////////////
// Disable the 96M_FCLK 
//
void cmDisableClock96M(void) 
{
	// Enables the 96M_FCLK clock
	//CLRBIT_REGL(CM_CLKSEL1_PLL, CM_CLKSEL1_PLL_SOURCE_96M);
	SETBIT_REGL(CM_CLKSEL1_PLL, CM_CLKSEL1_PLL_SOURCE_96M);
}


/////////////////////////////////////////////////////////////
// Enable the functional clock for the McBSP module 
//
void mcbspReset(unsigned int ulModule, unsigned char ulBlock)
{
  mcbspResetRx(ulModule);
  mcbspResetTx(ulModule);
  mcbspResetFsg(ulModule);
  mcbspResetSrg(ulModule);  
  if (ulBlock)
  {
  	while(CHKBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_GRST));   // Wait until GRST bit is clear
  } 
}
void mcbsp_receive_start(unsigned int ulModule)
{
	SETBIT_REGL(ulModule + MCBSPLP_RCCR_REG, 0x0);
}
void mcbsp_receive_stop(unsigned int ulModule)
{
	SETBIT_REGL(ulModule + MCBSPLP_RCCR_REG, 0x1);
}
/////////////////////////////////////////////////////////////
// Setup the tranmsitter
//
void mcbspSetTxMode(unsigned int ulModule, 
                    unsigned char ulCLKXM, 
                    unsigned char ulCLKXP, 
                    unsigned char ulFSXM, 
                    unsigned char ulFSXP, 
                    unsigned char ulCYCLE, 
                    unsigned char ulDXENAMode,
                    unsigned char ulEXTCLKGATE,
                    unsigned char ulFSGM)  
{
	
  CLRBIT_REGL(ulModule + MCBSPLP_PCR_REG, PCR_FSXM + PCR_CLKXM + PCR_FSXP + PCR_CLKXP); // clear the appropriate bits  
  SETBIT_REGL(ulModule + MCBSPLP_PCR_REG,  (ulFSXM<<11) + (ulCLKXM<<9) + (ulFSXP<<3) + (ulCLKXP<<1)); 
  CLRBIT_REGL(ulModule + MCBSPLP_SRGR2_REG, SRGR2_FSGM);
  SETBIT_REGL(ulModule + MCBSPLP_SRGR2_REG, (ulFSGM<<12));

  switch (ulDXENAMode) 
  {
  	case (DXENA_OFF):
  	  CLRBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_DXENA);
  	  break;
  	case (DXENA_DLY1):
  	  SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_DXENA);
      CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_1);
      CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_0);
  	  break;
  	case (DXENA_DLY2):
  	  SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_DXENA);
      CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_1);
      SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_0);
  	  break;
  	case (DXENA_DLY3):
  	  SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_DXENA);
      SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_1);
      CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_0);
  	  break;
  	case (DXENA_DLY4):
	  SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_DXENA);
      SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_1);
      SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DXENDLY_0);
  	  break;
  	default:
  	  break;
  }

  CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_XFULL_CYCLE + XCCR_EXTCLKGATE);
  SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, (ulCYCLE<<11) + (ulEXTCLKGATE<<15));
    
}

/////////////////////////////////////////////////////////////
// Setup the receiver
//

void mcbspSetRxMode(unsigned int ulModule, 
                    unsigned char ulCLKRM, 
                    unsigned char ulCLKRP, 
                    unsigned char ulFSRM, 
                    unsigned char ulFSRP, 
                    unsigned char ulCYCLE)  
{
	
  CLRBIT_REGL(ulModule + MCBSPLP_PCR_REG, PCR_FSRM + PCR_CLKRM + PCR_FSRP + PCR_CLKRP); // clear the appropriate bits  
  //SETBIT_REGL(ulModule + MCBSPLP_PCR_REG,  (ulFSRM<<11) + (ulCLKRM<<9) + (ulFSRP<<3) + (ulCLKRP<<1)); 
  SETBIT_REGL(ulModule + MCBSPLP_PCR_REG,  (ulFSRM<<10) + (ulCLKRM<<8) + (ulFSRP<<2) + (ulCLKRP)); 
  if (ulCYCLE) 
  {
    SETBIT_REGL(ulModule + MCBSPLP_RCCR_REG, RCCR_RFULL_CYCLE);    	
  } else {
    CLRBIT_REGL(ulModule + MCBSPLP_RCCR_REG, RCCR_RFULL_CYCLE);  
  }	
}

/////////////////////////////////////////////////////////////
// Setup the receive frame
//
void mcbspRxFrameSetup(unsigned int ulModule,
                       unsigned char ulRPHASE,  
                       unsigned char ulRREVERSE,  
                       unsigned char ulRDATDLY,  
                       unsigned char ulRFRLEN1,  
                       unsigned char ulRWDLEN1,  
                       unsigned char ulRFRLEN2,  
                       unsigned char ulRWDLEN2, 
                       unsigned char ulRJUST)  

{
	OUT_REGL(ulModule + MCBSPLP_RCR1_REG,  ((ulRFRLEN1-1)<<8) + (ulRWDLEN1<<5));
	OUT_REGL(ulModule + MCBSPLP_RCR2_REG,  (ulRPHASE<<15) + (ulRFRLEN2<<8) + (ulRWDLEN2<<5) + (ulRREVERSE<<3) + ulRDATDLY);
	CLRBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_RJUST_1 + SPCR1_RJUST_0);
	SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, (ulRJUST<<13));
}

/////////////////////////////////////////////////////////////
// Setup the receive frame
//
void mcbspTxFrameSetup(unsigned int ulModule,
                       unsigned char ulXPHASE,  
                       unsigned char ulXREVERSE,  
                       unsigned char ulXDATDLY,  
                       unsigned char ulXFRLEN1,  
                       unsigned char ulXWDLEN1,  
                       unsigned char ulXFRLEN2,  
                       unsigned char ulXWDLEN2) 

{
	OUT_REGL(ulModule + MCBSPLP_XCR1_REG,  ((ulXFRLEN1-1)<<8) + (ulXWDLEN1<<5));
	OUT_REGL(ulModule + MCBSPLP_XCR2_REG,  (ulXPHASE<<15) + (ulXFRLEN2<<8) + (ulXWDLEN2<<5) + (ulXREVERSE<<3) + ulXDATDLY);
}

/////////////////////////////////////////////////////////////
// Select the clock source
//
void mcbspSetupSrg(unsigned int ulModule, 
                   unsigned char ulSource, 
                   unsigned char ulCLKSP, 
                   unsigned char ulGSYNC, 
                   unsigned int  ulFPER, 
                   unsigned char ulFWID, 
                   unsigned char ulCLKGDV)
{
	OUT_REGL(ulModule + MCBSPLP_SRGR1_REG,  ((ulFWID-1)<<8) + (ulCLKGDV - 1));
	CLRBIT_REGL(ulModule + MCBSPLP_SRGR2_REG,  SRGR2_GSYNC + SRGR2_CLKSP + SRGR2_FPER_MASK);
	//------------------------------------------------------------------------------
	//SETBIT_REGL(ulModule + MCBSPLP_SRGR2_REG,  (ulGSYNC<<15) + (ulCLKSP<<14) + (ulFPER));
	SETBIT_REGL(ulModule + MCBSPLP_SRGR2_REG,  (ulGSYNC<<15) | (ulCLKSP<<14) | (ulFPER-1));

	switch(ulSource) {
		case(CLKS):
		  CLRBIT_REGL(ulModule + MCBSPLP_PCR_REG, PCR_SCLKME);
		  CLRBIT_REGL(ulModule + MCBSPLP_SRGR2_REG, SRGR2_CLKSM);
		  break;
		case(CLKI):
		  CLRBIT_REGL(ulModule + MCBSPLP_PCR_REG, PCR_SCLKME);
		  SETBIT_REGL(ulModule + MCBSPLP_SRGR2_REG, SRGR2_CLKSM);
		  break;
		case(CLKR):
		  SETBIT_REGL(ulModule + MCBSPLP_PCR_REG, PCR_SCLKME);
		  CLRBIT_REGL(ulModule + MCBSPLP_SRGR2_REG, SRGR2_CLKSM);
		  break;
		case(CLKX):
		  SETBIT_REGL(ulModule + MCBSPLP_PCR_REG, PCR_SCLKME);
		  SETBIT_REGL(ulModule + MCBSPLP_SRGR2_REG, SRGR2_CLKSM);
		  break;
		default:
		  break;
	}
}

/////////////////////////////////////////////////////////////
// Enable the functional clock for the McBSP module 
//
void mcbspEnableFclk(unsigned int ulModule) 
{
  switch (ulModule) {
    case(MCBSP1):
  	  SETBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP1);
      break;
    case(MCBSP2):
  	  SETBIT_REGL(CM_FCLKEN_PER, CM_FCLKEN_PER_EN_MCBSP2);
      break;
    case(MCBSP3):
  	  SETBIT_REGL(CM_FCLKEN_PER, CM_FCLKEN_PER_EN_MCBSP2);
      break;
    case(MCBSP4):
  	  SETBIT_REGL(CM_FCLKEN_PER, CM_FCLKEN_PER_EN_MCBSP2);
      break;
    case(MCBSP5):
  	  SETBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP5);
      break;
    default:
      return;
  }
}

/////////////////////////////////////////////////////////////
// Disable the functional clock for the McBSP module 
//
void mcbspDisableFclk(unsigned int ulModule) 
{
  switch (ulModule) {
    case(MCBSP1):
	  	  CLRBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP1);
	      break;
	    case(MCBSP2):
	  	  CLRBIT_REGL(CM_FCLKEN_PER, CM_FCLKEN_PER_EN_MCBSP2);
	      break;
	    case(MCBSP3):
	  	  CLRBIT_REGL(CM_FCLKEN_PER, CM_FCLKEN_PER_EN_MCBSP2);
	      break;
	    case(MCBSP4):
	  	  CLRBIT_REGL(CM_FCLKEN_PER, CM_FCLKEN_PER_EN_MCBSP2);
	      break;
	    case(MCBSP5):
	  	  CLRBIT_REGL(CM_FCLKEN1_CORE, CM_FCLKEN1_CORE_EN_MCBSP5);
	      break;
    default:
      return;
  }
}


/////////////////////////////////////////////////////////////
// Enable the interface clock for the McBSP module 
//
void mcbspEnableIclk(unsigned int ulModule) 
{
  switch (ulModule) {
    case(MCBSP1):
  	  SETBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP1);
      break;
    case(MCBSP2):
  	  SETBIT_REGL(CM_ICLKEN_PER, CM_ICLKEN_PER_EN_MCBSP2);
      break;
    case(MCBSP3):
  	  SETBIT_REGL(CM_ICLKEN_PER, CM_ICLKEN_PER_EN_MCBSP2);
      break;
    case(MCBSP4):
  	  SETBIT_REGL(CM_ICLKEN_PER, CM_ICLKEN_PER_EN_MCBSP2);
      break;
    case(MCBSP5):
  	  SETBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP5);
      break;
    default:
      return;
  }
}

/////////////////////////////////////////////////////////////
// Disable the interface clock for the McBSP module 
//
void mcbspDisableIclk(unsigned int ulModule) 
{
  	  CLRBIT_REGL(CM_ICLKEN1_CORE, CM_ICLKEN1_CORE_EN_MCBSP1);
}



/////////////////////////////////////////////////////////////
// Select mcbsp_clks pin as the source for the MCBSP 
//
void mcbspSelectClksSource(unsigned int ulModule, unsigned char ulSource) 
{
	if (ulSource)
	{
		// Select the external mcbsp_clks pin as the source
        switch (ulModule) {
          case(MCBSP1):
            SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKS);
            break;
          case(MCBSP2):
  	        SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP2_CLKS);
            SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKS);
            break;
          case(MCBSP3):
  	        SETBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP3_CLKS);
            break;
          case(MCBSP4):
  	        SETBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP4_CLKS);
            break;
          case(MCBSP5):
  	        SETBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP5_CLKS);
            break;
          default:
            return;
        }
	} else {
		// Select the internal FCLK as the source 
        switch (ulModule) {
          case(MCBSP1):
      	    CLRBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKS);
            break;
          case(MCBSP2):
  	        CLRBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP2_CLKS);
            break;
          case(MCBSP3):
  	        CLRBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP3_CLKS);
            break;
          case(MCBSP4):
  	        CLRBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP4_CLKS);
            break;
          case(MCBSP5):
  	        CLRBIT_REGL(CONTROL_DEVCONF1, CONTROL_DEVCONF1_MCBSP5_CLKS);
            break;
          default:
            return;
        }
	}
} 

/////////////////////////////////////////////////////////////
// Set McBSP to 6 pin mode 
//
// Only valid for McBSP 1
//
void mcbspSet6Pin(unsigned int ulModule)
{
  switch (ulModule) {
    case(MCBSP1):
  	  CLRBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKR);
	  CLRBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_FSR);	
    default:
      return;
  }
}
 
/////////////////////////////////////////////////////////////
// Set McBSP to 4 pin mode 
//
// Only really valid for McBSP 1, all others are 4 pin only. 
//
void mcbspSet4Pin(unsigned int ulModule)
{
  switch (ulModule) {
    case(MCBSP1):
  	  SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_CLKR);
	  SETBIT_REGL(CONTROL_DEVCONF0, CONTROL_DEVCONF0_MCBSP1_FSR);
    default:
      return;
  }
}


/////////////////////////////////////////////////////////////
// Enable Sample Rate Generator
void mcbspRemoveResetSrg (unsigned int ulModule)
{
  SETBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_GRST);	
}

/////////////////////////////////////////////////////////////
// Reset Sample Rate Generator
void mcbspResetSrg (unsigned int ulModule)
{
  CLRBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_GRST);	
}

/////////////////////////////////////////////////////////////
// Enable Receiver
void mcbspRemoveResetRx (unsigned int ulModule)
{
  SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_RRST);	
}

/////////////////////////////////////////////////////////////
// Reset Receiver
void mcbspResetRx(unsigned int ulModule)
{
  CLRBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_RRST);	
}


/////////////////////////////////////////////////////////////
// Enable Transmtter
void mcbspRemoveResetTx (unsigned int ulModule)
{
  SETBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_XRST);		
}

/////////////////////////////////////////////////////////////
// Reset Transmtter
void mcbspResetTx (unsigned int ulModule)
{
  CLRBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_XRST);		
}



/////////////////////////////////////////////////////////////
// Enable Frame Sync generator
void mcbspRemoveResetFsg (unsigned int ulModule)
{
  SETBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_FRST);			
}
  
/////////////////////////////////////////////////////////////
// Enable Frame Sync generator
void mcbspResetFsg (unsigned int ulModule)
{
  CLRBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_FRST);			
}

/////////////////////////////////////////////////////////////
// Enable Transmtter
void mcbspEnableTx (unsigned int ulModule)
{
  CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_XDISABLE);		
}

/////////////////////////////////////////////////////////////
// Disable Transmtter
void mcbspDisableTx (unsigned int ulModule)
{
  SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_XDISABLE);		
}

/////////////////////////////////////////////////////////////
// Enable Receiver
void mcbspEnableRx (unsigned int ulModule)
{
  CLRBIT_REGL(ulModule + MCBSPLP_RCCR_REG, RCCR_RDISABLE);		
}

/////////////////////////////////////////////////////////////
// Disable Receiver
void mcbspDisableRx (unsigned int ulModule)
{
  SETBIT_REGL(ulModule + MCBSPLP_RCCR_REG, RCCR_RDISABLE);		
}


/////////////////////////////////////////////////////////////
// Set loopback mode
void mcbspLoopback(unsigned int ulModule, unsigned char ulMode)
{
	switch(ulMode) 
	{
		case(NO_LOOPBACK):
		  CLRBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_ALB);
		  CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DLB);
		  break;
		case(DIGITAL_LOOPBACK):
		  CLRBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_ALB);
		  SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DLB);
		  break;
		case(ANALOG_LOOPBACK):
		  SETBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_ALB);
		  CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DLB);
		  break;
		default:
		  CLRBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_ALB);
		  CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_DLB);
		  break;
		
	}
}


void mcbspDataPut(unsigned int ulModule, unsigned int ulData)
{
  while (!CHKBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_XRDY));
  OUT_REGL(ulModule + MCBSPLP_DXR_REG, ulData);	
}

void mcbspDataGet(unsigned int ulModule, unsigned int *pulData)
{
  while(!CHKBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_RRDY));	
  *pulData = IN_REGL(ulModule + MCBSPLP_DRR_REG);	
}

unsigned char mcbspDataPutNoBlock(unsigned int ulModule, unsigned int ulData)
{
  if(CHKBIT_REGL(ulModule + MCBSPLP_SPCR2_REG, SPCR2_XRDY)) 
  {
     OUT_REGL(ulModule + MCBSPLP_DXR_REG, ulData);
     return 1;
  } else {
  	 return 0;
  }	
}

unsigned char mcbspDataGetNoBlock(unsigned int ulModule, unsigned int *pulData)
{
  if(CHKBIT_REGL(ulModule + MCBSPLP_SPCR1_REG, SPCR1_RRDY))
  {
    *pulData = IN_REGL(ulModule + MCBSPLP_DRR_REG);
    return 1;	
  } else {
  	return 0;
  }	
}


void mcbspSetRxThresh(unsigned int ulModule, unsigned int ulThreshold)
{
   OUT_REGL(ulModule + MCBSPLP_THRSH1_REG, (ulThreshold -1));
}

void mcbspSetTxThresh(unsigned int ulModule, unsigned int ulThreshold)
{
   OUT_REGL(ulModule + MCBSPLP_THRSH2_REG, (ulThreshold -1));
}

unsigned int mcbspTxBuffStat(unsigned int ulModule)
{
	return (IN_REGL(ulModule + MCBSPLP_XBUFFSTAT_REG));
}

unsigned int mcbspRxBuffStat(unsigned int ulModule)
{
	return (IN_REGL(ulModule + MCBSPLP_RBUFFSTAT_REG));
}

void mcbspEnableTxDma(unsigned int ulModule)
{
   SETBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_XDMAEN);
}

void mcbspDisableTxDma(unsigned int ulModule)
{
   CLRBIT_REGL(ulModule + MCBSPLP_XCCR_REG, XCCR_XDMAEN);
}

void mcbspEnableRxDma(unsigned int ulModule)
{
   SETBIT_REGL(ulModule + MCBSPLP_RCCR_REG, RCCR_RDMAEN);
}

void mcbspDisableRxDma(unsigned int ulModule)
{
   CLRBIT_REGL(ulModule + MCBSPLP_RCCR_REG, RCCR_RDMAEN);
}



