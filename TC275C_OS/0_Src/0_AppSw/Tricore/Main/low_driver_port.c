/****************************************************************************/
/* FILE NAME:    low_driver_port.h                                          */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the port logic of AURIX 3-core os      */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "low_driver_port.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define STM0_TICK_PERIOD_IN_MICROSECONDS    1000
#define STM1_TICK_PERIOD_IN_MICROSECONDS    1000
#define STM2_TICK_PERIOD_IN_MICROSECONDS    1000

#define IFX_CFG_ISR_PRIORITY_STM0_COMPARE0	10   /**< \brief Stm0 Compare 0 interrupt priority.  */
#define IFX_CFG_ISR_PRIORITY_STM1_COMPARE0	11   /**< \brief Stm1 Compare 0 interrupt priority.  */
#define IFX_CFG_ISR_PRIORITY_STM2_COMPARE0	12   /**< \brief Stm2 Compare 0 interrupt priority.  */

/****************************************************************************/
/* Global Variable Definitions                                              */
/****************************************************************************/
volatile unsigned int interrupt_test_flag;
unsigned int stm0CompareValue;
unsigned int stm1CompareValue;
unsigned int stm2CompareValue;

/****************************************************************************/
/* FUNTION NAME: LowDriver_Wait_In_Us                                       */
/* DESCRIPTION: Wait by querying the tick of STM TIM0 (tick unit:1us)in the */
/*              current STM configuration                                   */ 
/****************************************************************************/
void LowDriver_Wait_In_Us(unsigned int time)
{
  IfxStm_waitTicks(&MODULE_STM0, time*100);
} /* End of LowDriver_Wait_In_Us function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_GetStmLower_Count                                */
/* DESCRIPTION: Wait by querying the tick of STM TIM0 (tick unit:0.1Us)in   */
/*              the current STM configuration                               */ 
/****************************************************************************/
unsigned int LowDriver_GetStmLower_Count(void)
{
    return (unsigned int)(IfxStm_getLower(&MODULE_STM0)/10);
} /* End of LowDriver_GetStmLower_Count function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Port_TogglePin                                   */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
void LowDriver_Port_TogglePin(unsigned char pin_num)
{
    IfxPort_togglePin(&MODULE_P33, pin_num);
} /* End of LowDriver_Port_TogglePin function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Curr_Core_ID                                 */
/* DESCRIPTION:  Get the current core ID by the API                         */
/****************************************************************************/
unsigned int LowDriver_Get_Curr_Core_ID(void)
{
   unsigned int core_id;
   core_id=__mfcr(CPU_CORE_ID);
   
   return (core_id&0x7);
} /* End of LowDriver_Get_Curr_Core_ID function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Initialize_CORE0_OS_Tick                         */
/* DESCRIPTION:  Initialize the tick driver for core0 os                    */
/****************************************************************************/
void LowDriver_Initialize_CORE0_OS_Tick(void)
{
	/* <CORE0> Initialize STM for the triggers*/
	IfxStm_CompareConfig stmCompareConfig;

    /* <CORE0> Calculate the compare value of STM0 */
	stm0CompareValue = IfxStm_getFrequency(&MODULE_STM0) / STM0_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM0);

	stmCompareConfig.servProvider = IfxSrc_Tos_cpu0;

	/* <CORE0> Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* <CORE0> Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = stm0CompareValue;   /* <CORE0> Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = IFX_CFG_ISR_PRIORITY_STM0_COMPARE0;

	/* <CORE0> Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM0, &stmCompareConfig);

} /* End of LowDriver_Initialize_CORE0_OS_Tick function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Initialize_CORE1_OS_Tick                         */
/* DESCRIPTION:  Initialize the tick driver for core1 os                    */
/****************************************************************************/
void LowDriver_Initialize_CORE1_OS_Tick(void)
{
	/*  <CORE1> Initialize STM for the triggers*/
	IfxStm_CompareConfig stmCompareConfig;

    /* <CORE1> Calculate the compare value of STM0 */
	stm1CompareValue = IfxStm_getFrequency(&MODULE_STM1) / STM1_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM1);
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu1;

	/* <CORE1> Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* <CORE1> Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = stm1CompareValue;   /*<CORE1> Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = IFX_CFG_ISR_PRIORITY_STM1_COMPARE0;

	/* <CORE1> Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM1, &stmCompareConfig);

}/* End of LowDriver_Initialize_CORE1_OS_Tick function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Initialize_CORE2_OS_Tick                         */
/* DESCRIPTION:  Initialize the tick driver for core2 os                    */
/****************************************************************************/
void LowDriver_Initialize_CORE2_OS_Tick(void)
{
	/* <CORE2> Initialize STM for the triggers*/
	IfxStm_CompareConfig stmCompareConfig;

    /* <CORE2> Calculate the compare value of STM0 */
	stm2CompareValue = IfxStm_getFrequency(&MODULE_STM2) / STM2_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM2);

	/* <CORE2> Configure interrupt service requests for STM trigger outputs */
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu2;

	/* <CORE2> Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* <CORE2> Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = stm2CompareValue;   /* <CORE2> Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = IFX_CFG_ISR_PRIORITY_STM2_COMPARE0;

	/* <CORE2> Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM2, &stmCompareConfig);

}/* End of LowDriver_Initialize_CORE2_OS_Tick function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_trigger_software_interrupt1                      */
/* DESCRIPTION:  Trigger a software interrupt for core0                     */
/****************************************************************************/
void LowDriver_trigger_software_interrupt1(void)
{
    SRC_GPSR01.U = (1<<26)|   /* SRC_GPSR01.B.SETR=1;  */ 
  		           (1<<10)|   /* SRC_GPSR01.B.SRE=1;   */
  	               (0<<11)|   /* SRC_GPSR01.B.TOS=0;   */
  	               (20);      /* SRC_GPSR01.B.SRPN=20; */ 
} /* End of LowDriver_trigger_software_interrupt1 function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_trigger_software_interrupt1                      */
/* DESCRIPTION:  Trigger a software interrupt for core1                     */
/****************************************************************************/
void LowDriver_trigger_software_interrupt2(void)
{
    SRC_GPSR11.U = (1<<26)|   /* SRC_GPSR11.B.SETR=1;  */
    	           (1<<10)|   /* SRC_GPSR11.B.SRE=1;   */
    	           (1<<11)|   /* SRC_GPSR11.B.TOS=1;   */
    	           (21);      /* SRC_GPSR11.B.SRPN=21; */
} /* End of LowDriver_trigger_software_interrupt2 function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_trigger_software_interrupt1                      */
/* DESCRIPTION:  Trigger a software interrupt for core2                     */
/****************************************************************************/
void LowDriver_trigger_software_interrupt3(void)
{
    SRC_GPSR21.U = (1<<26)|   /* SRC_GPSR21.B.SETR=1;  */
    	           (1<<10)|   /* SRC_GPSR21.B.SRE=1;   */
    	           (2<<11)|   /* SRC_GPSR21.B.TOS=2;   */
    	           (22);      /* SRC_GPSR21.B.SRPN=22; */ 
} /* End of LowDriver_trigger_software_interrupt3 function */

/****************************************************************************/
/* FUNTION NAME: CPU0_SOFT1_Isr                                             */
/* DESCRIPTION:  Software interrupt for core0 to serve                      */
/****************************************************************************/
void __interrupt(20) CPU0_SOFT1_Isr(void) 
{
	interrupt_test_flag++;
} /* End of CPU0_SOFT1_Isr function */

/****************************************************************************/
/* FUNTION NAME: CPU1_SOFT1_Isr                                             */
/* DESCRIPTION:  Software interrupt for core1 to serve                      */
/****************************************************************************/
void __interrupt(21) CPU1_SOFT1_Isr(void) 
{
    interrupt_test_flag++;
} /* End of CPU1_SOFT1_Isr function */

/****************************************************************************/
/* FUNTION NAME: CPU2_SOFT1_Isr                                             */
/* DESCRIPTION:  Software interrupt for core2 to serve                      */
/****************************************************************************/
void __interrupt(22) CPU2_SOFT1_Isr(void) 
{
    interrupt_test_flag++;
} /* End of CPU2_SOFT1_Isr function */