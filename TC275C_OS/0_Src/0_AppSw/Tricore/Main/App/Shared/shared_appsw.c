/****************************************************************************/
/* FILE NAME:    shared_appsw.h                                             */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes prototype definitions of APP           */
/*               that are intended to map function                          */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "low_driver_port.h"
#include "stack_manager.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define LED_1    (8)
#define LED_2    (9)
#define LED_3    (10)
#define LED_4    (11)

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
static volatile unsigned int App_shared_var_test_count;

/****************************************************************************/
/* Shared Funtion Definitions                                               */
/****************************************************************************/
void  App_shared_func_flash_led_1(void)
{
   LowDriver_Port_TogglePin(LED_1);
}

void  App_shared_func_flash_led_2(void)
{
   LowDriver_Port_TogglePin(LED_2);
}

void  App_shared_func_flash_led_3(void)
{
   LowDriver_Port_TogglePin(LED_3);
}

void  App_shared_func_flash_led_4(void)
{
   LowDriver_Port_TogglePin(LED_4);
}
void App_shared_func_trigger_software_interrupt1(void)
{
   LowDriver_Trigger_Software_Interrupt1();
}
void App_shared_func_trigger_software_interrupt2(void)
{
   LowDriver_Trigger_Software_Interrupt2();
}
void App_shared_func_trigger_software_interrupt3(void)
{
   LowDriver_Trigger_Software_Interrupt3();
}
void App_shared_func_trigger_software_interrupt4(void)
{
   LowDriver_Trigger_Software_Interrupt4();
}
void App_shared_func_trigger_software_interrupt5(void)
{
   LowDriver_Trigger_Software_Interrupt5();
}
void App_shared_func_trigger_software_interrupt6(void)
{
   LowDriver_Trigger_Software_Interrupt6();
}
void App_shared_func_trigger_software_interrupt7(void)
{
   LowDriver_Trigger_Software_Interrupt7();
}
void App_shared_func_trigger_software_interrupt8(void)
{
   LowDriver_Trigger_Software_Interrupt8();
}
void App_shared_func_trigger_software_interrupt9(void)
{
   LowDriver_Trigger_Software_Interrupt9();
}
void App_shared_func_software_interrupt1_event(void)
{
}
void App_shared_func_software_interrupt2_event(void)
{
}
void App_shared_func_software_interrupt3_event(void)
{
}
void App_shared_func_software_interrupt4_event(void)
{
}
void App_shared_func_software_interrupt5_event(void)
{
}
void App_shared_func_software_interrupt6_event(void)
{
}
void App_shared_func_software_interrupt7_event(void)
{
}
void App_shared_func_software_interrupt8_event(void)
{
}
void App_shared_func_software_interrupt9_event(void)
{
}
void  App_shared_func_test_count()
{
   App_shared_var_test_count ++;
}



