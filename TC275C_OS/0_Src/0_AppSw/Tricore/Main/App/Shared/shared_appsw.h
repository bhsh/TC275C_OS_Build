/****************************************************************************/
/* FILE NAME:    shared_appsw.h                                             */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes prototype definitions of shared APP    */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef SHARED_APPSW_H_
#define SHARED_APPSW_H_

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
extern void  App_shared_func_flash_led_1(void);
extern void  App_shared_func_flash_led_2(void);
extern void  App_shared_func_flash_led_3(void);
extern void  App_shared_func_flash_led_4(void);
extern void  App_shared_func_stack_calculated(unsigned int channel);
extern void  App_shared_func_stack_background_count(unsigned int channel);
extern void  App_shared_func_task_test_count(unsigned int current_core_id,unsigned int channel);
extern void  App_shared_func_trigger_software_interrupt1(void);
extern void  App_shared_func_test_count();
extern void  App_shared_func_one_stack_measured(unsigned int channel);

#endif /* End of SHARED_APPSW_H_ */

