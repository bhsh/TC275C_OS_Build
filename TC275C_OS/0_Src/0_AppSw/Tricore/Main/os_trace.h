/****************************************************************************/
/* FILE NAME:    os_trace.h                                                 */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes logic that traces the time             */
/*               characteristics of tasks                                   */
/*               tasks                                                      */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

#ifndef OS_TRACE_H_
#define OS_TRACE_H_

extern void os_trace_task_time_begin(osu32_t curr_core_id,osu32_t thread_id);
extern void os_trace_task_time_end(osu32_t curr_core_id,osu32_t thread_id);

#endif
