/****************************************************************************/
/* FILE NAME:    os_mapping.h                                               */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes macro definitions and extern statements*/
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_MAPPING_H_
#define OS_MAPPING_H_

/****************************************************************************/
/* Macro Definitons                                                         */
/****************************************************************************/
#define  PTHREAD_OBTAIN_INIT_STACK_ADD_CALLBACK(core_id,thread_id,init_sp_address) \
	             get_thread_init_stack_address(core_id,thread_id,init_sp_address);

#define  PTHREAD_OBTAIN_TIMESLOT_CALLBACK(current_core_id) \
	             os_trace_thread_timeslot(current_core_id);

#define  os_kernel_update_core0_tick()  LowDriver_Update_CORE0_OS_Tick()
#define  os_kernel_update_core1_tick()  LowDriver_Update_CORE1_OS_Tick()
#define  os_kernel_update_core2_tick()  LowDriver_Update_CORE2_OS_Tick()

#define  CORE0_INITIALIZE_OS_TICK_BLOCK()   LowDriver_Initialize_CORE0_OS_Tick();
#define  CORE1_INITIALIZE_OS_TICK_BLOCK()   LowDriver_Initialize_CORE1_OS_Tick();
#define  CORE2_INITIALIZE_OS_TICK_BLOCK()   LowDriver_Initialize_CORE2_OS_Tick(); 

#define  CORE0_INITIALIZE_OS_STACK_MEASURE(stack_end_address,stack_size) \
	       initialize_stack_memory(0,stack_end_address,stack_size); 
#define  CORE1_INITIALIZE_OS_STACK_MEASURE(stack_end_address,stack_size) \
	       initialize_stack_memory(1,stack_end_address,stack_size); 
#define  CORE2_INITIALIZE_OS_STACK_MEASURE(stack_end_address,stack_size) \
	       initialize_stack_memory(2,stack_end_address,stack_size); 

#define  CORE0_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num,stack_end_address,stack_size) \
	       initialize_core0_many_stacks_memory(thread_order_num,stack_end_address,stack_size); 

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
extern void get_thread_init_stack_address(osu32_t,osu32_t,osu32_t);
extern void initialize_stack_memory(osu32_t core_id,osu32_t* stack_end_address,osu32_t stack_size);
extern void initialize_core0_many_stacks_memory(osu32_t thread_order_num,osu32_t* stack_end_address,osu32_t stack_size);


#endif /* End of OS_MAPPING_H_ */
