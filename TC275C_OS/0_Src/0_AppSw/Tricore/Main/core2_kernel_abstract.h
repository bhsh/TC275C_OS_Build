
#ifndef CORE2_KERNEL_ABSTRACT_H_
#define CORE2_KERNEL_ABSTRACT_H_

#include "os_type.h"
#include "os.h"
#include "os_kernel.h"


#define core2_thread_initialization();    CORE_ID_t        current_core_id = os_getCoreId() ;                \
                                          pthread_config_t pthread_config =                                  \
	                                      core2_pthread_init_config_database[(int)arg];                      \
                                          for (;;)                                                           \
                                          {                                                                  \
								 		  	core2_thread_done_before_task(&pthread_config,current_core_id); 
#define core2_thread_taskcallback();        task(&pthread_config,current_core_id);          	                                         
#define core2_thread_termination();         core2_thread_done_after_task(&pthread_config,current_core_id);   \
	                                      }

#define CORE2_PTHREAD_DEFINITION_BLOCK(thread_id)    void core2_os_thread##thread_id(void* arg,task_ptr_t task) \
			                                           {                                                        \
			                                               core2_thread_initialization();                       \
			                                               core2_thread_taskcallback();                         \
			                                               core2_thread_termination();                          \
		                                               }
#define CORE2_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  
#define CORE2_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_id,callback_task_name)  \
	           pthread_create_np(thread_var,thread_attr,thread_name,thread_id,callback_task_name);
#define CORE2_PTHREAD_START_BLOCK() pthread_start_np();

#endif
