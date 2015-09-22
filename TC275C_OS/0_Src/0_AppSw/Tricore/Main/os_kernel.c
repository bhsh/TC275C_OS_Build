/*
 * os_kernel.c
 *
 *  Created on: Aug 26, 2015
 *      Author: tz68d9
 */


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
//__syscallfunc(1) int syscall_a( int, int );
//__syscallfunc(2) int syscall_b( int, int );
//__syscallfunc(3) int syscall_c( int, int );

//! \cond IGNORE
#define DISPATCH_WAIT     2
#define DISPATCH_SIGNAL   3


//#define OLD_AVALIABLE


__syscallfunc(DISPATCH_WAIT)   int dispatch_wait(void *, void *);
__syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
//! \endcond

 uint32_t pthread_runnable;
 pthread_t pthread_running;
 pthread_t pthread_runnable_threads[PTHREAD_PRIO_MAX];
 static pthread_t blocked_threads;

 //! tw array hold condition and time for pthread_cond_timedwait_np.
 
 static struct {
         uint16_t ticks[PTHREAD_COND_TIMEDWAIT_SIZE];//!< time
         pthread_cond_t *cond[PTHREAD_COND_TIMEDWAIT_SIZE];//!< condition
         uint32_t idx; //!< current index to time and condition
     } tw = { 
                { 
			 	    USHRT_MAX, 
				    USHRT_MAX, 
				    USHRT_MAX, 
				    USHRT_MAX,
                    USHRT_MAX, 
                    USHRT_MAX, 
                    USHRT_MAX, 
                    USHRT_MAX
                }, 
                {
                    NULL,
				    NULL,
                    NULL,
				    NULL,
				    NULL,
				    NULL,
				    NULL,
				    NULL
			    },
			    0
	        };
	 

uint16_t  stm_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{

         		    USHRT_MAX, 
				    USHRT_MAX, 
				    USHRT_MAX, 
				    USHRT_MAX,
                    USHRT_MAX, 
                    USHRT_MAX, 
                    USHRT_MAX, 
                    USHRT_MAX
    };//!< time
pthread_cond_t  *stm_cond[PTHREAD_COND_TIMEDWAIT_SIZE]=
	{
                    NULL,
				    NULL,
                    NULL,
				    NULL,
				    NULL,
				    NULL,
				    NULL,
				    NULL
    };//!< condition

extern uint32 stm0CompareValue;
inline void update_stm0_ticks(void)
{
    uint32 stmTicks;

    stmTicks= (uint32)(stm0CompareValue*1);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_0, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_0) + stmTicks);
    IfxPort_togglePin(&MODULE_P33, 8);
}
extern uint32 stm0CompareValue2;

// Unit:ms ,the max is 0xFFFFFFFF/100000=42949ms(42.949s);
inline void update_stm0_compare1_ticks(uint32 tick_ms)
{
    uint32 stmTicks;

    stmTicks= (uint32)(stm0CompareValue2*tick_ms);
    IfxStm_updateCompare (&MODULE_STM0, IfxStm_Comparator_1, IfxStm_getCompare (&MODULE_STM0, IfxStm_Comparator_1) + stmTicks);
    IfxPort_togglePin(&MODULE_P33, 10);
}



//#define NULL (void*)0
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
            /* The bug is found here*/
        	blocked_threads=NULL;
        	//blocked_threads_prev_temp=cond->blocked_threads->prev;
        	list_append(&blocked_threads, cond->blocked_threads,
                         cond->blocked_threads->prev, cond->blocked_threads->next);
            //locked_threads=cond->blocked_threads;
            cond->blocked_threads = NULL;

            /*  The software interrupt 0 of core0 is used.   */
            SRC_GPSR00.B.SETR=1;
            SRC_GPSR00.B.SRE=1;
            SRC_GPSR00.B.TOS=0;
            SRC_GPSR00.B.SRPN=9;
            //CPU_SRC0.U = 1 << 15 // Set request
            //        | 1 << 12 // Service Request Enable
            //        | 0 << 10 // TOS=CPU
            //        | 1; //Service Request Priority Number
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

// dispatch_signal_in_tick function
inline void dispatch_signal_in_tick(pthread_t *blocked_threads_ptr, pthread_t last_thread) {

	pthread_t thread, tmp;
	int i;

    tmp = NULL;
    assert(blocked_threads_ptr);
    thread = *blocked_threads_ptr;
    while (thread != NULL) 
	{
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
}

/*! Trap class 6 handler (System trap) called by
 \code __syscallfunc(DISPATCH_WAIT)  int dispatch_wait(void *, void *);
 \code __syscallfunc(DISPATCH_SIGNAL) int dispatch_signal(void *, void *);
 */
pthread_t pthread_runnable_threads_test;
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
        pthread_runnable_threads_test=pthread_runnable_threads[i];
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

#if 0
void __interrupt(9) pthread_broadcast(
        void) {
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
}
#endif
int test_count;
void __interrupt(9) __vector_table(0) CPU0_SOFT0_Isr(void)
{
	#if 0
    __asm("; setup parameter and jump to trapsystem \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg trapsystem"
            ::"a"(&blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
            //::"a"(&blocked_threads),"a"(blocked_threads_prev_temp),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
	#endif
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
extern uint32_t pthread_runnable;
//! Currently running thread
extern pthread_t pthread_running;
//! Array of linked lists which holds runnable threads
extern pthread_t pthread_runnable_threads[PTHREAD_PRIO_MAX];

pthread_t pthread_running_testp;
uint32_t pthread_running_test;
int m=0;
extern pthread_t thread_1;
extern pthread_t thread_2;
pthread_t pthread_running_test2;

uint16_t tick_count;
uint16_t stm_tick_count;

//inline void update_stm0_ticks(void);
 void stm_src0(void) {

#if 0
    pthread_t thread;
    uint32 stmTicks;
#endif

    pthread_cond_t *cond;
    //int Null_Pointer_test;
#if 0
    pthread_running->lcx = __mfcr(CPU_PCXI);
    //pthread_running_test=__mfcr(CPU_PCXI);
    thread = pthread_running->next; // get next thread with same priority
    //pthread_running_test2=pthread_running;

   // assert(pthread_running->next);
   //  Null_Pointer_test=((void) (!(pthread_running->next) ? 1: (void) 0));

   // fix the bug that buserror will occur when pthread_running->next is NULL
    if(thread==NULL)
    {
    	thread=pthread_running;
    }

    pthread_runnable_threads[thread->priority] = thread;

    pthread_running = thread;

   // update_stm0_ticks();

#if 0
  if(m==0)
  {
    thread_2->lcx=__mfcr(CPU_PCXI);
    thread=thread_1;
    m=1;
  }
  else
  {
	thread_1->lcx=__mfcr(CPU_PCXI);
	thread=thread_2;
	m=0;
  }
#endif

    __dsync(); // required before PCXI manipulation (see RTOS porting guide)
    __mtcr(CPU_PCXI, thread->lcx);
    __asm("ji a11");
#endif

    update_stm0_ticks();
    // STM tick from 0-0xffff every 1ms
    tick_count++;


    if(tw.ticks[tw.idx]==tick_count)
    {


    }
    else
    {
#if 0

     cond = tw.cond[tw.idx]; // get current condition
     tw.ticks[tw.idx] = USHRT_MAX; // free place in array
     //uint32_t cmp = ixminu16(tw.ticks, PTHREAD_COND_TIMEDWAIT_SIZE, &tw.idx);

     //if (cmp == USHRT_MAX)
     //   STM_SRC1.B.SRE = 0; // disable the node if there are no more conditions waiting or
     //else
     //   STM_CMP1.U = __max((uint16_t)(STM_TIM4.U + 1), cmp); // set next compare

     //STM_ISRR.B.CMP1IRR = 1; // STOREBIT(STM_ISRR, 2, 1);
     assert(cond != NULL);

     //setup parameter and jump to trapsystem
    __asm( " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2   \n"
            " jg trapsystem  "
            ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
#endif
    }

}


 void __interrupt(10) __vector_table(0) Ifx_STM0_Isr(void)
 {

#ifdef OLD_AVALIABLE
 	//__svlcx();
 	//__isync();
 	//stm_src0();
 	/* we restore the lower context, this could be form any task or our saved from entry */
 	//__rslcx();
 	//__isync();
 	/* we don't was calling here we must return with rfe */
 	//__asm ( "rfe" );
	// stm_src0();

#if 0
    pthread_t thread;
    uint32 stmTicks;
#endif

    pthread_cond_t *cond;
    //int Null_Pointer_test;

    update_stm0_ticks();  // update the tick, this line cannot be changed now.
    // STM tick from 0-0xffff every 1ms
    tick_count++;


    if(tw.ticks[2]==tick_count)
    {
#if 1

     cond = tw.cond[2]; // get current condition
     tw.ticks[2]  =USHRT_MAX;
     tw.cond[2]   =NULL;



	 
     //tw.ticks[tw.idx] = USHRT_MAX; // free place in array
     //uint32_t cmp = ixminu16(tw.ticks, PTHREAD_COND_TIMEDWAIT_SIZE, &tw.idx);

     //if (cmp == USHRT_MAX)
     //   STM_SRC1.B.SRE = 0; // disable the node if there are no more conditions waiting or
     //else
     //   STM_CMP1.U = __max((uint16_t)(STM_TIM4.U + 1), cmp); // set next compare

     //STM_ISRR.B.CMP1IRR = 1; // STOREBIT(STM_ISRR, 2, 1);


	 //this line should be added to check the bug for example 5
     //assert(cond != NULL);       

     //setup parameter and jump to trapsystem
    __asm( " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2   \n"
            " jg trapsystem  "
            ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");

            //::"a"(&blocked_threads),"a"(blocked_threads_prev_temp),"d"(DISPATCH_SIGNAL),"a"(trapsystem):"a4","a5","d15");
#endif
#if 0
     __asm(  " svlcx          \n"
             " jla   stm_src0 \n"
   		    " rslcx"::"a"(pthread_running->next));
#endif
#if 0
       __asm( " svlcx   \t");
       __asm( " jla\t %0" : : "a" (stm_src0));
       __asm( " rslcx \t");
       __asm( " rfe");
#endif
   }

#else 
    
    pthread_cond_t  *cond;
	pthread_cond_t  *cond_buffer[PTHREAD_COND_TIMEDWAIT_SIZE];
    uint32_t        index;
	uint32_t        release_count=0;


	stm_tick_count=(stm_tick_count+1)%0xFFFF;                               // os tick from 0-0xffff
	update_stm0_ticks();                                                    // update the tick, this line cannot be changed now.
	
    for(index=0;index<PTHREAD_COND_TIMEDWAIT_SIZE;index++)
    {
      if(stm_ticks[index]==stm_tick_count)
	  {		
		cond_buffer[release_count] = stm_cond[index];
		stm_ticks[index]           = USHRT_MAX;                             // free place in array 
		
		release_count++;
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

#endif

 }
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//! Wait on a condition
	uint32_t current_id;
	uint16_t new_tick_count;
    uint16_t set_count;
int pthread_cond_timedwait_np(pthread_cond_t *cond,//!< [in] condition pointer
        pthread_mutex_t *mutex,//!< [in] mutex pointer
        uint16_t reltime,
        uint32_t task_id) //!< [in] relative time are the relative time STM_TIM4 ticks.NOT PORTABLE.
{

#ifdef OLD_AVALIABLE
    assert(cppn()==0); // CCPN must be 0, pthread_create cannot be called from ISR
    assert(cond != NULL);
    assert(mutex != NULL);

    uint32_t i;

    __disable();
    //STM_SRC1.B.SRE = 0; // STM_SRC1.U = 0x0000 | TIMEDWAIT_INT; // disable service request control register
    // add ticks value and condition to array
    //if (USHRT_MAX != ixmaxu16(tw.ticks, PTHREAD_COND_TIMEDWAIT_SIZE, &i))
    //    return -1; // no free

    //uint16_t tim4 = STM_TIM4.U + 1;

    //tw.ticks[i] = __min(tick_count + reltime, USHRT_MAX - 1); // __extru(tim4 + reltime, 0, 16)
    //tw.ticks[2] =(tick_count + reltime)%(USHRT_MAX - 1); // __extru(tim4 + reltime, 0, 16)
    tw.ticks[2] =(tick_count + reltime)%(USHRT_MAX - 1);
	tw.cond[2] = cond;

    //uint16_t temp=ixminu16(tw.ticks, PTHREAD_COND_TIMEDWAIT_SIZE,&tw.idx);

    // find the next compare
    //STM_CMP1.U = __max(tick_count, ixminu16(tw.ticks, PTHREAD_COND_TIMEDWAIT_SIZE,
    //        &tw.idx));
    //STM_SRC1.B.SRE = 1; // STM_SRC1.U = 0x1000 | TIMEDWAIT_INT; // enable service request control register
    

    __swap(&mutex->lock, false);
    int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
    __enable();
    __swap(&mutex->lock, true);
    mutex->owner = pthread_running;
    return 0;
#else

    assert(cppn()==0); // CCPN must be 0, pthread_create cannot be called from ISR
    assert(cond != NULL);
    assert(mutex != NULL);


			
    //if (USHRT_MAX != ixmaxu16(stm_ticks, PTHREAD_COND_TIMEDWAIT_SIZE, &current_id))
    //    return -1; // no free
			
	new_tick_count           = stm_tick_count + 1;
	set_count                = ((uint16_t)(new_tick_count + reltime))%0xFFFF;  // set_count ranges from 0-0xFFFE
	
    stm_ticks[task_id]       = set_count;                                      // load the current tick set(lconfig 1.)
    stm_cond[task_id]        = cond;                                           // load the cond.(lconfig 2.)

	
    __swap(&mutex->lock, false);
    int err = dispatch_wait(&cond->blocked_threads, NULL);// swap out with mutex unlocked
    __swap(&mutex->lock, true);
    mutex->owner = pthread_running;

    return 0;
#endif

}

//! STM interupts to manage timed wait conditions
//void __interrupt(PTHREAD_TIMEDWAIT_INT) stm_src1(void) {

//}
int __a0 test_count_stm0_compare1_small_data;
int  test_count_stm0_compare1;
void __interrupt(20) __vector_table(0) Ifx_STM0_compare1_Isr(void)
{
	test_count_stm0_compare1_small_data++;
	test_count_stm0_compare1++;

 	update_stm0_compare1_ticks(1000);// Unit:ms ,the max is 0xFFFFFFFF/100000=42949ms(42.949s);
}



