#include "os_kernel.h"



typedef struct 
{
    uint32_t stack_init_address;
    uint32_t stack_current_address;
    uint32_t stack_used_size_byte;
	uint32_t stack_used_percent;
	
} pthread_stack_t; 



uint32_t get_stack_used_percent(uint32_t task_id, uint32_t pos);

