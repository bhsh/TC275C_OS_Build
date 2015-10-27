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
#define DISPATCH_ONLY     4

//#define OLD_AVALIABLE


__syscallfunc(DISPATCH_WAIT)   int dispatch_wait(void *, void *);
__syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
__syscallfunc(DISPATCH_ONLY)   int dispatch_only(void *, void *);
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

uint32_t core0_os_pthread_time_waiting;
uint32_t core1_os_pthread_time_waiting;
uint32_t core2_os_pthread_time_waiting;

//pthread_cond_t *core0_cond = NULL;
//pthread_cond_t core1_cond  = PTHREAD_COND_INITIALIZER;
//pthread_cond_t core2_cond  = PTHREAD_COND_INITIALIZER;

allthreads_status_t core0_allthreads_status = ALLTHREADS_WORKING;
allthreads_status_t core1_allthreads_status = ALLTHREADS_WORKING;
allthreads_status_t core2_allthreads_status = ALLTHREADS_WORKING;

 //! tw array hold condition and time for pthread_cond_timedwait_np.
static uint16_t  stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
    { 
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 	
    };//!< time
static pthread_cond_t  *stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL                     
    };//!< condition
static pthread_cond_t  core0_os_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
	{  
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,                     
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,    
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,                     
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,    
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,                    
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,    
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,                     
        CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER,CORE0_PTHREAD_COND_INITIALIZER   
    };
static uint16_t  core1_os_stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 
				    
    };//!< time
static pthread_cond_t  *core1_os_stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL  

    };//!< condition
static pthread_cond_t  core1_os_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
	{  
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,                     
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,    
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,                     
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,    
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,                    
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,    
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,                     
        CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER,CORE1_PTHREAD_COND_INITIALIZER   
    };
static uint16_t  core2_os_stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE] =
	{
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
	    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 				    
    };//!< time
static pthread_cond_t  *core2_os_stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
	{
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL 

    };//!< condition
static pthread_cond_t  core2_os_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
	{  
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,                     
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,    
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,                     
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,    
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,                    
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,    
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,                     
        CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER,CORE2_PTHREAD_COND_INITIALIZER   
    };
extern uint32 stm0CompareValue;
extern uint32 stm1CompareValue;
extern uint32 stm2CompareValue;
extern uint32 stm0CompareValue2;

unsigned int core0_mutex=0;
unsigned int core1_mutex=0;
unsigned int core2_mutex=0;

inline unsigned int core_getMutex(uint32_t *mutex)
{
  return __swap(mutex, true);
}
inline void core_returnMutex(uint32_t *mutex)
{
  *mutex=0x0;
}

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
    //IfxPort_togglePin(&MODULE_P33, 10);
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
extern void get_thread_init_stack_address(uint32_t,uint32_t,uint32_t);
int pthread_create_np(pthread_t thread, //!< [in] thread control block pointer.
        const pthread_attr_t *attr, //!<  [in] thread attribute. Can be NULL to use default.
        void(*start_routine)(void *,task_ptr_t),//!<  [in] thread function pointer
        void *arg,
        task_ptr_t core0_task_ptr)
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
	cx->l.a5 = core0_task_ptr;
    thread->arg = arg;

	get_thread_init_stack_address(os_getCoreId(),(int)arg,(int)(thread->stack + *thread->stack));

    uint32_t i = thread->priority;
	
    if(os_getCoreId()== CORE0)
    {   
       list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                  core0_os_pthread_runnable_threads[i]);
       __putbit(1,(int*)&core0_os_pthread_runnable,i); // mark current thread ready
           }
    else if(os_getCoreId()==CORE1)
    {
       list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                  core1_os_pthread_runnable_threads[i]);
       __putbit(1,(int*)&core1_os_pthread_runnable,i); // mark current thread ready
    }
	else if(os_getCoreId()==CORE2)
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
    assert(cond!= NULL); // errno = EINVAL

	//if(cond->multi_semaphore <= 1)
	//{  
	//    cond->multi_semaphore = 0;
        dispatch_wait(&cond->blocked_threads, NULL);// add this thread to the list of blocked threads by this cond
    //}
    //else
	//{  
	   /* cond->multi_semaphore > 1 */
    //   cond->multi_semaphore--;
	//}	
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
	uint32_t current_cpu_id = os_getCoreId();
	uint32_t cond_core_id   = cond->core_id;

#if 0
	if(cond->multi_semaphore == 0)
	{
        cond->multi_semaphore = 1;
#endif
		if (cond->blocked_threads != NULL)
		{	 
			 if((cond_core_id == current_cpu_id)&&(0 == cppn()))
		     {		
	              // _pthread_running on CCPN=0
	              dispatch_signal(&cond->blocked_threads, cond->blocked_threads->prev);// swap in with mutex unlocked
		     }
	         else
			 {
		           if(cond_core_id == CORE0)
			      { 
					 while(0!=core_getMutex(&core0_mutex)){};
					 
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

					 //core_returnMutex(&core0_mutex);
	               }
				   else if(cond_core_id==CORE1)
				   { 
	                 while(0!=core_getMutex(&core1_mutex)){};
					
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
	                 //SRC_GPSR10.B.SRPN=8;    // Service Request Priority Number
	                 
					 SRC_GPSR10.U=(1<<26)|   //SRC_GPSR11.B.SETR=1;
				                  (1<<10)|   //SRC_GPSR11.B.SRE=1;
				                  (1<<11)|   //SRC_GPSR11.B.TOS=1;
				                  (8);       //SRC_GPSR11.B.SRPN=8; 
				                  
					 //core_returnMutex(&core1_mutex);
				   }
				   else if(cond_core_id==CORE2)
				   { 
	                 while(0!=core_getMutex(&core2_mutex)){};
					 
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
	                 //SRC_GPSR20.B.SRPN=7;    // Service Request Priority Number

					 SRC_GPSR20.U=(1<<26)|   //SRC_GPSR11.B.SETR=1;
				                  (1<<10)|   //SRC_GPSR11.B.SRE=1;
				                  (2<<11)|   //SRC_GPSR11.B.TOS=2;
				                  (7);       //SRC_GPSR11.B.SRPN=7; 	
				                  
				     //core_returnMutex(&core2_mutex);
				    }
			  }		
	    }
#if 0
	}
	else
	{
       cond->multi_semaphore++;
	}
#endif
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
	
    if(os_getCoreId()==CORE0)
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
	 else if(os_getCoreId()==CORE1)
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
	 else if(os_getCoreId()==CORE2)
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
//#pragma align 4
static void trapsystem(pthread_t *blocked_threads_ptr, pthread_t last_thread) {
    int tin, i;
    pthread_t thread, tmp;

    __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); // put d15 in C variable tin

    if(os_getCoreId()==CORE0)
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
		  case DISPATCH_ONLY:
		  	 break;
          default:
              break;
         }
		 /* unlock core0_mutex */
		 core_returnMutex(&core0_mutex);
	}
	else if(os_getCoreId()==CORE1)
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
		  case DISPATCH_ONLY:
		  	 break;		  
          default:
              break;
         }
		 /* unlock core1_mutex */
		 core_returnMutex(&core1_mutex);
	}
	else if(os_getCoreId()==CORE2)
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
		  case DISPATCH_ONLY:
		  	 break;		  
          default:
              break;
         }
		 /* unlock core0_mutex */
		 core_returnMutex(&core2_mutex);		
	}
     pthread_start_np();
}
//#pragma align restore
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
	 uint32_t        release_count = 0;
	 uint32_t        tempt_index;
	
	 if(os_getCoreId()==CORE0)
	 {  	
	    tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core0_os_pthread_time_waiting);
		if( tempt_index == 0) return;
		tempt_index = tempt_index - 1;
	    for(index = 0 ; index <= tempt_index ; index++)
	    {
		      if(stm_ticks[index] == stm_tick_count)
			  {		
				cond_buffer[release_count] = stm_cond[index];
				stm_ticks[index]           = USHRT_MAX;                             // free place in array 
				__putbit(0,(int*)&core0_os_pthread_time_waiting,index); 
				release_count++;
			  }
	    }
	 }
	 else if(os_getCoreId() == CORE1)
	 {		
	 	tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core1_os_pthread_time_waiting);
		if( tempt_index == 0) return;
		tempt_index = tempt_index - 1;
	    for(index = 0 ; index <= tempt_index ; index++)
	    {
		      if(core1_os_stm_ticks[index] == core1_os_stm_tick_count)
			  {		
				cond_buffer[release_count] = core1_os_stm_cond[index];
				core1_os_stm_ticks[index]  = USHRT_MAX;      
				__putbit(0,(int*)&core1_os_pthread_time_waiting,index); 
				release_count++;
			  }
	    }
	 }
	 else if(os_getCoreId() == CORE2)
	 {
	 	tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core2_os_pthread_time_waiting);
		if( tempt_index == 0) return;
		tempt_index = tempt_index - 1;
	    for(index = 0 ; index <= tempt_index ; index++)
	    {
		      if(core2_os_stm_ticks[index] == core2_os_stm_tick_count)
			  {		
				cond_buffer[release_count] = core2_os_stm_cond[index];
				core2_os_stm_ticks[index]  = USHRT_MAX;  
				__putbit(0,(int*)&core2_os_pthread_time_waiting,index); 
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
|           pthread_cond_timedwait_np(optimized)
|           time block
|           
--------------------------------------------------------------------------------------*/
int pthread_cond_timedwait_np(uint16_t reltime) //!< [in] relative time are the relative time STM_TIM4 ticks.NOT PORTABLE.
{
	uint16_t new_tick_count;
    uint16_t set_count;
	uint32_t task_id = 0;
	pthread_cond_t *cond;
	
    assert(cppn()==0); // CCPN must be 0, pthread_create cannot be called from ISR

	if(os_getCoreId()==CORE0)
	{	  	
	  new_tick_count           = stm_tick_count + 1;
	  set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE

      /* Search the empty position. */
      while((stm_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  /* There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;
 
      cond = &core0_os_cond[task_id];
	  __putbit(1,(int*)&core0_os_pthread_time_waiting,task_id); // mark current thread ready
      stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
      stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)

      int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
	}
	else if(os_getCoreId()==CORE1)
	{ 
	  new_tick_count           = core1_os_stm_tick_count + 1;
	  set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE

      /* Search the empty position. */
      while((core1_os_stm_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  /* There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;

      cond = &core1_os_cond[task_id];
	  __putbit(1,(int*)&core1_os_pthread_time_waiting,task_id); // mark current thread ready
	  
	  core1_os_stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
      core1_os_stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)
	
      int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked

	}
	else if(os_getCoreId()==CORE2)
	{
	  new_tick_count           = core2_os_stm_tick_count + 1;
	  set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE

      /* Search the empty position. */
      while((core2_os_stm_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  /* There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;

      cond = &core2_os_cond[task_id];
	  __putbit(1,(int*)&core2_os_pthread_time_waiting,task_id); // mark current thread ready

	  core2_os_stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
      core2_os_stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)

      int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
	}
    return 0;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           Suspend_AllThreads
|           time block
|           
--------------------------------------------------------------------------------------*/
void os_suspend_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */
   uint32_t current_cpu_id = os_getCoreId();

   if(current_cpu_id == CORE0)
   {	
   	   if(core0_allthreads_status == ALLTHREADS_WORKING)
	   {   
	   	   core0_allthreads_status = ALLTHREADS_SUSPENDED;
	   }
	   else
	   {
		   	    /* Do nothing. */
	   }
   }
   else if(current_cpu_id == CORE1)
   {
   	   if(core1_allthreads_status == ALLTHREADS_WORKING)
	   {   
	   	   core1_allthreads_status = ALLTHREADS_SUSPENDED;
	   }
	   else
	   {
		   	    /* Do nothing. */
	   }	
   }
   else if(current_cpu_id == CORE2)
   {
   	   if(core2_allthreads_status == ALLTHREADS_WORKING)
	   {   
	   	   core2_allthreads_status = ALLTHREADS_SUSPENDED;
	   }
	   else
	   {
		   	    /* Do nothing. */
	   }	
   }
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|           Restore_AllThreads
|           time block
|           
--------------------------------------------------------------------------------------*/
void os_restore_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */
   uint32_t current_cpu_id = os_getCoreId();

   if(current_cpu_id == CORE0)
   {  
   	   if(core0_allthreads_status == ALLTHREADS_SUSPENDED)
	   {  
	   	     core0_allthreads_status = ALLTHREADS_WORKING;
		     /* If there is thread higher than the current thread, switch the contex. else keep */
		     if(core0_os_pthread_running->priority < ((PTHREAD_PRIO_MAX-1) - __clz(core0_os_pthread_runnable)))
			 {
               dispatch_only(NULL,NULL);     
			 }
			 else
			 {
			      /* Do nothing. */
			 }
	   }
	   else
	   {
		   	    /* Do nothing. */
	   }	   
   }
   else if(current_cpu_id == CORE1)
   {
   	   if(core1_allthreads_status == ALLTHREADS_SUSPENDED)
	   {  
	   	  	 core1_allthreads_status = ALLTHREADS_WORKING;
		     /* If there is thread higher than the current thread, switch the contex. else keep */
		     if(core1_os_pthread_running->priority < ((PTHREAD_PRIO_MAX-1) - __clz(core1_os_pthread_runnable)))
			 {
               dispatch_only(NULL,NULL);     
			 }
			 else
			 {
			      /* Do nothing. */
			 }		  
	   }
	   else
	   {
		   	    /* Do nothing. */
	   }
   }
   else if(current_cpu_id == CORE2)
   {
   	   if(core2_allthreads_status == ALLTHREADS_SUSPENDED)
	   {  
	   	  	 core2_allthreads_status = ALLTHREADS_WORKING;
		     if(core2_os_pthread_running->priority < ((PTHREAD_PRIO_MAX-1) - __clz(core2_os_pthread_runnable)))
			 {
               dispatch_only(NULL,NULL);     
			 }
			 else
			 {
			      /* Do nothing. */
			 }		
	   }
	   else
	   {
		   	    /* Do nothing. */
	   }	
   }
 
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|           os_dsable_allinterrupts
|           time block
|           
--------------------------------------------------------------------------------------*/
void os_dsable_allinterrupts(void)
{
   __enable();
}
/*-------------------------------------------------------------------------------------
|
|   Description:
|           os_enable_allinterrupt
|           time block
|           
--------------------------------------------------------------------------------------*/
void os_enable_allinterrupt(void)
{
  __disable();
  __nop();

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
|           CPU1_SOFT0_Isr
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
|           CPU2_SOFT0_Isr
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



