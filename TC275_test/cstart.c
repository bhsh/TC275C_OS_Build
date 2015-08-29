/**************************************************************************
**                                                                        *
**  FILE        :  cstart.c                                               *
**                                                                        *
**  DESCRIPTION :                                                         *
**      The system startup code initializes the processor's registers     *
**      and the application C variables.                                  *
**                                                                        *
**  Copyright 1996-2014 Altium BV                                         *
**                                                                        *
**************************************************************************/

#include "cstart.h"                             /* include configuration */

#include <stdlib.h>
#include <stdbool.h>

#ifdef __CPU__
#include __SFRFILE__(__CPU__)
#endif

#pragma weak   exit
#pragma extern _Exit
#pragma profiling off                           /* prevent profiling information on cstart */
#pragma tradeoff 4                              /* preset tradeoff level (for size) */
#pragma runtime BCM                             /* disable runtime error checking for cstart */
#pragma nomisrac                                /* disable MISRA-C checking */
#pragma noclear                                 /* bss clearing not before cinit */
#pragma immediate_in_code                       /* no external ROM access before bus configuration */

#if __USE_ARGC_ARGV
static char argcv[__ARGCV_BUFSIZE];
extern int _argcv( const char *, size_t );
#endif

/* linker definitions */
extern __far void _lc_ue_ustack[];      /* user stack end */
extern __far void _lc_ue_istack[];      /* interrupt stack end */
extern __far void _lc_u_int_tab[];      /* interrupt table */
extern __far void _lc_u_trap_tab[];     /* trap table */
extern __far void _SMALL_DATA_[];       /* centre of A0 addressable area */
extern __far void _LITERAL_DATA_[];     /* centre of A1 addressable area */
extern __far void _A8_DATA_[];          /* centre of A8 addressable area */
extern __far void _A9_DATA_[];          /* centre of A9 addressable area */

/* external functions */
#if __C_INIT
extern void _c_init(void);              /* C initialization function */
#endif
#ifdef __CALL_INIT
extern void _call_init(void);           /* call a user function before main() */
#endif
#ifdef _CALL_ENDINIT
extern void _endinit(void);             /* call a user function with protection switched off */
#endif

/* local functions */
static void __noinline__ __noreturn__ __jump__ __init_sp( void );
static void __noinline__ __noreturn__ __jump__ _start( void );

/* library references */
#pragma extern main
extern int main( int argc, char *argv[] );

/* endinit types */
typedef enum
{
        _ENDINIT_DISABLE,
        _ENDINIT_ENABLE
}       _endinit_t;
static void inline endinit_set(_endinit_t endinit_value);

/* external interface to endinit_set */
extern void _endinit_clear(void) { endinit_set(_ENDINIT_DISABLE); }
extern void _endinit_set  (void) { endinit_set(_ENDINIT_ENABLE); }

#if __PROF_ENABLE__
extern void __prof_init( void );
#endif

#if __CLOCKS_PER_SEC_INIT
static void setclockpersec( void );
extern unsigned long long setfoschz( unsigned long long );
#endif

#if ( defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#define WDT_CON0        SCU_WDTCPU0CON0
#define WDT_CON1        SCU_WDTCPU0CON1

static void inline safety_endinit_set(_endinit_t endinit_value);

/* external interface to endinit_set */
extern void _safety_endinit_clear(void) { safety_endinit_set(_ENDINIT_DISABLE); }
extern void _safety_endinit_set  (void) { safety_endinit_set(_ENDINIT_ENABLE); }
#endif

#if ( defined _REGUSERDEF16X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#if (__HALT_INIT_TC1 && (__HALT_VALUE_TC1 & 0x2)) || (__HALT_INIT_TC2 && (__HALT_VALUE_TC2 & 0x2))
#if __C_INIT || __CLOCKS_PER_SEC_INIT || __PROF_ENABLE__ || _CALL_ENDINIT || (defined __CALL_INIT)
/* c init semaphores */
#if (defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC29X_H)
#define __AT_NOT_CACHED_MEMORY__        __at(0x70000000)
#else
#define __AT_NOT_CACHED_MEMORY__
#endif
unsigned int volatile __far __align(4)  _tcx_end_c_init __AT_NOT_CACHED_MEMORY__;       /* _tcx_end_c_init := 1 << core_id */
#endif
#endif
#endif

/*********************************************************************************
 * reset vector
 *********************************************************************************/

#pragma section code libc.reset
#pragma optimize g
void _START( void )
{
        __init_sp();
}
#pragma optimize restore
#pragma section code restore

/*********************************************************************************
 * EBU boot configuration
 *********************************************************************************/
#if defined EBU_BOOTCFG && defined __EBU_BOOTCFG_VALUE
#if __EBU_BOOTCFG_INIT
#pragma section farrom libc.ebu_bootcfg
const int __far _EBU_BOOTCFG __protect__  = __EBU_BOOTCFG_VALUE; /* locate at RESET + EBU_ALIGN */
#pragma section farrom restore
#endif
#endif

/*********************************************************************************
 * initialize stackpointer
 *********************************************************************************/

static void __noinline__ __noreturn__ __jump__ __init_sp( void )
{
        /* The initialization of the stackpointer is done in a seperate function, 
           because it must be executed in a function which has no stack use.
           
           When a function uses a stack it will be updated at the start of the 
           function. In this function, however, the stackpointer has an irrelevant
           value at the start of the function. A starting value for the stackpointer
           is determined and written in this function. The update to the 
           stackpointer at the start of the function would therefore be undone.
         */
         
        /* 
         * CPU_TC.033 workaround:
         * The stack pointers are aligned to quad-word boundary to workaround these 
         * functional problems CPU_TC.033.
         * Also the C compiler workaround for the appropriate CPU function problem
         * need to be enabled with --silicon-bug=cpu-tc033, to align circular
         * buffers on a quad-word boundary and to size all stack frames to an integral 
         * number of quad-words.
         */
#if      __CPU_TC033_INITIAL__
# define STACK_ALIGN    0xfffffff0
#else
# define STACK_ALIGN    0xfffffff8
#endif

        /* 
         * Load user stack pointer.
         * Disable this if not started from RESET vector. (E.g.
         * ROM monitors require to keep in control of vectors)
         */
#if  __USP_INIT
        unsigned int sp = (unsigned int)(_lc_ue_ustack) & STACK_ALIGN;
        __asm("mov.a\tsp,%0"::"d"(sp));
#endif
        _start();
}

/*********************************************************************************
 * startup code
 *********************************************************************************/

static void __noinline__ __noreturn__ __jump__ _start( void )
{

#if (  defined _REGUSERDEF16X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#if __STADD_INIT_TC1
        /*
         * Set start address of TC1
         * Reset value is 0xAFFFC000
         */
        extern void __noinline__ __noreturn__ __jump__ _start_tc1( void );
        CPU1_PC.U = (unsigned int)_start_tc1;
#endif
#if __STADD_INIT_TC2 && !( defined _REGTC26X_H )
        /*
         * Set start address of TC2
         * Reset value is 0xAFFFC000
         */
        extern void __noinline__ __noreturn__ __jump__ _start_tc2( void );
        CPU2_PC.U = (unsigned int)_start_tc2;
#endif
#if (__HALT_INIT_TC1 && (__HALT_VALUE_TC1 & 0x2)) || (__HALT_INIT_TC2 && (__HALT_VALUE_TC2 & 0x2))
#if __C_INIT || __CLOCKS_PER_SEC_INIT || __PROF_ENABLE__ || _CALL_ENDINIT || (defined __CALL_INIT)
        /*
         * Clear end of c init semaphores for all cores
         */
        _tcx_end_c_init = 0;
#endif
#endif
        /*
         * A core can be released by resetting its halt state.
         * HALT: 0 R:running W:unchanged
         *       1 R:halted  W:unchanged
         *       2 R:n.a.    W:reset halt
         *       3 R:n.a.    W:set halt when debug enable
         */
#if __HALT_INIT_TC1
        CPU1_DBGSR.B.HALT=__HALT_VALUE_TC1;
#endif
#if __HALT_INIT_TC2 && !( defined _REGTC26X_H )
        CPU2_DBGSR.B.HALT=__HALT_VALUE_TC2;
#endif
#endif  
        
        /* Do a dsync before changing any of the csfr values, thus any previous
         * background state gets flushed first. Required for applications that jump
         * to the reset address.
         */
        __dsync();
        
        /* Set the PSW to its reset value in case of a warm start */
#if __USER_STACK
        __mtcr(PSW, 0x00000980);        /* clear PSW.IS */
#else
        __mtcr(PSW, 0x00000b80);
#endif

        /* Set the PCXS and PCXO to its reset value in case of a warm start */
        unsigned int pcxi = __mfcr(PCXI);
        pcxi &= 0xfff00000;
        __mtcr(PCXI, pcxi);

#if (  defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        /*
         * Clear the ENDINIT bit in the WDTSCON0 register in order
         * to disable the write-protection for safety-critical registers
         * protected via the safety EndInit feature.
         */
        safety_endinit_set(_ENDINIT_DISABLE);
        
        /*
         * Disable the safety watchdog if requested. Safety watchdog
         * is enabled by default. The safety watchdog is disabled after
         * ENDINIT is set by safety_endinit_set().
         */       
#if __SAFETY_WATCHDOG_DISABLE
        SCU_WDTSCON1.U |= 0x8;
        safety_endinit_set(_ENDINIT_ENABLE);
        safety_endinit_set(_ENDINIT_DISABLE);
#endif
        
#endif
        
        /*
         * Clear the ENDINIT bit in the WDT_CON0 register in order
         * to disable the write-protection for registers protected 
         * via the EndInit feature (for example: WDT_CON1).
         */
        endinit_set(_ENDINIT_DISABLE);
        
        /*
         * Disable the Watchdog if requested. Watchdog is enabled by default.
         * The Watchdog is disabled after ENDINIT is set by endinit_set().
         */       
#if __WATCHDOG_DISABLE
        WDT_CON1.U |= 0x8;
        endinit_set(_ENDINIT_ENABLE);
        endinit_set(_ENDINIT_DISABLE);
#endif

        /*
         * PMI_TC.003 workaround:
         * The TLB-A and TLB-B mappings are set to a page size of 16KB.
         */
#if __PMI_TC003_INITIAL__  && defined MMU_CON
        unsigned int mmu_con = __mfcr(MMU_CON);
        mmu_con &= 0xffffffe1;      /* clear SZA and SZB */
        mmu_con |= 0x00000014;      /* set SZA=SZB=16k   */       
        __mtcr(MMU_CON, mmu_con);
#endif

        /*
         * Load Base Address of Trap Vector Table.
         * Disable this if not started from RESET vector. (E.g.
         * ROM monitors require to keep in control of vectors)
         */
#if __BTV_INIT
        __mtcr(BTV,  (unsigned int)_lc_u_trap_tab);
#endif

        /*
         * Load Base Address of Interrupt Vector Table.
         * Disable this if not started from RESET vector. (E.g.
         * ROM monitors require to keep in control of vectors)
         */
#if __BIV_INIT
#if __BIV_SINGLE_INIT && (defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC2X7_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        /*
         * Single Entry Vector Table, for core tc1.6.x, is supported
         * by _sevt_isr_tc0() calling interrupt handlers installed
         * with _sevt_isr_install() stored in _sevt_isrs_tc0 list.
         * The _sevt_isr_tc0() is located at interrupt vector table
         * entry 64. The start address of the interrupt vector table
         * is defined by linker definition INTTAB0, default value
         *_lc_u_int_tab is 0xa00f0000+0x800.
         */
#pragma extern _sevt_isr_tc0
        __mtcr(BIV, (unsigned int)(_lc_u_int_tab) | (0xff<<3) | 1 );
#else
#if __BIV_8BYTE_INIT && (defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        __mtcr(BIV, (unsigned int)(_lc_u_int_tab) | 1 );        /* 8 Byte vector spacing */
#else
        __mtcr(BIV, (unsigned int)(_lc_u_int_tab));             /* 32 Byte vector spacing */
#endif
#endif
#endif

        /*
         * Load interupt stack pointer.
         * Disable this if not started from RESET vector. (E.g.
         * ROM monitors require to keep in control of vectors)
         */
#if __ISP_INIT
        unsigned int isp = (unsigned int)(_lc_ue_istack) & STACK_ALIGN;
        __mtcr(ISP, isp);
#endif
                                                          
        /*
         * PMU/PMI configuration.
         */
#if defined PMI_CON0 && defined __PMI_CON0_VALUE
        if(__PMI_CON0_INIT)  PMI_CON0.U = __PMI_CON0_VALUE;        
#endif
#if defined PMI_CON1 && defined __PMI_CON1_VALUE
        if(__PMI_CON1_INIT)  PMI_CON1.U = __PMI_CON1_VALUE;        
#endif  
#if     defined PMI_CON2 && defined __PMI_CON2_VALUE && \
        (  defined _REGTC1337_H || defined _REGTC1367_H || defined _REGTC1387_H || defined _REGTC1728_H \
        || defined _REGTC1746_H || defined _REGTC1747_H || defined _REGTC1768_H || defined _REGTC1782_H \
        || defined _REGTC1784_H || defined _REGTC1184_H || defined _REGTC1797_H || defined _REGTC1197_H \
        || defined _REGTC1734_H || defined _REGTC1767_H || defined _REGTC1736_H || defined _REGTC1732_H \
        || defined _REGTC1738_H || defined _REGTC1167_H || defined _REGTC1735_H || defined _REGTC1724_H )
        if(__PMI_CON2_INIT)  PMI_CON2.U = __PMI_CON2_VALUE;        
#endif
        
#if defined PMU_EIFCON && defined __PMU_EIFCON_VALUE
        if(__PMU_EIFCON_INIT)  PMU_EIFCON.U = __PMU_EIFCON_VALUE;
#endif

        /*
         * DMI configuration.
         */
#if     defined DMI_CON && defined __DMI_CON_VALUE && \
        (  defined _REGTC1167_H || defined _REGTC1197_H || defined _REGTC1337_H || defined _REGTC1367_H \
        || defined _REGTC1387_H || defined _REGTC1728_H || defined _REGTC1734_H || defined _REGTC1738_H \
        || defined _REGTC1746_H || defined _REGTC1747_H || defined _REGTC1767_H || defined _REGTC1768_H \
        || defined _REGTC1782_H || defined _REGTC1784_H || defined _REGTC1184_H || defined _REGTC1797_H \
        || defined _REGTC1724_H )
        if(__DMI_CON_INIT)  DMI_CON.U = __DMI_CON_VALUE;        
#endif
        
        /*
         * Data cache control (Reset 0H).
         * CPU_TC013 workaround:
         * The 16KB D-Cache is enabled to workaround
         * the CPU_TC013 functional problem.     
         * NOTE: Setting the D-Cache size must be done at the
         *       very beginning of the startup code.
         */
#if defined  DMU_CON
#  if __CPU_TC013_INITIAL__ 
        DMU_CON.U = 0x1;
#  endif
#endif

        /*
         * PCON0 configuration.
         */
#if     defined PCON0 && defined __PCON0_VALUE
        if(__PCON0_INIT) __mtcr(PCON0, __PCON0_VALUE);
#endif

        /*
         * DCON0 configuration.
         */
#if     defined DCON0 && defined __DCON0_VALUE
        if(__DCON0_INIT) __mtcr(DCON0, __DCON0_VALUE);
#endif
        
        /*
         * Bus configuration EBU_CLC within endinit.
         */
#  if defined EBU_CLC && defined __EBU_CLC_VALUE
        if(__EBU_CLC_INIT)  EBU_CLC.U = __EBU_CLC_VALUE;
#  endif

        /*
         *      Setting up the PLL after Reset.
         *
         *      After reset, the system clock will be running at the VCO
         *      base frequency devided by a factor KDIV. To set up the PLL
         *      ater resert, next action must be executed.
         */
#if defined PLL_CLC && defined __PLL_CLC_VALUE
#if     __PLL_CLC_INIT
#if     ( defined _REGTC11IB_H )
#define __PLLBYP        PLL1_BP
#define __LOCK          PLL1_LOCK
        if ( PLL_CLC.B.__PLLBYP == 0 )
        {
                PLL_CLC.U = __PLL_CLC_VALUE;
                while( PLL_CLC.B.__LOCK==0);                      /* Wait until the PLL becomes locked */
        }
#else
#define __PLL_CLC_SYSFS_VALUE   ((__PLL_CLC_VALUE>>2)&0x1)
#define __PLL_CLC_VCOBYP_VALUE  ((__PLL_CLC_VALUE>>5)&0x1)
#define __PLL_CLC_VCOSEL_VALUE  ((__PLL_CLC_VALUE>>6)&0x3)
#define __PLL_CLC_KDIV_VALUE    ((__PLL_CLC_VALUE>>8)&0xf)
#define __PLL_CLC_PDIV_VALUE    ((__PLL_CLC_VALUE>>13)&0x3)
#define __PLL_CLC_NDIV_VALUE    ((__PLL_CLC_VALUE>>16)&0x7f)
        if ( PLL_CLC.B.BYPPIN == 0 )
        {
#if     ( defined _REGTC1130_H )
                while (OSC_CON.B.OSCR==1);                      /* Wait until the oscillator is running */
#else
                while (OSC_CON.B.OSCR==0);                      /* Wait until the oscillator is running */
#endif
                PLL_CLC.B.VCOBYP = 1;                           /* Enabled the VCO Bypass Mode */
                PLL_CLC.B.VCOSEL = __PLL_CLC_VCOSEL_VALUE;      /* Select the VCO band */
                PLL_CLC.B.PDIV = __PLL_CLC_PDIV_VALUE;
                PLL_CLC.B.KDIV = __PLL_CLC_KDIV_VALUE;
                PLL_CLC.B.NDIV = __PLL_CLC_NDIV_VALUE;
#if __PLL_CLC_VCOBYP_VALUE==0
                PLL_CLC.B.OSCDISC = 0;                          /* Connect the oscillator to the PLL */
                while( PLL_CLC.B.LOCK==0);                      /* Wait until the PLL becomes locked */
                PLL_CLC.B.VCOBYP = 0;                           /* Disabled the VCO Bypass Mode */
#endif
        }
#if     ( defined _REGTC1130_H )
        PLL_CLC.B.SYSFSL = __PLL_CLC_SYSFS_VALUE;                /* System frequency select */
#else
#if     (  defined _REGTC1762_H || defined _REGTC1764_H || defined _REGTC1766B_H \
        || defined _REGTC1164_H || defined _REGTC1166_H )
        PLL_CLC.B.RSV = __PLL_CLC_SYSFS_VALUE;                  /* System frequency select */
#else
        PLL_CLC.B.SYSFS = __PLL_CLC_SYSFS_VALUE;                /* System frequency select */
#endif
#endif
#endif
#endif
#endif

         /*
          * Configure CCU Clock Control
          *
          * For AURIX derivatives it is required to set the update request only
          * in the last CCUCON that is initialized. Set CCUCONx.UP where x is
          * the last one. A new complete parameter set is transferred to
          * the CCU.
          */
#if defined SCU_CCUCON0 && defined __SCU_CCUCON0_VALUE
         if(__SCU_CCUCON0_INIT)  SCU_CCUCON0.U = __SCU_CCUCON0_VALUE;
#endif

#if defined SCU_CCUCON1 && defined __SCU_CCUCON1_VALUE
         if(__SCU_CCUCON1_INIT)  SCU_CCUCON1.U = __SCU_CCUCON1_VALUE;
#endif

#if defined SCU_CCUCON2 && defined __SCU_CCUCON2_VALUE
         if(__SCU_CCUCON2_INIT)  SCU_CCUCON2.U = __SCU_CCUCON2_VALUE;
#endif
         
        /*
         * System Oscillator configuration
         */
#if defined SCU_OSCCON && defined __SCU_OSCCON_VALUE
#if __SCU_OSCCON_INIT
        SCU_OSCCON.U=__SCU_OSCCON_VALUE;
        
        while(SCU_OSCCON.B.PLLLV==0);           /* Oscillator not too low */
        while(SCU_OSCCON.B.PLLHV==0);           /* Oscillator not too high */
#endif
#endif

        /*
         * Configure PLL Prescaler Mode.
         */
#if defined SCU_PLLCON1 && defined __SCU_PLLCON1_VALUE
#if __SCU_PLLCON1_INIT
#define __SCU_PLLCON1__K1DIV_VALUE      ((__SCU_PLLCON1_VALUE>>16)&0x3f)
        SCU_PLLCON1.B.K1DIV=__SCU_PLLCON1__K1DIV_VALUE;
        while(SCU_PLLSTAT.B.K1RDY==0);          /* Wait until K1-Divider is ready to operate */
#endif
#endif

#if defined SCU_PLLCON0 && defined __SCU_PLLCON0_VALUE
#if     __SCU_PLLCON0_INIT
        SCU_PLLCON0.B.VCOBYP=1;                 /* Enabled the VCO Bypass Mode */
        while(SCU_PLLSTAT.B.VCOBYST==0);        /* Wait until prescaler mode is entered */

#define __SCU_PLLCON0__VCOPWD_VALUE     ((__SCU_PLLCON0_VALUE>>1)&0x1)
#define __SCU_PLLCON0__NDIV_VALUE       ((__SCU_PLLCON0_VALUE>>9)&0x7f)
#define __SCU_PLLCON0__PDIV_VALUE       ((__SCU_PLLCON0_VALUE>>24)&0xf)
        SCU_PLLCON0.B.PDIV=__SCU_PLLCON0__PDIV_VALUE;
        SCU_PLLCON0.B.NDIV=__SCU_PLLCON0__NDIV_VALUE;
        SCU_PLLCON0.B.VCOPWD=__SCU_PLLCON0__VCOPWD_VALUE; /* power down VCO */

#if __SCU_PLLCON0__VCOPWD_VALUE==0
        /*
         * Configure PLL normal mode.
         */
        SCU_PLLCON0.B.OSCDISCDIS=1;             /* Automatic oscillator disconnect disabled */
        SCU_PLLCON0.B.CLRFINDIS=1;              /* Connect VCO to the oscillator */
        while(SCU_PLLSTAT.B.FINDIS==1);         /* Wait until oscillator is connected to the VCO */
        SCU_PLLCON0.B.RESLD=1;                  /* Restart VCO lock detection */
        while(SCU_PLLSTAT.B.VCOLOCK==0);        /* Wait until the VCO becomes locked */
        SCU_PLLCON0.B.VCOBYP=0;                 /* Disable the VCO Bypass Mode */
        while(SCU_PLLSTAT.B.VCOBYST==1);        /* Wait until normal mode is entered */
        SCU_PLLCON0.B.OSCDISCDIS=0;             /* Automatic oscillator disconnect enabled */
#endif
#endif
#endif

        /*
         *      PLL K2 ramp up
         */
#if defined SCU_PLLCON1 && defined __SCU_PLLCON1_VALUE
#if __SCU_PLLCON1_INIT
#define __SCU_PLLCON1__K2DIV_VALUE      ((__SCU_PLLCON1_VALUE>>0)&0x3f)
#if __PLL_K2_RAMPUP
#if defined SCU_PLLSTAT && defined __fOSC
#if     (  defined _REGTC1167_H || defined _REGTC1197_H || defined _REGTC1337_H || defined _REGTC1367_H \
        || defined _REGTC1387_H || defined _REGTC1732_H || defined _REGTC1728_H || defined _REGTC1734_H \
        || defined _REGTC1735_H || defined _REGTC1736_H || defined _REGTC1738_H || defined _REGTC1746_H \
        || defined _REGTC1747_H || defined _REGTC1748_H || defined _REGTC1767_H || defined _REGTC1768_H \
        || defined _REGTC1782_H || defined _REGTC1784_H || defined _REGTC1184_H || defined _REGTC1797_H \
        || defined _REGTC1791_H || defined _REGTC1793_H || defined _REGTC1798_H || defined _REGTC1724_H \
        || defined _REGTC23X_ADAS_H || defined _REGTC23X_H \
        || defined _REGTC2D5T_H || defined _REGTC27X_H  || defined _REGTC27XB_H || defined _REGTC27XC_H \
        || defined _REGTC26X_H  || defined _REGTC29X_H)
#if     ( defined _REGTC2D5T_H )
#define PLL_K2_RAMPUP_STM_CLC_RMC       (STM0_CLC.B.RMC)
#else
#if ( defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#define PLL_K2_RAMPUP_STM_CLC_RMC       1
#else
#define PLL_K2_RAMPUP_STM_CLC_RMC       (STM_CLC.B.RMC)
#endif
#endif
#if ( defined _REGTC1337_H || defined _REGTC1367_H || defined _REGTC1387_H || defined _REGTC1768_H )
#define PLL_K2_RAMPUP_SYSCLK(CPUCLK)    (CPUCLK)
#else
#if ( defined _REGTC2D5T_H )
#define PLL_K2_RAMPUP_SYSCLK(CPUCLK)    (CPUCLK/(SCU_CCUCON0.B.SPBDIV+1))
#else
#if ( defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#define PLL_K2_RAMPUP_SYSCLK(CPUCLK)    (CPUCLK/SCU_CCUCON1.B.STMDIV)
#else
#define PLL_K2_RAMPUP_SYSCLK(CPUCLK)    (CPUCLK/(SCU_CCUCON0.B.FPIDIV+1))
#endif
#endif
#endif
#define USECCLK         (PLL_K2_RAMPUP_SYSCLK(((SCU_PLLCON0.B.NDIV+1)*(__fOSC/1000000))/((SCU_PLLCON0.B.PDIV+1)*(SCU_PLLCON1.B.K2DIV+1)))/PLL_K2_RAMPUP_STM_CLC_RMC)
#define WAITUSEC        (USECCLK*20)    /* wait 20 usec */
#endif
#endif
#pragma tradeoff 0      /* avoid call to run-time function */
        while ( SCU_PLLCON1.B.K2DIV > __SCU_PLLCON1__K2DIV_VALUE )
        {
                unsigned int wait;

                SCU_PLLCON1.B.K2DIV-=1;
                wait = SYSTIME_LOW+WAITUSEC;

                while( SYSTIME_LOW < wait ) ;
        }
#pragma tradeoff restore
#else
        SCU_PLLCON1.B.K2DIV=__SCU_PLLCON1__K2DIV_VALUE;
#endif
#endif
#endif

        /*
         * Configure flash registers.
         */
#if defined FLASH0_FCON && defined __FLASH0_FCON_VALUE
        if(__FLASH0_FCON_INIT)  FLASH0_FCON.U = __FLASH0_FCON_VALUE;        
#endif
#if defined FLASH1_FCON && defined __FLASH1_FCON_VALUE
        if(__FLASH1_FCON_INIT)  FLASH1_FCON.U = __FLASH1_FCON_VALUE;        
#endif
        
        /*
         * Configure system clock register.
         */
#if defined STM_CLC && defined __STM_CLC_VALUE
        if(__STM_CLC_INIT)  STM_CLC.U = __STM_CLC_VALUE;        
#endif

        /*
         * Enable the GTM to get MCS memory access,
         * required for MCS initialization which
         * is performed by _c_init.
         */
#if defined GTM_CLC && defined __GTM_CLC_VALUE
        if(__GTM_CLC_INIT)  GTM_CLC.U = __GTM_CLC_VALUE;
#endif
        
        
        /*
         * Set the ENDINIT bit in the WDT_CON0 register again
         * to enable the write-protection.
         */
        endinit_set(_ENDINIT_ENABLE);

#if (  defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        /*
         * Set the ENDINIT bit in the WDTSCON0 register to enable the
         * safety-critical register write-protection.
         */
        safety_endinit_set(_ENDINIT_ENABLE);
#endif
        
        /*
         * Initialize Bus configuration registers:
         * Set register-values according to define's created by the GUI
         * 
         * The recommended sequence of setting registers is as follows:
         * 1.EBUCON
         * 2.All other EBU registers except SDRAM specific registers
         * 3.SDRMCON0
         * 4.SDRMMOD0
         * 5.SDRMREF0
         * 6.SDRMCON1
         * 7.SDRMMOD1
         * 8.SDRMREF1
         */
#if defined EBU_CON && defined __EBU_CON_VALUE
        if(__EBU_CON_INIT)  EBU_CON.U = __EBU_CON_VALUE;
#endif
#if defined EBU_ADDRSEL0 && defined __EBU_ADDRSEL0_VALUE
        if(__EBU_ADDRSEL0_INIT)  EBU_ADDRSEL0.U = __EBU_ADDRSEL0_VALUE;
#endif
#if defined EBU_ADDRSEL1 && defined __EBU_ADDRSEL1_VALUE
        if(__EBU_ADDRSEL1_INIT)  EBU_ADDRSEL1.U = __EBU_ADDRSEL1_VALUE;
#endif
#if defined EBU_ADDRSEL2 && defined __EBU_ADDRSEL2_VALUE
        if(__EBU_ADDRSEL2_INIT)  EBU_ADDRSEL2.U = __EBU_ADDRSEL2_VALUE;
#endif
#if defined EBU_ADDRSEL3 && defined __EBU_ADDRSEL3_VALUE
        if(__EBU_ADDRSEL3_INIT)  EBU_ADDRSEL3.U = __EBU_ADDRSEL3_VALUE;
#endif
#if defined EBU_ADDRSEL4 && defined __EBU_ADDRSEL4_VALUE
        if(__EBU_ADDRSEL4_INIT)  EBU_ADDRSEL4.U = __EBU_ADDRSEL4_VALUE;
#endif
#if defined EBU_ADDRSEL5 && defined __EBU_ADDRSEL5_VALUE
        if(__EBU_ADDRSEL5_INIT)  EBU_ADDRSEL5.U = __EBU_ADDRSEL5_VALUE;
#endif
#if defined EBU_ADDRSEL6 && defined __EBU_ADDRSEL6_VALUE
        if(__EBU_ADDRSEL6_INIT)  EBU_ADDRSEL6.U = __EBU_ADDRSEL6_VALUE;
#endif
#if defined EBU_BFCON && defined __EBU_BFCON_VALUE
        if(__EBU_BFCON_INIT)  EBU_BFCON.U = __EBU_BFCON_VALUE;
#endif
#if defined EBU_BUSAP0 && defined __EBU_BUSAP0_VALUE
        if(__EBU_BUSAP0_INIT)  EBU_BUSAP0.U = __EBU_BUSAP0_VALUE;
#endif
#if defined EBU_BUSAP1 && defined __EBU_BUSAP1_VALUE
        if(__EBU_BUSAP1_INIT)  EBU_BUSAP1.U = __EBU_BUSAP1_VALUE;
#endif
#if defined EBU_BUSAP2 && defined __EBU_BUSAP2_VALUE
        if(__EBU_BUSAP2_INIT)  EBU_BUSAP2.U = __EBU_BUSAP2_VALUE;
#endif
#if defined EBU_BUSAP3 && defined __EBU_BUSAP3_VALUE
        if(__EBU_BUSAP3_INIT)  EBU_BUSAP3.U = __EBU_BUSAP3_VALUE;
#endif
#if defined EBU_BUSAP4 && defined __EBU_BUSAP4_VALUE
        if(__EBU_BUSAP4_INIT)  EBU_BUSAP4.U = __EBU_BUSAP4_VALUE;
#endif
#if defined EBU_BUSAP5 && defined __EBU_BUSAP5_VALUE
        if(__EBU_BUSAP5_INIT)  EBU_BUSAP5.U = __EBU_BUSAP5_VALUE;
#endif
#if defined EBU_BUSAP6 && defined __EBU_BUSAP6_VALUE
        if(__EBU_BUSAP6_INIT)  EBU_BUSAP6.U = __EBU_BUSAP6_VALUE;
#endif
#if defined EBU_BUSCON0 && defined __EBU_BUSCON0_VALUE
        if(__EBU_BUSCON0_INIT)  EBU_BUSCON0.U = __EBU_BUSCON0_VALUE;
#endif
#if defined EBU_BUSCON1 && defined __EBU_BUSCON1_VALUE
        if(__EBU_BUSCON1_INIT)  EBU_BUSCON1.U = __EBU_BUSCON1_VALUE;
#endif
#if defined EBU_BUSCON2 && defined __EBU_BUSCON2_VALUE
        if(__EBU_BUSCON2_INIT)  EBU_BUSCON2.U = __EBU_BUSCON2_VALUE;
#endif
#if defined EBU_BUSCON3 && defined __EBU_BUSCON3_VALUE
        if(__EBU_BUSCON3_INIT)  EBU_BUSCON3.U = __EBU_BUSCON3_VALUE;
#endif
#if defined EBU_BUSCON4 && defined __EBU_BUSCON4_VALUE
        if(__EBU_BUSCON4_INIT)  EBU_BUSCON4.U = __EBU_BUSCON4_VALUE;
#endif
#if defined EBU_BUSCON5 && defined __EBU_BUSCON5_VALUE
        if(__EBU_BUSCON5_INIT)  EBU_BUSCON5.U = __EBU_BUSCON5_VALUE;
#endif
#if defined EBU_BUSCON6 && defined __EBU_BUSCON6_VALUE
        if(__EBU_BUSCON6_INIT)  EBU_BUSCON6.U = __EBU_BUSCON6_VALUE;
#endif
#if defined EBU_EMUAS && defined __EBU_EMUAS_VALUE
        if(__EBU_EMUAS_INIT)  EBU_EMUAS.U = __EBU_EMUAS_VALUE;
#endif
#if defined EBU_EMUBAP && defined __EBU_EMUBAP_VALUE
        if(__EBU_EMUBAP_INIT)  EBU_EMUBAP.U = __EBU_EMUBAP_VALUE;
#endif
#if defined EBU_EMUBC && defined __EBU_EMUBC_VALUE
        if(__EBU_EMUBC_INIT)  EBU_EMUBC.U = __EBU_EMUBC_VALUE;
#endif
#if defined EBU_EMUCON && defined __EBU_EMUCON_VALUE
        if(__EBU_EMUCON_INIT)  EBU_EMUCON.U = __EBU_EMUCON_VALUE;
#endif
#if defined EBU_EMUOVL && defined __EBU_EMUOVL_VALUE
        if(__EBU_EMUOVL_INIT)  EBU_EMUOVL.U = __EBU_EMUOVL_VALUE;
#endif
#if defined EBU_SDRMCON0 && defined __EBU_SDRMCON0_VALUE
        if(__EBU_SDRMCON0_INIT)  EBU_SDRMCON0.U = __EBU_SDRMCON0_VALUE;
#endif
#if defined EBU_SDRMOD0 && defined __EBU_SDRMOD0_VALUE
        if(__EBU_SDRMOD0_INIT)  EBU_SDRMOD0.U = __EBU_SDRMOD0_VALUE;
#endif
#if defined EBU_SDRMREF0 && defined __EBU_SDRMREF0_VALUE
        if(__EBU_SDRMREF0_INIT)  EBU_SDRMREF0.U = __EBU_SDRMREF0_VALUE;
#endif
#if defined EBU_SDRMCON1 && defined __EBU_SDRMCON1_VALUE
        if(__EBU_SDRMCON1_INIT)  EBU_SDRMCON1.U = __EBU_SDRMCON1_VALUE;
#endif
#if defined EBU_SDRMOD1 && defined __EBU_SDRMOD1_VALUE
        if(__EBU_SDRMOD1_INIT)  EBU_SDRMOD1.U = __EBU_SDRMOD1_VALUE;
#endif
#if defined EBU_SDRMREF1 && defined __EBU_SDRMREF1_VALUE
        if(__EBU_SDRMREF1_INIT)  EBU_SDRMREF1.U = __EBU_SDRMREF1_VALUE;
#endif
#if defined CBS_MCDBBS && defined __CBS_MCDBBS_VALUE
        if(__CBS_MCDBBS_INIT)  CBS_MCDBBS .U = __CBS_MCDBBS_VALUE;
#endif
#if defined SBCU_CON && defined __SBCU_CON_VALUE
        if(__SBCU_CON_INIT)  SBCU_CON.U = __SBCU_CON_VALUE;
#endif
#if defined EBU_BUSRAP1 && defined __EBU_BUSRAP1_VALUE
        if(__EBU_BUSRAP1_INIT)  EBU_BUSRAP1.U = __EBU_BUSRAP1_VALUE;
#endif
#if defined EBU_BUSRAP0 && defined __EBU_BUSRAP0_VALUE
        if(__EBU_BUSRAP0_INIT)  EBU_BUSRAP0.U = __EBU_BUSRAP0_VALUE;
#endif
#if defined EBU_BUSRAP2 && defined __EBU_BUSRAP2_VALUE
        if(__EBU_BUSRAP2_INIT)  EBU_BUSRAP2.U = __EBU_BUSRAP2_VALUE;
#endif
#if defined EBU_BUSRAP3 && defined __EBU_BUSRAP3_VALUE
        if(__EBU_BUSRAP3_INIT)  EBU_BUSRAP3.U = __EBU_BUSRAP3_VALUE;
#endif
#if defined EBU_BUSRCON0 && defined __EBU_BUSRCON0_VALUE
        if(__EBU_BUSRCON0_INIT)  EBU_BUSRCON0.U = __EBU_BUSRCON0_VALUE;
#endif
#if defined EBU_BUSRCON1 && defined __EBU_BUSRCON1_VALUE
        if(__EBU_BUSRCON1_INIT)  EBU_BUSRCON1.U = __EBU_BUSRCON1_VALUE;
#endif
#if defined EBU_BUSRCON2 && defined __EBU_BUSRCON2_VALUE
        if(__EBU_BUSRCON2_INIT)  EBU_BUSRCON2.U = __EBU_BUSRCON2_VALUE;
#endif
#if defined EBU_BUSRCON3 && defined __EBU_BUSRCON3_VALUE
        if(__EBU_BUSRCON3_INIT)  EBU_BUSRCON3.U = __EBU_BUSRCON3_VALUE;
#endif
#if defined EBU_BUSWAP0 && defined __EBU_BUSWAP0_VALUE
        if(__EBU_BUSWAP0_INIT)  EBU_BUSWAP0.U = __EBU_BUSWAP0_VALUE;
#endif
#if defined EBU_BUSWAP1 && defined __EBU_BUSWAP1_VALUE
        if(__EBU_BUSWAP1_INIT)  EBU_BUSWAP1.U = __EBU_BUSWAP1_VALUE;
#endif
#if defined EBU_BUSWAP2 && defined __EBU_BUSWAP2_VALUE
        if(__EBU_BUSWAP2_INIT)  EBU_BUSWAP2.U = __EBU_BUSWAP2_VALUE;
#endif
#if defined EBU_BUSWAP3 && defined __EBU_BUSWAP3_VALUE
        if(__EBU_BUSWAP3_INIT)  EBU_BUSWAP3.U = __EBU_BUSWAP3_VALUE;
#endif
#if defined EBU_BUSWCON0 && defined __EBU_BUSWCON0_VALUE
        if(__EBU_BUSWCON0_INIT)  EBU_BUSWCON0.U = __EBU_BUSWCON0_VALUE;
#endif
#if defined EBU_BUSWCON1 && defined __EBU_BUSWCON1_VALUE
        if(__EBU_BUSWCON1_INIT)  EBU_BUSWCON1.U = __EBU_BUSWCON1_VALUE;
#endif
#if defined EBU_BUSWCON2 && defined __EBU_BUSWCON2_VALUE
        if(__EBU_BUSWCON2_INIT)  EBU_BUSWCON2.U = __EBU_BUSWCON2_VALUE;
#endif
#if defined EBU_BUSWCON3 && defined __EBU_BUSWCON3_VALUE
        if(__EBU_BUSWCON3_INIT)  EBU_BUSWCON3.U = __EBU_BUSWCON3_VALUE;
#endif
#if defined EBU_EXTBOOT && defined __EBU_EXTBOOT_VALUE
        if(__EBU_EXTBOOT_INIT)  EBU_EXTBOOT.U = __EBU_EXTBOOT_VALUE;
#endif
#if defined EBU_MODCON && defined __EBU_MODCON_VALUE
        if(__EBU_MODCON_INIT)  EBU_MODCON.U = __EBU_MODCON_VALUE;
#endif
#if defined EBU_DDRNCON && defined __EBU_DDRNCON_VALUE
        if(__EBU_DDRNCON_INIT)  EBU_DDRNCON.U = __EBU_DDRNCON_VALUE;
#endif
#if defined EBU_DDRNMOD && defined __EBU_DDRNMOD_VALUE
        if(__EBU_DDRNMOD_INIT)  EBU_DDRNMOD.U = __EBU_DDRNMOD_VALUE;
#endif
#if defined EBU_DDRNMOD2 && defined __EBU_DDRNMOD2_VALUE
        if(__EBU_DDRNMOD2_INIT)  EBU_DDRNMOD2.U = __EBU_DDRNMOD2_VALUE;
#endif
#if defined EBU_DDRNPRLD && defined __EBU_DDRNPRLD_VALUE
        if(__EBU_DDRNPRLD_INIT)  EBU_DDRNPRLD.U = __EBU_DDRNPRLD_VALUE;
#endif
#if defined EBU_DDRNTAG0 && defined __EBU_DDRNTAG0_VALUE
        if(__EBU_DDRNTAG0_INIT)  EBU_DDRNTAG0.U = __EBU_DDRNTAG0_VALUE;
#endif
#if defined EBU_DDRNTAG1 && defined __EBU_DDRNTAG1_VALUE
        if(__EBU_DDRNTAG1_INIT)  EBU_DDRNTAG1.U = __EBU_DDRNTAG1_VALUE;
#endif
#if defined EBU_DDRNTAG2 && defined __EBU_DDRNTAG2_VALUE
        if(__EBU_DDRNTAG2_INIT)  EBU_DDRNTAG2.U = __EBU_DDRNTAG2_VALUE;
#endif
#if defined EBU_DDRNTAG3 && defined __EBU_DDRNTAG3_VALUE
        if(__EBU_DDRNTAG3_INIT)  EBU_DDRNTAG3.U = __EBU_DDRNTAG3_VALUE;
#endif
#if defined EBU_DLLCON && defined __EBU_DLLCON_VALUE
        if(__EBU_DLLCON_INIT)  EBU_DLLCON.U = __EBU_DLLCON_VALUE;
#endif
#if defined EBU_SDRMCON && defined __EBU_SDRMCON_VALUE
        if(__EBU_SDRMCON_INIT)  EBU_SDRMCON.U = __EBU_SDRMCON_VALUE;
#endif
#if defined EBU_SDRMOD && defined __EBU_SDRMOD_VALUE
        if(__EBU_SDRMOD_INIT)  EBU_SDRMOD.U = __EBU_SDRMOD_VALUE;
#endif
#if defined EBU_SDRMREF && defined __EBU_SDRMREF_VALUE
        if(__EBU_SDRMREF_INIT)  EBU_SDRMREF.U = __EBU_SDRMREF_VALUE;
#endif
#if defined EBU_SDRSTAT && defined __EBU_SDRSTAT_VALUE
        if(__EBU_SDRSTAT_INIT)  EBU_SDRSTAT.U = __EBU_SDRSTAT_VALUE;
#endif

        /*
         * Inititialize global address registers a0/a1 to support
         * __a0/__a1 storage qualifiers of the C compiler.
         */
#if __A0A1_INIT
        void * a0 = _SMALL_DATA_;        
        __asm( "mov.aa\ta0,%0"::"a"(a0) );

        void * a1 = _LITERAL_DATA_;        
        __asm( "mov.aa\ta1,%0"::"a"(a1) );
#endif

        /*
         * Inititialize global address registers a8/a9 to support
         * __a8/__a9 storage qualifiers of the C compiler. A8 and A9
         * are reserved for OS use, or for application use in cases 
         * where the application ans OS are tightly coupled.
         */
#if __A8A9_INIT
        void * a8 = _A8_DATA_;        
        __asm( "mov.aa\ta8,%0"::"a"(a8) );

        void * a9 = _A9_DATA_;        
        __asm( "mov.aa\ta9,%0"::"a"(a9) );
#endif
        
        /* Setup the context save area linked list. */
#if __CSA_INIT
        
#  if !__CPU_TC051_INITIAL__
#  define MAX_NR_OF_CSA_AREAS     1
extern int _lc_ub_csa_01[][16];    /* context save area 1 begin */
extern int _lc_ue_csa_01[][16];    /* context save area 1 end   */
static __far int (* const csa_area_begin[])[16] = { _lc_ub_csa_01 }; 
static __far int (* const csa_area_end[])[16]   = { _lc_ue_csa_01 };
#  else
#  define MAX_NR_OF_CSA_AREAS     3
extern int _lc_ub_csa_01[][16];    /* context save area 1 begin */
extern int _lc_ue_csa_01[][16];    /* context save area 1 end   */
extern int _lc_ub_csa_02[][16];    /* context save area 2 begin */
extern int _lc_ue_csa_02[][16];    /* context save area 2 end   */
extern int _lc_ub_csa_03[][16];    /* context save area 3 begin */
extern int _lc_ue_csa_03[][16];    /* context save area 3 end   */
static __far int (* const csa_area_begin[])[16] = { _lc_ub_csa_01, _lc_ub_csa_02, _lc_ub_csa_03 };        
static __far int (* const csa_area_end[])[16]   = { _lc_ue_csa_01, _lc_ue_csa_02, _lc_ue_csa_03 };
#  endif

        int  i, k;
        int  no_of_csas;
        int * csa;
        unsigned int  seg_nr, seg_idx, pcxi_val=0;
        _Bool first=true;
        
        for (i=0; i < MAX_NR_OF_CSA_AREAS; i++)
        {
                /* first calculate nr of CSAs in this area */
                no_of_csas = csa_area_end[i] - csa_area_begin[i]; 
                
                for (k=0; k < no_of_csas; k++)
                {
                        csa = csa_area_begin[i][k];
                        /* Store null pointer in last CSA (= very first time!) */
                        *csa = pcxi_val;                        

                        seg_nr  = (((unsigned int)csa >> 28) & 0xf) << 16;
                        seg_idx = (((unsigned int)csa >> 6) & 0xffff);
                        pcxi_val = seg_nr | seg_idx;
                        if (first)
                        {
                                first = false;                                
                                __mtcr(LCX, pcxi_val);
                        }                        
                }
                __mtcr(FCX, pcxi_val);
        }
#endif
        
        /*
         * PMU_TC.004 workaround:
         * The split mode is disabled on the LMB bus to workaround.
         */
#if __PMU_TC004_INITIAL__  && defined LFI_CON
        LFI_CON.U &= 0xfffffffe;        
#endif
        
        /*
         * Initialize and clear C variables.
         */
#if __C_INIT
        _c_init();      /* initialize data */
#endif  

        /*
         * initialize __clocks_per_sec,
         * the oscillator frequency is defined by __fOSC.
         */
#if __CLOCKS_PER_SEC_INIT
        setclockpersec();
#endif  

        /* initialize profiling if required 
         */        
#if __PROF_ENABLE__
        __prof_init();
#endif

        /*
         * Call a user function called _endinit() within one can initialize the 
         * registers protected via the EndInit feature.
         * Beware that protected registers are unlocked 
         * for the duration of the Time-out Period only!
         */
#ifdef _CALL_ENDINIT
        endinit_set(_ENDINIT_DISABLE);  /* disable the write-protection */
        _endinit();        
        endinit_set(_ENDINIT_ENABLE);    /* enable the write-protection  */
#endif
        
        /*
         * Call a user function before starting main().
         */
#ifdef __CALL_INIT
        _call_init();        
#endif

#if (  defined _REGUSERDEF16X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#if (__HALT_INIT_TC1 && (__HALT_VALUE_TC1 & 0x2)) || (__HALT_INIT_TC2 && (__HALT_VALUE_TC2 & 0x2))
#if __C_INIT || __CLOCKS_PER_SEC_INIT || __PROF_ENABLE__ || _CALL_ENDINIT || (defined __CALL_INIT)
        __swapmskw( (unsigned int *)&_tcx_end_c_init, 0x1, 0x1 );       /* tc0 end of initialization */
        /*
         * Before calling main, which has code core association share,
         * wait until all cores have done the global initializations
         * to avoid race conditions on initialized shared global data.
         * Only wait for running cores.
         */
#if ( defined _REGTC26X_H )
        while ( ( _tcx_end_c_init & 0x7 ) != (1 | ( ( (CPU1_DBGSR.B.HALT & 0x1)==0 ) << 1)) ) ;
#else
        while ( ( _tcx_end_c_init & 0x7 ) != (1 | ( ( (CPU1_DBGSR.B.HALT & 0x1)==0 ) << 1) | ( ( (CPU2_DBGSR.B.HALT & 0x1)==0 ) << 2)) ) ;
#endif
#endif
#endif
#endif
        
        /*
         * Call C main program.
         */
#if __USE_ARGC_ARGV
        exit( main( _argcv( argcv, __ARGCV_BUFSIZE ), (char **)argcv ) );
#else
        exit( main( 0, NULL ) );                /* argc is 0 */
#endif

        /*
         * Default trap vectors are resolved from the C-library.
         */
#if __BTV_INIT
#  if __RESOLVE_TRAP_0
#    pragma extern  _trapmmu
#  endif
#  if __RESOLVE_TRAP_1
#    pragma extern  _trapprotection
#  endif
#  if __RESOLVE_TRAP_2
#    pragma extern  _trapinstruction
#  endif
#  if __RESOLVE_TRAP_3
#    pragma extern  _trapcontext
#  endif
#  if __RESOLVE_TRAP_4
#    pragma extern  _trapbus
#  endif
#  if __RESOLVE_TRAP_5
#    pragma extern  _trapassertion
#  endif
#  if __RESOLVE_TRAP_6
#    pragma extern  _trapsystem
#  endif
#  if __RESOLVE_TRAP_7
#    pragma extern  _trapnmi
#  endif
#endif
        
}

/**************************************************************************
 *
 * FUNCTION:     endinit_set
 *
 * DESCRIPTION:  Sets or Clears the ENDINIT bit in the WDT_CON0 register
 *               in order to enabled or disable the write-protection for
 *               registers protected via the EndInit feature
 *               (ie. BTV, BIV, ISP, PCON0, DCON0).
 *
 *************************************************************************/
static void inline endinit_set( _endinit_t endinit_value )
{
        unsigned int wdt_con0;

#if !(  defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        unsigned int wdt_con1;
#endif
        /*
         * 1st step: Password access (create password and send to WDT_CON0)
         */        
        wdt_con0 = WDT_CON0.U;
#if !(  defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        wdt_con1 = WDT_CON1.U;
#endif

        wdt_con0 &= 0xffffff01;         /* clear WDTLCK, WDTHPW0, WDTHPW1 */
        wdt_con0 |= 0xf0;               /* set WDTHPW1 to 0xf */
#if (  defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        wdt_con0 |= 0x1;                /* 1 must be written to ENDINIT for password access
                                         * (but this will not actually modify the bit) */
#else
        wdt_con1 &= 0x0c;               /* copy of WDT_CON1.DR and WDT_CON1.IR (d1) */
        wdt_con0 |= wdt_con1;           /* HPW0 is WDT_CON1.DR | WDT_CON1.IR */
#endif
        WDT_CON0.U = wdt_con0;

        /*
         * 2nd step: Modify access, set the bit ENDINIT to 1 or 0 to allow access to
         *           registers: WDT_CON1, BTV, BIV, ISP and mod_CLC
         */
        wdt_con0 &= 0xfffffff0;         /* clear WDTHPW0, WDTLCK, ENDINIT  */
        wdt_con0 |= 0x02 | endinit_value;       /* WDTHPW0=0, WDTLCK=1, ENDINIT=0 */
        __isync();
        WDT_CON0.U = wdt_con0;          
        WDT_CON0.U;                     /* read is required */
}

#if (  defined _REGUSERDEF16X_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC2D5T_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
/**************************************************************************
 *
 * FUNCTION:     safety_endinit_set
 *
 * DESCRIPTION:  Sets or Clears the ENDINIT bit in the WDTSCON0 register
 *               in order to enabled or disable the write-protection for
 *               safety-critical registers protected via the EndInit feature.
 *
 *************************************************************************/
static void inline safety_endinit_set( _endinit_t endinit_value )
{
        unsigned int wdtscon0;

        /*
         * 1st step: Password access (create password and send to WDTSCON0)
         */
        wdtscon0 = SCU_WDTSCON0.U;

        wdtscon0 &= 0xffffff01;         /* clear WDTLCK, WDTHPW0, WDTHPW1 */
        wdtscon0 |= 0xf0;               /* set WDTHPW1 to 0xf */
        wdtscon0 |= 0x1;                /* 1 must be written to ENDINIT for password access
                                         * (but this will not actually modify the bit) */
        SCU_WDTSCON0.U = wdtscon0;

        /*
         * 2nd step: Modify access, set the bit ENDINIT to 1 or 0 to allow access to
         *           registers: SCU_WDTSCON1, BTV, BIV, ISP and mod_CLC
         */
        wdtscon0 &= 0xfffffff0;         /* clear WDTHPW0, WDTLCK, ENDINIT  */
        wdtscon0 |= 0x02 | endinit_value;       /* WDTHPW0=0, WDTLCK=1, ENDINIT=0 */
        __isync();
        SCU_WDTSCON0.U = wdtscon0;          
        SCU_WDTSCON0.U;                 /* read is required */
}
#endif

#if     __CLOCKS_PER_SEC_INIT
static void setclockpersec(void)
{
        unsigned long long hz = 0;

#if defined PLL_CLC && defined __fOSC
#if ( defined _REGTC11IB_H )
#define K       (PLL_CLC.B.PLL1_KDIV+1)
        if ( PLL_CLC.B.PLL1_BP )                 /* PLL Bypass Operation */
        {
                hz = __fOSC;
        }
        else
        {
                if ( PLL_CLC.B.PLL1_VCOBP )         /* VCO Bypass Operation */
                {
                        hz = __fOSC/K;
                }
                else                            /* PLL Operation */
                {
                        hz = (16*__fOSC)/K;
                }
        }
#endif

#if     (  defined _REGTC1130_H || defined _REGTC1164_H \
        || defined _REGTC1166_H || defined _REGTC1762_H || defined _REGTC1764_H || defined _REGTC1766_H \
        || defined _REGTC1766B_H || defined _REGTC1792_H || defined _REGTC1796_H || defined _REGTC1796B_H )
#define P               (PLL_CLC.B.PDIV+1)
#define N               (PLL_CLC.B.NDIV+1)
#define K               (PLL_CLC.B.KDIV+1)
#if     ( defined _REGTC1130_H )
#define __SYSFS__       SYSFSL
#else
#if     (  defined _REGTC1762_H || defined _REGTC1764_H || defined _REGTC1766B_H \
        || defined _REGTC1164_H || defined _REGTC1166_H )
#define __SYSFS__       RSV
#else
#define __SYSFS__       SYSFS
#endif
#endif
#define SYSCLK(CPUCLK)  (CPUCLK/(2-PLL_CLC.B.__SYSFS__))
#define STMCLK(CPUCLK)  (SYSCLK(CPUCLK)/STM_CLC.B.RMC)
#define FVCOBASE        __fOSC
        if ( PLL_CLC.B.BYPPIN )                                                         /* Direct drive */
        {
                hz = STMCLK(__fOSC);
        }
        else
        {
                if ( PLL_CLC.B.VCOBYP )                                                 /* VCO Bypass Mode */
                {
                        hz = STMCLK(__fOSC/(P*K));
                }
                else
                {
                        if ( !PLL_CLC.B.OSCDISC && PLL_CLC.B.LOCK )     /* PLL Mode */
                        {
                                hz = STMCLK((N*__fOSC)/(P*K));
                        }
                        else                                                                            /* PLL base mode */
                        {
                                hz = STMCLK(FVCOBASE/K);
                        }
                }
        }
#endif
#endif

#if defined SCU_PLLSTAT && defined __fOSC
#if     (  defined _REGTC1167_H || defined _REGTC1197_H || defined _REGTC1337_H || defined _REGTC1367_H \
        || defined _REGTC1387_H || defined _REGTC1732_H || defined _REGTC1728_H || defined _REGTC1734_H \
        || defined _REGTC1735_H || defined _REGTC1736_H || defined _REGTC1738_H || defined _REGTC1746_H \
        || defined _REGTC1747_H || defined _REGTC1748_H || defined _REGTC1767_H || defined _REGTC1768_H \
        || defined _REGTC1782_H || defined _REGTC1784_H || defined _REGTC1184_H || defined _REGTC1797_H \
        || defined _REGTC1791_H || defined _REGTC1793_H || defined _REGTC1798_H || defined _REGTC1724_H \
        || defined _REGTC23X_ADAS_H || defined _REGTC23X_H \
        || defined _REGTC2D5T_H || defined _REGTC27X_H  || defined _REGTC27XB_H || defined _REGTC27XC_H \
        || defined _REGTC26X_H  || defined _REGTC29X_H)
#define P               (SCU_PLLCON0.B.PDIV+1)
#define N               (SCU_PLLCON0.B.NDIV+1)
#define K1              (SCU_PLLCON1.B.K1DIV+1)
#define K2              (SCU_PLLCON1.B.K2DIV+1)
#if     ( defined _REGTC2D5T_H )
#define STM_CLC_RMC     (STM0_CLC.B.RMC)
#else
#if     ( defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#define STM_CLC_RMC     1
#else   
#define STM_CLC_RMC     (STM_CLC.B.RMC)         
#endif
#endif
#if     ( defined _REGTC1337_H || defined _REGTC1367_H || defined _REGTC1387_H || defined _REGTC1768_H )
#define SYSCLK(CPUCLK)  (CPUCLK)
#else
#if ( defined _REGTC2D5T_H )
#define SYSCLK(CPUCLK)  (CPUCLK/(SCU_CCUCON0.B.SPBDIV+1))
#else
#if ( defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
#define SYSCLK(CPUCLK)  (CPUCLK/SCU_CCUCON1.B.STMDIV)
#else
#define SYSCLK(CPUCLK)  (CPUCLK/(SCU_CCUCON0.B.FPIDIV+1))
#endif
#endif
#endif
#define STMCLK(CPUCLK)  (SYSCLK(CPUCLK)/STM_CLC_RMC)
#define FVCOBASE        __fOSC
        if ( SCU_PLLSTAT.B.VCOBYST )    /* Prescaler mode */
        {
                hz = STMCLK(__fOSC/K1);
        }
#if ( defined _REGTC2D5T_H || defined _REGTC23X_ADAS_H || defined _REGTC23X_H || defined _REGTC27X_H || defined _REGTC27XB_H || defined _REGTC27XC_H || defined _REGTC26X_H || defined _REGTC29X_H)
        else if ( SCU_CCUCON0.B.CLKSEL==0)
        {
                hz = STMCLK(100000000);         /* back-up clock */
        }
#endif
        else
        {
                if ( SCU_PLLSTAT.B.FINDIS )     /* Free running mode */
                {
                        hz = STMCLK(FVCOBASE/K2);
                }
                else                                            /* Normal mode */
                {
                        hz = STMCLK((N*__fOSC)/(P*K2));
                }
        }
#endif
#endif
        setfoschz ( hz );
}
#endif
