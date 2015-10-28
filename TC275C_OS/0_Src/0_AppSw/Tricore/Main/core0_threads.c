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
#include "thread_cfg.h"
#include "kernel_abstract.h"
#include "os_trace.h"


#pragma align 16

// period threads...
PTHREAD_CONTROL_BLOCK(core0_os_th0,CORE0_THREAD0_PRIORITY,SCHED_FIFO,CORE0_THREAD0_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th1, CORE0_THREAD1_PRIORITY,SCHED_FIFO,CORE0_THREAD1_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th2, CORE0_THREAD2_PRIORITY,SCHED_FIFO,CORE0_THREAD2_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th3, CORE0_THREAD3_PRIORITY,SCHED_FIFO,CORE0_THREAD3_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th4, CORE0_THREAD4_PRIORITY,SCHED_FIFO,CORE0_THREAD4_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th5, CORE0_THREAD5_PRIORITY,SCHED_FIFO,CORE0_THREAD5_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th6, CORE0_THREAD6_PRIORITY,SCHED_FIFO,CORE0_THREAD6_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th7, CORE0_THREAD7_PRIORITY,SCHED_FIFO,CORE0_THREAD7_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th8, CORE0_THREAD8_PRIORITY,SCHED_FIFO,CORE0_THREAD8_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th9, CORE0_THREAD9_PRIORITY,SCHED_FIFO,CORE0_THREAD9_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th10,CORE0_THREAD10_PRIORITY,SCHED_FIFO,CORE0_THREAD10_STACK_SIZE)

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

    PTHREAD_CREATION_BLOCK(core0_os_th0, &os_thread_attr[CORE_ID0][THREAD_ID0], core0_os_thread0, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID0].task_id,CORE0_TASK0);
    PTHREAD_CREATION_BLOCK(core0_os_th1, &os_thread_attr[CORE_ID0][THREAD_ID1], core0_os_thread1, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID1].task_id,CORE0_TASK1);	
    PTHREAD_CREATION_BLOCK(core0_os_th2, &os_thread_attr[CORE_ID0][THREAD_ID2], core0_os_thread2, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID2].task_id,CORE0_TASK2);
#if 0	

	PTHREAD_CREATION_BLOCK(core0_os_th3, &os_thread_attr[CORE_ID0][THREAD_ID3], core0_os_thread3, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID3].task_id,CORE0_TASK3);

	PTHREAD_CREATION_BLOCK(core0_os_th4, &os_thread_attr[CORE_ID0][THREAD_ID4], core0_os_thread4, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID4].task_id,CORE0_TASK4);
	PTHREAD_CREATION_BLOCK(core0_os_th5, &os_thread_attr[CORE_ID0][THREAD_ID5], core0_os_thread5, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID5].task_id,CORE0_TASK5);

	PTHREAD_CREATION_BLOCK(core0_os_th6, &os_thread_attr[CORE_ID0][THREAD_ID6], core0_os_thread6, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID6].task_id,CORE0_TASK6);
	PTHREAD_CREATION_BLOCK(core0_os_th7, &os_thread_attr[CORE_ID0][THREAD_ID7], core0_os_thread7, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID7].task_id,CORE0_TASK7);
    PTHREAD_CREATION_BLOCK(core0_os_th8, &os_thread_attr[CORE_ID0][THREAD_ID8], core0_os_thread8, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID8].task_id,CORE0_TASK8);
    PTHREAD_CREATION_BLOCK(core0_os_th9, &os_thread_attr[CORE_ID0][THREAD_ID9], core0_os_thread9, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID9].task_id,CORE0_TASK9);

#endif
	PTHREAD_CREATION_BLOCK(core0_os_th10, &os_thread_attr[CORE_ID0][THREAD_ID10], core0_os_thread10,(void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID10].task_id,CORE0_TASK10);

	PTHREAD_START_BLOCK();
}


