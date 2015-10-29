
#ifndef KERNEL_ABSTRACT_H_
#define KERNEL_ABSTRACT_H_

#include "os_type.h"
#include "os.h"
#include "os_kernel.h"


#define thread_initialization();          CORE_ID_t        current_core_id = os_getCoreId() ;          \
                                          pthread_config_t pthread_config =                            \
	                                      core0_pthread_init_config_database[(int)arg];                \
                                          for (;;)                                                     \
                                          {                                                            \
								 		  	thread_done_before_task(&pthread_config,current_core_id); 
#define thread_taskcallback();              task(&pthread_config,current_core_id);          	                                         
#define thread_termination();               thread_done_after_task(&pthread_config,current_core_id);   \
	                                      }

#define PTHREAD_DEFINITION_BLOCK(core_id,thread_id)    void core##core_id##_os_thread##thread_id(void* arg,task_ptr_t task) \
			                                           {                                                                    \
			                                               thread_initialization();                                         \
			                                               thread_taskcallback();                                           \
			                                               thread_termination();                                            \
		                                               }
#define PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_id,callback_task_name)  \
	           pthread_create_np(thread_var,thread_attr,thread_name,thread_id,callback_task_name);
#define PTHREAD_START_BLOCK() pthread_start_np();

OS_EXTERN void thread_done_before_task(pthread_config_t*,CORE_ID_t);
OS_EXTERN void thread_done_after_task(pthread_config_t*,CORE_ID_t);

#endif
