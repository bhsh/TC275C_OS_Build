/****************************************************************************/
/* FILE NAME:    private1appsw.c                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes prototype definitions of private1 APP  */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "low_driver_port.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile unsigned int App_priv1_var_test_count;

/****************************************************************************/
/* Private1 Function Definitions                                            */
/****************************************************************************/
void  App_priv1_func_test_count(void)
{
   App_priv1_var_test_count ++;
}