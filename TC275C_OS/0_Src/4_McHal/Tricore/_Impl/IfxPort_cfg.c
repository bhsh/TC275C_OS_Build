/**
 * \file IfxPort_cfg.c
 * \brief Port on-chip implementation data
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
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxPort_cfg.h"

/******************************************************************************/
/*-----------------------Exported Variables/Constants-------------------------*/
/******************************************************************************/

const IfxPort_Esr_Masks  IfxPort_cfg_esrMasks[IFXPORT_NUM_MODULES] = {
    {&MODULE_P00, 0x0000FFFFUL},    // Port 00
    {&MODULE_P01, 0x0000FFFFUL},    // Port 01
    {&MODULE_P02, 0x0000FFFFUL},    // Port 02
    {&MODULE_P10, 0x0000FFFFUL},    // Port 10
    {&MODULE_P11, 0x0000FFFFUL},    // Port 11
    {&MODULE_P12, 0x0000FFFFUL},    // Port 12
    {&MODULE_P13, 0x0000FFFFUL},    // Port 13
    {&MODULE_P14, 0x0000FFFFUL},    // Port 14
    {&MODULE_P15, 0x0000FFFFUL},    // Port 15
    {&MODULE_P20, 0x0000FFFFUL},    // Port 20
    {&MODULE_P21, 0x0000FFFFUL},    // Port 21
    {&MODULE_P22, 0x0000FFFFUL},    // Port 22
    {&MODULE_P23, 0x0000FFFFUL},    // Port 23
    {&MODULE_P32, 0x0000FFFFUL},    // Port 32
    {&MODULE_P33, 0x0000FFFFUL},    // Port 33
    {&MODULE_P34, 0x0000FFFFUL}     // Port 34
    //{&MODULE_P40, 0x0000FFFFUL}   // Port 40
};

const IfxModule_IndexMap IfxPort_cfg_indexMap[IFXPORT_NUM_MODULES] = {
    {&MODULE_P00, 0 },     // Port 00
    {&MODULE_P01, 1 },     // Port 01
    {&MODULE_P02, 2 },     // Port 02
    {&MODULE_P10, 10},     // Port 10
    {&MODULE_P11, 11},     // Port 11
    {&MODULE_P12, 12},     // Port 12
    {&MODULE_P13, 13},     // Port 13
    {&MODULE_P14, 14},     // Port 14
    {&MODULE_P15, 15},     // Port 15
    {&MODULE_P20, 20},     // Port 20
    {&MODULE_P21, 21},     // Port 21
    {&MODULE_P22, 22},     // Port 22
    {&MODULE_P23, 23},     // Port 23
    {&MODULE_P32, 32},     // Port 32
    {&MODULE_P33, 33},     // Port 33
    {&MODULE_P34, 34}      // Port 34
    //{&MODULE_P40, 40}    // Port 40
};
