/*
 * os_kernel.c
 *
 *  Created on: Aug 26, 2015
 *      Author: tz68d9
 */


#include "os_kernel.h"


/* define the system call that is the 6th trap of CPU */
//__syscallfunc(1) int syscall_a( int, int );
//__syscallfunc(2) int syscall_b( int, int );
//__syscallfunc(3) int syscall_c( int, int );

//! \cond IGNORE
#define DISPATCH_WAIT     2
#define DISPATCH_SIGNAL   3
__syscallfunc(DISPATCH_WAIT)   int dispatch_wait(void *, void *);
__syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
//! \endcond

 uint32_t pthread_runnable;
 pthread_t pthread_running;
 pthread_t pthread_runnable_threads[PTHREAD_PRIO_MAX];

#define NULL (void*)0
static void list_append(pthread_t *head, pthread_t elem, pthread_t list_prev,
        pthread_t elem_next) {
   // assert(head != NULL);
   // assert(elem != NULL);

    pthread_t list = *head;
    if (list == NULL) {
        elem->next = elem;
        elem->prev = elem;
        *head = elem;
    } else {
        elem->next = elem_next;
        elem->prev = list->prev;
        list->prev->next = elem;
        list->prev = list_prev;
    }
}

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
pthread_t thread_1;
pthread_t thread_2;
context_t *cx_test;
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
#if 0
    if((uint32_t)(arg)==1)
    {
    	thread_1=thread;
    }
    if((uint32_t)(arg)==2)
    {
    	thread_2=thread;
    }
    uint32_t i = thread->priority;
    pthread_runnable_threads[i]=thread_2;
#endif


    uint32_t i = thread->priority;
    list_append(&pthread_runnable_threads[i], thread, thread,
            pthread_runnable_threads[i]);
    __putbit(1,(int*)&pthread_runnable,i); // mark current thread ready

    return 0;
}


int pthread_mutex_lock(pthread_mutex_t *mutex) //!<  [in] mutex pointer
{
    assert(cppn()==0); // CCPN must be 0, function cannot be called from ISR
    assert (mutex != NULL); // errno = EINVAL, return -1

    if (mutex->owner == pthread_running) // errno = EDEADLK
        return -1;

    while (true == __swap(&mutex->lock, true)) { // swap out if already looked by another thread
        dispatch_wait(&mutex->blocked_threads, NULL); // block this thread
    }
    mutex->owner = pthread_running;
    return 0;
}

//! Unlock a mutex
int pthread_mutex_unlock(pthread_mutex_t *mutex) //!<  [in] mutex pointer
{
    assert(cppn()==0); // CCPN must be 0, function cannot be called from ISR
    assert (mutex != NULL); // errno = EINVAL, return -1

    if (mutex->owner != pthread_running) // errno = EPERM
        return -1;

    pthread_t threads = mutex->blocked_threads;
    mutex->owner = NULL;
    mutex->lock = false;
    mutex->blocked_threads = NULL;
    if (threads != NULL)
        dispatch_signal(&threads, NULL);
    return 0;
}

//! Wait on a condition
int pthread_cond_wait(pthread_cond_t *cond,//!< [in] condition pointer
        pthread_mutex_t *mutex) //!< [in] mutex pointer
{
    assert(cppn()==0); // CCPN must be 0, pthread_create cannot be called from ISR
    assert(cond != NULL); // errno = EINVAL
    assert(mutex != NULL); // errno = EINVAL

    if (true != __swap(&mutex->lock, false)) // the calling thread must have mutex locked
        return -1; // errno = ENOTLOCKED

    dispatch_wait(&cond->blocked_threads, NULL);// add this thread to the list of blocked threads by this cond
    mutex->lock = true;
    mutex->owner = pthread_running;
    return 0;
}

//! Broadcast a condition.
int pthread_cond_broadcast(pthread_cond_t *cond) //!< [in] condition pointer
{
    assert(cond!=NULL);
    if (cond->blocked_threads != NULL) {
        if (0 == cppn()) { // _pthread_running on CCPN=0
            dispatch_signal(&cond->blocked_threads, cond->blocked_threads->prev);// swap in with mutex unlocked

        } else {
#if 0
            list_append(&blocked_threads, cond->blocked_threads,
                    cond->blocked_threads->prev, cond->blocked_threads->next);
            cond->blocked_threads = NULL;
            CPU_SRC0.U = 1 << 15 // Set request
                    | 1 << 12 // Service Request Enable
                    | 0 << 10 // TOS=CPU
                    | 1; //Service Request Priority Number
#endif
        }
    }
    return 0;// dummy to avoid warning
}

void trap6_call(void) {
#if 0
    pthread_t thread;
    pthread_running->lcx = __mfcr(CPU_PCXI);
    thread = pthread_running->next; // get next thread with same priority
    pthread_runnable_threads[thread->priority] = thread;

    pthread_running = thread;
    __dsync(); // required before PCXI manipulation (see RTOS porting guide)
    __mtcr(CPU_PCXI, thread->lcx);
    __asm("ji a11");
#endif
}

void __trap( 6 ) trap6( int a, int b ) // trap class 6 handler
{
   // int tin;
   // __asm("mov %0,d15 \n"
   // 	  "svlcx        ": "=d"(tin)); // put d15 in C variable tin

      __asm(  " svlcx        \n"
              " jla trap6_call \n"
    		  " rslcx"::"a"(pthread_running->next));

   /* switch( tin )
    {
    case 1:
         a += b;
         break;
    case 2:
         a -= b;
         break;
    case 3:
         break;
    default:
         break;
    } */

    //pthread_start_np();
}
/***********************************************************************************
 * function name:
 *                main_call_trap6_interface
 * return type:
 *                int
 *
 ***********************************************************************************/

int x_test_buffer;
int call_trap6_test_counter;


void call_trap6_interface(void)
{
	//syscall_a(1,2);  // causes a trap class 6 with TIN = 1
	//x = syscall_b(4,3); // causes a trap class 6 with TIN = 2

	//x_test_buffer=x;

	call_trap6_test_counter++;

}

/*! Trap class 6 handler (System trap) called by
 \code __syscallfunc(DISPATCH_WAIT)  int dispatch_wait(void *, void *);
 \code __syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
 */
static void trapsystem(pthread_t *blocked_threads_ptr, pthread_t last_thread) {
    int tin, i;
    pthread_t thread, tmp;

    __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); // put d15 in C variable tin

    pthread_running->lcx = __mfcr(CPU_PCXI);
    i = pthread_running->priority;
    assert(pthread_runnable_threads[i] == pthread_running);
    switch (tin) {
    case DISPATCH_WAIT: // _swap_out _pthread_running
        list_delete_first(&pthread_runnable_threads[i]);
        list_append(blocked_threads_ptr, pthread_running, pthread_running, NULL);
        __putbit(neza(pthread_runnable_threads[i]),(int*)&pthread_runnable,i);
        break;
    case DISPATCH_SIGNAL:
        tmp = NULL;
        assert(blocked_threads_ptr);
        thread = *blocked_threads_ptr;
        while (thread != NULL) {
            tmp = thread->next;
            i = thread->priority;
            list_append(&pthread_runnable_threads[i], thread, thread,
                    pthread_runnable_threads[i]);
            __putbit(1,(int*)&pthread_runnable,i);
            if (thread == last_thread)
                break;
            thread = tmp;
        }
        *blocked_threads_ptr = tmp;
        break;
    default:
        break;
    }
    pthread_start_np();
}
//! Trap vector table entry to trap class 6 handler enables interrupts
#if 0
void __trap_fast(6) trap6(void) {
    __asm(" mtcr #ICR,%0 \n"
            " isync      \n"
            " jg trapsystem"
            ::"d"(1 << 8 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");//
}
#endif

uint32_t core0_trap_count_test;
/* The trap is used for the OS of core0 */

void trap_test(int *b,int *c)
{
    int tin;

    __asm(" mov %0,d15 \n"
            : "=d"(tin)); // put d15 in C variable tin
    switch(tin)
    {
    case 1:
    	   *b=10;
    	   *c=11;
    	    break;
    case 2:
 	       *b=12;
 	       *c=13;
 	       break;
    case 3:
 	       *b=14;
 	       *c=15;
 	       break;
    default:
           break;
    }
    __asm(  " rfe");
}
//void IfxCpu_Trap_systemCall_Cpu0(uint32_t tin)
void IfxCpu_Trap_systemCall_Cpu0(uint32_t tin)
{
    //trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    //IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK(trapWatch);
	

	/* Add the kernel of OS */
	/* Kernel begins        */
#if 0
	core0_trap_count_test++;
	/* Kernel ends          */	
    __asm(  " svlcx        \n"
            " jla trap6_call \n"
  		    " rslcx"::"a"(trap6_call));
    __asm(  " rfe");
#endif

    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg trapsystem     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(trapsystem):"a4","a5","d15");//
    //__asm(  " rfe");
}
/***********************************************************************************
 * function name:
 *                switch_context
 * return type:
 *                int
 *
 ***********************************************************************************/
int test1=0;
int test2=0;
void switch_context(void)
{
	//syscall_c(1,2);  // causes a trap class 6 with TIN = 1
	dispatch_wait(&test1,&test2);
}
