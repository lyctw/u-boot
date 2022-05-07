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
#include "td/td.h"
#include <video/td/table/td_table_drv.h>

void TD_TEST_Rotation(unsigned char testCase)
{
    switch( testCase )
    {
        case TD_ROTATION_90_DEGREE_320352_MONO:
    //        TD_TestRotation90Degree320352YuvMONO(1,1,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_INPUT:
    //        TD_TestRotation90Degree320352YuvMONO(1,0,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_SWAP_INPUT:
    //        TD_TestRotation90Degree320352YuvMONO(0,1,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_OUTPUT:
    //        TD_TestRotation90Degree320352YuvMONO(1,1,1,0);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_SWAP_OUTPUT:
     //       TD_TestRotation90Degree320352YuvMONO(1,1,0,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_420:
    //        TD_TestRotation90Degree320352Yuv420();
            break;
        case TD_ROTATION_90_DEGREE_320352_422:
    //        TD_TestRotation90Degree320352Yuv422();
            break;
        case TD_ROTATION_90_DEGREE_444:
    //        TD_TestRotation90DegreeYuv444();
            break;
        case TD_ROTATION_90_DEGREE_1080p_420_TIMEOUT:
    //        TD_TestRotation90Degree1080pYuv420_Timeout();
            break;
        case TD_ROTATION_270_DEGREE_320352_420:
    //        TD_TestRotation270Degree320352Yuv420();
            break;
        case TD_ROTATION_270_DEGREE_320352_422://VO_CASE_LAYER_TD_ROTATION_TEST_422
    //        TD_TestRotation270Degree320352Yuv422();
            break;        
        case TD_ROTATION_90_DEGREE_MAIN_420_IRQ:   ////VO_CASE_LAYER_TD_ROTATION_TEST       
    //      TD_TestRotation90DegreeMainYuv420_IRQ();
            break;
        case TD_ROTATION_90_DEGREE_MAIN_420:   ////VO_CASE_LAYER_TD_ROTATION_TEST
          //TD_TestRotation270DegreeMainYuv420();
    //      TD_TestRotation90DegreeMainYuv420();
            break;
        case TD_ROTATION_270_DEGREE_MAIN_420:
     //       TD_TestRotation270DegreeMainYuv420();
            break;
        case TD_ROTATION_90_DEGREE_MAIN_422:
            //TD_TestRotation90DegreeMainYuv422();
     //       TD_TestRotation270DegreeMainYuv422();
            break;  
        case TD_ROTATION_90_DEGREE_MAIN_444:
     //       TD_TestRotation90DegreeMainYuv444();
            break;
        default:
            break;
                
    }
}
/*
*
*/
void TD_TEST_Mixer(unsigned char testCase)
{
    switch( testCase )
    {
        case TD_MIXER_MAIN_RGB:
 //           TD_MixerTestVideoMainRGB(TD_VIDEO_LAYER_YUV_MODE_420);
            break;        
        case TD_MIXER_VIDEO_320352_OSD_256200:
 //           TD_MixerTestVideo320240Osd256200(TD_VIDEO_LAYER_YUV_MODE_420);
            break;        
        case TD_MIXER_MAINYUV_320to640480://VO_CASE_LAYER_TD_MIXER_TEST
 //           TD_MixerTestVideoMainYUV_320to640480(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        case TD_MIXER_MAINYUV_320to176144://VO_CASE_LAYER_TD_MIXER_VOUT_COMPARE_TEST
 //           TD_MixerTestVideoMainYUV_320to176144(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        case TD_MIXER_MAINYUV_1080to320240://VO_CASE_LAYER_TD_MIXER_VOUT_COMPARE_TEST
 //           TD_MixerTestVideoMainYUV_1080to320240(TD_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 352, 288);
            break;
        case TD_MIXER_MAINYUV_BACKGROUND:
 //           TD_MixerTestVideoMainYUV_Backgroud(TD_VIDEO_LAYER_YUV_MODE_420);
            break;        
        case TD_MIXER_MAINYUV_ALPHA:
 //           TD_MixerTestVideoMainYUV_Alpha(TD_VIDEO_LAYER_YUV_MODE_420);
            break;        
        case TD_MIXER_MAINYUV_MIXER:
  //          TD_MixerTestVideoMainYUV_MixerSelect(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        case TD_MIXER_MAINYUV_POSITION:
  //          TD_MixerTestVideoMainYUV_Postion(TD_VIDEO_LAYER_YUV_MODE_420);
            break;        
        case TD_MIXER_MAINYUV_CROP:
 //           TD_MixerTestVideoMainYUV_Crop(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        case TD_MIXER_MAINYUV_JOINT:  ////VO_CASE_LAYER_TD_MIXER_TEST
 //           TD_MixerTestVideoMainYUV_Joint(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        case TD_MIXER_MAINYUV_JOINT_DEBUG:  ////VO_CASE_LAYER_TD_MIXER_TEST
 //           TD_MixerTestVideoMainYUV_Joint_debug(TD_VIDEO_LAYER_YUV_MODE_420);
            break;            
        case TD_MIXER_MAINYUV_ROTATION:
 //           TD_MixerTestVideoMainYUV_MixerMainStream_Rotation(TD_VIDEO_LAYER_YUV_MODE_420);
            break;            
        default:
            break;                
    }
}
/********************************************************************************
*wrap*
*********************************************************************************/
static int TD_TEST_Wrap(TD_WRAP_INFO_S *wrapInfo)
{
    TD_CHECK_POINTER(wrapInfo);
    TD_WRAP_CTL_S WrapCtl;

    TD_DRV_SetWrap(&WrapCtl);

    return 0;
}
/********************************************************************************
*core*
*********************************************************************************/
/*
*rotation
*/
static int TD_TEST_SetRotation(TD_ROT_ALL_INFO_S *rotAllInfo)
{
   TD_CHECK_POINTER(rotAllInfo);


   return 0;
}
/*
*disp
*/
static int TD_TEST_SetDisp(TD_DISP_INFO_S *dispInfo)
{
   TD_CHECK_POINTER(dispInfo);


   return 0;
}
/*
*layer0
*/
static int TD_TEST_SetLayer0(TD_LAYER0_INFO_S *layer0Info,TD_DISP_MIX_INFO_S *dispMixInfo)
{
   TD_CHECK_POINTER(layer0Info);
   TD_CHECK_POINTER(dispMixInfo);

   return 0;
}
/*
*Layer4Osd
*/
static int TD_TEST_SetLayer4Osd(TD_LAYER4_OSD_INFO_S *layer4OsdInfo,TD_DISP_MIX_INFO_S *dispMixInfo)
{
   TD_CHECK_POINTER(layer4OsdInfo);
   TD_CHECK_POINTER(dispMixInfo);


   return 0;
}
/*
*Yuv2Rgb
*/
static int TD_TEST_SetYuv2Rgb(TD_YUV2RGB_INFO_S *yuv2rgbInfo)
{
   TD_CHECK_POINTER(yuv2rgbInfo);


   return 0;
}
/*
*DispAllIrq
*/
static int TD_TEST_SetDispAllIrq(TD_DISP_IRQ_ALL_INFO_S *dispAllIrqInfo)
{
   TD_CHECK_POINTER(dispAllIrqInfo);


   return 0;
}
/*
*WB
*/
static int TD_TEST_SetWB(TD_WB_INFO_S *wbInfo)
{
   TD_CHECK_POINTER(wbInfo);


   return 0;
}
/*
*
*/
static int TD_TEST_Core(unsigned char testCase,TD_CORE_INFO_S *coreInfo)
{
    TD_CHECK_POINTER(coreInfo);
    //

    //
    TD_TEST_SetCore(coreInfo);

    //
    return 0;
}
/********************************************************************************
*td*
*********************************************************************************/
int TD_TEST(unsigned char testCase)
{
    TD_INFO_S tdInfo;

    td_table_init();
    //
    TD_WRAP_INFO_S *wrapInfo = &tdInfo.tdWrapInfo;
    TD_TEST_Wrap(wrapInfo);
    //
    TD_CORE_INFO_S *coreInfo = &tdInfo.tdCoreInfo;
    TD_TEST_Core(testCase,coreInfo);
    //
    return 0;
}
