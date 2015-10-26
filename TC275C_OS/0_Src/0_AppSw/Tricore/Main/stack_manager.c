



#include "stack_manager.h"
#include <stdlib.h>
//#include "simio.h"
#include <stdio.h>
#include "SysSe/Bsp/Bsp.h"
//#include "DemoApp.h"
#include "communication.h"


#include "Compilers.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include "Src\Std\IfxSrc.h"

#define MAX_POS_NUM           10
#define MAX_THREAD_NUM        11
#define MAX_CORE_NUM          3 

static pthread_stack_t pthread_stack[MAX_CORE_NUM][MAX_THREAD_NUM][MAX_POS_NUM];

uint32_t get_stack_used_percent(uint32_t thread_id, uint32_t pos)
{
	uint32_t current_cpu_id = os_getCoreId();

	pthread_stack[current_cpu_id][thread_id][pos].stack_current_address = (unsigned int)__getUstack();

	pthread_stack[current_cpu_id][thread_id][pos].stack_used_size_byte = 
		    pthread_stack[current_cpu_id][thread_id][pos].stack_init_address -
                         pthread_stack[current_cpu_id][thread_id][pos].stack_current_address;

	pthread_stack[current_cpu_id][thread_id][pos].stack_used_percent =
            (pthread_stack[current_cpu_id][thread_id][pos].stack_used_size_byte*1000)/256;

	return pthread_stack[current_cpu_id][thread_id][pos].stack_used_percent;
}

void get_thread_init_stack_address(uint32_t core_id,uint32_t thread_id,uint32_t init_sp_address)
{  
   uint32_t index;
   
   for(index = 0 ; index < MAX_POS_NUM ; index++ )
   {
     pthread_stack[core_id][thread_id][index].stack_init_address = init_sp_address;
   }
}

