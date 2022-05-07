/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
**************************************************************************
** \file       td_types.c
**
** \brief      redefine data types for top use
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   td_types.c  ,v 1.0 2019/12/12  11:30:00 Kite.Su Exp $
**
**************************************************************************
*/

#ifndef _MD_TYPES_H_
#define _MD_TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************

typedef enum {
    MS_FALSE = 0,
    MS_TRUE  = 1,
} MS_BOOL;


#ifndef size_t
typedef unsigned int                MS_size_t;
#endif
#ifndef s8
typedef signed char                 MS_S8;
#endif
#ifndef u8
typedef unsigned char               MS_U8;
#endif
#ifndef s16
typedef signed short                MS_S16;
#endif
#ifndef u16
typedef unsigned short              MS_U16;
#endif
#ifndef s32
typedef signed int                 MS_S32;
#endif
#ifndef u32
typedef unsigned int               MS_U32;
#endif
#ifndef s64
typedef signed long long            MS_S64;
#endif
#ifndef u64
typedef unsigned long  long         MS_U64;
#endif
#if 0
#ifndef TRUE
#define TRUE                        (1)
#endif
#ifndef FALSE
#define FALSE                       (0)
#endif
#endif
#ifndef bool
#define bool MS_U8
#endif

#ifndef MS_OK
#define MS_OK                        (0)
#endif
#ifndef MS_ERROR
#define MS_ERROR                     (-1)
#endif



#ifndef MS_INLINE
#define MS_INLINE                        __inline
#endif

#ifndef ABS
#define ABS(x)                      (((x)>=0)? (x):(-x))
#endif
#ifndef MIN
#define MIN(x,y)                    (((x)<(y))? (x):(y))
#endif
#ifndef MAX
#define MAX(x,y)                    (((x)>(y))? (x):(y))
#endif
#ifndef MAX3
#define MAX3(x,y,z)                 (MAX((x),MAX(y,z)))
#endif
#ifndef MIN3
#define MIN3(x,y,z)                 (MIN(MIN(x,y),z))
#endif
#ifndef CHECK_LIMIT
#define CHECK_LIMIT(x,low,high)     (MAX((low), MIN((x), (high))))
#endif
#ifndef CLIP3
#define CLIP3(x,y,z)                (((z)<(x))? (x):(((z)>(y))? (y):(z)))
#endif
#ifndef RSD
#define RSD(x)                      ((x&2)?(x|1):(x&(~1)))
#endif
#ifndef SWAP
#define SWAP(x,y)                   {s32 t = (x); (x) = (y); (y) = t;}
#endif
#ifndef ABS_DIFF
#define ABS_DIFF(x,y)               (((x)>=(y))? ((x)-(y)):((y)-(x)))
#endif
#ifndef DIV_DIV
#define DIV_DIV(x,y)                ((x>0)? (x+(y>>1))/y : (x-(y>>1))/y)
#endif
#ifndef ROUND_UP
#define ROUND_UP(size, align)       (((size) + ((align) - 1)) & ~((align) - 1))
#endif

#ifndef NULL
#define NULL 0
#endif


typedef unsigned int   pthread_cond_t;
typedef unsigned int   pthread_mutex_t;
/*!
****************************************************************************
** \brief The generic type of a driver handle.
**
** This type represents a handle for a driver instance. It is returned
** by the driver's \b Open function and must be provided as first
** parameter to each API call.
** The content of the handle is driver specific and must not be
** interpreted by the system.
****************************************************************************
*/
typedef void* MS_SYS_HandleT;



//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************





typedef enum 
{    
    MS_ID_SYS     = 0,
    MS_ID_VO      = 1,
    MS_ID_VI      = 2,  
} MS_MODULE_ID_E;

//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif



#endif 

