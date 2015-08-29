/**
 * \file IfxCcu6_cfg.h
 * \brief Ccu6 on-chip implementation data 
 * \ingroup IfxLld_Ccu6 
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

#ifndef IFXCCU6_CFG_H
#define IFXCCU6_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/Ifx_Types.h"
#include "_Reg/IfxCcu6_reg.h"
#include "_Reg/IfxCcu6_bf.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

#define IFXCCU6_NUM_MODULES (2)
                


/******************************************************************************/
/*-------------------------------Enumerations---------------------------------*/
/******************************************************************************/

typedef enum
{
    IfxCcu6_TrigOut_0 = IFX_CCU6_MOSEL_TRIG0SEL_OFF,  /**< \brief Output Trigger Select for CCU6061 TRIG0 */
    IfxCcu6_TrigOut_1 = IFX_CCU6_MOSEL_TRIG1SEL_OFF,  /**< \brief Output Trigger Select for CCU6061 TRIG1 */
    IfxCcu6_TrigOut_2 = IFX_CCU6_MOSEL_TRIG2SEL_OFF   /**< \brief Output Trigger Select for CCU6061 TRIG2 */
} IfxCcu6_TrigOut;

typedef enum
{
    IfxCcu6_TrigSel_cout63 = 0,  
    IfxCcu6_TrigSel_cc60 = 1,    
    IfxCcu6_TrigSel_cc61 = 1,    
    IfxCcu6_TrigSel_cc62 = 1,    
    IfxCcu6_TrigSel_sr1 = 2,     
    IfxCcu6_TrigSel_sr3 = 3      
} IfxCcu6_TrigSel;


/******************************************************************************/
/*-------------------Global Exported Variables/Constants----------------------*/
/******************************************************************************/

IFX_EXTERN const IfxModule_IndexMap IfxCcu6_indexMap[IFXCCU6_NUM_MODULES];


#endif /* IFXCCU6_CFG_H */
