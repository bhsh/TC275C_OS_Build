

#include "stack_manager.h"
#include "os_interface.h"


#define MAX_POS_NUM           10
#define MAX_THREAD_NUM        11
#define MAX_CORE_NUM          3 

static pthread_stack_t pthread_stack[MAX_CORE_NUM][MAX_THREAD_NUM][MAX_POS_NUM];

osu32_t get_stack_used_percent(osu32_t thread_id, osu32_t pos)
{
	osu32_t current_cpu_id = os_getCoreId();

	pthread_stack[current_cpu_id][thread_id][pos].stack_current_address = os_getUstack_address();

	pthread_stack[current_cpu_id][thread_id][pos].stack_used_size_byte = 
		    pthread_stack[current_cpu_id][thread_id][pos].stack_init_address -
                         pthread_stack[current_cpu_id][thread_id][pos].stack_current_address;

	pthread_stack[current_cpu_id][thread_id][pos].stack_used_percent =
            (pthread_stack[current_cpu_id][thread_id][pos].stack_used_size_byte*1000)/256;

	return pthread_stack[current_cpu_id][thread_id][pos].stack_used_percent;
}

void get_thread_init_stack_address(osu32_t core_id,osu32_t thread_id,osu32_t init_sp_address)
{  
   osu32_t index;
   
   for(index = 0 ; index < MAX_POS_NUM ; index++ )
   {
     pthread_stack[core_id][thread_id][index].stack_init_address = init_sp_address;
   }
}

