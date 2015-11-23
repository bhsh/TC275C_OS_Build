/****************************************************************************/
/* FILE NAME:    os.h                                                       */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the type definition  of the interface  */
/*               between thread and task                                    */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_H_
#define OS_H_

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define USER_CFG task_cfg_t task_cfg
#define OS_CORE0_TASK(task_num) void CORE0_TASK##task_num(USER_CFG)
#define OS_CORE1_TASK(task_num) void CORE1_TASK##task_num(USER_CFG)
#define OS_CORE2_TASK(task_num) void CORE2_TASK##task_num(USER_CFG)

#define CURR_CORE_ID          task_cfg->curr_task_core_id
#define CURR_TASK_ID          task_cfg->curr_task_id
#define CURR_TASK_TYPE        task_cfg->curr_task_type
#define CURR_TASK_PERIOD      task_cfg->curr_task_period
#define CURR_TASK_ORDER_NUM   task_cfg->curr_task_order_num
#define ACTIVED_CORE_ID       task_cfg->actived_task_core_id
#define ACTIVED_TASK_ID       task_cfg->actived_task_id

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/

/* <struct><pthread_config_t> The type is used by task and thread manager to*/
/* read information from thread and control thread configuration            */
typedef struct {  
    const osu32_t curr_task_core_id;
	const osu32_t curr_task_id;
    osu32_t       curr_task_type;
    osu32_t       curr_task_period;
    const osu32_t curr_task_order_num;
    osu32_t       actived_task_core_id;
	osu32_t       actived_task_id;
    
} pthread_config_t;

/* <typedef pthread_config_t* task_cfg_t><pthread_config_t> The type is used*/
/* by interface the thread type to task type for user                       */
typedef pthread_config_t* task_cfg_t;

/* <Function pointer><task_ptr_t> The type is used by thread creation API to*/
/* pass task address into thread and the encapsulated pthread_config_t * can*/
/* be pass to task                                                          */
typedef void (*task_ptr_t)(pthread_config_t * pthread_config);

#endif /* End of OS_H_ */
