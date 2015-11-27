/****************************************************************************/
/* FILE NAME:    core2_kernel_abstract.h                                    */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the abstract macro definition for the  */
/*               thread definitions of core2 os                             */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef CORE2_KERNEL_ABSTRACT_H_
#define CORE2_KERNEL_ABSTRACT_H_

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/


#if(OS_STACK_MODE == MANY_STACKS)

  /****************************************************************************/
  /* Macro Definitions <CORE2>: Many stacks structure for core2 OS threads    */
  /****************************************************************************/
  #define CORE2_PTHREAD_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  		  core2_pthread_init_config_database[(int)arg]; \
            for (;;){ \
  	        core2_pthread_management_before_task(&pthread_config); 
  	
  #define CORE2_PTHREAD_TASKCALLBACK_BLOCK \
  	      task(&pthread_config);   
  
  #define CORE2_PTHREAD_TERMINATION_BLOCK  \
  	      core2_pthread_management_after_task(&pthread_config);}
  
  #define CORE2_PTHREAD_DEFINITION_BLOCK(thread_order_num)  \
  	      void core2_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	        CORE2_PTHREAD_INITIALIZATION_BLOCK  \
  	        CORE2_PTHREAD_TASKCALLBACK_BLOCK  \
  	        CORE2_PTHREAD_TERMINATION_BLOCK}

  /****************************************************************************/
  /* Macro Definitions <CORE2>: Many stacks control block threads             */
  /****************************************************************************/
  #define _CORE2_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) \
  	      PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  
  	
  #define CORE2_PTHREAD_CONTROL_BLOCK(thread_order_num) \
  	      _CORE2_PTHREAD_CONTROL_BLOCK(core2_os_th##thread_order_num, \
  	                                   CORE2_THREAD##thread_order_num##_PRIORITY, \
  	                                   SCHED_FIFO, \
  	                                   CORE2_THREAD##thread_order_num##_STACK_SIZE)
  /****************************************************************************/
  /* Macro Definitions <CORE2>:CREATION BLOCK                                 */
  /****************************************************************************/
  #define _CORE2_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
  	      core2_pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);
  
  #define CORE2_PTHREAD_CREATION_BLOCK(thread_order_num) \
  	      _CORE2_PTHREAD_CREATION_BLOCK(core2_os_th##thread_order_num, \
  		                                &core2_thread_attr[CORE2_THREAD_ID##thread_order_num],\
  		                                core2_os_thread##thread_order_num,\
  		                                (void*) CORE2_THREAD_ID##thread_order_num, \
  		                                CORE2_TASK##thread_order_num) \
  		  CORE2_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num, \
  		                                      core2_os_th##thread_order_num->stack, \
  		                                      *core2_os_th##thread_order_num->stack)
  		                                      
#else

  /****************************************************************************/
  /* Macro Definitions <CORE2>: One stack structure for core2 OS threads      */
  /****************************************************************************/
  
  /****************************************************************************/
  /* Macro Definitions <CORE2>: One stack structure for application threads   */
  /****************************************************************************/
  #define CORE2_PTHREAD_INITIALIZATION_BLOCK  \
  	        pthread_config_t pthread_config = \
  	        core2_pthread_init_config_database[(int)arg]; \
  	        core2_pthread_management_before_task(&pthread_config); 
  
  #define CORE2_PTHREAD_TASKCALLBACK_BLOCK(thread_order_num) \
  	        if(core2_thread_condition_##thread_order_num == true) \
			{  task(&pthread_config); } \
			else \
			{ core2_thread_condition_##thread_order_num = true;}   
				  	
  #define core2_thread_termination_event() \
            if(pthread_config.curr_task_type == EVENT) \
  	  	    { __asm( " mov.aa a4,%0 \t\n jg pthread_cond_wait \n" ::"a"(&core2_pthread_cond[pthread_config.curr_task_id]),"a"(pthread_cond_wait):"a4");} \
  	        else if(pthread_config.curr_task_type == PERIODIC) \
  		    { __asm( " mov d4,%0 \t\n jg core2_pthread_cond_timedwait_np \n"::"d"(pthread_config.curr_task_period),"a"(core2_pthread_cond_timedwait_np):"d4");} \
  	        else if(pthread_config.curr_task_type == NO_DEFINITION){/* Do nothing*/} 
  
  #define CORE2_PTHREAD_TERMINATION_BLOCK  \
  	        core2_pthread_management_after_task(&pthread_config);\
  	        core2_thread_termination_event()
  
  #define CORE2_PTHREAD_DEFINITION_BLOCK(thread_order_num)  \
  	        static osu8_t core2_thread_condition_##thread_order_num = false; \
  	        void core2_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	          CORE2_PTHREAD_INITIALIZATION_BLOCK  \
  	          CORE2_PTHREAD_TASKCALLBACK_BLOCK(thread_order_num)  \
  	          CORE2_PTHREAD_TERMINATION_BLOCK}
  
  /****************************************************************************/
  /* Funtion Definitions <CORE2>: One stack for idle threads                  */
  /****************************************************************************/
  #define CORE2_PTHREAD_IDLE_INITIALIZATION_BLOCK  \
  	      pthread_config_t pthread_config = \
  	      core2_pthread_init_config_database[(int)arg]; \
            for (;;){ \
  	        core2_pthread_management_before_task(&pthread_config);
  
  #define CORE2_PTHREAD_IDLE_TASKCALLBACK_BLOCK \
  	        task(&pthread_config); 
  	
  #define CORE2_PTHREAD_IDLE_TERMINATION_BLOCK  \
  	        core2_pthread_management_after_task(&pthread_config);}
  
  #define CORE2_PTHREAD_IDLE_DEFINITION_BLOCK(thread_order_num)  \
  	      void core2_os_thread##thread_order_num(void* arg,task_ptr_t task){ \
  	        CORE2_PTHREAD_IDLE_INITIALIZATION_BLOCK  \
  	        CORE2_PTHREAD_IDLE_TASKCALLBACK_BLOCK  \
  	        CORE2_PTHREAD_IDLE_TERMINATION_BLOCK}

  /****************************************************************************/
  /* Macro Definitions <CORE2>:One stack control block for threads            */
  /****************************************************************************/
  #define _CORE2_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_ini_stack_address,_thread_ptr) \
  	      PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_ini_stack_address,_thread_ptr)  
  	
  #define CORE2_PTHREAD_CONTROL_BLOCK(thread_order_num) \
  	      _CORE2_PTHREAD_CONTROL_BLOCK(core2_os_th##thread_order_num, \
  	                                   CORE2_THREAD##thread_order_num##_PRIORITY, \
  	                                   SCHED_FIFO, \
  	                                   core2_os_stack,\
  	                                   core2_os_thread##thread_order_num)

  #define _CORE2_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
  	      core2_pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);
  
  #define CORE2_PTHREAD_CREATION_BLOCK(thread_order_num) \
  	      _CORE2_PTHREAD_CREATION_BLOCK(core2_os_th##thread_order_num, \
  		                                &core2_thread_attr[CORE2_THREAD_ID##thread_order_num],\
  		                                core2_os_thread##thread_order_num,\
  		                                (void*) CORE2_THREAD_ID##thread_order_num, \
  		                                CORE2_TASK##thread_order_num)  
#endif

/****************************************************************************/
/* Macro Definitions <CORE2>:START BLOCK                                    */
/****************************************************************************/		                           
#define CORE2_PTHREAD_START_BLOCK() core2_pthread_start_np();

#endif /* End of CORE2_KERNEL_ABSTRACT_H_*/
