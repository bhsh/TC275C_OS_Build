/*-----------------------------------------------------------------------------------
|
|   File name:    os_interface.h
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#include "os_type.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"

inline osu32_t os_getUstack_address(void)
{ 
   return (unsigned int)__getUstack();
}
extern void os_wait_in_us(osu32_t time);
extern osu32_t os_getstmlower_count(void);