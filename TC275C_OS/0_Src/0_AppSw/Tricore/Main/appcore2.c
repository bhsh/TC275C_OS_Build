/*
 * appcore1.c
 *
 *  Created on: Sep 23, 2015
 *      Author: tz68d9
 */


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

PTHREAD_CONTROL_BLOCK(core2_th0,0,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th1,1,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core2_th2,2,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

#pragma align restore

pthread_cond_t core2_os_cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core2_os_mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core2_os_cond2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core2_os_mutex2 = PTHREAD_MUTEX_INITIALIZER;


volatile int core2_os_thread_test_count_TASK0=0;
volatile int core2_os_thread_test_count_TASK1=0;
volatile int core2_os_thread_test_count_TASK2=0;


void core2_os_idle(void* arg) {
    for (;;)
    {
    	core2_os_thread_test_count_TASK0++;
    	delay_ms(200);
    }
}
void core2_os_thread1(void* arg) {
    for (;;) {

        printf("Thread %d blocked\n", (int) arg);

        core2_os_thread_test_count_TASK1++;

        pthread_cond_timedwait_np(&core2_os_cond1, 100,(int) arg);
        printf("Thread %d continued\n", (int) arg);
    }
}

void core2_os_thread2(void* arg) {
    for (;;) {

        printf("Thread %d blocked\n", (int) arg);

        core2_os_thread_test_count_TASK2++;

        pthread_cond_timedwait_np(&core2_os_cond2, 200,(int) arg);
        printf("Thread %d continued\n", (int) arg);
    }
}
void start_core2_os(void) {

    pthread_create_np(core2_th0, NULL, core2_os_idle, (void*) 0);
    pthread_create_np(core2_th1, NULL, core2_os_thread1, (void*) 1);
    pthread_create_np(core2_th2, NULL, core2_os_thread2, (void*) 2);
	
	pthread_start_np();
}



