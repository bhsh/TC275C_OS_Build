/*
 * os_kernel.c
 *
 *  Created on: Aug 26, 2015
 *      Author: tz68d9
 */


#include "os_kernel.h"


/* define the system call that is the 6th trap of CPU */
__syscallfunc(1) int syscall_a( int, int );
__syscallfunc(2) int syscall_b( int, int );
__syscallfunc(3) int syscall_c( int, int );


//! Bit number is index into pthread_runnable_threads.
 uint32_t pthread_runnable;
//! Currently running thread
 pthread_t pthread_running;
//! Array of linked lists which holds runnable threads
 pthread_t pthread_runnable_threads[PTHREAD_PRIO_MAX];

#define NULL (void*)0
static void list_append(pthread_t *head, pthread_t elem, pthread_t list_prev,
        pthread_t elem_next) {
   // assert(head != NULL);
   // assert(elem != NULL);

    pthread_t list = *head;
    if (list == NULL) {
        elem->next = elem_next;
        elem->prev = elem;
        *head = elem;
    } else {
        elem->next = elem_next;
        elem->prev = list->prev;
        list->prev->next = elem;
        list->prev = list_prev;
    }
}

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

    cx_test=cx;

    uint32_t i = thread->priority;
    list_append(&pthread_runnable_threads[i], thread, thread,
            pthread_runnable_threads[i]);
    __putbit(1,(int*)&pthread_runnable,i); // mark current thread ready

    return 0;
}

void trap6_call(void) {
    pthread_t thread;
    pthread_running->lcx = __mfcr(CPU_PCXI);
    thread = pthread_running->next; // get next thread with same priority
    pthread_runnable_threads[thread->priority] = thread;

    pthread_running = thread;
    __dsync(); // required before PCXI manipulation (see RTOS porting guide)
    __mtcr(CPU_PCXI, thread->lcx);
    __asm("ji a11");
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

/***********************************************************************************
 * function name:
 *                switch_context
 * return type:
 *                int
 *
 ***********************************************************************************/
void switch_context(void)
{
	syscall_c(1,2);  // causes a trap class 6 with TIN = 1
}
