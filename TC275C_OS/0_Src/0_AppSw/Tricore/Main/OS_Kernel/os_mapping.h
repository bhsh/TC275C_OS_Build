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
#define  PTHREAD_OBTAIN_TIMESLOT_CALLBACK(current_core_id) \
	             os_trace_thread_timeslot(current_core_id);

#define  os_kernel_update_core0_tick()  LowDriver_Update_CORE0_OS_Tick()
#define  os_kernel_update_core1_tick()  LowDriver_Update_CORE1_OS_Tick()
#define  os_kernel_update_core2_tick()  LowDriver_Update_CORE2_OS_Tick()

#define  CORE0_INITIALIZE_OS_TICK_BLOCK()   LowDriver_Initialize_CORE0_OS_Tick();
#define  CORE1_INITIALIZE_OS_TICK_BLOCK()   LowDriver_Initialize_CORE1_OS_Tick();
#define  CORE2_INITIALIZE_OS_TICK_BLOCK()   LowDriver_Initialize_CORE2_OS_Tick(); 

#define  CORE0_INITIALIZE_CONTEXT_MANAGER()  initialize_core0_context_manager(); 
#define  CORE1_INITIALIZE_CONTEXT_MANAGER()  initialize_core1_context_manager(); 
#define  CORE2_INITIALIZE_CONTEXT_MANAGER()  initialize_core2_context_manager(); 

#if (OS_STACK_MODE == MANY_STACKS)
  #define  CORE0_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num,stack_end_address,stack_size) \
	         initialize_core0_many_stacks_memory(thread_order_num,stack_end_address,stack_size); 
  #define  CORE1_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num,stack_end_address,stack_size) \
	         initialize_core1_many_stacks_memory(thread_order_num,stack_end_address,stack_size);   
  #define  CORE2_INITIALIZE_MANY_STACKS_MEMORY(thread_order_num,stack_end_address,stack_size) \
	         initialize_core2_many_stacks_memory(thread_order_num,stack_end_address,stack_size);     
#else 
  #define  CORE0_INITIALIZE_ONE_STACK_MEMORY(stack_end_address,stack_size) \
	         initialize_core0_one_stack_memory(stack_end_address,stack_size); 
  #define  CORE1_INITIALIZE_ONE_STACK_MEMORY(stack_end_address,stack_size) \
	         initialize_core1_one_stack_memory(stack_end_address,stack_size); 
  #define  CORE2_INITIALIZE_ONE_STACK_MEMORY(stack_end_address,stack_size) \
	         initialize_core2_one_stack_memory(stack_end_address,stack_size); 
#endif

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
#if (OS_STACK_MODE == MANY_STACKS)
  extern void initialize_core0_many_stacks_memory(osu32_t,osu32_t*,osu32_t);
  extern void initialize_core1_many_stacks_memory(osu32_t,osu32_t*,osu32_t);
  extern void initialize_core2_many_stacks_memory(osu32_t,osu32_t*,osu32_t);

#else
  extern void initialize_core0_one_stack_memory(osu32_t*,osu32_t);
  extern void initialize_core1_one_stack_memory(osu32_t*,osu32_t);
  extern void initialize_core2_one_stack_memory(osu32_t*,osu32_t);

#endif

extern void initialize_core0_context_manager(void);
extern void initialize_core1_context_manager(void);
extern void initialize_core2_context_manager(void);

#endif /* End of OS_MAPPING_H_ */
