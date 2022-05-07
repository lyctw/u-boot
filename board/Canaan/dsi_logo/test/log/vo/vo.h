
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

#ifndef _VO_DEF_H_
#define _VO_DEF_H_

#include <video/isp_com.h>
#include <video/video_subsystem_addr.h>
#include <video/vo/core/vo_core_drv.h>
#include <video/vo/table/vo_table_drv.h>
#include <video/vo/remap/vo_remap_drv.h>

//
#define VIDEO_DISP_ZONE_X_START   0xC6
#define VIDEO_DISP_ZONE_X_STOP    0x846
#define VIDEO_DISP_ZONE_Y_START   0x2A
#define VIDEO_DISP_ZONE_Y_STOP    0x462
//layer0
#define VIDEO_LAYER0_H_POSITION   198
#define VIDEO_LAYER0_V_POSITION   42
#define VIDEO_LAYER0_H_IN_SIZE   1920//1280
#define VIDEO_LAYER0_V_IN_SIZE   1080//720
#define VIDEO_LAYER0_H_OUT_SIZE   1920//1280
#define VIDEO_LAYER0_V_OUT_SIZE   1080//720
#define VIDEO_LAYER0_RD_STRIDE   2048
#define VIDEO_LAYER0_RD_1920_STRIDE   1920
//layer1
#define VIDEO_LAYER1_H_POSITION   (198+1400)
#define VIDEO_LAYER1_V_POSITION   100
#define VIDEO_LAYER1_H_OUT_SIZE   320
#define VIDEO_LAYER1_V_OUT_SIZE   240
#define VIDEO_LAYER1_RD_STRIDE   2048
//layer2
#define VIDEO_LAYER2_H_POSITION   (198+1400)
#define VIDEO_LAYER2_V_POSITION   500
#define VIDEO_LAYER2_H_OUT_SIZE   320
#define VIDEO_LAYER2_V_OUT_SIZE   240
#define VIDEO_LAYER2_RD_STRIDE   2048
//layer3
#define VIDEO_LAYER3_H_POSITION   (198+1400)
#define VIDEO_LAYER3_V_POSITION   800
#define VIDEO_LAYER3_H_OUT_SIZE   320
#define VIDEO_LAYER3_V_OUT_SIZE   240
#define VIDEO_LAYER3_RD_STRIDE   2048

#define OSD_LAYER0_H_POSITION    (800)
#define OSD_LAYER0_V_POSITION    400
#define OSD_LAYER0_H_SIZE        256
#define OSD_LAYER0_V_SIZE        200
#define OSD_LAYER0_RD_STRIDE     2048
#define OSD_LAYER1_H_POSITION    (298+300)
#define OSD_LAYER1_V_POSITION    400
#define OSD_LAYER1_H_SIZE        256
#define OSD_LAYER1_V_SIZE        200
#define OSD_LAYER1_RD_STRIDE     2048
#define OSD_LAYER2_H_POSITION    (298+700)
#define OSD_LAYER2_V_POSITION    400
#define OSD_LAYER2_H_SIZE        256
#define OSD_LAYER2_V_SIZE        200
#define OSD_LAYER2_RD_STRIDE     2048
       
#define LAYER0_Y_BASEAddr0       0x20000000 //  # y base: 0x800000
#define LAYER0_Y_BASEAddr1       0x20000000 //  # uv base: 0x900000
#define LAYER0_UV_BASEaddr0      0x20280000 //  # y base: 0x800000
#define LAYER0_UV_BASEaddr1      0x20280000 //  # uv base: 0x900000

#define LAYER1_Y_BASEAddr0       0x20600000 //  # y base: 0x800000
#define LAYER1_Y_BASEAddr1       0x20600000 // # uv base: 0x900000
#define LAYER1_UV_BASEaddr0      0x20880000 //  # y base: 0x800000
#define LAYER1_UV_BASEaddr1      0x20880000 // # uv base: 0x900000
          
#define LAYER2_Y_BASEAddr0       0x20A00000 //  # y base: 0x800000
#define LAYER2_Y_BASEAddr1       0x20A00000 // # uv base: 0x900000
#define LAYER2_UV_BASEaddr0      0x20C80000 //  # y base: 0x800000
#define LAYER2_UV_BASEaddr1      0x20C80000 // # uv base: 0x900000
     
#define LAYER3_Y_BASEAddr0       0x20A00000 //  # y base: 0x800000
#define LAYER3_Y_BASEAddr1       0x20A00000 // # uv base: 0x900000
#define LAYER3_UV_BASEaddr0      0x20C80000 //  # y base: 0x800000
#define LAYER3_UV_BASEaddr1      0x20C80000 // # uv base: 0x900000
     
#define OSD0_VLU_ADDR0           0x20E00000//  # y base: 0x800000  --argb mode --32bit
#define OSD0_VLU_ADDR1           0x20E00000// # uv base: 0x900000
#define OSD0_ALP_ADDR0           0x20E00000//  # y base: 0x800000
#define OSD0_ALP_ADDR1           0x20E00000// # uv base: 0x900000
                  
#define OSD1_VLU_ADDR0           0x20E00000 //  # y base: 0x800000
#define OSD1_VLU_ADDR1           0x20E00000 // # uv base: 0x900000
#define OSD1_ALP_ADDR0           0x20E00000 //  # y base: 0x800000
#define OSD1_ALP_ADDR1           0x20E00000 // # uv base: 0x900000

#define OSD2_VLU_ADDR0           0x20E00000 //  # y base: 0x800000
#define OSD2_VLU_ADDR1           0x20E00000 // # uv base: 0x900000
#define OSD2_ALP_ADDR0           0x20E00000 //  # y base: 0x800000
#define OSD2_ALP_ADDR1           0x20E00000 // # uv base: 0x900000

#define OSD0_LOAD_VLU_ADDR0           0x22000000 //  # y base: 0x800000
#define OSD0_LOAD_VLU_ADDR1           0x22000000 // # uv base: 0x900000
#define OSD0_LOAD_ALP_ADDR0           0x23000000 //  # y base: 0x800000
#define OSD0_LOAD_ALP_ADDR1           0x23000000 // # uv base: 0x900000

#define OSD1_LOAD_VLU_ADDR0           0x22000000 //  # y base: 0x800000
#define OSD1_LOAD_VLU_ADDR1           0x22000000 // # uv base: 0x900000
#define OSD1_LOAD_ALP_ADDR0           0x23000000 //  # y base: 0x800000
#define OSD1_LOAD_ALP_ADDR1           0x23000000 // # uv base: 0x900000

#define OSD2_LOAD_VLU_ADDR0           0x22000000 //  # y base: 0x800000
#define OSD2_LOAD_VLU_ADDR1           0x22000000 // # uv base: 0x900000
#define OSD2_LOAD_ALP_ADDR0           0x23000000 //  # y base: 0x800000
#define OSD2_LOAD_ALP_ADDR1           0x23000000 // # uv base: 0x900000

#define DUMP_Y_1080P_ADDR0           0x24000000 //  # y base: 0x800000
#define DUMP_UV_1080P_ADDR0           0x241FA400 // # uv base: 0x900000
#define DUMP_Y_1080P_ADDR1           0x24000000 //  # y base: 0x800000
#define DUMP_UV_1080P_ADDR1           0x241FA400 // # uv base: 0x900000

#define DUMP_Y_1080P_ADDR1_PP           0x24000000 //  # y base: 0x800000
#define DUMP_UV_1080P_ADDR1_PP           0x241FA400 // # uv base: 0x900000

#define DUMP_Y_320352_ADDR0           0x28500000 //  # y base: 0x800000
#define DUMP_UV_320352_ADDR0          0x28580000 // # uv base: 0x900000
#define DUMP_Y_320352_ADDR1           0x28500000 //  # y base: 0x800000
#define DUMP_UV_320352_ADDR1          0x28580000 // # uv base: 0x900000

#define VIDEO_LOAD_Y_SRAM_ADDR0         0x00090000
#define VIDEO_LOAD_UV_SRAM_ADDR0        0x000AB800
#define VIDEO_LOAD_Y_SRAM_ADDR1         0x00090000
#define VIDEO_LOAD_UV_SRAM_ADDR1        0x000AB800
#define OSD_LOAD_VLU_SRAM_ADDR0         0x000C0000
#define OSD_LOAD_VLU_SRAM_ADDR1         0x000C0000

#define DUMP_Y_MFBD_DATA_ADDR0             0x24000000 
#define DUMP_Y_MFBD_HEAD_ADDR0             0x25000000 
#define DUMP_Y_MFBD_DATA_STRIDE0             0x800 
#define DUMP_Y_MFBD_HEAD_STRIDE0             0x800 

#define DUMP_Y_MFBD_DATA_ADDR1             0x26000000 
#define DUMP_Y_MFBD_HEAD_ADDR1             0x27000000 
#define DUMP_Y_MFBD_DATA_STRIDE1             0x800 
#define DUMP_Y_MFBD_HEAD_STRIDE1             0x800 

#define DUMP_UV_MFBD_DATA_ADDR0             0x24280000 
#define DUMP_UV_MFBD_HEAD_ADDR0             0x25280000 
#define DUMP_UV_MFBD_DATA_STRIDE0             0x800 
#define DUMP_UV_MFBD_HEAD_STRIDE0             0x800 
#define DUMP_UV_MFBD_DATA_ADDR1             0x26280000 
#define DUMP_UV_MFBD_HEAD_ADDR1             0x27280000 
#define DUMP_UV_MFBD_DATA_STRIDE1             0x800 
#define DUMP_UV_MFBD_HEAD_STRIDE1             0x800 
//
typedef enum _VO_VIDEOLAYER_YUV_MODE_E
{
    VO_VIDEO_LAYER_YUV_MODE_420              = 0x08,
    VO_VIDEO_LAYER_YUV_MODE_422              = 0x09,
} VO_VIDEOLAYER_YUV_MODE_E;

typedef enum _VO_VIDEOLAYER_Y_ENDIAN_E
{
    VO_VIDEO_LAYER_Y_ENDIAN_MODE0              = 0x0,//Y4 Y5 Y6 Y7 Y0 Y1 Y2 Y3
    VO_VIDEO_LAYER_Y_ENDIAN_MODE1              = 0x1,//Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0
    VO_VIDEO_LAYER_Y_ENDIAN_MODE2              = 0x2,//Y0 Y1 Y2 Y3 Y4 Y5 Y6 Y7
    VO_VIDEO_LAYER_Y_ENDIAN_MODE3              = 0x3,//Y3 Y2 Y1 Y0 Y7 Y6 Y5 Y4
} VO_VIDEOLAYER_Y_ENDIAN_E;

typedef enum _VO_VIDEOLAYER_UV_ENDIAN_E
{
    VO_VIDEO_LAYER_UV_ENDIAN_MODE0              = 0x0,//U2 V2 U3 V3 U0 V0 U1 V1
    VO_VIDEO_LAYER_UV_ENDIAN_MODE1              = 0x1,//V2 U2 V3 U3 V0 U0 V1 U1
    VO_VIDEO_LAYER_UV_ENDIAN_MODE2              = 0x2,//U3 V3 U2 V2 U1 V1 U0 V0
    VO_VIDEO_LAYER_UV_ENDIAN_MODE3              = 0x3,//V3 U3 V2 U2 V1 U1 V0 U0  
    VO_VIDEO_LAYER_UV_ENDIAN_MODE4              = 0x4,//U0 V0 U1 V1 U2 V2 U3 V3  
    VO_VIDEO_LAYER_UV_ENDIAN_MODE5              = 0x5,//V0 U0 V1 U1 V2 U2 V3 U3 
    VO_VIDEO_LAYER_UV_ENDIAN_MODE6              = 0x6,//U1 V1 U0 V0 U3 V3 U2 V2
    VO_VIDEO_LAYER_UV_ENDIAN_MODE7              = 0x7//V1 U1 V0 U0 V3 U3 V2 U2 
} VO_VIDEOLAYER_UV_ENDIAN_E;

typedef enum _VO_SYSTEM_MODE_E
{
    //! Unknown system mode.
    VO_UNKNOWN_SYSTEM_MODE = 0,
    //! System mode is 1920x1080p at 25 Hz.
    VO_SYSTEM_MODE_1920x1080x25P,
    //! System mode is 1920x1080p at 30 Hz.
    VO_SYSTEM_MODE_1920x1080x30P,
    //! System mode is 1920x1080p at 60 Hz.
    VO_SYSTEM_MODE_1920x1080x60P,
    //! System mode is 1280x720p at 25 Hz.
    VO_SYSTEM_MODE_1280x720x25P,
    //! System mode is 1280x720p at 30 Hz.
    VO_SYSTEM_MODE_1280x720x30P,
    //! System mode is 1280x720p at 50 Hz.
    VO_SYSTEM_MODE_1280x720x50P,
    //! System mode is 1280x720p at 60 Hz.
    VO_SYSTEM_MODE_1280x720x60P,
    //! System mode is 1080x1920 at 30 Hz.
    VO_SYSTEM_MODE_1080x1920x30P,
    
}VO_SYSTEM_MODE_E;

typedef enum _VO_MIXER_ORDER_E
{
    VO_MIXER_VIDEO_LAYER_0              = 0,
    VO_MIXER_VIDEO_LAYER_1              = 1,
    VO_MIXER_VIDEO_LAYER_2              = 2,
    VO_MIXER_VIDEO_LAYER_3              = 3,
    VO_MIXER_OSD_LAYER_0                = 4,
    VO_MIXER_OSD_LAYER_1                = 5,
    VO_MIXER_OSD_LAYER_2                = 6,
} VO_MIXER_ORDER_E;

/********************************************************************************
*define data_struct
*********************************************************************************/

//disp
typedef struct _VO_DISP_INFO_S
{
    unsigned int dispEnable;
    unsigned int xZoneCtl_start;
    unsigned int xZoneCtl_stop;
    unsigned int yZoneCtl_start;
    unsigned int yZoneCtl_stop;
    unsigned int dispHsyncCtl_start;
    unsigned int dispHsyncCtl_stop;
    unsigned int dispHsync1Ctl_start;
    unsigned int dispHsync1Ctl_stop;
    unsigned int dispVsync1Ctl_start;
    unsigned int dispVsync1Ctl_stop;
    unsigned int dispHsync2Ctl_start;
    unsigned int dispHsync2Ctl_stop;
    unsigned int dispVsync2Ctl_start;
    unsigned int dispVsync2Ctl_stop; 
    unsigned int vcntbit0    ;
    unsigned int secndfoffset;
    unsigned int framesyncdly;
    unsigned int hsize;
    unsigned int vsize;    
}VO_DISP_INFO_S;
//LAYER0
typedef struct _VO_LAYER0_DAT_MODE_INFO_S
{
    unsigned int datmode ;
    unsigned int endiany ;
    unsigned int endianuv;
    unsigned int swi;
}VO_LAYER0_DAT_MODE_INFO_S;
//
typedef struct _VO_LAYER_AREA_INFO_S
{
    unsigned int xCtl_start;
    unsigned int xCtl_stop;
    unsigned int yCtl_start;
    unsigned int yCtl_stop;
}VO_LAYER_AREA_INFO_S;
//
typedef struct _VO_YUV_BUF_INFO_S
{
    unsigned int yAddr0;
    unsigned int yAddr1;
    unsigned int uvAddr0;
    unsigned int uvAddr1;
    unsigned int hsize_stride;
    unsigned int vsize_stride;
}VO_YUV_BUF_INFO_S;
//
typedef struct _VO_LAYER0_SCALE_INFO_S
{
    unsigned int v_pstep;
    unsigned int v_dstep;
    unsigned int v_pstep_st;
    unsigned int h_pstep;
    unsigned int h_dstep;
    unsigned int h_pstep_st;
}VO_LAYER0_SCALE_INFO_S;
//
typedef struct _VO_LAYER0_SIZE_INFO_S
{
    unsigned int offset_hsize;
    unsigned int offset_vsize;
    unsigned int in_hsize;
    unsigned int in_vsize;
    unsigned int out_hsize;
    unsigned int out_vsize;
}VO_LAYER0_SIZE_INFO_S;
//
typedef struct _VO_BASE_MODE_INFO_S
{
    unsigned int mode;
    unsigned int base0mask;
    unsigned int base1mask;
    unsigned int addrflag ;
} VO_BASE_MODE_INFO_S;
//
typedef struct _VO_LAYER0_MFBD_INFO_S
{
	unsigned int mfbd_en;
	unsigned int y_addr0;
	unsigned int y_stride0;		
	unsigned int y_addr1;
	unsigned int y_stride1;
	unsigned int y_head_addr0;
	unsigned int y_head_stride0;		
	unsigned int y_head_addr1;
	unsigned int y_head_stride1;
	unsigned int uv_addr0;
    unsigned int uv_stride0;
	unsigned int uv_addr1;
	unsigned int uv_stride1; 
	unsigned int uv_head_addr0;
    unsigned int uv_head_stride0;
	unsigned int uv_head_addr1;
	unsigned int uv_head_stride1;
}VO_LAYER0_MFBD_INFO_S;
//
typedef struct _VO_LAYER0_INFO_S
{
    unsigned int  layer0DispEn;
    unsigned int  layer0En; 
    unsigned int  scalerBlen;
    //
    VO_LAYER0_DAT_MODE_INFO_S datModeInfo;
    //
    VO_LAYER_AREA_INFO_S   areaInfo;
    //
    VO_YUV_BUF_INFO_S       bufInfo;
    //
    VO_LAYER0_SCALE_INFO_S  scaleInfo;
    //
    VO_LAYER0_SIZE_INFO_S   sizeInfo;
    //
    VO_BASE_MODE_INFO_S     baseModeInfo;
    //
    VO_LAYER0_MFBD_INFO_S   mfbdInfo;
}VO_LAYER0_INFO_S;
//LAYER1
//
typedef struct _VO_LAYER_INFO_S
{
    unsigned int enable   ;
    unsigned int yuv422en ;
    unsigned int yuv420en ;
    unsigned int endiany  ;        
    unsigned int endianuv ;        
    unsigned int uvswap   ; 
} VO_LAYER_INFO_S;
//
typedef struct _VO_LAYER_SIZE_INFO_S
{
    unsigned int offset_hsize;
    unsigned int offset_vsize;
    unsigned int in_hsize;
    unsigned int in_vsize;
}VO_LAYER_SIZE_INFO_S;
//
typedef struct _VO_IMG_IN_BLENTH_INFO_S
{
    unsigned int blen   ;        
    unsigned int voffset;
} VO_IMG_IN_BLENTH_INFO_S;
//
typedef struct _VO_LAYER1_INFO_S
{
    unsigned int layer1DispEn;
    //
    VO_LAYER_INFO_S layerInfo;
    //
    VO_LAYER_AREA_INFO_S   areaInfo;
    //
    VO_YUV_BUF_INFO_S       bufInfo;
    //
    VO_LAYER_SIZE_INFO_S    layer1SizeInfo; 
    //
    VO_IMG_IN_BLENTH_INFO_S imgInBlenthInfo; 
    //
    VO_BASE_MODE_INFO_S     baseModeInfo;      
}VO_LAYER1_INFO_S;
//LAYER2
typedef struct _VO_LAYER2_INFO_S
{
    unsigned int layer2DispEn;
    //
    VO_LAYER_INFO_S layerInfo;
    //
    VO_LAYER_AREA_INFO_S   areaInfo;
    //
    VO_YUV_BUF_INFO_S       bufInfo;
    //
    VO_LAYER_SIZE_INFO_S    layer2SizeInfo; 
    //
    VO_IMG_IN_BLENTH_INFO_S imgInBlenthInfo; 
    //
    VO_BASE_MODE_INFO_S     baseModeInfo; 
}VO_LAYER2_INFO_S;
//LAYER3
typedef struct _VO_LAYER3_INFO_S
{
    unsigned int layer3DispEn;
    //
    VO_LAYER_INFO_S layerInfo;
    //
    VO_LAYER_AREA_INFO_S   areaInfo;
    //
    VO_YUV_BUF_INFO_S       bufInfo;
    //
    VO_LAYER_SIZE_INFO_S    layer3SizeInfo; 
    //
    VO_IMG_IN_BLENTH_INFO_S imgInBlenthInfo; 
    //
    VO_BASE_MODE_INFO_S     baseModeInfo; 
}VO_LAYER3_INFO_S;
//osd0
typedef struct _VO_OSD_SIZE_INFO_S
{
    unsigned int width;
    unsigned int height; 
} VO_OSD_SIZE_INFO_S;
//
typedef struct _VO_OSD_BUF_INFO_S
{
    unsigned int    alp_addr0;
    unsigned int    alp_addr1;
    unsigned int    alpstride;        
    unsigned int    vlu_addr0;
    unsigned int    vlu_addr1;
    unsigned int    osdstride;
}VO_OSD_BUF_INFO_S;
//
typedef struct _VO_OSD_DMA_INFO_S
{
    unsigned int dmarequestlen;
    unsigned int dmamap       ;
    unsigned int rgbrev       ;     
} VO_OSD_DMA_INFO_S;
//
typedef struct _VO_OSD0_INFO_S
{
    unsigned int osdLayer4DispEn;
    unsigned int osdrgb2yuvEn;
    unsigned int osdtype  ;
    unsigned int alphatpye;
    VO_LAYER_AREA_INFO_S   osd0AreaInfo;
    VO_OSD_SIZE_INFO_S     osd0SizeInfo;
    VO_OSD_BUF_INFO_S      osd0BufInfo;
    VO_BASE_MODE_INFO_S    osd0BaseModeInfo;
    VO_OSD_DMA_INFO_S      osd0DmaInfo; 
}VO_OSD0_INFO_S;
//osd1
typedef struct _VO_OSD1_INFO_S
{
    unsigned int osdLayer5DispEn;
    unsigned int osdrgb2yuvEn;
    unsigned int osdtype  ;
    unsigned int alphatpye;
    VO_LAYER_AREA_INFO_S   osd1AreaInfo;
    VO_OSD_SIZE_INFO_S     osd1SizeInfo;
    VO_OSD_BUF_INFO_S      osd1BufInfo;
    VO_BASE_MODE_INFO_S    osd1BaseModeInfo;
    VO_OSD_DMA_INFO_S      osd1DmaInfo;
}VO_OSD1_INFO_S;
//osd2
typedef struct _VO_OSD2_INFO_S
{
    unsigned int osdLayer6DispEn;
    unsigned int osdrgb2yuvEn;
    unsigned int osdtype  ;
    unsigned int alphatpye;
    VO_LAYER_AREA_INFO_S   osd2AreaInfo;
    VO_OSD_SIZE_INFO_S     osd2SizeInfo;
    VO_OSD_BUF_INFO_S      osd2BufInfo;
    VO_BASE_MODE_INFO_S    osd2BaseModeInfo;
    VO_OSD_DMA_INFO_S      osd2DmaInfo;
}VO_OSD2_INFO_S;
//OSD RGB2YUV
typedef struct _VO_OSD_RGB2YUV_INFO_S
{
    unsigned int osdrgb2yuv_coeff[3][4];
}VO_OSD_RGB2YUV_INFO_S;
//YUV2RGB
typedef struct _VO_YUV2RGB_INFO_S
{
    unsigned int yuv2rgb_ctl_en;
	unsigned int yuv2rgb_coeff[3][4];
}VO_YUV2RGB_INFO_S;
//disp mix
//
typedef struct _VO_MIX_INFO_S
{
    unsigned int glben;
    unsigned int glbalp;
    unsigned int sel;
}VO_MIX_INFO_S;
//
typedef struct _VO_DISP_BACK_GROUD_INFO_S
{
    unsigned int y;
    unsigned int u;
    unsigned int v;
} VO_DISP_BACK_GROUD_INFO_S;
//
typedef struct _VO_DISP_MIX_INFO_S
{
    VO_MIX_INFO_S layerMixInfo[7];
    VO_DISP_BACK_GROUD_INFO_S dispBackGroudInfo;
}VO_DISP_MIX_INFO_S;
//disp irq
//
typedef struct _VO_DISP_IRQ_INFO_S
{
    unsigned int underrundcnt0;
    unsigned int en0;
    unsigned int underrundcnt1;
    unsigned int en1;
    unsigned int underrundcnt2;
    unsigned int en2;
}VO_DISP_IRQ_INFO_S;
//wb info
typedef struct _VO_WB_Y_INFO_S
{
    unsigned int y_en ;
    unsigned int addr0;
	unsigned int addr1;
	unsigned int hstride;
}VO_WB_Y_INFO_S;
//
typedef struct _VO_WB_UV_INFO_S
{
    unsigned int uv_en ;
    unsigned int addr0;
	unsigned int addr1;
	unsigned int hstride;
}VO_WB_UV_INFO_S;
//
typedef struct _VO_WB_BUF_INFO_S
{
    VO_WB_Y_INFO_S wbYInfo;
    VO_WB_UV_INFO_S wbUVInfo;
}VO_WB_BUF_INFO_S;
//
typedef struct _VO_WB_PIXEL_FORMAT_OUT_INFO_S
{
    unsigned int formatsel    ;
    unsigned int inputformat  ;
    unsigned int outputformat ;
    unsigned int pixelorder422;
    unsigned int rgbpixelwidth;
} VO_WB_PIXEL_FORMAT_OUT_INFO_S;
//
typedef struct _VO_WB_DMA_INFO_S
{
    unsigned int otnum         ;
    unsigned int blen          ;
    unsigned int continuousmode;
    unsigned int swap          ;
    unsigned int errdetecten   ;
} VO_WB_DMA_INFO_S;
//
typedef struct _VO_WB_INFO_CLR_INFO_S
{
    unsigned int frmcntclear ;
    unsigned int fifoerrclear;
    unsigned int maxbw       ;
    unsigned int totalbw     ;
} VO_WB_INFO_CLR_INFO_S;
//
typedef struct _VO_WB_CH_INFO_S
{ 
	unsigned int err_unit;
	unsigned int err_threshold;
	unsigned int request;
	VO_WB_DMA_INFO_S	wbDmaInfo;
	VO_WB_INFO_CLR_INFO_S	wbInfoClr;
}VO_WB_CH_INFO_S;
//
typedef struct _VO_WB_INFO_S
{
    unsigned int   wb_en;
    unsigned int   inchmode;
	unsigned int   buffersize;
	unsigned int   v_size_out;
	unsigned int   h_size_out;
    VO_WB_BUF_INFO_S wbBufInfo;
    VO_WB_PIXEL_FORMAT_OUT_INFO_S wbPixelFormatOutInfo;
    VO_WB_CH_INFO_S ch0Info;
    VO_WB_CH_INFO_S ch1Info;
}VO_WB_INFO_S;
//
typedef struct _VO_CORE_INFO_S
{
    VO_DISP_INFO_S   	dispInfo;
    VO_LAYER0_INFO_S 	layer0Info;
    VO_LAYER1_INFO_S 	layer1Info;
    VO_LAYER2_INFO_S 	layer2Info;
    VO_LAYER3_INFO_S 	layer3Info;
    VO_OSD0_INFO_S   	osd0Info;
    VO_OSD1_INFO_S   	osd1Info;
    VO_OSD2_INFO_S   	osd2Info;
    VO_OSD_RGB2YUV_INFO_S osdRgb2YuvInfo;
    VO_YUV2RGB_INFO_S   yuv2rgbInfo;  
    VO_DISP_MIX_INFO_S  dispMixCtlInfo;
    unsigned int        ditherctlen;
    unsigned int        clutctlen;
    VO_DISP_IRQ_INFO_S  dispIrqInfo;
    VO_WB_INFO_S        wbInfo;
}VO_CORE_INFO_S;
/*
*remap
*/
typedef struct _VO_REMAP_CTRL_INFO_S
{
    unsigned int line_draw_en;
    unsigned int v_line_r_en      ;
    unsigned int v_line_l_en      ;
    unsigned int h_line_b_en      ;
    unsigned int v_line_u_en      ;
    unsigned int line_start_pos_x ;
    unsigned int line_end_pos_x	  ;
    unsigned int line_start_pos_y ;
    unsigned int line_end_pos_y	  ;		
    unsigned int line_width_l;
    unsigned int line_width_h;		
    unsigned int fill_value_cr;
    unsigned int fill_value_cb;
    unsigned int fill_value_y ;
    unsigned int fill_alpha ; 
} VO_REMAP_CTRL_INFO_S;

typedef struct _VO_REMAP_CMD_INFO_S
{
    unsigned int image_active_h;
    unsigned int fill_en_rgb;
    unsigned int image_active_v;
    unsigned int fill_fill_en_yuv;
} VO_REMAP_CMD_INFO_S;

typedef struct _VO_REMAP_INFO_S
{
    VO_REMAP_CMD_INFO_S  CmdInfo;
    VO_REMAP_CTRL_INFO_S CtlInfo[VO_LINE_DRAW_AREA_MAX]; 
}VO_REMAP_INFO_S;

typedef struct _VO_INFO_S
{
    VO_CORE_INFO_S  voCoreInfo;
    VO_REMAP_INFO_S voRemapInfo;
}VO_INFO_S;
//
typedef struct _VO_DISP_CTL_INFO_S
{
    unsigned int Disp_en;
    unsigned int SyncMode;
    IMAGE_SIZE  total_size;
    IMAGE_SIZE  disp_start;
    IMAGE_SIZE  disp_stop;
}VO_DISP_CTL_INFO_S;

typedef struct _VO_LAYER_CTL_INFO_S
{
    unsigned int layer_en;
    unsigned int layer0_mfbd_en;
    unsigned int layerMix_en;
    unsigned int layerMix_glbalp;
    VO_VIDEOLAYER_Y_ENDIAN_E endiany;
    VO_VIDEOLAYER_Y_ENDIAN_E endianuv;
    VO_VIDEOLAYER_YUV_MODE_E ImgInDataMode;
    BOOL uvswap;
    IMAGE_SIZE  active_size;
    IMAGE_SIZE  out_size;
    IMAGE_SIZE  ctl_offset;
    IMAGE_SIZE  size_offset;
    VO_YUV_BUF_INFO_S bufInfo;
}VO_LAYER_CTL_INFO_S;

typedef struct _VO_LAYER_OSD_CTL_INFO_S
{
    unsigned int layer_en;
    unsigned int osdrgb2yuvEn;
    unsigned int layerMix_en;
    unsigned int layerMix_glbalp;
    VO_VIDEOLAYER_Y_ENDIAN_E endiany;
    VO_VIDEOLAYER_Y_ENDIAN_E endianuv;
    OSD_Layer_Type_E osdtype;
    OSD_Alpha_Type_E alphatpye;
    VO_VIDEOLAYER_YUV_MODE_E ImgInDataMode;
    IMAGE_SIZE  active_size;
    IMAGE_SIZE  ctl_offset;
    VO_OSD_BUF_INFO_S   osdBufInfo;
    VO_OSD_DMA_INFO_S   osdDmaInfo;
}VO_LAYER_OSD_CTL_INFO_S;

typedef struct _VO_CTL_S
{
    unsigned int     ditherctlen;
    unsigned int     clutctlen;
    unsigned int     yuv2rgb_ctl_en;
	VO_DISP_CTL_INFO_S    dispCtl;
	VO_LAYER_CTL_INFO_S   layer0Ctl;
	VO_LAYER_CTL_INFO_S   layer1Ctl;
	VO_LAYER_CTL_INFO_S   layer2Ctl;
	VO_LAYER_CTL_INFO_S   layer3Ctl;
	VO_LAYER_OSD_CTL_INFO_S   layer4osd0Ctl;
	VO_LAYER_OSD_CTL_INFO_S   layer5osd1Ctl;
	VO_LAYER_OSD_CTL_INFO_S   layer6osd2Ctl;
    VO_DISP_BACK_GROUD_INFO_S dispBackGroudInfo;
}VO_CTL_S;
//
//typedef int (*REMAP_FUNC) (VO_REMAP_CTRL_FILL_INFO_S *fillInfo);
int VO_DRV_Init(void);
int VO_TEST_Init(void);
int VO_TEST_Start(void);
int VO_TEST_SetWrap(void);
int VO_TEST_SetCore(VO_CORE_INFO_S *voCoreInfo);
//int VO_TEST_SetRemap(VO_REMAP_INFO_S *voRemapInfo);
int VO_TEST_SetRemap(unsigned int draw_num,VO_REMAP_INFO_S *voRemapInfo);
//
int VO_TEST_VideoOut(VO_TEST_CASE_E voTestCase);
#endif /*_VO_DEF_H_*/
