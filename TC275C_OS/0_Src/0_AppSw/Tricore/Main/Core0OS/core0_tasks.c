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
static volatile int core0_test0 = 0;
static volatile int core0_test1 = 0;
static volatile int core0_test2 = 0;
static volatile int core0_test3 = 0;
static volatile int core0_test4 = 0;
static volatile int core0_test5 = 0;
static volatile int core0_test6 = 0;
static volatile int core0_test7 = 0;
static volatile int core0_test8 = 0;
static volatile int core0_test9 = 0;
static volatile int core0_test10 = 0;
static volatile int core0_test11 = 0;
static volatile int core0_test12 = 0;
static volatile int core0_test13 = 0;
static volatile int core0_test14 = 0;
static volatile int core0_test15 = 0;
static volatile int core0_test16 = 0;
static volatile int core0_test17 = 0;
static volatile int core0_test18 = 0;
static volatile int core0_test19 = 0;
static volatile int core0_test20 = 0;
static volatile int core0_test21 = 0;
static volatile int core0_test22 = 0;
static volatile int core0_test23 = 0;
static volatile int core0_test24 = 0;
static volatile int core0_test25 = 0;
static volatile int core0_test26 = 0;
static volatile int core0_test27 = 0;
static volatile int core0_test28 = 0;
static volatile int core0_test29 = 0;
static volatile int core0_test30 = 0;
static volatile int core0_test31 = 0;
static volatile int core0_test32 = 0;
static volatile int core0_test33 = 0;
static volatile int core0_test34 = 0;
static volatile int core0_test35 = 0;
static volatile int core0_test36 = 0;
static volatile int core0_test37 = 0;
static volatile int core0_test38 = 0;
static volatile int core0_test39 = 0;
static volatile int core0_test40 = 0;
static volatile int core0_test41 = 0;
static volatile int core0_test42 = 0;
static volatile int core0_test43 = 0;
static volatile int core0_test44 = 0;
static volatile int core0_test45 = 0;
static volatile int core0_test46 = 0;
static volatile int core0_test47 = 0;
static volatile int core0_test48 = 0;
static volatile int core0_test49 = 0;
static volatile int core0_test50 = 0;
static volatile int core0_test51 = 0;
static volatile int core0_test52 = 0;
static volatile int core0_test53 = 0;
static volatile int core0_test54 = 0;
static volatile int core0_test55 = 0;
static volatile int core0_test56 = 0;
static volatile int core0_test57 = 0;
static volatile int core0_test58 = 0;
static volatile int core0_test59 = 0;
static volatile int core0_test60 = 0;
static volatile int core0_test61 = 0;
static volatile int core0_test62 = 0;
static volatile int core0_test63 = 0;
static volatile int core0_test64 = 0;
static volatile int core0_test65 = 0;
static volatile int core0_test66 = 0;
static volatile int core0_test67 = 0;
static volatile int core0_test68 = 0;
static volatile int core0_test69 = 0;
static volatile int core0_test70 = 0;
static volatile int core0_test71 = 0;
static volatile int core0_test72 = 0;
static volatile int core0_test73 = 0;
static volatile int core0_test74 = 0;
static volatile int core0_test75 = 0;
static volatile int core0_test76 = 0;
static volatile int core0_test77 = 0;
static volatile int core0_test78 = 0;
static volatile int core0_test79 = 0;
static volatile int core0_test80 = 0;
static volatile int core0_test81 = 0;
static volatile int core0_test82 = 0;
static volatile int core0_test83 = 0;
static volatile int core0_test84 = 0;
static volatile int core0_test85 = 0;
static volatile int core0_test86 = 0;
static volatile int core0_test87 = 0;
static volatile int core0_test88 = 0;
static volatile int core0_test89 = 0;
static volatile int core0_test90 = 0;
static volatile int core0_test91 = 0;
static volatile int core0_test92 = 0;
static volatile int core0_test93 = 0;
static volatile int core0_test94 = 0;
static volatile int core0_test95 = 0;
static volatile int core0_test96 = 0;
static volatile int core0_test97 = 0;
static volatile int core0_test98 = 0;
static volatile int core0_test99 = 0;
static volatile int core0_test100 = 0;
static volatile int core0_init_count  = 0;
static volatile int core0_end_count   = 0;
static volatile int core0_delta_count = 0;
OS_CORE0_TASK(0)
{ 
  /* There is a counter associated with task and increasing in by one when the task is entered */
 // App_priv0_func_task_test_count(CURR_TASK_ID);

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
  core0_test0++;
}

/****************************************************************************/
/* <CORE0>  The following is app tasks                                      */   
/****************************************************************************/
OS_CORE0_TASK(1)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
 // App_shared_func_flash_led_1();
  core0_test1++;
}
OS_CORE0_TASK(2)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  //App_shared_func_flash_led_2();
  core0_test2++;
  core0_init_count = Task_Obtain_OS_Tick(0);

#if (MEASURE_MODE == CPULOAD_MEASURE)
  #if(CPULOAD_MEASURE_SWITCH == ON)
    App_priv0_func_cpuload_calculated();
  #endif
#endif
}
OS_CORE0_TASK(3)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test3++;
}
OS_CORE0_TASK(4)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test4++;
}
OS_CORE0_TASK(5)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test5++;
}
OS_CORE0_TASK(6)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test6++;
}
OS_CORE0_TASK(7)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test7++;
}
OS_CORE0_TASK(8)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test8++;
}
OS_CORE0_TASK(9)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  //App_shared_func_flash_led_3();
  core0_test9++;
}
OS_CORE0_TASK(10)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test3++;
  //App_shared_func_trigger_software_interrupt7();

  //App_shared_func_flash_led_4();
  core0_test10++;
}
OS_CORE0_TASK(11)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test11++;
}
OS_CORE0_TASK(12)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test12++;
}
OS_CORE0_TASK(13)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test13++;
}
OS_CORE0_TASK(14)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test14++;
}
OS_CORE0_TASK(15)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test15++;
}
OS_CORE0_TASK(16)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test16++;
}
OS_CORE0_TASK(17)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test17++;
}
OS_CORE0_TASK(18)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test18++;
}
OS_CORE0_TASK(19)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test19++;
}
OS_CORE0_TASK(20)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test20++;
}
OS_CORE0_TASK(21)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test21++;
}
OS_CORE0_TASK(22)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test22++;
}
OS_CORE0_TASK(23)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test23++;
}
OS_CORE0_TASK(24)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test24++;
}
OS_CORE0_TASK(25)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test25++;
}
OS_CORE0_TASK(26)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test26++;
}
OS_CORE0_TASK(27)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test27++;
}
OS_CORE0_TASK(28)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test28++;
}
OS_CORE0_TASK(29)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test29++;
}
OS_CORE0_TASK(30)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test30++;
}
OS_CORE0_TASK(31)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test31++;
}
OS_CORE0_TASK(32)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test32++;
}
OS_CORE0_TASK(33)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test33++;
}
OS_CORE0_TASK(34)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test34++;
}
OS_CORE0_TASK(35)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test35++;
}
OS_CORE0_TASK(36)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test36++;
}
OS_CORE0_TASK(37)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test37++;
}
OS_CORE0_TASK(38)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test38++;
}
OS_CORE0_TASK(39)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test39++;
}
OS_CORE0_TASK(40)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test40++;
}
OS_CORE0_TASK(41)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test41++;
}
OS_CORE0_TASK(42)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test42++;
}
OS_CORE0_TASK(43)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test43++;
}
OS_CORE0_TASK(44)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test44++;
}
OS_CORE0_TASK(45)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test45++;
}
OS_CORE0_TASK(46)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test46++;
}
OS_CORE0_TASK(47)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test47++;
}
OS_CORE0_TASK(48)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test48++;
}
OS_CORE0_TASK(49)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test49++;
}
OS_CORE0_TASK(50)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test50++;
}
OS_CORE0_TASK(51)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test51++;
}
OS_CORE0_TASK(52)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test52++;
}
OS_CORE0_TASK(53)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test53++;
}
OS_CORE0_TASK(54)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test54++;
}
OS_CORE0_TASK(55)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test55++;
}
OS_CORE0_TASK(56)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test56++;
}
OS_CORE0_TASK(57)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test57++;
}
OS_CORE0_TASK(58)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test58++;
}
OS_CORE0_TASK(59)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test59++;
}
OS_CORE0_TASK(60)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test60++;
}
OS_CORE0_TASK(61)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test61++;
}
OS_CORE0_TASK(62)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test62++;
}
OS_CORE0_TASK(63)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test63++;
}
OS_CORE0_TASK(64)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test64++;
}
OS_CORE0_TASK(65)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test65++;
}
OS_CORE0_TASK(66)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test66++;
}
OS_CORE0_TASK(67)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test67++;
}
OS_CORE0_TASK(68)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test68++;
}
OS_CORE0_TASK(69)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test69++;
}
OS_CORE0_TASK(70)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test70++;
}
OS_CORE0_TASK(71)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test71++;
}
OS_CORE0_TASK(72)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test72++;
}
OS_CORE0_TASK(73)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test73++;
}
OS_CORE0_TASK(74)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test74++;
}
OS_CORE0_TASK(75)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test75++;
}
OS_CORE0_TASK(76)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test76++;
}
OS_CORE0_TASK(77)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test77++;
}
OS_CORE0_TASK(78)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test78++;
}
OS_CORE0_TASK(79)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test79++;
}
OS_CORE0_TASK(80)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test80++;
}
OS_CORE0_TASK(81)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test81++;
}
OS_CORE0_TASK(82)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test82++;
}
OS_CORE0_TASK(83)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test83++;
}
OS_CORE0_TASK(84)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test84++;
}
OS_CORE0_TASK(85)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test85++;
}
OS_CORE0_TASK(86)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test86++;
}
OS_CORE0_TASK(87)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test87++;
}
OS_CORE0_TASK(88)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test88++;
}
OS_CORE0_TASK(89)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test89++;
}
OS_CORE0_TASK(90)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test90++;
}
OS_CORE0_TASK(91)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test91++;
}
OS_CORE0_TASK(92)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test92++;
}
OS_CORE0_TASK(93)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test93++;
}
OS_CORE0_TASK(94)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test94++;
}
OS_CORE0_TASK(95)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test95++;
}
OS_CORE0_TASK(96)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test96++;
}
OS_CORE0_TASK(97)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test97++;
}
OS_CORE0_TASK(98)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test98++;
}
OS_CORE0_TASK(99)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test99++;
}
OS_CORE0_TASK(100)
{
  App_priv0_func_task_test_count(CURR_TASK_ID);
  core0_test100++;
  core0_end_count   = Task_Obtain_OS_Tick(0);
  core0_delta_count = core0_end_count - core0_init_count;  
}
