
#include "os_type.h"
#include "os_interface.h"

#define STACK_MAX_MEASURE_POS         (10)
#define TIME_UNIT_SWITCH              (1000)
#define PTHREAD_STACK_SIZE_IN_BYTE    (256)

#define MAX_CORE_NUM    (3)
#define MAX_THREAD_NUM  (11)

typedef struct 
{
    osu32_t stack_init_address;
    osu32_t stack_current_address;
    osu32_t stack_used_size_byte;
	osu32_t stack_used_percent;
	
} pthread_stack_t; 

static pthread_stack_t pthread_stack[MAX_CORE_NUM][MAX_THREAD_NUM][STACK_MAX_MEASURE_POS];

osu32_t get_stack_used_percent(osu32_t thread_id, osu32_t pos)
{
	osu32_t current_cpu_id = os_get_curr_coreid();

	pthread_stack[current_cpu_id][thread_id][pos].stack_current_address = os_getUstack_address();

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
   
   for(index = 0 ; index < STACK_MAX_MEASURE_POS ; index++ )
   {
     pthread_stack[core_id][thread_id][index].stack_init_address = init_sp_address;
   }
}

