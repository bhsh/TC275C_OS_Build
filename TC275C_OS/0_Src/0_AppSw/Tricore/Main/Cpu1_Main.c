#include "Cpu\Std\Ifx_Types.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Scu\Std\IfxScuWdt.h"
#include "Port/Std/IfxPort.h"
#include "communication.h"
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"


#include "os_kernel.h"

extern unsigned long lock;
extern unsigned long mask;
extern App_Cpu0 g_AppCpu0;

extern App_Cpu0 g_AppCpu1; /**< \brief CPU 0 global data */

/**********************************************************************************
 *
 *
 *   Core1 main function
 *
 *
 *
 *********************************************************************************/

volatile uint32 core1_tick_begin;
volatile uint32 core1_tick_end;
volatile uint32 core1_ticks_in_10ns;

int core1_main (void)
{
	//test_fun();
	//test_fun3();
//	g_AppCpu3++;
    __enable ();
    /*
     * !!WATCHDOG1 IS DISABLED HERE!!
     * Enable the watchdog in the demo if it is required and also service the watchdog periodically
     * */
   IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());

   g_AppCpu1.info.pllFreq = IfxScuCcu_getPllFrequency();
   g_AppCpu1.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreId());
   g_AppCpu1.info.sysFreq = IfxScuCcu_getSpbFrequency();
   g_AppCpu1.info.stmFreq = IfxStm_getFrequency(&MODULE_STM1);

  
   //start_core1_os();
   
   while(1)
   {
     // for(i=0;i<1000;i++)
    //  {
       //IfxPort_togglePin(&MODULE_P02, 1);
       //IfxStm_waitTicks(&MODULE_STM1, g_AppCpu0.info.stmFreq/100);
     // }
       while(0!=getMutex()){};  

       core1_tick_begin=IfxStm_getLower(&MODULE_STM0);

       core1_global_count1++;
	   core0_global_count1++;
	   IfxPort_togglePin(&MODULE_P33, 9);
       IfxStm_waitTicks(&MODULE_STM0, 50000000);
	   
	   core1_ticks_in_10ns=IfxStm_getLower(&MODULE_STM0)-core1_tick_begin;

	   returnMutex();
      //releaseLock(&lock, mask);
   }
    return (1);
}
