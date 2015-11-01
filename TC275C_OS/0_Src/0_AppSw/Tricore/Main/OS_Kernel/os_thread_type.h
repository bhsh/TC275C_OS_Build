/****************************************************************************/
/* FILE NAME:    os_thread_type.h                                           */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the thread type definitions            */ 
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_THREAD_TYPE_H_ 
#define OS_THREAD_TYPE_H_

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define NO_DEFINITION (0)
#define PERIODIC      (1)
#define EVENT         (2)
#define NO_ACTIVED_TASK       (0xFF)
#define NO_ACTIVED_THREAD     NO_ACTIVED_TASK

#define LEVEL_0       (0)
#define LEVEL_1       (1)
#define LEVEL_2       (2)
#define LEVEL_3       (3)
#define LEVEL_4       (4)
#define LEVEL_5       (5)
#define LEVEL_6       (6)
#define LEVEL_7       (7)
#define LEVEL_8       (8)
#define LEVEL_9       (9)
#define LEVEL_10      (10)
#define LEVEL_11      (11)
#define LEVEL_12      (12)
#define LEVEL_13      (13)
#define LEVEL_14      (14)
#define LEVEL_15      (15)
#define LEVEL_16      (16)
#define LEVEL_17      (17)
#define LEVEL_18      (18)
#define LEVEL_19      (19)
#define LEVEL_20      (20)
#define LEVEL_21      (21)
#define LEVEL_22      (22)
#define LEVEL_23      (23)
#define LEVEL_24      (24)
#define LEVEL_25      (25)
#define LEVEL_26      (26)
#define LEVEL_27      (27)
#define LEVEL_28      (28)
#define LEVEL_29      (29)
#define LEVEL_30      (30)
#define LEVEL_31      (31)

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef enum  {

	 CORE_ID0,
	 CORE_ID1,
	 CORE_ID2,
	 CORE_MAX_ID_NUM

}OS_CORE_ID_t;

#endif /* End of OS_THREAD_TYPE_H_ */

