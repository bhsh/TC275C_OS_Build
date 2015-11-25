/****************************************************************************/
/* FILE NAME:    low_driver_port.c                                          */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the port definiton of os and low friver*/
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

#define STM0_COMPARE0_ISR_PRIORITY	        10   
#define STM1_COMPARE0_ISR_PRIORITY       	11   
#define STM2_COMPARE0_ISR_PRIORITY      	12 

#define CORE0_SOFT1_ISR_PRIORITY	        20   
#define CORE1_SOFT1_ISR_PRIORITY       	    21   
#define CORE2_SOFT1_ISR_PRIORITY      	    22 

extern unsigned int __CSA0[];       /* <CORE0> context save area begin */  
extern unsigned int __CSA0_END[];   /* <CORE0> context save area end   */
extern unsigned int __CSA1[];       /* <CORE1> context save area begin */  
extern unsigned int __CSA1_END[];   /* <CORE1> context save area end   */
extern unsigned int __CSA2[];       /* <CORE2> context save area begin */  
extern unsigned int __CSA2_END[];   /* <CORE2> context save area end   */


/****************************************************************************/
/* Global Variable Definitions                                              */
/****************************************************************************/
volatile unsigned int LowDriver_interrupt_test_flag0;
volatile unsigned int LowDriver_interrupt_test_flag1;
volatile unsigned int LowDriver_interrupt_test_flag2;
unsigned int LowDriver_stm0CompareValue;
unsigned int LowDriver_stm1CompareValue;
unsigned int LowDriver_stm2CompareValue;

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
/* FUNTION NAME: LowDriver_Port_TogglePin                                   */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
void LowDriver_Port_TogglePin(unsigned char pin_num)
{
    IfxPort_togglePin(&MODULE_P33, pin_num);
} /* End of LowDriver_Port_TogglePin function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_End_Addr                       */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Core0_Context_End_Addr(void)
{
    return (unsigned int)__CSA0_END;
} /* End of LowDriver_Get_Core0_Context_End_Addr function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_End_Addr                       */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Core1_Context_End_Addr(void)
{
    return (unsigned int)__CSA1_END;
} /* End of LowDriver_Get_Core1_Context_End_Addr function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_End_Addr                       */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Core2_Context_End_Addr(void)
{
    return (unsigned int)__CSA2_END;
} /* End of LowDriver_Get_Core2_Context_End_Addr function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_Begin_Addr                     */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Core0_Context_Begin_Addr(void)
{
    return (unsigned int)__CSA0;
} /* End of LowDriver_Get_Core0_Context_End_Addr function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_End_Addr                       */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Core1_Context_Begin_Addr(void)
{
    return (unsigned int)__CSA1;
} /* End of LowDriver_Get_Core1_Context_End_Addr function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_End_Addr                       */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Core2_Context_Begin_Addr(void)
{
    return (unsigned int)__CSA2;
} /* End of LowDriver_Get_Core2_Context_End_Addr function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Get_Core0_Context_End_Addr                       */
/* DESCRIPTION:  Toggle the LED in the diver kit by providing the API       */
/*               special argument                                           */
/****************************************************************************/
unsigned int LowDriver_Get_Fcx_Physical_Addr(void)
{   
	unsigned int fcx,fcx_phy_addr,seg_nr;
	
	fcx          = __mfcr(CPU_FCX);
	seg_nr       = __extru(fcx, 16, 4);
    fcx_phy_addr = __insert(seg_nr << 28, fcx, 6, 16);
    
    return (unsigned int)fcx_phy_addr;
} /* End of LowDriver_Get_Core2_Context_End_Addr function */

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
	LowDriver_stm0CompareValue = IfxStm_getFrequency(&MODULE_STM0) / STM0_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM0);

	stmCompareConfig.servProvider = IfxSrc_Tos_cpu0;

	/* <CORE0> Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* <CORE0> Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = LowDriver_stm0CompareValue;   /* <CORE0> Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = STM0_COMPARE0_ISR_PRIORITY;

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
	LowDriver_stm1CompareValue = IfxStm_getFrequency(&MODULE_STM1) / STM1_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM1);
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu1;

	/* <CORE1> Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* <CORE1> Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = LowDriver_stm1CompareValue;   /*<CORE1> Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = STM1_COMPARE0_ISR_PRIORITY;

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
	LowDriver_stm2CompareValue = IfxStm_getFrequency(&MODULE_STM2) / STM2_TICK_PERIOD_IN_MICROSECONDS;	/* 1ms */

	IfxStm_enableOcdsSuspend(&MODULE_STM2);

	/* <CORE2> Configure interrupt service requests for STM trigger outputs */
	stmCompareConfig.servProvider = IfxSrc_Tos_cpu2;

	/* <CORE2> Call the constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);

	/* <CORE2> Modify only the number of ticks and enable the trigger output */
	stmCompareConfig.ticks = LowDriver_stm2CompareValue;   /* <CORE2> Interrupt after stm0CompareValue ticks from now */
	stmCompareConfig.triggerInterruptEnabled = STM2_COMPARE0_ISR_PRIORITY;

	/* <CORE2> Now Compare functionality is initialized */
	IfxStm_initCompare(&MODULE_STM2, &stmCompareConfig);

}/* End of LowDriver_Initialize_CORE2_OS_Tick function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_trigger_software_interrupt1                      */
/* DESCRIPTION:  Trigger a software interrupt for core0                     */
/****************************************************************************/
void LowDriver_Trigger_Software_Interrupt1(void)
{
    SRC_GPSR01.U = (1<<26)|   /* SRC_GPSR01.B.SETR=1;  */ 
  		           (1<<10)|   /* SRC_GPSR01.B.SRE=1;   */
  	               (0<<11)|   /* SRC_GPSR01.B.TOS=0;   */
                   (CORE0_SOFT1_ISR_PRIORITY);      /* SRC_GPSR01.B.SRPN=20; */ 
} /* End of LowDriver_Trigger_Software_Interrupt1 function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_trigger_software_interrupt1                      */
/* DESCRIPTION:  Trigger a software interrupt for core1                     */
/****************************************************************************/
void LowDriver_Trigger_Software_Interrupt2(void)
{
    SRC_GPSR11.U = (1<<26)|   /* SRC_GPSR11.B.SETR=1;  */
    	           (1<<10)|   /* SRC_GPSR11.B.SRE=1;   */
    	           (1<<11)|   /* SRC_GPSR11.B.TOS=1;   */
    	           (CORE1_SOFT1_ISR_PRIORITY);      /* SRC_GPSR11.B.SRPN=21; */
} /* End of LowDriver_Trigger_Software_Interrupt2 function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_Trigger_Software_Interrupt3                      */
/* DESCRIPTION:  Trigger a software interrupt for core2                     */
/****************************************************************************/
void LowDriver_Trigger_Software_Interrupt3(void)
{
    SRC_GPSR21.U = (1<<26)|   /* SRC_GPSR21.B.SETR=1;  */
    	           (1<<10)|   /* SRC_GPSR21.B.SRE=1;   */
    	           (2<<11)|   /* SRC_GPSR21.B.TOS=2;   */
    	           (CORE2_SOFT1_ISR_PRIORITY);      /* SRC_GPSR21.B.SRPN=22; */ 
} /* End of LowDriver_Trigger_Software_Interrupt3 function */

/****************************************************************************/
/* FUNTION NAME: CPU0_SOFT1_Isr                                             */
/* DESCRIPTION:  Software interrupt for core0 to serve                      */
/****************************************************************************/
void __interrupt(CORE0_SOFT1_ISR_PRIORITY) CPU0_SOFT1_Isr(void) 
{
	LowDriver_interrupt_test_flag0++;
} /* End of CPU0_SOFT1_Isr function */

/****************************************************************************/
/* FUNTION NAME: CPU1_SOFT1_Isr                                             */
/* DESCRIPTION:  Software interrupt for core1 to serve                      */
/****************************************************************************/
void __interrupt(CORE1_SOFT1_ISR_PRIORITY) CPU1_SOFT1_Isr(void) 
{
    LowDriver_interrupt_test_flag1++;
} /* End of CPU1_SOFT1_Isr function */

/****************************************************************************/
/* FUNTION NAME: CPU2_SOFT1_Isr                                             */
/* DESCRIPTION:  Software interrupt for core2 to serve                      */
/****************************************************************************/
void __interrupt(CORE2_SOFT1_ISR_PRIORITY) CPU2_SOFT1_Isr(void) 
{
    LowDriver_interrupt_test_flag2++;
} /* End of CPU2_SOFT1_Isr function */