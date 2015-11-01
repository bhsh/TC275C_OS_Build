/****************************************************************************/
/* FILE NAME:    os_trace.c                                                 */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes logic that traces the time             */
/*               characteristics of threads                                 */
/*               tasks                                                      */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_type.h"
#include "low_driver_port.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define TRACE_MAX_CORE_NUM    (3)
#define TRACE_MAX_THREAD_NUM  (11)

/****************************************************************************/
/* Global Variable Definitions                                              */
/****************************************************************************/
osu32_t os_thread_thread_timeslot[TRACE_MAX_CORE_NUM];

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile osu32_t os_thread_curr_exe_time_rec[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_max_exe_time_rec[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_begin_timeslot_rec[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_end_timeslot_rec[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_curr_switching_times[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];
static volatile osu32_t os_thread_max_switching_times[TRACE_MAX_CORE_NUM][TRACE_MAX_THREAD_NUM];

/****************************************************************************/
/* FUNTION NAME:os_trace_time                                               */
/* DESCRIPTION: Get time slot by call lowdriver API                         */
/****************************************************************************/
static osu32_t os_trace_time(void)
{
    return (osu32_t)LowDriver_GetStmLower_Count();
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:os_trace_task_time_begin                                    */
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void os_trace_task_time_begin(osu32_t curr_core_id,osu32_t thread_id)
{  
    if(thread_id < TRACE_MAX_THREAD_NUM)
	{
      /* <EVERY CORE> Record the timeslot before the task is executed */
      os_thread_begin_timeslot_rec[curr_core_id][thread_id] = os_trace_time();

	  os_thread_curr_switching_times[curr_core_id][thread_id] = 
	    os_thread_begin_timeslot_rec[curr_core_id][thread_id] - os_thread_thread_timeslot[curr_core_id];

	  if(os_thread_curr_switching_times[curr_core_id][thread_id] >
	  	   os_thread_max_switching_times[curr_core_id][thread_id])
	  {
        os_thread_max_switching_times[curr_core_id][thread_id] =
		  os_thread_curr_switching_times[curr_core_id][thread_id];	
	  }
	}
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:os_trace_task_time_begin                                    */ 
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void os_trace_task_time_end(osu32_t curr_core_id,osu32_t thread_id)
{ 
	if(thread_id < TRACE_MAX_THREAD_NUM)
	{
	  /* <EVERY CORE> Record the timeslot after the task is executed */
      os_thread_end_timeslot_rec[curr_core_id][thread_id] = os_trace_time(); 

      /* <EVERY CORE> Record the execution time of the current task, */
	  /* unit: 0.1 us in the current software configuration          */
      os_thread_curr_exe_time_rec[curr_core_id][thread_id] = 
        os_thread_end_timeslot_rec[curr_core_id][thread_id] - 
          os_thread_begin_timeslot_rec[curr_core_id][thread_id];

	  /* <EVERY CORE> Record the max execution time of task          */
	  if(os_thread_curr_exe_time_rec[curr_core_id][thread_id] > 
		     os_thread_max_exe_time_rec[curr_core_id][thread_id])
	  {
	    os_thread_max_exe_time_rec[curr_core_id][thread_id] = 
	 	  os_thread_curr_exe_time_rec[curr_core_id][thread_id];
	  }
	}
}/* End of os_trace_task_time_end function  */



