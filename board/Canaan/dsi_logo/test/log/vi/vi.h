/******************************************************************************

  Copyright (C), 2019, MS Tech. Co., Ltd.

 ******************************************************************************
  File Name     : vi.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : vin driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _VI_DEF_H_
#define _VI_DEF_H_

#include <video/vi/pipe/vi_pipe_drv.h>
#include <video/vi/wrap/vi_wrap_drv.h>
#include <video/video_subsystem_addr.h>

#include "vi/vi.h"
#include "isp/isp.h"




typedef struct _VI_DRV_CTL_S
{
    VI_WRAP_ATTR_S                      stWrapAttr;
    VI_PIPE_ATTR_S                      stPipeAttr[VI_MAX_PIPE_NUM];
    unsigned int                        stPipeId[VI_MAX_PIPE_NUM];
} VI_DRV_CTL_S;

typedef enum _VI_DEVICE_TYPE_E
{
	VI_DEV_MIPI,
	VI_DEV_MIPI_WDR,
	VI_DEV_DVP,
	VI_DEV_TOF,
	VI_DEV_BUTT
} VI_DEVICE_TYPE_E;

typedef enum _WDR_SENSOR_VENDOR_E
{
	SONY_WDR_SENSOR,
	OTHERS_WDR_SENSOR,
}WDR_SENSOR_VENDOR_E;

typedef enum _VI_SENSOR_TYPE_E
{
	MIPI_RAW_SENSOR,
	DVP_RAW_SENSOR,
	DVP_YUV_SENSOR,
	VI_TOF_SENSOR,
}SENSOR_TYPE_E;

typedef enum _SENSOR_INTERFACE_E
{
	MIPI0,
	MIPI1,
	DVP0,
	MAX_SENSOR_INTERFACE_NUM,
}SENSOR_INTERFACE_E;

typedef enum _MIPI_CSI_DMOE_E
{
	NORMAL_MODE,
	DEBUG_MODE,
} MIPI_CSI_MODE_E;

typedef enum _DPHY_MODE_E
{
	TWO_LANES_MODE,
	FOUR_LANES_MODE,
}DPHY_MODE_E;

typedef enum _SEL_CSI_DBG_INFO_E
{
	SEL_CSI0_DBG_INFO,
	SEL_CSI1_DBG_INFO,
}SEL_CSI_DBG_INFO_E;

typedef enum _F_CLK_SEL_E
{
	F_CSI_0_CLK,
	F_CSI_1_CLK,
	F_DVP_0_CLK,
	F_DPG_CLK,
}F_CLK_SEL_E;

typedef enum _R_TOF_CLK_SEL_E
{	
	R_TOF_CSI_1_CLK,
	R_TOF_CSI_0_CLK,
	R_TOF_DVP_0_CLK,
	R_TOF_DPG_CLK,
}R_TOF_CLK_SEL_E;

typedef enum _SONY_POL_MODE_E
{
	SONY_POL_MODE_DIS,
	SONY_POL_MODE_EN,	
}SONY_POL_MODE_E;

typedef enum _ISP_PIPELINE_E
{
	ISP_F_4K,
	ISP_F_2K,
	ISP_R_2K,
	ISP_TOF,
}ISP_PIPELINE_E;


typedef enum _DVP_SENSOR_CLK_MODE_E
{
	RAISE_EGDE,
	FALLING_EDGE,
}DVP_SENSOR_CLK_MODE_E;

typedef enum  _VI_PIPE_NUM_E
{
	CSI_00_PIPE = 0,
	CSI_01_PIPE = 1,
	CSI_02_PIPE = 2,
	CSI_10_PIPE = 3,
	CSI_11_PIPE = 4,
	CSI_12_PIPE = 5,
	DVP_0_PIPE  = 6,
	DVP_1_PIPE  = 7,	
}VI_PIPE_NUM_E;


typedef enum _VI_PIPE_TPG_TIMING
{
	SENSOR_TRG_TPG_TIMING,
	SW_TRG_TPG_TIMING,
}VI_PIPE_TPG_TIMING;

typedef struct _MIPI0_SENSOR_INFO
{
	unsigned int         sensor_interface_enable;
	unsigned int		 isDebug;
	unsigned int		 tpgEn;
	WDR_SENSOR_VENDOR_E  wdr_sensor_vendor;
	ISP_PIPE_WDR_MODE_E  wdr_mode;
	MIPI_CSI_MODE_E      mipi_mode;
	ISP_PIPELINE_E		 isp_pipeline;
}MIPI0_SENSOR_INFO;

typedef struct _MIPI1_SENSOR_INFO
{
	unsigned int         sensor_interface_enable;
	unsigned int		 isDebug;
	unsigned int		 tpgEn;
	MIPI_CSI_MODE_E      mipi_mode;
	ISP_PIPELINE_E		 isp_pipeline;
}MIPI1_SENSOR_INFO;

typedef struct _DVP_SENSOR_INFO
{
	unsigned int         sensor_interface_enable;
	unsigned int		 tpgEn;
	MIPI_CSI_MODE_E      mipi_mode;
	ISP_PIPELINE_E		 isp_pipeline;
}DVP_SENSOR_INFO;

typedef struct _SENSOR_INFO
{
	MIPI0_SENSOR_INFO mipi0Info;
	MIPI1_SENSOR_INFO mipi1Info;
	DVP_SENSOR_INFO   dvpInfo;
}SENSOR_INFO;

typedef struct _VI_WRAP_CONFIG_S
{
	DPHY_MODE_E	 dphy_mode;
	SONY_POL_MODE_E sony_mode;
	SEL_CSI_DBG_INFO_E dbgInfoSel;
	SENSOR_INFO  sensor_info;
	unsigned int vi_wrap_config_done;
} VI_WRAP_CONFIG_S;

typedef struct _VI_PIPE_CTRL_INFO
{
        unsigned int    win_mode_en;
        unsigned int    emb_en;
        unsigned int    hsync_vsync_out_en;
        unsigned int    sensor_input_swap_en; 
       
        unsigned int    sync_source_sel;
        unsigned int    input_ch_sel;
        unsigned int    ch_mode_sel;
        unsigned int    emb_enable;

		unsigned int 	isp_clk_pol;
		unsigned int 	isp_field_pol;
		unsigned int 	isp_hsync_pol;
		unsigned int 	isp_vsync_pol;
		unsigned int 	sen_mipi_clk_pol;
		unsigned int 	sen_mipi_field_pol ;
		unsigned int 	sen_mipi_hsync_pol ;
		unsigned int 	sen_mipi_vsync_pol ;  

        unsigned int    emb_mode_sel;
        unsigned int    emb_ecc_mode_en;
        unsigned int    sync_code_remove_en;
        unsigned int    sync_code_ext_en;
}VI_PIPE_CTRL_INFO;

typedef struct _VI_PIPE_TIMING_CTRL_INFO  
{
        unsigned int    input_pixel_type;
        unsigned int    input_yuv_format;
        unsigned int    output_yuv_format;
        unsigned int    yuv_order;

        unsigned int    raw_pixel_width;
        unsigned int    data_out_timming_ctrl;
        unsigned int    sync_mode; 
        unsigned int    sync_pulse_mode;

        unsigned int    emb_timeout_set;
} VI_PIPE_TIMING_CTRL_INFO;

typedef struct _VI_PIPE_SYNC_WIDTH_INFO
{
		unsigned int 	image_hsync_width;
		unsigned int 	image_vsync_width;
}VI_PIPE_SYNC_WIDTH_INFO;

typedef struct _VI_IMAGE_SZIE_INFO
{
	IMAGE_SIZE 	 vi_pipe_tpg_w_size_total;
	CROP_SIZE    vi_pipe_tpg_w_size_active;
}VI_IMAGE_SZIE_INFO;
//
typedef struct _VI_PIPE_TPG_DMA_INFO
{
    unsigned int    dma_y_module_en     ;
    unsigned int    dma_uv_module_en    ;
    unsigned int    dma_tpg_read_en     ;
    unsigned int    sync_out_en         ;
    unsigned int    sw_triger_en        ;
    unsigned int    dma_wr_ch_err_dec_en;
    unsigned int    dma_rd_ch_err_dec_en;
} VI_PIPE_TPG_DMA_INFO;
//
typedef struct _VI_PIPE_DMA_CTRL_INFO
{
    unsigned int    dma_y_outstand   ; 
    unsigned int    dma_uv_outstand  ; 
    unsigned int    dma_raw_outstand ; 
    unsigned int    dma_y_blen       ; 
    unsigned int    dma_uv_blen      ; 
    unsigned int    dma_raw_blen     ; 
    unsigned int    dma_y_uv_out_swap; 
    unsigned int    dma_int_line_num ; 
} VI_PIPE_DMA_CTRL_INFO;
//
typedef struct _VI_TPG_INFO
{
	VI_PIPE_TPG_DMA_INFO  viTpgDmaInfo;
	unsigned int vi_pipe_w_addr_y0;
	unsigned int vi_pipe_w_addr_y1;
	unsigned int vi_pipe_w_addr_uv0;
	unsigned int vi_pipe_w_addr_uv1;
	unsigned int vi_pipe_w_addr_stride_y;
	unsigned int vi_pipe_w_addr_stride_uv;
	unsigned int vi_pipe_r_addr_y0;
	unsigned int vi_pipe_r_addr_y1;
	unsigned int vi_pipe_r_addr_stride_y;
	IMAGE_SIZE 	 vi_pipe_tpg_r_size_total;
	CROP_SIZE    vi_pipe_tpg_r_size_active;
	VI_PIPE_DMA_CTRL_INFO dmaCtrlInfo;
}VI_TPG_INFO;
//
typedef struct _VI_ISP_TPG_INFO
{
	unsigned int vi_pipe_tpg_en;
	unsigned int vi_pipe_tpg_frm_ratio_mode;
	unsigned int vi_pipe_tpg_frm_ratio;
	unsigned int vi_tpg_sync_timing_gen_mode;
}VI_ISP_TPG_INFO;
//
typedef struct _VI_TOF_TPG_INFO
{
	unsigned int tof_mode_enable;
	unsigned int vi_pipe_tpg_tof_frm_num;
	unsigned int vi_pipe_tpg_tof_frm_stride;
}VI_TOF_TPG_INFO;
//
typedef struct _VI_PIPE_CONFIG_S
{  
	VI_PIPE_CTRL_INFO ctrlInfo;
	VI_PIPE_TIMING_CTRL_INFO timingInfo;
	VI_PIPE_SYNC_WIDTH_INFO  syncwidthInfo;
	VI_IMAGE_SZIE_INFO imageSizeInfo;
	VI_TPG_INFO          tpgInfo;
	VI_ISP_TPG_INFO		 ispTpgInfo;
	VI_TOF_TPG_INFO		 tofTpgInfo;
	//VI_PIPE_DMA_CTRL_INFO dmaCtrlInfo;
}VI_PIPE_CONFIG_S;

typedef struct _VI_CONFIG_S
{
	VI_WRAP_CONFIG_S 	viwrapInfo;
	VI_PIPE_CONFIG_S	vipipeInfo[VI_MAX_PIPE_NUM];	
}VI_CONFIG_S;

int VI_DRV_Init(void);
int VI_TEST_SetWrap(VI_WRAP_CONFIG_S *viWrapInfo);
int VI_TEST_SetPipe(int s8Index,VI_PIPE_CONFIG_S *vipipeInfo);
//
//int VI_TEST_Imx385NormalMode(ISP_PIPE_WDR_MODE_E wdr_mode);
int VI_TEST_Imx385NormalMode(CRITICAL_MODULE_EN *module_en);
int VI_TEST_Imx385NormalMIPI1Mode(ISP_PIPE_WDR_MODE_E wdr_mode);
//
int VI_TEST_Setjxf23sPipe(unsigned char s8Index,VI_PIPE_CONFIG_S *vipipeInfo);
int VI_TEST_jxf23s(void);
int VI_TEST_f2k_jxf23s(void);
//
int VI_TEST_opn8008(void);
//
int VI_TEST_irs238c(void);
int VI_TEST_DVP_jxf23s_irs238c(void);
//int VI_DRV_SetCsi00Int(unsigned int u32Data);
//unsigned int VI_DRV_GetCsi00Int(void);
//int VI_DRV_SetCsi10Int(unsigned int u32Data);
//unsigned int VI_DRV_GetCsi10Int(void);

#endif /* _VI_DEF_H_ */
