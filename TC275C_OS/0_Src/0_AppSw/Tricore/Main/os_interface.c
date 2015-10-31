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

#define STM0_TICK_PERIOD_IN_MICROSECONDS    1000
#define STM1_TICK_PERIOD_IN_MICROSECONDS    1000
#define STM2_TICK_PERIOD_IN_MICROSECONDS    1000

#define IFX_CFG_ISR_PRIORITY_STM0_COMPARE0	10   /**< \brief Stm0 Compare 0 interrupt priority.  */
#define IFX_CFG_ISR_PRIORITY_STM1_COMPARE0	11   /**< \brief Stm1 Compare 0 interrupt priority.  */
#define IFX_CFG_ISR_PRIORITY_STM2_COMPARE0	12   /**< \brief Stm2 Compare 0 interrupt priority.  */


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

osu32_t stm0CompareValue;
osu32_t stm1CompareValue;
osu32_t stm2CompareValue;

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
