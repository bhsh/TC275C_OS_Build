
#include "os_type.h"
#include "os.h"
#include "shareappsw.h"

void CORE0_TASK0(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
  App_share_func_stack_background_count(pthread_config->curr_task_core_id);
}
void CORE0_TASK1(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
  App_share_func_flash_led_1();
}
void CORE0_TASK2(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
  App_share_func_flash_led_2();
}
void CORE0_TASK3(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK4(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK5(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK6(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK7(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK8(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK9(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
}
void CORE0_TASK10(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->curr_task_core_id,pthread_config->task_id);
  App_share_func_stack_calculated(pthread_config->curr_task_core_id);
  App_share_func_flash_led_4();
}
void CORE0_TASK11(pthread_config_t *pthread_config){}
void CORE0_TASK12(pthread_config_t *pthread_config){}
void CORE0_TASK13(pthread_config_t *pthread_config){}
void CORE0_TASK14(pthread_config_t *pthread_config){}
void CORE0_TASK15(pthread_config_t *pthread_config){}
void CORE0_TASK16(pthread_config_t *pthread_config){}
void CORE0_TASK17(pthread_config_t *pthread_config){}
void CORE0_TASK18(pthread_config_t *pthread_config){}
void CORE0_TASK19(pthread_config_t *pthread_config){}
void CORE0_TASK20(pthread_config_t *pthread_config){}
void CORE0_TASK21(pthread_config_t *pthread_config){}
void CORE0_TASK22(pthread_config_t *pthread_config){}
void CORE0_TASK23(pthread_config_t *pthread_config){}
void CORE0_TASK24(pthread_config_t *pthread_config){}
void CORE0_TASK25(pthread_config_t *pthread_config){}
void CORE0_TASK26(pthread_config_t *pthread_config){}
void CORE0_TASK27(pthread_config_t *pthread_config){}
void CORE0_TASK28(pthread_config_t *pthread_config){}
void CORE0_TASK29(pthread_config_t *pthread_config){}
void CORE0_TASK30(pthread_config_t *pthread_config){}
void CORE0_TASK31(pthread_config_t *pthread_config){}
void CORE0_TASK32(pthread_config_t *pthread_config){}
void CORE0_TASK33(pthread_config_t *pthread_config){}
void CORE0_TASK34(pthread_config_t *pthread_config){}
void CORE0_TASK35(pthread_config_t *pthread_config){}
void CORE0_TASK36(pthread_config_t *pthread_config){}
void CORE0_TASK37(pthread_config_t *pthread_config){}
void CORE0_TASK38(pthread_config_t *pthread_config){}
void CORE0_TASK39(pthread_config_t *pthread_config){}
void CORE0_TASK40(pthread_config_t *pthread_config){}
void CORE0_TASK41(pthread_config_t *pthread_config){}
void CORE0_TASK42(pthread_config_t *pthread_config){}
void CORE0_TASK43(pthread_config_t *pthread_config){}
void CORE0_TASK44(pthread_config_t *pthread_config){}
void CORE0_TASK45(pthread_config_t *pthread_config){}
void CORE0_TASK46(pthread_config_t *pthread_config){}
void CORE0_TASK47(pthread_config_t *pthread_config){}
void CORE0_TASK48(pthread_config_t *pthread_config){}
void CORE0_TASK49(pthread_config_t *pthread_config){}
void CORE0_TASK50(pthread_config_t *pthread_config){}
void CORE0_TASK51(pthread_config_t *pthread_config){}
void CORE0_TASK52(pthread_config_t *pthread_config){}
void CORE0_TASK53(pthread_config_t *pthread_config){}
void CORE0_TASK54(pthread_config_t *pthread_config){}
void CORE0_TASK55(pthread_config_t *pthread_config){}
void CORE0_TASK56(pthread_config_t *pthread_config){}
void CORE0_TASK57(pthread_config_t *pthread_config){}
void CORE0_TASK58(pthread_config_t *pthread_config){}
void CORE0_TASK59(pthread_config_t *pthread_config){}
void CORE0_TASK60(pthread_config_t *pthread_config){}
void CORE0_TASK61(pthread_config_t *pthread_config){}
void CORE0_TASK62(pthread_config_t *pthread_config){}
void CORE0_TASK63(pthread_config_t *pthread_config){}
void CORE0_TASK64(pthread_config_t *pthread_config){}
void CORE0_TASK65(pthread_config_t *pthread_config){}
void CORE0_TASK66(pthread_config_t *pthread_config){}
void CORE0_TASK67(pthread_config_t *pthread_config){}
void CORE0_TASK68(pthread_config_t *pthread_config){}
void CORE0_TASK69(pthread_config_t *pthread_config){}
void CORE0_TASK70(pthread_config_t *pthread_config){}
void CORE0_TASK71(pthread_config_t *pthread_config){}
void CORE0_TASK72(pthread_config_t *pthread_config){}
void CORE0_TASK73(pthread_config_t *pthread_config){}
void CORE0_TASK74(pthread_config_t *pthread_config){}
void CORE0_TASK75(pthread_config_t *pthread_config){}
void CORE0_TASK76(pthread_config_t *pthread_config){}
void CORE0_TASK77(pthread_config_t *pthread_config){}
void CORE0_TASK78(pthread_config_t *pthread_config){}
void CORE0_TASK79(pthread_config_t *pthread_config){}
void CORE0_TASK80(pthread_config_t *pthread_config){}
void CORE0_TASK81(pthread_config_t *pthread_config){}
void CORE0_TASK82(pthread_config_t *pthread_config){}
void CORE0_TASK83(pthread_config_t *pthread_config){}
void CORE0_TASK84(pthread_config_t *pthread_config){}
void CORE0_TASK85(pthread_config_t *pthread_config){}
void CORE0_TASK86(pthread_config_t *pthread_config){}
void CORE0_TASK87(pthread_config_t *pthread_config){}
void CORE0_TASK88(pthread_config_t *pthread_config){}
void CORE0_TASK89(pthread_config_t *pthread_config){}
void CORE0_TASK90(pthread_config_t *pthread_config){}
void CORE0_TASK91(pthread_config_t *pthread_config){}
void CORE0_TASK92(pthread_config_t *pthread_config){}
void CORE0_TASK93(pthread_config_t *pthread_config){}
void CORE0_TASK94(pthread_config_t *pthread_config){}
void CORE0_TASK95(pthread_config_t *pthread_config){}
void CORE0_TASK96(pthread_config_t *pthread_config){}
void CORE0_TASK97(pthread_config_t *pthread_config){}
void CORE0_TASK98(pthread_config_t *pthread_config){}
void CORE0_TASK99(pthread_config_t *pthread_config){}
void CORE0_TASK100(pthread_config_t *pthread_config){}