/****************************************************************************/
/* FILE NAME:    core0_kernel_abstract.h                                    */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the abstract macro definition for the  */
/*               thread definitions of core0 os                             */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef CORE0_KERNEL_ABSTRACT_H_
#define CORE0_KERNEL_ABSTRACT_H_

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#if(OS_STACK_MODE == MANY_STACKS)

  /****************************************************************************/
  /* Macro Definitions <CORE0>: Many stacks structure for core0 OS threads    */
  /****************************************************************************/
  #define CORE0_PTHREAD_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  		  core0_pthread_init_config_database[(int)arg]; \
            for (;;){ \
  	        core0_pthread_management_before_task(&pthread_config); 
  	
  #define CORE0_PTHREAD_TASKCALLBACK_BLOCK \
  	      task(&pthread_config);   
  
  #define CORE0_PTHREAD_TERMINATION_BLOCK  \
  	      core0_pthread_management_after_task(&pthread_config);}
  
  #define CORE0_PTHREAD_DEFINITION_BLOCK(thread_order_num)  \
  	      void core0_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	        CORE0_PTHREAD_INITIALIZATION_BLOCK  \
  	        CORE0_PTHREAD_TASKCALLBACK_BLOCK  \
  	        CORE0_PTHREAD_TERMINATION_BLOCK}

  /****************************************************************************/
  /* Macro Definitions <CORE0>: Many stacks control block threads             */
  /****************************************************************************/
  #define _CORE0_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) \
  	      PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  
  	
  #define CORE0_PTHREAD_CONTROL_BLOCK(thread_order_num) \
  	      _CORE0_PTHREAD_CONTROL_BLOCK(core0_os_th##thread_order_num, \
  	                                   CORE0_THREAD##thread_order_num##_PRIORITY, \
  	                                   SCHED_FIFO, \
  	                                   CORE0_THREAD##thread_order_num##_STACK_SIZE)
  /****************************************************************************/
  /* Macro Definitions <CORE0>:CREATION BLOCK                                 */
  /****************************************************************************/
  #define _CORE0_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
  	      core0_pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);
  
  #define CORE0_PTHREAD_CREATION_BLOCK(thread_order_num) \
  	      _CORE0_PTHREAD_CREATION_BLOCK(core0_os_th##thread_order_num, \
  		                                &core0_thread_attr[CORE0_THREAD_ID##thread_order_num],\
  		                                core0_os_thread##thread_order_num,\
  		                                (void*) CORE0_THREAD_ID##thread_order_num, \
  		                                CORE0_TASK##thread_order_num) \
  		  CORE0_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num, \
  		                                      core0_os_th##thread_order_num->stack, \
  		                                      *core0_os_th##thread_order_num->stack)
  		                                      
#else

  /****************************************************************************/
  /* Macro Definitions <CORE0>: One stack structure for core0 OS threads      */
  /****************************************************************************/
  
  /****************************************************************************/
  /* Macro Definitions <CORE0>: One stack structure for application threads   */
  /****************************************************************************/
  #define CORE0_PTHREAD_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  	      core0_pthread_init_config_database[(int)arg]; \
  	      core0_pthread_management_before_task(&pthread_config); 
  
  #define CORE0_PTHREAD_TASKCALLBACK_BLOCK \
  	      task(&pthread_config);   
  
  #define CORE0_PTHREAD_TERMINATION_BLOCK  \
  	      core0_pthread_management_after_task(&pthread_config);\
            if(pthread_config.curr_task_type == EVENT) \
  	  	  { __asm( " mov.aa a4,%0 \t\n jg pthread_cond_wait \n" ::"a"(&core0_pthread_cond[pthread_config.curr_task_id]),"a"(pthread_cond_wait):"a4");} \
  	      else if(pthread_config.curr_task_type == PERIODIC) \
  		  { __asm( " mov d4,%0 \t\n jg pthread_cond_timedwait_np \n"::"d"(pthread_config.curr_task_period),"a"(pthread_cond_timedwait_np):"d4");} \
  	      else if(pthread_config.curr_task_type == NO_DEFINITION){}
  
  #define CORE0_PTHREAD_DEFINITION_BLOCK(thread_order_num)  \
  	      void core0_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	      CORE0_PTHREAD_INITIALIZATION_BLOCK  \
  	      CORE0_PTHREAD_TASKCALLBACK_BLOCK  \
  	      CORE0_PTHREAD_TERMINATION_BLOCK}
  
  /****************************************************************************/
  /* Funtion Definitions <CORE0>: One stack for idle threads                  */
  /****************************************************************************/
  #define CORE0_PTHREAD_IDLE_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  	      core0_pthread_init_config_database[(int)arg]; \
            for (;;){ \
  	        core0_pthread_management_before_task(&pthread_config);
  
  #define CORE0_PTHREAD_IDLE_TASKCALLBACK_BLOCK \
  	        task(&pthread_config); 
  	
  #define CORE0_PTHREAD_IDLE_TERMINATION_BLOCK  \
  	        core0_pthread_management_after_task(&pthread_config);}
  
  #define CORE0_PTHREAD_IDLE_DEFINITION_BLOCK(thread_order_num)  \
  	      void core0_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	        CORE0_PTHREAD_IDLE_INITIALIZATION_BLOCK  \
  	        CORE0_PTHREAD_IDLE_TASKCALLBACK_BLOCK  \
  	        CORE0_PTHREAD_IDLE_TERMINATION_BLOCK}

  /****************************************************************************/
  /* Macro Definitions <CORE0>:One stack control block for threads            */
  /****************************************************************************/
  #define _CORE0_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_ini_stack_address,_thread_ptr) \
  	      PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_ini_stack_address,_thread_ptr)  
  	
  #define CORE0_PTHREAD_CONTROL_BLOCK(thread_order_num) \
  	      _CORE0_PTHREAD_CONTROL_BLOCK(core0_os_th##thread_order_num, \
  	                                   CORE0_THREAD##thread_order_num##_PRIORITY, \
  	                                   SCHED_FIFO, \
  	                                   core0_os_stack,\
  	                                   core0_os_thread##thread_order_num)

  #define _CORE0_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
  	      core0_pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);
  
  #define CORE0_PTHREAD_CREATION_BLOCK(thread_order_num) \
  	      _CORE0_PTHREAD_CREATION_BLOCK(core0_os_th##thread_order_num, \
  		                                &core0_thread_attr[CORE0_THREAD_ID##thread_order_num],\
  		                                core0_os_thread##thread_order_num,\
  		                                (void*) CORE0_THREAD_ID##thread_order_num, \
  		                                CORE0_TASK##thread_order_num)  
#endif

/****************************************************************************/
/* Macro Definitions <CORE0>:START BLOCK                                    */
/****************************************************************************/		                           
#define CORE0_PTHREAD_START_BLOCK() core0_pthread_start_np();

#endif /* End of CORE0_KERNEL_ABSTRACT_H_*/
