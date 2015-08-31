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
PTHREAD_CONTROL_BLOCK(th1,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(th2,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
//PTHREAD_CONTROL_BLOCK(th3,1,SCHED_RR,PTHREAD_DEFAULT_STACK_SIZE)
#pragma align restore

void thread1(void* arg) {
    uint32_t volatile counter = 0;
    for (;;) {
        counter++;
  //      printf("Thread %d counter = %d\n", (int) arg, counter);
        delay_ms(50);
        IfxPort_togglePin(&MODULE_P33, 8);
        //IfxPort_togglePin(&MODULE_P33, 10);

        //switch_context();
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

        //switch_context();
    }
}

void start_core0_os(void) {

   // printf("Example 1: Creates 2 threads with round-robin policy.\n");

    pthread_create_np(th1, NULL, thread1, (void*)1);
    pthread_create_np(th2, NULL, thread2, (void*)2);
   // pthread_create_np(th3, NULL, thread3, (void*)3);

    pthread_start_np();
}


