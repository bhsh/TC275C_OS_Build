/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2010)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
**  FILENAME  : communication.c                                               **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
**                                                                            **
**  DATE      :                                                               **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  :                                                            **
**                                                                            **
**  SPECIFICATION(S) :                                                        **
**                                                                            **
*******************************************************************************/


#include "communication.h"
#include "Stddef.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"

communication mycommunicationCore0Core1_ptr;
communication* communicationCore0Core1_ptr=&mycommunicationCore0Core1_ptr;

const unsigned int core0ID = 0;
const unsigned int core1ID = 1;

int getCoreId()
{

	int coreId;
// get Core Id from CORE_ID Register
#ifndef GNU
	return __mfcr(0xFE1c);
#else
	asm ("mfcr %0, 0xFE1c":"=d"(coreId):);
#endif
	return coreId;
}
//extern static unsigned long requestLock(unsigned long* address, unsigned long mask);
//extern static void releaseLock(unsigned long* address, unsigned long mask);
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


// implement a barrier 
void synchronizeCore0Core1(void)
{
	if(getCoreId() == core0ID)
	{
		communicationCore0Core1_ptr->core0Ready=1;
		while (communicationCore0Core1_ptr->core1Ready!=1)
		{
			__nop();
		}
 		communicationCore0Core1_ptr->core0Ready=0;
	}
	else if(getCoreId() == core1ID)
	{
		communicationCore0Core1_ptr->core1Ready=1;
 		while (communicationCore0Core1_ptr->core0Ready!=1)
		{
			__nop();

		}
		communicationCore0Core1_ptr->core1Ready=0;
	}
}

