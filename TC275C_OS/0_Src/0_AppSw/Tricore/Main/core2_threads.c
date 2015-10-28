/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore2.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#define  THREAD_GLOBAL_CONFIG_DEFINITION DISABLE
#include "os_type.h"
#include "os.h"
#include <stdlib.h>
#include "core2_tasks.h"
#include "thread_config.h"
#include "os_thread_type.h"
#include "kernel_abstract.h"

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

PTHREAD_DEFINITION_BLOCK(2,0)
PTHREAD_DEFINITION_BLOCK(2,1)
PTHREAD_DEFINITION_BLOCK(2,2)
PTHREAD_DEFINITION_BLOCK(2,3)
PTHREAD_DEFINITION_BLOCK(2,4)
PTHREAD_DEFINITION_BLOCK(2,5)
PTHREAD_DEFINITION_BLOCK(2,6)
PTHREAD_DEFINITION_BLOCK(2,7)
PTHREAD_DEFINITION_BLOCK(2,8)
PTHREAD_DEFINITION_BLOCK(2,9)
PTHREAD_DEFINITION_BLOCK(2,10)
	
void start_core2_os(void)
{

	/* Create threads...  */
    PTHREAD_CREATION_BLOCK(core2_th0, &os_thread_attr[CORE_ID2][THREAD_ID0], core2_os_thread0, (void*) 0,CORE2_TASK0);
    PTHREAD_CREATION_BLOCK(core2_th1, &os_thread_attr[CORE_ID2][THREAD_ID1], core2_os_thread1, (void*) 1,CORE2_TASK1);
    PTHREAD_CREATION_BLOCK(core2_th2, &os_thread_attr[CORE_ID2][THREAD_ID2], core2_os_thread2, (void*) 2,CORE2_TASK2);
	PTHREAD_CREATION_BLOCK(core2_th3, &os_thread_attr[CORE_ID2][THREAD_ID3], core2_os_thread3, (void*) 3,CORE2_TASK3);
	PTHREAD_CREATION_BLOCK(core2_th4, &os_thread_attr[CORE_ID2][THREAD_ID4], core2_os_thread4, (void*) 4,CORE2_TASK4);
	PTHREAD_CREATION_BLOCK(core2_th5, &os_thread_attr[CORE_ID2][THREAD_ID5], core2_os_thread5, (void*) 5,CORE2_TASK5);
	PTHREAD_CREATION_BLOCK(core2_th6, &os_thread_attr[CORE_ID2][THREAD_ID6], core2_os_thread6, (void*) 6,CORE2_TASK6);
	PTHREAD_CREATION_BLOCK(core2_th7, &os_thread_attr[CORE_ID2][THREAD_ID7], core2_os_thread7, (void*) 7,CORE2_TASK7);
	PTHREAD_CREATION_BLOCK(core2_th8, &os_thread_attr[CORE_ID2][THREAD_ID8], core2_os_thread8, (void*) 8,CORE2_TASK8);
    PTHREAD_CREATION_BLOCK(core2_th9, &os_thread_attr[CORE_ID2][THREAD_ID9], core2_os_thread9, (void*) 9,CORE2_TASK9);
	PTHREAD_CREATION_BLOCK(core2_th10, &os_thread_attr[CORE_ID2][THREAD_ID10], core2_os_thread10, (void*) 10,CORE2_TASK10);

	/* Start the core2 OS scheduler now and never return!!! */
	PTHREAD_START_BLOCK()
}





