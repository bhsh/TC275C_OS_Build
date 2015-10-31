

#ifndef OS_H_
#define OS_H_

typedef struct {
    const osu32_t curr_task_core_id;
	const osu32_t curr_task_id;
    osu32_t       curr_task_type;
    osu32_t       curr_task_period;
    const osu32_t curr_task_order_num;
    osu32_t       actived_task_core_id;
	osu32_t       actived_task_id;
    
} pthread_config_t;

typedef void (*task_ptr_t)(pthread_config_t * const pthread_config);

#endif
