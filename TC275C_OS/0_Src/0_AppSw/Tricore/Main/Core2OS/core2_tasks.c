/****************************************************************************/
/* FILE NAME:    core2_tasks.c                                              */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes the task definitions of AURIX core2    */
/*               os                                                         */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/ 
#include "os_type.h"
#include "os.h"
#include "shared_appsw.h"
#include "priv2_appsw.h"

/****************************************************************************/
/* <CORE2> Task Definitions                                                 */
/****************************************************************************/
void CORE2_TASK0(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
  App_shared_func_stack_background_count(task_cfg->curr_task_core_id);
  App_priv2_func_test_count();

}
void CORE2_TASK1(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
  //App_shared_func_flash_led_1();
}
void CORE2_TASK2(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
  //App_shared_func_flash_led_2();
}
void CORE2_TASK3(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK4(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK5(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK6(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK7(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK8(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK9(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
}
void CORE2_TASK10(task_cfg_t task_cfg)
{
  App_shared_func_task_test_count(task_cfg->curr_task_core_id,task_cfg->curr_task_id);
  App_shared_func_stack_calculated(task_cfg->curr_task_core_id);
  //App_shared_func_flash_led_4();
}
void CORE2_TASK11(task_cfg_t task_cfg){}
void CORE2_TASK12(task_cfg_t task_cfg){}
void CORE2_TASK13(task_cfg_t task_cfg){}
void CORE2_TASK14(task_cfg_t task_cfg){}
void CORE2_TASK15(task_cfg_t task_cfg){}
void CORE2_TASK16(task_cfg_t task_cfg){}
void CORE2_TASK17(task_cfg_t task_cfg){}
void CORE2_TASK18(task_cfg_t task_cfg){}
void CORE2_TASK19(task_cfg_t task_cfg){}
void CORE2_TASK20(task_cfg_t task_cfg){}
void CORE2_TASK21(task_cfg_t task_cfg){}
void CORE2_TASK22(task_cfg_t task_cfg){}
void CORE2_TASK23(task_cfg_t task_cfg){}
void CORE2_TASK24(task_cfg_t task_cfg){}
void CORE2_TASK25(task_cfg_t task_cfg){}
void CORE2_TASK26(task_cfg_t task_cfg){}
void CORE2_TASK27(task_cfg_t task_cfg){}
void CORE2_TASK28(task_cfg_t task_cfg){}
void CORE2_TASK29(task_cfg_t task_cfg){}
void CORE2_TASK30(task_cfg_t task_cfg){}
void CORE2_TASK31(task_cfg_t task_cfg){}
void CORE2_TASK32(task_cfg_t task_cfg){}
void CORE2_TASK33(task_cfg_t task_cfg){}
void CORE2_TASK34(task_cfg_t task_cfg){}
void CORE2_TASK35(task_cfg_t task_cfg){}
void CORE2_TASK36(task_cfg_t task_cfg){}
void CORE2_TASK37(task_cfg_t task_cfg){}
void CORE2_TASK38(task_cfg_t task_cfg){}
void CORE2_TASK39(task_cfg_t task_cfg){}
void CORE2_TASK40(task_cfg_t task_cfg){}
void CORE2_TASK41(task_cfg_t task_cfg){}
void CORE2_TASK42(task_cfg_t task_cfg){}
void CORE2_TASK43(task_cfg_t task_cfg){}
void CORE2_TASK44(task_cfg_t task_cfg){}
void CORE2_TASK45(task_cfg_t task_cfg){}
void CORE2_TASK46(task_cfg_t task_cfg){}
void CORE2_TASK47(task_cfg_t task_cfg){}
void CORE2_TASK48(task_cfg_t task_cfg){}
void CORE2_TASK49(task_cfg_t task_cfg){}
void CORE2_TASK50(task_cfg_t task_cfg){}
void CORE2_TASK51(task_cfg_t task_cfg){}
void CORE2_TASK52(task_cfg_t task_cfg){}
void CORE2_TASK53(task_cfg_t task_cfg){}
void CORE2_TASK54(task_cfg_t task_cfg){}
void CORE2_TASK55(task_cfg_t task_cfg){}
void CORE2_TASK56(task_cfg_t task_cfg){}
void CORE2_TASK57(task_cfg_t task_cfg){}
void CORE2_TASK58(task_cfg_t task_cfg){}
void CORE2_TASK59(task_cfg_t task_cfg){}
void CORE2_TASK60(task_cfg_t task_cfg){}
void CORE2_TASK61(task_cfg_t task_cfg){}
void CORE2_TASK62(task_cfg_t task_cfg){}
void CORE2_TASK63(task_cfg_t task_cfg){}
void CORE2_TASK64(task_cfg_t task_cfg){}
void CORE2_TASK65(task_cfg_t task_cfg){}
void CORE2_TASK66(task_cfg_t task_cfg){}
void CORE2_TASK67(task_cfg_t task_cfg){}
void CORE2_TASK68(task_cfg_t task_cfg){}
void CORE2_TASK69(task_cfg_t task_cfg){}
void CORE2_TASK70(task_cfg_t task_cfg){}
void CORE2_TASK71(task_cfg_t task_cfg){}
void CORE2_TASK72(task_cfg_t task_cfg){}
void CORE2_TASK73(task_cfg_t task_cfg){}
void CORE2_TASK74(task_cfg_t task_cfg){}
void CORE2_TASK75(task_cfg_t task_cfg){}
void CORE2_TASK76(task_cfg_t task_cfg){}
void CORE2_TASK77(task_cfg_t task_cfg){}
void CORE2_TASK78(task_cfg_t task_cfg){}
void CORE2_TASK79(task_cfg_t task_cfg){}
void CORE2_TASK80(task_cfg_t task_cfg){}
void CORE2_TASK81(task_cfg_t task_cfg){}
void CORE2_TASK82(task_cfg_t task_cfg){}
void CORE2_TASK83(task_cfg_t task_cfg){}
void CORE2_TASK84(task_cfg_t task_cfg){}
void CORE2_TASK85(task_cfg_t task_cfg){}
void CORE2_TASK86(task_cfg_t task_cfg){}
void CORE2_TASK87(task_cfg_t task_cfg){}
void CORE2_TASK88(task_cfg_t task_cfg){}
void CORE2_TASK89(task_cfg_t task_cfg){}
void CORE2_TASK90(task_cfg_t task_cfg){}
void CORE2_TASK91(task_cfg_t task_cfg){}
void CORE2_TASK92(task_cfg_t task_cfg){}
void CORE2_TASK93(task_cfg_t task_cfg){}
void CORE2_TASK94(task_cfg_t task_cfg){}
void CORE2_TASK95(task_cfg_t task_cfg){}
void CORE2_TASK96(task_cfg_t task_cfg){}
void CORE2_TASK97(task_cfg_t task_cfg){}
void CORE2_TASK98(task_cfg_t task_cfg){}
void CORE2_TASK99(task_cfg_t task_cfg){}
void CORE2_TASK100(task_cfg_t task_cfg){}
