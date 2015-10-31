/*-----------------------------------------------------------------------------------
|
|   File name:    os_interface.h
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

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


inline unsigned int  LowDriver_GetUstack_Address(void)
{  
   unsigned int *res;
   __asm volatile ("mov.aa %0, a10": "=a" (res) : :"a10");
   return (unsigned int)res;
}
/****************************************************************************/
/* DESCRIPTION: <CORE0> Update stm0 compare1                                */
/****************************************************************************/
inline void LowDriver_Update_CORE0_OS_Tick(void) 
{   
	extern unsigned int  stm0CompareValue;
    unsigned int core0_ticks;

    core0_ticks = (unsigned int)(stm0CompareValue*1);
    IfxStm_updateCompare (&MODULE_STM0,
		                  IfxStm_Comparator_0,
	                      IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + core0_ticks);

} /* End of LowDriver_Update_CORE0_OS_Tick function */

/****************************************************************************/
/* DESCRIPTION: <CORE1> Update stm1 compare1                                */
/****************************************************************************/
inline void LowDriver_Update_CORE1_OS_Tick(void)
{
    extern unsigned int  stm1CompareValue;
    unsigned int core1_ticks;
	
    core1_ticks = (unsigned int) (stm1CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM1,
		                  IfxStm_Comparator_0, 
		                  IfxStm_getCompare (&MODULE_STM1, IfxStm_Comparator_0) + core1_ticks);

} /* End of LowDriver_Update_Core1_Tick function */

/****************************************************************************/
/* DESCRIPTION: <CORE2> Update stm0 compare1                                */
/****************************************************************************/
inline void LowDriver_Update_CORE2_OS_Tick(void)
{
    extern unsigned int  stm2CompareValue;
    unsigned int core2_ticks;
	
    core2_ticks = (unsigned int) (stm2CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM2,
		                  IfxStm_Comparator_0, 
		                  IfxStm_getCompare (&MODULE_STM2, IfxStm_Comparator_0) + core2_ticks);

} /* End of LowDriver_Update_Core2_Tick function */

extern void         LowDriver_Wait_In_Us(unsigned int time);
extern void         LowDriver_Port_TogglePin(unsigned char pin_num);
extern void         LowDriver_trigger_software_interrupt1(void);
extern void         LowDriver_trigger_software_interrupt2(void);
extern void         LowDriver_trigger_software_interrupt3(void);
extern void         LowDriver_Initialize_CORE0_OS_Tick(void);
extern void         LowDriver_Initialize_CORE1_OS_Tick(void);
extern void         LowDriver_Initialize_CORE2_OS_Tick(void);
extern unsigned int LowDriver_Get_Curr_Core_ID(void);
extern unsigned int LowDriver_GetStmLower_Count(void);
