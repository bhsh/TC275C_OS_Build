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


PTHREAD_CONTROL_BLOCK(core0_os_th11,11,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th12,12,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th13,13,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th14,14,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th15,15,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th16,16,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th17,17,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th18,18,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th19,19,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th20,20,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)


PTHREAD_CONTROL_BLOCK(core0_os_th21,21,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th22,22,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th23,23,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th24,24,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th25,25,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th26,26,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th27,27,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th28,28,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th29,29,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th30,30,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)
PTHREAD_CONTROL_BLOCK(core0_os_th31,31,SCHED_FIFO,PTHREAD_DEFAULT_STACK_SIZE)

#pragma align restore


pthread_cond_t core0_os_cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex2 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond3 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex3 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond4 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex4 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond5 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex5 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond6 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex6 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond7 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex7 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond8 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex8 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond9 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex9 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond10 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex10 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond11 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex11 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond12 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex12 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond13 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex13 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond14 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex14 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond15 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex15 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond16 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex16 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond17 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex17 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond18 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex18 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond19 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex19 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond20 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex20 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond21 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex21 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond22 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex22 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond23 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex23 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond24 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex24 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond25 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex25 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond26 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex26 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond27 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex27 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond28 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex28 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond29 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex29 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond30 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex30 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t core0_os_cond31 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t core0_os_mutex31 = PTHREAD_MUTEX_INITIALIZER;


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


volatile int core0_os_thread_test_count_TASK11=0;
volatile int core0_os_thread_test_count_TASK12=0;
volatile int core0_os_thread_test_count_TASK13=0;
volatile int core0_os_thread_test_count_TASK14=0;
volatile int core0_os_thread_test_count_TASK15=0;
volatile int core0_os_thread_test_count_TASK16=0;
volatile int core0_os_thread_test_count_TASK17=0;
volatile int core0_os_thread_test_count_TASK18=0;
volatile int core0_os_thread_test_count_TASK19=0;
volatile int core0_os_thread_test_count_TASK20=0;

volatile int core0_os_thread_test_count_TASK21=0;
volatile int core0_os_thread_test_count_TASK22=0;
volatile int core0_os_thread_test_count_TASK23=0;
volatile int core0_os_thread_test_count_TASK24=0;
volatile int core0_os_thread_test_count_TASK25=0;
volatile int core0_os_thread_test_count_TASK26=0;
volatile int core0_os_thread_test_count_TASK27=0;
volatile int core0_os_thread_test_count_TASK28=0;
volatile int core0_os_thread_test_count_TASK29=0;
volatile int core0_os_thread_test_count_TASK30=0;

volatile int core0_os_thread_test_count_TASK31=0;

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 0 :void core0_os_idle(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_idle(void* arg) {
    for (;;)
    {

    	core0_os_thread_test_count_TASK0++;
    	delay_ms(200);
		
        /* Trigger a software interrupt for test only */

		SRC_GPSR01.U=(1<<26)|   //SRC_GPSR01.B.SETR=1;
			         (1<<10)|   //SRC_GPSR01.B.SRE=1;
			         (0<<11)|   //SRC_GPSR01.B.TOS=0;
			         (20);      //SRC_GPSR01.B.SRPN=3; 

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
    pthread_cond_broadcast(&core0_os_cond16);
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
volatile int core0_os_test1;
void core0_os_thread1(void* arg) {
    for (;;) {
		
        printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK1++;
        pthread_cond_timedwait_np(&core0_os_cond1,100,(int) arg);
		printf("Thread %d continued\n", (int) arg);

    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|    
|   Define thread 2 :void core0_os_thread2(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread2(void* arg) {
    for (;;) {

		printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK2++;
        pthread_cond_timedwait_np(&core0_os_cond2, 200,(int) arg);
        printf("Thread %d continued\n", (int) arg);
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
    for (;;) {

        printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK3++;
        pthread_cond_timedwait_np(&core0_os_cond3, 400,(int) arg);
        printf("Thread %d continued\n", (int) arg);
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
    for (;;) {

        printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK4++;
        pthread_cond_timedwait_np(&core0_os_cond4, 200,(int) arg);
		printf("Thread %d continued\n", (int) arg);

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
    for (;;) {

        printf("Thread %d blocked\n", (int) arg);
        core0_os_thread_test_count_TASK5++;
        pthread_cond_timedwait_np(&core0_os_cond5, 320,(int) arg);
		printf("Thread %d continued\n", (int) arg);		
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
    for (;;) {

        printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK6++;
        pthread_cond_timedwait_np(&core0_os_cond6, 640,(int) arg);
		printf("Thread %d continued\n", (int) arg);		

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
    for (;;) {

		printf("Thread %d blocked\n", (int) arg);				
        core0_os_thread_test_count_TASK7++;
        pthread_cond_timedwait_np(&core0_os_cond7, 1280,(int) arg);
	    printf("Thread %d continued\n", (int) arg);		

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
    for (;;) {

		printf("Thread %d blocked\n", (int) arg);				
        core0_os_thread_test_count_TASK8++;
        pthread_cond_timedwait_np(&core0_os_cond8, 640,(int) arg);
	    printf("Thread %d continued\n", (int) arg);		

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
    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK9++;
        pthread_cond_timedwait_np(&core0_os_cond9, 320,(int) arg);
	    printf("Thread %d continued\n", (int) arg);		

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
    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK10++;
        pthread_cond_timedwait_np(&core0_os_cond10, 640,(int) arg);
	    printf("Thread %d continued\n", (int) arg);		

	   // pthread_cond_broadcast(&core0_os_cond11);
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 11 :void core0_os_thread11(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread11(void* arg) {
    for (;;) {

        //delay_ms(200);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK11++;
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
		//pthread_cond_broadcast(&core0_os_cond21);

    }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 12 :void core0_os_thread12(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread12(void* arg) {
    for (;;) {

        //delay_ms(200);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK12++;		
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
    }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 13 :void core0_os_thread13(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread13(void* arg) {
    for (;;) {

        //delay_ms(200);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK13++;		
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 14 :void core0_os_thread14(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread14(void* arg) {
    for (;;) {

        //delay_ms(200);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK14++;
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 15 :void core0_os_thread15(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread15(void* arg) {
    for (;;) {

        //delay_ms(200);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK15++;
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
		//pthread_cond_broadcast(&core0_os_cond16);	
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 16 :void core0_os_thread16(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread16(void* arg) {
    for (;;) {

        //delay_ms(200);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK16++;
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 17 :void core0_os_thread17(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread17(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK17++;
        pthread_cond_wait(&core0_os_cond16);
	    printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 18 :void core0_os_thread18(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread18(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK18++;
        pthread_cond_wait(&core0_os_cond16);
		printf("Thread %d continued\n", (int) arg);		
		
    }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 19 :void core0_os_thread19(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread19(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK19++;
        pthread_cond_wait(&core0_os_cond16);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: software sync
|   Define thread 20 :void core0_os_thread20(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread20(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK20++;
        pthread_cond_wait(&core0_os_cond16);
		printf("Thread %d continued\n", (int) arg);		
		pthread_cond_broadcast(&core0_os_cond21);	
		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 21 :void core0_os_thread21(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread21(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK21++;
        pthread_cond_wait(&core0_os_cond21);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 22 :void core0_os_thread22(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread22(void* arg) {
    for (;;) {
		
        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK22++;
        pthread_cond_wait(&core0_os_cond21);
		printf("Thread %d continued\n", (int) arg);		
    }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 23 :void core0_os_thread23(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread23(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK23++;
        pthread_cond_wait(&core0_os_cond21);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 24 :void core0_os_thread24(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread24(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK24++;
        pthread_cond_wait(&core0_os_cond21);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 25 :void core0_os_thread25(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread25(void* arg) {
    for (;;) {

        //delay_ms(100);
	    printf("Thread %d blocked\n", (int) arg);		
		core0_os_thread_test_count_TASK25++;
        pthread_cond_wait(&core0_os_cond21);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 26 :void core0_os_thread26(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread26(void* arg) {
    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK26++;
        pthread_cond_timedwait_np(&core0_os_cond26, 640,(int) arg);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 27 :void core0_os_thread27(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread27(void* arg) {
    for (;;) {
		
	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK27++;
        pthread_cond_timedwait_np(&core0_os_cond27, 1280,(int) arg);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 28 :void core0_os_thread28(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread28(void* arg) {
    for (;;) {
		
	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK28++;
        pthread_cond_timedwait_np(&core0_os_cond28, 640,(int) arg);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 29 :void core0_os_thread29(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread29(void* arg) {
    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK29++;
        pthread_cond_timedwait_np(&core0_os_cond29, 320,(int) arg);
	    printf("Thread %d continued\n", (int) arg);		

    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 30 :void core0_os_thread30(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread30(void* arg) {
    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK30++;
        pthread_cond_timedwait_np(&core0_os_cond30, 160,(int) arg);
		printf("Thread %d continued\n", (int) arg);		

    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: interrupt sync
|   Define thread 31 :void core0_os_thread31(void* arg) 
|
--------------------------------------------------------------------------------------*/
void core0_os_thread31(void* arg) {
    for (;;) {

	    printf("Thread %d blocked\n", (int) arg);		
        core0_os_thread_test_count_TASK31++;
        pthread_cond_timedwait_np(&core0_os_cond31, 50,(int) arg);
		printf("Thread %d continued\n", (int) arg);		
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|   Test type: start OS
|   Define OS API :void start_core0_os(void) 
|
--------------------------------------------------------------------------------------*/
void start_core0_os(void) {

    pthread_create_np(core0_os_th0, NULL, core0_os_idle, (void*) 0);

    pthread_create_np(core0_os_th1, NULL, core0_os_thread1, (void*) 1);	
    pthread_create_np(core0_os_th2, NULL, core0_os_thread2, (void*) 2);

	pthread_create_np(core0_os_th3, NULL, core0_os_thread3, (void*) 3);
	pthread_create_np(core0_os_th4, NULL, core0_os_thread4, (void*) 4);
	pthread_create_np(core0_os_th5, NULL, core0_os_thread5, (void*) 5);
	pthread_create_np(core0_os_th6, NULL, core0_os_thread6, (void*) 6);
	pthread_create_np(core0_os_th7, NULL, core0_os_thread7, (void*) 7);
    pthread_create_np(core0_os_th8, NULL, core0_os_thread8, (void*) 8);
    pthread_create_np(core0_os_th9, NULL, core0_os_thread9, (void*) 9);
	pthread_create_np(core0_os_th10, NULL, core0_os_thread10,(void*) 10);
	
	pthread_create_np(core0_os_th11, NULL, core0_os_thread11, (void*) 11);
	pthread_create_np(core0_os_th12, NULL, core0_os_thread12, (void*) 12);
	pthread_create_np(core0_os_th13, NULL, core0_os_thread13, (void*) 13);
	pthread_create_np(core0_os_th14, NULL, core0_os_thread14, (void*) 14);
    pthread_create_np(core0_os_th15, NULL, core0_os_thread15, (void*) 15);
	pthread_create_np(core0_os_th16, NULL, core0_os_thread16, (void*) 16);
	pthread_create_np(core0_os_th17, NULL, core0_os_thread17, (void*) 17);
	pthread_create_np(core0_os_th18, NULL, core0_os_thread18, (void*) 18);
	pthread_create_np(core0_os_th19, NULL, core0_os_thread19, (void*) 19);
	pthread_create_np(core0_os_th20, NULL, core0_os_thread20, (void*) 20);


    pthread_create_np(core0_os_th21, NULL, core0_os_thread21, (void*) 21);
	pthread_create_np(core0_os_th22, NULL, core0_os_thread22, (void*) 22);	
	pthread_create_np(core0_os_th23, NULL, core0_os_thread23, (void*) 23);
	pthread_create_np(core0_os_th24, NULL, core0_os_thread24, (void*) 24);
    pthread_create_np(core0_os_th25, NULL, core0_os_thread25, (void*) 25);
#if 0
	pthread_create_np(core0_os_th26, NULL, core0_os_thread26, (void*) 26);
	pthread_create_np(core0_os_th27, NULL, core0_os_thread27, (void*) 27);
	pthread_create_np(core0_os_th28, NULL, core0_os_thread28, (void*) 28);
	pthread_create_np(core0_os_th29, NULL, core0_os_thread29, (void*) 29);
	pthread_create_np(core0_os_th30, NULL, core0_os_thread30, (void*) 30);

    pthread_create_np(core0_os_th31, NULL, core0_os_thread31, (void*) 31);
#endif
	pthread_start_np();
}


