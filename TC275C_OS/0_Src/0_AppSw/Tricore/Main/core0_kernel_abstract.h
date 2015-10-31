
#ifndef CORE0_KERNEL_ABSTRACT_H_
#define CORE0_KERNEL_ABSTRACT_H_

#include "os_kernel.h"

#define CORE0_PTHREAD_INITIALIZATION_BLOCK  \
	pthread_config_t pthread_config = \
	core0_pthread_init_config_database[(int)arg]; \
    for (;;){ \
	  core0_pthread_done_before_task(&pthread_config); 
	
#define CORE0_PTHREAD_TASKCALLBACK_BLOCK \
	  task(&pthread_config);   

#define CORE0_PTHREAD_TERMINATION_BLOCK  \
	  core0_pthread_done_after_task(&pthread_config);}

#define CORE0_PTHREAD_DEFINITION_BLOCK(thread_id)  \
	void core0_os_thread##thread_id(void* arg,task_ptr_t task){ \
	    CORE0_PTHREAD_INITIALIZATION_BLOCK  \
	    CORE0_PTHREAD_TASKCALLBACK_BLOCK  \
	    CORE0_PTHREAD_TERMINATION_BLOCK}

#define _CORE0_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) \
	PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  

#define CORE0_PTHREAD_CONTROL_BLOCK(thread_id) \
	_CORE0_PTHREAD_CONTROL_BLOCK(core0_os_th##thread_id, \
	                             CORE0_THREAD##thread_id##_PRIORITY, \
	                             SCHED_FIFO, \
	                             CORE0_THREAD##thread_id##_STACK_SIZE)

#define _CORE0_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_id,callback_task_name)  \
	 pthread_create_np(thread_var,thread_attr,thread_name,thread_id,callback_task_name);

#define CORE0_PTHREAD_CREATION_BLOCK(thread_id) \
	_CORE0_PTHREAD_CREATION_BLOCK(core0_os_th##thread_id, \
		                          &core0_thread_attr[CORE0_THREAD_ID##thread_id],\
		                          core0_os_thread##thread_id,\
		                          (void*) CORE0_THREAD_ID##thread_id, \
		                          CORE0_TASK##thread_id)
		                           
#define CORE0_PTHREAD_START_BLOCK() pthread_start_np();

#endif /* End of CORE0_KERNEL_ABSTRACT_H_*/
