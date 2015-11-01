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
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_kernel.h"

/****************************************************************************/
/* Type Definitions                                                        */
/****************************************************************************/
typedef pthread_mutex_t task_mutex_t;
typedef pthread_cond_t  task_cond_t;

/****************************************************************************/
/* User APIs                                                                */
/****************************************************************************/

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Lock                                              */
/* FUNCTION PROTOTYPE:  Task_Mutex_Lock(task_mutex_t *mutex)                */
/* ARGUMENT NAME: mutex                                                     */
/* ARGUMENT TYPE: task_mutex_t *                                            */
/* RETURN NAME :  None                                                      */
/* RETURN TYPE :  None                                                      */
/* USING RANGE :  Inside tasks                                              */
/****************************************************************************/
/* USAGE DESCRIPTION :                                                      */
/*                                                                          */
/*   task_mutex_t  mutex;                                                   */
/*   ......                                                                 */
/*   Task_Mutex_Lock(&mutex);                                               */
/*   // Your critical source that can only belong to                        */
/*   // one user at one time                                                */           
/*   Task_Mutex_Unlock(&mutex);                                             */
/*   ......                                                                 */
/****************************************************************************/
#define Task_Mutex_Lock(mutex_ptr)          pthread_mutex_lock(mutex_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Mutex_Unlock                                            */
/* FUNCTION PROTOTYPE:  Task_Mutex_Unlock(task_mutex_t *mutex)              */
/* ARGUMENT NAME: mutex                                                     */
/* ARGUMENT TYPE: task_mutex_t *                                            */
/* RETURN NAME :  None                                                      */
/* RETURN TYPE :  None                                                      */
/* USING RANGE :  Inside tasks                                              */
/****************************************************************************/
/* USAGE DESCRIPTION :  Please refer to Task_Mutex_Lock                     */
/****************************************************************************/
#define Task_Mutex_Unlock(mutex_ptr)        pthread_mutex_lock(mutex_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Cond_Wait                                               */
/* FUNCTION PROTOTYPE:  Task_Cond_Wait(task_cond_t *cond)                   */
/* ARGUMENT NAME: cond                                                      */
/* ARGUMENT TYPE: task_cond_t *                                             */
/* RETURN NAME :  None                                                      */
/* RETURN TYPE :  None                                                      */
/* USING RANGE :  Inside tasks                                              */
/****************************************************************************/
/* USAGE DESCRIPTION :                                                      */
/*                                                                          */
/*   task_cond_t  cond;                                                     */
/*   ......                                                                 */
/*   Task_Cond_Wait(&cond);                                                 */
/*   // The current task has been blocked when Task_Cond_Wait is reached    */ 
/*   // The following code of the task can only be executed after the task  */
/*   // is actived by Task_Cond_Broadcast                                   */
/*   ......                                                                 */
/****************************************************************************/
#define Task_Cond_Wait(cond_ptr)            pthread_cond_wait(cond_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Cond_Broadcast                                          */
/* FUNCTION PROTOTYPE:  Task_Cond_Broadcast(task_cond_t *cond)              */
/* ARGUMENT NAME: cond                                                      */
/* ARGUMENT TYPE: task_cond_t *                                             */
/* RETURN NAME :  None                                                      */
/* RETURN TYPE :  None                                                      */
/* USING RANGE :  Inside tasks or interrupt                                 */
/****************************************************************************/
/* USAGE DESCRIPTION : The API can actives tasks that have been blocked by  */
/*                     Task_Cond_Wait.                                      */
/*                     Here Task_Cond_Wait and Task_Cond_Broadcast should   */
/*                     use the same cond                                    */
/*                     Task_Cond_Broadcast can also be use to active task of*/
/*                     another core os                                      */
/*   task_cond_t  cond;                                                     */
/*   ......                                                                 */
/*   Task_Cond_Broadcast(&cond);                                            */
/*   ......                                                                 */
/****************************************************************************/
#define Task_Cond_Broadcast(cond_ptr)       pthread_cond_broadcast(cond_ptr)

/****************************************************************************/
/* MACRO NAME: Task_Cond_Timedwait                                          */
/* FUNCTION PROTOTYPE:  Task_Cond_Timedwait(usigned short wait_time)        */
/* ARGUMENT NAME: wait_time                                                 */
/* ARGUMENT TYPE: usigned short                                             */
/* RETURN NAME :  None                                                      */
/* RETURN TYPE :  None                                                      */
/* USING RANGE :  Inside tasks                                              */
/****************************************************************************/
/* USAGE DESCRIPTION : The API can active the task for wait_time ms.When    */
/*                     the task is blocked, the task owns lower priority    */
/*                     can be executed                                      */
/*   ......                                                                 */
/*   Task_Cond_Timedwait(500); // Wait 500ms                                */
/*   ......                                                                 */
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

#endif /* End of OS_TASK_H_ */
