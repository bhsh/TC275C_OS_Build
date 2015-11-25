/****************************************************************************/
/* FILE NAME:    stack_manager.c                                            */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The c file includes logic that tests the stack usage of    */
/*               each task in thread                                        */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/

/****************************************************************************/
/* Feature Include Files                                                    */
/****************************************************************************/
#include "os_type.h"
#include "low_driver_port.h"
#include "os_mode.h"

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define FACTOR                      (1000)

#if (OS_STACK_MODE == MANY_STACKS)
  #define MAX_MEASURE_THREADS       (10)
#endif

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum 
{
    STACK_BGEGIN,
    STACK_END,
    STACK_SIZE_IN_BYTE,
    STACK_SIZE_USED_IN_BYTE,
    STACK_SIZE_USED_IN_PERCENT,
#if (OS_STACK_MODE == MANY_STACKS)
    THREAD_ORDER_NUM,
#endif 
	STACK_INFO_MAX_ITEMS
	
} pthread_stack_info_t; 

/****************************************************************************/
/* Static Variable Definitions                                              */
/****************************************************************************/
#if (OS_STACK_MODE == MANY_STACKS)
  static osu32_t core0_thread_num = 0;
  static osu32_t core1_thread_num = 0;
  static osu32_t core2_thread_num = 0;
  static osu32_t core0_many_stacks_info[MAX_MEASURE_THREADS][STACK_INFO_MAX_ITEMS];
  static osu32_t core1_many_stacks_info[MAX_MEASURE_THREADS][STACK_INFO_MAX_ITEMS];
  static osu32_t core2_many_stacks_info[MAX_MEASURE_THREADS][STACK_INFO_MAX_ITEMS];
#else
  static osu32_t core0_one_stack_info[STACK_INFO_MAX_ITEMS];
  static osu32_t core1_one_stack_info[STACK_INFO_MAX_ITEMS];
  static osu32_t core2_one_stack_info[STACK_INFO_MAX_ITEMS];
#endif

/****************************************************************************/
/*  The Function Definitions Of Stack manager                               */
/****************************************************************************/

#if (OS_STACK_MODE == MANY_STACKS)
  /****************************************************************************/
  /* <OS CORE0>                                                               */
  /****************************************************************************/
  /****************************************************************************/
  /* FUNTION NAME:initialize_core0_many_stacks_memory                         */
  /* DESCRIPTION: Initialize the stack memory of many-stack mode              */
  /****************************************************************************/
  void initialize_core0_many_stacks_memory(osu32_t thread_order_num,osu32_t* stack_end_address,osu32_t stack_size)
  { 
    /* The stack memory is filled with 0xAA in byte*/
    osu32_t stack_size_in_word,index;
  
    if(core0_thread_num < MAX_MEASURE_THREADS)
    {
    	/* The input unit of stack size is word ,get the size in byte */
    	stack_size = stack_size*4;
  	
      core0_many_stacks_info[core0_thread_num][STACK_BGEGIN]        = (osu32_t)stack_end_address + stack_size;
      core0_many_stacks_info[core0_thread_num][STACK_END]           = (osu32_t)stack_end_address;
      core0_many_stacks_info[core0_thread_num][STACK_SIZE_IN_BYTE]  = stack_size;
      core0_many_stacks_info[core0_thread_num][THREAD_ORDER_NUM]    = thread_order_num;
    
      core0_thread_num++;
      
      stack_size_in_word = stack_size/4;
      for(index = 0 ; index < stack_size_in_word; index++ )
      {
         *stack_end_address++ = 0xAAAAAAAA;
      }
    }
  }/* End of function initialize_core0_many_stacks_memory */
  
  /****************************************************************************/
  /* FUNTION NAME:core0_get_the_many_stacks_used                              */
  /* DESCRIPTION: Get usage percent of every stack for many-stack mode        */
  /****************************************************************************/ 
  static osu32_t core0_get_the_many_stacks_used(osu32_t thread_num)
  { 
    osu8_t* stack_end_address;
    osu32_t byte_counter =0;
  
    stack_end_address = (osu8_t*)core0_many_stacks_info[thread_num][STACK_END]; 
  
    while(*stack_end_address++ == 0xAA)
    {
       byte_counter++;  
    }	
    core0_many_stacks_info[thread_num][STACK_SIZE_USED_IN_BYTE]    = 
      core0_many_stacks_info[thread_num][STACK_SIZE_IN_BYTE] - byte_counter;
    
    core0_many_stacks_info[thread_num][STACK_SIZE_USED_IN_PERCENT] = 
    	(core0_many_stacks_info[thread_num][STACK_SIZE_USED_IN_BYTE]*FACTOR)/core0_many_stacks_info[thread_num][STACK_SIZE_IN_BYTE]; 
  
    return core0_many_stacks_info[thread_num][STACK_SIZE_USED_IN_PERCENT];
  } /* End of function core0_get_the_many_stacks_used */
  
  /****************************************************************************/
  /* FUNTION NAME:core0_get_the_many_stacks_used                              */
  /* DESCRIPTION: Get usage percent of all stacks for many-stack mode         */
  /****************************************************************************/ 
  void core0_get_all_stacks_used(void)
  {
    osu32_t index;
    
    for(index = 0 ;index < core0_thread_num;index++)
    {
      core0_get_the_many_stacks_used(index);
    } 	
  } /* End of function core0_get_all_stacks_used */


  /****************************************************************************/
  /* <OS CORE1>                                                               */
  /****************************************************************************/
  /****************************************************************************/
  /* FUNTION NAME:initialize_core0_many_stacks_memory                         */
  /* DESCRIPTION: Initialize the stack memory of many-stack mode              */
  /****************************************************************************/
  void initialize_core1_many_stacks_memory(osu32_t thread_order_num,osu32_t* stack_end_address,osu32_t stack_size)
  { 
    /* The stack memory is filled with 0xAA in byte*/
    osu32_t stack_size_in_word,index;
  
    if(core1_thread_num < MAX_MEASURE_THREADS)
    {
    	/* The input unit of stack size is word ,get the size in byte */
    	stack_size = stack_size*4;
  	
      core1_many_stacks_info[core1_thread_num][STACK_BGEGIN]        = (osu32_t)stack_end_address + stack_size;
      core1_many_stacks_info[core1_thread_num][STACK_END]           = (osu32_t)stack_end_address;
      core1_many_stacks_info[core1_thread_num][STACK_SIZE_IN_BYTE]  = stack_size;
      core1_many_stacks_info[core1_thread_num][THREAD_ORDER_NUM]    = thread_order_num;
    
      core1_thread_num++;
      
      stack_size_in_word = stack_size/4;
      for(index = 0 ; index < stack_size_in_word; index++ )
      {
         *stack_end_address++ = 0xAAAAAAAA;
      }
    }
  }/* End of function initialize_core0_many_stacks_memory */
  
  /****************************************************************************/
  /* FUNTION NAME:core1_get_the_many_stacks_used                              */
  /* DESCRIPTION: Get usage percent of every stack for many-stack mode        */
  /****************************************************************************/ 
  static osu32_t core1_get_the_many_stacks_used(osu32_t thread_num)
  { 
    osu8_t* stack_end_address;
    osu32_t byte_counter =0;
  
    stack_end_address = (osu8_t*)core1_many_stacks_info[thread_num][STACK_END]; 
  
    while(*stack_end_address++ == 0xAA)
    {
       byte_counter++;  
    }	
    core1_many_stacks_info[thread_num][STACK_SIZE_USED_IN_BYTE]    = 
      core1_many_stacks_info[thread_num][STACK_SIZE_IN_BYTE] - byte_counter;
    
    core1_many_stacks_info[thread_num][STACK_SIZE_USED_IN_PERCENT] = 
    	(core1_many_stacks_info[thread_num][STACK_SIZE_USED_IN_BYTE]*FACTOR)/core1_many_stacks_info[thread_num][STACK_SIZE_IN_BYTE]; 
  
    return core1_many_stacks_info[thread_num][STACK_SIZE_USED_IN_PERCENT];
  } /* End of function core1_get_the_many_stacks_used */
  
  /****************************************************************************/
  /* FUNTION NAME:core0_get_the_many_stacks_used                              */
  /* DESCRIPTION: Get usage percent of all stacks for many-stack mode         */
  /****************************************************************************/ 
  void core1_get_all_stacks_used(void)
  {
    osu32_t index;
    
    for(index = 0 ;index < core1_thread_num;index++)
    {
      core1_get_the_many_stacks_used(index);
    } 	
  } /* End of function core1_get_all_stacks_used */


  /****************************************************************************/
  /* <OS CORE2>                                                               */
  /****************************************************************************/
  /****************************************************************************/
  /* FUNTION NAME:initialize_core2_many_stacks_memory                         */
  /* DESCRIPTION: Initialize the stack memory of many-stack mode              */
  /****************************************************************************/
  void initialize_core2_many_stacks_memory(osu32_t thread_order_num,osu32_t* stack_end_address,osu32_t stack_size)
  { 
    /* The stack memory is filled with 0xAA in byte*/
    osu32_t stack_size_in_word,index;
  
    if(core2_thread_num < MAX_MEASURE_THREADS)
    {
    	/* The input unit of stack size is word ,get the size in byte */
    	stack_size = stack_size*4;
  	
      core2_many_stacks_info[core2_thread_num][STACK_BGEGIN]        = (osu32_t)stack_end_address + stack_size;
      core2_many_stacks_info[core2_thread_num][STACK_END]           = (osu32_t)stack_end_address;
      core2_many_stacks_info[core2_thread_num][STACK_SIZE_IN_BYTE]  = stack_size;
      core2_many_stacks_info[core2_thread_num][THREAD_ORDER_NUM]    = thread_order_num;
    
      core2_thread_num++;
      
      stack_size_in_word = stack_size/4;
      for(index = 0 ; index < stack_size_in_word; index++ )
      {
         *stack_end_address++ = 0xAAAAAAAA;
      }
    }
  }/* End of function initialize_core2_many_stacks_memory */
  
  /****************************************************************************/
  /* FUNTION NAME:core2_get_the_many_stacks_used                              */
  /* DESCRIPTION: Get usage percent of every stack for many-stack mode        */
  /****************************************************************************/ 
  static osu32_t core2_get_the_many_stacks_used(osu32_t thread_num)
  { 
    osu8_t* stack_end_address;
    osu32_t byte_counter =0;
  
    stack_end_address = (osu8_t*)core2_many_stacks_info[thread_num][STACK_END]; 
  
    while(*stack_end_address++ == 0xAA)
    {
       byte_counter++;  
    }	
    core2_many_stacks_info[thread_num][STACK_SIZE_USED_IN_BYTE]    = 
      core2_many_stacks_info[thread_num][STACK_SIZE_IN_BYTE] - byte_counter;
    
    core2_many_stacks_info[thread_num][STACK_SIZE_USED_IN_PERCENT] = 
    	(core2_many_stacks_info[thread_num][STACK_SIZE_USED_IN_BYTE]*FACTOR)/core2_many_stacks_info[thread_num][STACK_SIZE_IN_BYTE]; 
  
    return core2_many_stacks_info[thread_num][STACK_SIZE_USED_IN_PERCENT];
  } /* End of function core2_get_the_many_stacks_used */
  
  /****************************************************************************/
  /* FUNTION NAME:core2_get_the_many_stacks_used                              */
  /* DESCRIPTION: Get usage percent of all stacks for many-stack mode         */
  /****************************************************************************/ 
  void core2_get_all_stacks_used(void)
  {
    osu32_t index;
    
    for(index = 0 ;index < core2_thread_num;index++)
    {
      core2_get_the_many_stacks_used(index);
    } 	
  } /* End of function core2_get_all_stacks_used */


#else

  /****************************************************************************/
  /* <OS CORE0>                                                               */
  /****************************************************************************/

  /****************************************************************************/
  /* FUNTION NAME:get_thread_init_stack_address                               */
  /* DESCRIPTION: Initialize the stack memory of one-stack mode               */
  /****************************************************************************/
  void initialize_core0_one_stack_memory(osu32_t* stack_end_address,osu32_t stack_size)
  { 
    /* The stack memory is filled with 0xAA in byte*/
    osu32_t stack_size_in_word,index;
  
    core0_one_stack_info[STACK_BGEGIN]        = (osu32_t)stack_end_address + stack_size;
    core0_one_stack_info[STACK_END]           = (osu32_t)stack_end_address;
    core0_one_stack_info[STACK_SIZE_IN_BYTE]  = stack_size;
    
    stack_size_in_word = stack_size/4;
    for(index = 0 ; index < stack_size_in_word; index++ )
    {
       *stack_end_address++ = 0xAAAAAAAA;
    }
  } /* End of function initialize_core0_one_stack_memory */
  
  /****************************************************************************/
  /* FUNTION NAME:core0_get_the_one_stack_used                                */
  /* DESCRIPTION: Get the usage percent of the stack for one-stack mode       */
  /****************************************************************************/ 
  osu32_t core0_get_the_one_stack_used(void)
  { 
    osu8_t* stack_end_address;
    osu32_t byte_counter =0;
  
    stack_end_address = (osu8_t*)core0_one_stack_info[STACK_END]; 
  
    while(*stack_end_address++ == 0xAA)
    {
       byte_counter++;  
    }	
    core0_one_stack_info[STACK_SIZE_USED_IN_BYTE]    = 
      core0_one_stack_info[STACK_SIZE_IN_BYTE] - byte_counter;
    
    core0_one_stack_info[STACK_SIZE_USED_IN_PERCENT] = 
    	(core0_one_stack_info[STACK_SIZE_USED_IN_BYTE]*FACTOR)/core0_one_stack_info[STACK_SIZE_IN_BYTE]; 
  
    return core0_one_stack_info[STACK_SIZE_USED_IN_PERCENT];
  } /* End of function core0_get_the_one_stack_used */



  /****************************************************************************/
  /* <OS CORE1>                                                               */
  /****************************************************************************/

  /****************************************************************************/
  /* FUNTION NAME:initialize_core1_one_stack_memory                           */
  /* DESCRIPTION: Initialize the stack memory of one-stack mode               */
  /****************************************************************************/
  void initialize_core1_one_stack_memory(osu32_t* stack_end_address,osu32_t stack_size)
  { 
    /* The stack memory is filled with 0xAA in byte*/
    osu32_t stack_size_in_word,index;
  
    core1_one_stack_info[STACK_BGEGIN]        = (osu32_t)stack_end_address + stack_size;
    core1_one_stack_info[STACK_END]           = (osu32_t)stack_end_address;
    core1_one_stack_info[STACK_SIZE_IN_BYTE]  = stack_size;
    
    stack_size_in_word = stack_size/4;
    for(index = 0 ; index < stack_size_in_word; index++ )
    {
       *stack_end_address++ = 0xAAAAAAAA;
    }
  } /* End of function initialize_core1_one_stack_memory */
  
  /****************************************************************************/
  /* FUNTION NAME:core1_get_the_one_stack_used                                */
  /* DESCRIPTION: Get the usage percent of the stack for one-stack mode       */
  /****************************************************************************/ 
  osu32_t core1_get_the_one_stack_used(void)
  { 
    osu8_t* stack_end_address;
    osu32_t byte_counter =0;
  
    stack_end_address = (osu8_t*)core1_one_stack_info[STACK_END]; 
  
    while(*stack_end_address++ == 0xAA)
    {
       byte_counter++;  
    }	
    core1_one_stack_info[STACK_SIZE_USED_IN_BYTE]    = 
      core1_one_stack_info[STACK_SIZE_IN_BYTE] - byte_counter;
    
    core1_one_stack_info[STACK_SIZE_USED_IN_PERCENT] = 
    	(core1_one_stack_info[STACK_SIZE_USED_IN_BYTE]*FACTOR)/core1_one_stack_info[STACK_SIZE_IN_BYTE]; 
  
    return core1_one_stack_info[STACK_SIZE_USED_IN_PERCENT];
  } /* End of function core1_get_the_one_stack_used */


  /****************************************************************************/
  /* <OS CORE2>                                                               */
  /****************************************************************************/

  /****************************************************************************/
  /* FUNTION NAME:get_thread_init_stack_address                               */
  /* DESCRIPTION: Initialize the stack memory of one-stack mode               */
  /****************************************************************************/
  void initialize_core2_one_stack_memory(osu32_t* stack_end_address,osu32_t stack_size)
  { 
    /* The stack memory is filled with 0xAA in byte*/
    osu32_t stack_size_in_word,index;
  
    core2_one_stack_info[STACK_BGEGIN]        = (osu32_t)stack_end_address + stack_size;
    core2_one_stack_info[STACK_END]           = (osu32_t)stack_end_address;
    core2_one_stack_info[STACK_SIZE_IN_BYTE]  = stack_size;
    
    stack_size_in_word = stack_size/4;
    for(index = 0 ; index < stack_size_in_word; index++ )
    {
       *stack_end_address++ = 0xAAAAAAAA;
    }
  } /* End of function initialize_core2_one_stack_memory */
  
  /****************************************************************************/
  /* FUNTION NAME:core2_get_the_one_stack_used                                */
  /* DESCRIPTION: Get the usage percent of the stack for one-stack mode       */
  /****************************************************************************/ 
  osu32_t core2_get_the_one_stack_used(void)
  { 
    osu8_t* stack_end_address;
    osu32_t byte_counter =0;
  
    stack_end_address = (osu8_t*)core2_one_stack_info[STACK_END]; 
  
    while(*stack_end_address++ == 0xAA)
    {
       byte_counter++;  
    }	
    core2_one_stack_info[STACK_SIZE_USED_IN_BYTE]    = 
      core2_one_stack_info[STACK_SIZE_IN_BYTE] - byte_counter;
    
    core2_one_stack_info[STACK_SIZE_USED_IN_PERCENT] = 
    	(core2_one_stack_info[STACK_SIZE_USED_IN_BYTE]*FACTOR)/core2_one_stack_info[STACK_SIZE_IN_BYTE]; 
  
    return core2_one_stack_info[STACK_SIZE_USED_IN_PERCENT];
  } /* End of function core2_get_the_one_stack_used */  
#endif
