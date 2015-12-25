#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"



#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"
#include "Gtm\Std\IfxGtm.h"
#include "Gtm\Std\IfxGtm_Atom.h"
#include "Gtm\Std\IfxGtm_Tom.h"
#include "Gtm\Std\IfxGtm_Tim.h"
#include "Gtm\Tom\Timer\IfxGtm_Tom_Timer.h"
#include "Gtm\Tom\PwmHl\IfxGtm_Tom_PwmHl.h"
#include "Gtm\Trig\IfxGtm_Trig.h"
#include "IfxGtm_PinMap.h"
//#include "DemoApp.h


#define STM0_TICK_PERIOD_IN_MICROSECONDS 1000
#define IFX_CFG_ISR_PRIORITY_STM0_COMPARE0	10 /**< \brief Stm0 Compare 0 interrupt priority.  */
unsigned char Data_pointer = 0;
uint32 stm0CompareValue;
unsigned int Data_array[100];
uint32 Update_flag = 0;
uint32 Up_Down_flag = 0;
float32 PwmFrequency;
uint32 PwmPeriod;
uint32 PwmDuty;
IfxGtm_Cmu_Clk PwmGtmCmuClk = IfxGtm_Cmu_Clk_0;




App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
unsigned long  lock=1; // 1 means available,
unsigned long mask=1;

//SYSCON
//unsigned int CPU_SYSCON_Temp;

uint32 core0_switch_context_count_test;

extern  uint32 _lc_ue_ustack_tc0[];  /* user stack end */

volatile uint32 ustack_end_address=(uint32)(_lc_ue_ustack_tc0);
volatile uint32 ustack_used_size_in_byte;
volatile uint32 ustack_address;

volatile uint32 tick_begin;
volatile uint32 tick_end;
volatile uint32 ticks_in_10ns;

 void test_ustack(void)
{
   ustack_address            = (unsigned int)__getUstack();
   ustack_used_size_in_byte  = ustack_end_address - ustack_address;
}
 int math_test;

 int math1(int a,int b,int c,int d,int e ,int f,int g);
 int math2(int a,int b,int c,int d,int e ,int f,int g);
 int math3(int a,int b,int c,int d,int e ,int f,int g);
 int math1(int a,int b,int c,int d,int e ,int f,int g)
 {

    int a1=1;
    int b1=2;
    int c1=3;
    int d1=4;
    int e1=5;
    int f1=6;
    int g1=7;
    int total;

    a1=a1+a;
    b1=b1+b;
    c1=c1+c;
    d1=d1+d;
    e1=e1+e;
    f1=f1+f;
    g1=g1+g;

    total=a1+b1*2+c1+d1*6+d1+f1+g1+e1*4+2;

    math_test=math2(7,6,5,4,3,2,1);
    test_ustack();

    return total;
 }

 int math2(int a,int b,int c,int d,int e ,int f,int g)
 {

    int a1=1;
    int b1=2;
    int c1=3;
    int d1=4;
    int e1=5;
    int f1=6;
    int g1=7;
    int total;

    a1=a1+a;
    b1=b1+b;
    c1=c1+c;
    d1=d1+d;
    e1=e1+e;
    f1=f1+f;
    g1=g1+g;

    total=a1+b1*2+c1+d1*6+d1+f1+g1+e1*4+2;

    math_test=math3(7,6,5,4,3,2,1);
    //test_ustack();

    return total;
 }
 int math3(int a,int b,int c,int d,int e ,int f,int g)
 {

    int a1=1;
    int b1=2;
    int c1=3;
    int d1=4;
    int e1=5;
    int f1=6;
    int g1=7;
    int total;

    a1=a1+a;
    b1=b1+b;
    c1=c1+c;
    d1=d1+d;
    e1=e1+e;
    f1=f1+f;
    g1=g1+g;

    total=a1+b1*2+c1+d1*6+d1+f1+g1+e1*4+2;

    //math_test=math3(7,6,5,4,3,2,1);
    test_ustack();

    return total;
 }
int core0_main (void)
{


	// Enable memory protection
	//CPU_SYSCON_Temp = __mfcr(CPU_SYSCON);
	//CPU_SYSCON_Temp = CPU_SYSCON_Temp|(1<<1);
	//__mtcr(CPU_SYSCON,CPU_SYSCON_Temp);


    /*
     * !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdog in the demo if it is required and also service the watchdog periodically
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
    IfxScuWdt_disableSafetyWatchdog (IfxScuWdt_getSafetyWatchdogPassword ());

    /* Initialise the application state */
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreId());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    /* Enable the global interrupts of this CPU */
    IfxCpu_enableInterrupts();

    /* Demo init */
    // configure P33.8 as general output
    IfxPort_setPinMode(&MODULE_P33, 8,  IfxPort_Mode_outputPushPullGeneral);
    // configure P33.9 as general output
    IfxPort_setPinMode(&MODULE_P33, 9,  IfxPort_Mode_outputPushPullGeneral);

    IfxPort_setPinMode(&MODULE_P33, 10,  IfxPort_Mode_outputPushPullGeneral);
    // configure P33.9 as general output
    IfxPort_setPinMode(&MODULE_P33, 11,  IfxPort_Mode_outputPushPullGeneral);

    /* background endless loop */

    //math1(7,6,5,4,3,2,1);
    //while (1)
    {
    	//synchronizeCore0Core1();
    	//communicationCore0Core1_ptr->core0Ready = 1;
    	//IfxPort_togglePin(&MODULE_P33, 8);
    	//IfxPort_togglePin(&MODULE_P33, 9);
    	//IfxPort_togglePin(&MODULE_P33, 10);
    	//IfxPort_togglePin(&MODULE_P33, 11);
    	//IfxStm_waitTicks(&MODULE_STM0, g_AppCpu0.info.stmFreq/1000000);
    	//communicationCore0Core1_ptr->core0Ready = 0;
    	//IfxStm_waitTicks(&MODULE_STM0, g_AppCpu0.info.stmFreq/100);
    }

   // while(lock==0) requestLock(&lock, mask);
   // for(i=0;i<1000;i++)
    while(1)
    {
       //IfxPort_togglePin(&MODULE_P33, 8);
       //IfxPort_togglePin(&MODULE_P33, 9);

      // test_fun_share();
      // IfxStm_waitTicks(&MODULE_STM0, g_AppCpu0.info.stmFreq/100);
    }
    //releaseLock(&lock, mask);

    while(1);
    return (1);
}
//#pragma code_core_association  private1

void STM_Demo_init(void)
{
	/* Initialize STM for the triggers*/
	IfxStm_CompareConfig stmCompareConfig;

    // configure P33.8 as general output
    IfxPort_setPinMode(&MODULE_P33, 8,  IfxPort_Mode_outputPushPullGeneral);

    /* Calculate the compare value of STM0 */
	stm0CompareValue = IfxStm_getFrequency(&MODULE_STM0) / STM0_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM0);

	/* Configure interrupt service requests for STM trigger outputs */
	//IfxSrc_init(&MODULE_SRC.STM[0].SR[0], IfxSrc_Tos_cpu0, IFX_CFG_ISR_PRIORITY_STM0_COMPARE0);
	//IfxSrc_enable(&MODULE_SRC.STM[0].SR[0]);
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu0;

	/* Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = stm0CompareValue;   /*Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = IFX_CFG_ISR_PRIORITY_STM0_COMPARE0;

	/* Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM0, &stmCompareConfig);

}
IFX_INTERRUPT(Ifx_STM0_Isr,0,IFX_CFG_ISR_PRIORITY_STM0_COMPARE0)
{
    uint32 stmTicks;
    stmTicks= (uint32)(stm0CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + stmTicks);
    IfxPort_togglePin(&MODULE_P33, 8);
    Data_pointer++;
    if(Data_pointer == 100) Data_pointer = 0;
    Data_array[Data_pointer] = MODULE_STM0.TIM0.U;
    __enable ();
    if(Update_flag==1){
    	if(Up_Down_flag == 1){
    		PwmFrequency-=10;
    	}else{
    		PwmFrequency+=10;
    	}

    	if(PwmFrequency != 0){
    	    PwmPeriod = (uint32)(IfxGtm_Cmu_getClkFrequency(&MODULE_GTM, PwmGtmCmuClk, FALSE) / PwmFrequency);
    	    PwmDuty = (PwmPeriod * 30) / 100;
    	}else{
    	    	PwmPeriod = 0x100;
    	    	PwmDuty = 0x0;
    	}

    	/*
    	if(Up_Down_flag == 1){
    		PwmPeriod-=100;
    	}else{
    		PwmPeriod+=100;
    	}
    	*/
    	//PwmDuty+=100;
    	if(PwmFrequency >= 20000) Up_Down_flag = 1;
    	if(PwmFrequency <= 50) Up_Down_flag = 0;

    	//PwmPeriod+=100;
    	//if(PwmFrequecncy>= 200000) PwmFrequency = 100000;
    	//IfxGtm_Atom_Ch_setCompareShadow(PwmGTMATOM, PwmGtmAtomCh, PwmPeriod, PwmDuty);
    }
    //CounterTick(IFX_OSTASK_COUNTER);
}


