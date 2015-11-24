/****************************************************************************/
/* FILE NAME:    low_driver_port.h                                          */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the port definiton of os and low friver*/
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef LOW_DRIVER_PORT_H_ 
#define LOW_DRIVER_PORT_H_
/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_type.h"
#include <stdlib.h>
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
#include "communication.h"
#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

/****************************************************************************/
/* FUNTION NAME: LowDriver_GetStmLower_Count                                */
/* DESCRIPTION: Wait by querying the tick of STM TIM0 (tick unit:0.1Us)in   */
/*              the current STM configuration                               */ 
/****************************************************************************/
inline unsigned int LowDriver_GetStmLower_Count(void)
{
    return (unsigned int)(IfxStm_getLower(&MODULE_STM0)/10);
} /* End of LowDriver_GetStmLower_Count function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_GetStm0_LowerCount                               */
/* DESCRIPTION: Wait by querying the tick of STM TIM0 (tick unit:0.1Us)in   */
/*              the current STM configuration                               */ 
/****************************************************************************/
inline unsigned int LowDriver_GetStm0_LowerCount(void)
{
    return (unsigned int)(IfxStm_getLower(&MODULE_STM0)/10);
} /* End of LowDriver_GetStmLower_Count function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_GetStm1_LowerCount                               */
/* DESCRIPTION: Wait by querying the tick of STM TIM1 (tick unit:0.1Us)in   */
/*              the current STM configuration                               */ 
/****************************************************************************/
inline unsigned int LowDriver_GetStm1_LowerCount(void)
{
    return (unsigned int)(IfxStm_getLower(&MODULE_STM1)/10);
} /* End of LowDriver_GetStmLower_Count function */

/****************************************************************************/
/* FUNTION NAME: LowDriver_GetStm2_LowerCount                               */
/* DESCRIPTION: Wait by querying the tick of STM TIM2 (tick unit:0.1Us)in   */
/*              the current STM configuration                               */ 
/****************************************************************************/
inline unsigned int LowDriver_GetStm2_LowerCount(void)
{
    return (unsigned int)(IfxStm_getLower(&MODULE_STM2)/10);
} /* End of LowDriver_GetStmLower_Count function */

/****************************************************************************/
/* DESCRIPTION: <CORE0> Update stm0 compare1                                */
/****************************************************************************/
inline unsigned int  LowDriver_GetUstack_Address(void)
{  
   unsigned int *res;
   __asm volatile ("mov.aa %0, a10": "=a" (res) : :"a10");
   return (unsigned int)res;
} /* End of LowDriver_GetUstack_Address function */

/****************************************************************************/
/* FUNTION NAME: os_trace_thread_timeslot                                   */
/* DESCRIPTION: Wait by querying the tick of STM TIM0 (tick unit:1Us)in     */
/*              the current STM configuration                               */ 
/****************************************************************************/
inline void os_trace_thread_timeslot(unsigned int curr_core_id)
{   
	extern osu32_t core0_os_thread_thread_timeslot;
	extern osu32_t core1_os_thread_thread_timeslot;
	extern osu32_t core2_os_thread_thread_timeslot;

    switch(curr_core_id)
	{
      case 0:
	  	core0_os_thread_thread_timeslot = LowDriver_GetStm0_LowerCount()/10;
	  	break;
      case 1:
	  	core1_os_thread_thread_timeslot = LowDriver_GetStm1_LowerCount()/10;
	  	break;
	  case 2:
	  	core2_os_thread_thread_timeslot = LowDriver_GetStm2_LowerCount()/10;
	  	break;
	  default:
	  	break;
	}
	
} /* End of LowDriver_GetStmLower_Count function */

/****************************************************************************/
/* FUNTION NAME: core0_os_trace_thread_timeslot                             */
/* DESCRIPTION: Wait by querying the tick of STM TIM0 (tick unit:1Us)in     */
/*              the current STM configuration                               */ 
/****************************************************************************/

/****************************************************************************/
/* DESCRIPTION: <CORE0> Update stm0 compare1                                */
/****************************************************************************/
inline void LowDriver_Update_CORE0_OS_Tick(void) 
{   
	extern unsigned int  LowDriver_stm0CompareValue;
    unsigned int core0_ticks;

    core0_ticks = (unsigned int)(LowDriver_stm0CompareValue*1);
    IfxStm_updateCompare (&MODULE_STM0,
		                  IfxStm_Comparator_0,
	                      IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + core0_ticks);

} /* End of LowDriver_Update_CORE0_OS_Tick function */

/****************************************************************************/
/* DESCRIPTION: <CORE1> Update stm1 compare0                                */
/****************************************************************************/
inline void LowDriver_Update_CORE1_OS_Tick(void)
{
    extern unsigned int  LowDriver_stm1CompareValue;
    unsigned int core1_ticks;
	
    core1_ticks = (unsigned int) (LowDriver_stm1CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM1,
		                  IfxStm_Comparator_0, 
		                  IfxStm_getCompare (&MODULE_STM1, IfxStm_Comparator_0) + core1_ticks);

} /* End of LowDriver_Update_CORE1_OS_Tick function */

/****************************************************************************/
/* DESCRIPTION: <CORE2> Update stm2 compare0                                */
/****************************************************************************/
inline void LowDriver_Update_CORE2_OS_Tick(void)
{
    extern unsigned int  LowDriver_stm2CompareValue;
    unsigned int core2_ticks;
	
    core2_ticks = (unsigned int) (LowDriver_stm2CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM2,
		                  IfxStm_Comparator_0, 
		                  IfxStm_getCompare (&MODULE_STM2, IfxStm_Comparator_0) + core2_ticks);

} /* End of LowDriver_Update_CORE2_OS_Tick function */

/****************************************************************************/
/* Extern Statements                                                        */
/****************************************************************************/
extern void         LowDriver_Wait_In_Us(unsigned int time);
extern void         LowDriver_Port_TogglePin(unsigned char pin_num);
extern void         LowDriver_Trigger_Software_Interrupt1(void);
extern void         LowDriver_Trigger_Software_Interrupt2(void);
extern void         LowDriver_Trigger_Software_Interrupt3(void);
extern void         LowDriver_Initialize_CORE0_OS_Tick(void);
extern void         LowDriver_Initialize_CORE1_OS_Tick(void);
extern void         LowDriver_Initialize_CORE2_OS_Tick(void);
extern unsigned int LowDriver_Get_Curr_Core_ID(void);
#endif /* End of LOW_DRIVER_PORT_H_ */
