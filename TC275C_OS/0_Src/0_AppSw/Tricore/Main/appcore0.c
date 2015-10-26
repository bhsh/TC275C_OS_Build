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
//#include <stdio.h>
//#include "Cpu0_Main.h"
//#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
//#include "communication.h"


//#include "Compilers.h"
//#include "Cpu\Std\IfxCpu_Intrinsics.h"
//#include "Port\Io\IfxPort_Io.h"
//#include "Stm\Std\IfxStm.h"
//#include "Src\Std\IfxSrc.h"


#include "os_trace.h"
#include "os_interface.h"
#include "core0_tasks.h"

#include "task_config.h"
#include "kernel_abstract.h"


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

const pthread_config_t core0_pthread_init_config_database[TASK_ID_MAX] =
{
  {TASK_ID0,  CORE0_TASK0_TYPE,  CORE0_TASK0_PERIOD,  CORE0_TASK0_ACTIVED },
  {TASK_ID1,  CORE0_TASK1_TYPE,  CORE0_TASK1_PERIOD,  CORE0_TASK1_ACTIVED },
  {TASK_ID2,  CORE0_TASK2_TYPE,  CORE0_TASK2_PERIOD,  CORE0_TASK2_ACTIVED },
  {TASK_ID3,  CORE0_TASK3_TYPE,  CORE0_TASK3_PERIOD,  CORE0_TASK3_ACTIVED },
  {TASK_ID4,  CORE0_TASK4_TYPE,  CORE0_TASK4_PERIOD,  CORE0_TASK4_ACTIVED },
  {TASK_ID5,  CORE0_TASK5_TYPE,  CORE0_TASK5_PERIOD,  CORE0_TASK5_ACTIVED },  
  {TASK_ID6,  CORE0_TASK6_TYPE,  CORE0_TASK6_PERIOD,  CORE0_TASK6_ACTIVED },
  {TASK_ID7,  CORE0_TASK7_TYPE,  CORE0_TASK7_PERIOD,  CORE0_TASK7_ACTIVED },
  {TASK_ID8,  CORE0_TASK8_TYPE,  CORE0_TASK8_PERIOD,  CORE0_TASK8_ACTIVED },
  {TASK_ID9,  CORE0_TASK9_TYPE,  CORE0_TASK9_PERIOD,  CORE0_TASK9_ACTIVED },
  {TASK_ID10, CORE0_TASK10_TYPE, CORE0_TASK10_PERIOD, CORE0_TASK10_ACTIVED},
};

pthread_cond_t core0_os_cond_def[11] =
  { 
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
	 CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,
     CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER
  };

/*-------------------------------------------------------------------------------------
|   Define thread 0 
--------------------------------------------------------------------------------------*/
void core0_os_idle(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}
/*-------------------------------------------------------------------------------------
|   Define thread 1 
--------------------------------------------------------------------------------------*/
void core0_os_thread1(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}
/*-------------------------------------------------------------------------------------
|   Define thread 2 
--------------------------------------------------------------------------------------*/
void core0_os_thread2(void* arg,task_ptr_t task)
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}
/*-------------------------------------------------------------------------------------
|   Define thread 3 
--------------------------------------------------------------------------------------*/
void core0_os_thread3(void* arg,task_ptr_t task) 
{
    thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 4 
--------------------------------------------------------------------------------------*/
void core0_os_thread4(void* arg,task_ptr_t task)
{
    thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 5 
--------------------------------------------------------------------------------------*/
void core0_os_thread5(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 6 
--------------------------------------------------------------------------------------*/
void core0_os_thread6(void* arg,task_ptr_t task)
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 7 
--------------------------------------------------------------------------------------*/
void core0_os_thread7(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 8 
--------------------------------------------------------------------------------------*/
void core0_os_thread8(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 9 
--------------------------------------------------------------------------------------*/
void core0_os_thread9(void* arg,task_ptr_t task) 
{
	thread_initialization();
    thread_taskcallback();
    thread_termination();
}

/*-------------------------------------------------------------------------------------
|   Define thread 10 
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


void thread_done_before_task(pthread_config_t *pthread_config)
{ 
  if(pthread_config->type == TASK_EVENT)
  {
      pthread_cond_wait(&core0_os_cond_def[pthread_config->task_id]);
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
  os_trace_task_time_begin(pthread_config->task_id);
}

void thread_done_after_task(pthread_config_t *pthread_config)
{ 	
  /* Trace */
  os_trace_task_time_end(pthread_config->task_id);

  if(pthread_config->type == TASK_EVENT)
  {
      /* Active thread */
	  pthread_cond_broadcast(&core0_os_cond_def[pthread_config->actived_task_id]);
  }
  else if((pthread_config->type == TASK_PERIODIC)||
  	      (pthread_config->type == NO_DEFINITION))
  {
      /* Do nothing */
  }
}


