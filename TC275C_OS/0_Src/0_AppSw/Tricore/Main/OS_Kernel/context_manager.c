/****************************************************************************/
/* FILE NAME:    context_manager.c                                          */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the logic of context manager           */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_type.h"
#include "low_driver_port.h"
#include "os_mode.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

#define  BYTES_IN_CONTEXT  64
#define  RATIO             1000

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum 
{
    CONTEXT_BGEGIN_ADDRESS,
    CONTEXT_END_ADDRESS,
    CONTEXT_CURR_FCX_ADDRESS,
    CONTEXT_SIZE_IN_BYTE,
    CONTEXT_SIZE_USED_IN_BYTE,
    CONTEXT_SIZE_IN_16WORD,
    CONTEXT_SIZE_USED_IN_16WORD,
    CONTEXT_SIZE_USED_IN_PERCENT,

	CONTEXT_MAX_ITEMS

} os_context_info_t; 

/****************************************************************************/
/* Static variables Definitions                                             */
/****************************************************************************/
static osu32_t core0_context_info[CONTEXT_MAX_ITEMS];
static osu32_t core1_context_info[CONTEXT_MAX_ITEMS];
static osu32_t core2_context_info[CONTEXT_MAX_ITEMS];

/****************************************************************************/
/* Function Definitions                                                     */
/****************************************************************************/

/****************************************************************************/
/* FUNTION NAME:initialize_core0_context_manager                            */
/* DESCRIPTION: Initialize the context manager of core0                     */
/****************************************************************************/
void initialize_core0_context_manager(void)
{
  core0_context_info[CONTEXT_BGEGIN_ADDRESS] = LowDriver_Get_Core0_Context_Begin_Addr(); 
  core0_context_info[CONTEXT_END_ADDRESS]    = LowDriver_Get_Core0_Context_End_Addr();

  core0_context_info[CONTEXT_SIZE_IN_BYTE]   = 
    core0_context_info[CONTEXT_END_ADDRESS] - core0_context_info[CONTEXT_BGEGIN_ADDRESS];
  
  core0_context_info[CONTEXT_SIZE_IN_16WORD] = 
  	core0_context_info[CONTEXT_SIZE_IN_BYTE]/BYTES_IN_CONTEXT;
}

/****************************************************************************/
/* FUNTION NAME:initialize_core1_context_manager                            */
/* DESCRIPTION: Initialize the context manager of core1                     */
/****************************************************************************/
void initialize_core1_context_manager(void)
{
  core1_context_info[CONTEXT_BGEGIN_ADDRESS] = LowDriver_Get_Core1_Context_Begin_Addr(); 
  core1_context_info[CONTEXT_END_ADDRESS]    = LowDriver_Get_Core1_Context_End_Addr();

  core1_context_info[CONTEXT_SIZE_IN_BYTE]   = 
  	core1_context_info[CONTEXT_END_ADDRESS] - core1_context_info[CONTEXT_BGEGIN_ADDRESS];
  
  core1_context_info[CONTEXT_SIZE_IN_16WORD] = 
  	core1_context_info[CONTEXT_SIZE_IN_BYTE]/BYTES_IN_CONTEXT;
}

/****************************************************************************/
/* FUNTION NAME:initialize_core2_context_manager                            */
/* DESCRIPTION: Initialize the context manager of core2                     */
/****************************************************************************/
void initialize_core2_context_manager(void)
{
  core2_context_info[CONTEXT_BGEGIN_ADDRESS] = LowDriver_Get_Core2_Context_Begin_Addr(); 
  core2_context_info[CONTEXT_END_ADDRESS]    = LowDriver_Get_Core2_Context_End_Addr();

  core2_context_info[CONTEXT_SIZE_IN_BYTE]   = 
  	core2_context_info[CONTEXT_END_ADDRESS] - core2_context_info[CONTEXT_BGEGIN_ADDRESS];
  
  core2_context_info[CONTEXT_SIZE_IN_16WORD] = 
  	core2_context_info[CONTEXT_SIZE_IN_BYTE]/BYTES_IN_CONTEXT;
}

/****************************************************************************/
/* FUNTION NAME:core0_get_context_status                                    */
/* DESCRIPTION: get the current context status of core0                     */
/****************************************************************************/
void core0_get_context_status(void)
{
  core0_context_info[CONTEXT_CURR_FCX_ADDRESS]     = LowDriver_Get_Fcx_Physical_Addr(); 
  
  core0_context_info[CONTEXT_SIZE_USED_IN_BYTE]    = 
  	core0_context_info[CONTEXT_END_ADDRESS] - core0_context_info[CONTEXT_CURR_FCX_ADDRESS];
  
  core0_context_info[CONTEXT_SIZE_USED_IN_16WORD]  = 
  	core0_context_info[CONTEXT_SIZE_USED_IN_BYTE]/BYTES_IN_CONTEXT;
  
  core0_context_info[CONTEXT_SIZE_USED_IN_PERCENT] = 
  	core0_context_info[CONTEXT_SIZE_USED_IN_16WORD]*RATIO/core0_context_info[CONTEXT_SIZE_IN_16WORD];
}

/****************************************************************************/
/* FUNTION NAME:core1_get_context_status                                    */
/* DESCRIPTION: get the current context status of core1                     */
/****************************************************************************/
void core1_get_context_status(void)
{
  core1_context_info[CONTEXT_CURR_FCX_ADDRESS]     = LowDriver_Get_Fcx_Physical_Addr(); 
  
  core1_context_info[CONTEXT_SIZE_USED_IN_BYTE]    = 
  	core1_context_info[CONTEXT_END_ADDRESS] - core1_context_info[CONTEXT_CURR_FCX_ADDRESS];
  
  core1_context_info[CONTEXT_SIZE_USED_IN_16WORD]  = 
  	core1_context_info[CONTEXT_SIZE_USED_IN_BYTE]/BYTES_IN_CONTEXT;
  
  core1_context_info[CONTEXT_SIZE_USED_IN_PERCENT] = 
  	core1_context_info[CONTEXT_SIZE_USED_IN_16WORD]*RATIO/core1_context_info[CONTEXT_SIZE_IN_16WORD];
}

/****************************************************************************/
/* FUNTION NAME:core2_get_context_status                                    */
/* DESCRIPTION: get the current context status of core2                     */
/****************************************************************************/
void core2_get_context_status(void)
{
  core2_context_info[CONTEXT_CURR_FCX_ADDRESS]     = LowDriver_Get_Fcx_Physical_Addr(); 
  
  core2_context_info[CONTEXT_SIZE_USED_IN_BYTE]    = 
  	core2_context_info[CONTEXT_END_ADDRESS] - core2_context_info[CONTEXT_CURR_FCX_ADDRESS];
  
  core2_context_info[CONTEXT_SIZE_USED_IN_16WORD]  = 
  	core2_context_info[CONTEXT_SIZE_USED_IN_BYTE]/BYTES_IN_CONTEXT;
  
  core2_context_info[CONTEXT_SIZE_USED_IN_PERCENT] = 
  	core2_context_info[CONTEXT_SIZE_USED_IN_16WORD]*RATIO/core2_context_info[CONTEXT_SIZE_IN_16WORD];
}


