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
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum 
{
    REC_CURR_EXE_TIME,
    REC_MAX_EXE_TIME,
    REC_BEGIN_TIMESLOT,
    REC_END_TIMESLOT,
    REC_CURR_SWITCHING_TIME,
	REC_MAX_SWITCHING_TIME,

	REC_MAX_ITEMS
	
} pthread_trace_info_t; 
/****************************************************************************/
/* Global Variable Definitions                                              */
/****************************************************************************/
osu32_t core0_os_thread_thread_timeslot;
osu32_t core1_os_thread_thread_timeslot;
osu32_t core2_os_thread_thread_timeslot;

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile osu32_t core0_os_trace_info[TRACE_MAX_THREAD_NUM][REC_MAX_ITEMS];
static volatile osu32_t core1_os_trace_info[TRACE_MAX_THREAD_NUM][REC_MAX_ITEMS];
static volatile osu32_t core2_os_trace_info[TRACE_MAX_THREAD_NUM][REC_MAX_ITEMS];

/****************************************************************************/
/* Function Definitions of core0 trace                                      */
/****************************************************************************/

/****************************************************************************/
/* FUNTION NAME:core0_os_trace_info_time                                         */
/* DESCRIPTION: Get time slot by call lowdriver API                         */
/****************************************************************************/
static osu32_t core0_os_trace_time(void)
{
    return (osu32_t)LowDriver_GetStm0_LowerCount();
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:core0_os_trace_info_task_time_begin                              */
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void core0_os_trace_task_time_begin(osu32_t thread_id)
{  
    if(thread_id < TRACE_MAX_THREAD_NUM)
	{
      /* <EVERY CORE> Record the timeslot before the task is executed */
      core0_os_trace_info[thread_id][REC_BEGIN_TIMESLOT] = core0_os_trace_time();

	  core0_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME] = 
	    core0_os_trace_info[thread_id][REC_BEGIN_TIMESLOT] - core0_os_thread_thread_timeslot;

	  if(core0_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME] >
	  	   core0_os_trace_info[thread_id][REC_MAX_SWITCHING_TIME])
	  {
        core0_os_trace_info[thread_id][REC_MAX_SWITCHING_TIME] =
		  core0_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME];	
	  }
	}
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:core0_os_trace_info_task_time_end                                */ 
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void core0_os_trace_task_time_end(osu32_t thread_id)
{ 
	if(thread_id < TRACE_MAX_THREAD_NUM)
	{
	  /* <EVERY CORE> Record the timeslot after the task is executed */
      core0_os_trace_info[thread_id][REC_END_TIMESLOT] = core0_os_trace_time(); 

      /* <EVERY CORE> Record the execution time of the current task, */
	  /* unit: 0.1 us in the current software configuration          */
      core0_os_trace_info[thread_id][REC_CURR_EXE_TIME] = 
        core0_os_trace_info[thread_id][REC_END_TIMESLOT] - 
          core0_os_trace_info[thread_id][REC_BEGIN_TIMESLOT];

	  /* <EVERY CORE> Record the max execution time of task          */
	  if(core0_os_trace_info[thread_id][REC_CURR_EXE_TIME] > 
		     core0_os_trace_info[thread_id][REC_MAX_EXE_TIME])
	  {
	    core0_os_trace_info[thread_id][REC_MAX_EXE_TIME] = 
	 	  core0_os_trace_info[thread_id][REC_CURR_EXE_TIME];
	  }
	}
}/* End of os_trace_task_time_end function  */

/****************************************************************************/
/* Function Definitions of core1 trace                                      */
/****************************************************************************/

/****************************************************************************/
/* FUNTION NAME:core1_os_trace_info_time                                         */
/* DESCRIPTION: Get time slot by call lowdriver API                         */
/****************************************************************************/
static osu32_t core1_os_trace_time(void)
{
    return (osu32_t)LowDriver_GetStm1_LowerCount();
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:core1_os_trace_info_task_time_begin                              */
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void core1_os_trace_task_time_begin(osu32_t thread_id)
{  
    if(thread_id < TRACE_MAX_THREAD_NUM)
	{
      /* <EVERY CORE> Record the timeslot before the task is executed */
      core1_os_trace_info[thread_id][REC_BEGIN_TIMESLOT] = core1_os_trace_time();

	  core1_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME] = 
	    core1_os_trace_info[thread_id][REC_BEGIN_TIMESLOT] - core1_os_thread_thread_timeslot;

	  if(core1_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME] >
	  	   core1_os_trace_info[thread_id][REC_MAX_SWITCHING_TIME])
	  {
        core1_os_trace_info[thread_id][REC_MAX_SWITCHING_TIME] =
		  core1_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME];	
	  }
	}
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:core1_os_trace_info_task_time_end                                */ 
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void core1_os_trace_task_time_end(osu32_t thread_id)
{ 
	if(thread_id < TRACE_MAX_THREAD_NUM)
	{
	  /* <EVERY CORE> Record the timeslot after the task is executed */
      core1_os_trace_info[thread_id][REC_END_TIMESLOT] = core1_os_trace_time(); 

      /* <EVERY CORE> Record the execution time of the current task, */
	  /* unit: 0.1 us in the current software configuration          */
      core1_os_trace_info[thread_id][REC_CURR_EXE_TIME] = 
        core1_os_trace_info[thread_id][REC_END_TIMESLOT] - 
          core1_os_trace_info[thread_id][REC_BEGIN_TIMESLOT];

	  /* <EVERY CORE> Record the max execution time of task          */
	  if(core1_os_trace_info[thread_id][REC_CURR_EXE_TIME] > 
		     core1_os_trace_info[thread_id][REC_MAX_EXE_TIME])
	  {
	    core1_os_trace_info[thread_id][REC_MAX_EXE_TIME] = 
	 	  core1_os_trace_info[thread_id][REC_CURR_EXE_TIME];
	  }
	}
}/* End of os_trace_task_time_end function  */

/****************************************************************************/
/* Function Definitions of core2 trace                                      */
/****************************************************************************/

/****************************************************************************/
/* FUNTION NAME:core2_os_trace_info_time                                         */
/* DESCRIPTION: Get time slot by call lowdriver API                         */
/****************************************************************************/
static osu32_t core2_os_trace_time(void)
{
    return (osu32_t)LowDriver_GetStm1_LowerCount();
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:core2_os_trace_info_task_time_begin                              */
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void core2_os_trace_task_time_begin(osu32_t thread_id)
{  
    if(thread_id < TRACE_MAX_THREAD_NUM)
	{
      /* <EVERY CORE> Record the timeslot before the task is executed */
      core2_os_trace_info[thread_id][REC_BEGIN_TIMESLOT] = core2_os_trace_time();

	  core2_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME] = 
	    core2_os_trace_info[thread_id][REC_BEGIN_TIMESLOT] - core2_os_thread_thread_timeslot;

	  if(core2_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME] >
	  	   core2_os_trace_info[thread_id][REC_MAX_SWITCHING_TIME])
	  {
        core2_os_trace_info[thread_id][REC_MAX_SWITCHING_TIME] =
		  core2_os_trace_info[thread_id][REC_CURR_SWITCHING_TIME];	
	  }
	}
} /* End of os_trace_time function  */

/****************************************************************************/
/* FUNTION NAME:core2_os_trace_info_task_time_end                                */ 
/* DESCRIPTION: Trace logic that is set up before each task in thread       */
/****************************************************************************/
void core2_os_trace_task_time_end(osu32_t thread_id)
{ 
	if(thread_id < TRACE_MAX_THREAD_NUM)
	{
	  /* <EVERY CORE> Record the timeslot after the task is executed */
      core2_os_trace_info[thread_id][REC_END_TIMESLOT] = core2_os_trace_time(); 

      /* <EVERY CORE> Record the execution time of the current task, */
	  /* unit: 0.1 us in the current software configuration          */
      core2_os_trace_info[thread_id][REC_CURR_EXE_TIME] = 
        core2_os_trace_info[thread_id][REC_END_TIMESLOT] - 
          core2_os_trace_info[thread_id][REC_BEGIN_TIMESLOT];

	  /* <EVERY CORE> Record the max execution time of task          */
	  if(core2_os_trace_info[thread_id][REC_CURR_EXE_TIME] > 
		     core2_os_trace_info[thread_id][REC_MAX_EXE_TIME])
	  {
	    core2_os_trace_info[thread_id][REC_MAX_EXE_TIME] = 
	 	  core2_os_trace_info[thread_id][REC_CURR_EXE_TIME];
	  }
	}
}/* End of os_trace_task_time_end function  */

