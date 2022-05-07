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
#include "vi/vi.h"
/************************************************************
*irs238c
*************************************************************/
/*
*wrap
*/
static int VI_TEST_Setirs238cWrap(VI_WRAP_CONFIG_S *viwrapInfo )
{
	VI_CHECK_POINTER(viwrapInfo);
	//
	viwrapInfo->dphy_mode = 1;
	viwrapInfo->sony_mode = SONY_POL_MODE_DIS;
	//
	MIPI0_SENSOR_INFO *mipi0Info = &viwrapInfo->sensor_info.mipi0Info;
	mipi0Info->sensor_interface_enable = 1;
	mipi0Info->mipi_mode = 0;
	mipi0Info->wdr_mode = ISP_PIPE_WDR_NONE;
	mipi0Info->isp_pipeline = ISP_TOF;
	mipi0Info->tpgEn = TRUE;
	//
	MIPI1_SENSOR_INFO *mipi1Info = &viwrapInfo->sensor_info.mipi1Info;
	mipi1Info->sensor_interface_enable = 0;
	mipi1Info->mipi_mode = 0;
	//
	DVP_SENSOR_INFO   *dvpInfo = &viwrapInfo->sensor_info.dvpInfo;
	dvpInfo->sensor_interface_enable = 0;
	//dvpInfo->mipi_mode = NORMAL_MODE;
	//dvpInfo->tpgEn = FALSE;
	//dvpInfo->isp_pipeline = ISP_R_2K;
	//
	VI_TEST_SetWrap(viwrapInfo);
	return 0;
}
/*
 *
*/
static int VI_TEST_Setjxf23sirs238cWrap(VI_WRAP_CONFIG_S *viwrapInfo )
{
	VI_CHECK_POINTER(viwrapInfo);
	//
	viwrapInfo->dphy_mode = 1;
	viwrapInfo->sony_mode = SONY_POL_MODE_DIS;
	//
	MIPI0_SENSOR_INFO *mipi0Info = &viwrapInfo->sensor_info.mipi0Info;
	mipi0Info->sensor_interface_enable = 1;
	mipi0Info->mipi_mode = 0;
	mipi0Info->wdr_mode = ISP_PIPE_WDR_NONE;
	mipi0Info->isp_pipeline = ISP_TOF;
	mipi0Info->tpgEn = TRUE;
	//
	MIPI1_SENSOR_INFO *mipi1Info = &viwrapInfo->sensor_info.mipi1Info;
	mipi1Info->sensor_interface_enable = 0;
	mipi1Info->mipi_mode = 0;
	//
	DVP_SENSOR_INFO   *dvpInfo = &viwrapInfo->sensor_info.dvpInfo;
	dvpInfo->sensor_interface_enable = 1;
	dvpInfo->mipi_mode = NORMAL_MODE;
	dvpInfo->tpgEn = FALSE;
	dvpInfo->isp_pipeline = ISP_R_2K;
	//
	VI_TEST_SetWrap(viwrapInfo);
	return 0;
}

/*
*pipe
*/
static int VI_TEST_Setirs238cPipeCtrl(VI_PIPE_CTRL_INFO *ctrlInfo)
{
	VI_CHECK_POINTER(ctrlInfo);

    ctrlInfo->win_mode_en= 1;
    ctrlInfo->emb_en= 0;
    ctrlInfo->hsync_vsync_out_en= 1;
    ctrlInfo->sensor_input_swap_en= 0; 

    ctrlInfo->sync_source_sel= 0;
    ctrlInfo->input_ch_sel= 1;
    ctrlInfo->ch_mode_sel= 1;
    ctrlInfo->emb_enable= 0;

	ctrlInfo->isp_clk_pol= 1;
	ctrlInfo->isp_field_pol= 1;
	ctrlInfo->isp_hsync_pol= 1;
	ctrlInfo->isp_vsync_pol= 1;

	ctrlInfo->sen_mipi_clk_pol= 1;
	ctrlInfo->sen_mipi_field_pol = 1;
	ctrlInfo->sen_mipi_hsync_pol = 0;
	ctrlInfo->sen_mipi_vsync_pol = 0;

    ctrlInfo->emb_mode_sel= 0;
    ctrlInfo->emb_ecc_mode_en= 0;
    ctrlInfo->sync_code_remove_en= 0;
    ctrlInfo->sync_code_ext_en= 0;

	return 0;
}
/*
*timing
*/
static int VI_TEST_Setirs238cTimingCtrl(VI_PIPE_TIMING_CTRL_INFO *timingInfo)
{
	VI_CHECK_POINTER(timingInfo);

    timingInfo->input_pixel_type= 0; /*RAW input*/
    timingInfo->input_yuv_format= 0;
    timingInfo->output_yuv_format= 0;
    timingInfo->yuv_order= 0;

    timingInfo->raw_pixel_width= 2; /*RAW 10bit*/
    timingInfo->data_out_timming_ctrl= 3;/*tree cycle delay*/
    timingInfo->sync_mode= 4;
    timingInfo->sync_pulse_mode= 4;
   // timingInfo->emb_timeout_set= ;
	return 0;
}
/*
*sync width
*/
static int VI_TEST_Setirs238cSyncWidth(VI_PIPE_SYNC_WIDTH_INFO *syncwidthInfo)
{
	VI_CHECK_POINTER(syncwidthInfo);

	syncwidthInfo->image_hsync_width = 0x7;
	syncwidthInfo->image_vsync_width = 0x7;

	return 0;
}
/*
*image size
*/
static int VI_TEST_Setirs238cImageSize(VI_IMAGE_SZIE_INFO *imageSizeInfo)
{
	VI_CHECK_POINTER(imageSizeInfo);

	imageSizeInfo->vi_pipe_tpg_w_size_total.Width = 0x14a;//0x897;
	imageSizeInfo->vi_pipe_tpg_w_size_total.Height = 0x3fff;//0x464;

	imageSizeInfo->vi_pipe_tpg_w_size_active.Width = 0xdf;//0x781;
	imageSizeInfo->vi_pipe_tpg_w_size_active.Height = 0x614;//0x437;
	imageSizeInfo->vi_pipe_tpg_w_size_active.Width_st = 0x0;//0x0;
	imageSizeInfo->vi_pipe_tpg_w_size_active.Height_st = 0x3fff;//0x1fff;

	return 0;
}
/*
*tpg info
*/
static int VI_TEST_Setirs238cTpgInfo(VI_TPG_INFO  *tpgInfo)
{
	VI_CHECK_POINTER(tpgInfo);
	//
	VI_PIPE_TPG_DMA_INFO  *viTpgDmaInfo = &tpgInfo->viTpgDmaInfo;
    viTpgDmaInfo->dma_y_module_en     = TRUE;
    viTpgDmaInfo->dma_uv_module_en    = FALSE;
    viTpgDmaInfo->dma_tpg_read_en     = TRUE;
    viTpgDmaInfo->sync_out_en         = TRUE;
    viTpgDmaInfo->sw_triger_en        = TRUE;
    viTpgDmaInfo->dma_wr_ch_err_dec_en= TRUE;
    viTpgDmaInfo->dma_rd_ch_err_dec_en= TRUE;
	//
	tpgInfo->vi_pipe_w_addr_y0= 0x100000;//0x30000000;//ISP_TPG_W_Y_BUF;
	tpgInfo->vi_pipe_w_addr_y1= 0x100000;//0x30000000;//ISP_TPG_W_Y_BUF;
	tpgInfo->vi_pipe_w_addr_uv0= 0x200000;//0x00500000;//ISP_TPG_W_UV_BUF;
	tpgInfo->vi_pipe_w_addr_uv1= 0x200000;//;0x00D00000;//ISP_TPG_W_UV_BUF;
	tpgInfo->vi_pipe_w_addr_stride_y= 0x180;//ISP_TPG_W_Y_STRIDE;
	tpgInfo->vi_pipe_w_addr_stride_uv= 0x0;//ISP_TPG_W_UV_STRIDE;
	tpgInfo->vi_pipe_r_addr_y0= 0x300000;//0x30010380;//ISP_TPG_R_Y_BUF;
	tpgInfo->vi_pipe_r_addr_y1= 0x300000;//0x30010380;//ISP_TPG_R_Y_BUF;
	tpgInfo->vi_pipe_r_addr_stride_y= 0x180;//ISP_TPG_R_Y_STRIDE;
	//
	IMAGE_SIZE 	 *vi_pipe_tpg_r_size_total  = &tpgInfo->vi_pipe_tpg_r_size_total;
	vi_pipe_tpg_r_size_total->Width = 0x3e7;//0x897;
	vi_pipe_tpg_r_size_total->Height =  0x7cf;//0x464;
	//
	CROP_SIZE    *vi_pipe_tpg_r_size_active  = &tpgInfo->vi_pipe_tpg_r_size_active;
	vi_pipe_tpg_r_size_active->Width_st = 0x10;
	vi_pipe_tpg_r_size_active->Width =  0xdf;//0x781;
	vi_pipe_tpg_r_size_active->Height_st = 0x10;
	vi_pipe_tpg_r_size_active->Height =  0x2b3;//0x437;
	//

	VI_PIPE_DMA_CTRL_INFO *dmaCtrlInfo  = &tpgInfo->dmaCtrlInfo;

    dmaCtrlInfo->dma_y_outstand   = 0x0;
    dmaCtrlInfo->dma_uv_outstand  = 0x0;
    dmaCtrlInfo->dma_raw_outstand = 0x0;
    dmaCtrlInfo->dma_y_blen       = 0x8;
    dmaCtrlInfo->dma_uv_blen      = 0x0;
    dmaCtrlInfo->dma_raw_blen     = 0x0;
    dmaCtrlInfo->dma_y_uv_out_swap= 0;
    dmaCtrlInfo->dma_int_line_num = 0x0;

	return 0;
}
/*
*isp tpg
*/
static int VI_TEST_Setirs238cIspTpg(VI_ISP_TPG_INFO *ispTpgInfo)
{
	VI_CHECK_POINTER(ispTpgInfo);

	ispTpgInfo->vi_pipe_tpg_en= TRUE;
	ispTpgInfo->vi_pipe_tpg_frm_ratio_mode= 0x0;
	ispTpgInfo->vi_pipe_tpg_frm_ratio= 0x1;
	ispTpgInfo->vi_tpg_sync_timing_gen_mode= 0x1;

	return 0;
}
/*
*tof tpg
*/
static int VI_TEST_Setirs238cTofTpg(VI_TOF_TPG_INFO *tofTpgInfo)
{
	VI_CHECK_POINTER(tofTpgInfo);

	tofTpgInfo->tof_mode_enable= TRUE;
	tofTpgInfo->vi_pipe_tpg_tof_frm_num= 0x3;
	tofTpgInfo->vi_pipe_tpg_tof_frm_stride= 0x10380;//0x8;

	return 0;
}
/*
*
*/
static int VI_TEST_Setirs238cPipe(unsigned char s8Index,VI_PIPE_CONFIG_S *vipipeInfo)
{
	VI_CHECK_POINTER(vipipeInfo);
	//
	VI_PIPE_CTRL_INFO *ctrlInfo = &vipipeInfo->ctrlInfo;
	VI_TEST_Setirs238cPipeCtrl(ctrlInfo);
	//
	VI_PIPE_TIMING_CTRL_INFO *timingInfo = &vipipeInfo->timingInfo;
	VI_TEST_Setirs238cTimingCtrl(timingInfo);
	//
	VI_PIPE_SYNC_WIDTH_INFO *syncwidthInfo = &vipipeInfo->syncwidthInfo;
	VI_TEST_Setirs238cSyncWidth(syncwidthInfo);
	//
	VI_IMAGE_SZIE_INFO *imageSizeInfo = &vipipeInfo->imageSizeInfo;
	VI_TEST_Setirs238cImageSize(imageSizeInfo);
	//
	VI_TPG_INFO  *tpgInfo = &vipipeInfo->tpgInfo;
	VI_TEST_Setirs238cTpgInfo(tpgInfo);
	//
	VI_ISP_TPG_INFO	*ispTpgInfo = &vipipeInfo->ispTpgInfo;
	VI_TEST_Setirs238cIspTpg(ispTpgInfo);
	//
	VI_TOF_TPG_INFO	*tofTpgInfo = &vipipeInfo->tofTpgInfo;
	VI_TEST_Setirs238cTofTpg(tofTpgInfo);
	//
	VI_TEST_SetPipe(s8Index,vipipeInfo);
	return 0;
}

/*
*
*/
int VI_TEST_irs238c(void)
{
	VI_WRAP_CONFIG_S viwrapInfo;
	VI_PIPE_CONFIG_S vipipeInfo;
	//
	VI_TEST_Setirs238cWrap(&viwrapInfo);
	//
	int s8Index = VI_MIPI_CSI00_PIPE_ID;//VI_DVP_0_PIPE_ID;//6;
	VI_TEST_Setirs238cPipe(s8Index,&vipipeInfo);
	
	return 0;
}
/*
*
*/
int VI_TEST_DVP_jxf23s_irs238c(void)
{
	VI_WRAP_CONFIG_S viwrapInfo;
	VI_PIPE_CONFIG_S vipipeInfo;
	//
	VI_TEST_Setjxf23sirs238cWrap(&viwrapInfo);
	//
	int s8Index = VI_MIPI_CSI00_PIPE_ID;//VI_DVP_0_PIPE_ID;//6;
	VI_TEST_Setirs238cPipe(s8Index,&vipipeInfo);
	//
	s8Index = VI_DVP_0_PIPE_ID;//6;
	VI_TEST_Setjxf23sPipe(s8Index,&vipipeInfo);

	return 0;
}
