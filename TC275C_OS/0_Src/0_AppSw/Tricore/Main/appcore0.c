/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore0.c
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


#include "os_trace.h"
#include "os_interface.h"

#pragma align 8

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

pthread_cond_t core0_os_cond1 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond2 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond3 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond4 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond5 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond6 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond7 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond8 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond9 = CORE0_PTHREAD_COND_INITIALIZER;
pthread_cond_t core0_os_cond10 = CORE0_PTHREAD_COND_INITIALIZER;

volatile int core0_os_thread_test_count_TASK0=0;
volatile int core0_os_thread_test_count_TASK1=0;
volatile int core0_os_thread_test_count_TASK2=0;
volatile int core0_os_thread_test_count_TASK3=0;
volatile int core0_os_thread_test_count_TASK4=0;
volatile int core0_os_thread_test_count_TASK5=0;
volatile int core0_os_thread_test_count_TASK6=0;
volatile int core0_os_thread_test_count_TASK7=0;
volatile int core0_os_thread_test_count_TASK8=0;
volatile int core0_os_thread_test_count_TASK9=0;
volatile int core0_os_thread_test_count_TASK10=0;

TsUTIL_ThruPutMeasurement core0_thread_execution_time[E_MaxItems];

#define CORE0_THREAD_TIME_MEASURE

volatile uint32 core0_thread_time[11];
volatile uint32 tick_begin_test1;
volatile uint32 tick_begin_test2;
volatile uint32 tick_begin_test3;
volatile uint32 tick_begin_test4;
volatile uint32 tick_begin_test5;
/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 0 :void core0_os_idle(void* arg) 
|
--------------------------------------------------------------------------------------*/


int core0_math_test(int a,int b)
{

 return (a+b+2);

}

void core0_os_idle(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
uint32 tick_begin_test;
uint32 tick_begin_temp_test;
#endif
    for (;;)
    {   	
        OS_test1(100);
		core0_os_thread_test_count_TASK0++;
		
#ifdef CORE0_THREAD_TIME_MEASURE
        EnterUTIL_TimeMeas(&core0_thread_execution_time[CORE0_IDLE]);
        tick_begin_test = OS_Measure_thread_Time();
#endif

		OS_wait_in_us(200000);
        tick_begin_test1 = core0_math_test(tick_begin_test2,(tick_begin_test3+11));

#ifdef CORE0_THREAD_TIME_MEASURE
        tick_begin_temp_test = OS_Measure_thread_Time();
	   	core0_thread_time[(int) arg] = tick_begin_temp_test - tick_begin_test;
		
		ExitUTIL_TimeMeas(&core0_thread_execution_time[CORE0_IDLE]);
#endif		
        /* Trigger a software interrupt for test only */
		//SRC_GPSR01.U=(1<<26)|   //SRC_GPSR01.B.SETR=1;
	   	//	           (1<<10)|   //SRC_GPSR01.B.SRE=1;
		//	           (0<<11)|   //SRC_GPSR01.B.TOS=0;
		//	           (20);      //SRC_GPSR01.B.SRPN=20; 
		OS_test1(4);

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
volatile int interrupt_test_flag;
void __interrupt(20) CPU0_SOFT1_Isr(void) 
{

	interrupt_test_flag++;
    //pthread_cond_broadcast(&core0_os_cond3);
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   test code  that is used to test the blocked time function of core0 os
|   threads from 0-10 is used.
|
|
--------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 1 :void core0_os_thread1(void* arg) 
|
--------------------------------------------------------------------------------------*/
#pragma protect 
#pragma optimize O2
#pragma tradeoff 4
void core0_os_thread1(void* arg) 
{

	uint32 tick_begin;
	uint32 local_test_flag=20;
	uint32 i,j,k;
    for (;;) 
	{		
		//printf("Thread %d blocked\n", (int) arg);
		//OS_test1((((int) arg)+20));	
        pthread_cond_timedwait_np(&core0_os_cond1,300,(int) arg);
        core0_os_thread_test_count_TASK1++;	
        OS_test1(100);		
		
		//OS_wait_in_us(20);
        //printf("Thread %d continued\n", (int) arg);
		//OS_test1(((int) arg+5));	
        EnterUTIL_TimeMeas(&core0_thread_execution_time[CORE0_THREAD1]);

		tick_begin=OS_Measure_thread_Time();
        tick_begin_test2 = core0_math_test(tick_begin_test1,(tick_begin_test3+31));
		core0_thread_time[1]=OS_Measure_thread_Time() - tick_begin;
        printf("Thread %d continued\n", (int) arg);
		tick_begin_test3 = core0_math_test(tick_begin_test1,(tick_begin_test2+1));
		IfxPort_togglePin(&MODULE_P33, 9);
		ExitUTIL_TimeMeas(&core0_thread_execution_time[CORE0_THREAD1]);

		for(i = 0;i < local_test_flag; i++)
		{
		}
		for(j = 0;j < local_test_flag; j++)
		{
		}
		for(k = 0;k < local_test_flag; k++)
		{
		}
	
    }
}
#pragma tradeoff restore
#pragma endoptimize
#pragma endprotect

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 2 :void core0_os_thread2(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread2(void* arg)
{

	uint32 tick_begin;

    for (;;) 
	{
		
        OS_test1(100);	
		tick_begin = OS_Measure_thread_Time();

        EnterUTIL_TimeMeas(&core0_thread_execution_time[CORE0_THREAD2]);

		printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK2++;
        pthread_cond_timedwait_np(&core0_os_cond2, 200,(int) arg);
        printf("Thread %d continued\n", (int) arg);

        IfxStm_waitTicks(&MODULE_STM0, 20*100); // 20us delay

		core0_thread_time[2] = OS_Measure_thread_Time()-tick_begin;
        IfxPort_togglePin(&MODULE_P33, 8);
		ExitUTIL_TimeMeas(&core0_thread_execution_time[CORE0_THREAD2]);
    }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 3 :void core0_os_thread3(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread3(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

        //printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK3++;
        //pthread_cond_timedwait_np(&core0_os_cond3, 400,(int) arg);
	    pthread_cond_wait(&core0_os_cond3);
		//printf("Thread %d continued\n", (int) arg);

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 20us delay
		
#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif
	    //pthread_cond_broadcast(&core0_os_cond4);

    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 4 :void core0_os_thread4(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread4(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

        printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK4++;
        //pthread_cond_timedwait_np(&core0_os_cond4, 200,(int) arg);

	    pthread_cond_wait(&core0_os_cond4);
		printf("Thread %d continued\n", (int) arg);
		
#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 20us delay
		
#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif
		
	    pthread_cond_broadcast(&core0_os_cond5);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 5 :void core0_os_thread5(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread5(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

        printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK5++;
        //pthread_cond_timedwait_np(&core0_os_cond5, 320,(int) arg);

	    pthread_cond_wait(&core0_os_cond5);
		printf("Thread %d continued\n", (int) arg);

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 500us delay
		
#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif
	    pthread_cond_broadcast(&core0_os_cond6);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 6 :void core0_os_thread6(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread6(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

        printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK6++;
        //pthread_cond_timedwait_np(&core0_os_cond6, 640,(int) arg);

		pthread_cond_wait(&core0_os_cond6);
		printf("Thread %d continued\n", (int) arg);	

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 500us delay

#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif

	    pthread_cond_broadcast(&core0_os_cond7);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 7 :void core0_os_thread7(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread7(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

		printf("Thread %d blocked\n", (int) arg);				
        core0_os_thread_test_count_TASK7++;
        //pthread_cond_timedwait_np(&core0_os_cond7, 1280,(int) arg);

		pthread_cond_wait(&core0_os_cond7);
	    printf("Thread %d continued\n", (int) arg);	

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 500us delay

#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif

	    pthread_cond_broadcast(&core0_os_cond8);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 8 :void core0_os_thread8(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread8(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

		printf("Thread %d blocked\n", (int) arg);				
        core0_os_thread_test_count_TASK8++;

	    pthread_cond_wait(&core0_os_cond8);
	    printf("Thread %d continued\n", (int) arg);	

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 500us delay
		
#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif

	    pthread_cond_broadcast(&core0_os_cond9);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 9 :void core0_os_thread9(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread9(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK9++;
        //pthread_cond_timedwait_np(&core0_os_cond9, 320,(int) arg);

	    pthread_cond_wait(&core0_os_cond9);
	    printf("Thread %d continued\n", (int) arg);	

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 500us delay
		
#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif

	    pthread_cond_broadcast(&core0_os_cond10);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 10 :void core0_os_thread10(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread10(void* arg) {

#ifdef CORE0_THREAD_TIME_MEASURE
	uint32 tick_begin;
#endif

    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK10++;
        //pthread_cond_timedwait_np(&core0_os_cond10, 640,(int) arg);

		pthread_cond_wait(&core0_os_cond10);
	    printf("Thread %d continued\n", (int) arg);	

#ifdef CORE0_THREAD_TIME_MEASURE
		tick_begin=IfxStm_getLower(&MODULE_STM0);
#endif

		IfxStm_waitTicks(&MODULE_STM0, 500*100); // 500us delay
		
#ifdef CORE0_THREAD_TIME_MEASURE
		core0_thread_time[(int) arg]=IfxStm_getLower(&MODULE_STM0)-tick_begin;
#endif
	
	    //pthread_cond_broadcast(&core0_os_cond11);
	    //pthread_other_core_cond_broadcast(&core0_os_cond11,CORE0);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: start OS
|   Define OS API :void start_core0_os(void) 
|
--------------------------------------------------------------------------------------*/
const pthread_attr_t core0_os_th0_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th1_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th2_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th3_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th4_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th5_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th6_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th7_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th8_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th9_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};
const pthread_attr_t core0_os_th10_attr = { SUPER, CALL_DEPTH_OVERFLOW_AT_64};

void start_core0_os(void) {

    pthread_create_np(core0_os_th0, &core0_os_th0_attr, core0_os_idle, (void*) 0);
    pthread_create_np(core0_os_th1, &core0_os_th1_attr, core0_os_thread1, (void*) 1);	
    pthread_create_np(core0_os_th2, &core0_os_th2_attr, core0_os_thread2, (void*) 2);
#if 0
	pthread_create_np(core0_os_th3, &core0_os_th3_attr, core0_os_thread3, (void*) 3);

	pthread_create_np(core0_os_th4, &core0_os_th4_attr, core0_os_thread4, (void*) 4);
	pthread_create_np(core0_os_th5, &core0_os_th5_attr, core0_os_thread5, (void*) 5);

	pthread_create_np(core0_os_th6, &core0_os_th6_attr, core0_os_thread6, (void*) 6);
	pthread_create_np(core0_os_th7, &core0_os_th7_attr, core0_os_thread7, (void*) 7);
    pthread_create_np(core0_os_th8, &core0_os_th8_attr, core0_os_thread8, (void*) 8);
    pthread_create_np(core0_os_th9, &core0_os_th9_attr, core0_os_thread9, (void*) 9);
	pthread_create_np(core0_os_th10, &core0_os_th10_attr, core0_os_thread10,(void*) 10);
#endif

	pthread_start_np();
}


