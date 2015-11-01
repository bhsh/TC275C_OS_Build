
#ifndef CORE2_KERNEL_ABSTRACT_H_
#define CORE2_KERNEL_ABSTRACT_H_

#include "os_kernel.h"

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

#define _CORE2_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) \
	PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  

#define CORE2_PTHREAD_CONTROL_BLOCK(thread_order_num) \
	_CORE2_PTHREAD_CONTROL_BLOCK(core2_os_th##thread_order_num, \
	                             CORE2_THREAD##thread_order_num##_PRIORITY, \
	                             SCHED_FIFO, \
	                             CORE2_THREAD##thread_order_num##_STACK_SIZE)

#define _CORE2_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name)  \
	 pthread_create_np(thread_var,thread_attr,thread_name,thread_order_num,callback_task_name);

#define CORE2_PTHREAD_CREATION_BLOCK(thread_order_num) \
	_CORE2_PTHREAD_CREATION_BLOCK(core2_os_th##thread_order_num, \
		                          &core2_thread_attr[CORE2_THREAD_ID##thread_order_num],\
		                          core2_os_thread##thread_order_num,\
		                          (void*) CORE2_THREAD_ID##thread_order_num, \
		                          CORE2_TASK##thread_order_num)
		                           
#define CORE2_PTHREAD_START_BLOCK() pthread_start_np();

#endif
