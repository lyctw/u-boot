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
** \file       td_test.h
**
** \brief      for test vo module and will be continuous updating
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version    td_test.h ,v 1.1 2019/12/16  Kite.Su Exp $
**
**************************************************************************
*/

#ifndef td_TEST_H_
#define td_TEST_H_
//#include <vo_types.h>
#include <md_td.h>


typedef enum 
{
    TD_CASE_UNDEFINE = 0,
    TD_ROTATION_90_DEGREE_320352_MONO,
    TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_INPUT,
    TD_ROTATION_90_DEGREE_320352_MONO_SWAP_INPUT,
    TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_OUTPUT,
    TD_ROTATION_90_DEGREE_320352_MONO_SWAP_OUTPUT,
    TD_ROTATION_90_DEGREE_320352_420,
    TD_ROTATION_90_DEGREE_320352_422,
    TD_ROTATION_90_DEGREE_444,
    TD_ROTATION_90_DEGREE_1080p_420_TIMEOUT,
    TD_ROTATION_270_DEGREE_320352_420,
    TD_ROTATION_270_DEGREE_320352_422,
    TD_ROTATION_90_DEGREE_MAIN_420,
    TD_ROTATION_270_DEGREE_MAIN_420,
    TD_ROTATION_90_DEGREE_MAIN_422,
    TD_ROTATION_90_DEGREE_MAIN_444,

    TD_ROTATION_90_DEGREE_1080P_420,
    TD_ROTATION_90_DEGREE_720P_420,
    TD_ROTATION_90_DEGREE_VGA_420,
    TD_ROTATION_90_DEGREE_CIF_420,
    TD_ROTATION_90_DEGREE_QCIF_420,
    TD_ROTATION_270_DEGREE_1080P_420,
    TD_ROTATION_270_DEGREE_720P_420,
    TD_ROTATION_270_DEGREE_VGA_420,
    TD_ROTATION_270_DEGREE_CIF_420,
    TD_ROTATION_270_DEGREE_QCIF_420,
    TD_ROTATION_90_DEGREE_1080P_422,
    TD_ROTATION_90_DEGREE_720P_422,
    TD_ROTATION_90_DEGREE_VGA_422,
    TD_ROTATION_90_DEGREE_CIF_422,
    TD_ROTATION_90_DEGREE_QCIF_422,
    TD_ROTATION_270_DEGREE_1080P_422,
    TD_ROTATION_270_DEGREE_720P_422,
    TD_ROTATION_270_DEGREE_VGA_422,
    TD_ROTATION_270_DEGREE_CIF_422,
    TD_ROTATION_270_DEGREE_QCIF_422,
    TD_ROTATION_90_DEGREE_1080P_MONO,
    TD_ROTATION_270_DEGREE_1080P_MONO,
    TD_ROTATION_90_DEGREE_CIF_RGB888,
    TD_ROTATION_270_DEGREE_CIF_RGB888,
    TD_ROTATION_90_DEGREE_1080P_BITSWAP_420,
    TD_ROTATION_90_DEGREE_1080P_ENDIANSWAP_420,
    TD_ROTATION_90_DEGREE_STRIDE_TEST,
    TD_ROTATION_90_DEGREE_MAIN_420_IRQ,

    TD_SCALER_1080P_420IN_YUV420OUT,
    TD_SCALER_1080P_420IN_YUV422OUT,//needed?
    TD_SCALER_1080P_420IN_ARGBOUT,
    TD_SCALER_1080P_420IN_SEPARATE_RGBOUT,    
    TD_SCALER_1080P_422IN_YUV422OUT,
    TD_SCALER_1080P_422IN_YUV420OUT,
    TD_SCALER_1080P_422IN_ARGBOUT,
    TD_SCALER_1080P_422IN_SEPARATE_RGBOUT,
  
    TD_MIXER_VIDEO_320352_OSD_256200,
    TD_MIXER_MAINYUV_320to640480,
    TD_MIXER_MAINYUV_320to176144,
    TD_MIXER_MAINYUV_1080to320240,
    TD_MIXER_MAINYUV_BACKGROUND,
    TD_MIXER_MAINYUV_ALPHA,
    TD_MIXER_MAINYUV_MIXER,
    TD_MIXER_MAINYUV_POSITION,
    TD_MIXER_MAINYUV_CROP,
    TD_MIXER_MAINYUV_JOINT,
    TD_MIXER_MAINYUV_JOINT_DEBUG,
    TD_MIXER_MAINYUV_ROTATION,
    TD_MIXER_MAIN_RGB,

    TD_MIXER_420_ARGB8888_GLOBAL_ALPHA_TRAVERSAL,
    TD_MIXER_422_RGB888_SEPARATE_ALPHA,
    TD_MIXER_420_ARGB4444_INTEGRATED_ALPHA,
    TD_MIXER_420_RGB565_ENDIANSWAP_BGR,
    TD_MIXER_420_ARGB1555_TWOBYTEENDIAN_RGB,
    TD_MIXER_420_MONO8_RANDOM_SIZE,
    TD_MIXER_420_STRIDE,

}TD_TestCaseE;


typedef struct
{
    MD_TD_RotationModeE rotMode;
    MD_TD_RotationPixelFormatE pxlFormat;
    MS_U32 width;
    MS_U32 height;
    MS_U32 inStride;
    MS_U32 outStride;
    MS_U32 addrSrcY;
    MS_U32 addrSrcUV;
    MS_U32 addrSrcV;
    MS_U32 addrDstY;
    MS_U32 addrDstUV;
    MS_U32 addrDstV;
    MS_U8  InSwapEn;
    MS_U8  BigLittleInEndia;    
    MS_U8  enOutSwap;
    MS_U8  enEndianSwap;
}TD_RotationTestParam;

typedef struct
{
    MS_U32 inWidth;
    MS_U32 inHeight;
    MS_U32 outWidth;
    MS_U32 outHeight;
    MS_U32 inStride;
    MD_TD_VideoLayerYuvModeE yuvMode;
    MD_TD_VideoLayerYEndianE endianModeY;
    MD_TD_VideoLayerUVEndianE endianModeUV;
    MS_U8 wbRGBorYUV;
    MS_U8 wbYUVInputFormat;
    MS_U8 wbOutputFormat;
    MS_U8 wbYUV422PxlOrder;
    MS_U32 wbBaseAddrY;
    MS_U32 wbBaseAddrUV;
    MS_U32 wbStride;
}TD_ScalerTestParam;

typedef struct
{
    MS_U32 videoWidth;
    MS_U32 videoHeight;
    MS_U32 videoOutWidth;
    MS_U32 videoOutHeight;
    MS_U32 videoStride;
    MS_S32 videoStartX;
    MS_S32 videoStartY;
    MD_TD_VideoLayerYuvModeE yuvMode;
    MD_TD_VideoLayerYEndianE endianModeY;
    MD_TD_VideoLayerUVEndianE endianModeUV;
    MS_U32 videoGlbAlpha;
    MS_U32 videoAddrY;
    MS_U32 videoAddrUV;
    MS_U32 osdWidth;
    MS_U32 osdHeight;
    MS_U32 osdStride;
    MS_U32 alphaStride;
    
    MD_TD_OSDLayerTypeE osdType;
    MD_TD_OSDAlphaTypeE alphaType;
    MS_U16 dmaMap;
    MS_U16 revRGB;
    MS_U32 osdGlbAlpha;
    MS_U32 osdAddr;
    MS_U32 osdAlphaAddr;
    MS_S32 osdStartX;
    MS_S32 osdStartY;
    MS_U32 wbWidth;
    MS_U32 wbHeight;
    MS_U32 wbStride;
    MS_U8 wbRGBorYUV;
    MS_U8 wbYUVInputFormat;
    MS_U8 wbOutputFormat;
    MS_U8 wbYUV422PxlOrder;
    MS_U32 wbBaseAddrY;
    MS_U32 wbBaseAddrUV;
    MS_U8 wbPixWidth;
}TD_MixerTestParam;


#define ROTATE_TEST_ADDRESS_SRCY    0x20600000
#define ROTATE_TEST_ADDRESS_SRCUV   0x20880000
#define ROTATE_TEST_ADDRESS_DSTY0    0x25000000
#define ROTATE_TEST_ADDRESS_DSTUV0   0x25200000
#define ROTATE_TEST_ADDRESS_DSTY1    0x25400000
#define ROTATE_TEST_ADDRESS_DSTUV1   0x25600000

#define DUMP_ROTATION_ADDR_SRCY      0x01000000
#define DUMP_ROTATION_ADDR_SRCUV     0x011FA400
#define DUMP_ROTATION_ADDR_DSTY      0x26400000
#define DUMP_ROTATION_ADDR_DSTUV     0x26600000
#define DUMP_ROTATION_ADDR_DSTV      0x26800000

#define DUMP_MIXER_ADDR_VIDEO_Y     0x25000000
#define DUMP_MIXER_ADDR_VIDEO_UV    0x25300000
#define DUMP_MIXER_ADDR_OSD         0x25600000
#define DUMP_MIXER_ADDR_ALPHA       0x25D00000
#define DUMP_MIXER_DST_ADDR_Y       0x02000000
#define DUMP_MIXER_DST_ADDR_UV      0x26600000
#define DUMP_MIXER_DST_ADDR_V       0x26800000




void TestTDRotation(MS_U8 testCase);
void TestTDMixer(MS_U8 testCase);
void TD_MixerTestVideoMainYUV_1080to320240(MS_U32 ImgInDataMode,MS_U32 InputW,MS_U32 InputH,MS_U32 downscaleW,MS_U32 downscaleH);
void TD_TestRotation90DegreeMainYuv420_Parm(MS_U32 RatationMode,MS_U16 srcW,MS_U16 srcStride,MS_U16 srcH,MS_U16 OtMaxRD,MS_U16 OtMaxWR);
void TD_TestRotation270DegreeMainYuv420_Parm(MS_U32 RatationMode,MS_U16 srcW,MS_U16 srcStride,MS_U16 srcH,MS_U16 OtMaxRD,MS_U16 OtMaxWR);

#endif /* td_TEST_H_ */
