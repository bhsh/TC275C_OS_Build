/****************************************************************************/
/* FILE NAME:    kernel_callback_mapping.h                                  */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes macro definitions and extern statements*/
/*               that are intended to mapping the upper logic into os kernel*/
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef KERNEL_CALLBACK_MAPPING_H_ 
#define KERNEL_CALLBACK_MAPPING_H_

#define  PTHREAD_OBTAIN_INIT_STACK_ADD_CALLBACK(core_id,thread_id,init_sp_address) \
	             get_thread_init_stack_address(core_id,thread_id,init_sp_address);

#define  PTHREAD_OBTAIN_TIMESLOT_CALLBACK(current_core_id,thread_id) \
	             os_trace_thread_timeslot(current_core_id,thread_id)

#define  os_kernel_update_core0_tick()  LowDriver_Update_Core0_Tick()
#define  os_kernel_update_core1_tick()  LowDriver_Update_Core1_Tick()
#define  os_kernel_update_core2_tick()  LowDriver_Update_Core2_Tick()

extern void get_thread_init_stack_address(osu32_t,osu32_t,osu32_t);
extern void os_trace_thread_timeslot(osu32_t ,osu32_t);

#endif /* End of KERNEL_CALLBACK_MAPPING_H_ */
