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

#ifndef _ISP_DEF_H_
#define _ISP_DEF_H_

#include <stdlib.h>
#include <stdio.h>
#include <video/isp_com.h>
#include <video/video_subsystem_addr.h>
#include <video/isp/core/isp_core_drv.h>
#include <video/isp/ds/isp_ds_drv.h>
#include <video/isp/mfbc/isp_mfbc_drv.h>
#include <video/isp/mfbd/isp_mfbd_drv.h>
#include <video/isp/remap/isp_remap_drv.h>
#include <video/isp/table/isp_table_drv.h>
#include <video/isp/wrap/isp_wrap_drv.h>

#include "isp/isp.h"

//
#define ISP_2K_REG_BASE                           ISP_2K_BASE_ADDR
#define ISP_2K_REG_WRAP_OFFSET                    0x00000000
#define ISP_2K_REG_CORE_OFFSET                    0x00000400
#define ISP_2K_REG_TABLE_OFFSET                   0x00000800
#define ISP_2K_REG_DS_OFFSET                      0x00003000
#define ISP_2K_REG_MFBC_OFFSET					  0x00005000
#define ISP_2K_REG_MFBD_OFFSET					  0x00005400
#define ISP_2K_REG_REMAP_OFFSET					  0x00006000

#define ISP_2K_WRAP_REG_BASE                      (ISP_2K_REG_BASE + ISP_2K_REG_WRAP_OFFSET)
#define ISP_2K_WRAP_REG_SIZE_ALIGN                0x0400

#define ISP_2K_CORE_REG_BASE                      (ISP_2K_REG_BASE + ISP_2K_REG_CORE_OFFSET)
#define ISP_2K_CORE_REG_SIZE_ALIGN                0x0400

#define ISP_2K_TABLE_REG_BASE                     (ISP_2K_REG_BASE + ISP_2K_REG_TABLE_OFFSET)
#define ISP_2K_TABLE_REG_SIZE_ALIGN               0x1f00

#define ISP_2K_DS_REG_BASE                        (ISP_2K_REG_BASE + ISP_2K_REG_DS_OFFSET)
#define ISP_2K_DS_REG_SIZE_ALIGN                  0x1f00

#define ISP_2K_MFBC_REG_BASE					  (ISP_2K_REG_BASE + ISP_2K_REG_MFBC_OFFSET)
#define ISP_2K_MFBC_REG_SIZE_ALIGN			      0x400

#define ISP_2K_MFBD_REG_BASE					  (ISP_2K_REG_BASE + ISP_2K_REG_MFBD_OFFSET)
#define ISP_2K_MFBD_REG_SIZE_ALIGN				  0x400

#define ISP_2K_REMAP_REG_BASE					  (ISP_2K_REG_BASE + ISP_2K_REG_REMAP_OFFSET)
#define ISP_2K_REMAP_REG_SIZE_ALIGN				  0x200
//
#define ISP_4K_REG_BASE                           ISP_4K_BASE_ADDR
#define ISP_4K_REG_WRAP_OFFSET                    0x00000000
#define ISP_4K_REG_CORE_OFFSET                    0x00000400
#define ISP_4K_REG_TABLE_OFFSET                   0x00000800
#define ISP_4K_REG_DS_OFFSET                      0x00003000
#define ISP_4K_REG_MFBC_OFFSET					  0x00005000
#define ISP_4K_REG_MFBD_OFFSET					  0x00005400
#define ISP_4K_REG_REMAP_OFFSET					  0x00006000

#define ISP_4K_WRAP_REG_BASE                      (ISP_4K_REG_BASE + ISP_4K_REG_WRAP_OFFSET)
#define ISP_4K_WRAP_REG_SIZE_ALIGN                0x0400

#define ISP_4K_CORE_REG_BASE                      (ISP_4K_REG_BASE + ISP_4K_REG_CORE_OFFSET)
#define ISP_4K_CORE_REG_SIZE_ALIGN                0x0400

#define ISP_4K_TABLE_REG_BASE                     (ISP_4K_REG_BASE + ISP_4K_REG_TABLE_OFFSET)
#define ISP_4K_TABLE_REG_SIZE_ALIGN               0x1f00

#define ISP_4K_DS_REG_BASE                        (ISP_4K_REG_BASE + ISP_4K_REG_DS_OFFSET)
#define ISP_4K_DS_REG_SIZE_ALIGN                  0x1f00

#define ISP_4K_MFBC_REG_BASE					  (ISP_4K_REG_BASE + ISP_4K_REG_MFBC_OFFSET)
#define ISP_4K_MFBC_REG_SIZE_ALIGN			      0x400

#define ISP_4K_MFBD_REG_BASE					  (ISP_4K_REG_BASE + ISP_4K_REG_MFBD_OFFSET)
#define ISP_4K_MFBD_REG_SIZE_ALIGN				  0x400

#define ISP_4K_REMAP_REG_BASE					  (ISP_4K_REG_BASE + ISP_4K_REG_REMAP_OFFSET)
#define ISP_4K_REMAP_REG_SIZE_ALIGN				  0x200

#define ISP_R2K_REG_BASE                          ISP_R2K_BASE_ADDR
#define ISP_R2K_REG_WRAP_OFFSET                   0x00000000
#define ISP_R2K_REG_CORE_OFFSET                   0x00000400
#define ISP_R2K_REG_TABLE_OFFSET                  0x00000800
#define ISP_R2K_REG_DS_OFFSET                     0x00003000

#define ISP_R2K_WRAP_REG_BASE                     (ISP_R2K_REG_BASE + ISP_R2K_REG_WRAP_OFFSET)
#define ISP_R2K_WRAP_REG_SIZE_ALIGN               0x0400

#define ISP_R2K_CORE_REG_BASE                     (ISP_R2K_REG_BASE + ISP_R2K_REG_CORE_OFFSET)
#define ISP_R2K_CORE_REG_SIZE_ALIGN               0x0400

#define ISP_R2K_TABLE_REG_BASE                    (ISP_R2K_REG_BASE + ISP_R2K_REG_TABLE_OFFSET)
#define ISP_R2K_TABLE_REG_SIZE_ALIGN              0x1f00

#define ISP_R2K_DS_REG_BASE                       (ISP_R2K_REG_BASE + ISP_R2K_REG_DS_OFFSET)
#define ISP_R2K_DS_REG_SIZE_ALIGN                 0x1f00

//#define ISP_2K_DRV_WRAP_REG_CTX(pstCtx)					pstCtx = (S_ISP_WRAP_REGS_TYPE *)(reg_isp_2k_wrap_base)
//#define ISP_2K_DRV_CORE_REG_CTX(pstCtx)					pstCtx = (S_ISP_CORE_REGS_TYPE *)(reg_isp_2k_core_base)
//#define ISP_2K_DRV_DS_REG_CTX(pstCtx)					  pstCtx = (S_ISP_DS_REGS_TYPE *)(reg_isp_2k_downscaler_base)
//#define ISP_2K_DRV_MFBC_REG_CTX(pstCtx)					pstCtx = (S_ISP_MFBC_REGS_TYPE *)(reg_isp_2k_mfbc_base)
//#define ISP_2K_DRV_MFBD_REG_CTX(pstCtx)					pstCtx = (S_ISP_MFBD_REGS_TYPE *)(reg_isp_2k_mfbd_base)
//#define ISP_2K_DRV_TABLE_REG_CTX(pstCtx)				pstCtx = (S_ISP_WRAP_REGS_TYPE *)(reg_isp_2k_wrap_base)

//only for simulation
#define DDR_SYS_DMAC_ADDR_START     0x00000000
#define DDR_SYS_DMAC_LENGTH         0x800
#define DDR_SYS_DMAC_ADDR_END       DDR_SYS_DMAC_ADDR_START+DDR_SYS_DMAC_LENGTH

#define DDR_GNNE_ADDR_START         DDR_SYS_DMAC_ADDR_END
#define DDR_GNNE_LENGTH             0x1000
#define DDR_GNNE_ADDR_END           DDR_GNNE_ADDR_START+DDR_GNNE_LENGTH

#define DDR_VIDEO_R2K_ADDR0_Y_START      DDR_GNNE_ADDR_END
#define DDR_VIDEO_R2K_ADDR0_Y_LENGTH     0x2f7600
#define DDR_VIDEO_R2K_ADDR0_UV_START     DDR_VIDEO_R2K_ADDR0_Y_START+DDR_VIDEO_R2K_ADDR0_Y_LENGTH
#define DDR_VIDEO_R2K_ADDR0_UV_LENGTH    0x1fa400
#define DDR_VIDEO_R2K_ADDR1_Y_START      DDR_VIDEO_R2K_ADDR0_UV_START+DDR_VIDEO_R2K_ADDR0_UV_LENGTH
#define DDR_VIDEO_R2K_ADDR1_Y_LENGTH     0x2f7600
#define DDR_VIDEO_R2K_ADDR1_UV_START     DDR_VIDEO_R2K_ADDR1_Y_START+DDR_VIDEO_R2K_ADDR1_Y_LENGTH
#define DDR_VIDEO_R2K_ADDR1_UV_LENGTH    0x1fa400
#define DDR_VIDEO_R2K_ADDR_END           DDR_VIDEO_R2K_ADDR1_UV_START+DDR_VIDEO_R2K_ADDR1_UV_LENGTH
#define VIDEO_SUBSYS_INIT_FINISH         0x100001800


typedef enum _ISP_OUT_CHL_SEL{
    MAIN_OUT,
    DS0_OUT,
    DS1_OUT,
    DS2_OUT,
}ISP_OUT_CHL_SEL;

typedef enum _ISP_IN_CH_MODE{
    BT656,
    BT1120_MIPI,
}ISP_IN_CH_MODE;

typedef enum _ISP_SYNC_POLARITY_E
{
	ISP_SYNC_POL_LOW = 0,
	ISP_SYNC_POL_HIGH = 1,
	ISP_SYNC_POL_BUTT
} ISP_SYNC_POLARITY_E;

typedef enum _ISP_HSYNC_GEN_MODE_E
{
	HSYNC_BASE_ON_INPUT_GEN_BY_ISP = 0,
	HSYNC_BASE_ON_INPUT = 1,
	HSYNC_GEN_BY_ISP_IN_FIELD_BLANK = 2,
	HSYNC_GEN_BY_ISP = 3,
	ISP_HSYNC_BUTT
} ISP_HSYNC_GEN_MODE_E;

typedef enum _ISP_VSYNC_GEN_MODE_E
{
	VSYNC_GEN_BY_ISP = 0,
	VSYNC_BASE_ON_INPUT = 1,
	ISP_VSYNC_BUTT
} ISP_VSYNC_GEN_MODE_E;

typedef enum _ISP_VIDEO_FORMAT_E
{
	ISP_RGBRAW_DATA = 0,
	ISP_YUV_DATA = 1,
	ISP_VIDEO_FORMAT_BUTT
} ISP_VIDEO_FORMAT_E;

typedef enum _ISP_YUV_FOTMAT_E
{
    IN_YUV422,
    IN_YUV420,
}ISP_YUV_FOTMAT_E;

typedef enum _ISP_RGB_OUTPUT_FOTMAT_E
{
    OUT_S_RGB,
    OUT_ARGB,
}ISP_RGB_OUTPUT_FOTMAT_E;

typedef enum _ISP_YUV422_PIXEL_ORDER_E
{
    YUYV,
    YVYU,
    UYVY,
    VYUY,
}ISP_YUV422_PIXEL_ORDER_E;

typedef enum _ISP_PIXEL_ORDER_E
{
    PIXEL_8,
    PIXEL_10,
    PIXEL_12,
    PIXEL_14,
    PIXEL_16,
    PIXEL_18,
    PIXEL_20,
    PIXEL_24,
}ISP_PIXEL_ORDER_E;

typedef enum _NR3D_MFBC_FORMAT
{
    NR3D_YUV422_ENABLE,
    NR3D_YUV420_ENABLE,
}NR3D_MFBC_FORMAT;

typedef struct _ISP_DRV_CTL_S
{
	ISP_WRAP_ATTR_S stWrapAttr;
	ISP_CORE_ATRR_S stCoreAttr;
	//ISP_DS_ATTR_S 	stDsAttr;
	ISP_MFBC_ATTR_S stMfbcAttr;
	ISP_MFBD_ATTR_S stMfbdAttr; 
  	ISP_REMAP_CTL_S stRemapAttr;
} ISP_DRV_CTL_S;

//
#if 0
typedef struct _IMAGE_SIZE{
	unsigned int Width;
	unsigned int Height;	
}IMAGE_SIZE;
#endif

typedef struct _CROP_SIZE{
	unsigned int Width_st;
	unsigned int Height_st;	
	unsigned int Width;
	unsigned int Height;	
}CROP_SIZE;

typedef struct _WIN_SIZE{
	unsigned int v_start;
	unsigned int h_start;	
	unsigned int v_end;
	unsigned int h_end;	
}WIN_SIZE;

typedef struct _ISP_WRAP_WDR_S
{
    ISP_PIPE_WDR_MODE_E 	wdr_mode ;
	unsigned int    wdr_long_ch_mode; 	
	unsigned int 	wdr_long_l2_buf_en;
    unsigned int    wdr_short_s1_buf_en; 
    unsigned int    wdr_dynamic_switch_en;
    unsigned int    wdr_long_l2_buf_depth;	
    unsigned int 	wdr_long_img_format;   
    unsigned int 	wdr_long_yuv_in_format;   
    unsigned int 	wdr_long_img_out_format;  
    unsigned int 	wdr_long_yuv422_pxl_order;
    unsigned int 	wdr_long_pixel_width;
    unsigned int    wdr_buf_base;        
    unsigned int    wdr_line_stride;	
	unsigned int    wdr_frame_buf_size;		
}ISP_WRAP_WDR_S;

typedef struct _ISP_WRAP_3DNR_S
{
    unsigned int 	nr3d_en ;
    unsigned int    nr3d_mfbcd_en;
    unsigned int    nr3d_mv_out_en;
    unsigned int 	nr3d_y_img_format; 
    unsigned int 	nr3d_y_yuv_in_format;   
    unsigned int 	nr3d_y_img_out_format;  
    unsigned int 	nr3d_y_yuv422_pxl_order;
    unsigned int 	nr3d_y_pixel_width; 
    unsigned int 	nr3d_uv_img_format; 
    unsigned int 	nr3d_uv_yuv_in_format;   
    unsigned int 	nr3d_uv_mig_out_format;  
    unsigned int 	nr3d_uv_yuv422_pxl_order;
    unsigned int 	nr3d_uv_pixel_width;    
    unsigned int    nr3d_y_buf_base; 
    unsigned int    nr3d_uv_buf_base;        
    unsigned int    nr3d_y_line_stride;
    unsigned int    nr3d_uv_line_stride;
	unsigned int    nr3d_frame_buf_size;	
}ISP_WRAP_3DNR_S;

typedef struct _ISP_WRAP_LDC_S
{
   unsigned int 	ldc_en;
   unsigned int     ldc_y_buf_base; 
   unsigned int     ldc_uv_buf_base; 
   unsigned int     ldc_line_stride; 
   unsigned int     ldc_frame_buf_size;     
}ISP_WRAP_LDC_S;

typedef struct _ISP_WRAP_MAIN_S
{
    unsigned int 	main_out_en;
	IMAGE_SIZE		main_size;
	unsigned int    main_pix_remap_en;
    unsigned int 	main_out_img_format;   
    unsigned int 	main_out_yuv_in_format;   
    unsigned int 	main_out_img_out_format;  
    unsigned int 	main_out_yuv422_pxl_order;
    unsigned int 	main_out_pxl_width;	
    unsigned int    main_y_buf0_base;   
    unsigned int    main_y_buf1_base;
    unsigned int    main_uv_buf0_base;   
    unsigned int    main_uv_buf1_base;        
    unsigned int    main_line_stride; 
	unsigned int    main_frame_buf_size;	
}ISP_WRAP_MAIN_S;

typedef struct _ISP_WRAP_DS0_S
{
    unsigned int 	ds0_out_en;
    unsigned int 	ds0_osd0_en ;   
    unsigned int 	ds0_osd1_en ; 
    unsigned int 	ds0_osd2_en ;
    unsigned int    pix_remap_out0_en;		 		
	IMAGE_SIZE		ds0_size;
    unsigned int 	ds0_out_img_format;   
    unsigned int 	ds0_out_yuv_in_format;   
    unsigned int 	ds0_out_img_out_format;  
    unsigned int 	ds0_out_yuv422_pxl_order;
    unsigned int    ds0_out_pxl_width;	
    unsigned int    ds0_y_buf0_base;   
    unsigned int    ds0_y_buf1_base;
    unsigned int    ds0_uv_buf0_base;   
    unsigned int    ds0_uv_buf1_base;       
    unsigned int    ds0_line_stride;
	unsigned int    ds0_frame_buf_size;	 
}ISP_WRAP_DS0_S;

typedef struct _ISP_WRAP_DS1_S
{
    unsigned int 	ds1_out_en;
    unsigned int 	ds1_osd0_en ;   
    unsigned int 	ds1_osd1_en ; 
    unsigned int 	ds1_osd2_en ;
    unsigned int    pix_remap_out1_en;		 		
	IMAGE_SIZE		ds1_size;
    unsigned int 	ds1_out_img_format;   
    unsigned int 	ds1_out_yuv_in_format;   
    unsigned int 	ds1_out_img_out_format;  
    unsigned int 	ds1_out_yuv422_pxl_order;
    unsigned int    ds1_out_pxl_width;	
    unsigned int    ds1_y_buf0_base;   
    unsigned int    ds1_y_buf1_base;
    unsigned int    ds1_uv_buf0_base;   
    unsigned int    ds1_uv_buf1_base;  
    unsigned int    ds1_line_stride;
	unsigned int    ds1_frame_buf_size;	 
}ISP_WRAP_DS1_S;

typedef struct _ISP_WRAP_DS2_S
{
    unsigned int 	ds2_out_en;
    unsigned int 	ds2_osd0_en ;   
    unsigned int 	ds2_osd1_en ; 	 		
	IMAGE_SIZE		ds2_size;
    unsigned int 	ds2_out_img_format;   
    unsigned int 	ds2_out_yuv_in_format;   
    unsigned int 	ds2_out_img_out_format;  
    unsigned int 	ds2_out_yuv422_pxl_order;
    unsigned int    ds2_out_pxl_width;	
    unsigned int    ds2_r_buf0_base;   
    unsigned int    ds2_r_buf1_base;
    unsigned int    ds2_g_buf0_base;   
    unsigned int    ds2_g_buf1_base; 
    unsigned int    ds2_b_buf0_base;   
    unsigned int    ds2_b_buf1_base;      
    unsigned int    ds2_line_stride; 
	unsigned int    ds2_frame_buf_size;	
}ISP_WRAP_DS2_S;

typedef struct _ISP_WRAP_DMA_S
{
	unsigned int    dma_wr_data_mode;
	unsigned int    dma_wr_out_swap;
}ISP_WRAP_DMA_S;

typedef struct _ISP_WRAP_CONFIG_S
{
	unsigned int	isp_out_sel;
	unsigned int    dvp_ch_mode;
    unsigned int    hist_3a_out_en;
	ISP_WRAP_WDR_S  wdrInfo;
	ISP_WRAP_3DNR_S nr3dInfo;
	ISP_WRAP_LDC_S  ldcInfo;
	ISP_WRAP_MAIN_S	mainInfo;
	ISP_WRAP_DS0_S	ds0Info;
	ISP_WRAP_DS1_S	ds1Info;
	ISP_WRAP_DS2_S	ds2Info;
	ISP_WRAP_DMA_S  dmaInfo[16];
} ISP_WRAP_CONFIG_S;

typedef struct _ISP_ITC_CONFIG_S
{
 	unsigned int     hsync_pol;
	unsigned int     vsync_pol;
	unsigned int     hsync_input_timing;
	unsigned int     vsync_input_timing;   
	unsigned int     flip_ctl;         
    unsigned int     video_fmt_sel;
	IMAGE_SIZE		 total_img_size;
	CROP_SIZE        itc_out_szie;
}ISP_ITC_CONFIG_S;

typedef struct _ISP_TPG_CONFIG_S
{
    unsigned int    tpg_en;
	unsigned int    tpg_sel;
    unsigned int    bayer_mode_sel;  
    unsigned int    motion_mode_sel;    
    unsigned int    wdr_l_mul_data;  
    unsigned int    wdr_m_mul_data;  
    unsigned int    wdr_s_mul_data;
}ISP_TPG_CONFIG_S;

typedef struct _ISP_BLC_CONFIG_S
{
	unsigned int    blc_en;     
    unsigned int    blc_offset; 
    unsigned int    blc_ratio;
}ISP_BLC_CONFIG_S;

typedef struct _ISP_LSC_CONFIG_S
{
    unsigned int    lsc_en;           
    unsigned int    lsc_h_center;     
    unsigned int    lsc_v_center;     
    unsigned int    lsc_r_ratio;    
    unsigned int    lsc_g_ratio;  
    unsigned int    lsc_b_ratio;   
    unsigned int    lsc_ir_ratio; 
}ISP_LSC_CONFIG_S;

typedef struct _ISP_AE_CONFIG_S
{ 
    unsigned int    ae_as_en; 
    unsigned int    ae_ag_en;      
    unsigned int    ae_airis_en;      
    unsigned int    ae_enter_ls_sel; 
    unsigned int    ae_exit_ls_sel;     
    unsigned int    ae_win_mode_sel;    
    unsigned int    ae_back_light_mode_sel;
    unsigned int    ae_day_change_en;    
    unsigned int    ae_day_change_sel;
	WIN_SIZE		ae_win_size;
    
    unsigned int    ae_tar_bright;    
    unsigned int    ae_tar_bright_range;     
    unsigned int    ae_l_ex_time;
    unsigned int    ae_m_ex_time;
    unsigned int    ae_s_ex_time;     
    unsigned int    ae_agc;       
    unsigned int    ae_ad_shuttle_freq;
    unsigned int    ae_ad_gain_freq;    
    unsigned int    ae_adjust_step_max;     
    unsigned int    ae_ex_value_max;  
    unsigned int    ae_ex_value_mid;    
    unsigned int    ae_ex_value_min;     
    unsigned int    ae_gain_value_max;    
    unsigned int    ae_gain_value_mid;
    unsigned int    ae_gain_value_min;    
    unsigned int    ae_dn_switch_ad_step_max;
    unsigned int    ae_dn_switch_wait_time;
    unsigned int    ape_max_diff;    
    unsigned int    ape_drv_signal_max;    
    unsigned int    ape_coeff_distance;    
    unsigned int    ape_coeff_speed;    
    unsigned int    ape_coeff_acceleration;     
    unsigned int    ape_drv_manual_value;  
    unsigned int    ape_damp_manual_value; 
}ISP_AE_CONFIG_S;

typedef struct _ISP_AWB_CONFIG_S
{
    unsigned int      awb_d65_en; 
    unsigned int      awb_ccm_en; 
    unsigned int      awb_en;     
    unsigned int      awb_mode_sel;
        
    unsigned int      awb_hist_mode_sel;
    unsigned int      awb_veri_en;      
    unsigned int      awb_fb_en;
    unsigned int      awb_value_save_en;
        
    unsigned int      awb_ccm_adp_adjust_en;
    unsigned int      awb_stab_en; 
    unsigned int      awb_d65_red_gain;
    
    unsigned int      awb_d65_blue_gain;
    unsigned int      ccm_coff[3][3];
  
    unsigned int      ccm_correct_coff;
        
	WIN_SIZE		  awb_win_size; 
    
    unsigned int       awb_correct_diff_th;     
    unsigned int       awb_color_changeres_time;
    unsigned int       awb_historgram_th;
    
    unsigned int      awb_red_gain_adjust;     
    unsigned int      awb_green_gain_adjust;   
    unsigned int      awb_blue_gain_adjust;    
    unsigned int      awb_red_max_value;
    unsigned int      awb_blue_max_value;      
    unsigned int      awb_red_min_value;       
    
    unsigned int      awb_blue_min_value;
    unsigned int      awb_red_obj_value;
    unsigned int      awb_blue_obj_value;
}ISP_AWB_CONFIG_S;

typedef struct _ISP_WDR_CONFIG_S
{
    unsigned int       wdr_fusion_en;      
    unsigned int       wdr_frame_sel;      
    unsigned int       wdr_adp_adjust_en;  
    unsigned int       wdr_stab_en;
    
    unsigned int       wdr_en;             
    unsigned int       wdr_ghost_remove_en; 
    unsigned int       wdr_3frame_out_mode;
    unsigned int       wdr_mode_sel;
    
    unsigned int       wdr_2frame_ex_ratio;
    unsigned int       wdr_3frame_ex_ratio; 
    unsigned int       wdr_stat_img_sel;   
    unsigned int       wdr_ltm_data_sel;
    
    unsigned int       wdr_tz_data_sel;
    unsigned int       wdr_remove_purple_en;
    unsigned int       wdr_over_ex_ratio_th1;
    
    unsigned int       wdr_over_ex_ratio_th2;
    unsigned int       wdr_fusion_ratio_th;
    
    unsigned int       wdr_fusion_value1;  
    unsigned int       wdr_fusion_value2;
}ISP_WDR_CONFIG_S;

typedef struct _ISP_CSC_CONFIG_S
{
	unsigned int    csc_r2y[3][3];
}ISP_CSC_CONFIG_S;

typedef struct _ISP_ADA_CONFIG_S
{
    unsigned int       ada_rgb_gamma_en; 
    unsigned int       ada_yuv_gamma_en; 
    unsigned int       ada_adjust_en;    
    unsigned int       ada_img_stab_en;
    
    unsigned int       ada_ccr_en;       
    unsigned int       ada_adp_en;       
    unsigned int       ada_adp_ccr_en;   
    unsigned int       ada_stat_mode_sel;
        
    unsigned int       ada_enh_mode_sel;
    unsigned int       ada_stat_max_value; 
    unsigned int       ada_ad_stren_max_value;
     
	WIN_SIZE			ada_win_size;
}ISP_ADA_CONFIG_S;

typedef struct _ISP_RGBIR_CONFIG_S
{
    unsigned int    rgbir_en;        
    unsigned int    rgbir_rtf_en;    
    unsigned int    rgbir_rpc_en;    
    unsigned int    rgbir_fusion_en;
    
    unsigned int    rgbir_output_sel;
 
    unsigned int    rgbir_rpc_max_value; 
    unsigned int    rgbir_rpc_color_coff;
    unsigned int    rgbir_rpc_luma_coff; 
    
    unsigned int    rgbir_rpc_th;       
    unsigned int    rgbir_rpc_th1;  
}ISP_RGBIR_CONFIG_S;

typedef struct _ISP_NR2D_CONFIG_S
{
    unsigned int   d2nr_pcf_en;       
    unsigned int   d2nr_raw_en;       
    unsigned int   d2nr_edge_en;      
    unsigned int   d2nr_bap_en;       
    
    unsigned int   d2nr_luma_en;      
    unsigned int   d2nr_chroma_en;    
    unsigned int   d2nr_pcf_adp_en;   
    unsigned int   d2nr_raw_adp_en;   
    
    unsigned int   d2nr_luma_adp_en;  
    unsigned int   d2nr_chroma_adp_en;
    unsigned int   d2nr_raw_intensity;
    unsigned int   d2nr_bap_intensity;

    unsigned int   d2nr_edge_intensity;
    unsigned int   d2nr_luma_intensity;
    unsigned int   d2nr_chroma_intensity;
}ISP_NR2D_CONFIG_S;

typedef struct _ISP_NR3D_CONFIG_S
{
    unsigned int    d3nr_en;            
    unsigned int    d3nr_pre_luma_en;  
    unsigned int    d3nr_pre_chroma_en; 
    unsigned int    d3nr_main_luma_en;
    
    unsigned int    d3nr_main_chroma_en;
    unsigned int    d3nr_post_luma_en;  
    unsigned int    d3nr_post_chroma_en;
    unsigned int    d3nr_2d_luma_en;
    
    unsigned int    d3nr_2d_chroma_en;  
    unsigned int    d3nr_wb_en;         
    unsigned int    d3nr_wb_sel;
    unsigned int    d3nr_adp_luma_en;
    
    unsigned int    d3nr_adp_chroma_en;
    unsigned int    d3nr_pre_luma_th;        
    unsigned int    d3nr_pre_luma_intensity;   
    unsigned int    d3nr_pre_chroma_intensity;
    
    unsigned int   d3nr_mid_filter_th;
    unsigned int   d3nr_pre_mid_filter_th;    
    unsigned int   d3nr_cur_mid_filter_th;    
    unsigned int   d3nr_low_pass_filter_th;
    unsigned int   d3nr_luma_th;             
    unsigned int   d3nr_min_value;
    unsigned int   d3nr_luma_intensity;
    
    unsigned int   d3nr_chroma_intensity;    
    unsigned int   d3nr_post_edge_th;        
    unsigned int   d3nr_post_luma_intensity;  
    unsigned int   d3nr_post_chroma_intensity;  
}ISP_NR3D_CONFIG_S;

typedef struct _ISP_ENH_CONFIG_S
{
    unsigned int    enh_ltm_en;       
    unsigned int    enh_sharp_en;     
    unsigned int    enh_cc_en;        
    unsigned int    enh_adp_ltm_en;
    
    unsigned int    enh_adp_sharp_en; 
    unsigned int    enh_adp_cc_en;    
    unsigned int    ltm_gain;  
    unsigned int    ltm_th;    
    
    unsigned int    enh_nr_th; 
    unsigned int   	enh_th1;
    unsigned int   	enh_th2;
    unsigned int    sharp_gain; 
}ISP_ENH_CONFIG_S;

typedef struct _ISP_POST_CONFIG_S
{
    unsigned int    post_cont_ad_en;   
    unsigned int    post_luma_ad_en;   
    unsigned int    post_satu_ad_en;   
    unsigned int    cont_ad_intensity;    
    unsigned int    luma_ad_intensity;
    unsigned int    satu_ad_intensity; 
}ISP_POST_CONFIG_S;

typedef struct _ISP_OTC_CONFIG_S
{
    unsigned int    post_otc_en;  
    unsigned int    otc_yc_sel;        
    unsigned int    otc_uv_format_sel; 
    unsigned int    otc_hsync_pol_sel;
    unsigned int    otc_vsync_pol_sel;
	CROP_SIZE 		otc_out_size; 	 
}ISP_OTC_CONFIG_S;

typedef struct _ISP_LDC_CONFIG_S
{
	unsigned int    ldc_en;     
    unsigned int    ldc_arith_en;   
    unsigned int    ldc_req_freq;   
    
    unsigned int    ldc_stt_ln;
    unsigned int    ldc_h_center_pos;
    
    unsigned int    ldc_v_center_pos;
    unsigned int    ldc_rectify_cr; 
    
    unsigned int    ldc_rectify_cz; 
}ISP_LDC_CONFIG_S;

typedef struct _ISP_AF_CONFIG_S
{
    unsigned int    af_stat_en;          
    unsigned int    af_stat_mode_sel; 
	WIN_SIZE		af_win_size; 
} ISP_AF_CONFIG_S;

typedef struct _ISP_MFBCD_BUF_S
{
	unsigned int data_buf_base0;
	unsigned int data_buf_base1;	
	unsigned int data_stride;
	unsigned int data_wr_blen;
}ISP_MFBCD_BUF_S;

typedef struct _ISP_MFBC_CONFIG_S
{
    unsigned int  mfbc_out_format_cfg;
    
	IMAGE_SIZE	 mfbc_input_size; 

	ISP_MFBCD_BUF_S yDataBufInfo;
	ISP_MFBCD_BUF_S yHeadBufInfo;

	ISP_MFBCD_BUF_S uvDataBufInfo;
	ISP_MFBCD_BUF_S uvHeadBufInfo;

	ISP_MFBCD_BUF_S ylDataBufInfo;
	ISP_MFBCD_BUF_S ylHeadBufInfo;
} ISP_MFBC_CONFIG_S;

typedef struct _ISP_MFBD_CONFIG_S
{
    unsigned int  mfbd_en;
    unsigned int  mfbd_format_cfg;

	IMAGE_SIZE	 mfbd_input_size; 
	
	ISP_MFBCD_BUF_S yDataBufInfo;
	ISP_MFBCD_BUF_S yHeadBufInfo;

	ISP_MFBCD_BUF_S uvDataBufInfo;
	ISP_MFBCD_BUF_S uvHeadBufInfo;

	ISP_MFBCD_BUF_S ylDataBufInfo;
	ISP_MFBCD_BUF_S ylHeadBufInfo;

} ISP_MFBD_CONFIG_S;

typedef struct _ISP_CORE_CONFIG_S
{
    unsigned int        sensor_type;
    ISP_PIPE_MODE_E 	enIspMode;
//itc
	ISP_ITC_CONFIG_S	itcInfo;
//tpg
	ISP_TPG_CONFIG_S	tpgInfo;
//blc
	ISP_BLC_CONFIG_S	blcInfo;
//lsc
	ISP_LSC_CONFIG_S	lscInfo;
//ae
	ISP_AE_CONFIG_S		aeInfo;
//awb
	ISP_AWB_CONFIG_S	awbInfo;
//wdr
	ISP_WDR_CONFIG_S	wdrInfo;
//csc
	ISP_CSC_CONFIG_S	cscInfo;
//ada
	ISP_ADA_CONFIG_S	adaInfo;
//rgbir
	ISP_RGBIR_CONFIG_S	rgbirInfo;
//nr2d
	ISP_NR2D_CONFIG_S	nr2dInfo;
//nr3d
	ISP_NR3D_CONFIG_S	nr3dInfo;
//enh
	ISP_ENH_CONFIG_S	enhInfo;
//post ctrl
	ISP_POST_CONFIG_S	postInfo;
//otc
	ISP_OTC_CONFIG_S	otcInfo;
//ldc
	ISP_LDC_CONFIG_S	ldcInfo;
//af
	ISP_AF_CONFIG_S		afInfo;
//mfbc
    ISP_MFBC_CONFIG_S   mfbcInfo;
//mdbd
    ISP_MFBD_CONFIG_S   mfbdInfo;    
} ISP_CORE_CONFIG_S;

typedef struct _ISP_REMAP_CONFIG_S
{
    unsigned int    LineCtlSet;
    unsigned int    LineDataSet;

    unsigned int    LineEndPosX;
    unsigned int    LineStartPosX;	
    unsigned int    LineStartPosY;
    unsigned int    LineEndPosY;

    unsigned int    LineDrawEn;
    unsigned int    VlineRightEn;
    unsigned int    VlineLeftEn; 
    unsigned int    HlineBottomEn;
    unsigned int    HlineUpEn; 

    unsigned int    LineWidthL; 
    unsigned int    LineWidthH;

    unsigned int    ValueCr;
    unsigned int    ValueCb; 
    unsigned int    ValueY;
    unsigned int    ValueAlpha;
} ISP_REMAP_CONFIG_S;

typedef struct _ISP_OSD_INFO_S
{
    unsigned int    osd_enable;
    unsigned int    osd_type;      
    unsigned int    osd_alpha_tpye;
	IMAGE_SIZE		osd_size;
    unsigned int    osd_rgb_addr[2];    
    unsigned int    osd_alpha_addr[2];
    unsigned int    osd_stride;       
    unsigned int    osd_alpha_stride; 
	WIN_SIZE		osd_position_win;
    unsigned int    osd_dma_request_length;
    unsigned int    osd_dma_map;           
    unsigned int    osd_rgb_rev;           
    unsigned int    osd_global_alpha;       
    unsigned int    osd_swap_64;
    unsigned int    osd_outstanding_num;
    unsigned int    osd_bd_limit_en;
}ISP_OSD_INFO_S;

typedef struct _ISP_DS_INFO_S
{
    unsigned int    scale_en;
    unsigned int    vscale_dstep;    
    unsigned int    vscale_pstep;     
    unsigned int    vscale_filter_en;
    unsigned int    hscale_dstep;     
    unsigned int    hscale_pstep;     
    unsigned int    hscale_filter_en;
	IMAGE_SIZE		ds_out_size;
    unsigned int    out_rgb_mode;
    unsigned int    out_rgb_en;  
    unsigned int    out_yuv_mode;
    unsigned int    out_uv_swap;
	ISP_OSD_INFO_S   osdInfo[ISP_DS_CH_OSD_NUM];
    ISP_REMAP_CONFIG_S	ispRemapInfo[ISP_LINE_DRAW_AREA_MAX];			
}ISP_DS_INFO_S;  

typedef struct _ISP_DS_CONFIG_S
{
	IMAGE_SIZE 		dsInSizeInfo;
	unsigned int    osd_rgb2yuv_coeff[3][4];
	unsigned int    osd_yuv2rgb_coeff[3][4];
	ISP_REMAP_CONFIG_S	ispRemapInfo[ISP_LINE_DRAW_AREA_MAX];
	ISP_DS_INFO_S	dsInfo[ISP_DS_CH_NUM];
} ISP_DS_CONFIG_S;

typedef struct _ISP_CONFIG_S
{
	ISP_WRAP_CONFIG_S 	ispWrapInfo;
	ISP_CORE_CONFIG_S 	ispCoreInfo;
	ISP_DS_CONFIG_S	  	ispDsInfo[ISP_DS_CH_NUM];
//	ISP_MFBC_CONFIG_S	ispMfbcInfo;
//	ISP_MFBD_CONFIG_S	ispMfbdInfo;
//	ISP_REMAP_CONFIG_S	ispRemapInfo[ISP_LINE_DRAW_AREA_MAX];
} ISP_CONFIG_S;

typedef struct _ISP_SIZE_S
{
    IMAGE_SIZE in_size;
    IMAGE_SIZE out_size;
    IMAGE_SIZE ds0_size;
    IMAGE_SIZE ds1_size;
    IMAGE_SIZE ds2_size;
}ISP_SIZE_S;

int ISP_DRV_Init(ISP_PIPE_MODE_E enIspMode);
int ISP_TEST_setWrap(ISP_WRAP_CONFIG_S *ispWrapInfo);
int ISP_TEST_setCore(ISP_CORE_CONFIG_S *ispCoreInfo);
//int ISP_TEST_setDs(ISP_DS_CONFIG_S *ispDsInfo);
int ISP_TEST_setDs(CRITICAL_MODULE_EN *module_en,ISP_DS_CONFIG_S *ispDsInfo);
//
int ISP_DRV_TEST_Imx385NormalMode(CRITICAL_MODULE_EN *module_en,ISP_SIZE_S *sizeInfo);
int ISP_DRV_TEST_Jxf23s(CRITICAL_MODULE_EN *module_en,ISP_SIZE_S *sizeInfo);
int ISP_DRV_TEST_Os4a10NormalMode(CRITICAL_MODULE_EN *module_en,ISP_SIZE_S *sizeInfo);
#endif /*_ISP_DEF_H_*/
