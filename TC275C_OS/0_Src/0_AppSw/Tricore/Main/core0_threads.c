/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore0.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#define  THREAD_GLOBAL_CONFIG_DEFINITION ENABLE
#include "os_type.h"
#include "os.h"
#include <stdlib.h>
#include "core0_tasks.h"
#include "thread_config.h"
#include "kernel_abstract.h"
#include "os_trace.h"


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

PTHREAD_DEFINITION_BLOCK(0,0)
PTHREAD_DEFINITION_BLOCK(0,1)
PTHREAD_DEFINITION_BLOCK(0,2)
PTHREAD_DEFINITION_BLOCK(0,3)
PTHREAD_DEFINITION_BLOCK(0,4)
PTHREAD_DEFINITION_BLOCK(0,5)
PTHREAD_DEFINITION_BLOCK(0,6)
PTHREAD_DEFINITION_BLOCK(0,7)
PTHREAD_DEFINITION_BLOCK(0,8)
PTHREAD_DEFINITION_BLOCK(0,9)
PTHREAD_DEFINITION_BLOCK(0,10)

void start_core0_os(void) {

    PTHREAD_CREATION_BLOCK(core0_os_th0, &os_thread_attr[CORE_ID0][THREAD_ID0], core0_os_thread0, (void*) 0,CORE0_TASK0);
    PTHREAD_CREATION_BLOCK(core0_os_th1, &os_thread_attr[CORE_ID0][THREAD_ID1], core0_os_thread1, (void*) 1,CORE0_TASK1);	
    PTHREAD_CREATION_BLOCK(core0_os_th2, &os_thread_attr[CORE_ID0][THREAD_ID2], core0_os_thread2, (void*) 2,CORE0_TASK2);
#if 0	

	PTHREAD_CREATION_BLOCK(core0_os_th3, &os_thread_attr[CORE_ID0][THREAD_ID3], core0_os_thread3, (void*) 3,CORE0_TASK3);

	PTHREAD_CREATION_BLOCK(core0_os_th4, &os_thread_attr[CORE_ID0][THREAD_ID4], core0_os_thread4, (void*) 4,CORE0_TASK4);
	PTHREAD_CREATION_BLOCK(core0_os_th5, &os_thread_attr[CORE_ID0][THREAD_ID5], core0_os_thread5, (void*) 5,CORE0_TASK5);

	PTHREAD_CREATION_BLOCK(core0_os_th6, &os_thread_attr[CORE_ID0][THREAD_ID6], core0_os_thread6, (void*) 6,CORE0_TASK6);
	PTHREAD_CREATION_BLOCK(core0_os_th7, &os_thread_attr[CORE_ID0][THREAD_ID7], core0_os_thread7, (void*) 7,CORE0_TASK7);
    PTHREAD_CREATION_BLOCK(core0_os_th8, &os_thread_attr[CORE_ID0][THREAD_ID8], core0_os_thread8, (void*) 8,CORE0_TASK8);
    PTHREAD_CREATION_BLOCK(core0_os_th9, &os_thread_attr[CORE_ID0][THREAD_ID9], core0_os_thread9, (void*) 9,CORE0_TASK9);

#endif
	PTHREAD_CREATION_BLOCK(core0_os_th10, &os_thread_attr[CORE_ID0][THREAD_ID10], core0_os_thread10,(void*) 10,CORE0_TASK10);

	PTHREAD_START_BLOCK();
}


