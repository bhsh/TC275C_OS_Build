/****************************************************************************/
/* FILE NAME:    os_kernel_cfg.h                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes configuration parameter of os kernel   */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_KERNEL_CFG_H_
#define OS_KERNEL_CFG_H_

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_type.h"
#include "os.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* Configuration Definitions For Os Kernel                                  */
/****************************************************************************/
#define PTHREAD_PRIO_MAX 32               /* <EVERY CORE> Maximal priority thread level [0,31] */
#define PTHREAD_DEFAULT_STACK_SIZE 256/4  /* <EVERY CORE> Default stack size is 256 bytes */
#define PTHREAD_MEMORY_QUALIFIER          /* <EVERY CORE> None or global a8, a9 which are reserved for RTOS */
#define PTHREAD_DEFAULT_ATTR {SUPER, CALL_DEPTH_OVERFLOW_AT_64} /* <EVERY CORE> Default thread attributes: Supervisor mode, call depth = 64 */
#define PTHREAD_SWAP_HANDLER 0            /* <EVERY CORE> No swap handler installed */
#define PTHREAD_COND_TIMEDWAIT_SIZE 32    /* <EVERY CORE> Number of conditions that can wait for a period to be elapsed */
#define PTHREAD_USER_INT_LEVEL 13         /* Maximal interrupt level for routines that are managed by the library */

#define USHRT_MAX 0xFFFF

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define CPU_PCXI    0xFE00  /* <EVERY CORE> FE00,PCXI, Previous Context Information Register */
#define CPU_PSW     0xFE04  /* <EVERY CORE> FE04,PSW, Program Status Word                    */
#define CPU_FCX     0xFE38  /* <EVERY CORE> FE38,FCX, Free CSA List Head Pointer             */
#define CPU_ICR     0xFE2C  /* <EVERY CORE> FE2C,ICR, Interrupt Control Register             */
#define CPU_CORE_ID 0xFE1C  /* <EVERY CORE> FE1C,CORE_ID, CORE ID                            */

#define VECTOR_TABLE0  0    /* The vector table of core 0 is used */
#define VECTOR_TABLE1  1    /* The vector table of core 1 is used */
#define VECTOR_TABLE2  2    /* The vector table of core 2 is used */

#define CORE0_KERNEL_SOFT_INT_LEVEL  9
#define CORE1_KERNEL_SOFT_INT_LEVEL  8
#define CORE2_KERNEL_SOFT_INT_LEVEL  7

#define CORE0_KERNEL_TICK_INT_LEVEL  10
#define CORE1_KERNEL_TICK_INT_LEVEL  11
#define CORE2_KERNEL_TICK_INT_LEVEL  12

#endif /* OS_KERNEL_CFG_H_ */
