/**
 * \file IfxCpu_Trap.c
 * \brief This file contains the APIs for Trap related functions.
 *
 *
 * \version iLLD_1_0_0_4_0
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IfxCpu_Trap.h"
#include "Cpu/Std/IfxCpu.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxCpu_reg.h"
#include "Ifx_Cfg.h"
#ifdef IFX_CFG_EXTEND_TRAP_HOOKS
#include "Ifx_Cfg_Trap.h"
#endif

/******************************************************************************/
/*                           Macros                                           */
/******************************************************************************/
/** \brief Configuration for CpuX enable.
 *
 */
#ifndef IFX_CFG_CPU_TRAP_TSR_HOOK
#   define IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch)          /**< By default macro is empty*/
#endif
#ifndef IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK
#   define IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK(trapWatch) /**< By default macro is empty*/
#endif
#ifndef IFX_CFG_CPU_TRAP_SYSCALL_CPU1_HOOK
#   define IFX_CFG_CPU_TRAP_SYSCALL_CPU1_HOOK(trapWatch) /**< By default macro is empty*/
#endif
#ifndef IFX_CFG_CPU_TRAP_SYSCALL_CPU2_HOOK
#   define IFX_CFG_CPU_TRAP_SYSCALL_CPU2_HOOK(trapWatch) /**< By default macro is empty*/
#endif
#ifndef IFX_CFG_CPU_TRAP_SYSCALL_CPU3_HOOK
#   define IFX_CFG_CPU_TRAP_SYSCALL_CPU3_HOOK(trapWatch) /**< By default macro is empty*/
#endif
#ifndef IFX_CFG_CPU_TRAP_SYSCALL_CPU4_HOOK
#   define IFX_CFG_CPU_TRAP_SYSCALL_CPU4_HOOK(trapWatch) /**< By default macro is empty*/
#endif
#ifndef IFX_CFG_CPU_TRAP_SYSCALL_CPU5_HOOK
#   define IFX_CFG_CPU_TRAP_SYSCALL_CPU5_HOOK(trapWatch) /**< By default macro is empty*/
#endif

/*******************************************************************************
**                      variables                                     **
*******************************************************************************/
IfxCpu_Trap trapWatch;

/*******************************************************************************
**                      Function definitions                          **
*******************************************************************************/
IFX_INLINE IfxCpu_Trap IfxCpu_Trap_extractTrapInfo(uint8 trapClass, uint32 tin)
{
    IfxCpu_Trap trapInfo;
    trapInfo.tAddr  = (unsigned int)__getA11();
    trapInfo.tClass = trapClass;
    trapInfo.tId    = tin;
    trapInfo.tCpu   = IfxCpu_getCoreId();
    return trapInfo;
}


void IfxCpu_Trap_memoryManagementError(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_memoryManagement, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}


void IfxCpu_Trap_internalProtectionError(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_internalProtection, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}


void IfxCpu_Trap_instructionError(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_instructionErrors, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}


void IfxCpu_Trap_contextManagementError(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_contextManagement, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}


void IfxCpu_Trap_busError(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_bus, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}


void IfxCpu_Trap_assertion(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_assertion, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}

uint32 core0_trap_count_test;
/* The trap is used for the OS of core0 */
void IfxCpu_Trap_systemCall_Cpu0(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK(trapWatch);
	
	/* Add the kernel of OS */
	/* Kernel begins        */
	core0_trap_count_test++;
	/* Kernel ends          */	
    __asm("rfe");
}


void IfxCpu_Trap_systemCall_Cpu1(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    IFX_CFG_CPU_TRAP_SYSCALL_CPU1_HOOK(trapWatch);
    __asm("rfe");
}


void IfxCpu_Trap_systemCall_Cpu2(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    IFX_CFG_CPU_TRAP_SYSCALL_CPU2_HOOK(trapWatch);
    __asm("rfe");
}


void IfxCpu_Trap_systemCall_Cpu3(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    IFX_CFG_CPU_TRAP_SYSCALL_CPU3_HOOK(trapWatch);
    __asm("rfe");
}


void IfxCpu_Trap_systemCall_Cpu4(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    IFX_CFG_CPU_TRAP_SYSCALL_CPU4_HOOK(trapWatch);
    __asm("rfe");
}


void IfxCpu_Trap_systemCall_Cpu5(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_systemCall, tin);
    IFX_CFG_CPU_TRAP_SYSCALL_CPU5_HOOK(trapWatch);
    __asm("rfe");
}


void IfxCpu_Trap_nonMaskableInterrupt(uint32 tin)
{
    trapWatch = IfxCpu_Trap_extractTrapInfo(IfxCpu_Trap_Class_nonMaskableInterrupt, tin);
    IFX_CFG_CPU_TRAP_TSR_HOOK(trapWatch);
    __debug();
    __asm("rfe");
}


#if defined(__GNUC__)
#pragma section
#pragma section ".traptab_cpu0" awx
#endif
#if defined(__DCC__)
#pragma section
#pragma section CODE ".traptab_cpu0" X
#endif
#if defined(__TASKING__)
#pragma protect on
#pragma section code "traptab_cpu0"
#endif

void IfxCpu_Trap_vectorTable0(void)
{
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_memoryManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_internalProtectionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_instructionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_contextManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_busError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_assertion);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_systemCall_Cpu0);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_nonMaskableInterrupt);
}


#if IFXCPU_NUM_MODULES >= 2
#if defined(__GNUC__)
#pragma section
#pragma section ".traptab_cpu1" awx
#endif
#if defined(__DCC__)
#pragma section
#pragma section CODE ".traptab_cpu1" X
#endif
#if defined(__TASKING__)
#pragma section code "traptab_cpu1"
#endif

void IfxCpu_Trap_vectorTable1(void)
{
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_memoryManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_internalProtectionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_instructionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_contextManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_busError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_assertion);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_systemCall_Cpu1);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_nonMaskableInterrupt);
}


#endif

#if IFXCPU_NUM_MODULES >= 3
#if defined(__GNUC__)
#pragma section
#pragma section ".traptab_cpu2" awx
#endif
#if defined(__DCC__)
#pragma section
#pragma section CODE ".traptab_cpu2" X
#endif
#if defined(__TASKING__)
#pragma section code "traptab_cpu2"
#endif

void IfxCpu_Trap_vectorTable2(void)
{
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_memoryManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_internalProtectionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_instructionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_contextManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_busError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_assertion);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_systemCall_Cpu2);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_nonMaskableInterrupt);
}


#endif

#if IFXCPU_NUM_MODULES >= 4
#if defined(__GNUC__)
#pragma section
#pragma section ".traptab_cpu3" awx
#endif
#if defined(__DCC__)
#pragma section
#pragma section CODE ".traptab_cpu3" X
#endif
#if defined(__TASKING__)
#pragma section code "traptab_cpu3"
#endif

void IfxCpu_Trap_vectorTable3(void)
{
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_memoryManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_internalProtectionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_instructionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_contextManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_busError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_assertion);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_systemCall_Cpu3);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_nonMaskableInterrupt);
}


#endif

#if IFXCPU_NUM_MODULES >= 5
#if defined(__GNUC__)
#pragma section
#pragma section ".traptab_cpu4" awx
#endif
#if defined(__DCC__)
#pragma section
#pragma section CODE ".traptab_cpu4" X
#endif
#if defined(__TASKING__)
#pragma section code "traptab_cpu4"
#endif

void IfxCpu_Trap_vectorTable4(void)
{
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_memoryManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_internalProtectionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_instructionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_contextManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_busError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_assertion);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_systemCall_Cpu4);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_nonMaskableInterrupt);
}


#endif

#if IFXCPU_NUM_MODULES >= 6
#if defined(__GNUC__)
#pragma section
#pragma section ".traptab_cpu5" awx
#endif
#if defined(__DCC__)
#pragma section
#pragma section CODE ".traptab_cpu5" X
#endif
#if defined(__TASKING__)
#pragma section code "traptab_cpu5"
#endif

void IfxCpu_Trap_vectorTable5(void)
{
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_memoryManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_internalProtectionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_instructionError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_contextManagementError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_busError);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_assertion);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_systemCall_Cpu5);
    IfxCpu_Tsr_CallTSR(IfxCpu_Trap_nonMaskableInterrupt);
}


#endif

#if defined(__GNUC__)
#pragma section
#endif
#if defined(__DCC__)
#pragma section
#endif
#if defined(__DCC__)
#pragma interrupt IfxInterruptEx
#endif
#if defined(__TASKING__)
#pragma endprotect
#endif
