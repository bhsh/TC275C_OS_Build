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
/* STACK MODE                                                               */
/****************************************************************************/
#define MANY_STACKS  0
#define ONE_STACK    1

/****************************************************************************/
/* MODE SELECTION                                                           */
/****************************************************************************/
//#define OS_STACK_MODE     MANY_STACKS
#define OS_STACK_MODE    ONE_STACK

#endif /* End of OS_MODE_H_ */