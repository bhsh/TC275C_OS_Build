
#ifndef KERNEL_ABSTRACT_H_
#define KERNEL_ABSTRACT_H_

#include "os_kernel.h"

#define thread_initialization();          core_id_e        current_core_id = os_getCoreId() ;          \
                                          pthread_config_t pthread_config =                            \
	                                      os_pthread_init_config_database[current_core_id][(int)arg];  \
                                          for (;;)                                                     \
                                          {                                                            \
								 		  	thread_done_before_task(&pthread_config,current_core_id); 
#define thread_taskcallback();              task(&pthread_config);          	                                         
#define thread_termination();               thread_done_after_task(&pthread_config,current_core_id);                   \
	                                      }

OS_EXTERN pthread_cond_t os_pthread_cond[MAX_CORE_NUM][TASK_ID_MAX];										  
OS_EXTERN void thread_done_before_task(pthread_config_t*,core_id_e);
OS_EXTERN void thread_done_after_task(pthread_config_t*,core_id_e);

#endif
