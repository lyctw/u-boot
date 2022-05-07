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
** \file       mh_td.h
**
** \brief      td hw register layer
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   mh_td.h  ,v 1.0 2019/12/16  Kite.Su Exp $
**
**************************************************************************
*/



#ifndef _MH_ISP_H
#define _MH_ISP_H

#include <td_types.h>

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
//#include <vo/vo_types.h> /* global type definitions */

#endif
#ifndef MH_INLINE
#define MH_INLINE                        __inline
#endif

#ifndef MH_INLINE
#define MH_INLINE                        __inline
#endif
#ifndef MH_INLINE_LEVEL
#define MH_INLINE_LEVEL                        0
#endif


#define MH_TD_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define MH_TD_DEBUG_PRINT_FUNCTION printk
#else
#define MH_TD_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if MH_VO_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef MH_INLINE_LEVEL
  #error "MH_INLINE_LEVEL is not defined!"
#endif
#if MH_INLINE_LEVEL > 2
  #error "MH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef MH_INLINE
  #error "MH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef MH_INLINE_LEVEL
  #define MH_INLINE_LEVEL 0
#endif
#include <video_subsystem_addr.h>

#define REG_TD_BASE TD_BASE_ADDR

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_TD_WRAPSWRST                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0000) /* read/write */
#define REG_TD_WRAPCLKEN                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x000c) /* read/write */
#define REG_TD_WRAPDMAARBMODE                               FIO_ADDRESS(TD,REG_TD_BASE + 0x0020) /* read/write */
#define REG_TD_WRAPDMAWEIGHTWR0                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0024) /* read/write */
#define REG_TD_WRAPDMAWEIGHTWR1                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0028) /* read/write */
#define REG_TD_WRAPDMAWEIGHTRD0                             FIO_ADDRESS(TD,REG_TD_BASE + 0x002C) /* read/write */
#define REG_TD_WRAPDMAWEIGHTRD1                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0030) /* read/write */
#define REG_TD_WRAPDMAPRIORITYWR                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0034) /* read/write */
#define REG_TD_WRAPDMAPRIORITYRD                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0038) /* read/write */
#define REG_TD_WRAPDMAIDWR                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x003c) /* read/write */
#define REG_TD_WRAPDMAIDRD                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x0040) /* read/write */
#define REG_TD_WRAPCFG                                      FIO_ADDRESS(TD,REG_TD_BASE + 0x0078) /* read/write */
#define REG_TD_WRAPINT                                      FIO_ADDRESS(TD,REG_TD_BASE + 0x007c) /* read/write */
#define REG_TD_ROTCMD                                       FIO_ADDRESS(TD,REG_TD_BASE + 0x0080) /* read/write */
#define REG_TD_ROTCTL                                       FIO_ADDRESS(TD,REG_TD_BASE + 0x0084) /* read/write */
#define REG_TD_ROTTIMEOUT                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0088) /* read/write */
#define REG_TD_ROTIMAGESIZEACTIVE                           FIO_ADDRESS(TD,REG_TD_BASE + 0x008c) /* read/write */
#define REG_TD_ROTADDRBASEYSRC                              FIO_ADDRESS(TD,REG_TD_BASE + 0x0090) /* read/write */
#define REG_TD_ROTADDRBASEUSRC                              FIO_ADDRESS(TD,REG_TD_BASE + 0x0094) /* read/write */
#define REG_TD_ROTADDRBASEVSRC                              FIO_ADDRESS(TD,REG_TD_BASE + 0x0098) /* read/write */
#define REG_TD_ROTADDRBASEYDES                              FIO_ADDRESS(TD,REG_TD_BASE + 0x009c) /* read/write */
#define REG_TD_ROTADDRBASEUDES                              FIO_ADDRESS(TD,REG_TD_BASE + 0x00a0) /* read/write */
#define REG_TD_ROTADDRBASEVDES                              FIO_ADDRESS(TD,REG_TD_BASE + 0x00a4) /* read/write */
#define REG_TD_ROTSTRIDEY                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x00a8) /* read/write */
#define REG_TD_ROTSTRIDEU                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x00ac) /* read/write */
#define REG_TD_ROTSTRIDEV                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x00b0) /* read/write */
#define REG_TD_ROTST                                        FIO_ADDRESS(TD,REG_TD_BASE + 0x00c0) /* read */
#define REG_TD_SOFTRSTCTL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0800) /* read/write */
#define REG_TD_DMASWCTL                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0808) /* read/write */
#define REG_TD_LAYER0LINE0BDCTL                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0880) /* read/write */
#define REG_TD_LAYER0LINE1BDCTL                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0884) /* read/write */
#define REG_TD_LAYER0LINE2BDCTL                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0888) /* read/write */
#define REG_TD_LAYER0LINE3BDCTL                             FIO_ADDRESS(TD,REG_TD_BASE + 0x088c) /* read/write */
#define REG_TD_LAYER4BDCTL                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x089c) /* read/write */
#define REG_TD_DISPXZONE                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x08c0) /* read/write */
#define REG_TD_DISPYZONE                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x08c4) /* read/write */
#define REG_TD_LAYER0XCTL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x08c8) /* read/write */
#define REG_TD_LAYER0YCTL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x08cc) /* read/write */
#define REG_TD_LAYER4XCTL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x08e8) /* read/write */
#define REG_TD_LAYER4YCTL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x08ec) /* read/write */
#define REG_TD_DISPHSYNCCTL                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0900) /* read/write */
#define REG_TD_DISPVSYNCCTL                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0904) /* read/write */
#define REG_TD_DISPCTL                                      FIO_ADDRESS(TD,REG_TD_BASE + 0x0914) /* read/write */
#define REG_TD_DISPENABLE                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0918) /* read/write */
#define REG_TD_DISPSIZE                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x091c) /* read/write */
#define REG_TD_LAYER0CTL                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0940) /* read/write */
#define REG_TD_LAYER0SCALEBLENTH                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0944) /* read/write */
#define REG_TD_LAYER0IMGINDATMODE                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0948) /* read/write */
#define REG_TD_LAYER0BADDR0Y                                FIO_ADDRESS(TD,REG_TD_BASE + 0x094c) /* read/write */
#define REG_TD_LAYER0BADDR0UV                               FIO_ADDRESS(TD,REG_TD_BASE + 0x0950) /* read/write */
#define REG_TD_LAYER0IMGINPIXSZIE                           FIO_ADDRESS(TD,REG_TD_BASE + 0x095c) /* read/write */
#define REG_TD_LAYER0IMGOUTPIXSZIE                          FIO_ADDRESS(TD,REG_TD_BASE + 0x0960) /* read/write */
#define REG_TD_LAYER0IMGINSTRIDE                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0964) /* read/write */
#define REG_TD_LAYER0IMGINOFFSET                            FIO_ADDRESS(TD,REG_TD_BASE + 0x096c) /* read/write */
#define REG_TD_LAYER0VSCALESTEP                             FIO_ADDRESS(TD,REG_TD_BASE + 0x0974) /* read/write */
#define REG_TD_LAYER0VSCALEST                               FIO_ADDRESS(TD,REG_TD_BASE + 0x0978) /* read/write */
#define REG_TD_LAYER0HSCALESTEP                             FIO_ADDRESS(TD,REG_TD_BASE + 0x097c) /* read/write */
#define REG_TD_LAYER0HSCALEST                               FIO_ADDRESS(TD,REG_TD_BASE + 0x0980) /* read/write */
#define REG_TD_LAYER0BASEMODE                               FIO_ADDRESS(TD,REG_TD_BASE + 0x0984) /* read/write */
#define REG_TD_OSD0INFO                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0a80) /* read/write */
#define REG_TD_OSD0SIZE                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0a84) /* read/write */
#define REG_TD_OSD0VLUADDR0                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0a88) /* read/write */
#define REG_TD_OSD0ALPADDR0                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0a8c) /* read/write */
#define REG_TD_OSD0DMACTL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0a98) /* read/write */
#define REG_TD_OSD0STRIDE                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0a9c) /* read/write */
#define REG_TD_OSDRGB2YUVCTL                                FIO_ADDRESS(TD,REG_TD_BASE + 0x0b40) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF00                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b44) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF01                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b48) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF02                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b4c) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF03                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b50) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF10                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b54) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF11                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b58) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF12                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b5c) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF13                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b60) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF20                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b64) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF21                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b68) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF22                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b6c) /* read/write */
#define REG_TD_OSDRGB2YUVCOEFF23                            FIO_ADDRESS(TD,REG_TD_BASE + 0x0b70) /* read/write */
#define REG_TD_DISPYUV2RGBCTL                               FIO_ADDRESS(TD,REG_TD_BASE + 0x0b80) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF00                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b84) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF01                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b88) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF02                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b8c) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF03                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b90) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF10                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b94) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF11                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b98) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF12                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0b9c) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF13                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0ba0) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF20                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0ba4) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF21                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0ba8) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF22                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0bac) /* read/write */
#define REG_TD_DISPYUV2RGBCOEFF23                           FIO_ADDRESS(TD,REG_TD_BASE + 0x0bb0) /* read/write */
#define REG_TD_DISPMIXALP0                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x0bC4) /* read/write */
#define REG_TD_DISPMIXALP1                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x0bC8) /* read/write */
#define REG_TD_DISPMIXSEL                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0bcc) /* read/write */
#define REG_TD_DISPBACKGROUD                                FIO_ADDRESS(TD,REG_TD_BASE + 0x0bd0) /* read/write */
#define REG_TD_DISPIRQ0                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0be0) /* read/write */
#define REG_TD_DISPIRQ1                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0be4) /* read/write */
#define REG_TD_DISPIRQ2                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0be8) /* read/write */
#define REG_TD_DISPIRQ                                      FIO_ADDRESS(TD,REG_TD_BASE + 0x0bec) /* read/write */
#define REG_TD_WBDMA                                        FIO_ADDRESS(TD,REG_TD_BASE + 0x0c00) /* read/write */
#define REG_TD_WBMODE                                       FIO_ADDRESS(TD,REG_TD_BASE + 0x0c04) /* read/write */
#define REG_TD_WBPIXEL                                      FIO_ADDRESS(TD,REG_TD_BASE + 0x0c08) /* read/write */
#define REG_TD_WBBASEADDR0Y                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0c0c) /* read/write */
#define REG_TD_WBBASEADDR1Y                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0c10) /* read/write */
#define REG_TD_WBBASEADDR0UV                                FIO_ADDRESS(TD,REG_TD_BASE + 0x0c14) /* read/write */
#define REG_TD_WBBASEADDR1UV                                FIO_ADDRESS(TD,REG_TD_BASE + 0x0c18) /* read/write */
#define REG_TD_WBOUTY                                       FIO_ADDRESS(TD,REG_TD_BASE + 0x0c1c) /* read/write */
#define REG_TD_WBOUTUV                                      FIO_ADDRESS(TD,REG_TD_BASE + 0x0c20) /* read/write */
#define REG_TD_WBLOOP                                       FIO_ADDRESS(TD,REG_TD_BASE + 0x0c24) /* read/write */
#define REG_TD_WBACTIVEV                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0c28) /* read/write */
#define REG_TD_WBACTIVEH                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0c2c) /* read/write */
#define REG_TD_WBCH1DMA                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0c40) /* read/write */
#define REG_TD_WBCH1ERRUNIT                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0c44) /* read/write */
#define REG_TD_WBCH1ERRTH                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0c48) /* read/write */
#define REG_TD_WBCH1INFO                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0c4c) /* read/write */
#define REG_TD_WBCH1RST                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0c50) /* read/write */
#define REG_TD_WBCH2DMA                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0c60) /* read/write */
#define REG_TD_WBCH2ERRUNIT                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0c64) /* read/write */
#define REG_TD_WBCH2ERRTH                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0c68) /* read/write */
#define REG_TD_WBCH2INFO                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0c6c) /* read/write */
#define REG_TD_WBCH2RST                                     FIO_ADDRESS(TD,REG_TD_BASE + 0x0c70) /* read/write */
#define REG_TD_WBYOUTIDLE                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0c80) /* read */
#define REG_TD_WBUVOUTIDLE                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x0c84) /* read */
#define REG_TD_WBYOUTINT                                    FIO_ADDRESS(TD,REG_TD_BASE + 0x0c88) /* read */
#define REG_TD_WBUVOUTINT                                   FIO_ADDRESS(TD,REG_TD_BASE + 0x0c8c) /* read */
#define REG_TD_WBYOUTFUNC0                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x0c90) /* read */
#define REG_TD_WBYOUTFUNC1                                  FIO_ADDRESS(TD,REG_TD_BASE + 0x0c94) /* read */
#define REG_TD_WBUVOUTFUNC0                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0c98) /* read */
#define REG_TD_WBUVOUTFUNC1                                 FIO_ADDRESS(TD,REG_TD_BASE + 0x0c9c) /* read */


/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* TD_WrapSwRst */
    MS_U32 all;
    struct {
        MS_U32 rotationrw                  : 1;
        MS_U32 mixerrw                     : 1;
        MS_U32                             : 6;
        MS_U32 axiwr                       : 1;
        MS_U32 axird                       : 1;
        MS_U32                             : 22;
    } bitc;
} MH_TD_WRAPSWRST_S;

typedef union { /* TD_WrapClkEn */
    MS_U32 all;
    struct {
        MS_U32 ch0rd                       : 1;
        MS_U32 ch1rd                       : 1;
        MS_U32 ch2rd                       : 1;
        MS_U32 ch3rd                       : 1;
        MS_U32 ch4rd                       : 1;
        MS_U32 ch5rd                       : 1;
        MS_U32                             : 2;
        MS_U32 ch0wr                       : 1;
        MS_U32 ch1wr                       : 1;
        MS_U32 ch2wr                       : 1;
        MS_U32                             : 5;
        MS_U32 axiwr                       : 1;
        MS_U32 axird                       : 1;
        MS_U32                             : 14;
    } bitc;
} MH_TD_WRAPCLKEN_S;

typedef union { /* TD_WrapDmaArbMode */
    MS_U32 all;
    struct {
        MS_U32 wr                          : 1;
        MS_U32 rd                          : 1;
        MS_U32                             : 30;
    } bitc;
} MH_TD_WRAPDMAARBMODE_S;

typedef union { /* TD_WrapDmaWeightWR0 */
    MS_U32 all;
    struct {
        MS_U32 ch0                         : 8;
        MS_U32 ch1                         : 8;
        MS_U32 ch2                         : 8;
        MS_U32 ch3                         : 8;
    } bitc;
} MH_TD_WRAPDMAWEIGHTWR0_S;

typedef union { /* TD_WrapDmaWeightWR1 */
    MS_U32 all;
    struct {
        MS_U32 ch4                         : 8;
        MS_U32 ch5                         : 8;
        MS_U32 ch6                         : 8;
        MS_U32 ch7                         : 8;
    } bitc;
} MH_TD_WRAPDMAWEIGHTWR1_S;

typedef union { /* TD_WrapDmaWeightRD0 */
    MS_U32 all;
    struct {
        MS_U32 ch0                         : 8;
        MS_U32 ch1                         : 8;
        MS_U32 ch2                         : 8;
        MS_U32 ch3                         : 8;
    } bitc;
} MH_TD_WRAPDMAWEIGHTRD0_S;

typedef union { /* TD_WrapDmaWeightRD1 */
    MS_U32 all;
    struct {
        MS_U32 ch4                         : 8;
        MS_U32 ch5                         : 8;
        MS_U32 ch6                         : 8;
        MS_U32 ch7                         : 8;
    } bitc;
} MH_TD_WRAPDMAWEIGHTRD1_S;

typedef union { /* TD_WrapDmaPriorityWR */
    MS_U32 all;
    struct {
        MS_U32 ch0                         : 4;
        MS_U32 ch1                         : 4;
        MS_U32 ch2                         : 4;
        MS_U32 ch3                         : 4;
        MS_U32 ch4                         : 4;
        MS_U32 ch5                         : 4;
        MS_U32 ch6                         : 4;
        MS_U32 ch7                         : 4;
    } bitc;
} MH_TD_WRAPDMAPRIORITYWR_S;

typedef union { /* TD_WrapDmaPriorityRD */
    MS_U32 all;
    struct {
        MS_U32 ch0                         : 4;
        MS_U32 ch1                         : 4;
        MS_U32 ch2                         : 4;
        MS_U32 ch3                         : 4;
        MS_U32 ch4                         : 4;
        MS_U32 ch5                         : 4;
        MS_U32 ch6                         : 4;
        MS_U32 ch7                         : 4;
    } bitc;
} MH_TD_WRAPDMAPRIORITYRD_S;

typedef union { /* TD_WrapDmaIdWR */
    MS_U32 all;
    struct {
        MS_U32 ch0                         : 4;
        MS_U32 ch1                         : 4;
        MS_U32 ch2                         : 4;
        MS_U32 ch3                         : 4;
        MS_U32 ch4                         : 4;
        MS_U32 ch5                         : 4;
        MS_U32 ch6                         : 4;
        MS_U32 ch7                         : 4;
    } bitc;
} MH_TD_WRAPDMAIDWR_S;

typedef union { /* TD_WrapDmaIdRD */
    MS_U32 all;
    struct {
        MS_U32 ch0                         : 4;
        MS_U32 ch1                         : 4;
        MS_U32 ch2                         : 4;
        MS_U32 ch3                         : 4;
        MS_U32 ch4                         : 4;
        MS_U32 ch5                         : 4;
        MS_U32 ch6                         : 4;
        MS_U32 ch7                         : 4;
    } bitc;
} MH_TD_WRAPDMAIDRD_S;

typedef union { /* TD_WrapCfg */
    MS_U32 all;
    struct {
        MS_U32 done                        : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WRAPCFG_S;

typedef union { /* TD_WrapInt */
    MS_U32 all;
    struct {
        MS_U32 rotationdone                : 1;
        MS_U32 rotationtimeout             : 1;
        MS_U32 mixerdone                   : 1;
        MS_U32                             : 29;
    } bitc;
} MH_TD_WRAPINT_S;

typedef union { /* TD_RotCmd */
    MS_U32 all;
    struct {
        MS_U32 framestart                  : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_ROTCMD_S;

typedef union { /* TD_RotCtl */
    MS_U32 all;
    struct {
        MS_U32 mode                        : 2;
        MS_U32                             : 2;
        MS_U32 pixformat                   : 2;
        MS_U32                             : 2;
        MS_U32 Inswap                      : 1;
        MS_U32 endianInEn                  : 1;
        MS_U32 Outswap                     : 1;
        MS_U32 endianOutEn                 : 1;
        MS_U32                             : 4;
        MS_U32 otmaxrd                     : 6;
        MS_U32                             : 2;
        MS_U32 otmaxwr                     : 6;
        MS_U32                             : 2;
    } bitc;
} MH_TD_ROTCTL_S;

typedef union { /* TD_RotTimeOut */
    MS_U32 all;
    struct {
        MS_U32 val                         : 16;
        MS_U32                             : 16;
    } bitc;
} MH_TD_ROTTIMEOUT_S;

typedef union { /* TD_RotImageSizeActive */
    MS_U32 all;
    struct {
        MS_U32 hor                         : 16;
        MS_U32 ver                          : 16;
    } bitc;
} MH_TD_ROTIMAGESIZEACTIVE_S;

typedef union { /* TD_RotStrideY */
    MS_U32 all;
    struct {
        MS_U32 src                         : 16;
        MS_U32 des                         : 16;
    } bitc;
} MH_TD_ROTSTRIDEY_S;

typedef union { /* TD_RotStrideU */
    MS_U32 all;
    struct {
        MS_U32 src                         : 16;
        MS_U32 des                         : 16;
    } bitc;
} MH_TD_ROTSTRIDEU_S;

typedef union { /* TD_RotStrideV */
    MS_U32 all;
    struct {
        MS_U32 src                         : 16;
        MS_U32 des                         : 16;
    } bitc;
} MH_TD_ROTSTRIDEV_S;

typedef union { /* TD_RotSt */
    MS_U32 all;
    struct {
        MS_U32 frameend                    : 1;
        MS_U32 done                        : 3;
        MS_U32                             : 4;
        MS_U32 dmard                       : 3;
        MS_U32                             : 1;
        MS_U32 dmawr                       : 3;
        MS_U32                             : 1;
        MS_U32 cyclecnt                    : 16;
    } bitc;
} MH_TD_ROTST_S;

typedef union { /* TD_SoftRstCtl */
    MS_U32 all;
    struct {
        MS_U32 mix                         : 1;
        MS_U32 axi                         : 1;
        MS_U32 apb                         : 1;
        MS_U32 core                        : 1;
        MS_U32                             : 28;
    } bitc;
} MH_TD_SOFTRSTCTL_S;

typedef union { /* TD_DmaSwCtl */
    MS_U32 all;
    struct {
        MS_U32 reqwr                       : 1;
        MS_U32                             : 3;
        MS_U32 reqrd                       : 1;
        MS_U32                             : 27;
    } bitc;
} MH_TD_DMASWCTL_S;

typedef union { /* TD_Layer0Line0BdCtl */
    MS_U32 all;
    struct {
        MS_U32 limiten                     : 1;
        MS_U32                             : 7;
        MS_U32 outstand                    : 5;
        MS_U32                             : 19;
    } bitc;
} MH_TD_LAYER0LINE0BDCTL_S;

typedef union { /* TD_Layer0Line1BdCtl */
    MS_U32 all;
    struct {
        MS_U32 limiten                     : 1;
        MS_U32                             : 7;
        MS_U32 outstand                    : 5;
        MS_U32                             : 19;
    } bitc;
} MH_TD_LAYER0LINE1BDCTL_S;

typedef union { /* TD_Layer0Line2BdCtl */
    MS_U32 all;
    struct {
        MS_U32 limiten                     : 1;
        MS_U32                             : 7;
        MS_U32 outstand                    : 5;
        MS_U32                             : 19;
    } bitc;
} MH_TD_LAYER0LINE2BDCTL_S;

typedef union { /* TD_Layer0Line3BdCtl */
    MS_U32 all;
    struct {
        MS_U32 limiten                     : 1;
        MS_U32                             : 7;
        MS_U32 outstand                    : 5;
        MS_U32                             : 19;
    } bitc;
} MH_TD_LAYER0LINE3BDCTL_S;

typedef union { /* TD_Layer4BdCtl */
    MS_U32 all;
    struct {
        MS_U32 limiten                     : 1;
        MS_U32                             : 7;
        MS_U32 outstand                    : 5;
        MS_U32                             : 19;
    } bitc;
} MH_TD_LAYER4BDCTL_S;

typedef union { /* TD_DispXZone */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_DISPXZONE_S;

typedef union { /* TD_DispYZone */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_DISPYZONE_S;

typedef union { /* TD_Layer0XCtl */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER0XCTL_S;

typedef union { /* TD_Layer0YCtl */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER0YCTL_S;

typedef union { /* TD_Layer4XCtl */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER4XCTL_S;

typedef union { /* TD_Layer4YCtl */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER4YCTL_S;

typedef union { /* TD_DispHsyncCtl */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_DISPHSYNCCTL_S;

typedef union { /* TD_DispVsyncCtl */
    MS_U32 all;
    struct {
        MS_U32 start                       : 13;
        MS_U32                             : 3;
        MS_U32 stop                        : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_DISPVSYNCCTL_S;

typedef union { /* TD_DispCtl */
    MS_U32 all;
    struct {
        MS_U32 vcntbit0                    : 1;
        MS_U32                             : 7;
        MS_U32 secndfoffset                  : 1;
        MS_U32                             : 7;
        MS_U32 framesyncdly                : 8;
        MS_U32                             : 8;
    } bitc;
} MH_TD_DISPCTL_S;

typedef union { /* TD_DispEnable */
    MS_U32 all;
    struct {
        MS_U32 layer0en                    : 1;
        MS_U32 layer0enhs                  : 1;
        MS_U32 layer0Wenhs                 : 1;
        MS_U32                             : 1;
        MS_U32 layer4en                    : 1;
        MS_U32 layer4enhs                  : 1;
        MS_U32 layer4Wenhs                 : 1;
        MS_U32 framestart                  : 1;
        MS_U32                             : 24;
    } bitc;
} MH_TD_DISPENABLE_S;

typedef union { /* TD_DispSize */
    MS_U32 all;
    struct {
        MS_U32 hsize                       : 13;
        MS_U32                             : 3;
        MS_U32 vsize                       : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_DISPSIZE_S;

typedef union { /* TD_Layer0Ctl */
    MS_U32 all;
    struct {
        MS_U32 enable                      : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_LAYER0CTL_S;

typedef union { /* TD_Layer0ScaleBlenth */
    MS_U32 all;
    struct {
        MS_U32 blen                        : 4;
        MS_U32                             : 28;
    } bitc;
} MH_TD_LAYER0SCALEBLENTH_S;

typedef union { /* TD_Layer0ImgInDatMode */
    MS_U32 all;
    struct {
        MS_U32 datmode                     : 5;
        MS_U32                             : 3;
        MS_U32 endiany                     : 2;
        MS_U32                             : 2;
        MS_U32 endianuv                    : 3;
        MS_U32                             : 9;
        MS_U32 swapuv                      : 1;
        MS_U32                             : 7;
    } bitc;
} MH_TD_LAYER0IMGINDATMODE_S;

typedef union { /* TD_Layer0ImgInPixSzie */
    MS_U32 all;
    struct {
        MS_U32 hsize                       : 13;
        MS_U32                             : 3;
        MS_U32 vsize                       : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER0IMGINPIXSZIE_S;

typedef union { /* TD_Layer0ImgOutPixSzie */
    MS_U32 all;
    struct {
        MS_U32 hsize                       : 13;
        MS_U32                             : 3;
        MS_U32 vsize                       : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER0IMGOUTPIXSZIE_S;

typedef union { /* TD_Layer0ImgInStride */
    MS_U32 all;
    struct {
        MS_U32 hsize                       : 13;
        MS_U32                             : 3;
        MS_U32 vsize                       : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER0IMGINSTRIDE_S;

typedef union { /* TD_Layer0ImgInOffset */
    MS_U32 all;
    struct {
        MS_U32 hoffset                     : 13;
        MS_U32                             : 3;
        MS_U32 voffset                     : 13;
        MS_U32                             : 3;
    } bitc;
} MH_TD_LAYER0IMGINOFFSET_S;

typedef union { /* TD_Layer0VscaleStep */
    MS_U32 all;
    struct {
        MS_U32 pstep                       : 8;
        MS_U32                             : 8;
        MS_U32 dstep                       : 16;
    } bitc;
} MH_TD_LAYER0VSCALESTEP_S;

typedef union { /* TD_Layer0VscaleSt */
    MS_U32 all;
    struct {
        MS_U32 pstep                       : 16;
        MS_U32                             : 16;
    } bitc;
} MH_TD_LAYER0VSCALEST_S;

typedef union { /* TD_Layer0HscaleStep */
    MS_U32 all;
    struct {
        MS_U32 pstep                       : 8;
        MS_U32                             : 8;
        MS_U32 dstep                       : 16;
    } bitc;
} MH_TD_LAYER0HSCALESTEP_S;

typedef union { /* TD_Layer0HscaleSt */
    MS_U32 all;
    struct {
        MS_U32 pstep                       : 16;
        MS_U32                             : 16;
    } bitc;
} MH_TD_LAYER0HSCALEST_S;

typedef union { /* TD_Layer0BaseMode */
    MS_U32 all;
    struct {
        MS_U32 mode                        : 1;
        MS_U32                             : 3;
        MS_U32 base0mask                   : 1;
        MS_U32                             : 3;
        MS_U32 base1mask                   : 1;
        MS_U32                             : 3;
        MS_U32 addrflag                    : 1;
        MS_U32                             : 19;
    } bitc;
} MH_TD_LAYER0BASEMODE_S;

typedef union { /* TD_Osd0Info */
    MS_U32 all;
    struct {
        MS_U32 osdtype                     : 4;
        MS_U32 alphatpye                   : 3;
        MS_U32                             : 25;
    } bitc;
} MH_TD_OSD0INFO_S;

typedef union { /* TD_Osd0Size */
    MS_U32 all;
    struct {
        MS_U32 width                       : 16;
        MS_U32 height                      : 16;
    } bitc;
} MH_TD_OSD0SIZE_S;

typedef union { /* TD_Osd0DMACtl */
    MS_U32 all;
    struct {
        MS_U32 dmarequestlen               : 4;
        MS_U32 dmamap                      : 2;
        MS_U32 rgbrev                      : 1;
        MS_U32                             : 25;
    } bitc;
} MH_TD_OSD0DMACTL_S;

typedef union { /* TD_Osd0Stride */
    MS_U32 all;
    struct {
        MS_U32 osdstride                   : 16;
        MS_U32 alpstride                   : 16;
    } bitc;
} MH_TD_OSD0STRIDE_S;

typedef union { /* TD_OsdRGB2YUVCtl */
    MS_U32 all;
    struct {
        MS_U32 osd0en                      : 1;
        MS_U32                             : 7;
        MS_U32 osd1en                      : 1;
        MS_U32                             : 7;
        MS_U32 osd2en                      : 1;
        MS_U32                             : 15;
    } bitc;
} MH_TD_OSDRGB2YUVCTL_S;

typedef union { /* TD_OsdRGB2YUVCoeff00 */
    MS_U32 all;
    struct {
        MS_U32 c00                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF00_S;

typedef union { /* TD_OsdRGB2YUVCoeff01 */
    MS_U32 all;
    struct {
        MS_U32 c01                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF01_S;

typedef union { /* TD_OsdRGB2YUVCoeff02 */
    MS_U32 all;
    struct {
        MS_U32 c02                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF02_S;

typedef union { /* TD_OsdRGB2YUVCoeff03 */
    MS_U32 all;
    struct {
        MS_U32 c03                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF03_S;

typedef union { /* TD_OsdRGB2YUVCoeff10 */
    MS_U32 all;
    struct {
        MS_U32 c10                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF10_S;

typedef union { /* TD_OsdRGB2YUVCoeff11 */
    MS_U32 all;
    struct {
        MS_U32 c11                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF11_S;

typedef union { /* TD_OsdRGB2YUVCoeff12 */
    MS_U32 all;
    struct {
        MS_U32 c12                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF12_S;

typedef union { /* TD_OsdRGB2YUVCoeff13 */
    MS_U32 all;
    struct {
        MS_U32 c13                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF13_S;

typedef union { /* TD_OsdRGB2YUVCoeff20 */
    MS_U32 all;
    struct {
        MS_U32 c20                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF20_S;

typedef union { /* TD_OsdRGB2YUVCoeff21 */
    MS_U32 all;
    struct {
        MS_U32 c21                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF21_S;

typedef union { /* TD_OsdRGB2YUVCoeff22 */
    MS_U32 all;
    struct {
        MS_U32 c22                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF22_S;

typedef union { /* TD_OsdRGB2YUVCoeff23 */
    MS_U32 all;
    struct {
        MS_U32 c23                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_OSDRGB2YUVCOEFF23_S;

typedef union { /* TD_DispYUV2RGBCtl */
    MS_U32 all;
    struct {
        MS_U32 en                          : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_DISPYUV2RGBCTL_S;

typedef union { /* TD_DispYUV2RGBCoeff00 */
    MS_U32 all;
    struct {
        MS_U32 c00                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF00_S;

typedef union { /* TD_DispYUV2RGBCoeff01 */
    MS_U32 all;
    struct {
        MS_U32 c01                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF01_S;

typedef union { /* TD_DispYUV2RGBCoeff02 */
    MS_U32 all;
    struct {
        MS_U32 c02                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF02_S;

typedef union { /* TD_DispYUV2RGBCoeff03 */
    MS_U32 all;
    struct {
        MS_U32 c03                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF03_S;

typedef union { /* TD_DispYUV2RGBCoeff10 */
    MS_U32 all;
    struct {
        MS_U32 c10                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF10_S;

typedef union { /* TD_DispYUV2RGBCoeff11 */
    MS_U32 all;
    struct {
        MS_U32 c11                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF11_S;

typedef union { /* TD_DispYUV2RGBCoeff12 */
    MS_U32 all;
    struct {
        MS_U32 c12                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF12_S;

typedef union { /* TD_DispYUV2RGBCoeff13 */
    MS_U32 all;
    struct {
        MS_U32 c13                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF13_S;

typedef union { /* TD_DispYUV2RGBCoeff20 */
    MS_U32 all;
    struct {
        MS_U32 c20                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF20_S;

typedef union { /* TD_DispYUV2RGBCoeff21 */
    MS_U32 all;
    struct {
        MS_U32 c21                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF21_S;

typedef union { /* TD_DispYUV2RGBCoeff22 */
    MS_U32 all;
    struct {
        MS_U32 c22                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF22_S;

typedef union { /* TD_DispYUV2RGBCoeff23 */
    MS_U32 all;
    struct {
        MS_U32 c23                         : 12;
        MS_U32                             : 20;
    } bitc;
} MH_TD_DISPYUV2RGBCOEFF23_S;

typedef union { /* TD_DispMixAlp0 */
    MS_U32 all;
    struct {
        MS_U32 layer0glbalp                : 8;
        MS_U32                             : 24;
    } bitc;
} MH_TD_DISPMIXALP0_S;

typedef union { /* TD_DispMixAlp1 */
    MS_U32 all;
    struct {
        MS_U32 layer4glbalp                : 8;
        MS_U32                             : 24;
    } bitc;
} MH_TD_DISPMIXALP1_S;

typedef union { /* TD_DispMixSel */
    MS_U32 all;
    struct {
        MS_U32 layer0sel                   : 3;
        MS_U32                             : 1;
        MS_U32 layer1sel                   : 3;
        MS_U32                             : 25;
    } bitc;
} MH_TD_DISPMIXSEL_S;

typedef union { /* TD_DispBackGroud */
    MS_U32 all;
    struct {
        MS_U32 y                           : 8;
        MS_U32 u                           : 8;
        MS_U32 v                           : 8;
        MS_U32                             : 8;
    } bitc;
} MH_TD_DISPBACKGROUD_S;

typedef union { /* TD_DispIRQ0 */
    MS_U32 all;
    struct {
        MS_U32                             : 20;
        MS_U32 en                          : 1;
        MS_U32                             : 11;
    } bitc;
} MH_TD_DISPIRQ0_S;

typedef union { /* TD_DispIRQ1 */
    MS_U32 all;
    struct {
        MS_U32 underrundcnt                : 20;
        MS_U32 en                          : 1;
        MS_U32                             : 11;
    } bitc;
} MH_TD_DISPIRQ1_S;

typedef union { /* TD_DispIRQ2 */
    MS_U32 all;
    struct {
        MS_U32                             : 20;
        MS_U32 en                          : 1;
        MS_U32                             : 11;
    } bitc;
} MH_TD_DISPIRQ2_S;

typedef union { /* TD_DispIRQ */
    MS_U32 all;
    struct {
        MS_U32 irq0                        : 1;
        MS_U32 irq0ctl                     : 1;
        MS_U32 irq1                        : 1;
        MS_U32                             : 13;
        MS_U32 underrun                    : 8;
        MS_U32                             : 4;
        MS_U32 addrflag                    : 1;
        MS_U32                             : 3;
    } bitc;
} MH_TD_DISPIRQ_S;

typedef union { /* TD_WbDma */
    MS_U32 all;
    struct {
        MS_U32 en                          : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBDMA_S;

typedef union { /* TD_WbMode */
    MS_U32 all;
    struct {
        MS_U32                             : 2;
        MS_U32 input                       : 1;
        MS_U32                             : 29;
    } bitc;
} MH_TD_WBMODE_S;

typedef union { /* TD_WbPixel */
    MS_U32 all;
    struct {
        MS_U32 formatsel                   : 1;
        MS_U32 inputformat                 : 1;
        MS_U32 outputformat                : 1;
        MS_U32 pixelorder422               : 2;
        MS_U32 rgbpixelwidth               : 3;
        MS_U32                             : 24;
    } bitc;
} MH_TD_WBPIXEL_S;

typedef union { /* TD_WbOutY */
    MS_U32 all;
    struct {
        MS_U32 hstride                     : 13;
        MS_U32                             : 19;
    } bitc;
} MH_TD_WBOUTY_S;

typedef union { /* TD_WbOutUV */
    MS_U32 all;
    struct {
        MS_U32 hstride                     : 13;
        MS_U32                             : 19;
    } bitc;
} MH_TD_WBOUTUV_S;

typedef union { /* TD_WbLoop */
    MS_U32 all;
    struct {
        MS_U32 buffersize                  : 16;
        MS_U32                             : 16;
    } bitc;
} MH_TD_WBLOOP_S;

typedef union { /* TD_WbActiveV */
    MS_U32 all;
    struct {
        MS_U32 size                        : 13;
        MS_U32                             : 19;
    } bitc;
} MH_TD_WBACTIVEV_S;

typedef union { /* TD_WbActiveH */
    MS_U32 all;
    struct {
        MS_U32 size                        : 13;
        MS_U32                             : 19;
    } bitc;
} MH_TD_WBACTIVEH_S;

typedef union { /* TD_WbCh1Dma */
    MS_U32 all;
    struct {
        MS_U32 otnum                       : 4;
        MS_U32                             : 8;
        MS_U32 blen                        : 1;
        MS_U32                             : 1;
        MS_U32 continuousmode              : 1;
        MS_U32 swap                        : 1;
        MS_U32                             : 12;
        MS_U32 errdetecten                 : 1;
        MS_U32                             : 3;
    } bitc;
} MH_TD_WBCH1DMA_S;

typedef union { /* TD_WbCh1ErrUnit */
    MS_U32 all;
    struct {
        MS_U32 unit                        : 8;
        MS_U32                             : 24;
    } bitc;
} MH_TD_WBCH1ERRUNIT_S;

typedef union { /* TD_WbCh1ErrTh */
    MS_U32 all;
    struct {
        MS_U32 threshold                   : 8;
        MS_U32                             : 24;
    } bitc;
} MH_TD_WBCH1ERRTH_S;

typedef union { /* TD_WbCh1Info */
    MS_U32 all;
    struct {
        MS_U32 frmcntclear                 : 1;
        MS_U32 fifoerrclear                : 1;
        MS_U32 maxbw                       : 1;
        MS_U32 totalbw                     : 1;
        MS_U32                             : 28;
    } bitc;
} MH_TD_WBCH1INFO_S;

typedef union { /* TD_WbCh1Rst */
    MS_U32 all;
    struct {
        MS_U32 request                     : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBCH1RST_S;

typedef union { /* TD_WbCh2Dma */
    MS_U32 all;
    struct {
        MS_U32 otnum                       : 4;
        MS_U32                             : 8;
        MS_U32 blen                        : 1;
        MS_U32                             : 1;
        MS_U32 continuousmode              : 1;
        MS_U32 swap                        : 1;
        MS_U32                             : 12;
        MS_U32 errdetecten                 : 1;
        MS_U32                             : 3;
    } bitc;
} MH_TD_WBCH2DMA_S;

typedef union { /* TD_WbCh2ErrUnit */
    MS_U32 all;
    struct {
        MS_U32 unit                        : 8;
        MS_U32                             : 24;
    } bitc;
} MH_TD_WBCH2ERRUNIT_S;

typedef union { /* TD_WbCh2ErrTh */
    MS_U32 all;
    struct {
        MS_U32 threshold                   : 8;
        MS_U32                             : 24;
    } bitc;
} MH_TD_WBCH2ERRTH_S;

typedef union { /* TD_WbCh2Info */
    MS_U32 all;
    struct {
        MS_U32 frmcntclear                 : 1;
        MS_U32 fifoerrclear                : 1;
        MS_U32 maxbw                       : 1;
        MS_U32 totalbw                     : 1;
        MS_U32                             : 28;
    } bitc;
} MH_TD_WBCH2INFO_S;

typedef union { /* TD_WbCh2Rst */
    MS_U32 all;
    struct {
        MS_U32 request                     : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBCH2RST_S;

typedef union { /* TD_WbYOutIdle */
    MS_U32 all;
    struct {
        MS_U32 status                      : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBYOUTIDLE_S;

typedef union { /* TD_WbUVOutIdle */
    MS_U32 all;
    struct {
        MS_U32 status                      : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBUVOUTIDLE_S;

typedef union { /* TD_WbYOutInt */
    MS_U32 all;
    struct {
        MS_U32 status                      : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBYOUTINT_S;

typedef union { /* TD_WbUVOutInt */
    MS_U32 all;
    struct {
        MS_U32 status                      : 1;
        MS_U32                             : 31;
    } bitc;
} MH_TD_WBUVOUTINT_S;

typedef union { /* TD_WbYOutFunc0 */
    MS_U32 all;
    struct {
        MS_U32 frmcnt                      : 16;
        MS_U32 buffererrcnt                : 16;
    } bitc;
} MH_TD_WBYOUTFUNC0_S;

typedef union { /* TD_WbYOutFunc1 */
    MS_U32 all;
    struct {
        MS_U32 maxbd                       : 8;
        MS_U32 totalbd                     : 18;
        MS_U32                             : 4;
        MS_U32 frmbasesel                  : 1;
        MS_U32 dmabusy                     : 1;
    } bitc;
} MH_TD_WBYOUTFUNC1_S;

typedef union { /* TD_WbUVOutFunc0 */
    MS_U32 all;
    struct {
        MS_U32 frmcnt                      : 16;
        MS_U32 buffererrcnt                : 16;
    } bitc;
} MH_TD_WBUVOUTFUNC0_S;

typedef union { /* TD_WbUVOutFunc1 */
    MS_U32 all;
    struct {
        MS_U32 maxbd                       : 8;
        MS_U32 totalbd                     : 18;
        MS_U32                             : 4;
        MS_U32 frmbasesel                  : 1;
        MS_U32 dmabusy                     : 1;
    } bitc;
} MH_TD_WBUVOUTFUNC1_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register TD_WrapSwRst (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapSwRst'. */
void MH_TD_set_WrapSwRst(MS_U32 data);
/*! \brief Reads the register 'TD_WrapSwRst'. */
MS_U32  MH_TD_get_WrapSwRst(void);
/*! \brief Writes the bit group 'RotationRW' of register 'TD_WrapSwRst'. */
void MH_TD_set_WrapSwRst_RotationRW(MS_U8 data);
/*! \brief Reads the bit group 'RotationRW' of register 'TD_WrapSwRst'. */
MS_U8   MH_TD_get_WrapSwRst_RotationRW(void);
/*! \brief Writes the bit group 'MixerRW' of register 'TD_WrapSwRst'. */
void MH_TD_set_WrapSwRst_MixerRW(MS_U8 data);
/*! \brief Reads the bit group 'MixerRW' of register 'TD_WrapSwRst'. */
MS_U8   MH_TD_get_WrapSwRst_MixerRW(void);
/*! \brief Writes the bit group 'AXIWr' of register 'TD_WrapSwRst'. */
void MH_TD_set_WrapSwRst_AXIWr(MS_U8 data);
/*! \brief Reads the bit group 'AXIWr' of register 'TD_WrapSwRst'. */
MS_U8   MH_TD_get_WrapSwRst_AXIWr(void);
/*! \brief Writes the bit group 'AXIRd' of register 'TD_WrapSwRst'. */
void MH_TD_set_WrapSwRst_AXIRd(MS_U8 data);
/*! \brief Reads the bit group 'AXIRd' of register 'TD_WrapSwRst'. */
MS_U8   MH_TD_get_WrapSwRst_AXIRd(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapSwRst(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPSWRST = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapSwRst] <-- 0x%08x\n",
                        REG_TD_WRAPSWRST,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapSwRst(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPSWRST);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapSwRst] --> 0x%08x\n",
                        REG_TD_WRAPSWRST,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapSwRst_RotationRW(MS_U8 data)
{
    MH_TD_WRAPSWRST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPSWRST;
    d.bitc.rotationrw = data;
    *(volatile MS_U32 *)REG_TD_WRAPSWRST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapSwRst_RotationRW] <-- 0x%08x\n",
                        REG_TD_WRAPSWRST,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapSwRst_RotationRW(void)
{
    MH_TD_WRAPSWRST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPSWRST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapSwRst_RotationRW] --> 0x%08x\n",
                        REG_TD_WRAPSWRST,value);
    #endif
    return tmp_value.bitc.rotationrw;
}
MH_INLINE void MH_TD_set_WrapSwRst_MixerRW(MS_U8 data)
{
    MH_TD_WRAPSWRST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPSWRST;
    d.bitc.mixerrw = data;
    *(volatile MS_U32 *)REG_TD_WRAPSWRST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapSwRst_MixerRW] <-- 0x%08x\n",
                        REG_TD_WRAPSWRST,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapSwRst_MixerRW(void)
{
    MH_TD_WRAPSWRST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPSWRST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapSwRst_MixerRW] --> 0x%08x\n",
                        REG_TD_WRAPSWRST,value);
    #endif
    return tmp_value.bitc.mixerrw;
}
MH_INLINE void MH_TD_set_WrapSwRst_AXIWr(MS_U8 data)
{
    MH_TD_WRAPSWRST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPSWRST;
    d.bitc.axiwr = data;
    *(volatile MS_U32 *)REG_TD_WRAPSWRST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapSwRst_AXIWr] <-- 0x%08x\n",
                        REG_TD_WRAPSWRST,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapSwRst_AXIWr(void)
{
    MH_TD_WRAPSWRST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPSWRST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapSwRst_AXIWr] --> 0x%08x\n",
                        REG_TD_WRAPSWRST,value);
    #endif
    return tmp_value.bitc.axiwr;
}
MH_INLINE void MH_TD_set_WrapSwRst_AXIRd(MS_U8 data)
{
    MH_TD_WRAPSWRST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPSWRST;
    d.bitc.axird = data;
    *(volatile MS_U32 *)REG_TD_WRAPSWRST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapSwRst_AXIRd] <-- 0x%08x\n",
                        REG_TD_WRAPSWRST,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapSwRst_AXIRd(void)
{
    MH_TD_WRAPSWRST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPSWRST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapSwRst_AXIRd] --> 0x%08x\n",
                        REG_TD_WRAPSWRST,value);
    #endif
    return tmp_value.bitc.axird;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapClkEn (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn(MS_U32 data);
/*! \brief Reads the register 'TD_WrapClkEn'. */
MS_U32  MH_TD_get_WrapClkEn(void);
/*! \brief Writes the bit group 'Ch0Rd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch0Rd(MS_U8 data);
/*! \brief Reads the bit group 'Ch0Rd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch0Rd(void);
/*! \brief Writes the bit group 'Ch1Rd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch1Rd(MS_U8 data);
/*! \brief Reads the bit group 'Ch1Rd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch1Rd(void);
/*! \brief Writes the bit group 'Ch2Rd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch2Rd(MS_U8 data);
/*! \brief Reads the bit group 'Ch2Rd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch2Rd(void);
/*! \brief Writes the bit group 'Ch3Rd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch3Rd(MS_U8 data);
/*! \brief Reads the bit group 'Ch3Rd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch3Rd(void);
/*! \brief Writes the bit group 'Ch4Rd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch4Rd(MS_U8 data);
/*! \brief Reads the bit group 'Ch4Rd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch4Rd(void);
/*! \brief Writes the bit group 'Ch5Rd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch5Rd(MS_U8 data);
/*! \brief Reads the bit group 'Ch5Rd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch5Rd(void);
/*! \brief Writes the bit group 'Ch0Wr' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch0Wr(MS_U8 data);
/*! \brief Reads the bit group 'Ch0Wr' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch0Wr(void);
/*! \brief Writes the bit group 'Ch1Wr' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch1Wr(MS_U8 data);
/*! \brief Reads the bit group 'Ch1Wr' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch1Wr(void);
/*! \brief Writes the bit group 'Ch2Wr' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_Ch2Wr(MS_U8 data);
/*! \brief Reads the bit group 'Ch2Wr' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_Ch2Wr(void);
/*! \brief Writes the bit group 'AXIWr' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_AXIWr(MS_U8 data);
/*! \brief Reads the bit group 'AXIWr' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_AXIWr(void);
/*! \brief Writes the bit group 'AXIRd' of register 'TD_WrapClkEn'. */
void MH_TD_set_WrapClkEn_AXIRd(MS_U8 data);
/*! \brief Reads the bit group 'AXIRd' of register 'TD_WrapClkEn'. */
MS_U8   MH_TD_get_WrapClkEn_AXIRd(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapClkEn(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapClkEn(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch0Rd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch0rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch0Rd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch0Rd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch0Rd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch0rd;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch1Rd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch1rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch1Rd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch1Rd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch1Rd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch1rd;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch2Rd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch2rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch2Rd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch2Rd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch2Rd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch2rd;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch3Rd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch3rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch3Rd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch3Rd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch3Rd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch3rd;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch4Rd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch4rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch4Rd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch4Rd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch4Rd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch4rd;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch5Rd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch5rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch5Rd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch5Rd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch5Rd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch5rd;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch0Wr(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch0wr = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch0Wr] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch0Wr(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch0Wr] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch0wr;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch1Wr(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch1wr = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch1Wr] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch1Wr(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch1Wr] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch1wr;
}
MH_INLINE void MH_TD_set_WrapClkEn_Ch2Wr(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.ch2wr = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_Ch2Wr] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_Ch2Wr(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_Ch2Wr] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.ch2wr;
}
MH_INLINE void MH_TD_set_WrapClkEn_AXIWr(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.axiwr = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_AXIWr] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_AXIWr(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_AXIWr] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.axiwr;
}
MH_INLINE void MH_TD_set_WrapClkEn_AXIRd(MS_U8 data)
{
    MH_TD_WRAPCLKEN_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCLKEN;
    d.bitc.axird = data;
    *(volatile MS_U32 *)REG_TD_WRAPCLKEN = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapClkEn_AXIRd] <-- 0x%08x\n",
                        REG_TD_WRAPCLKEN,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapClkEn_AXIRd(void)
{
    MH_TD_WRAPCLKEN_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCLKEN);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapClkEn_AXIRd] --> 0x%08x\n",
                        REG_TD_WRAPCLKEN,value);
    #endif
    return tmp_value.bitc.axird;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaArbMode (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaArbMode'. */
void MH_TD_set_WrapDmaArbMode(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaArbMode'. */
MS_U32  MH_TD_get_WrapDmaArbMode(void);
/*! \brief Writes the bit group 'Wr' of register 'TD_WrapDmaArbMode'. */
void MH_TD_set_WrapDmaArbMode_Wr(MS_U8 data);
/*! \brief Reads the bit group 'Wr' of register 'TD_WrapDmaArbMode'. */
MS_U8   MH_TD_get_WrapDmaArbMode_Wr(void);
/*! \brief Writes the bit group 'Rd' of register 'TD_WrapDmaArbMode'. */
void MH_TD_set_WrapDmaArbMode_Rd(MS_U8 data);
/*! \brief Reads the bit group 'Rd' of register 'TD_WrapDmaArbMode'. */
MS_U8   MH_TD_get_WrapDmaArbMode_Rd(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaArbMode(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaArbMode] <-- 0x%08x\n",
                        REG_TD_WRAPDMAARBMODE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaArbMode(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaArbMode] --> 0x%08x\n",
                        REG_TD_WRAPDMAARBMODE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaArbMode_Wr(MS_U8 data)
{
    MH_TD_WRAPDMAARBMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE;
    d.bitc.wr = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaArbMode_Wr] <-- 0x%08x\n",
                        REG_TD_WRAPDMAARBMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaArbMode_Wr(void)
{
    MH_TD_WRAPDMAARBMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaArbMode_Wr] --> 0x%08x\n",
                        REG_TD_WRAPDMAARBMODE,value);
    #endif
    return tmp_value.bitc.wr;
}
MH_INLINE void MH_TD_set_WrapDmaArbMode_Rd(MS_U8 data)
{
    MH_TD_WRAPDMAARBMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE;
    d.bitc.rd = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaArbMode_Rd] <-- 0x%08x\n",
                        REG_TD_WRAPDMAARBMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaArbMode_Rd(void)
{
    MH_TD_WRAPDMAARBMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAARBMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaArbMode_Rd] --> 0x%08x\n",
                        REG_TD_WRAPDMAARBMODE,value);
    #endif
    return tmp_value.bitc.rd;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaWeightWR0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaWeightWR0'. */
void MH_TD_set_WrapDmaWeightWR0(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaWeightWR0'. */
MS_U32  MH_TD_get_WrapDmaWeightWR0(void);
/*! \brief Writes the bit group 'Ch0' of register 'TD_WrapDmaWeightWR0'. */
void MH_TD_set_WrapDmaWeightWR0_Ch0(MS_U8 data);
/*! \brief Reads the bit group 'Ch0' of register 'TD_WrapDmaWeightWR0'. */
MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch0(void);
/*! \brief Writes the bit group 'Ch1' of register 'TD_WrapDmaWeightWR0'. */
void MH_TD_set_WrapDmaWeightWR0_Ch1(MS_U8 data);
/*! \brief Reads the bit group 'Ch1' of register 'TD_WrapDmaWeightWR0'. */
MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch1(void);
/*! \brief Writes the bit group 'Ch2' of register 'TD_WrapDmaWeightWR0'. */
void MH_TD_set_WrapDmaWeightWR0_Ch2(MS_U8 data);
/*! \brief Reads the bit group 'Ch2' of register 'TD_WrapDmaWeightWR0'. */
MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch2(void);
/*! \brief Writes the bit group 'Ch3' of register 'TD_WrapDmaWeightWR0'. */
void MH_TD_set_WrapDmaWeightWR0_Ch3(MS_U8 data);
/*! \brief Reads the bit group 'Ch3' of register 'TD_WrapDmaWeightWR0'. */
MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch3(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaWeightWR0(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaWeightWR0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR0] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR0_Ch0(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0;
    d.bitc.ch0 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR0_Ch0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch0(void)
{
    MH_TD_WRAPDMAWEIGHTWR0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR0_Ch0] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,value);
    #endif
    return tmp_value.bitc.ch0;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR0_Ch1(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0;
    d.bitc.ch1 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR0_Ch1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch1(void)
{
    MH_TD_WRAPDMAWEIGHTWR0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR0_Ch1] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,value);
    #endif
    return tmp_value.bitc.ch1;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR0_Ch2(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0;
    d.bitc.ch2 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR0_Ch2] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch2(void)
{
    MH_TD_WRAPDMAWEIGHTWR0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR0_Ch2] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,value);
    #endif
    return tmp_value.bitc.ch2;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR0_Ch3(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0;
    d.bitc.ch3 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR0_Ch3] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR0_Ch3(void)
{
    MH_TD_WRAPDMAWEIGHTWR0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR0_Ch3] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR0,value);
    #endif
    return tmp_value.bitc.ch3;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaWeightWR1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaWeightWR1'. */
void MH_TD_set_WrapDmaWeightWR1(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaWeightWR1'. */
MS_U32  MH_TD_get_WrapDmaWeightWR1(void);
/*! \brief Writes the bit group 'Ch4' of register 'TD_WrapDmaWeightWR1'. */
void MH_TD_set_WrapDmaWeightWR1_Ch4(MS_U8 data);
/*! \brief Reads the bit group 'Ch4' of register 'TD_WrapDmaWeightWR1'. */
MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch4(void);
/*! \brief Writes the bit group 'Ch5' of register 'TD_WrapDmaWeightWR1'. */
void MH_TD_set_WrapDmaWeightWR1_Ch5(MS_U8 data);
/*! \brief Reads the bit group 'Ch5' of register 'TD_WrapDmaWeightWR1'. */
MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch5(void);
/*! \brief Writes the bit group 'Ch6' of register 'TD_WrapDmaWeightWR1'. */
void MH_TD_set_WrapDmaWeightWR1_Ch6(MS_U8 data);
/*! \brief Reads the bit group 'Ch6' of register 'TD_WrapDmaWeightWR1'. */
MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch6(void);
/*! \brief Writes the bit group 'Ch7' of register 'TD_WrapDmaWeightWR1'. */
void MH_TD_set_WrapDmaWeightWR1_Ch7(MS_U8 data);
/*! \brief Reads the bit group 'Ch7' of register 'TD_WrapDmaWeightWR1'. */
MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch7(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaWeightWR1(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaWeightWR1(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR1] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR1_Ch4(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1;
    d.bitc.ch4 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR1_Ch4] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch4(void)
{
    MH_TD_WRAPDMAWEIGHTWR1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR1_Ch4] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,value);
    #endif
    return tmp_value.bitc.ch4;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR1_Ch5(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1;
    d.bitc.ch5 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR1_Ch5] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch5(void)
{
    MH_TD_WRAPDMAWEIGHTWR1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR1_Ch5] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,value);
    #endif
    return tmp_value.bitc.ch5;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR1_Ch6(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1;
    d.bitc.ch6 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR1_Ch6] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch6(void)
{
    MH_TD_WRAPDMAWEIGHTWR1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR1_Ch6] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,value);
    #endif
    return tmp_value.bitc.ch6;
}
MH_INLINE void MH_TD_set_WrapDmaWeightWR1_Ch7(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTWR1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1;
    d.bitc.ch7 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightWR1_Ch7] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightWR1_Ch7(void)
{
    MH_TD_WRAPDMAWEIGHTWR1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTWR1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightWR1_Ch7] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTWR1,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaWeightRD0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaWeightRD0'. */
void MH_TD_set_WrapDmaWeightRD0(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaWeightRD0'. */
MS_U32  MH_TD_get_WrapDmaWeightRD0(void);
/*! \brief Writes the bit group 'Ch0' of register 'TD_WrapDmaWeightRD0'. */
void MH_TD_set_WrapDmaWeightRD0_Ch0(MS_U8 data);
/*! \brief Reads the bit group 'Ch0' of register 'TD_WrapDmaWeightRD0'. */
MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch0(void);
/*! \brief Writes the bit group 'Ch1' of register 'TD_WrapDmaWeightRD0'. */
void MH_TD_set_WrapDmaWeightRD0_Ch1(MS_U8 data);
/*! \brief Reads the bit group 'Ch1' of register 'TD_WrapDmaWeightRD0'. */
MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch1(void);
/*! \brief Writes the bit group 'Ch2' of register 'TD_WrapDmaWeightRD0'. */
void MH_TD_set_WrapDmaWeightRD0_Ch2(MS_U8 data);
/*! \brief Reads the bit group 'Ch2' of register 'TD_WrapDmaWeightRD0'. */
MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch2(void);
/*! \brief Writes the bit group 'Ch3' of register 'TD_WrapDmaWeightRD0'. */
void MH_TD_set_WrapDmaWeightRD0_Ch3(MS_U8 data);
/*! \brief Reads the bit group 'Ch3' of register 'TD_WrapDmaWeightRD0'. */
MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch3(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaWeightRD0(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaWeightRD0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD0] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD0_Ch0(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0;
    d.bitc.ch0 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD0_Ch0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch0(void)
{
    MH_TD_WRAPDMAWEIGHTRD0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD0_Ch0] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,value);
    #endif
    return tmp_value.bitc.ch0;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD0_Ch1(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0;
    d.bitc.ch1 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD0_Ch1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch1(void)
{
    MH_TD_WRAPDMAWEIGHTRD0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD0_Ch1] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,value);
    #endif
    return tmp_value.bitc.ch1;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD0_Ch2(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0;
    d.bitc.ch2 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD0_Ch2] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch2(void)
{
    MH_TD_WRAPDMAWEIGHTRD0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD0_Ch2] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,value);
    #endif
    return tmp_value.bitc.ch2;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD0_Ch3(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0;
    d.bitc.ch3 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD0_Ch3] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD0_Ch3(void)
{
    MH_TD_WRAPDMAWEIGHTRD0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD0_Ch3] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD0,value);
    #endif
    return tmp_value.bitc.ch3;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaWeightRD1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaWeightRD1'. */
void MH_TD_set_WrapDmaWeightRD1(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaWeightRD1'. */
MS_U32  MH_TD_get_WrapDmaWeightRD1(void);
/*! \brief Writes the bit group 'Ch4' of register 'TD_WrapDmaWeightRD1'. */
void MH_TD_set_WrapDmaWeightRD1_Ch4(MS_U8 data);
/*! \brief Reads the bit group 'Ch4' of register 'TD_WrapDmaWeightRD1'. */
MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch4(void);
/*! \brief Writes the bit group 'Ch5' of register 'TD_WrapDmaWeightRD1'. */
void MH_TD_set_WrapDmaWeightRD1_Ch5(MS_U8 data);
/*! \brief Reads the bit group 'Ch5' of register 'TD_WrapDmaWeightRD1'. */
MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch5(void);
/*! \brief Writes the bit group 'Ch6' of register 'TD_WrapDmaWeightRD1'. */
void MH_TD_set_WrapDmaWeightRD1_Ch6(MS_U8 data);
/*! \brief Reads the bit group 'Ch6' of register 'TD_WrapDmaWeightRD1'. */
MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch6(void);
/*! \brief Writes the bit group 'Ch7' of register 'TD_WrapDmaWeightRD1'. */
void MH_TD_set_WrapDmaWeightRD1_Ch7(MS_U8 data);
/*! \brief Reads the bit group 'Ch7' of register 'TD_WrapDmaWeightRD1'. */
MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch7(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaWeightRD1(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaWeightRD1(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD1] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD1_Ch4(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1;
    d.bitc.ch4 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD1_Ch4] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch4(void)
{
    MH_TD_WRAPDMAWEIGHTRD1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD1_Ch4] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,value);
    #endif
    return tmp_value.bitc.ch4;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD1_Ch5(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1;
    d.bitc.ch5 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD1_Ch5] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch5(void)
{
    MH_TD_WRAPDMAWEIGHTRD1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD1_Ch5] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,value);
    #endif
    return tmp_value.bitc.ch5;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD1_Ch6(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1;
    d.bitc.ch6 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD1_Ch6] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch6(void)
{
    MH_TD_WRAPDMAWEIGHTRD1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD1_Ch6] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,value);
    #endif
    return tmp_value.bitc.ch6;
}
MH_INLINE void MH_TD_set_WrapDmaWeightRD1_Ch7(MS_U8 data)
{
    MH_TD_WRAPDMAWEIGHTRD1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1;
    d.bitc.ch7 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaWeightRD1_Ch7] <-- 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaWeightRD1_Ch7(void)
{
    MH_TD_WRAPDMAWEIGHTRD1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAWEIGHTRD1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaWeightRD1_Ch7] --> 0x%08x\n",
                        REG_TD_WRAPDMAWEIGHTRD1,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaPriorityWR (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaPriorityWR'. */
MS_U32  MH_TD_get_WrapDmaPriorityWR(void);
/*! \brief Writes the bit group 'Ch0' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch0(MS_U8 data);
/*! \brief Reads the bit group 'Ch0' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch0(void);
/*! \brief Writes the bit group 'Ch1' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch1(MS_U8 data);
/*! \brief Reads the bit group 'Ch1' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch1(void);
/*! \brief Writes the bit group 'Ch2' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch2(MS_U8 data);
/*! \brief Reads the bit group 'Ch2' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch2(void);
/*! \brief Writes the bit group 'Ch3' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch3(MS_U8 data);
/*! \brief Reads the bit group 'Ch3' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch3(void);
/*! \brief Writes the bit group 'Ch4' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch4(MS_U8 data);
/*! \brief Reads the bit group 'Ch4' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch4(void);
/*! \brief Writes the bit group 'Ch5' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch5(MS_U8 data);
/*! \brief Reads the bit group 'Ch5' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch5(void);
/*! \brief Writes the bit group 'Ch6' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch6(MS_U8 data);
/*! \brief Reads the bit group 'Ch6' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch6(void);
/*! \brief Writes the bit group 'Ch7' of register 'TD_WrapDmaPriorityWR'. */
void MH_TD_set_WrapDmaPriorityWR_Ch7(MS_U8 data);
/*! \brief Reads the bit group 'Ch7' of register 'TD_WrapDmaPriorityWR'. */
MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch7(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaPriorityWR(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaPriorityWR(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch0(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch0 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch0(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch0] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch0;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch1(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch1 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch1(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch1] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch1;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch2(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch2 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch2] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch2(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch2] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch2;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch3(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch3 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch3] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch3(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch3] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch3;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch4(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch4 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch4] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch4(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch4] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch4;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch5(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch5 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch5] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch5(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch5] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch5;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch6(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch6 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch6] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch6(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch6] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch6;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityWR_Ch7(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR;
    d.bitc.ch7 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityWR_Ch7] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityWR_Ch7(void)
{
    MH_TD_WRAPDMAPRIORITYWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityWR_Ch7] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYWR,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaPriorityRD (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaPriorityRD'. */
MS_U32  MH_TD_get_WrapDmaPriorityRD(void);
/*! \brief Writes the bit group 'Ch0' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch0(MS_U8 data);
/*! \brief Reads the bit group 'Ch0' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch0(void);
/*! \brief Writes the bit group 'Ch1' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch1(MS_U8 data);
/*! \brief Reads the bit group 'Ch1' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch1(void);
/*! \brief Writes the bit group 'Ch2' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch2(MS_U8 data);
/*! \brief Reads the bit group 'Ch2' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch2(void);
/*! \brief Writes the bit group 'Ch3' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch3(MS_U8 data);
/*! \brief Reads the bit group 'Ch3' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch3(void);
/*! \brief Writes the bit group 'Ch4' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch4(MS_U8 data);
/*! \brief Reads the bit group 'Ch4' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch4(void);
/*! \brief Writes the bit group 'Ch5' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch5(MS_U8 data);
/*! \brief Reads the bit group 'Ch5' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch5(void);
/*! \brief Writes the bit group 'Ch6' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch6(MS_U8 data);
/*! \brief Reads the bit group 'Ch6' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch6(void);
/*! \brief Writes the bit group 'Ch7' of register 'TD_WrapDmaPriorityRD'. */
void MH_TD_set_WrapDmaPriorityRD_Ch7(MS_U8 data);
/*! \brief Reads the bit group 'Ch7' of register 'TD_WrapDmaPriorityRD'. */
MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch7(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaPriorityRD(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaPriorityRD(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch0(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch0 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch0(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch0] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch0;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch1(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch1 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch1(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch1] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch1;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch2(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch2 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch2] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch2(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch2] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch2;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch3(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch3 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch3] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch3(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch3] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch3;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch4(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch4 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch4] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch4(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch4] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch4;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch5(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch5 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch5] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch5(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch5] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch5;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch6(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch6 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch6] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch6(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch6] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch6;
}
MH_INLINE void MH_TD_set_WrapDmaPriorityRD_Ch7(MS_U8 data)
{
    MH_TD_WRAPDMAPRIORITYRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD;
    d.bitc.ch7 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaPriorityRD_Ch7] <-- 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaPriorityRD_Ch7(void)
{
    MH_TD_WRAPDMAPRIORITYRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAPRIORITYRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaPriorityRD_Ch7] --> 0x%08x\n",
                        REG_TD_WRAPDMAPRIORITYRD,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaIdWR (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaIdWR'. */
MS_U32  MH_TD_get_WrapDmaIdWR(void);
/*! \brief Writes the bit group 'Ch0' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch0(MS_U8 data);
/*! \brief Reads the bit group 'Ch0' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch0(void);
/*! \brief Writes the bit group 'Ch1' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch1(MS_U8 data);
/*! \brief Reads the bit group 'Ch1' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch1(void);
/*! \brief Writes the bit group 'Ch2' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch2(MS_U8 data);
/*! \brief Reads the bit group 'Ch2' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch2(void);
/*! \brief Writes the bit group 'Ch3' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch3(MS_U8 data);
/*! \brief Reads the bit group 'Ch3' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch3(void);
/*! \brief Writes the bit group 'Ch4' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch4(MS_U8 data);
/*! \brief Reads the bit group 'Ch4' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch4(void);
/*! \brief Writes the bit group 'Ch5' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch5(MS_U8 data);
/*! \brief Reads the bit group 'Ch5' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch5(void);
/*! \brief Writes the bit group 'Ch6' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch6(MS_U8 data);
/*! \brief Reads the bit group 'Ch6' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch6(void);
/*! \brief Writes the bit group 'Ch7' of register 'TD_WrapDmaIdWR'. */
void MH_TD_set_WrapDmaIdWR_Ch7(MS_U8 data);
/*! \brief Reads the bit group 'Ch7' of register 'TD_WrapDmaIdWR'. */
MS_U8   MH_TD_get_WrapDmaIdWR_Ch7(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaIdWR(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaIdWR(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch0(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch0 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch0(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch0] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch0;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch1(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch1 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch1(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch1] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch1;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch2(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch2 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch2] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch2(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch2] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch2;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch3(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch3 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch3] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch3(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch3] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch3;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch4(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch4 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch4] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch4(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch4] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch4;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch5(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch5 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch5] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch5(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch5] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch5;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch6(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch6 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch6] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch6(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch6] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch6;
}
MH_INLINE void MH_TD_set_WrapDmaIdWR_Ch7(MS_U8 data)
{
    MH_TD_WRAPDMAIDWR_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR;
    d.bitc.ch7 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDWR = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdWR_Ch7] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdWR_Ch7(void)
{
    MH_TD_WRAPDMAIDWR_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDWR);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdWR_Ch7] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDWR,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapDmaIdRD (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD(MS_U32 data);
/*! \brief Reads the register 'TD_WrapDmaIdRD'. */
MS_U32  MH_TD_get_WrapDmaIdRD(void);
/*! \brief Writes the bit group 'Ch0' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch0(MS_U8 data);
/*! \brief Reads the bit group 'Ch0' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch0(void);
/*! \brief Writes the bit group 'Ch1' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch1(MS_U8 data);
/*! \brief Reads the bit group 'Ch1' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch1(void);
/*! \brief Writes the bit group 'Ch2' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch2(MS_U8 data);
/*! \brief Reads the bit group 'Ch2' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch2(void);
/*! \brief Writes the bit group 'Ch3' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch3(MS_U8 data);
/*! \brief Reads the bit group 'Ch3' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch3(void);
/*! \brief Writes the bit group 'Ch4' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch4(MS_U8 data);
/*! \brief Reads the bit group 'Ch4' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch4(void);
/*! \brief Writes the bit group 'Ch5' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch5(MS_U8 data);
/*! \brief Reads the bit group 'Ch5' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch5(void);
/*! \brief Writes the bit group 'Ch6' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch6(MS_U8 data);
/*! \brief Reads the bit group 'Ch6' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch6(void);
/*! \brief Writes the bit group 'Ch7' of register 'TD_WrapDmaIdRD'. */
void MH_TD_set_WrapDmaIdRD_Ch7(MS_U8 data);
/*! \brief Reads the bit group 'Ch7' of register 'TD_WrapDmaIdRD'. */
MS_U8   MH_TD_get_WrapDmaIdRD_Ch7(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapDmaIdRD(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapDmaIdRD(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch0(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch0 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch0] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch0(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch0] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch0;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch1(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch1 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch1] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch1(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch1] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch1;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch2(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch2 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch2] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch2(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch2] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch2;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch3(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch3 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch3] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch3(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch3] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch3;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch4(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch4 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch4] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch4(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch4] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch4;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch5(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch5 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch5] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch5(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch5] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch5;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch6(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch6 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch6] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch6(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch6] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch6;
}
MH_INLINE void MH_TD_set_WrapDmaIdRD_Ch7(MS_U8 data)
{
    MH_TD_WRAPDMAIDRD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD;
    d.bitc.ch7 = data;
    *(volatile MS_U32 *)REG_TD_WRAPDMAIDRD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapDmaIdRD_Ch7] <-- 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapDmaIdRD_Ch7(void)
{
    MH_TD_WRAPDMAIDRD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPDMAIDRD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapDmaIdRD_Ch7] --> 0x%08x\n",
                        REG_TD_WRAPDMAIDRD,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapCfg (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapCfg'. */
void MH_TD_set_WrapCfg(MS_U32 data);
/*! \brief Reads the register 'TD_WrapCfg'. */
MS_U32  MH_TD_get_WrapCfg(void);
/*! \brief Writes the bit group 'Done' of register 'TD_WrapCfg'. */
void MH_TD_set_WrapCfg_Done(MS_U8 data);
/*! \brief Reads the bit group 'Done' of register 'TD_WrapCfg'. */
MS_U8   MH_TD_get_WrapCfg_Done(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapCfg(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPCFG = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapCfg] <-- 0x%08x\n",
                        REG_TD_WRAPCFG,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapCfg(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCFG);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapCfg] --> 0x%08x\n",
                        REG_TD_WRAPCFG,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapCfg_Done(MS_U8 data)
{
    MH_TD_WRAPCFG_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPCFG;
    d.bitc.done = data;
    *(volatile MS_U32 *)REG_TD_WRAPCFG = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapCfg_Done] <-- 0x%08x\n",
                        REG_TD_WRAPCFG,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapCfg_Done(void)
{
    MH_TD_WRAPCFG_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPCFG);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapCfg_Done] --> 0x%08x\n",
                        REG_TD_WRAPCFG,value);
    #endif
    return tmp_value.bitc.done;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WrapInt (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WrapInt'. */
void MH_TD_set_WrapInt(MS_U32 data);
/*! \brief Reads the register 'TD_WrapInt'. */
MS_U32  MH_TD_get_WrapInt(void);
/*! \brief Writes the bit group 'RotationDone' of register 'TD_WrapInt'. */
void MH_TD_set_WrapInt_RotationDone(MS_U8 data);
/*! \brief Reads the bit group 'RotationDone' of register 'TD_WrapInt'. */
MS_U8   MH_TD_get_WrapInt_RotationDone(void);
/*! \brief Writes the bit group 'RotationTimeOut' of register 'TD_WrapInt'. */
void MH_TD_set_WrapInt_RotationTimeOut(MS_U8 data);
/*! \brief Reads the bit group 'RotationTimeOut' of register 'TD_WrapInt'. */
MS_U8   MH_TD_get_WrapInt_RotationTimeOut(void);
/*! \brief Writes the bit group 'MixerDone' of register 'TD_WrapInt'. */
void MH_TD_set_WrapInt_MixerDone(MS_U8 data);
/*! \brief Reads the bit group 'MixerDone' of register 'TD_WrapInt'. */
MS_U8   MH_TD_get_WrapInt_MixerDone(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WrapInt(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WRAPINT = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapInt] <-- 0x%08x\n",
                        REG_TD_WRAPINT,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WrapInt(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPINT);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapInt] --> 0x%08x\n",
                        REG_TD_WRAPINT,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WrapInt_RotationDone(MS_U8 data)
{
    MH_TD_WRAPINT_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPINT;
    d.bitc.rotationdone = data;
    *(volatile MS_U32 *)REG_TD_WRAPINT = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapInt_RotationDone] <-- 0x%08x\n",
                        REG_TD_WRAPINT,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapInt_RotationDone(void)
{
    MH_TD_WRAPINT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPINT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapInt_RotationDone] --> 0x%08x\n",
                        REG_TD_WRAPINT,value);
    #endif
    return tmp_value.bitc.rotationdone;
}
MH_INLINE void MH_TD_set_WrapInt_RotationTimeOut(MS_U8 data)
{
    MH_TD_WRAPINT_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPINT;
    d.bitc.rotationtimeout = data;
    *(volatile MS_U32 *)REG_TD_WRAPINT = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapInt_RotationTimeOut] <-- 0x%08x\n",
                        REG_TD_WRAPINT,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapInt_RotationTimeOut(void)
{
    MH_TD_WRAPINT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPINT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapInt_RotationTimeOut] --> 0x%08x\n",
                        REG_TD_WRAPINT,value);
    #endif
    return tmp_value.bitc.rotationtimeout;
}
MH_INLINE void MH_TD_set_WrapInt_MixerDone(MS_U8 data)
{
    MH_TD_WRAPINT_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WRAPINT;
    d.bitc.mixerdone = data;
    *(volatile MS_U32 *)REG_TD_WRAPINT = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WrapInt_MixerDone] <-- 0x%08x\n",
                        REG_TD_WRAPINT,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WrapInt_MixerDone(void)
{
    MH_TD_WRAPINT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WRAPINT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WrapInt_MixerDone] --> 0x%08x\n",
                        REG_TD_WRAPINT,value);
    #endif
    return tmp_value.bitc.mixerdone;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotCmd (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotCmd'. */
void MH_TD_set_RotCmd(MS_U32 data);
/*! \brief Reads the register 'TD_RotCmd'. */
MS_U32  MH_TD_get_RotCmd(void);
/*! \brief Writes the bit group 'FrameStart' of register 'TD_RotCmd'. */
void MH_TD_set_RotCmd_FrameStart(MS_U8 data);
/*! \brief Reads the bit group 'FrameStart' of register 'TD_RotCmd'. */
MS_U8   MH_TD_get_RotCmd_FrameStart(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotCmd(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTCMD = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCmd] <-- 0x%08x\n",
                        REG_TD_ROTCMD,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotCmd(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCMD);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCmd] --> 0x%08x\n",
                        REG_TD_ROTCMD,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotCmd_FrameStart(MS_U8 data)
{
    MH_TD_ROTCMD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCMD;
    d.bitc.framestart = data;
    *(volatile MS_U32 *)REG_TD_ROTCMD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCmd_FrameStart] <-- 0x%08x\n",
                        REG_TD_ROTCMD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCmd_FrameStart(void)
{
    MH_TD_ROTCMD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCMD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCmd_FrameStart] --> 0x%08x\n",
                        REG_TD_ROTCMD,value);
    #endif
    return tmp_value.bitc.framestart;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotCtl (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotCtl'. */
void MH_TD_set_RotCtl(MS_U32 data);
/*! \brief Reads the register 'TD_RotCtl'. */
MS_U32  MH_TD_get_RotCtl(void);
/*! \brief Writes the bit group 'Mode' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_Mode(MS_U8 data);
/*! \brief Reads the bit group 'Mode' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_Mode(void);
/*! \brief Writes the bit group 'PixFormat' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_PixFormat(MS_U8 data);
/*! \brief Reads the bit group 'PixFormat' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_PixFormat(void);
/*! \brief Writes the bit group 'Inswap' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_InSwap(MS_U8 data);
/*! \brief Reads the bit group 'Inswap' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_InSwap(void);
/*! \brief Writes the bit group 'endianInEn' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_EndiaInEn(MS_U8 data);
/*! \brief Reads the bit group 'endianInEn' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_EndianInEn(void);



void MH_TD_set_RotCtl_OutSwap(MS_U8 data);
/*! \brief Reads the bit group 'Inswap' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_OutSwap(void);
/*! \brief Writes the bit group 'endianInEn' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_EndiaOutEn(MS_U8 data);
/*! \brief Reads the bit group 'endianInEn' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_EndianOutEn(void);

/*! \brief Writes the bit group 'OtMaxRd' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_OtMaxRd(MS_U8 data);
/*! \brief Reads the bit group 'OtMaxRd' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_OtMaxRd(void);
/*! \brief Writes the bit group 'OtMaxWr' of register 'TD_RotCtl'. */
void MH_TD_set_RotCtl_OtMaxWr(MS_U8 data);
/*! \brief Reads the bit group 'OtMaxWr' of register 'TD_RotCtl'. */
MS_U8   MH_TD_get_RotCtl_OtMaxWr(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl] <-- 0x%08x\n",
                        REG_TD_ROTCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotCtl_Mode(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.mode = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_Mode] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_Mode(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_Mode] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.mode;
}
MH_INLINE void MH_TD_set_RotCtl_PixFormat(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.pixformat = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_PixFormat] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_PixFormat(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_PixFormat] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.pixformat;
}
MH_INLINE void MH_TD_set_RotCtl_InSwap(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.Inswap = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_InSwap] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_InSwap(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_InSwap] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.Inswap;
}
MH_INLINE void MH_TD_set_RotCtl_EndiaInEn(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.endianInEn = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_EndiaInEn] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_EndianInEn(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_EndianInEn] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.endianInEn;
}




MH_INLINE void MH_TD_set_RotCtl_OutSwap(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.Outswap = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_OutSwap] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_InSwap(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_OutSwap] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.Outswap;
}
MH_INLINE void MH_TD_set_RotCtl_EndiaOutEn(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.endianOutEn = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_EndiaOutEn] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_EndianOutEn(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_EndianOutEn] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.endianOutEn;
}




MH_INLINE void MH_TD_set_RotCtl_OtMaxRd(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.otmaxrd = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_OtMaxRd] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_OtMaxRd(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_OtMaxRd] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.otmaxrd;
}
MH_INLINE void MH_TD_set_RotCtl_OtMaxWr(MS_U8 data)
{
    MH_TD_ROTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTCTL;
    d.bitc.otmaxwr = data;
    *(volatile MS_U32 *)REG_TD_ROTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotCtl_OtMaxWr] <-- 0x%08x\n",
                        REG_TD_ROTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_RotCtl_OtMaxWr(void)
{
    MH_TD_ROTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotCtl_OtMaxWr] --> 0x%08x\n",
                        REG_TD_ROTCTL,value);
    #endif
    return tmp_value.bitc.otmaxwr;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotTimeOut (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotTimeOut'. */
void MH_TD_set_RotTimeOut(MS_U32 data);
/*! \brief Reads the register 'TD_RotTimeOut'. */
MS_U32  MH_TD_get_RotTimeOut(void);
/*! \brief Writes the bit group 'Val' of register 'TD_RotTimeOut'. */
void MH_TD_set_RotTimeOut_Val(MS_U16 data);
/*! \brief Reads the bit group 'Val' of register 'TD_RotTimeOut'. */
MS_U16  MH_TD_get_RotTimeOut_Val(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotTimeOut(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTTIMEOUT = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotTimeOut] <-- 0x%08x\n",
                        REG_TD_ROTTIMEOUT,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotTimeOut(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTTIMEOUT);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotTimeOut] --> 0x%08x\n",
                        REG_TD_ROTTIMEOUT,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotTimeOut_Val(MS_U16 data)
{
    MH_TD_ROTTIMEOUT_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTTIMEOUT;
    d.bitc.val = data;
    *(volatile MS_U32 *)REG_TD_ROTTIMEOUT = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotTimeOut_Val] <-- 0x%08x\n",
                        REG_TD_ROTTIMEOUT,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotTimeOut_Val(void)
{
    MH_TD_ROTTIMEOUT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTTIMEOUT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotTimeOut_Val] --> 0x%08x\n",
                        REG_TD_ROTTIMEOUT,value);
    #endif
    return tmp_value.bitc.val;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotImageSizeActive (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotImageSizeActive'. */
void MH_TD_set_RotImageSizeActive(MS_U32 data);
/*! \brief Reads the register 'TD_RotImageSizeActive'. */
MS_U32  MH_TD_get_RotImageSizeActive(void);
/*! \brief Writes the bit group 'Ver' of register 'TD_RotImageSizeActive'. */
void MH_TD_set_RotImageSizeActive_Ver(MS_U16 data);
/*! \brief Reads the bit group 'Ver' of register 'TD_RotImageSizeActive'. */
MS_U16  MH_TD_get_RotImageSizeActive_Ver(void);
/*! \brief Writes the bit group 'Hor' of register 'TD_RotImageSizeActive'. */
void MH_TD_set_RotImageSizeActive_Hor(MS_U16 data);
/*! \brief Reads the bit group 'Hor' of register 'TD_RotImageSizeActive'. */
MS_U16  MH_TD_get_RotImageSizeActive_Hor(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotImageSizeActive(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotImageSizeActive] <-- 0x%08x\n",
                        REG_TD_ROTIMAGESIZEACTIVE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotImageSizeActive(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotImageSizeActive] --> 0x%08x\n",
                        REG_TD_ROTIMAGESIZEACTIVE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotImageSizeActive_Ver(MS_U16 data)
{
    MH_TD_ROTIMAGESIZEACTIVE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE;
    d.bitc.ver = data;
    *(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotImageSizeActive_Ver] <-- 0x%08x\n",
                        REG_TD_ROTIMAGESIZEACTIVE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotImageSizeActive_Ver(void)
{
    MH_TD_ROTIMAGESIZEACTIVE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotImageSizeActive_Ver] --> 0x%08x\n",
                        REG_TD_ROTIMAGESIZEACTIVE,value);
    #endif
    return tmp_value.bitc.ver;
}
MH_INLINE void MH_TD_set_RotImageSizeActive_Hor(MS_U16 data)
{
    MH_TD_ROTIMAGESIZEACTIVE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE;
    d.bitc.hor = data;
    *(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotImageSizeActive_Hor] <-- 0x%08x\n",
                        REG_TD_ROTIMAGESIZEACTIVE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotImageSizeActive_Hor(void)
{
    MH_TD_ROTIMAGESIZEACTIVE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTIMAGESIZEACTIVE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotImageSizeActive_Hor] --> 0x%08x\n",
                        REG_TD_ROTIMAGESIZEACTIVE,value);
    #endif
    return tmp_value.bitc.hor;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotAddrBaseYSrc (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotAddrBaseYSrc'. */
void MH_TD_set_RotAddrBaseYSrc(MS_U32 data);
/*! \brief Reads the register 'TD_RotAddrBaseYSrc'. */
MS_U32  MH_TD_get_RotAddrBaseYSrc(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotAddrBaseYSrc(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTADDRBASEYSRC = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotAddrBaseYSrc] <-- 0x%08x\n",
                        REG_TD_ROTADDRBASEYSRC,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotAddrBaseYSrc(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTADDRBASEYSRC);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotAddrBaseYSrc] --> 0x%08x\n",
                        REG_TD_ROTADDRBASEYSRC,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotAddrBaseUSrc (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotAddrBaseUSrc'. */
void MH_TD_set_RotAddrBaseUSrc(MS_U32 data);
/*! \brief Reads the register 'TD_RotAddrBaseUSrc'. */
MS_U32  MH_TD_get_RotAddrBaseUSrc(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotAddrBaseUSrc(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTADDRBASEUSRC = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotAddrBaseUSrc] <-- 0x%08x\n",
                        REG_TD_ROTADDRBASEUSRC,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotAddrBaseUSrc(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTADDRBASEUSRC);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotAddrBaseUSrc] --> 0x%08x\n",
                        REG_TD_ROTADDRBASEUSRC,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotAddrBaseVSrc (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotAddrBaseVSrc'. */
void MH_TD_set_RotAddrBaseVSrc(MS_U32 data);
/*! \brief Reads the register 'TD_RotAddrBaseVSrc'. */
MS_U32  MH_TD_get_RotAddrBaseVSrc(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotAddrBaseVSrc(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTADDRBASEVSRC = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotAddrBaseVSrc] <-- 0x%08x\n",
                        REG_TD_ROTADDRBASEVSRC,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotAddrBaseVSrc(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTADDRBASEVSRC);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotAddrBaseVSrc] --> 0x%08x\n",
                        REG_TD_ROTADDRBASEVSRC,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotAddrBaseYDes (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotAddrBaseYDes'. */
void MH_TD_set_RotAddrBaseYDes(MS_U32 data);
/*! \brief Reads the register 'TD_RotAddrBaseYDes'. */
MS_U32  MH_TD_get_RotAddrBaseYDes(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotAddrBaseYDes(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTADDRBASEYDES = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotAddrBaseYDes] <-- 0x%08x\n",
                        REG_TD_ROTADDRBASEYDES,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotAddrBaseYDes(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTADDRBASEYDES);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotAddrBaseYDes] --> 0x%08x\n",
                        REG_TD_ROTADDRBASEYDES,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotAddrBaseUDes (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotAddrBaseUDes'. */
void MH_TD_set_RotAddrBaseUDes(MS_U32 data);
/*! \brief Reads the register 'TD_RotAddrBaseUDes'. */
MS_U32  MH_TD_get_RotAddrBaseUDes(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotAddrBaseUDes(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTADDRBASEUDES = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotAddrBaseUDes] <-- 0x%08x\n",
                        REG_TD_ROTADDRBASEUDES,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotAddrBaseUDes(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTADDRBASEUDES);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotAddrBaseUDes] --> 0x%08x\n",
                        REG_TD_ROTADDRBASEUDES,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotAddrBaseVDes (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotAddrBaseVDes'. */
void MH_TD_set_RotAddrBaseVDes(MS_U32 data);
/*! \brief Reads the register 'TD_RotAddrBaseVDes'. */
MS_U32  MH_TD_get_RotAddrBaseVDes(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotAddrBaseVDes(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTADDRBASEVDES = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotAddrBaseVDes] <-- 0x%08x\n",
                        REG_TD_ROTADDRBASEVDES,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotAddrBaseVDes(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTADDRBASEVDES);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotAddrBaseVDes] --> 0x%08x\n",
                        REG_TD_ROTADDRBASEVDES,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotStrideY (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotStrideY'. */
void MH_TD_set_RotStrideY(MS_U32 data);
/*! \brief Reads the register 'TD_RotStrideY'. */
MS_U32  MH_TD_get_RotStrideY(void);
/*! \brief Writes the bit group 'Src' of register 'TD_RotStrideY'. */
void MH_TD_set_RotStrideY_Src(MS_U16 data);
/*! \brief Reads the bit group 'Src' of register 'TD_RotStrideY'. */
MS_U16  MH_TD_get_RotStrideY_Src(void);
/*! \brief Writes the bit group 'Des' of register 'TD_RotStrideY'. */
void MH_TD_set_RotStrideY_Des(MS_U16 data);
/*! \brief Reads the bit group 'Des' of register 'TD_RotStrideY'. */
MS_U16  MH_TD_get_RotStrideY_Des(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotStrideY(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEY = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideY] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEY,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotStrideY(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEY);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideY] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEY,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotStrideY_Src(MS_U16 data)
{
    MH_TD_ROTSTRIDEY_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTSTRIDEY;
    d.bitc.src = data;
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEY = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideY_Src] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEY,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotStrideY_Src(void)
{
    MH_TD_ROTSTRIDEY_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEY);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideY_Src] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEY,value);
    #endif
    return tmp_value.bitc.src;
}
MH_INLINE void MH_TD_set_RotStrideY_Des(MS_U16 data)
{
    MH_TD_ROTSTRIDEY_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTSTRIDEY;
    d.bitc.des = data;
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEY = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideY_Des] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEY,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotStrideY_Des(void)
{
    MH_TD_ROTSTRIDEY_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEY);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideY_Des] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEY,value);
    #endif
    return tmp_value.bitc.des;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotStrideU (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotStrideU'. */
void MH_TD_set_RotStrideU(MS_U32 data);
/*! \brief Reads the register 'TD_RotStrideU'. */
MS_U32  MH_TD_get_RotStrideU(void);
/*! \brief Writes the bit group 'Src' of register 'TD_RotStrideU'. */
void MH_TD_set_RotStrideU_Src(MS_U16 data);
/*! \brief Reads the bit group 'Src' of register 'TD_RotStrideU'. */
MS_U16  MH_TD_get_RotStrideU_Src(void);
/*! \brief Writes the bit group 'Des' of register 'TD_RotStrideU'. */
void MH_TD_set_RotStrideU_Des(MS_U16 data);
/*! \brief Reads the bit group 'Des' of register 'TD_RotStrideU'. */
MS_U16  MH_TD_get_RotStrideU_Des(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotStrideU(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEU = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideU] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEU,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotStrideU(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEU);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideU] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEU,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotStrideU_Src(MS_U16 data)
{
    MH_TD_ROTSTRIDEU_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTSTRIDEU;
    d.bitc.src = data;
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEU = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideU_Src] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEU,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotStrideU_Src(void)
{
    MH_TD_ROTSTRIDEU_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEU);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideU_Src] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEU,value);
    #endif
    return tmp_value.bitc.src;
}
MH_INLINE void MH_TD_set_RotStrideU_Des(MS_U16 data)
{
    MH_TD_ROTSTRIDEU_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTSTRIDEU;
    d.bitc.des = data;
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEU = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideU_Des] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEU,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotStrideU_Des(void)
{
    MH_TD_ROTSTRIDEU_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEU);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideU_Des] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEU,value);
    #endif
    return tmp_value.bitc.des;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotStrideV (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_RotStrideV'. */
void MH_TD_set_RotStrideV(MS_U32 data);
/*! \brief Reads the register 'TD_RotStrideV'. */
MS_U32  MH_TD_get_RotStrideV(void);
/*! \brief Writes the bit group 'Src' of register 'TD_RotStrideV'. */
void MH_TD_set_RotStrideV_Src(MS_U16 data);
/*! \brief Reads the bit group 'Src' of register 'TD_RotStrideV'. */
MS_U16  MH_TD_get_RotStrideV_Src(void);
/*! \brief Writes the bit group 'Des' of register 'TD_RotStrideV'. */
void MH_TD_set_RotStrideV_Des(MS_U16 data);
/*! \brief Reads the bit group 'Des' of register 'TD_RotStrideV'. */
MS_U16  MH_TD_get_RotStrideV_Des(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_RotStrideV(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEV = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideV] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEV,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_RotStrideV(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEV);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideV] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEV,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_RotStrideV_Src(MS_U16 data)
{
    MH_TD_ROTSTRIDEV_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTSTRIDEV;
    d.bitc.src = data;
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEV = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideV_Src] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEV,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotStrideV_Src(void)
{
    MH_TD_ROTSTRIDEV_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEV);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideV_Src] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEV,value);
    #endif
    return tmp_value.bitc.src;
}
MH_INLINE void MH_TD_set_RotStrideV_Des(MS_U16 data)
{
    MH_TD_ROTSTRIDEV_S d;
    d.all = *(volatile MS_U32 *)REG_TD_ROTSTRIDEV;
    d.bitc.des = data;
    *(volatile MS_U32 *)REG_TD_ROTSTRIDEV = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_RotStrideV_Des] <-- 0x%08x\n",
                        REG_TD_ROTSTRIDEV,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_RotStrideV_Des(void)
{
    MH_TD_ROTSTRIDEV_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTSTRIDEV);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotStrideV_Des] --> 0x%08x\n",
                        REG_TD_ROTSTRIDEV,value);
    #endif
    return tmp_value.bitc.des;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_RotSt (read)                                                   */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_RotSt'. */
MS_U32  MH_TD_get_RotSt(void);
/*! \brief Reads the bit group 'FrameEnd' of register 'TD_RotSt'. */
MS_U8   MH_TD_get_RotSt_FrameEnd(void);
/*! \brief Reads the bit group 'Done' of register 'TD_RotSt'. */
MS_U8   MH_TD_get_RotSt_Done(void);
/*! \brief Reads the bit group 'DmaRd' of register 'TD_RotSt'. */
MS_U8   MH_TD_get_RotSt_DmaRd(void);
/*! \brief Reads the bit group 'DmaWr' of register 'TD_RotSt'. */
MS_U8   MH_TD_get_RotSt_DmaWr(void);
/*! \brief Reads the bit group 'CycleCnt' of register 'TD_RotSt'. */
MS_U16  MH_TD_get_RotSt_CycleCnt(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_RotSt(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTST);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotSt] --> 0x%08x\n",
                        REG_TD_ROTST,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_RotSt_FrameEnd(void)
{
    MH_TD_ROTST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotSt_FrameEnd] --> 0x%08x\n",
                        REG_TD_ROTST,value);
    #endif
    return tmp_value.bitc.frameend;
}
MH_INLINE MS_U8   MH_TD_get_RotSt_Done(void)
{
    MH_TD_ROTST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotSt_Done] --> 0x%08x\n",
                        REG_TD_ROTST,value);
    #endif
    return tmp_value.bitc.done;
}
MH_INLINE MS_U8   MH_TD_get_RotSt_DmaRd(void)
{
    MH_TD_ROTST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotSt_DmaRd] --> 0x%08x\n",
                        REG_TD_ROTST,value);
    #endif
    return tmp_value.bitc.dmard;
}
MH_INLINE MS_U8   MH_TD_get_RotSt_DmaWr(void)
{
    MH_TD_ROTST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotSt_DmaWr] --> 0x%08x\n",
                        REG_TD_ROTST,value);
    #endif
    return tmp_value.bitc.dmawr;
}
MH_INLINE MS_U16  MH_TD_get_RotSt_CycleCnt(void)
{
    MH_TD_ROTST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_ROTST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_RotSt_CycleCnt] --> 0x%08x\n",
                        REG_TD_ROTST,value);
    #endif
    return tmp_value.bitc.cyclecnt;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_SoftRstCtl (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_SoftRstCtl'. */
void MH_TD_set_SoftRstCtl(MS_U32 data);
/*! \brief Reads the register 'TD_SoftRstCtl'. */
MS_U32  MH_TD_get_SoftRstCtl(void);
/*! \brief Writes the bit group 'Mix' of register 'TD_SoftRstCtl'. */
void MH_TD_set_SoftRstCtl_Mix(MS_U8 data);
/*! \brief Reads the bit group 'Mix' of register 'TD_SoftRstCtl'. */
MS_U8   MH_TD_get_SoftRstCtl_Mix(void);
/*! \brief Writes the bit group 'Axi' of register 'TD_SoftRstCtl'. */
void MH_TD_set_SoftRstCtl_Axi(MS_U8 data);
/*! \brief Reads the bit group 'Axi' of register 'TD_SoftRstCtl'. */
MS_U8   MH_TD_get_SoftRstCtl_Axi(void);
/*! \brief Writes the bit group 'Apb' of register 'TD_SoftRstCtl'. */
void MH_TD_set_SoftRstCtl_Apb(MS_U8 data);
/*! \brief Reads the bit group 'Apb' of register 'TD_SoftRstCtl'. */
MS_U8   MH_TD_get_SoftRstCtl_Apb(void);
/*! \brief Writes the bit group 'Core' of register 'TD_SoftRstCtl'. */
void MH_TD_set_SoftRstCtl_Core(MS_U8 data);
/*! \brief Reads the bit group 'Core' of register 'TD_SoftRstCtl'. */
MS_U8   MH_TD_get_SoftRstCtl_Core(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_SoftRstCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_SOFTRSTCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_SoftRstCtl] <-- 0x%08x\n",
                        REG_TD_SOFTRSTCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_SoftRstCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_SOFTRSTCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_SoftRstCtl] --> 0x%08x\n",
                        REG_TD_SOFTRSTCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_SoftRstCtl_Mix(MS_U8 data)
{
    MH_TD_SOFTRSTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_SOFTRSTCTL;
    d.bitc.mix = data;
    *(volatile MS_U32 *)REG_TD_SOFTRSTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_SoftRstCtl_Mix] <-- 0x%08x\n",
                        REG_TD_SOFTRSTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_SoftRstCtl_Mix(void)
{
    MH_TD_SOFTRSTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_SOFTRSTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_SoftRstCtl_Mix] --> 0x%08x\n",
                        REG_TD_SOFTRSTCTL,value);
    #endif
    return tmp_value.bitc.mix;
}
MH_INLINE void MH_TD_set_SoftRstCtl_Axi(MS_U8 data)
{
    MH_TD_SOFTRSTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_SOFTRSTCTL;
    d.bitc.axi = data;
    *(volatile MS_U32 *)REG_TD_SOFTRSTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_SoftRstCtl_Axi] <-- 0x%08x\n",
                        REG_TD_SOFTRSTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_SoftRstCtl_Axi(void)
{
    MH_TD_SOFTRSTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_SOFTRSTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_SoftRstCtl_Axi] --> 0x%08x\n",
                        REG_TD_SOFTRSTCTL,value);
    #endif
    return tmp_value.bitc.axi;
}
MH_INLINE void MH_TD_set_SoftRstCtl_Apb(MS_U8 data)
{
    MH_TD_SOFTRSTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_SOFTRSTCTL;
    d.bitc.apb = data;
    *(volatile MS_U32 *)REG_TD_SOFTRSTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_SoftRstCtl_Apb] <-- 0x%08x\n",
                        REG_TD_SOFTRSTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_SoftRstCtl_Apb(void)
{
    MH_TD_SOFTRSTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_SOFTRSTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_SoftRstCtl_Apb] --> 0x%08x\n",
                        REG_TD_SOFTRSTCTL,value);
    #endif
    return tmp_value.bitc.apb;
}
MH_INLINE void MH_TD_set_SoftRstCtl_Core(MS_U8 data)
{
    MH_TD_SOFTRSTCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_SOFTRSTCTL;
    d.bitc.core = data;
    *(volatile MS_U32 *)REG_TD_SOFTRSTCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_SoftRstCtl_Core] <-- 0x%08x\n",
                        REG_TD_SOFTRSTCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_SoftRstCtl_Core(void)
{
    MH_TD_SOFTRSTCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_SOFTRSTCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_SoftRstCtl_Core] --> 0x%08x\n",
                        REG_TD_SOFTRSTCTL,value);
    #endif
    return tmp_value.bitc.core;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DmaSwCtl (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DmaSwCtl'. */
void MH_TD_set_DmaSwCtl(MS_U32 data);
/*! \brief Reads the register 'TD_DmaSwCtl'. */
MS_U32  MH_TD_get_DmaSwCtl(void);
/*! \brief Writes the bit group 'ReqWr' of register 'TD_DmaSwCtl'. */
void MH_TD_set_DmaSwCtl_ReqWr(MS_U8 data);
/*! \brief Reads the bit group 'ReqWr' of register 'TD_DmaSwCtl'. */
MS_U8   MH_TD_get_DmaSwCtl_ReqWr(void);
/*! \brief Writes the bit group 'ReqRd' of register 'TD_DmaSwCtl'. */
void MH_TD_set_DmaSwCtl_ReqRd(MS_U8 data);
/*! \brief Reads the bit group 'ReqRd' of register 'TD_DmaSwCtl'. */
MS_U8   MH_TD_get_DmaSwCtl_ReqRd(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DmaSwCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DMASWCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DmaSwCtl] <-- 0x%08x\n",
                        REG_TD_DMASWCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DmaSwCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DMASWCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DmaSwCtl] --> 0x%08x\n",
                        REG_TD_DMASWCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DmaSwCtl_ReqWr(MS_U8 data)
{
    MH_TD_DMASWCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DMASWCTL;
    d.bitc.reqwr = data;
    *(volatile MS_U32 *)REG_TD_DMASWCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DmaSwCtl_ReqWr] <-- 0x%08x\n",
                        REG_TD_DMASWCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DmaSwCtl_ReqWr(void)
{
    MH_TD_DMASWCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DMASWCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DmaSwCtl_ReqWr] --> 0x%08x\n",
                        REG_TD_DMASWCTL,value);
    #endif
    return tmp_value.bitc.reqwr;
}
MH_INLINE void MH_TD_set_DmaSwCtl_ReqRd(MS_U8 data)
{
    MH_TD_DMASWCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DMASWCTL;
    d.bitc.reqrd = data;
    *(volatile MS_U32 *)REG_TD_DMASWCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DmaSwCtl_ReqRd] <-- 0x%08x\n",
                        REG_TD_DMASWCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DmaSwCtl_ReqRd(void)
{
    MH_TD_DMASWCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DMASWCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DmaSwCtl_ReqRd] --> 0x%08x\n",
                        REG_TD_DMASWCTL,value);
    #endif
    return tmp_value.bitc.reqrd;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Line0BdCtl (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Line0BdCtl'. */
void MH_TD_set_Layer0Line0BdCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Line0BdCtl'. */
MS_U32  MH_TD_get_Layer0Line0BdCtl(void);
/*! \brief Writes the bit group 'LimitEn' of register 'TD_Layer0Line0BdCtl'. */
void MH_TD_set_Layer0Line0BdCtl_LimitEn(MS_U8 data);
/*! \brief Reads the bit group 'LimitEn' of register 'TD_Layer0Line0BdCtl'. */
MS_U8   MH_TD_get_Layer0Line0BdCtl_LimitEn(void);
/*! \brief Writes the bit group 'OutStand' of register 'TD_Layer0Line0BdCtl'. */
void MH_TD_set_Layer0Line0BdCtl_OutStand(MS_U8 data);
/*! \brief Reads the bit group 'OutStand' of register 'TD_Layer0Line0BdCtl'. */
MS_U8   MH_TD_get_Layer0Line0BdCtl_OutStand(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Line0BdCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line0BdCtl] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE0BDCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Line0BdCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line0BdCtl] --> 0x%08x\n",
                        REG_TD_LAYER0LINE0BDCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0Line0BdCtl_LimitEn(MS_U8 data)
{
    MH_TD_LAYER0LINE0BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL;
    d.bitc.limiten = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line0BdCtl_LimitEn] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE0BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line0BdCtl_LimitEn(void)
{
    MH_TD_LAYER0LINE0BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line0BdCtl_LimitEn] --> 0x%08x\n",
                        REG_TD_LAYER0LINE0BDCTL,value);
    #endif
    return tmp_value.bitc.limiten;
}
MH_INLINE void MH_TD_set_Layer0Line0BdCtl_OutStand(MS_U8 data)
{
    MH_TD_LAYER0LINE0BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL;
    d.bitc.outstand = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line0BdCtl_OutStand] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE0BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line0BdCtl_OutStand(void)
{
    MH_TD_LAYER0LINE0BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE0BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line0BdCtl_OutStand] --> 0x%08x\n",
                        REG_TD_LAYER0LINE0BDCTL,value);
    #endif
    return tmp_value.bitc.outstand;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Line1BdCtl (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Line1BdCtl'. */
void MH_TD_set_Layer0Line1BdCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Line1BdCtl'. */
MS_U32  MH_TD_get_Layer0Line1BdCtl(void);
/*! \brief Writes the bit group 'LimitEn' of register 'TD_Layer0Line1BdCtl'. */
void MH_TD_set_Layer0Line1BdCtl_LimitEn(MS_U8 data);
/*! \brief Reads the bit group 'LimitEn' of register 'TD_Layer0Line1BdCtl'. */
MS_U8   MH_TD_get_Layer0Line1BdCtl_LimitEn(void);
/*! \brief Writes the bit group 'OutStand' of register 'TD_Layer0Line1BdCtl'. */
void MH_TD_set_Layer0Line1BdCtl_OutStand(MS_U8 data);
/*! \brief Reads the bit group 'OutStand' of register 'TD_Layer0Line1BdCtl'. */
MS_U8   MH_TD_get_Layer0Line1BdCtl_OutStand(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Line1BdCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line1BdCtl] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE1BDCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Line1BdCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line1BdCtl] --> 0x%08x\n",
                        REG_TD_LAYER0LINE1BDCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0Line1BdCtl_LimitEn(MS_U8 data)
{
    MH_TD_LAYER0LINE1BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL;
    d.bitc.limiten = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line1BdCtl_LimitEn] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE1BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line1BdCtl_LimitEn(void)
{
    MH_TD_LAYER0LINE1BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line1BdCtl_LimitEn] --> 0x%08x\n",
                        REG_TD_LAYER0LINE1BDCTL,value);
    #endif
    return tmp_value.bitc.limiten;
}
MH_INLINE void MH_TD_set_Layer0Line1BdCtl_OutStand(MS_U8 data)
{
    MH_TD_LAYER0LINE1BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL;
    d.bitc.outstand = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line1BdCtl_OutStand] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE1BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line1BdCtl_OutStand(void)
{
    MH_TD_LAYER0LINE1BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE1BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line1BdCtl_OutStand] --> 0x%08x\n",
                        REG_TD_LAYER0LINE1BDCTL,value);
    #endif
    return tmp_value.bitc.outstand;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Line2BdCtl (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Line2BdCtl'. */
void MH_TD_set_Layer0Line2BdCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Line2BdCtl'. */
MS_U32  MH_TD_get_Layer0Line2BdCtl(void);
/*! \brief Writes the bit group 'LimitEn' of register 'TD_Layer0Line2BdCtl'. */
void MH_TD_set_Layer0Line2BdCtl_LimitEn(MS_U8 data);
/*! \brief Reads the bit group 'LimitEn' of register 'TD_Layer0Line2BdCtl'. */
MS_U8   MH_TD_get_Layer0Line2BdCtl_LimitEn(void);
/*! \brief Writes the bit group 'OutStand' of register 'TD_Layer0Line2BdCtl'. */
void MH_TD_set_Layer0Line2BdCtl_OutStand(MS_U8 data);
/*! \brief Reads the bit group 'OutStand' of register 'TD_Layer0Line2BdCtl'. */
MS_U8   MH_TD_get_Layer0Line2BdCtl_OutStand(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Line2BdCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line2BdCtl] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE2BDCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Line2BdCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line2BdCtl] --> 0x%08x\n",
                        REG_TD_LAYER0LINE2BDCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0Line2BdCtl_LimitEn(MS_U8 data)
{
    MH_TD_LAYER0LINE2BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL;
    d.bitc.limiten = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line2BdCtl_LimitEn] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE2BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line2BdCtl_LimitEn(void)
{
    MH_TD_LAYER0LINE2BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line2BdCtl_LimitEn] --> 0x%08x\n",
                        REG_TD_LAYER0LINE2BDCTL,value);
    #endif
    return tmp_value.bitc.limiten;
}
MH_INLINE void MH_TD_set_Layer0Line2BdCtl_OutStand(MS_U8 data)
{
    MH_TD_LAYER0LINE2BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL;
    d.bitc.outstand = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line2BdCtl_OutStand] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE2BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line2BdCtl_OutStand(void)
{
    MH_TD_LAYER0LINE2BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE2BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line2BdCtl_OutStand] --> 0x%08x\n",
                        REG_TD_LAYER0LINE2BDCTL,value);
    #endif
    return tmp_value.bitc.outstand;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Line3BdCtl (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Line3BdCtl'. */
void MH_TD_set_Layer0Line3BdCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Line3BdCtl'. */
MS_U32  MH_TD_get_Layer0Line3BdCtl(void);
/*! \brief Writes the bit group 'LimitEn' of register 'TD_Layer0Line3BdCtl'. */
void MH_TD_set_Layer0Line3BdCtl_LimitEn(MS_U8 data);
/*! \brief Reads the bit group 'LimitEn' of register 'TD_Layer0Line3BdCtl'. */
MS_U8   MH_TD_get_Layer0Line3BdCtl_LimitEn(void);
/*! \brief Writes the bit group 'OutStand' of register 'TD_Layer0Line3BdCtl'. */
void MH_TD_set_Layer0Line3BdCtl_OutStand(MS_U8 data);
/*! \brief Reads the bit group 'OutStand' of register 'TD_Layer0Line3BdCtl'. */
MS_U8   MH_TD_get_Layer0Line3BdCtl_OutStand(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Line3BdCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line3BdCtl] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE3BDCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Line3BdCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line3BdCtl] --> 0x%08x\n",
                        REG_TD_LAYER0LINE3BDCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0Line3BdCtl_LimitEn(MS_U8 data)
{
    MH_TD_LAYER0LINE3BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL;
    d.bitc.limiten = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line3BdCtl_LimitEn] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE3BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line3BdCtl_LimitEn(void)
{
    MH_TD_LAYER0LINE3BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line3BdCtl_LimitEn] --> 0x%08x\n",
                        REG_TD_LAYER0LINE3BDCTL,value);
    #endif
    return tmp_value.bitc.limiten;
}
MH_INLINE void MH_TD_set_Layer0Line3BdCtl_OutStand(MS_U8 data)
{
    MH_TD_LAYER0LINE3BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL;
    d.bitc.outstand = data;
    *(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Line3BdCtl_OutStand] <-- 0x%08x\n",
                        REG_TD_LAYER0LINE3BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Line3BdCtl_OutStand(void)
{
    MH_TD_LAYER0LINE3BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0LINE3BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Line3BdCtl_OutStand] --> 0x%08x\n",
                        REG_TD_LAYER0LINE3BDCTL,value);
    #endif
    return tmp_value.bitc.outstand;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer4BdCtl (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer4BdCtl'. */
void MH_TD_set_Layer4BdCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer4BdCtl'. */
MS_U32  MH_TD_get_Layer4BdCtl(void);
/*! \brief Writes the bit group 'LimitEn' of register 'TD_Layer4BdCtl'. */
void MH_TD_set_Layer4BdCtl_LimitEn(MS_U8 data);
/*! \brief Reads the bit group 'LimitEn' of register 'TD_Layer4BdCtl'. */
MS_U8   MH_TD_get_Layer4BdCtl_LimitEn(void);
/*! \brief Writes the bit group 'OutStand' of register 'TD_Layer4BdCtl'. */
void MH_TD_set_Layer4BdCtl_OutStand(MS_U8 data);
/*! \brief Reads the bit group 'OutStand' of register 'TD_Layer4BdCtl'. */
MS_U8   MH_TD_get_Layer4BdCtl_OutStand(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer4BdCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER4BDCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4BdCtl] <-- 0x%08x\n",
                        REG_TD_LAYER4BDCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer4BdCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4BDCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4BdCtl] --> 0x%08x\n",
                        REG_TD_LAYER4BDCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer4BdCtl_LimitEn(MS_U8 data)
{
    MH_TD_LAYER4BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER4BDCTL;
    d.bitc.limiten = data;
    *(volatile MS_U32 *)REG_TD_LAYER4BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4BdCtl_LimitEn] <-- 0x%08x\n",
                        REG_TD_LAYER4BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer4BdCtl_LimitEn(void)
{
    MH_TD_LAYER4BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4BdCtl_LimitEn] --> 0x%08x\n",
                        REG_TD_LAYER4BDCTL,value);
    #endif
    return tmp_value.bitc.limiten;
}
MH_INLINE void MH_TD_set_Layer4BdCtl_OutStand(MS_U8 data)
{
    MH_TD_LAYER4BDCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER4BDCTL;
    d.bitc.outstand = data;
    *(volatile MS_U32 *)REG_TD_LAYER4BDCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4BdCtl_OutStand] <-- 0x%08x\n",
                        REG_TD_LAYER4BDCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer4BdCtl_OutStand(void)
{
    MH_TD_LAYER4BDCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4BDCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4BdCtl_OutStand] --> 0x%08x\n",
                        REG_TD_LAYER4BDCTL,value);
    #endif
    return tmp_value.bitc.outstand;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispXZone (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispXZone'. */
void MH_TD_set_DispXZone(MS_U32 data);
/*! \brief Reads the register 'TD_DispXZone'. */
MS_U32  MH_TD_get_DispXZone(void);
/*! \brief Writes the bit group 'Start' of register 'TD_DispXZone'. */
void MH_TD_set_DispXZone_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_DispXZone'. */
MS_U16  MH_TD_get_DispXZone_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_DispXZone'. */
void MH_TD_set_DispXZone_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_DispXZone'. */
MS_U16  MH_TD_get_DispXZone_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispXZone(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPXZONE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispXZone] <-- 0x%08x\n",
                        REG_TD_DISPXZONE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispXZone(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPXZONE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispXZone] --> 0x%08x\n",
                        REG_TD_DISPXZONE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispXZone_Start(MS_U16 data)
{
    MH_TD_DISPXZONE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPXZONE;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_DISPXZONE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispXZone_Start] <-- 0x%08x\n",
                        REG_TD_DISPXZONE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispXZone_Start(void)
{
    MH_TD_DISPXZONE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPXZONE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispXZone_Start] --> 0x%08x\n",
                        REG_TD_DISPXZONE,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_DispXZone_Stop(MS_U16 data)
{
    MH_TD_DISPXZONE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPXZONE;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_DISPXZONE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispXZone_Stop] <-- 0x%08x\n",
                        REG_TD_DISPXZONE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispXZone_Stop(void)
{
    MH_TD_DISPXZONE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPXZONE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispXZone_Stop] --> 0x%08x\n",
                        REG_TD_DISPXZONE,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYZone (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYZone'. */
void MH_TD_set_DispYZone(MS_U32 data);
/*! \brief Reads the register 'TD_DispYZone'. */
MS_U32  MH_TD_get_DispYZone(void);
/*! \brief Writes the bit group 'Start' of register 'TD_DispYZone'. */
void MH_TD_set_DispYZone_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_DispYZone'. */
MS_U16  MH_TD_get_DispYZone_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_DispYZone'. */
void MH_TD_set_DispYZone_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_DispYZone'. */
MS_U16  MH_TD_get_DispYZone_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYZone(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYZONE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYZone] <-- 0x%08x\n",
                        REG_TD_DISPYZONE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYZone(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYZONE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYZone] --> 0x%08x\n",
                        REG_TD_DISPYZONE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYZone_Start(MS_U16 data)
{
    MH_TD_DISPYZONE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYZONE;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_DISPYZONE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYZone_Start] <-- 0x%08x\n",
                        REG_TD_DISPYZONE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYZone_Start(void)
{
    MH_TD_DISPYZONE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYZONE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYZone_Start] --> 0x%08x\n",
                        REG_TD_DISPYZONE,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_DispYZone_Stop(MS_U16 data)
{
    MH_TD_DISPYZONE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYZONE;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_DISPYZONE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYZone_Stop] <-- 0x%08x\n",
                        REG_TD_DISPYZONE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYZone_Stop(void)
{
    MH_TD_DISPYZONE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYZONE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYZone_Stop] --> 0x%08x\n",
                        REG_TD_DISPYZONE,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0XCtl (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0XCtl'. */
void MH_TD_set_Layer0XCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0XCtl'. */
MS_U32  MH_TD_get_Layer0XCtl(void);
/*! \brief Writes the bit group 'Start' of register 'TD_Layer0XCtl'. */
void MH_TD_set_Layer0XCtl_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_Layer0XCtl'. */
MS_U16  MH_TD_get_Layer0XCtl_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_Layer0XCtl'. */
void MH_TD_set_Layer0XCtl_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_Layer0XCtl'. */
MS_U16  MH_TD_get_Layer0XCtl_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0XCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0XCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0XCtl] <-- 0x%08x\n",
                        REG_TD_LAYER0XCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0XCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0XCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0XCtl] --> 0x%08x\n",
                        REG_TD_LAYER0XCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0XCtl_Start(MS_U16 data)
{
    MH_TD_LAYER0XCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0XCTL;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_LAYER0XCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0XCtl_Start] <-- 0x%08x\n",
                        REG_TD_LAYER0XCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0XCtl_Start(void)
{
    MH_TD_LAYER0XCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0XCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0XCtl_Start] --> 0x%08x\n",
                        REG_TD_LAYER0XCTL,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_Layer0XCtl_Stop(MS_U16 data)
{
    MH_TD_LAYER0XCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0XCTL;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_LAYER0XCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0XCtl_Stop] <-- 0x%08x\n",
                        REG_TD_LAYER0XCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0XCtl_Stop(void)
{
    MH_TD_LAYER0XCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0XCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0XCtl_Stop] --> 0x%08x\n",
                        REG_TD_LAYER0XCTL,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0YCtl (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0YCtl'. */
void MH_TD_set_Layer0YCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0YCtl'. */
MS_U32  MH_TD_get_Layer0YCtl(void);
/*! \brief Writes the bit group 'Start' of register 'TD_Layer0YCtl'. */
void MH_TD_set_Layer0YCtl_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_Layer0YCtl'. */
MS_U16  MH_TD_get_Layer0YCtl_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_Layer0YCtl'. */
void MH_TD_set_Layer0YCtl_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_Layer0YCtl'. */
MS_U16  MH_TD_get_Layer0YCtl_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0YCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0YCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0YCtl] <-- 0x%08x\n",
                        REG_TD_LAYER0YCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0YCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0YCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0YCtl] --> 0x%08x\n",
                        REG_TD_LAYER0YCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0YCtl_Start(MS_U16 data)
{
    MH_TD_LAYER0YCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0YCTL;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_LAYER0YCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0YCtl_Start] <-- 0x%08x\n",
                        REG_TD_LAYER0YCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0YCtl_Start(void)
{
    MH_TD_LAYER0YCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0YCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0YCtl_Start] --> 0x%08x\n",
                        REG_TD_LAYER0YCTL,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_Layer0YCtl_Stop(MS_U16 data)
{
    MH_TD_LAYER0YCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0YCTL;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_LAYER0YCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0YCtl_Stop] <-- 0x%08x\n",
                        REG_TD_LAYER0YCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0YCtl_Stop(void)
{
    MH_TD_LAYER0YCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0YCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0YCtl_Stop] --> 0x%08x\n",
                        REG_TD_LAYER0YCTL,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer4XCtl (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer4XCtl'. */
void MH_TD_set_Layer4XCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer4XCtl'. */
MS_U32  MH_TD_get_Layer4XCtl(void);
/*! \brief Writes the bit group 'Start' of register 'TD_Layer4XCtl'. */
void MH_TD_set_Layer4XCtl_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_Layer4XCtl'. */
MS_U16  MH_TD_get_Layer4XCtl_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_Layer4XCtl'. */
void MH_TD_set_Layer4XCtl_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_Layer4XCtl'. */
MS_U16  MH_TD_get_Layer4XCtl_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer4XCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER4XCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4XCtl] <-- 0x%08x\n",
                        REG_TD_LAYER4XCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer4XCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4XCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4XCtl] --> 0x%08x\n",
                        REG_TD_LAYER4XCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer4XCtl_Start(MS_U16 data)
{
    MH_TD_LAYER4XCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER4XCTL;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_LAYER4XCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4XCtl_Start] <-- 0x%08x\n",
                        REG_TD_LAYER4XCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer4XCtl_Start(void)
{
    MH_TD_LAYER4XCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4XCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4XCtl_Start] --> 0x%08x\n",
                        REG_TD_LAYER4XCTL,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_Layer4XCtl_Stop(MS_U16 data)
{
    MH_TD_LAYER4XCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER4XCTL;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_LAYER4XCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4XCtl_Stop] <-- 0x%08x\n",
                        REG_TD_LAYER4XCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer4XCtl_Stop(void)
{
    MH_TD_LAYER4XCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4XCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4XCtl_Stop] --> 0x%08x\n",
                        REG_TD_LAYER4XCTL,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer4YCtl (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer4YCtl'. */
void MH_TD_set_Layer4YCtl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer4YCtl'. */
MS_U32  MH_TD_get_Layer4YCtl(void);
/*! \brief Writes the bit group 'Start' of register 'TD_Layer4YCtl'. */
void MH_TD_set_Layer4YCtl_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_Layer4YCtl'. */
MS_U16  MH_TD_get_Layer4YCtl_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_Layer4YCtl'. */
void MH_TD_set_Layer4YCtl_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_Layer4YCtl'. */
MS_U16  MH_TD_get_Layer4YCtl_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer4YCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER4YCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4YCtl] <-- 0x%08x\n",
                        REG_TD_LAYER4YCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer4YCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4YCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4YCtl] --> 0x%08x\n",
                        REG_TD_LAYER4YCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer4YCtl_Start(MS_U16 data)
{
    MH_TD_LAYER4YCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER4YCTL;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_LAYER4YCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4YCtl_Start] <-- 0x%08x\n",
                        REG_TD_LAYER4YCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer4YCtl_Start(void)
{
    MH_TD_LAYER4YCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4YCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4YCtl_Start] --> 0x%08x\n",
                        REG_TD_LAYER4YCTL,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_Layer4YCtl_Stop(MS_U16 data)
{
    MH_TD_LAYER4YCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER4YCTL;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_LAYER4YCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer4YCtl_Stop] <-- 0x%08x\n",
                        REG_TD_LAYER4YCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer4YCtl_Stop(void)
{
    MH_TD_LAYER4YCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER4YCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer4YCtl_Stop] --> 0x%08x\n",
                        REG_TD_LAYER4YCTL,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispHsyncCtl (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispHsyncCtl'. */
void MH_TD_set_DispHsyncCtl(MS_U32 data);
/*! \brief Reads the register 'TD_DispHsyncCtl'. */
MS_U32  MH_TD_get_DispHsyncCtl(void);
/*! \brief Writes the bit group 'Start' of register 'TD_DispHsyncCtl'. */
void MH_TD_set_DispHsyncCtl_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_DispHsyncCtl'. */
MS_U16  MH_TD_get_DispHsyncCtl_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_DispHsyncCtl'. */
void MH_TD_set_DispHsyncCtl_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_DispHsyncCtl'. */
MS_U16  MH_TD_get_DispHsyncCtl_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispHsyncCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPHSYNCCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispHsyncCtl] <-- 0x%08x\n",
                        REG_TD_DISPHSYNCCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispHsyncCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPHSYNCCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispHsyncCtl] --> 0x%08x\n",
                        REG_TD_DISPHSYNCCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispHsyncCtl_Start(MS_U16 data)
{
    MH_TD_DISPHSYNCCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPHSYNCCTL;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_DISPHSYNCCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispHsyncCtl_Start] <-- 0x%08x\n",
                        REG_TD_DISPHSYNCCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispHsyncCtl_Start(void)
{
    MH_TD_DISPHSYNCCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPHSYNCCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispHsyncCtl_Start] --> 0x%08x\n",
                        REG_TD_DISPHSYNCCTL,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_DispHsyncCtl_Stop(MS_U16 data)
{
    MH_TD_DISPHSYNCCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPHSYNCCTL;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_DISPHSYNCCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispHsyncCtl_Stop] <-- 0x%08x\n",
                        REG_TD_DISPHSYNCCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispHsyncCtl_Stop(void)
{
    MH_TD_DISPHSYNCCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPHSYNCCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispHsyncCtl_Stop] --> 0x%08x\n",
                        REG_TD_DISPHSYNCCTL,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispVsyncCtl (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispVsyncCtl'. */
void MH_TD_set_DispVsyncCtl(MS_U32 data);
/*! \brief Reads the register 'TD_DispVsyncCtl'. */
MS_U32  MH_TD_get_DispVsyncCtl(void);
/*! \brief Writes the bit group 'Start' of register 'TD_DispVsyncCtl'. */
void MH_TD_set_DispVsyncCtl_Start(MS_U16 data);
/*! \brief Reads the bit group 'Start' of register 'TD_DispVsyncCtl'. */
MS_U16  MH_TD_get_DispVsyncCtl_Start(void);
/*! \brief Writes the bit group 'Stop' of register 'TD_DispVsyncCtl'. */
void MH_TD_set_DispVsyncCtl_Stop(MS_U16 data);
/*! \brief Reads the bit group 'Stop' of register 'TD_DispVsyncCtl'. */
MS_U16  MH_TD_get_DispVsyncCtl_Stop(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispVsyncCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPVSYNCCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispVsyncCtl] <-- 0x%08x\n",
                        REG_TD_DISPVSYNCCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispVsyncCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPVSYNCCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispVsyncCtl] --> 0x%08x\n",
                        REG_TD_DISPVSYNCCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispVsyncCtl_Start(MS_U16 data)
{
    MH_TD_DISPVSYNCCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPVSYNCCTL;
    d.bitc.start = data;
    *(volatile MS_U32 *)REG_TD_DISPVSYNCCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispVsyncCtl_Start] <-- 0x%08x\n",
                        REG_TD_DISPVSYNCCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispVsyncCtl_Start(void)
{
    MH_TD_DISPVSYNCCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPVSYNCCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispVsyncCtl_Start] --> 0x%08x\n",
                        REG_TD_DISPVSYNCCTL,value);
    #endif
    return tmp_value.bitc.start;
}
MH_INLINE void MH_TD_set_DispVsyncCtl_Stop(MS_U16 data)
{
    MH_TD_DISPVSYNCCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPVSYNCCTL;
    d.bitc.stop = data;
    *(volatile MS_U32 *)REG_TD_DISPVSYNCCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispVsyncCtl_Stop] <-- 0x%08x\n",
                        REG_TD_DISPVSYNCCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispVsyncCtl_Stop(void)
{
    MH_TD_DISPVSYNCCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPVSYNCCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispVsyncCtl_Stop] --> 0x%08x\n",
                        REG_TD_DISPVSYNCCTL,value);
    #endif
    return tmp_value.bitc.stop;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispCtl (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispCtl'. */
void MH_TD_set_DispCtl(MS_U32 data);
/*! \brief Reads the register 'TD_DispCtl'. */
MS_U32  MH_TD_get_DispCtl(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispCtl] <-- 0x%08x\n",
                        REG_TD_DISPCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispCtl] --> 0x%08x\n",
                        REG_TD_DISPCTL,value);
    #endif
    return value;
}

#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispEnable (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispEnable'. */
void MH_TD_set_DispEnable(MS_U32 data);
/*! \brief Reads the register 'TD_DispEnable'. */
MS_U32  MH_TD_get_DispEnable(void);
/*! \brief Writes the bit group 'Layer0En' of register 'TD_DispEnable'. */
void MH_TD_set_DispEnable_Layer0En(MS_U8 data);
/*! \brief Reads the bit group 'Layer0En' of register 'TD_DispEnable'. */
MS_U8   MH_TD_get_DispEnable_Layer0En(void);



void MH_TD_set_DispEnable_Layer0Enhs(MS_U8 data);

MS_U8   MH_TD_get_DispEnable_Layer0Enhs(void);

void MH_TD_set_DispEnable_Layer0WEnhs(MS_U8 data);
MS_U8   MH_TD_get_DispEnable_Layer0WEnhs(void);

/*! \brief Writes the bit group 'Layer4En' of register 'TD_DispEnable'. */
void    MH_TD_set_DispEnable_Layer4En(MS_U8 data);
/*! \brief Reads the bit group 'Layer4En' of register 'TD_DispEnable'. */
MS_U8   MH_TD_get_DispEnable_Layer4En(void);


void    MH_TD_set_DispEnable_Layer4Enhs(MS_U8 data);

MS_U8   MH_TD_get_DispEnable_Layer4Enhs(void);


void MH_TD_set_DispEnable_Layer4WEnhs(MS_U8 data);

MS_U8   MH_TD_get_DispEnable_Layer4WEnhs(void);


/*! \brief Writes the bit group 'FrameStart' of register 'TD_DispEnable'. */
void MH_TD_set_DispEnable_FrameStart(MS_U8 data);
/*! \brief Reads the bit group 'FrameStart' of register 'TD_DispEnable'. */
MS_U8   MH_TD_get_DispEnable_FrameStart(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispEnable(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPENABLE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispEnable(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispEnable_Layer0En(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.layer0en = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_Layer0En] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispEnable_Layer0En(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_Layer0En] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.layer0en;
}


MH_INLINE void MH_TD_set_DispEnable_Layer0Enhs(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.layer0enhs = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_layer0enhs] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispEnable_Layer0Enhs(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_layer0enhs] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.layer0enhs;
}

MH_INLINE void MH_TD_set_DispEnable_Layer0WEnhs(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.layer0Wenhs = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_Layer0WEnhs] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispEnable_Layer0WEnhs(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_layer0enhs] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.layer0Wenhs;
}


MH_INLINE void MH_TD_set_DispEnable_Layer4En(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.layer4en = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_Layer4En] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispEnable_Layer4En(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_Layer4En] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.layer4en;
}

MH_INLINE void MH_TD_set_DispEnable_Layer4Enhs(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.layer4enhs = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_Layer4Enhs] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE  MS_U8   MH_TD_get_DispEnable_Layer4Enhs(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_Layer4En] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.layer4enhs;
}
MH_INLINE void MH_TD_set_DispEnable_Layer4WEnhs(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.layer4Wenhs = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_Layer4WEnhs] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispEnable_Layer4WEnhs(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_Layer4WEn] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.layer4Wenhs;
}

MH_INLINE void MH_TD_set_DispEnable_FrameStart(MS_U8 data)
{
    MH_TD_DISPENABLE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPENABLE;
    d.bitc.framestart = data;
    *(volatile MS_U32 *)REG_TD_DISPENABLE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispEnable_FrameStart] <-- 0x%08x\n",
                        REG_TD_DISPENABLE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispEnable_FrameStart(void)
{
    MH_TD_DISPENABLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPENABLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispEnable_FrameStart] --> 0x%08x\n",
                        REG_TD_DISPENABLE,value);
    #endif
    return tmp_value.bitc.framestart;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispSize (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispSize'. */
void MH_TD_set_DispSize(MS_U32 data);
/*! \brief Reads the register 'TD_DispSize'. */
MS_U32  MH_TD_get_DispSize(void);
/*! \brief Writes the bit group 'Hsize' of register 'TD_DispSize'. */
void MH_TD_set_DispSize_Hsize(MS_U16 data);
/*! \brief Reads the bit group 'Hsize' of register 'TD_DispSize'. */
MS_U16  MH_TD_get_DispSize_Hsize(void);
/*! \brief Writes the bit group 'Vsize' of register 'TD_DispSize'. */
void MH_TD_set_DispSize_Vsize(MS_U16 data);
/*! \brief Reads the bit group 'Vsize' of register 'TD_DispSize'. */
MS_U16  MH_TD_get_DispSize_Vsize(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispSize(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPSIZE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispSize] <-- 0x%08x\n",
                        REG_TD_DISPSIZE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispSize(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPSIZE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispSize] --> 0x%08x\n",
                        REG_TD_DISPSIZE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispSize_Hsize(MS_U16 data)
{
    MH_TD_DISPSIZE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPSIZE;
    d.bitc.hsize = data;
    *(volatile MS_U32 *)REG_TD_DISPSIZE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispSize_Hsize] <-- 0x%08x\n",
                        REG_TD_DISPSIZE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispSize_Hsize(void)
{
    MH_TD_DISPSIZE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPSIZE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispSize_Hsize] --> 0x%08x\n",
                        REG_TD_DISPSIZE,value);
    #endif
    return tmp_value.bitc.hsize;
}
MH_INLINE void MH_TD_set_DispSize_Vsize(MS_U16 data)
{
    MH_TD_DISPSIZE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPSIZE;
    d.bitc.vsize = data;
    *(volatile MS_U32 *)REG_TD_DISPSIZE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispSize_Vsize] <-- 0x%08x\n",
                        REG_TD_DISPSIZE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispSize_Vsize(void)
{
    MH_TD_DISPSIZE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPSIZE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispSize_Vsize] --> 0x%08x\n",
                        REG_TD_DISPSIZE,value);
    #endif
    return tmp_value.bitc.vsize;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Ctl (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Ctl'. */
void MH_TD_set_Layer0Ctl(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Ctl'. */
MS_U32  MH_TD_get_Layer0Ctl(void);
/*! \brief Writes the bit group 'Enable' of register 'TD_Layer0Ctl'. */
void MH_TD_set_Layer0Ctl_Enable(MS_U8 data);
/*! \brief Reads the bit group 'Enable' of register 'TD_Layer0Ctl'. */
MS_U8   MH_TD_get_Layer0Ctl_Enable(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Ctl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0CTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Ctl] <-- 0x%08x\n",
                        REG_TD_LAYER0CTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Ctl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0CTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Ctl] --> 0x%08x\n",
                        REG_TD_LAYER0CTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0Ctl_Enable(MS_U8 data)
{
    MH_TD_LAYER0CTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0CTL;
    d.bitc.enable = data;
    *(volatile MS_U32 *)REG_TD_LAYER0CTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Ctl_Enable] <-- 0x%08x\n",
                        REG_TD_LAYER0CTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0Ctl_Enable(void)
{
    MH_TD_LAYER0CTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0CTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Ctl_Enable] --> 0x%08x\n",
                        REG_TD_LAYER0CTL,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0ScaleBlenth (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0ScaleBlenth'. */
void MH_TD_set_Layer0ScaleBlenth(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0ScaleBlenth'. */
MS_U32  MH_TD_get_Layer0ScaleBlenth(void);
/*! \brief Writes the bit group 'Blen' of register 'TD_Layer0ScaleBlenth'. */
void MH_TD_set_Layer0ScaleBlenth_Blen(MS_U8 data);
/*! \brief Reads the bit group 'Blen' of register 'TD_Layer0ScaleBlenth'. */
MS_U8   MH_TD_get_Layer0ScaleBlenth_Blen(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0ScaleBlenth(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0SCALEBLENTH = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ScaleBlenth] <-- 0x%08x\n",
                        REG_TD_LAYER0SCALEBLENTH,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0ScaleBlenth(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0SCALEBLENTH);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ScaleBlenth] --> 0x%08x\n",
                        REG_TD_LAYER0SCALEBLENTH,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0ScaleBlenth_Blen(MS_U8 data)
{
    MH_TD_LAYER0SCALEBLENTH_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0SCALEBLENTH;
    d.bitc.blen = data;
    *(volatile MS_U32 *)REG_TD_LAYER0SCALEBLENTH = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ScaleBlenth_Blen] <-- 0x%08x\n",
                        REG_TD_LAYER0SCALEBLENTH,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0ScaleBlenth_Blen(void)
{
    MH_TD_LAYER0SCALEBLENTH_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0SCALEBLENTH);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ScaleBlenth_Blen] --> 0x%08x\n",
                        REG_TD_LAYER0SCALEBLENTH,value);
    #endif
    return tmp_value.bitc.blen;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0ImgInDatMode (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0ImgInDatMode'. */
void MH_TD_set_Layer0ImgInDatMode(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0ImgInDatMode'. */
MS_U32  MH_TD_get_Layer0ImgInDatMode(void);
/*! \brief Writes the bit group 'DatMode' of register 'TD_Layer0ImgInDatMode'. */
void MH_TD_set_Layer0ImgInDatMode_DatMode(MS_U8 data);
/*! \brief Reads the bit group 'DatMode' of register 'TD_Layer0ImgInDatMode'. */
MS_U8   MH_TD_get_Layer0ImgInDatMode_DatMode(void);
/*! \brief Writes the bit group 'EndianY' of register 'TD_Layer0ImgInDatMode'. */
void MH_TD_set_Layer0ImgInDatMode_EndianY(MS_U8 data);
/*! \brief Reads the bit group 'EndianY' of register 'TD_Layer0ImgInDatMode'. */
MS_U8   MH_TD_get_Layer0ImgInDatMode_EndianY(void);
/*! \brief Writes the bit group 'EndianUv' of register 'TD_Layer0ImgInDatMode'. */
void MH_TD_set_Layer0ImgInDatMode_EndianUv(MS_U8 data);
/*! \brief Reads the bit group 'EndianUv' of register 'TD_Layer0ImgInDatMode'. */
MS_U8   MH_TD_get_Layer0ImgInDatMode_EndianUv(void);
/*! \brief Writes the bit group 'SwapUv' of register 'TD_Layer0ImgInDatMode'. */
void MH_TD_set_Layer0ImgInDatMode_SwapUv(MS_U8 data);
/*! \brief Reads the bit group 'SwapUv' of register 'TD_Layer0ImgInDatMode'. */
MS_U8   MH_TD_get_Layer0ImgInDatMode_SwapUv(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0ImgInDatMode(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInDatMode] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0ImgInDatMode(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInDatMode] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0ImgInDatMode_DatMode(MS_U8 data)
{
    MH_TD_LAYER0IMGINDATMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE;
    d.bitc.datmode = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInDatMode_DatMode] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0ImgInDatMode_DatMode(void)
{
    MH_TD_LAYER0IMGINDATMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInDatMode_DatMode] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,value);
    #endif
    return tmp_value.bitc.datmode;
}
MH_INLINE void MH_TD_set_Layer0ImgInDatMode_EndianY(MS_U8 data)
{
    MH_TD_LAYER0IMGINDATMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE;
    d.bitc.endiany = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInDatMode_EndianY] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0ImgInDatMode_EndianY(void)
{
    MH_TD_LAYER0IMGINDATMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInDatMode_EndianY] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,value);
    #endif
    return tmp_value.bitc.endiany;
}
MH_INLINE void MH_TD_set_Layer0ImgInDatMode_EndianUv(MS_U8 data)
{
    MH_TD_LAYER0IMGINDATMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE;
    d.bitc.endianuv = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInDatMode_EndianUv] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0ImgInDatMode_EndianUv(void)
{
    MH_TD_LAYER0IMGINDATMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInDatMode_EndianUv] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,value);
    #endif
    return tmp_value.bitc.endianuv;
}
MH_INLINE void MH_TD_set_Layer0ImgInDatMode_SwapUv(MS_U8 data)
{
    MH_TD_LAYER0IMGINDATMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE;
    d.bitc.swapuv = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInDatMode_SwapUv] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0ImgInDatMode_SwapUv(void)
{
    MH_TD_LAYER0IMGINDATMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINDATMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInDatMode_SwapUv] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINDATMODE,value);
    #endif
    return tmp_value.bitc.swapuv;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Baddr0Y (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Baddr0Y'. */
void MH_TD_set_Layer0Baddr0Y(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Baddr0Y'. */
MS_U32  MH_TD_get_Layer0Baddr0Y(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Baddr0Y(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0BADDR0Y = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Baddr0Y] <-- 0x%08x\n",
                        REG_TD_LAYER0BADDR0Y,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Baddr0Y(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BADDR0Y);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Baddr0Y] --> 0x%08x\n",
                        REG_TD_LAYER0BADDR0Y,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0Baddr0UV (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0Baddr0UV'. */
void MH_TD_set_Layer0Baddr0UV(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0Baddr0UV'. */
MS_U32  MH_TD_get_Layer0Baddr0UV(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0Baddr0UV(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0BADDR0UV = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0Baddr0UV] <-- 0x%08x\n",
                        REG_TD_LAYER0BADDR0UV,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0Baddr0UV(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BADDR0UV);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0Baddr0UV] --> 0x%08x\n",
                        REG_TD_LAYER0BADDR0UV,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0ImgInPixSzie (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0ImgInPixSzie'. */
void MH_TD_set_Layer0ImgInPixSzie(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0ImgInPixSzie'. */
MS_U32  MH_TD_get_Layer0ImgInPixSzie(void);
/*! \brief Writes the bit group 'Hsize' of register 'TD_Layer0ImgInPixSzie'. */
void MH_TD_set_Layer0ImgInPixSzie_Hsize(MS_U16 data);
/*! \brief Reads the bit group 'Hsize' of register 'TD_Layer0ImgInPixSzie'. */
MS_U16  MH_TD_get_Layer0ImgInPixSzie_Hsize(void);
/*! \brief Writes the bit group 'Vsize' of register 'TD_Layer0ImgInPixSzie'. */
void MH_TD_set_Layer0ImgInPixSzie_Vsize(MS_U16 data);
/*! \brief Reads the bit group 'Vsize' of register 'TD_Layer0ImgInPixSzie'. */
MS_U16  MH_TD_get_Layer0ImgInPixSzie_Vsize(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0ImgInPixSzie(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInPixSzie] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINPIXSZIE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0ImgInPixSzie(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInPixSzie] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINPIXSZIE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0ImgInPixSzie_Hsize(MS_U16 data)
{
    MH_TD_LAYER0IMGINPIXSZIE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE;
    d.bitc.hsize = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInPixSzie_Hsize] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINPIXSZIE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgInPixSzie_Hsize(void)
{
    MH_TD_LAYER0IMGINPIXSZIE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInPixSzie_Hsize] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINPIXSZIE,value);
    #endif
    return tmp_value.bitc.hsize;
}
MH_INLINE void MH_TD_set_Layer0ImgInPixSzie_Vsize(MS_U16 data)
{
    MH_TD_LAYER0IMGINPIXSZIE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE;
    d.bitc.vsize = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInPixSzie_Vsize] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINPIXSZIE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgInPixSzie_Vsize(void)
{
    MH_TD_LAYER0IMGINPIXSZIE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINPIXSZIE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInPixSzie_Vsize] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINPIXSZIE,value);
    #endif
    return tmp_value.bitc.vsize;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0ImgOutPixSzie (read/write)                               */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0ImgOutPixSzie'. */
void MH_TD_set_Layer0ImgOutPixSzie(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0ImgOutPixSzie'. */
MS_U32  MH_TD_get_Layer0ImgOutPixSzie(void);
/*! \brief Writes the bit group 'Hsize' of register 'TD_Layer0ImgOutPixSzie'. */
void MH_TD_set_Layer0ImgOutPixSzie_Hsize(MS_U16 data);
/*! \brief Reads the bit group 'Hsize' of register 'TD_Layer0ImgOutPixSzie'. */
MS_U16  MH_TD_get_Layer0ImgOutPixSzie_Hsize(void);
/*! \brief Writes the bit group 'Vsize' of register 'TD_Layer0ImgOutPixSzie'. */
void MH_TD_set_Layer0ImgOutPixSzie_Vsize(MS_U16 data);
/*! \brief Reads the bit group 'Vsize' of register 'TD_Layer0ImgOutPixSzie'. */
MS_U16  MH_TD_get_Layer0ImgOutPixSzie_Vsize(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0ImgOutPixSzie(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgOutPixSzie] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGOUTPIXSZIE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0ImgOutPixSzie(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgOutPixSzie] --> 0x%08x\n",
                        REG_TD_LAYER0IMGOUTPIXSZIE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0ImgOutPixSzie_Hsize(MS_U16 data)
{
    MH_TD_LAYER0IMGOUTPIXSZIE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE;
    d.bitc.hsize = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgOutPixSzie_Hsize] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGOUTPIXSZIE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgOutPixSzie_Hsize(void)
{
    MH_TD_LAYER0IMGOUTPIXSZIE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgOutPixSzie_Hsize] --> 0x%08x\n",
                        REG_TD_LAYER0IMGOUTPIXSZIE,value);
    #endif
    return tmp_value.bitc.hsize;
}
MH_INLINE void MH_TD_set_Layer0ImgOutPixSzie_Vsize(MS_U16 data)
{
    MH_TD_LAYER0IMGOUTPIXSZIE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE;
    d.bitc.vsize = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgOutPixSzie_Vsize] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGOUTPIXSZIE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgOutPixSzie_Vsize(void)
{
    MH_TD_LAYER0IMGOUTPIXSZIE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGOUTPIXSZIE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgOutPixSzie_Vsize] --> 0x%08x\n",
                        REG_TD_LAYER0IMGOUTPIXSZIE,value);
    #endif
    return tmp_value.bitc.vsize;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0ImgInStride (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0ImgInStride'. */
void MH_TD_set_Layer0ImgInStride(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0ImgInStride'. */
MS_U32  MH_TD_get_Layer0ImgInStride(void);
/*! \brief Writes the bit group 'Hsize' of register 'TD_Layer0ImgInStride'. */
void MH_TD_set_Layer0ImgInStride_Hsize(MS_U16 data);
/*! \brief Reads the bit group 'Hsize' of register 'TD_Layer0ImgInStride'. */
MS_U16  MH_TD_get_Layer0ImgInStride_Hsize(void);
/*! \brief Writes the bit group 'Vsize' of register 'TD_Layer0ImgInStride'. */
void MH_TD_set_Layer0ImgInStride_Vsize(MS_U16 data);
/*! \brief Reads the bit group 'Vsize' of register 'TD_Layer0ImgInStride'. */
MS_U16  MH_TD_get_Layer0ImgInStride_Vsize(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0ImgInStride(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInStride] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINSTRIDE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0ImgInStride(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInStride] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINSTRIDE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0ImgInStride_Hsize(MS_U16 data)
{
    MH_TD_LAYER0IMGINSTRIDE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE;
    d.bitc.hsize = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInStride_Hsize] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINSTRIDE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgInStride_Hsize(void)
{
    MH_TD_LAYER0IMGINSTRIDE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInStride_Hsize] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINSTRIDE,value);
    #endif
    return tmp_value.bitc.hsize;
}
MH_INLINE void MH_TD_set_Layer0ImgInStride_Vsize(MS_U16 data)
{
    MH_TD_LAYER0IMGINSTRIDE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE;
    d.bitc.vsize = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInStride_Vsize] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINSTRIDE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgInStride_Vsize(void)
{
    MH_TD_LAYER0IMGINSTRIDE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINSTRIDE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInStride_Vsize] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINSTRIDE,value);
    #endif
    return tmp_value.bitc.vsize;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0ImgInOffset (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0ImgInOffset'. */
void MH_TD_set_Layer0ImgInOffset(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0ImgInOffset'. */
MS_U32  MH_TD_get_Layer0ImgInOffset(void);
/*! \brief Writes the bit group 'Hoffset' of register 'TD_Layer0ImgInOffset'. */
void MH_TD_set_Layer0ImgInOffset_Hoffset(MS_U16 data);
/*! \brief Reads the bit group 'Hoffset' of register 'TD_Layer0ImgInOffset'. */
MS_U16  MH_TD_get_Layer0ImgInOffset_Hoffset(void);
/*! \brief Writes the bit group 'Voffset' of register 'TD_Layer0ImgInOffset'. */
void MH_TD_set_Layer0ImgInOffset_Voffset(MS_U16 data);
/*! \brief Reads the bit group 'Voffset' of register 'TD_Layer0ImgInOffset'. */
MS_U16  MH_TD_get_Layer0ImgInOffset_Voffset(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0ImgInOffset(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInOffset] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINOFFSET,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0ImgInOffset(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInOffset] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINOFFSET,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0ImgInOffset_Hoffset(MS_U16 data)
{
    MH_TD_LAYER0IMGINOFFSET_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET;
    d.bitc.hoffset = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInOffset_Hoffset] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINOFFSET,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgInOffset_Hoffset(void)
{
    MH_TD_LAYER0IMGINOFFSET_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInOffset_Hoffset] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINOFFSET,value);
    #endif
    return tmp_value.bitc.hoffset;
}
MH_INLINE void MH_TD_set_Layer0ImgInOffset_Voffset(MS_U16 data)
{
    MH_TD_LAYER0IMGINOFFSET_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET;
    d.bitc.voffset = data;
    *(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0ImgInOffset_Voffset] <-- 0x%08x\n",
                        REG_TD_LAYER0IMGINOFFSET,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0ImgInOffset_Voffset(void)
{
    MH_TD_LAYER0IMGINOFFSET_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0IMGINOFFSET);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0ImgInOffset_Voffset] --> 0x%08x\n",
                        REG_TD_LAYER0IMGINOFFSET,value);
    #endif
    return tmp_value.bitc.voffset;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0VscaleStep (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0VscaleStep'. */
void MH_TD_set_Layer0VscaleStep(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0VscaleStep'. */
MS_U32  MH_TD_get_Layer0VscaleStep(void);
/*! \brief Writes the bit group 'Pstep' of register 'TD_Layer0VscaleStep'. */
void MH_TD_set_Layer0VscaleStep_Pstep(MS_U8 data);
/*! \brief Reads the bit group 'Pstep' of register 'TD_Layer0VscaleStep'. */
MS_U8   MH_TD_get_Layer0VscaleStep_Pstep(void);
/*! \brief Writes the bit group 'Dstep' of register 'TD_Layer0VscaleStep'. */
void MH_TD_set_Layer0VscaleStep_Dstep(MS_U16 data);
/*! \brief Reads the bit group 'Dstep' of register 'TD_Layer0VscaleStep'. */
MS_U16  MH_TD_get_Layer0VscaleStep_Dstep(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0VscaleStep(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0VscaleStep] <-- 0x%08x\n",
                        REG_TD_LAYER0VSCALESTEP,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0VscaleStep(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0VscaleStep] --> 0x%08x\n",
                        REG_TD_LAYER0VSCALESTEP,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0VscaleStep_Pstep(MS_U8 data)
{
    MH_TD_LAYER0VSCALESTEP_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP;
    d.bitc.pstep = data;
    *(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0VscaleStep_Pstep] <-- 0x%08x\n",
                        REG_TD_LAYER0VSCALESTEP,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0VscaleStep_Pstep(void)
{
    MH_TD_LAYER0VSCALESTEP_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0VscaleStep_Pstep] --> 0x%08x\n",
                        REG_TD_LAYER0VSCALESTEP,value);
    #endif
    return tmp_value.bitc.pstep;
}
MH_INLINE void MH_TD_set_Layer0VscaleStep_Dstep(MS_U16 data)
{
    MH_TD_LAYER0VSCALESTEP_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP;
    d.bitc.dstep = data;
    *(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0VscaleStep_Dstep] <-- 0x%08x\n",
                        REG_TD_LAYER0VSCALESTEP,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0VscaleStep_Dstep(void)
{
    MH_TD_LAYER0VSCALESTEP_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0VSCALESTEP);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0VscaleStep_Dstep] --> 0x%08x\n",
                        REG_TD_LAYER0VSCALESTEP,value);
    #endif
    return tmp_value.bitc.dstep;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0VscaleSt (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0VscaleSt'. */
void MH_TD_set_Layer0VscaleSt(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0VscaleSt'. */
MS_U32  MH_TD_get_Layer0VscaleSt(void);
/*! \brief Writes the bit group 'Pstep' of register 'TD_Layer0VscaleSt'. */
void MH_TD_set_Layer0VscaleSt_Pstep(MS_U16 data);
/*! \brief Reads the bit group 'Pstep' of register 'TD_Layer0VscaleSt'. */
MS_U16  MH_TD_get_Layer0VscaleSt_Pstep(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0VscaleSt(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0VSCALEST = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0VscaleSt] <-- 0x%08x\n",
                        REG_TD_LAYER0VSCALEST,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0VscaleSt(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0VSCALEST);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0VscaleSt] --> 0x%08x\n",
                        REG_TD_LAYER0VSCALEST,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0VscaleSt_Pstep(MS_U16 data)
{
    MH_TD_LAYER0VSCALEST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0VSCALEST;
    d.bitc.pstep = data;
    *(volatile MS_U32 *)REG_TD_LAYER0VSCALEST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0VscaleSt_Pstep] <-- 0x%08x\n",
                        REG_TD_LAYER0VSCALEST,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0VscaleSt_Pstep(void)
{
    MH_TD_LAYER0VSCALEST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0VSCALEST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0VscaleSt_Pstep] --> 0x%08x\n",
                        REG_TD_LAYER0VSCALEST,value);
    #endif
    return tmp_value.bitc.pstep;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0HscaleStep (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0HscaleStep'. */
void MH_TD_set_Layer0HscaleStep(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0HscaleStep'. */
MS_U32  MH_TD_get_Layer0HscaleStep(void);
/*! \brief Writes the bit group 'Pstep' of register 'TD_Layer0HscaleStep'. */
void MH_TD_set_Layer0HscaleStep_Pstep(MS_U8 data);
/*! \brief Reads the bit group 'Pstep' of register 'TD_Layer0HscaleStep'. */
MS_U8   MH_TD_get_Layer0HscaleStep_Pstep(void);
/*! \brief Writes the bit group 'Dstep' of register 'TD_Layer0HscaleStep'. */
void MH_TD_set_Layer0HscaleStep_Dstep(MS_U16 data);
/*! \brief Reads the bit group 'Dstep' of register 'TD_Layer0HscaleStep'. */
MS_U16  MH_TD_get_Layer0HscaleStep_Dstep(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0HscaleStep(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0HscaleStep] <-- 0x%08x\n",
                        REG_TD_LAYER0HSCALESTEP,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0HscaleStep(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0HscaleStep] --> 0x%08x\n",
                        REG_TD_LAYER0HSCALESTEP,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0HscaleStep_Pstep(MS_U8 data)
{
    MH_TD_LAYER0HSCALESTEP_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP;
    d.bitc.pstep = data;
    *(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0HscaleStep_Pstep] <-- 0x%08x\n",
                        REG_TD_LAYER0HSCALESTEP,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0HscaleStep_Pstep(void)
{
    MH_TD_LAYER0HSCALESTEP_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0HscaleStep_Pstep] --> 0x%08x\n",
                        REG_TD_LAYER0HSCALESTEP,value);
    #endif
    return tmp_value.bitc.pstep;
}
MH_INLINE void MH_TD_set_Layer0HscaleStep_Dstep(MS_U16 data)
{
    MH_TD_LAYER0HSCALESTEP_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP;
    d.bitc.dstep = data;
    *(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0HscaleStep_Dstep] <-- 0x%08x\n",
                        REG_TD_LAYER0HSCALESTEP,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0HscaleStep_Dstep(void)
{
    MH_TD_LAYER0HSCALESTEP_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0HSCALESTEP);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0HscaleStep_Dstep] --> 0x%08x\n",
                        REG_TD_LAYER0HSCALESTEP,value);
    #endif
    return tmp_value.bitc.dstep;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0HscaleSt (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0HscaleSt'. */
void MH_TD_set_Layer0HscaleSt(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0HscaleSt'. */
MS_U32  MH_TD_get_Layer0HscaleSt(void);
/*! \brief Writes the bit group 'Pstep' of register 'TD_Layer0HscaleSt'. */
void MH_TD_set_Layer0HscaleSt_Pstep(MS_U16 data);
/*! \brief Reads the bit group 'Pstep' of register 'TD_Layer0HscaleSt'. */
MS_U16  MH_TD_get_Layer0HscaleSt_Pstep(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0HscaleSt(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0HSCALEST = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0HscaleSt] <-- 0x%08x\n",
                        REG_TD_LAYER0HSCALEST,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0HscaleSt(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0HSCALEST);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0HscaleSt] --> 0x%08x\n",
                        REG_TD_LAYER0HSCALEST,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0HscaleSt_Pstep(MS_U16 data)
{
    MH_TD_LAYER0HSCALEST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0HSCALEST;
    d.bitc.pstep = data;
    *(volatile MS_U32 *)REG_TD_LAYER0HSCALEST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0HscaleSt_Pstep] <-- 0x%08x\n",
                        REG_TD_LAYER0HSCALEST,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Layer0HscaleSt_Pstep(void)
{
    MH_TD_LAYER0HSCALEST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0HSCALEST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0HscaleSt_Pstep] --> 0x%08x\n",
                        REG_TD_LAYER0HSCALEST,value);
    #endif
    return tmp_value.bitc.pstep;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Layer0BaseMode (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Layer0BaseMode'. */
void MH_TD_set_Layer0BaseMode(MS_U32 data);
/*! \brief Reads the register 'TD_Layer0BaseMode'. */
MS_U32  MH_TD_get_Layer0BaseMode(void);
/*! \brief Writes the bit group 'Mode' of register 'TD_Layer0BaseMode'. */
void MH_TD_set_Layer0BaseMode_Mode(MS_U8 data);
/*! \brief Reads the bit group 'Mode' of register 'TD_Layer0BaseMode'. */
MS_U8   MH_TD_get_Layer0BaseMode_Mode(void);
/*! \brief Writes the bit group 'Base0Mask' of register 'TD_Layer0BaseMode'. */
void MH_TD_set_Layer0BaseMode_Base0Mask(MS_U8 data);
/*! \brief Reads the bit group 'Base0Mask' of register 'TD_Layer0BaseMode'. */
MS_U8   MH_TD_get_Layer0BaseMode_Base0Mask(void);
/*! \brief Writes the bit group 'Base1Mask' of register 'TD_Layer0BaseMode'. */
void MH_TD_set_Layer0BaseMode_Base1Mask(MS_U8 data);
/*! \brief Reads the bit group 'Base1Mask' of register 'TD_Layer0BaseMode'. */
MS_U8   MH_TD_get_Layer0BaseMode_Base1Mask(void);
/*! \brief Writes the bit group 'AddrFlag' of register 'TD_Layer0BaseMode'. */
void MH_TD_set_Layer0BaseMode_AddrFlag(MS_U8 data);
/*! \brief Reads the bit group 'AddrFlag' of register 'TD_Layer0BaseMode'. */
MS_U8   MH_TD_get_Layer0BaseMode_AddrFlag(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Layer0BaseMode(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0BaseMode] <-- 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Layer0BaseMode(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BASEMODE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0BaseMode] --> 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Layer0BaseMode_Mode(MS_U8 data)
{
    MH_TD_LAYER0BASEMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE;
    d.bitc.mode = data;
    *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0BaseMode_Mode] <-- 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0BaseMode_Mode(void)
{
    MH_TD_LAYER0BASEMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BASEMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0BaseMode_Mode] --> 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,value);
    #endif
    return tmp_value.bitc.mode;
}
MH_INLINE void MH_TD_set_Layer0BaseMode_Base0Mask(MS_U8 data)
{
    MH_TD_LAYER0BASEMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE;
    d.bitc.base0mask = data;
    *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0BaseMode_Base0Mask] <-- 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0BaseMode_Base0Mask(void)
{
    MH_TD_LAYER0BASEMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BASEMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0BaseMode_Base0Mask] --> 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,value);
    #endif
    return tmp_value.bitc.base0mask;
}
MH_INLINE void MH_TD_set_Layer0BaseMode_Base1Mask(MS_U8 data)
{
    MH_TD_LAYER0BASEMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE;
    d.bitc.base1mask = data;
    *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0BaseMode_Base1Mask] <-- 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0BaseMode_Base1Mask(void)
{
    MH_TD_LAYER0BASEMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BASEMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0BaseMode_Base1Mask] --> 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,value);
    #endif
    return tmp_value.bitc.base1mask;
}
MH_INLINE void MH_TD_set_Layer0BaseMode_AddrFlag(MS_U8 data)
{
    MH_TD_LAYER0BASEMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE;
    d.bitc.addrflag = data;
    *(volatile MS_U32 *)REG_TD_LAYER0BASEMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Layer0BaseMode_AddrFlag] <-- 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Layer0BaseMode_AddrFlag(void)
{
    MH_TD_LAYER0BASEMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_LAYER0BASEMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Layer0BaseMode_AddrFlag] --> 0x%08x\n",
                        REG_TD_LAYER0BASEMODE,value);
    #endif
    return tmp_value.bitc.addrflag;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Osd0Info (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Osd0Info'. */
void MH_TD_set_Osd0Info(MS_U32 data);
/*! \brief Reads the register 'TD_Osd0Info'. */
MS_U32  MH_TD_get_Osd0Info(void);
/*! \brief Writes the bit group 'OsdType' of register 'TD_Osd0Info'. */
void MH_TD_set_Osd0Info_OsdType(MS_U8 data);
/*! \brief Reads the bit group 'OsdType' of register 'TD_Osd0Info'. */
MS_U8   MH_TD_get_Osd0Info_OsdType(void);
/*! \brief Writes the bit group 'AlphaTpye' of register 'TD_Osd0Info'. */
void MH_TD_set_Osd0Info_AlphaTpye(MS_U8 data);
/*! \brief Reads the bit group 'AlphaTpye' of register 'TD_Osd0Info'. */
MS_U8   MH_TD_get_Osd0Info_AlphaTpye(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Osd0Info(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSD0INFO = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Info] <-- 0x%08x\n",
                        REG_TD_OSD0INFO,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Osd0Info(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0INFO);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Info] --> 0x%08x\n",
                        REG_TD_OSD0INFO,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Osd0Info_OsdType(MS_U8 data)
{
    MH_TD_OSD0INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0INFO;
    d.bitc.osdtype = data;
    *(volatile MS_U32 *)REG_TD_OSD0INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Info_OsdType] <-- 0x%08x\n",
                        REG_TD_OSD0INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Osd0Info_OsdType(void)
{
    MH_TD_OSD0INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Info_OsdType] --> 0x%08x\n",
                        REG_TD_OSD0INFO,value);
    #endif
    return tmp_value.bitc.osdtype;
}
MH_INLINE void MH_TD_set_Osd0Info_AlphaTpye(MS_U8 data)
{
    MH_TD_OSD0INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0INFO;
    d.bitc.alphatpye = data;
    *(volatile MS_U32 *)REG_TD_OSD0INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Info_AlphaTpye] <-- 0x%08x\n",
                        REG_TD_OSD0INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Osd0Info_AlphaTpye(void)
{
    MH_TD_OSD0INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Info_AlphaTpye] --> 0x%08x\n",
                        REG_TD_OSD0INFO,value);
    #endif
    return tmp_value.bitc.alphatpye;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Osd0Size (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Osd0Size'. */
void MH_TD_set_Osd0Size(MS_U32 data);
/*! \brief Reads the register 'TD_Osd0Size'. */
MS_U32  MH_TD_get_Osd0Size(void);
/*! \brief Writes the bit group 'Width' of register 'TD_Osd0Size'. */
void MH_TD_set_Osd0Size_Width(MS_U16 data);
/*! \brief Reads the bit group 'Width' of register 'TD_Osd0Size'. */
MS_U16  MH_TD_get_Osd0Size_Width(void);
/*! \brief Writes the bit group 'Height' of register 'TD_Osd0Size'. */
void MH_TD_set_Osd0Size_Height(MS_U16 data);
/*! \brief Reads the bit group 'Height' of register 'TD_Osd0Size'. */
MS_U16  MH_TD_get_Osd0Size_Height(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Osd0Size(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSD0SIZE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Size] <-- 0x%08x\n",
                        REG_TD_OSD0SIZE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Osd0Size(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0SIZE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Size] --> 0x%08x\n",
                        REG_TD_OSD0SIZE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Osd0Size_Width(MS_U16 data)
{
    MH_TD_OSD0SIZE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0SIZE;
    d.bitc.width = data;
    *(volatile MS_U32 *)REG_TD_OSD0SIZE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Size_Width] <-- 0x%08x\n",
                        REG_TD_OSD0SIZE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Osd0Size_Width(void)
{
    MH_TD_OSD0SIZE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0SIZE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Size_Width] --> 0x%08x\n",
                        REG_TD_OSD0SIZE,value);
    #endif
    return tmp_value.bitc.width;
}
MH_INLINE void MH_TD_set_Osd0Size_Height(MS_U16 data)
{
    MH_TD_OSD0SIZE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0SIZE;
    d.bitc.height = data;
    *(volatile MS_U32 *)REG_TD_OSD0SIZE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Size_Height] <-- 0x%08x\n",
                        REG_TD_OSD0SIZE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Osd0Size_Height(void)
{
    MH_TD_OSD0SIZE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0SIZE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Size_Height] --> 0x%08x\n",
                        REG_TD_OSD0SIZE,value);
    #endif
    return tmp_value.bitc.height;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Osd0VluAddr0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Osd0VluAddr0'. */
void MH_TD_set_Osd0VluAddr0(MS_U32 data);
/*! \brief Reads the register 'TD_Osd0VluAddr0'. */
MS_U32  MH_TD_get_Osd0VluAddr0(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Osd0VluAddr0(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSD0VLUADDR0 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0VluAddr0] <-- 0x%08x\n",
                        REG_TD_OSD0VLUADDR0,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Osd0VluAddr0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0VLUADDR0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0VluAddr0] --> 0x%08x\n",
                        REG_TD_OSD0VLUADDR0,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Osd0AlpAddr0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Osd0AlpAddr0'. */
void MH_TD_set_Osd0AlpAddr0(MS_U32 data);
/*! \brief Reads the register 'TD_Osd0AlpAddr0'. */
MS_U32  MH_TD_get_Osd0AlpAddr0(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Osd0AlpAddr0(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSD0ALPADDR0 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0AlpAddr0] <-- 0x%08x\n",
                        REG_TD_OSD0ALPADDR0,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Osd0AlpAddr0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0ALPADDR0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0AlpAddr0] --> 0x%08x\n",
                        REG_TD_OSD0ALPADDR0,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Osd0DMACtl (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Osd0DMACtl'. */
void MH_TD_set_Osd0DMACtl(MS_U32 data);
/*! \brief Reads the register 'TD_Osd0DMACtl'. */
MS_U32  MH_TD_get_Osd0DMACtl(void);
/*! \brief Writes the bit group 'DMARequestLen' of register 'TD_Osd0DMACtl'. */
void MH_TD_set_Osd0DMACtl_DMARequestLen(MS_U8 data);
/*! \brief Reads the bit group 'DMARequestLen' of register 'TD_Osd0DMACtl'. */
MS_U8   MH_TD_get_Osd0DMACtl_DMARequestLen(void);
/*! \brief Writes the bit group 'DMAMap' of register 'TD_Osd0DMACtl'. */
void MH_TD_set_Osd0DMACtl_DMAMap(MS_U8 data);
/*! \brief Reads the bit group 'DMAMap' of register 'TD_Osd0DMACtl'. */
MS_U8   MH_TD_get_Osd0DMACtl_DMAMap(void);
/*! \brief Writes the bit group 'RGBRev' of register 'TD_Osd0DMACtl'. */
void MH_TD_set_Osd0DMACtl_RGBRev(MS_U8 data);
/*! \brief Reads the bit group 'RGBRev' of register 'TD_Osd0DMACtl'. */
MS_U8   MH_TD_get_Osd0DMACtl_RGBRev(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Osd0DMACtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSD0DMACTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0DMACtl] <-- 0x%08x\n",
                        REG_TD_OSD0DMACTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Osd0DMACtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0DMACTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0DMACtl] --> 0x%08x\n",
                        REG_TD_OSD0DMACTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Osd0DMACtl_DMARequestLen(MS_U8 data)
{
    MH_TD_OSD0DMACTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0DMACTL;
    d.bitc.dmarequestlen = data;
    *(volatile MS_U32 *)REG_TD_OSD0DMACTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0DMACtl_DMARequestLen] <-- 0x%08x\n",
                        REG_TD_OSD0DMACTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Osd0DMACtl_DMARequestLen(void)
{
    MH_TD_OSD0DMACTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0DMACTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0DMACtl_DMARequestLen] --> 0x%08x\n",
                        REG_TD_OSD0DMACTL,value);
    #endif
    return tmp_value.bitc.dmarequestlen;
}
MH_INLINE void MH_TD_set_Osd0DMACtl_DMAMap(MS_U8 data)
{
    MH_TD_OSD0DMACTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0DMACTL;
    d.bitc.dmamap = data;
    *(volatile MS_U32 *)REG_TD_OSD0DMACTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0DMACtl_DMAMap] <-- 0x%08x\n",
                        REG_TD_OSD0DMACTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Osd0DMACtl_DMAMap(void)
{
    MH_TD_OSD0DMACTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0DMACTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0DMACtl_DMAMap] --> 0x%08x\n",
                        REG_TD_OSD0DMACTL,value);
    #endif
    return tmp_value.bitc.dmamap;
}
MH_INLINE void MH_TD_set_Osd0DMACtl_RGBRev(MS_U8 data)
{
    MH_TD_OSD0DMACTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0DMACTL;
    d.bitc.rgbrev = data;
    *(volatile MS_U32 *)REG_TD_OSD0DMACTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0DMACtl_RGBRev] <-- 0x%08x\n",
                        REG_TD_OSD0DMACTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_Osd0DMACtl_RGBRev(void)
{
    MH_TD_OSD0DMACTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0DMACTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0DMACtl_RGBRev] --> 0x%08x\n",
                        REG_TD_OSD0DMACTL,value);
    #endif
    return tmp_value.bitc.rgbrev;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_Osd0Stride (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_Osd0Stride'. */
void MH_TD_set_Osd0Stride(MS_U32 data);
/*! \brief Reads the register 'TD_Osd0Stride'. */
MS_U32  MH_TD_get_Osd0Stride(void);
/*! \brief Writes the bit group 'OsdStride' of register 'TD_Osd0Stride'. */
void MH_TD_set_Osd0Stride_OsdStride(MS_U16 data);
/*! \brief Reads the bit group 'OsdStride' of register 'TD_Osd0Stride'. */
MS_U16  MH_TD_get_Osd0Stride_OsdStride(void);
/*! \brief Writes the bit group 'AlpStride' of register 'TD_Osd0Stride'. */
void MH_TD_set_Osd0Stride_AlpStride(MS_U16 data);
/*! \brief Reads the bit group 'AlpStride' of register 'TD_Osd0Stride'. */
MS_U16  MH_TD_get_Osd0Stride_AlpStride(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_Osd0Stride(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSD0STRIDE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Stride] <-- 0x%08x\n",
                        REG_TD_OSD0STRIDE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_Osd0Stride(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0STRIDE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Stride] --> 0x%08x\n",
                        REG_TD_OSD0STRIDE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_Osd0Stride_OsdStride(MS_U16 data)
{
    MH_TD_OSD0STRIDE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0STRIDE;
    d.bitc.osdstride = data;
    *(volatile MS_U32 *)REG_TD_OSD0STRIDE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Stride_OsdStride] <-- 0x%08x\n",
                        REG_TD_OSD0STRIDE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Osd0Stride_OsdStride(void)
{
    MH_TD_OSD0STRIDE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0STRIDE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Stride_OsdStride] --> 0x%08x\n",
                        REG_TD_OSD0STRIDE,value);
    #endif
    return tmp_value.bitc.osdstride;
}
MH_INLINE void MH_TD_set_Osd0Stride_AlpStride(MS_U16 data)
{
    MH_TD_OSD0STRIDE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSD0STRIDE;
    d.bitc.alpstride = data;
    *(volatile MS_U32 *)REG_TD_OSD0STRIDE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_Osd0Stride_AlpStride] <-- 0x%08x\n",
                        REG_TD_OSD0STRIDE,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_Osd0Stride_AlpStride(void)
{
    MH_TD_OSD0STRIDE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSD0STRIDE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_Osd0Stride_AlpStride] --> 0x%08x\n",
                        REG_TD_OSD0STRIDE,value);
    #endif
    return tmp_value.bitc.alpstride;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCtl (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCtl'. */
void MH_TD_set_OsdRGB2YUVCtl(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCtl'. */
MS_U32  MH_TD_get_OsdRGB2YUVCtl(void);
/*! \brief Writes the bit group 'Osd0En' of register 'TD_OsdRGB2YUVCtl'. */
void MH_TD_set_OsdRGB2YUVCtl_Osd0En(MS_U8 data);
/*! \brief Reads the bit group 'Osd0En' of register 'TD_OsdRGB2YUVCtl'. */
MS_U8   MH_TD_get_OsdRGB2YUVCtl_Osd0En(void);
/*! \brief Writes the bit group 'Osd1En' of register 'TD_OsdRGB2YUVCtl'. */
void MH_TD_set_OsdRGB2YUVCtl_Osd1En(MS_U8 data);
/*! \brief Reads the bit group 'Osd1En' of register 'TD_OsdRGB2YUVCtl'. */
MS_U8   MH_TD_get_OsdRGB2YUVCtl_Osd1En(void);
/*! \brief Writes the bit group 'Osd2En' of register 'TD_OsdRGB2YUVCtl'. */
void MH_TD_set_OsdRGB2YUVCtl_Osd2En(MS_U8 data);
/*! \brief Reads the bit group 'Osd2En' of register 'TD_OsdRGB2YUVCtl'. */
MS_U8   MH_TD_get_OsdRGB2YUVCtl_Osd2En(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCtl] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCtl] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCtl_Osd0En(MS_U8 data)
{
    MH_TD_OSDRGB2YUVCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL;
    d.bitc.osd0en = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCtl_Osd0En] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_OsdRGB2YUVCtl_Osd0En(void)
{
    MH_TD_OSDRGB2YUVCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCtl_Osd0En] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,value);
    #endif
    return tmp_value.bitc.osd0en;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCtl_Osd1En(MS_U8 data)
{
    MH_TD_OSDRGB2YUVCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL;
    d.bitc.osd1en = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCtl_Osd1En] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_OsdRGB2YUVCtl_Osd1En(void)
{
    MH_TD_OSDRGB2YUVCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCtl_Osd1En] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,value);
    #endif
    return tmp_value.bitc.osd1en;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCtl_Osd2En(MS_U8 data)
{
    MH_TD_OSDRGB2YUVCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL;
    d.bitc.osd2en = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCtl_Osd2En] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_OsdRGB2YUVCtl_Osd2En(void)
{
    MH_TD_OSDRGB2YUVCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCtl_Osd2En] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCTL,value);
    #endif
    return tmp_value.bitc.osd2en;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff00 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff00'. */
void MH_TD_set_OsdRGB2YUVCoeff00(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff00'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff00(void);
/*! \brief Writes the bit group 'C00' of register 'TD_OsdRGB2YUVCoeff00'. */
void MH_TD_set_OsdRGB2YUVCoeff00_C00(MS_U16 data);
/*! \brief Reads the bit group 'C00' of register 'TD_OsdRGB2YUVCoeff00'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff00_C00(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff00(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF00 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff00] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF00,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff00(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF00);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff00] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF00,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff00_C00(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF00_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF00;
    d.bitc.c00 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF00 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff00_C00] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF00,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff00_C00(void)
{
    MH_TD_OSDRGB2YUVCOEFF00_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF00);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff00_C00] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF00,value);
    #endif
    return tmp_value.bitc.c00;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff01 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff01'. */
void MH_TD_set_OsdRGB2YUVCoeff01(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff01'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff01(void);
/*! \brief Writes the bit group 'C01' of register 'TD_OsdRGB2YUVCoeff01'. */
void MH_TD_set_OsdRGB2YUVCoeff01_C01(MS_U16 data);
/*! \brief Reads the bit group 'C01' of register 'TD_OsdRGB2YUVCoeff01'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff01_C01(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff01(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF01 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff01] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF01,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff01(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF01);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff01] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF01,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff01_C01(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF01_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF01;
    d.bitc.c01 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF01 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff01_C01] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF01,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff01_C01(void)
{
    MH_TD_OSDRGB2YUVCOEFF01_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF01);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff01_C01] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF01,value);
    #endif
    return tmp_value.bitc.c01;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff02 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff02'. */
void MH_TD_set_OsdRGB2YUVCoeff02(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff02'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff02(void);
/*! \brief Writes the bit group 'C02' of register 'TD_OsdRGB2YUVCoeff02'. */
void MH_TD_set_OsdRGB2YUVCoeff02_C02(MS_U16 data);
/*! \brief Reads the bit group 'C02' of register 'TD_OsdRGB2YUVCoeff02'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff02_C02(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff02(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF02 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff02] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF02,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff02(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF02);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff02] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF02,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff02_C02(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF02_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF02;
    d.bitc.c02 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF02 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff02_C02] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF02,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff02_C02(void)
{
    MH_TD_OSDRGB2YUVCOEFF02_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF02);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff02_C02] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF02,value);
    #endif
    return tmp_value.bitc.c02;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff03 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff03'. */
void MH_TD_set_OsdRGB2YUVCoeff03(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff03'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff03(void);
/*! \brief Writes the bit group 'C03' of register 'TD_OsdRGB2YUVCoeff03'. */
void MH_TD_set_OsdRGB2YUVCoeff03_C03(MS_U16 data);
/*! \brief Reads the bit group 'C03' of register 'TD_OsdRGB2YUVCoeff03'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff03_C03(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff03(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF03 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff03] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF03,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff03(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF03);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff03] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF03,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff03_C03(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF03_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF03;
    d.bitc.c03 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF03 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff03_C03] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF03,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff03_C03(void)
{
    MH_TD_OSDRGB2YUVCOEFF03_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF03);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff03_C03] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF03,value);
    #endif
    return tmp_value.bitc.c03;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff10 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff10'. */
void MH_TD_set_OsdRGB2YUVCoeff10(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff10'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff10(void);
/*! \brief Writes the bit group 'C10' of register 'TD_OsdRGB2YUVCoeff10'. */
void MH_TD_set_OsdRGB2YUVCoeff10_C10(MS_U16 data);
/*! \brief Reads the bit group 'C10' of register 'TD_OsdRGB2YUVCoeff10'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff10_C10(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff10(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF10 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff10] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF10,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff10(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF10);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff10] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF10,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff10_C10(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF10_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF10;
    d.bitc.c10 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF10 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff10_C10] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF10,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff10_C10(void)
{
    MH_TD_OSDRGB2YUVCOEFF10_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF10);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff10_C10] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF10,value);
    #endif
    return tmp_value.bitc.c10;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff11 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff11'. */
void MH_TD_set_OsdRGB2YUVCoeff11(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff11'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff11(void);
/*! \brief Writes the bit group 'C11' of register 'TD_OsdRGB2YUVCoeff11'. */
void MH_TD_set_OsdRGB2YUVCoeff11_C11(MS_U16 data);
/*! \brief Reads the bit group 'C11' of register 'TD_OsdRGB2YUVCoeff11'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff11_C11(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff11(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF11 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff11] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF11,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff11(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF11);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff11] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF11,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff11_C11(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF11_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF11;
    d.bitc.c11 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF11 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff11_C11] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF11,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff11_C11(void)
{
    MH_TD_OSDRGB2YUVCOEFF11_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF11);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff11_C11] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF11,value);
    #endif
    return tmp_value.bitc.c11;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff12 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff12'. */
void MH_TD_set_OsdRGB2YUVCoeff12(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff12'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff12(void);
/*! \brief Writes the bit group 'C12' of register 'TD_OsdRGB2YUVCoeff12'. */
void MH_TD_set_OsdRGB2YUVCoeff12_C12(MS_U16 data);
/*! \brief Reads the bit group 'C12' of register 'TD_OsdRGB2YUVCoeff12'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff12_C12(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff12(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF12 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff12] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF12,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff12(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF12);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff12] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF12,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff12_C12(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF12_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF12;
    d.bitc.c12 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF12 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff12_C12] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF12,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff12_C12(void)
{
    MH_TD_OSDRGB2YUVCOEFF12_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF12);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff12_C12] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF12,value);
    #endif
    return tmp_value.bitc.c12;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff13 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff13'. */
void MH_TD_set_OsdRGB2YUVCoeff13(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff13'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff13(void);
/*! \brief Writes the bit group 'C13' of register 'TD_OsdRGB2YUVCoeff13'. */
void MH_TD_set_OsdRGB2YUVCoeff13_C13(MS_U16 data);
/*! \brief Reads the bit group 'C13' of register 'TD_OsdRGB2YUVCoeff13'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff13_C13(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff13(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF13 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff13] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF13,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff13(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF13);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff13] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF13,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff13_C13(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF13_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF13;
    d.bitc.c13 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF13 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff13_C13] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF13,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff13_C13(void)
{
    MH_TD_OSDRGB2YUVCOEFF13_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF13);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff13_C13] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF13,value);
    #endif
    return tmp_value.bitc.c13;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff20 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff20'. */
void MH_TD_set_OsdRGB2YUVCoeff20(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff20'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff20(void);
/*! \brief Writes the bit group 'C20' of register 'TD_OsdRGB2YUVCoeff20'. */
void MH_TD_set_OsdRGB2YUVCoeff20_C20(MS_U16 data);
/*! \brief Reads the bit group 'C20' of register 'TD_OsdRGB2YUVCoeff20'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff20_C20(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff20(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF20 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff20] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF20,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff20(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF20);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff20] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF20,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff20_C20(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF20_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF20;
    d.bitc.c20 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF20 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff20_C20] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF20,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff20_C20(void)
{
    MH_TD_OSDRGB2YUVCOEFF20_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF20);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff20_C20] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF20,value);
    #endif
    return tmp_value.bitc.c20;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff21 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff21'. */
void MH_TD_set_OsdRGB2YUVCoeff21(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff21'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff21(void);
/*! \brief Writes the bit group 'C21' of register 'TD_OsdRGB2YUVCoeff21'. */
void MH_TD_set_OsdRGB2YUVCoeff21_C21(MS_U16 data);
/*! \brief Reads the bit group 'C21' of register 'TD_OsdRGB2YUVCoeff21'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff21_C21(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff21(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF21 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff21] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF21,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff21(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF21);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff21] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF21,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff21_C21(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF21_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF21;
    d.bitc.c21 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF21 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff21_C21] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF21,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff21_C21(void)
{
    MH_TD_OSDRGB2YUVCOEFF21_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF21);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff21_C21] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF21,value);
    #endif
    return tmp_value.bitc.c21;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff22 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff22'. */
void MH_TD_set_OsdRGB2YUVCoeff22(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff22'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff22(void);
/*! \brief Writes the bit group 'C22' of register 'TD_OsdRGB2YUVCoeff22'. */
void MH_TD_set_OsdRGB2YUVCoeff22_C22(MS_U16 data);
/*! \brief Reads the bit group 'C22' of register 'TD_OsdRGB2YUVCoeff22'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff22_C22(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff22(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF22 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff22] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF22,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff22(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF22);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff22] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF22,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff22_C22(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF22_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF22;
    d.bitc.c22 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF22 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff22_C22] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF22,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff22_C22(void)
{
    MH_TD_OSDRGB2YUVCOEFF22_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF22);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff22_C22] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF22,value);
    #endif
    return tmp_value.bitc.c22;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_OsdRGB2YUVCoeff23 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_OsdRGB2YUVCoeff23'. */
void MH_TD_set_OsdRGB2YUVCoeff23(MS_U32 data);
/*! \brief Reads the register 'TD_OsdRGB2YUVCoeff23'. */
MS_U32  MH_TD_get_OsdRGB2YUVCoeff23(void);
/*! \brief Writes the bit group 'C23' of register 'TD_OsdRGB2YUVCoeff23'. */
void MH_TD_set_OsdRGB2YUVCoeff23_C23(MS_U16 data);
/*! \brief Reads the bit group 'C23' of register 'TD_OsdRGB2YUVCoeff23'. */
MS_U16  MH_TD_get_OsdRGB2YUVCoeff23_C23(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff23(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF23 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff23] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF23,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_OsdRGB2YUVCoeff23(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF23);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff23] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF23,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_OsdRGB2YUVCoeff23_C23(MS_U16 data)
{
    MH_TD_OSDRGB2YUVCOEFF23_S d;
    d.all = *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF23;
    d.bitc.c23 = data;
    *(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF23 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_OsdRGB2YUVCoeff23_C23] <-- 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF23,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_OsdRGB2YUVCoeff23_C23(void)
{
    MH_TD_OSDRGB2YUVCOEFF23_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_OSDRGB2YUVCOEFF23);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_OsdRGB2YUVCoeff23_C23] --> 0x%08x\n",
                        REG_TD_OSDRGB2YUVCOEFF23,value);
    #endif
    return tmp_value.bitc.c23;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCtl (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCtl'. */
void MH_TD_set_DispYUV2RGBCtl(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCtl'. */
MS_U32  MH_TD_get_DispYUV2RGBCtl(void);
/*! \brief Writes the bit group 'En' of register 'TD_DispYUV2RGBCtl'. */
void MH_TD_set_DispYUV2RGBCtl_En(MS_U8 data);
/*! \brief Reads the bit group 'En' of register 'TD_DispYUV2RGBCtl'. */
MS_U8   MH_TD_get_DispYUV2RGBCtl_En(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCtl(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCTL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCtl] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCTL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCtl(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCTL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCtl] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCTL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCtl_En(MS_U8 data)
{
    MH_TD_DISPYUV2RGBCTL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCTL;
    d.bitc.en = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCTL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCtl_En] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCTL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispYUV2RGBCtl_En(void)
{
    MH_TD_DISPYUV2RGBCTL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCTL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCtl_En] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCTL,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff00 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff00'. */
void MH_TD_set_DispYUV2RGBCoeff00(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff00'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff00(void);
/*! \brief Writes the bit group 'C00' of register 'TD_DispYUV2RGBCoeff00'. */
void MH_TD_set_DispYUV2RGBCoeff00_C00(MS_U16 data);
/*! \brief Reads the bit group 'C00' of register 'TD_DispYUV2RGBCoeff00'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff00_C00(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff00(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF00 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff00] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF00,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff00(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF00);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff00] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF00,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff00_C00(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF00_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF00;
    d.bitc.c00 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF00 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff00_C00] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF00,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff00_C00(void)
{
    MH_TD_DISPYUV2RGBCOEFF00_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF00);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff00_C00] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF00,value);
    #endif
    return tmp_value.bitc.c00;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff01 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff01'. */
void MH_TD_set_DispYUV2RGBCoeff01(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff01'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff01(void);
/*! \brief Writes the bit group 'C01' of register 'TD_DispYUV2RGBCoeff01'. */
void MH_TD_set_DispYUV2RGBCoeff01_C01(MS_U16 data);
/*! \brief Reads the bit group 'C01' of register 'TD_DispYUV2RGBCoeff01'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff01_C01(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff01(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF01 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff01] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF01,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff01(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF01);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff01] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF01,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff01_C01(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF01_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF01;
    d.bitc.c01 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF01 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff01_C01] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF01,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff01_C01(void)
{
    MH_TD_DISPYUV2RGBCOEFF01_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF01);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff01_C01] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF01,value);
    #endif
    return tmp_value.bitc.c01;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff02 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff02'. */
void MH_TD_set_DispYUV2RGBCoeff02(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff02'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff02(void);
/*! \brief Writes the bit group 'C02' of register 'TD_DispYUV2RGBCoeff02'. */
void MH_TD_set_DispYUV2RGBCoeff02_C02(MS_U16 data);
/*! \brief Reads the bit group 'C02' of register 'TD_DispYUV2RGBCoeff02'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff02_C02(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff02(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF02 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff02] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF02,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff02(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF02);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff02] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF02,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff02_C02(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF02_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF02;
    d.bitc.c02 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF02 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff02_C02] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF02,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff02_C02(void)
{
    MH_TD_DISPYUV2RGBCOEFF02_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF02);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff02_C02] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF02,value);
    #endif
    return tmp_value.bitc.c02;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff03 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff03'. */
void MH_TD_set_DispYUV2RGBCoeff03(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff03'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff03(void);
/*! \brief Writes the bit group 'C03' of register 'TD_DispYUV2RGBCoeff03'. */
void MH_TD_set_DispYUV2RGBCoeff03_C03(MS_U16 data);
/*! \brief Reads the bit group 'C03' of register 'TD_DispYUV2RGBCoeff03'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff03_C03(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff03(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF03 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff03] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF03,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff03(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF03);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff03] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF03,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff03_C03(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF03_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF03;
    d.bitc.c03 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF03 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff03_C03] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF03,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff03_C03(void)
{
    MH_TD_DISPYUV2RGBCOEFF03_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF03);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff03_C03] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF03,value);
    #endif
    return tmp_value.bitc.c03;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff10 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff10'. */
void MH_TD_set_DispYUV2RGBCoeff10(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff10'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff10(void);
/*! \brief Writes the bit group 'C10' of register 'TD_DispYUV2RGBCoeff10'. */
void MH_TD_set_DispYUV2RGBCoeff10_C10(MS_U16 data);
/*! \brief Reads the bit group 'C10' of register 'TD_DispYUV2RGBCoeff10'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff10_C10(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff10(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF10 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff10] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF10,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff10(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF10);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff10] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF10,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff10_C10(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF10_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF10;
    d.bitc.c10 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF10 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff10_C10] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF10,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff10_C10(void)
{
    MH_TD_DISPYUV2RGBCOEFF10_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF10);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff10_C10] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF10,value);
    #endif
    return tmp_value.bitc.c10;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff11 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff11'. */
void MH_TD_set_DispYUV2RGBCoeff11(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff11'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff11(void);
/*! \brief Writes the bit group 'C11' of register 'TD_DispYUV2RGBCoeff11'. */
void MH_TD_set_DispYUV2RGBCoeff11_C11(MS_U16 data);
/*! \brief Reads the bit group 'C11' of register 'TD_DispYUV2RGBCoeff11'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff11_C11(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff11(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF11 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff11] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF11,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff11(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF11);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff11] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF11,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff11_C11(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF11_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF11;
    d.bitc.c11 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF11 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff11_C11] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF11,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff11_C11(void)
{
    MH_TD_DISPYUV2RGBCOEFF11_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF11);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff11_C11] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF11,value);
    #endif
    return tmp_value.bitc.c11;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff12 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff12'. */
void MH_TD_set_DispYUV2RGBCoeff12(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff12'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff12(void);
/*! \brief Writes the bit group 'C12' of register 'TD_DispYUV2RGBCoeff12'. */
void MH_TD_set_DispYUV2RGBCoeff12_C12(MS_U16 data);
/*! \brief Reads the bit group 'C12' of register 'TD_DispYUV2RGBCoeff12'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff12_C12(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff12(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF12 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff12] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF12,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff12(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF12);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff12] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF12,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff12_C12(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF12_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF12;
    d.bitc.c12 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF12 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff12_C12] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF12,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff12_C12(void)
{
    MH_TD_DISPYUV2RGBCOEFF12_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF12);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff12_C12] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF12,value);
    #endif
    return tmp_value.bitc.c12;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff13 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff13'. */
void MH_TD_set_DispYUV2RGBCoeff13(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff13'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff13(void);
/*! \brief Writes the bit group 'C13' of register 'TD_DispYUV2RGBCoeff13'. */
void MH_TD_set_DispYUV2RGBCoeff13_C13(MS_U16 data);
/*! \brief Reads the bit group 'C13' of register 'TD_DispYUV2RGBCoeff13'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff13_C13(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff13(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF13 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff13] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF13,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff13(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF13);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff13] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF13,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff13_C13(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF13_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF13;
    d.bitc.c13 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF13 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff13_C13] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF13,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff13_C13(void)
{
    MH_TD_DISPYUV2RGBCOEFF13_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF13);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff13_C13] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF13,value);
    #endif
    return tmp_value.bitc.c13;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff20 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff20'. */
void MH_TD_set_DispYUV2RGBCoeff20(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff20'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff20(void);
/*! \brief Writes the bit group 'C20' of register 'TD_DispYUV2RGBCoeff20'. */
void MH_TD_set_DispYUV2RGBCoeff20_C20(MS_U16 data);
/*! \brief Reads the bit group 'C20' of register 'TD_DispYUV2RGBCoeff20'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff20_C20(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff20(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF20 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff20] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF20,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff20(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF20);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff20] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF20,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff20_C20(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF20_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF20;
    d.bitc.c20 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF20 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff20_C20] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF20,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff20_C20(void)
{
    MH_TD_DISPYUV2RGBCOEFF20_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF20);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff20_C20] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF20,value);
    #endif
    return tmp_value.bitc.c20;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff21 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff21'. */
void MH_TD_set_DispYUV2RGBCoeff21(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff21'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff21(void);
/*! \brief Writes the bit group 'C21' of register 'TD_DispYUV2RGBCoeff21'. */
void MH_TD_set_DispYUV2RGBCoeff21_C21(MS_U16 data);
/*! \brief Reads the bit group 'C21' of register 'TD_DispYUV2RGBCoeff21'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff21_C21(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff21(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF21 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff21] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF21,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff21(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF21);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff21] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF21,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff21_C21(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF21_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF21;
    d.bitc.c21 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF21 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff21_C21] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF21,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff21_C21(void)
{
    MH_TD_DISPYUV2RGBCOEFF21_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF21);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff21_C21] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF21,value);
    #endif
    return tmp_value.bitc.c21;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff22 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff22'. */
void MH_TD_set_DispYUV2RGBCoeff22(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff22'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff22(void);
/*! \brief Writes the bit group 'C22' of register 'TD_DispYUV2RGBCoeff22'. */
void MH_TD_set_DispYUV2RGBCoeff22_C22(MS_U16 data);
/*! \brief Reads the bit group 'C22' of register 'TD_DispYUV2RGBCoeff22'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff22_C22(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff22(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF22 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff22] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF22,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff22(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF22);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff22] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF22,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff22_C22(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF22_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF22;
    d.bitc.c22 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF22 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff22_C22] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF22,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff22_C22(void)
{
    MH_TD_DISPYUV2RGBCOEFF22_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF22);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff22_C22] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF22,value);
    #endif
    return tmp_value.bitc.c22;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispYUV2RGBCoeff23 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispYUV2RGBCoeff23'. */
void MH_TD_set_DispYUV2RGBCoeff23(MS_U32 data);
/*! \brief Reads the register 'TD_DispYUV2RGBCoeff23'. */
MS_U32  MH_TD_get_DispYUV2RGBCoeff23(void);
/*! \brief Writes the bit group 'C23' of register 'TD_DispYUV2RGBCoeff23'. */
void MH_TD_set_DispYUV2RGBCoeff23_C23(MS_U16 data);
/*! \brief Reads the bit group 'C23' of register 'TD_DispYUV2RGBCoeff23'. */
MS_U16  MH_TD_get_DispYUV2RGBCoeff23_C23(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff23(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF23 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff23] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF23,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispYUV2RGBCoeff23(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF23);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff23] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF23,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispYUV2RGBCoeff23_C23(MS_U16 data)
{
    MH_TD_DISPYUV2RGBCOEFF23_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF23;
    d.bitc.c23 = data;
    *(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF23 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispYUV2RGBCoeff23_C23] <-- 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF23,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_DispYUV2RGBCoeff23_C23(void)
{
    MH_TD_DISPYUV2RGBCOEFF23_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPYUV2RGBCOEFF23);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispYUV2RGBCoeff23_C23] --> 0x%08x\n",
                        REG_TD_DISPYUV2RGBCOEFF23,value);
    #endif
    return tmp_value.bitc.c23;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispMixAlp0 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispMixAlp0'. */
void MH_TD_set_DispMixAlp0(MS_U32 data);
/*! \brief Reads the register 'TD_DispMixAlp0'. */
MS_U32  MH_TD_get_DispMixAlp0(void);
/*! \brief Writes the bit group 'Layer0GlbAlp' of register 'TD_DispMixAlp0'. */
void MH_TD_set_DispMixAlp0_Layer0GlbAlp(MS_U8 data);
/*! \brief Reads the bit group 'Layer0GlbAlp' of register 'TD_DispMixAlp0'. */
MS_U8   MH_TD_get_DispMixAlp0_Layer0GlbAlp(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispMixAlp0(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPMIXALP0 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixAlp0] <-- 0x%08x\n",
                        REG_TD_DISPMIXALP0,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispMixAlp0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXALP0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixAlp0] --> 0x%08x\n",
                        REG_TD_DISPMIXALP0,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispMixAlp0_Layer0GlbAlp(MS_U8 data)
{
    MH_TD_DISPMIXALP0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPMIXALP0;
    d.bitc.layer0glbalp = data;
    *(volatile MS_U32 *)REG_TD_DISPMIXALP0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixAlp0_Layer0GlbAlp] <-- 0x%08x\n",
                        REG_TD_DISPMIXALP0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispMixAlp0_Layer0GlbAlp(void)
{
    MH_TD_DISPMIXALP0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXALP0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixAlp0_Layer0GlbAlp] --> 0x%08x\n",
                        REG_TD_DISPMIXALP0,value);
    #endif
    return tmp_value.bitc.layer0glbalp;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispMixAlp1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispMixAlp1'. */
void MH_TD_set_DispMixAlp1(MS_U32 data);
/*! \brief Reads the register 'TD_DispMixAlp1'. */
MS_U32  MH_TD_get_DispMixAlp1(void);
/*! \brief Writes the bit group 'Layer4GlbAlp' of register 'TD_DispMixAlp1'. */
void MH_TD_set_DispMixAlp1_Layer4GlbAlp(MS_U8 data);
/*! \brief Reads the bit group 'Layer4GlbAlp' of register 'TD_DispMixAlp1'. */
MS_U8   MH_TD_get_DispMixAlp1_Layer4GlbAlp(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispMixAlp1(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPMIXALP1 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixAlp1] <-- 0x%08x\n",
                        REG_TD_DISPMIXALP1,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispMixAlp1(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXALP1);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixAlp1] --> 0x%08x\n",
                        REG_TD_DISPMIXALP1,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispMixAlp1_Layer4GlbAlp(MS_U8 data)
{
    MH_TD_DISPMIXALP1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPMIXALP1;
    d.bitc.layer4glbalp = data;
    *(volatile MS_U32 *)REG_TD_DISPMIXALP1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixAlp1_Layer4GlbAlp] <-- 0x%08x\n",
                        REG_TD_DISPMIXALP1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispMixAlp1_Layer4GlbAlp(void)
{
    MH_TD_DISPMIXALP1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXALP1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixAlp1_Layer4GlbAlp] --> 0x%08x\n",
                        REG_TD_DISPMIXALP1,value);
    #endif
    return tmp_value.bitc.layer4glbalp;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispMixSel (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispMixSel'. */
void MH_TD_set_DispMixSel(MS_U32 data);
/*! \brief Reads the register 'TD_DispMixSel'. */
MS_U32  MH_TD_get_DispMixSel(void);
/*! \brief Writes the bit group 'Layer0Sel' of register 'TD_DispMixSel'. */
void MH_TD_set_DispMixSel_Layer0Sel(MS_U8 data);
/*! \brief Reads the bit group 'Layer0Sel' of register 'TD_DispMixSel'. */
MS_U8   MH_TD_get_DispMixSel_Layer0Sel(void);
/*! \brief Writes the bit group 'Layer1Sel' of register 'TD_DispMixSel'. */
void MH_TD_set_DispMixSel_Layer1Sel(MS_U8 data);
/*! \brief Reads the bit group 'Layer1Sel' of register 'TD_DispMixSel'. */
MS_U8   MH_TD_get_DispMixSel_Layer1Sel(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispMixSel(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPMIXSEL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixSel] <-- 0x%08x\n",
                        REG_TD_DISPMIXSEL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispMixSel(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXSEL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixSel] --> 0x%08x\n",
                        REG_TD_DISPMIXSEL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispMixSel_Layer0Sel(MS_U8 data)
{
    MH_TD_DISPMIXSEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPMIXSEL;
    d.bitc.layer0sel = data;
    *(volatile MS_U32 *)REG_TD_DISPMIXSEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixSel_Layer0Sel] <-- 0x%08x\n",
                        REG_TD_DISPMIXSEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispMixSel_Layer0Sel(void)
{
    MH_TD_DISPMIXSEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXSEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixSel_Layer0Sel] --> 0x%08x\n",
                        REG_TD_DISPMIXSEL,value);
    #endif
    return tmp_value.bitc.layer0sel;
}
MH_INLINE void MH_TD_set_DispMixSel_Layer1Sel(MS_U8 data)
{
    MH_TD_DISPMIXSEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPMIXSEL;
    d.bitc.layer1sel = data;
    *(volatile MS_U32 *)REG_TD_DISPMIXSEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispMixSel_Layer1Sel] <-- 0x%08x\n",
                        REG_TD_DISPMIXSEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispMixSel_Layer1Sel(void)
{
    MH_TD_DISPMIXSEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPMIXSEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispMixSel_Layer1Sel] --> 0x%08x\n",
                        REG_TD_DISPMIXSEL,value);
    #endif
    return tmp_value.bitc.layer1sel;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispBackGroud (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispBackGroud'. */
void MH_TD_set_DispBackGroud(MS_U32 data);
/*! \brief Reads the register 'TD_DispBackGroud'. */
MS_U32  MH_TD_get_DispBackGroud(void);
/*! \brief Writes the bit group 'Y' of register 'TD_DispBackGroud'. */
void MH_TD_set_DispBackGroud_Y(MS_U8 data);
/*! \brief Reads the bit group 'Y' of register 'TD_DispBackGroud'. */
MS_U8   MH_TD_get_DispBackGroud_Y(void);
/*! \brief Writes the bit group 'U' of register 'TD_DispBackGroud'. */
void MH_TD_set_DispBackGroud_U(MS_U8 data);
/*! \brief Reads the bit group 'U' of register 'TD_DispBackGroud'. */
MS_U8   MH_TD_get_DispBackGroud_U(void);
/*! \brief Writes the bit group 'V' of register 'TD_DispBackGroud'. */
void MH_TD_set_DispBackGroud_V(MS_U8 data);
/*! \brief Reads the bit group 'V' of register 'TD_DispBackGroud'. */
MS_U8   MH_TD_get_DispBackGroud_V(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispBackGroud(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPBACKGROUD = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispBackGroud] <-- 0x%08x\n",
                        REG_TD_DISPBACKGROUD,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispBackGroud(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPBACKGROUD);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispBackGroud] --> 0x%08x\n",
                        REG_TD_DISPBACKGROUD,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispBackGroud_Y(MS_U8 data)
{
    MH_TD_DISPBACKGROUD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPBACKGROUD;
    d.bitc.y = data;
    *(volatile MS_U32 *)REG_TD_DISPBACKGROUD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispBackGroud_Y] <-- 0x%08x\n",
                        REG_TD_DISPBACKGROUD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispBackGroud_Y(void)
{
    MH_TD_DISPBACKGROUD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPBACKGROUD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispBackGroud_Y] --> 0x%08x\n",
                        REG_TD_DISPBACKGROUD,value);
    #endif
    return tmp_value.bitc.y;
}
MH_INLINE void MH_TD_set_DispBackGroud_U(MS_U8 data)
{
    MH_TD_DISPBACKGROUD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPBACKGROUD;
    d.bitc.u = data;
    *(volatile MS_U32 *)REG_TD_DISPBACKGROUD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispBackGroud_U] <-- 0x%08x\n",
                        REG_TD_DISPBACKGROUD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispBackGroud_U(void)
{
    MH_TD_DISPBACKGROUD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPBACKGROUD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispBackGroud_U] --> 0x%08x\n",
                        REG_TD_DISPBACKGROUD,value);
    #endif
    return tmp_value.bitc.u;
}
MH_INLINE void MH_TD_set_DispBackGroud_V(MS_U8 data)
{
    MH_TD_DISPBACKGROUD_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPBACKGROUD;
    d.bitc.v = data;
    *(volatile MS_U32 *)REG_TD_DISPBACKGROUD = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispBackGroud_V] <-- 0x%08x\n",
                        REG_TD_DISPBACKGROUD,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispBackGroud_V(void)
{
    MH_TD_DISPBACKGROUD_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPBACKGROUD);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispBackGroud_V] --> 0x%08x\n",
                        REG_TD_DISPBACKGROUD,value);
    #endif
    return tmp_value.bitc.v;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispIRQ0 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispIRQ0'. */
void MH_TD_set_DispIRQ0(MS_U32 data);
/*! \brief Reads the register 'TD_DispIRQ0'. */
MS_U32  MH_TD_get_DispIRQ0(void);
/*! \brief Writes the bit group 'En' of register 'TD_DispIRQ0'. */
void MH_TD_set_DispIRQ0_En(MS_U8 data);
/*! \brief Reads the bit group 'En' of register 'TD_DispIRQ0'. */
MS_U8   MH_TD_get_DispIRQ0_En(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispIRQ0(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPIRQ0 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ0] <-- 0x%08x\n",
                        REG_TD_DISPIRQ0,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispIRQ0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ0] --> 0x%08x\n",
                        REG_TD_DISPIRQ0,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispIRQ0_En(MS_U8 data)
{
    MH_TD_DISPIRQ0_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ0;
    d.bitc.en = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ0 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ0_En] <-- 0x%08x\n",
                        REG_TD_DISPIRQ0,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ0_En(void)
{
    MH_TD_DISPIRQ0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ0_En] --> 0x%08x\n",
                        REG_TD_DISPIRQ0,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispIRQ1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispIRQ1'. */
void MH_TD_set_DispIRQ1(MS_U32 data);
/*! \brief Reads the register 'TD_DispIRQ1'. */
MS_U32  MH_TD_get_DispIRQ1(void);
/*! \brief Writes the bit group 'UnderrundCnt' of register 'TD_DispIRQ1'. */
void MH_TD_set_DispIRQ1_UnderrundCnt(MS_U32 data);
/*! \brief Reads the bit group 'UnderrundCnt' of register 'TD_DispIRQ1'. */
MS_U32  MH_TD_get_DispIRQ1_UnderrundCnt(void);
/*! \brief Writes the bit group 'En' of register 'TD_DispIRQ1'. */
void MH_TD_set_DispIRQ1_En(MS_U8 data);
/*! \brief Reads the bit group 'En' of register 'TD_DispIRQ1'. */
MS_U8   MH_TD_get_DispIRQ1_En(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispIRQ1(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPIRQ1 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ1] <-- 0x%08x\n",
                        REG_TD_DISPIRQ1,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispIRQ1(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ1);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ1] --> 0x%08x\n",
                        REG_TD_DISPIRQ1,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispIRQ1_UnderrundCnt(MS_U32 data)
{
    MH_TD_DISPIRQ1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ1;
    d.bitc.underrundcnt = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ1_UnderrundCnt] <-- 0x%08x\n",
                        REG_TD_DISPIRQ1,d.all,d.all);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispIRQ1_UnderrundCnt(void)
{
    MH_TD_DISPIRQ1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ1_UnderrundCnt] --> 0x%08x\n",
                        REG_TD_DISPIRQ1,value);
    #endif
    return tmp_value.bitc.underrundcnt;
}
MH_INLINE void MH_TD_set_DispIRQ1_En(MS_U8 data)
{
    MH_TD_DISPIRQ1_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ1;
    d.bitc.en = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ1 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ1_En] <-- 0x%08x\n",
                        REG_TD_DISPIRQ1,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ1_En(void)
{
    MH_TD_DISPIRQ1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ1_En] --> 0x%08x\n",
                        REG_TD_DISPIRQ1,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispIRQ2 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispIRQ2'. */
void MH_TD_set_DispIRQ2(MS_U32 data);
/*! \brief Reads the register 'TD_DispIRQ2'. */
MS_U32  MH_TD_get_DispIRQ2(void);
/*! \brief Writes the bit group 'En' of register 'TD_DispIRQ2'. */
void MH_TD_set_DispIRQ2_En(MS_U8 data);
/*! \brief Reads the bit group 'En' of register 'TD_DispIRQ2'. */
MS_U8   MH_TD_get_DispIRQ2_En(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispIRQ2(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPIRQ2 = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ2] <-- 0x%08x\n",
                        REG_TD_DISPIRQ2,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispIRQ2(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ2);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ2] --> 0x%08x\n",
                        REG_TD_DISPIRQ2,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispIRQ2_En(MS_U8 data)
{
    MH_TD_DISPIRQ2_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ2;
    d.bitc.en = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ2 = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ2_En] <-- 0x%08x\n",
                        REG_TD_DISPIRQ2,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ2_En(void)
{
    MH_TD_DISPIRQ2_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ2);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ2_En] --> 0x%08x\n",
                        REG_TD_DISPIRQ2,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_DispIRQ (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_DispIRQ'. */
void MH_TD_set_DispIRQ(MS_U32 data);
/*! \brief Reads the register 'TD_DispIRQ'. */
MS_U32  MH_TD_get_DispIRQ(void);
/*! \brief Writes the bit group 'IRQ0' of register 'TD_DispIRQ'. */
void MH_TD_set_DispIRQ_IRQ0(MS_U8 data);
/*! \brief Reads the bit group 'IRQ0' of register 'TD_DispIRQ'. */
MS_U8   MH_TD_get_DispIRQ_IRQ0(void);
/*! \brief Writes the bit group 'IRQ0Ctl' of register 'TD_DispIRQ'. */
void MH_TD_set_DispIRQ_IRQ0Ctl(MS_U8 data);
/*! \brief Reads the bit group 'IRQ0Ctl' of register 'TD_DispIRQ'. */
MS_U8   MH_TD_get_DispIRQ_IRQ0Ctl(void);
/*! \brief Writes the bit group 'IRQ1' of register 'TD_DispIRQ'. */
void MH_TD_set_DispIRQ_IRQ1(MS_U8 data);
/*! \brief Reads the bit group 'IRQ1' of register 'TD_DispIRQ'. */
MS_U8   MH_TD_get_DispIRQ_IRQ1(void);
/*! \brief Writes the bit group 'Underrun' of register 'TD_DispIRQ'. */
void MH_TD_set_DispIRQ_Underrun(MS_U8 data);
/*! \brief Reads the bit group 'Underrun' of register 'TD_DispIRQ'. */
MS_U8   MH_TD_get_DispIRQ_Underrun(void);
/*! \brief Writes the bit group 'AddrFlag' of register 'TD_DispIRQ'. */
void MH_TD_set_DispIRQ_AddrFlag(MS_U8 data);
/*! \brief Reads the bit group 'AddrFlag' of register 'TD_DispIRQ'. */
MS_U8   MH_TD_get_DispIRQ_AddrFlag(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_DispIRQ(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_DISPIRQ = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ] <-- 0x%08x\n",
                        REG_TD_DISPIRQ,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_DispIRQ(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ] --> 0x%08x\n",
                        REG_TD_DISPIRQ,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_DispIRQ_IRQ0(MS_U8 data)
{
    MH_TD_DISPIRQ_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ;
    d.bitc.irq0 = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ_IRQ0] <-- 0x%08x\n",
                        REG_TD_DISPIRQ,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ_IRQ0(void)
{
    MH_TD_DISPIRQ_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ_IRQ0] --> 0x%08x\n",
                        REG_TD_DISPIRQ,value);
    #endif
    return tmp_value.bitc.irq0;
}
MH_INLINE void MH_TD_set_DispIRQ_IRQ0Ctl(MS_U8 data)
{
    MH_TD_DISPIRQ_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ;
    d.bitc.irq0ctl = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ_IRQ0Ctl] <-- 0x%08x\n",
                        REG_TD_DISPIRQ,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ_IRQ0Ctl(void)
{
    MH_TD_DISPIRQ_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ_IRQ0Ctl] --> 0x%08x\n",
                        REG_TD_DISPIRQ,value);
    #endif
    return tmp_value.bitc.irq0ctl;
}
MH_INLINE void MH_TD_set_DispIRQ_IRQ1(MS_U8 data)
{
    MH_TD_DISPIRQ_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ;
    d.bitc.irq1 = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ_IRQ1] <-- 0x%08x\n",
                        REG_TD_DISPIRQ,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ_IRQ1(void)
{
    MH_TD_DISPIRQ_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ_IRQ1] --> 0x%08x\n",
                        REG_TD_DISPIRQ,value);
    #endif
    return tmp_value.bitc.irq1;
}
MH_INLINE void MH_TD_set_DispIRQ_Underrun(MS_U8 data)
{
    MH_TD_DISPIRQ_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ;
    d.bitc.underrun = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ_Underrun] <-- 0x%08x\n",
                        REG_TD_DISPIRQ,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ_Underrun(void)
{
    MH_TD_DISPIRQ_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ_Underrun] --> 0x%08x\n",
                        REG_TD_DISPIRQ,value);
    #endif
    return tmp_value.bitc.underrun;
}
MH_INLINE void MH_TD_set_DispIRQ_AddrFlag(MS_U8 data)
{
    MH_TD_DISPIRQ_S d;
    d.all = *(volatile MS_U32 *)REG_TD_DISPIRQ;
    d.bitc.addrflag = data;
    *(volatile MS_U32 *)REG_TD_DISPIRQ = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_DispIRQ_AddrFlag] <-- 0x%08x\n",
                        REG_TD_DISPIRQ,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_DispIRQ_AddrFlag(void)
{
    MH_TD_DISPIRQ_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_DISPIRQ);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_DispIRQ_AddrFlag] --> 0x%08x\n",
                        REG_TD_DISPIRQ,value);
    #endif
    return tmp_value.bitc.addrflag;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbDma (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbDma'. */
void MH_TD_set_WbDma(MS_U32 data);
/*! \brief Reads the register 'TD_WbDma'. */
MS_U32  MH_TD_get_WbDma(void);
/*! \brief Writes the bit group 'En' of register 'TD_WbDma'. */
void MH_TD_set_WbDma_En(MS_U8 data);
/*! \brief Reads the bit group 'En' of register 'TD_WbDma'. */
MS_U8   MH_TD_get_WbDma_En(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbDma(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBDMA = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbDma] <-- 0x%08x\n",
                        REG_TD_WBDMA,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbDma(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBDMA);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbDma] --> 0x%08x\n",
                        REG_TD_WBDMA,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbDma_En(MS_U8 data)
{
    MH_TD_WBDMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBDMA;
    d.bitc.en = data;
    *(volatile MS_U32 *)REG_TD_WBDMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbDma_En] <-- 0x%08x\n",
                        REG_TD_WBDMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbDma_En(void)
{
    MH_TD_WBDMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBDMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbDma_En] --> 0x%08x\n",
                        REG_TD_WBDMA,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbMode (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbMode'. */
void MH_TD_set_WbMode(MS_U32 data);
/*! \brief Reads the register 'TD_WbMode'. */
MS_U32  MH_TD_get_WbMode(void);
/*! \brief Writes the bit group 'Input' of register 'TD_WbMode'. */
void MH_TD_set_WbMode_Input(MS_U8 data);
/*! \brief Reads the bit group 'Input' of register 'TD_WbMode'. */
MS_U8   MH_TD_get_WbMode_Input(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbMode(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBMODE = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbMode] <-- 0x%08x\n",
                        REG_TD_WBMODE,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbMode(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBMODE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbMode] --> 0x%08x\n",
                        REG_TD_WBMODE,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbMode_Input(MS_U8 data)
{
    MH_TD_WBMODE_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBMODE;
    d.bitc.input = data;
    *(volatile MS_U32 *)REG_TD_WBMODE = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbMode_Input] <-- 0x%08x\n",
                        REG_TD_WBMODE,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbMode_Input(void)
{
    MH_TD_WBMODE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBMODE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbMode_Input] --> 0x%08x\n",
                        REG_TD_WBMODE,value);
    #endif
    return tmp_value.bitc.input;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbPixel (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbPixel'. */
void MH_TD_set_WbPixel(MS_U32 data);
/*! \brief Reads the register 'TD_WbPixel'. */
MS_U32  MH_TD_get_WbPixel(void);
/*! \brief Writes the bit group 'FormatSel' of register 'TD_WbPixel'. */
void MH_TD_set_WbPixel_FormatSel(MS_U8 data);
/*! \brief Reads the bit group 'FormatSel' of register 'TD_WbPixel'. */
MS_U8   MH_TD_get_WbPixel_FormatSel(void);
/*! \brief Writes the bit group 'InputFormat' of register 'TD_WbPixel'. */
void MH_TD_set_WbPixel_InputFormat(MS_U8 data);
/*! \brief Reads the bit group 'InputFormat' of register 'TD_WbPixel'. */
MS_U8   MH_TD_get_WbPixel_InputFormat(void);
/*! \brief Writes the bit group 'OutputFormat' of register 'TD_WbPixel'. */
void MH_TD_set_WbPixel_OutputFormat(MS_U8 data);
/*! \brief Reads the bit group 'OutputFormat' of register 'TD_WbPixel'. */
MS_U8   MH_TD_get_WbPixel_OutputFormat(void);
/*! \brief Writes the bit group 'pixelorder422' of register 'TD_WbPixel'. */
void MH_TD_set_WbPixel_422PixelOrder(MS_U8 data);
/*! \brief Reads the bit group 'pixelorder422' of register 'TD_WbPixel'. */
MS_U8   MH_TD_get_WbPixel_422PixelOrder(void);
/*! \brief Writes the bit group 'RGBPixelWidth' of register 'TD_WbPixel'. */
void MH_TD_set_WbPixel_RGBPixelWidth(MS_U8 data);
/*! \brief Reads the bit group 'RGBPixelWidth' of register 'TD_WbPixel'. */
MS_U8   MH_TD_get_WbPixel_RGBPixelWidth(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbPixel(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBPIXEL = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbPixel] <-- 0x%08x\n",
                        REG_TD_WBPIXEL,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbPixel(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBPIXEL);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbPixel] --> 0x%08x\n",
                        REG_TD_WBPIXEL,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbPixel_FormatSel(MS_U8 data)
{
    MH_TD_WBPIXEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBPIXEL;
    d.bitc.formatsel = data;
    *(volatile MS_U32 *)REG_TD_WBPIXEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbPixel_FormatSel] <-- 0x%08x\n",
                        REG_TD_WBPIXEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbPixel_FormatSel(void)
{
    MH_TD_WBPIXEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBPIXEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbPixel_FormatSel] --> 0x%08x\n",
                        REG_TD_WBPIXEL,value);
    #endif
    return tmp_value.bitc.formatsel;
}
MH_INLINE void MH_TD_set_WbPixel_InputFormat(MS_U8 data)
{
    MH_TD_WBPIXEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBPIXEL;
    d.bitc.inputformat = data;
    *(volatile MS_U32 *)REG_TD_WBPIXEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbPixel_InputFormat] <-- 0x%08x\n",
                        REG_TD_WBPIXEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbPixel_InputFormat(void)
{
    MH_TD_WBPIXEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBPIXEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbPixel_InputFormat] --> 0x%08x\n",
                        REG_TD_WBPIXEL,value);
    #endif
    return tmp_value.bitc.inputformat;
}
MH_INLINE void MH_TD_set_WbPixel_OutputFormat(MS_U8 data)
{
    MH_TD_WBPIXEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBPIXEL;
    d.bitc.outputformat = data;
    *(volatile MS_U32 *)REG_TD_WBPIXEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbPixel_OutputFormat] <-- 0x%08x\n",
                        REG_TD_WBPIXEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbPixel_OutputFormat(void)
{
    MH_TD_WBPIXEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBPIXEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbPixel_OutputFormat] --> 0x%08x\n",
                        REG_TD_WBPIXEL,value);
    #endif
    return tmp_value.bitc.outputformat;
}
MH_INLINE void MH_TD_set_WbPixel_422PixelOrder(MS_U8 data)
{
    MH_TD_WBPIXEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBPIXEL;
    d.bitc.pixelorder422 = data;
    *(volatile MS_U32 *)REG_TD_WBPIXEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbPixel_422PixelOrder] <-- 0x%08x\n",
                        REG_TD_WBPIXEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbPixel_422PixelOrder(void)
{
    MH_TD_WBPIXEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBPIXEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbPixel_422PixelOrder] --> 0x%08x\n",
                        REG_TD_WBPIXEL,value);
    #endif
    return tmp_value.bitc.pixelorder422;
}
MH_INLINE void MH_TD_set_WbPixel_RGBPixelWidth(MS_U8 data)
{
    MH_TD_WBPIXEL_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBPIXEL;
    d.bitc.rgbpixelwidth = data;
    *(volatile MS_U32 *)REG_TD_WBPIXEL = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbPixel_RGBPixelWidth] <-- 0x%08x\n",
                        REG_TD_WBPIXEL,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbPixel_RGBPixelWidth(void)
{
    MH_TD_WBPIXEL_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBPIXEL);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbPixel_RGBPixelWidth] --> 0x%08x\n",
                        REG_TD_WBPIXEL,value);
    #endif
    return tmp_value.bitc.rgbpixelwidth;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbBaseAddr0Y (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbBaseAddr0Y'. */
void MH_TD_set_WbBaseAddr0Y(MS_U32 data);
/*! \brief Reads the register 'TD_WbBaseAddr0Y'. */
MS_U32  MH_TD_get_WbBaseAddr0Y(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbBaseAddr0Y(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBBASEADDR0Y = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbBaseAddr0Y] <-- 0x%08x\n",
                        REG_TD_WBBASEADDR0Y,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbBaseAddr0Y(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBBASEADDR0Y);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbBaseAddr0Y] --> 0x%08x\n",
                        REG_TD_WBBASEADDR0Y,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbBaseAddr1Y (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbBaseAddr1Y'. */
void MH_TD_set_WbBaseAddr1Y(MS_U32 data);
/*! \brief Reads the register 'TD_WbBaseAddr1Y'. */
MS_U32  MH_TD_get_WbBaseAddr1Y(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbBaseAddr1Y(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBBASEADDR1Y = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbBaseAddr1Y] <-- 0x%08x\n",
                        REG_TD_WBBASEADDR1Y,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbBaseAddr1Y(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBBASEADDR1Y);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbBaseAddr1Y] --> 0x%08x\n",
                        REG_TD_WBBASEADDR1Y,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbBaseAddr0UV (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbBaseAddr0UV'. */
void MH_TD_set_WbBaseAddr0UV(MS_U32 data);
/*! \brief Reads the register 'TD_WbBaseAddr0UV'. */
MS_U32  MH_TD_get_WbBaseAddr0UV(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbBaseAddr0UV(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBBASEADDR0UV = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbBaseAddr0UV] <-- 0x%08x\n",
                        REG_TD_WBBASEADDR0UV,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbBaseAddr0UV(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBBASEADDR0UV);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbBaseAddr0UV] --> 0x%08x\n",
                        REG_TD_WBBASEADDR0UV,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbBaseAddr1UV (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbBaseAddr1UV'. */
void MH_TD_set_WbBaseAddr1UV(MS_U32 data);
/*! \brief Reads the register 'TD_WbBaseAddr1UV'. */
MS_U32  MH_TD_get_WbBaseAddr1UV(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbBaseAddr1UV(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBBASEADDR1UV = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbBaseAddr1UV] <-- 0x%08x\n",
                        REG_TD_WBBASEADDR1UV,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbBaseAddr1UV(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBBASEADDR1UV);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbBaseAddr1UV] --> 0x%08x\n",
                        REG_TD_WBBASEADDR1UV,value);
    #endif
    return value;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbOutY (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbOutY'. */
void MH_TD_set_WbOutY(MS_U32 data);
/*! \brief Reads the register 'TD_WbOutY'. */
MS_U32  MH_TD_get_WbOutY(void);
/*! \brief Writes the bit group 'Hstride' of register 'TD_WbOutY'. */
void MH_TD_set_WbOutY_Hstride(MS_U16 data);
/*! \brief Reads the bit group 'Hstride' of register 'TD_WbOutY'. */
MS_U16  MH_TD_get_WbOutY_Hstride(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbOutY(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBOUTY = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbOutY] <-- 0x%08x\n",
                        REG_TD_WBOUTY,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbOutY(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBOUTY);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbOutY] --> 0x%08x\n",
                        REG_TD_WBOUTY,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbOutY_Hstride(MS_U16 data)
{
    MH_TD_WBOUTY_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBOUTY;
    d.bitc.hstride = data;
    *(volatile MS_U32 *)REG_TD_WBOUTY = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbOutY_Hstride] <-- 0x%08x\n",
                        REG_TD_WBOUTY,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_WbOutY_Hstride(void)
{
    MH_TD_WBOUTY_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBOUTY);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbOutY_Hstride] --> 0x%08x\n",
                        REG_TD_WBOUTY,value);
    #endif
    return tmp_value.bitc.hstride;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbOutUV (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbOutUV'. */
void MH_TD_set_WbOutUV(MS_U32 data);
/*! \brief Reads the register 'TD_WbOutUV'. */
MS_U32  MH_TD_get_WbOutUV(void);
/*! \brief Writes the bit group 'Hstride' of register 'TD_WbOutUV'. */
void MH_TD_set_WbOutUV_Hstride(MS_U16 data);
/*! \brief Reads the bit group 'Hstride' of register 'TD_WbOutUV'. */
MS_U16  MH_TD_get_WbOutUV_Hstride(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbOutUV(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBOUTUV = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbOutUV] <-- 0x%08x\n",
                        REG_TD_WBOUTUV,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbOutUV(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBOUTUV);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbOutUV] --> 0x%08x\n",
                        REG_TD_WBOUTUV,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbOutUV_Hstride(MS_U16 data)
{
    MH_TD_WBOUTUV_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBOUTUV;
    d.bitc.hstride = data;
    *(volatile MS_U32 *)REG_TD_WBOUTUV = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbOutUV_Hstride] <-- 0x%08x\n",
                        REG_TD_WBOUTUV,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_WbOutUV_Hstride(void)
{
    MH_TD_WBOUTUV_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBOUTUV);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbOutUV_Hstride] --> 0x%08x\n",
                        REG_TD_WBOUTUV,value);
    #endif
    return tmp_value.bitc.hstride;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbLoop (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbLoop'. */
void MH_TD_set_WbLoop(MS_U32 data);
/*! \brief Reads the register 'TD_WbLoop'. */
MS_U32  MH_TD_get_WbLoop(void);
/*! \brief Writes the bit group 'BufferSize' of register 'TD_WbLoop'. */
void MH_TD_set_WbLoop_BufferSize(MS_U16 data);
/*! \brief Reads the bit group 'BufferSize' of register 'TD_WbLoop'. */
MS_U16  MH_TD_get_WbLoop_BufferSize(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbLoop(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBLOOP = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbLoop] <-- 0x%08x\n",
                        REG_TD_WBLOOP,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbLoop(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBLOOP);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbLoop] --> 0x%08x\n",
                        REG_TD_WBLOOP,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbLoop_BufferSize(MS_U16 data)
{
    MH_TD_WBLOOP_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBLOOP;
    d.bitc.buffersize = data;
    *(volatile MS_U32 *)REG_TD_WBLOOP = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbLoop_BufferSize] <-- 0x%08x\n",
                        REG_TD_WBLOOP,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_WbLoop_BufferSize(void)
{
    MH_TD_WBLOOP_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBLOOP);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbLoop_BufferSize] --> 0x%08x\n",
                        REG_TD_WBLOOP,value);
    #endif
    return tmp_value.bitc.buffersize;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbActiveV (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbActiveV'. */
void MH_TD_set_WbActiveV(MS_U32 data);
/*! \brief Reads the register 'TD_WbActiveV'. */
MS_U32  MH_TD_get_WbActiveV(void);
/*! \brief Writes the bit group 'size' of register 'TD_WbActiveV'. */
void MH_TD_set_WbActiveV_size(MS_U16 data);
/*! \brief Reads the bit group 'size' of register 'TD_WbActiveV'. */
MS_U16  MH_TD_get_WbActiveV_size(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbActiveV(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBACTIVEV = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbActiveV] <-- 0x%08x\n",
                        REG_TD_WBACTIVEV,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbActiveV(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBACTIVEV);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbActiveV] --> 0x%08x\n",
                        REG_TD_WBACTIVEV,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbActiveV_size(MS_U16 data)
{
    MH_TD_WBACTIVEV_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBACTIVEV;
    d.bitc.size = data;
    *(volatile MS_U32 *)REG_TD_WBACTIVEV = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbActiveV_size] <-- 0x%08x\n",
                        REG_TD_WBACTIVEV,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_WbActiveV_size(void)
{
    MH_TD_WBACTIVEV_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBACTIVEV);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbActiveV_size] --> 0x%08x\n",
                        REG_TD_WBACTIVEV,value);
    #endif
    return tmp_value.bitc.size;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbActiveH (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbActiveH'. */
void MH_TD_set_WbActiveH(MS_U32 data);
/*! \brief Reads the register 'TD_WbActiveH'. */
MS_U32  MH_TD_get_WbActiveH(void);
/*! \brief Writes the bit group 'size' of register 'TD_WbActiveH'. */
void MH_TD_set_WbActiveH_size(MS_U16 data);
/*! \brief Reads the bit group 'size' of register 'TD_WbActiveH'. */
MS_U16  MH_TD_get_WbActiveH_size(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbActiveH(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBACTIVEH = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbActiveH] <-- 0x%08x\n",
                        REG_TD_WBACTIVEH,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbActiveH(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBACTIVEH);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbActiveH] --> 0x%08x\n",
                        REG_TD_WBACTIVEH,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbActiveH_size(MS_U16 data)
{
    MH_TD_WBACTIVEH_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBACTIVEH;
    d.bitc.size = data;
    *(volatile MS_U32 *)REG_TD_WBACTIVEH = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbActiveH_size] <-- 0x%08x\n",
                        REG_TD_WBACTIVEH,d.all,d.all);
    #endif
}
MH_INLINE MS_U16  MH_TD_get_WbActiveH_size(void)
{
    MH_TD_WBACTIVEH_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBACTIVEH);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbActiveH_size] --> 0x%08x\n",
                        REG_TD_WBACTIVEH,value);
    #endif
    return tmp_value.bitc.size;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh1Dma (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh1Dma'. */
void MH_TD_set_WbCh1Dma(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh1Dma'. */
MS_U32  MH_TD_get_WbCh1Dma(void);
/*! \brief Writes the bit group 'OtNum' of register 'TD_WbCh1Dma'. */
void MH_TD_set_WbCh1Dma_OtNum(MS_U8 data);
/*! \brief Reads the bit group 'OtNum' of register 'TD_WbCh1Dma'. */
MS_U8   MH_TD_get_WbCh1Dma_OtNum(void);
/*! \brief Writes the bit group 'Blen' of register 'TD_WbCh1Dma'. */
void MH_TD_set_WbCh1Dma_Blen(MS_U8 data);
/*! \brief Reads the bit group 'Blen' of register 'TD_WbCh1Dma'. */
MS_U8   MH_TD_get_WbCh1Dma_Blen(void);
/*! \brief Writes the bit group 'ContinuousMode' of register 'TD_WbCh1Dma'. */
void MH_TD_set_WbCh1Dma_ContinuousMode(MS_U8 data);
/*! \brief Reads the bit group 'ContinuousMode' of register 'TD_WbCh1Dma'. */
MS_U8   MH_TD_get_WbCh1Dma_ContinuousMode(void);
/*! \brief Writes the bit group 'Swap' of register 'TD_WbCh1Dma'. */
void MH_TD_set_WbCh1Dma_Swap(MS_U8 data);
/*! \brief Reads the bit group 'Swap' of register 'TD_WbCh1Dma'. */
MS_U8   MH_TD_get_WbCh1Dma_Swap(void);
/*! \brief Writes the bit group 'ErrDetectEn' of register 'TD_WbCh1Dma'. */
void MH_TD_set_WbCh1Dma_ErrDetectEn(MS_U8 data);
/*! \brief Reads the bit group 'ErrDetectEn' of register 'TD_WbCh1Dma'. */
MS_U8   MH_TD_get_WbCh1Dma_ErrDetectEn(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh1Dma(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH1DMA = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Dma] <-- 0x%08x\n",
                        REG_TD_WBCH1DMA,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh1Dma(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1DMA);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Dma] --> 0x%08x\n",
                        REG_TD_WBCH1DMA,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh1Dma_OtNum(MS_U8 data)
{
    MH_TD_WBCH1DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1DMA;
    d.bitc.otnum = data;
    *(volatile MS_U32 *)REG_TD_WBCH1DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Dma_OtNum] <-- 0x%08x\n",
                        REG_TD_WBCH1DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Dma_OtNum(void)
{
    MH_TD_WBCH1DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Dma_OtNum] --> 0x%08x\n",
                        REG_TD_WBCH1DMA,value);
    #endif
    return tmp_value.bitc.otnum;
}
MH_INLINE void MH_TD_set_WbCh1Dma_Blen(MS_U8 data)
{
    MH_TD_WBCH1DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1DMA;
    d.bitc.blen = data;
    *(volatile MS_U32 *)REG_TD_WBCH1DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Dma_Blen] <-- 0x%08x\n",
                        REG_TD_WBCH1DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Dma_Blen(void)
{
    MH_TD_WBCH1DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Dma_Blen] --> 0x%08x\n",
                        REG_TD_WBCH1DMA,value);
    #endif
    return tmp_value.bitc.blen;
}
MH_INLINE void MH_TD_set_WbCh1Dma_ContinuousMode(MS_U8 data)
{
    MH_TD_WBCH1DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1DMA;
    d.bitc.continuousmode = data;
    *(volatile MS_U32 *)REG_TD_WBCH1DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Dma_ContinuousMode] <-- 0x%08x\n",
                        REG_TD_WBCH1DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Dma_ContinuousMode(void)
{
    MH_TD_WBCH1DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Dma_ContinuousMode] --> 0x%08x\n",
                        REG_TD_WBCH1DMA,value);
    #endif
    return tmp_value.bitc.continuousmode;
}
MH_INLINE void MH_TD_set_WbCh1Dma_Swap(MS_U8 data)
{
    MH_TD_WBCH1DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1DMA;
    d.bitc.swap = data;
    *(volatile MS_U32 *)REG_TD_WBCH1DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Dma_Swap] <-- 0x%08x\n",
                        REG_TD_WBCH1DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Dma_Swap(void)
{
    MH_TD_WBCH1DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Dma_Swap] --> 0x%08x\n",
                        REG_TD_WBCH1DMA,value);
    #endif
    return tmp_value.bitc.swap;
}
MH_INLINE void MH_TD_set_WbCh1Dma_ErrDetectEn(MS_U8 data)
{
    MH_TD_WBCH1DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1DMA;
    d.bitc.errdetecten = data;
    *(volatile MS_U32 *)REG_TD_WBCH1DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Dma_ErrDetectEn] <-- 0x%08x\n",
                        REG_TD_WBCH1DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Dma_ErrDetectEn(void)
{
    MH_TD_WBCH1DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Dma_ErrDetectEn] --> 0x%08x\n",
                        REG_TD_WBCH1DMA,value);
    #endif
    return tmp_value.bitc.errdetecten;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh1ErrUnit (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh1ErrUnit'. */
void MH_TD_set_WbCh1ErrUnit(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh1ErrUnit'. */
MS_U32  MH_TD_get_WbCh1ErrUnit(void);
/*! \brief Writes the bit group 'Unit' of register 'TD_WbCh1ErrUnit'. */
void MH_TD_set_WbCh1ErrUnit_Unit(MS_U8 data);
/*! \brief Reads the bit group 'Unit' of register 'TD_WbCh1ErrUnit'. */
MS_U8   MH_TD_get_WbCh1ErrUnit_Unit(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh1ErrUnit(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH1ERRUNIT = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1ErrUnit] <-- 0x%08x\n",
                        REG_TD_WBCH1ERRUNIT,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh1ErrUnit(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1ERRUNIT);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1ErrUnit] --> 0x%08x\n",
                        REG_TD_WBCH1ERRUNIT,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh1ErrUnit_Unit(MS_U8 data)
{
    MH_TD_WBCH1ERRUNIT_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1ERRUNIT;
    d.bitc.unit = data;
    *(volatile MS_U32 *)REG_TD_WBCH1ERRUNIT = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1ErrUnit_Unit] <-- 0x%08x\n",
                        REG_TD_WBCH1ERRUNIT,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1ErrUnit_Unit(void)
{
    MH_TD_WBCH1ERRUNIT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1ERRUNIT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1ErrUnit_Unit] --> 0x%08x\n",
                        REG_TD_WBCH1ERRUNIT,value);
    #endif
    return tmp_value.bitc.unit;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh1ErrTh (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh1ErrTh'. */
void MH_TD_set_WbCh1ErrTh(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh1ErrTh'. */
MS_U32  MH_TD_get_WbCh1ErrTh(void);
/*! \brief Writes the bit group 'threshold' of register 'TD_WbCh1ErrTh'. */
void MH_TD_set_WbCh1ErrTh_threshold(MS_U8 data);
/*! \brief Reads the bit group 'threshold' of register 'TD_WbCh1ErrTh'. */
MS_U8   MH_TD_get_WbCh1ErrTh_threshold(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh1ErrTh(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH1ERRTH = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1ErrTh] <-- 0x%08x\n",
                        REG_TD_WBCH1ERRTH,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh1ErrTh(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1ERRTH);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1ErrTh] --> 0x%08x\n",
                        REG_TD_WBCH1ERRTH,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh1ErrTh_threshold(MS_U8 data)
{
    MH_TD_WBCH1ERRTH_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1ERRTH;
    d.bitc.threshold = data;
    *(volatile MS_U32 *)REG_TD_WBCH1ERRTH = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1ErrTh_threshold] <-- 0x%08x\n",
                        REG_TD_WBCH1ERRTH,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1ErrTh_threshold(void)
{
    MH_TD_WBCH1ERRTH_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1ERRTH);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1ErrTh_threshold] --> 0x%08x\n",
                        REG_TD_WBCH1ERRTH,value);
    #endif
    return tmp_value.bitc.threshold;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh1Info (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh1Info'. */
void MH_TD_set_WbCh1Info(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh1Info'. */
MS_U32  MH_TD_get_WbCh1Info(void);
/*! \brief Writes the bit group 'FrmCntClear' of register 'TD_WbCh1Info'. */
void MH_TD_set_WbCh1Info_FrmCntClear(MS_U8 data);
/*! \brief Reads the bit group 'FrmCntClear' of register 'TD_WbCh1Info'. */
MS_U8   MH_TD_get_WbCh1Info_FrmCntClear(void);
/*! \brief Writes the bit group 'FifoErrClear' of register 'TD_WbCh1Info'. */
void MH_TD_set_WbCh1Info_FifoErrClear(MS_U8 data);
/*! \brief Reads the bit group 'FifoErrClear' of register 'TD_WbCh1Info'. */
MS_U8   MH_TD_get_WbCh1Info_FifoErrClear(void);
/*! \brief Writes the bit group 'MaxBW' of register 'TD_WbCh1Info'. */
void MH_TD_set_WbCh1Info_MaxBW(MS_U8 data);
/*! \brief Reads the bit group 'MaxBW' of register 'TD_WbCh1Info'. */
MS_U8   MH_TD_get_WbCh1Info_MaxBW(void);
/*! \brief Writes the bit group 'TotalBW' of register 'TD_WbCh1Info'. */
void MH_TD_set_WbCh1Info_TotalBW(MS_U8 data);
/*! \brief Reads the bit group 'TotalBW' of register 'TD_WbCh1Info'. */
MS_U8   MH_TD_get_WbCh1Info_TotalBW(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh1Info(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH1INFO = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Info] <-- 0x%08x\n",
                        REG_TD_WBCH1INFO,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh1Info(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1INFO);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Info] --> 0x%08x\n",
                        REG_TD_WBCH1INFO,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh1Info_FrmCntClear(MS_U8 data)
{
    MH_TD_WBCH1INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1INFO;
    d.bitc.frmcntclear = data;
    *(volatile MS_U32 *)REG_TD_WBCH1INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Info_FrmCntClear] <-- 0x%08x\n",
                        REG_TD_WBCH1INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Info_FrmCntClear(void)
{
    MH_TD_WBCH1INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Info_FrmCntClear] --> 0x%08x\n",
                        REG_TD_WBCH1INFO,value);
    #endif
    return tmp_value.bitc.frmcntclear;
}
MH_INLINE void MH_TD_set_WbCh1Info_FifoErrClear(MS_U8 data)
{
    MH_TD_WBCH1INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1INFO;
    d.bitc.fifoerrclear = data;
    *(volatile MS_U32 *)REG_TD_WBCH1INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Info_FifoErrClear] <-- 0x%08x\n",
                        REG_TD_WBCH1INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Info_FifoErrClear(void)
{
    MH_TD_WBCH1INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Info_FifoErrClear] --> 0x%08x\n",
                        REG_TD_WBCH1INFO,value);
    #endif
    return tmp_value.bitc.fifoerrclear;
}
MH_INLINE void MH_TD_set_WbCh1Info_MaxBW(MS_U8 data)
{
    MH_TD_WBCH1INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1INFO;
    d.bitc.maxbw = data;
    *(volatile MS_U32 *)REG_TD_WBCH1INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Info_MaxBW] <-- 0x%08x\n",
                        REG_TD_WBCH1INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Info_MaxBW(void)
{
    MH_TD_WBCH1INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Info_MaxBW] --> 0x%08x\n",
                        REG_TD_WBCH1INFO,value);
    #endif
    return tmp_value.bitc.maxbw;
}
MH_INLINE void MH_TD_set_WbCh1Info_TotalBW(MS_U8 data)
{
    MH_TD_WBCH1INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1INFO;
    d.bitc.totalbw = data;
    *(volatile MS_U32 *)REG_TD_WBCH1INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Info_TotalBW] <-- 0x%08x\n",
                        REG_TD_WBCH1INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Info_TotalBW(void)
{
    MH_TD_WBCH1INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Info_TotalBW] --> 0x%08x\n",
                        REG_TD_WBCH1INFO,value);
    #endif
    return tmp_value.bitc.totalbw;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh1Rst (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh1Rst'. */
void MH_TD_set_WbCh1Rst(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh1Rst'. */
MS_U32  MH_TD_get_WbCh1Rst(void);
/*! \brief Writes the bit group 'request' of register 'TD_WbCh1Rst'. */
void MH_TD_set_WbCh1Rst_request(MS_U8 data);
/*! \brief Reads the bit group 'request' of register 'TD_WbCh1Rst'. */
MS_U8   MH_TD_get_WbCh1Rst_request(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh1Rst(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH1RST = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Rst] <-- 0x%08x\n",
                        REG_TD_WBCH1RST,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh1Rst(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1RST);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Rst] --> 0x%08x\n",
                        REG_TD_WBCH1RST,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh1Rst_request(MS_U8 data)
{
    MH_TD_WBCH1RST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH1RST;
    d.bitc.request = data;
    *(volatile MS_U32 *)REG_TD_WBCH1RST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh1Rst_request] <-- 0x%08x\n",
                        REG_TD_WBCH1RST,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh1Rst_request(void)
{
    MH_TD_WBCH1RST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH1RST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh1Rst_request] --> 0x%08x\n",
                        REG_TD_WBCH1RST,value);
    #endif
    return tmp_value.bitc.request;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh2Dma (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh2Dma'. */
void MH_TD_set_WbCh2Dma(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh2Dma'. */
MS_U32  MH_TD_get_WbCh2Dma(void);
/*! \brief Writes the bit group 'OtNum' of register 'TD_WbCh2Dma'. */
void MH_TD_set_WbCh2Dma_OtNum(MS_U8 data);
/*! \brief Reads the bit group 'OtNum' of register 'TD_WbCh2Dma'. */
MS_U8   MH_TD_get_WbCh2Dma_OtNum(void);
/*! \brief Writes the bit group 'Blen' of register 'TD_WbCh2Dma'. */
void MH_TD_set_WbCh2Dma_Blen(MS_U8 data);
/*! \brief Reads the bit group 'Blen' of register 'TD_WbCh2Dma'. */
MS_U8   MH_TD_get_WbCh2Dma_Blen(void);
/*! \brief Writes the bit group 'ContinuousMode' of register 'TD_WbCh2Dma'. */
void MH_TD_set_WbCh2Dma_ContinuousMode(MS_U8 data);
/*! \brief Reads the bit group 'ContinuousMode' of register 'TD_WbCh2Dma'. */
MS_U8   MH_TD_get_WbCh2Dma_ContinuousMode(void);
/*! \brief Writes the bit group 'Swap' of register 'TD_WbCh2Dma'. */
void MH_TD_set_WbCh2Dma_Swap(MS_U8 data);
/*! \brief Reads the bit group 'Swap' of register 'TD_WbCh2Dma'. */
MS_U8   MH_TD_get_WbCh2Dma_Swap(void);
/*! \brief Writes the bit group 'ErrDetectEn' of register 'TD_WbCh2Dma'. */
void MH_TD_set_WbCh2Dma_ErrDetectEn(MS_U8 data);
/*! \brief Reads the bit group 'ErrDetectEn' of register 'TD_WbCh2Dma'. */
MS_U8   MH_TD_get_WbCh2Dma_ErrDetectEn(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh2Dma(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH2DMA = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Dma] <-- 0x%08x\n",
                        REG_TD_WBCH2DMA,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh2Dma(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2DMA);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Dma] --> 0x%08x\n",
                        REG_TD_WBCH2DMA,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh2Dma_OtNum(MS_U8 data)
{
    MH_TD_WBCH2DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2DMA;
    d.bitc.otnum = data;
    *(volatile MS_U32 *)REG_TD_WBCH2DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Dma_OtNum] <-- 0x%08x\n",
                        REG_TD_WBCH2DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Dma_OtNum(void)
{
    MH_TD_WBCH2DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Dma_OtNum] --> 0x%08x\n",
                        REG_TD_WBCH2DMA,value);
    #endif
    return tmp_value.bitc.otnum;
}
MH_INLINE void MH_TD_set_WbCh2Dma_Blen(MS_U8 data)
{
    MH_TD_WBCH2DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2DMA;
    d.bitc.blen = data;
    *(volatile MS_U32 *)REG_TD_WBCH2DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Dma_Blen] <-- 0x%08x\n",
                        REG_TD_WBCH2DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Dma_Blen(void)
{
    MH_TD_WBCH2DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Dma_Blen] --> 0x%08x\n",
                        REG_TD_WBCH2DMA,value);
    #endif
    return tmp_value.bitc.blen;
}
MH_INLINE void MH_TD_set_WbCh2Dma_ContinuousMode(MS_U8 data)
{
    MH_TD_WBCH2DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2DMA;
    d.bitc.continuousmode = data;
    *(volatile MS_U32 *)REG_TD_WBCH2DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Dma_ContinuousMode] <-- 0x%08x\n",
                        REG_TD_WBCH2DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Dma_ContinuousMode(void)
{
    MH_TD_WBCH2DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Dma_ContinuousMode] --> 0x%08x\n",
                        REG_TD_WBCH2DMA,value);
    #endif
    return tmp_value.bitc.continuousmode;
}
MH_INLINE void MH_TD_set_WbCh2Dma_Swap(MS_U8 data)
{
    MH_TD_WBCH2DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2DMA;
    d.bitc.swap = data;
    *(volatile MS_U32 *)REG_TD_WBCH2DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Dma_Swap] <-- 0x%08x\n",
                        REG_TD_WBCH2DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Dma_Swap(void)
{
    MH_TD_WBCH2DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Dma_Swap] --> 0x%08x\n",
                        REG_TD_WBCH2DMA,value);
    #endif
    return tmp_value.bitc.swap;
}
MH_INLINE void MH_TD_set_WbCh2Dma_ErrDetectEn(MS_U8 data)
{
    MH_TD_WBCH2DMA_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2DMA;
    d.bitc.errdetecten = data;
    *(volatile MS_U32 *)REG_TD_WBCH2DMA = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Dma_ErrDetectEn] <-- 0x%08x\n",
                        REG_TD_WBCH2DMA,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Dma_ErrDetectEn(void)
{
    MH_TD_WBCH2DMA_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2DMA);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Dma_ErrDetectEn] --> 0x%08x\n",
                        REG_TD_WBCH2DMA,value);
    #endif
    return tmp_value.bitc.errdetecten;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh2ErrUnit (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh2ErrUnit'. */
void MH_TD_set_WbCh2ErrUnit(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh2ErrUnit'. */
MS_U32  MH_TD_get_WbCh2ErrUnit(void);
/*! \brief Writes the bit group 'Unit' of register 'TD_WbCh2ErrUnit'. */
void MH_TD_set_WbCh2ErrUnit_Unit(MS_U8 data);
/*! \brief Reads the bit group 'Unit' of register 'TD_WbCh2ErrUnit'. */
MS_U8   MH_TD_get_WbCh2ErrUnit_Unit(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh2ErrUnit(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH2ERRUNIT = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2ErrUnit] <-- 0x%08x\n",
                        REG_TD_WBCH2ERRUNIT,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh2ErrUnit(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2ERRUNIT);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2ErrUnit] --> 0x%08x\n",
                        REG_TD_WBCH2ERRUNIT,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh2ErrUnit_Unit(MS_U8 data)
{
    MH_TD_WBCH2ERRUNIT_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2ERRUNIT;
    d.bitc.unit = data;
    *(volatile MS_U32 *)REG_TD_WBCH2ERRUNIT = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2ErrUnit_Unit] <-- 0x%08x\n",
                        REG_TD_WBCH2ERRUNIT,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2ErrUnit_Unit(void)
{
    MH_TD_WBCH2ERRUNIT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2ERRUNIT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2ErrUnit_Unit] --> 0x%08x\n",
                        REG_TD_WBCH2ERRUNIT,value);
    #endif
    return tmp_value.bitc.unit;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh2ErrTh (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh2ErrTh'. */
void MH_TD_set_WbCh2ErrTh(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh2ErrTh'. */
MS_U32  MH_TD_get_WbCh2ErrTh(void);
/*! \brief Writes the bit group 'threshold' of register 'TD_WbCh2ErrTh'. */
void MH_TD_set_WbCh2ErrTh_threshold(MS_U8 data);
/*! \brief Reads the bit group 'threshold' of register 'TD_WbCh2ErrTh'. */
MS_U8   MH_TD_get_WbCh2ErrTh_threshold(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh2ErrTh(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH2ERRTH = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2ErrTh] <-- 0x%08x\n",
                        REG_TD_WBCH2ERRTH,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh2ErrTh(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2ERRTH);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2ErrTh] --> 0x%08x\n",
                        REG_TD_WBCH2ERRTH,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh2ErrTh_threshold(MS_U8 data)
{
    MH_TD_WBCH2ERRTH_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2ERRTH;
    d.bitc.threshold = data;
    *(volatile MS_U32 *)REG_TD_WBCH2ERRTH = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2ErrTh_threshold] <-- 0x%08x\n",
                        REG_TD_WBCH2ERRTH,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2ErrTh_threshold(void)
{
    MH_TD_WBCH2ERRTH_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2ERRTH);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2ErrTh_threshold] --> 0x%08x\n",
                        REG_TD_WBCH2ERRTH,value);
    #endif
    return tmp_value.bitc.threshold;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh2Info (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh2Info'. */
void MH_TD_set_WbCh2Info(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh2Info'. */
MS_U32  MH_TD_get_WbCh2Info(void);
/*! \brief Writes the bit group 'FrmCntClear' of register 'TD_WbCh2Info'. */
void MH_TD_set_WbCh2Info_FrmCntClear(MS_U8 data);
/*! \brief Reads the bit group 'FrmCntClear' of register 'TD_WbCh2Info'. */
MS_U8   MH_TD_get_WbCh2Info_FrmCntClear(void);
/*! \brief Writes the bit group 'FifoErrClear' of register 'TD_WbCh2Info'. */
void MH_TD_set_WbCh2Info_FifoErrClear(MS_U8 data);
/*! \brief Reads the bit group 'FifoErrClear' of register 'TD_WbCh2Info'. */
MS_U8   MH_TD_get_WbCh2Info_FifoErrClear(void);
/*! \brief Writes the bit group 'MaxBW' of register 'TD_WbCh2Info'. */
void MH_TD_set_WbCh2Info_MaxBW(MS_U8 data);
/*! \brief Reads the bit group 'MaxBW' of register 'TD_WbCh2Info'. */
MS_U8   MH_TD_get_WbCh2Info_MaxBW(void);
/*! \brief Writes the bit group 'TotalBW' of register 'TD_WbCh2Info'. */
void MH_TD_set_WbCh2Info_TotalBW(MS_U8 data);
/*! \brief Reads the bit group 'TotalBW' of register 'TD_WbCh2Info'. */
MS_U8   MH_TD_get_WbCh2Info_TotalBW(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh2Info(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH2INFO = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Info] <-- 0x%08x\n",
                        REG_TD_WBCH2INFO,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh2Info(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2INFO);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Info] --> 0x%08x\n",
                        REG_TD_WBCH2INFO,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh2Info_FrmCntClear(MS_U8 data)
{
    MH_TD_WBCH2INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2INFO;
    d.bitc.frmcntclear = data;
    *(volatile MS_U32 *)REG_TD_WBCH2INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Info_FrmCntClear] <-- 0x%08x\n",
                        REG_TD_WBCH2INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Info_FrmCntClear(void)
{
    MH_TD_WBCH2INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Info_FrmCntClear] --> 0x%08x\n",
                        REG_TD_WBCH2INFO,value);
    #endif
    return tmp_value.bitc.frmcntclear;
}
MH_INLINE void MH_TD_set_WbCh2Info_FifoErrClear(MS_U8 data)
{
    MH_TD_WBCH2INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2INFO;
    d.bitc.fifoerrclear = data;
    *(volatile MS_U32 *)REG_TD_WBCH2INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Info_FifoErrClear] <-- 0x%08x\n",
                        REG_TD_WBCH2INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Info_FifoErrClear(void)
{
    MH_TD_WBCH2INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Info_FifoErrClear] --> 0x%08x\n",
                        REG_TD_WBCH2INFO,value);
    #endif
    return tmp_value.bitc.fifoerrclear;
}
MH_INLINE void MH_TD_set_WbCh2Info_MaxBW(MS_U8 data)
{
    MH_TD_WBCH2INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2INFO;
    d.bitc.maxbw = data;
    *(volatile MS_U32 *)REG_TD_WBCH2INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Info_MaxBW] <-- 0x%08x\n",
                        REG_TD_WBCH2INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Info_MaxBW(void)
{
    MH_TD_WBCH2INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Info_MaxBW] --> 0x%08x\n",
                        REG_TD_WBCH2INFO,value);
    #endif
    return tmp_value.bitc.maxbw;
}
MH_INLINE void MH_TD_set_WbCh2Info_TotalBW(MS_U8 data)
{
    MH_TD_WBCH2INFO_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2INFO;
    d.bitc.totalbw = data;
    *(volatile MS_U32 *)REG_TD_WBCH2INFO = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Info_TotalBW] <-- 0x%08x\n",
                        REG_TD_WBCH2INFO,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Info_TotalBW(void)
{
    MH_TD_WBCH2INFO_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2INFO);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Info_TotalBW] --> 0x%08x\n",
                        REG_TD_WBCH2INFO,value);
    #endif
    return tmp_value.bitc.totalbw;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbCh2Rst (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Writes the register 'TD_WbCh2Rst'. */
void MH_TD_set_WbCh2Rst(MS_U32 data);
/*! \brief Reads the register 'TD_WbCh2Rst'. */
MS_U32  MH_TD_get_WbCh2Rst(void);
/*! \brief Writes the bit group 'request' of register 'TD_WbCh2Rst'. */
void MH_TD_set_WbCh2Rst_request(MS_U8 data);
/*! \brief Reads the bit group 'request' of register 'TD_WbCh2Rst'. */
MS_U8   MH_TD_get_WbCh2Rst_request(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE void MH_TD_set_WbCh2Rst(MS_U32 data)
{
    *(volatile MS_U32 *)REG_TD_WBCH2RST = data;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Rst] <-- 0x%08x\n",
                        REG_TD_WBCH2RST,data,data);
    #endif
}
MH_INLINE MS_U32  MH_TD_get_WbCh2Rst(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2RST);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Rst] --> 0x%08x\n",
                        REG_TD_WBCH2RST,value);
    #endif
    return value;
}
MH_INLINE void MH_TD_set_WbCh2Rst_request(MS_U8 data)
{
    MH_TD_WBCH2RST_S d;
    d.all = *(volatile MS_U32 *)REG_TD_WBCH2RST;
    d.bitc.request = data;
    *(volatile MS_U32 *)REG_TD_WBCH2RST = d.all;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [MH_TD_set_WbCh2Rst_request] <-- 0x%08x\n",
                        REG_TD_WBCH2RST,d.all,d.all);
    #endif
}
MH_INLINE MS_U8   MH_TD_get_WbCh2Rst_request(void)
{
    MH_TD_WBCH2RST_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBCH2RST);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbCh2Rst_request] --> 0x%08x\n",
                        REG_TD_WBCH2RST,value);
    #endif
    return tmp_value.bitc.request;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbYOutIdle (read)                                              */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbYOutIdle'. */
MS_U32  MH_TD_get_WbYOutIdle(void);
/*! \brief Reads the bit group 'Status' of register 'TD_WbYOutIdle'. */
MS_U8   MH_TD_get_WbYOutIdle_Status(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbYOutIdle(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTIDLE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutIdle] --> 0x%08x\n",
                        REG_TD_WBYOUTIDLE,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_WbYOutIdle_Status(void)
{
    MH_TD_WBYOUTIDLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTIDLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutIdle_Status] --> 0x%08x\n",
                        REG_TD_WBYOUTIDLE,value);
    #endif
    return tmp_value.bitc.status;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbUVOutIdle (read)                                             */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbUVOutIdle'. */
MS_U32  MH_TD_get_WbUVOutIdle(void);
/*! \brief Reads the bit group 'Status' of register 'TD_WbUVOutIdle'. */
MS_U8   MH_TD_get_WbUVOutIdle_Status(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbUVOutIdle(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTIDLE);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutIdle] --> 0x%08x\n",
                        REG_TD_WBUVOUTIDLE,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_WbUVOutIdle_Status(void)
{
    MH_TD_WBUVOUTIDLE_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTIDLE);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutIdle_Status] --> 0x%08x\n",
                        REG_TD_WBUVOUTIDLE,value);
    #endif
    return tmp_value.bitc.status;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbYOutInt (read)                                               */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbYOutInt'. */
MS_U32  MH_TD_get_WbYOutInt(void);
/*! \brief Reads the bit group 'Status' of register 'TD_WbYOutInt'. */
MS_U8   MH_TD_get_WbYOutInt_Status(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbYOutInt(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTINT);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutInt] --> 0x%08x\n",
                        REG_TD_WBYOUTINT,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_WbYOutInt_Status(void)
{
    MH_TD_WBYOUTINT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTINT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutInt_Status] --> 0x%08x\n",
                        REG_TD_WBYOUTINT,value);
    #endif
    return tmp_value.bitc.status;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbUVOutInt (read)                                              */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbUVOutInt'. */
MS_U32  MH_TD_get_WbUVOutInt(void);
/*! \brief Reads the bit group 'Status' of register 'TD_WbUVOutInt'. */
MS_U8   MH_TD_get_WbUVOutInt_Status(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbUVOutInt(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTINT);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutInt] --> 0x%08x\n",
                        REG_TD_WBUVOUTINT,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_WbUVOutInt_Status(void)
{
    MH_TD_WBUVOUTINT_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTINT);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutInt_Status] --> 0x%08x\n",
                        REG_TD_WBUVOUTINT,value);
    #endif
    return tmp_value.bitc.status;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbYOutFunc0 (read)                                             */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbYOutFunc0'. */
MS_U32  MH_TD_get_WbYOutFunc0(void);
/*! \brief Reads the bit group 'FrmCnt' of register 'TD_WbYOutFunc0'. */
MS_U16  MH_TD_get_WbYOutFunc0_FrmCnt(void);
/*! \brief Reads the bit group 'BufferErrCnt' of register 'TD_WbYOutFunc0'. */
MS_U16  MH_TD_get_WbYOutFunc0_BufferErrCnt(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbYOutFunc0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc0] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC0,value);
    #endif
    return value;
}
MH_INLINE MS_U16  MH_TD_get_WbYOutFunc0_FrmCnt(void)
{
    MH_TD_WBYOUTFUNC0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc0_FrmCnt] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC0,value);
    #endif
    return tmp_value.bitc.frmcnt;
}
MH_INLINE MS_U16  MH_TD_get_WbYOutFunc0_BufferErrCnt(void)
{
    MH_TD_WBYOUTFUNC0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc0_BufferErrCnt] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC0,value);
    #endif
    return tmp_value.bitc.buffererrcnt;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbYOutFunc1 (read)                                             */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbYOutFunc1'. */
MS_U32  MH_TD_get_WbYOutFunc1(void);
/*! \brief Reads the bit group 'MaxBD' of register 'TD_WbYOutFunc1'. */
MS_U8   MH_TD_get_WbYOutFunc1_MaxBD(void);
/*! \brief Reads the bit group 'TotalBD' of register 'TD_WbYOutFunc1'. */
MS_U32  MH_TD_get_WbYOutFunc1_TotalBD(void);
/*! \brief Reads the bit group 'FrmBaseSel' of register 'TD_WbYOutFunc1'. */
MS_U8   MH_TD_get_WbYOutFunc1_FrmBaseSel(void);
/*! \brief Reads the bit group 'DmaBusy' of register 'TD_WbYOutFunc1'. */
MS_U8   MH_TD_get_WbYOutFunc1_DmaBusy(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbYOutFunc1(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC1);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc1] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC1,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_WbYOutFunc1_MaxBD(void)
{
    MH_TD_WBYOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc1_MaxBD] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC1,value);
    #endif
    return tmp_value.bitc.maxbd;
}
MH_INLINE MS_U32  MH_TD_get_WbYOutFunc1_TotalBD(void)
{
    MH_TD_WBYOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc1_TotalBD] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC1,value);
    #endif
    return tmp_value.bitc.totalbd;
}
MH_INLINE MS_U8   MH_TD_get_WbYOutFunc1_FrmBaseSel(void)
{
    MH_TD_WBYOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc1_FrmBaseSel] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC1,value);
    #endif
    return tmp_value.bitc.frmbasesel;
}
MH_INLINE MS_U8   MH_TD_get_WbYOutFunc1_DmaBusy(void)
{
    MH_TD_WBYOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBYOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbYOutFunc1_DmaBusy] --> 0x%08x\n",
                        REG_TD_WBYOUTFUNC1,value);
    #endif
    return tmp_value.bitc.dmabusy;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbUVOutFunc0 (read)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbUVOutFunc0'. */
MS_U32  MH_TD_get_WbUVOutFunc0(void);
/*! \brief Reads the bit group 'FrmCnt' of register 'TD_WbUVOutFunc0'. */
MS_U16  MH_TD_get_WbUVOutFunc0_FrmCnt(void);
/*! \brief Reads the bit group 'BufferErrCnt' of register 'TD_WbUVOutFunc0'. */
MS_U16  MH_TD_get_WbUVOutFunc0_BufferErrCnt(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbUVOutFunc0(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC0);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc0] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC0,value);
    #endif
    return value;
}
MH_INLINE MS_U16  MH_TD_get_WbUVOutFunc0_FrmCnt(void)
{
    MH_TD_WBUVOUTFUNC0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc0_FrmCnt] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC0,value);
    #endif
    return tmp_value.bitc.frmcnt;
}
MH_INLINE MS_U16  MH_TD_get_WbUVOutFunc0_BufferErrCnt(void)
{
    MH_TD_WBUVOUTFUNC0_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC0);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc0_BufferErrCnt] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC0,value);
    #endif
    return tmp_value.bitc.buffererrcnt;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TD_WbUVOutFunc1 (read)                                            */
/*----------------------------------------------------------------------------*/
#if MH_INLINE_LEVEL == 0
/*! \brief Reads the register 'TD_WbUVOutFunc1'. */
MS_U32  MH_TD_get_WbUVOutFunc1(void);
/*! \brief Reads the bit group 'MaxBD' of register 'TD_WbUVOutFunc1'. */
MS_U8   MH_TD_get_WbUVOutFunc1_MaxBD(void);
/*! \brief Reads the bit group 'TotalBD' of register 'TD_WbUVOutFunc1'. */
MS_U32  MH_TD_get_WbUVOutFunc1_TotalBD(void);
/*! \brief Reads the bit group 'FrmBaseSel' of register 'TD_WbUVOutFunc1'. */
MS_U8   MH_TD_get_WbUVOutFunc1_FrmBaseSel(void);
/*! \brief Reads the bit group 'DmaBusy' of register 'TD_WbUVOutFunc1'. */
MS_U8   MH_TD_get_WbUVOutFunc1_DmaBusy(void);
#else /* MH_INLINE_LEVEL == 0 */
MH_INLINE MS_U32  MH_TD_get_WbUVOutFunc1(void)
{
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC1);

    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc1] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC1,value);
    #endif
    return value;
}
MH_INLINE MS_U8   MH_TD_get_WbUVOutFunc1_MaxBD(void)
{
    MH_TD_WBUVOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc1_MaxBD] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC1,value);
    #endif
    return tmp_value.bitc.maxbd;
}
MH_INLINE MS_U32  MH_TD_get_WbUVOutFunc1_TotalBD(void)
{
    MH_TD_WBUVOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc1_TotalBD] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC1,value);
    #endif
    return tmp_value.bitc.totalbd;
}
MH_INLINE MS_U8   MH_TD_get_WbUVOutFunc1_FrmBaseSel(void)
{
    MH_TD_WBUVOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc1_FrmBaseSel] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC1,value);
    #endif
    return tmp_value.bitc.frmbasesel;
}
MH_INLINE MS_U8   MH_TD_get_WbUVOutFunc1_DmaBusy(void)
{
    MH_TD_WBUVOUTFUNC1_S tmp_value;
    MS_U32 value = (*(volatile MS_U32 *)REG_TD_WBUVOUTFUNC1);

    tmp_value.all = value;
    #if MH_TD_ENABLE_DEBUG_PRINT
    MH_TD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [MH_TD_get_WbUVOutFunc1_DmaBusy] --> 0x%08x\n",
                        REG_TD_WBUVOUTFUNC1,value);
    #endif
    return tmp_value.bitc.dmabusy;
}
#endif /* MH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void MH_TD_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _MH_ISP_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

