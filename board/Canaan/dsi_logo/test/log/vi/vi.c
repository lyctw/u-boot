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

#define OPEN_VI_WRAP_DEBUG 0
#define OPEN_VI_PIPE_DEBUG 0

//xtern unsigned int  *reg_vi_wrap_base  = NULL;
//extern unsigned int  *reg_vi_pipe_base[VI_MAX_PIPE_NUM]  = {NULL};
/*
*
*/
static int VI_DRV_Remap(void)
{
#if 0
	unsigned int *pu32Addr = NULL;
	
	reg_vi_wrap_base = (unsigned int *)VI_WRAP_REG_BASE;

	reg_vi_pipe_base[0] = (unsigned int *)VI_PIPE_CSI_0_0_REG_BASE;
	
	reg_vi_pipe_base[1] = (unsigned int *)VI_PIPE_CSI_0_1_REG_BASE;
	
	reg_vi_pipe_base[2] = (unsigned int *)VI_PIPE_CSI_0_2_REG_BASE;
	
	reg_vi_pipe_base[3] = (unsigned int *)VI_PIPE_CSI_1_0_REG_BASE;
	
	reg_vi_pipe_base[4] = (unsigned int *)VI_PIPE_CSI_1_1_REG_BASE;

	reg_vi_pipe_base[5] = (unsigned int *)VI_PIPE_CSI_1_2_REG_BASE;

	reg_vi_pipe_base[6] = (unsigned int *)VI_PIPE_DVP_0_REG_BASE;

	reg_vi_pipe_base[7] = (unsigned int *)VI_PIPE_DVP_1_REG_BASE;

	for(int i = 0; i<8; i++)
	{
		printf("reg_vi_pipe_base[%d] = 0x%x\n",i,reg_vi_pipe_base[i]);
	}
#endif
	VI_DRV_WRAP_Remap();
	VI_DRV_PIPE_Remap();
	return SUCCESS;
}

/****************************************************************************
 * GLOBAL VARIABLES 														*
 ****************************************************************************/
VI_DRV_CTL_S g_astViDrvCtx[VI_MAX_DEV_NUM];
#define VI_DRV_GET_CTX(ViDev) (&g_astViDrvCtx[ViDev])

/****************************************************************************
 * OSAL FUNCTION DECLARATION											*
 ****************************************************************************/

void * osal_memset(void *str,int c,int count)
{
    return memset(str, c, count);
}
/****************************************************************************
 * INTERNAL FUNCTION DECLARATION											*
 ****************************************************************************/

/****************************************************************************
 * PUBLIC FUNCTION DECLARATION											*
 ****************************************************************************/
int VI_DRV_Init(void)
{
	int Ret = 0;
	int DevIndex = 0;
	BOOL bIntrPolHigh = TRUE;
	unsigned int uIntrCtlData = 0;

	Ret = VI_DRV_Remap();

	if(FAILURE == Ret)
	{
		return Ret;
	}

	for(DevIndex=0; DevIndex<VI_MAX_DEV_NUM; DevIndex++)
	{
		osal_memset(&g_astViDrvCtx[DevIndex], 0, sizeof(VI_DRV_CTL_S));
	}

	
	for(DevIndex=0; DevIndex<VI_MAX_PIPE_NUM; DevIndex++)
	{
		uIntrCtlData = 0xffff0000;
		bIntrPolHigh = TRUE;
		VI_DRV_PIPE_InitPipeInterrupt(DevIndex, bIntrPolHigh, uIntrCtlData);
	}
	return 0;

}
/****************************************************************************
 * wrap											*
 ****************************************************************************/
/*
*rst
*/
static int VI_TEST_GetRstCtl(VI_WRAP_RESET_CTL_S *stRstCtl)
{
	VI_CHECK_POINTER(stRstCtl);

	stRstCtl->csi_00_rst_en =  1;
	stRstCtl->csi_01_rst_en =  1;
	stRstCtl->csi_02_rst_en =  1;
	
	stRstCtl->csi_10_rst_en =  1;
	stRstCtl->csi_11_rst_en =  1;
	stRstCtl->csi_12_rst_en =  1;
	stRstCtl->dvp_0_rst_en =  1;
	stRstCtl->dvp_1_rst_en =  1;
	
	stRstCtl->axi_wr_ch_rst_en =  1;
	stRstCtl->axi_rd_ch_rst_en =  1;    

	return 0;
}
/*
*ctl mode
*/
static int VI_TEST_GetCtlMode(SONY_POL_MODE_E sony_mode,DPHY_MODE_E dphy_mode,SEL_CSI_DBG_INFO_E dbgInfoSel,SENSOR_INFO *sensor_info,VI_WRAP_CSI_MODE_CTL_S *stCsiModeCtl)
{
	VI_CHECK_POINTER(sensor_info);
	VI_CHECK_POINTER(stCsiModeCtl);

	MIPI0_SENSOR_INFO *mipi0Info = &sensor_info->mipi0Info;
	MIPI1_SENSOR_INFO *mipi1Info = &sensor_info->mipi1Info;
	DVP_SENSOR_INFO   *dvpInfo = &sensor_info->dvpInfo;

	stCsiModeCtl->mipi_csi_0_mode = NORMAL_MODE;
	stCsiModeCtl->mipi_csi_1_mode = NORMAL_MODE;
	stCsiModeCtl->mipi_dphy_mode = dphy_mode;//TWO_LANES_MODE;
	stCsiModeCtl->mipi_csi01_dbg_sel = dbgInfoSel;
	stCsiModeCtl->csi_0_sony_dol_en = sony_mode;//SONY_POL_MODE_DIS;//SONY_POL_MODE_EN;//SONY_POL_MODE_DIS;
	stCsiModeCtl->isp_2k_clk_sel = F_CSI_0_CLK;
	stCsiModeCtl->isp_r_2k_clk_sel = R_TOF_CSI_1_CLK;
	stCsiModeCtl->tof_clk_sel = R_TOF_CSI_1_CLK;
	stCsiModeCtl->dvp_clk_0_mode = FALLING_EDGE;//RAISE_EGDE;
	//MIPI0
	if( TRUE == mipi0Info->sensor_interface_enable)
	{
		if( TRUE == mipi0Info->isDebug)
		{
			//stCsiModeCtl->mipi_csi_0_mode = DEBUG_MODE;
		}

    	if(SONY_WDR_SENSOR == mipi0Info->wdr_sensor_vendor)
		{
			if(( ISP_PIPE_WDR_2_FRAME == mipi0Info->wdr_mode) ||(ISP_PIPE_WDR_3_FRAME == mipi0Info->wdr_mode))
			{
				stCsiModeCtl->csi_0_sony_dol_en = SONY_POL_MODE_EN;
			}			
		}

		if( ISP_F_2K == mipi0Info->isp_pipeline)
		{
			stCsiModeCtl->isp_2k_clk_sel = F_CSI_0_CLK;
			if(TRUE == mipi0Info->tpgEn)
			{
				stCsiModeCtl->isp_2k_clk_sel = F_DPG_CLK;
			}
		}
		else if(ISP_R_2K == mipi0Info->isp_pipeline)
		{
			stCsiModeCtl->isp_r_2k_clk_sel = R_TOF_CSI_0_CLK;
			stCsiModeCtl->dvp_clk_0_mode = FALLING_EDGE;
			if(TRUE == mipi0Info->tpgEn)
			{
				stCsiModeCtl->isp_2k_clk_sel = R_TOF_DPG_CLK;
			}		
		}
		else if(ISP_TOF == mipi0Info->isp_pipeline)
		{
			stCsiModeCtl->tof_clk_sel = R_TOF_CSI_0_CLK;
			if(TRUE == mipi0Info->tpgEn)
			{
				stCsiModeCtl->tof_clk_sel = R_TOF_DPG_CLK;
			}	
		}
	}
	//MIPI1	
	if( TRUE == mipi1Info->sensor_interface_enable)
	{
		if( TRUE == mipi1Info->isDebug)
		{
			stCsiModeCtl->mipi_csi_1_mode = DEBUG_MODE;
		}	

		if( ISP_F_2K == mipi1Info->isp_pipeline)
		{
			stCsiModeCtl->isp_2k_clk_sel = F_CSI_1_CLK;
			if(TRUE == mipi1Info->tpgEn)
			{
				stCsiModeCtl->isp_2k_clk_sel = F_DPG_CLK;
			}
		}
		else if(ISP_R_2K == mipi1Info->isp_pipeline)
		{
			stCsiModeCtl->isp_r_2k_clk_sel = R_TOF_CSI_1_CLK;
			if(TRUE == mipi1Info->tpgEn)
			{
				stCsiModeCtl->isp_2k_clk_sel = R_TOF_DPG_CLK;
			}		
		}
		else if(ISP_TOF == mipi1Info->isp_pipeline)
		{
			stCsiModeCtl->tof_clk_sel = R_TOF_CSI_1_CLK;
			if(TRUE == mipi1Info->tpgEn)
			{
				stCsiModeCtl->tof_clk_sel = R_TOF_DPG_CLK;
			}	
		}
	}
	//DVP
	if(TRUE == dvpInfo->sensor_interface_enable)
	{
		if( ISP_F_2K == dvpInfo->isp_pipeline)
		{
			stCsiModeCtl->isp_2k_clk_sel = F_DVP_0_CLK;//F_DPG_CLK;
			if(TRUE == dvpInfo->tpgEn)
			{
				stCsiModeCtl->isp_2k_clk_sel = F_DPG_CLK;
			}
		}
		else if(ISP_R_2K == dvpInfo->isp_pipeline)
		{
			stCsiModeCtl->isp_r_2k_clk_sel = R_TOF_DVP_0_CLK;
			if(TRUE == dvpInfo->tpgEn)
			{
				stCsiModeCtl->isp_2k_clk_sel = R_TOF_DPG_CLK;
			}		
		}
		else if(ISP_TOF == dvpInfo->isp_pipeline)
		{
			stCsiModeCtl->tof_clk_sel = R_TOF_DPG_CLK;
			if(TRUE == dvpInfo->tpgEn)
			{
				stCsiModeCtl->tof_clk_sel = R_TOF_DPG_CLK;
			}	
		} 
	}
	return 0;
}
/*
*chl sel
*/
static int VI_TEST_GetIspChSel(SENSOR_INFO *sensor_info,VI_WRAP_ISP_CH_SEL_S *stIspChSel)
{
	VI_CHECK_POINTER(sensor_info);
	VI_CHECK_POINTER(stIspChSel);

	MIPI0_SENSOR_INFO *mipi0Info = &sensor_info->mipi0Info;
	MIPI1_SENSOR_INFO *mipi1Info = &sensor_info->mipi1Info;
	DVP_SENSOR_INFO   *dvpInfo = &sensor_info->dvpInfo;

    stIspChSel->isp_4k_l_ch_sel = CSI_00_PIPE;
    stIspChSel->isp_4k_m_ch_sel = CSI_01_PIPE;
    stIspChSel->isp_4k_s_ch_sel = CSI_02_PIPE;
    stIspChSel->isp_2k_l_ch_sel = CSI_00_PIPE;
    stIspChSel->isp_2k_m_ch_sel = CSI_01_PIPE;
    stIspChSel->isp_2k_s_ch_sel = CSI_02_PIPE;
    stIspChSel->isp_r_2k_ch_sel = DVP_0_PIPE;
    stIspChSel->isp_3d_ch_sel = DVP_1_PIPE;//CSI_10_PIPE;
	//MIPI0
	if( TRUE == mipi0Info->sensor_interface_enable)
	{
		if( ISP_F_2K == mipi0Info->isp_pipeline)
		{
    		stIspChSel->isp_2k_l_ch_sel = CSI_00_PIPE;
    		stIspChSel->isp_2k_m_ch_sel = CSI_01_PIPE;
    		stIspChSel->isp_2k_s_ch_sel = CSI_02_PIPE;
		}
		else if(ISP_R_2K == mipi0Info->isp_pipeline)
		{
			stIspChSel->isp_r_2k_ch_sel = CSI_00_PIPE;		
		}
		else if(ISP_TOF == mipi0Info->isp_pipeline)
		{
		#if 0
		    stIspChSel->isp_4k_l_ch_sel = CSI_00_PIPE;
		    stIspChSel->isp_4k_m_ch_sel = CSI_01_PIPE;
		    stIspChSel->isp_4k_s_ch_sel = CSI_02_PIPE;
		    stIspChSel->isp_2k_l_ch_sel = CSI_10_PIPE;
		    stIspChSel->isp_2k_m_ch_sel = CSI_11_PIPE;
		    stIspChSel->isp_2k_s_ch_sel = CSI_12_PIPE;
		    stIspChSel->isp_r_2k_ch_sel = DVP_0_PIPE;
		#endif
		    stIspChSel->isp_3d_ch_sel = CSI_00_PIPE;//CSI_10_PIPE;
		}		
	}
	//MIPI1
	if( TRUE == mipi1Info->sensor_interface_enable)
	{
		if( ISP_F_2K == mipi1Info->isp_pipeline)
		{
    		stIspChSel->isp_2k_l_ch_sel = CSI_10_PIPE;
    		stIspChSel->isp_2k_m_ch_sel = CSI_11_PIPE;
    		stIspChSel->isp_2k_s_ch_sel = CSI_12_PIPE;
		}
		else if(ISP_R_2K == mipi1Info->isp_pipeline)
		{
			stIspChSel->isp_r_2k_ch_sel = CSI_10_PIPE;		
		}
		else if(ISP_TOF == mipi1Info->isp_pipeline)
		{
			stIspChSel->isp_3d_ch_sel = CSI_10_PIPE; 	
		}		
	}

	if( TRUE == dvpInfo->sensor_interface_enable)
	{
	#if 0
	    stIspChSel->isp_4k_l_ch_sel = CSI_00_PIPE;
	    stIspChSel->isp_4k_m_ch_sel = CSI_01_PIPE;
	    stIspChSel->isp_4k_s_ch_sel = CSI_02_PIPE;
	    stIspChSel->isp_2k_l_ch_sel = CSI_10_PIPE;
	    stIspChSel->isp_2k_m_ch_sel = CSI_11_PIPE;
	    stIspChSel->isp_2k_s_ch_sel = CSI_12_PIPE;
	    stIspChSel->isp_r_2k_ch_sel = DVP_0_PIPE;
	    stIspChSel->isp_3d_ch_sel = DVP_1_PIPE;//CSI_10_PIPE;
	#endif
		if( ISP_F_2K == dvpInfo->isp_pipeline)
		{
    		stIspChSel->isp_2k_l_ch_sel = DVP_0_PIPE;
		}
		else if(ISP_R_2K == dvpInfo->isp_pipeline)
		{
			stIspChSel->isp_r_2k_ch_sel = DVP_0_PIPE;		
		}
		else if(ISP_TOF == dvpInfo->isp_pipeline)
		{
			stIspChSel->isp_3d_ch_sel = DVP_0_PIPE; 	
		}		
	}

	return 0;
}	
/*
*CLK
*/
static int VI_TEST_GetClockCtl(SENSOR_INFO *sensor_info,VI_WRAP_CLOCK_CTL_S *stClkCtl)
{
	VI_CHECK_POINTER(sensor_info);	
	VI_CHECK_POINTER(stClkCtl);

	MIPI0_SENSOR_INFO *mipi0Info = &sensor_info->mipi0Info;
	MIPI1_SENSOR_INFO *mipi1Info = &sensor_info->mipi1Info;
	DVP_SENSOR_INFO   *dvpInfo = &sensor_info->dvpInfo;

    stClkCtl->axi_wr_ch_clk_en = FALSE;//TRUE;
    stClkCtl->axi_rd_ch_clk_en = FALSE;//TRUE;
	//
    stClkCtl->csi_00_pixel_clk_en = FALSE;
    stClkCtl->csi_01_pixel_clk_en = FALSE;
    stClkCtl->csi_02_pixel_clk_en = FALSE;
    stClkCtl->csi_00_dma_clk_en = FALSE;
    stClkCtl->csi_01_dma_clk_en = FALSE;
    stClkCtl->csi_02_dma_clk_en = FALSE;
	if( TRUE == mipi0Info->sensor_interface_enable)
	{
		stClkCtl->csi_00_pixel_clk_en = TRUE;
		stClkCtl->csi_01_pixel_clk_en = TRUE;
		stClkCtl->csi_02_pixel_clk_en = TRUE;
		stClkCtl->csi_00_dma_clk_en = FALSE;
		if(( ISP_PIPE_WDR_2_FRAME == mipi0Info->wdr_mode) ||(ISP_PIPE_WDR_3_FRAME == mipi0Info->wdr_mode))
		{
			stClkCtl->csi_01_pixel_clk_en = TRUE;
    		stClkCtl->csi_02_pixel_clk_en = TRUE;
			stClkCtl->csi_01_dma_clk_en = TRUE;
    		stClkCtl->csi_02_dma_clk_en = TRUE;	
		}
		if(TRUE == mipi0Info->tpgEn )
		{
		    stClkCtl->axi_wr_ch_clk_en = TRUE;
		    stClkCtl->axi_rd_ch_clk_en = TRUE;
		    stClkCtl->csi_00_dma_clk_en = TRUE;
		}
	}
	//
    stClkCtl->csi_10_pixel_clk_en = FALSE;
    stClkCtl->csi_11_pixel_clk_en = FALSE;
    stClkCtl->csi_12_pixel_clk_en = FALSE;
    stClkCtl->csi_10_dma_clk_en = FALSE;
    stClkCtl->csi_11_dma_clk_en = FALSE;
    stClkCtl->csi_12_dma_clk_en = FALSE;
	if( TRUE == mipi1Info->sensor_interface_enable)
	{
		stClkCtl->csi_10_pixel_clk_en = TRUE;
		stClkCtl->csi_10_dma_clk_en = TRUE;
	}
	//
    stClkCtl->dvp_0_pixel_clk_en = FALSE;
    stClkCtl->dvp_0_dma_clk_en = FALSE;
	if( TRUE == dvpInfo->sensor_interface_enable)
	{
		stClkCtl->dvp_0_pixel_clk_en = TRUE;
		stClkCtl->dvp_0_dma_clk_en = TRUE;
	}
	//
    stClkCtl->dvp_1_pixel_clk_en = FALSE;
    stClkCtl->dvp_1_dma_clk_en = FALSE;

	return 0;
}
/*
*DMA
*/
static int VI_TEST_WRAP_GetDmaCtl(VI_WRAP_DMA_ATTR_S *stDmaAttr)
{
	VI_CHECK_POINTER(stDmaAttr);
	//
	VI_WRAP_DMA_ARB_MODE_S *stDmaArbMode = &stDmaAttr->stDmaArbMode;
	stDmaArbMode->wr_dma_arb_mode = 0;//1;
	stDmaArbMode->rd_dma_arb_mode = 0;//1;
	//
	VI_WRAP_DMA_WR_WEIGHT_0_S  *stWrChWeight0 = &stDmaAttr->stWrChWeight0;
	stWrChWeight0->vi_dma_ch0_wr_weight = 1;
	stWrChWeight0->vi_dma_ch1_wr_weight = 1;
	stWrChWeight0->vi_dma_ch2_wr_weight = 1;
	stWrChWeight0->vi_dma_ch3_wr_weight = 1;

	VI_WRAP_DMA_WR_WEIGHT_1_S  *stWrChWeight1 = &stDmaAttr->stWrChWeight1;
	stWrChWeight1->vi_dma_ch4_wr_weight = 1;
	stWrChWeight1->vi_dma_ch5_wr_weight = 1;
	stWrChWeight1->vi_dma_ch6_wr_weight = 1;
	stWrChWeight1->vi_dma_ch7_wr_weight = 1;

    VI_WRAP_DMA_RD_WEIGHT_0_S  *stRdChWeight0 = &stDmaAttr->stRdChWeight0;
	stRdChWeight0->vi_dma_ch0_rd_weight = 1;
	stRdChWeight0->vi_dma_ch1_rd_weight = 1;
	stRdChWeight0->vi_dma_ch2_rd_weight = 1;
	stRdChWeight0->vi_dma_ch3_rd_weight = 1;
	VI_WRAP_DMA_RD_WEIGHT_1_S  *stRdChWeight1 = &stDmaAttr->stRdChWeight1;
	stRdChWeight1->vi_dma_ch4_rd_weight = 1;
	stRdChWeight1->vi_dma_ch5_rd_weight = 1;
	stRdChWeight1->vi_dma_ch6_rd_weight = 1;
	stRdChWeight1->vi_dma_ch7_rd_weight = 1;
	//
    VI_WRAP_DMA_WR_PRIORITY_S  *stWrChPriority = &stDmaAttr->stWrChPriority;
	stWrChPriority->vi_dma_ch0_wr_priority = 0;
	stWrChPriority->vi_dma_ch1_wr_priority = 1;
	stWrChPriority->vi_dma_ch2_wr_priority = 2;
	stWrChPriority->vi_dma_ch3_wr_priority = 3;
	stWrChPriority->vi_dma_ch4_wr_priority = 4;
	stWrChPriority->vi_dma_ch5_wr_priority = 5;
	stWrChPriority->vi_dma_ch6_wr_priority = 6;
	stWrChPriority->vi_dma_ch7_wr_priority = 7;
	//
    VI_WRAP_DMA_RD_PRIORITY_S  *stRdChPriority = &stDmaAttr->stRdChPriority;
	stRdChPriority->vi_dma_ch0_rd_priority = 0;
	stRdChPriority->vi_dma_ch1_rd_priority = 1;
	stRdChPriority->vi_dma_ch2_rd_priority = 2;
	stRdChPriority->vi_dma_ch3_rd_priority = 3;
	stRdChPriority->vi_dma_ch4_rd_priority = 4;
	stRdChPriority->vi_dma_ch5_rd_priority = 5;
	stRdChPriority->vi_dma_ch6_rd_priority = 6;
	stRdChPriority->vi_dma_ch7_rd_priority = 7;
	//
    VI_WRAP_DMA_WR_CH_ID_S     *stWriteChId = &stDmaAttr->stWriteChId;
	stWriteChId->vi_dma_wr_ch0_id = 0;
	stWriteChId->vi_dma_wr_ch1_id = 1;
	stWriteChId->vi_dma_wr_ch2_id = 2;
	stWriteChId->vi_dma_wr_ch3_id = 3;
	stWriteChId->vi_dma_wr_ch4_id = 4;
	stWriteChId->vi_dma_wr_ch5_id = 5;
	stWriteChId->vi_dma_wr_ch6_id = 6;
	stWriteChId->vi_dma_wr_ch7_id = 7;
	//
    VI_WRAP_DMA_RD_CH_ID_S     *stReadChId = &stDmaAttr->stReadChId;	
	stReadChId->vi_dma_rd_ch0_id = 0;
	stReadChId->vi_dma_rd_ch1_id = 1;
	stReadChId->vi_dma_rd_ch2_id = 2;
	stReadChId->vi_dma_rd_ch3_id = 3;
	stReadChId->vi_dma_rd_ch4_id = 4;
	stReadChId->vi_dma_rd_ch5_id = 5;
	stReadChId->vi_dma_rd_ch6_id = 6;
	stReadChId->vi_dma_rd_ch7_id = 7; 

	return 0;
}	
/*
*
*/
int VI_TEST_SetWrap(VI_WRAP_CONFIG_S *viWrapInfo)
{
	VI_CHECK_POINTER(viWrapInfo);
	VI_WRAP_ATTR_S stViWrapAttr;
	//
	VI_WRAP_RESET_CTL_S *stRstCtl = &stViWrapAttr.stRestCtl;
	VI_TEST_GetRstCtl(stRstCtl);
	//
	SENSOR_INFO *sensor_info = &viWrapInfo->sensor_info;
	VI_WRAP_CSI_MODE_CTL_S *stCsiModeCtl = &stViWrapAttr.stWrapCsiCtl;
	DPHY_MODE_E dphy_mode  = viWrapInfo->dphy_mode;
	SEL_CSI_DBG_INFO_E dbgInfoSel = viWrapInfo->dbgInfoSel;
	SONY_POL_MODE_E sony_mode = viWrapInfo->sony_mode;
	VI_TEST_GetCtlMode(sony_mode,dphy_mode,dbgInfoSel,sensor_info,stCsiModeCtl);
	//
	sensor_info = &viWrapInfo->sensor_info;
	VI_WRAP_ISP_CH_SEL_S *stIspChSel = &stViWrapAttr.stWrapIspChSel;
	VI_TEST_GetIspChSel(sensor_info,stIspChSel);
	//
	sensor_info = &viWrapInfo->sensor_info;
	VI_WRAP_CLOCK_CTL_S *stClkCtl = &stViWrapAttr.stWarpClockCtl;
	VI_TEST_GetClockCtl(sensor_info,stClkCtl);
	//
	VI_WRAP_DMA_ATTR_S *stDmaAttr = &stViWrapAttr.stWrapDmaAttr;
	VI_TEST_WRAP_GetDmaCtl(stDmaAttr);	
	//
	VI_WRAP_CFG_DONE_S *stWrapCfgDone = &stViWrapAttr.stWrapCfgDone;
	stWrapCfgDone->vi_wrap_wp_clr = 0;
	stWrapCfgDone->vi_wrap_config_done = 1;	
	//
	VI_DRV_SetWrap(&stViWrapAttr);
	//debug
	VI_DRV_WRAP_GetWrapRegsVal();
	return 0;
}
/****************************************************************************
 * pipe											*
 ****************************************************************************/
/*
*pipe ctrl
*/
static int VI_TEST_GetPipeCtl(VI_PIPE_CTRL_INFO *ctrlInfo,VI_PIPE_CTRL_S *stPipeCtl)
{
	VI_CHECK_POINTER(ctrlInfo);
	VI_CHECK_POINTER(stPipeCtl);

    stPipeCtl->win_mode_en = ctrlInfo->win_mode_en;
    stPipeCtl->sensor_input_swap_en = ctrlInfo->sensor_input_swap_en;
    stPipeCtl->input_ch_sel = ctrlInfo->input_ch_sel;
    stPipeCtl->ch_mode_sel = ctrlInfo->ch_mode_sel;    
	
    stPipeCtl->sen_mipi_clk_pol = ctrlInfo->sen_mipi_clk_pol;
    stPipeCtl->sen_mipi_vsync_pol = ctrlInfo->sen_mipi_vsync_pol;
    stPipeCtl->sen_mipi_hsync_pol = ctrlInfo->sen_mipi_hsync_pol;
    stPipeCtl->sen_mipi_field_pol = ctrlInfo->sen_mipi_field_pol;
    
    stPipeCtl->isp_clk_pol = ctrlInfo->isp_clk_pol;
    stPipeCtl->isp_vsync_pol = ctrlInfo->isp_vsync_pol;
    stPipeCtl->isp_hsync_pol = ctrlInfo->isp_hsync_pol;
    stPipeCtl->isp_field_pol = ctrlInfo->isp_field_pol; 

	stPipeCtl->emb_en = ctrlInfo->emb_en;
    stPipeCtl->emb_enable = ctrlInfo->emb_enable;        
    stPipeCtl->emb_mode_sel = ctrlInfo->emb_mode_sel;
    stPipeCtl->emb_ecc_mode_en = ctrlInfo->emb_ecc_mode_en;

    stPipeCtl->hsync_vsync_out_en = ctrlInfo->hsync_vsync_out_en;
    stPipeCtl->sync_source_sel = ctrlInfo->sync_source_sel;
    stPipeCtl->sync_code_remove_en = ctrlInfo->sync_code_remove_en;
    stPipeCtl->sync_code_ext_en = ctrlInfo->sync_code_ext_en;  	
	
	return 0;
}
/*
*timing ctrl
*/
static int VI_TEST_GetTimingCtl(VI_PIPE_TIMING_CTRL_INFO *timingInfo,VI_PIPE_TIMING_CTRL_S *stTimingCtl)
{
	VI_CHECK_POINTER(timingInfo);
	VI_CHECK_POINTER(stTimingCtl);

    stTimingCtl->input_pixel_type= timingInfo->input_pixel_type ;
    stTimingCtl->input_yuv_format= timingInfo->input_yuv_format ;
    stTimingCtl->output_yuv_format= timingInfo->output_yuv_format ;
    stTimingCtl->yuv_order= timingInfo->yuv_order ;

    stTimingCtl->raw_pixel_width= timingInfo->raw_pixel_width ;
    stTimingCtl->data_out_timming_ctrl= timingInfo->data_out_timming_ctrl ;
    stTimingCtl->sync_mode= timingInfo->sync_mode ; 
    stTimingCtl->sync_pulse_mode= timingInfo->sync_pulse_mode ;

    stTimingCtl->emb_timeout_set= timingInfo->emb_timeout_set ; 

	return 0;
}
/*
*sync width
*/
static int VI_TEST_GetSyncWidth(VI_PIPE_SYNC_WIDTH_INFO *syncwidthInfo,VI_PIPE_SYNC_WIDTH_S *stSyncWidth)
{
	VI_CHECK_POINTER(syncwidthInfo);
	VI_CHECK_POINTER(stSyncWidth);

	stSyncWidth->image_hsync_width =  syncwidthInfo->image_hsync_width;
	stSyncWidth->image_vsync_width =  syncwidthInfo->image_vsync_width;

	return 0;
}
/*
*image size
*/
static int VI_TEST_GetImageSize(VI_IMAGE_SZIE_INFO *imageSizeInfo,VI_PIPE_IMAGE_ATTR_S *stImgAttr)
{
	VI_CHECK_POINTER(imageSizeInfo);
	VI_CHECK_POINTER(stImgAttr);

	IMAGE_SIZE 	 *vi_pipe_tpg_w_size_total = &imageSizeInfo->vi_pipe_tpg_w_size_total;
    VI_PIPE_IMAGE_SIZE_TOTAL_S *stImageSizeTotal = &stImgAttr->stImageSizeTotal;	
	stImageSizeTotal->image_h_size_total = vi_pipe_tpg_w_size_total->Width;
	stImageSizeTotal->image_v_size_total = vi_pipe_tpg_w_size_total->Height;

	CROP_SIZE   *vi_pipe_tpg_w_size_active = &imageSizeInfo->vi_pipe_tpg_w_size_active;
	VI_PIPE_IMAGE_START_S       *stImageStart = &stImgAttr->stImageStart;
	stImageStart->image_h_start = vi_pipe_tpg_w_size_active->Width_st;
	stImageStart->image_v_start = vi_pipe_tpg_w_size_active->Height_st;
	VI_PIPE_IMAGE_SIZE_ACTIVE_S *stImageSizeActive = &stImgAttr->stImageSizeActive;	
	stImageSizeActive->image_h_size_active = vi_pipe_tpg_w_size_active->Width;
	stImageSizeActive->image_v_size_active = vi_pipe_tpg_w_size_active->Height;

	return 0;
}
/*
*tpg info
*/
static int VI_TEST_GetTpgInfo(VI_TPG_INFO *tpgInfo,VI_PIPE_TPG_S *stTpg)
{
	VI_CHECK_POINTER(tpgInfo);
	VI_CHECK_POINTER(stTpg);

    VI_PIPE_BUF_S               *stPipeBuf = &stTpg->stPipeBuf;
	stPipeBuf->y_base_addr0 = tpgInfo->vi_pipe_w_addr_y0;
	stPipeBuf->y_base_addr1 = tpgInfo->vi_pipe_w_addr_y1;
	stPipeBuf->y_line_stride = tpgInfo->vi_pipe_w_addr_stride_y;
	stPipeBuf->uv_base_addr0 = tpgInfo->vi_pipe_w_addr_uv0;
	stPipeBuf->uv_base_addr1 = tpgInfo->vi_pipe_w_addr_uv1;
	stPipeBuf->uv_line_stride = tpgInfo->vi_pipe_w_addr_stride_uv;

	VI_PIPE_TPG_DMA_INFO  *viTpgDmaInfo = &tpgInfo->viTpgDmaInfo;
	VI_PIPE_TPG_DMA_CTL_S       *stTpgDmaCtrl = &stPipeBuf->stTpgDmaCtrl;
    stTpgDmaCtrl->dma_y_module_en     = viTpgDmaInfo->dma_y_module_en ;
    stTpgDmaCtrl->dma_uv_module_en    = viTpgDmaInfo->dma_uv_module_en ;
    stTpgDmaCtrl->dma_tpg_read_en     = viTpgDmaInfo->dma_tpg_read_en ;
    stTpgDmaCtrl->sync_out_en         = viTpgDmaInfo->sync_out_en ;
    stTpgDmaCtrl->sw_triger_en        = viTpgDmaInfo->sw_triger_en ;
    stTpgDmaCtrl->dma_wr_ch_err_dec_en= viTpgDmaInfo->dma_wr_ch_err_dec_en ;
    stTpgDmaCtrl->dma_rd_ch_err_dec_en= viTpgDmaInfo->dma_rd_ch_err_dec_en ; 

    VI_PIPE_TPG_IMAGE_ATTR_S    *stPipeTpgImage = &stTpg->stPipeTpgImage;
	IMAGE_SIZE 	 *vi_pipe_tpg_r_size_total = &tpgInfo->vi_pipe_tpg_r_size_total;
    VI_PIPE_TPG_SIZE_TOTAL_S    *stTpgSizeTotal = &stPipeTpgImage->stTpgSizeTotal;
	stTpgSizeTotal->tpg_hsize_total = vi_pipe_tpg_r_size_total->Width;
	stTpgSizeTotal->tpg_vsize_total = vi_pipe_tpg_r_size_total->Height;
	CROP_SIZE    *vi_pipe_tpg_r_size_active = &tpgInfo->vi_pipe_tpg_r_size_active;
    VI_PIPE_TPG_SIZE_ACTIVE_S   *stTpgSizeActive = &stPipeTpgImage->stTpgSizeActive;
	stTpgSizeActive->tpg_hsize_active = vi_pipe_tpg_r_size_active->Width;
	stTpgSizeActive->tpg_vsize_active = vi_pipe_tpg_r_size_active->Height;
    VI_PIPE_TPG_START_S         *stTpgStart = &stPipeTpgImage->stTpgStart;
	stTpgStart->tpg_v_start = vi_pipe_tpg_r_size_active->Width_st;
	stTpgStart->tpg_h_start = vi_pipe_tpg_r_size_active->Height_st;

    VI_PIPE_TPG_BUF_S           *stPipeTpgBuf = &stTpg->stPipeTpgBuf;
	stPipeTpgBuf->tpg_y_base_addr0 = tpgInfo->vi_pipe_r_addr_y0;
	stPipeTpgBuf->tpg_y_base_addr1 = tpgInfo->vi_pipe_r_addr_y1;
	stPipeTpgBuf->tpg_y_line_stride = tpgInfo->vi_pipe_r_addr_stride_y;
	VI_PIPE_DMA_CTRL_INFO      *dmaCtrlInfo = &tpgInfo->dmaCtrlInfo;
	VI_PIPE_DMA_MODE_S         *stPipeDmaMode = &stPipeTpgBuf->stPipeDmaMode;
    stPipeDmaMode->dma_y_outstand        =  dmaCtrlInfo->dma_y_outstand; 
    stPipeDmaMode->dma_uv_outstand       =  dmaCtrlInfo->dma_uv_outstand; 
    stPipeDmaMode->dma_raw_outstand      =  dmaCtrlInfo->dma_raw_outstand; 
    stPipeDmaMode->dma_y_blen            =  dmaCtrlInfo->dma_y_blen; 
    stPipeDmaMode->dma_uv_blen           =  dmaCtrlInfo->dma_uv_blen; 
    stPipeDmaMode->dma_raw_blen          =  dmaCtrlInfo->dma_raw_blen; 
    stPipeDmaMode->dma_y_uv_out_swap     =  dmaCtrlInfo->dma_y_uv_out_swap; 
    stPipeDmaMode->dma_int_line_num      =  dmaCtrlInfo->dma_int_line_num;

	return 0;	
}
/*
*isp tpg ctrl
*/
static int VI_TEST_GetIspTpg(VI_ISP_TPG_INFO *ispTpgInfo,VI_PIPE_TPG_CTL_S *stPipeTpgCtl)
{
	VI_CHECK_POINTER(ispTpgInfo);
	VI_CHECK_POINTER(stPipeTpgCtl);

	stPipeTpgCtl->tpg_en = ispTpgInfo->vi_pipe_tpg_en;
	stPipeTpgCtl->tpg_frame_ratio_fast_slow = ispTpgInfo->vi_pipe_tpg_frm_ratio;
	stPipeTpgCtl->tpg_frame_ratio_mode = ispTpgInfo->vi_pipe_tpg_frm_ratio_mode;
	stPipeTpgCtl->tpg_sync_timing_gen_mode = ispTpgInfo->vi_tpg_sync_timing_gen_mode;
	return 0;	
}
/*
*tof tpg info
*/
static int VI_TEST_GetTofTpg(VI_TOF_TPG_INFO *tofTpgInfo,VI_PIPE_TPG_TOF_S *stPipeTpgTof)
{
	VI_CHECK_POINTER(tofTpgInfo);
	VI_CHECK_POINTER(stPipeTpgTof);

	stPipeTpgTof->tof_mode_enable = tofTpgInfo->tof_mode_enable;
	stPipeTpgTof->vi_pipe_tpg_tof_frm_num = tofTpgInfo->vi_pipe_tpg_tof_frm_num;
	stPipeTpgTof->vi_pipe_tpg_tof_frm_stride = tofTpgInfo->vi_pipe_tpg_tof_frm_stride;

	return 0;	
}
/*
*int mask
*/
static int VI_TEST_GetIntMask(VI_PIPE_INT_CTL_S *stIntCtl)
{
	VI_CHECK_POINTER(stIntCtl);

	stIntCtl->dma_raw_rd_ch_err_frame_end_mask= 1;
	stIntCtl->dma_raw_rd_ch_err_immediate_mask= 1;
	stIntCtl->dma_raw_rd_ch_frame_end_mask= 1;
	stIntCtl->dma_raw_rd_ch_line_base_mask= 1;
	stIntCtl->dma_uv_wr_ch_err_frame_end_mask= 1;
	stIntCtl->dma_uv_wr_ch_err_immediate_int= 1;
	stIntCtl->dma_uv_wr_ch_frame_end_mask= 1;
	stIntCtl->dma_uv_wr_ch_line_base_mask= 1;
	stIntCtl->dma_y_wr_ch_err_frame_end_mask= 1;
	stIntCtl->dma_y_wr_ch_err_immediate_int= 1;
	stIntCtl->dma_y_wr_ch_line_base_mask= 1;
	stIntCtl->dma_y_wr_frame_end_mask= 1;
	stIntCtl->emb_ctl_frame_end_mask= 1;
	stIntCtl->emb_ctl_time_out_mask= 1;
	stIntCtl->tpg_ctl_frame_end_mask= 1;
	stIntCtl->win_ctl_frame_end_mask= 1;

	return 0;
}
/*
*int mask
*/
static int VI_TEST_GetConfigDone(VI_PIPE_CONFIG_DONE_S *stConfigDone)
{
	VI_CHECK_POINTER(stConfigDone);

	stConfigDone->pipe_config_done = 1;
	stConfigDone->int_pol = 1;

	return 0;
}
/*
*
*/
int VI_TEST_SetPipe(int s8Index,VI_PIPE_CONFIG_S *vipipeInfo)
{
	VI_CHECK_POINTER(vipipeInfo);
	VI_CHECK_PIPE(s8Index);

	VI_PIPE_ATTR_S stVipipe;
	//
	VI_PIPE_CTRL_INFO *ctrlInfo = &vipipeInfo->ctrlInfo;
	VI_PIPE_CTRL_S *stPipeCtl = &stVipipe.stPipeCtl;
	VI_TEST_GetPipeCtl(ctrlInfo,stPipeCtl);
	//
	VI_PIPE_TIMING_CTRL_INFO *timingInfo = &vipipeInfo->timingInfo;
	VI_PIPE_TIMING_CTRL_S *stTimingCtl = &stVipipe.stTimingCtl;
	VI_TEST_GetTimingCtl(timingInfo,stTimingCtl);
	//
	VI_PIPE_SYNC_WIDTH_INFO *syncwidthInfo = &vipipeInfo->syncwidthInfo;
	VI_PIPE_SYNC_WIDTH_S *stSyncWidth = &stVipipe.stPipeSync;
	VI_TEST_GetSyncWidth(syncwidthInfo,stSyncWidth);
	//
	VI_IMAGE_SZIE_INFO *imageSizeInfo = &vipipeInfo->imageSizeInfo;
	VI_PIPE_IMAGE_ATTR_S *stImgAttr = &stVipipe.stPipeImage;
	VI_TEST_GetImageSize(imageSizeInfo,stImgAttr);
	//
	VI_TPG_INFO *tpgInfo = &vipipeInfo->tpgInfo;
	VI_PIPE_TPG_S *pstTpg = &stVipipe.stPipeTpg;
	VI_TEST_GetTpgInfo(tpgInfo,pstTpg);
	//
	VI_ISP_TPG_INFO *ispTpgInfo = &vipipeInfo->ispTpgInfo;
	VI_PIPE_TPG_CTL_S *pstPipeTpgCtl = &stVipipe.stPipeTpgCtl;
	VI_TEST_GetIspTpg(ispTpgInfo,pstPipeTpgCtl);
	//
	VI_TOF_TPG_INFO *tofTpgInfo = &vipipeInfo->tofTpgInfo;
	VI_PIPE_TPG_TOF_S *pstPipeTpgTof = &stVipipe.stPipeTpgTof;
	VI_TEST_GetTofTpg(tofTpgInfo,pstPipeTpgTof);
	//
	VI_PIPE_INT_CTL_S *stIntCtl = &stVipipe.stIntCtl;
	VI_TEST_GetIntMask(stIntCtl);
	//
	VI_PIPE_CONFIG_DONE_S *stConfigDone = &stVipipe.stConfigDone;
	VI_TEST_GetConfigDone(stConfigDone);
	//

	VI_DRV_PIPE_SetPipe(s8Index,&stVipipe);
	//debug
	for(int i = 0;i<VI_MAX_PIPE_NUM;i++)
	{
		VI_DRV_PIPE_GetPipeRegsVal(i);
	}

	return 0;
}
