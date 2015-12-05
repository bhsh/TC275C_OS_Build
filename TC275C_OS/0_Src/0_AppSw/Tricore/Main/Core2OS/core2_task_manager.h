/****************************************************************************/
/* FILE NAME:    core2_task_manager.h                                       */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes switch definition of AURIX core2 tasks */
/*               os                                                         */
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/ 
#ifndef CRRE2_TASK_MANAGER_H_
#define CRRE2_TASK_MANAGER_H_

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* <CORE2> Task Switch Configuration                                        */
/****************************************************************************/
#define  CORE2_OS_SWITCH        OFF  /* <CORE2> Switch off or on the os of core2 */

#define	 CORE2_TASK0_SWITCH	    ON
#define	 CORE2_TASK1_SWITCH 	ON
#define	 CORE2_TASK2_SWITCH 	ON
#define	 CORE2_TASK3_SWITCH	    ON
#define	 CORE2_TASK4_SWITCH	    ON
#define	 CORE2_TASK5_SWITCH	    ON
#define	 CORE2_TASK6_SWITCH	    ON
#define	 CORE2_TASK7_SWITCH	    ON
#define	 CORE2_TASK8_SWITCH	    ON
#define	 CORE2_TASK9_SWITCH	    ON
#define	 CORE2_TASK10_SWITCH	ON
#define	 CORE2_TASK11_SWITCH 	OFF
#define	 CORE2_TASK12_SWITCH 	OFF
#define	 CORE2_TASK13_SWITCH	OFF
#define	 CORE2_TASK14_SWITCH	OFF
#define	 CORE2_TASK15_SWITCH	OFF
#define	 CORE2_TASK16_SWITCH	OFF
#define	 CORE2_TASK17_SWITCH	OFF
#define	 CORE2_TASK18_SWITCH	OFF
#define	 CORE2_TASK19_SWITCH	OFF
#define	 CORE2_TASK20_SWITCH	OFF
#define	 CORE2_TASK21_SWITCH 	OFF
#define	 CORE2_TASK22_SWITCH 	OFF
#define	 CORE2_TASK23_SWITCH	OFF
#define	 CORE2_TASK24_SWITCH	OFF
#define	 CORE2_TASK25_SWITCH	OFF
#define	 CORE2_TASK26_SWITCH	OFF
#define	 CORE2_TASK27_SWITCH	OFF
#define	 CORE2_TASK28_SWITCH	OFF
#define	 CORE2_TASK29_SWITCH	OFF
#define	 CORE2_TASK30_SWITCH	OFF
#define	 CORE2_TASK31_SWITCH 	OFF
#define	 CORE2_TASK32_SWITCH 	OFF
#define	 CORE2_TASK33_SWITCH	OFF
#define	 CORE2_TASK34_SWITCH	OFF
#define	 CORE2_TASK35_SWITCH	OFF
#define	 CORE2_TASK36_SWITCH	OFF
#define	 CORE2_TASK37_SWITCH	OFF
#define	 CORE2_TASK38_SWITCH	OFF
#define	 CORE2_TASK39_SWITCH	OFF
#define	 CORE2_TASK40_SWITCH	OFF
#define	 CORE2_TASK41_SWITCH 	OFF
#define	 CORE2_TASK42_SWITCH 	OFF
#define	 CORE2_TASK43_SWITCH	OFF
#define	 CORE2_TASK44_SWITCH	OFF
#define	 CORE2_TASK45_SWITCH	OFF
#define	 CORE2_TASK46_SWITCH	OFF
#define	 CORE2_TASK47_SWITCH	OFF
#define	 CORE2_TASK48_SWITCH	OFF
#define	 CORE2_TASK49_SWITCH	OFF
#define	 CORE2_TASK50_SWITCH	OFF
#define	 CORE2_TASK51_SWITCH 	OFF
#define	 CORE2_TASK52_SWITCH 	OFF
#define	 CORE2_TASK53_SWITCH	OFF
#define	 CORE2_TASK54_SWITCH	OFF
#define	 CORE2_TASK55_SWITCH	OFF
#define	 CORE2_TASK56_SWITCH	OFF
#define	 CORE2_TASK57_SWITCH	OFF
#define	 CORE2_TASK58_SWITCH	OFF
#define	 CORE2_TASK59_SWITCH	OFF
#define	 CORE2_TASK60_SWITCH	OFF
#define	 CORE2_TASK61_SWITCH 	OFF
#define	 CORE2_TASK62_SWITCH 	OFF
#define	 CORE2_TASK63_SWITCH	OFF
#define	 CORE2_TASK64_SWITCH	OFF
#define	 CORE2_TASK65_SWITCH	OFF
#define	 CORE2_TASK66_SWITCH	OFF
#define	 CORE2_TASK67_SWITCH	OFF
#define	 CORE2_TASK68_SWITCH	OFF
#define	 CORE2_TASK69_SWITCH	OFF
#define	 CORE2_TASK70_SWITCH	OFF
#define	 CORE2_TASK71_SWITCH 	OFF
#define	 CORE2_TASK72_SWITCH 	OFF
#define	 CORE2_TASK73_SWITCH	OFF
#define	 CORE2_TASK74_SWITCH	OFF
#define	 CORE2_TASK75_SWITCH	OFF
#define	 CORE2_TASK76_SWITCH	OFF
#define	 CORE2_TASK77_SWITCH	OFF
#define	 CORE2_TASK78_SWITCH	OFF
#define	 CORE2_TASK79_SWITCH	OFF
#define	 CORE2_TASK80_SWITCH	OFF
#define	 CORE2_TASK81_SWITCH 	OFF
#define	 CORE2_TASK82_SWITCH 	OFF
#define	 CORE2_TASK83_SWITCH	OFF
#define	 CORE2_TASK84_SWITCH	OFF
#define	 CORE2_TASK85_SWITCH	OFF
#define	 CORE2_TASK86_SWITCH	OFF
#define	 CORE2_TASK87_SWITCH	OFF
#define	 CORE2_TASK88_SWITCH	OFF
#define	 CORE2_TASK89_SWITCH	OFF
#define	 CORE2_TASK99_SWITCH	OFF
#define	 CORE2_TASK90_SWITCH	OFF
#define	 CORE2_TASK91_SWITCH 	OFF
#define	 CORE2_TASK92_SWITCH 	OFF
#define	 CORE2_TASK93_SWITCH	OFF
#define	 CORE2_TASK94_SWITCH	OFF
#define	 CORE2_TASK95_SWITCH	OFF
#define	 CORE2_TASK96_SWITCH	OFF
#define	 CORE2_TASK97_SWITCH	OFF
#define	 CORE2_TASK98_SWITCH	OFF
#define	 CORE2_TASK99_SWITCH	OFF
#define	 CORE2_TASK100_SWITCH	OFF

typedef enum  {

#if (CORE2_TASK0_SWITCH == ON) 
	 CORE2_TASK_ID0,
#endif
#if (CORE2_TASK1_SWITCH == ON) 
	 CORE2_TASK_ID1,
#endif
#if (CORE2_TASK2_SWITCH == ON) 
	 CORE2_TASK_ID2,
#endif
#if (CORE2_TASK3_SWITCH == ON) 
	 CORE2_TASK_ID3,
#endif
#if (CORE2_TASK4_SWITCH == ON) 
	 CORE2_TASK_ID4,
#endif	 
#if (CORE2_TASK5_SWITCH == ON) 
	 CORE2_TASK_ID5,
#endif	 
#if (CORE2_TASK6_SWITCH == ON) 	
	 CORE2_TASK_ID6,
#endif	 
#if (CORE2_TASK7_SWITCH == ON) 	 
	 CORE2_TASK_ID7,
#endif	 
#if (CORE2_TASK8_SWITCH == ON) 	
	 CORE2_TASK_ID8,
#endif	 
#if (CORE2_TASK9_SWITCH == ON) 	
	 CORE2_TASK_ID9,
#endif	 
#if (CORE2_TASK10_SWITCH == ON) 		 
	 CORE2_TASK_ID10,
#endif	 
#if (CORE2_TASK11_SWITCH == ON) 	
	 CORE2_TASK_ID11,
#endif	 
#if (CORE2_TASK12_SWITCH == ON) 	
	 CORE2_TASK_ID12,
#endif	 
#if (CORE2_TASK13_SWITCH == ON) 	
	 CORE2_TASK_ID13,
#endif	 
#if (CORE2_TASK14_SWITCH == ON) 	
	 CORE2_TASK_ID14,
#endif	 
#if (CORE2_TASK15_SWITCH == ON) 	
	 CORE2_TASK_ID15,
#endif	 
#if (CORE2_TASK16_SWITCH == ON) 	
	 CORE2_TASK_ID16,
#endif	 
#if (CORE2_TASK17_SWITCH == ON) 	
	 CORE2_TASK_ID17,
#endif	 
#if (CORE2_TASK18_SWITCH == ON) 	
	 CORE2_TASK_ID18,
#endif	 
#if (CORE2_TASK19_SWITCH == ON) 	
	 CORE2_TASK_ID19,
#endif	 
#if (CORE2_TASK20_SWITCH == ON) 	
	 CORE2_TASK_ID20,
#endif	 
#if (CORE2_TASK21_SWITCH == ON) 	
	 CORE2_TASK_ID21,
#endif	 
#if (CORE2_TASK22_SWITCH == ON) 	
	 CORE2_TASK_ID22,
#endif	 
#if (CORE2_TASK23_SWITCH == ON) 	
	 CORE2_TASK_ID23,
#endif	 
#if (CORE2_TASK24_SWITCH == ON) 	
	 CORE2_TASK_ID24,
#endif	 
#if (CORE2_TASK25_SWITCH == ON) 	
	 CORE2_TASK_ID25,
#endif	 
#if (CORE2_TASK26_SWITCH == ON) 	
	 CORE2_TASK_ID26,
#endif	 
#if (CORE2_TASK27_SWITCH == ON) 	
	 CORE2_TASK_ID27,
#endif	 
#if (CORE2_TASK28_SWITCH == ON) 	
	 CORE2_TASK_ID28,
#endif	 
#if (CORE2_TASK29_SWITCH == ON) 	
	 CORE2_TASK_ID29,
#endif	 
#if (CORE2_TASK30_SWITCH == ON) 	
	 CORE2_TASK_ID30,
#endif	 
#if (CORE2_TASK31_SWITCH == ON) 	
	 CORE2_TASK_ID31,
#endif	 
#if (CORE2_TASK32_SWITCH == ON) 		 
	 CORE2_TASK_ID32,
#endif	 
#if (CORE2_TASK33_SWITCH == ON) 	
	 CORE2_TASK_ID33,
#endif	 
#if (CORE2_TASK34_SWITCH == ON) 	
	 CORE2_TASK_ID34,
#endif	 
#if (CORE2_TASK35_SWITCH == ON) 	
	 CORE2_TASK_ID35,
#endif	 
#if (CORE2_TASK36_SWITCH == ON) 	
	 CORE2_TASK_ID36,
#endif	 
#if (CORE2_TASK37_SWITCH == ON) 	
	 CORE2_TASK_ID37,
#endif	 
#if (CORE2_TASK38_SWITCH == ON) 	
	 CORE2_TASK_ID38,
#endif	 
#if (CORE2_TASK39_SWITCH == ON) 	
	 CORE2_TASK_ID39,
#endif	 
#if (CORE2_TASK40_SWITCH == ON) 	
	 CORE2_TASK_ID40,
#endif	 
#if (CORE2_TASK41_SWITCH == ON) 	
	 CORE2_TASK_ID41,
#endif	 
#if (CORE2_TASK42_SWITCH == ON) 	
	 CORE2_TASK_ID42,
#endif	 
#if (CORE2_TASK43_SWITCH == ON) 	
	 CORE2_TASK_ID43,
#endif	 
#if (CORE2_TASK44_SWITCH == ON) 	
	 CORE2_TASK_ID44,
#endif	 
#if (CORE2_TASK45_SWITCH == ON) 	
	 CORE2_TASK_ID45,
#endif	 
#if (CORE2_TASK46_SWITCH == ON) 	
	 CORE2_TASK_ID46,
#endif	 
#if (CORE2_TASK47_SWITCH == ON) 	
	 CORE2_TASK_ID47,
#endif	 
#if (CORE2_TASK48_SWITCH == ON) 	
	 CORE2_TASK_ID48,
#endif	 
#if (CORE2_TASK49_SWITCH == ON) 	
	 CORE2_TASK_ID49,
#endif	 
#if (CORE2_TASK50_SWITCH == ON) 	
	 CORE2_TASK_ID50,
#endif	 
#if (CORE2_TASK51_SWITCH == ON) 	
	 CORE2_TASK_ID51,
#endif	 
#if (CORE2_TASK52_SWITCH == ON) 	
	 CORE2_TASK_ID52,
#endif	 
#if (CORE2_TASK53_SWITCH == ON) 	
	 CORE2_TASK_ID53,
#endif	 
#if (CORE2_TASK54_SWITCH == ON) 	
	 CORE2_TASK_ID54,
#endif	 
#if (CORE2_TASK55_SWITCH == ON) 	
	 CORE2_TASK_ID55,
#endif	 
#if (CORE2_TASK56_SWITCH == ON) 	
	 CORE2_TASK_ID56,
#endif	 
#if (CORE2_TASK57_SWITCH == ON) 	
	 CORE2_TASK_ID57,
#endif	 
#if (CORE2_TASK58_SWITCH == ON) 	
	 CORE2_TASK_ID58,
#endif	 
#if (CORE2_TASK59_SWITCH == ON) 	
	 CORE2_TASK_ID59,
#endif	 
#if (CORE2_TASK60_SWITCH == ON) 	
	 CORE2_TASK_ID60,
#endif	 
#if (CORE2_TASK61_SWITCH == ON) 	
	 CORE2_TASK_ID61,
#endif	 
#if (CORE2_TASK62_SWITCH == ON) 	
	 CORE2_TASK_ID62,
#endif	 
#if (CORE2_TASK63_SWITCH == ON) 	
	 CORE2_TASK_ID63,
#endif	 
#if (CORE2_TASK64_SWITCH == ON) 	
	 CORE2_TASK_ID64,
#endif	 
#if (CORE2_TASK65_SWITCH == ON) 	
	 CORE2_TASK_ID65,
#endif	 
#if (CORE2_TASK66_SWITCH == ON) 	
	 CORE2_TASK_ID66,
#endif	 
#if (CORE2_TASK67_SWITCH == ON) 	
	 CORE2_TASK_ID67,
#endif	 
#if (CORE2_TASK68_SWITCH == ON) 	
	 CORE2_TASK_ID68,
#endif	 
#if (CORE2_TASK69_SWITCH == ON) 	
	 CORE2_TASK_ID69,
#endif	 
#if (CORE2_TASK70_SWITCH == ON) 	
	 CORE2_TASK_ID70,
#endif	 
#if (CORE2_TASK71_SWITCH == ON) 	
	 CORE2_TASK_ID71,
#endif	 
#if (CORE2_TASK72_SWITCH == ON) 	
	 CORE2_TASK_ID72,
#endif	 
#if (CORE2_TASK73_SWITCH == ON) 	
	 CORE2_TASK_ID73,
#endif	 
#if (CORE2_TASK74_SWITCH == ON) 	
	 CORE2_TASK_ID74,
#endif	 
#if (CORE2_TASK75_SWITCH == ON) 	
	 CORE2_TASK_ID75,
#endif	 
#if (CORE2_TASK76_SWITCH == ON) 	
	 CORE2_TASK_ID76,
#endif	 
#if (CORE2_TASK77_SWITCH == ON) 	
	 CORE2_TASK_ID77,
#endif	 
#if (CORE2_TASK78_SWITCH == ON) 	
	 CORE2_TASK_ID78,
#endif	 
#if (CORE2_TASK79_SWITCH == ON) 	
	 CORE2_TASK_ID79,
#endif	 
#if (CORE2_TASK80_SWITCH == ON) 	
	 CORE2_TASK_ID80,
#endif	 
#if (CORE2_TASK81_SWITCH == ON) 	
	 CORE2_TASK_ID81,
#endif	 
#if (CORE2_TASK82_SWITCH == ON) 	
	 CORE2_TASK_ID82,
#endif	 
#if (CORE2_TASK83_SWITCH == ON) 	
	 CORE2_TASK_ID83,
#endif	 
#if (CORE2_TASK84_SWITCH == ON) 	
	 CORE2_TASK_ID84,
#endif	 
#if (CORE2_TASK85_SWITCH == ON) 	
	 CORE2_TASK_ID85,
#endif	 
#if (CORE2_TASK86_SWITCH == ON) 	
	 CORE2_TASK_ID86,
#endif	 
#if (CORE2_TASK87_SWITCH == ON) 	
	 CORE2_TASK_ID87,
#endif	 
#if (CORE2_TASK88_SWITCH == ON) 	
	 CORE2_TASK_ID88,
#endif	 
#if (CORE2_TASK89_SWITCH == ON) 	
	 CORE2_TASK_ID89,
#endif	 
#if (CORE2_TASK90_SWITCH == ON) 	
	 CORE2_TASK_ID90,
#endif	 
#if (CORE2_TASK91_SWITCH == ON) 	
	 CORE2_TASK_ID91,
#endif	 
#if (CORE2_TASK92_SWITCH == ON) 	
	 CORE2_TASK_ID92,
#endif	 
#if (CORE2_TASK93_SWITCH == ON) 	
	 CORE2_TASK_ID93,
#endif	 
#if (CORE2_TASK94_SWITCH == ON) 	
	 CORE2_TASK_ID94,	
#endif	 
#if (CORE2_TASK95_SWITCH == ON) 	
	 CORE2_TASK_ID95,
#endif	 
#if (CORE2_TASK96_SWITCH == ON) 	
	 CORE2_TASK_ID96,
#endif	 
#if (CORE2_TASK97_SWITCH == ON) 	
	 CORE2_TASK_ID97,
#endif	 
#if (CORE2_TASK98_SWITCH == ON) 	
	 CORE2_TASK_ID98,
#endif	 
#if (CORE2_TASK99_SWITCH == ON) 	
	 CORE2_TASK_ID99,
#endif	 
#if (CORE2_TASK100_SWITCH == ON) 	
	 CORE2_TASK_ID100,
#endif	
	 CORE2_TASK_MAX_ID_NUM,
}CORE2_TASK_ID_t;

#if (CORE2_TASK0_SWITCH != ON)
  #error "<CORE2> The TASK0 must be on, or there will a compiler error."
#endif

#endif  /* End of CORE2_TASK_MANAGER_H_ */
