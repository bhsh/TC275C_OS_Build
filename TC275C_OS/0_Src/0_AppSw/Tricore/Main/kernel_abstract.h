
#ifndef KERNEL_ABSTRACT_H_
#define KERNEL_ABSTRACT_H_

#include "os_kernel.h"
//#include "task_config.h"
enum task_type{

   NO_DEFINITION,
   TASK_PERIODIC,
   TASK_EVENT
};

#define thread_initialization();          pthread_config_t pthread_config =                      \
	                                               core0_pthread_init_config_database[(int)arg]; \
                                          for (;;)                                               \
                                          {                                                      \
								 		  	thread_done_before_task(&pthread_config); 
#define thread_taskcallback();              task(&pthread_config);          	                                         
#define thread_termination();               thread_done_after_task(&pthread_config);             \
	                                      }

extern pthread_cond_t core0_os_cond_def[11];										  
extern void thread_done_before_task(pthread_config_t *pthread_config);
extern void thread_done_after_task(pthread_config_t *pthread_config);

#endif
