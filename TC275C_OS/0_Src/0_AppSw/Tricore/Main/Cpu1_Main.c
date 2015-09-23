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

/**********************************************************************************
 *
 *
 *   Core1 main function
 *
 *
 *
 *********************************************************************************/



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

  
   start_core1_os();
   
   while(1)
   {
     // for(i=0;i<1000;i++)
    //  {
       //IfxPort_togglePin(&MODULE_P02, 1);
       //IfxStm_waitTicks(&MODULE_STM1, g_AppCpu0.info.stmFreq/100);
     // }
       IfxPort_togglePin(&MODULE_P33, 10);
       IfxStm_waitTicks(&MODULE_STM0, 20000000);
      //releaseLock(&lock, mask);
   }
    return (1);
}
