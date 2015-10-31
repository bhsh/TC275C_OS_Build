#include "os_type.h"
#include "os_interface.h"
#include "stack_manager.h"

#define LED_1    (8)
#define LED_2    (9)
#define LED_3    (10)
#define LED_4    (11)

#define  TOTAL_COUNT             (500000000)
#define  TIME_PER_COUNT_NS       (60)
#define  TASK_NUM                (11)
#define  APP_MAX_CORE_USED       (3)

typedef enum  {

	 FINISH,
	 RUNNING	
}APP_SHARE_CPU_LOAD_LOGIC_STATUS_t;

static volatile unsigned int App_share_var_task_test_count[APP_MAX_CORE_USED][TASK_NUM];
static volatile unsigned int App_share_var_CPU_Load_Backg_Count[APP_MAX_CORE_USED];
static volatile unsigned int App_share_var_CPU_load[APP_MAX_CORE_USED];
static APP_SHARE_CPU_LOAD_LOGIC_STATUS_t App_share_var_state_machine_state[APP_MAX_CORE_USED] = { RUNNING, RUNNING, RUNNING };

void App_share_func_stack_background_count(unsigned int channel)
{
  while((App_share_var_CPU_Load_Backg_Count[channel] < TOTAL_COUNT)&&(App_share_var_state_machine_state[channel] == RUNNING ))
  {
     App_share_var_CPU_Load_Backg_Count[channel]++;
  }
}
void App_share_func_stack_calculated(unsigned int channel)
{
  /*<CPU load> can be got here. <Section begins> */
  /* Core0_CPU_LOAD = (Core0_CPU_Load_Background_Count * 100)/(1000*1000); */
  if(App_share_var_CPU_Load_Backg_Count[channel] < TOTAL_COUNT)
  {
    App_share_var_CPU_load[channel] = 1000 - (App_share_var_CPU_Load_Backg_Count[channel] * TIME_PER_COUNT_NS)/(1000*1000);
  }
  else
  {
    App_share_var_CPU_load[channel] = 0;
  }
  App_share_var_state_machine_state[channel] = RUNNING;
  App_share_var_CPU_Load_Backg_Count[channel] = 0;
  /*<CPU load> can be got here. <Section ends> */
}

void App_share_func_task_test_count(unsigned int current_core_id,unsigned int channel)
{
  App_share_var_task_test_count[current_core_id][channel]++;
}
void  App_share_func_flash_led_1(void)
{
   LowDriver_Port_TogglePin(LED_1);
}

void  App_share_func_flash_led_2(void)
{
   LowDriver_Port_TogglePin(LED_2);
}

void  App_share_func_flash_led_3(void)
{
   LowDriver_Port_TogglePin(LED_3);
}

void  App_share_func_flash_led_4(void)
{
   LowDriver_Port_TogglePin(LED_4);
}
void App_share_func_trigger_software_interrupt1(void)
{
   LowDriver_trigger_software_interrupt1();
}

