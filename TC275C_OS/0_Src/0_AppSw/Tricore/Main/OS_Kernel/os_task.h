/****************************************************************************/
/* FILE NAME:    os_task.h                                                  */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes APIs definitions of Task for os user   */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_TASK_H_
#define OS_TASK_H_

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Mutex_Lock(mutex_ptr)          pthread_mutex_lock(mutex_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Mutex_Unlock(mutex_ptr)        pthread_mutex_lock(mutex_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Cond_Wait(cond_ptr)            pthread_cond_wait(cond_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Cond_Broadcast(cond_ptr)       pthread_cond_broadcast(cond_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Cond_Timedwait(wait_time)      pthread_cond_timedwait_np(wait_time)

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Enable_AllInterrupts()         pthread_enable_allinterrupts()

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Disable_AllInterrupts()        pthread_enable_allinterrupts()

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Suspend_AllThreads()           pthread_suspend_allthreads()

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Restore_AllThreads()           pthread_restore_allthreads()

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* DESCRIPTION:                                                             */
/****************************************************************************/
#define Task_Obtain_os_tick(cpu_id)         pthread_obtain_os_tick(cpu_id)

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"

#endif /* End of OS_TASK_H_ */
