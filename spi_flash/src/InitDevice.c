//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library includes]
#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_assert.h"
#include "em_adc.h"
#include "em_cryotimer.h"
#include "em_crypto.h"
#include "em_gpcrc.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_letimer.h"
#include "em_rtcc.h"
#include "em_timer.h"
#include "em_usart.h"
#include "em_wdog.h"
// [Library includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	CHIP_Init();

	EMU_enter_DefaultMode_from_RESET();
	CMU_enter_DefaultMode_from_RESET();
	ADC0_enter_DefaultMode_from_RESET();
	RTCC_enter_DefaultMode_from_RESET();
	USART0_enter_DefaultMode_from_RESET();
	USART1_enter_DefaultMode_from_RESET();
	WDOG0_enter_DefaultMode_from_RESET();
	I2C0_enter_DefaultMode_from_RESET();
	GPCRC_enter_DefaultMode_from_RESET();
	TIMER0_enter_DefaultMode_from_RESET();
	TIMER1_enter_DefaultMode_from_RESET();
	LETIMER0_enter_DefaultMode_from_RESET();
	CRYOTIMER_enter_DefaultMode_from_RESET();
	PORTIO_enter_DefaultMode_from_RESET();
	// [Config Calls]$

}

//================================================================================
// EMU_enter_DefaultMode_from_RESET
//================================================================================
extern void EMU_enter_DefaultMode_from_RESET(void) {

	// $[EMU Initialization]
	/* Initialize DCDC regulator */
	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;

	dcdcInit.powerConfig = emuPowerConfig_DcdcToDvdd;
	dcdcInit.dcdcMode = emuDcdcMode_LowNoise;
	dcdcInit.mVout = 1800;
	dcdcInit.em01LoadCurrent_mA = 15;
	dcdcInit.em234LoadCurrent_uA = 10;
	dcdcInit.maxCurrent_mA = 200;
	dcdcInit.anaPeripheralPower = emuDcdcAnaPeripheralPower_DCDC;
	dcdcInit.reverseCurrentControl = 160;

	EMU_DCDCInit(&dcdcInit);
	/* Initialize EM2/EM3 mode */
	EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;

	em23Init.em23VregFullEn = 0;

	EMU_EM23Init(&em23Init);
	/* Initialize EM4H/S mode */
	EMU_EM4Init_TypeDef em4Init = EMU_EM4INIT_DEFAULT;

	em4Init.retainLfrco = 0;
	em4Init.retainLfxo = 0;
	em4Init.retainUlfrco = 0;
	em4Init.em4State = emuEM4Shutoff;
	em4Init.pinRetentionMode = emuPinRetentionDisable;

	EMU_EM4Init(&em4Init);
	// [EMU Initialization]$

}

//================================================================================
// LFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void LFXO_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// CMU_enter_DefaultMode_from_RESET
//================================================================================
extern void CMU_enter_DefaultMode_from_RESET(void) {

	// $[High Frequency Clock Setup]
	/* Initializing HFXO */
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

	CMU_HFXOInit(&hfxoInit);

	/* Setting system HFXO frequency */
	SystemHFXOClockSet(38400000);

	/* Enable HFXO oscillator, and wait for it to be stable */
	CMU_OscillatorEnable(cmuOsc_HFXO, true, true);

	/* Using HFXO as high frequency clock, HFCLK */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

	/* HFRCO not needed when using HFXO */
	CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

	/* Set autostart behaviour */
	CMU_HFXOAutostartEnable(0, false, false);

	// [High Frequency Clock Setup]$

	// $[LE clocks enable]
	/* Enable clock to LE modules */
	CMU_ClockEnable(cmuClock_CORELE, true);
	/* Enable LFRCO oscillator, and wait for it to be stable */
	CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);

	/* Enable ULFRCO oscillator, and wait for it to be stable */
	CMU_OscillatorEnable(cmuOsc_ULFRCO, true, true);

	// [LE clocks enable]$

	// $[LFACLK Setup]
	/* Select LFRCO as clock source for LFACLK */
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
	// [LFACLK Setup]$
	// $[LFBCLK Setup]
	/* LFBCLK is disabled */
	// [LFBCLK Setup]$
	// $[LFECLK Setup]
	/* Select LFRCO as clock source for LFECLK */
	CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFRCO);
	// [LFECLK Setup]$
	// $[Peripheral Clock enables]
	/* Enable clock for HF peripherals */
	CMU_ClockEnable(cmuClock_HFPER, true);

	/* Enable clock for ADC0 */
	CMU_ClockEnable(cmuClock_ADC0, true);

	/* Enable clock for CRYOTIMER */
	CMU_ClockEnable(cmuClock_CRYOTIMER, true);

	/* Enable clock for GPCRC */
	CMU_ClockEnable(cmuClock_GPCRC, true);

	/* Enable clock for I2C0 */
	CMU_ClockEnable(cmuClock_I2C0, true);

	/* Enable clock for LETIMER0 */
	CMU_ClockEnable(cmuClock_LETIMER0, true);

	/* Enable clock for RTCC */
	CMU_ClockEnable(cmuClock_RTCC, true);

	/* Enable clock for TIMER0 */
	CMU_ClockEnable(cmuClock_TIMER0, true);

	/* Enable clock for TIMER1 */
	CMU_ClockEnable(cmuClock_TIMER1, true);

	/* Enable clock for USART0 */
	CMU_ClockEnable(cmuClock_USART0, true);

	/* Enable clock for USART1 */
	CMU_ClockEnable(cmuClock_USART1, true);

	/* Enable clock for GPIO by default */
	CMU_ClockEnable(cmuClock_GPIO, true);

	// [Peripheral Clock enables]$

	// $[Clock output]
	/* Disable CLKOUT0 output */
	CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_CLKOUTSEL0_MASK)
			| CMU_CTRL_CLKOUTSEL0_DISABLED;
	/* Disable CLKOUT1 output */
	CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_CLKOUTSEL1_MASK)
			| CMU_CTRL_CLKOUTSEL1_DISABLED;

	// [Clock output]$

	// $[CMU_IO]
	/* Disable CLKOUT0 pin */
	CMU->ROUTEPEN &= ~CMU_ROUTEPEN_CLKOUT0PEN;

	/* Disable CLKOUT1 pin */
	CMU->ROUTEPEN &= ~CMU_ROUTEPEN_CLKOUT1PEN;

	// [CMU_IO]$

}

//================================================================================
// ADC0_enter_DefaultMode_from_RESET
//================================================================================
extern void ADC0_enter_DefaultMode_from_RESET(void) {

	// $[ADC0_Init]
	ADC_Init_TypeDef ADC0_init = ADC_INIT_DEFAULT;

	ADC0_init.ovsRateSel = adcOvsRateSel2;
	ADC0_init.warmUpMode = adcWarmupNormal;
	ADC0_init.timebase = ADC_TimebaseCalc(0);
	ADC0_init.prescale = ADC_PrescaleCalc(7000000, 0);
	ADC0_init.tailgate = 0;
	ADC0_init.em2ClockConfig = adcEm2Disabled;

	ADC_Init(ADC0, &ADC0_init);
	// [ADC0_Init]$

	// $[ADC0_InputConfiguration]
	// [ADC0_InputConfiguration]$

}

//================================================================================
// ACMP0_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP0_enter_DefaultMode_from_RESET(void) {

	// $[ACMP0_Init]
	// [ACMP0_Init]$

	// $[ACMP0_IO]
	// [ACMP0_IO]$

}

//================================================================================
// ACMP1_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP1_enter_DefaultMode_from_RESET(void) {

	// $[ACMP1_Init]
	// [ACMP1_Init]$

	// $[ACMP1_IO]
	// [ACMP1_IO]$

}

//================================================================================
// IDAC0_enter_DefaultMode_from_RESET
//================================================================================
extern void IDAC0_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// RTCC_enter_DefaultMode_from_RESET
//================================================================================
extern void RTCC_enter_DefaultMode_from_RESET(void) {

	// $[Compare/Capture Channel 0 init]
	// [Compare/Capture Channel 0 init]$

	// $[Compare/Capture Channel 1 init]
	// [Compare/Capture Channel 1 init]$

	// $[Compare/Capture Channel 2 init]
	// [Compare/Capture Channel 2 init]$

	// $[RTCC init]
	RTCC_Init_TypeDef rtccInit = RTCC_INIT_DEFAULT;

	rtccInit.enable = true;
	rtccInit.debugRun = false;
	rtccInit.precntWrapOnCCV0 = false;
	rtccInit.cntWrapOnCCV1 = true;
	rtccInit.prescMode = rtccCntTickCCV0Match;
	rtccInit.presc = rtccCntPresc_32768;
	rtccInit.enaOSCFailDetect = false;
	rtccInit.cntMode = rtccCntModeCalendar;
	rtccInit.disLeapYearCorr = false;

	RTCC_Init(&rtccInit);
	// [RTCC init]$

}

//================================================================================
// USART0_enter_DefaultMode_from_RESET
//================================================================================
extern void USART0_enter_DefaultMode_from_RESET(void) {

	// $[USART_InitAsync]
	USART_InitAsync_TypeDef initasync = USART_INITASYNC_DEFAULT;

	initasync.enable = usartDisable;
	initasync.baudrate = 115200;
	initasync.databits = usartDatabits8;
	initasync.parity = usartNoParity;
	initasync.stopbits = usartStopbits1;
	initasync.oversampling = usartOVS16;
#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
	initasync.mvdis = 0;
	initasync.prsRxEnable = 0;
	initasync.prsRxCh = 0;
#endif

	USART_InitAsync(USART0, &initasync);
	// [USART_InitAsync]$

	// $[USART_InitSync]
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART0, &initprs);
	// [USART_InitPrsTrigger]$

	// $[USART_InitIO]
	/* Disable CLK pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_CLKLOC_MASK))
			| USART_ROUTELOC0_CLKLOC_LOC4;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CLKPEN);

	/* Disable CS pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK))
			| USART_ROUTELOC0_CSLOC_LOC3;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CSPEN);

	/* Disable CTS pin */
	USART0->ROUTELOC1 = (USART0->ROUTELOC1 & (~_USART_ROUTELOC1_CTSLOC_MASK))
			| USART_ROUTELOC1_CTSLOC_LOC2;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CTSPEN);

	/* Disable RTS pin */
	USART0->ROUTELOC1 = (USART0->ROUTELOC1 & (~_USART_ROUTELOC1_RTSLOC_MASK))
			| USART_ROUTELOC1_RTSLOC_LOC1;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_RTSPEN);

	/* Set up RX pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_RXLOC_MASK))
			| USART_ROUTELOC0_RXLOC_LOC8;
	USART0->ROUTEPEN = USART0->ROUTEPEN | USART_ROUTEPEN_RXPEN;

	/* Set up TX pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_TXLOC_MASK))
			| USART_ROUTELOC0_TXLOC_LOC10;
	USART0->ROUTEPEN = USART0->ROUTEPEN | USART_ROUTEPEN_TXPEN;

	// [USART_InitIO]$

	// $[USART_Misc]
	/* Disable CTS */
	USART0->CTRLX = USART0->CTRLX & (~USART_CTRLX_CTSEN);
	/* Set CTS active low */
	USART0->CTRLX = USART0->CTRLX & (~USART_CTRLX_CTSINV);
	/* Set RTS active low */
	USART0->CTRLX = USART0->CTRLX & (~USART_CTRLX_RTSINV);
	/* Set CS active low */
	USART0->CTRL = USART0->CTRL & (~USART_CTRL_CSINV);
	/* Set TX active high */
	USART0->CTRL = USART0->CTRL & (~USART_CTRL_TXINV);
	/* Set RX active high */
	USART0->CTRL = USART0->CTRL & (~USART_CTRL_RXINV);
	// [USART_Misc]$

	// $[USART_Enable]

	/* Enable USART if opted by user */
	USART_Enable(USART0, usartEnable);
	// [USART_Enable]$

}

//================================================================================
// USART1_enter_DefaultMode_from_RESET
//================================================================================
extern void USART1_enter_DefaultMode_from_RESET(void) {

	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	USART_InitSync_TypeDef initsync = USART_INITSYNC_DEFAULT;

	initsync.enable = usartDisable;
	initsync.baudrate = 1000000;
	initsync.databits = usartDatabits8;
	initsync.master = 1;
	initsync.msbf = 1;
	initsync.clockMode = usartClockMode0;
#if defined( USART_INPUT_RXPRS ) && defined( USART_TRIGCTRL_AUTOTXTEN )
	initsync.prsRxEnable = 0;
	initsync.prsRxCh = 0;
	initsync.autoTx = 0;
#endif

	USART_InitSync(USART1, &initsync);
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART1, &initprs);
	// [USART_InitPrsTrigger]$

	// $[USART_InitIO]
	/* Set up CLK pin */
	USART1->ROUTELOC0 = (USART1->ROUTELOC0 & (~_USART_ROUTELOC0_CLKLOC_MASK))
			| USART_ROUTELOC0_CLKLOC_LOC19;
	USART1->ROUTEPEN = USART1->ROUTEPEN | USART_ROUTEPEN_CLKPEN;

	/* Set up CS pin */
	USART1->ROUTELOC0 = (USART1->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK))
			| USART_ROUTELOC0_CSLOC_LOC3;
	USART1->ROUTEPEN = USART1->ROUTEPEN | USART_ROUTEPEN_CSPEN;

	/* Disable CTS pin */
	USART1->ROUTELOC1 = (USART1->ROUTELOC1 & (~_USART_ROUTELOC1_CTSLOC_MASK))
			| USART_ROUTELOC1_CTSLOC_LOC2;
	USART1->ROUTEPEN = USART1->ROUTEPEN & (~USART_ROUTEPEN_CTSPEN);

	/* Disable RTS pin */
	USART1->ROUTELOC1 = (USART1->ROUTELOC1 & (~_USART_ROUTELOC1_RTSLOC_MASK))
			| USART_ROUTELOC1_RTSLOC_LOC1;
	USART1->ROUTEPEN = USART1->ROUTEPEN & (~USART_ROUTEPEN_RTSPEN);

	/* Set up RX pin */
	USART1->ROUTELOC0 = (USART1->ROUTELOC0 & (~_USART_ROUTELOC0_RXLOC_MASK))
			| USART_ROUTELOC0_RXLOC_LOC21;
	USART1->ROUTEPEN = USART1->ROUTEPEN | USART_ROUTEPEN_RXPEN;

	/* Set up TX pin */
	USART1->ROUTELOC0 = (USART1->ROUTELOC0 & (~_USART_ROUTELOC0_TXLOC_MASK))
			| USART_ROUTELOC0_TXLOC_LOC23;
	USART1->ROUTEPEN = USART1->ROUTEPEN | USART_ROUTEPEN_TXPEN;

	// [USART_InitIO]$

	// $[USART_Misc]
	/* Disable CTS */
	USART1->CTRLX = USART1->CTRLX & (~USART_CTRLX_CTSEN);
	/* Set CTS active low */
	USART1->CTRLX = USART1->CTRLX & (~USART_CTRLX_CTSINV);
	/* Set RTS active low */
	USART1->CTRLX = USART1->CTRLX & (~USART_CTRLX_RTSINV);
	/* Set CS active low */
	USART1->CTRL = USART1->CTRL & (~USART_CTRL_CSINV);
	/* Set TX active high */
	USART1->CTRL = USART1->CTRL & (~USART_CTRL_TXINV);
	/* Set RX active high */
	USART1->CTRL = USART1->CTRL & (~USART_CTRL_RXINV);
	// [USART_Misc]$

	// $[USART_Enable]

	/* Enable USART if opted by user */
	USART_Enable(USART1, usartEnable);
	// [USART_Enable]$

}

//================================================================================
// LEUART0_enter_DefaultMode_from_RESET
//================================================================================
extern void LEUART0_enter_DefaultMode_from_RESET(void) {

	// $[LEUART0 initialization]
	// [LEUART0 initialization]$

}

//================================================================================
// WDOG0_enter_DefaultMode_from_RESET
//================================================================================
extern void WDOG0_enter_DefaultMode_from_RESET(void) {

	// $[WDOG Initialization]
	/*
	WDOG_Init_TypeDef wdogInit = WDOG_INIT_DEFAULT;

	wdogInit.enable = 1;
	wdogInit.debugRun = 0;
	wdogInit.em2Run = 0;
	wdogInit.em3Run = 0;
	wdogInit.em4Block = 0;
	wdogInit.swoscBlock = 0;
	wdogInit.lock = 0;
	wdogInit.clkSel = wdogClkSelULFRCO;
	wdogInit.perSel = wdogPeriod_4k;
	wdogInit.warnSel = wdogWarnTime75pct;
	wdogInit.winSel = wdogIllegalWindowTime75_0pct;
	wdogInit.resetDisable = false;

	WDOGn_Init(WDOG0, &wdogInit);
	 */
	// [WDOG Initialization]$

}

//================================================================================
// I2C0_enter_DefaultMode_from_RESET
//================================================================================
extern void I2C0_enter_DefaultMode_from_RESET(void) {

	// $[I2C0 I/O setup]
	/* Set up SCL */
	I2C0->ROUTEPEN = I2C0->ROUTEPEN | I2C_ROUTEPEN_SCLPEN;
	I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SCLLOC_MASK))
			| I2C_ROUTELOC0_SCLLOC_LOC0;
	/* Set up SDA */
	I2C0->ROUTEPEN = I2C0->ROUTEPEN | I2C_ROUTEPEN_SDAPEN;
	I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SDALOC_MASK))
			| I2C_ROUTELOC0_SDALOC_LOC0;
	// [I2C0 I/O setup]$

	// $[I2C0 initialization]
	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	init.enable = 1;
	init.master = 1;
	init.freq = I2C_FREQ_STANDARD_MAX;
	init.clhr = i2cClockHLRStandard;
	I2C_Init(I2C0, &init);
	// [I2C0 initialization]$

}

//================================================================================
// GPCRC_enter_DefaultMode_from_RESET
//================================================================================
extern void GPCRC_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// LDMA_enter_DefaultMode_from_RESET
//================================================================================
extern void LDMA_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// TIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER0_enter_DefaultMode_from_RESET(void) {

	// $[TIMER0 I/O setup]
	/* Set up CC0 */
	TIMER0->ROUTELOC0 = (TIMER0->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC0LOC_MASK))
			| TIMER_ROUTELOC0_CC0LOC_LOC0;
	TIMER0->ROUTEPEN = TIMER0->ROUTEPEN & (~TIMER_ROUTEPEN_CC0PEN);
	/* Set up CC1 */
	TIMER0->ROUTELOC0 = (TIMER0->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC1LOC_MASK))
			| TIMER_ROUTELOC0_CC1LOC_LOC0;
	TIMER0->ROUTEPEN = TIMER0->ROUTEPEN & (~TIMER_ROUTEPEN_CC1PEN);
	/* Set up CC2 */
	TIMER0->ROUTELOC0 = (TIMER0->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC2LOC_MASK))
			| TIMER_ROUTELOC0_CC2LOC_LOC4;
	TIMER0->ROUTEPEN = TIMER0->ROUTEPEN & (~TIMER_ROUTEPEN_CC2PEN);
	/* Set up CDTI0 */
	TIMER0->ROUTELOC2 = (TIMER0->ROUTELOC2 & (~_TIMER_ROUTELOC2_CDTI0LOC_MASK))
			| TIMER_ROUTELOC2_CDTI0LOC_LOC3;
	TIMER0->ROUTEPEN = TIMER0->ROUTEPEN & (~TIMER_ROUTEPEN_CDTI0PEN);
	/* Set up CDTI1 */
	TIMER0->ROUTELOC2 = (TIMER0->ROUTELOC2 & (~_TIMER_ROUTELOC2_CDTI1LOC_MASK))
			| TIMER_ROUTELOC2_CDTI1LOC_LOC2;
	TIMER0->ROUTEPEN = TIMER0->ROUTEPEN & (~TIMER_ROUTEPEN_CDTI1PEN);
	/* Set up CDTI2 */
	TIMER0->ROUTELOC2 = (TIMER0->ROUTELOC2 & (~_TIMER_ROUTELOC2_CDTI2LOC_MASK))
			| TIMER_ROUTELOC2_CDTI2LOC_LOC1;
	TIMER0->ROUTEPEN = TIMER0->ROUTEPEN & (~TIMER_ROUTEPEN_CDTI2PEN);
	// [TIMER0 I/O setup]$

	// $[TIMER0 initialization]
	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 1;
	init.debugRun = 0;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;
	init.prescale = timerPrescale1;
	init.fallAction = timerInputActionNone;
	init.riseAction = timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 0;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER0, &init);
	// [TIMER0 initialization]$

	// $[TIMER0 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = false;
	initCC0.prsSel = timerPRSSELCh0;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModeOff;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER0, 0, &initCC0);
	// [TIMER0 CC0 init]$

	// $[TIMER0 CC1 init]
	TIMER_InitCC_TypeDef initCC1 = TIMER_INITCC_DEFAULT;

	initCC1.prsInput = false;
	initCC1.prsSel = timerPRSSELCh0;
	initCC1.edge = timerEdgeRising;
	initCC1.mode = timerCCModeOff;
	initCC1.eventCtrl = timerEventEveryEdge;
	initCC1.filter = 0;
	initCC1.cofoa = timerOutputActionNone;
	initCC1.cufoa = timerOutputActionNone;
	initCC1.cmoa = timerOutputActionNone;
	initCC1.coist = 0;
	initCC1.outInvert = 0;
	TIMER_InitCC(TIMER0, 1, &initCC1);
	// [TIMER0 CC1 init]$

	// $[TIMER0 CC2 init]
	TIMER_InitCC_TypeDef initCC2 = TIMER_INITCC_DEFAULT;

	initCC2.prsInput = false;
	initCC2.prsSel = timerPRSSELCh0;
	initCC2.edge = timerEdgeRising;
	initCC2.mode = timerCCModeOff;
	initCC2.eventCtrl = timerEventEveryEdge;
	initCC2.filter = 0;
	initCC2.cofoa = timerOutputActionNone;
	initCC2.cufoa = timerOutputActionNone;
	initCC2.cmoa = timerOutputActionNone;
	initCC2.coist = 0;
	initCC2.outInvert = 0;
	TIMER_InitCC(TIMER0, 2, &initCC2);
	// [TIMER0 CC2 init]$

	// $[TIMER0 DTI init]
	TIMER_InitDTI_TypeDef initDTI = TIMER_INITDTI_DEFAULT;

	initDTI.enable = 0;
	initDTI.activeLowOut = 0;
	initDTI.invertComplementaryOut = 0;
	initDTI.autoRestart = 0;
	initDTI.enablePrsSource = 0;
	initDTI.prsSel = timerPRSSELCh0;
	initDTI.prescale = timerPrescale1;
	initDTI.riseTime = 1;
	initDTI.fallTime = 1;
	initDTI.enableFaultSourceCoreLockup = 1;
	initDTI.enableFaultSourceDebugger = 1;
	initDTI.faultSourcePrsSel0 = 0;
	initDTI.faultSourcePrsSel0 = timerPRSSELCh0;
	initDTI.faultSourcePrsSel1 = 0;
	initDTI.faultSourcePrsSel1 = timerPRSSELCh0;
	initDTI.faultAction = timerDtiFaultActionInactive;
	initDTI.outputsEnableMask = 0;
	TIMER_InitDTI(TIMER0, &initDTI);
	// [TIMER0 DTI init]$

}

//================================================================================
// TIMER1_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER1_enter_DefaultMode_from_RESET(void) {

	// $[TIMER1 I/O setup]
	/* Set up CC0 */
	TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC0LOC_MASK))
			| TIMER_ROUTELOC0_CC0LOC_LOC0;
	TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC0PEN);
	/* Set up CC1 */
	TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC1LOC_MASK))
			| TIMER_ROUTELOC0_CC1LOC_LOC0;
	TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC1PEN);
	/* Set up CC2 */
	TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC2LOC_MASK))
			| TIMER_ROUTELOC0_CC2LOC_LOC4;
	TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC2PEN);
	/* Set up CC3 */
	TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC3LOC_MASK))
			| TIMER_ROUTELOC0_CC3LOC_LOC3;
	TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC3PEN);
	// [TIMER1 I/O setup]$

	// $[TIMER1 initialization]
	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 1;
	init.debugRun = 0;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;
	init.prescale = timerPrescale1;
	init.fallAction = timerInputActionNone;
	init.riseAction = timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 0;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER1, &init);
	// [TIMER1 initialization]$

	// $[TIMER1 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = false;
	initCC0.prsSel = timerPRSSELCh0;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModeOff;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER1, 0, &initCC0);
	// [TIMER1 CC0 init]$

	// $[TIMER1 CC1 init]
	TIMER_InitCC_TypeDef initCC1 = TIMER_INITCC_DEFAULT;

	initCC1.prsInput = false;
	initCC1.prsSel = timerPRSSELCh0;
	initCC1.edge = timerEdgeRising;
	initCC1.mode = timerCCModeOff;
	initCC1.eventCtrl = timerEventEveryEdge;
	initCC1.filter = 0;
	initCC1.cofoa = timerOutputActionNone;
	initCC1.cufoa = timerOutputActionNone;
	initCC1.cmoa = timerOutputActionNone;
	initCC1.coist = 0;
	initCC1.outInvert = 0;
	TIMER_InitCC(TIMER1, 1, &initCC1);
	// [TIMER1 CC1 init]$

	// $[TIMER1 CC2 init]
	TIMER_InitCC_TypeDef initCC2 = TIMER_INITCC_DEFAULT;

	initCC2.prsInput = false;
	initCC2.prsSel = timerPRSSELCh0;
	initCC2.edge = timerEdgeRising;
	initCC2.mode = timerCCModeOff;
	initCC2.eventCtrl = timerEventEveryEdge;
	initCC2.filter = 0;
	initCC2.cofoa = timerOutputActionNone;
	initCC2.cufoa = timerOutputActionNone;
	initCC2.cmoa = timerOutputActionNone;
	initCC2.coist = 0;
	initCC2.outInvert = 0;
	TIMER_InitCC(TIMER1, 2, &initCC2);
	// [TIMER1 CC2 init]$

	// $[TIMER1 CC3 init]
	TIMER_InitCC_TypeDef initCC3 = TIMER_INITCC_DEFAULT;

	initCC3.prsInput = false;
	initCC3.prsSel = timerPRSSELCh0;
	initCC3.edge = timerEdgeRising;
	initCC3.mode = timerCCModeOff;
	initCC3.eventCtrl = timerEventEveryEdge;
	initCC3.filter = 0;
	initCC3.cofoa = timerOutputActionNone;
	initCC3.cufoa = timerOutputActionNone;
	initCC3.cmoa = timerOutputActionNone;
	initCC3.coist = 0;
	initCC3.outInvert = 0;
	TIMER_InitCC(TIMER1, 3, &initCC3);
	// [TIMER1 CC3 init]$

}

//================================================================================
// LETIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void LETIMER0_enter_DefaultMode_from_RESET(void) {

	// $[LETIMER0 Compare Values]
	// [LETIMER0 Compare Values]$

	// $[LETIMER0 Repeat Values]
	// [LETIMER0 Repeat Values]$

	// $[LETIMER0 Initialization]
	LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;

	letimerInit.enable = true;
	letimerInit.debugRun = false;
	letimerInit.comp0Top = true;
	letimerInit.bufTop = false;
	letimerInit.out0Pol = 0;
	letimerInit.out1Pol = 0;
	letimerInit.ufoa0 = letimerUFOAPwm;
	letimerInit.ufoa1 = letimerUFOANone;
	letimerInit.repMode = letimerRepeatFree;

	LETIMER_Init(LETIMER0, &letimerInit);
	// [LETIMER0 Initialization]$

	// $[LETIMER0 PRS Input Triggers]
	/* Don't start timer on PRS input */

	/* Don't stop timer on PRS input */

	/* Don't clear timer on PRS input */

	// [LETIMER0 PRS Input Triggers]$
	// $[LETIMER0 I/O setup]
	/* Disable OUT0 pin */
	LETIMER0->ROUTEPEN &= ~LETIMER_ROUTEPEN_OUT0PEN;

	/* Disable OUT1 pin */
	LETIMER0->ROUTEPEN &= ~LETIMER_ROUTEPEN_OUT1PEN;

	// [LETIMER0 I/O setup]$

}

//================================================================================
// CRYOTIMER_enter_DefaultMode_from_RESET
//================================================================================
extern void CRYOTIMER_enter_DefaultMode_from_RESET(void) {

	// $[CRYOTIMER_Init]
	CRYOTIMER_Init_TypeDef cryoInit = CRYOTIMER_INIT_DEFAULT;

	/* General settings */
	cryoInit.enable = 1;
	cryoInit.debugRun = 0;
	cryoInit.em4Wakeup = 1;

	/* Clocking settings */
	/* With a frequency of 32768Hz on LFRCO, this will result in a 1000.00 ms timeout */
	cryoInit.osc = cryotimerOscLFRCO;
	cryoInit.presc = cryotimerPresc_1;
	cryoInit.period = cryotimerPeriod_32k;
	CRYOTIMER_Init(&cryoInit);
	// [CRYOTIMER_Init]$

}

//================================================================================
// PCNT0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT0_enter_DefaultMode_from_RESET(void) {

	// $[PCNT0 I/O setup]
	// [PCNT0 I/O setup]$

	// $[PCNT0 initialization]
	// [PCNT0 initialization]$

}

//================================================================================
// PRS_enter_DefaultMode_from_RESET
//================================================================================
extern void PRS_enter_DefaultMode_from_RESET(void) {

	// $[PRS initialization]
	// [PRS initialization]$

}

//================================================================================
// PORTIO_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTIO_enter_DefaultMode_from_RESET(void) {

    // $[Port A Configuration]
    // [Port A Configuration]$

    // $[Port B Configuration]

    /* Pin PB11 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortB, 11, gpioModePushPull, 0);

    /* Pin PB14 is configured to Input enabled */
    GPIO_PinModeSet(gpioPortB, 14, gpioModeInput, 0);

    /* Pin PB15 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 0);
    // [Port B Configuration]$

    // $[Port C Configuration]

    /* Pin PC10 is configured to Input enabled with pull-up */
    GPIO_PinModeSet(gpioPortC, 10, gpioModeInputPull, 1);
    // [Port C Configuration]$

    // $[Port D Configuration]

    /* Pin PD13 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 0);

    /* Pin PD14 is configured to Input enabled */
    GPIO_PinModeSet(gpioPortD, 14, gpioModeInput, 0);

    /* Pin PD15 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortD, 15, gpioModePushPull, 0);
    // [Port D Configuration]$

    // $[Port E Configuration]
    // [Port E Configuration]$

    // $[Port F Configuration]
    // [Port F Configuration]$

}

