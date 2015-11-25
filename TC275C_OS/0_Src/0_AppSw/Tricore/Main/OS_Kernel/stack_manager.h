/****************************************************************************/
/* FILE NAME:    stack_manager.h                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes logic that measure the stack usages of */
/*               every each task in thread                                  */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef  STACK_MANAGER_H_  
#define  STACK_MANAGER_H_

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_mode.h"

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
#if (OS_STACK_MODE == MANY_STACKS)
  OS_EXTERN void    core0_get_all_stacks_used(void);
  OS_EXTERN void    core1_get_all_stacks_used(void);
  OS_EXTERN void    core2_get_all_stacks_used(void);

#else
  OS_EXTERN osu32_t core0_get_the_one_stack_used(void);
  OS_EXTERN osu32_t core1_get_the_one_stack_used(void);
  OS_EXTERN osu32_t core2_get_the_one_stack_used(void);

#endif

#endif /* End of STACK_MANAGER_H_ */

