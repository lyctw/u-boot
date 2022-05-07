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

#include <video/isp_com.h>
#include "isp_3d/isp_3d.h"
#include <video/isp_3d/core/isp_3d_core_drv.h>
#include <video/isp_3d/wrap/isp_3d_wrap_drv.h>
/******************************************************************************
*wrap
******************************************************************************/
static int TOF_TEST_setOpn8008Wrap(TOF_WRAP_CONFIG_S *tofWrapInfo,IMAGE_SIZE *imagesize)
{
	TOF_CHECK_POINTER(tofWrapInfo);
	TOF_CHECK_POINTER(imagesize);
	//
	tofWrapInfo->outSizeInfo.tof_out_v_size = imagesize->Width - 1;//320 - 1;
	tofWrapInfo->outSizeInfo.tof_out_h_size = imagesize->Height - 1;//240 - 1;
	//
	TOF_WRAP_BUF_INFO   *bufInfo = &tofWrapInfo->bufInfo;
	bufInfo->tof_depth_buf0_base = TOF_BUF_DEPTH;
	bufInfo->tof_depth_buf1_base = TOF_BUF_DEPTH;
	bufInfo->tof_depth_line_stride = TOF_BUF_DEPTH_STRIDE;
	bufInfo->tof_gray_buf0_base = TOF_BUF_GRAY;
	bufInfo->tof_gray_buf1_base = TOF_BUF_GRAY;
	bufInfo->tof_gray_line_stride = TOF_BUF_GRAY_STRIDE;
	//
	TOF_TEST_setWrap(tofWrapInfo);
	return 0;
}

/******************************************************************************
*core
******************************************************************************/
/*
*itc
*/
static int TOF_TEST_setItc(TOF_CORE_ITC_INFO *ItcInfo,IMAGE_SIZE *imagesize)
{
	TOF_CHECK_POINTER(ItcInfo);
	TOF_CHECK_POINTER(imagesize);

    ItcInfo->enSensorType =  TOF_SENSOR_TYPE_TOF;
    ItcInfo->hsync_pol =  0;
    ItcInfo->vsync_pol =  0;
    ItcInfo->hsync_input_timing =  2;
    ItcInfo->vsync_input_timing =  1;
    ItcInfo->tof_itc_height = 1999;//0x5c4;
    ItcInfo->tof_itc_width =  999;//497;
    ItcInfo->tof_itc_v_start =  0x1;
    ItcInfo->tof_itc_h_start =  0x4;
    ItcInfo->tof_itc_active_width =  imagesize->Width;
    ItcInfo->tof_itc_active_height =  imagesize->Height;
    ItcInfo->tof_itc_active_start_line =  5;

	return 0;
}
/*
*gen
*/
static int TOF_TEST_setGen(TOF_CORE_GEN_INFO *GenInfo)
{
	TOF_CHECK_POINTER(GenInfo);

	GenInfo->tof_gray_sel = VISIBLE_INFRARED_LIGHT;//0;
	GenInfo->tof_dm_sel = CWM;//1
	GenInfo->tof_sensor_sel = DPG; //1
	GenInfo->tof_depth_pol_sel = POSTIVE_POL;//0;
	GenInfo->tof_pwm_order_cfg = PWM_ORDER_012;//0;
	GenInfo->tof_cwm_order_cfg = CWM_ORDER_0123;//0;

	return 0;
}
/*
*gray th
*/
static int TOF_TEST_setGrayTh(TOF_CORE_GRAY_TH_INFO *GrayThInfo)
{
	TOF_CHECK_POINTER(GrayThInfo);

	GrayThInfo->tof_gray_th = 0x80;

	return 0;
}
/*
*ae
*/
static int TOF_TEST_setAe(TOF_CORE_AE_INFO *AeInfo)
{
	TOF_CHECK_POINTER(AeInfo);

	AeInfo->ae_as_en = TRUE;
	AeInfo->ae_ag_en = TRUE;
	AeInfo->ae_airis_en = 0;
	AeInfo->ae_enter_lock_sel = 0;
	AeInfo->ae_exit_lock_sel = 0;
	AeInfo->ae_win_mode_sel = 0;
	AeInfo->ae_back_light_mode_sel = 0;
	AeInfo->ae_win_h_start = 0;
	AeInfo->ae_win_v_start = 0;
	AeInfo->ae_win_h_end = 0;
	AeInfo->ae_win_v_end = 0;
	AeInfo->ae_tar_bright = 0;
	AeInfo->ae_tar_bright_range = 0;
	AeInfo->ae_ex_time = 0;
	AeInfo->ae_agc = 0;
	AeInfo->ae_ad_freq = 0;
	AeInfo->ae_ad_step_max = 0;
	AeInfo->ae_ex_value_max = 0;
	AeInfo->ae_ex_value_mid = 0;
	AeInfo->ae_ex_value_min = 0;
	AeInfo->ae_gain_value_max = 0;
	AeInfo->ae_gain_value_mid = 0;
	AeInfo->ae_gain_value_min = 0;

	return 0;
}
/*
*nr2d
*/
static int TOF_TEST_setNr2d(TOF_CORE_NR2D_INFO *Nr2dInfo)
{
	TOF_CHECK_POINTER(Nr2dInfo);

	Nr2dInfo->tof_gray_dpc_en = TRUE;
	Nr2dInfo->tof_depth_dpc_en = TRUE;
	Nr2dInfo->tof_2dnr_gray_en = TRUE;
	Nr2dInfo->tof_2dnr_depth_en = TRUE;
	Nr2dInfo->tof_2dnr_gray = 0x10;
	Nr2dInfo->tof_2dnr_depth = 0x10;

	return 0;
}
/*
*post
*/
static int TOF_TEST_setPost(TOF_CORE_POST_INFO *PostInfo)
{
	TOF_CHECK_POINTER(PostInfo);

	PostInfo->tof_output_sel = 1;
	PostInfo->tof_hsync_pol_sel = 0;
	PostInfo->tof_vsync_pol_sel = 0;
	PostInfo->tof_gray_gmma_en = TRUE;
	PostInfo->tof_gray_cont_en = TRUE;
    PostInfo->tof_gray_luma_ad_en = TRUE;
    PostInfo->tof_depth_cont_ad_en = TRUE;
	PostInfo->tof_cont_ad_intensity = 0x80;
	PostInfo->tof_luma_ad_intensity = 0x80;
	PostInfo->tof_Depth_cont_ad_intensity = 0x10;

	return 0;
}
/*
*
*/
static int TOF_TEST_setOpn8008Core(TOF_CORE_CONFIG_S *tofCoreInfo,IMAGE_SIZE *imagesize)
{
	TOF_CHECK_POINTER(tofCoreInfo);
	TOF_CHECK_POINTER(imagesize);
	//
	TOF_CORE_ITC_INFO *ItcInfo = &tofCoreInfo->ItcInfo;
	TOF_TEST_setItc(ItcInfo,imagesize);
	//
	TOF_CORE_GEN_INFO *GenInfo = &tofCoreInfo->GenInfo;
	TOF_TEST_setGen(GenInfo);
	//
	TOF_CORE_GRAY_TH_INFO *GrayThInfo = &tofCoreInfo->GrayThInfo;
	TOF_TEST_setGrayTh(GrayThInfo);
	//
	TOF_CORE_AE_INFO *AeInfo = &tofCoreInfo->AeInfo;
	TOF_TEST_setAe(AeInfo);
	//
	TOF_CORE_NR2D_INFO *Nr2dInfo = &tofCoreInfo->Nr2dInfo;
	TOF_TEST_setNr2d(Nr2dInfo);
	//
	TOF_CORE_POST_INFO *PostInfo = &tofCoreInfo->PostInfo;
	TOF_TEST_setPost(PostInfo);
	//
	TOF_TEST_setCore(tofCoreInfo);
	return 0;
}
/******************************************************************************
*
******************************************************************************/
int TOF_TEST_opn8008(IMAGE_SIZE *imagesize)
{
//	unsigned int width = 320;
//	unsigned int height = 240;
	TOF_CONFIG_S tofConfig;

	TOF_WRAP_CONFIG_S *tofWrapInfo = &tofConfig.tofWrap;
	TOF_TEST_setOpn8008Wrap(tofWrapInfo,imagesize);
	//
	TOF_CORE_CONFIG_S *tofCoreInfo = &tofConfig.tofCore;
	TOF_TEST_setOpn8008Core(tofCoreInfo,imagesize);

	return 0;
}
