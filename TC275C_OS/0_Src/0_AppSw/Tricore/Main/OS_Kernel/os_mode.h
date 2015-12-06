/****************************************************************************/
/* FILE NAME:    os_mode.h                                                  */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes mode selection of stack                */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_MODE_H_
#define OS_MODE_H_

/****************************************************************************/
/* MACRO DEFINITION                                                         */
/****************************************************************************/

/****************************************************************************/
/* MODE                                                                     */
/****************************************************************************/
/* STACK MODE DEFINITION */
#define MANY_STACKS        0
#define ONE_STACK          1

/* MEASURE MODE DEFINITION */
#define STACK_CONTEXT_MEASURE      0
#define CPULOAD_MEASURE            1

/****************************************************************************/
/* STATIC MODE SELECTION                                                    */
/****************************************************************************/
//#define OS_STACK_MODE     MANY_STACKS
#define OS_STACK_MODE    ONE_STACK

/****************************************************************************/
/* MEASURE MODE SELECTION                                                   */
/****************************************************************************/
#define MEASURE_MODE     STACK_CONTEXT_MEASURE
//#define MEASURE_MODE     CPULOAD_MEASURE

/****************************************************************************/
/* MEASURE SWITCH                                                           */
/****************************************************************************/
#if(MEASURE_MODE == STACK_CONTEXT_MEASURE)
  #define STACKS_MEASURE_SWITCH   ON
  #define CONTEXT_MEASURE_SWITCH  ON
#else
  #define CPULOAD_MEASURE_SWITCH  ON
#endif

/****************************************************************************/
/* TRACE SWITCH                                                             */
/****************************************************************************/
#define TRACE_MEASURE_SWITCH      ON

/****************************************************************************/
/* Compiler error                                                           */
/****************************************************************************/
#if((OS_STACK_MODE != MANY_STACKS)&&(OS_STACK_MODE != ONE_STACK))
  #error " One of the stack modes should be selected for OS_STACK_MODE in os_mode.h"
#endif
#ifndef OS_STACK_MODE
  #define OS_STACK_MODE MANY_STACKS
#endif

#endif /* End of OS_MODE_H_ */
