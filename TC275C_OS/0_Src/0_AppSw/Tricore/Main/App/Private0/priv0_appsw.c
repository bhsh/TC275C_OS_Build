/****************************************************************************/
/* FILE NAME:    private0appsw.c                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes prototype definitions of private0 APP  */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "low_driver_port.h"
#include "stack_manager.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile unsigned int App_priv0_var_test_count;

#if (OS_STACK_MODE == ONE_STACK)
  static volatile unsigned int App_priv0_var_one_stack_used_in_per;
#endif

/****************************************************************************/
/* Private1 Function Definitions                                            */
/****************************************************************************/
void  App_priv0_func_test_count(void)
{
  App_priv0_var_test_count ++;
}

void App_priv0_func_many_stacks_measured(void)
{
#if (OS_STACK_MODE == MORE_STACKS)
  core0_get_all_stacks_used();
#endif
}
void App_priv0_func_one_stack_measured(void)
{
#if (OS_STACK_MODE == ONE_STACK)
  App_priv0_var_one_stack_used_in_per = core0_get_the_one_stack_used();
#endif
}

