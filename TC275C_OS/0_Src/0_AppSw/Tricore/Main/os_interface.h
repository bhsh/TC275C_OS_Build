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

OS_EXTERN osu32_t  stm0CompareValue;
OS_EXTERN osu32_t  stm1CompareValue;
OS_EXTERN osu32_t  stm2CompareValue;
OS_INLINE osu32_t os_getUstack_address(void)
{  
   osu32_t *res;
   __asm volatile ("mov.aa %0, a10": "=a" (res) : :"a10");
   return (osu32_t)res;
}
/****************************************************************************/
/* DESCRIPTION: <CORE0> Update stm0 compare1                                */
/****************************************************************************/
OS_INLINE void LowDriver_Update_Core0_Tick(void) 
{
    osu32_t core0_ticks;

    core0_ticks = (osu32_t)(stm0CompareValue*1);
    IfxStm_updateCompare (&MODULE_STM0,
		                  IfxStm_Comparator_0,
	                      IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + core0_ticks);

} /* End of LowDriver_Update_Core0_Tick function */

/****************************************************************************/
/* DESCRIPTION: <CORE1> Update stm1 compare1                                */
/****************************************************************************/
OS_INLINE void LowDriver_Update_Core1_Tick(void)
{
    osu32_t core1_ticks;
	
    core1_ticks = (osu32_t) (stm1CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM1,
		                  IfxStm_Comparator_0, 
		                  IfxStm_getCompare (&MODULE_STM1, IfxStm_Comparator_0) + core1_ticks);

} /* End of LowDriver_Update_Core1_Tick function */

/****************************************************************************/
/* DESCRIPTION: <CORE2> Update stm0 compare1                                */
/****************************************************************************/
OS_INLINE void LowDriver_Update_Core2_Tick(void)
{
    osu32_t core2_ticks;
	
    core2_ticks = (osu32_t) (stm2CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM2,
		                  IfxStm_Comparator_0, 
		                  IfxStm_getCompare (&MODULE_STM2, IfxStm_Comparator_0) + core2_ticks);

} /* End of LowDriver_Update_Core2_Tick function */
OS_EXTERN void    os_wait_in_us(osu32_t time);
OS_EXTERN osu32_t os_getstmlower_count(void);
OS_EXTERN void    osPort_togglePin(osu8_t pin_num);
OS_EXTERN void    os_trigger_software_interrupt1(void);
OS_EXTERN void    os_trigger_software_interrupt2(void);
OS_EXTERN void    os_trigger_software_interrupt3(void);
OS_EXTERN osu32_t os_get_curr_coreid(void);