/*-----------------------------------------------------------------------------------
|
|   File name:    os_trace.h
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#ifndef OS_TRACE_H_
#define OS_TRACE_H_

#include "os_type.h"

#define TRACE_STATUS       ENABLE

extern void OS_test1(osu32_t time);
extern void os_trace_task_time_begin(osu32_t current_core_id,osu32_t thread_id);
extern void os_trace_task_time_end(osu32_t current_core_id,osu32_t thread_id);

#endif
