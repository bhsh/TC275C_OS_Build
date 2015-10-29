
#ifndef CORE2_KERNEL_ABSTRACT_H_
#define CORE2_KERNEL_ABSTRACT_H_

#include "os_type.h"
#include "os.h"
#include "os_kernel.h"


#define core2_thread_initialization();    pthread_config_t pthread_config =                                  \
	                                      core2_pthread_init_config_database[(int)arg];                      \
                                          for (;;)                                                           \
                                          {                                                                  \
								 		  	core2_thread_done_before_task(&pthread_config); 
#define core2_thread_taskcallback();        task(&pthread_config);          	                                         
#define core2_thread_termination();         core2_thread_done_after_task(&pthread_config);                   \
	                                      }

#define CORE2_PTHREAD_DEFINITION_BLOCK(thread_id)    void core2_os_thread##thread_id(void* arg,task_ptr_t task) \
			                                           {                                                        \
			                                               core2_thread_initialization();                       \
			                                               core2_thread_taskcallback();                         \
			                                               core2_thread_termination();                          \
		                                               }
#define CORE2_PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize) PTHREAD_CONTROL_BLOCK(_name,_priority,_policy,_stacksize)  

#define __CORE2_PTHREAD_CREATION_BLOCK(thread_var,thread_attr,thread_name,thread_id,callback_task_name)  \
	           pthread_create_np(thread_var,thread_attr,thread_name,thread_id,callback_task_name);

#define CORE2_PTHREAD_CREATION_BLOCK(thread_id)     __CORE2_PTHREAD_CREATION_BLOCK(core2_os_th##thread_id, \
		                                                                           &core2_thread_attr[CORE2_THREAD_ID##thread_id],\
		                                                                           core2_os_thread##thread_id,\
		                                                                           (void*)core2_pthread_init_config_database[CORE2_THREAD_ID##thread_id].task_id, \
		                                                                           CORE2_TASK##thread_id)
#define CORE2_PTHREAD_START_BLOCK() pthread_start_np();

#endif
