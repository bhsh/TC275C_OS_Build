/***************************************************************
 *                                                             *
 *   Filename:       communication.h                           *
 *                                                             *
 *   Author(s):      Jens Harnisch                             *
 *   Copyright:      Infineon Technologies AG, 2008            * 
 *   Created:        September 2008                            *
 *                                                             *
 *   Purpose:        examples for dual core communication      *
 *                                                             *
 *   Content:                                                  *
 *                                                             *
 *                                                             *
 ***************************************************************/
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>

#define LOCKED 1
#define UNLOCKED 0


void synchronizeCore0Core1(void); 
unsigned int getCoreID(void);
extern const unsigned int core0ID;
extern const unsigned int core1ID;
//static inline unsigned long requestLock(unsigned long* address, unsigned long mask) __attribute__((always_inline));
//static inline void releaseLock(unsigned long* address, unsigned long mask) __attribute__ ((always_inline));

#define PATTERN1 0x01234567

typedef struct _communication
{
	unsigned int sharedMemory;
	unsigned int semaphore; 
	unsigned int core1Ready;
	unsigned int core0Ready;
} communication;

extern communication* communicationCore0Core1_ptr;

#if 0
static inline  unsigned long requestLock(unsigned long* address, unsigned long mask)
{
	unsigned long long result = mask | (unsigned long long)mask << 32;
	__asm__ volatile( "swapmsk.w [%1] 0,%A0"
	: "+d" (result)
	: "a" (address)
	: "memory");
	return (unsigned long)result & mask;
}


static inline void releaseLock(unsigned long* address, unsigned long mask)
{
	unsigned long long result = ~mask | (unsigned long long)mask << 32;
	__asm__ volatile (
	"swapmsk.w [%1] 0,%A0"
	: "+d" (result)
	: "a" (address)
	: "memory");
}
#endif


#endif
