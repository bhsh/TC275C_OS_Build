/****************************************************************************/
/* FILE NAME:    sharedappsw.h                                               */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes prototype definitions of APP           */
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
#define LED_1    (8)
#define LED_2    (9)
#define LED_3    (10)
#define LED_4    (11)

#define  TOTAL_COUNT             (500000000)
#define  TIME_PER_COUNT_NS       (60)
#define  TASK_NUM                (11)
#define  APP_MAX_CORE_USED       (3)

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum  {

	 FINISH,
	 RUNNING	
}APP_SHARE_CPU_LOAD_LOGIC_STATUS_t;

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile unsigned int App_shared_var_task_test_count[APP_MAX_CORE_USED][TASK_NUM];
static volatile unsigned int App_shared_var_CPU_Load_Backg_Count[APP_MAX_CORE_USED];
static volatile unsigned int App_shared_var_CPU_load[APP_MAX_CORE_USED];
static APP_SHARE_CPU_LOAD_LOGIC_STATUS_t App_shared_var_state_machine_state[APP_MAX_CORE_USED] = { RUNNING, RUNNING, RUNNING };

/****************************************************************************/
/* Shared Funtion Definitions                                               */
/****************************************************************************/
void App_shared_func_stack_background_count(unsigned int channel)
{
  while((App_shared_var_CPU_Load_Backg_Count[channel] < TOTAL_COUNT)&&(App_shared_var_state_machine_state[channel] == RUNNING ))
  {
     App_shared_var_CPU_Load_Backg_Count[channel]++;
  }
}
void App_shared_func_stack_calculated(unsigned int channel)
{
  /*<CPU load> can be got here. <Section begins> */
  /* Core0_CPU_LOAD = (Core0_CPU_Load_Background_Count * 100)/(1000*1000); */
  if(App_shared_var_CPU_Load_Backg_Count[channel] < TOTAL_COUNT)
  {
    App_shared_var_CPU_load[channel] = 1000 - (App_shared_var_CPU_Load_Backg_Count[channel] * TIME_PER_COUNT_NS)/(1000*1000);
  }
  else
  {
    App_shared_var_CPU_load[channel] = 0;
  }
  App_shared_var_state_machine_state[channel] = RUNNING;
  App_shared_var_CPU_Load_Backg_Count[channel] = 0;
  /*<CPU load> can be got here. <Section ends> */
}
void App_shared_func_task_test_count(unsigned int current_core_id,unsigned int channel)
{
  App_shared_var_task_test_count[current_core_id][channel]++;
}
void  App_shared_func_flash_led_1(void)
{
   LowDriver_Port_TogglePin(LED_1);
}

void  App_shared_func_flash_led_2(void)
{
   LowDriver_Port_TogglePin(LED_2);
}

void  App_shared_func_flash_led_3(void)
{
   LowDriver_Port_TogglePin(LED_3);
}

void  App_shared_func_flash_led_4(void)
{
   LowDriver_Port_TogglePin(LED_4);
}
void App_shared_func_trigger_software_interrupt1(void)
{
   LowDriver_Trigger_Software_Interrupt1();
}

