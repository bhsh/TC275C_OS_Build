

#ifndef TASK_CONFIG_H_
#define TASK_CONFIG_H_

#include "os.h"

enum task_type{

   NO_DEFINITION,
   TASK_PERIODIC,
   TASK_EVENT
};

/* core 0*/
/* 0 TASK config initialization */ 
#define CORE0_TASK0_TYPE       NO_DEFINITION             
#define CORE0_TASK0_PERIOD     (0)  /* unit:ms */
#define CORE0_TASK0_ACTIVED    NO_TASK

#define CORE0_TASK1_TYPE       TASK_PERIODIC
#define CORE0_TASK1_PERIOD     (300)  /* unit:ms */
#define CORE0_TASK1_ACTIVED    NO_TASK

#define CORE0_TASK2_TYPE       TASK_PERIODIC
#define CORE0_TASK2_PERIOD     (500)  /* unit:ms */
#define CORE0_TASK2_ACTIVED    NO_TASK

#define CORE0_TASK3_TYPE       TASK_EVENT
#define CORE0_TASK3_PERIOD     (0)
#define CORE0_TASK3_ACTIVED    TASK_ID4

#define CORE0_TASK4_TYPE       TASK_EVENT
#define CORE0_TASK4_PERIOD     (0)
#define CORE0_TASK4_ACTIVED    TASK_ID5

#define CORE0_TASK5_TYPE       TASK_EVENT
#define CORE0_TASK5_PERIOD     (0)
#define CORE0_TASK5_ACTIVED    TASK_ID6

#define CORE0_TASK6_TYPE       TASK_EVENT
#define CORE0_TASK6_PERIOD     (0)
#define CORE0_TASK6_ACTIVED    TASK_ID7

#define CORE0_TASK7_TYPE       TASK_EVENT
#define CORE0_TASK7_PERIOD     (0)
#define CORE0_TASK7_ACTIVED    TASK_ID8

#define CORE0_TASK8_TYPE       TASK_EVENT
#define CORE0_TASK8_PERIOD     (0)
#define CORE0_TASK8_ACTIVED    TASK_ID9

#define CORE0_TASK9_TYPE       TASK_EVENT
#define CORE0_TASK9_PERIOD     (0)
#define CORE0_TASK9_ACTIVED    NO_TASK

#define CORE0_TASK10_TYPE      TASK_PERIODIC
#define CORE0_TASK10_PERIOD    (1000)  /* unit:ms */
#define CORE0_TASK10_ACTIVED   NO_TASK


/* core 1                      */

#define CORE1_TASK0_TYPE       NO_DEFINITION             
#define CORE1_TASK0_PERIOD     (0)  /* unit:ms */
#define CORE1_TASK0_ACTIVED    NO_TASK

#define CORE1_TASK1_TYPE       TASK_PERIODIC
#define CORE1_TASK1_PERIOD     (1000)  /* unit:ms */
#define CORE1_TASK1_ACTIVED    NO_TASK

#define CORE1_TASK2_TYPE       TASK_PERIODIC
#define CORE1_TASK2_PERIOD     (1000)
#define CORE1_TASK2_ACTIVED    NO_TASK

#define CORE1_TASK3_TYPE       TASK_EVENT
#define CORE1_TASK3_PERIOD     (0)
#define CORE1_TASK3_ACTIVED    TASK_ID4

#define CORE1_TASK4_TYPE       TASK_EVENT
#define CORE1_TASK4_PERIOD     (0)
#define CORE1_TASK4_ACTIVED    TASK_ID5

#define CORE1_TASK5_TYPE       TASK_EVENT
#define CORE1_TASK5_PERIOD     (0)
#define CORE1_TASK5_ACTIVED    TASK_ID6

#define CORE1_TASK6_TYPE       TASK_EVENT
#define CORE1_TASK6_PERIOD     (0)
#define CORE1_TASK6_ACTIVED    TASK_ID7

#define CORE1_TASK7_TYPE       TASK_EVENT
#define CORE1_TASK7_PERIOD     (0)
#define CORE1_TASK7_ACTIVED    TASK_ID8

#define CORE1_TASK8_TYPE       TASK_EVENT
#define CORE1_TASK8_PERIOD     (0)
#define CORE1_TASK8_ACTIVED    TASK_ID9

#define CORE1_TASK9_TYPE       TASK_EVENT
#define CORE1_TASK9_PERIOD     (0)
#define CORE1_TASK9_ACTIVED    NO_TASK

#define CORE1_TASK10_TYPE      TASK_PERIODIC
#define CORE1_TASK10_PERIOD    (1000)
#define CORE1_TASK10_ACTIVED   NO_TASK


/* core 2 */
#define CORE2_TASK0_TYPE       NO_DEFINITION             
#define CORE2_TASK0_PERIOD     (0)  /* unit:ms */
#define CORE2_TASK0_ACTIVED    NO_TASK

#define CORE2_TASK1_TYPE       TASK_PERIODIC
#define CORE2_TASK1_PERIOD     (1000)  /* unit:ms */
#define CORE2_TASK1_ACTIVED    NO_TASK

#define CORE2_TASK2_TYPE       TASK_PERIODIC
#define CORE2_TASK2_PERIOD     (1000)
#define CORE2_TASK2_ACTIVED    NO_TASK

#define CORE2_TASK3_TYPE       TASK_EVENT
#define CORE2_TASK3_PERIOD     (0)
#define CORE2_TASK3_ACTIVED    TASK_ID4

#define CORE2_TASK4_TYPE       TASK_EVENT
#define CORE2_TASK4_PERIOD     (0)
#define CORE2_TASK4_ACTIVED    TASK_ID5

#define CORE2_TASK5_TYPE       TASK_EVENT
#define CORE2_TASK5_PERIOD     (0)
#define CORE2_TASK5_ACTIVED    TASK_ID6

#define CORE2_TASK6_TYPE       TASK_EVENT
#define CORE2_TASK6_PERIOD     (0)
#define CORE2_TASK6_ACTIVED    TASK_ID7

#define CORE2_TASK7_TYPE       TASK_EVENT
#define CORE2_TASK7_PERIOD     (0)
#define CORE2_TASK7_ACTIVED    TASK_ID8

#define CORE2_TASK8_TYPE       TASK_EVENT
#define CORE2_TASK8_PERIOD     (0)
#define CORE2_TASK8_ACTIVED    TASK_ID9

#define CORE2_TASK9_TYPE       TASK_EVENT
#define CORE2_TASK9_PERIOD     (0)
#define CORE2_TASK9_ACTIVED    NO_TASK

#define CORE2_TASK10_TYPE      TASK_PERIODIC
#define CORE2_TASK10_PERIOD    (1000)
#define CORE2_TASK10_ACTIVED   NO_TASK

#endif

