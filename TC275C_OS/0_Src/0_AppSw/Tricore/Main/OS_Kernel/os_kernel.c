/****************************************************************************/
/* FILE NAME:    os_kernel.c                                                */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the kernel logic of AURIX 3-core os    */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define DISPATCH_WAIT     2
#define DISPATCH_SIGNAL   3
#define DISPATCH_ONLY     4

/****************************************************************************/
/* Global Variable Definitions                                              */
/****************************************************************************/
PTHREAD_MEMORY_QUALIFIER osu32_t           core0_os_pthread_runnable;
PTHREAD_MEMORY_QUALIFIER osu32_t           core1_os_pthread_runnable;
PTHREAD_MEMORY_QUALIFIER osu32_t           core2_os_pthread_runnable;
PTHREAD_MEMORY_QUALIFIER pthread_t         core0_os_pthread_running;
PTHREAD_MEMORY_QUALIFIER pthread_t         core1_os_pthread_running;
PTHREAD_MEMORY_QUALIFIER pthread_t         core2_os_pthread_running;
PTHREAD_MEMORY_QUALIFIER pthread_t         core0_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
PTHREAD_MEMORY_QUALIFIER pthread_t         core1_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
PTHREAD_MEMORY_QUALIFIER pthread_t         core2_os_pthread_runnable_threads[PTHREAD_PRIO_MAX];
PTHREAD_MEMORY_QUALIFIER pthreads_status_t core0_os_pthreads_status;
PTHREAD_MEMORY_QUALIFIER pthreads_status_t core1_os_pthreads_status;
PTHREAD_MEMORY_QUALIFIER pthreads_status_t core2_os_pthreads_status;

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu32_t   core0_os_mutex;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu32_t   core1_os_mutex;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu32_t   core2_os_mutex;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu16_t   core0_os_tick_count;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu16_t   core1_os_tick_count;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu16_t   core2_os_tick_count;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu32_t   core0_os_pthread_timewait_table;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu32_t   core1_os_pthread_timewait_table;
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu32_t   core2_os_pthread_timewait_table;
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_t core0_os_blocked_threads;
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_t core1_os_blocked_threads;
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_t core2_os_blocked_threads;

OS_STATIC PTHREAD_MEMORY_QUALIFIER osu16_t   core0_os_timewait_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
{ 
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 	
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_timewait_t  *core0_os_timewait_cond_ptr[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL                     
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_timewait_t  core0_os_timewait_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
{  
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu16_t  core1_os_timewait_ticks[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_timewait_t  *core1_os_timewait_cond_ptr[PTHREAD_COND_TIMEDWAIT_SIZE]=
{
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL  
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_timewait_t  core1_os_timewait_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
{  
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER osu16_t  core2_os_timewait_ticks[PTHREAD_COND_TIMEDWAIT_SIZE] =
{
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                      
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,  
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,                     
    USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX,USHRT_MAX 				    
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_timewait_t  *core2_os_timewait_cond_ptr[PTHREAD_COND_TIMEDWAIT_SIZE] =
{
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,                     
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL 
};
OS_STATIC PTHREAD_MEMORY_QUALIFIER pthread_timewait_t  core2_os_timewait_cond[PTHREAD_COND_TIMEDWAIT_SIZE] =
{  
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
    {NULL},{NULL},{NULL},{NULL},                     
};

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
__syscallfunc(DISPATCH_WAIT)   os32_t dispatch_wait(void *, void *);
__syscallfunc(DISPATCH_SIGNAL) os32_t dispatch_signal(void *, void *);
__syscallfunc(DISPATCH_ONLY)   os32_t dispatch_only(void *, void *);

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Get mutex                                      */
/****************************************************************************/
OS_INLINE osu32_t core_getMutex(osu32_t *mutex)
{
  return __swap(mutex, true);
} /* End of core_getMutex function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Return mutex                                   */
/****************************************************************************/
OS_INLINE void core_returnMutex(osu32_t *mutex)
{
  *mutex=0x0;
} /* End of core_returnMutex function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Append an element at the end of a list         */
/****************************************************************************/
OS_INLINE void list_append(pthread_t *head, /* <*head> list head pointer */
                           pthread_t  elem,  /* <elem> list element pointer */
                           pthread_t  list_prev, /* <list_prev> list_prev  pointer */
                           pthread_t  elem_next) /* <elem_next> elem_next  pointer */
{
    assert(head != NULL);
    assert(elem != NULL);

    pthread_t list = *head;
    if (list == NULL) 
	{
      elem->next = elem_next;
      /* elem->next = elem; */
      elem->prev = elem;
      *head = elem;
    }
	else 
	{
      elem->next = elem_next;
      elem->prev = list->prev;
      list->prev->next = elem;
      list->prev = list_prev;
    }
} /* End of list_append function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Delete the first element of a list             */
/****************************************************************************/
OS_STATIC void list_delete_first(pthread_t *head)  /* <*head> list head pointer */
{
	assert(head);

    pthread_t old = *head;
    pthread_t new = old->next;

    if (new != NULL)
	{
      old->prev->next = new;
      new->prev = old->prev;
      if (new->next == new) new->next = NULL; /* If the list has only one element than set ->next = NULL */
    }
    *head = new;
} /* End of list_delete_first function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Create threads                                 */
/****************************************************************************/
#if(OS_STACK_MODE == MANY_STACKS)  /* <MORE_STACKS> More stacks interface */
  os32_t core0_pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                                 const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                                 void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                                 void *arg,  /* <*arg> 1st argument of thread */
                                 task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
  {
      osu32_t              fcx;
  	  context_t            *cx;
      const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
  	
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
  	
      osu32_t i = thread->priority;
  	  
      list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                  core0_os_pthread_runnable_threads[i]);
      __putbit(1,(os32_t*)&core0_os_pthread_runnable,i); /* <CORE0> Mark current thread ready */
      
      return 0; /* Dummy to avoid warning */
  } /* End of pthread_create_np function */


  os32_t core1_pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                                 const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                                 void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                                 void *arg,  /* <*arg> 1st argument of thread */
                                 task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
  {
      osu32_t              fcx;
  	  context_t            *cx;
      const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
  	
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
  	
      osu32_t i = thread->priority;
  	
      list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                   core1_os_pthread_runnable_threads[i]);
      __putbit(1,(os32_t*)&core1_os_pthread_runnable,i); /* <CORE1> Mark current thread ready */

      return 0; /* Dummy to avoid warning */
  } /* End of pthread_create_np function */


  os32_t core2_pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                                 const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                                 void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                                 void *arg,  /* <*arg> 1st argument of thread */
                                 task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
  {
      osu32_t              fcx;
  	  context_t            *cx;
      const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
  	
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
  	
      osu32_t i = thread->priority;

      list_append(&core2_os_pthread_runnable_threads[i], thread, thread,
                 core2_os_pthread_runnable_threads[i]);
      __putbit(1,(os32_t*)&core2_os_pthread_runnable,i); /* <CORE2> Mark current thread ready */

      return 0; /* Dummy to avoid warning */
  } /* End of pthread_create_np function */

#else
  os32_t core0_pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                                 const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                                 void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                                 void *arg,  /* <*arg> 1st argument of thread */
                                 task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
  {
      osu32_t              fcx;
  	  context_t            *cx;
      const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
  	
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
      //cx->u.a10 = thread->stack + *thread->stack; /* <EVERY CORE> Stack grow down */
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
  	  thread->thread_a4 = arg;
  	  thread->thread_a5 = core0_task_ptr;
      thread->arg = arg;
  	  
      osu32_t i = thread->priority;
  	 
      list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                 core0_os_pthread_runnable_threads[i]);
      __putbit(1,(os32_t*)&core0_os_pthread_runnable,i); /* <CORE0> Mark current thread ready */

      return 0; /* Dummy to avoid warning */
  } /* End of pthread_create_np function */

  os32_t core1_pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                                 const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                                 void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                                 void *arg,  /* <*arg> 1st argument of thread */
                                 task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
  {
      osu32_t              fcx;
  	  context_t            *cx;
      const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
  	
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
      //cx->u.a10 = thread->stack + *thread->stack; /* <EVERY CORE> Stack grow down */
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
  	  thread->thread_a4 = arg;
  	  thread->thread_a5 = core0_task_ptr;
      thread->arg = arg;
  	  
      osu32_t i = thread->priority;
  	
      list_append(&core1_os_pthread_runnable_threads[i], thread, thread,
                 core1_os_pthread_runnable_threads[i]);
      __putbit(1,(os32_t*)&core1_os_pthread_runnable,i); /* <CORE1> Mark current thread ready */

      return 0; /* Dummy to avoid warning */
  } /* End of pthread_create_np function */

  os32_t core2_pthread_create_np(pthread_t thread, /* <thread> Thread control block pointer */
                                 const pthread_attr_t *attr, /* <*attr> Thread attribute. Can be NULL to use default */
                                 void(*start_routine)(void *,task_ptr_t),/* <*start_routine> Thread function pointer */
                                 void *arg,  /* <*arg> 1st argument of thread */
                                 task_ptr_t core0_task_ptr) /* <*arg> 2nd argument of thread */
  {
      osu32_t              fcx;
  	  context_t            *cx;
      const pthread_attr_t default_attr = PTHREAD_DEFAULT_ATTR;
  	
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
      //cx->u.a10 = thread->stack + *thread->stack; /* <EVERY CORE> Stack grow down */
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
  	  thread->thread_a4 = arg;
  	  thread->thread_a5 = core0_task_ptr;
      thread->arg = arg;
  	  
      osu32_t i = thread->priority;

      list_append(&core2_os_pthread_runnable_threads[i], thread, thread,
                 core2_os_pthread_runnable_threads[i]);
      __putbit(1,(os32_t*)&core2_os_pthread_runnable,i); /* <CORE2> Mark current thread ready */

      return 0; /* Dummy to avoid warning */
  } /* End of pthread_create_np function */

#endif

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Lock an resource.This is an OS API that is     */
/*              provided to os user                                         */
/****************************************************************************/
os32_t core0_pthread_mutex_lock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{	
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */

    if (mutex->owner == core0_os_pthread_running) return -1;

	/* <CORE0> Swap out if already looked by another thread */
    while (true == __swap(&mutex->lock, true)) 
	{  
      dispatch_wait(&mutex->blocked_threads, NULL); /* <CORE0> Block this thread */
    }
    mutex->owner = core0_os_pthread_running;
	
    return 0;/* Dummy to avoid warning */
} /* End of pthread_mutex_lock function */

os32_t core1_pthread_mutex_lock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */

    if (mutex->owner == core1_os_pthread_running) return -1;
	
	/* <CORE1> Swap out if already looked by another thread */
    while (true == __swap(&mutex->lock, true))
	{ 
      dispatch_wait(&mutex->blocked_threads, NULL); /* <CORE1> Block this thread */
    }
    mutex->owner = core1_os_pthread_running;
	
    return 0;/* Dummy to avoid warning */
} /* End of pthread_mutex_lock function */

os32_t core2_pthread_mutex_lock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{		
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */

    if (mutex->owner == core2_os_pthread_running) return -1;

	/* <CORE2> Swap out if already looked by another thread */
    while (true == __swap(&mutex->lock, true))
	{ 
      dispatch_wait(&mutex->blocked_threads, NULL); /* <CORE2> Block this thread */
    }
    mutex->owner = core2_os_pthread_running;

    return 0;/* Dummy to avoid warning */
} /* End of pthread_mutex_lock function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> Unlock an resource.This is an OS API that is   */
/*              provided to os user                                         */
/****************************************************************************/
os32_t core0_pthread_mutex_unlock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */ 
	
    if (mutex->owner != core0_os_pthread_running) return -1;

    pthread_t threads = mutex->blocked_threads;
    mutex->owner = NULL;
    mutex->lock = false;
    mutex->blocked_threads = NULL;
    if (threads != NULL) dispatch_signal(&threads, NULL);

    return 0; /* Dummy to avoid warning */
} /* End of pthread_mutex_unlock function */

os32_t core1_pthread_mutex_unlock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{		
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */ 
	
    if (mutex->owner != core1_os_pthread_running) return -1;

    pthread_t threads = mutex->blocked_threads;
    mutex->owner = NULL;
    mutex->lock = false;
    mutex->blocked_threads = NULL;
    if (threads != NULL) dispatch_signal(&threads, NULL);
	
    return 0; /* Dummy to avoid warning */
} /* End of pthread_mutex_unlock function */

os32_t core2_pthread_mutex_unlock(pthread_mutex_t *mutex) /* <*mutex> mutex pointer */
{		
    assert(cppn()==0); /* CCPN must be 0, function cannot be called from ISR */
    assert (mutex != NULL); /* Make sure there is one mutex argument. If no, __debug() will be entered */ 
	
    if (mutex->owner != core2_os_pthread_running) return -1;

    pthread_t threads = mutex->blocked_threads;
    mutex->owner = NULL;
    mutex->lock = false;
    mutex->blocked_threads = NULL;
    if (threads != NULL) dispatch_signal(&threads, NULL);
	
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

	//if(cond->semaphore <= 1)
	//{  
	//    cond->semaphore = 0;

	    /* <EVERY CORE> Add this thread to the list of blocked threads by this cond */
        dispatch_wait(&cond->blocked_threads, NULL);
    //}
    //else
	//{  
	   /* cond->semaphore > 1 */
    //   cond->semaphore --;
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
	osu32_t current_core_id = os_getCoreId();
	osu32_t cond_core_id   = cond->core_id;

#if 0
	if(cond->semaphore == 0)
	{
      cond->semaphore = 1;
#endif
      if (cond->blocked_threads != NULL)
	  {	 
	  	PTHREAD_OBTAIN_TIMESLOT_CALLBACK(cond_core_id)
		if((cond_core_id == current_core_id)&&(0 == cppn()))
        {		
          /* <EVERY CORE> _pthread_running on CCPN=0 */
          dispatch_signal(&cond->blocked_threads, cond->blocked_threads->prev);
        }
        else
		{
	      if(cond_core_id == CORE0_ID)
	      { 
			while(0!=core_getMutex(&core0_os_mutex)){};
			 
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
		                 (CORE0_KERNEL_SOFT_INT_LEVEL);     /* SRC_GPSR00.B.SRPN=9; <Service Request Priority Number> */

			/* core_returnMutex(&core0_os_mutex); */
          }
		  else if(cond_core_id == CORE1_ID)
		  { 
            while(0!=core_getMutex(&core1_os_mutex)){};
			
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
		                 (CORE1_KERNEL_SOFT_INT_LEVEL);     /* SRC_GPSR10.B.SRPN=8;  <Service Request Priority Number> */     
		                 
			/* core_returnMutex(&core1_os_mutex); */
		  }
		  else if(cond_core_id == CORE2_ID)
		  { 
            while(0!=core_getMutex(&core2_os_mutex)){};
			 
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
		                 (CORE2_KERNEL_SOFT_INT_LEVEL);     /* SRC_GPSR20.B.SRPN=7;  <Service Request Priority Number> */
		                 
		    /* core_returnMutex(&core2_os_mutex); */
		  }
		}		
      }
#if 0
	}
	else
	{
       cond->semaphore ++;
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
 OS_INLINE void core0_dispatch_signal_in_tick(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
 {
 	os32_t    i;
 	pthread_t thread, tmp;
 
 	tmp = NULL;
   assert(blocked_threads_ptr);
   thread = *blocked_threads_ptr;
 	
   while (thread != NULL) 
 	{
     tmp = thread->next;
     i = thread->priority;

	  #if(OS_STACK_MODE == ONE_STACK)  /* <MORE_STACKS> More stacks interface */
 	    /* <CORE0> Set the status of the current thread to "ready" */
 	    thread->thread_status = S_READY;
	  #endif
 				  
     list_append(&core0_os_pthread_runnable_threads[i], thread, thread,
                   core0_os_pthread_runnable_threads[i]);
     __putbit(1,(os32_t*)&core0_os_pthread_runnable,i);
     if (thread == last_thread) break;
     thread = tmp;
   }
   *blocked_threads_ptr = tmp;
 }/* End of dispatch_signal_in_tick functio */

   OS_INLINE void core1_dispatch_signal_in_tick(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
 {
 	os32_t    i;
 	pthread_t thread, tmp;
 
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
     if (thread == last_thread)break;
     thread = tmp;
   }
   *blocked_threads_ptr = tmp;
 	
 }/* End of dispatch_signal_in_tick functio */

 OS_INLINE void core2_dispatch_signal_in_tick(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
 {
 	os32_t    i;
 	pthread_t thread, tmp;
 
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
     if (thread == last_thread)break;
     thread = tmp;
   }
   *blocked_threads_ptr = tmp;
 }/* End of dispatch_signal_in_tick functio */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE>  Os kernel logic that can be called by trap 6  */
/*              and software interrupts that are used for thread activation */
/*                                                                          */
/* OPTIONS:                                                                 */
/*    __syscallfunc(DISPATCH_WAIT)   os32_t dispatch_wait(void *, void *);  */
/*    <EVERY CORE> Make threads that have been actived be blocked           */
/*                                                                          */
/*    __syscallfunc(DISPATCH_SIGNAL) os32_t dispatch_signal(void *, void *);*/
/*    <EVERY CORE> Make threads that have been blocked be actived           */
/*                                                                          */
/*    __syscallfunc(DISPATCH_ONLY)   os32_t dispatch_only(void *, void *);  */
/*    <EVERY CORE> Only reschedule all threads that have been actived       */
/*    without changing the scheduling table                                 */
/****************************************************************************/
#if(OS_STACK_MODE == MANY_STACKS)  /* <MORE_STACKS> More stacks interface */
  OS_STATIC void core0_os_kernel(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
  {
      os32_t tin, i;
      pthread_t thread, tmp;
  
      __asm(" mov %0,d15 \n"
              " svlcx        "
              : "=d"(tin)); /* Put d15 in C variable tin */
    
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
    
    /* <CORE0> Unlock core0_os_mutex */
    core_returnMutex(&core0_os_mutex);
	
    core0_pthread_start_np();
  } /* End of os_kernel function */

OS_STATIC void core1_os_kernel(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
  {
      os32_t tin, i;
      pthread_t thread, tmp;
  
      __asm(" mov %0,d15 \n"
              " svlcx        "
              : "=d"(tin)); /* Put d15 in C variable tin */
    
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
  		
  	  /* <CORE1> Unlock core1_os_mutex */
  	  core_returnMutex(&core1_os_mutex);
  	
      core1_pthread_start_np();
  } /* End of os_kernel function */

  OS_STATIC void core2_os_kernel(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
  {
      os32_t tin, i;
      pthread_t thread, tmp;
  
      __asm(" mov %0,d15 \n"
              " svlcx        "
              : "=d"(tin)); /* Put d15 in C variable tin */
  
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
  		
  	  /* <CORE2> Unlock core2_os_mutex */
      core_returnMutex(&core2_os_mutex);		
      core2_pthread_start_np();
  } /* End of os_kernel function */


#else

 OS_STATIC void core0_os_kernel(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
  {
      os32_t tin, i;
      pthread_t thread, tmp;
  	  context_t *cx;
  
      __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); /* Put d15 in C variable tin */
  
  	  osu32_t current_core_id = os_getCoreId();
    
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
  
	   		/* <CORE0> Section used for one stack for all threads begins */
	   		/* <CORE0> Set the status of the current thread to "terminated" */
	   		core0_os_pthread_running->thread_status = S_TERMINATED;
	   		 
	   		/* <CORE0> Update the entry point of the current thread into the sintial point */
	   		/* <CORE0> Get the lower context address */
	   		cx = cx_to_addr(core0_os_pthread_running->lcx);
	   
	   		/* <CORE0> Reset the enrty point of thread to the initial position */
	   		/* Notice:the initial point is placed in task_ptr when the thread  */
	   		/* block was being initialized                                     */
	   		cx->l.pc = core0_os_pthread_running->thread_ptr; /* <EVERY CORE> init new thread start address */ 
	        cx->l.a4 = core0_os_pthread_running->thread_a4;
	        cx->l.a5 = core0_os_pthread_running->thread_a5;
	   		/* <CORE0> Get the upper context address */
	   		//cx = cx_to_addr(cx->l.pcxi);
	   
	   		/* <CORE0> Set the curr_stack_address of the thread to the stack  */
	   		/* address the current thread                                     */
	   		//core0_os_pthread_running->curr_stack_address = cx->u.a10;
	   		/* <CORE0> Section used for one stack for all threads ends */
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
  		  
	  		  /* <CORE0> Set the status of the current thread to "ready" */
	  		  thread->thread_status = S_READY;
  		  
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
    
      /* <CORE0> Unlock core0_os_mutex */
      core_returnMutex(&core0_os_mutex);
  
      core0_pthread_start_np();
  } /* End of os_kernel function */

  OS_STATIC void core1_os_kernel(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
  {
      os32_t tin, i;
      pthread_t thread, tmp;
	  
      __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); /* Put d15 in C variable tin */
  
  	  osu32_t current_core_id = os_getCoreId();
  
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
  		
  	  /* <CORE1> Unlock core1_os_mutex */
  	core_returnMutex(&core1_os_mutex);  	
    core1_pthread_start_np();
  } /* End of os_kernel function */

  OS_STATIC void core2_os_kernel(pthread_t *blocked_threads_ptr, pthread_t last_thread) 
  {
      os32_t tin, i;
      pthread_t thread, tmp;
  
      __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); /* Put d15 in C variable tin */
  
  	  osu32_t current_core_id = os_getCoreId();
  	
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
  		
  	  /* <CORE2> Unlock core2_os_mutex */
      core_returnMutex(&core2_os_mutex);		
      core2_pthread_start_np();
  } /* End of os_kernel function */


#endif

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_kernel_in_tick) is used inside the  */
/*              tick interrupts of STM0,STM1 and STM2 to deal with periodic */
/*              thread scheduling events                                    */
/****************************************************************************/
OS_INLINE void core0_os_kernel_in_tick(void)
{
    osu32_t             index;
	osu32_t             release_count = 0;
	osu32_t             tempt_index;
	pthread_timewait_t  *cond;
	pthread_timewait_t  *cond_buffer[PTHREAD_COND_TIMEDWAIT_SIZE];
	
	tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core0_os_pthread_timewait_table);
	if( tempt_index == 0) return;
	tempt_index = tempt_index - 1;
	for(index = 0 ; index <= tempt_index ; index++)
	{
	  if(core0_os_timewait_ticks[index] == core0_os_tick_count)
	  {		
  		  cond_buffer[release_count] = core0_os_timewait_cond_ptr[index];
  		  core0_os_timewait_ticks[index] = USHRT_MAX;     /* <CORE0> Free place in array */
  		  __putbit(0,(os32_t*)&core0_os_pthread_timewait_table,index); 
  		  release_count++;
	  }
	}

    /* <EVERY CORE> If more than one threads that haved been set to periodic */
	/* mode have reached the waiting time,the logic is entered in order to   */
	/* reschedule the threads                                                */
	if(release_count != 0)
	{
	  assert(cond_buffer[0] != NULL);
	  if(release_count > 1)
	  {
        while( -- release_count)
	    {
          core0_dispatch_signal_in_tick(&cond_buffer[release_count]->blocked_threads ,NULL );
	    }
	  }
	  assert(cond_buffer[0] != NULL);
		
	  cond = cond_buffer[0];  /* <EVERY CORE> Get the current condition */

	  PTHREAD_OBTAIN_TIMESLOT_CALLBACK(0)

	  /* <EVERY CORE> Setup parameter and jump to os_kernel */
	  __asm( " mov.aa a4,%0 \n"
	         " mov.aa a5,%1 \n"
	         " mov d15,%2   \n"
	         " jg core0_os_kernel  "
	         ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(core0_os_kernel):"a4","a5","d15");
	}
} /* End of os_kernel_in_tick function */

OS_INLINE void core1_os_kernel_in_tick(void)
{
    osu32_t             index;
	osu32_t             release_count = 0;
	osu32_t             tempt_index;
	pthread_timewait_t  *cond;
	pthread_timewait_t  *cond_buffer[PTHREAD_COND_TIMEDWAIT_SIZE];
	
	tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core1_os_pthread_timewait_table);
	if( tempt_index == 0) return;
	tempt_index = tempt_index - 1;
	for(index = 0 ; index <= tempt_index ; index++)
	{
  	   if(core1_os_timewait_ticks[index] == core1_os_tick_count)
  	  {		
  		  cond_buffer[release_count] = core1_os_timewait_cond_ptr[index];
  		  core1_os_timewait_ticks[index] = USHRT_MAX;   /* <CORE1> Free place in array */    
  		  __putbit(0,(os32_t*)&core1_os_pthread_timewait_table,index); 
  		  release_count++;
  	  }
	}
	
    /* <EVERY CORE> If more than one threads that haved been set to periodic */
	/* mode have reached the waiting time,the logic is entered in order to   */
	/* reschedule the threads                                                */
	if(release_count != 0)
	{
	  assert(cond_buffer[0] != NULL);
	  if(release_count > 1)
	  {
        while( -- release_count)
	    {
          core1_dispatch_signal_in_tick(&cond_buffer[release_count]->blocked_threads ,NULL );
	    }
	  }
	  assert(cond_buffer[0] != NULL);
		
	  cond = cond_buffer[0];  /* <EVERY CORE> Get the current condition */

	  PTHREAD_OBTAIN_TIMESLOT_CALLBACK(1)

	  /* <EVERY CORE> Setup parameter and jump to os_kernel */
	  __asm( " mov.aa a4,%0 \n"
	         " mov.aa a5,%1 \n"
	         " mov d15,%2   \n"
	         " jg core1_os_kernel  "
	         ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(core1_os_kernel):"a4","a5","d15");
	}
} /* End of os_kernel_in_tick function */

OS_INLINE void core2_os_kernel_in_tick(void)
{
    osu32_t             index;
	osu32_t             release_count = 0;
	osu32_t             tempt_index;
	osu32_t             current_core_id = os_getCoreId();
	pthread_timewait_t  *cond;
	pthread_timewait_t  *cond_buffer[PTHREAD_COND_TIMEDWAIT_SIZE];
	
	tempt_index = PTHREAD_COND_TIMEDWAIT_SIZE - __clz(core2_os_pthread_timewait_table);
	if( tempt_index == 0) return;
	tempt_index = tempt_index - 1;
	for(index = 0 ; index <= tempt_index ; index++)
	{
    	if(core2_os_timewait_ticks[index] == core2_os_tick_count)
    	{		
    	  cond_buffer[release_count] = core2_os_timewait_cond_ptr[index];
    	  core2_os_timewait_ticks[index] = USHRT_MAX;  /* <CORE2> Free place in array */
    	  __putbit(0,(os32_t*)&core2_os_pthread_timewait_table,index); 
    	  release_count++;
    	}
	}

    /* <EVERY CORE> If more than one threads that haved been set to periodic */
	/* mode have reached the waiting time,the logic is entered in order to   */
	/* reschedule the threads                                                */
	if(release_count != 0)
	{
	  assert(cond_buffer[0] != NULL);
	  if(release_count > 1)
	  {
        while( -- release_count)
	    {
          core2_dispatch_signal_in_tick(&cond_buffer[release_count]->blocked_threads ,NULL );
	    }
	  }
	  assert(cond_buffer[0] != NULL);
		
	  cond = cond_buffer[0];  /* <EVERY CORE> Get the current condition */

	  PTHREAD_OBTAIN_TIMESLOT_CALLBACK(2)

	  /* <EVERY CORE> Setup parameter and jump to os_kernel */
	  __asm( " mov.aa a4,%0 \n"
	         " mov.aa a5,%1 \n"
	         " mov d15,%2   \n"
	         " jg core2_os_kernel  "
	         ::"a"(&cond->blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(core2_os_kernel):"a4","a5","d15");
	}
} /* End of os_kernel_in_tick function */
/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(pthread_cond_timedwait_np) can be used */
/*              inside threads to let the current thread blocked in for     */
/*              reltime(unit ms).This is an OS API that is provided to os   */
/*              user                                                        */
/****************************************************************************/
os32_t pthread_cond_timedwait_np(osu16_t reltime) /* <reltime> Waiting time, unit:ms */
{
	osu16_t new_tick_count;
    osu16_t set_count;
	osu32_t task_id = 0;
	osu32_t current_core_id = os_getCoreId();
	pthread_timewait_t *cond;
		
    assert(cppn()==0); /* CCPN must be 0, pthread_cond_timedwait_np cannot be called from ISR */

	if(current_core_id == CORE0_ID)
	{	  	
	  new_tick_count  = core0_os_tick_count + 1;
	  set_count = ((osu16_t)(new_tick_count + reltime))%0xFFFF;  /* <CORE0> set_count ranges from 0 to 0xFFFE */

      /* <CORE0> Search the empty position. */
      while((core0_os_timewait_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  
	  /* <CORE0> There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;
 
      cond = &core0_os_timewait_cond[task_id];
	  __putbit(1,(os32_t*)&core0_os_pthread_timewait_table,task_id); /* <CORE0> mark current thread ready */
	  
      core0_os_timewait_ticks[task_id] = set_count;     /* <CORE0> Load the current tick set(lconfig 1.) */ 
      core0_os_timewait_cond_ptr[task_id] = cond;           /* <CORE0> Load the cond.(lconfig 2.) */            

      os32_t err = dispatch_wait(&cond->blocked_threads, NULL);
	}
	else if(current_core_id == CORE1_ID)
	{ 
	  new_tick_count = core1_os_tick_count + 1;
	  set_count = ((osu16_t)(new_tick_count + reltime))%0xFFFF;  /* <CORE1> set_count ranges from 0 to 0xFFFE */

      /* <CORE1> Search the empty position. */
      while((core1_os_timewait_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  
	  /* <CORE1> There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;

      cond = &core1_os_timewait_cond[task_id];
	  __putbit(1,(os32_t*)&core1_os_pthread_timewait_table,task_id); /* <CORE1> mark current thread ready */
	  
	  core1_os_timewait_ticks[task_id] = set_count;  /* <CORE1> Load the current tick set(lconfig 1.) */    
      core1_os_timewait_cond_ptr[task_id] = cond;        /* <CORE1> Load the cond.(lconfig 2.) */              
	
      os32_t err = dispatch_wait(&cond->blocked_threads, NULL);
	  
	}
	else if(current_core_id == CORE2_ID)
	{
	  new_tick_count  = core2_os_tick_count + 1;
	  set_count = ((osu16_t)(new_tick_count + reltime))%0xFFFF;  /* <CORE2> set_count ranges from 0 to 0xFFFE */

      /* <CORE2> Search the empty position. */
      while((core2_os_timewait_ticks[task_id] != USHRT_MAX)&&(task_id < PTHREAD_COND_TIMEDWAIT_SIZE ))
	  {
        task_id++;
	  }
	  
	  /* <CORE2> There is not any empty position now. the call is returned. */
	  if(task_id == PTHREAD_COND_TIMEDWAIT_SIZE ) return 0;

      cond = &core2_os_timewait_cond[task_id];
	  __putbit(1,(os32_t*)&core2_os_pthread_timewait_table,task_id); /* <CORE2> mark current thread ready */

	  core2_os_timewait_ticks[task_id] = set_count;  /* <CORE2> Load the current tick set(lconfig 1.) */
      core2_os_timewait_cond_ptr[task_id] = cond;        /* <CORE2> Load the cond.(lconfig 2.) */

      os32_t err = dispatch_wait(&cond->blocked_threads, NULL);
	}
    return 0; /* Dummy to avoid warning */
} /* End of pthread_cond_timedwait_np function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(pthread_suspend_allthreads) can be used*/
/*              inside threads to suspend all that happend after the API is */
/*              called.This is an OS API that is provided to os user        */
/****************************************************************************/
void core0_pthread_suspend_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */ 
    if(core0_os_pthreads_status == ALLTHREADS_WORKING)
    {	
      core0_os_pthreads_status = ALLTHREADS_SUSPENDED;
    }

} /* End of pthread_suspend_allthreads function */
void core1_pthread_suspend_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */
    if(core1_os_pthreads_status == ALLTHREADS_WORKING)
    {
      core1_os_pthreads_status = ALLTHREADS_SUSPENDED;
    }
} /* End of pthread_suspend_allthreads function */
void core2_pthread_suspend_allthreads(void)
{
	/* Because the scheduler logic is located in stm tick interrupt, and */
    if(core2_os_pthreads_status == ALLTHREADS_WORKING)
    {
      core2_os_pthreads_status = ALLTHREADS_SUSPENDED;
    }
} /* End of pthread_suspend_allthreads function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(pthread_restore_allthreads) can be used*/
/*              inside threads to restore all threads that are suspended.   */
/*              After the API is called all thread that are suspended by    */
/*              os_restore_allthreads can be restore immediately This is    */
/*              an OS API that is provided to os user                       */
/****************************************************************************/
void core0_pthread_restore_allthreads(void)
{
    if(core0_os_pthreads_status == ALLTHREADS_SUSPENDED)
    {  
	  core0_os_pthreads_status = ALLTHREADS_WORKING;
	  
	  /* <CORE0> If there is thread higher than the current thread, switch the context. else keep */
	  if(core0_os_pthread_running->priority < 
	  	 ((PTHREAD_PRIO_MAX-1) - __clz(core0_os_pthread_runnable))) dispatch_only(NULL,NULL);     
    }
    
} /* End of pthread_restore_allthreads function */
void core1_pthread_restore_allthreads(void)
{   
    if(core1_os_pthreads_status == ALLTHREADS_SUSPENDED)
    {
	  core1_os_pthreads_status = ALLTHREADS_WORKING;
	   
	  /* <CORE1> If there is thread higher than the current thread, switch the context. else keep */
	  if(core1_os_pthread_running->priority < 
	   	 ((PTHREAD_PRIO_MAX-1) - __clz(core1_os_pthread_runnable))) dispatch_only(NULL,NULL);     
    }
    
} /* End of pthread_restore_allthreads function */
void core2_pthread_restore_allthreads(void)
{ 
    if(core2_os_pthreads_status == ALLTHREADS_SUSPENDED)
    {
	  core2_os_pthreads_status = ALLTHREADS_WORKING;
	   
	  /* <CORE2> If there is thread higher than the current thread, switch the context. else keep */
	  if(core2_os_pthread_running->priority < 
	   	 ((PTHREAD_PRIO_MAX-1) - __clz(core2_os_pthread_runnable))) dispatch_only(NULL,NULL);     
    }
} /* End of pthread_restore_allthreads function */


/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_disable_allinterrupts) can be used   */
/*              inside threads to disable all interrupts.This is an OS API  */
/*              that is provided to os user                                 */
/****************************************************************************/
void pthread_disable_allinterrupts(void) 
{
    __asm volatile ("disable" : : : "memory");
    __asm volatile ("nop" : : : "memory");
} /* End of os_disable_allinterrupts function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(os_enable_allinterrupt) can be used    */
/*              inside threads to enable all interrupts.This is an OS API   */
/*              that is provided to os user                                 */
/****************************************************************************/
void pthread_enable_allinterrupts(void)
{
    __asm volatile ("enable" : : : "memory");
}   /* End of os_enable_allinterrupt function */

/****************************************************************************/
/* DESCRIPTION: <EVERY CORE> The API(pthread_obtain_os_tick) can be used    */
/*              inside threads to obtain os tick of core0,core1 and core2   */
/****************************************************************************/
osu16_t pthread_obtain_os_tick(os32_t core_id)
{
    osu16_t core_curr_tick = 0;

    if(core_id == CORE0_ID)
    {
      core_curr_tick = core0_os_tick_count;
    }
    else if(core_id == CORE1_ID)
    {
      core_curr_tick = core1_os_tick_count;
    }
    else if(core_id == CORE2_ID)
    {
      core_curr_tick = core2_os_tick_count;
    }
    return core_curr_tick;
}  /* End of os_enable_allinterrupt function */

/****************************************************************************/
/* DESCRIPTION:  <CORE0> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(CORE0_KERNEL_TICK_INT_LEVEL) __vector_table(VECTOR_TABLE0) core0_kernel_tick_isr(void)
{  
    /* <CORE0> OS tick ranges from 0-0xffff */
    core0_os_tick_count = ( core0_os_tick_count + 1)%0xFFFF;  

    /* <CORE0> Update the os tick of core0 */
	os_kernel_update_core0_tick();

    /* <CORE0> Call the scheduler part in the interrupt to deal with the */
    /* periodic thread activation of core0 */   
    core0_os_kernel_in_tick();
} /* End of core1_kernel_tick_isr intterrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE1> software interrupt 1 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(CORE1_KERNEL_TICK_INT_LEVEL) __vector_table(VECTOR_TABLE0) core1_kernel_tick_isr(void)
{ 
    /* <CORE1> OS tick ranges from 0-0xffff */
    core1_os_tick_count = ( core1_os_tick_count + 1)%0xFFFF; 

    /* <CORE1> Update the os tick of core1 */
    os_kernel_update_core1_tick();  

    /* <CORE1> Call the scheduler part in the interrupt to deal with the */
    /* periodic thread activation of core1 */   
    core1_os_kernel_in_tick();

} /* End of core1_kernel_tick_isr interrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE2> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(CORE2_KERNEL_TICK_INT_LEVEL) __vector_table(VECTOR_TABLE0) core2_kernel_tick_isr(void)
{  
    /* <CORE2> OS tick ranges from 0-0xffff */
    core2_os_tick_count = (core2_os_tick_count + 1)%0xFFFF; 

    /* <CORE2> Update the os tick of core2 */
    os_kernel_update_core2_tick(); 

    /* <CORE2> Call the scheduler part in the interrupt to deal with the */
    /* periodic thread activation of core2 */
    core2_os_kernel_in_tick();

} /* End of core2_kernel_tick_isr interrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE0> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(CORE0_KERNEL_SOFT_INT_LEVEL) __vector_table(VECTOR_TABLE0) core0_kernel_soft_isr(void)
{
    __asm("; setup parameter and jump to os_kernel \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg core0_os_kernel"
            ::"a"(&core0_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(core0_os_kernel):"a4","a5","d15");
} /* End of core0_kernel_soft_isr interrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE1> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(CORE1_KERNEL_SOFT_INT_LEVEL) __vector_table(VECTOR_TABLE0) core1_kernel_soft_isr(void)
{
    __asm("; setup parameter and jump to os_kernel \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg core1_os_kernel"
            ::"a"(&core1_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(core1_os_kernel):"a4","a5","d15");
} /* End of core1_kernel_soft_isr interrupt */

/****************************************************************************/
/* DESCRIPTION:  <CORE2> software interrupt 0 that is used for thread       */
/*                       activation when the activation source is located   */
/*                       in interrupt                                       */
/****************************************************************************/
void __interrupt(CORE2_KERNEL_SOFT_INT_LEVEL) __vector_table(VECTOR_TABLE0) core2_kernel_soft_isr(void)
{
    __asm("; setup parameter and jump to os_kernel \n"
            " mov.aa a4,%0 \n"
            " mov.aa a5,%1 \n"
            " mov d15,%2 \n"
            " jg core2_os_kernel"
            ::"a"(&core2_os_blocked_threads),"a"(0),"d"(DISPATCH_SIGNAL),"a"(core2_os_kernel):"a4","a5","d15");
} /* End of core2_kernel_soft_isr interrupt */

/****************************************************************************/
/* DESCRIPTION: <CORE0>  Trap vector table entry to trap class 6 handler    */
/****************************************************************************/
void core0_kernel_trap_systemcall(osu32_t tin)
{
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg core0_os_kernel     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(core0_os_kernel):"a4","a5","d15");
} /* End of core0_kernel_trap_systemcall function */

/****************************************************************************/
/* DESCRIPTION: <CORE1>  Trap vector table entry to trap class 6 handler    */
/****************************************************************************/
void core1_kernel_trap_systemcall(osu32_t tin)
{
	/* Add the kernel of OS */
	/* Kernel begins        */
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg core1_os_kernel     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(core1_os_kernel):"a4","a5","d15");
} /* End of core1_kernel_trap_systemcall function */

/****************************************************************************/
/* DESCRIPTION: <CORE2>  Trap vector table entry to trap class 6 handler    */
/****************************************************************************/
void core2_kernel_trap_systemcall(osu32_t tin)
{
    __asm(  " mtcr #ICR,%0    \n"
            " isync           \n"
            " jg core2_os_kernel     "
            ::"d"(1 << 15 | PTHREAD_USER_INT_LEVEL),"a"(core2_os_kernel):"a4","a5","d15");
} /* End of core2_kernel_trap_systemcall function */

