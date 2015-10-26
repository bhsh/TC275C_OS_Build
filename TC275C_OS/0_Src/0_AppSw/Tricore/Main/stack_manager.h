#include "os.h"



typedef struct 
{
    osu32_t stack_init_address;
    osu32_t stack_current_address;
    osu32_t stack_used_size_byte;
	osu32_t stack_used_percent;
	
} pthread_stack_t; 



osu32_t get_stack_used_percent(osu32_t task_id, osu32_t pos);

