/*-----------------------------------------------------------------------------------
|
|   File name:    os_kernel.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#include "os_kernel.h"
#include "_Reg/IfxSrc_reg.h"

#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"



#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

/* define the system call that is the 6th trap of CPU */

//! \cond IGNORE
#define DISPATCH_WAIT     2
#define DISPATCH_SIGNAL   3


//#define OLD_AVALIABLE


__syscallfunc(DISPATCH_WAIT)   int dispatch_wait(void *, void *);
__syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
//! \endcond

uint32_t  core0_os_pthread_runnable;
pthread_t core0_os_pthread_running;
pthread_t core0_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
static pthread_t core0_os_blocked_threads;

 
uint32_t core1_os_pthread_runnable;
pthread_t core1_os_pthread_running;
pthread_t core1_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
static pthread_t core1_os_blocked_threads;

uint32_t core2_os_pthread_runnable;
pthread_t core2_os_pthread_running;
pthread_t core2_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
static pthread_t core2_os_blocked_threads;

uint16_t stm_tick_count;
uint16_t core1_os_stm_tick_count;
uint16_t core2_os_stm_tick_count;

 //! tw array hold condition and time for pthread_cond_timedwait_np.
 
uint16_t  stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
         		    USHRT_MAX,                      // task 0 
				    USHRT_MAX,                      // task 1 
				    USHRT_MAX,                      // task 2
				    USHRT_MAX,                      // task 3
                    USHRT_MAX,                      // task 4
                    USHRT_MAX,                      // task 5
                    USHRT_MAX,                      // task 6
                    USHRT_MAX,                      // task 7
                    USHRT_MAX,                      // task 8                      
				    USHRT_MAX,                      // task 9                      
	         		USHRT_MAX,                      // task 10 
	         		
				    USHRT_MAX,                      // task 11 
				    USHRT_MAX,                      // task 12
				    USHRT_MAX,                      // task 13
                    USHRT_MAX,                      // task 14
                    USHRT_MAX,                      // task 15
                    USHRT_MAX,                      // task 16
                    USHRT_MAX,                      // task 17
                    USHRT_MAX,                      // task 18                      
				    USHRT_MAX,                      // task 19  
				    USHRT_MAX,                      // task 20 
				    
				    USHRT_MAX,                      // task 21 
				    USHRT_MAX,                      // task 22
				    USHRT_MAX,                      // task 23
                    USHRT_MAX,                      // task 24
                    USHRT_MAX,                      // task 25
                    USHRT_MAX,                      // task 26
                    USHRT_MAX,                      // task 27
                    USHRT_MAX,                      // task 28                      
				    USHRT_MAX,                      // task 29    

					USHRT_MAX,                      // task 30                      
				    USHRT_MAX,                      // task 31
				    
    };//!< time
pthread_cond_t  *stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
          		    NULL,                      // task 0 
				    NULL,                      // task 1 
				    NULL,                      // task 2
				    NULL,                      // task 3
                    NULL,                      // task 4
                    NULL,                      // task 5
                    NULL,                      // task 6
                    NULL,                      // task 7
                    NULL,                      // task 8                      
				    NULL,                      // task 9                      
	         		NULL,                      // task 10 
	         		
				    NULL,                      // task 11 
				    NULL,                      // task 12
				    NULL,                      // task 13
                    NULL,                      // task 14
                    NULL,                      // task 15
                    NULL,                      // task 16
                    NULL,                      // task 17
                    NULL,                      // task 18                      
				    NULL,                      // task 19  
				    NULL,                      // task 20 
				    
				    NULL,                      // task 21 
				    NULL,                      // task 22
				    NULL,                      // task 23
                    NULL,                      // task 24
                    NULL,                      // task 25
                    NULL,                      // task 26
                    NULL,                      // task 27
                    NULL,                      // task 28                      
				    NULL,                      // task 29    

					NULL,                      // task 30                      
				    NULL,                      // task 31

    };//!< condition

uint16_t  core1_os_stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
         		    USHRT_MAX,                      // task 0 
				    USHRT_MAX,                      // task 1 
				    USHRT_MAX,                      // task 2
				    USHRT_MAX,                      // task 3
                    USHRT_MAX,                      // task 4
                    USHRT_MAX,                      // task 5
                    USHRT_MAX,                      // task 6
                    USHRT_MAX,                      // task 7
                    USHRT_MAX,                      // task 8                      
				    USHRT_MAX,                      // task 9                      
	         		USHRT_MAX,                      // task 10 
	         		
				    USHRT_MAX,                      // task 11 
				    USHRT_MAX,                      // task 12
				    USHRT_MAX,                      // task 13
                    USHRT_MAX,                      // task 14
                    USHRT_MAX,                      // task 15
                    USHRT_MAX,                      // task 16
                    USHRT_MAX,                      // task 17
                    USHRT_MAX,                      // task 18                      
				    USHRT_MAX,                      // task 19  
				    USHRT_MAX,                      // task 20 
				    
				    USHRT_MAX,                      // task 21 
				    USHRT_MAX,                      // task 22
				    USHRT_MAX,                      // task 23
                    USHRT_MAX,                      // task 24
                    USHRT_MAX,                      // task 25
                    USHRT_MAX,                      // task 26
                    USHRT_MAX,                      // task 27
                    USHRT_MAX,                      // task 28                      
				    USHRT_MAX,                      // task 29    

					USHRT_MAX,                      // task 30                      
				    USHRT_MAX,                      // task 31
				    
    };//!< time
pthread_cond_t  *core1_os_stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
          		    NULL,                      // task 0 
				    NULL,                      // task 1 
				    NULL,                      // task 2
				    NULL,                      // task 3
                    NULL,                      // task 4
                    NULL,                      // task 5
                    NULL,                      // task 6
                    NULL,                      // task 7
                    NULL,                      // task 8                      
				    NULL,                      // task 9                      
	         		NULL,                      // task 10 
	         		
				    NULL,                      // task 11 
				    NULL,                      // task 12
				    NULL,                      // task 13
                    NULL,                      // task 14
                    NULL,                      // task 15
                    NULL,                      // task 16
                    NULL,                      // task 17
                    NULL,                      // task 18                      
				    NULL,                      // task 19  
				    NULL,                      // task 20 
				    
				    NULL,                      // task 21 
				    NULL,                      // task 22
				    NULL,                      // task 23
                    NULL,                      // task 24
                    NULL,                      // task 25
                    NULL,                      // task 26
                    NULL,                      // task 27
                    NULL,                      // task 28                      
				    NULL,                      // task 29    

					NULL,                      // task 30                      
				    NULL,                      // task 31

    };//!< condition
uint16_t  core2_os_stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
         		    USHRT_MAX,                      // task 0 
				    USHRT_MAX,                      // task 1 
				    USHRT_MAX,                      // task 2
				    USHRT_MAX,                      // task 3
                    USHRT_MAX,                      // task 4
                    USHRT_MAX,                      // task 5
                    USHRT_MAX,                      // task 6
                    USHRT_MAX,                      // task 7
                    USHRT_MAX,                      // task 8                      
				    USHRT_MAX,                      // task 9                      
	         		USHRT_MAX,                      // task 10 
	         		
				    USHRT_MAX,                      // task 11 
				    USHRT_MAX,                      // task 12
				    USHRT_MAX,                      // task 13
                    USHRT_MAX,                      // task 14
                    USHRT_MAX,                      // task 15
                    USHRT_MAX,                      // task 16
                    USHRT_MAX,                      // task 17
                    USHRT_MAX,                      // task 18                      
				    USHRT_MAX,                      // task 19  
				    USHRT_MAX,                      // task 20 
				    
				    USHRT_MAX,                      // task 21 
				    USHRT_MAX,                      // task 22
				    USHRT_MAX,                      // task 23
                    USHRT_MAX,                      // task 24
                    USHRT_MAX,                      // task 25
                    USHRT_MAX,                      // task 26
                    USHRT_MAX,                      // task 27
                    USHRT_MAX,                      // task 28                      
				    USHRT_MAX,                      // task 29    

					USHRT_MAX,                      // task 30                      
				    USHRT_MAX,                      // task 31
				    
    };//!< time
pthread_cond_t  *core2_os_stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
          		    NULL,                      // task 0 
				    NULL,                      // task 1 
				    NULL,                      // task 2
				    NULL,                      // task 3
                    NULL,                      // task 4
                    NULL,                      // task 5
                    NULL,                      // task 6
                    NULL,                      // task 7
                    NULL,                      // task 8                      
				    NULL,                      // task 9                      
	         		NULL,                      // task 10 
	         		
				    NULL,                      // task 11 
				    NULL,                      // task 12
				    NULL,                      // task 13
                    NULL,                      // task 14
                    NULL,                      // task 15
                    NULL,                      // task 16
                    NULL,                      // task 17
                    NULL,                      // task 18                      
				    NULL,                      // task 19  
				    NULL,                      // task 20 
				    
				    NULL,                      // task 21 
				    NULL,                      // task 22
				    NULL,                      // task 23
                    NULL,                      // task 24
                    NULL,                      // task 25
                    NULL,                      // task 26
                    NULL,                      // task 27
                    NULL,                      // task 28                      
				    NULL,                      // task 29    

					NULL,                      // task 30                      
				    NULL,                      // task 31

    };//!< condition

extern uint32 stm0CompareValue;
extern uint32 stm1CompareValue;
extern uint32 stm2CompareValue;
extern uint32 stm0CompareValue2;

extern uint32_t  core0_os_pthread_runnable;              //! Currently running thread
extern pthread_t core0_os_pthread_running;              //! Array of linked lists which holds runnable threads
extern pthread_t core0_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];

extern uint32_t  core1_os_pthread_runnable;    //! Currently running thread
extern pthread_t core1_os_pthread_running;    //! Array of linked lists which holds runnable threads
extern pthread_t core1_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];

extern uint32_t  core2_os_pthread_runnable;    //! Currently running thread
extern pthread_t core2_os_pthread_running;    //! Array of linked lists which holds runnable threads
extern pthread_t core2_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];


/*-------------------------------------------------------------------------------------
|
|   Description:
|             update_stm0_ticks 
|             update stm0 ticks
|
--------------------------------------------------------------------------------------*/
inline void update_stm0_ticks(void)
{
    uint32 stmTicks;

    stmTicks= (uint32)(stm0CompareValue*1);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + stmTicks);
    //IfxPort_togglePin(&MODULE_P33, 8);
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|             update_stm1_ticks 
|             update stm1 ticks
|
--------------------------------------------------------------------------------------*/
inline void update_stm1_ticks(void)
{
    uint32 stmTicks;
	
    stmTicks= (uint32)(stm1CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM1, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM1, IfxStm_Comparator_0) + stmTicks);
    //IfxPort_togglePin(&MODULE_P33, 9);
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|             update_stm2_ticks 
|             update stm2 ticks
|
--------------------------------------------------------------------------------------*/
inline void update_stm2_ticks(void)
{
    uint32 stmTicks;
    stmTicks= (uint32)(stm2CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM2, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM2, IfxStm_Comparator_0) + stmTicks);
    //IfxPort_togglePin(&MODULE_P33, 10);
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             update_stm0_compare1_ticks
|             update stm0 compare1
|
--------------------------------------------------------------------------------------*/
// Unit:ms ,the max is 0xFFFFFFFF/100000=42949ms(42.949s);
inline void update_stm0_compare1_ticks(uint32 tick_ms)
{
    uint32 stmTicks;

    stmTicks= (uint32)(stm0CompareValue2*tick_ms);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_1, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_1) + stmTicks);
    IfxPort_togglePin(&MODULE_P33, 10);
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             list_append 
|             add one node into a list 
|
--------------------------------------------------------------------------------------*/
inline void list_append(pthread_t *head, pthread_t elem, pthread_t list_prev,
        pthread_t elem_next) {
    assert(head != NULL);
    assert(elem != NULL);

    pthread_t list = *head;
    if (list == NULL) {
        elem->next = elem_next;
    	//elem->next = elem;
        elem->prev = elem;
        *head = elem;
    } else {
        elem->next = elem_next;
        elem->prev = list->prev;
        list->prev->next = elem;
        list->prev = list_prev;
    }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             static void list_delete_first(pthread_t *head) 
|             delete one node in a list
|
--------------------------------------------------------------------------------------*/
static void list_delete_first(pthread_t *head) {
    assert(head);

    pthread_t old = *head;
    pthread_t new = old->next;

    if (new != NULL) {
        old->prev->next = new;
        new->prev = old->prev;
        if (new->next == new)
            new->next = NULL; // if the list has only one element than set ->next = NULL
    }
    *head = new;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             pthread_create_np 
|             create threads from users
|
--------------------------------------------------------------------------------------*/
int pthread_create_np(pthread_t thread, //!< [in] thread control block pointer.
        const pthread_attr_t *attr, //!<  [in] thread attribute. Can be NULL to use default.
        void(*start_routine)(void *),//!<  [in] thread function pointer
        void *arg) //!<  [in] argument passed to thread function when started
{

    const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
    uint32_t fcx;
    context_t *cx;

    if (attr == NULL)
        attr = &default_attr;

    fcx = __mfcr(CPU_FCX);
    thread->lcx = fcx - 1;
    __mtcr(CPU_FCX, fcx - 2);

    cx = cx_to_addr(fcx);
    cx->u.psw = 0 << 12 // Protection Register Set PRS=0
            | attr->mode << 10 // I/O Privilege
            | 0 << 9 // Current task uses a user stack IS=0
            | 0 << 8 // Write permission to global registers A0, A1, A8, A9 is disabled
            | 1L << 7 // Call depth counting is enabled CDE=1
            | attr->call_depth_overflow; // Call Depth Overflow
    cx->u.a10 = thread->stack + *thread->stack; // stack grow down
    cx->u.a11 = 0; // New task has no return address
    cx->u.pcxi = 0; // No previous context;
    cx--;
    cx->l.pcxi = 0L << 22 // Previous CPU Priority Number PCPN=0 TriCore:0L << 24
            | 1L << 21 // Previous Interrupt Enable PIE=1        TriCore:| 1L << 23 different PCXI between Aurix and TriCores
            | 1L << 20 // Upper Context Tag.                     TriCore:| 1L << 22
            | fcx; // Previous Context Pointer is the upper context
    cx->l.pc = start_routine; // init new task start address
    cx->l.a4 = arg;
    thread->arg = arg;

    uint32_t i = thread->priority;
	
    if(os_getCoreId()==0)
    {   
       list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                  core0_os_pthread_runnable_threads[i]);
       __putbit(1,(int*)&core0_os_pthread_runnable,i); // mark current thread ready
    }
    else if(os_getCoreId()==1)
    {
       list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                  core1_os_pthread_runnable_threads[i]);
       __putbit(1,(int*)&core1_os_pthread_runnable,i); // mark current thread ready
    }
	else if(os_getCoreId()==2)
	{
       list_append(&core2_os_pthread_runnable_threads[i], thread, thread,
                  core2_os_pthread_runnable_threads[i]);
       __putbit(1,(int*)&core2_os_pthread_runnable,i); // mark current thread ready
	}
    return 0;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             int pthread_mutex_lock(pthread_mutex_t *mutex) 
|             lock a mutex
|
--------------------------------------------------------------------------------------*/
int pthread_mutex_lock(pthread_mutex_t *mutex) //!<  [in] mutex pointer
{
    assert(cppn()==0); // CCPN must be 0, function cannot be called from ISR
    assert (mutex != NULL); // errno = EINVAL, return -1

	if(os_getCoreId()==0)
	{
        if (mutex->owner == core0_os_pthread_running) // errno = EDEADLK
            return -1;

        while (true == __swap(&mutex->lock, true)) { // swap out if already looked by another thread
             dispatch_wait(&mutex->blocked_threads, NULL); // block this thread
        }
        mutex->owner = core0_os_pthread_running;
	}
	else if(os_getCoreId()==1)
	{

        if (mutex->owner == core1_os_pthread_running) // errno = EDEADLK
            return -1;

        while (true == __swap(&mutex->lock, true)) { // swap out if already looked by another thread
             dispatch_wait(&mutex->blocked_threads, NULL); // block this thread
        }
        mutex->owner = core1_os_pthread_running;
	}
	else if(os_getCoreId()==2)
	{
        if (mutex->owner == core2_os_pthread_running) // errno = EDEADLK
            return -1;

        while (true == __swap(&mutex->lock, true)) { // swap out if already looked by another thread
             dispatch_wait(&mutex->blocked_threads, NULL); // block this thread
        }
        mutex->owner = core2_os_pthread_running;
	}
    return 0;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             int pthread_mutex_unlock(pthread_mutex_t *mutex) 
|             Unlock a mutex
|
--------------------------------------------------------------------------------------*/
int pthread_mutex_unlock(pthread_mutex_t *mutex) //!<  [in] mutex pointer
{
    assert(cppn()==0); // CCPN must be 0, function cannot be called from ISR
    assert (mutex != NULL); // errno = EINVAL, return -1

	if(os_getCoreId()==0)
	{
        if (mutex->owner != core0_os_pthread_running) // errno = EPERM
             return -1;

        pthread_t threads = mutex->blocked_threads;
        mutex->owner = NULL;
        mutex->lock = false;
        mutex->blocked_threads = NULL;
        if (threads != NULL)
            dispatch_signal(&threads, NULL);
	}
	else if(os_getCoreId()==1)
	{
        if (mutex->owner != core1_os_pthread_running) // errno = EPERM
             return -1;

        pthread_t threads = mutex->blocked_threads;
        mutex->owner = NULL;
        mutex->lock = false;
        mutex->blocked_threads = NULL;
        if (threads != NULL)
            dispatch_signal(&threads, NULL);
	}
	else if(os_getCoreId()==2)
	{
        if (mutex->owner != core2_os_pthread_running) // errno = EPERM
             return -1;

        pthread_t threads = mutex->blocked_threads;
        mutex->owner = NULL;
        mutex->lock = false;
        mutex->blocked_threads = NULL;
        if (threads != NULL)
            dispatch_signal(&threads, NULL);
	}
    return 0;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|             int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
|             Wait on a condition
|
--------------------------------------------------------------------------------------*/
int pthread_cond_wait(pthread_cond_t *cond)//!< [in] condition pointer
{
    assert(cppn()==0); // CCPN must be 0, pthread_create cannot be called from ISR
    assert(cond != NULL); // errno = EINVAL
    //assert(mutex != NULL); // errno = EINVAL

    //if (true != __swap(&mutex->lock, false)) // the calling thread must have mutex locked
    //    return -1; // errno = ENOTLOCKED

    dispatch_wait(&cond->blocked_threads, NULL);// add this thread to the list of blocked threads by this cond
    //mutex->lock = true;
    //mutex->owner = core0_os_pthread_running;

	
    return 0;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               int pthread_cond_broadcast(pthread_cond_t *cond)
|               Broadcast a condition
|
--------------------------------------------------------------------------------------*/
int pthread_cond_broadcast(pthread_cond_t *cond) //!< [in] condition pointer
{
    assert(cond!=NULL);
    if (cond->blocked_threads != NULL) {
        if (0 == cppn()) { // _pthread_running on CCPN=0
            dispatch_signal(&cond->blocked_threads, cond->blocked_threads->prev);// swap in with mutex unlocked
        } 
		else 
        {
	        if(os_getCoreId()==0)
		    {
                 /* The bug is found here*/
        	     core0_os_blocked_threads=NULL;
        	     //blocked_threads_prev_temp=cond->blocked_threads->prev;
        	     list_append(&core0_os_blocked_threads, cond->blocked_threads,
                              cond->blocked_threads->prev, cond->blocked_threads->next);
                 //locked_threads=cond->blocked_threads;
                 cond->blocked_threads = NULL;

                 /*  The software interrupt 0 of core0 is used.   */
                 //SRC_GPSR00.B.SETR=1;    // Set request
                 //SRC_GPSR00.B.SRE=1;     // Service Request Enable
                 //SRC_GPSR00.B.TOS=0;     // TOS=CPU0
                 //SRC_GPSR00.B.SRPN=9;    // Service Request Priority Number

				 SRC_GPSR00.U=(1<<26)|   //SRC_GPSR01.B.SETR=1;
			                  (1<<10)|   //SRC_GPSR01.B.SRE=1;
			                  (0<<11)|   //SRC_GPSR01.B.TOS=0;
			                  (9);       //SRC_GPSR01.B.SRPN=9; 
            }
			else if(os_getCoreId()==1)
			{
                 /* The bug is found here*/
        	     core1_os_blocked_threads=NULL;
        	     //blocked_threads_prev_temp=cond->blocked_threads->prev;
        	     list_append(&core1_os_blocked_threads, cond->blocked_threads,
                              cond->blocked_threads->prev, cond->blocked_threads->next);
                 //locked_threads=cond->blocked_threads;
                 cond->blocked_threads = NULL;

                 /*  The software interrupt 0 of core0 is used.   */
                 //SRC_GPSR10.B.SETR=1;    // Set request
                 //SRC_GPSR10.B.SRE=1;     // Service Request Enable
                 //SRC_GPSR10.B.TOS=0;     // TOS=CPU0
                 //SRC_GPSR10.B.SRPN=9;    // Service Request Priority Number
                 
				 SRC_GPSR10.U=(1<<26)|   //SRC_GPSR11.B.SETR=1;
			                  (1<<10)|   //SRC_GPSR11.B.SRE=1;
			                  (1<<11)|   //SRC_GPSR11.B.TOS=1;
			                  (8);       //SRC_GPSR11.B.SRPN=8; 
			}
			else if(os_getCoreId()==2)
			{
                 /* The bug is found here*/
        	     core2_os_blocked_threads=NULL;
        	     //blocked_threads_prev_temp=cond->blocked_threads->prev;
        	     list_append(&core2_os_blocked_threads, cond->blocked_threads,
                              cond->blocked_threads->prev, cond->blocked_threads->next);
                 //locked_threads=cond->blocked_threads;
                 cond->blocked_threads = NULL;

                 /*  The software interrupt 0 of core0 is used.   */
                 //SRC_GPSR20.B.SETR=1;    // Set request
                 //SRC_GPSR20.B.SRE=1;     // Service Request Enable
                 //SRC_GPSR20.B.TOS=0;     // TOS=CPU0
                 //SRC_GPSR20.B.SRPN=9;    // Service Request Priority Number

				 SRC_GPSR20.U=(1<<26)|   //SRC_GPSR11.B.SETR=1;
			                  (1<<10)|   //SRC_GPSR11.B.SRE=1;
			                  (2<<11)|   //SRC_GPSR11.B.TOS=2;
			                  (7);       //SRC_GPSR11.B.SRPN=7; 			
			}
        }
    }
    return 0;// dummy to avoid warning
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               dispatch_signal_in_tick
|
--------------------------------------------------------------------------------------*/
inline void dispatch_signal_in_tick(pthread_t *blocked_threads_ptr, pthread_t last_thread) {

	pthread_t thread, tmp;
	int i;

    tmp = NULL;
    assert(blocked_threads_ptr);
    thread = *blocked_threads_ptr;
	
    if(os_getCoreId()==0)
	{
       while (thread != NULL) 
	   {
        tmp = thread->next;
        i = thread->priority;
        list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                      core0_os_pthread_runnable_threads[i]);
        __putbit(1,(int*)&core0_os_pthread_runnable,i);
        if (thread == last_thread)break;
        thread = tmp;
       }
       *blocked_threads_ptr = tmp;
	 }
	 else if(os_getCoreId()==1)
	 {
       while (thread != NULL) 
	   {
        tmp = thread->next;
        i = thread->priority;
          list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                      core1_os_pthread_runnable_threads[i]);
        __putbit(1,(int*)&core1_os_pthread_runnable,i);
        if (thread == last_thread)break;
        thread = tmp;
       }
       *blocked_threads_ptr = tmp;
	 }
	 else if(os_getCoreId()==2)
	 {
       while (thread != NULL) 
	   {
        tmp = thread->next;
        i = thread->priority;
          list_append(&core2_os_pthread_runnable_threads[i], thread, thread,
                      core2_os_pthread_runnable_threads[i]);
        __putbit(1,(int*)&core2_os_pthread_runnable,i);
        if (thread == last_thread)break;
        thread = tmp;
       }
       *blocked_threads_ptr = tmp;
	 }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               Trap class 6 handler (System trap) called by
|               __syscallfunc(DISPATCH_WAIT)  int dispatch_wait(void *, void *);
|               __syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
|
--------------------------------------------------------------------------------------*/
static void trapsystem(pthread_t *blocked_threads_ptr, pthread_t last_thread) {
    int tin, i;
    pthread_t thread, tmp;

    __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); // put d15 in C variable tin

    if(os_getCoreId()==0)
	{
        core0_os_pthread_running->lcx = __mfcr(CPU_PCXI);
        i = core0_os_pthread_running->priority;
        assert(core0_os_pthread_runnable_threads[i] == core0_os_pthread_running);
        switch (tin) 
		{
          case DISPATCH_WAIT: // _swap_out _pthread_running
             {
                list_delete_first(&core0_os_pthread_runnable_threads[i]);
                list_append(blocked_threads_ptr, core0_os_pthread_running, core0_os_pthread_running, NULL);
                __putbit(neza(core0_os_pthread_runnable_threads[i]),(int*)&core0_os_pthread_runnable,i);
		     }
             break;
          case DISPATCH_SIGNAL:
		     {
                tmp = NULL;
                assert(blocked_threads_ptr);
                thread = *blocked_threads_ptr;
                while (thread != NULL)
			    {
                     tmp = thread->next;
                     i = thread->priority;
                     list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                        core0_os_pthread_runnable_threads[i]);
                     __putbit(1,(int*)&core0_os_pthread_runnable,i);
                     if (thread == last_thread) break;
                     thread = tmp;
                }
                *blocked_threads_ptr = tmp;
                break;
			  }
          default:
              break;
         }
	}
	else if(os_getCoreId()==1)
	{
        core1_os_pthread_running->lcx = __mfcr(CPU_PCXI);
        i = core1_os_pthread_running->priority;
        assert(core1_os_pthread_runnable_threads[i] == core1_os_pthread_running);
        switch (tin) 
		{
          case DISPATCH_WAIT: // _swap_out _pthread_running
             {
                list_delete_first(&core1_os_pthread_runnable_threads[i]);
                list_append(blocked_threads_ptr, core1_os_pthread_running, core1_os_pthread_running, NULL);
                __putbit(neza(core1_os_pthread_runnable_threads[i]),(int*)&core1_os_pthread_runnable,i);
		     }
             break;
          case DISPATCH_SIGNAL:
		     {
                tmp = NULL;
                assert(blocked_threads_ptr);
                thread = *blocked_threads_ptr;
                while (thread != NULL)
			    {
                     tmp = thread->next;
                     i = thread->priority;
                     list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                        core1_os_pthread_runnable_threads[i]);
                      __putbit(1,(int*)&core1_os_pthread_runnable,i);
                     if (thread == last_thread) break;
                     thread = tmp;
                }
                *blocked_threads_ptr = tmp;
                break;
			  }
          default:
              break;
         }
	}
	else if(os_getCoreId()==2)
	{
        core2_os_pthread_running->lcx = __mfcr(CPU_PCXI);
        i = core2_os_pthread_running->priority;
        assert(core2_os_pthread_runnable_threads[i] == core2_os_pthread_running);
        switch (tin) 
		{
          case DISPATCH_WAIT: // _swap_out _pthread_running
             {
                list_delete_first(&core2_os_pthread_runnable_threads[i]);
                list_append(blocked_threads_ptr, core2_os_pthread_running, core2_os_pthread_running, NULL);
                __putbit(neza(core2_os_pthread_runnable_threads[i]),(int*)&core2_os_pthread_runnable,i);
		     }
             break;
          case DISPATCH_SIGNAL:
		     {
                tmp = NULL;
                assert(blocked_threads_ptr);
                thread = *blocked_threads_ptr;
                while (thread != NULL)
			    {
                     tmp = thread->next;
                     i = thread->priority;
                     list_append(&core2_os_pthread_runnable_threads[i], thread, thread,
                        core2_os_pthread_runnable_threads[i]);
                      __putbit(1,(int*)&core2_os_pthread_runnable,i);
                     if (thread == last_thread) break;
                     thread = tmp;
                }
                *blocked_threads_ptr = tmp;
                break;
			  }
          default:
              break;
         }
	}

    pthread_start_np();
}



/*-------------------------------------------------------------------------------------
|
|   Description:
|           schedule_in_tick
|           
--------------------------------------------------------------------------------------*/
inline void schedule_in_tick(void)
{
    pthread_cond_t  *cond;
	pthread_cond_t  *cond_buffer[PTHREAD_COND_TIMEDWAIT_SIZE];
    uint32_t        index;
	uint32_t        release_count=0;

 if(os_getCoreId()==0)
 {
    for(index=0;index<PTHREAD_COND_TIMEDWAIT_SIZE;index++)
    {
      if(stm_ticks[index]==stm_tick_count)
	  {		
		cond_buffer[release_count] = stm_cond[index];
		stm_ticks[index]           = USHRT_MAX;                             // free place in array 
		
		release_count++;
	  }
    }
 }
 else if(os_getCoreId()==1)
 {
    for(index=0;index<PTHREAD_COND_TIMEDWAIT_SIZE;index++)
    {
      if(core1_os_stm_ticks[index]==core1_os_stm_tick_count)
	  {		
		cond_buffer[release_count] = core1_os_stm_cond[index];
		core1_os_stm_ticks[index]  = USHRT_MAX;                             // free place in array 
		
		release_count++;
	  }
    }
 }
 else if(os_getCoreId()==2)
 {
    for(index=0;index<PTHREAD_COND_TIMEDWAIT_SIZE;index++)
    {
      if(core2_os_stm_ticks[index]==core2_os_stm_tick_count)
	  {		
		cond_buffer[release_count] = core2_os_stm_cond[index];
		core2_os_stm_ticks[index]  = USHRT_MAX;                             // free place in array 
		
		release_count++;
	  }
    }
 }
    //setup parameter and jump to trapsystem
    if(release_count!=0)
	{
	   assert(cond_buffer[0] != NULL);
	    if(release_count>1)
 	   {
 	        while(--release_count)
 		   {
 	          dispatch_signal_in_tick(&cond_buffer[release_count]->blocked_threads,NULL);
 		   }
 	   }
	  assert(cond_buffer[0] != NULL);
 	
	   cond   =cond_buffer[0];                        // get current condition
       __asm( " mov.aa a4,%0 \n"
              " mov.aa a5,%1 \n"
              " mov d15,%2   \n"
              " jg trapsystem  "
              ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
	 }
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           pthread_cond_timedwait_np
|           time block
|           
--------------------------------------------------------------------------------------*/
int pthread_cond_timedwait_np(pthread_cond_t *cond,//!< [in] condition pointer
        uint16_t reltime,
        uint32_t task_id) //!< [in] relative time are the relative time STM_TIM4 ticks.NOT PORTABLE.
{
	uint16_t new_tick_count;
    uint16_t set_count;
	
    assert(cppn()==0); // CCPN must be 0, pthread_create cannot be called from ISR
    assert(cond != NULL);

	if(os_getCoreId()==0)
	{
	  new_tick_count           = stm_tick_count + 1;
	  set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE
	
      stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
      stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)

      //__swap(&mutex->lock, false);
      int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
      //__swap(&mutex->lock, true);
      //mutex->owner = core0_os_pthread_running;
	}
	else if(os_getCoreId()==1)
	{
	  new_tick_count           = core1_os_stm_tick_count + 1;
	  set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE
	
      core1_os_stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
      core1_os_stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)
	
      //__swap(&mutex->lock, false);
      int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
      //__swap(&mutex->lock, true);
      //mutex->owner = core1_os_pthread_running;

	}
	else if(os_getCoreId()==2)
	{
	  new_tick_count           = core2_os_stm_tick_count + 1;
	  set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE
	
      core2_os_stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
      core2_os_stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)

      //__swap(&mutex->lock, false);
      int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
      //__swap(&mutex->lock, true);
      //mutex->owner = core2_os_pthread_running;
	}
    return 0;
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|           Ifx_STM0_compare1_Isr
|           the stm0 interrupt is used for core0
|           
--------------------------------------------------------------------------------------*/

void __interrupt(10) __vector_table(0) Ifx_STM0_Isr(void)
{  
   stm_tick_count=(stm_tick_count+1)%0xFFFF;   // os tick from 0-0xffff
   update_stm0_ticks();                        // update the tick, this line cannot be changed now. 
   schedule_in_tick();

}
/*-------------------------------------------------------------------------------------
|
|   Description:
|           Ifx_STM0_compare1_Isr
|           the stm1 interrupt is used for core1
|           
--------------------------------------------------------------------------------------*/
void __interrupt(11) __vector_table(0) Ifx_STM1_Isr(void)
{
   core1_os_stm_tick_count=(core1_os_stm_tick_count+1)%0xFFFF;   // os tick from 0-0xffff
   update_stm1_ticks();                                          // update the tick, this line cannot be changed now. 
   schedule_in_tick();

}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           Ifx_STM0_compare1_Isr
|           the stm2 interrupt is used for core2
|           
--------------------------------------------------------------------------------------*/

void __interrupt(12) __vector_table(0) Ifx_STM2_Isr(void)
{
   core2_os_stm_tick_count=(core2_os_stm_tick_count+1)%0xFFFF;   // os tick from 0-0xffff
   update_stm2_ticks();                                          // update the tick, this line cannot be changed now. 
   schedule_in_tick();

}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           CPU0_SOFT0_Isr
|           
--------------------------------------------------------------------------------------*/
void __interrupt(9) __vector_table(0) CPU0_SOFT0_Isr(void)
{
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&core0_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           CPU0_SOFT0_Isr
|           
--------------------------------------------------------------------------------------*/
void __interrupt(8) __vector_table(0) CPU1_SOFT0_Isr(void)
{
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&core1_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           CPU0_SOFT0_Isr
|           
--------------------------------------------------------------------------------------*/
void __interrupt(7) __vector_table(0) CPU2_SOFT0_Isr(void)
{
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&core2_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           Ifx_STM0_compare1_Isr
|           
--------------------------------------------------------------------------------------*/
void __interrupt(21) __vector_table(0) Ifx_STM0_compare1_Isr(void)
{
 	update_stm0_compare1_ticks(1000);// Unit:ms ,the max is 0xFFFFFFFF/100000=42949ms(42.949s);
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           Trap vector table entry to trap class 6 handler enables interrupts
|           core0 trap 6
|
--------------------------------------------------------------------------------------*/
void IfxCpu_Trap_systemCall_Cpu0(uint32_t tin)
{
	/* Add the kernel of OS */
	/* Kernel begins        */
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|           Trap vector table entry to trap class 6 handler enables interrupts
|           core1 trap 6
|
--------------------------------------------------------------------------------------*/

void IfxCpu_Trap_systemCall_Cpu1(uint32_t tin)
{
	/* Add the kernel of OS */
	/* Kernel begins        */
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           Trap vector table entry to trap class 6 handler enables interrupts
|           core2 trap 6
|
--------------------------------------------------------------------------------------*/
void IfxCpu_Trap_systemCall_Cpu2(uint32_t tin)
{
	/* Add the kernel of OS */
	/* Kernel begins        */
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");
}



