/****************************************************************************/
/* FILE NAME:    os_type.h                                                  */
/* CREATE ON:    Aug 26, 2015                                               */
/* AUTHER:       Yanpeng.xi                                                 */
/* DESCRIPTION:  The h file includes the thread type definitions            */ 
/* COMMENT:      Multicore OS based on Aurix 275C app kit and TASKING 4.3   */
/*               compiler                                                   */
/****************************************************************************/
#ifndef OS_TYPE_H
#define OS_TYPE_H

/****************************************************************************/
/* Type Definitions                                                         */
/****************************************************************************/
typedef unsigned char       osu8_t; 
typedef unsigned short      osu16_t;
typedef unsigned int        osu32_t;     
typedef unsigned long long  osu64_t; 

typedef char       os8_t; 
typedef short      os16_t;
typedef int        os32_t;     
typedef long long  os64_t; 

/****************************************************************************/
/* Macro Definitions                                                        */
/****************************************************************************/
#define  ENABLE    (1)
#define  DISABLE   (0)

#define  ON        (1)
#define  OFF       (0)

#define  true      (1)
#define  false     (0)

#define OS_EXTERN  extern 
#define OS_INLINE  inline
#define OS_CONST   const
#define OS_STATIC  static

#define STACK_SIZE_KB(size)   size*1024

//#define OS_NULL (void*)0
 
#endif /* End of OS_TYPE_H */

