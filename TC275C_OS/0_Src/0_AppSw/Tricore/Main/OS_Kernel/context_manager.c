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
#define  RATIO             1000
#define  BYTES_IN_CONTEXT  64
#define  WORDS_IN_CONTEXT  16

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
/* FUNTION NAME:clear_context_section                                       */
/* DESCRIPTION: clear the context into 0                                    */
/****************************************************************************/
inline void clear_context_section(osu32_t* context_begine_addr,osu32_t* fcx_phy_addr)
{
  osu32_t   context_index;  
  osu32_t   word_index;
  osu32_t   context_num_not_used;
  osu32_t*  context_offset_addr;
  osu32_t*  word_offset_addr;

  context_offset_addr  = context_begine_addr;
  word_offset_addr     = context_offset_addr;
  context_num_not_used = 1 + ((osu32_t)fcx_phy_addr - (osu32_t)context_begine_addr)/WORDS_IN_CONTEXT;

  for(context_index = 0; context_index < context_num_not_used; context_index++)
  {
    for(word_index = 1;word_index < WORDS_IN_CONTEXT ;word_index++)
	{
      *(word_offset_addr + word_index) = 0x0; 
	}

	/* Increase the offset address of context to next 16 word*/
	context_offset_addr += WORDS_IN_CONTEXT;
	word_offset_addr     = context_offset_addr;
  }
}

/****************************************************************************/
/* FUNTION NAME:clear_context_section                                       */
/* DESCRIPTION: clear the context into 0                                    */
/****************************************************************************/
inline osu32_t get_context_last_used_addr(osu32_t* context_begine_addr,osu32_t context_size_in_size)
{
  osu32_t*  context_offset_addr;
  osu32_t   delta_context_size;
  osu32_t   return_address;
  
  context_offset_addr  = context_begine_addr;
  while((*context_offset_addr++ == 0x0)||
  	     ((osu32_t)context_offset_addr%WORDS_IN_CONTEXT == 0))
  {
  }

  delta_context_size =((osu32_t)context_offset_addr - (osu32_t)context_begine_addr);

  if(delta_context_size > context_size_in_size)
  {  
  	return_address = 0xFFFFFFFF;
  }
  else
  {
    return_address = (osu32_t)context_offset_addr;
  }
  return return_address;
}

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

  core0_context_info[CONTEXT_CURR_FCX_ADDRESS]  = LowDriver_Get_Fcx_Physical_Addr(); 
  clear_context_section((osu32_t*)core0_context_info[CONTEXT_BGEGIN_ADDRESS],
  	                    (osu32_t*)core0_context_info[CONTEXT_CURR_FCX_ADDRESS]);
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

  core1_context_info[CONTEXT_CURR_FCX_ADDRESS]  = LowDriver_Get_Fcx_Physical_Addr(); 
  clear_context_section((osu32_t*)core1_context_info[CONTEXT_BGEGIN_ADDRESS],
  	                    (osu32_t*)core1_context_info[CONTEXT_CURR_FCX_ADDRESS]);
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

  core2_context_info[CONTEXT_CURR_FCX_ADDRESS]  = LowDriver_Get_Fcx_Physical_Addr(); 
  clear_context_section((osu32_t*)core2_context_info[CONTEXT_BGEGIN_ADDRESS],
  	                    (osu32_t*)core2_context_info[CONTEXT_CURR_FCX_ADDRESS]);
}

/****************************************************************************/
/* FUNTION NAME:core0_get_context_usage                                     */
/* DESCRIPTION: get the current context status of core0                     */
/****************************************************************************/
void core0_get_context_usage(void)
{  
  core0_context_info[CONTEXT_SIZE_USED_IN_BYTE]    = 
  	core0_context_info[CONTEXT_END_ADDRESS] - get_context_last_used_addr((osu32_t*)core0_context_info[CONTEXT_BGEGIN_ADDRESS],
  	                                                                     core0_context_info[CONTEXT_SIZE_IN_BYTE]); 
  core0_context_info[CONTEXT_SIZE_USED_IN_16WORD]  = 
  	core0_context_info[CONTEXT_SIZE_USED_IN_BYTE]/BYTES_IN_CONTEXT;
  
  core0_context_info[CONTEXT_SIZE_USED_IN_PERCENT] = 
  	core0_context_info[CONTEXT_SIZE_USED_IN_16WORD]*RATIO/core0_context_info[CONTEXT_SIZE_IN_16WORD];
    
}

/****************************************************************************/
/* FUNTION NAME:core1_get_context_usage                                     */
/* DESCRIPTION: get the current context status of core1                     */
/****************************************************************************/
void core1_get_context_usage(void)
{
  core1_context_info[CONTEXT_SIZE_USED_IN_BYTE]    = 
  	core1_context_info[CONTEXT_END_ADDRESS] - get_context_last_used_addr((osu32_t*)core1_context_info[CONTEXT_BGEGIN_ADDRESS],
  	                                                                     core1_context_info[CONTEXT_SIZE_IN_BYTE]); 
  core1_context_info[CONTEXT_SIZE_USED_IN_16WORD]  = 
  	core1_context_info[CONTEXT_SIZE_USED_IN_BYTE]/BYTES_IN_CONTEXT;
  
  core1_context_info[CONTEXT_SIZE_USED_IN_PERCENT] = 
  	core1_context_info[CONTEXT_SIZE_USED_IN_16WORD]*RATIO/core1_context_info[CONTEXT_SIZE_IN_16WORD];
}

/****************************************************************************/
/* FUNTION NAME:core2_get_context_usage                                     */
/* DESCRIPTION: get the current context status of core2                     */
/****************************************************************************/
void core2_get_context_usage(void)
{
  core2_context_info[CONTEXT_SIZE_USED_IN_BYTE]    = 
  	core2_context_info[CONTEXT_END_ADDRESS] - get_context_last_used_addr((osu32_t*)core2_context_info[CONTEXT_BGEGIN_ADDRESS],
  	                                                                     core2_context_info[CONTEXT_SIZE_IN_BYTE]); 
  core2_context_info[CONTEXT_SIZE_USED_IN_16WORD]  = 
  	core2_context_info[CONTEXT_SIZE_USED_IN_BYTE]/BYTES_IN_CONTEXT;
  
  core2_context_info[CONTEXT_SIZE_USED_IN_PERCENT] = 
  	core2_context_info[CONTEXT_SIZE_USED_IN_16WORD]*RATIO/core2_context_info[CONTEXT_SIZE_IN_16WORD];
}


