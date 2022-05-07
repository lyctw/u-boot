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
#if 0
int VI_DRV_TEST_Os8a104kMode(void)
{
	VI_DEV viDev = 0;
	unsigned char s8PipeIndex = 0;
	VI_DRV_CTL_S *pstMipiDrvCtx = NULL;
	VI_WRAP_CSI_MODE_CTL_S *pstCsiMode = NULL;
	VI_WRAP_ISP_CH_SEL_S *pstIspChSel = NULL;
	VI_WRAP_CLOCK_CTL_S *pstClkConf = NULL;
	VI_WRAP_DMA_ATTR_S *pstDmaAttr = NULL;

	VI_PIPE_CTRL_S *pstPipeCtl = NULL;
	VI_PIPE_TIMING_CTRL_S *pstPipeTiming = NULL;
	VI_PIPE_SYNC_WIDTH_S *pstPipeSyncWidth = NULL;
	VI_PIPE_IMAGE_ATTR_S *pstImageAttr = NULL;

	pstMipiDrvCtx = VI_DRV_GET_CTX(viDev);
	VI_CHECK_POINTER(pstMipiDrvCtx);

	/*reset the vin wrap*/
	VI_DRV_WRAP_SetReset();

	/*config vi wrapper attibute*/
	pstCsiMode = &(pstMipiDrvCtx->stWrapAttr.stWrapCsiCtl);
	pstCsiMode->mipi_csi_0_mode = 0; 
	pstCsiMode->mipi_csi_1_mode = 0; 
	pstCsiMode->mipi_dphy_mode = 1; 
	VI_DRV_WRAP_SetCtlMode(pstCsiMode);

	/*config vi isp channel*/
	pstIspChSel = &(pstMipiDrvCtx->stWrapAttr.stWrapIspChSel);
	VI_DRV_GetWraptIspChannelDefaulConfig(pstIspChSel);
	pstIspChSel->isp_2k_l_ch_sel = VI_MIPI_CSI10_PIPE_ID;
	pstIspChSel->isp_2k_m_ch_sel = VI_MIPI_CSI11_PIPE_ID;
	pstIspChSel->isp_2k_s_ch_sel = VI_MIPI_CSI12_PIPE_ID;
	VI_DRV_WRAP_SetIspChSel(pstIspChSel);

	/*enable vi clock*/
	pstClkConf = &(pstMipiDrvCtx->stWrapAttr.stWarpClockCtl);
	VI_DRV_GetWrapClkDefaultConfig(pstClkConf);
	pstClkConf->csi_00_dma_clk_en = 0;
	pstClkConf->csi_01_dma_clk_en = 0;
	pstClkConf->csi_02_dma_clk_en = 0;
	pstClkConf->csi_00_pixel_clk_en = 1;
	pstClkConf->csi_01_pixel_clk_en = 1;
	pstClkConf->csi_02_pixel_clk_en = 1;	
	pstClkConf->csi_10_dma_clk_en = 0;
	pstClkConf->csi_11_dma_clk_en = 0;
	pstClkConf->csi_12_dma_clk_en = 0;
	pstClkConf->csi_10_pixel_clk_en = 0;
	pstClkConf->csi_11_pixel_clk_en = 0;
	pstClkConf->csi_12_pixel_clk_en = 0;
	pstClkConf->dvp_0_dma_clk_en = 0;
	pstClkConf->dvp_1_dma_clk_en = 0;
	pstClkConf->dvp_0_pixel_clk_en = 0;
	pstClkConf->dvp_1_pixel_clk_en = 0;
	pstClkConf->axi_rd_ch_clk_en = 0;
	pstClkConf->axi_wr_ch_clk_en = 0;
	VI_DRV_WRAP_SetClockCtl(pstClkConf);

	/*config vi DMA */
	pstDmaAttr = &(pstMipiDrvCtx->stWrapAttr.stWrapDmaAttr);
	VI_DRV_GetWrapDmaDefaultConfig(pstDmaAttr);
	VI_DRV_WRAP_SetDmaAttr(pstDmaAttr);
	
	/*call wrap config done*/
	VI_DRV_WRAP_SetConfigDone();

	
	/*config vi pipe 0 attibute*/	
	s8PipeIndex = 0;
	pstMipiDrvCtx->stPipeId[s8PipeIndex] = VI_MIPI_CSI00_PIPE_ID;

	/*config pipe control*/
	pstPipeCtl = &(pstMipiDrvCtx->stPipeAttr[s8PipeIndex].stPipeCtl);
	pstPipeCtl->win_mode_en = 1;
	pstPipeCtl->hsync_vsync_out_en = 1;
	
	pstPipeCtl->sen_mipi_clk_pol = 1;
	pstPipeCtl->sen_mipi_field_pol = 1;
	
	pstPipeCtl->isp_clk_pol = 1;	
	pstPipeCtl->isp_vsync_pol = 1;
	pstPipeCtl->isp_hsync_pol = 1;
	pstPipeCtl->isp_field_pol = 1;
	
	pstPipeCtl->input_ch_sel = 1;
	pstPipeCtl->ch_mode_sel = 1;
	VI_DRV_PIPE_SetPipeCtl(pstMipiDrvCtx->stPipeId[s8PipeIndex], pstPipeCtl);

	/*config pipe timing and vi input info, the config values related to sensor*/
	pstPipeTiming = &(pstMipiDrvCtx->stPipeAttr[s8PipeIndex].stTimingCtl);
	pstPipeTiming->input_pixel_type = 0;/*RAW input*/
	pstPipeTiming->input_yuv_format = 0;
	pstPipeTiming->yuv_order = 0;
	pstPipeTiming->raw_pixel_width = 2; /*RAW 12bit*/
	pstPipeTiming->data_out_timming_ctrl = 3;/*four cycle delay*/
	pstPipeTiming->sync_mode = 4;
	VI_DRV_PIPE_SetTimingCtl(pstMipiDrvCtx->stPipeId[s8PipeIndex], pstPipeTiming);

	/*config pipe sync widht*/
	pstPipeSyncWidth = &(pstMipiDrvCtx->stPipeAttr[s8PipeIndex].stPipeSyncAttr);
	pstPipeSyncWidth->image_hsync_width = 7;
	pstPipeSyncWidth->image_vsync_width = 7;
	VI_DRV_PIPE_SetSyncWidthCtl(pstMipiDrvCtx->stPipeId[s8PipeIndex], pstPipeSyncWidth);
	
	/*config pipe image info*/
	pstImageAttr =  &(pstMipiDrvCtx->stPipeAttr[s8PipeIndex].stPipeImageAttr);
	
	pstImageAttr->stImageSizeTotal.image_v_size_total = 0x903;
	pstImageAttr->stImageSizeTotal.image_h_size_total = 0x21bb;
	pstImageAttr->stImageSizeActive.image_v_size_active = 0x86f;
	pstImageAttr->stImageSizeActive.image_h_size_active = 0xeff;


	pstImageAttr->stImageStart.image_v_start = 0x3fff;
	pstImageAttr->stImageStart.image_h_start = 0x0;
	VI_DRV_PIPE_SetImageAttr(pstMipiDrvCtx->stPipeId[s8PipeIndex], pstImageAttr);
	
	/*call pipe config done*/
	VI_DRV_PIPE_SetConfigDoneCtl(pstMipiDrvCtx->stPipeId[s8PipeIndex]);
	
	return 0;
}
#endif
