/****************************************************************************/
/* FILE NAME:    core0_task_manager.h                                       */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes switch definition of AURIX core0 tasks */
/*               os                                                         */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/ 
#ifndef CRRE0_TASK_MANAGER_H_
#define CRRE0_TASK_MANAGER_H_

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* <CORE0> Task Switch Configuration                                        */
/****************************************************************************/
#define  CORE0_OS_SWITCH        ON  /* <CORE0> Switch off or on the os of core0 */

#define	 CORE0_TASK0_SWITCH	    ON
#define	 CORE0_TASK1_SWITCH 	ON
#define	 CORE0_TASK2_SWITCH 	ON
#define	 CORE0_TASK3_SWITCH	    OFF
#define	 CORE0_TASK4_SWITCH	    OFF
#define	 CORE0_TASK5_SWITCH	    OFF
#define	 CORE0_TASK6_SWITCH	    OFF
#define	 CORE0_TASK7_SWITCH	    OFF
#define	 CORE0_TASK8_SWITCH	    OFF
#define	 CORE0_TASK9_SWITCH	    OFF
#define	 CORE0_TASK10_SWITCH	OFF
#define	 CORE0_TASK11_SWITCH 	OFF
#define	 CORE0_TASK12_SWITCH 	OFF
#define	 CORE0_TASK13_SWITCH	OFF
#define	 CORE0_TASK14_SWITCH	OFF
#define	 CORE0_TASK15_SWITCH	OFF
#define	 CORE0_TASK16_SWITCH	OFF
#define	 CORE0_TASK17_SWITCH	OFF
#define	 CORE0_TASK18_SWITCH	OFF
#define	 CORE0_TASK19_SWITCH	OFF
#define	 CORE0_TASK20_SWITCH	OFF
#define	 CORE0_TASK21_SWITCH 	OFF
#define	 CORE0_TASK22_SWITCH 	OFF
#define	 CORE0_TASK23_SWITCH	OFF
#define	 CORE0_TASK24_SWITCH	OFF
#define	 CORE0_TASK25_SWITCH	OFF
#define	 CORE0_TASK26_SWITCH	OFF
#define	 CORE0_TASK27_SWITCH	OFF
#define	 CORE0_TASK28_SWITCH	OFF
#define	 CORE0_TASK29_SWITCH	OFF
#define	 CORE0_TASK30_SWITCH	OFF
#define	 CORE0_TASK31_SWITCH 	OFF
#define	 CORE0_TASK32_SWITCH 	OFF
#define	 CORE0_TASK33_SWITCH	OFF
#define	 CORE0_TASK34_SWITCH	OFF
#define	 CORE0_TASK35_SWITCH	OFF
#define	 CORE0_TASK36_SWITCH	OFF
#define	 CORE0_TASK37_SWITCH	OFF
#define	 CORE0_TASK38_SWITCH	OFF
#define	 CORE0_TASK39_SWITCH	OFF
#define	 CORE0_TASK40_SWITCH	OFF
#define	 CORE0_TASK41_SWITCH 	OFF
#define	 CORE0_TASK42_SWITCH 	OFF
#define	 CORE0_TASK43_SWITCH	OFF
#define	 CORE0_TASK44_SWITCH	OFF
#define	 CORE0_TASK45_SWITCH	OFF
#define	 CORE0_TASK46_SWITCH	OFF
#define	 CORE0_TASK47_SWITCH	OFF
#define	 CORE0_TASK48_SWITCH	OFF
#define	 CORE0_TASK49_SWITCH	OFF
#define	 CORE0_TASK50_SWITCH	OFF
#define	 CORE0_TASK51_SWITCH 	OFF
#define	 CORE0_TASK52_SWITCH 	OFF
#define	 CORE0_TASK53_SWITCH	OFF
#define	 CORE0_TASK54_SWITCH	OFF
#define	 CORE0_TASK55_SWITCH	OFF
#define	 CORE0_TASK56_SWITCH	OFF
#define	 CORE0_TASK57_SWITCH	OFF
#define	 CORE0_TASK58_SWITCH	OFF
#define	 CORE0_TASK59_SWITCH	OFF
#define	 CORE0_TASK60_SWITCH	OFF
#define	 CORE0_TASK61_SWITCH 	OFF
#define	 CORE0_TASK62_SWITCH 	OFF
#define	 CORE0_TASK63_SWITCH	OFF
#define	 CORE0_TASK64_SWITCH	OFF
#define	 CORE0_TASK65_SWITCH	OFF
#define	 CORE0_TASK66_SWITCH	OFF
#define	 CORE0_TASK67_SWITCH	OFF
#define	 CORE0_TASK68_SWITCH	OFF
#define	 CORE0_TASK69_SWITCH	OFF
#define	 CORE0_TASK70_SWITCH	OFF
#define	 CORE0_TASK71_SWITCH 	OFF
#define	 CORE0_TASK72_SWITCH 	OFF
#define	 CORE0_TASK73_SWITCH	OFF
#define	 CORE0_TASK74_SWITCH	OFF
#define	 CORE0_TASK75_SWITCH	OFF
#define	 CORE0_TASK76_SWITCH	OFF
#define	 CORE0_TASK77_SWITCH	OFF
#define	 CORE0_TASK78_SWITCH	OFF
#define	 CORE0_TASK79_SWITCH	OFF
#define	 CORE0_TASK80_SWITCH	OFF
#define	 CORE0_TASK81_SWITCH 	OFF
#define	 CORE0_TASK82_SWITCH 	OFF
#define	 CORE0_TASK83_SWITCH	OFF
#define	 CORE0_TASK84_SWITCH	OFF
#define	 CORE0_TASK85_SWITCH	OFF
#define	 CORE0_TASK86_SWITCH	OFF
#define	 CORE0_TASK87_SWITCH	OFF
#define	 CORE0_TASK88_SWITCH	OFF
#define	 CORE0_TASK89_SWITCH	OFF
#define	 CORE0_TASK99_SWITCH	OFF
#define	 CORE0_TASK90_SWITCH	OFF
#define	 CORE0_TASK91_SWITCH 	OFF
#define	 CORE0_TASK92_SWITCH 	OFF
#define	 CORE0_TASK93_SWITCH	OFF
#define	 CORE0_TASK94_SWITCH	OFF
#define	 CORE0_TASK95_SWITCH	OFF
#define	 CORE0_TASK96_SWITCH	OFF
#define	 CORE0_TASK97_SWITCH	OFF
#define	 CORE0_TASK98_SWITCH	OFF
#define	 CORE0_TASK99_SWITCH	OFF
#define	 CORE0_TASK100_SWITCH	OFF


typedef enum  {

#if (CORE0_TASK0_SWITCH == ON) 
	 CORE0_TASK_ID0,
#endif
#if (CORE0_TASK1_SWITCH == ON) 
	 CORE0_TASK_ID1,
#endif
#if (CORE0_TASK2_SWITCH == ON) 
	 CORE0_TASK_ID2,
#endif
#if (CORE0_TASK3_SWITCH == ON) 
	 CORE0_TASK_ID3,
#endif
#if (CORE0_TASK4_SWITCH == ON) 
	 CORE0_TASK_ID4,
#endif	 
#if (CORE0_TASK5_SWITCH == ON) 
	 CORE0_TASK_ID5,
#endif	 
#if (CORE0_TASK6_SWITCH == ON) 	
	 CORE0_TASK_ID6,
#endif	 
#if (CORE0_TASK7_SWITCH == ON) 	 
	 CORE0_TASK_ID7,
#endif	 
#if (CORE0_TASK8_SWITCH == ON) 	
	 CORE0_TASK_ID8,
#endif	 
#if (CORE0_TASK9_SWITCH == ON) 	
	 CORE0_TASK_ID9,
#endif	 
#if (CORE0_TASK10_SWITCH == ON) 		 
	 CORE0_TASK_ID10,
#endif	 
#if (CORE0_TASK11_SWITCH == ON) 	
	 CORE0_TASK_ID11,
#endif	 
#if (CORE0_TASK12_SWITCH == ON) 	
	 CORE0_TASK_ID12,
#endif	 
#if (CORE0_TASK13_SWITCH == ON) 	
	 CORE0_TASK_ID13,
#endif	 
#if (CORE0_TASK14_SWITCH == ON) 	
	 CORE0_TASK_ID14,
#endif	 
#if (CORE0_TASK15_SWITCH == ON) 	
	 CORE0_TASK_ID15,
#endif	 
#if (CORE0_TASK16_SWITCH == ON) 	
	 CORE0_TASK_ID16,
#endif	 
#if (CORE0_TASK17_SWITCH == ON) 	
	 CORE0_TASK_ID17,
#endif	 
#if (CORE0_TASK18_SWITCH == ON) 	
	 CORE0_TASK_ID18,
#endif	 
#if (CORE0_TASK19_SWITCH == ON) 	
	 CORE0_TASK_ID19,
#endif	 
#if (CORE0_TASK20_SWITCH == ON) 	
	 CORE0_TASK_ID20,
#endif	 
#if (CORE0_TASK21_SWITCH == ON) 	
	 CORE0_TASK_ID21,
#endif	 
#if (CORE0_TASK22_SWITCH == ON) 	
	 CORE0_TASK_ID22,
#endif	 
#if (CORE0_TASK23_SWITCH == ON) 	
	 CORE0_TASK_ID23,
#endif	 
#if (CORE0_TASK24_SWITCH == ON) 	
	 CORE0_TASK_ID24,
#endif	 
#if (CORE0_TASK25_SWITCH == ON) 	
	 CORE0_TASK_ID25,
#endif	 
#if (CORE0_TASK26_SWITCH == ON) 	
	 CORE0_TASK_ID26,
#endif	 
#if (CORE0_TASK27_SWITCH == ON) 	
	 CORE0_TASK_ID27,
#endif	 
#if (CORE0_TASK28_SWITCH == ON) 	
	 CORE0_TASK_ID28,
#endif	 
#if (CORE0_TASK29_SWITCH == ON) 	
	 CORE0_TASK_ID29,
#endif	 
#if (CORE0_TASK30_SWITCH == ON) 	
	 CORE0_TASK_ID30,
#endif	 
#if (CORE0_TASK31_SWITCH == ON) 	
	 CORE0_TASK_ID31,
#endif	 
#if (CORE0_TASK32_SWITCH == ON) 		 
	 CORE0_TASK_ID32,
#endif	 
#if (CORE0_TASK33_SWITCH == ON) 	
	 CORE0_TASK_ID33,
#endif	 
#if (CORE0_TASK34_SWITCH == ON) 	
	 CORE0_TASK_ID34,
#endif	 
#if (CORE0_TASK35_SWITCH == ON) 	
	 CORE0_TASK_ID35,
#endif	 
#if (CORE0_TASK36_SWITCH == ON) 	
	 CORE0_TASK_ID36,
#endif	 
#if (CORE0_TASK37_SWITCH == ON) 	
	 CORE0_TASK_ID37,
#endif	 
#if (CORE0_TASK38_SWITCH == ON) 	
	 CORE0_TASK_ID38,
#endif	 
#if (CORE0_TASK39_SWITCH == ON) 	
	 CORE0_TASK_ID39,
#endif	 
#if (CORE0_TASK40_SWITCH == ON) 	
	 CORE0_TASK_ID40,
#endif	 
#if (CORE0_TASK41_SWITCH == ON) 	
	 CORE0_TASK_ID41,
#endif	 
#if (CORE0_TASK42_SWITCH == ON) 	
	 CORE0_TASK_ID42,
#endif	 
#if (CORE0_TASK43_SWITCH == ON) 	
	 CORE0_TASK_ID43,
#endif	 
#if (CORE0_TASK44_SWITCH == ON) 	
	 CORE0_TASK_ID44,
#endif	 
#if (CORE0_TASK45_SWITCH == ON) 	
	 CORE0_TASK_ID45,
#endif	 
#if (CORE0_TASK46_SWITCH == ON) 	
	 CORE0_TASK_ID46,
#endif	 
#if (CORE0_TASK47_SWITCH == ON) 	
	 CORE0_TASK_ID47,
#endif	 
#if (CORE0_TASK48_SWITCH == ON) 	
	 CORE0_TASK_ID48,
#endif	 
#if (CORE0_TASK49_SWITCH == ON) 	
	 CORE0_TASK_ID49,
#endif	 
#if (CORE0_TASK50_SWITCH == ON) 	
	 CORE0_TASK_ID50,
#endif	 
#if (CORE0_TASK51_SWITCH == ON) 	
	 CORE0_TASK_ID51,
#endif	 
#if (CORE0_TASK52_SWITCH == ON) 	
	 CORE0_TASK_ID52,
#endif	 
#if (CORE0_TASK53_SWITCH == ON) 	
	 CORE0_TASK_ID53,
#endif	 
#if (CORE0_TASK54_SWITCH == ON) 	
	 CORE0_TASK_ID54,
#endif	 
#if (CORE0_TASK55_SWITCH == ON) 	
	 CORE0_TASK_ID55,
#endif	 
#if (CORE0_TASK56_SWITCH == ON) 	
	 CORE0_TASK_ID56,
#endif	 
#if (CORE0_TASK57_SWITCH == ON) 	
	 CORE0_TASK_ID57,
#endif	 
#if (CORE0_TASK58_SWITCH == ON) 	
	 CORE0_TASK_ID58,
#endif	 
#if (CORE0_TASK59_SWITCH == ON) 	
	 CORE0_TASK_ID59,
#endif	 
#if (CORE0_TASK60_SWITCH == ON) 	
	 CORE0_TASK_ID60,
#endif	 
#if (CORE0_TASK61_SWITCH == ON) 	
	 CORE0_TASK_ID61,
#endif	 
#if (CORE0_TASK62_SWITCH == ON) 	
	 CORE0_TASK_ID62,
#endif	 
#if (CORE0_TASK63_SWITCH == ON) 	
	 CORE0_TASK_ID63,
#endif	 
#if (CORE0_TASK64_SWITCH == ON) 	
	 CORE0_TASK_ID64,
#endif	 
#if (CORE0_TASK65_SWITCH == ON) 	
	 CORE0_TASK_ID65,
#endif	 
#if (CORE0_TASK66_SWITCH == ON) 	
	 CORE0_TASK_ID66,
#endif	 
#if (CORE0_TASK67_SWITCH == ON) 	
	 CORE0_TASK_ID67,
#endif	 
#if (CORE0_TASK68_SWITCH == ON) 	
	 CORE0_TASK_ID68,
#endif	 
#if (CORE0_TASK69_SWITCH == ON) 	
	 CORE0_TASK_ID69,
#endif	 
#if (CORE0_TASK70_SWITCH == ON) 	
	 CORE0_TASK_ID70,
#endif	 
#if (CORE0_TASK71_SWITCH == ON) 	
	 CORE0_TASK_ID71,
#endif	 
#if (CORE0_TASK72_SWITCH == ON) 	
	 CORE0_TASK_ID72,
#endif	 
#if (CORE0_TASK73_SWITCH == ON) 	
	 CORE0_TASK_ID73,
#endif	 
#if (CORE0_TASK74_SWITCH == ON) 	
	 CORE0_TASK_ID74,
#endif	 
#if (CORE0_TASK75_SWITCH == ON) 	
	 CORE0_TASK_ID75,
#endif	 
#if (CORE0_TASK76_SWITCH == ON) 	
	 CORE0_TASK_ID76,
#endif	 
#if (CORE0_TASK77_SWITCH == ON) 	
	 CORE0_TASK_ID77,
#endif	 
#if (CORE0_TASK78_SWITCH == ON) 	
	 CORE0_TASK_ID78,
#endif	 
#if (CORE0_TASK79_SWITCH == ON) 	
	 CORE0_TASK_ID79,
#endif	 
#if (CORE0_TASK80_SWITCH == ON) 	
	 CORE0_TASK_ID80,
#endif	 
#if (CORE0_TASK81_SWITCH == ON) 	
	 CORE0_TASK_ID81,
#endif	 
#if (CORE0_TASK82_SWITCH == ON) 	
	 CORE0_TASK_ID82,
#endif	 
#if (CORE0_TASK83_SWITCH == ON) 	
	 CORE0_TASK_ID83,
#endif	 
#if (CORE0_TASK84_SWITCH == ON) 	
	 CORE0_TASK_ID84,
#endif	 
#if (CORE0_TASK85_SWITCH == ON) 	
	 CORE0_TASK_ID85,
#endif	 
#if (CORE0_TASK86_SWITCH == ON) 	
	 CORE0_TASK_ID86,
#endif	 
#if (CORE0_TASK87_SWITCH == ON) 	
	 CORE0_TASK_ID87,
#endif	 
#if (CORE0_TASK88_SWITCH == ON) 	
	 CORE0_TASK_ID88,
#endif	 
#if (CORE0_TASK89_SWITCH == ON) 	
	 CORE0_TASK_ID89,
#endif	 
#if (CORE0_TASK90_SWITCH == ON) 	
	 CORE0_TASK_ID90,
#endif	 
#if (CORE0_TASK91_SWITCH == ON) 	
	 CORE0_TASK_ID91,
#endif	 
#if (CORE0_TASK92_SWITCH == ON) 	
	 CORE0_TASK_ID92,
#endif	 
#if (CORE0_TASK93_SWITCH == ON) 	
	 CORE0_TASK_ID93,
#endif	 
#if (CORE0_TASK94_SWITCH == ON) 	
	 CORE0_TASK_ID94,	
#endif	 
#if (CORE0_TASK95_SWITCH == ON) 	
	 CORE0_TASK_ID95,
#endif	 
#if (CORE0_TASK96_SWITCH == ON) 	
	 CORE0_TASK_ID96,
#endif	 
#if (CORE0_TASK97_SWITCH == ON) 	
	 CORE0_TASK_ID97,
#endif	 
#if (CORE0_TASK98_SWITCH == ON) 	
	 CORE0_TASK_ID98,
#endif	 
#if (CORE0_TASK99_SWITCH == ON) 	
	 CORE0_TASK_ID99,
#endif	 
#if (CORE0_TASK100_SWITCH == ON) 	
	 CORE0_TASK_ID100,
#endif	
	 CORE0_TASK_MAX_ID_NUM,
}CORE0_TASK_ID_t;

#endif /* End of CORE0_TASK_MANAGER_H_ */
