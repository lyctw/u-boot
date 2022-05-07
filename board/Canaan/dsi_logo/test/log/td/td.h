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

#ifndef _TD_DEF_H_
#define _TD_DEF_H_

#include <video/isp_com.h>
#include <video/video_subsystem_addr.h>
#include <video/td/wrap/td_wrap_drv.h>
#include <video/td/core/td_core_drv.h>

#include "td/td.h"

typedef enum _TD_TEST_CASE_E
{
    TD_CASE_UNDEFINE = 0,
    TD_ROTATION_90_DEGREE_320352_MONO,
    TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_INPUT,
    TD_ROTATION_90_DEGREE_320352_MONO_SWAP_INPUT,
    TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_OUTPUT,
    TD_ROTATION_90_DEGREE_320352_MONO_SWAP_OUTPUT,
    TD_ROTATION_90_DEGREE_320352_420,
    TD_ROTATION_90_DEGREE_320352_422,
    TD_ROTATION_90_DEGREE_444,
    TD_ROTATION_90_DEGREE_1080p_420_TIMEOUT,
    TD_ROTATION_270_DEGREE_320352_420,
    TD_ROTATION_270_DEGREE_320352_422,
    TD_ROTATION_90_DEGREE_MAIN_420,
    TD_ROTATION_270_DEGREE_MAIN_420,
    TD_ROTATION_90_DEGREE_MAIN_422,
    TD_ROTATION_90_DEGREE_MAIN_444,

    TD_ROTATION_90_DEGREE_1080P_420,
    TD_ROTATION_90_DEGREE_720P_420,
    TD_ROTATION_90_DEGREE_VGA_420,
    TD_ROTATION_90_DEGREE_CIF_420,
    TD_ROTATION_90_DEGREE_QCIF_420,
    TD_ROTATION_270_DEGREE_1080P_420,
    TD_ROTATION_270_DEGREE_720P_420,
    TD_ROTATION_270_DEGREE_VGA_420,
    TD_ROTATION_270_DEGREE_CIF_420,
    TD_ROTATION_270_DEGREE_QCIF_420,
    TD_ROTATION_90_DEGREE_1080P_422,
    TD_ROTATION_90_DEGREE_720P_422,
    TD_ROTATION_90_DEGREE_VGA_422,
    TD_ROTATION_90_DEGREE_CIF_422,
    TD_ROTATION_90_DEGREE_QCIF_422,
    TD_ROTATION_270_DEGREE_1080P_422,
    TD_ROTATION_270_DEGREE_720P_422,
    TD_ROTATION_270_DEGREE_VGA_422,
    TD_ROTATION_270_DEGREE_CIF_422,
    TD_ROTATION_270_DEGREE_QCIF_422,
    TD_ROTATION_90_DEGREE_1080P_MONO,
    TD_ROTATION_270_DEGREE_1080P_MONO,
    TD_ROTATION_90_DEGREE_CIF_RGB888,
    TD_ROTATION_270_DEGREE_CIF_RGB888,
    TD_ROTATION_90_DEGREE_1080P_BITSWAP_420,
    TD_ROTATION_90_DEGREE_1080P_ENDIANSWAP_420,
    TD_ROTATION_90_DEGREE_STRIDE_TEST,
    TD_ROTATION_90_DEGREE_MAIN_420_IRQ,

    TD_SCALER_1080P_420IN_YUV420OUT,
    TD_SCALER_1080P_420IN_YUV422OUT,//needed?
    TD_SCALER_1080P_420IN_ARGBOUT,
    TD_SCALER_1080P_420IN_SEPARATE_RGBOUT,    
    TD_SCALER_1080P_422IN_YUV422OUT,
    TD_SCALER_1080P_422IN_YUV420OUT,
    TD_SCALER_1080P_422IN_ARGBOUT,
    TD_SCALER_1080P_422IN_SEPARATE_RGBOUT,
  
    TD_MIXER_VIDEO_320352_OSD_256200,
    TD_MIXER_MAINYUV_320to640480,
    TD_MIXER_MAINYUV_320to176144,
    TD_MIXER_MAINYUV_1080to320240,
    TD_MIXER_MAINYUV_BACKGROUND,
    TD_MIXER_MAINYUV_ALPHA,
    TD_MIXER_MAINYUV_MIXER,
    TD_MIXER_MAINYUV_POSITION,
    TD_MIXER_MAINYUV_CROP,
    TD_MIXER_MAINYUV_JOINT,
    TD_MIXER_MAINYUV_JOINT_DEBUG,
    TD_MIXER_MAINYUV_ROTATION,
    TD_MIXER_MAIN_RGB,

    TD_MIXER_420_ARGB8888_GLOBAL_ALPHA_TRAVERSAL,
    TD_MIXER_422_RGB888_SEPARATE_ALPHA,
    TD_MIXER_420_ARGB4444_INTEGRATED_ALPHA,
    TD_MIXER_420_RGB565_ENDIANSWAP_BGR,
    TD_MIXER_420_ARGB1555_TWOBYTEENDIAN_RGB,
    TD_MIXER_420_MONO8_RANDOM_SIZE,
    TD_MIXER_420_STRIDE,
}TD_TEST_CASE_E;
/*
*wrap
*/
typedef struct _TD_WRAP_CLK_INFO_S
{
    unsigned int ch0rd;
    unsigned int ch1rd;
    unsigned int ch2rd;
    unsigned int ch3rd;
    unsigned int ch4rd;
    unsigned int ch5rd;
    unsigned int ch0wr;
    unsigned int ch1wr;
    unsigned int ch2wr;
    unsigned int axiwr;
    unsigned int axird;
} TD_WRAP_CLK_INFO_S;

typedef struct _TD_WRAP_INFO_S
{
  TD_WRAP_CLK_INFO_S clkInfo;  
}TD_WRAP_INFO_S;
/*
*core
*/
/*
* ROTATION
*/
typedef struct _TD_ROT_INFO_S
{
    unsigned int rotmode    ;
    unsigned int pixformat  ;
    unsigned int Inswap     ;
    unsigned int endianInEn ;
    unsigned int Outswap    ;
    unsigned int endianOutEn;
    unsigned int otmaxrd    ;
    unsigned int otmaxwr    ;
} TD_ROT_INFO_S;
 
typedef struct _TD_ROT_SIZE_INFO_S
{
    unsigned int hor;
    unsigned int ver;
} TD_ROT_SIZE_INFO_S;

typedef struct _TD_ROT_Y_BUF_INFO_S
{
	  unsigned int y_src_addr;
    unsigned int src_stride;
	  unsigned int y_des_addr;
    unsigned int des_stride;
} TD_ROT_Y_BUF_INFO_S;

typedef struct _TD_ROT_U_BUF_INFO_S
{
	  unsigned int u_src_addr;
    unsigned int src_stride;
	  unsigned int u_des_addr;
    unsigned int des_stride;
} TD_ROT_U_BUF_INFO_S;

typedef struct _TD_ROT_V_BUF_INFO_S
{
    unsigned int v_src_addr;
    unsigned int src_stride;      
    unsigned int v_des_addr;
    unsigned int des_stride;
} TD_ROT_V_BUF_INFO_S;

typedef struct _TD_ROT_ALL_INFO_S
{
    TD_ROT_INFO_S           rotInfo;
    TD_ROT_SIZE_INFO_S      imgSize;
    TD_ROT_Y_BUF_INFO_S     yBufInfo;
    TD_ROT_U_BUF_INFO_S     uBufInfo;
    TD_ROT_V_BUF_INFO_S     vBufInfo;
	  unsigned int      rot_framestart;
    unsigned int      timeout_val;
}TD_ROT_ALL_INFO_S;
/*
*Scaler/Mixer
*/
typedef struct _TD_SOFT_RST_INFO_S
{
    unsigned int mix ;
    unsigned int axi ;
    unsigned int apb ;
    unsigned int core;
} TD_SOFT_RST_INFO_S;

typedef struct _TD_DMA_SW_INFO_S
{
    unsigned int reqwr;
    unsigned int reqrd;
} TD_DMA_SW_INFO_S;

typedef struct _TD_BD_INFO_S
{
    unsigned int limiten  ;							   
    unsigned int outstand ;
} TD_BD_INFO_S;

typedef struct _TD_AREA_INFO_S
{
    unsigned int start;
    unsigned int stop ;
}TD_AREA_INFO_S;

typedef struct _TD_DISP_INFO_S
{
    unsigned int vcntbit0    ;
    unsigned int secndfoffset;
    unsigned int framesyncdly;
} TD_DISP_INFO_S;

typedef struct _TD_DISP_SIZE_INFO_S
{
    unsigned int hsize;
    unsigned int vsize;
} TD_DISP_SIZE_INFO_S;

typedef struct _TD_DISP_ALL_INFO_S
{
    unsigned int     framestart;
    TD_AREA_INFO_S   xZoneInfo;
    TD_AREA_INFO_S   yZoneInfo;
    TD_AREA_INFO_S   hSyncInfo;
    TD_AREA_INFO_S   vSyncInfo;
    TD_DISP_INFO_S   dispInfo;    
    TD_DISP_SIZE_INFO_S   dispSizeInfo; 
}TD_DISP_ALL_INFO_S;

typedef struct _TD_LAYER0_IMG_MODE_INFO_S
{
    unsigned int datmode ;
    unsigned int endiany ;
    unsigned int endianuv;
    unsigned int swapuv  ;
} TD_LAYER0_IMG_MODE_INFO_S;

typedef struct _TD_LAYER0_SIZE_INFO_S
{
    unsigned int hsize;
    unsigned int vsize;
} TD_LAYER0_SIZE_INFO_S;

typedef struct _TD_LAYER0_SCALE_INFO_S
{
    unsigned int pstep;
    unsigned int dstep;
    unsigned int pstep_st;
} TD_LAYER0_SCALE_INFO_S;

typedef struct _TD_LAYER0_BASE_MODE_INFO_S
{
    unsigned int mode;
    unsigned int base0mask;
    unsigned int base1mask;
    unsigned int addrflag ;
} TD_LAYER0_BASE_MODE_INFO_S;

typedef struct _TD_LAYER0_INFO_S
{
    unsigned int                 ctlen;
    unsigned int                 layer0en    ;
    unsigned int                 layer0enhs  ;
    unsigned int                 layer0Wenhs ; 
    unsigned int                 layer0Scalerblen;
    TD_BD_INFO_S                 layer0Line0BDInfo;
    TD_BD_INFO_S                 layer0Line1BDInfo;
    TD_BD_INFO_S                 layer0Line2BDInfo;
    TD_BD_INFO_S                 layer0Line3BDInfo;                                
    TD_AREA_INFO_S               layer0XInfo;        
    TD_AREA_INFO_S               layer0YInfo;
    TD_LAYER0_IMG_MODE_INFO_S    imgInDatModeInfo;
    unsigned int                 y_addr;
    unsigned int                 uv_addr;
    TD_LAYER0_SIZE_INFO_S        imgInSizeInfo;
    TD_LAYER0_SIZE_INFO_S        imgOutSizeInfo;
    TD_LAYER0_SIZE_INFO_S        imgInStrideInfo;
    TD_LAYER0_SIZE_INFO_S        imgInOffsetInfo;
    TD_LAYER0_SCALE_INFO_S       vScaleInfo;
    TD_LAYER0_SCALE_INFO_S       hScaleInfo;
    TD_LAYER0_BASE_MODE_INFO_S   baseModeInfo;
}TD_LAYER0_INFO_S;
/*
*LAYER4 (OSD0)
*/
typedef struct _TD_OSD0_INFO_S
{
    unsigned int osdtype  ;
    unsigned int alphatpye;
} TD_OSD0_INFO_S;

typedef struct _TD_OSD0_SIZE_INFO_S
{
    unsigned int width ;
    unsigned int height;
} TD_OSD0_SIZE_INFO_S;

typedef struct _TD_OSD0_DMA_INFO_S
{
    unsigned int dmarequestlen;
    unsigned int dmamap       ;
    unsigned int rgbrev       ;
} TD_OSD0_DMA_INFO_S;

typedef struct _TD_OSD0_ADDR_INFO_S
{
	  unsigned int vlu_addr;
    unsigned int osdstride;
	  unsigned int alp_addr;
    unsigned int alpstride;
} TD_OSD0_ADDR_INFO_S;

typedef struct _TD_OSD_RGB2YUV_INFO_S
{
    unsigned int osd0en;
    unsigned int osd1en;
    unsigned int osd2en;
	  unsigned int osdrgb2yuv_coeff[3][4]; 
} TD_OSD_RGB2YUV_INFO_S;

typedef struct _TD_LAYER4_OSD_INFO_S
{
    unsigned int       layer4en;
    unsigned int       layer4enhs;
    unsigned int       layer4Wenhs;
    TD_BD_INFO_S       layer4BDInfo;
    TD_AREA_INFO_S      layer4XInfo;
    TD_AREA_INFO_S      layer4YInfo;
    TD_OSD0_INFO_S      osd0Info;
    TD_OSD0_SIZE_INFO_S osd0SizeInfo;
    TD_OSD0_DMA_INFO_S  osd0DmaInfo;
    TD_OSD0_ADDR_INFO_S osd0AddrInfo;
    TD_OSD_RGB2YUV_INFO_S osdRgb2YuvInfo;
}TD_LAYER4_OSD_INFO_S;

typedef struct _TD_YUV2RGB_INFO_S
{
    unsigned int yuv2rgb_ctl_en;
	  unsigned int yuv2rgb_coeff[3][4];
}TD_YUV2RGB_INFO_S;
/*
*MIXER OUTPUT
*/
typedef struct _TD_DISP_BACK_GROUD_INFO_S
{
    unsigned int y;
    unsigned int u;
    unsigned int v;
} TD_DISP_BACK_GROUD_INFO_S;

typedef struct _TD_DISP_MIX_INFO_S
{
    unsigned int layer0glbalp;
    unsigned int layer4glbalp;
    unsigned int layer0sel;        
    unsigned int layer1sel;   //osd0     
    TD_DISP_BACK_GROUD_INFO_S  backGroudInfo;
}TD_DISP_MIX_INFO_S;

/*
*INTERRUPT
*/
typedef struct _TD_DISP_IRQ_INFO_S
{
    unsigned int underrundcnt;
    unsigned int en;
} TD_DISP_IRQ_INFO_S;

typedef struct _TD_DISP_IRQ_ALL_INFO_S
{
    TD_DISP_IRQ_INFO_S irq0Info;
    TD_DISP_IRQ_INFO_S irq1Info;
    TD_DISP_IRQ_INFO_S irq2Info;
} TD_DISP_IRQ_ALL_INFO_S;
/*
*DMA WRITE BACK
*/
typedef struct _TD_WB_Y_BUF_INFO_S
{
    unsigned int y_en ;
    unsigned int addr0;
	  unsigned int addr1;
	  unsigned int hstride;
}TD_WB_Y_BUF_INFO_S;

typedef struct _TD_WB_UV_BUF_INFO_S
{
    unsigned int uv_en ;
    unsigned int addr0;
	  unsigned int addr1;
	  unsigned int hstride;
}TD_WB_UV_BUF_INFO_S;

typedef struct _TD_WB_PIXEL_FORMAT_OUT_INFO_S
{
    unsigned int formatsel    ;
    unsigned int inputformat  ;
    unsigned int outputformat ;
    unsigned int pixelorder422;
    unsigned int rgbpixelwidth;
} TD_WB_PIXEL_FORMAT_OUT_INFO_S;

typedef struct _TD_WB_DMA_MODE_INFO_S
{
    unsigned int otnum         ;
    unsigned int blen          ;
    unsigned int continuousmode;
    unsigned int swap          ;
    unsigned int errdetecten   ;
} TD_WB_DMA_MODE_INFO_S;

typedef struct _TD_WB_INFO_CLR_INFO_S
{
    unsigned int frmcntclear ;
    unsigned int fifoerrclear;
    unsigned int maxbw       ;
    unsigned int totalbw     ;
} TD_WB_INFO_CLR_INFO_S;

typedef struct _TD_WB_CH_INFO_S
{ 
		unsigned int err_unit;
		unsigned int err_threshold;
		unsigned int request;
		TD_WB_DMA_MODE_INFO_S	dmaModeInfo;
		TD_WB_INFO_CLR_INFO_S	infoClrInfo;
}TD_WB_CH_INFO_S;
		
typedef struct _TD_WB_INFO_S
{
		unsigned int              wb_en;
		unsigned int              input_mode;
		unsigned int              buffersize;
		unsigned int              v_size_out;
		unsigned int              h_size_out;
		TD_WB_Y_BUF_INFO_S        yBufInfo;
		TD_WB_UV_BUF_INFO_S       uvBufInfo;
		TD_WB_PIXEL_FORMAT_OUT_INFO_S  PixelFormatOutInfo;
		TD_WB_CH_INFO_S            ch0Info;
		TD_WB_CH_INFO_S            ch1Info;
}TD_WB_INFO_S;

typedef struct _TD_CORE_INFO_S
{
    TD_ROT_ALL_INFO_S          rotAllInfo;
    TD_SOFT_RST_INFO_S         rstInfo;
    TD_DMA_SW_INFO_S           swInfo;
    TD_DISP_INFO_S             dispInfo;
    TD_LAYER0_INFO_S           layer0Info;
    TD_LAYER4_OSD_INFO_S       layer4OsdInfo;
    TD_YUV2RGB_INFO_S          yuv2rgbInfo;
    TD_DISP_MIX_INFO_S         dispMixInfo;
    TD_DISP_IRQ_ALL_INFO_S     dispIrqAllInfo;
    TD_WB_INFO_S               wbInfo;
}TD_CORE_INFO_S;
/*
*
*/
typedef struct _TD_INFO_S
{
    TD_WRAP_INFO_S tdWrapInfo;
    TD_CORE_INFO_S tdCoreInfo;
}TD_INFO_S;

int TD_DRV_Init(void);
int TD_TEST_SetWrap(TD_WRAP_INFO_S *wrapInfo);
int TD_TEST_SetCore(TD_CORE_INFO_S *tdCoreInfo);
//
void TD_TEST_Mixer(unsigned char testCase);
int TD_config(TD_INFO_S *tdInfo);

#endif /*_TD_DEF_H_*/
