

#ifndef OS_H_
#define OS_H_

typedef struct {
    osu32_t core_id;
	osu32_t task_id;
    osu32_t type;
    osu32_t period;
    osu32_t actived_task_id;
    
} pthread_config_t;

typedef void (*task_ptr_t)(pthread_config_t * const pthread_config);

#endif
