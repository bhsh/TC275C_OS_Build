/*-----------------------------------------------------------------------------------
|
|   File name:    Appcore0.c
|   Created on:   Aug 26, 2015
|   Author:       Yanpeng.xi
|   Description:
|                 Multicore OS based on Aurix 275C app kit and TASKING 4.3 compiler
|
--------------------------------------------------------------------------------------*/

#define  THREAD_GLOBAL_CONFIG_DEFINITION ENABLE
#include "os_type.h"
#include "os.h"
#include <stdlib.h>
#include "core0_tasks.h"
#include "thread_cfg.h"
#include "kernel_abstract.h"
#include "os_trace.h"


#pragma align 16

// period threads...
#if (CORE0_THREAD0_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th0,CORE0_THREAD0_PRIORITY,SCHED_FIFO,CORE0_THREAD0_STACK_SIZE)
#endif
#if (CORE0_THREAD1_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th1, CORE0_THREAD1_PRIORITY,SCHED_FIFO,CORE0_THREAD1_STACK_SIZE)
#endif
#if (CORE0_THREAD2_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th2, CORE0_THREAD2_PRIORITY,SCHED_FIFO,CORE0_THREAD2_STACK_SIZE)
#endif
#if (CORE0_THREAD3_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th3, CORE0_THREAD3_PRIORITY,SCHED_FIFO,CORE0_THREAD3_STACK_SIZE)
#endif
#if (CORE0_THREAD4_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th4, CORE0_THREAD4_PRIORITY,SCHED_FIFO,CORE0_THREAD4_STACK_SIZE)
#endif
#if (CORE0_THREAD5_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th5, CORE0_THREAD5_PRIORITY,SCHED_FIFO,CORE0_THREAD5_STACK_SIZE)
#endif
#if (CORE0_THREAD6_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th6, CORE0_THREAD6_PRIORITY,SCHED_FIFO,CORE0_THREAD6_STACK_SIZE)
#endif
#if (CORE0_THREAD7_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th7, CORE0_THREAD7_PRIORITY,SCHED_FIFO,CORE0_THREAD7_STACK_SIZE)
#endif
#if (CORE0_THREAD8_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th8, CORE0_THREAD8_PRIORITY,SCHED_FIFO,CORE0_THREAD8_STACK_SIZE)
#endif
#if (CORE0_THREAD9_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th9, CORE0_THREAD9_PRIORITY,SCHED_FIFO,CORE0_THREAD9_STACK_SIZE)
#endif
#if (CORE0_THREAD10_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th10,CORE0_THREAD10_PRIORITY,SCHED_FIFO,CORE0_THREAD10_STACK_SIZE)
#endif
#if (CORE0_THREAD11_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th11,CORE0_THREAD11_PRIORITY,SCHED_FIFO,CORE0_THREAD11_STACK_SIZE)
#endif
#if (CORE0_THREAD12_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th12,CORE0_THREAD12_PRIORITY,SCHED_FIFO,CORE0_THREAD12_STACK_SIZE)
#endif
#if (CORE0_THREAD13_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th13,CORE0_THREAD13_PRIORITY,SCHED_FIFO,CORE0_THREAD13_STACK_SIZE)
#endif
#if (CORE0_THREAD14_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th14,CORE0_THREAD14_PRIORITY,SCHED_FIFO,CORE0_THREAD14_STACK_SIZE)
#endif
#if (CORE0_THREAD15_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th15,CORE0_THREAD15_PRIORITY,SCHED_FIFO,CORE0_THREAD15_STACK_SIZE)
#endif
#if (CORE0_THREAD16_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th16,CORE0_THREAD16_PRIORITY,SCHED_FIFO,CORE0_THREAD16_STACK_SIZE)
#endif
#if (CORE0_THREAD17_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th17,CORE0_THREAD17_PRIORITY,SCHED_FIFO,CORE0_THREAD17_STACK_SIZE)
#endif
#if (CORE0_THREAD18_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th18,CORE0_THREAD18_PRIORITY,SCHED_FIFO,CORE0_THREAD18_STACK_SIZE)
#endif
#if (CORE0_THREAD19_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th19,CORE0_THREAD19_PRIORITY,SCHED_FIFO,CORE0_THREAD19_STACK_SIZE)
#endif
#if (CORE0_THREAD20_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th20,CORE0_THREAD20_PRIORITY,SCHED_FIFO,CORE0_THREAD20_STACK_SIZE)
#endif
#if (CORE0_THREAD21_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th21,CORE0_THREAD21_PRIORITY,SCHED_FIFO,CORE0_THREAD21_STACK_SIZE)
#endif
#if (CORE0_THREAD22_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th22,CORE0_THREAD22_PRIORITY,SCHED_FIFO,CORE0_THREAD22_STACK_SIZE)
#endif
#if (CORE0_THREAD23_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th23,CORE0_THREAD23_PRIORITY,SCHED_FIFO,CORE0_THREAD23_STACK_SIZE)
#endif
#if (CORE0_THREAD24_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th24,CORE0_THREAD24_PRIORITY,SCHED_FIFO,CORE0_THREAD24_STACK_SIZE)
#endif
#if (CORE0_THREAD25_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th25,CORE0_THREAD25_PRIORITY,SCHED_FIFO,CORE0_THREAD25_STACK_SIZE)
#endif
#if (CORE0_THREAD26_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th26,CORE0_THREAD26_PRIORITY,SCHED_FIFO,CORE0_THREAD26_STACK_SIZE)
#endif
#if (CORE0_THREAD27_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th27,CORE0_THREAD27_PRIORITY,SCHED_FIFO,CORE0_THREAD27_STACK_SIZE)
#endif
#if (CORE0_THREAD28_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th28,CORE0_THREAD28_PRIORITY,SCHED_FIFO,CORE0_THREAD28_STACK_SIZE)
#endif
#if (CORE0_THREAD29_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th29,CORE0_THREAD29_PRIORITY,SCHED_FIFO,CORE0_THREAD29_STACK_SIZE)
#endif
#if (CORE0_THREAD30_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th30,CORE0_THREAD30_PRIORITY,SCHED_FIFO,CORE0_THREAD30_STACK_SIZE)
#endif
#if (CORE0_THREAD31_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th31,CORE0_THREAD31_PRIORITY,SCHED_FIFO,CORE0_THREAD31_STACK_SIZE)
#endif
#if (CORE0_THREAD32_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th32,CORE0_THREAD32_PRIORITY,SCHED_FIFO,CORE0_THREAD32_STACK_SIZE)
#endif
#if (CORE0_THREAD33_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th33,CORE0_THREAD33_PRIORITY,SCHED_FIFO,CORE0_THREAD33_STACK_SIZE)
#endif
#if (CORE0_THREAD34_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th34,CORE0_THREAD34_PRIORITY,SCHED_FIFO,CORE0_THREAD34_STACK_SIZE)
#endif
#if (CORE0_THREAD35_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th35,CORE0_THREAD35_PRIORITY,SCHED_FIFO,CORE0_THREAD35_STACK_SIZE)
#endif
#if (CORE0_THREAD36_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th36,CORE0_THREAD36_PRIORITY,SCHED_FIFO,CORE0_THREAD36_STACK_SIZE)
#endif
#if (CORE0_THREAD37_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th37,CORE0_THREAD37_PRIORITY,SCHED_FIFO,CORE0_THREAD37_STACK_SIZE)
#endif
#if (CORE0_THREAD38_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th38,CORE0_THREAD38_PRIORITY,SCHED_FIFO,CORE0_THREAD38_STACK_SIZE)
#endif
#if (CORE0_THREAD39_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th39,CORE0_THREAD39_PRIORITY,SCHED_FIFO,CORE0_THREAD39_STACK_SIZE)
#endif
#if (CORE0_THREAD40_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th40,CORE0_THREAD40_PRIORITY,SCHED_FIFO,CORE0_THREAD40_STACK_SIZE)
#endif
#if (CORE0_THREAD41_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th41,CORE0_THREAD41_PRIORITY,SCHED_FIFO,CORE0_THREAD41_STACK_SIZE)
#endif
#if (CORE0_THREAD42_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th42,CORE0_THREAD42_PRIORITY,SCHED_FIFO,CORE0_THREAD42_STACK_SIZE)
#endif
#if (CORE0_THREAD43_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th43,CORE0_THREAD43_PRIORITY,SCHED_FIFO,CORE0_THREAD43_STACK_SIZE)
#endif
#if (CORE0_THREAD44_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th44,CORE0_THREAD44_PRIORITY,SCHED_FIFO,CORE0_THREAD44_STACK_SIZE)
#endif
#if (CORE0_THREAD45_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th45,CORE0_THREAD45_PRIORITY,SCHED_FIFO,CORE0_THREAD45_STACK_SIZE)
#endif
#if (CORE0_THREAD46_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th46,CORE0_THREAD46_PRIORITY,SCHED_FIFO,CORE0_THREAD46_STACK_SIZE)
#endif
#if (CORE0_THREAD47_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th47,CORE0_THREAD47_PRIORITY,SCHED_FIFO,CORE0_THREAD47_STACK_SIZE)
#endif
#if (CORE0_THREAD48_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th48,CORE0_THREAD48_PRIORITY,SCHED_FIFO,CORE0_THREAD48_STACK_SIZE)
#endif
#if (CORE0_THREAD49_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th49,CORE0_THREAD49_PRIORITY,SCHED_FIFO,CORE0_THREAD49_STACK_SIZE)
#endif
#if (CORE0_THREAD50_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th50,CORE0_THREAD50_PRIORITY,SCHED_FIFO,CORE0_THREAD50_STACK_SIZE)
#endif
#if (CORE0_THREAD51_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th51,CORE0_THREAD51_PRIORITY,SCHED_FIFO,CORE0_THREAD51_STACK_SIZE)
#endif
#if (CORE0_THREAD52_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th52,CORE0_THREAD52_PRIORITY,SCHED_FIFO,CORE0_THREAD52_STACK_SIZE)
#endif
#if (CORE0_THREAD53_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th53,CORE0_THREAD53_PRIORITY,SCHED_FIFO,CORE0_THREAD53_STACK_SIZE)
#endif
#if (CORE0_THREAD54_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th54,CORE0_THREAD54_PRIORITY,SCHED_FIFO,CORE0_THREAD54_STACK_SIZE)
#endif
#if (CORE0_THREAD55_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th55,CORE0_THREAD55_PRIORITY,SCHED_FIFO,CORE0_THREAD55_STACK_SIZE)
#endif
#if (CORE0_THREAD56_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th56,CORE0_THREAD56_PRIORITY,SCHED_FIFO,CORE0_THREAD56_STACK_SIZE)
#endif
#if (CORE0_THREAD57_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th57,CORE0_THREAD57_PRIORITY,SCHED_FIFO,CORE0_THREAD57_STACK_SIZE)
#endif
#if (CORE0_THREAD58_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th58,CORE0_THREAD58_PRIORITY,SCHED_FIFO,CORE0_THREAD58_STACK_SIZE)
#endif
#if (CORE0_THREAD59_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th59,CORE0_THREAD59_PRIORITY,SCHED_FIFO,CORE0_THREAD59_STACK_SIZE)
#endif
#if (CORE0_THREAD60_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th60,CORE0_THREAD60_PRIORITY,SCHED_FIFO,CORE0_THREAD60_STACK_SIZE)
#endif
#if (CORE0_THREAD61_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th61,CORE0_THREAD61_PRIORITY,SCHED_FIFO,CORE0_THREAD61_STACK_SIZE)
#endif
#if (CORE0_THREAD62_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th62,CORE0_THREAD62_PRIORITY,SCHED_FIFO,CORE0_THREAD62_STACK_SIZE)
#endif
#if (CORE0_THREAD63_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th63,CORE0_THREAD63_PRIORITY,SCHED_FIFO,CORE0_THREAD63_STACK_SIZE)
#endif
#if (CORE0_THREAD64_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th64,CORE0_THREAD64_PRIORITY,SCHED_FIFO,CORE0_THREAD64_STACK_SIZE)
#endif
#if (CORE0_THREAD65_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th65,CORE0_THREAD65_PRIORITY,SCHED_FIFO,CORE0_THREAD65_STACK_SIZE)
#endif
#if (CORE0_THREAD66_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th66,CORE0_THREAD66_PRIORITY,SCHED_FIFO,CORE0_THREAD66_STACK_SIZE)
#endif
#if (CORE0_THREAD67_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th67,CORE0_THREAD67_PRIORITY,SCHED_FIFO,CORE0_THREAD67_STACK_SIZE)
#endif
#if (CORE0_THREAD68_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th68,CORE0_THREAD68_PRIORITY,SCHED_FIFO,CORE0_THREAD68_STACK_SIZE)
#endif
#if (CORE0_THREAD69_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th69,CORE0_THREAD69_PRIORITY,SCHED_FIFO,CORE0_THREAD69_STACK_SIZE)
#endif
#if (CORE0_THREAD70_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th70,CORE0_THREAD70_PRIORITY,SCHED_FIFO,CORE0_THREAD70_STACK_SIZE)
#endif
#if (CORE0_THREAD71_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th71,CORE0_THREAD71_PRIORITY,SCHED_FIFO,CORE0_THREAD71_STACK_SIZE)
#endif
#if (CORE0_THREAD72_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th72,CORE0_THREAD72_PRIORITY,SCHED_FIFO,CORE0_THREAD72_STACK_SIZE)
#endif
#if (CORE0_THREAD73_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th73,CORE0_THREAD73_PRIORITY,SCHED_FIFO,CORE0_THREAD73_STACK_SIZE)
#endif
#if (CORE0_THREAD74_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th74,CORE0_THREAD74_PRIORITY,SCHED_FIFO,CORE0_THREAD74_STACK_SIZE)
#endif
#if (CORE0_THREAD75_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th75,CORE0_THREAD75_PRIORITY,SCHED_FIFO,CORE0_THREAD75_STACK_SIZE)
#endif
#if (CORE0_THREAD76_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th76,CORE0_THREAD76_PRIORITY,SCHED_FIFO,CORE0_THREAD76_STACK_SIZE)
#endif
#if (CORE0_THREAD77_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th77,CORE0_THREAD77_PRIORITY,SCHED_FIFO,CORE0_THREAD77_STACK_SIZE)
#endif
#if (CORE0_THREAD78_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th78,CORE0_THREAD78_PRIORITY,SCHED_FIFO,CORE0_THREAD78_STACK_SIZE)
#endif
#if (CORE0_THREAD79_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th79,CORE0_THREAD79_PRIORITY,SCHED_FIFO,CORE0_THREAD79_STACK_SIZE)
#endif
#if (CORE0_THREAD80_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th80,CORE0_THREAD80_PRIORITY,SCHED_FIFO,CORE0_THREAD80_STACK_SIZE)
#endif
#if (CORE0_THREAD81_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th81,CORE0_THREAD81_PRIORITY,SCHED_FIFO,CORE0_THREAD81_STACK_SIZE)
#endif
#if (CORE0_THREAD82_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th82,CORE0_THREAD82_PRIORITY,SCHED_FIFO,CORE0_THREAD82_STACK_SIZE)
#endif
#if (CORE0_THREAD83_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th83,CORE0_THREAD83_PRIORITY,SCHED_FIFO,CORE0_THREAD83_STACK_SIZE)
#endif
#if (CORE0_THREAD84_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th84,CORE0_THREAD84_PRIORITY,SCHED_FIFO,CORE0_THREAD84_STACK_SIZE)
#endif
#if (CORE0_THREAD85_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th85,CORE0_THREAD85_PRIORITY,SCHED_FIFO,CORE0_THREAD85_STACK_SIZE)
#endif
#if (CORE0_THREAD86_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th86,CORE0_THREAD86_PRIORITY,SCHED_FIFO,CORE0_THREAD86_STACK_SIZE)
#endif
#if (CORE0_THREAD87_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th87,CORE0_THREAD87_PRIORITY,SCHED_FIFO,CORE0_THREAD87_STACK_SIZE)
#endif
#if (CORE0_THREAD88_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th88,CORE0_THREAD88_PRIORITY,SCHED_FIFO,CORE0_THREAD88_STACK_SIZE)
#endif
#if (CORE0_THREAD89_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th89,CORE0_THREAD89_PRIORITY,SCHED_FIFO,CORE0_THREAD89_STACK_SIZE)
#endif
#if (CORE0_THREAD90_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th90,CORE0_THREAD90_PRIORITY,SCHED_FIFO,CORE0_THREAD90_STACK_SIZE)
#endif
#if (CORE0_THREAD91_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th91,CORE0_THREAD91_PRIORITY,SCHED_FIFO,CORE0_THREAD91_STACK_SIZE)
#endif
#if (CORE0_THREAD92_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th92,CORE0_THREAD92_PRIORITY,SCHED_FIFO,CORE0_THREAD92_STACK_SIZE)
#endif
#if (CORE0_THREAD93_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th93,CORE0_THREAD93_PRIORITY,SCHED_FIFO,CORE0_THREAD93_STACK_SIZE)
#endif
#if (CORE0_THREAD94_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th94,CORE0_THREAD94_PRIORITY,SCHED_FIFO,CORE0_THREAD94_STACK_SIZE)
#endif
#if (CORE0_THREAD95_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th95,CORE0_THREAD95_PRIORITY,SCHED_FIFO,CORE0_THREAD95_STACK_SIZE)
#endif
#if (CORE0_THREAD96_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th96,CORE0_THREAD96_PRIORITY,SCHED_FIFO,CORE0_THREAD96_STACK_SIZE)
#endif
#if (CORE0_THREAD97_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th97,CORE0_THREAD97_PRIORITY,SCHED_FIFO,CORE0_THREAD97_STACK_SIZE)
#endif
#if (CORE0_THREAD98_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th98,CORE0_THREAD98_PRIORITY,SCHED_FIFO,CORE0_THREAD98_STACK_SIZE)
#endif
#if (CORE0_THREAD99_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th99,CORE0_THREAD99_PRIORITY,SCHED_FIFO,CORE0_THREAD99_STACK_SIZE)
#endif
#if (CORE0_THREAD100_SWITCH == ON) 
PTHREAD_CONTROL_BLOCK(core0_os_th100,CORE0_THREAD100_PRIORITY,SCHED_FIFO,CORE0_THREAD100_STACK_SIZE)
#endif
#pragma align restore

#if (CORE0_THREAD0_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,0)
#endif
#if (CORE0_THREAD1_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,1)
#endif
#if (CORE0_THREAD2_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,2)
#endif
#if (CORE0_THREAD3_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,3)
#endif
#if (CORE0_THREAD4_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,4)
#endif
#if (CORE0_THREAD5_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,5)
#endif
#if (CORE0_THREAD6_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,6)
#endif
#if (CORE0_THREAD7_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,7)
#endif
#if (CORE0_THREAD8_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,8)
#endif
#if (CORE0_THREAD9_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,9)
#endif
#if (CORE0_THREAD10_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,10)
#endif
#if (CORE0_THREAD11_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,11)
#endif
#if (CORE0_THREAD12_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,12)
#endif
#if (CORE0_THREAD13_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,13)
#endif
#if (CORE0_THREAD14_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,14)
#endif
#if (CORE0_THREAD15_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,15)
#endif
#if (CORE0_THREAD16_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,16)
#endif
#if (CORE0_THREAD17_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,17)
#endif
#if (CORE0_THREAD18_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,18)
#endif
#if (CORE0_THREAD19_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,19)
#endif
#if (CORE0_THREAD20_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,20)
#endif
#if (CORE0_THREAD21_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,21)
#endif
#if (CORE0_THREAD22_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,22)
#endif
#if (CORE0_THREAD23_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,23)
#endif
#if (CORE0_THREAD24_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,24)
#endif
#if (CORE0_THREAD25_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,25)
#endif
#if (CORE0_THREAD26_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,26)
#endif
#if (CORE0_THREAD27_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,27)
#endif
#if (CORE0_THREAD28_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,28)
#endif
#if (CORE0_THREAD29_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,29)
#endif
#if (CORE0_THREAD30_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,30)
#endif
#if (CORE0_THREAD31_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,31)
#endif
#if (CORE0_THREAD32_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,32)
#endif
#if (CORE0_THREAD33_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,33)
#endif
#if (CORE0_THREAD34_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,34)
#endif
#if (CORE0_THREAD35_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,35)
#endif
#if (CORE0_THREAD36_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,36)
#endif
#if (CORE0_THREAD37_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,37)
#endif
#if (CORE0_THREAD38_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,38)
#endif
#if (CORE0_THREAD39_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,39)
#endif
#if (CORE0_THREAD40_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,40)
#endif
#if (CORE0_THREAD41_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,41)
#endif
#if (CORE0_THREAD42_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,42)
#endif
#if (CORE0_THREAD43_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,43)
#endif
#if (CORE0_THREAD44_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,44)
#endif
#if (CORE0_THREAD45_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,45)
#endif
#if (CORE0_THREAD46_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,46)
#endif
#if (CORE0_THREAD47_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,47)
#endif
#if (CORE0_THREAD48_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,48)
#endif
#if (CORE0_THREAD49_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,49)
#endif
#if (CORE0_THREAD50_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,50)
#endif
#if (CORE0_THREAD51_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,51)
#endif
#if (CORE0_THREAD55_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,55)
#endif
#if (CORE0_THREAD52_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,52)
#endif
#if (CORE0_THREAD54_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,54)
#endif
#if (CORE0_THREAD55_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,55)
#endif
#if (CORE0_THREAD56_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,56)
#endif
#if (CORE0_THREAD57_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,57)
#endif
#if (CORE0_THREAD58_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,58)
#endif
#if (CORE0_THREAD59_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,59)
#endif
#if (CORE0_THREAD60_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,60)
#endif
#if (CORE0_THREAD61_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,61)
#endif
#if (CORE0_THREAD62_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,62)
#endif
#if (CORE0_THREAD63_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,63)
#endif
#if (CORE0_THREAD64_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,64)
#endif
#if (CORE0_THREAD65_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,65)
#endif
#if (CORE0_THREAD66_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,66)
#endif
#if (CORE0_THREAD67_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,67)
#endif
#if (CORE0_THREAD68_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,68)
#endif
#if (CORE0_THREAD69_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,69)
#endif
#if (CORE0_THREAD70_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,70)
#endif
#if (CORE0_THREAD71_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,71)
#endif
#if (CORE0_THREAD72_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,72)
#endif
#if (CORE0_THREAD73_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,73)
#endif
#if (CORE0_THREAD74_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,74)
#endif
#if (CORE0_THREAD75_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,75)
#endif
#if (CORE0_THREAD76_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,76)
#endif
#if (CORE0_THREAD77_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,77)
#endif
#if (CORE0_THREAD78_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,78)
#endif
#if (CORE0_THREAD79_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,79)
#endif
#if (CORE0_THREAD80_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,80)
#endif
#if (CORE0_THREAD81_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,81)
#endif
#if (CORE0_THREAD82_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,82)
#endif
#if (CORE0_THREAD83_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,83)
#endif
#if (CORE0_THREAD84_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,84)
#endif
#if (CORE0_THREAD85_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,85)
#endif
#if (CORE0_THREAD86_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,86)
#endif
#if (CORE0_THREAD87_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,87)
#endif
#if (CORE0_THREAD88_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,88)
#endif
#if (CORE0_THREAD89_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,89)
#endif
#if (CORE0_THREAD90_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,90)
#endif
#if (CORE0_THREAD91_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,91)
#endif
#if (CORE0_THREAD92_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,92)
#endif
#if (CORE0_THREAD93_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,93)
#endif
#if (CORE0_THREAD94_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,94)
#endif
#if (CORE0_THREAD95_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,95)
#endif
#if (CORE0_THREAD96_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,96)
#endif
#if (CORE0_THREAD97_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,97)
#endif
#if (CORE0_THREAD98_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,98)
#endif
#if (CORE0_THREAD99_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,99)
#endif
#if (CORE0_THREAD100_SWITCH == ON) 
PTHREAD_DEFINITION_BLOCK(0,100)
#endif

void start_core0_os(void) {

    PTHREAD_CREATION_BLOCK(core0_os_th0, &os_thread_attr[CORE_ID0][THREAD_ID0], core0_os_thread0, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID0].task_id,CORE0_TASK0);
    PTHREAD_CREATION_BLOCK(core0_os_th1, &os_thread_attr[CORE_ID0][THREAD_ID1], core0_os_thread1, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID1].task_id,CORE0_TASK1);	
    PTHREAD_CREATION_BLOCK(core0_os_th2, &os_thread_attr[CORE_ID0][THREAD_ID2], core0_os_thread2, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID2].task_id,CORE0_TASK2);
#if 0	

	PTHREAD_CREATION_BLOCK(core0_os_th3, &os_thread_attr[CORE_ID0][THREAD_ID3], core0_os_thread3, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID3].task_id,CORE0_TASK3);

	PTHREAD_CREATION_BLOCK(core0_os_th4, &os_thread_attr[CORE_ID0][THREAD_ID4], core0_os_thread4, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID4].task_id,CORE0_TASK4);
	PTHREAD_CREATION_BLOCK(core0_os_th5, &os_thread_attr[CORE_ID0][THREAD_ID5], core0_os_thread5, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID5].task_id,CORE0_TASK5);

	PTHREAD_CREATION_BLOCK(core0_os_th6, &os_thread_attr[CORE_ID0][THREAD_ID6], core0_os_thread6, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID6].task_id,CORE0_TASK6);
	PTHREAD_CREATION_BLOCK(core0_os_th7, &os_thread_attr[CORE_ID0][THREAD_ID7], core0_os_thread7, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID7].task_id,CORE0_TASK7);
    PTHREAD_CREATION_BLOCK(core0_os_th8, &os_thread_attr[CORE_ID0][THREAD_ID8], core0_os_thread8, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID8].task_id,CORE0_TASK8);
    PTHREAD_CREATION_BLOCK(core0_os_th9, &os_thread_attr[CORE_ID0][THREAD_ID9], core0_os_thread9, (void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID9].task_id,CORE0_TASK9);

#endif
	PTHREAD_CREATION_BLOCK(core0_os_th10, &os_thread_attr[CORE_ID0][THREAD_ID10], core0_os_thread10,(void*)os_pthread_init_config_database[CORE_ID0][THREAD_ID10].task_id,CORE0_TASK10);

	PTHREAD_START_BLOCK();
}


