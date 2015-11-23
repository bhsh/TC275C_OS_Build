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
/* Function Prototype Definitions                                           */
/****************************************************************************/
OS_EXTERN osu32_t get_stack_used_percent(osu32_t task_id, osu32_t pos);
OS_EXTERN osu32_t get_the_stack_used(osu32_t core_id);
void core0_get_all_stacks_used(void);

#endif /* End of STACK_MANAGER_H_ */

