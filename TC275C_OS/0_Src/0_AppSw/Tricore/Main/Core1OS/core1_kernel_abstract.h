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

#define _CORE1_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) \
	PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  

#define CORE1_PTHREAD_CONTROL_BLOCK(thread_order_num) \
	_CORE1_PTHREAD_CONTROL_BLOCK(core1_os_th##thread_order_num, \
	                             CORE1_THREAD##thread_order_num##_PRIORITY, \
	                             SCHED_FIFO, \
	                             CORE1_THREAD##thread_order_num##_STACK_SIZE)

#define _CORE1_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
	 pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);

#define CORE1_PTHREAD_CREATION_BLOCK(thread_order_num) \
	_CORE1_PTHREAD_CREATION_BLOCK(core1_os_th##thread_order_num, \
		                          &core1_thread_attr[CORE1_THREAD_ID##thread_order_num],\
		                          core1_os_thread##thread_order_num,\
		                          (void*) CORE1_THREAD_ID##thread_order_num, \
		                          CORE1_TASK##thread_order_num)
		                           
#define CORE1_PTHREAD_START_BLOCK() pthread_start_np();

#endif /* End of CORE1_KERNEL_ABSTRACT_H_*/
