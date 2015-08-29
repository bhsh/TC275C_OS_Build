#include "Cpu\Std\Ifx_Types.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Scu\Std\IfxScuWdt.h"
#include "Port/Std/IfxPort.h"
#include "communication.h"
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"

extern unsigned long lock;
extern unsigned long mask;

#pragma section nearbss "zbss_cpu0"
#pragma section neardata "zdata_cpu0"

 unsigned char core1_test;
 unsigned long core1_test2;

#pragma section nearbss "zbss_cpu1"
#pragma section neardata "zdata_cpu1"

 unsigned char core1_test3;
 unsigned long core1_test4;

#pragma section nearbss "zbss_cpu2"
#pragma section neardata "zdata_cpu2"

 unsigned char core1_test5;
 unsigned long core1_test6;

//#pragma section nearbss restore

extern App_Cpu0 g_AppCpu0;
//extern float32  g_AppCpu3;

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

   //while (1)
    {
    	//synchronizeCore0Core1();
    	//IfxPort_togglePin(&MODULE_P02, 1);
    }

   // while(lock== 0) requestLock(&lock, mask);
   while(1)
   {
     // for(i=0;i<1000;i++)
    //  {
       //IfxPort_togglePin(&MODULE_P02, 1);
       //IfxStm_waitTicks(&MODULE_STM1, g_AppCpu0.info.stmFreq/100);
     // }
       //IfxPort_togglePin(&MODULE_P33, 10);
       IfxStm_waitTicks(&MODULE_STM0, 20000000);
      //releaseLock(&lock, mask);
   }
    return (1);
}
