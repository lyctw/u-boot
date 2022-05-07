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

#ifndef _ISP_3D_DEF_H_
#define _ISP_3D_DEF_H_

#include <video/isp_com.h>
#include <video/video_subsystem_addr.h>
#include <video/isp_3d/wrap/isp_3d_wrap_reg.h>
#include <video/isp_3d/wrap/isp_3d_wrap_drv.h>
#include <video/isp_3d/core/isp_3d_core_reg.h>
#include <video/isp_3d/core/isp_3d_core_drv.h>



#define TOF_REG_BASE                        ISP_3D_BASE_ADDR
#define TOF_REG_WRAP_OFFSET                 0x00000000
#define TOF_REG_CORE_OFFSET                 0x00000400
#define TOF_REG_TABLE_OFFSET                0x00000800
#define TOF_REG_DS_OFFSET                   0x00003000

#define TOF_WRAP_REG_BASE                   (TOF_REG_BASE + TOF_REG_WRAP_OFFSET)
#define TOF_WRAP_REG_SIZE_ALIGN             0x0400

#define TOF_CORE_REG_BASE                   (TOF_REG_BASE + TOF_REG_CORE_OFFSET)
#define TOF_CORE_REG_SIZE_ALIGN             0x0400

#define TOF_TABLE_REG_BASE                  (TOF_REG_BASE + TOF_REG_TABLE_OFFSET)
#define TOF_TABLE_REG_SIZE_ALIGN            0x1f00

#define TOF_DS_REG_BASE                     (TOF_REG_BASE + TOF_REG_DS_OFFSET)
#define TOF_DS_REG_SIZE_ALIGN               0x1f00

#define TOF_MAX_DEV_NUM 1

typedef enum _TOF_INFRARED_E
{
    VISIBLE_INFRARED_LIGHT = 0,
    INFRARED_LIGHT = 1,
}TOF_INFRARED_E;

typedef enum _TOF_DM_E
{
    PWM = 0,
    CWM = 1,
}TOF_DM_E;

typedef enum _TOF_SENSEOR_TYPE_E
{
    NO_DPG = 0,
    DPG = 1,
}TOF_SENSEOR_TYPE_E;

typedef enum _TOF_POLARITY_E
{
    POSTIVE_POL = 0,
    NEGATIVE_POL = 1,
}TOF_POLARITY_E;

typedef enum _TOF_PWM_ORDER_CFG_E
{
    PWM_ORDER_012 = 0,
    PWM_ORDER_120 = 1,
    PWM_ORDER_201 = 2,
}TOF_PWM_ORDER_CFG_E;

typedef enum _TOF_CWM_ORDER_CFG_E
{
    CWM_ORDER_0123 = 0,
    CWM_ORDER_1230 = 1,
    CWM_ORDER_2301 = 2,
    CWM_ORDER_3012 = 3,
}TOF_CWM_ORDER_CFG_E;

typedef struct _TOF_WRAP_OUT_SIZE_INFO
{
    unsigned int tof_out_v_size;
    unsigned int tof_out_h_size;
}TOF_WRAP_OUT_SIZE_INFO;

typedef struct _TOF_WRAP_DMA_ARB_MODE_INFO
{
    unsigned char    tof_dma_rd_arb_mode;
    unsigned char    tof_dma_wr_arb_mode;
} TOF_WRAP_DMA_ARB_MODE_INFO;

typedef  struct _TOF_WRAP_DMA_CFG_INFO
{
    unsigned int    tof_wr_outst       ;
    unsigned int    tof_rd_outst       ;
    unsigned int    tof_wr_burstl      ;
    unsigned int    tof_rd_burstl      ;
    unsigned int    tof_y_uv_noncon_en ;
    unsigned int    tof_y_uv_swap_en   ;
    unsigned int    tof_wr_int_line_num;
    unsigned int    tof_wr_err_dec_en  ;
    unsigned int    tof_rd_err_dec_en  ;
} TOF_WRAP_DMA_CFG_INFO;
											   
typedef struct _TOF_WRAP_DMA_ERR_DEC_CFG_INFO                                 
{                                         
    unsigned int    tof_wr_err_dec_unit;
    unsigned int    tof_rd_err_dec_unit;
    unsigned int    tof_wr_err_gen_thr ;
    unsigned int    tof_rd_err_gen_thr ;
} TOF_WRAP_DMA_ERR_DEC_CFG_INFO; 

typedef struct _TOF_WRAP_DMA_MODE_INFO
{
    TOF_WRAP_DMA_ARB_MODE_INFO     DmaArbMode;
    unsigned char                  wr_dma_ch_weight[TOF_DMA_CH_NUM];
    unsigned char                  rd_dma_ch_weight[TOF_DMA_CH_NUM];
    unsigned char                  wr_dma_ch_priority[TOF_DMA_CH_NUM];
    unsigned char                  rd_dma_ch_priority[TOF_DMA_CH_NUM];
    unsigned char                  wr_dma_ch_id[TOF_DMA_CH_NUM];
    unsigned char                  rd_dma_ch_id[TOF_DMA_CH_NUM];
    TOF_WRAP_DMA_CFG_INFO          DmaCh0Cfg;
    TOF_WRAP_DMA_ERR_DEC_CFG_INFO  DmaCh0ErrCfg;
    TOF_WRAP_DMA_CFG_INFO          DmaCh1Cfg;
    TOF_WRAP_DMA_ERR_DEC_CFG_INFO  DmaCh1ErrCfg;   
} TOF_WRAP_DMA_MODE_INFO;

typedef struct _TOF_WRAP_BUF_INFO
{
    unsigned int    tof_gray_buf0_base;
    unsigned int    tof_gray_buf1_base;
    
    unsigned int    tof_depth_buf0_base;
    unsigned int    tof_depth_buf1_base;
    
    unsigned short    tof_gray_line_stride;
    unsigned short    tof_depth_line_stride;
} TOF_WRAP_BUF_INFO;

typedef struct _TOF_WRAP_AXI_CTL_INFO
{
    unsigned int    tof_axi_wr_ch_rst_req ;
    unsigned int    tof_axi_rd_ch_rst_req ;
    unsigned int    tof_axi_wr_swrst_ready;
    unsigned int    tof_axi_rd_swrst_ready;
} TOF_WRAP_AXI_CTL_INFO;  

typedef struct _TOF_WRAP_INT_CTL_INFO
{
    unsigned int    tof_core_int_st_in_msk        ;
    unsigned int    tof_core_int_st_itc_out_msk   ;
    unsigned int    tof_core_int_st_demo_out_msk  ;
    unsigned int    tof_core_int_st_ae_out_msk    ;
    unsigned int    tof_core_int_st_img_out_msk   ;
    unsigned int    tof_dma_wr_int_gray_frame_msk ;
    unsigned int    tof_dma_wr_int_gray_line_msk  ;
    unsigned int    tof_dma_wr_int_gray_frame_err_msk ;
    unsigned int    tof_dma_wr_int_gray_imm_err_msk   ;
    unsigned int    tof_dma_wr_int_depth_frame_msk    ;
    unsigned int    tof_dma_wr_int_depth_line_msk     ;
    unsigned int    tof_dma_wr_int_depth_frame_err_msk;
    unsigned int    tof_dma_wr_int_depth_imm_err_msk  ; 
} TOF_WRAP_INT_CTL_INFO;

typedef struct _TOF_WRAP_CONFIG_S
{
    TOF_WRAP_OUT_SIZE_INFO outSizeInfo;
    TOF_WRAP_DMA_MODE_INFO dmaModeInfo;
    TOF_WRAP_BUF_INFO      bufInfo;
    TOF_WRAP_AXI_CTL_INFO  axiCtlInfo;
    TOF_WRAP_INT_CTL_INFO  intCtlInfo;
}TOF_WRAP_CONFIG_S;

typedef struct _TOF_CORE_ITC_INFO
{    
    TOF_DRV_SENSOR_TYPE_E enSensorType;
    unsigned int  hsync_pol;
    unsigned int  vsync_pol;
    unsigned int  hsync_input_timing;
    unsigned int  vsync_input_timing;
    unsigned int  itc_sl;
    unsigned int  tof_itc_height;
    unsigned int  tof_itc_width;
    unsigned int  tof_itc_v_start;
    unsigned int  tof_itc_h_start;
    unsigned int  tof_itc_active_width;
    unsigned int  tof_itc_active_height;
    unsigned int  tof_itc_active_start_line;
} TOF_CORE_ITC_INFO;


#if 0
typedef enum _TOF_DRV_SENSOR_TYPE_E
{
    TOF_SENSOR_TYPE_TOF = 0,
    TOF_SENSOR_TYPE_INFRADE = 1,
    TOF_SENSOR_TYPE_BUTT
}TOF_DRV_SENSOR_TYPE_E;
#endif

typedef struct _TOF_CORE_GEN_INFO
{
    unsigned int   tof_gray_sel;
    unsigned int   tof_dm_sel;
    unsigned int   tof_sensor_sel;
    unsigned int   tof_depth_pol_sel;
    unsigned int   tof_pwm_order_cfg;
    unsigned int   tof_cwm_order_cfg;
} TOF_CORE_GEN_INFO;

typedef struct _TOF_CORE_GRAY_INFO
{
    unsigned int   tof_gray_th;
} TOF_CORE_GRAY_TH_INFO;

typedef struct _TOF_CORE_AE_INFO
{
    unsigned int       ae_as_en;
    unsigned int       ae_ag_en;
    unsigned int       ae_airis_en;
    unsigned int       ae_enter_lock_sel;

    unsigned int       ae_exit_lock_sel;
    unsigned int       ae_win_mode_sel;
    unsigned int       ae_back_light_mode_sel;
    unsigned int       reserved0;

    unsigned int      ae_win_h_start;
    unsigned int      ae_win_v_start;
    unsigned int      ae_win_h_end;
    unsigned int      ae_win_v_end;

    unsigned int      ae_tar_bright;
    unsigned int      ae_tar_bright_range;
    unsigned int      ae_ex_time;
    unsigned int      ae_agc;
    
    unsigned int      ae_ad_freq;
    unsigned int      ae_ad_step_max;

    unsigned int      ae_ex_value_max;
    unsigned int      ae_ex_value_mid;
    unsigned int      ae_ex_value_min;
    
    unsigned int      ae_gain_value_max;
    unsigned int      ae_gain_value_mid;
    unsigned int      ae_gain_value_min;

} TOF_CORE_AE_INFO;


typedef struct _TOF_CORE_NR2D_INFO
{
    unsigned int   tof_gray_dpc_en;
    unsigned int   tof_depth_dpc_en;
    unsigned int   tof_2dnr_gray_en;
    unsigned int   tof_2dnr_depth_en;
    unsigned int   tof_2dnr_gray;
    unsigned int   tof_2dnr_depth;
} TOF_CORE_NR2D_INFO;

typedef struct _TOF_CORE_POST_INFO
{
    unsigned int   tof_output_sel;
    unsigned int   tof_hsync_pol_sel;
    unsigned int   tof_vsync_pol_sel;
    unsigned int   tof_gray_gmma_en;
    unsigned int   tof_depth_cont_ad_en;
    
    unsigned int   tof_gray_cont_en;
    unsigned int   tof_gray_luma_ad_en;
    
    unsigned int   tof_cont_ad_intensity;
    unsigned int   tof_luma_ad_intensity;
    unsigned int   tof_Depth_cont_ad_intensity;
} TOF_CORE_POST_INFO;

typedef struct _TOF_CORE_CONFIG_S
{  
    TOF_CORE_ITC_INFO  ItcInfo;
    TOF_CORE_GEN_INFO  GenInfo; 
    TOF_CORE_GRAY_TH_INFO GrayThInfo;
    TOF_CORE_AE_INFO   AeInfo;
    TOF_CORE_NR2D_INFO Nr2dInfo;
    TOF_CORE_POST_INFO PostInfo;
}TOF_CORE_CONFIG_S;

typedef struct _TOF_CONFIG_S
{
    TOF_WRAP_CONFIG_S tofWrap;
    TOF_CORE_CONFIG_S tofCore;
}TOF_CONFIG_S;

typedef struct _TOF_DRV_CTL_S
{
    TOF_WRAP_ATTR_S stTofWrapAttr;
    TOF_CORE_ATTR_S stTofCoreAttr;
} TOF_DRV_CTL_S;

int TOF_DRV_Init( void );
int TOF_TEST_setWrap(TOF_WRAP_CONFIG_S *tofWrapInfo);
int TOF_TEST_setCore(TOF_CORE_CONFIG_S *tofCoreInfo);
//
int TOF_TEST_opn8008(IMAGE_SIZE *imagesize);
int TOF_TEST_irs238c(IMAGE_SIZE *imagesize);
void InitIsp3D_Irs238c(void);
#endif /*_ISP_3D_DEF_H_*/
