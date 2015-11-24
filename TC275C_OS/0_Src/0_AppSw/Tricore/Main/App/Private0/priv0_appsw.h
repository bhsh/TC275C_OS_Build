/****************************************************************************/
/* FILE NAME:    priv0_appsw.h                                              */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes prototype definitions of private0 APP  */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef PRIV0_APPSW_H_
#define PRIV0_APPSW_H_

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
extern void  App_priv0_func_test_count(void);
extern void  App_priv0_func_many_stacks_measured(void);
extern void  App_priv0_func_one_stack_measured(void);
extern void  App_priv0_func_task_test_count(unsigned int channel);
extern void  App_priv0_func_stack_background_count(void);
extern void  App_priv0_func_stack_calculated(void);


#endif /* End of PRIV0_APPSW_H_*/
