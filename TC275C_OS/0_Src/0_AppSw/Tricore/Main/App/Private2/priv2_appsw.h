/****************************************************************************/
/* FILE NAME:    priv2_appsw.h                                              */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes prototype definitions of private2 APP  */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef PRIV2_APPSW_H_
#define PRIV2_APPSW_H_

/****************************************************************************/
/* Function Prototype Definitions                                           */
/****************************************************************************/
extern void  App_priv2_func_test_count(void);
extern void  App_priv2_func_many_stacks_measured(void);
extern void  App_priv2_func_one_stack_measured(void);
extern void  App_priv2_func_task_test_count(unsigned int channel);
extern void  App_priv2_func_cpuload_bkg_count(void);
extern void  App_priv2_func_cpuload_calculated(void);
extern void  App_priv2_func_get_context_status(void);

#endif /* End of PRIV2_APPSW_H_*/