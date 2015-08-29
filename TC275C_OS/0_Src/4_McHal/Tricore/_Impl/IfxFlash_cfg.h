/**
 * \file IfxFlash_cfg.h
 * \brief Flash on-chip implementation data
 * \ingroup IfxLld_Flash
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

#ifndef IFXFLASH_CFG_H
#define IFXFLASH_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/IfxCpu_Intrinsics.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief base address for general command sequences
 */
#define IFXFLASH_CMD_BASE_ADDRESS                        (0xaf000000)

/** \brief number of flash modules
 */
#define IFXFLASH_NUM_FLASH_MODULES                       (1)

#define IFXFLASH_PFLASH_BANKS                            (2)

/** \brief
 */
#define IFXFLASH_PFLASH_NUM_LOG_SECTORS                  (IFXFLASH_PFLASH_BANKS * 27)

#define IFXFLASH_PFLASH_NUM_PHYSICAL_SECTORS             (IFXFLASH_PFLASH_BANKS * 4)

#define IFXFLASH_PFLASH_PAGE_LENGTH                      (32)

/** \brief Phy sector for DF
 */
#define IFXFLASH_DFLASH_NUM_PHYSICAL_SECTORS             (1)

#define IFXFLASH_DFLASH_NUM_LOG_SECTORS                  (48)

#define IFXFLASH_DFLASH_START                            (0xaf000000)

#define IFXFLASH_DFLASH_SIZE                             (IFXFLASH_DFLASH_NUM_LOG_SECTORS * 0x2000)

#define IFXFLASH_DFLASH_END                              (IFXFLASH_DFLASH_START + IFXFLASH_DFLASH_SIZE - 1)

#define IFXFLASH_DFLASH_NUM_HSM_LOG_SECTORS              (8)

#define IFXFLASH_DFLASH_NUM_UCB_LOG_SECTORS              (16)

#define IFXFLASH_DFLASH_BANKS                            (1)

#define IFXFLASH_DFLASH_PAGE_LENGTH                      (8)

#define IFXFLASH_ERROR_TRACKING_MAX_CORRECTABLE_ERRORS   (10)

#define IFXFLASH_ERROR_TRACKING_MAX_UNCORRECTABLE_ERRORS (1)

/******************************************************************************/
/*-------------------------------Enumerations---------------------------------*/
/******************************************************************************/

typedef enum
{
    IfxFlash_FlashType_Fa = 0,  /**< \brief Flash Array */
    IfxFlash_FlashType_D0 = 1,  /**< \brief data flash #0 */
    IfxFlash_FlashType_D1 = 2,  /**< \brief data flash #1 */
    IfxFlash_FlashType_P0 = 3,  /**< \brief program flash #0 */
    IfxFlash_FlashType_P1 = 4,  /**< \brief program flash #1 */
    IfxFlash_FlashType_P2 = 5,  /**< \brief program flash #2 */
    IfxFlash_FlashType_P3 = 6,  /**< \brief program flash #3 */
} IfxFlash_FlashType;

/** \brief user configuration block type
 */
typedef enum
{
    IfxFlash_UcbType_ucb0    = 0,  /**< \brief UCB 0 */
    IfxFlash_UcbType_ucb1    = 1,  /**< \brief UCB 1 */
    IfxFlash_UcbType_ucbHsmc = 5,  /**< \brief HSM UCB */
} IfxFlash_UcbType;

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \brief contains start and end address of sectors
 */
typedef struct
{
    uint32 start;     /**< \brief start address of sector */
    uint32 end;       /**< \brief end address of sector */
} IfxFlash_flashSector;

/******************************************************************************/
/*-------------------Global Exported Variables/Constants----------------------*/
/******************************************************************************/

IFX_EXTERN const IfxFlash_flashSector IfxFlash_dFlashTableEepLog[IFXFLASH_DFLASH_NUM_LOG_SECTORS];

IFX_EXTERN const IfxFlash_flashSector IfxFlash_dFlashTableHsmLog[IFXFLASH_DFLASH_NUM_HSM_LOG_SECTORS];

IFX_EXTERN const IfxFlash_flashSector IfxFlash_dFlashTablePhys[IFXFLASH_DFLASH_NUM_PHYSICAL_SECTORS];

IFX_EXTERN const IfxFlash_flashSector IfxFlash_dFlashTableUcbLog[IFXFLASH_DFLASH_NUM_UCB_LOG_SECTORS];

IFX_EXTERN const IfxFlash_flashSector IfxFlash_pFlashTableLog[IFXFLASH_PFLASH_NUM_LOG_SECTORS];

IFX_EXTERN const IfxFlash_flashSector IfxFlash_pFlashTablePhys[IFXFLASH_PFLASH_NUM_PHYSICAL_SECTORS];

#endif /* IFXFLASH_CFG_H */
