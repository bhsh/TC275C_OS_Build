/*
 * os_kernel.h
 *
 *  Created on: Aug 26, 2015
 *      Author: tz68d9
 */

#ifndef OS_KERNEL_H_
#define OS_KERNEL_H_

#include "os_kernel_cfg.h"

#define PTHREAD_COND_INITIALIZER {false,NULL}
#define PTHREAD_MUTEX_INITIALIZER {false,NULL}

#define PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) static struct { \
    pthread_t next,prev;\
    uint32_t lcx; \
    uint32_t priority; \
    uint32_t policy; \
    uint32_t *arg; \
    uint32_t stack[_stacksize]; \
    } _##_name = {0,(pthread_t)&_##_name,0,_priority,_policy,NULL,{_stacksize+1}};\
    \
    pthread_t _name = (pthread_t)&_##_name;

//! Scheduling policy
enum sched_policy_e {
    SCHED_FIFO, SCHED_RR, SCHED_OTHER
};

//! User mode definition
enum user_e {
    USER0, USER1, SUPER
};

typedef enum allthreads_status {	
    ALLTHREADS_WORKING, 
	ALLTHREADS_SUSPENDED
	
}allthreads_status_t;
//! core definition
typedef enum  {

	CORE0,
	CORE1, 
	CORE2,
	MAX_CORE_NUM
}core_id_e;

//! Call depth definition
enum call_depth_overflow_e {
    CALL_DEPTH_OVERFLOW_AT_64 = 0,
    CALL_DEPTH_OVERFLOW_AT_32 = 0x40,
    CALL_DEPTH_OVERFLOW_AT_16 = 0x60,
    CALL_DEPTH_OVERFLOW_AT_8 = 0x70,
    CALL_DEPTH_OVERFLOW_AT_4 = 0x78,
    CALL_DEPTH_OVERFLOW_AT_2 = 0x7C,
    CALL_DEPTH_TRAP_EVERY_CALL = 0x7E,
    CALL_DEPTH_OVERFLOW_DISABLED = 0x7F,
};

//! Description of the thread attributes.
typedef struct {
    enum user_e mode;//!< thread mode must be 0 user_e
    uint32_t call_depth_overflow;//!< call depth overflow
} pthread_attr_t;

//! Description the thread record.
typedef struct pthread_s {
    struct pthread_s *next; //!< Next thread pointer
    struct pthread_s *prev; //!< Previous thread pointer
    uint32_t lcx; //!< Lower context pointer
    uint32_t priority; //!< Thread priority must be 0 to \ref PTHREAD_PRIO_MAX
    uint32_t policy; //!< Policy is one of sched_policy_e
    uint32_t *arg; //!< Container that saves the argument passed to the thread function
    uint32_t stack[1]; //!< Stack. The size 1 is only a dummy. Memory allocation is done via \ref PTHREAD_CONTROL_BLOCK
}*pthread_t;

//! Description of a thread mutex.
typedef struct {
    uint32_t lock;//!< mutex lock status is one of <true | false>
    pthread_t owner; //!< owner thread
    pthread_t blocked_threads; //!< list threads waiting for mutex
} pthread_mutex_t;

typedef struct {
	uint32_t task_id;//!< mutex lock status is one of <true | false> 
    uint32_t type;//!< mutex lock status is one of <true | false>
    uint32_t period;//!< mutex lock status is one of <true | false> 
    uint32_t actived_task_id;
    
} pthread_config_t;

//! Description of a thread conditional variable.
typedef struct {
    const uint32_t core_id;//!< cond status is one of <true | false>
    uint32_t  multi_semaphore;
    pthread_t blocked_threads; //!< list threads waiting for condition
} pthread_cond_t;

typedef void (*task_ptr_t)(pthread_config_t * const pthread_config,uint32_t current_core_id);

#define CORE0_PTHREAD_COND_INITIALIZER {CORE0,0,NULL}
#define CORE1_PTHREAD_COND_INITIALIZER {CORE1,0,NULL}
#define CORE2_PTHREAD_COND_INITIALIZER {CORE2,0,NULL}

int pthread_create_np(pthread_t, const pthread_attr_t *, void(*)(void *,task_ptr_t),
        void *,task_ptr_t);
void start_core0_os(void);
void start_core1_os(void);
void start_core2_os(void);

inline uint32_t os_getCoreId(void)
{
   uint32_t core_id;

   core_id=__mfcr(CPU_CORE_ID);
   
   return (core_id&0x7);
}

//! Start threads
inline void pthread_start_np(void) {
    extern  uint32_t  core0_os_pthread_runnable;
    extern  pthread_t core0_os_pthread_running;
    extern  pthread_t core0_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
	extern  uint32_t  core1_os_pthread_runnable;
    extern  pthread_t core1_os_pthread_running;
    extern  pthread_t core1_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
	extern  uint32_t  core2_os_pthread_runnable;
    extern  pthread_t core2_os_pthread_running;
    extern  pthread_t core2_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
	extern  allthreads_status_t core0_allthreads_status;
	extern  allthreads_status_t core1_allthreads_status;
	extern  allthreads_status_t core2_allthreads_status;

    pthread_t thread = (void*)0;
 
	if(os_getCoreId()==CORE0)
	{  
	      assert(core0_os_pthread_runnable != 0);
		  if(core0_allthreads_status == ALLTHREADS_WORKING)
		  {
			      thread = core0_os_pthread_runnable_threads[31 - __clz(core0_os_pthread_runnable)]; //  get ready thread with highest priority ready			    
			      core0_os_pthread_running = thread;
		  }
		  else if(core0_allthreads_status == ALLTHREADS_SUSPENDED)
		  {
                  /* In order to keep core0_os_pthread_running unchanged */
				  thread = core0_os_pthread_running;
		  }
	}
    else if(os_getCoreId()==CORE1)
	{
	      assert(core1_os_pthread_runnable != 0);
		  if(core1_allthreads_status == ALLTHREADS_WORKING)
		  {
			      thread = core1_os_pthread_runnable_threads[31 - __clz(core1_os_pthread_runnable)]; //  get ready thread with highest priority ready
				  core1_os_pthread_running = thread;
		  }
		  else if(core1_allthreads_status == ALLTHREADS_SUSPENDED)
		  {
                  /* In order to keep core1_os_pthread_running unchanged */
				  thread = core1_os_pthread_running;
		  }
	}
	else if(os_getCoreId()==CORE2)
	{
	      assert(core2_os_pthread_runnable != 0);
		  if(core2_allthreads_status == ALLTHREADS_WORKING)
		  {
			      thread = core2_os_pthread_runnable_threads[31 - __clz(core2_os_pthread_runnable)]; //  get ready thread with highest priority ready
                  core2_os_pthread_running = thread;//
	      } 
		  else if(core2_allthreads_status == ALLTHREADS_SUSPENDED)
		  {
                  /* Do nothing in order to keep core2_os_pthread_running unchanged */
				  thread = core2_os_pthread_running;
		  }
	}
	assert(thread);
    assert(thread->lcx);
    __mtcr(CPU_PSW, 0x00000980);        /* clear PSW.IS */
    __dsync();
    __mtcr(CPU_PCXI,  thread->lcx);
    __rslcx();         // restore the lower context
    __asm(" mov d2,#0"); // the return value is 2
    __asm(" rfe");       // restore the upper context
}

//!  TriCore context structure
typedef union {
    struct {
        uint32_t pcxi; //!< upper context PCXI
        uint32_t psw; //!< upper context PSW
        void * a10; //!< upper context A10 (SP)
        void * a11; //!< upper context A11 (RA)
        uint32_t d8; //!< upper context D8
        uint32_t d9; //!< upper context D9
        uint32_t d10; //!< upper context D10
        uint32_t d11; //!< upper context D11
        uint32_t a12; //!< upper context A12
        uint32_t a13; //!< upper context A13
        uint32_t a14; //!< upper context A14
        uint32_t a15; //!< upper context A15
        uint32_t d12; //!< upper context D12
        uint32_t d13; //!< upper context D13
        uint32_t d14; //!< upper context D14
        uint32_t d15; //!< upper context D15
    } u; //!< upper context
    struct {
        uint32_t pcxi; //!< lower context PCXI
        void (*pc)(void*,task_ptr_t); //!< lower context saved PC
        uint32_t a2; //!< lower context A2
        uint32_t a3; //!< lower context A3
        uint32_t d0; //!< lower context D0
        uint32_t d1; //!< lower context D1
        uint32_t d2; //!< lower context D2
        uint32_t d3; //!< lower context D3
        void * a4; //!< lower context A4
        void * a5; //!< lower context A5
        uint32_t a6; //!< lower context A6
        uint32_t a7; //!< lower context A7
        uint32_t d4; //!< lower context D4
        uint32_t d5; //!< lower context D5
        uint32_t d6; //!< lower context D6
        uint32_t d7; //!< lower context D7
    } l; //!< lower context
} context_t;

inline context_t *cx_to_addr(uint32_t cx) {
    uint32_t seg_nr = __extru(cx, 16, 4);
    return (context_t *) __insert(seg_nr << 28, cx, 6, 16);
}

#define __fCPU 200
inline void delay_ms(uint32_t _milliseconds) {
    __asm( "  mov.u d15,#1000 \n"
            "  mov.a a15,d15  \n"
            "  nop16          \n"
            "  nop16          \n"
            "  loop a15,*-4    \n"
            "  loop %0,*-8   \n"
            ::"a"((_milliseconds*__fCPU)/2): "a15","d15");
}

//! Insert NEZ.A instruction
inline uint32_t neza(void *p) {
    int ret;
    __asm("nez.a %0,%1":"=d"(ret):"a"(p));
    return ret;
}

/* The functions are called by app */
int pthread_mutex_lock(pthread_mutex_t *mutex) ;//!<  [in] mutex pointer
int pthread_mutex_unlock(pthread_mutex_t *mutex) ;
//! Wait on a condition
int pthread_cond_wait(pthread_cond_t *cond);//!< [in] condition pointer
int pthread_cond_broadcast(pthread_cond_t *cond); //!< [in] condition pointer
//! Wait on a condition
//int pthread_other_core_cond_broadcast(pthread_cond_t *cond,core_id_e actived_core_id); //!< [in] condition pointer
int pthread_cond_timedwait_np(uint16_t reltime); //!< [in] relative time are the relative time STM_TIM4 ticks.NOT PORTABLE.


#endif /* OS_KERNEL_H_ */
