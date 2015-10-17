#include "Cpu\Std\Ifx_Types.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Scu\Std\IfxScuWdt.h"
#include "Port/Std/IfxPort.h"
#include "communication.h"
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"

/**********************************************************************************
 *
 *
 *   Core2 main function
 *
 *
 *
 *********************************************************************************/
extern App_Cpu0 g_AppCpu2; /**< \brief CPU 0 global data */
int core2_main (void)
{
    __enable ();
    /*
     * !!WATCHDOG2 IS DISABLED HERE!!
     * Enable the watchdog in the demo if it is required and also service the watchdog periodically
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());

	g_AppCpu2.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu2.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreId());
    g_AppCpu2.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu2.info.stmFreq = IfxStm_getFrequency(&MODULE_STM2);

    //start_core2_os();
    while(1);
    while (1)
    {
        // for(i=0;i<1000;i++)
       //  {
          //IfxPort_togglePin(&MODULE_P02, 1);
          //IfxStm_waitTicks(&MODULE_STM1, g_AppCpu0.info.stmFreq/100);
        // }

          IfxPort_togglePin(&MODULE_P33, 10);
		
		  core2_global_count1++;
		  core0_global_count1++;
          IfxStm_waitTicks(&MODULE_STM0, 50000000);
		
         //releaseLock(&lock, mask);
    }
    return (1);
}
