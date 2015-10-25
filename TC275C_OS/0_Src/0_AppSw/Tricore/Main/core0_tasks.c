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

typedef enum  {
	 FINISH,
	 RUNNING
		
}cpu_load_get_status_t;

volatile int core0_os_thread_test_count_TASK[11];
volatile uint32 Core0_CPU_Load_Background_Count;
volatile uint32 Core0_CPU_Load_Background;
volatile uint32 Core0_CPU_LOAD;

cpu_load_get_status_t  cpu0_load_get_status = RUNNING;

#define  TOTAL_COUNT        500000000
#define  TIME_PER_COUNT_NS  60

void CORE0_TASK0(pthread_config_t *pthread_config)
{
  //core0_os_thread_test_count_TASK[pthread_config->task_id]++;

  while((Core0_CPU_Load_Background_Count < TOTAL_COUNT)&&(cpu0_load_get_status == RUNNING ))
  {
     Core0_CPU_Load_Background_Count++;
  }
  //delay_ms(200);
  
  /* Trigger a software interrupt for test only */
  //SRC_GPSR01.U=  (1<<26)|   //SRC_GPSR01.B.SETR=1;
  //		         (1<<10)|   //SRC_GPSR01.B.SRE=1;
  //	             (0<<11)|   //SRC_GPSR01.B.TOS=0;
  //	             (20);      //SRC_GPSR01.B.SRPN=20; 
}
void CORE0_TASK1(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
  IfxPort_togglePin(&MODULE_P33, 9);
  delay_ms(50);
}
void CORE0_TASK2(pthread_config_t *pthread_config)
{
  core0_os_thread_test_count_TASK[pthread_config->task_id]++;
  IfxPort_togglePin(&MODULE_P33, 8);
  delay_ms(50);

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
	
  IfxPort_togglePin(&MODULE_P33, 10);
  //IfxStm_waitTicks(&MODULE_STM0, 50*100); // 500us delay
}
