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

PTHREAD_CONTROL_BLOCK(core1_th0, CORE1_THREAD0_PRIORITY,SCHED_FIFO,CORE1_THREAD0_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th1, CORE1_THREAD1_PRIORITY,SCHED_FIFO,CORE1_THREAD1_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th2, CORE1_THREAD2_PRIORITY,SCHED_FIFO,CORE1_THREAD2_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th3, CORE1_THREAD3_PRIORITY,SCHED_FIFO,CORE1_THREAD3_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th4, CORE1_THREAD4_PRIORITY,SCHED_FIFO,CORE1_THREAD4_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th5, CORE1_THREAD5_PRIORITY,SCHED_FIFO,CORE1_THREAD5_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th6, CORE1_THREAD6_PRIORITY,SCHED_FIFO,CORE1_THREAD6_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th7, CORE1_THREAD7_PRIORITY,SCHED_FIFO,CORE1_THREAD7_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th8, CORE1_THREAD8_PRIORITY,SCHED_FIFO,CORE1_THREAD8_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th9, CORE1_THREAD9_PRIORITY,SCHED_FIFO,CORE1_THREAD9_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th10,CORE1_THREAD10_PRIORITY,SCHED_FIFO,CORE1_THREAD10_STACK_SIZE)

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
    PTHREAD_CREATION_BLOCK(core1_th0, &os_thread_attr[CORE_ID1][THREAD_ID0], core1_os_thread0,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID0].task_id,CORE1_TASK0);
    PTHREAD_CREATION_BLOCK(core1_th1, &os_thread_attr[CORE_ID1][THREAD_ID1], core1_os_thread1,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID1].task_id,CORE1_TASK1);
    PTHREAD_CREATION_BLOCK(core1_th2, &os_thread_attr[CORE_ID1][THREAD_ID2], core1_os_thread2,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID2].task_id,CORE1_TASK2);
	PTHREAD_CREATION_BLOCK(core1_th3, &os_thread_attr[CORE_ID1][THREAD_ID3], core1_os_thread3,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID3].task_id,CORE1_TASK3);
	PTHREAD_CREATION_BLOCK(core1_th4, &os_thread_attr[CORE_ID1][THREAD_ID4], core1_os_thread4,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID4].task_id,CORE1_TASK4);
	PTHREAD_CREATION_BLOCK(core1_th5, &os_thread_attr[CORE_ID1][THREAD_ID5], core1_os_thread5,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID5].task_id,CORE1_TASK5);
	PTHREAD_CREATION_BLOCK(core1_th6, &os_thread_attr[CORE_ID1][THREAD_ID6], core1_os_thread6,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID6].task_id,CORE1_TASK6);
	PTHREAD_CREATION_BLOCK(core1_th7, &os_thread_attr[CORE_ID1][THREAD_ID7], core1_os_thread7,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID7].task_id,CORE1_TASK7);
	PTHREAD_CREATION_BLOCK(core1_th8, &os_thread_attr[CORE_ID1][THREAD_ID8], core1_os_thread8,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID8].task_id,CORE1_TASK8);
    PTHREAD_CREATION_BLOCK(core1_th9, &os_thread_attr[CORE_ID1][THREAD_ID9], core1_os_thread9,  (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID9].task_id,CORE1_TASK9);
	PTHREAD_CREATION_BLOCK(core1_th10,&os_thread_attr[CORE_ID1][THREAD_ID10],core1_os_thread10, (void*)os_pthread_init_config_database[CORE_ID1][THREAD_ID10].task_id,CORE1_TASK10);

	/* Start the core1 OS scheduler now and never return!!! */
	PTHREAD_START_BLOCK()
}


