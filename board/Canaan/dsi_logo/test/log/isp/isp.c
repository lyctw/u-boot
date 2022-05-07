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
#include "isp/isp.h"
#include <io.h>
#include <video/isp/wrap/isp_wrap_reg.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

ISP_DRV_CTL_S g_astispDrvCtx[ISP_MAX_DEV_NUM];
#define ISP_DRV_GET_CTX(IspDev) (&g_astispDrvCtx[IspDev]);

unsigned int  *reg_isp_2k_wrap_base  = NULL;
unsigned int  *reg_isp_2k_core_base  = NULL;
unsigned int  *reg_isp_2k_ds_base    = NULL;
unsigned int  *reg_isp_2k_table_base = NULL;
unsigned int  *reg_isp_2k_mfbc_base  = NULL;
unsigned int  *reg_isp_2k_mfbd_base  = NULL;
unsigned int  *reg_isp_2k_remap_base = NULL;
/*
*
*/
int ISP_DRV_Remap(ISP_PIPE_MODE_E enIspMode)
{
	switch(enIspMode)
	{
		case ISP_PIPE_MODE_4K:
			{
				reg_isp_2k_wrap_base 	= (unsigned int *)ISP_4K_WRAP_REG_BASE;
				reg_isp_2k_core_base 	= (unsigned int *)ISP_4K_CORE_REG_BASE;
				reg_isp_2k_ds_base 		= (unsigned int *)ISP_4K_DS_REG_BASE;
                reg_isp_2k_table_base 	= (unsigned int *)ISP_4K_TABLE_REG_BASE;
				reg_isp_2k_mfbc_base 	= (unsigned int *)ISP_4K_MFBC_REG_BASE;
				reg_isp_2k_mfbd_base 	= (unsigned int *)ISP_4K_MFBD_REG_BASE;
                reg_isp_2k_remap_base 	= (unsigned int *)ISP_4K_REMAP_REG_BASE;
			}
			break;
		case ISP_PIPE_MODE_F2K:
			{
				reg_isp_2k_wrap_base 	= (unsigned int *)ISP_2K_WRAP_REG_BASE;
				reg_isp_2k_core_base 	= (unsigned int *)ISP_2K_CORE_REG_BASE;
				reg_isp_2k_ds_base 		= (unsigned int *)ISP_2K_DS_REG_BASE;
                reg_isp_2k_table_base 	= (unsigned int *)ISP_2K_TABLE_REG_BASE;
				reg_isp_2k_mfbc_base 	= (unsigned int *)ISP_2K_MFBC_REG_BASE;
				reg_isp_2k_mfbd_base 	= (unsigned int *)ISP_2K_MFBD_REG_BASE;
                reg_isp_2k_remap_base 	= (unsigned int *)ISP_2K_REMAP_REG_BASE;
			}
			break;
		case ISP_PIPE_MODE_R2K:
			{
				reg_isp_2k_wrap_base 	= (unsigned int *)ISP_R2K_WRAP_REG_BASE;
				reg_isp_2k_core_base 	= (unsigned int *)ISP_R2K_CORE_REG_BASE;
				reg_isp_2k_ds_base 		= (unsigned int *)ISP_R2K_DS_REG_BASE;
				reg_isp_2k_table_base 	= (unsigned int *)ISP_2K_TABLE_REG_BASE;
				reg_isp_2k_remap_base 	= (unsigned int *)ISP_2K_REMAP_REG_BASE;
			}
			break;
		case ISP_PIPE_MODE_TOF:
			{
	//			reg_tof_wrap_base = (unsigned int *)TOF_WRAP_REG_BASE;
	//			reg_tof_core_base = (unsigned int *)TOF_CORE_REG_BASE;
			}
			break;
		default:
			break;

	}
	
	return 0;
}

/****************************************************************************
 * OSAL FUNCTION DECLARATION                                            *
 ****************************************************************************/
void * osal_isp_memset(void *str,int c,int count)
{
    return memset(str, c, count);
}
/****************************************************************************
 * PUBLIC FUNCTION DECLARATION                                          *
 ****************************************************************************/
int ISP_DRV_Init(ISP_PIPE_MODE_E enIspMode)
{
    int Ret = 0;
    int DevIndex = 0;
	
    Ret = ISP_DRV_Remap(enIspMode);

    if(FAILURE == Ret)
    {
        return Ret;
    }
    
    for(DevIndex=0; DevIndex<ISP_MAX_DEV_NUM; DevIndex++)
    {
        osal_isp_memset(&g_astispDrvCtx[DevIndex], 0, sizeof(ISP_DRV_CTL_S));
    }	
	
    return Ret;
}
/****************************************************************************
 * isp wrap                                         *
 ****************************************************************************/
/*
*DMA config
*/
static int ISP_TEST_GetWrapComCLK(ISP_WRAP_PIPE_CLK_CTL_S *pstPipeClkCtl)
{
	ISP_CHECK_POINTER(pstPipeClkCtl);

	pstPipeClkCtl->axi_rd_ch_en = 1;
	pstPipeClkCtl->axi_wr_ch_en = 1;
	pstPipeClkCtl->core_cfg_clk_en = 1;
	pstPipeClkCtl->core_com_clk_en = 1;
	pstPipeClkCtl->wrap_cfg_clk_en = 1;
	pstPipeClkCtl->wrap_com_clk_en =1;

	return 0;
}
/*
*WDR config
*/
static int ISP_TEST_GetWrapWdr(ISP_WRAP_WDR_S *wdrInfo,ISP_WRAP_WDR_ATTR_S *pstWdrAttr)
{
	ISP_CHECK_POINTER(wdrInfo);
	ISP_CHECK_POINTER(pstWdrAttr);

    ISP_WRAP_WDR_CLK_CTL_S          *stWdrClkCtl = &pstWdrAttr->stWdrClkCtl;
	ISP_WRAP_WDR_DMA_EN_CTL_S       *stWdrDmaEn = &pstWdrAttr->stWdrDmaEn;
    ISP_WRAP_WDR_MODE_CTL_S         *stWdrModeCtl = &pstWdrAttr->stWdrModeCtl;
	if( ISP_PIPE_WDR_2_FRAME == wdrInfo->wdr_mode)
	{
		stWdrClkCtl->wdr_2_frame_clk_en = 1;
		stWdrClkCtl->wdr_3_frame_clk_en = 0;
		stWdrDmaEn->wdr_short_dma_en = 1;//1
		stWdrDmaEn->wdr_long_dma_en  = 0;
		stWdrModeCtl->wdr_dynamic_switch_en = 0;
		stWdrModeCtl->wdr_long_l2_buf_depth = 0;
		stWdrModeCtl->wdr_long_ch_mode = 0;
		stWdrModeCtl->wdr_long_l2_buf_en = 0;
		stWdrModeCtl->wdr_short_s1_buf_en = 0;//1
	}
	else if(ISP_PIPE_WDR_3_FRAME == wdrInfo->wdr_mode)
	{
		stWdrClkCtl->wdr_2_frame_clk_en = 0;
		stWdrClkCtl->wdr_3_frame_clk_en = 1;
		stWdrDmaEn->wdr_short_dma_en = 1; //1?
		stWdrDmaEn->wdr_long_dma_en  = 1;
		stWdrModeCtl->wdr_dynamic_switch_en = 0;
		stWdrModeCtl->wdr_long_l2_buf_depth = 20;
		stWdrModeCtl->wdr_long_ch_mode = 0;
		stWdrModeCtl->wdr_long_l2_buf_en = 0; //1?
		stWdrModeCtl->wdr_short_s1_buf_en = 0;//1
	}
	else
	{
		stWdrClkCtl->wdr_2_frame_clk_en = 0;
		stWdrClkCtl->wdr_3_frame_clk_en = 0;
		stWdrDmaEn->wdr_short_dma_en = 0;
		stWdrDmaEn->wdr_long_dma_en  = 0;
		stWdrModeCtl->wdr_dynamic_switch_en = 0;
		stWdrModeCtl->wdr_long_l2_buf_depth = 0;
		stWdrModeCtl->wdr_long_ch_mode = 0;
		stWdrModeCtl->wdr_long_l2_buf_en = 0;
		stWdrModeCtl->wdr_short_s1_buf_en = 0;				
	}

    ISP_WRAP_WDR_PIXEL_FORMAT_CTL_S *stWdrPixelFormat = &pstWdrAttr->stWdrPixelFormat;
	stWdrPixelFormat->wdr_long_img_format = ISP_RGBRAW_DATA;
	stWdrPixelFormat->wdr_long_img_out_format = IN_YUV422;
	stWdrPixelFormat->wdr_long_pixel_width = PIXEL_12;
	stWdrPixelFormat->wdr_long_yuv422_pxl_order = YUYV;
	stWdrPixelFormat->wdr_long_yuv_in_format =IN_YUV422;

    ISP_WRAP_WDR_BUF_S              *stWdrBuf = &pstWdrAttr->stWdrBuf;
	stWdrBuf->wdr_buf_base = 0x0;
	stWdrBuf->wdr_buf_size = 0x0;
	stWdrBuf->wdr_line_stride = 0x0;
	return 0;
}
/*
*3DNR config
*/
static int ISP_TEST_GetWrap3dnr(ISP_WRAP_3DNR_S *nr3dInfo,ISP_WRAP_3DNR_ATTR_S *pst3dnrAttr)
{
	ISP_CHECK_POINTER(nr3dInfo);
	ISP_CHECK_POINTER(pst3dnrAttr);

	if( 1 == nr3dInfo->nr3d_en) 
	{
		pst3dnrAttr->clk_3dnr_en = 1;
		pst3dnrAttr->pipe_3dnr_dma_en = 1;
		pst3dnrAttr->nr3d_mfbcd_en = 0;
		pst3dnrAttr->nr3d_mv_out_en = 0;
		if( 1 == nr3dInfo->nr3d_mfbcd_en)
		{
			pst3dnrAttr->nr3d_mfbcd_en = 1;
		}
		if( 1 == nr3dInfo->nr3d_mv_out_en)
		{
			pst3dnrAttr->nr3d_mv_out_en = 1;
		}
	}
	else
	{
		pst3dnrAttr->clk_3dnr_en = 0;
		pst3dnrAttr->pipe_3dnr_dma_en = 0;
		pst3dnrAttr->nr3d_mfbcd_en = 0;
		pst3dnrAttr->nr3d_mv_out_en = 0;
	}
	
    ISP_WRAP_3DNR_PIXEL_FORMAT_CTL_S *st3DnrPixelFormat = &pst3dnrAttr->st3DnrPixelFormat;
	st3DnrPixelFormat->y_3dnr_img_format = ISP_RGBRAW_DATA;
	st3DnrPixelFormat->y_3dnr_img_out_format = IN_YUV422;
	st3DnrPixelFormat->y_3dnr_pixel_width = PIXEL_12;
	st3DnrPixelFormat->y_3dnr_yuv422_pxl_order = YUYV;
	st3DnrPixelFormat->y_3dnr_yuv_in_format = IN_YUV422;
	st3DnrPixelFormat->uv_3dnr_img_format = ISP_RGBRAW_DATA;
	st3DnrPixelFormat->uv_3dnr_img_out_format = IN_YUV422;
	st3DnrPixelFormat->uv_3dnr_pixel_width = PIXEL_8;
	st3DnrPixelFormat->uv_3dnr_yuv422_pxl_order = YUYV;
	st3DnrPixelFormat->uv_3dnr_yuv_in_format = IN_YUV422;

    ISP_WRAP_3DNR_BUF_S             *st3dnrBuf = &pst3dnrAttr->st3dnrBuf;
    st3dnrBuf->y_3dnr_buf_base = ISP_BUF_3DNR_Y;
    st3dnrBuf->uv_3dnr_buf_base = ISP_BUF_3DNR_UV;
    st3dnrBuf->y_3dnr_line_stride = ISP_BUF_3DNR_Y_STRIDE;
    st3dnrBuf->uv_3dnr_line_stride = ISP_BUF_3DNR_UV_STRIDE;
	return 0;
}
/*
*LDC config
*/
static int ISP_TEST_GetWrapLdc(ISP_WRAP_LDC_S  *ldcInfo,ISP_WRAP_LDC_ATTR_S *pstLdcAttr)
{
	ISP_CHECK_POINTER(ldcInfo);
	ISP_CHECK_POINTER(pstLdcAttr);
	if( 1 == ldcInfo->ldc_en)
	{
		pstLdcAttr->ldc_clk_en = 1;
		pstLdcAttr->ldc_dma_en = 1;
	}
	else
	{
		pstLdcAttr->ldc_clk_en = 0;
		pstLdcAttr->ldc_dma_en = 0;
	}	

    ISP_WRAP_LDC_BUF_S              *stLdcBuf = &pstLdcAttr->stLdcBuf;
    stLdcBuf->ldc_y_buf_base = ISP_BUF_LDC_Y;
    stLdcBuf->ldc_uv_buf_base = ISP_BUF_LDC_UV;
    stLdcBuf->ldc_y_line_stride = ISP_BUF_LDC_Y_STRIDE;
    stLdcBuf->ldc_uv_line_stride = ISP_BUF_LDC_UV_STRIDE;
	return 0;
}
/*
*Main OUT config
*/
static int ISP_TEST_GetWrapMainOut(ISP_WRAP_MAIN_S	*mainInfo,ISP_WRAP_MAINOUT_ATTR_S *pstMainOutAttr)
{
	ISP_CHECK_POINTER(mainInfo);
	ISP_CHECK_POINTER(pstMainOutAttr);

	if( 1 == mainInfo->main_out_en)
	{
		pstMainOutAttr->main_out_clk_en = 1;
		pstMainOutAttr->main_out_dma_en = 1;
		pstMainOutAttr->pix_remap_main_en = mainInfo->main_pix_remap_en;
	}
	else
	{
		pstMainOutAttr->main_out_clk_en = 0;
		pstMainOutAttr->main_out_dma_en = 0;
	}
	
    ISP_WRAP_MAIN_PIXEL_FORMAT_CTL_S *stMainPixelFormat = &pstMainOutAttr->stMainPixelFormat;
	stMainPixelFormat->main_out_img_format = ISP_YUV_DATA;
	stMainPixelFormat->main_out_img_out_format = IN_YUV420;
	stMainPixelFormat->main_out_pixel_width = PIXEL_8;
	stMainPixelFormat->main_out_yuv422_pxl_order = YUYV;
	stMainPixelFormat->main_out_yuv_in_format = IN_YUV422;

    ISP_WRAP_MAIN_OUT_SIZE_S        *stMainOutSize = &pstMainOutAttr->stMainOutSize;
	stMainOutSize->main_out_h_size = mainInfo->main_size.Width - 1;
	stMainOutSize->main_out_v_size = mainInfo->main_size.Height - 1;

    ISP_WRAP_MAIN_BUF_S             *stMainBuf = &pstMainOutAttr->stMainBuf;
    stMainBuf->main_y_buf0_base = ISP_BUF_MAIN_Y;
    stMainBuf->main_y_buf1_base = ISP_BUF_MAIN_Y;
    stMainBuf->main_uv_buf0_base = ISP_BUF_MAIN_UV;
    stMainBuf->main_uv_buf1_base = ISP_BUF_MAIN_UV;
    stMainBuf->main_y_line_stride = ISP_BUF_MAIN_Y_STRIDE;
    stMainBuf->main_uv_line_stride = ISP_BUF_MAIN_UV_STRIDE;
	return 0;	
}
/*
*DS0 OUT config
*/
static int ISP_TEST_GetWrapDs0Out(ISP_WRAP_DS0_S *ds0Info,ISP_WRAP_DS0OUT_ATTR_S *pstDs0OutAttr)
{
	ISP_CHECK_POINTER(pstDs0OutAttr);
    ISP_WRAP_DS0_CLK_CTL_S          *stDs0ClkCtl = &pstDs0OutAttr->stDs0ClkCtl;
    ISP_WRAP_DS0_DMA_EN_CTL_S       *stDs0DmaEn = &pstDs0OutAttr->stDs0DmaEn;
	if(1 == ds0Info->ds0_out_en)
	{
		stDs0ClkCtl->ds0_out_clk_en = 1;
		stDs0ClkCtl->ds0_out_y_ch_clk_en = 1;
		stDs0ClkCtl->ds0_out_uv_ch_clk_en = 1;
		stDs0ClkCtl->ds_out0_osd0_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd1_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd2_ch_clk_en = 0;
		if( 1 == ds0Info->ds0_osd0_en)
		{
			stDs0ClkCtl->ds_out0_osd0_ch_clk_en = 1;
		}
		if( 1 == ds0Info->ds0_osd1_en)
		{
			stDs0ClkCtl->ds_out0_osd1_ch_clk_en = 1;
		}
		if( 1 == ds0Info->ds0_osd2_en)
		{
			stDs0ClkCtl->ds_out0_osd2_ch_clk_en = 1;
		}
	}
	else
	{
		stDs0ClkCtl->ds0_out_clk_en = 0;
		stDs0ClkCtl->ds0_out_y_ch_clk_en = 0;
		stDs0ClkCtl->ds0_out_uv_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd0_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd1_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd2_ch_clk_en = 0;
	}
	
    pstDs0OutAttr->pix_remap_out0_en = ds0Info->pix_remap_out0_en;

    ISP_WRAP_DS0_PIXEL_FORMAT_CTL_S *stDs0PixelFormat = &pstDs0OutAttr->stDs0PixelFormat;
	stDs0PixelFormat->ds0_out_img_format = ISP_YUV_DATA;
	stDs0PixelFormat->ds0_out_img_out_format = IN_YUV420;
	stDs0PixelFormat->ds0_out_pixel_width = PIXEL_8;
	stDs0PixelFormat->ds0_out_yuv422_pxl_order = YUYV;
	stDs0PixelFormat->ds0_out_yuv_in_format = IN_YUV422;

    ISP_WRAP_DS0_OUT_SIZE_S         *stDs0OutSize = &pstDs0OutAttr->stDs0OutSize;
	stDs0OutSize->ds0_out_h_size = ds0Info->ds0_size.Width - 1;
	stDs0OutSize->ds0_out_v_size = ds0Info->ds0_size.Height - 1;

    ISP_WRAP_DS0_BUF_S              *stDs0Buf = &pstDs0OutAttr->stDs0Buf;
    stDs0Buf->ds0_y_buf0_base = ISP_BUF_DS0_Y;
    stDs0Buf->ds0_y_buf1_base = ISP_BUF_DS0_Y;
    stDs0Buf->ds0_uv_buf0_base = ISP_BUF_DS0_UV;
    stDs0Buf->ds0_uv_buf1_base = ISP_BUF_DS0_UV;
    stDs0Buf->ds0_y_line_stride = ISP_BUF_DS0_Y_STRIDE;
    stDs0Buf->ds0_uv_line_stride = ISP_BUF_DS0_UV_STRIDE;	
	return 0;	
}
/*
*DS1 OUT config
*/
static int ISP_TEST_GetWrapDs1Out(ISP_WRAP_DS1_S *ds1Info,ISP_WRAP_DS1OUT_ATTR_S *pstDs1OutAttr)
{
	ISP_CHECK_POINTER(ds1Info);
	ISP_CHECK_POINTER(pstDs1OutAttr);

    ISP_WRAP_DS1_CLK_CTL_S          *stDs1ClkCtl = &pstDs1OutAttr->stDs1ClkCtl;
    ISP_WRAP_DS1_DMA_EN_CTL_S       *stDs1DmaEn = &pstDs1OutAttr->stDs1DmaEn;
	if( 1 == ds1Info->ds1_out_en)
	{
		stDs1ClkCtl->ds1_out_clk_en  = 1;
		stDs1ClkCtl->ds1_out_y_ch_clk_en = 1;
		stDs1ClkCtl->ds1_out_uv_ch_clk_en = 1;
		stDs1ClkCtl->ds_out1_osd0_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd1_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd2_ch_clk_en = 0;
		if( 1 == ds1Info->ds1_osd0_en)
		{
			stDs1ClkCtl->ds_out1_osd0_ch_clk_en = 0;
		}
		if( 1 == ds1Info->ds1_osd1_en)
		{
			stDs1ClkCtl->ds_out1_osd1_ch_clk_en = 0;
		}
		if( 1 == ds1Info->ds1_osd2_en)
		{
			stDs1ClkCtl->ds_out1_osd2_ch_clk_en = 0;
		}
	}
	else
	{
		stDs1ClkCtl->ds1_out_clk_en  = 0;
		stDs1ClkCtl->ds1_out_y_ch_clk_en = 0;
		stDs1ClkCtl->ds1_out_uv_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd0_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd1_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd2_ch_clk_en = 0;
	}
	
    pstDs1OutAttr->pix_remap_out1_en = ds1Info->pix_remap_out1_en;

    ISP_WRAP_DS1_PIXEL_FORMAT_CTL_S *stDs1PixelFormat = &pstDs1OutAttr->stDs1PixelFormat;
	stDs1PixelFormat->ds1_out_img_format = ISP_YUV_DATA;
	stDs1PixelFormat->ds1_out_img_out_format = IN_YUV420;
	stDs1PixelFormat->ds1_out_pixel_width = PIXEL_8;
	stDs1PixelFormat->ds1_out_yuv422_pxl_order = YUYV;
	stDs1PixelFormat->ds1_out_yuv_in_format = IN_YUV422;
	//
    ISP_WRAP_DS1_OUT_SIZE_S         *stDs1OutSize = &pstDs1OutAttr->stDs1OutSize;
	stDs1OutSize->ds1_out_h_size = ds1Info->ds1_size.Width - 1;
	stDs1OutSize->ds1_out_v_size = ds1Info->ds1_size.Height - 1;
	//
    ISP_WRAP_DS1_BUF_S              *stDs1Buf = &pstDs1OutAttr->stDs1Buf;
    stDs1Buf->ds1_y_buf0_base = ISP_BUF_DS1_Y;
    stDs1Buf->ds1_y_buf1_base = ISP_BUF_DS1_Y;
    stDs1Buf->ds1_uv_buf0_base = ISP_BUF_DS1_UV;
    stDs1Buf->ds1_uv_buf1_base = ISP_BUF_DS1_UV;
    stDs1Buf->ds1_y_line_stride = ISP_BUF_DS1_Y_STRIDE;
    stDs1Buf->ds1_uv_line_stride = ISP_BUF_DS1_Y_STRIDE;	
	return 0;	
}
/*
*DS2 OUT config
*/
static int ISP_TEST_GetWrapDs2Out(ISP_WRAP_DS2_S *ds2Info,ISP_WRAP_DS2OUT_ATTR_S *pstDs2OutAttr)
{
	ISP_CHECK_POINTER(ds2Info);
	ISP_CHECK_POINTER(pstDs2OutAttr);

    ISP_WRAP_DS2_CLK_CTL_S          *stDs2ClkCtl = &pstDs2OutAttr->stDs2ClkCtl;
    ISP_WRAP_DS2_DMA_EN_CTL_S       *stDs2DmaEn = &pstDs2OutAttr->stDs2DmaEn;
	if( 1 == ds2Info->ds2_out_en )
	{
		stDs2ClkCtl->ds2_out_clk_en = 1;
		stDs2ClkCtl->ds2_out_r_ch_clk_en = 1;
		stDs2ClkCtl->ds2_out_g_ch_clk_en = 1;
		stDs2ClkCtl->ds2_out_b_ch_clk_en = 1;
		stDs2ClkCtl->ds_out2_osd0_ch_clk_en = 0;
		stDs2ClkCtl->ds_out2_osd1_ch_clk_en = 0;
		stDs2DmaEn->ds_out2_dma_en = 1 ;
		stDs2DmaEn->ds_out2_r_ch_dma_en = 1;
		stDs2DmaEn->ds_out2_g_ch_dma_en = 1;
		stDs2DmaEn->ds_out2_b_ch_dma_en = 1;
		stDs2DmaEn->ds2_osd0_ch_dma_en = 0;
		stDs2DmaEn->ds2_osd1_ch_dma_en = 0;
		if( 1 == ds2Info->ds2_osd0_en)
		{
			stDs2ClkCtl->ds_out2_osd0_ch_clk_en = 1;
			stDs2DmaEn->ds2_osd0_ch_dma_en = 1;
		}
		if( 1 == ds2Info->ds2_osd1_en)
		{
			stDs2ClkCtl->ds_out2_osd1_ch_clk_en = 1;
			stDs2DmaEn->ds2_osd1_ch_dma_en = 1;
		}
	}
	else
	{
		stDs2ClkCtl->ds2_out_clk_en = 0;
		stDs2ClkCtl->ds2_out_r_ch_clk_en = 0;
		stDs2ClkCtl->ds2_out_g_ch_clk_en = 0;
		stDs2ClkCtl->ds2_out_b_ch_clk_en = 0;
		stDs2ClkCtl->ds_out2_osd0_ch_clk_en = 0;
		stDs2ClkCtl->ds_out2_osd1_ch_clk_en = 0;
		stDs2DmaEn->ds_out2_dma_en = 0 ;
		stDs2DmaEn->ds_out2_r_ch_dma_en = 0;
		stDs2DmaEn->ds_out2_g_ch_dma_en = 0;
		stDs2DmaEn->ds_out2_b_ch_dma_en = 0;
		stDs2DmaEn->ds2_osd0_ch_dma_en = 0;
		stDs2DmaEn->ds2_osd1_ch_dma_en = 0;
	}

    ISP_WRAP_DS2_PIXEL_FORMAT_CTL_S *stDs2PixelFormat = &pstDs2OutAttr->stDs2PixelFormat;
	stDs2PixelFormat->ds2_out_img_format = ISP_RGBRAW_DATA;
	stDs2PixelFormat->ds2_out_img_out_format = OUT_ARGB; 
	stDs2PixelFormat->ds2_out_pixel_width = PIXEL_8;
	stDs2PixelFormat->ds2_out_yuv422_pxl_order = YUYV; //not need
	stDs2PixelFormat->ds2_out_yuv_in_format = IN_YUV422; //not need

    ISP_WRAP_DS2_OUT_SIZE_S         *stDs2OutSize = &pstDs2OutAttr->stDs2OutSize;
	stDs2OutSize->ds2_out_h_size = ds2Info->ds2_size.Width - 1;
	stDs2OutSize->ds2_out_v_size = ds2Info->ds2_size.Height - 1;

    ISP_WRAP_DS2_BUF_S              *stDs2Buf = &pstDs2OutAttr->stDs2Buf;
    stDs2Buf->ds2_r_buf0_base = ISP_BUF_DS2_R;
    stDs2Buf->ds2_r_buf1_base = ISP_BUF_DS2_R;
    stDs2Buf->ds2_g_buf0_base = ISP_BUF_DS2_G;
    stDs2Buf->ds2_g_buf1_base = ISP_BUF_DS2_G;
    stDs2Buf->ds2_b_buf0_base = ISP_BUF_DS2_B;
    stDs2Buf->ds2_b_buf1_base = ISP_BUF_DS2_B;
    stDs2Buf->ds2_r_line_stride = ISP_BUF_DS2_R_STRIDE;
    stDs2Buf->ds2_g_line_stride = ISP_BUF_DS2_G_STRIDE;
    stDs2Buf->ds2_b_line_stride = ISP_BUF_DS2_B_STRIDE;
	return 0;	
}
/*
*DMA config
*/
static int ISP_TEST_GetWrapDmaDefaultConfig(ISP_WRAP_DMA_ATTR_S *pstDmaAttr)
{
    unsigned int DmaChIndex = 0;
    ISP_CHECK_POINTER(pstDmaAttr);
    
	ISP_WRAP_DMA_MODE_S *stDmaChMode = &pstDmaAttr->stDmaChMode;
    stDmaChMode->rd_dma_arb_mode = 0;
    stDmaChMode->wr_dma_arb_mode = 0;

    for(DmaChIndex=0; DmaChIndex<ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stDmaChMode->rd_dma_ch_id[DmaChIndex] = DmaChIndex;
        stDmaChMode->wr_dma_ch_id[DmaChIndex] = DmaChIndex;
        stDmaChMode->rd_dma_ch_weight[DmaChIndex] = 0x01;
        stDmaChMode->wr_dma_ch_weight[DmaChIndex] = 0x01;
        stDmaChMode->rd_dma_ch_priority[DmaChIndex] = ISP_DMA_CH_NUM-DmaChIndex-1;
        stDmaChMode->wr_dma_ch_priority[DmaChIndex] = ISP_DMA_CH_NUM-DmaChIndex-1;
    }

	ISP_WRAP_DMA_CFG_S *stDmaCfg = &pstDmaAttr->stDmaCfg;
    for(DmaChIndex=0; DmaChIndex < ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_ch_outst = 8;
        stDmaCfg->stDmaChcfg[DmaChIndex].rd_ch_outst = 8;
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_ch_burstl = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].rd_ch_burstl = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_int_line_num = 16;
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_err_dec_en = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].rd_err_dec_en = 0;

        if((DmaChIndex > 5) && (DmaChIndex < 8))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 0;
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 1;
        }

        if((DmaChIndex > 7) && (DmaChIndex < 13))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 1;
        }

        if((DmaChIndex > 12))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 1;
        }
    }

    ISP_WRAP_DMA_ERR_DEC_CFG_S *stErrDecCfg = &pstDmaAttr->stErrDecCfg;
    for(DmaChIndex=0; DmaChIndex < ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].wr_err_dec_unit = 1;
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].rd_err_dec_unit = 1;
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].wr_err_gen_thr = 1;
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].rd_err_gen_thr = 1;
    }

	ISP_WRAP_DMA_ERR_STATUS_S *stErrStatus = &pstDmaAttr->stErrStatus;
    for(DmaChIndex=0; DmaChIndex < ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stErrStatus->stDmaErrStatus[DmaChIndex].err_y_wr_status = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_uv_wr_status = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_raw_read_status = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_wr_rst_req = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_rd_rst_req = 0;
    }
    return 0;
}
/*
*axi ctl
*/
int ISP_TEST_GetWrapAxiCtl(ISP_WRAP_AXI_CTL_S *pstAxiCtl)
{
	ISP_CHECK_POINTER(pstAxiCtl);

	pstAxiCtl->axi_wr_ch_rst_req = 1;
	pstAxiCtl->axi_rd_ch_rst_req = 1;
	pstAxiCtl->axi_wr_ch_rst_req = 1;
	pstAxiCtl->axi_rd_ch_state = 1;
	return 0;
}
/*
*int mask
*/
int ISP_TEST_GetWrapIntCtl(ISP_WRAP_INT_CTL_S *pstIntCtl)
{
	ISP_CHECK_POINTER(pstIntCtl);
	//
	ISP_WRAP_CORE_INT_CTL_S *stCoreIntCtl = &pstIntCtl->stCoreIntCtl;
    stCoreIntCtl->int_raw_in_mask= 1 ;  
    stCoreIntCtl->int_3a_mask= 1 ;      
    stCoreIntCtl->raw_int_mask= 1 ;     
    stCoreIntCtl->rgb_int_mask= 1 ;     
    stCoreIntCtl->yuv_int_mask= 1 ;     
    stCoreIntCtl->ldc_int_mask= 1 ;     
    stCoreIntCtl->main_out_int_mask= 1 ;
    stCoreIntCtl->isp_awb_int_mask= 1 ; 
    stCoreIntCtl->isp_ae_int_mask= 1 ;  
    stCoreIntCtl->isp_af_int_mask= 1 ; 
	//
    ISP_WRAP_DMA_WR_INT_MASK0_S *stDmaWRMask0 = &pstIntCtl->stDmaWRMask0;
    stDmaWRMask0->wr_3dnr_y_frm_end_int_mask= 1 ;           
    stDmaWRMask0->wr_3dnr_y_line_base_int_mask= 1 ;         
    stDmaWRMask0->wr_3dnr_y_err_frm_end_int_mask= 1 ;       
    stDmaWRMask0->wr_3dnr_y_err_immediate_int_mask= 1 ;     
    stDmaWRMask0->wr_3dnr_uv_frm_end_int_mask= 1 ;          
    stDmaWRMask0->wr_3dnr_uv_line_base_int_mask= 1 ;        
    stDmaWRMask0->wr_3dnr_uv_err_frm_end_int_mask= 1 ;      
    stDmaWRMask0->wr_3dnr_uv_err_immediate_int_mask= 1 ;    
    stDmaWRMask0->ldc_wr_y_frm_end_int_mask= 1 ;            
    stDmaWRMask0->ldc_wr_y_line_base_int_mask= 1 ;          
    stDmaWRMask0->ldc_wr_y_err_frm_end_int_mask= 1 ;        
    stDmaWRMask0->ldc_wr_y_err_immediate_int_mask= 1 ;      
    stDmaWRMask0->ldc_wr_uv_frm_end_int_mask= 1 ;           
    stDmaWRMask0->ldc_wr_uv_line_base_int_mask= 1 ;         
    stDmaWRMask0->ldc_wr_uv_err_frm_end_int_mask= 1 ;       
    stDmaWRMask0->ldc_wr_uv_err_immediate_int_mask= 1 ;     
    stDmaWRMask0->wdr_wr_raw_frm_end_int_mask= 1 ;          
    stDmaWRMask0->wdr_wr_raw_line_base_int_mask= 1 ;        
    stDmaWRMask0->wdr_wr_raw_err_frm_end_int_mask= 1 ;      
    stDmaWRMask0->wdr_wr_raw_err_immediate_int_mask= 1 ;    

    stDmaWRMask0->main_out_wr_y_frm_end_int_mask= 1 ;       
    stDmaWRMask0->main_out_wr_y_line_base_int_mask= 1 ;     
    stDmaWRMask0->main_out_wr_y_err_frm_end_int_mask= 1 ;   
    stDmaWRMask0->main_out_wr_y_err_immediate_int_mask= 1 ; 
    stDmaWRMask0->main_out_wr_uv_frm_end_int_mask= 1 ;      
    stDmaWRMask0->main_out_wr_uv_line_base_int_mask= 1 ;    
    stDmaWRMask0->main_out_wr_uv_err_frm_end_int_mask= 1 ;  
    stDmaWRMask0->main_out_wr_uv_err_immediate_int_mask= 1 ;
	//	
    ISP_WRAP_DMA_WR_INT_MASK1_S *stDmaWRMask1 = &pstIntCtl->stDmaWRMask1;
    stDmaWRMask1->ds0_out_wr_y_frm_end_mask= 1 ;        
    stDmaWRMask1->ds0_out_wr_y_line_base_mask= 1 ;      
    stDmaWRMask1->ds0_out_wr_y_err_frm_end_mask= 1 ;    
    stDmaWRMask1->ds0_out_wr_y_err_immediate_mask= 1 ;  
    stDmaWRMask1->ds0_out_wr_uv_frm_end_mask= 1 ;       
    stDmaWRMask1->ds0_out_wr_uv_line_base_mask= 1 ;     
    stDmaWRMask1->ds0_out_wr_uv_err_frm_end_mask= 1 ;   
    stDmaWRMask1->ds0_out_wr_uv_err_immediate_mask= 1 ; 
    stDmaWRMask1->ds1_out_wr_y_frm_end_mask= 1 ;        
    stDmaWRMask1->ds1_out_wr_y_line_base_mask= 1 ;      
    stDmaWRMask1->ds1_out_wr_y_err_frm_end_mask= 1 ;    
    stDmaWRMask1->ds1_out_wr_y_err_immediate_mask= 1 ;  
    stDmaWRMask1->ds1_out_wr_uv_frm_end_mask= 1 ;       
    stDmaWRMask1->ds1_out_wr_uv_line_base_mask= 1 ;     
    stDmaWRMask1->ds1_out_wr_uv_err_frm_end_mask= 1 ;   
    stDmaWRMask1->ds1_out_wr_uv_err_immediate_mask= 1 ; 
    stDmaWRMask1->ds2_out_wr_r_frm_end_mask= 1 ;        
    stDmaWRMask1->ds2_out_wr_r_line_base_mask= 1 ;      
    stDmaWRMask1->ds2_out_wr_r_err_frm_end_mask= 1 ;    
    stDmaWRMask1->ds2_out_wr_r_err_immediate_mask= 1 ;  
    stDmaWRMask1->ds2_out_wr_g_frm_end_mask= 1 ;        
    stDmaWRMask1->ds2_out_wr_g_line_base_mask= 1 ;      
    stDmaWRMask1->ds2_out_wr_g_err_frm_end_mask= 1 ;    
    stDmaWRMask1->ds2_out_wr_g_err_immediate_mask= 1 ;  
    stDmaWRMask1->ds2_out_wr_b_frm_end_mask= 1 ;        
    stDmaWRMask1->ds2_out_wr_b_line_base_mask= 1 ;      
    stDmaWRMask1->ds2_out_wr_b_err_frm_end_mask= 1 ;    
    stDmaWRMask1->ds2_out_wr_b_err_immediate_mask= 1 ; 
	//	
    ISP_WRAP_DMA_RD_INT_MASK0_S *stDmaRDMask0 = &pstIntCtl->stDmaRDMask0;
    stDmaRDMask0->rd_3dnr_y_frm_end_int_mask= 1 ;       
    stDmaRDMask0->rd_3dnr_y_line_base_int_mask= 1 ;     
    stDmaRDMask0->rd_3dnr_y_err_frm_end_int_mask= 1 ;   
    stDmaRDMask0->rd_3dnr_y_err_immediate_int_mask= 1 ; 
    stDmaRDMask0->rd_3dnr_uv_frm_end_int_mask= 1 ;      
    stDmaRDMask0->rd_3dnr_uv_line_base_int_mask= 1 ;    
    stDmaRDMask0->rd_3dnr_uv_err_frm_end_int_mask= 1 ;  
    stDmaRDMask0->rd_3dnr_uv_err_immediate_int_mask= 1 ;
    stDmaRDMask0->ldc_rd_y_frm_end_int_mask= 1 ;        
    stDmaRDMask0->ldc_rd_y_line_base_int_mask= 1 ;      
    stDmaRDMask0->ldc_rd_y_err_frm_end_int_mask= 1 ;    
    stDmaRDMask0->ldc_rd_y_err_immediate_int_mask= 1 ;  
    stDmaRDMask0->ldc_rd_uv_frm_end_int_mask= 1 ;       
    stDmaRDMask0->ldc_rd_uv_line_base_int_mask= 1 ;     
    stDmaRDMask0->ldc_rd_uv_err_frm_end_int_mask= 1 ;   
    stDmaRDMask0->ldc_rd_uv_err_immediate_int_mask= 1 ; 
    stDmaRDMask0->wdr_rd_raw_frm_end_int_mask= 1 ;      
    stDmaRDMask0->wdr_rd_raw_line_base_int_mask= 1 ;    
    stDmaRDMask0->wdr_rd_raw_err_frm_end_int_mask= 1 ;  
    stDmaRDMask0->wdr_rd_raw_err_immediate_int_mask= 1 ;  

	return 0;
}
/*
*config done
*/
int ISP_TEST_GetWrapConfigDone(ISP_WRAP_CONFIG_DONE_S *pstConfigDone)
{
	ISP_CHECK_POINTER(pstConfigDone);

	pstConfigDone->int_polarity = 1;
	pstConfigDone->sen_reg_pro_en = 0;
	pstConfigDone->wrap_config_done_en = 1;

	return 0;
}
/*
*
*/
int ISP_TEST_setWrap(ISP_WRAP_CONFIG_S *ispWrapInfo)
{
	ISP_CHECK_POINTER(ispWrapInfo);
	ISP_WRAP_ATTR_S pstWrapAttr;
	//
	pstWrapAttr.external_out_ch_sel = ispWrapInfo->isp_out_sel;
	//
	pstWrapAttr.dvp_input_ch_type = ispWrapInfo->dvp_ch_mode;
	//
	pstWrapAttr.hist_3a_out_en = ispWrapInfo->hist_3a_out_en;
	//
	ISP_WRAP_PIPE_CLK_CTL_S *pstPipeClkCtl = &pstWrapAttr.stPipeClkCtl;
	ISP_TEST_GetWrapComCLK(pstPipeClkCtl);
	//wdr
	ISP_WRAP_WDR_ATTR_S *pstWdrAttr = &pstWrapAttr.stWdr;
	ISP_WRAP_WDR_S  *wdrInfo = &ispWrapInfo->wdrInfo;
	ISP_TEST_GetWrapWdr(wdrInfo,pstWdrAttr);
	//3dnr
	ISP_WRAP_3DNR_ATTR_S *pst3dnrAttr = &pstWrapAttr.st3Dnr;
	ISP_WRAP_3DNR_S *nr3dInfo = &ispWrapInfo->nr3dInfo;
	ISP_TEST_GetWrap3dnr(nr3dInfo,pst3dnrAttr);
	//ldc
	ISP_WRAP_LDC_ATTR_S *pstLdcAttr = &pstWrapAttr.stLdc;
	ISP_WRAP_LDC_S  *ldcInfo = &ispWrapInfo->ldcInfo;
	ISP_TEST_GetWrapLdc(ldcInfo,pstLdcAttr);
	//main out
	ISP_WRAP_MAINOUT_ATTR_S *pstMainOutAttr = &pstWrapAttr.stMainOut;
	ISP_WRAP_MAIN_S	*mainInfo = &ispWrapInfo->mainInfo;	
	ISP_TEST_GetWrapMainOut(mainInfo,pstMainOutAttr);
	//DS0 out
	ISP_WRAP_DS0OUT_ATTR_S *pstDs0OutAttr = &pstWrapAttr.stDs0Out;
	ISP_WRAP_DS0_S *ds0Info = &ispWrapInfo->ds0Info;
	ISP_TEST_GetWrapDs0Out(ds0Info,pstDs0OutAttr);
	//DS1 out
	ISP_WRAP_DS1OUT_ATTR_S *pstDs1OutAttr = &pstWrapAttr.stDs1Out;
	ISP_WRAP_DS1_S *ds1Info = &ispWrapInfo->ds1Info;
	ISP_TEST_GetWrapDs1Out(ds1Info,pstDs1OutAttr);
	//DS2 out
	ISP_WRAP_DS2OUT_ATTR_S *pstDs2OutAttr = &pstWrapAttr.stDs2Out;
	ISP_WRAP_DS2_S *ds2Info = &ispWrapInfo->ds2Info;
	ISP_TEST_GetWrapDs2Out(ds2Info,pstDs2OutAttr);
	//DMA
	ISP_WRAP_DMA_ATTR_S *pstDmaAttr = &pstWrapAttr.stDmaAttr;
	ISP_TEST_GetWrapDmaDefaultConfig(pstDmaAttr);
	//INT mask
	ISP_WRAP_INT_CTL_S *pstIntCtl = &pstWrapAttr.stIntCtl;
	ISP_TEST_GetWrapIntCtl(pstIntCtl);
	//AXI CTL
	ISP_WRAP_AXI_CTL_S *pstAxiCtl = &pstWrapAttr.stAxiCtl;
	ISP_TEST_GetWrapAxiCtl(pstAxiCtl);
	//CONFIG DONE
	ISP_WRAP_CONFIG_DONE_S *pstConfigDone = &pstWrapAttr.stConfigDone;
	ISP_TEST_GetWrapConfigDone(pstConfigDone);
	//	
	ISP_DRV_SetWrap(&pstWrapAttr);
	//debug
	ISP_DRV_GetWrapRegsVal();
	return 0;
}
/****************************************************************************
 * isp core                                         *
 ****************************************************************************/
/*
*itc config
*/
static int ISP_TEST_GetItc(ISP_ITC_CONFIG_S	*itcInfo,ISP_CORE_ITC_CTL_S *stItcCtl)
{
	ISP_CHECK_POINTER(itcInfo);
	ISP_CHECK_POINTER(stItcCtl);

	stItcCtl->hsync_pol = itcInfo->hsync_pol;           
    stItcCtl->vsync_pol = itcInfo->vsync_pol ;           
    stItcCtl->hsync_input_timing = itcInfo->hsync_input_timing;  
    stItcCtl->vsync_input_timing = itcInfo->vsync_input_timing;
    stItcCtl->mirror_ctl = itcInfo->flip_ctl;         
    stItcCtl->video_format_ctl = itcInfo->video_fmt_sel; 
	return 0;
}
/*
*image config
*/
static int ISP_TEST_GetImage(ISP_ITC_CONFIG_S	*itcInfo,ISP_CORE_IMAGE_ATTR_S *stImgAttr)
{
	ISP_CHECK_POINTER(itcInfo);
	ISP_CHECK_POINTER(stImgAttr);

    stImgAttr->image_height = itcInfo->total_img_size.Height;       
    stImgAttr->image_width = itcInfo->total_img_size.Width;        
    stImgAttr->image_v_start = itcInfo->itc_out_szie.Height_st;      
    stImgAttr->image_h_start = itcInfo->itc_out_szie.Width_st;      
    stImgAttr->image_active_width = itcInfo->itc_out_szie.Width; 
    stImgAttr->image_active_height = itcInfo->itc_out_szie.Height;
	return 0;
}
/*
*tpg
*/
static int ISP_TEST_GetTpgCtl(ISP_TPG_CONFIG_S *tpgInfo,ISP_CORE_TEST_CTL_S *stTestCtl)
{
	ISP_CHECK_POINTER(tpgInfo);
	ISP_CHECK_POINTER(stTestCtl);

	stTestCtl->test_pattern_en = tpgInfo->tpg_en;
	stTestCtl->bayer_mode_sel = tpgInfo->bayer_mode_sel;
	stTestCtl->motion_mode_sel = tpgInfo->motion_mode_sel;
	stTestCtl->test_pattern_sel = tpgInfo->tpg_sel;
	stTestCtl->wdr_l_mul_data = tpgInfo->wdr_l_mul_data;
	stTestCtl->wdr_m_mul_data = tpgInfo->wdr_m_mul_data;
	stTestCtl->wdr_s_mul_data = tpgInfo->wdr_s_mul_data; 
	return 0;
}
/*
*blc
*/
static int ISP_TEST_GetBlcCtl(ISP_BLC_CONFIG_S *blcInfo,ISP_CORE_BLC_CTL_S *stBlcCtl)
{
	ISP_CHECK_POINTER(blcInfo);
	ISP_CHECK_POINTER(stBlcCtl);

	stBlcCtl->blc_en = blcInfo->blc_en;
	stBlcCtl->blc_offset = blcInfo->blc_offset;
	stBlcCtl->blc_ratio = blcInfo->blc_ratio;
	return 0;
}
/*
*lsc
*/
static int ISP_TEST_GetLscCtl(ISP_LSC_CONFIG_S *lscInfo,ISP_CORE_LSC_CTL_S *stLscCtl)
{
	ISP_CHECK_POINTER(lscInfo);
	ISP_CHECK_POINTER(stLscCtl);

    stLscCtl->lsc_en = lscInfo->lsc_en; 

    stLscCtl->lsc_h_center = lscInfo->lsc_h_center;     
    stLscCtl->lsc_v_center = lscInfo->lsc_v_center;

    stLscCtl->lsc_red_ratio = lscInfo->lsc_r_ratio;
    stLscCtl->lsc_green_ratio = lscInfo->lsc_g_ratio;  
    stLscCtl->lsc_blue_ratio = lscInfo->lsc_b_ratio;   
    stLscCtl->lsc_ir_ratio = lscInfo->lsc_ir_ratio;  

	return 0;
}
/*
*ae
*/
static int ISP_TEST_GetAeCtl(ISP_AE_CONFIG_S *aeInfo,ISP_CORE_AE_CTL_S *stAeCtl)
{
	ISP_CHECK_POINTER(aeInfo);
	ISP_CHECK_POINTER(stAeCtl);

    stAeCtl->ae_as_en = aeInfo->ae_as_en;              
    stAeCtl->ae_ag_en = aeInfo->ae_ag_en;              
    stAeCtl->ae_airis_en = aeInfo->ae_airis_en;           
    stAeCtl->ae_enter_ls_sel = aeInfo->ae_enter_ls_sel;

    stAeCtl->ae_exit_ls_sel = aeInfo->ae_exit_ls_sel;        
    stAeCtl->ae_win_mode_sel = aeInfo->ae_win_mode_sel;       
    stAeCtl->ae_back_light_mode_sel = aeInfo->ae_back_light_mode_sel;
    stAeCtl->ae_day_change_en = aeInfo->ae_day_change_en;    
    stAeCtl->ae_day_change_sel = aeInfo->ae_day_change_sel;     

    stAeCtl->ae_win_h_start = aeInfo->ae_win_size.h_start;
    stAeCtl->ae_win_v_start = aeInfo->ae_win_size.v_start;
    stAeCtl->ae_win_h_end = aeInfo->ae_win_size.h_end;  
    stAeCtl->ae_win_v_end = aeInfo->ae_win_size.v_end;  

    stAeCtl->ae_tar_bright = aeInfo->ae_tar_bright;      
    stAeCtl->ae_tar_bright_range = aeInfo->ae_tar_bright_range;

    stAeCtl->ae_l_ex_time = aeInfo->ae_l_ex_time;
    stAeCtl->ae_m_ex_time = aeInfo->ae_m_ex_time;
    stAeCtl->ae_s_ex_time = aeInfo->ae_s_ex_time;

    stAeCtl->ae_agc = aeInfo->ae_agc;            
    stAeCtl->ae_ad_shuttle_freq = aeInfo->ae_ad_shuttle_freq;
    stAeCtl->ae_ad_gain_freq = aeInfo->ae_ad_gain_freq;

    stAeCtl->ae_adjust_step_max = aeInfo->ae_adjust_step_max;

    stAeCtl->ae_ex_value_max = aeInfo->ae_ex_value_max;  
    stAeCtl->ae_ex_value_mid = aeInfo->ae_ex_value_mid;    
    stAeCtl->ae_ex_value_min = aeInfo->ae_ex_value_min; 

    stAeCtl->ae_gain_value_max = aeInfo->ae_gain_value_max;    
    stAeCtl->ae_gain_value_mid = aeInfo->ae_gain_value_mid;
    stAeCtl->ae_gain_value_min = aeInfo->ae_gain_value_min;

    stAeCtl->ae_dn_switch_ad_step_max = aeInfo->ae_dn_switch_ad_step_max;
    stAeCtl->ae_dn_switch_wait_time = aeInfo->ae_dn_switch_wait_time;
    stAeCtl->ape_max_diff = aeInfo->ape_max_diff;

    stAeCtl->ape_drv_signal_max = aeInfo->ape_drv_signal_max;    

    stAeCtl->ape_coeff_distance = aeInfo->ape_coeff_distance;    
    stAeCtl->ape_coeff_speed = aeInfo->ape_coeff_speed;       
    stAeCtl->ape_coeff_acceleration = aeInfo->ape_coeff_acceleration;

    stAeCtl->ape_drv_manual_value = aeInfo->ape_drv_manual_value;  
    stAeCtl->ape_damp_manual_value = aeInfo->ape_damp_manual_value;
	return 0;
}
/*
*awb
*/
static int ISP_TEST_GetAwbCtl(ISP_AWB_CONFIG_S *awbInfo,ISP_CORE_AWB_CTL_S *stAwbCtl)
{
	ISP_CHECK_POINTER(awbInfo);
	ISP_CHECK_POINTER(stAwbCtl);

    stAwbCtl->awb_d65_en = awbInfo->awb_d65_en; 
    stAwbCtl->awb_ccm_en = awbInfo->awb_ccm_en; 
    stAwbCtl->awb_en = awbInfo->awb_en;     
    stAwbCtl->awb_mode_sel = awbInfo->awb_mode_sel;

    stAwbCtl->awb_hist_mode_sel = awbInfo->awb_hist_mode_sel;
    stAwbCtl->awb_veri_en = awbInfo->awb_veri_en;      
    stAwbCtl->awb_mode_sel = awbInfo->awb_mode_sel;     
    stAwbCtl->awb_value_save_en = awbInfo->awb_value_save_en;

    stAwbCtl->awb_ccm_adp_adjust_en = awbInfo->awb_ccm_adp_adjust_en;
    stAwbCtl->awb_stab_en = awbInfo->awb_stab_en;          
    stAwbCtl->awb_d65_red_gain = awbInfo->awb_d65_red_gain;

    stAwbCtl->awb_d65_blue_gain = awbInfo->awb_d65_blue_gain;

    stAwbCtl->ccm_rr_coff = awbInfo->ccm_coff[0][0];
    stAwbCtl->ccm_rg_coff = awbInfo->ccm_coff[0][1];
    stAwbCtl->ccm_rb_coff = awbInfo->ccm_coff[0][2];
    stAwbCtl->ccm_gr_coff = awbInfo->ccm_coff[1][0];
    stAwbCtl->ccm_gg_coff = awbInfo->ccm_coff[1][1];
    stAwbCtl->ccm_gb_coff = awbInfo->ccm_coff[1][2];
    stAwbCtl->ccm_br_coff = awbInfo->ccm_coff[2][0];
    stAwbCtl->ccm_bg_coff = awbInfo->ccm_coff[2][1];
    stAwbCtl->ccm_bb_coff = awbInfo->ccm_coff[2][2];
    stAwbCtl->ccm_correct_coff = awbInfo->ccm_correct_coff;

    stAwbCtl->awb_win_h_start = awbInfo->awb_win_size.h_start;
    stAwbCtl->awb_win_v_start = awbInfo->awb_win_size.v_start;
    stAwbCtl->awb_win_h_end = awbInfo->awb_win_size.h_end;  
    stAwbCtl->awb_win_v_end = awbInfo->awb_win_size.v_end;  

    stAwbCtl->awb_correct_diff_th = awbInfo->awb_correct_diff_th;     
    stAwbCtl->awb_color_changeres_time = awbInfo->awb_color_changeres_time;
    stAwbCtl->awb_historgram_th = awbInfo->awb_historgram_th;

    stAwbCtl->awb_red_gain_adjust = awbInfo->awb_red_gain_adjust;     
    stAwbCtl->awb_green_gain_adjust = awbInfo->awb_green_gain_adjust;   
    stAwbCtl->awb_blue_gain_adjust = awbInfo->awb_blue_gain_adjust;

    stAwbCtl->awb_red_max_value = awbInfo->awb_red_max_value;
    stAwbCtl->awb_blue_max_value = awbInfo->awb_blue_max_value;      
    stAwbCtl->awb_red_min_value = awbInfo->awb_red_min_value;
    stAwbCtl->awb_blue_min_value = awbInfo->awb_blue_min_value;

    stAwbCtl->awb_red_obj_value = awbInfo->awb_red_obj_value;
    stAwbCtl->awb_blue_obj_value = awbInfo->awb_blue_obj_value;

	return 0;
}
/*
*wdr
*/
static int ISP_TEST_GetWdrCtl(ISP_WDR_CONFIG_S *wdrInfo,ISP_CORE_WDR_CTL_S *stWdrCtl)
{
	ISP_CHECK_POINTER(wdrInfo);
	ISP_CHECK_POINTER(stWdrCtl);

    stWdrCtl->wdr_fusion_en = wdrInfo->wdr_fusion_en;      
    stWdrCtl->wdr_frame_sel = wdrInfo->wdr_frame_sel;      
    stWdrCtl->wdr_adp_adjust_en = wdrInfo->wdr_adp_adjust_en;  
    stWdrCtl->wdr_stab_en = wdrInfo->wdr_stab_en;

    stWdrCtl->wdr_en = wdrInfo->wdr_en;             
    stWdrCtl->wdr_ghost_remove_en = wdrInfo->wdr_ghost_remove_en; 
    stWdrCtl->wdr_3_frame_out_mode = wdrInfo->wdr_3frame_out_mode;
    stWdrCtl->wdr_mode_sel = wdrInfo->wdr_mode_sel;

    stWdrCtl->wdr_2frame_ex_ratio = wdrInfo->wdr_2frame_ex_ratio;
    stWdrCtl->wdr_3frame_ex_ratio = wdrInfo->wdr_3frame_ex_ratio; 
    stWdrCtl->wdr_stat_img_sel = wdrInfo->wdr_stat_img_sel;   
    stWdrCtl->wdr_ltm_data_sel = wdrInfo->wdr_ltm_data_sel;

    stWdrCtl->wdr_tz_data_sel = wdrInfo->wdr_tz_data_sel;
    stWdrCtl->wdr_remove_purple_en = wdrInfo->wdr_remove_purple_en;

    stWdrCtl->wdr_over_ex_ratio_th1 = wdrInfo->wdr_over_ex_ratio_th1;
    stWdrCtl->wdr_over_ex_ratio_th2 = wdrInfo->wdr_over_ex_ratio_th2;

    stWdrCtl->wdr_fusion_ratio_th = wdrInfo->wdr_fusion_ratio_th;
    stWdrCtl->wdr_fusion_value1 = wdrInfo->wdr_fusion_value1;  
    stWdrCtl->wdr_fusion_value2 = wdrInfo->wdr_fusion_value2;

	return 0;
}
/*
*csc
*/
static int ISP_TEST_GetCscCtl(ISP_CSC_CONFIG_S	*cscInfo,ISP_CORE_CSC_CTL_S *stCscCtl)
{
	ISP_CHECK_POINTER(cscInfo);
	ISP_CHECK_POINTER(stCscCtl);

    stCscCtl->csc_r2y_00 = cscInfo->csc_r2y[0][0];
    stCscCtl->csc_r2y_01 = cscInfo->csc_r2y[0][1];
    stCscCtl->csc_r2y_02 = cscInfo->csc_r2y[0][2];
    stCscCtl->csc_r2y_10 = cscInfo->csc_r2y[1][0];
    stCscCtl->csc_r2y_11 = cscInfo->csc_r2y[1][1];
    stCscCtl->csc_r2y_12 = cscInfo->csc_r2y[1][2];
    stCscCtl->csc_r2y_20 = cscInfo->csc_r2y[2][0];
    stCscCtl->csc_r2y_21 = cscInfo->csc_r2y[2][1];
    stCscCtl->csc_r2y_22 = cscInfo->csc_r2y[2][2];

	return 0;
}
/*
*ada
*/
static int ISP_TEST_GetAdaCtl(ISP_ADA_CONFIG_S	*adaInfo,ISP_CORE_ADA_CTL_S *stAdaCtl)
{
	ISP_CHECK_POINTER(adaInfo);
	ISP_CHECK_POINTER(stAdaCtl);

    stAdaCtl->ada_rgb_gamma_en = adaInfo->ada_rgb_gamma_en; 
    stAdaCtl->ada_yuv_gamma_en = adaInfo->ada_yuv_gamma_en; 
    stAdaCtl->ada_adjust_en = adaInfo->ada_adjust_en;    
    stAdaCtl->ada_img_stab_en = adaInfo->ada_img_stab_en;

    stAdaCtl->ada_ccr_en = adaInfo->ada_ccr_en;       
    stAdaCtl->ada_adp_en = adaInfo->ada_adp_en;       
    stAdaCtl->ada_adp_ccr_en = adaInfo->ada_adp_ccr_en;   
    stAdaCtl->ada_stat_mode_sel = adaInfo->ada_stat_mode_sel;

    stAdaCtl->ada_enh_mode_sel = adaInfo->ada_enh_mode_sel;
    stAdaCtl->ada_stat_max_value = adaInfo->ada_stat_max_value; 
    stAdaCtl->ada_ad_stren_max_value = adaInfo->ada_ad_stren_max_value;

    stAdaCtl->ada_win_h_start = adaInfo->ada_win_size.h_start;
    stAdaCtl->ada_win_v_start = adaInfo->ada_win_size.v_start;
    stAdaCtl->ada_win_h_end = adaInfo->ada_win_size.h_end;  
    stAdaCtl->ada_win_v_end = adaInfo->ada_win_size.v_end; 

	return 0;
}
/*
*rgbir
*/
static int ISP_TEST_GetRgbirCtl(ISP_RGBIR_CONFIG_S *rgbirInfo,ISP_CORE_RGBIR_CTL_S *stRgbirCtl)
{
	ISP_CHECK_POINTER(rgbirInfo);
	ISP_CHECK_POINTER(stRgbirCtl);

    stRgbirCtl->rgbir_en = rgbirInfo->rgbir_en;        
    stRgbirCtl->rgbir_rtf_en = rgbirInfo->rgbir_rtf_en;    
    stRgbirCtl->rgbir_rpc_en = rgbirInfo->rgbir_rpc_en;    
    stRgbirCtl->rgbir_fusion_en = rgbirInfo->rgbir_fusion_en;

    stRgbirCtl->rgbir_output_sel = rgbirInfo->rgbir_output_sel;

    stRgbirCtl->rgbir_rpc_max_value = rgbirInfo->rgbir_rpc_max_value; 
    stRgbirCtl->rgbir_rpc_color_coff = rgbirInfo->rgbir_rpc_color_coff;
    stRgbirCtl->rgbir_rpc_luma_coff = rgbirInfo->rgbir_rpc_luma_coff; 

    stRgbirCtl->rgbir_rpc_th = rgbirInfo->rgbir_rpc_th;       
    stRgbirCtl->rgbir_rpc_th1 = rgbirInfo->rgbir_rpc_th1; 

	return 0;
}
/*
*2dnr
*/
static int ISP_TEST_Get2dnrCtl(ISP_NR2D_CONFIG_S *nr2dInfo,ISP_CORE_2DNR_CTL_S *st2dnrCtl)
{
	ISP_CHECK_POINTER(nr2dInfo);
	ISP_CHECK_POINTER(st2dnrCtl);

    st2dnrCtl->core_2dnr_pcf_en = nr2dInfo->d2nr_pcf_en;       
    st2dnrCtl->core_2dnr_raw_en = nr2dInfo->d2nr_raw_en;       
    st2dnrCtl->core_2dnr_edge_en = nr2dInfo->d2nr_edge_en;      
    st2dnrCtl->core_2dnr_bap_en = nr2dInfo->d2nr_bap_en;       

    st2dnrCtl->core_2dnr_luma_en = nr2dInfo->d2nr_luma_en;      
    st2dnrCtl->core_2dnr_chroma_en = nr2dInfo->d2nr_chroma_en;    
    st2dnrCtl->core_2dnr_pcf_adp_en = nr2dInfo->d2nr_pcf_adp_en;   
    st2dnrCtl->core_2dnr_raw_adp_en = nr2dInfo->d2nr_raw_adp_en;   

    st2dnrCtl->core_2dnr_luma_adp_en = nr2dInfo->d2nr_luma_adp_en;  
    st2dnrCtl->core_2dnr_chroma_adp_en = nr2dInfo->d2nr_chroma_adp_en;
    st2dnrCtl->core_2dnr_raw_intensity = nr2dInfo->d2nr_raw_intensity;
    st2dnrCtl->core_2dnr_bap_intensity = nr2dInfo->d2nr_bap_intensity;

    st2dnrCtl->core_2dnr_edge_intensity = nr2dInfo->d2nr_edge_intensity;
    st2dnrCtl->core_2dnr_luma_intensity = nr2dInfo->d2nr_luma_intensity;
    st2dnrCtl->core_2dnr_chroma_intensity = nr2dInfo->d2nr_chroma_intensity;

	return 0;
}
/*
*3dnr
*/
static int ISP_TEST_Get3dnrCtl(ISP_NR3D_CONFIG_S *nr3dInfo,ISP_CORE_3DNR_CTL_S *st3dnrCtl)
{
	ISP_CHECK_POINTER(nr3dInfo);
	ISP_CHECK_POINTER(st3dnrCtl);

    st3dnrCtl->core_3dnr_en = nr3dInfo->d3nr_en;            
    st3dnrCtl->core_3dnr_pre_luma_en = nr3dInfo->d3nr_pre_luma_en;  
    st3dnrCtl->core_3dnr_pre_chroma_en = nr3dInfo->d3nr_pre_chroma_en; 

    st3dnrCtl->core_3dnr_main_luma_en = nr3dInfo->d3nr_main_luma_en;
    st3dnrCtl->core_3dnr_main_chroma_en = nr3dInfo->d3nr_main_chroma_en;

    st3dnrCtl->core_3dnr_post_luma_en = nr3dInfo->d3nr_post_luma_en;  
    st3dnrCtl->core_3dnr_post_chroma_en = nr3dInfo->d3nr_post_chroma_en;

    st3dnrCtl->core_3dnr_2d_luma_en = nr3dInfo->d3nr_2d_luma_en;
    st3dnrCtl->core_3dnr_2d_chroma_en = nr3dInfo->d3nr_2d_luma_en;

    st3dnrCtl->core_3dnr_wb_en = nr3dInfo->d3nr_wb_en;         
    st3dnrCtl->core_3dnr_wb_sel = nr3dInfo->d3nr_wb_sel;
    st3dnrCtl->core_3dnr_adp_luma_en = nr3dInfo->d3nr_adp_luma_en;

    st3dnrCtl->core_3dnr_adp_chroma_en = nr3dInfo->d3nr_adp_chroma_en;
    st3dnrCtl->core_3dnr_pre_luma_th = nr3dInfo->d3nr_pre_luma_th;        
    st3dnrCtl->core_3dnr_pre_luma_intensity = nr3dInfo->d3nr_pre_luma_intensity;   
    st3dnrCtl->core_3dnr_pre_chroma_intensity = nr3dInfo->d3nr_pre_chroma_intensity;

    st3dnrCtl->core_3dnr_mid_filter_th = nr3dInfo->d3nr_mid_filter_th;
    st3dnrCtl->core_3dnr_pre_mid_filter_th = nr3dInfo->d3nr_pre_mid_filter_th;    
    st3dnrCtl->core_3dnr_cur_mid_filter_th = nr3dInfo->d3nr_cur_mid_filter_th;    
    st3dnrCtl->core_3dnr_low_pass_filter_th = nr3dInfo->d3nr_low_pass_filter_th;
    st3dnrCtl->core_3dnr_luma_th = nr3dInfo->d3nr_luma_th;             
    st3dnrCtl->core_3dnr_min_value = nr3dInfo->d3nr_min_value;
    st3dnrCtl->core_3dnr_luma_intensity = nr3dInfo->d3nr_luma_intensity;

    st3dnrCtl->core_3dnr_chroma_intensity = nr3dInfo->d3nr_chroma_intensity;    
    st3dnrCtl->core_3dnr_post_edge_th = nr3dInfo->d3nr_post_edge_th;        
    st3dnrCtl->core_3dnr_post_luma_intensity = nr3dInfo->d3nr_post_luma_intensity;  
    st3dnrCtl->core_3dnr_post_chroma_intensity = nr3dInfo->d3nr_post_chroma_intensity;

	return 0;
}
/*
*enh
*/
static int ISP_TEST_GetEnhCtl(ISP_ENH_CONFIG_S *enhInfo,ISP_CORE_ENH_CTL_S *stEnhCtl)
{
	ISP_CHECK_POINTER(enhInfo);
	ISP_CHECK_POINTER(stEnhCtl);

    stEnhCtl->enh_ltm_en = enhInfo->enh_ltm_en;       
    stEnhCtl->enh_sharp_en = enhInfo->enh_sharp_en;     
    stEnhCtl->enh_cc_en = enhInfo->enh_cc_en;        
    stEnhCtl->enh_adp_ltm_en = enhInfo->enh_adp_ltm_en;    
    stEnhCtl->enh_adp_sharp_en = enhInfo->enh_adp_sharp_en; 
    stEnhCtl->enh_adp_cc_en = enhInfo->enh_adp_cc_en;    
    stEnhCtl->ltm_gain = enhInfo->ltm_gain;  
    stEnhCtl->ltm_th = enhInfo->ltm_th; 
    stEnhCtl->enh_nr_th = enhInfo->enh_nr_th; 
    stEnhCtl->enh_th1 = enhInfo->enh_th1;
    stEnhCtl->enh_th2 = enhInfo->enh_th2;
    stEnhCtl->sharp_gain = enhInfo->sharp_gain; 

	return 0;
}
/*
*post ctl
*/
static int ISP_TEST_GetPostCtl(ISP_POST_CONFIG_S *postInfo,ISP_CORE_POST_CTL_S *stPostCtl)
{
	ISP_CHECK_POINTER(postInfo);
	ISP_CHECK_POINTER(stPostCtl);

    stPostCtl->post_cont_ad_en = postInfo->post_cont_ad_en;   
    stPostCtl->post_luma_ad_en = postInfo->post_luma_ad_en;   
    stPostCtl->post_satu_ad_en = postInfo->post_satu_ad_en;
    stPostCtl->cont_ad_intensity = postInfo->cont_ad_intensity;    
    stPostCtl->luma_ad_intensity = postInfo->luma_ad_intensity;
    stPostCtl->satu_ad_intensity = postInfo->satu_ad_intensity;

	return 0;
}
/*
*otc
*/
static int ISP_TEST_GetOtcCtl(ISP_OTC_CONFIG_S *otcInfo,ISP_CORE_OTC_CTL_S *stOtcCtl)
{
	ISP_CHECK_POINTER(otcInfo);
	ISP_CHECK_POINTER(stOtcCtl);

    stOtcCtl->post_otc_en = otcInfo->post_otc_en;
   	stOtcCtl->otc_yc_sel = otcInfo->otc_yc_sel;        
   	stOtcCtl->otc_uv_format_sel = otcInfo->otc_uv_format_sel; 
   	stOtcCtl->otc_hsync_pol_sel = otcInfo->otc_hsync_pol_sel; 
   	stOtcCtl->otc_vsync_pol_sel = otcInfo->otc_vsync_pol_sel;    
   	stOtcCtl->otc_stt_vr = otcInfo->otc_out_size.Width_st;   
   	stOtcCtl->otc_stt_hr = otcInfo->otc_out_size.Height_st;   
   	stOtcCtl->otc_height = otcInfo->otc_out_size.Height;   
   	stOtcCtl->otc_width = otcInfo->otc_out_size.Width; 

	return 0;
}
/*
*ldc
*/
static int ISP_TEST_GetLdcCtl(ISP_LDC_CONFIG_S *ldcInfo,ISP_CORE_LDC_CTL_S *stLdcCtl)
{
	ISP_CHECK_POINTER(ldcInfo);
	ISP_CHECK_POINTER(stLdcCtl);

    stLdcCtl->ldc_en = ldcInfo->ldc_en; 
    stLdcCtl->ldc_arith_en = ldcInfo->ldc_arith_en;   
    stLdcCtl->ldc_req_freq = ldcInfo->ldc_req_freq;
    stLdcCtl->ldc_stt_ln = ldcInfo->ldc_stt_ln;
    stLdcCtl->ldc_h_center_pos = ldcInfo->ldc_h_center_pos;
    stLdcCtl->ldc_v_center_pos = ldcInfo->ldc_v_center_pos;
    stLdcCtl->ldc_rectify_cr = ldcInfo->ldc_rectify_cr;
    stLdcCtl->ldc_rectify_cz = ldcInfo->ldc_rectify_cz; 
 
	return 0;
}
/*
*af
*/
static int ISP_TEST_GetAfCtl(ISP_AF_CONFIG_S *afInfo,ISP_CORE_AF_CTL_S *stAfCtl)
{
	ISP_CHECK_POINTER(afInfo);
	ISP_CHECK_POINTER(stAfCtl);

	stAfCtl->af_stat_en = afInfo->af_stat_en; 
   	stAfCtl->af_stat_mode_sel= afInfo->af_stat_mode_sel; 
    stAfCtl->af_stat_win_h_start= afInfo->af_win_size.h_start;    
    stAfCtl->af_stat_win_v_start= afInfo->af_win_size.v_start; 
    stAfCtl->af_stat_win_h_end= afInfo->af_win_size.h_end;  
    stAfCtl->af_stat_win_v_end= afInfo->af_win_size.v_end;

	return 0;
}
/*
*3dnr mfbc
*/
static int ISP_TEST_GetIspMfbc(ISP_MFBC_CONFIG_S *mfbcInfo,ISP_MFBC_ATTR_S *pstMfbcAttr)
{
	ISP_CHECK_POINTER(pstMfbcAttr);
	ISP_CHECK_POINTER(mfbcInfo);
	//
	ISP_MFBC_CTL_S	*stIspMfbcCtl = &pstMfbcAttr->stIspMfbcCtl;
	stIspMfbcCtl->mfbc_out_format_cfg = mfbcInfo->mfbc_out_format_cfg;
    //
	ISP_MFBC_SIZE_S *stIspMfbcSize = &pstMfbcAttr->stIspMfbcSize;
	stIspMfbcSize->mfbc_input_width = mfbcInfo->mfbc_input_size.Width;
	stIspMfbcSize->mfbc_input_height = mfbcInfo->mfbc_input_size.Height;
    //
	ISP_MFBC_Y_BUF_S *stIspMfbcYBuf = &pstMfbcAttr->stIspMfbcBuf.stIspMfbcYBuf;
	ISP_MFBCD_BUF_S  *yDataBufInfo = &mfbcInfo->yDataBufInfo;
	stIspMfbcYBuf->mfbc_y_data_buf_base0 = yDataBufInfo->data_buf_base0;
	stIspMfbcYBuf->mfbc_y_data_buf_base1 = yDataBufInfo->data_buf_base1;
	stIspMfbcYBuf->mfbc_y_data_stride = yDataBufInfo->data_stride;
	stIspMfbcYBuf->mfbc_y_data_wr_blen = yDataBufInfo->data_wr_blen;
	ISP_MFBCD_BUF_S  *yHeadBufInfo = &mfbcInfo->yHeadBufInfo;
	stIspMfbcYBuf->mfbc_y_head_buf_base0 = yHeadBufInfo->data_buf_base0;
	stIspMfbcYBuf->mfbc_y_head_buf_base1 = yHeadBufInfo->data_buf_base1;
	stIspMfbcYBuf->mfbc_y_head_stride = yHeadBufInfo->data_stride;
	stIspMfbcYBuf->mfbc_y_head_wr_blen = yHeadBufInfo->data_wr_blen;
	//
	ISP_MFBC_YL_BUF_S *stIspMfbcYLBuf = &pstMfbcAttr->stIspMfbcBuf.stIspMfbcUVBuf;
	ISP_MFBCD_BUF_S *ylDataBufInfo = &mfbcInfo->ylDataBufInfo;
	stIspMfbcYLBuf->mfbc_yl_data_buf_base0 = ylDataBufInfo->data_buf_base0;
	stIspMfbcYLBuf->mfbc_yl_data_buf_base1 = ylDataBufInfo->data_buf_base1;
	stIspMfbcYLBuf->mfbc_yl_data_stride = ylDataBufInfo->data_stride;
	stIspMfbcYLBuf->mfbc_yl_data_wr_blen = ylDataBufInfo->data_wr_blen;
	ISP_MFBCD_BUF_S *ylHeadBufInfo = &mfbcInfo->ylHeadBufInfo;
	stIspMfbcYLBuf->mfbc_yl_head_buf_base0 = ylHeadBufInfo->data_buf_base0;
	stIspMfbcYLBuf->mfbc_yl_head_buf_base1 = ylHeadBufInfo->data_buf_base1;
	stIspMfbcYLBuf->mfbc_yl_head_stride = ylHeadBufInfo->data_stride;
	stIspMfbcYLBuf->mfbc_yl_head_wr_blen = ylHeadBufInfo->data_wr_blen;
	//
	ISP_MFBC_UV_BUF_S *stIspMfbcUVBuf = &pstMfbcAttr->stIspMfbcBuf.stIspMfbcYLBuf;
	ISP_MFBCD_BUF_S *uvDataBufInfo = &mfbcInfo->uvDataBufInfo;
	stIspMfbcUVBuf->mfbc_uv_data_buf_base0 = uvDataBufInfo->data_buf_base0;
	stIspMfbcUVBuf->mfbc_uv_data_buf_base1 = uvDataBufInfo->data_buf_base1;
	stIspMfbcUVBuf->mfbc_uv_data_stride = uvDataBufInfo->data_stride;
	stIspMfbcUVBuf->mfbc_uv_data_wr_blen = uvDataBufInfo->data_wr_blen;
	ISP_MFBCD_BUF_S *uvHeadBufInfo = &mfbcInfo->uvHeadBufInfo;
	stIspMfbcUVBuf->mfbc_uv_head_buf_base0 = uvHeadBufInfo->data_buf_base0;
	stIspMfbcUVBuf->mfbc_uv_head_buf_base1 = uvHeadBufInfo->data_buf_base1;
	stIspMfbcUVBuf->mfbc_uv_head_stride = uvHeadBufInfo->data_stride;
	stIspMfbcUVBuf->mfbc_uv_head_wr_blen = uvHeadBufInfo->data_wr_blen;
	return 0;
}
/*
*3dnr mfbd
*/
static int ISP_TEST_GetIspMfbd(ISP_MFBD_CONFIG_S *mfbdInfo,ISP_MFBD_ATTR_S *pstIspMfbdAttr)
{
	ISP_CHECK_POINTER(pstIspMfbdAttr);
	ISP_CHECK_POINTER(mfbdInfo);

	ISP_MFBD_CTL_S		*stIspMfbdCtl = &pstIspMfbdAttr->stIspMfbdCtl;
	stIspMfbdCtl->mfbd_en = mfbdInfo->mfbd_en;
	stIspMfbdCtl->mfbd_format_cfg = mfbdInfo->mfbd_format_cfg;
	//
	ISP_MFBD_SIZE_S		*stIspMfbdSize = &pstIspMfbdAttr->stIspMfbdSize;
	stIspMfbdSize->mfbd_input_width = mfbdInfo->mfbd_input_size.Width;
	stIspMfbdSize->mfbd_input_height = mfbdInfo->mfbd_input_size.Height;
	//
	ISP_MFBD_BUF_S		*stIspMfbdBuf = &pstIspMfbdAttr->stIspMfbdBuf;
	ISP_MFBD_Y_BUF_S  	*stIspMfbdYBuf = &stIspMfbdBuf->stIspMfbdYBuf;
	ISP_MFBCD_BUF_S *yDataBufInfo = &mfbdInfo->yDataBufInfo;
	stIspMfbdYBuf->mfbd_y_data_buf_base0 = yDataBufInfo->data_buf_base0;
	stIspMfbdYBuf->mfbd_y_data_buf_base0 = yDataBufInfo->data_buf_base1;
	stIspMfbdYBuf->mfbd_y_data_stride = yDataBufInfo->data_stride;	
	ISP_MFBCD_BUF_S *yHeadBufInfo = &mfbdInfo->yHeadBufInfo;
	stIspMfbdYBuf->mfbd_y_head_buf_base0 = yHeadBufInfo->data_buf_base0;
	stIspMfbdYBuf->mfbd_y_head_buf_base1 = yHeadBufInfo->data_buf_base1;
	stIspMfbdYBuf->mfbd_y_head_stride = yHeadBufInfo->data_stride;

	ISP_MFBD_YL_BUF_S 	*stIspMfbdYLBuf = &stIspMfbdBuf->stIspMfbdYLBuf;
	ISP_MFBCD_BUF_S  *ylDataBufInfo = &mfbdInfo->ylDataBufInfo;
	stIspMfbdYLBuf->mfbd_yl_data_buf_base0 = ylDataBufInfo->data_buf_base0;
	stIspMfbdYLBuf->mfbd_yl_data_buf_base1 = ylDataBufInfo->data_buf_base1;
	stIspMfbdYLBuf->mfbd_yl_data_stride = ylDataBufInfo->data_stride;
	ISP_MFBCD_BUF_S  *ylHeadBufInfo = &mfbdInfo->ylHeadBufInfo;
	stIspMfbdYLBuf->mfbd_yl_head_buf_base0 = ylHeadBufInfo->data_buf_base0;
	stIspMfbdYLBuf->mfbd_yl_head_buf_base1 = ylHeadBufInfo->data_buf_base1;
	stIspMfbdYLBuf->mfbd_yl_head_stride = ylHeadBufInfo->data_stride;

	ISP_MFBD_UV_BUF_S 	*stIspMfbdUVBuf = &stIspMfbdBuf->stIspMfbdUVBuf; 
	ISP_MFBCD_BUF_S  *uvDataBufInfo = &mfbdInfo->uvDataBufInfo;
	stIspMfbdUVBuf->mfbd_uv_data_buf_base0 = uvDataBufInfo->data_buf_base0;
	stIspMfbdUVBuf->mfbd_uv_data_buf_base1 = uvDataBufInfo->data_buf_base1;
	stIspMfbdUVBuf->mfbd_uv_data_stride = uvDataBufInfo->data_stride;
	ISP_MFBCD_BUF_S  *uvHeadBufInfo = &mfbdInfo->uvHeadBufInfo;
	stIspMfbdUVBuf->mfbd_uv_head_buf_base0 = uvHeadBufInfo->data_buf_base0;
	stIspMfbdUVBuf->mfbd_uv_head_buf_base1 = uvHeadBufInfo->data_buf_base1;
	stIspMfbdUVBuf->mfbd_uv_head_stride = uvHeadBufInfo->data_stride;
	
	return 0;
}
/*
*
*/
int ISP_TEST_setCore(ISP_CORE_CONFIG_S *ispCoreInfo)
{
	ISP_CHECK_POINTER(ispCoreInfo);
	ISP_CORE_ATRR_S pstCoreAttr;

	SENSOR_TYPE sensor_type = ispCoreInfo->sensor_type;
	//itc
	ISP_ITC_CONFIG_S	*itcInfo = &ispCoreInfo->itcInfo;
	ISP_CORE_ITC_CTL_S  *stItcCtl = &pstCoreAttr.stItcCtl;
	ISP_TEST_GetItc(itcInfo,stItcCtl);
	//image
	ISP_CORE_IMAGE_ATTR_S *stImageAttr = &pstCoreAttr.stImageAttr;
	ISP_TEST_GetImage(itcInfo,stImageAttr);
	//test pattern
    ISP_CORE_TEST_CTL_S *stTestCtl= &pstCoreAttr.stTestCtl;
	ISP_TPG_CONFIG_S	*tpgInfo = &ispCoreInfo->tpgInfo;
	ISP_TEST_GetTpgCtl(tpgInfo,stTestCtl);
	//blc
    ISP_CORE_BLC_CTL_S *stBlcCtl= &pstCoreAttr.stBlcCtl;
	ISP_BLC_CONFIG_S *blcInfo = &ispCoreInfo->blcInfo;
	ISP_TEST_GetBlcCtl(blcInfo,stBlcCtl);
	//lsc
    ISP_CORE_LSC_CTL_S *stLscCtl= &pstCoreAttr.stLscCtl;
	ISP_LSC_CONFIG_S *lscInfo = &ispCoreInfo->lscInfo;
	ISP_TEST_GetLscCtl(lscInfo,stLscCtl);
	//ae
    ISP_CORE_AE_CTL_S *stAeCtl= &pstCoreAttr.stAeCtl;
	ISP_AE_CONFIG_S	*aeInfo = &ispCoreInfo->aeInfo;
	ISP_TEST_GetAeCtl(aeInfo,stAeCtl);
	//awb
    ISP_CORE_AWB_CTL_S *stAwbCtl= &pstCoreAttr.stAwbCtl;
	ISP_AWB_CONFIG_S  *awbInfo = &ispCoreInfo->awbInfo;
	ISP_TEST_GetAwbCtl(awbInfo,stAwbCtl);
	//wdr
    ISP_CORE_WDR_CTL_S *stWdrCtl= &pstCoreAttr.stWdrCtl;
	ISP_WDR_CONFIG_S *wdrInfo = &ispCoreInfo->wdrInfo;
	ISP_TEST_GetWdrCtl(wdrInfo,stWdrCtl);
	//csc
    ISP_CORE_CSC_CTL_S *stCscCtl= &pstCoreAttr.stCscCtl;
	ISP_CSC_CONFIG_S	*cscInfo = &ispCoreInfo->cscInfo;
	ISP_TEST_GetCscCtl(cscInfo,stCscCtl);
	//ada
    ISP_CORE_ADA_CTL_S *stAdaCtl= &pstCoreAttr.stAdaCtl;
	ISP_ADA_CONFIG_S  *adaInfo = &ispCoreInfo->adaInfo;
	ISP_TEST_GetAdaCtl(adaInfo,stAdaCtl);
	//rgbir
    ISP_CORE_RGBIR_CTL_S *stRgbirCtl= &pstCoreAttr.stRgbirCtl;
	ISP_RGBIR_CONFIG_S	*rgbirInfo = &ispCoreInfo->rgbirInfo;
	ISP_TEST_GetRgbirCtl(rgbirInfo,stRgbirCtl);
	//2dnr
    ISP_CORE_2DNR_CTL_S *st2dnrCtl= &pstCoreAttr.st2dnrCtl;
	ISP_NR2D_CONFIG_S	*nr2dInfo = &ispCoreInfo->nr2dInfo;
	ISP_TEST_Get2dnrCtl(nr2dInfo,st2dnrCtl);
	//3dnr
    ISP_CORE_3DNR_CTL_S *st3dnrCtl= &pstCoreAttr.st3dnrCtl;
	ISP_NR3D_CONFIG_S	*nr3dInfo = &ispCoreInfo->nr3dInfo;
	ISP_TEST_Get3dnrCtl(nr3dInfo,st3dnrCtl);
	//enh
    ISP_CORE_ENH_CTL_S *stEnhCtl= &pstCoreAttr.stEnhCtl;
	ISP_ENH_CONFIG_S *enhInfo= &ispCoreInfo->enhInfo;
	ISP_TEST_GetEnhCtl(enhInfo,stEnhCtl);
	//post ctl
    ISP_CORE_POST_CTL_S *stPostCtl= &pstCoreAttr.stPostCtl;
	ISP_POST_CONFIG_S *postInfo= &ispCoreInfo->postInfo;
	ISP_TEST_GetPostCtl(postInfo,stPostCtl);
	//otc
    ISP_CORE_OTC_CTL_S  *stOtcCtl= &pstCoreAttr.stOtcCtl;
	ISP_OTC_CONFIG_S *otcInfo= &ispCoreInfo->otcInfo;
	ISP_TEST_GetOtcCtl(otcInfo,stOtcCtl);
	//ldc
    ISP_CORE_LDC_CTL_S *stLdcCtl= &pstCoreAttr.stLdcCtl;
	ISP_LDC_CONFIG_S *ldcInfo= &ispCoreInfo->ldcInfo;
	ISP_TEST_GetLdcCtl(ldcInfo,stLdcCtl);
	//af
    ISP_CORE_AF_CTL_S *stAfCtl= &pstCoreAttr.stAfCtl;
	ISP_AF_CONFIG_S	*afInfo= &ispCoreInfo->afInfo;
	ISP_TEST_GetAfCtl(afInfo,stAfCtl);
	//
	ISP_DRV_SetCore(&pstCoreAttr,sensor_type);


	switch(ispCoreInfo->enIspMode)
	{
		case ISP_PIPE_MODE_4K:
		case ISP_PIPE_MODE_F2K:
		{
			//3dnr mfbc
			ISP_MFBC_ATTR_S pstMfbcAttr;
			ISP_MFBC_CONFIG_S *mfbcInfo = &ispCoreInfo->mfbcInfo;
			ISP_TEST_GetIspMfbc(mfbcInfo,&pstMfbcAttr);
			ISP_DRV_SetMFBC(&pstMfbcAttr);
			//3dnr mfbd
			ISP_MFBD_ATTR_S pstIspMfbdAttr;
			ISP_MFBD_CONFIG_S *mfbdInfo = &ispCoreInfo->mfbdInfo;
			ISP_TEST_GetIspMfbd(mfbdInfo,&pstIspMfbdAttr);
			ISP_DRV_SetMFBD(&pstIspMfbdAttr);
		}
		break;
		default: //ISP_PIPE_MODE_R2K
			printf("r2k doesn't 3ndr!\n");
			break;
	}


	//debug
	ISP_DRV_GetCoreRegsVal();	
	ISP_DRV_GetMFBCRegsVal();
	ISP_DRV_GetMFBDRegsVal();

	return 0;
}
/****************************************************************************
 * isp ds                                         *
 ****************************************************************************/
/*
*osd
*/
static int ISP_TEST_GetSingleOsd(ISP_DS_OSD_ATTR_S *stDsOsdAttr,ISP_OSD_INFO_S *osdInfo)
{
	ISP_CHECK_POINTER(stDsOsdAttr);
	ISP_CHECK_POINTER(osdInfo);
	//
    ISP_DS_OSD_INFO_S *stOsdInfo = &stDsOsdAttr->stOsdInfo;
	stOsdInfo->osd_enable = osdInfo->osd_enable;
	stOsdInfo->osd_type = osdInfo->osd_type;
	stOsdInfo->osd_alpha_tpye = osdInfo->osd_alpha_tpye;
	//
    ISP_DS_OSD_SIZE_S *stOsdSize = &stDsOsdAttr->stOsdSize;
	stOsdSize->osd_width = osdInfo->osd_size.Width;
	stOsdSize->osd_height = osdInfo->osd_size.Height;
	//
    ISP_DS_OSD_BUF_S *stOsdBuf   = &stDsOsdAttr->stOsdBuf;
	stOsdBuf->osd_rgb_addr0 = osdInfo->osd_rgb_addr[0];
	stOsdBuf->osd_rgb_addr1 =  osdInfo->osd_rgb_addr[1];
	stOsdBuf->osd_stride = osdInfo->osd_stride;
	stOsdBuf->osd_alpha_addr0 = osdInfo->osd_alpha_addr[0];
	stOsdBuf->osd_alpha_addr1 = osdInfo->osd_alpha_addr[1];
	stOsdBuf->osd_alpha_stride = osdInfo->osd_alpha_stride;
	stOsdBuf->osd_position_start_x = osdInfo->osd_position_win.v_start;
	stOsdBuf->osd_position_stop_x = osdInfo->osd_position_win.v_end;
	stOsdBuf->osd_position_start_y = osdInfo->osd_position_win.h_start;
	stOsdBuf->osd_position_stop_y = osdInfo->osd_position_win.h_end;
	//
    ISP_DS_OSD_DMA_CTL_S *stOsdDmaCtl = &stDsOsdAttr->stOsdDmaCtl;
	stOsdDmaCtl->osd_bd_limit_en = osdInfo->osd_bd_limit_en;
	stOsdDmaCtl->osd_dma_map = osdInfo->osd_dma_map;
	stOsdDmaCtl->osd_dma_request_length = osdInfo->osd_dma_request_length;
	stOsdDmaCtl->osd_global_alpha = osdInfo->osd_global_alpha;
	stOsdDmaCtl->osd_outstanding_num = osdInfo->osd_outstanding_num;
	stOsdDmaCtl->osd_rgb_rev = osdInfo->osd_rgb_rev;
	stOsdDmaCtl->osd_swap_64 = osdInfo->osd_swap_64;

	return 0;
}
/*
*Single Ds
*/
static int ISP_TEST_GetSingleDs(ISP_S_DS_ATTR_S *stSDsAttr,ISP_DS_INFO_S *dsInfo)
{
	ISP_CHECK_POINTER(stSDsAttr);
	ISP_CHECK_POINTER(dsInfo);
	//
	stSDsAttr->stVscalePram.scale_en = dsInfo->scale_en;
	stSDsAttr->stVscalePram.vscale_dstep = dsInfo->vscale_dstep; 
	stSDsAttr->stVscalePram.vscale_pstep = dsInfo->vscale_pstep;
	stSDsAttr->stVscalePram.vscale_filter_en = dsInfo->vscale_filter_en;
	//
    stSDsAttr->stHscalePram.hscale_dstep =  dsInfo->hscale_dstep;     
    stSDsAttr->stHscalePram.hscale_pstep=  dsInfo->hscale_pstep;     
    stSDsAttr->stHscalePram.hscale_filter_en=  dsInfo->hscale_filter_en;
	//
	stSDsAttr->stDsSize.frame_output_width = dsInfo->ds_out_size.Width;
	stSDsAttr->stDsSize.frame_output_height = dsInfo->ds_out_size.Height;
	// 
	stSDsAttr->stDsFormat.out_rgb_en =  dsInfo->out_rgb_en;
	stSDsAttr->stDsFormat.out_rgb_mode =  dsInfo->out_rgb_mode;
	stSDsAttr->stDsFormat.out_yuv_mode =  dsInfo->out_yuv_mode;
	stSDsAttr->stDsFormat.out_rgb_mode =  dsInfo->out_uv_swap;
	//osd0
	ISP_DS_OSD_ATTR_S *stDsOsdAttr = &stSDsAttr->stDsOsdAttr[0];
	ISP_OSD_INFO_S   *osdInfo = &dsInfo->osdInfo[0];
	ISP_TEST_GetSingleOsd(stDsOsdAttr,osdInfo);
	//osd1
	stDsOsdAttr = &stSDsAttr->stDsOsdAttr[1];
	osdInfo = &dsInfo->osdInfo[1];
	ISP_TEST_GetSingleOsd(stDsOsdAttr,osdInfo);
	//osd2
	stDsOsdAttr = &stSDsAttr->stDsOsdAttr[2];
	osdInfo = &dsInfo->osdInfo[2];
	ISP_TEST_GetSingleOsd(stDsOsdAttr,osdInfo);

	return 0;
}
/*
*remap
*/
static int ISP_TEST_GetRemap(ISP_REMAP_CTL_S *stIspRemapCtl,ISP_REMAP_CONFIG_S *ispRemapInfo)
{
	ISP_CHECK_POINTER(stIspRemapCtl);
	ISP_CHECK_POINTER(ispRemapInfo);

	stIspRemapCtl->LineCtlSet = ispRemapInfo->LineCtlSet;
	stIspRemapCtl->LineDataSet = ispRemapInfo->LineDataSet;
				 
	stIspRemapCtl->LineDrawEn = ispRemapInfo->LineDrawEn;
	stIspRemapCtl->VlineRightEn = ispRemapInfo->VlineRightEn;
	stIspRemapCtl->VlineLeftEn = ispRemapInfo->VlineLeftEn; 
	stIspRemapCtl->HlineBottomEn = ispRemapInfo->HlineBottomEn;
	stIspRemapCtl->HlineUpEn = ispRemapInfo->HlineUpEn; 
				
	stIspRemapCtl->LineStartPosX = ispRemapInfo->LineStartPosX;
	stIspRemapCtl->LineEndPosX = ispRemapInfo->LineEndPosX;
	stIspRemapCtl->LineStartPosY = ispRemapInfo->LineStartPosY;		
	stIspRemapCtl->LineEndPosY = ispRemapInfo->LineEndPosY;
	stIspRemapCtl->LineWidthL = ispRemapInfo->LineWidthL;
	stIspRemapCtl->LineWidthH = ispRemapInfo->LineWidthH;
				
	stIspRemapCtl->ValueCr = ispRemapInfo->ValueCr;
	stIspRemapCtl->ValueCb = ispRemapInfo->ValueCb; 
	stIspRemapCtl->ValueY = ispRemapInfo->ValueY;
	stIspRemapCtl->ValueAlpha = ispRemapInfo->ValueAlpha;			

	return 0;
}
//
static int ISP_TEST_setRemap(CRITICAL_MODULE_EN *module_en,ISP_REMAP_CONFIG_S *ispRemapInfo)
{
	ISP_CHECK_POINTER(ispRemapInfo);

	ISP_REMAP_CTL_S pstIspRemapCtl;
	ISP_DRV_LINE_DRAW_U DrawAreaNum =ISP_LINE_DRAW_AREA_0;

	if( TRUE == module_en->remap_main_en )
	{
		for(DrawAreaNum = ISP_LINE_DRAW_AREA_0;DrawAreaNum<ISP_LINE_DRAW_AREA_MAX;DrawAreaNum++)
		{
			ISP_TEST_GetRemap(&pstIspRemapCtl,&ispRemapInfo[DrawAreaNum]);
			ISP_DRV_SetRemap(ISP_PIPE_MAIN_OUT,DrawAreaNum,&pstIspRemapCtl);
		}
	}

	if( TRUE == module_en->remap0_en )
	{
		for(DrawAreaNum = ISP_LINE_DRAW_AREA_0;DrawAreaNum<ISP_LINE_DRAW_AREA_MAX;DrawAreaNum++)
		{
			ISP_TEST_GetRemap(&pstIspRemapCtl,&ispRemapInfo[DrawAreaNum]);
			ISP_DRV_SetRemap(ISP_PIPE_DS0_OUT,DrawAreaNum,&pstIspRemapCtl);
		}
	}

	if( TRUE == module_en->remap1_en )
	{
		for(DrawAreaNum = ISP_LINE_DRAW_AREA_0;DrawAreaNum<ISP_LINE_DRAW_AREA_MAX;DrawAreaNum++)
		{
			ISP_TEST_GetRemap(&pstIspRemapCtl,&ispRemapInfo[DrawAreaNum]);
			ISP_DRV_SetRemap(ISP_PIPE_DS1_OUT,DrawAreaNum,&pstIspRemapCtl);
		}
	}

	return 0;
}
/*
*
*/
int ISP_TEST_setDs(CRITICAL_MODULE_EN *module_en,ISP_DS_CONFIG_S *ispDsInfo)
{
	ISP_CHECK_POINTER(ispDsInfo);	
	ISP_DS_ATTR_S pstDsAttr;
	//
	pstDsAttr.stDsInputSize.input_frame_width = ispDsInfo->dsInSizeInfo.Width;
	pstDsAttr.stDsInputSize.input_frame_height = ispDsInfo->dsInSizeInfo.Height;
	//
	ISP_DS_OSD_RGB2YUV_COEFF_S *stDsOsdRgb2YuvCoeff = &pstDsAttr.stDsOsdRgb2YuvCoeff;
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff00 = ispDsInfo->osd_rgb2yuv_coeff[0][0];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff01 = ispDsInfo->osd_rgb2yuv_coeff[0][1];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff02 = ispDsInfo->osd_rgb2yuv_coeff[0][2];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff03 = ispDsInfo->osd_rgb2yuv_coeff[0][3];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff10 = ispDsInfo->osd_rgb2yuv_coeff[1][0];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff11 = ispDsInfo->osd_rgb2yuv_coeff[1][1];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff12 = ispDsInfo->osd_rgb2yuv_coeff[1][2];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff13 = ispDsInfo->osd_rgb2yuv_coeff[1][3];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff20 = ispDsInfo->osd_rgb2yuv_coeff[2][0];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff21 = ispDsInfo->osd_rgb2yuv_coeff[2][1];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff22 = ispDsInfo->osd_rgb2yuv_coeff[2][2];
	stDsOsdRgb2YuvCoeff->osd_rgb2yuv_coeff23 = ispDsInfo->osd_rgb2yuv_coeff[2][3];
	//
	ISP_DS_OSD_YUV2RGB_COEFF_S *stDsOsdYuv2RgbCoeff = &pstDsAttr.stDsOsdYuv2RgbCoeff;
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff00 = ispDsInfo->osd_yuv2rgb_coeff[0][0];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff01 = ispDsInfo->osd_yuv2rgb_coeff[0][1];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff02 = ispDsInfo->osd_yuv2rgb_coeff[0][2];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff03 = ispDsInfo->osd_yuv2rgb_coeff[0][3];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff10 = ispDsInfo->osd_yuv2rgb_coeff[1][0];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff11 = ispDsInfo->osd_yuv2rgb_coeff[1][1];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff12 = ispDsInfo->osd_yuv2rgb_coeff[1][2];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff13 = ispDsInfo->osd_yuv2rgb_coeff[1][3];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff20 = ispDsInfo->osd_yuv2rgb_coeff[2][0];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff21 = ispDsInfo->osd_yuv2rgb_coeff[2][1];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff22 = ispDsInfo->osd_yuv2rgb_coeff[2][2];
	stDsOsdYuv2RgbCoeff->osd_yuv2rgb_coeff23 = ispDsInfo->osd_yuv2rgb_coeff[2][3];
	ISP_REMAP_CONFIG_S *ispRemapInfo = &ispDsInfo->ispRemapInfo[0];
	ISP_TEST_setRemap(module_en->remap_main_en,ispRemapInfo);
	//DS0
	ISP_S_DS_ATTR_S *stSDsAttr = &pstDsAttr.stSDsAttr[0];
	ISP_DS_INFO_S *dsInfo = &ispDsInfo->dsInfo[0];
	ISP_TEST_GetSingleDs(stSDsAttr,dsInfo);
	ispRemapInfo = &dsInfo->ispRemapInfo[0];
	ISP_TEST_setRemap(module_en->remap0_en,ispRemapInfo);
	//DS1
	stSDsAttr = &pstDsAttr.stSDsAttr[1];
	dsInfo = &ispDsInfo->dsInfo[1];
	ISP_TEST_GetSingleDs(stSDsAttr,dsInfo);	
	ispRemapInfo = &dsInfo->ispRemapInfo[0];
	ISP_TEST_setRemap(module_en->remap1_en,ispRemapInfo);
	//DS2
	stSDsAttr = &pstDsAttr.stSDsAttr[2];
	dsInfo = &ispDsInfo->dsInfo[2];
	ISP_TEST_GetSingleDs(stSDsAttr,dsInfo);
	//	
	ISP_DRV_SetDs(&pstDsAttr);

	//debug
	ISP_DRV_GetDsRegsVal();
	ISP_DRV_GetRemapRegsVal();

	return 0;
}


