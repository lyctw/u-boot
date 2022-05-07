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
#include <video/video_subsystem_addr.h>
#include "isp_3d/isp_3d.h"
 
//unsigned int  *reg_tof_wrap_base  = NULL;
//unsigned int  *reg_tof_core_base  = NULL;

TOF_DRV_CTL_S g_asttofDrvCtx[TOF_MAX_DEV_NUM];
#define TOF_DRV_GET_CTX(TofDev) (&g_asttofDrvCtx[TofDev]);
/*
*
*/
static int TOF_DRV_Remap(void)
{
	TOF_DRV_Wrap_Remap();
	TOF_DRV_Core_Remap();

	return SUCCESS;
}
/****************************************************************************
 * OSAL FUNCTION DECLARATION                                            *
 ****************************************************************************/
int *osal_tof_memset(void *str,int c,int count)
{
    memset(str, c, count);
    return 0;
}
/*
*
*/
int TOF_DRV_Init( void )
{
    int Ret = 0;

    Ret = TOF_DRV_Remap( );

    for(int DevIndex=0; DevIndex< TOF_MAX_DEV_NUM; DevIndex++)
    {
    	osal_tof_memset(&g_asttofDrvCtx[DevIndex], 0, sizeof(TOF_DRV_CTL_S));
    }

    return Ret;
}
/****************************************************************************
 * wrap                                            *
 ****************************************************************************/
/*
*rst
*/
static int TOF_TEST_GetRst(TOF_WRAP_CTL_SWRST_S  *stSwRst)
{
	TOF_CHECK_POINTER(stSwRst);

    stSwRst->tof_wrap_com_pipe_rst  = 1;
    stSwRst->tof_wrap_cfg_pipe_rst  = 1;
    stSwRst->tof_core_com_pipe_rst  = 1;
    stSwRst->tof_core_cfg_pipe_rst  = 1;
    stSwRst->tof_out_depth_pipe_rst = 1;
    stSwRst->tof_out_gray_pipe_rst  = 1;
    stSwRst->tof_pixel_clk_pipe_rst = 1;
    stSwRst->tof_pixel_div6_clk_pipe_rst = 1;
    stSwRst->tof_depth_dma_ch_rst = 1;
    stSwRst->tof_gray_dma_ch_rst  = 1;
    stSwRst->tof_axi_wr_ch_rst    = 1;
    stSwRst->tof_axi_rd_ch_rst    = 1; 

	return 0;
}
/*
*ctl mode
*/
static int TOF_TEST_GetCtlMode(TOF_WRAP_CTL_MODE_S  *stCtlMode)
{
	TOF_CHECK_POINTER(stCtlMode);
	
	stCtlMode->tof_out_ch_sel = 0;
	stCtlMode->tof_dvp_input_ch_type = 1;
    stCtlMode->tof_dma_chl_sel = 1;

	return 0;
}
/*
*clock
*/
static int TOF_TEST_GetClkEn(TOF_WRAP_CTL_CLK_EN_S *stClkEn)
{
	TOF_CHECK_POINTER(stClkEn);

    stClkEn->tof_wrap_com_clk_en    = 1;
    stClkEn->tof_wrap_cfg_clk_en    = 1;
    stClkEn->tof_core_com_clk_en    = 1;
    stClkEn->tof_core_cfg_clk_en    = 1;
    stClkEn->tof_out_depth_clk_en   = 1;
    stClkEn->tof_out_gray_clk_en    = 1;
    stClkEn->tof_core_sensor_clk_en = 1;
    stClkEn->tof_axi_wr_clk_en      = 1;
    stClkEn->tof_axi_rd_clk_en      = 1;

	return 0;
}
/*
*out size
*/
static int TOF_TEST_GetOutSize(TOF_WRAP_OUT_SIZE_INFO *outSizeInfo,TOF_WRAP_OUT_SIZE_S *stOutSize)
{
	TOF_CHECK_POINTER(outSizeInfo);
	TOF_CHECK_POINTER(stOutSize);

	stOutSize->tof_out_v_size = outSizeInfo->tof_out_v_size;
	stOutSize->tof_out_h_size = outSizeInfo->tof_out_h_size;

	return 0;
}	
/*
*dma mode
*/
static int TOF_TEST_GetDmaMode(TOF_WRAP_DMA_MODE_INFO *dmaModeInfo,TOF_WRAP_DMA_MODE_S *stDmaMode)
{
	TOF_CHECK_POINTER(dmaModeInfo);
	TOF_CHECK_POINTER(stDmaMode);
	unsigned int dmaChNum = 0;

	TOF_WRAP_DMA_ARB_MODE_S *DmaArbMode = &stDmaMode->stDmaArbMode;
	DmaArbMode->tof_dma_wr_arb_mode = 1;
	DmaArbMode->tof_dma_rd_arb_mode = 1;
	//
	for(dmaChNum = 0;dmaChNum<TOF_DMA_CH_NUM;dmaChNum++)
	{
    	stDmaMode->wr_dma_ch_id[dmaChNum] = dmaChNum;
    	stDmaMode->rd_dma_ch_id[dmaChNum] = dmaChNum;
	}
	//
    stDmaMode->wr_dma_ch_weight[0] = 0x1;
	stDmaMode->wr_dma_ch_weight[1] = 0x0;
    stDmaMode->wr_dma_ch_weight[2] = 0x1;
	stDmaMode->wr_dma_ch_weight[3] = 0x0;
    stDmaMode->wr_dma_ch_weight[4] = 0x1;
	stDmaMode->wr_dma_ch_weight[5] = 0x0;
    stDmaMode->wr_dma_ch_weight[6] = 0x1;
	stDmaMode->wr_dma_ch_weight[7] = 0x0;
	//
    stDmaMode->rd_dma_ch_weight[0] = 0x1;
	stDmaMode->rd_dma_ch_weight[1] = 0x0;
    stDmaMode->rd_dma_ch_weight[2] = 0x1;
	stDmaMode->rd_dma_ch_weight[3] = 0x0;
    stDmaMode->rd_dma_ch_weight[4] = 0x1;
	stDmaMode->rd_dma_ch_weight[5] = 0x0;
    stDmaMode->rd_dma_ch_weight[6] = 0x1;
	stDmaMode->rd_dma_ch_weight[7] = 0x0;
	//
    stDmaMode->wr_dma_ch_priority[0] = 0x1;
	stDmaMode->wr_dma_ch_priority[1] = 0x0;
    stDmaMode->wr_dma_ch_priority[2] = 0x1;
	stDmaMode->wr_dma_ch_priority[3] = 0x0;
    stDmaMode->wr_dma_ch_priority[4] = 0x1;
	stDmaMode->wr_dma_ch_priority[5] = 0x0;
    stDmaMode->wr_dma_ch_priority[6] = 0x1;
	stDmaMode->wr_dma_ch_priority[7] = 0x0;
	//
    stDmaMode->rd_dma_ch_priority[0] = 0x1;
	stDmaMode->rd_dma_ch_priority[1] = 0x0;
    stDmaMode->rd_dma_ch_priority[2] = 0x1;
	stDmaMode->rd_dma_ch_priority[3] = 0x0;
    stDmaMode->rd_dma_ch_priority[4] = 0x1;
	stDmaMode->rd_dma_ch_priority[5] = 0x0;
    stDmaMode->rd_dma_ch_priority[6] = 0x1;
	stDmaMode->rd_dma_ch_priority[7] = 0x0;
	//
	TOF_WRAP_DMA_CFG_S   *DmaCh0Cfg = &stDmaMode->stDmaCh0Cfg;
    DmaCh0Cfg->tof_wr_outst        = 0x8;
    DmaCh0Cfg->tof_rd_outst        = 0x0;
    DmaCh0Cfg->tof_wr_burstl       = 0x0;
    DmaCh0Cfg->tof_rd_burstl       = 0x0;
    DmaCh0Cfg->tof_y_uv_noncon_en  = 0x0;
    DmaCh0Cfg->tof_y_uv_swap_en    = 0x1;
    DmaCh0Cfg->tof_wr_int_line_num = 0x0;
    DmaCh0Cfg->tof_wr_err_dec_en   = 0x1;
	DmaCh0Cfg->tof_rd_err_dec_en   = 0x0;
	//
	TOF_WRAP_DMA_ERR_DEC_CFG_S  *DmaCh0ErrCfg = &stDmaMode->stDmaCh0ErrCfg;
    DmaCh0ErrCfg->tof_wr_err_dec_unit = 0x00;
    DmaCh0ErrCfg->tof_rd_err_dec_unit = 0x10;
    DmaCh0ErrCfg->tof_wr_err_gen_thr  = 0x01;
    DmaCh0ErrCfg->tof_rd_err_gen_thr  = 0x00;
	//
    TOF_WRAP_DMA_CFG_S  *DmaCh1Cfg = &stDmaMode->stDmaCh1Cfg;
    DmaCh1Cfg->tof_wr_outst        = 0x8;
    DmaCh1Cfg->tof_rd_outst        = 0x0;
    DmaCh1Cfg->tof_wr_burstl       = 0x0;
    DmaCh1Cfg->tof_rd_burstl       = 0x0;
    DmaCh1Cfg->tof_y_uv_noncon_en  = 0x0;
    DmaCh1Cfg->tof_y_uv_swap_en    = 0x1;
    DmaCh1Cfg->tof_wr_int_line_num = 0x0;
    DmaCh1Cfg->tof_wr_err_dec_en   = 0x1;
	DmaCh1Cfg->tof_rd_err_dec_en   = 0x0;
	//
	TOF_WRAP_DMA_ERR_DEC_CFG_S *DmaCh1ErrCfg = &stDmaMode->stDmaCh1ErrCfg;
    DmaCh1ErrCfg->tof_wr_err_dec_unit = 0x0;
    DmaCh1ErrCfg->tof_rd_err_dec_unit = 0x0;
    DmaCh1ErrCfg->tof_wr_err_gen_thr  = 0x0;
    DmaCh1ErrCfg->tof_rd_err_gen_thr  = 0x0;

	return 0;
}
/*
*buf
*/
static int TOF_TEST_GetBufInfo(TOF_WRAP_BUF_INFO *bufInfo,TOF_WRAP_BUF_S *stBuf)
{
	TOF_CHECK_POINTER(bufInfo);
	TOF_CHECK_POINTER(stBuf);

	stBuf->tof_depth_buf0_base = bufInfo->tof_depth_buf0_base;
	stBuf->tof_depth_buf1_base = bufInfo->tof_depth_buf1_base;
	stBuf->tof_depth_line_stride = bufInfo->tof_depth_line_stride;
	stBuf->tof_gray_buf0_base = bufInfo->tof_gray_buf0_base;
	stBuf->tof_gray_buf1_base = bufInfo->tof_gray_buf1_base;
	stBuf->tof_gray_line_stride = bufInfo->tof_gray_line_stride;

	return 0;
}
/*
*axi
*/
static int TOF_TEST_GetAxiCtl(TOF_WRAP_AXI_CTL_S *stAxiCtl)
{
	TOF_CHECK_POINTER(stAxiCtl);

    stAxiCtl->tof_axi_wr_ch_rst_req = 0x0;//0x1;
    stAxiCtl->tof_axi_rd_ch_rst_req = 0x0;//0x1;
    stAxiCtl->tof_axi_wr_swrst_ready = 0x0;//0x1;
    stAxiCtl->tof_axi_rd_swrst_ready = 0x0;//0x1;

	return 0;
}
/*
*Int Mask
*/
static int TOF_TEST_GetIntMask(TOF_WRAP_INT_CTL_INFO *intCtlInfo,TOF_WRAP_INT_CTL_S *stIntMask)
{
	TOF_CHECK_POINTER(intCtlInfo);
	TOF_CHECK_POINTER(stIntMask);

    stIntMask->tof_core_int_st_in_msk         =  1;
    stIntMask->tof_core_int_st_itc_out_msk    =  1;
    stIntMask->tof_core_int_st_demo_out_msk   =  1;
    stIntMask->tof_core_int_st_ae_out_msk     =  1;
    stIntMask->tof_core_int_st_img_out_msk    =  1;
    stIntMask->tof_dma_wr_int_gray_frame_msk  =  1;
    stIntMask->tof_dma_wr_int_gray_line_msk   =  1;
    stIntMask->tof_dma_wr_int_gray_frame_err_msk  =  1;
    stIntMask->tof_dma_wr_int_gray_imm_err_msk    =  1;
    stIntMask->tof_dma_wr_int_depth_frame_msk     =  1;
    stIntMask->tof_dma_wr_int_depth_line_msk      =  1;
    stIntMask->tof_dma_wr_int_depth_frame_err_msk =  1;
    stIntMask->tof_dma_wr_int_depth_imm_err_msk   =  1;

	return 0;
}
/*
*
*/
int TOF_TEST_setWrap(TOF_WRAP_CONFIG_S *tofWrapInfo)
{
	TOF_CHECK_POINTER(tofWrapInfo);
	TOF_WRAP_ATTR_S  tofWrapAttr;
	//rst
    TOF_WRAP_CTL_SWRST_S *stSwRst = &tofWrapAttr.stSwRst;
	TOF_TEST_GetRst(stSwRst);
	//
    TOF_WRAP_CTL_MODE_S  *stCtlMode = &tofWrapAttr.stMode;
	TOF_TEST_GetCtlMode(stCtlMode);
	//
    TOF_WRAP_CTL_CLK_EN_S   *stClkEn = &tofWrapAttr.stClkEn;
    TOF_TEST_GetClkEn(stClkEn);
	//
    tofWrapAttr.tof_wrap_dma_out_en = 1;
    tofWrapAttr.ctrl_pixel_format_isp = 0; //reserved
    tofWrapAttr.tof_out_pixel_format = 9;
	//
    TOF_WRAP_OUT_SIZE_S     *stOutSize = &tofWrapAttr.stOutSize;
	TOF_WRAP_OUT_SIZE_INFO *outSizeInfo = &tofWrapInfo->outSizeInfo;
	TOF_TEST_GetOutSize(outSizeInfo,stOutSize);
	//
    TOF_WRAP_DMA_MODE_S     *stDmaMode = &tofWrapAttr.stDmaMode;
	TOF_WRAP_DMA_MODE_INFO *dmaModeInfo = &tofWrapInfo->dmaModeInfo;
	TOF_TEST_GetDmaMode(dmaModeInfo,stDmaMode);
	//
    TOF_WRAP_BUF_S    *stBuf = &tofWrapAttr.stBuf;
	TOF_WRAP_BUF_INFO *bufInfo = &tofWrapInfo->bufInfo;
	TOF_TEST_GetBufInfo(bufInfo,stBuf);
	//
    TOF_WRAP_AXI_CTL_S   *stAxiCtl = &tofWrapAttr.stAxiCtl;
	TOF_TEST_GetAxiCtl(stAxiCtl);
	//
	tofWrapAttr.stCfgDone.tof_wrap_config_done_en = 1;
	//
    TOF_WRAP_INT_CTL_S   *stIntMask = &tofWrapAttr.stIntMask;
    TOF_WRAP_INT_CTL_INFO *intCtlInfo = &tofWrapInfo->intCtlInfo;
	TOF_TEST_GetIntMask(intCtlInfo,stIntMask);
	//
	TOF_DRV_setWrap(&tofWrapAttr);
	//
	TOF_DRV_GetWrapRegsVal();
	return 0;
}
/****************************************************************************
 * core                                           *
 ****************************************************************************/
/*
*itc
*/
static int ISP_TEST_GetItcCtl(TOF_CORE_ITC_INFO *ItcInfo,TOF_CORE_ITC_ATTR_S *pstItcAttr)
{
	TOF_CHECK_POINTER(ItcInfo);
	TOF_CHECK_POINTER(pstItcAttr);

	pstItcAttr->hsync_pol = ItcInfo->hsync_pol;
	pstItcAttr->vsync_pol =  ItcInfo->vsync_pol;
	pstItcAttr->hsync_input_timing =  ItcInfo->hsync_input_timing;
	pstItcAttr->vsync_input_timing =  ItcInfo->vsync_input_timing;
	pstItcAttr->itc_sl =  ItcInfo->itc_sl;
	pstItcAttr->tof_itc_height =  ItcInfo->tof_itc_height;
	pstItcAttr->tof_itc_width =  ItcInfo->tof_itc_width;
	pstItcAttr->tof_itc_v_start =  ItcInfo->tof_itc_v_start;
	pstItcAttr->tof_itc_h_start =  ItcInfo->tof_itc_h_start;
	pstItcAttr->tof_itc_active_width =  ItcInfo->tof_itc_active_width;
	pstItcAttr->tof_itc_active_height =  ItcInfo->tof_itc_active_height;
	pstItcAttr->tof_itc_active_start_line =  ItcInfo->tof_itc_active_start_line;

	return 0;
}
/*
*gen
*/
static int ISP_TEST_GetGenCtl(TOF_CORE_GEN_INFO *GenInfo,TOF_CORE_GEN_ATTR_S *pstGenAttr)
{
	TOF_CHECK_POINTER(GenInfo);
	TOF_CHECK_POINTER(pstGenAttr);

    pstGenAttr->tof_gray_sel = GenInfo->tof_gray_sel;
    pstGenAttr->tof_dm_sel = GenInfo->tof_dm_sel;
    pstGenAttr->tof_sensor_sel = GenInfo->tof_sensor_sel;
    pstGenAttr->tof_depth_pol_sel = GenInfo->tof_depth_pol_sel;
    pstGenAttr->tof_pwm_order_cfg = GenInfo->tof_pwm_order_cfg;
    pstGenAttr->tof_cwm_order_cfg = GenInfo->tof_cwm_order_cfg;

	return 0;
}
/*
*gray th
*/
static int ISP_TEST_GetGrayThCtl(TOF_CORE_GRAY_TH_INFO *GrayThInfo,TOF_CORE_GRAY_TH_ATTR_S *pstGrayTHAttr)
{
	TOF_CHECK_POINTER(GrayThInfo);
	TOF_CHECK_POINTER(pstGrayTHAttr);

	pstGrayTHAttr->tof_gray_th = GrayThInfo->tof_gray_th;

	return 0;
}
/*
*ae
*/
static int ISP_TEST_GetAeCtl(TOF_CORE_AE_INFO *AeInfo,TOF_CORE_AE_ATTR_S *pstAeAttr)
{
	TOF_CHECK_POINTER(AeInfo);
	TOF_CHECK_POINTER(pstAeAttr);

    pstAeAttr->ae_as_en = AeInfo->ae_as_en;
    pstAeAttr->ae_ag_en = AeInfo->ae_ag_en;
    pstAeAttr->ae_airis_en = AeInfo->ae_airis_en;
    pstAeAttr->ae_enter_lock_sel = AeInfo->ae_enter_lock_sel;

    pstAeAttr->ae_exit_lock_sel = AeInfo->ae_exit_lock_sel;
    pstAeAttr->ae_win_mode_sel = AeInfo->ae_win_mode_sel;
    pstAeAttr->ae_back_light_mode_sel = AeInfo->ae_back_light_mode_sel;

    pstAeAttr->ae_win_h_start = AeInfo->ae_win_h_start;
    pstAeAttr->ae_win_v_start = AeInfo->ae_win_v_start;
    pstAeAttr->ae_win_h_end = AeInfo->ae_win_h_end;
    pstAeAttr->ae_win_v_end = AeInfo->ae_win_v_end;

    pstAeAttr->ae_tar_bright = AeInfo->ae_tar_bright;
    pstAeAttr->ae_tar_bright_range = AeInfo->ae_tar_bright_range;
    pstAeAttr->ae_ex_time = AeInfo->ae_ex_time;
    pstAeAttr->ae_agc = AeInfo->ae_agc;

    pstAeAttr->ae_ad_freq = AeInfo->ae_ad_freq;
    pstAeAttr->ae_ad_step_max = AeInfo->ae_ad_step_max;

    pstAeAttr->ae_ex_value_max = AeInfo->ae_ex_value_max;
    pstAeAttr->ae_ex_value_mid = AeInfo->ae_ex_value_mid;
    pstAeAttr->ae_ex_value_min = AeInfo->ae_ex_value_min;

    pstAeAttr->ae_gain_value_max = AeInfo->ae_gain_value_max;
    pstAeAttr->ae_gain_value_mid = AeInfo->ae_gain_value_mid;
    pstAeAttr->ae_gain_value_min = AeInfo->ae_gain_value_min;

	return 0;
}
/*
*nr2d
*/
static int ISP_TEST_GetNr2dCtl(TOF_CORE_NR2D_INFO *Nr2dInfo,TOF_CORE_NR2D_ATTR_S *pstNr2dAttr)
{
	TOF_CHECK_POINTER(Nr2dInfo);
	TOF_CHECK_POINTER(pstNr2dAttr);

    pstNr2dAttr->tof_gray_dpc_en = Nr2dInfo->tof_gray_dpc_en;
    pstNr2dAttr->tof_depth_dpc_en = Nr2dInfo->tof_depth_dpc_en;
    pstNr2dAttr->tof_2dnr_gray_en = Nr2dInfo->tof_2dnr_gray_en;
    pstNr2dAttr->tof_2dnr_depth_en = Nr2dInfo->tof_2dnr_depth_en;
    pstNr2dAttr->tof_2dnr_gray = Nr2dInfo->tof_2dnr_gray;
    pstNr2dAttr->tof_2dnr_depth = Nr2dInfo->tof_2dnr_depth;

	return 0;
}
/*
*post
*/
static int ISP_TEST_GetPostCtl(TOF_CORE_POST_INFO *PostInfo,TOF_CORE_POST_ATTR_S *pstPostAttr)
{
	TOF_CHECK_POINTER(PostInfo);
	TOF_CHECK_POINTER(pstPostAttr);

    pstPostAttr->tof_output_sel = PostInfo->tof_output_sel;
    pstPostAttr->tof_hsync_pol_sel = PostInfo->tof_hsync_pol_sel;
    pstPostAttr->tof_vsync_pol_sel = PostInfo->tof_vsync_pol_sel;
    pstPostAttr->tof_gray_gmma_en = PostInfo->tof_gray_gmma_en;
    pstPostAttr->tof_depth_cont_ad_en = PostInfo->tof_depth_cont_ad_en;

    pstPostAttr->tof_gray_cont_en = PostInfo->tof_gray_cont_en;
    pstPostAttr->tof_gray_luma_ad_en = PostInfo->tof_gray_luma_ad_en;

    pstPostAttr->tof_cont_ad_intensity = PostInfo->tof_cont_ad_intensity;
    pstPostAttr->tof_luma_ad_intensity = PostInfo->tof_luma_ad_intensity;
    pstPostAttr->tof_Depth_cont_ad_intensity = PostInfo->tof_Depth_cont_ad_intensity;

	return 0;
}
/*
*
*/
int TOF_TEST_setCore(TOF_CORE_CONFIG_S *tofCoreInfo)
{
	TOF_CHECK_POINTER(tofCoreInfo);
	TOF_CORE_ATTR_S  tofCoreAttr;
	//
	TOF_CORE_ITC_ATTR_S *pstItcAttr = &tofCoreAttr.stItcAttr;
    TOF_CORE_ITC_INFO  *ItcInfo = &tofCoreInfo->ItcInfo;
	ISP_TEST_GetItcCtl(ItcInfo,pstItcAttr);
    //
    tofCoreAttr.eSensorType = ItcInfo->enSensorType;
	//
	TOF_CORE_GEN_ATTR_S *pstGenAttr = &tofCoreAttr.stGenAttr;
	TOF_CORE_GEN_INFO  *GenInfo = &tofCoreInfo->GenInfo;
	ISP_TEST_GetGenCtl(GenInfo,pstGenAttr);
	//
    TOF_CORE_GRAY_TH_ATTR_S *pstGrayTHAttr = &tofCoreAttr.stGrayTHAttr;
    TOF_CORE_GRAY_TH_INFO *GrayThInfo = &tofCoreInfo->GrayThInfo;
	ISP_TEST_GetGrayThCtl(GrayThInfo,pstGrayTHAttr);
	//
	TOF_CORE_AE_ATTR_S *pstAeAttr = &tofCoreAttr.stAeAttr;
    TOF_CORE_AE_INFO   *AeInfo = &tofCoreInfo->AeInfo;
	ISP_TEST_GetAeCtl(AeInfo,pstAeAttr);
	//
	TOF_CORE_NR2D_ATTR_S *pstNr2dAttr = &tofCoreAttr.stNr2dAttr;
    TOF_CORE_NR2D_INFO *Nr2dInfo = &tofCoreInfo->Nr2dInfo;
	ISP_TEST_GetNr2dCtl(Nr2dInfo,pstNr2dAttr);
	//
	TOF_CORE_POST_ATTR_S *pstPostAttr = &tofCoreAttr.stPostAttr;
    TOF_CORE_POST_INFO *PostInfo = &tofCoreInfo->PostInfo;
	ISP_TEST_GetPostCtl(PostInfo,pstPostAttr);
	//
	TOF_DRV_setCore(&tofCoreAttr);
	//
	TOF_DRV_GetCoreRegsVal();
	return 0;
}
