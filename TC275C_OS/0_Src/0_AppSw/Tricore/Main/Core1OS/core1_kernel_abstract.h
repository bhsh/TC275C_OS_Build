/****************************************************************************/
/* FILE NAME:    core1_kernel_abstract.h                                    */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the abstract macro definition for the  */
/*               thread definitions of core1 os                             */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef CORE1_KERNEL_ABSTRACT_H_
#define CORE1_KERNEL_ABSTRACT_H_

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#if(OS_STACK_MODE == MANY_STACKS)

  /****************************************************************************/
  /* Macro Definitions <CORE1>: Many stacks structure for core1 OS threads    */
  /****************************************************************************/
  #define CORE1_PTHREAD_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  		  core1_pthread_init_config_database[(int)arg]; \
            for (;;){ \
  	        core1_pthread_management_before_task(&pthread_config); 
  	
  #define CORE1_PTHREAD_TASKCALLBACK_BLOCK \
  	      task(&pthread_config);   
  
  #define CORE1_PTHREAD_TERMINATION_BLOCK  \
  	      core1_pthread_management_after_task(&pthread_config);}
  
  #define CORE1_PTHREAD_DEFINITION_BLOCK(thread_order_num)  \
  	      void core1_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	        CORE1_PTHREAD_INITIALIZATION_BLOCK  \
  	        CORE1_PTHREAD_TASKCALLBACK_BLOCK  \
  	        CORE1_PTHREAD_TERMINATION_BLOCK}

  /****************************************************************************/
  /* Macro Definitions <CORE1>: Many stacks control block threads             */
  /****************************************************************************/
  #define _CORE1_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) \
  	      PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  
  	
  #define CORE1_PTHREAD_CONTROL_BLOCK(thread_order_num) \
  	      _CORE1_PTHREAD_CONTROL_BLOCK(core1_os_th##thread_order_num, \
  	                                   CORE1_THREAD##thread_order_num##_PRIORITY, \
  	                                   SCHED_FIFO, \
  	                                   CORE1_THREAD##thread_order_num##_STACK_SIZE)
  /****************************************************************************/
  /* Macro Definitions <CORE1>:CREATION BLOCK                                 */
  /****************************************************************************/
  #define _CORE1_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
  	      core1_pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);
  
  #define CORE1_PTHREAD_CREATION_BLOCK(thread_order_num) \
  	      _CORE1_PTHREAD_CREATION_BLOCK(core1_os_th##thread_order_num, \
  		                                &core1_thread_attr[CORE1_THREAD_ID##thread_order_num],\
  		                                core1_os_thread##thread_order_num,\
  		                                (void*) CORE1_THREAD_ID##thread_order_num, \
  		                                CORE1_TASK##thread_order_num) \
  		  CORE1_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num, \
  		                                      core1_os_th##thread_order_num->stack, \
  		                                      *core1_os_th##thread_order_num->stack)
  		                                      
#else

  /****************************************************************************/
  /* Macro Definitions <CORE1>: One stack structure for core1 OS threads      */
  /****************************************************************************/
  
  /****************************************************************************/
  /* Macro Definitions <CORE1>: One stack structure for application threads   */
  /****************************************************************************/
  #define CORE1_PTHREAD_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  	      core1_pthread_init_config_database[(int)arg]; \
  	      core1_pthread_management_before_task(&pthread_config); 
  
  #define CORE1_PTHREAD_TASKCALLBACK_BLOCK \
  	      task(&pthread_config);   
  
  #define CORE1_PTHREAD_TERMINATION_BLOCK  \
  	      core1_pthread_management_after_task(&pthread_config);\
            if(pthread_config.curr_task_type == EVENT) \
  	  	  { __asm( " mov.aa a4,%0 \t\n jg pthread_cond_wait \n" ::"a"(&core1_pthread_cond[pthread_config.curr_task_id]),"a"(pthread_cond_wait):"a4");} \
  	      else if(pthread_config.curr_task_type == PERIODIC) \
  		  { __asm( " mov d4,%0 \t\n jg core1_pthread_cond_timedwait_np \n"::"d"(pthread_config.curr_task_period),"a"(core1_pthread_cond_timedwait_np):"d4");} \
  	      else if(pthread_config.curr_task_type == NO_DEFINITION){}
  
  #define CORE1_PTHREAD_DEFINITION_BLOCK(thread_order_num)  \
  	      void core1_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	      CORE1_PTHREAD_INITIALIZATION_BLOCK  \
  	      CORE1_PTHREAD_TASKCALLBACK_BLOCK  \
  	      CORE1_PTHREAD_TERMINATION_BLOCK}
  
  /****************************************************************************/
  /* Funtion Definitions <CORE1>: One stack for idle threads                  */
  /****************************************************************************/
  #define CORE1_PTHREAD_IDLE_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  	      core1_pthread_init_config_database[(int)arg]; \
            for (;;){ \
  	        core1_pthread_management_before_task(&pthread_config);
  
  #define CORE1_PTHREAD_IDLE_TASKCALLBACK_BLOCK \
  	        task(&pthread_config); 
  	
  #define CORE1_PTHREAD_IDLE_TERMINATION_BLOCK  \
  	        core1_pthread_management_after_task(&pthread_config);}
  
  #define CORE1_PTHREAD_IDLE_DEFINITION_BLOCK(thread_order_num)  \
  	      void core1_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	        CORE1_PTHREAD_IDLE_INITIALIZATION_BLOCK  \
  	        CORE1_PTHREAD_IDLE_TASKCALLBACK_BLOCK  \
  	        CORE1_PTHREAD_IDLE_TERMINATION_BLOCK}

  /****************************************************************************/
  /* Macro Definitions <CORE1>:One stack control block for threads            */
  /****************************************************************************/
  #define _CORE1_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_ini_stack_address,_thread_ptr) \
  	      PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_ini_stack_address,_thread_ptr)  
  	
  #define CORE1_PTHREAD_CONTROL_BLOCK(thread_order_num) \
  	      _CORE1_PTHREAD_CONTROL_BLOCK(core1_os_th##thread_order_num, \
  	                                   CORE1_THREAD##thread_order_num##_PRIORITY, \
  	                                   SCHED_FIFO, \
  	                                   core1_os_stack,\
  	                                   core1_os_thread##thread_order_num)

  #define _CORE1_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
  	      core1_pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);
  
  #define CORE1_PTHREAD_CREATION_BLOCK(thread_order_num) \
  	      _CORE1_PTHREAD_CREATION_BLOCK(core1_os_th##thread_order_num, \
  		                                &core1_thread_attr[CORE1_THREAD_ID##thread_order_num],\
  		                                core1_os_thread##thread_order_num,\
  		                                (void*) CORE1_THREAD_ID##thread_order_num, \
  		                                CORE1_TASK##thread_order_num)  
#endif

/****************************************************************************/
/* Macro Definitions <CORE1>:START BLOCK                                    */
/****************************************************************************/		                           
#define CORE1_PTHREAD_START_BLOCK() core1_pthread_start_np();

#endif /* End of CORE1_KERNEL_ABSTRACT_H_*/
