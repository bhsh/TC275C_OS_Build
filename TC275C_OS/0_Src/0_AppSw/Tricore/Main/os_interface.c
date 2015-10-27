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
#include <stdio.h>
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
#include "communication.h"


#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

#include "os_interface.h"

volatile osu32_t interrupt_test_flag;

void os_wait_in_us(osu32_t time)
{
  IfxStm_waitTicks(&MODULE_STM0, time*100);
}

osu32_t os_getstmlower_count(void)
{
  return (osu32_t)(IfxStm_getLower(&MODULE_STM0)/10);
}
void __interrupt(20) CPU0_SOFT1_Isr(void) 
{
	interrupt_test_flag++;
}

void __interrupt(21) CPU1_SOFT1_Isr(void) 
{
    interrupt_test_flag++;
}

void __interrupt(22) CPU2_SOFT1_Isr(void) 
{
    interrupt_test_flag++;
}
void osPort_togglePin(osu8_t pin_num)
{
    IfxPort_togglePin(&MODULE_P33, pin_num);
}
void os_trigger_software_interrupt1(void)
{
  SRC_GPSR01.U=  (1<<26)|   /* SRC_GPSR01.B.SETR=1;  */ 
  		         (1<<10)|   /* SRC_GPSR01.B.SRE=1;   */
  	             (0<<11)|   /* SRC_GPSR01.B.TOS=0;   */
  	             (20);      /* SRC_GPSR01.B.SRPN=20; */ 
}
void os_trigger_software_interrupt2(void)
{
  SRC_GPSR11.U=  (1<<26)|   /* SRC_GPSR11.B.SETR=1;  */
  	             (1<<10)|   /* SRC_GPSR11.B.SRE=1;   */
  	             (1<<11)|   /* SRC_GPSR11.B.TOS=1;   */
  	             (21);      /* SRC_GPSR11.B.SRPN=21; */
}
void os_trigger_software_interrupt3(void)
{
  SRC_GPSR21.U=  (1<<26)|   /* SRC_GPSR21.B.SETR=1;  */
  	             (1<<10)|   /* SRC_GPSR21.B.SRE=1;   */
  	             (2<<11)|   /* SRC_GPSR21.B.TOS=2;   */
  	             (22);      /* SRC_GPSR21.B.SRPN=22; */ 
}
osu32_t os_get_curr_coreid(void)
{
   osu32_t core_id;
   core_id=__mfcr(CPU_CORE_ID);
   return (core_id&0x7);
}