/****************************************************************************/
/* FILE NAME:    priv0_appsw.c                                              */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the task definitions of AURIX core0    */
/*               os                                                         */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#include "os_type.h"
#include "os.h"
#include "shared_appsw.h"
#include "priv0_appsw.h"
#include "os_task.h"

/****************************************************************************/
/* <CORE0> Macro Definitions                                                */
/****************************************************************************/

/****************************************************************************/
/* <CORE0> Task Definitions                                                 */
/****************************************************************************/

/****************************************************************************/
/* <CORE0> task0 is an idle task in default and the the config parameters   */
/*         of the task should not be changed                                */
/*         The task is usually used to:                                     */
/*              1. Monitor CPU Load                                         */
/*              2. Manage the memory                                        */ 
/*              3. Monitor the usage of stack                               */
/*              4. Other background task                                    */
/****************************************************************************/
volatile int test0 = 0;
volatile int test1 = 0;
volatile int test2 = 0;
volatile int test3 = 0;
OS_CORE0_TASK(0)
{ 
  /* There is a counter associated with task and increasing in by one when the task is entered */
  App_priv0_func_task_test_count(CURR_TASK_ID);

  /* There are two background tasks:1,stack measure;2,cpu load measure */
#if(MEASURE_MODE == CPULOAD_MEASURE)
  #if(CPULOAD_MEASURE_SWITCH == ON)
    App_priv0_func_cpuload_bkg_count();
  #endif
#else
  #if(STACKS_MEASURE_SWITCH == ON)
	#if (OS_STACK_MODE == MANY_STACKS)
	  /* Many threads are measured */
	  App_priv0_func_many_stacks_measured();
	#else
	  /* Measure the usage of stack ,there is not any measure taken when the stack has overflown */
	  /* Here,the is only one stack for all threads */
	  App_priv0_func_one_stack_measured();
	#endif
  #endif
  #if(CONTEXT_MEASURE_SWITCH == ON)
    App_priv0_func_get_context_usage();
  #endif
#endif
  App_priv0_func_test_count();
}

/****************************************************************************/
/* <CORE0>  The following is app tasks                                      */   
/****************************************************************************/
OS_CORE0_TASK(1)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
 // App_shared_func_flash_led_1();

}
OS_CORE0_TASK(2)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  //App_shared_func_flash_led_2();
  test0++;
}
OS_CORE0_TASK(3)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  test1++;
}
OS_CORE0_TASK(4)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  test2++;
}
OS_CORE0_TASK(5)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
}
OS_CORE0_TASK(6)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
}
OS_CORE0_TASK(7)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
}
OS_CORE0_TASK(8)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
}
OS_CORE0_TASK(9)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  //App_shared_func_flash_led_3();
}
OS_CORE0_TASK(10)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  test3++;
  //App_shared_func_trigger_software_interrupt7();
  
#if (MEASURE_MODE == CPULOAD_MEASURE)
  #if(CPULOAD_MEASURE_SWITCH == ON)
    App_priv0_func_cpuload_calculated();
  #endif
#endif

  //App_shared_func_flash_led_4();
}
OS_CORE0_TASK(11){}
OS_CORE0_TASK(12){}
OS_CORE0_TASK(13){}
OS_CORE0_TASK(14){}
OS_CORE0_TASK(15){}
OS_CORE0_TASK(16){}
OS_CORE0_TASK(17){}
OS_CORE0_TASK(18){}
OS_CORE0_TASK(19){}
OS_CORE0_TASK(20){}
OS_CORE0_TASK(21){}
OS_CORE0_TASK(22){}
OS_CORE0_TASK(23){}
OS_CORE0_TASK(24){}
OS_CORE0_TASK(25){}
OS_CORE0_TASK(26){}
OS_CORE0_TASK(27){}
OS_CORE0_TASK(28){}
OS_CORE0_TASK(29){}
OS_CORE0_TASK(30){}
OS_CORE0_TASK(31){}
OS_CORE0_TASK(32){}
OS_CORE0_TASK(33){}
OS_CORE0_TASK(34){}
OS_CORE0_TASK(35){}
OS_CORE0_TASK(36){}
OS_CORE0_TASK(37){}
OS_CORE0_TASK(38){}
OS_CORE0_TASK(39){}
OS_CORE0_TASK(40){}
OS_CORE0_TASK(41){}
OS_CORE0_TASK(42){}
OS_CORE0_TASK(43){}
OS_CORE0_TASK(44){}
OS_CORE0_TASK(45){}
OS_CORE0_TASK(46){}
OS_CORE0_TASK(47){}
OS_CORE0_TASK(48){}
OS_CORE0_TASK(49){}
OS_CORE0_TASK(50){}
OS_CORE0_TASK(51){}
OS_CORE0_TASK(52){}
OS_CORE0_TASK(53){}
OS_CORE0_TASK(54){}
OS_CORE0_TASK(55){}
OS_CORE0_TASK(56){}
OS_CORE0_TASK(57){}
OS_CORE0_TASK(58){}
OS_CORE0_TASK(59){}
OS_CORE0_TASK(60){}
OS_CORE0_TASK(61){}
OS_CORE0_TASK(62){}
OS_CORE0_TASK(63){}
OS_CORE0_TASK(64){}
OS_CORE0_TASK(65){}
OS_CORE0_TASK(66){}
OS_CORE0_TASK(67){}
OS_CORE0_TASK(68){}
OS_CORE0_TASK(69){}
OS_CORE0_TASK(70){}
OS_CORE0_TASK(71){}
OS_CORE0_TASK(72){}
OS_CORE0_TASK(73){}
OS_CORE0_TASK(74){}
OS_CORE0_TASK(75){}
OS_CORE0_TASK(76){}
OS_CORE0_TASK(77){}
OS_CORE0_TASK(78){}
OS_CORE0_TASK(79){}
OS_CORE0_TASK(80){}
OS_CORE0_TASK(81){}
OS_CORE0_TASK(82){}
OS_CORE0_TASK(83){}
OS_CORE0_TASK(84){}
OS_CORE0_TASK(85){}
OS_CORE0_TASK(86){}
OS_CORE0_TASK(87){}
OS_CORE0_TASK(88){}
OS_CORE0_TASK(89){}
OS_CORE0_TASK(90){}
OS_CORE0_TASK(91){}
OS_CORE0_TASK(92){}
OS_CORE0_TASK(93){}
OS_CORE0_TASK(94){}
OS_CORE0_TASK(95){}
OS_CORE0_TASK(96){}
OS_CORE0_TASK(97){}
OS_CORE0_TASK(98){}
OS_CORE0_TASK(99){}
OS_CORE0_TASK(100){}
