/*
 * app.c
 *
 *  Created on: Aug 26, 2015
 *      Author: tz68d9
 */

/*!
 ******************************************************************************
 * \verbatim
 * Copyright (c) Infineon Technologies AG 2010.
 * Infineon Technologies
 * Am Campeon 1-12
 * 85579 Neubiberg
 * Germany
 * Tel.   : 0 800 951 951 951 (Germany)
 * E-mail : support@infineon.com
 * Website: http://www.infineon.com/support
 * \endverbatim
 * \brief    Example to show how to use pthread library
 * \author   Martin Schrape
 * \version  1.0
 * \date     2010-03-18
 * \mainpage
 * \file  main.c
 */
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
// define thread name, priority, policy, stack size
//PTHREAD_CONTROL_BLOCK(th1,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th2,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th3,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)

//PTHREAD_CONTROL_BLOCK(th1,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th2,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th3,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th4,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)

// define thread name, priority, policy, stack size
//PTHREAD_CONTROL_BLOCK(th0,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th1,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th3,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th4,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th5,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th6,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th7,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

// define thread name, priority, policy, stack size
//PTHREAD_CONTROL_BLOCK(th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th1,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th3,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th4,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th5,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th6,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th7,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th8,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th9,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th10,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

PTHREAD_CONTROL_BLOCK(th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th1,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th3,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th4,4,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th5,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th6,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th7,4,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
#pragma align restore


#if 0
pthread_mutex_t    mutex = PTHREAD_MUTEX_INITIALIZER;
int                i,j,k,l;
int volatile       uselock=1;

void thread(void* arg) {
    for (;;) {
        if (uselock)
            pthread_mutex_lock(&mutex);
        ++i; ++j; ++k; ++l;
        if (uselock)
           pthread_mutex_unlock(&mutex);
    }
}

void thread1(void* arg) {
    uint32_t volatile counter = 0;
    for (;;) {
        counter++;
  //      printf("Thread %d counter = %d\n", (int) arg, counter);
        delay_ms(50);
        IfxPort_togglePin(&MODULE_P33, 8);
        //IfxPort_togglePin(&MODULE_P33, 10);

        switch_context();
    }
}

int thread2_read_trap_return;
int thread2_test_counter;

void thread2(void* arg) {
    uint32_t volatile counter = 0;
    for (;;) {
        counter++;
 //       printf("Thread %d counter = %d\n", (int) arg, counter);
        delay_ms(100);
        IfxPort_togglePin(&MODULE_P33, 9);

        //call_trap6_interface();
        thread2_test_counter++;

        switch_context();
    }
}

void thread3(void* arg) {
    uint32_t volatile counter = 0;
    for (;;) {
        counter++;
 //       printf("Thread %d counter = %d\n", (int) arg, counter);
        delay_ms(100);
        IfxPort_togglePin(&MODULE_P33, 11);

        //call_trap6_interface();
        thread2_test_counter++;

        switch_context();
    }
}


uint32_t volatile conditionMet = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
uint32_t test_flag=0;

void thread1(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        conditionMet = 1;
        puts("Wake up all waiters...");
        delay_ms(600);
        test_flag=111;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

void thread2(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        conditionMet = 0;
        while (!conditionMet) {
            printf("Thread %d blocked\n", (int) arg);
            delay_ms(600);
            test_flag++;
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}
#endif


#if 0
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int thread_test_count;
volatile int thread_test_count1;

volatile int interrupt_test1=0;
volatile int interrupt_test1_condition=0;

void __interrupt(20) CPU0_SOFT1_Isr(void) {

	//interrupt_test1=1;

    puts("Wake up all waiters...");
    thread_test_count=100;
    pthread_cond_broadcast(&cond);

    interrupt_test1=0;
}
int flag;
void idle(void* arg) {
    for (;;)
    {
    	thread_test_count1++;
    	delay_ms(500);
    	//if(flag==1)
    	//{
    	//  flag=0;
          SRC_GPSR01.B.SETR=1;
          SRC_GPSR01.B.SRE=1;
          SRC_GPSR01.B.TOS=0;
          SRC_GPSR01.B.SRPN=20;
    	//}
    }
}

void thread(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count++;
        delay_ms(200);
        pthread_cond_wait(&cond, &mutex);
        // test if the task is sync with the interrupt.
//        if(interrupt_test1==1)
//        {
//        	interrupt_test1_condition++;
//        }
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex);
    }
}
#endif

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond5 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex5 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond6 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex6 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond7 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex7 = PTHREAD_MUTEX_INITIALIZER;


volatile int thread_test_count1=0;

volatile int thread_test_count_TASK0=0;
volatile int thread_test_count_TASK1=0;
volatile int thread_test_count_TASK2=0;
volatile int thread_test_count_TASK3=0;
volatile int thread_test_count_TASK4=0;
volatile int thread_test_count_TASK5=0;
volatile int thread_test_count_TASK6=0;
volatile int thread_test_count_TASK7=0;


void idle(void* arg) {
    for (;;)
    {

    	thread_test_count_TASK0++;
    	delay_ms(200);

    }
}

void thread1(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex1);
        printf("Thread %d blocked\n", (int) arg);
		
        thread_test_count_TASK1++;

        pthread_cond_timedwait_np(&cond1, &mutex1, 10,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex1);
    }
}

void thread2(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex2);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK2++;
        pthread_cond_timedwait_np(&cond2, &mutex2, 20,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex2);
    }
}

void thread3(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex3);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK3++;
        pthread_cond_timedwait_np(&cond3, &mutex3, 40,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex3);
    }
}

void thread4(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex4);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK4++;
        pthread_cond_timedwait_np(&cond4, &mutex4, 80,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex4);
    }
}

void thread5(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex5);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK5++;
        pthread_cond_timedwait_np(&cond5, &mutex5, 320,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex5);
    }
}

void thread6(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex6);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK6++;
        pthread_cond_timedwait_np(&cond6, &mutex6, 640,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex6);
    }
}

void thread7(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex7);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK7++;
        pthread_cond_timedwait_np(&cond7, &mutex7, 1280,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex7);
    }
}

void start_core0_os(void) {

   // printf("Example 1: Creates 2 threads with round-robin policy.\n");

   // pthread_create_np(th1, NULL, thread1, (void*)1);
   // pthread_create_np(th2, NULL, thread2, (void*)2);
   // pthread_create_np(th3, NULL, thread3, (void*)3);

   // pthread_create_np(th3, NULL, thread3, (void*)3);

   //printf("Example 2: Creates 4 threads with round-robin policy."
   //        "Demonstrating serialization through mutex variables.\n");

   //pthread_create_np(th1, NULL, thread, (void*) 1);
   //pthread_create_np(th2, NULL, thread, (void*) 2);
   //pthread_create_np(th3, NULL, thread, (void*) 2);
   //pthread_create_np(th4, NULL, thread, (void*) 2);


    //printf("Example 3: Create 8 threads with first-in-first-out policy."
    //       "Shows how to use a condition variable to wake up a thread\n");

    //pthread_create_np(th0, NULL, thread1, (void*) 0);
    //pthread_create_np(th1, NULL, thread2, (void*) 1);
    //pthread_create_np(th2, NULL, thread2, (void*) 2);
    //pthread_create_np(th3, NULL, thread2, (void*) 3);
    //pthread_create_np(th4, NULL, thread2, (void*) 4);
    //pthread_create_np(th5, NULL, thread2, (void*) 5);
    //pthread_create_np(th6, NULL, thread2, (void*) 6);
    //pthread_create_np(th7, NULL, thread2, (void*) 7);
    //printf("Example 4: Create 3 threads with first-in-first-out policy."
    //        "Shows how to use a condition variable to wake up a thread from an interrupt.\n");

    //pthread_create_np(th0, NULL, idle, (void*) 0);
    //pthread_create_np(th1, NULL, thread, (void*) 1);
    //pthread_create_np(th2, NULL, thread, (void*) 2);
    //pthread_create_np(th3, NULL, thread, (void*) 3);
    //pthread_create_np(th4, NULL, thread, (void*) 4);
    //pthread_create_np(th5, NULL, thread, (void*) 5);
    //pthread_create_np(th6, NULL, thread, (void*) 6);
    //pthread_create_np(th7, NULL, thread, (void*) 7);
    //pthread_create_np(th8, NULL, thread, (void*) 8);
    //pthread_create_np(th9, NULL, thread, (void*) 9);
    //pthread_create_np(th10, NULL, thread, (void*) 10);




    printf("Example 5: Create 3 threads with first-in-first-out policy."
           "Shows how to block a thread until the condition is signaled or until a timeout period elapsed.\n");

    pthread_create_np(th0, NULL, idle, (void*) 0);
    pthread_create_np(th1, NULL, thread1, (void*) 1);
    pthread_create_np(th2, NULL, thread2, (void*) 2);
	pthread_create_np(th3, NULL, thread3, (void*) 3);
	pthread_create_np(th4, NULL, thread4, (void*) 4);
	pthread_create_np(th5, NULL, thread5, (void*) 5);
	pthread_create_np(th6, NULL, thread6, (void*) 6);
	pthread_create_np(th7, NULL, thread7, (void*) 7);

	pthread_start_np();
}


