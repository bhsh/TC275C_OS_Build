
#include "os_kernel.h"
#include "shareappsw.h"


void CORE0_TASK0(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  //core0_os_thread_test_count_TASK[pthread_config->task_id]++;
  App_share_task_test_count(current_core_id,pthread_config->task_id);
  App_share_stack_background_count();
  //delay_ms(200);
  
  /* Trigger a software interrupt for test only */
  //SRC_GPSR01.U=  (1<<26)|   //SRC_GPSR01.B.SETR=1;
  //		         (1<<10)|   //SRC_GPSR01.B.SRE=1;
  //	             (0<<11)|   //SRC_GPSR01.B.TOS=0;
  //	             (20);      //SRC_GPSR01.B.SRPN=20; 
}
void CORE0_TASK1(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
  App_share_flash_led_1();
  delay_ms(50);
}
void CORE0_TASK2(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
  App_share_flash_led_2();
  delay_ms(50);
}
void CORE0_TASK3(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK4(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK5(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK6(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK7(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK8(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK9(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
}
void CORE0_TASK10(pthread_config_t *pthread_config,osu32_t current_core_id)
{
  App_share_task_test_count(current_core_id,pthread_config->task_id);
  App_share_stack_calculated();
  App_share_flash_led_4();
}
