#include "os_type.h"
#include "os.h"
#include "shareappsw.h"

void CORE1_TASK0(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  App_share_func_stack_background_count(pthread_config->current_task_core_id);
}
void CORE1_TASK1(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  //App_share_func_flash_led_1();
}
void CORE1_TASK2(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  //App_share_func_flash_led_2();
}
void CORE1_TASK3(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK4(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK5(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK6(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK7(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK8(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK9(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
}
void CORE1_TASK10(pthread_config_t *pthread_config)
{
  App_share_func_task_test_count(pthread_config->current_task_core_id,pthread_config->task_id);
  App_share_func_stack_calculated(pthread_config->current_task_core_id);
  //App_share_func_flash_led_4();
}
void CORE1_TASK11(pthread_config_t *pthread_config){}
void CORE1_TASK12(pthread_config_t *pthread_config){}
void CORE1_TASK13(pthread_config_t *pthread_config){}
void CORE1_TASK14(pthread_config_t *pthread_config){}
void CORE1_TASK15(pthread_config_t *pthread_config){}
void CORE1_TASK16(pthread_config_t *pthread_config){}
void CORE1_TASK17(pthread_config_t *pthread_config){}
void CORE1_TASK18(pthread_config_t *pthread_config){}
void CORE1_TASK19(pthread_config_t *pthread_config){}
void CORE1_TASK20(pthread_config_t *pthread_config){}
void CORE1_TASK21(pthread_config_t *pthread_config){}
void CORE1_TASK22(pthread_config_t *pthread_config){}
void CORE1_TASK23(pthread_config_t *pthread_config){}
void CORE1_TASK24(pthread_config_t *pthread_config){}
void CORE1_TASK25(pthread_config_t *pthread_config){}
void CORE1_TASK26(pthread_config_t *pthread_config){}
void CORE1_TASK27(pthread_config_t *pthread_config){}
void CORE1_TASK28(pthread_config_t *pthread_config){}
void CORE1_TASK29(pthread_config_t *pthread_config){}
void CORE1_TASK30(pthread_config_t *pthread_config){}
void CORE1_TASK31(pthread_config_t *pthread_config){}
void CORE1_TASK32(pthread_config_t *pthread_config){}
void CORE1_TASK33(pthread_config_t *pthread_config){}
void CORE1_TASK34(pthread_config_t *pthread_config){}
void CORE1_TASK35(pthread_config_t *pthread_config){}
void CORE1_TASK36(pthread_config_t *pthread_config){}
void CORE1_TASK37(pthread_config_t *pthread_config){}
void CORE1_TASK38(pthread_config_t *pthread_config){}
void CORE1_TASK39(pthread_config_t *pthread_config){}
void CORE1_TASK40(pthread_config_t *pthread_config){}
void CORE1_TASK41(pthread_config_t *pthread_config){}
void CORE1_TASK42(pthread_config_t *pthread_config){}
void CORE1_TASK43(pthread_config_t *pthread_config){}
void CORE1_TASK44(pthread_config_t *pthread_config){}
void CORE1_TASK45(pthread_config_t *pthread_config){}
void CORE1_TASK46(pthread_config_t *pthread_config){}
void CORE1_TASK47(pthread_config_t *pthread_config){}
void CORE1_TASK48(pthread_config_t *pthread_config){}
void CORE1_TASK49(pthread_config_t *pthread_config){}
void CORE1_TASK50(pthread_config_t *pthread_config){}
void CORE1_TASK51(pthread_config_t *pthread_config){}
void CORE1_TASK52(pthread_config_t *pthread_config){}
void CORE1_TASK53(pthread_config_t *pthread_config){}
void CORE1_TASK54(pthread_config_t *pthread_config){}
void CORE1_TASK55(pthread_config_t *pthread_config){}
void CORE1_TASK56(pthread_config_t *pthread_config){}
void CORE1_TASK57(pthread_config_t *pthread_config){}
void CORE1_TASK58(pthread_config_t *pthread_config){}
void CORE1_TASK59(pthread_config_t *pthread_config){}
void CORE1_TASK60(pthread_config_t *pthread_config){}
void CORE1_TASK61(pthread_config_t *pthread_config){}
void CORE1_TASK62(pthread_config_t *pthread_config){}
void CORE1_TASK63(pthread_config_t *pthread_config){}
void CORE1_TASK64(pthread_config_t *pthread_config){}
void CORE1_TASK65(pthread_config_t *pthread_config){}
void CORE1_TASK66(pthread_config_t *pthread_config){}
void CORE1_TASK67(pthread_config_t *pthread_config){}
void CORE1_TASK68(pthread_config_t *pthread_config){}
void CORE1_TASK69(pthread_config_t *pthread_config){}
void CORE1_TASK70(pthread_config_t *pthread_config){}
void CORE1_TASK71(pthread_config_t *pthread_config){}
void CORE1_TASK72(pthread_config_t *pthread_config){}
void CORE1_TASK73(pthread_config_t *pthread_config){}
void CORE1_TASK74(pthread_config_t *pthread_config){}
void CORE1_TASK75(pthread_config_t *pthread_config){}
void CORE1_TASK76(pthread_config_t *pthread_config){}
void CORE1_TASK77(pthread_config_t *pthread_config){}
void CORE1_TASK78(pthread_config_t *pthread_config){}
void CORE1_TASK79(pthread_config_t *pthread_config){}
void CORE1_TASK80(pthread_config_t *pthread_config){}
void CORE1_TASK81(pthread_config_t *pthread_config){}
void CORE1_TASK82(pthread_config_t *pthread_config){}
void CORE1_TASK83(pthread_config_t *pthread_config){}
void CORE1_TASK84(pthread_config_t *pthread_config){}
void CORE1_TASK85(pthread_config_t *pthread_config){}
void CORE1_TASK86(pthread_config_t *pthread_config){}
void CORE1_TASK87(pthread_config_t *pthread_config){}
void CORE1_TASK88(pthread_config_t *pthread_config){}
void CORE1_TASK89(pthread_config_t *pthread_config){}
void CORE1_TASK90(pthread_config_t *pthread_config){}
void CORE1_TASK91(pthread_config_t *pthread_config){}
void CORE1_TASK92(pthread_config_t *pthread_config){}
void CORE1_TASK93(pthread_config_t *pthread_config){}
void CORE1_TASK94(pthread_config_t *pthread_config){}
void CORE1_TASK95(pthread_config_t *pthread_config){}
void CORE1_TASK96(pthread_config_t *pthread_config){}
void CORE1_TASK97(pthread_config_t *pthread_config){}
void CORE1_TASK98(pthread_config_t *pthread_config){}
void CORE1_TASK99(pthread_config_t *pthread_config){}
void CORE1_TASK100(pthread_config_t *pthread_config){}