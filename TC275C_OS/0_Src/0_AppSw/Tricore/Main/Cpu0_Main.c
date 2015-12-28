#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
#include "communication.h"

#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

void test_func(void);
void STM_Demo_init(void);
int math1(int a,int b,int c,int d,int e ,int f,int g);
int math2(int a,int b,int c,int d,int e ,int f,int g);
int math3(int a,int b,int c,int d,int e ,int f,int g);

#define STM0_TICK_PERIOD_IN_MICROSECONDS 1000
#define IFX_CFG_ISR_PRIORITY_STM0_COMPARE0	10 /**< \brief Stm0 Compare 0 interrupt priority.  */
uint32 stm0CompareValue;
App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
unsigned long  lock=1; // 1 means available,
unsigned long mask=1;

extern  uint32 _lc_ue_ustack_tc0[];  /* user stack end */
volatile uint32 ustack_end_address=(uint32)(_lc_ue_ustack_tc0);
volatile uint32 ustack_used_size_in_byte;
volatile uint32 ustack_address;
volatile uint32 tick_begin;
volatile uint32 tick_end;
volatile uint32 ticks_in_10ns;
int math_test;

#define NUM 5
volatile unsigned int test_count[NUM];

 void test_ustack(void)
{
   ustack_address            = (unsigned int)__getUstack();
   ustack_used_size_in_byte  = ustack_end_address - ustack_address;
}
 
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

    return total;
 }

void test_func(void)
{  
   unsigned int temp_count1[NUM];
   unsigned int temp_count2[NUM];
   unsigned int i,j,k;

   for(i=0;i<NUM;i++)
   {
     temp_count1[i] = 0;
     temp_count2[i] = 0;
   }
   for(j=0;j<NUM;j++)
   {
     temp_count1[j] = 5+j;
	 temp_count2[j] = 3+j;
   }
   for(k=0;k<NUM;k++)
   {
	 temp_count2[k] = 2*temp_count1[k] + temp_count2[k]-1;
   }
   for(k=0;k<NUM;k++)
   {
	 test_count[k] = 2*temp_count2[k]-1;
   }
   test_ustack();
}

volatile unsigned int temp_buffer;
int core0_main (void)
{
	// enable memory protection to avoid SRI interrupt on speculative fetch in case we go to sleep
	// we execute code only from flash (segment 8) and PSPRx (segment C)
	__mtcr (CPU_CPR0_U, 0xC0006000);
	__mtcr (CPU_CPR0_L, 0xC0000000);
	__mtcr (CPU_CPR0_U, 0xA0400000);
    __mtcr (CPU_CPR0_L, 0xA0000000);
	__mtcr (CPU_CPR1_U, 0x80400000);
	__mtcr (CPU_CPR1_L, 0x80000000);

	__mtcr (CPU_CPXE0, 0x00000007);
	
	// data access from/to pflash (segment 8 and A), data access from/to dflash0 (segment A), DSPRx (segment D), LMURAM/EDRAM (segment B)and peripherals (segment F)
	__mtcr (CPU_DPR0_U, 0x80400000);
	__mtcr (CPU_DPR0_L, 0x80000000);
	__mtcr (CPU_DPR1_U, 0xA0400000);
    __mtcr (CPU_DPR1_L, 0xA0000000);
	__mtcr (CPU_DPR2_U, 0xAF104000);
	__mtcr (CPU_DPR2_L, 0xAF000000);
	__mtcr (CPU_DPR3_U, 0xD001F000);
	__mtcr (CPU_DPR3_L, 0xD0000000);
	__mtcr (CPU_DPR4_U, 0xBF100000);
	__mtcr (CPU_DPR4_L, 0xB0000000);
	__mtcr (CPU_DPR5_U, 0xFFFFFFFF);
	__mtcr (CPU_DPR5_L, 0xF0000000);
	__mtcr (CPU_DPR6_U, 0x6001F000);
	__mtcr (CPU_DPR6_L, 0x60000000);
	__mtcr (CPU_DPR7_U, 0x5001F000);
	__mtcr (CPU_DPR7_L, 0x50000000);

	__mtcr (CPU_DPR8_U, 0x7001F000);
	__mtcr (CPU_DPR8_L, 0x7001b7c0);
	
	// The csa section can't be entered by CPU after the csa is initialized
	__mtcr (CPU_DPR9_U, 0x7001b7c0);
	__mtcr (CPU_DPR9_L, 0x700197c0);

	__mtcr (CPU_DPR10_U, 0x700197c0);
	__mtcr (CPU_DPR10_L, 0x70000000);

	__mtcr (CPU_DPRE0, 0x000005FF);
	__mtcr (CPU_DPWE0, 0x000005FF);
	//enable memory protection
	__mtcr (CPU_SYSCON, 0x2);
	__dsync ();

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

    STM_Demo_init();
	
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
    //*((unsigned int *)(0x7001b7b0)) = 7;
	temp_buffer = *((unsigned int *)(0x7001b7b0));
	
    while (1)
    {
	  test_func();
    }
    return (1);
}

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
    stmTicks= (uint32)(stm0CompareValue * 100);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + stmTicks);
    IfxPort_togglePin(&MODULE_P33, 8);
	math1(7,6,5,4,3,2,1);
}


