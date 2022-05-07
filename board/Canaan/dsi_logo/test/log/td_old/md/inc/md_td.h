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
** \file       md_td.h
**
** \brief      td driver layer for operate hw
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   md_td.h  ,v 1.0 2019/12/16  Kite.Su Exp $
**
**************************************************************************
*/


#ifndef TD_H
 #define TD_H

//#include <vo/vo_types.h>
//#include <vo/md/inc/vo_error.h>

#include <mh_td.h>

//***********************************************************************
//***********************************************************************
//** Defines and Macros
//***********************************************************************
//***********************************************************************


#define     TD_VIDEO_LAYER0   0
#define     TD_VIDEO_LAYER1   1
#define     TD_VIDEO_LAYER2   2
#define     TD_VIDEO_LAYER3   3

#define     TD_OSD_LAYER0     0
#define     TD_OSD_LAYER1     1
#define     TD_OSD_LAYER2     2

#define MS_TD_MAX_NUM_VIDEO_LAYER0                             0x01
#define MS_TD_MAX_NUM_VIDEO_LAYER1                             0x00
#define MS_TD_MAX_NUM_VIDEO_LAYER2                             0x00
#define MS_TD_MAX_NUM_VIDEO_LAYER3                             0x00
#define MS_TD_MAX_NUM_OSD_LAYER0                               0x01
#define MS_TD_MAX_NUM_OSD_LAYER1                               0x00
#define MS_TD_MAX_NUM_OSD_LAYER2                               0x00



#define MS_TD_VIDEO_LAYER_TOTAL                                      \
                                       (MS_TD_MAX_NUM_VIDEO_LAYER0 +\
                                        MS_TD_MAX_NUM_VIDEO_LAYER1   +\
                                        MS_TD_MAX_NUM_VIDEO_LAYER2   +\
                                        MS_TD_MAX_NUM_VIDEO_LAYER3  )

#define MS_TD_OSD_LAYER_TOTAL                                      \
                                       (MS_TD_MAX_NUM_OSD_LAYER0  +\
                                        MS_TD_MAX_NUM_OSD_LAYER1  +\
                                        MS_TD_MAX_NUM_OSD_LAYER2 )


#define MS_TD_MAX_NUM_LAYER_TOTAL                                      \
                                       (MS_TD_MAX_NUM_VIDEO_LAYER0 +\
                                        MS_TD_MAX_NUM_VIDEO_LAYER1   +\
                                        MS_TD_MAX_NUM_VIDEO_LAYER2   +\
                                        MS_TD_MAX_NUM_VIDEO_LAYER3  +\
                                        MS_TD_MAX_NUM_OSD_LAYER0  +\
                                        MS_TD_MAX_NUM_OSD_LAYER1  +\
                                        MS_TD_MAX_NUM_OSD_LAYER2  +\)



typedef enum 
{
    TD_ROTATION_90_DEGREE              = 0,
    TD_ROTATION_270_DEGREE             = 1
} MD_TD_RotationModeE;

typedef enum 
{
    TD_ROTATION_PIX_FORMAT_MONO         = 0,
    TD_ROTATION_PIX_FORMAT_420SP        = 1,
    TD_ROTATION_PIX_FORMAT_422SP        = 2,
    TD_ROTATION_PIX_FORMAT_RGB888       = 3
} MD_TD_RotationPixelFormatE;







typedef enum 
{
    TD_MIXER_VIDEO_LAYER_0              = 0,
    TD_MIXER_VIDEO_LAYER_1              = 1,
    TD_MIXER_VIDEO_LAYER_2              = 2,
    TD_MIXER_VIDEO_LAYER_3              = 3,
    TD_MIXER_OSD_LAYER_0              = 4,
    TD_MIXER_OSD_LAYER_1              = 5,
    TD_MIXER_OSD_LAYER_2              = 6,
} MD_TD_MixerOrderE;


typedef enum 
{
    TD_VIDEO_LAYER_YUV_MODE_420              = 0x08,
    TD_VIDEO_LAYER_YUV_MODE_422              = 0x09,
} MD_TD_VideoLayerYuvModeE;


typedef enum 
{
    TD_VIDEO_LAYER_Y_ENDIAN_MODE0              = 0x0,//Y4 Y5 Y6 Y7 Y0 Y1 Y2 Y3
    TD_VIDEO_LAYER_Y_ENDIAN_MODE1              = 0x1,//Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0
    TD_VIDEO_LAYER_Y_ENDIAN_MODE2              = 0x2,//Y0 Y1 Y2 Y3 Y4 Y5 Y6 Y7
    TD_VIDEO_LAYER_Y_ENDIAN_MODE3              = 0x3,//Y3 Y2 Y1 Y0 Y7 Y6 Y5 Y4
} MD_TD_VideoLayerYEndianE;



typedef enum 
{
    TD_VIDEO_LAYER_UV_ENDIAN_MODE0              = 0x0,//U2 V2 U3 V3 U0 V0 U1 V1
    TD_VIDEO_LAYER_UV_ENDIAN_MODE1              = 0x1,//V2 U2 V3 U3 V0 U0 V1 U1
    TD_VIDEO_LAYER_UV_ENDIAN_MODE2              = 0x2,//U3 V3 U2 V2 U1 V1 U0 V0
    TD_VIDEO_LAYER_UV_ENDIAN_MODE3              = 0x3,//V3 U3 V2 U2 V1 U1 V0 U0  
    TD_VIDEO_LAYER_UV_ENDIAN_MODE4              = 0x4,//U0 V0 U1 V1 U2 V2 U3 V3  
    TD_VIDEO_LAYER_UV_ENDIAN_MODE5              = 0x5,//V0 U0 V1 U1 V2 U2 V3 U3 
    TD_VIDEO_LAYER_UV_ENDIAN_MODE6              = 0x6,//U1 V1 U0 V0 U3 V3 U2 V2
    TD_VIDEO_LAYER_UV_ENDIAN_MODE7              = 0x7//V1 U1 V0 U0 V3 U3 V2 U2 
} MD_TD_VideoLayerUVEndianE;


 
 typedef enum {
     TD_RGB_24BIT         = 0,
     TD_MONOCHROME_8BIT   = 1,
     TD_RGB_16BIT         = 2,
     TD_RGB_32BIT         = 3,
     TD_RGB_4444          = 4,
     TD_RGB_1555            = 5,
 }MD_TD_OSDLayerTypeE;


 typedef enum {
     TD_ORIGINAL_ORDER     = 0,
     TD_TWO_BIT_ENDIAN    = 2,
     TD_LITTLE_ENDIAN      = 3,
 }MD_TD_OSDDmaCtlE;

  typedef enum {
     TD_RGB_REV_R     = 0,
     TD_RGB_REV_B     = 1,
     TD_RGB_REV_NUM   = 2,
 }MD_TD_OSDDmaRGBRev;

 typedef enum {
     TD_FIXED_VALUE         = 0,  //Alpha data is a fixed value
     TD_L2_ALPHA_ADDR       = 1,  //Alpha data is at alpha data block in L2_ALPHA_ADDR.
     TD_INTERVAL_R          = 2,  //Alpha data interval is aligned with R channel of OSD
     TD_INTERVAL_G          = 3,  //Alpha data interval is aligned with G channel of OSD
     TD_INTERVAL_B          = 4,  //Alpha data interval is aligned with B channel of OSD
     TD_INTERVAL_A          = 5   //Alpha data interval is aligned with Alpha Channel of OSD for OSD type is 3, 4, and 5
 }MD_TD_OSDAlphaTypeE;



 /*
 *************************************************************************
 ** Defines for general error codes of the module.
 *************************************************************************
 */

//ERR
 typedef enum 
 {
    ERR_TD_NOT_INIT                = 0x40,//TD not init
    ERR_TD_MEM_NOT_INIT            = 0x41,//TD memory not init
    ERR_TD_ATTR_NOT_CFG            = 0x42,//TD attribute not cfg
    ERR_TD_ERR_START               = 0x43,//TD sensor unregister
    ERR_TD_INVALID_ADDR            = 0x44,//TD invalid address
    ERR_TD_NOMEM                   = 0x45,//TD nomem
    ERR_TD_LAYER_NOT_ENABLE        = 0x46,//TD
    ERR_TD_ALREADY_INIT            = 0x47,//TD
    ERR_TD_HANDLE_CHECK_FAILED     = 0x48,//TD
    ERR_TD_UNSUPPORTED_FUNCTIONALITY     = 0x49,//TD
    ERR_TD_EXCEEDED_MAX_HANDLES    = 0x4a,//TD
    ERR_TD_NULL_PTR                = 0x4b,//TD
    ERR_TD_ILLEGAL_PARAM           = 0x4c,//TD
    ERR_TD_NOT_SUPPORT             = 0x4d//TD
} MD_TD_ErrCodeE;

#if 0
#define MS_ERR_TD_NOT_INIT                MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_NOT_INIT)
#define MS_ERR_TD_MEM_NOT_INIT            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_MEM_NOT_INIT)
#define MS_ERR_TD_ATTR_NOT_CFG            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ATTR_NOT_CFG)
#define MS_ERR_TD_ERR_START               MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ERR_START)
#define MS_ERR_TD_INVALID_ADDR            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_INVALID_ADDR)
#define MS_ERR_TD_NOMEM                   MD_D0F_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_NOMEM)
#define MS_ERR_TD_LAYER_NOT_ENABLE        MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_LAYER_NOT_ENABLE)
#define MS_ERR_TD_ALREADY_INIT            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ALREADY_INIT)
#define MS_ERR_TD_HANDLE_CHECK_FAILED     MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_HANDLE_CHECK_FAILED)
#define MS_ERR_UNSUPPORTED_FUNCTIONALITY  MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_UNSUPPORTED_FUNCTIONALITY)
#define MS_ERR_TD_EXCEEDED_MAX_HANDLES    MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_EXCEEDED_MAX_HANDLES)
#define MS_ERR_TD_NULL_PTR                MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_NULL_PTR)
#define MS_ERR_TD_ILLEGAL_PARAM           MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ILLEGAL_PARAM)


#define MS_ERR_TD_NOT_SUPPORT             MD_DEF_ERR(MS_ID_VO,ERR_LEVEL_ERROR, ERR_TD_NOT_SUPPORT)

#else
#define MD_DEF_ERR(a,b,c) c
#define MS_ERR_TD_NOT_INIT                MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_NOT_INIT)
#define MS_ERR_TD_MEM_NOT_INIT            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_MEM_NOT_INIT)
#define MS_ERR_TD_ATTR_NOT_CFG            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ATTR_NOT_CFG)
#define MS_ERR_TD_ERR_START               MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ERR_START)
#define MS_ERR_TD_INVALID_ADDR            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_INVALID_ADDR)
#define MS_ERR_TD_NOMEM                   MD_D0F_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_NOMEM)
#define MS_ERR_TD_LAYER_NOT_ENABLE        MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_LAYER_NOT_ENABLE)
#define MS_ERR_TD_ALREADY_INIT            MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ALREADY_INIT)
#define MS_ERR_TD_HANDLE_CHECK_FAILED     MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_HANDLE_CHECK_FAILED)
#define MS_ERR_UNSUPPORTED_FUNCTIONALITY  MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_UNSUPPORTED_FUNCTIONALITY)
#define MS_ERR_TD_EXCEEDED_MAX_HANDLES    MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_EXCEEDED_MAX_HANDLES)
#define MS_ERR_TD_NULL_PTR                MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_NULL_PTR)
#define MS_ERR_TD_ILLEGAL_PARAM           MD_DEF_ERR(MS_ID_TD,ERR_LEVEL_ERROR, ERR_TD_ILLEGAL_PARAM)


#define MS_ERR_TD_NOT_SUPPORT             MD_DEF_ERR(MS_ID_VO,ERR_LEVEL_ERROR, ERR_TD_NOT_SUPPORT)

#endif






typedef enum 
{
    TD_SF_RST_DISP_DOMAIN = 0,
    TD_SF_RST_AXI_DOMAIN,
    TD_SF_RST_APB_DOMAIN   
}TD_SwRstE;

/*!
****************************************************************************
** \brief Enumeration type for system mode.
****************************************************************************
*/



typedef enum 
{
    TD_DMA_ARB_PRIORITY = 0x00,
    TD_DMA_ARB_WEIGHT_RR = 0x3 
}TD_ARBModeE;



typedef enum {
    TD_VISCALE_ENDIAN_DEFAULT = 0,
    TD_VISCALE_ENDIAN_SWAP
}TD_EndiannessE;


typedef enum {
    TD_PIXEL_ORDER_DEFAULT = 0,
    TD_PIXEL_ORDER_REVERSE
}TD_PixelOrderE;



typedef struct 
{   
    MS_U16 StartX;
    MS_U16 StopX;
    MS_U16 StartY;
    MS_U16 StopY;
} MD_TD_LayerPositonParamT;


typedef struct {

    MS_U8                            LayerEnable;
    MS_U32                           Line0BDCtl;
    MS_U32                           Line1BDCtl;
    MS_U32                           Line2BDCtl;
    MS_U32                           Line3BDCtl;
    MS_U32                           LayerBDCtl;
    MD_TD_LayerPositonParamT         LayerPosition;
    MS_U8                            LayerScalerBLen;
    MD_TD_VideoLayerYuvModeE         ImgInDataMode;
    MD_TD_VideoLayerYEndianE         EndianModeY;
    MD_TD_VideoLayerUVEndianE        EndianModeUV;
    MS_U32                           ReadAddress0Y;
    MS_U32                           ReadAddress0UV;
    MS_U16                           ImgInPixelHszie;
    MS_U16                           ImgInPixelVszie;
    MS_U16                           ImgOutPixelHszie;
    MS_U16                           ImgOutPixelVszie;
    MS_U16                           ImgInPixelStrideH;
    MS_U16                           ImgInPixelStrideV;
    MS_U16                           ImgInPixelOffsetH;
    MS_U16                           ImgInPixelOffsetV;
    MS_U8                            LayerOrder; 
    //! Flag to enable using the global alpha.
    MS_U32                           useGlobalAlpha;
    //! global alpha
    MS_U32                           GlobalAlpha;
} MD_TD_VideoLayerParamT;

typedef struct
{
    MS_U8                            OsdEnable;       
    MD_TD_OSDLayerTypeE              OsdType;
    MD_TD_OSDAlphaTypeE              AlphaTpye;
    MS_U8                            RGB2YUVEnable;
    MD_TD_LayerPositonParamT         LayerPosition;
    MS_U16                           OsdPixelHszie;
    MS_U16                           OsdPixelVszie;
    MS_U32                           ReadAddress0Value;
    MS_U32                           ReadAddress0Alp;
    MS_U8                            RequestBLen;
    MS_U16                           DmaMap;
    MS_U16                           RevRGB;
    MS_U16                           DataInStride;
    MS_U16                           AlphaInStride;
    MS_U8                            LayerOrder; 
    //! global alpha
    MS_U32                           GlobalAlpha;
} MD_TD_OSDLayerParamT;


typedef struct
{
    MS_U8                            InputMode;      //0：bt656  1:BT1120       
  
    
    MS_U8                            DataFormat;     //RGB/RAW  1:YUV  
    MS_U8                            DmaInputFormat; //1`b0:YUV422;1`b1:YUV420
    MS_U8                            OutputMode;
    MS_U8                            DmaInput422PixelOrder;
    MS_U8                            RawPixelWidth;
    
    MS_U32                           WriteBaseAddressY0;
    MS_U32                           WriteBaseAddressY1;
    
    MS_U32                           WriteBaseAddressUV0;
    MS_U32                           WriteBaseAddressUV1;

    MS_U32                           DataLineYStride;
    MS_U16                           DataLineUVStride;
    MS_U16                           DramLoopSzie;

    MS_U16                           ActiveHszie;
    MS_U16                           ActiveVszie;

    //CH1
    MS_U8                            Ch1OtNum; 
    MS_U8                            Ch1BlenMode; 
    MS_U8                            Ch1ContinuousMode;   
    MS_U8                            Ch1DmaYUVMap;
    MS_U8                            Ch1WbErrDetectEn;         
    MS_U8                            Ch1ErrUnit;
    MS_U8                            Ch1ErrTh;
    //CH2
    MS_U8                            Ch2OtNum; 
    MS_U8                            Ch2BlenMode; 
    MS_U8                            Ch2ContinuousMode;   
    MS_U8                            Ch2DmaYUVMap;
    MS_U8                            Ch2WbErrDetectEn;         
    MS_U8                            Ch2ErrUnit;
    MS_U8                            Ch2ErrTh;

} MD_TD_MixerWbParamT;



typedef struct {

    //! These are the fields used for setting the Vo scaler.
    MD_TD_OSDLayerParamT             OSDLayerParam[MS_TD_OSD_LAYER_TOTAL];
    MD_TD_VideoLayerParamT           VideoLayerParam[MS_TD_VIDEO_LAYER_TOTAL];
    MS_U8                            DmaWriteBackEn; 
    MD_TD_MixerWbParamT              DmaWbParam;        
    MS_U32                           DisplayEnable;
    MS_U32                           LayerMixerOrder;
    MS_U32                           LayerMixerEnable;
    MD_TD_LayerPositonParamT         WindowZone;
    MS_U8                            DisplayYUV2RGBEn;
    MS_U32                           BackGroundComp; 
} MD_TD_MixerParamaterT;






typedef struct {

    //! These are the fields used for setting the Vo scaler.
    MD_TD_RotationModeE             RotationMode;
    MD_TD_RotationPixelFormatE      RotationPixelFormat;

    MS_U8                           InSwapEn;
    MS_U8                           BigLittleInEndia;
    MS_U8                           OutSwapEn;
    MS_U8                           BigLittleOutEndia;

    MS_U8                           OtMaxRD;
    MS_U8                           OtMaxWR;
    
    MS_U16                          DoneTimeOut;
    
    MS_U16                          ActiveVer;
    MS_U16                          ActiveHor;
    
    MS_U32                          BaseAddrSrcY; 
    MS_U32                          BaseAddrSrcU; 
    MS_U32                          BaseAddrSrcV; 
    
    MS_U32                          BaseAddrDesY; 
    MS_U32                          BaseAddrDesU; 
    MS_U32                          BaseAddrDesV; 

    MS_U16                          StrideSrcY;
    MS_U16                          StrideDesY;

    MS_U16                          StrideSrcU;
    MS_U16                          StrideDesU;

    MS_U16                          StrideSrcV;
    MS_U16                          StrideDesV;
}MD_TD_RotationParmT;



typedef struct {
    MD_TD_RotationParmT             RotationParm;
} MD_TD_RotationHandleT;


typedef struct {
    MD_TD_MixerParamaterT           MixerParamater;
} MD_TD_MixerHandleT;



 
//***********************************************************************
//***********************************************************************
//** Global Data
//***********************************************************************
//***********************************************************************

//***********************************************************************
//***********************************************************************
//** API Functions
//***********************************************************************
//***********************************************************************


extern MS_U32 MS_API_TD_SoftwareRstCtl(TD_SwRstE RestDomain);

extern MS_U32 MS_API_TD_SetOsdLayerType( MS_U8 OsdLayer,MD_TD_OSDLayerTypeE OsdType,MD_TD_OSDAlphaTypeE AlphaTpye);

extern MS_U32 MS_API_TD_WrapInit(void);

extern MS_SYS_HandleT MS_API_TD_MixerOpen(const MD_TD_MixerParamaterT* LayerOpenLayerParm,
                                  MS_U32* errorCodePtr);


extern MS_SYS_HandleT MS_API_TD_RotationOpen(const MD_TD_RotationParmT* RotationOpenParm,
                                                                 MS_U32* errorCodePtr);

extern MS_U32 MS_API_TD_WrapInit(void);
 
extern MS_U32 MS_API_TD_RotationFrameStart(void);

extern MS_U32 MS_API_TD_WrapCfgDone(void);
extern MS_U32 MS_API_TD_MixerInit(void);
extern MS_U32 MS_API_TD_MixerFrameStart(void);

 extern   MS_U32 MS_API_TD_RotationFrameStartAF(void);

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
    }
    #endif
#endif





