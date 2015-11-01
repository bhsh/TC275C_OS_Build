/****************************************************************************/
/* FILE NAME:    os_kernel.h                                                */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes type definitions for os kernel and     */
/*               function statements for os user                            */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_KERNEL_H_
#define OS_KERNEL_H_

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel_cfg.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define __fCPU 200

#define CORE0_PTHREAD_TIMEWAIT_INITIALIZER {NULL}
#define CORE1_PTHREAD_TIMEWAIT_INITIALIZER {NULL}
#define CORE2_PTHREAD_TIMEWAIT_INITIALIZER {NULL}

#define assert(_expr)  \
       ((void) (!(_expr) ? __debug(): (void) 0))
#define PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) static struct { \
    pthread_t next,prev;\
    osu32_t lcx; \
    osu32_t priority; \
    osu32_t policy; \
    osu32_t *arg; \
    osu32_t stack[_stacksize]; \
    } _##_name = {0,(pthread_t)&_##_name,0,_priority,_policy,NULL,{_stacksize+1}};\
    \
    pthread_t _name = (pthread_t)&_##_name;

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum  {  /* <enum><sched_policy_t> Scheduling policy definition */
    SCHED_FIFO, 
	SCHED_RR, 
	SCHED_OTHER
}sched_policy_t; 

typedef enum  { /* <enum><user_t> User mode definition */
    USER0,
    USER1,
    SUPER
}user_t;

typedef enum  { /* <enum><allthreads_status_t> Thread status definition */
	
    ALLTHREADS_WORKING, 
	ALLTHREADS_SUSPENDED
	
}pthreads_status_t;

typedef enum  {  /* <enum><call_depth_overflow_t> Call depth definition */
    CALL_DEPTH_OVERFLOW_AT_64 = 0,
    CALL_DEPTH_OVERFLOW_AT_32 = 0x40,
    CALL_DEPTH_OVERFLOW_AT_16 = 0x60,
    CALL_DEPTH_OVERFLOW_AT_8 = 0x70,
    CALL_DEPTH_OVERFLOW_AT_4 = 0x78,
    CALL_DEPTH_OVERFLOW_AT_2 = 0x7C,
    CALL_DEPTH_TRAP_EVERY_CALL = 0x7E,
    CALL_DEPTH_OVERFLOW_DISABLED = 0x7F,
} call_depth_overflow_t;

typedef struct { /* <struct><pthread_attr_t>  Description of the thread attributes */
    user_t mode;/* thread mode must be 0 user_t */
    osu32_t call_depth_overflow;/* call depth overflow */
} pthread_attr_t;

typedef struct pthread_s { /* <struct><pthread_t> Describe the thread record */
    struct pthread_s *next; /* Next thread pointer */
    struct pthread_s *prev; /* Previous thread pointer */
    osu32_t lcx; /* Lower context pointer */
    osu32_t priority; /* Thread priority must be 0 to \ref PTHREAD_PRIO_MAX */
    osu32_t policy; /* Policy is one of sched_policy_t */
    osu32_t *arg; /* Container that saves the argument passed to the thread function */
    osu32_t stack[1]; /* Stack. The size 1 is only a dummy. Memory allocation is done via \ref PTHREAD_CONTROL_BLOCK */
}*pthread_t;

typedef struct { /* <struct><pthread_cond_t> Describe the thread condition */
    const osu32_t core_id; /* The core id of the thread actived */
    osu32_t       semaphore; /* Semaphore is used for many activations at one moment */
	const osu32_t thread_id; /* thread_id */
    pthread_t     blocked_threads; /* list threads waiting for condition */
} pthread_cond_t;

typedef struct { /* <struct><pthread_timewait_t> Describe the thread timewait */
    pthread_t     blocked_threads; /* list threads waiting for timewait */
} pthread_timewait_t;

typedef struct { /* <struct><pthread_mutex_t> Description of a thread mutex */
    osu32_t   lock;/* mutex lock status is one of <true | false> */
    pthread_t owner; /* < owner thread */
    pthread_t blocked_threads; /* list threads waiting for mutex */
} pthread_mutex_t;

typedef union { /* <union><context_t> TriCore context structure */
    struct { /* <struct><u> Upper context */
        osu32_t pcxi;/* Upper context PCXI*/
        osu32_t psw; /* Upper context PSW */
        void * a10;  /* Upper context A10 (SP) */
        void * a11;  /* Upper context A11 (RA) */
        osu32_t d8;  /* Upper context D8  */
        osu32_t d9;  /* Upper context D9  */
        osu32_t d10; /* Upper context D10 */
        osu32_t d11; /* Upper context D11 */
        osu32_t a12; /* Upper context A12 */
        osu32_t a13; /* Upper context A13 */
        osu32_t a14; /* Upper context A14 */
        osu32_t a15; /* Upper context A15 */
        osu32_t d12; /* Upper context D12 */
        osu32_t d13; /* Upper context D13 */
        osu32_t d14; /* Upper context D14 */
        osu32_t d15; /* Upper context D15 */
    } u; 
    struct {  /* <struct><l> Lower context */
        osu32_t pcxi; /* lower context PCXI */
        void (*pc)(void*,task_ptr_t); /* lower context saved PC */
        osu32_t a2; /* Lower context A2 */
        osu32_t a3; /* Lower context A3 */
        osu32_t d0; /* Lower context D0 */
        osu32_t d1; /* Lower context D1 */
        osu32_t d2; /* Lower context D2 */
        osu32_t d3; /* Lower context D3 */
        void * a4;  /* Lower context A4 */
        void * a5;  /* Lower context A5 */
        osu32_t a6; /* Lower context A6 */
        osu32_t a7; /* Lower context A7 */
        osu32_t d4; /* Lower context D4 */
        osu32_t d5; /* Lower context D5 */
        osu32_t d6; /* Lower context D6 */
        osu32_t d7; /* Lower context D7 */
    } l; 
} context_t;


/****************************************************************************/
/* Inline Function Definitions                                              */
/****************************************************************************/

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Return current process priority number         */
/****************************************************************************/
OS_INLINE osu32_t cppn(void) {
    return __extru(__mfcr(CPU_ICR), 0, 8);
} /* End of cppn function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Get the core id                                */
/****************************************************************************/
OS_INLINE osu32_t os_getCoreId(void)
{
   osu32_t core_id;
   core_id=__mfcr(CPU_CORE_ID);
   return (core_id&0x7);
} /* End of os_getCoreId function */
 
/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Start threads                                  */
/****************************************************************************/
OS_INLINE void pthread_start_np(void) {
    extern  osu32_t           core0_os_pthread_runnable;
	extern  osu32_t           core1_os_pthread_runnable;
	extern  osu32_t           core2_os_pthread_runnable;
    extern  pthread_t         core0_os_pthread_running;
    extern  pthread_t         core1_os_pthread_running;
    extern  pthread_t         core2_os_pthread_running;
    extern  pthread_t         core0_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
    extern  pthread_t         core1_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
    extern  pthread_t         core2_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
	extern  pthreads_status_t core0_os_pthreads_status;
	extern  pthreads_status_t core1_os_pthreads_status;
	extern  pthreads_status_t core2_os_pthreads_status;

    pthread_t thread = (void*)0;
	osu32_t   current_core_id = os_getCoreId();

	if(current_core_id == CORE0_ID)
	{  
      assert(core0_os_pthread_runnable != 0);
	  if(core0_os_pthreads_status == ALLTHREADS_WORKING)
	  {       
         /* <CORE0> Get ready thread with highest priority ready */  
         thread = core0_os_pthread_runnable_threads[31 - __clz(core0_os_pthread_runnable)]; 			    
         core0_os_pthread_running = thread;
	  }
	  else if(core0_os_pthreads_status == ALLTHREADS_SUSPENDED)
	  {
         /* <CORE0> In order to keep core0_os_pthread_running unchanged */
	     thread = core0_os_pthread_running;
	  }
	}
    else if(current_core_id == CORE1_ID)
	{
      assert(core1_os_pthread_runnable != 0);
	  if(core1_os_pthreads_status == ALLTHREADS_WORKING)
	  {     
	     /* <CORE1> Get ready thread with highest priority ready */  
         thread = core1_os_pthread_runnable_threads[31 - __clz(core1_os_pthread_runnable)];
	     core1_os_pthread_running = thread;
	  }
	  else if(core1_os_pthreads_status == ALLTHREADS_SUSPENDED)
	  {
         /* <CORE1> In order to keep core1_os_pthread_running unchanged */
	     thread = core1_os_pthread_running;
	  }
	}
	else if(current_core_id == CORE2_ID)
	{
      assert(core2_os_pthread_runnable != 0);
	  if(core2_os_pthreads_status == ALLTHREADS_WORKING)
	  {       
	     /* <CORE2> Get ready thread with highest priority ready */  
         thread = core2_os_pthread_runnable_threads[31 - __clz(core2_os_pthread_runnable)]; 
         core2_os_pthread_running = thread;
      } 
	  else if(core2_os_pthreads_status == ALLTHREADS_SUSPENDED)
	  {
         /* <CORE2> Do nothing in order to keep core2_os_pthread_running unchanged */
	     thread = core2_os_pthread_running;
	  }
	}
	assert(thread);
    assert(thread->lcx);
    __mtcr(CPU_PSW, 0x00000980);   /* <EVERY CORE> Clear PSW.IS */
    __dsync();
    __mtcr(CPU_PCXI,  thread->lcx);
    __rslcx();           /* <EVERY CORE> Restore the lower context */
    __asm(" mov d2,#0"); /* <EVERY CORE> The return value is 0     */
    __asm(" rfe");       /* <EVERY CORE>restore the upper context  */
} /* End of pthread_start_np function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Transfer address from cx mode to physical mode */
/****************************************************************************/
OS_INLINE context_t *cx_to_addr(osu32_t cx)
{
    osu32_t seg_nr = __extru(cx, 16, 4);
    return (context_t *) __insert(seg_nr << 28, cx, 6, 16);
} /* End of cx_to_addr function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Delay                                          */
/****************************************************************************/
OS_INLINE void delay_ms(osu32_t _milliseconds) {
    __asm( "  mov.u d15,#1000 \n"
            "  mov.a a15,d15  \n"
            "  nop16          \n"
            "  nop16          \n"
            "  loop a15,*-4    \n"
            "  loop %0,*-8   \n"
            ::"a"((_milliseconds*__fCPU)/2): "a15","d15");
}

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Insert NEZ.A instruction                       */
/****************************************************************************/
OS_INLINE osu32_t neza(void *p)
{
    os32_t ret;
    __asm("nez.a %0,%1":"=d"(ret):"a"(p));
    return ret;
} /* End of neza */
 
/****************************************************************************/
/* Function Prototype Definitions(The functions are called by threads)      */
/****************************************************************************/
void    start_core0_os(void);
void    start_core1_os(void);
void    start_core2_os(void);
os32_t  pthread_create_np(pthread_t, const pthread_attr_t *, void(*)(void *,task_ptr_t),void *,task_ptr_t);
os32_t  pthread_mutex_lock(pthread_mutex_t *mutex); /* <*mutex> Mutex pointer*/
os32_t  pthread_mutex_unlock(pthread_mutex_t *mutex); /* <*mutex> Mutex pointer*/
os32_t  pthread_cond_wait(pthread_cond_t *cond); /* <*cond> Condition pointer*/
os32_t  pthread_cond_broadcast(pthread_cond_t *cond); /* <*cond> Condition pointer*/
os32_t  pthread_cond_timedwait_np(osu16_t reltime); /* <reltime> Waiting time ,unit:ms */
void    pthread_enable_allinterrupt(void);
void    pthread_disable_allinterrupts(void);
void    pthread_suspend_allthreads(void);
void    pthread_restore_allthreads(void);
osu16_t pthread_obtain_os_tick(os32_t core_id);

#include "low_driver_port.h"
#include "os_mapping.h"

#endif /* OS_KERNEL_H_ */
