#include "Cpu\Std\Ifx_Types.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Scu\Std\IfxScuWdt.h"
#include "Port/Std/IfxPort.h"
#include "communication.h"
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"

int core2_main (void)
{
    __enable ();
    /*
     * !!WATCHDOG2 IS DISABLED HERE!!
     * Enable the watchdog in the demo if it is required and also service the watchdog periodically
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
    while (1)
    {
        // for(i=0;i<1000;i++)
       //  {
          //IfxPort_togglePin(&MODULE_P02, 1);
          //IfxStm_waitTicks(&MODULE_STM1, g_AppCpu0.info.stmFreq/100);
        // }

          IfxPort_togglePin(&MODULE_P33, 11);
          IfxStm_waitTicks(&MODULE_STM0, 10000000);
         //releaseLock(&lock, mask);
    }
    return (1);
}
