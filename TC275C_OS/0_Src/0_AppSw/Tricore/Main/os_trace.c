
#include "os_interface.h"


#define MAX_CORE_NUM    (3)
#define MAX_THREAD_NUM  (11)

static volatile osu32_t os_thread_time[MAX_CORE_NUM][MAX_THREAD_NUM];
static volatile osu32_t os_tick_begin[MAX_CORE_NUM][MAX_THREAD_NUM];
static volatile osu32_t os_thread_timeslot[MAX_CORE_NUM][MAX_THREAD_NUM];
static volatile osu32_t os_thread_switch_times[MAX_CORE_NUM][MAX_THREAD_NUM];
static volatile osu32_t os_thread_begin_timeslot[MAX_CORE_NUM];
static volatile osu32_t os_thread_end_timeslot[MAX_CORE_NUM];

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
  os_thread_switch_times[current_core_id][thread_id] = os_thread_begin_timeslot[current_core_id] - os_thread_end_timeslot[current_core_id];
}
void os_trace_task_time_end(osu32_t current_core_id,osu32_t thread_id)
{
  os_thread_time[current_core_id][thread_id] = os_trace_time() - os_tick_begin[current_core_id][thread_id];
}

void os_trace_thread_timeslot(osu32_t current_core_id,osu32_t thread_id)
{
  os_thread_timeslot[current_core_id][thread_id] = os_trace_time();  
  os_thread_end_timeslot[current_core_id] = os_thread_timeslot[current_core_id][thread_id];
}


