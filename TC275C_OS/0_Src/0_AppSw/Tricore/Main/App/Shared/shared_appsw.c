/****************************************************************************/
/* FILE NAME:    shared_appsw.c                                             */
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
#include "shared_appsw.h"

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
static volatile unsigned int App_shared_var_soft_int_test_count1;
static volatile unsigned int App_shared_var_soft_int_test_count2;
static volatile unsigned int App_shared_var_soft_int_test_count3;
static volatile unsigned int App_shared_var_soft_int_test_count4;
static volatile unsigned int App_shared_var_soft_int_test_count5;
static volatile unsigned int App_shared_var_soft_int_test_count6;
static volatile unsigned int App_shared_var_soft_int_test_count7;
static volatile unsigned int App_shared_var_soft_int_test_count8;
static volatile unsigned int App_shared_var_soft_int_test_count9;
static volatile unsigned int App_shared_var_switch_count = 0;
static volatile unsigned int App_shared_var_trig_count = 2;
static volatile unsigned int App_shared_var_int_sequence_count;
static volatile unsigned int App_shared_var_int_sequence_end_c;
static volatile unsigned int App_shared_var_soft_int_read_buff1;
static volatile unsigned int App_shared_var_soft_int_read_buff4;
static volatile unsigned int App_shared_var_soft_int_read_buff7;
static volatile unsigned int App_shared_var_read_end_c_buff1;
static volatile unsigned int App_shared_var_read_end_c_buff4;
static volatile unsigned int App_shared_var_read_end_c_buff7;
static volatile unsigned int App_shared_var_int1_trig_switch_count = 0;


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
static void App_shared_func_nested_trig(void)
{
  unsigned int index;
  if(App_shared_var_switch_count == 0)
  {
  	App_shared_var_switch_count = 1;
	
	for(index = 0; index < App_shared_var_trig_count ;index++)
	{
      App_shared_func_trigger_software_interrupt1();
	  App_shared_func_trigger_software_interrupt4();
	}
  }
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
  App_shared_var_soft_int_test_count1++;
  
  App_shared_var_soft_int_read_buff1 = App_shared_var_int_sequence_count;
  App_shared_var_int_sequence_count++;

  App_shared_var_read_end_c_buff1 = App_shared_var_int_sequence_end_c;

  if(App_shared_var_int1_trig_switch_count == 0)
  { 
  	App_shared_var_int1_trig_switch_count = 1;
    App_shared_func_trigger_software_interrupt1();
  }
}
void App_shared_func_software_interrupt2_event(void)
{
  App_shared_var_soft_int_test_count2++;
}
void App_shared_func_software_interrupt3_event(void)
{
  App_shared_var_soft_int_test_count3++;
}
void App_shared_func_software_interrupt4_event(void)
{
  App_shared_var_soft_int_test_count4++;

  App_shared_var_soft_int_read_buff4 = App_shared_var_int_sequence_count;
  App_shared_var_int_sequence_count++;

  App_shared_var_read_end_c_buff4 = App_shared_var_int_sequence_end_c;

}
void App_shared_func_software_interrupt5_event(void)
{
  App_shared_var_soft_int_test_count5++;
}
void App_shared_func_software_interrupt6_event(void)
{
  App_shared_var_soft_int_test_count6++;
}
void App_shared_func_software_interrupt7_event(void)
{ 
  App_shared_var_soft_int_test_count7++;

  App_shared_var_soft_int_read_buff7 = App_shared_var_int_sequence_count;
  App_shared_var_int_sequence_count ++;
  App_shared_func_nested_trig();

  App_shared_var_read_end_c_buff7 = App_shared_var_int_sequence_end_c;
  App_shared_var_int_sequence_end_c++;
 
}
void App_shared_func_software_interrupt8_event(void)
{
  App_shared_var_soft_int_test_count8++;
}
void App_shared_func_software_interrupt9_event(void)
{
  App_shared_var_soft_int_test_count9++;
}
void  App_shared_func_test_count()
{
   App_shared_var_test_count ++;
}



