/*-----------------------------------------------------------------------------------
|
|   File name:    os_trace.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "os_kernel.h"
//#include "simio.h"
#include <stdio.h>
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"


#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

#include "os_trace.h"
/*-------------------------------------------------------------------------------------
|
|   Description:
|               OS_Measure_thread_Time
|
--------------------------------------------------------------------------------------*/
uint32 OS_Measure_thread_Time(void)
{
  return (uint32)(IfxStm_getLower(&MODULE_STM0)/100);
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               OS_Measure_thread_Time
|
--------------------------------------------------------------------------------------*/
uint32 Get_Free_Running_Timer_1usRes(void)
{
   return (uint32)(IfxStm_getLower(&MODULE_STM0)/100);
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               CalcUTIL_TimeDiffWord
|
--------------------------------------------------------------------------------------*/
static uint32 CalcUTIL_TimeDiffWord(uint32 LfUTIL_CurrentTime,
                                          uint32 LfUTIL_SavedTime)
{
    uint32 LfUTIL_DeltaTime;

    if (LfUTIL_CurrentTime > LfUTIL_SavedTime )
    {
        LfUTIL_DeltaTime = LfUTIL_CurrentTime - LfUTIL_SavedTime;
    }
    else
    {
        LfUTIL_DeltaTime = (0xffffffff - LfUTIL_SavedTime) + LfUTIL_CurrentTime + 1;
    }

    return LfUTIL_DeltaTime;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               OS_Measure_thread_Time
|
--------------------------------------------------------------------------------------*/
void EnterUTIL_TimeMeas( TsUTIL_ThruPutMeasurement *LpUTIL_MeasData )
{
   uint32 LfUTIL_t_PrevEnterTime = LpUTIL_MeasData->f_t_PrevEntryTime;
   uint32 LfUTIL_t_CurrEnterTime = Get_Free_Running_Timer_1usRes();
   uint32 LfUTIL_t_DeltaTime;

   LfUTIL_t_DeltaTime = CalcUTIL_TimeDiffWord(LfUTIL_t_CurrEnterTime,
                                              LfUTIL_t_PrevEnterTime);

   if (LpUTIL_MeasData->f_t_MaxDeltaTime == 0)
   {
       // This is to disregard the time from reset to the first Enter corrupting
       // the max delta time.
       LpUTIL_MeasData->f_t_MaxDeltaTime = 1;
   }
   else
   {
       if ( LfUTIL_t_DeltaTime > LpUTIL_MeasData->f_t_MaxDeltaTime )
       {
           LpUTIL_MeasData->f_t_MaxDeltaTime = LfUTIL_t_DeltaTime;
       }
   }

   LpUTIL_MeasData->f_t_CurrDeltaTime = LfUTIL_t_DeltaTime;

   if (LpUTIL_MeasData->f_t_AvgDeltaTime > LfUTIL_t_DeltaTime)
   {
      LpUTIL_MeasData->f_t_AvgDeltaTime -= ((LpUTIL_MeasData->f_t_AvgDeltaTime - LfUTIL_t_DeltaTime) >> 5);
   }
   else
   {
      LpUTIL_MeasData->f_t_AvgDeltaTime += ((LfUTIL_t_DeltaTime - LpUTIL_MeasData->f_t_AvgDeltaTime) >> 5);
   }

   LpUTIL_MeasData->f_t_PrevEntryTime = LfUTIL_t_CurrEnterTime;
}

/*-------------------------------------------------------------------------------------
|
|   Description:
|               OS_Measure_thread_Time
|
--------------------------------------------------------------------------------------*/
void ExitUTIL_TimeMeas( TsUTIL_ThruPutMeasurement *LpUTIL_MeasData )
{
   uint32 LfUTIL_t_EnterTime;
   uint32 LfUTIL_t_CurrTime;

   LfUTIL_t_EnterTime = LpUTIL_MeasData->f_t_PrevEntryTime;
   LfUTIL_t_CurrTime = CalcUTIL_TimeDiffWord(Get_Free_Running_Timer_1usRes(),
                                             LfUTIL_t_EnterTime);


   if ( LfUTIL_t_CurrTime > LpUTIL_MeasData->f_t_MaxExecTime )
   {
      LpUTIL_MeasData->f_t_MaxExecTime = LfUTIL_t_CurrTime;
   }

   LpUTIL_MeasData->f_t_CurrExecTime = LfUTIL_t_CurrTime;

   if (LpUTIL_MeasData->f_t_AvgExecTime > LfUTIL_t_CurrTime)
   {
      LpUTIL_MeasData->f_t_AvgExecTime -= ((LpUTIL_MeasData->f_t_AvgExecTime - LfUTIL_t_CurrTime) >> 2);
   }
   else if (LpUTIL_MeasData->f_t_AvgExecTime < LfUTIL_t_CurrTime)
   {
      LpUTIL_MeasData->f_t_AvgExecTime += ((LfUTIL_t_CurrTime - LpUTIL_MeasData->f_t_AvgExecTime) >> 2);
   }
}



void OS_test1(uint32 time)
{
   uint32 i,j,m;
   for(i=0;i<time;i++)
   {
       for(j=0;j<time;j++)
	   m=i+j;
   }	
}


