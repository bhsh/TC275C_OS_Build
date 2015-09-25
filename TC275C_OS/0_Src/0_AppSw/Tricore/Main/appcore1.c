/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore1.c
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


#pragma align 8

PTHREAD_CONTROL_BLOCK(core1_th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th1,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core1_th3,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

#pragma align restore

pthread_cond_t core1_os_cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core1_os_mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core1_os_cond2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core1_os_mutex2 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core1_os_cond3 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core1_os_mutex3 = PTHREAD_MUTEX_INITIALIZER;


volatile int core1_os_thread_test_count_TASK0;
volatile int core1_os_thread_test_count_TASK1;
volatile int core1_os_thread_test_count_TASK2;
volatile int core1_os_thread_test_count_TASK3;

volatile int core1_os_interrupt_test_flag;

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define  a test interrupt :void __interrupt(20) CPU0_SOFT1_Isr(void)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
void core1_os_idle(void* arg) {
    for (;;)
    {
        printf("Thread %d blocked\n", (int) arg);
    	core1_os_thread_test_count_TASK0++;
    	delay_ms(200);
        printf("Thread %d continued\n", (int) arg);

		/* A software interrupt is issued now!!! */
		SRC_GPSR11.U=(1<<26)|   /* SRC_GPSR11.B.SETR=1; */
			         (1<<10)|   /* SRC_GPSR11.B.SRE=1;  */
			         (1<<11)|   /* SRC_GPSR11.B.TOS=1;  */
			         (21);      /* SRC_GPSR11.B.SRPN=21; */ 
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define  a test interrupt :void __interrupt(20) CPU0_SOFT1_Isr(void)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
void __interrupt(21) CPU1_SOFT1_Isr(void) 
{
	/* The counter records the times that the interrupt is entered. */
	core1_os_interrupt_test_flag++;
	
	/* Active the threads that are blocked by core1_os_cond16. */
	/* The thread is actived in a high level interrupt. */
    pthread_cond_broadcast(&core1_os_cond3);
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: period thread
|   Define  a test interrupt :void core1_os_thread1(void* arg)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
void core1_os_thread1(void* arg) {
    for (;;) {
        printf("Thread %d blocked\n", (int) arg);

        core1_os_thread_test_count_TASK1++;

        pthread_cond_timedwait_np(&core1_os_cond1, 100,(int) arg);
        printf("Thread %d continued\n", (int) arg);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: period thread
|   Define  the thread :void core1_os_thread2(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core1_os_thread2(void* arg) {
    for (;;) {
        printf("Thread %d blocked\n", (int) arg);

        core1_os_thread_test_count_TASK2++;

        pthread_cond_timedwait_np(&core1_os_cond2, 200,(int) arg);
        printf("Thread %d continued\n", (int) arg);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrut sync
|   Define  a test interrupt :void core1_os_thread2(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core1_os_thread3(void* arg) {
    for (;;) {
		
        printf("Thread %d blocked\n", (int) arg);
        core1_os_thread_test_count_TASK3++;
        pthread_cond_wait(&core1_os_cond3);
        printf("Thread %d continued\n", (int) arg);
    }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|  
|   Define the start API :void start_core1_os(void)
|   
|
--------------------------------------------------------------------------------------*/
void start_core1_os(void)
{

	/* Create threads...  */
    pthread_create_np(core1_th0, NULL, core1_os_idle, (void*) 0);
    pthread_create_np(core1_th1, NULL, core1_os_thread1, (void*) 1);
    pthread_create_np(core1_th2, NULL, core1_os_thread2, (void*) 2);

	pthread_create_np(core1_th3, NULL, core1_os_thread3, (void*) 3);

	/* Start the core1 OS scheduler now and never return!!! */
	pthread_start_np();
}


