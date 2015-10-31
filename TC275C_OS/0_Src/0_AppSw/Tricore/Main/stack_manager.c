/****************************************************************************/
/* FILE NAME:    stack_manager.c                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes logic that tests the stack usage of    */
/*               tasks                                                      */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#include "os_type.h"
#include "os_interface.h"

#define TIME_UNIT_SWITCH            (1000)
#define STACK_MEA_MAX_POS_NUM       (10)
#define PTHREAD_STACK_SIZE_IN_BYTE  (256)

#define STACK_MEA_MAX_CORE_NUM      (3)
#define STACK_MEA_MAX_THREAD_NUM    (11)

typedef struct 
{
    osu32_t stack_init_address;
    osu32_t stack_current_address;
    osu32_t stack_used_size_byte;
	osu32_t stack_used_percent;
	
} pthread_stack_t; 

static pthread_stack_t pthread_stack[STACK_MEA_MAX_CORE_NUM][STACK_MEA_MAX_THREAD_NUM][STACK_MEA_MAX_POS_NUM];

osu32_t get_stack_used_percent(osu32_t thread_id, osu32_t pos)
{
	osu32_t current_cpu_id = LowDriver_Get_Curr_Core_ID();

	pthread_stack[current_cpu_id][thread_id][pos].stack_current_address = LowDriver_GetUstack_Address();

	pthread_stack[current_cpu_id][thread_id][pos].stack_used_size_byte = 
		    pthread_stack[current_cpu_id][thread_id][pos].stack_init_address -
                         pthread_stack[current_cpu_id][thread_id][pos].stack_current_address;

	pthread_stack[current_cpu_id][thread_id][pos].stack_used_percent =
            (pthread_stack[current_cpu_id][thread_id][pos].stack_used_size_byte*TIME_UNIT_SWITCH)/PTHREAD_STACK_SIZE_IN_BYTE;

	return pthread_stack[current_cpu_id][thread_id][pos].stack_used_percent;
}

void get_thread_init_stack_address(osu32_t core_id,osu32_t thread_id,osu32_t init_sp_address)
{  
   osu32_t index;
   
   if(thread_id < STACK_MEA_MAX_THREAD_NUM)
   {
     for(index = 0 ; index < STACK_MEA_MAX_POS_NUM ; index++ )
     {
       pthread_stack[core_id][thread_id][index].stack_init_address = init_sp_address;
     }
   }
}

