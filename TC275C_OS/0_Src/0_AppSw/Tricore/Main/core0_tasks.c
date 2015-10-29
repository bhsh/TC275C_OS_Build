
#include "os_type.h"
#include "os.h"
#include "shareappsw.h"


void CORE0_TASK0(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  App_share_func_stack_background_count(pthread_config->current_task_core_id);
}
void CORE0_TASK1(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  App_share_func_flash_led_1();
}
void CORE0_TASK2(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  App_share_func_flash_led_2();
}
void CORE0_TASK3(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK4(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK5(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK6(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK7(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK8(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK9(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE0_TASK10(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  App_share_func_stack_calculated(pthread_config->current_task_core_id);
  App_share_func_flash_led_4();
}
