/*
 * os_kernel_cfg.h
 *
 *  Created on: Aug 26, 2015
 *      Author: tz68d9
 */

#ifndef OS_KERNEL_CFG_H_
#define OS_KERNEL_CFG_H_


#define PTHREAD_PRIO_MAX 32               //!< Maximal priority thread level [0,31]
#define PTHREAD_DEFAULT_STACK_SIZE 256/4  //!< Default stack size is 256 bytes
#define PTHREAD_MEMORY_QUALIFIER          //!< None or global a8, a9 which are reserved for RTOS
#define PTHREAD_DEFAULT_ATTR {SUPER, CALL_DEPTH_OVERFLOW_AT_64} //!< Default thread attributes: Supervisor mode, call depth = 64, default stack size
#define PTHREAD_SWAP_HANDLER 0            //!< 0 = no swap handler installed
#define PTHREAD_COND_TIMEDWAIT_SIZE 32    //!< Number of conditions that can wait for a period to be elapsed
#define PTHREAD_USER_INT_LEVEL 13         //!< Maximal interrupt level for routines that are managed by the library

typedef unsigned int   uint32_t;    // 4 byte unsigned; prefix: uw
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;

#define USHRT_MAX 0xffff

/** \\brief  FE00, , type: Ifx_CPU_PCXI, Previous Context Information Register */
#define CPU_PCXI 0xFE00
/** \\brief  FE04, , type: Ifx_CPU_PSW, Program Status Word */
#define CPU_PSW 0xFE04
/** \\brief  FE38, , type: Ifx_CPU_FCX, Free CSA List Head Pointer */
#define CPU_FCX 0xFE38
/** \\brief  FE2C, , type: Ifx_CPU_ICR, Interrupt Control Register */
#define CPU_ICR 0xFE2C

#define CPU_CORE_ID 0xFE1C

#define false 0
#define true  1



//#define PCXI	0xfe00	/* Previous Context Information Register  */
//#define NULL (void*)0
#define assert(_expr)  \
    ((void) (!(_expr) ? __debug(): (void) 0))

/*! Return current process priority number
 \return current priority process number
 */
inline uint32_t cppn(void) {
    return __extru(__mfcr(CPU_ICR), 0, 8);
}

#endif /* OS_KERNEL_CFG_H_ */
