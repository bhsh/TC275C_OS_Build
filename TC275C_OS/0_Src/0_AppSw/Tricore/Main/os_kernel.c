/****************************************************************************/
/* FILE NAME:    os_kernel.c                                                */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file include the kernel logic of AURIX 3-core os     */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"
#include "_Reg/IfxSrc_reg.h"
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
#include "communication.h"
#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define DISPATCH_WAIT     2
#define DISPATCH_SIGNAL   3
#define DISPATCH_ONLY     4

/****************************************************************************/
/* Global Variable Definitions                                              */
/****************************************************************************/
osu32_t  core0_os_pthread_runnable;
osu32_t  core1_os_pthread_runnable;
osu32_t  core2_os_pthread_runnable;
pthread_t core0_os_pthread_running;
pthread_t core1_os_pthread_running;
pthread_t core2_os_pthread_running;
pthread_t core0_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
pthread_t core1_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
pthread_t core2_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
allthreads_status_t core0_allthreads_status;
allthreads_status_t core1_allthreads_status;
allthreads_status_t core2_allthreads_status;

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static osu32_t  core0_mutex;
static osu32_t  core1_mutex;
static osu32_t  core2_mutex;
static osu16_t  core0_os_stm_tick_count;
static osu16_t  core1_os_stm_tick_count;
static osu16_t  core2_os_stm_tick_count;
static osu32_t  core0_os_pthread_time_waiting;
static osu32_t  core1_os_pthread_time_waiting;
static osu32_t  core2_os_pthread_time_waiting;
static pthread_t core0_os_blocked_threads;
static pthread_t core1_os_blocked_threads;
static pthread_t core2_os_blocked_threads;
static osu16_t  stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
{ 
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 	
};
static pthread_cond_t  *stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL                     
};
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
static osu16_t  core1_os_stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 
};
static pthread_cond_t  *core1_os_stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL  
};
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
static osu16_t  core2_os_stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE] =
{
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 				    
};
static pthread_cond_t  *core2_os_stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
{
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL 
};
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

/****************************************************************************/
/* Extern Variable Definitions                                              */
/****************************************************************************/
extern osu32_t  stm0CompareValue;
extern osu32_t  stm1CompareValue;
extern osu32_t  stm2CompareValue;
extern osu32_t  stm0CompareValue2;

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
__syscallfunc(DISPATCH_WAIT)   os32_t dispatch_wait(void *, void *);
__syscallfunc(DISPATCH_SIGNAL) os32_t dispatch_signal(void *, void *);
__syscallfunc(DISPATCH_ONLY)   os32_t dispatch_only(void *, void *);

/****************************************************************************/
/* Extern Prototype Definitions                                             */
/****************************************************************************/
extern void get_thread_init_stack_address(osu32_t,osu32_t,osu32_t);

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Get mutex                                      */
/****************************************************************************/
inline osu32_t core_getMutex(osu32_t *mutex)
{
  return __swap(mutex, true);
} /* End of core_getMutex function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Return mutex                                   */
/****************************************************************************/
inline void core_returnMutex(osu32_t *mutex)
{
  *mutex=0x0;
} /* End of core_returnMutex function */

/****************************************************************************/
/* DESCRIPTION: <CORE0> Update stm0 compare1                                */
/****************************************************************************/
inline void update_stm0_ticks(void)
{
    osu32_t stmTicks;

    stmTicks= (osu32_t)(stm0CompareValue*1);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + stmTicks);
    /* IfxPort_togglePin(&MODULE_P33, 8); */
} /* End of update_stm0_ticks function */

/****************************************************************************/
/* DESCRIPTION: <CORE1> Update stm1 compare1                                */
/****************************************************************************/
inline void update_stm1_ticks(void)
{
    osu32_t stmTicks;
	
    stmTicks= (osu32_t)(stm1CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM1, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM1, IfxStm_Comparator_0) + stmTicks);
    /* IfxPort_togglePin(&MODULE_P33, 9); */
} /* End of update_stm1_ticks function */

/****************************************************************************/
/* DESCRIPTION: <CORE2> Update stm0 compare1                                */
/****************************************************************************/
inline void update_stm2_ticks(void)
{
    osu32_t stmTicks;
    stmTicks= (osu32_t)(stm2CompareValue * 1);
    IfxStm_updateCompare (&MODULE_STM2, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM2, IfxStm_Comparator_0) + stmTicks);
    /* IfxPort_togglePin(&MODULE_P33, 10); */
} /* End of update_stm2_ticks function */

/****************************************************************************/
/* DESCRIPTION: <CORE0> Update stm0 compare1                                */
/****************************************************************************/
inline void update_stm0_compare1_ticks(osu32_t tick_ms)
{
    osu32_t stmTicks;

    stmTicks= (osu32_t)(stm0CompareValue2*tick_ms);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_1, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_1) + stmTicks);
    /* IfxPort_togglePin(&MODULE_P33, 10); */
} /* End of update_stm0_compare1_ticks function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Append an element at the end of a list         */
/****************************************************************************/
inline void list_append(pthread_t *head, /* <*head> list head pointer */
                           pthread_t  elem,  /* <elem> list element pointer */
                           pthread_t  list_prev, /* <list_prev> list_prev  pointer */
                           pthread_t  elem_next) /* <elem_next> elem_next  pointer */
{
    assert(head != NULL);
    assert(elem != NULL);

    pthread_t list = *head;
    if (list == NULL) {
        elem->next = elem_next;
    	/* elem->next = elem; */
        elem->prev = elem;
        *head = elem;
    } else {
        elem->next = elem_next;
        elem->prev = list->prev;
        list->prev->next = elem;
        list->prev = list_prev;
    }
} /* End of list_append function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Delete the first element of a list             */
/****************************************************************************/
static void list_delete_first(pthread_t *head) { /* <*head> list head pointer */
    assert(head);

    pthread_t old = *head;
    pthread_t new = old->next;

    if (new != NULL) {
        old->prev->next = new;
        new->prev = old->prev;
        if (new->next == new)
            new->next = NULL; /* If the list has only one element than set ->next = NULL */
    }
    *head = new;
} /* End of list_delete_first function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Create threads                                 */
/****************************************************************************/
os32_t pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                            const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                            void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                            void *arg,  /* <*arg> 1st argument of thread */
                            task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
{

    const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
    osu32_t fcx;
    context_t *cx;

    if (attr == NULL)
        attr = &default_attr;

    fcx = __mfcr(CPU_FCX);
    thread->lcx = fcx - 1;
    __mtcr(CPU_FCX, fcx - 2);

    cx = cx_to_addr(fcx);
    cx->u.psw = 0 << 12          /* <EVERY CORE> Protection Register Set PRS=0 */
            | attr->mode << 10   /* <EVERY CORE> I/O Privilege */
            | 0 << 9             /* <EVERY CORE> Current task uses a user stack IS=0 */
            | 0 << 8             /* <EVERY CORE> Write permission to global registers A0, A1, A8, A9 is disabled */
            | 1L << 7            /* <EVERY CORE> Call depth counting is enabled CDE=1 */
            | attr->call_depth_overflow; /* <EVERY CORE>  Call Depth Overflow */
    cx->u.a10 = thread->stack + *thread->stack; /* <EVERY CORE> Stack grow down */
    cx->u.a11 = 0;  /* <EVERY CORE> New task has no return address */
    cx->u.pcxi = 0; /* <EVERY CORE> No previous context; */
    cx--;
    cx->l.pcxi = 0L << 22 /* <EVERY CORE> Previous CPU Priority Number PCPN=0 TriCore:  0L << 24  different PCXI between */
            | 1L << 21    /* <EVERY CORE> Previous Interrupt Enable PIE=1     TriCore:| 1L << 23  Aurix and TriCores     */
            | 1L << 20    /* <EVERY CORE> Upper Context Tag.                  TriCore:| 1L << 22                         */
            | fcx;        /* <EVERY CORE> Previous Context Pointer is the upper context                                  */
    cx->l.pc = start_routine; /* <EVERY CORE> init new thread start address */ 
    cx->l.a4 = arg;
	cx->l.a5 = core0_task_ptr;
    thread->arg = arg;

	get_thread_init_stack_address(os_getCoreId(),(os32_t)arg,(os32_t)(thread->stack + *thread->stack));

    osu32_t i = thread->priority;
	
    if(os_getCoreId()== CORE0)
    {   
       list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                  core0_os_pthread_runnable_threads[i]);
       __putbit(1,(os32_t*)&core0_os_pthread_runnable,i); /* <CORE0> Mark current thread ready */
           }
    else if(os_getCoreId()==CORE1)
    {
       list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                  core1_os_pthread_runnable_threads[i]);
       __putbit(1,(os32_t*)&core1_os_pthread_runnable,i); /* <CORE1> Mark current thread ready */
    }
	else if(os_getCoreId()==CORE2)
	{
       list_append(&core2_os_pthread_runnable_threads[i], thread, thread,
                  core2_os_pthread_runnable_threads[i]);
       __putbit(1,(os32_t*)&core2_os_pthread_runnable,i); /* <CORE2> Mark current thread ready */
	}
    return 0; /* Dummy to avoid warning */
} /* End of pthread_create_np function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Lock an resource.This is an OS API that is     */
/*              provided to os user                                         */
/****************************************************************************/
os32_t pthread_mutex_lock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */

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
    return 0;/* Dummy to avoid warning */
} /* End of pthread_mutex_lock function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Unlock an resource.This is an OS API that is   */
/*              provided to os user                                         */
/****************************************************************************/
os32_t pthread_mutex_unlock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */ 

	if(os_getCoreId()==0)
	{
        if (mutex->owner != core0_os_pthread_running) 
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
        if (mutex->owner != core1_os_pthread_running) 
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
        if (mutex->owner != core2_os_pthread_running) 
             return -1;

        pthread_t threads = mutex->blocked_threads;
        mutex->owner = NULL;
        mutex->lock = false;
        mutex->blocked_threads = NULL;
        if (threads != NULL)
            dispatch_signal(&threads, NULL);
	}
    return 0; /* Dummy to avoid warning */
} /* End of pthread_mutex_unlock function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Wait a condition.This is an OS API that is     */
/*              provided to os user                                         */
/****************************************************************************/
os32_t pthread_cond_wait(pthread_cond_t *cond)/* <*cond> condition pointer */
{
    assert(cppn()==0); /* CCPN must be 0, pthread_create cannot be called from ISR */
    assert(cond!= NULL); /* Make sure there is one condition argument. If no, __debug() will be entered */

	//if(cond->multi_semaphore <= 1)
	//{  
	//    cond->multi_semaphore = 0;

	    /* <EVERY CORE> Add this thread to the list of blocked threads by this cond */
        dispatch_wait(&cond->blocked_threads, NULL);
    //}
    //else
	//{  
	   /* cond->multi_semaphore > 1 */
    //   cond->multi_semaphore--;
	//}	
    return 0;/* Dummy to avoid warning */
} /* End of pthread_cond_wait function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(pthread_cond_broadcast) is used inside */
/*              threads and interrupts in order to active threads blocked.  */
/*              The thread and interrupt in one core can active the thread  */
/*              of another core                                             */
/****************************************************************************/
os32_t pthread_cond_broadcast(pthread_cond_t *cond) /* <*cond> condition pointer */
{
    assert(cond!=NULL);
	osu32_t current_cpu_id = os_getCoreId();
	osu32_t cond_core_id   = cond->core_id;

#if 0
	if(cond->multi_semaphore == 0)
	{
        cond->multi_semaphore = 1;
#endif
		if (cond->blocked_threads != NULL)
		{	 
			 if((cond_core_id == current_cpu_id)&&(0 == cppn()))
		     {		
	              /* <EVERY CORE> _pthread_running on CCPN=0 */
	              dispatch_signal(&cond->blocked_threads, cond->blocked_threads->prev);
		     }
	         else
			 {
		           if(cond_core_id == CORE0)
			      { 
					 while(0!=core_getMutex(&core0_mutex)){};
					 
	        	     core0_os_blocked_threads=NULL;
					 
	        	     /* blocked_threads_prev_temp=cond->blocked_threads->prev; */
	        	     list_append(&core0_os_blocked_threads, cond->blocked_threads,
	                              cond->blocked_threads->prev, cond->blocked_threads->next);

					 /* locked_threads=cond->blocked_threads; */
	                 cond->blocked_threads = NULL;

	                 /* <CORE0> The software interrupt 0 of core0 is used.   */
					 SRC_GPSR00.U=(1<<26)| /* SRC_GPSR00.B.SETR=1; <Set request>                     */
				                  (1<<10)| /* SRC_GPSR00.B.SRE=1;  <Service Request Enable>          */
				                  (0<<11)| /* SRC_GPSR00.B.TOS=0;  <TOS=CPU0>                        */
				                  (9);     /* SRC_GPSR00.B.SRPN=9; <Service Request Priority Number> */

					 /* core_returnMutex(&core0_mutex); */
	               }
				   else if(cond_core_id==CORE1)
				   { 
	                 while(0!=core_getMutex(&core1_mutex)){};
					
	        	     core1_os_blocked_threads=NULL;
					 
	        	     /* blocked_threads_prev_temp=cond->blocked_threads->prev; */
	        	     list_append(&core1_os_blocked_threads, cond->blocked_threads,
	                                cond->blocked_threads->prev, cond->blocked_threads->next);

	                 /* locked_threads=cond->blocked_threads; */
	                 cond->blocked_threads = NULL;

	                 /* <CORE1>  The software interrupt 0 of core1 is used.   */
					 SRC_GPSR10.U=(1<<26)| /* SRC_GPSR10.B.SETR=1;  <Set request>                     */
				                  (1<<10)| /* SRC_GPSR10.B.SRE=1;   <Service Request Enable>          */
				                  (1<<11)| /* SRC_GPSR10.B.TOS=0;   <TOS=CPU1>                        */
				                  (8);     /* SRC_GPSR10.B.SRPN=8;  <Service Request Priority Number> */     
				                  
					 /* core_returnMutex(&core1_mutex); */
				   }
				   else if(cond_core_id==CORE2)
				   { 
	                 while(0!=core_getMutex(&core2_mutex)){};
					 
	        	     core2_os_blocked_threads=NULL;
					 
	        	     /* blocked_threads_prev_temp=cond->blocked_threads->prev; */
	        	     list_append(&core2_os_blocked_threads, cond->blocked_threads,
	                                   cond->blocked_threads->prev, cond->blocked_threads->next);

					 /* locked_threads=cond->blocked_threads; */
	                 cond->blocked_threads = NULL;

	                 /* <CORE2> The software interrupt 0 of core2 is used.   */
					 SRC_GPSR20.U=(1<<26)| /* SRC_GPSR20.B.SETR=1;  <Set request>                     */               
				                  (1<<10)| /* SRC_GPSR20.B.SRE=1;   <Service Request Enable>          */
				                  (2<<11)| /* SRC_GPSR20.B.TOS=2;   <TOS=CPU2>                        */
				                  (7);     /* SRC_GPSR20.B.SRPN=7;  <Service Request Priority Number> */
				                  
				     /* core_returnMutex(&core2_mutex); */
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
	return 0; /* Dummy to avoid warning */
} /* End of pthread_cond_broadcast function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> If the number of threads that are actived      */
/*              periodically is more than one,the API is used inside the    */
/*              tick interrupts of STM0,STM1 and STM2 to insert the threads */
/*              actived newly into the scheduling table. There must be only */
/*              one thread actived newly left and not be inserted into the  */
/*              scheduling table                                            */
/****************************************************************************/
inline void dispatch_signal_in_tick(pthread_t *blocked_threads_ptr, pthread_t last_thread) {

	pthread_t thread, tmp;
	os32_t i;

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
        __putbit(1,(os32_t*)&core0_os_pthread_runnable,i);
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
        __putbit(1,(os32_t*)&core1_os_pthread_runnable,i);
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
        __putbit(1,(os32_t*)&core2_os_pthread_runnable,i);
        if (thread == last_thread)break;
        thread = tmp;
       }
       *blocked_threads_ptr = tmp;
	 }
}/* End of dispatch_signal_in_tick functio */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE>  Os kernel logic that can be called by trap 6  */
/*              and software interrupts that are used for thread activation */
/*                                                                          */
/* OPTIONS:                                                                 */
/*    __syscallfunc(DISPATCH_WAIT)   os32_t dispatch_wait(void *, void *);     */
/*    <EVERY CORE> Make threads that have been actived be blocked           */
/*                                                                          */
/*    __syscallfunc(DISPATCH_SIGNAL) os32_t dispatch_signal(void *, void *);   */
/*    <EVERY CORE> Make threads that have been blocked be actived           */
/*                                                                          */
/*    __syscallfunc(DISPATCH_ONLY)   os32_t dispatch_only(void *, void *);     */
/*    <EVERY CORE> Only reschedule all threads that have been actived       */
/*    without changing the scheduling table                                 */
/****************************************************************************/
static void trapsystem(pthread_t *blocked_threads_ptr, pthread_t last_thread) {
    os32_t tin, i;
    pthread_t thread, tmp;

    __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); /* Put d15 in C variable tin */

    if(os_getCoreId()==CORE0)
	{
        core0_os_pthread_running->lcx = __mfcr(CPU_PCXI);
        i = core0_os_pthread_running->priority;
        assert(core0_os_pthread_runnable_threads[i] == core0_os_pthread_running);
        switch (tin) 
		{
          case DISPATCH_WAIT: 
             {
                list_delete_first(&core0_os_pthread_runnable_threads[i]);
                list_append(blocked_threads_ptr, core0_os_pthread_running, core0_os_pthread_running, NULL);
                __putbit(neza(core0_os_pthread_runnable_threads[i]),(os32_t*)&core0_os_pthread_runnable,i);
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
                     __putbit(1,(os32_t*)&core0_os_pthread_runnable,i);
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
		
		 /* <CORE0> Unlock core0_mutex */
		 core_returnMutex(&core0_mutex);
	}
	else if(os_getCoreId()==CORE1)
	{
        core1_os_pthread_running->lcx = __mfcr(CPU_PCXI);
        i = core1_os_pthread_running->priority;
        assert(core1_os_pthread_runnable_threads[i] == core1_os_pthread_running);
        switch (tin) 
		{
          case DISPATCH_WAIT: 
             {
                list_delete_first(&core1_os_pthread_runnable_threads[i]);
                list_append(blocked_threads_ptr, core1_os_pthread_running, core1_os_pthread_running, NULL);
                __putbit(neza(core1_os_pthread_runnable_threads[i]),(os32_t*)&core1_os_pthread_runnable,i);
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
                      __putbit(1,(os32_t*)&core1_os_pthread_runnable,i);
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
		
		 /* <CORE1> Unlock core1_mutex */
		 core_returnMutex(&core1_mutex);
	}
	else if(os_getCoreId()==CORE2)
	{
        core2_os_pthread_running->lcx = __mfcr(CPU_PCXI);
        i = core2_os_pthread_running->priority;
        assert(core2_os_pthread_runnable_threads[i] == core2_os_pthread_running);
        switch (tin) 
		{
          case DISPATCH_WAIT: 
             {
                list_delete_first(&core2_os_pthread_runnable_threads[i]);
                list_append(blocked_threads_ptr, core2_os_pthread_running, core2_os_pthread_running, NULL);
                __putbit(neza(core2_os_pthread_runnable_threads[i]),(os32_t*)&core2_os_pthread_runnable,i);
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
                      __putbit(1,(os32_t*)&core2_os_pthread_runnable,i);
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
		
		 /* <CORE2> Unlock core2_mutex */
		 core_returnMutex(&core2_mutex);		
	}
     pthread_start_np();
} /* End of trapsystem function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(schedule_in_tick) is used inside the   */
/*              tick interrupts of STM0,STM1 and STM2 to deal with periodic */
/*              thread scheduling events                                    */
/****************************************************************************/
inline void schedule_in_tick(void)
{
     pthread_cond_t  *cond;
	 pthread_cond_t  *cond_buffer[PTHREAD_COND_TIMEDWAIT_SIZE];
     osu32_t        index;
	 osu32_t        release_count = 0;
	 osu32_t        tempt_index;
	
	 if(os_getCoreId()==CORE0)
	 {  	
	    tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core0_os_pthread_time_waiting);
		if( tempt_index == 0) return;
		tempt_index = tempt_index - 1;
	    for(index = 0 ; index <= tempt_index ; index++)
	    {
		      if(stm_ticks[index] == core0_os_stm_tick_count)
			  {		
				cond_buffer[release_count] = stm_cond[index];
				stm_ticks[index]           = USHRT_MAX;                             // free place in array 
				__putbit(0,(os32_t*)&core0_os_pthread_time_waiting,index); 
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
				__putbit(0,(os32_t*)&core1_os_pthread_time_waiting,index); 
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
				__putbit(0,(os32_t*)&core2_os_pthread_time_waiting,index); 
				release_count++;
			  }
	    }
	 }

    /* <EVERY CORE> If more than one threads that haved been set to periodic */
	/* mode have reached the waiting time,the logic is entered in order to   */
	/* reschedule the threads                                                */
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
		
	   cond   =cond_buffer[0];  /* <EVERY CORE> Get the current condition */

	   /* <EVERY CORE> Setup parameter and jump to trapsystem */
	   __asm( " mov.aa a4,%0 \n"
	          " mov.aa a5,%1 \n"
	          " mov d15,%2   \n"
	          " jg trapsystem  "
	          ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
	 }
} /* End of schedule_in_tick function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(pthread_cond_timedwait_np) can be used */
/*              inside threads to let the current thread blocked in for     */
/*              reltime(unit ms).This is an OS API that is provided to os   */
/*              user                                                        */
/****************************************************************************/
os32_t pthread_cond_timedwait_np(osu16_t reltime) //!< [in] relative time are the relative time STM_TIM4 ticks.NOT PORTABLE.
{
	osu16_t new_tick_count;
    osu16_t set_count;
	osu32_t task_id = 0;
	pthread_cond_t *cond;
	
    assert(cppn()==0); /* CCPN must be 0, pthread_cond_timedwait_np cannot be called from ISR */

	if(os_getCoreId()==CORE0)
	{	  	
	  new_tick_count  = core0_os_stm_tick_count + 1;
	  set_count = ((osu16_t)(new_tick_count + reltime))%0xFFFF;  /* <CORE0> set_count ranges from 0 to 0xFFFE */

      /* <CORE0> Search the empty position. */
      while((stm_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  
	  /* <CORE0> There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;
 
      cond = &core0_os_cond[task_id];
	  __putbit(1,(os32_t*)&core0_os_pthread_time_waiting,task_id); /* <CORE0> mark current thread ready */
	  
      stm_ticks[task_id] = set_count;     /* <CORE0> Load the current tick set(lconfig 1.) */ 
      stm_cond[task_id] = cond;           /* <CORE0> Load the cond.(lconfig 2.) */            

      os32_t err = dispatch_wait(&cond->blocked_threads, NULL);
	}
	else if(os_getCoreId()==CORE1)
	{ 
	  new_tick_count = core1_os_stm_tick_count + 1;
	  set_count = ((osu16_t)(new_tick_count + reltime))%0xFFFF;  /* <CORE1> set_count ranges from 0 to 0xFFFE */

      /* <CORE1> Search the empty position. */
      while((core1_os_stm_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  
	  /* <CORE1> There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;

      cond = &core1_os_cond[task_id];
	  __putbit(1,(os32_t*)&core1_os_pthread_time_waiting,task_id); /* <CORE1> mark current thread ready */
	  
	  core1_os_stm_ticks[task_id] = set_count;  /* <CORE1> Load the current tick set(lconfig 1.) */    
      core1_os_stm_cond[task_id] = cond;        /* <CORE1> Load the cond.(lconfig 2.) */              
	
      os32_t err = dispatch_wait(&cond->blocked_threads, NULL);

	}
	else if(os_getCoreId()==CORE2)
	{
	  new_tick_count  = core2_os_stm_tick_count + 1;
	  set_count = ((osu16_t)(new_tick_count + reltime))%0xFFFF;  /* <CORE2> set_count ranges from 0 to 0xFFFE */

      /* <CORE2> Search the empty position. */
      while((core2_os_stm_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  
	  /* <CORE2> There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;

      cond = &core2_os_cond[task_id];
	  __putbit(1,(os32_t*)&core2_os_pthread_time_waiting,task_id); /* <CORE2> mark current thread ready */

	  core2_os_stm_ticks[task_id] = set_count;  /* <CORE2> Load the current tick set(lconfig 1.) */
      core2_os_stm_cond[task_id] = cond;        /* <CORE2> Load the cond.(lconfig 2.) */

      os32_t err = dispatch_wait(&cond->blocked_threads, NULL);
	}
    return 0;
} /* End of pthread_cond_timedwait_np function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_suspend_allthreads) can be used     */
/*              inside threads to suspend all that happend after the API is */
/*              called.This is an OS API that is provided to os user        */
/****************************************************************************/
void os_suspend_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */
   osu32_t current_cpu_id = os_getCoreId();

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
} /* End of os_suspend_allthreads function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_restore_allthreads) can be used     */
/*              inside threads to restore all threads that are suspended.   */
/*              After the API is called all thread that are suspended by    */
/*              os_restore_allthreads can be restore immediately This is    */
/*              an OS API that is provided to os user                       */
/****************************************************************************/
void os_restore_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */
   osu32_t current_cpu_id = os_getCoreId();

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
 
} /* End of os_restore_allthreads function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_dsable_allinterrupts) can be used   */
/*              inside threads to disable all interrupts.This is an OS API  */
/*              that is provided to os user                                 */
/****************************************************************************/
void os_dsable_allinterrupts(void)
{
   __enable();
} /* End of os_dsable_allinterrupts function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_enable_allinterrupt) can be used    */
/*              inside threads to enable all interrupts.This is an OS API   */
/*              that is provided to os user                                 */
/****************************************************************************/
void os_enable_allinterrupt(void)
{
  __disable();
  __nop();

} /* End of os_enable_allinterrupt function */

/****************************************************************************/
/* DESCRIPTION:  <CORE0> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(10) __vector_table(0) Ifx_STM0_Isr(void)
{  
   /* <CORE0> OS tick ranges from 0-0xffff */
   core0_os_stm_tick_count=(core0_os_stm_tick_count+1)%0xFFFF;  

   /* <CORE0> Update the os tick of core0 */
   update_stm0_ticks(); 

   /* <CORE0> Call the scheduler part in the interrupt to deal with the */
   /* periodic thread activation of core0 */   
   schedule_in_tick();
} /* End of Ifx_STM0_Isr intterrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE1> software interrupt 1 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(11) __vector_table(0) Ifx_STM1_Isr(void)
{ 
   /* <CORE1> OS tick ranges from 0-0xffff */
   core1_os_stm_tick_count=(core1_os_stm_tick_count+1)%0xFFFF; 

   /* <CORE1> Update the os tick of core1 */
   update_stm1_ticks();  

   /* <CORE1> Call the scheduler part in the interrupt to deal with the */
   /* periodic thread activation of core1 */   
   schedule_in_tick();

} /* End of Ifx_STM1_Isr intterrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE2> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(12) __vector_table(0) Ifx_STM2_Isr(void)
{  
   /* <CORE2> OS tick ranges from 0-0xffff */
   core2_os_stm_tick_count=(core2_os_stm_tick_count+1)%0xFFFF; 

   /* <CORE2> Update the os tick of core2 */
   update_stm2_ticks(); 

   /* <CORE2> Call the scheduler part in the interrupt to deal with the */
   /* periodic thread activation of core2 */
   schedule_in_tick();

} /* End of Ifx_STM2_Isr intterrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE0> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(9) __vector_table(0) CPU0_SOFT0_Isr(void)
{
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&core0_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
} /* End of CPU0_SOFT0_Isr interrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE1> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(8) __vector_table(0) CPU1_SOFT0_Isr(void)
{
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&core1_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
} /* End of CPU1_SOFT0_Isr interrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE2> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(7) __vector_table(0) CPU2_SOFT0_Isr(void)
{
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&core2_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
} /* End of CPU2_SOFT0_Isr interrupt */

/****************************************************************************/
/* DESCRIPTION: STM0 compare1 interrupt event                               */
/****************************************************************************/
void __interrupt(21) __vector_table(0) Ifx_STM0_compare1_Isr(void)
{ 
	 /* Unit:ms ,the max is 0xFFFFFFFF/100000=42949ms(42.949s */
 	update_stm0_compare1_ticks(1000);
} /* End of Ifx_STM0_compare1_Isr interrupt */

/****************************************************************************/
/* DESCRIPTION: <CORE0>  Trap vector table entry to trap class 6 handler    */
/****************************************************************************/
void IfxCpu_Trap_systemCall_Cpu0(osu32_t tin)
{
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");
} /* End of IfxCpu_Trap_systemCall_Cpu0 function */

/****************************************************************************/
/* DESCRIPTION: <CORE1>  Trap vector table entry to trap class 6 handler    */
/****************************************************************************/
void IfxCpu_Trap_systemCall_Cpu1(osu32_t tin)
{
	/* Add the kernel of OS */
	/* Kernel begins        */
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");
} /* End of IfxCpu_Trap_systemCall_Cpu1 function */

/****************************************************************************/
/* DESCRIPTION: <CORE2>  Trap vector table entry to trap class 6 handler    */
/****************************************************************************/
void IfxCpu_Trap_systemCall_Cpu2(osu32_t tin)
{
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");
} /* End of IfxCpu_Trap_systemCall_Cpu2 function */



