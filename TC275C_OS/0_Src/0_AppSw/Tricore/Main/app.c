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

PTHREAD_CONTROL_BLOCK(th1,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th3,3,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th4,4,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th5,5,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th6,6,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th7,7,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th8,8,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th9,9,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th10,10,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)


PTHREAD_CONTROL_BLOCK(th11,11,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th12,12,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th13,13,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th14,14,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th15,15,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th16,16,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th17,17,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th18,18,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th19,19,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th20,20,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

PTHREAD_CONTROL_BLOCK(th21,21,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th22,22,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th23,23,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th24,24,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th25,25,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th26,26,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th27,27,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th28,28,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th29,29,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th30,30,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th31,31,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

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

pthread_cond_t cond8 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex8 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond9 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex9 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond10 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex10 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond11 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex11 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond12 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex12 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond13 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex13 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond14 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex14 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond15 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex15 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond16 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex16 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond17 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex17 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond18 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex18 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond19 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex19 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond20 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex20 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond21 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex21 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond22 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex22 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond23 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex23 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond24 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex24 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond25 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex25 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond26 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex26 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond27 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex27 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond28 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex28 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond29 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex29 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond30 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex30 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond31 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex31 = PTHREAD_MUTEX_INITIALIZER;


volatile int thread_test_count_TASK0=0;

volatile int thread_test_count_TASK1=0;
volatile int thread_test_count_TASK2=0;
volatile int thread_test_count_TASK3=0;
volatile int thread_test_count_TASK4=0;
volatile int thread_test_count_TASK5=0;
volatile int thread_test_count_TASK6=0;
volatile int thread_test_count_TASK7=0;
volatile int thread_test_count_TASK8=0;
volatile int thread_test_count_TASK9=0;
volatile int thread_test_count_TASK10=0;


volatile int thread_test_count_TASK11=0;
volatile int thread_test_count_TASK12=0;
volatile int thread_test_count_TASK13=0;
volatile int thread_test_count_TASK14=0;
volatile int thread_test_count_TASK15=0;
volatile int thread_test_count_TASK16=0;
volatile int thread_test_count_TASK17=0;
volatile int thread_test_count_TASK18=0;
volatile int thread_test_count_TASK19=0;
volatile int thread_test_count_TASK20=0;

volatile int thread_test_count_TASK21=0;
volatile int thread_test_count_TASK22=0;
volatile int thread_test_count_TASK23=0;
volatile int thread_test_count_TASK24=0;
volatile int thread_test_count_TASK25=0;
volatile int thread_test_count_TASK26=0;
volatile int thread_test_count_TASK27=0;
volatile int thread_test_count_TASK28=0;
volatile int thread_test_count_TASK29=0;
volatile int thread_test_count_TASK30=0;

volatile int thread_test_count_TASK31=0;

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
void thread8(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex8);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK8++;
        pthread_cond_timedwait_np(&cond8, &mutex8, 640,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex8);
    }
}

void thread9(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex9);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK9++;
        pthread_cond_timedwait_np(&cond9, &mutex9, 320,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex9);
    }
}
void thread10(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex10);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK10++;
        pthread_cond_timedwait_np(&cond10, &mutex10, 160,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex10);
    }
}


void thread11(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex11);
        printf("Thread %d blocked\n", (int) arg);
		
        thread_test_count_TASK11++;

        pthread_cond_timedwait_np(&cond11, &mutex11, 10,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex11);
    }
}

void thread12(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex12);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK12++;
        pthread_cond_timedwait_np(&cond12, &mutex12, 20,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex12);
    }
}

void thread13(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex13);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK13++;
        pthread_cond_timedwait_np(&cond13, &mutex13, 40,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex13);
    }
}

void thread14(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex14);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK14++;
        pthread_cond_timedwait_np(&cond14, &mutex14, 80,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex14);
    }
}

void thread15(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex15);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK15++;
        pthread_cond_timedwait_np(&cond15, &mutex15, 320,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex15);
    }
}

void thread16(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex16);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK16++;
        pthread_cond_timedwait_np(&cond16, &mutex16, 640,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex16);
    }
}

void thread17(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex17);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK17++;
        pthread_cond_timedwait_np(&cond17, &mutex17, 1280,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex17);
    }
}
void thread18(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex18);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK18++;
        pthread_cond_timedwait_np(&cond18, &mutex18, 640,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex18);
    }
}

void thread19(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex19);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK19++;
        pthread_cond_timedwait_np(&cond19, &mutex19, 320,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex19);
    }
}
void thread20(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex20);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK20++;
        pthread_cond_timedwait_np(&cond20, &mutex20, 160,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex20);
    }
}

void thread21(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex21);
        printf("Thread %d blocked\n", (int) arg);
		
        thread_test_count_TASK21++;

        pthread_cond_timedwait_np(&cond21, &mutex21, 10,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex21);
    }
}

void thread22(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex22);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK22++;
        pthread_cond_timedwait_np(&cond22, &mutex22, 20,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex22);
    }
}

void thread23(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex23);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK23++;
        pthread_cond_timedwait_np(&cond23, &mutex23, 40,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex23);
    }
}

void thread24(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex24);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK24++;
        pthread_cond_timedwait_np(&cond24, &mutex24, 80,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex24);
    }
}

void thread25(void* arg) {
    for (;;) {
        //pthread_mutex_lock(&mutex25);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK25++;
        //pthread_cond_timedwait_np(&cond25, &mutex25, 320,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        //pthread_mutex_unlock(&mutex25);
    }
}
void thread26(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex26);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK26++;
        pthread_cond_timedwait_np(&cond26, &mutex26, 640,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex26);
    }
}

void thread27(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex27);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK27++;
        pthread_cond_timedwait_np(&cond27, &mutex27, 1280,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex27);
    }
}
void thread28(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex28);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK28++;
        pthread_cond_timedwait_np(&cond28, &mutex28, 640,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex28);
    }
}

void thread29(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex29);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK29++;
        pthread_cond_timedwait_np(&cond29, &mutex29, 320,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex29);
    }
}
void thread30(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex30);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK30++;
        pthread_cond_timedwait_np(&cond30, &mutex30, 160,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex30);
    }
}

void thread31(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex31);
        printf("Thread %d blocked\n", (int) arg);
        thread_test_count_TASK31++;
        pthread_cond_timedwait_np(&cond31, &mutex31, 5,(int) arg);
        printf("Thread %d continued\n", (int) arg);
        pthread_mutex_unlock(&mutex31);
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
    pthread_create_np(th8, NULL, thread8, (void*) 8);
    pthread_create_np(th9, NULL, thread9, (void*) 9);
	pthread_create_np(th10, NULL, thread10,(void*) 10);

	pthread_create_np(th11, NULL, thread11, (void*) 11);
	pthread_create_np(th12, NULL, thread12, (void*) 12);
	pthread_create_np(th13, NULL, thread13, (void*) 13);
	pthread_create_np(th14, NULL, thread14, (void*) 14);
    pthread_create_np(th15, NULL, thread15, (void*) 15);
	pthread_create_np(th16, NULL, thread16, (void*) 16);
	pthread_create_np(th17, NULL, thread17, (void*) 17);
	pthread_create_np(th18, NULL, thread18, (void*) 18);
	pthread_create_np(th19, NULL, thread19, (void*) 19);
	pthread_create_np(th20, NULL, thread20, (void*) 20);

    pthread_create_np(th21, NULL, thread21, (void*) 21);


	pthread_create_np(th22, NULL, thread22, (void*) 22);	
	pthread_create_np(th23, NULL, thread23, (void*) 23);
	pthread_create_np(th24, NULL, thread24, (void*) 24);
#if 0	
    pthread_create_np(th25, NULL, thread25, (void*) 25);
	pthread_create_np(th26, NULL, thread26, (void*) 26);
	pthread_create_np(th27, NULL, thread27, (void*) 27);
	pthread_create_np(th28, NULL, thread28, (void*) 28);
	pthread_create_np(th29, NULL, thread29, (void*) 29);
	pthread_create_np(th30, NULL, thread30, (void*) 30);


    pthread_create_np(th31, NULL, thread7, (void*) 31);
#endif


	pthread_start_np();
}


