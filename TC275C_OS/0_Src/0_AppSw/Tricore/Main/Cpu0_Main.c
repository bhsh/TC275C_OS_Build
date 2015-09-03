#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"



#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

#include "os_kernel.h"

#define STM0_TICK_PERIOD_IN_MICROSECONDS    1000
#define STM1_TICK_PERIOD_IN_MICROSECONDS    1000
#define STM2_TICK_PERIOD_IN_MICROSECONDS    1000

#define IFX_CFG_ISR_PRIORITY_STM0_COMPARE0	10   /**< \brief Stm0 Compare 0 interrupt priority.  */
#define IFX_CFG_ISR_PRIORITY_STM1_COMPARE0	11   /**< \brief Stm1 Compare 0 interrupt priority.  */
#define IFX_CFG_ISR_PRIORITY_STM2_COMPARE0	12   /**< \brief Stm2 Compare 0 interrupt priority.  */

uint32 stm0CompareValue;
uint32 stm1CompareValue;
uint32 stm2CompareValue;

App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
unsigned long  lock=1; // 1 means available,
unsigned long mask=1;


extern uint32_t pthread_runnable;
//! Currently running thread
extern pthread_t pthread_running;
//! Array of linked lists which holds runnable threads
extern pthread_t pthread_runnable_threads[PTHREAD_PRIO_MAX];

pthread_t pthread_running_testp;
uint32_t pthread_running_test;
int m=0;
extern pthread_t thread_1;
extern pthread_t thread_2;
pthread_t pthread_running_test2;
 void stm_src0(void) {

    pthread_t thread;
    uint32 stmTicks;

    pthread_running->lcx = __mfcr(CPU_PCXI);
    //pthread_running_test=__mfcr(CPU_PCXI);
    thread = pthread_running->next; // get next thread with same priority
    //pthread_running_test2=pthread_running;
    pthread_runnable_threads[thread->priority] = thread;

    pthread_running = thread;

    stmTicks= (uint32)(stm0CompareValue*10);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + stmTicks);
    IfxPort_togglePin(&MODULE_P33, 10);

#if 0
  if(m==0)
  {
    thread_2->lcx=__mfcr(CPU_PCXI);
    thread=thread_1;
    m=1;
  }
  else
  {
	thread_1->lcx=__mfcr(CPU_PCXI);
	thread=thread_2;
	m=0;
  }
#endif

    __dsync(); // required before PCXI manipulation (see RTOS porting guide)
    __mtcr(CPU_PCXI, thread->lcx);
    __asm("ji a11");

}
/**********************************************************************************
 *
 *
 *   STM0 initialization and interrupt
 *
 *
 *
 *********************************************************************************/


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

	//__svlcx();
	//__isync();
	//stm_src0();
	/* we restore the lower context, this could be form any task or our saved from entry */
	//__rslcx();
	//__isync();
	/* we don't was calling here we must return with rfe */
	//__asm ( "rfe" );
    __asm(  " svlcx          \n"
            " jla   stm_src0 \n"
  		    " rslcx"::"a"(pthread_running->next));

#if 0
      __asm( " svlcx   \t");
      __asm( " jla\t %0" : : "a" (stm_src0));
      __asm( " rslcx \t");
      __asm( " rfe");
#endif
}
/**********************************************************************************
 *
 *
 *   STM1 initialization and interrupt
 *
 *
 *
 *********************************************************************************/
void STM1_Demo_init(void)
{
	/* Initialize STM for the triggers*/
	IfxStm_CompareConfig stmCompareConfig;

    // configure P33.8 as general output
    IfxPort_setPinMode(&MODULE_P33, 9,  IfxPort_Mode_outputPushPullGeneral);

    /* Calculate the compare value of STM0 */
	stm1CompareValue = IfxStm_getFrequency(&MODULE_STM1) / STM1_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM1);

	/* Configure interrupt service requests for STM trigger outputs */
	//IfxSrc_init(&MODULE_SRC.STM[0].SR[0], IfxSrc_Tos_cpu0, IFX_CFG_ISR_PRIORITY_STM0_COMPARE0);
	//IfxSrc_enable(&MODULE_SRC.STM[0].SR[0]);
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu1;

	/* Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = stm1CompareValue;   /*Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = IFX_CFG_ISR_PRIORITY_STM1_COMPARE0;

	/* Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM1, &stmCompareConfig);

}

IFX_INTERRUPT(Ifx_STM1_Isr,0,IFX_CFG_ISR_PRIORITY_STM1_COMPARE0)
{
    uint32 stmTicks;
    stmTicks= (uint32)(stm1CompareValue * 100);
    IfxStm_updateCompare (&MODULE_STM1, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM1, IfxStm_Comparator_0) + stmTicks);
    //IfxPort_togglePin(&MODULE_P33, 9);
}

/**********************************************************************************
 *
 *
 *   STM2 initialization and interrupt
 *
 *
 *
 *********************************************************************************/
void STM2_Demo_init(void)
{
	/* Initialize STM for the triggers*/
	IfxStm_CompareConfig stmCompareConfig;

    // configure P33.8 as general output
    IfxPort_setPinMode(&MODULE_P33, 10,  IfxPort_Mode_outputPushPullGeneral);

    /* Calculate the compare value of STM0 */
	stm2CompareValue = IfxStm_getFrequency(&MODULE_STM2) / STM2_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM2);

	/* Configure interrupt service requests for STM trigger outputs */
	//IfxSrc_init(&MODULE_SRC.STM[0].SR[0], IfxSrc_Tos_cpu0, IFX_CFG_ISR_PRIORITY_STM0_COMPARE0);
	//IfxSrc_enable(&MODULE_SRC.STM[0].SR[0]);
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu2;

	/* Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = stm2CompareValue;   /*Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = IFX_CFG_ISR_PRIORITY_STM2_COMPARE0;

	/* Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM2, &stmCompareConfig);

}

IFX_INTERRUPT(Ifx_STM2_Isr,0,IFX_CFG_ISR_PRIORITY_STM2_COMPARE0)
{
    uint32 stmTicks;
    stmTicks= (uint32)(stm0CompareValue * 100);
    IfxStm_updateCompare (&MODULE_STM2, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM2, IfxStm_Comparator_0) + stmTicks);
    //IfxPort_togglePin(&MODULE_P33, 10);
}

/**********************************************************************************
 *
 *
 *   Core0 main function
 *
 *
 *
 *********************************************************************************/
uint32 core0_switch_context_count_test;
int core0_main (void)
{
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

    //STM_Demo_init();
    //STM1_Demo_init();
    //STM2_Demo_init();

    /* Enable the global interrupts of this CPU */
    //IfxCpu_enableInterrupts();

    /* Demo init */
    // configure P33.8 as general output
    IfxPort_setPinMode(&MODULE_P33, 8,  IfxPort_Mode_outputPushPullGeneral);
     //configure P33.9 as general output
    IfxPort_setPinMode(&MODULE_P33, 9,  IfxPort_Mode_outputPushPullGeneral);

    IfxPort_setPinMode(&MODULE_P33, 10,  IfxPort_Mode_outputPushPullGeneral);
    // configure P33.9 as general output
    IfxPort_setPinMode(&MODULE_P33, 11,  IfxPort_Mode_outputPushPullGeneral);

    /* background endless loop */
    start_core0_os();

    while (1)
    {
    	//synchronizeCore0Core1();
    	//communicationCore0Core1_ptr->core0Ready = 1;
    	//IfxPort_togglePin(&MODULE_P33, 8);
    	//IfxPort_togglePin(&MODULE_P33, 9);
    	//IfxPort_togglePin(&MODULE_P33, 10);
    	//IfxPort_togglePin(&MODULE_P33, 11);
    	switch_context();
    	core0_switch_context_count_test++;
        IfxStm_waitTicks(&MODULE_STM0, 10000000);

    	//IfxStm_waitTicks(&MODULE_STM0, g_AppCpu0.info.stmFreq/1000000);
    	//communicationCore0Core1_ptr->core0Ready = 0;
    	//IfxStm_waitTicks(&MODULE_STM0, g_AppCpu0.info.stmFreq/100);
    }

   // while(lock==0) requestLock(&lock, mask);
   // for(i=0;i<1000;i++)
#if 0
    while(1)
    {
       //IfxPort_togglePin(&MODULE_P33, 8);
       //IfxPort_togglePin(&MODULE_P33, 9);

      // IfxStm_waitTicks(&MODULE_STM0, g_AppCpu0.info.stmFreq/100);
    }
    //releaseLock(&lock, mask);
#endif

    return (1);
}



