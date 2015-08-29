/**
 * \file IfxEmem_cfg.h
 * \brief Emem on-chip implementation data 
 * \ingroup IfxLld_Emem 
 *
 * \version iLLD_1_0_0_4_0
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
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
 */

#ifndef IFXEMEM_CFG_H
#define IFXEMEM_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/Ifx_Types.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

#define IFXEMEM_START_ADDR_CPU_CACHED 0x9F000000UL
                
#define IFXEMEM_START_ADDR_CPU 0xBF000000UL
                
#define IFXEMEM_START_ADDR_BBB (0xAF000000UL)
                
#define IFXEMEM_SIZE (0x100000UL)
                

#endif /* IFXEMEM_CFG_H */
