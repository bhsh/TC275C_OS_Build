
#ifndef KERNEL_ABSTRACT_H_
#define KERNEL_ABSTRACT_H_

#include "os_kernel.h"

#define thread_initialization();          core_id_e        current_core_id = os_getCoreId() ;          \
                                          pthread_config_t pthread_config =                            \
	                                      os_pthread_init_config_database[current_core_id][(int)arg];  \
                                          for (;;)                                                     \
                                          {                                                            \
								 		  	thread_done_before_task(&pthread_config,current_core_id); 
#define thread_taskcallback();              task(&pthread_config,current_core_id);          	                                         
#define thread_termination();               thread_done_after_task(&pthread_config,current_core_id);   \
	                                      }

#define DEFINE_OS_THREAD(core_id,thread_id)    void core##core_id##_os_thread##thread_id(void* arg,task_ptr_t task) \
	                                           {                                                                    \
	                                               thread_initialization();                                         \
	                                               thread_taskcallback();                                           \
	                                               thread_termination();                                            \
                                               }
                                                

OS_EXTERN pthread_cond_t os_pthread_cond[CORE_MAX_ID_NUM][THREAD_MAX_ID_NUM];										  
OS_EXTERN void thread_done_before_task(pthread_config_t*,core_id_e);
OS_EXTERN void thread_done_after_task(pthread_config_t*,core_id_e);

#endif
