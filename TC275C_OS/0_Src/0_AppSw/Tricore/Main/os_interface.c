/*-----------------------------------------------------------------------------------
|
|   File name:    os_interface.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#include "os_type.h"


#include <stdlib.h>
#include "os_kernel.h"
//#include "simio.h"
#include <stdio.h>
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"


#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

//#include "os_interface.h"

/*-------------------------------------------------------------------------------------
|
--------------------------------------------------------------------------------------*/
void os_wait_in_us(osu32_t time)
{
  IfxStm_waitTicks(&MODULE_STM0, time*100);
}


osu32_t os_getstmlower_count(void)
{
  return (osu32_t)(IfxStm_getLower(&MODULE_STM0)/10);
}


volatile osu32_t interrupt_test_flag;
void __interrupt(20) CPU0_SOFT1_Isr(void) 
{

	interrupt_test_flag++;
    //pthread_cond_broadcast(&core0_os_cond4);
}
