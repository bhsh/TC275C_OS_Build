
#ifndef CORE0_KERNEL_ABSTRACT_H_
#define CORE0_KERNEL_ABSTRACT_H_

#include "os_type.h"
#include "os.h"
#include "os_kernel.h"


#define core0_thread_initialization();    pthread_config_t pthread_config =                                  \
	                                      core0_pthread_init_config_database[(int)arg];                      \
                                          for (;;)                                                           \
                                          {                                                                  \
								 		  	core0_thread_done_before_task(&pthread_config); 
#define core0_thread_taskcallback();        task(&pthread_config);          	                                         
#define core0_thread_termination();         core0_thread_done_after_task(&pthread_config);                   \
	                                      }

#define CORE0_PTHREAD_DEFINITION_BLOCK(thread_id)    void core0_os_thread##thread_id(void* arg,task_ptr_t task) \
			                                           {                                                        \
			                                               core0_thread_initialization();                       \
			                                               core0_thread_taskcallback();                         \
			                                               core0_thread_termination();                          \
		                                               }
#define CORE0_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  
#define CORE0_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_id,callback_task_name)  \
	           pthread_create_np(thread_var,thread_attr,thread_name,thread_id,callback_task_name);
#define CORE0_PTHREAD_START_BLOCK() pthread_start_np();

#endif
