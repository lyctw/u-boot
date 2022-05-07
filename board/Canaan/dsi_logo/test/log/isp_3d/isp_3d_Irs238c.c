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
#include <stdio.h>
#include <k510.h>
#include <sleep.h>
#include <video/isp_com.h>
#include <video/isp_3d/core/isp_3d_core_drv.h>
#include <video/isp_3d/wrap/isp_3d_wrap_drv.h>

#include "isp_3d/isp_3d.h"
/******************************************************************************
*wrap
******************************************************************************/
static int TOF_TEST_setIrs238cWrap(TOF_WRAP_CONFIG_S *tofWrapInfo,IMAGE_SIZE *imagesize)
{
	TOF_CHECK_POINTER(tofWrapInfo);
	TOF_CHECK_POINTER(imagesize);
	//
	tofWrapInfo->outSizeInfo.tof_out_v_size = imagesize->Height - 1;//320 - 1;
	tofWrapInfo->outSizeInfo.tof_out_h_size = imagesize->Width - 1;//240 - 1;
	//
	TOF_WRAP_BUF_INFO   *bufInfo = &tofWrapInfo->bufInfo;
	bufInfo->tof_depth_buf0_base = 0x1000000;//TOF_BUF_DEPTH;
	bufInfo->tof_depth_buf1_base =0x1000000 ;//TOF_BUF_DEPTH;
	bufInfo->tof_depth_line_stride = TOF_BUF_DEPTH_STRIDE;
	bufInfo->tof_gray_buf0_base = 0x1100000;//TOF_BUF_GRAY;
	bufInfo->tof_gray_buf1_base = 0x1100000;//TOF_BUF_GRAY;
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

    ItcInfo->enSensorType =  TOF_SENSOR_TYPE_TOF;
    ItcInfo->hsync_pol =  0;
    ItcInfo->vsync_pol =  0;
    ItcInfo->hsync_input_timing =  2;
    ItcInfo->vsync_input_timing =  1;
	ItcInfo->itc_sl = 1;
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
	GenInfo->tof_sensor_sel = NO_DPG; //0
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
static int TOF_TEST_setIrs238cCore(TOF_CORE_CONFIG_S *tofCoreInfo,IMAGE_SIZE *imagesize)
{
	TOF_CHECK_POINTER(tofCoreInfo);
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
int TOF_TEST_irs238c(IMAGE_SIZE *imagesize)
{
//	unsigned int width = 224;
//	unsigned int height = 173;
	TOF_CONFIG_S tofConfig;

	TOF_WRAP_CONFIG_S *tofWrapInfo = &tofConfig.tofWrap;
	TOF_TEST_setIrs238cWrap(tofWrapInfo,imagesize);
	//
	TOF_CORE_CONFIG_S *tofCoreInfo = &tofConfig.tofCore;
	TOF_TEST_setIrs238cCore(tofCoreInfo,imagesize);

	return 0;
}
/******************************************************************************
*
******************************************************************************/
void InitIsp3D_Irs238c(void)
{
	  writel(0x38,   TOF_CORE_REG_BASE + 0x00 );  //ISP_3D_ITC_CTL_OFFSET      ,
	   writel(1999,  TOF_CORE_REG_BASE + 0x04 );  //ISP_3D_ITC_TTL_V_OFFSET    ,
	   writel(999 ,  TOF_CORE_REG_BASE + 0x08 );  //ISP_3D_ITC_TTL_H_OFFSET    ,
	   writel(0x1 ,  TOF_CORE_REG_BASE + 0x0c );  //ISP_3D_ITC_STT_VR_OFFSET   ,
	   writel(0x4 ,  TOF_CORE_REG_BASE + 0x10 );  //ISP_3D_ITC_STT_HR_OFFSET   ,
	   writel(224 ,  TOF_CORE_REG_BASE + 0x14 ); //ISP_3D_WIDTH_IN_OFFSET     ,
	   writel(173 ,  TOF_CORE_REG_BASE + 0x18 );  //ISP_3D_HEIGHT_IN_OFFSET    ,
	   writel(5   ,  TOF_CORE_REG_BASE + 0x1c );  //ISP_3D_ITC_STT_LN_OFFSET
	                                                                                    ;
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x20 ); //ISP_3D_SENSOR_SL_OFFSET    ,
	   writel(0x80,  TOF_CORE_REG_BASE + 0x28 );  //ISP_3D_GRAY_TH_OFFSET      ,
	   writel(2   ,  TOF_CORE_REG_BASE + 0x24 );  //ISP_3D_TOF_GEN_CTL_OFFSET  ,
	                                                                                    ;
	   writel(0x3 ,  TOF_CORE_REG_BASE + 0x50 );  //ISP_3D_AE_CTL_OFFSET       ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x54 );  //ISP_3D_AE_WIN_STTH_OFFSET  ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x58 );  //ISP_3D_AE_WIN_STTV_OFFSET  ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x5c );  //ISP_3D_AE_WIN_ENDH_OFFSET  ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x60 );  //ISP_3D_AE_WIN_ENDV_OFFSET  ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x64 );  //ISP_3D_AE_YOBJ_OFFSET      ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x68 );  //ISP_3D_AE_AV_RG_OFFSET     ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x6c );  //ISP_3D_AE_EXP_L_OFFSET     ,

	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x74 );  //ISP_3D_AE_AGC_OFFSET       ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x78 );  //ISP_3D_AE_CHG_CNT_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x7c );  //ISP_3D_AE_NUM_MAX_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x80 );  //ISP_3D_AE_EXP_MAX_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x84 );  //ISP_3D_AE_EXP_MID_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x88 );  //ISP_3D_AE_EXP_MIN_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x8c );  //ISP_3D_AE_AGC_MAX_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x90 );  //ISP_3D_AE_AGC_MID_OFFSET   ,
	   writel(0x0 ,  TOF_CORE_REG_BASE + 0x94 );  //ISP_3D_AE_AGC_MIN_OFFSET   ,
	   writel(0xf ,	 TOF_CORE_REG_BASE + 0x1e4 );    //ISP_3D_NR2D_CTL_OFFSET     ,
	   writel(0x10,	 TOF_CORE_REG_BASE + 0x1e8 );    //ISP_3D_NR2D_RAW_YK_OFFSET  ,
	   writel(0x10,	 TOF_CORE_REG_BASE + 0x1ec );    //ISP_3D_NR2D_RAW_DK_OFFSET  ,
	   writel(0xf1,	 TOF_CORE_REG_BASE + 0x254 );    //ISP_3D_POST_CTL_OFFSET     ,
	   writel(0x80,	 TOF_CORE_REG_BASE + 0x258 );    //ISP_3D_CTRST_GAIN_OFFSET   ,
	   writel(0x80,	 TOF_CORE_REG_BASE + 0x25c );     //ISP_3D_LUMA_GAIN_OFFSET    ,
	   writel(0x10,	 TOF_CORE_REG_BASE + 0x260 );     //ISP_3D_DEPTH_CTRST_OFFSET  ,
	   writel(0x0 ,	 TOF_CORE_REG_BASE + 0x320 );     //ISP_3D_RAM_WR_RDY_OFFSET   ,

	    //core wrap  register config
	    writel(0x000000FF, TOF_WRAP_REG_BASE + 0x00); //00,                                   ISP_3D_CTRL_SWRST_OFFSET
	    writel(0x0000000F, TOF_WRAP_REG_BASE + 0x04); //01,                                  ISP_3D_CTRL_DMA_SWRST_OFFSET
	    writel(0x0000000C, TOF_WRAP_REG_BASE + 0x08); //02, 0x00000F74 wdr3f [5]:1 else 0     ISP_3D_CTRL_MODE_OFFSET
	    writel(0x0000FFFF, TOF_WRAP_REG_BASE + 0x0c); //03,                                  ISP_3D_CTRL_CLK_EN_OFFSET
	    writel(0x00000001, TOF_WRAP_REG_BASE + 0x10); //04,                                  ISP_3D_CTRL_DMA_EN_OFFSET
	    writel(0x00000000, TOF_WRAP_REG_BASE + 0x14); //05,                                    ISP_3D_CTRL_PIXEL_FORMAT_ISP_OFFSET
	    writel(0x00000009, TOF_WRAP_REG_BASE + 0x18); //06,                                    ISP_3D_CTRL_PIXEL_FORMAT_OUT_OFFSET
	    writel(0x00df00ac, TOF_WRAP_REG_BASE + 0x1c); //07,320x240                                ISP_3D_CTRL_VH_SIZE_ACTIVE_OFFSET


	    writel(0x00000003, TOF_WRAP_REG_BASE + 0x3c); //08,                 ISP_3D_CTRL_ARB_MODE_OFFSET
	    writel(0x01010101, TOF_WRAP_REG_BASE + 0x40); //09,                     ISP_3D_CTRL_WEIGHT_WR_0_OFFSET
	    writel(0x01010101, TOF_WRAP_REG_BASE + 0x44);//0A,                   ISP_3D_CTRL_WEIGHT_WR_1_OFFSET
	    writel(0x01010101, TOF_WRAP_REG_BASE + 0x48) ;  //0F,                   ISP_3D_CTRL_WEIGHT_RD_0_OFFSET
	    writel(0x01010101, TOF_WRAP_REG_BASE + 0x4c) ;  //10,         ISP_3D_CTRL_WEIGHT_RD_1_OFFSET
	    writel(0x01010101, TOF_WRAP_REG_BASE + 0x50) ;  //11,         ISP_3D_CTRL_PRIORITY_WR_OFFSET
	    writel(0x01010101, TOF_WRAP_REG_BASE + 0x54) ;  //12,         ISP_3D_CTRL_PRIORITY_RD_OFFSET
	    writel(0x76543210, TOF_WRAP_REG_BASE + 0x58) ;  //13,      ISP_3D_CTRL_ID_WR_OFFSET
	    writel(0x76543210, TOF_WRAP_REG_BASE + 0x5c) ;  //14,      ISP_3D_CTRL_ID_RD_OFFSET

	    writel(0x20000000, TOF_WRAP_REG_BASE + 0x98) ;  //17,     ISP_3D_CTRL_FRAME_BASE_ADDR0_Y_OFFSET
	    writel(0x20000000, TOF_WRAP_REG_BASE + 0x9c) ;  //18,     ISP_3D_CTRL_FRAME_BASE_ADDR1_Y_OFFSET
	    writel(0x20200000, TOF_WRAP_REG_BASE + 0xa0) ;  //19,     ISP_3D_CTRL_FRAME_BASE_ADDR0_UV_OFFSET
	    writel(0x20200000, TOF_WRAP_REG_BASE + 0xa4) ;  //1A,     ISP_3D_CTRL_FRAME_BASE_ADDR1_UV_OFFSET
	    writel(0x01000100, TOF_WRAP_REG_BASE + 0xa8) ;  //1B,   `SP_3D_CTRL_HSTRIDE_Y_UV_OFFSET

	    writel(0x10008008, TOF_WRAP_REG_BASE + 0xc0) ;  //20,   ISP_3D_CTRL_CH0_DMA_MODE_OFFSET
	    writel(0x00011000, TOF_WRAP_REG_BASE + 0xc8) ;  //21,   ISP_3D_CTRL_CH0_ERROR_UNIT_TH_OFFSET
	    writel(0x00000000, TOF_WRAP_REG_BASE + 0xd0) ;  //22,   ISP_3D_CTRL_CH0_INFO_CLR_RST_REQ_OFFSET
	    writel(0x10008008, TOF_WRAP_REG_BASE + 0xc4) ;  //23,   ISP_3D_CTRL_CH1_DMA_MODE_OFFSET
	    writel(0x00000000, TOF_WRAP_REG_BASE + 0xcc) ;  //24,   ISP_3D_CTRL_CH1_ERROR_UNIT_TH_OFFSET
	    writel(0x00000000, TOF_WRAP_REG_BASE + 0xd4) ;  //25,   ISP_3D_CTRL_CH1_INFO_CLR_RST_REQ_OFFSET
	    writel(0x00000000, TOF_WRAP_REG_BASE + 0xd8) ;  //26,   ISP_3D_CTRL_AXI_SWRST_REQ_OFFSET
	    //writel(0x00000001, TOF_WRAP_REG_BASE + 0xdc) ;  //27,   ISP_3D_CTRL_CONFIG_DONE_OFFSET


}
