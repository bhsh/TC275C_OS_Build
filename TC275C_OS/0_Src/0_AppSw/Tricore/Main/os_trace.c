/****************************************************************************/
/* FILE NAME:    os_trace.c                                                 */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes logic that traces the time             */
/*               characteristics of tasks                                   */
/*               tasks                                                      */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#include "os_type.h"
#include "os_interface.h"

#define TRACE_MAX_CORE_NUM    (3)
#define TRACE_MAX_THREAD_NUM  (11)

static volatile osu32_t os_thread_time[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_tick_begin[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_timeslot[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_switch_times[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_begin_timeslot[TRACE_MAX_CORE_NUM];
static volatile osu32_t os_thread_end_timeslot[TRACE_MAX_CORE_NUM];

static osu32_t os_trace_time(void)
{
  return (osu32_t)(os_getstmlower_count()/10);
}
void OS_test1(osu32_t time)
{
   osu32_t i,j,m;
   for(i=0;i<time;i++)
   {
       for(j=0;j<time;j++)
	   m=i+j;
   }	
}
void os_trace_task_time_begin(osu32_t current_core_id,osu32_t thread_id)
{
  os_tick_begin[current_core_id][thread_id] = os_trace_time();
  os_thread_begin_timeslot[current_core_id] = os_tick_begin[current_core_id][thread_id];
  os_thread_switch_times[current_core_id][thread_id] = 
  	   os_thread_begin_timeslot[current_core_id] - os_thread_end_timeslot[current_core_id];
}
void os_trace_task_time_end(osu32_t current_core_id,osu32_t thread_id)
{
  os_thread_time[current_core_id][thread_id] = 
  	   os_trace_time() - os_tick_begin[current_core_id][thread_id];
}
void os_trace_thread_timeslot(osu32_t current_core_id,osu32_t thread_id)
{
  os_thread_timeslot[current_core_id][thread_id] = os_trace_time();  
  os_thread_end_timeslot[current_core_id] = os_thread_timeslot[current_core_id][thread_id];
}


