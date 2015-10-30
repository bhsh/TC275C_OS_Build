

#ifndef KERNEL_CALLBACK_MAPPING_H_ 
#define KERNEL_CALLBACK_MAPPING_H_


#define  PTHREAD_OBTAIN_INIT_STACK_ADD_CALLBACK(core_id,thread_id,init_sp_address) \
	             get_thread_init_stack_address(core_id,thread_id,init_sp_address);

extern void get_thread_init_stack_address(osu32_t,osu32_t,osu32_t);

#endif /* End of KERNEL_CALLBACK_MAPPING_H_ */
