
#ifndef CORE1_KERNEL_ABSTRACT_H_
#define CORE1_KERNEL_ABSTRACT_H_

#include "os_kernel.h"


#define core1_thread_initialization();    pthread_config_t pthread_config =                  \
	                                      core1_pthread_init_config_database[(int)arg];      \
                                          for (;;)                                           \
                                          {                                                  \
								 		  	core1_thread_done_before_task(&pthread_config); 
#define core1_thread_taskcallback();        task(&pthread_config);          	                                         
#define core1_thread_termination();         core1_thread_done_after_task(&pthread_config);   \
	                                      }

#define CORE1_PTHREAD_DEFINITION_BLOCK(thread_id)    void core1_os_thread##thread_id(void* arg,task_ptr_t task) \
			                                           {                                                        \
			                                               core1_thread_initialization();                       \
			                                               core1_thread_taskcallback();                         \
			                                               core1_thread_termination();                          \
		                                               }
#define __CORE1_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  

#define CORE1_PTHREAD_CONTROL_BLOCK(thread_id)  __CORE1_PTHREAD_CONTROL_BLOCK(core1_os_th##thread_id, \
	                                                                          CORE1_THREAD##thread_id##_PRIORITY, \
	                                                                          SCHED_FIFO, \
	                                                                          CORE1_THREAD##thread_id##_STACK_SIZE)
	                                                                          
#define __CORE1_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_id,callback_task_name)  \
	           pthread_create_np(thread_var,thread_attr,thread_name,thread_id,callback_task_name);

#define CORE1_PTHREAD_CREATION_BLOCK(thread_id)     __CORE1_PTHREAD_CREATION_BLOCK(core1_os_th##thread_id, \
		                                                                           &core1_thread_attr[CORE1_THREAD_ID##thread_id],\
		                                                                           core1_os_thread##thread_id,\
		                                                                           (void*)core1_pthread_init_config_database[CORE1_THREAD_ID##thread_id].task_id, \
		                                                                           CORE1_TASK##thread_id)
#define CORE1_PTHREAD_START_BLOCK() pthread_start_np();

#endif
