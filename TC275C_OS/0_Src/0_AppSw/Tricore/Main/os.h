/****************************************************************************/
/* FILE NAME:    os.h                                                       */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the type definition                    */
/*               core0 os                                                   */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_H_
#define OS_H_

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

/* <Function pointer><task_ptr_t> The type is used by thread creation API to*/
/* pass task address into thread and the encapsulated pthread_config_t * can*/
/* be pass to task                                                          */
typedef void (*task_ptr_t)(pthread_config_t * const pthread_config);

#endif /* End of OS_H_ */
