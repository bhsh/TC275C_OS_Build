/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore2.c
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

pthread_cond_t core2_os_cond1   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond2   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond3   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond4   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond5   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond6   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond7   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond8   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond9   = CORE2_PTHREAD_COND_INITIALIZER;
pthread_cond_t core2_os_cond10  = CORE2_PTHREAD_COND_INITIALIZER;

volatile int core2_os_thread_test_count_TASK0;
volatile int core2_os_thread_test_count_TASK1;
volatile int core2_os_thread_test_count_TASK2;
volatile int core2_os_thread_test_count_TASK3;
volatile int core2_os_thread_test_count_TASK4;
volatile int core2_os_thread_test_count_TASK5;
volatile int core2_os_thread_test_count_TASK6;
volatile int core2_os_thread_test_count_TASK7;
volatile int core2_os_thread_test_count_TASK8;
volatile int core2_os_thread_test_count_TASK9;
volatile int core2_os_thread_test_count_TASK10;

volatile int core2_os_interrupt_test_flag;

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define  a test interrupt :void __interrupt(20) CPU0_SOFT1_Isr(void)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
void core2_os_idle(void* arg) {
    for (;;)
    {
    	core2_os_thread_test_count_TASK0++;
    	delay_ms(200);

		/* A software interrupt is issued now!!! */
		SRC_GPSR21.U=(1<<26)|   /* SRC_GPSR21.B.SETR=1; */
			         (1<<10)|   /* SRC_GPSR21.B.SRE=1;  */
			         (2<<11)|   /* SRC_GPSR21.B.TOS=2;  */
			         (22);      /* SRC_GPSR21.B.SRPN=22; */ 
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define  a test interrupt :void __interrupt(22) CPU2_SOFT1_Isr(void)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
void __interrupt(22) CPU2_SOFT1_Isr(void) 
{
	/* The counter records the times that the interrupt is entered. */
	core2_os_interrupt_test_flag++;
	
	/* Active the threads that are blocked by core2_os_cond16. */
	/* The thread is actived in a high level interrupt. */
    pthread_cond_broadcast(&core2_os_cond3);
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: period thread
|   Define  a test interrupt :void core2_os_thread1(void* arg)
|   This is only a test interrupt
|
--------------------------------------------------------------------------------------*/
void core2_os_thread1(void* arg) {
    for (;;) {

        core2_os_thread_test_count_TASK1++;

        pthread_cond_timedwait_np(300);

		IfxPort_togglePin(&MODULE_P33, 10);
		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: period thread
|   Define  the thread :void core2_os_thread2(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread2(void* arg) {
    for (;;) {

        core2_os_thread_test_count_TASK2++;

        pthread_cond_timedwait_np(200);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrut sync
|   Define  a test interrupt :void core2_os_thread2(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread3(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK3++;
        pthread_cond_wait(&core2_os_cond3);

		/* What is really done by thread3 finally. */
		pthread_cond_broadcast(&core2_os_cond4);    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread4(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread4(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK4++;
        pthread_cond_wait(&core2_os_cond4);

		/* What is really done by thread4 finally. */
		pthread_cond_broadcast(&core2_os_cond5);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread5(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread5(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK5++;
        pthread_cond_wait(&core2_os_cond5);

		/* What is really done by thread5 finally. */
		pthread_cond_broadcast(&core2_os_cond6);    
	}
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread6(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread6(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK6++;
        pthread_cond_wait(&core2_os_cond6);

		/* What is really done by thread6 finally. */
		pthread_cond_broadcast(&core2_os_cond7);
	}
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread7(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread7(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK7++;
        pthread_cond_wait(&core2_os_cond7);

		/* What is really done by thread7 finally. */
		pthread_cond_broadcast(&core2_os_cond8);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread8(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread8(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK8++;
        pthread_cond_wait(&core2_os_cond8);

		/* What is really done by thread8 finally. */
		pthread_cond_broadcast(&core2_os_cond9);    
	}
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread9(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread9(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK9++;
        pthread_cond_wait(&core2_os_cond9);

	    /* What is really done by thread9 finally. */
		pthread_cond_broadcast(&core2_os_cond10);    
	}
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: thread sync
|   Define  a test thread :void core2_os_thread10(void* arg)
|   This is only a test task
|
--------------------------------------------------------------------------------------*/
void core2_os_thread10(void* arg) {
    for (;;) {
		
        core2_os_thread_test_count_TASK10++;
        pthread_cond_wait(&core2_os_cond10);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|  
|   Define the start API :void start_core2_os(void)
|   
|
--------------------------------------------------------------------------------------*/
void start_core2_os(void)
{

	/* Create threads...  */
    pthread_create_np(core2_th0, NULL, core2_os_idle,    (void*) 0);
    pthread_create_np(core2_th1, NULL, core2_os_thread1, (void*) 1);
    pthread_create_np(core2_th2, NULL, core2_os_thread2, (void*) 2);


	pthread_create_np(core2_th3, NULL, core2_os_thread3, (void*) 3);
	pthread_create_np(core2_th4, NULL, core2_os_thread4, (void*) 4);
	pthread_create_np(core2_th5, NULL, core2_os_thread5, (void*) 5);
	pthread_create_np(core2_th6, NULL, core2_os_thread6, (void*) 6);
	pthread_create_np(core2_th7, NULL, core2_os_thread7, (void*) 7);
	pthread_create_np(core2_th8, NULL, core2_os_thread8, (void*) 8);
    pthread_create_np(core2_th9, NULL, core2_os_thread9, (void*) 9);
	pthread_create_np(core2_th10, NULL, core2_os_thread10, (void*) 10);

	/* Start the core2 OS scheduler now and never return!!! */
	pthread_start_np();
}





