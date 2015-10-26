/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore0.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/
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

#include "task_config.h"


void thread_done_before_task(pthread_config_t *pthread_config);
void thread_done_after_task(pthread_config_t *pthread_config);
#pragma align 16

// period threads...
PTHREAD_CONTROL_BLOCK(core0_os_th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th1,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th3,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th4,4,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th5,5,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th6,6,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th7,7,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th8,8,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th9,9,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th10,10,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

#pragma align restore

pthread_cond_t core0_os_cond1 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond2 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond3 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond4 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond5 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond6 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond7 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond8 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond9 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond10 = CORE0_PTHREAD_COND_INITIALIZER;

pthread_cond_t core0_os_cond[TASK_ID10] =
  { 
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
	 CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER
  };

volatile int core0_os_thread_test_count_TASK0=0;
volatile int core0_os_thread_test_count_TASK1=0;
volatile int core0_os_thread_test_count_TASK2=0;
volatile int core0_os_thread_test_count_TASK3=0;
volatile int core0_os_thread_test_count_TASK4=0;
volatile int core0_os_thread_test_count_TASK5=0;
volatile int core0_os_thread_test_count_TASK6=0;
volatile int core0_os_thread_test_count_TASK7=0;
volatile int core0_os_thread_test_count_TASK8=0;
volatile int core0_os_thread_test_count_TASK9=0;
volatile int core0_os_thread_test_count_TASK10=0;

TsUTIL_ThruPutMeasurement core0_thread_execution_time[E_MaxItems];

volatile uint32 tick_begin_test1;
volatile uint32 tick_begin_test2;
volatile uint32 tick_begin_test3;

#define thread_initialization();          pthread_config_t pthread_config =                      \
	                                               core0_pthread_init_config_database[(int)arg]; \
                                          for (;;)                                               \
                                          {                                                      \
								 		  	thread_done_before_task(&pthread_config); 
#define thread_taskcallback();              task(&pthread_config);          	                                         
#define thread_termination();               thread_done_after_task(&pthread_config);             \
	                                      }

 
/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 0 :void core0_os_idle(void* arg) 
|
--------------------------------------------------------------------------------------*/


int core0_math_test(int a,int b)
{

 return (a+b+2);

}

void core0_os_idle(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define  a test interrupt :void __interrupt(20) CPU0_SOFT1_Isr(void)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
volatile int interrupt_test_flag;
void __interrupt(20) CPU0_SOFT1_Isr(void) 
{

	interrupt_test_flag++;
    //pthread_cond_broadcast(&core0_os_cond4);
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   test code  that is used to test the blocked time function of core0 os
|   threads from 0-10 is used.
|
|
--------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 1 :void core0_os_thread1(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread1(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}
//#pragma align restore
//#pragma tradeoff restore
//#pragma endoptimize
//#pragma endprotect

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 2 :void core0_os_thread2(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread2(void* arg,task_ptr_t task)
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 3 :void core0_os_thread3(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread3(void* arg,task_ptr_t task) 
{
    thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 4 :void core0_os_thread4(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread4(void* arg,task_ptr_t task)
{
    thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 5 :void core0_os_thread5(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread5(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 6 :void core0_os_thread6(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread6(void* arg,task_ptr_t task)
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 7 :void core0_os_thread7(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread7(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 8 :void core0_os_thread8(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread8(void* arg,task_ptr_t task) 
{
	thread_initialization()
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 9 :void core0_os_thread9(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread9(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 10 :void core0_os_thread10(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread10(void* arg,task_ptr_t task) 
{    
	thread_initialization();
    thread_taskcallback();
    thread_termination();
 }

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: start OS
|   Define OS API :void start_core0_os(void) 
|
--------------------------------------------------------------------------------------*/
void thread_done_before_task(pthread_config_t *pthread_config)
{ 
  if(pthread_config->type == TASK_EVENT)
  {
      pthread_cond_wait(&core0_os_cond[pthread_config->task_id]);
  }
  else if(pthread_config->type == TASK_PERIODIC)
  {
	  pthread_cond_timedwait_np((uint16_t)(pthread_config->period));
  }
  else if(pthread_config->type == NO_DEFINITION)
  {
     /* Do nothing. */
  }
  /* trace */
  os_trace_begin(pthread_config->task_id);
}

void thread_done_after_task(pthread_config_t *pthread_config)
{ 	
  /* Trace */
  os_trace_end(pthread_config->task_id);

  if(pthread_config->type == TASK_EVENT)
  {
      /* Active thread */
	  pthread_cond_broadcast(&core0_os_cond[pthread_config->actived_task_id]);
  }
  else if((pthread_config->type == TASK_PERIODIC)||
  	      (pthread_config->type == NO_DEFINITION))
  {
      /* Do nothing */
  }
}

const pthread_attr_t core0_os_th0_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th1_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th2_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th3_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th4_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th5_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th6_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th7_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th8_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th9_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th10_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};

void start_core0_os(void) {

    pthread_create_np(core0_os_th0, &core0_os_th0_attr, core0_os_idle, (void*) 0,CORE0_TASK0);
    pthread_create_np(core0_os_th1, &core0_os_th1_attr, core0_os_thread1, (void*) 1,CORE0_TASK1);	
    pthread_create_np(core0_os_th2, &core0_os_th2_attr, core0_os_thread2, (void*) 2,CORE0_TASK2);
#if 0	

	pthread_create_np(core0_os_th3, &core0_os_th3_attr, core0_os_thread3, (void*) 3,CORE0_TASK3);

	pthread_create_np(core0_os_th4, &core0_os_th4_attr, core0_os_thread4, (void*) 4,CORE0_TASK4);
	pthread_create_np(core0_os_th5, &core0_os_th5_attr, core0_os_thread5, (void*) 5,CORE0_TASK5);

	pthread_create_np(core0_os_th6, &core0_os_th6_attr, core0_os_thread6, (void*) 6,CORE0_TASK6);
	pthread_create_np(core0_os_th7, &core0_os_th7_attr, core0_os_thread7, (void*) 7,CORE0_TASK7);
    pthread_create_np(core0_os_th8, &core0_os_th8_attr, core0_os_thread8, (void*) 8,CORE0_TASK8);
    pthread_create_np(core0_os_th9, &core0_os_th9_attr, core0_os_thread9, (void*) 9,CORE0_TASK9);

#endif
	pthread_create_np(core0_os_th10, &core0_os_th10_attr, core0_os_thread10,(void*) 10,CORE0_TASK10);


	pthread_start_np();
}


