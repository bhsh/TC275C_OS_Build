//#include "core0_tasks.h"
//#include "os_kernel.h"


#include <stdlib.h>
#include "os_kernel.h"
//#include "simio.h"
#include <stdio.h>
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"


#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"


#include "os_trace.h"
#include "os_interface.h"
#include "core0_tasks.h"

volatile int core0_os_thread_test_count_TASK[11];

void CORE0_TASK0(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK1(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK2(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK3(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK4(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK5(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK6(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK7(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK8(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK9(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
void CORE0_TASK10(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
}
