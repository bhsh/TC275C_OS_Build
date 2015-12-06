/****************************************************************************/
/* FILE NAME:    private2appsw.c                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes prototype definitions of private2 APP  */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "low_driver_port.h"
#include "stack_manager.h"
#include "context_manager.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define  CORE2_TASK_NUM                (11)
#define  CORE2_TOTAL_COUNT             (500000000)
#define  CORE2_TIME_PER_COUNT_NS       (60)

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum  {

	 FINISH,
	 RUNNING	
}APP_PRIV2_CPU_LOAD_LOGIC_STATUS_t;

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile unsigned int App_priv2_var_test_count;

#if (OS_STACK_MODE == ONE_STACK)
  static volatile unsigned int App_priv2_var_one_stack_used_in_per;
#endif

static volatile unsigned int App_priv2_var_task_test_count[CORE2_TASK_NUM];
static volatile unsigned int App_priv2_var_CPU_Load_Backg_Count;
static volatile unsigned int App_priv2_var_CPU_load;
static APP_PRIV2_CPU_LOAD_LOGIC_STATUS_t App_priv2_var_state_machine_state = RUNNING;
static volatile unsigned int App_priv2_var_context_usage_percent;
static volatile unsigned int App_priv2_var_task_test_count0;
static volatile unsigned int App_priv2_var_task_test_count1;
static volatile unsigned int App_priv2_var_task_test_count2;
static volatile unsigned int App_priv2_var_task_test_count3;
static volatile unsigned int App_priv2_var_task_test_count4;
static volatile unsigned int App_priv2_var_task_test_count5;
static volatile unsigned int App_priv2_var_task_test_count6;
static volatile unsigned int App_priv2_var_task_test_count7;
static volatile unsigned int App_priv2_var_task_test_count8;
static volatile unsigned int App_priv2_var_task_test_count9;
static volatile unsigned int App_priv2_var_task_test_count10;

/****************************************************************************/
/* Private0 Function Definitions                                            */
/****************************************************************************/

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_test_count                                 */
/* DESCRIPTION: Test counter increases by 1 when the task is entered        */
/****************************************************************************/
void  App_priv2_func_test_count(void)
{
  App_priv2_var_test_count ++;
} /* End of function App_priv2_func_test_count */

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_many_stacks_measured                       */
/* DESCRIPTION: Measure the stack usage of one stack mode                   */
/****************************************************************************/
void App_priv2_func_many_stacks_measured(void)
{
#if (OS_STACK_MODE == MANY_STACKS)
  core2_get_all_stacks_used();
#endif
} /* End of function App_priv2_func_many_stacks_measured */

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_one_stack_measured                         */
/* DESCRIPTION: Measure the stack usage of many stacks mode                 */
/****************************************************************************/
void App_priv2_func_one_stack_measured(void)
{
#if (OS_STACK_MODE == ONE_STACK)
  App_priv2_var_one_stack_used_in_per = core2_get_the_one_stack_used();
#endif
} /* End of function App_priv2_func_one_stack_measured */

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_task_test_count                            */
/* DESCRIPTION: The test count is increased by 1 when task is entered       */
/****************************************************************************/
void App_priv2_func_task_test_count(unsigned int channel)
{
  App_priv2_var_task_test_count[channel]++;
  switch(channel)
  {
   case 0:
     App_priv2_var_task_test_count0++;
	 break;
   case 1:
     App_priv2_var_task_test_count1++;
	 break;
   case 2:
     App_priv2_var_task_test_count2++;
	 break;
   case 3:
     App_priv2_var_task_test_count3++;
	 break;
   case 4:
     App_priv2_var_task_test_count4++;
	 break;
   case 5:
     App_priv2_var_task_test_count5++;
	 break;
   case 6:
     App_priv2_var_task_test_count6++;
	 break;
   case 7:
     App_priv2_var_task_test_count7++;
	 break;
   case 8:
     App_priv2_var_task_test_count8++;
	 break;
   case 9:
     App_priv2_var_task_test_count9++;
	 break;
   case 10:
     App_priv2_var_task_test_count10++;
	 break;
   default:
   	 break;
  }
}  /* End of function App_priv2_func_task_test_count */

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_cpuload_bkg_count                          */
/* DESCRIPTION: Update the cpuload count in background logic                */
/****************************************************************************/
void App_priv2_func_cpuload_bkg_count(void)
{
  while((App_priv2_var_CPU_Load_Backg_Count < CORE2_TOTAL_COUNT)&&(App_priv2_var_state_machine_state == RUNNING ))
  {
     App_priv2_var_CPU_Load_Backg_Count++;
  }
}  /* End of function App_priv2_func_cpuload_bkg_count */

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_cpuload_calculated                         */
/* DESCRIPTION: Calculate the current cpuload                               */
/****************************************************************************/
void App_priv2_func_cpuload_calculated(void)
{
  /*<CPU load> can be got here. <Section begins> */
  /* Core2_CPU_LOAD = (Core0_CPU_Load_Background_Count * 100)/(1000*1000); */
  if(App_priv2_var_CPU_Load_Backg_Count < CORE2_TOTAL_COUNT)
  {
    App_priv2_var_CPU_load = 1000 - (App_priv2_var_CPU_Load_Backg_Count * CORE2_TIME_PER_COUNT_NS)/(1000*1000);
  }
  else
  {
    App_priv2_var_CPU_load = 0;
  }
  App_priv2_var_state_machine_state = RUNNING;
  App_priv2_var_CPU_Load_Backg_Count = 0;
  /*<CPU load> can be got here. <Section ends> */
}  /* End of function App_priv2_func_cpuload_calculated */ 

/****************************************************************************/
/* FUNCTION NAME: App_priv2_func_get_context_usage                          */
/* DESCRIPTION: Get the context usage percent of core2                      */
/****************************************************************************/
void App_priv2_func_get_context_usage(void)
{
  App_priv2_var_context_usage_percent = core2_get_context_usage();
}  /* End of function App_priv2_func_get_context_usage */

