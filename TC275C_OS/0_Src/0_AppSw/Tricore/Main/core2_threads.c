/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore2.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/
#include "os_type.h"
#include "os.h"
#include <stdlib.h>

#include "core2_tasks.h"
//#include "thread_config.h"
#include "os_thread_type.h"
#include "kernel_abstract.h"
//#include "os_trace.h"

#pragma align 16
PTHREAD_CONTROL_BLOCK(core2_th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th1,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th3,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th4,4,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th5,5,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th6,6,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th7,7,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th8,8,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th9,9,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th10,10,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
#pragma align restore

	DEFINE_OS_THREAD(2,0)
	DEFINE_OS_THREAD(2,1)
	DEFINE_OS_THREAD(2,2)
	DEFINE_OS_THREAD(2,3)
	DEFINE_OS_THREAD(2,4)
	DEFINE_OS_THREAD(2,5)
	DEFINE_OS_THREAD(2,6)
	DEFINE_OS_THREAD(2,7)
	DEFINE_OS_THREAD(2,8)
	DEFINE_OS_THREAD(2,9)
	DEFINE_OS_THREAD(2,10)
	
void start_core2_os(void)
{

	/* Create threads...  */
    pthread_create_np(core2_th0, NULL, core2_os_thread0, (void*) 0,CORE2_TASK0);
    pthread_create_np(core2_th1, NULL, core2_os_thread1, (void*) 1,CORE2_TASK1);
    pthread_create_np(core2_th2, NULL, core2_os_thread2, (void*) 2,CORE2_TASK2);
	pthread_create_np(core2_th3, NULL, core2_os_thread3, (void*) 3,CORE2_TASK3);
	pthread_create_np(core2_th4, NULL, core2_os_thread4, (void*) 4,CORE2_TASK4);
	pthread_create_np(core2_th5, NULL, core2_os_thread5, (void*) 5,CORE2_TASK5);
	pthread_create_np(core2_th6, NULL, core2_os_thread6, (void*) 6,CORE2_TASK6);
	pthread_create_np(core2_th7, NULL, core2_os_thread7, (void*) 7,CORE2_TASK7);
	pthread_create_np(core2_th8, NULL, core2_os_thread8, (void*) 8,CORE2_TASK8);
    pthread_create_np(core2_th9, NULL, core2_os_thread9, (void*) 9,CORE2_TASK9);
	pthread_create_np(core2_th10, NULL, core2_os_thread10, (void*) 10,CORE2_TASK10);

	/* Start the core2 OS scheduler now and never return!!! */
	pthread_start_np();
}





