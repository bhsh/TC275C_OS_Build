
#include "os_interface.h"

#define LED_1    (8)
#define LED_2    (9)
#define LED_3    (10)
#define LED_4    (11)

#define  TOTAL_COUNT        (500000000)
#define  TIME_PER_COUNT_NS  (60)
#define  TASK_NUM           (11)
#define  APP_MAX_CORE       (3)

typedef enum  {
	 FINISH,
	 RUNNING
		
}cpu_load_get_status_t;

static volatile unsigned int App_task_test_count[APP_MAX_CORE][TASK_NUM];
static volatile unsigned int Core0_CPU_Load_Background_Count;
static volatile unsigned int Core0_CPU_LOAD;
static cpu_load_get_status_t cpu0_load_get_status = RUNNING;

void App_share_stack_background_count(void)
{
  while((Core0_CPU_Load_Background_Count < TOTAL_COUNT)&&(cpu0_load_get_status == RUNNING ))
  {
     Core0_CPU_Load_Background_Count++;
  }
}
void App_share_stack_calculated(void)
{
  /*<CPU load> can be got here. <Section begins> */
  /* Core0_CPU_LOAD = (Core0_CPU_Load_Background_Count * 100)/(1000*1000); */
  if(Core0_CPU_Load_Background_Count < TOTAL_COUNT)
  {
    Core0_CPU_LOAD = 1000 - (Core0_CPU_Load_Background_Count * TIME_PER_COUNT_NS)/(1000*1000);
  }
  else
  {
    Core0_CPU_LOAD = 0;
  }
  cpu0_load_get_status = RUNNING;
  Core0_CPU_Load_Background_Count = 0;
  /*<CPU load> can be got here. <Section ends> */
}

void App_share_task_test_count(unsigned int current_core_id,unsigned int channel)
{
  App_task_test_count[current_core_id][channel]++;
}
void  App_share_flash_led_1(void)
{
   osPort_togglePin(LED_1);
}

void  App_share_flash_led_2(void)
{
   osPort_togglePin(LED_2);
}

void  App_share_flash_led_3(void)
{
   osPort_togglePin(LED_3);
}

void  App_share_flash_led_4(void)
{
   osPort_togglePin(LED_4);
}
void App_share_trigger_software_interrupt1(void)
{
   os_trigger_software_interrupt1();
}

