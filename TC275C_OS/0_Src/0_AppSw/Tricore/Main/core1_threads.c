/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore1.c
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
#include "core1_tasks.h"
#include "thread_cfg.h"
#include "os_thread_type.h"
#include "kernel_abstract.h"

#pragma align 16

PTHREAD_CONTROL_BLOCK(core1_th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th1,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th3,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th4,4,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th5,5,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th6,6,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th7,7,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th8,8,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th9,9,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th10,10,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

#pragma align restore

PTHREAD_DEFINITION_BLOCK(1,0)
PTHREAD_DEFINITION_BLOCK(1,1)
PTHREAD_DEFINITION_BLOCK(1,2)
PTHREAD_DEFINITION_BLOCK(1,3)
PTHREAD_DEFINITION_BLOCK(1,4)
PTHREAD_DEFINITION_BLOCK(1,5)
PTHREAD_DEFINITION_BLOCK(1,6)
PTHREAD_DEFINITION_BLOCK(1,7)
PTHREAD_DEFINITION_BLOCK(1,8)
PTHREAD_DEFINITION_BLOCK(1,9)
PTHREAD_DEFINITION_BLOCK(1,10)

/*-------------------------------------------------------------------------------------
|   Define the start API :void start_core1_os(void)
--------------------------------------------------------------------------------------*/
void start_core1_os(void)
{

	/* Create threads...  */
    PTHREAD_CREATION_BLOCK(core1_th0, &os_thread_attr[CORE_ID1][THREAD_ID0], core1_os_thread0, (void*) 0,CORE1_TASK0);
    PTHREAD_CREATION_BLOCK(core1_th1, &os_thread_attr[CORE_ID1][THREAD_ID1], core1_os_thread1, (void*) 1,CORE1_TASK1);
    PTHREAD_CREATION_BLOCK(core1_th2, &os_thread_attr[CORE_ID1][THREAD_ID2], core1_os_thread2, (void*) 2,CORE1_TASK2);


	PTHREAD_CREATION_BLOCK(core1_th3, &os_thread_attr[CORE_ID1][THREAD_ID3], core1_os_thread3, (void*) 3,CORE1_TASK3);
	PTHREAD_CREATION_BLOCK(core1_th4, &os_thread_attr[CORE_ID1][THREAD_ID4], core1_os_thread4, (void*) 4,CORE1_TASK4);
	PTHREAD_CREATION_BLOCK(core1_th5, &os_thread_attr[CORE_ID1][THREAD_ID5], core1_os_thread5, (void*) 5,CORE1_TASK5);
	PTHREAD_CREATION_BLOCK(core1_th6, &os_thread_attr[CORE_ID1][THREAD_ID6], core1_os_thread6, (void*) 6,CORE1_TASK6);
	PTHREAD_CREATION_BLOCK(core1_th7, &os_thread_attr[CORE_ID1][THREAD_ID7], core1_os_thread7, (void*) 7,CORE1_TASK7);
	PTHREAD_CREATION_BLOCK(core1_th8, &os_thread_attr[CORE_ID1][THREAD_ID8], core1_os_thread8, (void*) 8,CORE1_TASK8);
    PTHREAD_CREATION_BLOCK(core1_th9, &os_thread_attr[CORE_ID1][THREAD_ID9], core1_os_thread9, (void*) 9,CORE1_TASK9);
	PTHREAD_CREATION_BLOCK(core1_th10, &os_thread_attr[CORE_ID1][THREAD_ID10], core1_os_thread10, (void*) 10,CORE1_TASK10);

	/* Start the core1 OS scheduler now and never return!!! */
	PTHREAD_START_BLOCK()
}


