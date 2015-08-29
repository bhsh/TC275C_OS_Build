/*
 * DemoApp.c
 *
 *  Created on: Mar 31, 2014
 *      Author: lisherry
 */

#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"
#include "DemoApp.h"

//#define iLLD

static IfxDsadc_Dsadc dsadc;
IfxDsadc_Dsadc_Channel dsadcChannel[IFXDSADC_NUM_CHANNELS];
#if defined(DERIVATIVE_TC22x) || defined(DERIVATIVE_TC23x) || defined(DERIVATIVE_TC24x)
uint8 dsadcChannelAvailable[IFXDSADC_NUM_CHANNELS] = { 1, 0, 0, 1 };
#elif defined(DERIVATIVE_TC27x) || defined(DERIVATIVE_TC27xB) || defined(DERIVATIVE_TC27xC) || defined(DERIVATIVE_TC27xD)
uint8 dsadcChannelAvailable[IFXDSADC_NUM_CHANNELS] = { 1, 1, 1, 1, 1, 1 };
#elif defined(DERIVATIVE_TC26x) || defined(DERIVATIVE_TC26xB)
uint8 dsadcChannelAvailable[IFXDSADC_NUM_CHANNELS] = { 1, 0, 1, 1 };
#elif defined(DERIVATIVE_TC29x) || defined(DERIVATIVE_TC29xB)
uint8 dsadcChannelAvailable[IFXDSADC_NUM_CHANNELS] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
#else# error "Testcase not prepared for this derivative!"
#endif

sint16 result[10];

void Appli_DsadcModule_Init(void)
{
	int chn;
#ifdef iLLD
	// create module config
	IfxDsadc_Dsadc_Config dsadcConfig;
	IfxDsadc_Dsadc_initModuleConfig(&dsadcConfig, &MODULE_DSADC);

	// initialize module
	IfxDsadc_Dsadc_initModule(&dsadc, &dsadcConfig);

	// create channel config
	IfxDsadc_Dsadc_ChannelConfig dsadcChannelConfig;
	IfxDsadc_Dsadc_initChannelConfig(&dsadcChannelConfig, &dsadc);

	// modify default configuration
	dsadcChannelConfig.modulator.positiveInput      = IfxDsadc_InputConfig_inputPin;
	dsadcChannelConfig.modulator.negativeInput      = IfxDsadc_InputConfig_inputPin;
	dsadcChannelConfig.modulator.inputGain          = IfxDsadc_InputGain_factor1;
	dsadcChannelConfig.modulator.inputPin           = IfxDsadc_InputPin_a;
	dsadcChannelConfig.modulator.modulatorClockFreq = 10.0e6;
	dsadcChannelConfig.modulator.commonModeVoltage  = IfxDsadc_CommonModeVoltage_c;
	dsadcChannelConfig.combFilter.bypassed          = FALSE;
	dsadcChannelConfig.combFilter.combFilterType    = IfxDsadc_MainCombFilterType_comb3;
	dsadcChannelConfig.combFilter.combFilterShift   = IfxDsadc_MainCombFilterShift_noShift;
	dsadcChannelConfig.combFilter.serviceRequest    = IfxDsadc_MainServiceRequest_everyNewResult;
	dsadcChannelConfig.combFilter.decimationFactor  = 32;
	dsadcChannelConfig.combFilter.startValue        = 32;
	dsadcChannelConfig.firFilter.fir0Enabled        = TRUE;
	dsadcChannelConfig.firFilter.fir1Enabled        = TRUE;
	dsadcChannelConfig.firFilter.offsetCompensation = FALSE;
	dsadcChannelConfig.firFilter.dataShift          = IfxDsadc_FirDataShift_shiftBy2;
	dsadcChannelConfig.firFilter.internalShift      = IfxDsadc_FirInternalShift_shiftBy1;

	// initialize channels
	for(chn=0; chn<IFXDSADC_NUM_CHANNELS; ++chn)
	{
		if( dsadcChannelAvailable[chn] )
		{
			dsadcChannelConfig.channelId = (IfxDsadc_ChannelId)chn;
			IfxDsadc_Dsadc_initChannel(&dsadcChannel[chn], &dsadcChannelConfig);
		}
	}
#endif
}

void Appli_DsadcInit(void)
{

#ifdef iLLD
	Appli_DsadcModule_Init();
#else
	uint16 endinitPw;
    endinitPw = IfxScuWdt_getCpuWatchdogPassword ();
	IfxScuWdt_clearCpuEndinit(endinitPw);

	DSADC_CLC.B.DISR = 0;;    // enable module clock

    while (DSADC_CLC.B.DISS == 1); // wait until module is enabled

    DSADC_KRST0.B.RST = 1;
    DSADC_KRST1.B.RST = 1;

    while (DSADC_KRST0.B.RSTSTAT == 0);

    IfxScuWdt_setCpuEndinit(endinitPw);

    DSADC_GLOBCFG.B.MCSEL = 1; //select fDSD
    /* first we set the inputs to GND to measure offset error */
    DSADC_MODCFG0.U = 0x8682800B;
    //DSADC_MODCFG0.U = 0xA682800B;
    //MODCFG0.APC = 0 = alwasy runnign
    //MODCFG0.GCEN = 0 = normal operation
    //MODCFG0.MCFG = 01B = high-performance+anti-alias filter
    //MODCFG0.CMVS = 10B = VCM is VAREF/2 = 2.5V
    //MODCFG0.DIVM = 2 = fMOD = fCLK/6 = 100MHz/6
    //MODCFG0.INSEL = 0 = input pin position A
    //MODCFG0.GAINSEL = 0 = gain factor 1
    //MODCFG0.INCFGN = 10B = VCM
    //MODCFG0.INCFGP = 11B = reference GND

    /* set Main Comb Filter (DSADC_FCFGCx) */
    DSADC_FCFGC0.U = 0x00313631;
    //DSADC_FCFGC0.U = 0x001F3631;
    //DSADC_FCFGC0.U = 0x001F3631;
    //FCFGC0.CFMSV = 0x31 = decimation counter start = 49
    //FCFGC0.SRGM = 0 = no interrupt
    //FCFGC0.MFSC = 11B = Shift by 3
    //FCFGC0.CFEN = 1 = CIC enabled
    //FCFGC0.CFMC = 10B = CIC3 selected
    //FCFGC0.CFMDF = 0x31 = decimation rate = 50

    /* set demodulator input (DSADC_DICFGx) */
    DSADC_DICFG0.U = 0x80108080;
    //DICFG0.DSRC = 0000B = Input Data Source = On-chip modulator (3rd order)
    //DICFG0.STROBE = 1 = sample trigger at rising clock edge

    /* set Filter Configuration Register (DSADC_FCFGMx) */
    DSADC_FCFGM0.U = 0x2B;
    //DSADC_FCFGM0.U = 0xA;
    //FCFGM0.FSH = 1 = FIR0 shift to left 1 time
    //FCFGM0.DSH = 1 = FIR1 shift to left 1 time
    //FCFGM0.FIR0EN = 1 = FIR0 enabled
    //FCFGM0.FIR1EN = 1 = FIR1 enabled

    /* set Integrator (DSADC_IWCTRx) */
    DSADC_IWCTR0.U = 0x0;
#endif
}

void Appli_DsadcDemoInit(void)
{
}

void Appli_DsadcDemoDeInit(void)
{
}
void delay(void)
{
	int i, j;
	volatile k;
	for(i=0;i<65535;i++)
	{
		for(j=0;j<1000;j++)
		{
			k = i + j;
		}
	}
}

void Appli_DsadcCyclic(void)
{
	char str_adc[10];
	int chn;
#ifdef iLLD
	// start conversions
	IfxDsadc_Dsadc_startScan(&dsadc, 0x3f, 0x3f);
	// results are now available in IFXDSADC(ds).CH[x].RESM.B.RESULT (x=0..5

	// declared globally    // sint16 result[];
	for(chn=0; chn<IFXDSADC_NUM_CHANNELS; ++chn)
	{
		if( dsadcChannelAvailable[chn] )
		{
			result[chn] = IfxDsadc_Dsadc_getMainResult(&dsadcChannel[chn]);
#if 0
			ConsolePrint("\tCH");
			ShortToAscii(chn, str_adc);
			ConsolePrint(str_adc);
			ConsolePrint(" :");
			ShortToAscii(result, str_adc);  //str_adc[10] = '\0';
			ConsolePrint(str_adc);
#endif
		}
	}
#else
	DSADC_GLOBRC.U = 0x010001;
	delay();
	//note that DSADC result is 2's complement
	if ((DSADC_RESM0.B.RESULT & 0x8000) == 0x8000)
	{
		result[0] = (float) (~DSADC_RESM0.U + 1) * 11.375290337;
		//display_ascii_printf(DISPLAYSTDOUT0, "DSADC0 = -%.4fV\n", result);
	}
	else
	{
		result[0] = (float) DSADC_RESM0.U * 11.375290337;
		//display_ascii_printf(DISPLAYSTDOUT0, "DSADC0 = %.4fV\n", result);
	}

#endif
}

