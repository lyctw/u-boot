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
#include <stdio.h>
#include <stdlib.h>

#include <video/isp_com.h>
#include "vo/vo_calc.h"
#include "vo/vo.h"
#include "hw_dev/inc/dev_hw.h"

#include "hw_dev/inc/display_hardware_init.h"
#include "hw_dev/inc/lt9611.h"

#include "interrupt.h"
#include "env.h"

/******************************************************************************
 *  CORE com*
******************************************************************************/
/*
*disp
*/
static int VO_TEST_SetFrameBit(VO_DISP_CTL_INFO_S *dispCtl,VO_DISP_INFO_S *dispInfo)
{
	VO_CHECK_POINTER(dispCtl);
    VO_CHECK_POINTER(dispInfo);

    switch(dispCtl->SyncMode)
    {
        case VO_SYSTEM_MODE_1920x1080x30P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x32;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
		//	dispInfo->vsize= 0x898;
		//	dispInfo->hsize= 0x465; 
            break;
        case VO_SYSTEM_MODE_1920x1080x25P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x32;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
		//	dispInfo->vsize= 0xa50;
		//	dispInfo->hsize= 0x465;         
            break; 
        case VO_SYSTEM_MODE_1280x720x50P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
		//	dispInfo->vsize= 0x7bc;
		//	dispInfo->hsize= 0x2ee;         
            break; 
        case VO_SYSTEM_MODE_1280x720x60P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
		//	dispInfo->vsize= 0x672;
		//	dispInfo->hsize= 0x2ee; 
            break; 
        case VO_SYSTEM_MODE_1280x720x30P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
		//	dispInfo->vsize= 0xce4;
		//	dispInfo->hsize= 0x2ee;         
            break; 
        case VO_SYSTEM_MODE_1280x720x25P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
		//	dispInfo->vsize= 0xf78;
		//	dispInfo->hsize= 0x2ee;  
            break;
        case VO_SYSTEM_MODE_1080x1920x30P:
#if 0
			dispInfo->dispHsyncCtl_start= 0x5;                              // HSA = 0x19 - 0x5 = 20
			dispInfo->dispHsyncCtl_stop= 0x19;//0x25;
		
			dispInfo->dispHsync1Ctl_start= 0x1;
			dispInfo->dispHsync1Ctl_stop= 0x5;
            
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x1;
#else
            dispInfo->dispHsyncCtl_start= 0x5;                              // HSA = 0x19 - 0x5 = 20
			dispInfo->dispHsyncCtl_stop= 0x19;//0x25;
		
			dispInfo->dispHsync1Ctl_start= 0x1;                             //  VSA = 0x05 - 0x01 = 0x04
			dispInfo->dispHsync1Ctl_stop= 0x5;
            
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x1;

#endif
		
//			dispInfo->dispHsync2Ctl_start= 0x1;                             // 可以不配
//			dispInfo->dispHsync2Ctl_stop= 0x5;                              // 可以不配

//			dispInfo->dispVsync2Ctl_start= 0x1;
//			dispInfo->dispVsync2Ctl_stop= 0x1;

			//
		//	dispInfo->vsize= 0x53c;
		//	dispInfo->hsize= 0x7a6;  
            break; 
        case VO_SYSTEM_MODE_800x1280x30P:

            printf("------------------------VO_SYSTEM_MODE_800x1280x30P  \n");
#if 0 
            dispInfo->dispHsyncCtl_start= 0x5;                              // HSA = 0x19 - 0x5 = 20
			dispInfo->dispHsyncCtl_stop= 0x19;//0x25;
		
			dispInfo->dispHsync1Ctl_start= 0x1;                             //  VSA = 0x05 - 0x01 = 0x04
			dispInfo->dispHsync1Ctl_stop= 0x5;
            
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x1;

            dispInfo->dispHsync2Ctl_start= 0x1;                             // 可以不配
			dispInfo->dispHsync2Ctl_stop= 0x5;                              // 可以不配

			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x1;
#else
            dispInfo->dispHsyncCtl_start= 5;                              // HSA = 0x19 - 0x5 = 20
			dispInfo->dispHsyncCtl_stop= 10;
		
			dispInfo->dispHsync1Ctl_start= 1;                             //  VSA = 0x05 - 0x01 = 0x04
			dispInfo->dispHsync1Ctl_stop= 5;
            
			dispInfo->dispVsync1Ctl_start= 1;
			dispInfo->dispVsync1Ctl_stop= 1;
#endif

            break;   
        default:
            VO_PRINTF_FUNC("ERR_VO_ILLEGAL_PARAM!\n");
            break;     
    }
    return 0;
}
/*
*Osd Rgb2Yuv
*/
static int VO_TEST_SetOsdRgb2YuvInfo(VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo)
{
    VO_CHECK_POINTER(osdRgb2YuvInfo);

    osdRgb2YuvInfo->osdrgb2yuv_coeff[0][0] = 0x00000132;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[0][1] = 0x00000259;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[0][2] = 0x00000075;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[0][3] = 0x00000000;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[1][0] = 0x00000f50;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[1][1] = 0x00000ea5;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[1][2] = 0x0000020b;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[1][3] = 0x00000080;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[2][0] = 0x0000020b;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[2][1] = 0x00000e4a;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[2][2] = 0x00000fab;
    osdRgb2YuvInfo->osdrgb2yuv_coeff[2][3] = 0x00000080;

    return 0; 
}  
/*
*MFBD
*/
static int VO_TEST_SetMfbdInfo(unsigned int mfbd_en,VO_LAYER0_MFBD_INFO_S *mfbdInfo)
{
    VO_CHECK_POINTER(mfbdInfo);

	mfbdInfo->mfbd_en = mfbd_en;
	mfbdInfo->y_addr0= MFBC_Y_DATA_WR_ADDR0;//DUMP_Y_MFBD_DATA_ADDR0;
	mfbdInfo->y_stride0= MFBC_DATA_STRIDE*4;//DUMP_Y_MFBD_DATA_STRIDE0*4;
	mfbdInfo->y_addr1= MFBC_Y_DATA_WR_ADDR1;//DUMP_Y_MFBD_DATA_ADDR0;
	mfbdInfo->y_stride1= MFBC_DATA_STRIDE*4;//DUMP_Y_MFBD_DATA_STRIDE0*4;
	mfbdInfo->y_head_addr0= MFBC_Y_HEAD_WR_ADDR0;//DUMP_Y_MFBD_HEAD_ADDR0;
	mfbdInfo->y_head_stride0= MFBC_DATA_STRIDE*4/32;//DUMP_Y_MFBD_HEAD_STRIDE0*4/32;
	mfbdInfo->y_head_addr1= MFBC_Y_HEAD_WR_ADDR1;//DUMP_Y_MFBD_HEAD_ADDR0;
	mfbdInfo->y_head_stride1= MFBC_DATA_STRIDE*4/32;//DUMP_Y_MFBD_HEAD_STRIDE0*4/32;
	mfbdInfo->uv_addr0= MFBC_UV_DATA_WR_ADDR0;//DUMP_UV_MFBD_DATA_ADDR0;
	mfbdInfo->uv_stride0= MFBC_DATA_STRIDE*4;//DUMP_UV_MFBD_DATA_STRIDE0*4;
	mfbdInfo->uv_addr1= MFBC_UV_DATA_WR_ADDR1;//DUMP_UV_MFBD_DATA_ADDR0;
	mfbdInfo->uv_stride1= MFBC_DATA_STRIDE*4;//DUMP_UV_MFBD_DATA_STRIDE0*4;
	mfbdInfo->uv_head_addr0= MFBC_UV_HEAD_WR_ADDR0;//DUMP_UV_MFBD_HEAD_ADDR0;
	mfbdInfo->uv_head_stride0= MFBC_DATA_STRIDE*4/32;//DUMP_UV_MFBD_HEAD_STRIDE0*4/32;
	mfbdInfo->uv_head_addr1= MFBC_UV_HEAD_WR_ADDR1;//DUMP_UV_MFBD_HEAD_ADDR0;
	mfbdInfo->uv_head_stride1= MFBC_DATA_STRIDE*4/32;//DUMP_UV_MFBD_HEAD_STRIDE0*4/32;

    return 0;
}
/*
*Yuv2Rgb
*/
static int VO_TEST_SetYuv2RgbInfo(unsigned int yuv2rgb_ctl_en,VO_YUV2RGB_INFO_S *yuv2rgbInfo)
{
    VO_CHECK_POINTER(yuv2rgbInfo);

    yuv2rgbInfo->yuv2rgb_ctl_en = yuv2rgb_ctl_en;

    yuv2rgbInfo->yuv2rgb_coeff[0][0] =0x00000400;
    yuv2rgbInfo->yuv2rgb_coeff[0][1] =0x00000000;
    yuv2rgbInfo->yuv2rgb_coeff[0][2] =0x000005a1;
    yuv2rgbInfo->yuv2rgb_coeff[0][3] =0x00000f4c;
    yuv2rgbInfo->yuv2rgb_coeff[1][0] =0x00000400;
    yuv2rgbInfo->yuv2rgb_coeff[1][1] =0x00000e9e;
    yuv2rgbInfo->yuv2rgb_coeff[1][2] =0x00000d22;
    yuv2rgbInfo->yuv2rgb_coeff[1][3] =0x00000088;
    yuv2rgbInfo->yuv2rgb_coeff[2][0] =0x00000400;
    yuv2rgbInfo->yuv2rgb_coeff[2][1] =0x0000071e;
    yuv2rgbInfo->yuv2rgb_coeff[2][2] =0x00000000;
    yuv2rgbInfo->yuv2rgb_coeff[2][3] =0x00000f1c;

    return 0; 
}
/*
*Disp iRQ
*/
static int VO_TEST_SetDispIrqInfo(VO_DISP_IRQ_INFO_S *dispIrqInfo)
{
    VO_CHECK_POINTER(dispIrqInfo);

    dispIrqInfo->underrundcnt0= 2;
    dispIrqInfo->en0= FALSE;
    dispIrqInfo->underrundcnt1= 2;
    dispIrqInfo->en1= FALSE;
    dispIrqInfo->underrundcnt2= 2;
    dispIrqInfo->en2= FALSE;

    return 0; 
}
/*
*disp
*/
static int VO_TEST_SetDisp(VO_DISP_CTL_INFO_S *dispCtl,VO_DISP_INFO_S *dispInfo)
{
    VO_CHECK_POINTER(dispCtl);
    VO_CHECK_POINTER(dispInfo);

    if(TRUE == dispCtl->Disp_en)
    {
    	dispInfo->dispEnable= FALSE;
    }
    else
    {
    	dispInfo->dispEnable= TRUE;
    }

    dispInfo->xZoneCtl_start=  dispCtl->disp_start.Width;//VIDEO_DISP_ZONE_X_START;
    dispInfo->xZoneCtl_stop=  dispCtl->disp_stop.Width - 1;//VIDEO_DISP_ZONE_X_STOP - 1;
    dispInfo->yZoneCtl_start=  dispCtl->disp_start.Height;//VIDEO_DISP_ZONE_Y_START;
    dispInfo->yZoneCtl_stop=  dispCtl->disp_stop.Height - 1;//VIDEO_DISP_ZONE_Y_STOP -1;
    //
    dispInfo->vcntbit0    = 0;
    dispInfo->secndfoffset= 3;
    dispInfo->framesyncdly= 8;
    //
    //unsigned int SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    VO_TEST_SetFrameBit(dispCtl,dispInfo);
    dispInfo->hsize= dispCtl->total_size.Width;//0x898;
	dispInfo->vsize= dispCtl->total_size.Height;//0x465;
    return 0;
}
/*
*layer0
*/
static int VO_TEST_SetLayer0(VO_LAYER_CTL_INFO_S *layer0Ctl,VO_LAYER0_INFO_S *layer0Info,VO_MIX_INFO_S *layer0MixInfo)
{	
    VO_CHECK_POINTER(layer0Ctl);
    VO_CHECK_POINTER(layer0Info);
    VO_CHECK_POINTER(layer0MixInfo);


    layer0Info->layer0DispEn= layer0Ctl->layer_en;
	layer0Info->layer0En= layer0Ctl->layer_en; 
	layer0Info->scalerBlen= 0x7;
	//
	VO_LAYER0_DAT_MODE_INFO_S *datModeInfo= &layer0Info->datModeInfo;
    datModeInfo->datmode = layer0Ctl->ImgInDataMode;
    datModeInfo->endiany = layer0Ctl->endiany ;//VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    datModeInfo->endianuv= layer0Ctl->endianuv ;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3;
    datModeInfo->swi= layer0Ctl->uvswap;//TRUE;
	//
	VO_LAYER_AREA_INFO_S *areaInfo= &layer0Info->areaInfo;
    areaInfo->xCtl_start= layer0Ctl->ctl_offset.Width;//VIDEO_LAYER0_H_POSITION;
    areaInfo->xCtl_stop= layer0Ctl->ctl_offset.Width + layer0Ctl->out_size.Width - 1;// - 1;//VIDEO_LAYER0_H_POSITION + VIDEO_LAYER0_H_OUT_SIZE;
    areaInfo->yCtl_start= layer0Ctl->ctl_offset.Height;//VIDEO_LAYER0_V_POSITION;
    areaInfo->yCtl_stop= layer0Ctl->ctl_offset.Height + layer0Ctl->out_size.Height;// - 1;//VIDEO_LAYER0_V_POSITION + VIDEO_LAYER0_V_OUT_SIZE;
	//
	VO_YUV_BUF_INFO_S *bufInfo= &layer0Info->bufInfo;
    bufInfo->yAddr0= layer0Ctl->bufInfo.yAddr0;//LAYER0_Y_BASEAddr0;//DUMP_Y_1080P_ADDR0;
    bufInfo->yAddr1= layer0Ctl->bufInfo.yAddr1;//LAYER0_Y_BASEAddr0;//DUMP_Y_1080P_ADDR1;
    bufInfo->uvAddr0= layer0Ctl->bufInfo.uvAddr0;//LAYER0_UV_BASEaddr0;//DUMP_UV_1080P_ADDR0;
    bufInfo->uvAddr1= layer0Ctl->bufInfo.uvAddr1;//LAYER0_UV_BASEaddr0;//DUMP_UV_1080P_ADDR1;
    //bufInfo->hsize_stride= VIDEO_LAYER0_RD_1920_STRIDE; //1920
    //bufInfo->vsize_stride= 0;
    bufInfo->hsize_stride= layer0Ctl->bufInfo.hsize_stride;//0xff;//VIDEO_LAYER2_RD_STRIDE;
    bufInfo->vsize_stride= layer0Ctl->bufInfo.vsize_stride;//0x437;//0;
	//		
	VO_LAYER0_SIZE_INFO_S *layer0sizeInfo= &layer0Info->sizeInfo;
    layer0sizeInfo->offset_hsize= layer0Ctl->size_offset.Width;//0;
    layer0sizeInfo->offset_vsize= layer0Ctl->size_offset.Height;//0;
    layer0sizeInfo->in_hsize= layer0Ctl->active_size.Width -1;//VIDEO_LAYER0_H_IN_SIZE;
    layer0sizeInfo->in_vsize= layer0Ctl->active_size.Height -1;//VIDEO_LAYER0_V_IN_SIZE;
    layer0sizeInfo->out_hsize= layer0Ctl->out_size.Width -1;//VIDEO_LAYER0_H_OUT_SIZE;
    layer0sizeInfo->out_vsize= layer0Ctl->out_size.Height -1;// VIDEO_LAYER0_V_OUT_SIZE;
    //
    VO_LAYER0_SCALE_INFO_S *layer0ScaleInfo = &layer0Info->scaleInfo;
    vo_core_calc_scale(layer0sizeInfo,layer0ScaleInfo);
	//		
	VO_BASE_MODE_INFO_S *baseModeInfo= &layer0Info->baseModeInfo;
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 0;
    baseModeInfo->base1mask= 0;
	//	 
    unsigned int mfbd_en = layer0Ctl->layer0_mfbd_en;//FALSE;
	VO_LAYER0_MFBD_INFO_S *mfbdInfo= &layer0Info->mfbdInfo;    
    VO_TEST_SetMfbdInfo(mfbd_en,mfbdInfo);
    //layer0 mix
    layer0MixInfo->glben = layer0Ctl->layerMix_en;//layer0Ctl->layer_en;
    layer0MixInfo->glbalp = layer0Ctl->layerMix_glbalp ;//0xff;
    layer0MixInfo->sel = VO_MIXER_VIDEO_LAYER_0;

    return 0;
}
/*
*layer1
*/
static int VO_TEST_SetLayer1(VO_LAYER_CTL_INFO_S *layer1Ctl,VO_LAYER1_INFO_S *layer1Info,VO_MIX_INFO_S *layer1MixInfo)
{
    VO_CHECK_POINTER(layer1Ctl);
    VO_CHECK_POINTER(layer1Info);
    VO_CHECK_POINTER(layer1MixInfo);

    layer1Info->layer1DispEn = layer1Ctl->layer_en;
    //
    VO_LAYER_INFO_S *layerInfo = &layer1Info->layerInfo;
    layerInfo->enable   = layer1Ctl->layer_en;
    if( layer1Ctl->ImgInDataMode == VO_VIDEO_LAYER_YUV_MODE_420)
    {
        layerInfo->yuv422en = FALSE;
        layerInfo->yuv420en = TRUE;
    }
    else
    {
        layerInfo->yuv422en = TRUE;
        layerInfo->yuv420en = FALSE;
    }  

    layerInfo->endiany  = layer1Ctl->endiany;//VO_VIDEO_LAYER_Y_ENDIAN_MODE1;        
    layerInfo->endianuv = layer1Ctl->endianuv;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;        
    layerInfo->uvswap   = layer1Ctl->uvswap;//TRUE;
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer1Info->areaInfo;
    areaInfo->xCtl_start= layer1Ctl->ctl_offset.Width;//198;
    areaInfo->xCtl_stop= layer1Ctl->ctl_offset.Width + layer1Ctl->active_size.Width - 1;// - 1;//198 + 1920 -1;
    areaInfo->yCtl_start= layer1Ctl->ctl_offset.Height;//42;
    areaInfo->yCtl_stop= layer1Ctl->ctl_offset.Height + layer1Ctl->active_size.Height;// - 1;//42 + 1080 -1;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer1Info->bufInfo;
    bufInfo->yAddr0= layer1Ctl->bufInfo.yAddr0;//LAYER0_Y_BASEAddr0;
    bufInfo->yAddr1= layer1Ctl->bufInfo.yAddr1;//LAYER0_Y_BASEAddr0;
    bufInfo->uvAddr0= layer1Ctl->bufInfo.uvAddr0;//LAYER0_UV_BASEaddr0;
    bufInfo->uvAddr1= layer1Ctl->bufInfo.uvAddr1;//LAYER0_UV_BASEaddr0;
    bufInfo->hsize_stride= layer1Ctl->bufInfo.hsize_stride;//0xff;//VIDEO_LAYER2_RD_STRIDE;
    bufInfo->vsize_stride= layer1Ctl->bufInfo.vsize_stride;//0x437;//0;
    //
    VO_LAYER_SIZE_INFO_S *layer1sizeInfo = &layer1Info->layer1SizeInfo; 
    layer1sizeInfo->offset_hsize= layer1Ctl->size_offset.Width;//0;
    layer1sizeInfo->offset_vsize= layer1Ctl->size_offset.Height;//0;
    layer1sizeInfo->in_hsize= layer1Ctl->active_size.Width - 1;//1920 - 1;
    layer1sizeInfo->in_vsize= layer1Ctl->active_size.Height - 1;//1080 - 1;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer1Info->imgInBlenthInfo;
    imgInBlenthInfo->blen  = 0xf;
    imgInBlenthInfo->voffset = 0x0;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer1Info->baseModeInfo;
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 0;
    baseModeInfo->base1mask= 1;//0;
    //layer1
    layer1MixInfo->glben = layer1Ctl->layerMix_en;//layer1Ctl->layer_en;
    layer1MixInfo->glbalp = layer1Ctl->layerMix_glbalp;//0xff;
    layer1MixInfo->sel = VO_MIXER_VIDEO_LAYER_1;

    return 0; 
}
/*
*layer2
*/
static int VO_TEST_SetLayer2(VO_LAYER_CTL_INFO_S *layer2Ctl,VO_LAYER2_INFO_S *layer2Info,VO_MIX_INFO_S *layer2MixInfo)
{
    VO_CHECK_POINTER(layer2Ctl);
    VO_CHECK_POINTER(layer2Info);
    VO_CHECK_POINTER(layer2MixInfo);

    layer2Info->layer2DispEn = layer2Ctl->layer_en;
    //
    VO_LAYER_INFO_S *layerInfo = &layer2Info->layerInfo;
    layerInfo->enable   = layer2Ctl->layer_en;
    if( layer2Ctl->ImgInDataMode == VO_VIDEO_LAYER_YUV_MODE_420)
    {
        layerInfo->yuv422en = FALSE;
        layerInfo->yuv420en = TRUE;
    }
    else
    {
        layerInfo->yuv422en = TRUE;
        layerInfo->yuv420en = FALSE;
    }  

    layerInfo->endiany  = layer2Ctl->endiany;//VO_VIDEO_LAYER_Y_ENDIAN_MODE1;        
    layerInfo->endianuv = layer2Ctl->endianuv;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;        
    layerInfo->uvswap   = layer2Ctl->uvswap;//TRUE;
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer2Info->areaInfo;
    areaInfo->xCtl_start= layer2Ctl->ctl_offset.Width;//198;
    areaInfo->xCtl_stop= layer2Ctl->ctl_offset.Width + layer2Ctl->active_size.Width - 1;// - 1;//198 + 1920 -1;
    areaInfo->yCtl_start= layer2Ctl->ctl_offset.Height;//42;
    areaInfo->yCtl_stop= layer2Ctl->ctl_offset.Height + layer2Ctl->active_size.Height;// - 1;//42 + 1080 -1;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer2Info->bufInfo;
    bufInfo->yAddr0= layer2Ctl->bufInfo.yAddr0;//LAYER0_Y_BASEAddr0;
    bufInfo->yAddr1= layer2Ctl->bufInfo.yAddr1;//LAYER0_Y_BASEAddr0;
    bufInfo->uvAddr0= layer2Ctl->bufInfo.uvAddr0;//LAYER0_UV_BASEaddr0;
    bufInfo->uvAddr1= layer2Ctl->bufInfo.uvAddr1;//LAYER0_UV_BASEaddr0;
    bufInfo->hsize_stride= layer2Ctl->bufInfo.hsize_stride;//0xff;//VIDEO_LAYER2_RD_STRIDE;
    bufInfo->vsize_stride= layer2Ctl->bufInfo.vsize_stride;//0x437;//0;
    //
    VO_LAYER_SIZE_INFO_S *layer2sizeInfo = &layer2Info->layer2SizeInfo; 
    layer2sizeInfo->offset_hsize= layer2Ctl->size_offset.Width;//0;
    layer2sizeInfo->offset_vsize= layer2Ctl->size_offset.Height;//0;
    layer2sizeInfo->in_hsize= layer2Ctl->active_size.Width - 1;//1920 - 1;
    layer2sizeInfo->in_vsize= layer2Ctl->active_size.Height - 1;//1080 - 1;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer2Info->imgInBlenthInfo; 
    imgInBlenthInfo->blen  = 0xf;
    imgInBlenthInfo->voffset = 0x0;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer2Info->baseModeInfo; 
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 0;
    baseModeInfo->base1mask= 1;//0;
    //layer2
    layer2MixInfo->glben = layer2Ctl->layerMix_en;//layer2Ctl->layer_en;
    layer2MixInfo->glbalp = layer2Ctl->layerMix_glbalp;//0xff;
    layer2MixInfo->sel = VO_MIXER_VIDEO_LAYER_2;

    return 0; 
}
/*
*layer3
*/
static int VO_TEST_SetLayer3(VO_LAYER_CTL_INFO_S *layer3Ctl,VO_LAYER3_INFO_S *layer3Info,VO_MIX_INFO_S *layer3MixInfo)
{
    VO_CHECK_POINTER(layer3Ctl);
    VO_CHECK_POINTER(layer3Info);
    VO_CHECK_POINTER(layer3MixInfo);

    layer3Info->layer3DispEn = layer3Ctl->layer_en;
    //
    VO_LAYER_INFO_S *layerInfo = &layer3Info->layerInfo;
    layerInfo->enable   = layer3Ctl->layer_en;
    if( layer3Ctl->ImgInDataMode == VO_VIDEO_LAYER_YUV_MODE_420)
    {
        layerInfo->yuv422en = FALSE;
        layerInfo->yuv420en = TRUE;
    }
    else
    {
        layerInfo->yuv422en = TRUE;
        layerInfo->yuv420en = FALSE;
    }  

    layerInfo->endiany  = layer3Ctl->endiany;//VO_VIDEO_LAYER_Y_ENDIAN_MODE1;        
    layerInfo->endianuv = layer3Ctl->endianuv;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;        
    layerInfo->uvswap   = layer3Ctl->uvswap;//TRUE;
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer3Info->areaInfo;
    areaInfo->xCtl_start= layer3Ctl->ctl_offset.Width;//198;
    areaInfo->xCtl_stop= layer3Ctl->ctl_offset.Width + layer3Ctl->active_size.Width -1;// - 1;//198 + 1920 -1;
    areaInfo->yCtl_start= layer3Ctl->ctl_offset.Height;//42;
    areaInfo->yCtl_stop= layer3Ctl->ctl_offset.Height + layer3Ctl->active_size.Height;// - 1;//42 + 1080 -1;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer3Info->bufInfo;
    bufInfo->yAddr0= layer3Ctl->bufInfo.yAddr0;//LAYER0_Y_BASEAddr0;
    bufInfo->yAddr1= layer3Ctl->bufInfo.yAddr1;//LAYER0_Y_BASEAddr0;
    bufInfo->uvAddr0= layer3Ctl->bufInfo.uvAddr0;//LAYER0_UV_BASEaddr0;
    bufInfo->uvAddr1= layer3Ctl->bufInfo.uvAddr1;//LAYER0_UV_BASEaddr0;
    bufInfo->hsize_stride= layer3Ctl->bufInfo.hsize_stride;//0xff;//VIDEO_layer3_RD_STRIDE;
    bufInfo->vsize_stride= layer3Ctl->bufInfo.vsize_stride;//0x437;//0;
    //
    VO_LAYER_SIZE_INFO_S *layer3sizeInfo = &layer3Info->layer3SizeInfo; 
    layer3sizeInfo->offset_hsize= layer3Ctl->size_offset.Width;//0;
    layer3sizeInfo->offset_vsize= layer3Ctl->size_offset.Height;//0;
    layer3sizeInfo->in_hsize= layer3Ctl->active_size.Width - 1;//1920 - 1;
    layer3sizeInfo->in_vsize= layer3Ctl->active_size.Height - 1;//1080 - 1;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer3Info->imgInBlenthInfo; 
    imgInBlenthInfo->blen  = 0xf;
    imgInBlenthInfo->voffset = 0x0;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer3Info->baseModeInfo; 
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 0;
    baseModeInfo->base1mask= 0;
    //layer3
    layer3MixInfo->glben = layer3Ctl->layerMix_en;//layer3Ctl->layer_en;
    layer3MixInfo->glbalp = layer3Ctl->layerMix_glbalp;//0xff;
    layer3MixInfo->sel = VO_MIXER_VIDEO_LAYER_3;

    return 0; 
}
/*
*Layer4 osd0
*/
static int VO_TEST_SetLayer4Osd0(VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl,VO_OSD0_INFO_S *osd0Info,VO_MIX_INFO_S *layer4osd0MixInfo)
{
    VO_CHECK_POINTER(layer4osd0Ctl);
    VO_CHECK_POINTER(osd0Info);
    VO_CHECK_POINTER(layer4osd0MixInfo);

    osd0Info->osdLayer4DispEn = layer4osd0Ctl->layer_en;
    osd0Info->osdrgb2yuvEn = layer4osd0Ctl->osdrgb2yuvEn;
    osd0Info->osdtype = layer4osd0Ctl->osdtype;//OSD_MONOCHROME_8BIT;
    osd0Info->alphatpye = layer4osd0Ctl->alphatpye;//OSD_FIXED_VALUE;
    VO_LAYER_AREA_INFO_S   *osd0AreaInfo = &osd0Info->osd0AreaInfo;
    osd0AreaInfo->xCtl_start= layer4osd0Ctl->ctl_offset.Width;//400;
    osd0AreaInfo->xCtl_stop= layer4osd0Ctl->ctl_offset.Width + layer4osd0Ctl->active_size.Width-1;//400 + 216;
    osd0AreaInfo->yCtl_start= layer4osd0Ctl->ctl_offset.Height;//200;
    osd0AreaInfo->yCtl_stop= layer4osd0Ctl->ctl_offset.Height + layer4osd0Ctl->active_size.Height;//200 + 172;    
    VO_OSD_SIZE_INFO_S     *osd0SizeInfo =  &osd0Info->osd0SizeInfo;
    osd0SizeInfo->width = layer4osd0Ctl->active_size.Width;//216;
    osd0SizeInfo->height = layer4osd0Ctl->active_size.Height;//172;
    VO_OSD_BUF_INFO_S      *osd0BufInfo =  &osd0Info->osd0BufInfo;
    osd0BufInfo->alp_addr0= layer4osd0Ctl->osdBufInfo.alp_addr0;//0x20000100;
    osd0BufInfo->alp_addr1= layer4osd0Ctl->osdBufInfo.alp_addr1;//0x20000100;
    osd0BufInfo->alpstride= layer4osd0Ctl->osdBufInfo.alpstride;//256/8;
    osd0BufInfo->vlu_addr0= layer4osd0Ctl->osdBufInfo.vlu_addr0;//0x20000100;
    osd0BufInfo->vlu_addr1= layer4osd0Ctl->osdBufInfo.vlu_addr1;//0x20000100;
    osd0BufInfo->osdstride= layer4osd0Ctl->osdBufInfo.osdstride;//256/8;
    VO_BASE_MODE_INFO_S    *baseModeInfo =  &osd0Info->osd0BaseModeInfo;
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 0;
    baseModeInfo->base1mask= 0;
    VO_OSD_DMA_INFO_S      *osd0DmaInfo =  &osd0Info->osd0DmaInfo;
    osd0DmaInfo->dmarequestlen= 0xf;
    osd0DmaInfo->dmamap       = OSD_ORIGINAL_ORDER;
    osd0DmaInfo->rgbrev       = OSD_RGB_REV_B; 
//printf("zxj, VO_TEST_SetLayer4Osd0, osd0DmaInfo->rgbrev = %d\n", osd0DmaInfo->rgbrev);
    
    //layer4 osd0 mix
    layer4osd0MixInfo->glben = layer4osd0Ctl->layerMix_en;//layer4osd0Ctl->layer_en;
    layer4osd0MixInfo->glbalp = layer4osd0Ctl->layerMix_glbalp;//0xff;
    layer4osd0MixInfo->sel = VO_MIXER_OSD_LAYER_0;

    return 0; 
}
/*
*Layer5 osd1
*/
static int VO_TEST_SetLayer5Osd1(VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl,VO_OSD1_INFO_S *osd1Info,VO_MIX_INFO_S *layer5osd1MixInfo)
{
    VO_CHECK_POINTER(layer5osd1Ctl);
    VO_CHECK_POINTER(osd1Info);
    VO_CHECK_POINTER(layer5osd1MixInfo);

    osd1Info->osdLayer5DispEn = layer5osd1Ctl->layer_en;
    osd1Info->osdrgb2yuvEn = layer5osd1Ctl->osdrgb2yuvEn;
    osd1Info->osdtype = layer5osd1Ctl->osdtype;//OSD_MONOCHROME_8BIT;
    osd1Info->alphatpye = layer5osd1Ctl->alphatpye;//OSD_FIXED_VALUE;
    VO_LAYER_AREA_INFO_S   *osd1AreaInfo = &osd1Info->osd1AreaInfo;
    osd1AreaInfo->xCtl_start= layer5osd1Ctl->ctl_offset.Width;//800;
    osd1AreaInfo->xCtl_stop= layer5osd1Ctl->ctl_offset.Width + layer5osd1Ctl->active_size.Width-1;//800 + 216;
    osd1AreaInfo->yCtl_start= layer5osd1Ctl->ctl_offset.Height;//200;
    osd1AreaInfo->yCtl_stop= layer5osd1Ctl->ctl_offset.Height + layer5osd1Ctl->active_size.Height;//200 + 172;
    VO_OSD_SIZE_INFO_S     *osd1SizeInfo =  &osd1Info->osd1SizeInfo;
    osd1SizeInfo->width = layer5osd1Ctl->active_size.Width;//216;
    osd1SizeInfo->height = layer5osd1Ctl->active_size.Height;//172;
    VO_OSD_BUF_INFO_S      *osd1BufInfo =  &osd1Info->osd1BufInfo;
    osd1BufInfo->alp_addr0= layer5osd1Ctl->osdBufInfo.alp_addr0;//0x20200100;
    osd1BufInfo->alp_addr1= layer5osd1Ctl->osdBufInfo.alp_addr1;//0x20200100;
    osd1BufInfo->alpstride= layer5osd1Ctl->osdBufInfo.alpstride;//256/8;
    osd1BufInfo->vlu_addr0= layer5osd1Ctl->osdBufInfo.vlu_addr0;//0x20200100;
    osd1BufInfo->vlu_addr1= layer5osd1Ctl->osdBufInfo.vlu_addr1;//0x20200100;
    osd1BufInfo->osdstride= layer5osd1Ctl->osdBufInfo.osdstride;//256/8;
    VO_BASE_MODE_INFO_S    *baseModeInfo =  &osd1Info->osd1BaseModeInfo;
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 0;
    baseModeInfo->base1mask= 0;
    VO_OSD_DMA_INFO_S      *osd1DmaInfo =  &osd1Info->osd1DmaInfo;
    osd1DmaInfo->dmarequestlen= 0xf;
    osd1DmaInfo->dmamap       = OSD_ORIGINAL_ORDER;
    osd1DmaInfo->rgbrev       = OSD_RGB_REV_R; 
    //layer5 osd1
    layer5osd1MixInfo->glben = layer5osd1Ctl->layerMix_en;//layer5osd1Ctl->layer_en;
    layer5osd1MixInfo->glbalp = layer5osd1Ctl->layerMix_glbalp;//0xff;
    layer5osd1MixInfo->sel = VO_MIXER_OSD_LAYER_1;

    return 0; 
}
/*
*Layer6 osd2
*/
static int VO_TEST_SetLayer6Osd2(VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl,VO_OSD2_INFO_S *osd2Info,VO_MIX_INFO_S *layer6osd2MixInfo)
{
    VO_CHECK_POINTER(layer6osd2Ctl);
    VO_CHECK_POINTER(osd2Info);
    VO_CHECK_POINTER(layer6osd2MixInfo);

    osd2Info->osdLayer6DispEn = layer6osd2Ctl->layer_en;
    osd2Info->osdrgb2yuvEn = layer6osd2Ctl->osdrgb2yuvEn;
    osd2Info->osdtype = layer6osd2Ctl->osdtype;//OSD_MONOCHROME_8BIT;
    osd2Info->alphatpye = layer6osd2Ctl->alphatpye;//OSD_FIXED_VALUE;
    VO_LAYER_AREA_INFO_S   *osd2AreaInfo = &osd2Info->osd2AreaInfo;
    osd2AreaInfo->xCtl_start= layer6osd2Ctl->ctl_offset.Width;//800;
    osd2AreaInfo->xCtl_stop= layer6osd2Ctl->ctl_offset.Width + layer6osd2Ctl->active_size.Width;//800 + 216;
    osd2AreaInfo->yCtl_start= layer6osd2Ctl->ctl_offset.Height;//200;
    osd2AreaInfo->yCtl_stop= layer6osd2Ctl->ctl_offset.Height + layer6osd2Ctl->active_size.Height;//200 + 172;
    VO_OSD_SIZE_INFO_S     *osd2SizeInfo =  &osd2Info->osd2SizeInfo;
    osd2SizeInfo->width = layer6osd2Ctl->active_size.Width;//216;
    osd2SizeInfo->height = layer6osd2Ctl->active_size.Height;//172;
    VO_OSD_BUF_INFO_S      *osd2BufInfo =  &osd2Info->osd2BufInfo;
    osd2BufInfo->alp_addr0= layer6osd2Ctl->osdBufInfo.alp_addr0;//0x20200100;
    osd2BufInfo->alp_addr1= layer6osd2Ctl->osdBufInfo.alp_addr1;//0x20200100;
    osd2BufInfo->alpstride= layer6osd2Ctl->osdBufInfo.alpstride;//256;        
    osd2BufInfo->vlu_addr0= layer6osd2Ctl->osdBufInfo.vlu_addr0;//0x20200100;
    osd2BufInfo->vlu_addr1= layer6osd2Ctl->osdBufInfo.vlu_addr1;//0x20200100;
    osd2BufInfo->osdstride= layer6osd2Ctl->osdBufInfo.osdstride;//256;
    VO_BASE_MODE_INFO_S    *baseModeInfo =  &osd2Info->osd2BaseModeInfo;
    baseModeInfo->mode= 0;
    baseModeInfo->base0mask= 1;
    baseModeInfo->base1mask= 1;
    VO_OSD_DMA_INFO_S      *osd2DmaInfo =  &osd2Info->osd2DmaInfo;
    osd2DmaInfo->dmarequestlen= 0xf;
    osd2DmaInfo->dmamap       = OSD_ORIGINAL_ORDER;
    osd2DmaInfo->rgbrev       = OSD_RGB_REV_R; 
    //layer6 osd2
    layer6osd2MixInfo->glben = layer6osd2Ctl->layerMix_en;//layer6osd2Ctl->layer_en;
    layer6osd2MixInfo->glbalp = layer6osd2Ctl->layerMix_glbalp;//0xff;
    layer6osd2MixInfo->sel = VO_MIXER_OSD_LAYER_2;

    return 0; 
}
#if 0
/*
*WB
*/
static int VO_TEST_SetWBInfo(VO_WB_INFO_S *wbInfo)
{
    VO_CHECK_POINTER(wbInfo);
    wbInfo->wb_en= FALSE;
    wbInfo->inchmode= ;
	wbInfo->buffersize= ;
	wbInfo->v_size_out= ;
	wbInfo->h_size_out= ;
    //
    VO_WB_BUF_INFO_S *wbBufInfo= &wbInfo->wbBufInfo;
    wbBufInfo->wbYInfo.y_en = ;
    wbBufInfo->wbYInfo.addr0 = ;
    wbBufInfo->wbYInfo.addr1 = ;
    wbBufInfo->wbYInfo.hstride = ;
    wbBufInfo->wbUVInfo.uv_en = ;
    wbBufInfo->wbUVInfo.addr0 = ;
    wbBufInfo->wbUVInfo.addr1 = ;
    wbBufInfo->wbUVInfo.hstride = ;
    //
    VO_WB_PIXEL_FORMAT_OUT_INFO_S *wbPixelFormatOutInfo= &wbInfo->wbPixelFormatOutInfo;
    wbPixelFormatOutInfo->formatsel    = ;
    wbPixelFormatOutInfo->inputformat  = ;
    wbPixelFormatOutInfo->outputformat = ;
    wbPixelFormatOutInfo->pixelorder422= ;
    wbPixelFormatOutInfo->rgbpixelwidth= ;
    //
    VO_WB_CH_INFO_S *ch0Info= &wbInfo->ch0Info;
    ch0Info->request = ;
    ch0Info->err_unit = ;
    ch0Info->err_threshold = ;
    //
    ch0Info->wbDmaInfo.blen = ;
    ch0Info->wbDmaInfo.continuousmode = ;
    ch0Info->wbDmaInfo.errdetecten = ;
    ch0Info->wbDmaInfo.otnum =;
    ch0Info->wbDmaInfo.swap =;
    //
    ch0Info->wbInfoClr.maxbw = ;
    ch0Info->wbInfoClr.totalbw = ;
    ch0Info->wbInfoClr.frmcntclear = ;
    ch0Info->wbInfoClr.fifoerrclear =;
    //
    VO_WB_CH_INFO_S *ch1Info= &wbInfo->ch1Info;
    ch1Info->request = ;
    ch1Info->err_unit = ;
    ch1Info->err_threshold = ;
    //
    ch1Info->wbDmaInfo.blen = ;
    ch1Info->wbDmaInfo.continuousmode = ;
    ch1Info->wbDmaInfo.errdetecten = ;
    ch1Info->wbDmaInfo.otnum =;
    ch1Info->wbDmaInfo.swap =;
    //
    ch1Info->wbInfoClr.maxbw = ;
    ch1Info->wbInfoClr.totalbw = ;
    ch1Info->wbInfoClr.frmcntclear = ;
    ch1Info->wbInfoClr.fifoerrclear =;
    return 0; 
}
#endif
/************************************************************************
*default*
*************************************************************************/
static VO_TEST_GetCoreDefault(VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(voCoreInfo);
    //
    #if 0
    VO_DISP_INFO_S   	*dispInfo = &voCoreInfo->dispInfo;
    dispInfo->dispEnable    = ;
    dispInfo->xZoneCtl_start    = ;
    dispInfo->xZoneCtl_stop    = ;
    dispInfo->yZoneCtl_start    = ;
    dispInfo->yZoneCtl_stop    = ;
    dispInfo->dispHsyncCtl_start    = ;
    dispInfo->dispHsyncCtl_stop    = ;
    dispInfo->dispHsync1Ctl_start    = ;
    dispInfo->dispHsync1Ctl_stop    = ;
    dispInfo->dispVsync1Ctl_start    = ;
    dispInfo->dispVsync1Ctl_stop    = ;
    dispInfo->dispHsync2Ctl_start    = ;
    dispInfo->dispHsync2Ctl_stop    = ;
    dispInfo->dispVsync2Ctl_start    = ;
    dispInfo->dispVsync2Ctl_stop    = ; 
    dispInfo->vcntbit0        = ;
    dispInfo->secndfoffset    = ;
    dispInfo->framesyncdly    = ;
    dispInfo->hsize    = ;
    dispInfo->vsize    = ; 
    //
    VO_LAYER0_INFO_S 	*layer0Info = &voCoreInfo->layer0Info;
    layer0Info->
    //
    VO_LAYER1_INFO_S 	*layer1Info = &voCoreInfo->layer1Info;

    //
    VO_LAYER2_INFO_S 	*layer2Info = &voCoreInfo->layer2Info;

    VO_LAYER3_INFO_S 	*layer3Info = &voCoreInfo->layer3Info;

    VO_OSD0_INFO_S   	*osd0Info = &voCoreInfo->osd0Info;

    VO_OSD1_INFO_S   	*osd1Info = &voCoreInfo->osd1Info;

    VO_OSD2_INFO_S   	*osd2Info = &voCoreInfo->osd2Info;

    VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo = &voCoreInfo->osdRgb2YuvInfo;

    VO_YUV2RGB_INFO_S   *yuv2rgbInfo = &voCoreInfo->yuv2rgbInfo;  

    VO_DISP_MIX_INFO_S  *dispMixCtlInfo = &voCoreInfo->dispMixCtlInfo;

    unsigned int        ditherctlen = voCoreInfo->di;
    unsigned int        clutctlen;
    VO_DISP_IRQ_INFO_S  *dispIrqInfo = &voCoreInfo->dispIrqInfo;
    #endif
    VO_WB_INFO_S        *wbInfo = &voCoreInfo->wbInfo;
    wbInfo->wb_en= 0;
    wbInfo->inchmode= 0;
	wbInfo->buffersize= 0;
	wbInfo->v_size_out= 0;
	wbInfo->h_size_out= 0; 

}

#define REG_VO_BASE                                         0x92700000
#define REG_VO_WB_DMACH                                     (REG_VO_BASE + 0x400) /* read/write */
#define REG_VO_WB_DMAMODE                                   (REG_VO_BASE + 0x404) /* read/write */
#define REG_VO_WB_WBPIXEL                                   (REG_VO_BASE + 0x408) /* read/write */
#define REG_VO_WB_OUTADDR0DATAY                             (REG_VO_BASE + 0x40c) /* read/write */
#define REG_VO_WB_OUTADDR1DATAY                             (REG_VO_BASE + 0x410) /* read/write */
#define REG_VO_WB_OUTADDR0DATAUV                            (REG_VO_BASE + 0x414) /* read/write */
#define REG_VO_WB_OUTADDR1DATAUV                            (REG_VO_BASE + 0x418) /* read/write */
#define REG_VO_WB_HSTRIDEY                                  (REG_VO_BASE + 0x41C) /* read/write */
#define REG_VO_WB_HSTRIDEUV                                 (REG_VO_BASE + 0x420) /* read/write */
#define REG_VO_WB_BUFSIZE                                   (REG_VO_BASE + 0x424) /* read/write */
#define REG_VO_WB_VSIZE                                     (REG_VO_BASE + 0x428) /* read/write */
#define REG_VO_WB_HSIZE                                     (REG_VO_BASE + 0x42c) /* read/write */
#define REG_VO_WB_WBCH0DMA                                  (REG_VO_BASE + 0x440) /* read/write */
#define REG_VO_WB_WBCH0ERRUNIT                              (REG_VO_BASE + 0x444) /* read/write */
#define REG_VO_WB_WBCH0ERRTH                                (REG_VO_BASE + 0x448) /* read/write */
#define REG_VO_WB_WBCH0INFO                                 (REG_VO_BASE + 0x44c) /* read/write */
#define REG_VO_WB_WBCH0RST                                  (REG_VO_BASE + 0x450) /* read/write */
#define REG_VO_WB_WBCH1DMA                                  (REG_VO_BASE + 0x460) /* read/write */
#define REG_VO_WB_WBCH1ERRUNIT                              (REG_VO_BASE + 0x464) /* read/write */
#define REG_VO_WB_WBCH1ERRTH                                (REG_VO_BASE + 0x468) /* read/write */
#define REG_VO_WB_WBCH1INFO                                 (REG_VO_BASE + 0x46c) /* read/write */
#define REG_VO_WB_WBCH1RST                                  (REG_VO_BASE + 0x470) /* read/write */
#define REG_VO_WB_WBYOUTIDLE                                (REG_VO_BASE + 0x480) /* read */
#define REG_VO_WB_WBUVOUTIDLE                               (REG_VO_BASE + 0x484) /* read */
#define REG_VO_WB_WBYOUTINT                                 (REG_VO_BASE + 0x488) /* read */
#define REG_VO_WB_WBUVOUTINT                                (REG_VO_BASE + 0x48C) /* read */
#define REG_VO_WB_WBYOUTFUNC0                               (REG_VO_BASE + 0x490) /* read */
#define REG_VO_WB_WBYOUTFUNC1                               (REG_VO_BASE + 0x494) /* read */
#define REG_VO_WB_WBUVOUTFUNC0                              (REG_VO_BASE + 0x498) /* read */
#define REG_VO_WB_WBUVOUTFUNC1                              (REG_VO_BASE + 0x49c) /* read */

#define VO_WB_ADDR_Y        (0x02000000)
#include <io.h>
void MS_API_VO_WriteBackSet(unsigned int width, unsigned int height)
{
printf("set vo wb\n");

    //MH_VO_WB_set_DmaCh(0x3);

    writel(0x4, REG_VO_WB_DMAMODE);
    writel(0x7, REG_VO_WB_WBPIXEL);
    writel(VO_WB_ADDR_Y, REG_VO_WB_OUTADDR0DATAY);    
    writel(VO_WB_ADDR_Y, REG_VO_WB_OUTADDR1DATAY);
    writel(VO_WB_ADDR_Y + width*height, REG_VO_WB_OUTADDR0DATAUV);
    writel(VO_WB_ADDR_Y + width*height, REG_VO_WB_OUTADDR1DATAUV);
       
    writel(width, REG_VO_WB_HSTRIDEY);
    
    writel(width, REG_VO_WB_HSTRIDEUV);
    
    writel(0xffffffff, REG_VO_WB_BUFSIZE);
 
    
    writel(width-1, REG_VO_WB_HSIZE);    
   writel(height-1, REG_VO_WB_VSIZE);
        writel(0x10c111, REG_VO_WB_WBCH0DMA);
    
    writel(0x1010101, REG_VO_WB_WBCH0ERRUNIT);
        

    writel(0x1010101, REG_VO_WB_WBCH0ERRTH);
    
    writel(0, REG_VO_WB_WBCH0INFO);
    
    writel(0, REG_VO_WB_WBCH0RST);

    
    writel(0x10c111, REG_VO_WB_WBCH1DMA);
    
    writel(0x1010101, REG_VO_WB_WBCH1ERRUNIT);
    
    writel(0x1010101, REG_VO_WB_WBCH1ERRTH);
    
    writel(0, REG_VO_WB_WBCH1INFO);
    writel(0, REG_VO_WB_WBCH1RST);


    
    writel(0x3, REG_VO_WB_DMACH);


}

/************************************************************************
*VO/BT1120/HDMI Bringup*
*************************************************************************/
static int VO_TEST_BRINGUP_BT1120_GetCtl(VO_CTL_S *voCtl)
{
printf("zxj, VO_TEST_BRINGUP_BT1120_GetCtl enter\n");

    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 640+128;
    dispCtl->total_size.Height = 480+64;
    dispCtl->disp_start.Width = 0x42;
    dispCtl->disp_stop.Width = 0x42 + 640;
    dispCtl->disp_start.Height = 0xb;
    dispCtl->disp_stop.Height = 0xb + 480;

    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
  

    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = 1920;
    layer0Ctl->active_size.Height = 1080;
    layer0Ctl->out_size.Width = 640; //1920
    layer0Ctl->out_size.Height = 480; //1080
    layer0Ctl->ctl_offset.Width = 0x42;//198;
    layer0Ctl->ctl_offset.Height = 0xb;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= 0x01000000;
    layer0Ctl->bufInfo.yAddr1= 0x01000000;
    layer0Ctl->bufInfo.uvAddr0= 0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= 0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.hsize_stride= 0xf;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0;//0;
	layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;

    
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;

    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->osdtype = OSD_RGB_32BIT;
    layer4osd0Ctl->alphatpye = OSD_FIXED_VALUE;
    layer4osd0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer4osd0Ctl->active_size.Width = 128;
    layer4osd0Ctl->active_size.Height = 128;
    layer4osd0Ctl->ctl_offset.Width = 0x42;
    layer4osd0Ctl->ctl_offset.Height = 0xb;
    layer4osd0Ctl->osdBufInfo.alp_addr0= 0x80160000;
    layer4osd0Ctl->osdBufInfo.alp_addr1= 0x80160000;
    layer4osd0Ctl->osdBufInfo.alpstride= 128*4/8;
    layer4osd0Ctl->osdBufInfo.vlu_addr0= 0x80160000;
    layer4osd0Ctl->osdBufInfo.vlu_addr1= 0x80160000;
    layer4osd0Ctl->osdBufInfo.osdstride= 128*4/8;    
    layer4osd0Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer4osd0Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer4osd0Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_B;

    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x80;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = FALSE;
    voCtl->clutctlen = FALSE;


}
#if 0
static int VO_TEST_BRINGUP_BT1120_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;

    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x80;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = FALSE;
    voCtl->clutctlen = FALSE;


}
#endif

/************************************************************************
*VO/DSI/DPHY Bringup*
*************************************************************************/
static int VO_TEST_800x1280_GetCtl(VO_CTL_S *voCtl)
{


    int HACT = 800;
    int HSA = 24;
    int HBP = 24;
    int HFP = 30;

    int VACT = 1280;
    int VSA = 4;
    int VBP = 12;
    int VFP = 12;
    int VOFF=1;
    int HOFF=0;


    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0,sizeof(voCtl));

    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1080x1920x30P;
#if 0
    dispCtl->total_size.Width = 960 ;//1060  ;//1061 ;//1340;  1125            1264
    dispCtl->total_size.Height =1298 + 5 ;// 1319;//1958;//1938???  2200

    dispCtl->disp_start.Width = (5+20+20+1);  // 46
    dispCtl->disp_stop.Width = 800 +(5+20+20+1) ;

    dispCtl->disp_start.Height = (5+8+1);   //14
    dispCtl->disp_stop.Height = 1280 + (5+8+1);  // 1958 - 1920 - 14 = 24
#else
    dispCtl->total_size.Width = HACT+HSA+HBP+HFP;
    dispCtl->total_size.Height = VACT+VSA+VBP+VFP;
    dispCtl->disp_start.Width = HSA+HBP+HOFF;
    dispCtl->disp_stop.Width = HACT+HSA+HBP+HOFF;
    dispCtl->disp_start.Height = VSA+VBP+VOFF;
    dispCtl->disp_stop.Height = VACT+VSA+VBP+VOFF;
#endif
#if 1
    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;                                //TRUE  zhaoshuai  use picture true or  full red  FALSE
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;       //VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = 1080;//1920;
    layer0Ctl->active_size.Height = 1920;//1080;
    layer0Ctl->out_size.Width = 1080; //1920
    layer0Ctl->out_size.Height = 1920; //1080
    layer0Ctl->ctl_offset.Width = 46;//198;
    layer0Ctl->ctl_offset.Height = 14;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    
    layer0Ctl->layerMix_glbalp = 0xff;

    layer0Ctl->bufInfo.yAddr0= 0x01000000;
    layer0Ctl->bufInfo.yAddr1= 0x01000000;
    layer0Ctl->bufInfo.uvAddr0= 0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= 0x01000000 + 1920*1080;

    layer0Ctl->bufInfo.hsize_stride= 1080/8 -1;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 1920;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
#else
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width =1080;//1920;
    layer0Ctl->active_size.Height = 720;//1080;
    layer0Ctl->out_size.Width = 1080;//1080; //1920
    layer0Ctl->out_size.Height = 720;//1920; //1080
    layer0Ctl->ctl_offset.Width = 46;//198;
    layer0Ctl->ctl_offset.Height = 14;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= ISP_BUF_MAIN_Y;//0x01000000;
    layer0Ctl->bufInfo.yAddr1= ISP_BUF_MAIN_Y;//0x01000000;
    layer0Ctl->bufInfo.uvAddr0= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.hsize_stride= ISP_BUF_MAIN_Y_STRIDE/8 -1;//1080/8 -1;//1080/8 -1;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 1920;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
#endif
/*
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width =1080;//1920;
    layer0Ctl->active_size.Height = 720;//1080;
    layer0Ctl->out_size.Width = 1080;//1080; //1920
    layer0Ctl->out_size.Height = 720;//1920; //1080
    layer0Ctl->ctl_offset.Width = 46;//198;
    layer0Ctl->ctl_offset.Height = 14;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= 0x01000000;
    layer0Ctl->bufInfo.yAddr1= 0x01000000;//0x01000000;
    layer0Ctl->bufInfo.uvAddr0= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.hsize_stride= 1080/8 -1;//1080/8 -1;//1080/8 -1;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 1920;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
*/
   

    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = TRUE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->osdtype = OSD_RGB_32BIT;//OSD_MONOCHROME_8BIT;
    layer4osd0Ctl->alphatpye = OSD_FIXED_VALUE;
    layer4osd0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer4osd0Ctl->active_size.Width = 640;
    layer4osd0Ctl->active_size.Height = 480;
    layer4osd0Ctl->ctl_offset.Width = dispCtl->disp_start.Width + 80;//80 + 46;
    layer4osd0Ctl->ctl_offset.Height = 400;
    layer4osd0Ctl->osdBufInfo.alp_addr0= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.alp_addr1= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.alpstride= 2560/8;
    layer4osd0Ctl->osdBufInfo.vlu_addr0= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.vlu_addr1= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.osdstride= 2560/8;
    layer4osd0Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer4osd0Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer4osd0Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer5osd1Ctl->alphatpye = OSD_FIXED_VALUE;
    layer5osd1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer5osd1Ctl->active_size.Width = 216;
    layer5osd1Ctl->active_size.Height = 960;
    layer5osd1Ctl->ctl_offset.Width = 800;
    layer5osd1Ctl->ctl_offset.Height = 200;
    layer5osd1Ctl->osdBufInfo.alp_addr0= 0x20200100;
    layer5osd1Ctl->osdBufInfo.alp_addr1= 0x20200100;
    layer5osd1Ctl->osdBufInfo.alpstride= 256/8;
    layer5osd1Ctl->osdBufInfo.vlu_addr0= 0x20200100;
    layer5osd1Ctl->osdBufInfo.vlu_addr1= 0x20200100;
    layer5osd1Ctl->osdBufInfo.osdstride= 256/8;
    layer5osd1Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer5osd1Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer5osd1Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0xff;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
}

/************************************************************************
*VO/DSI/DPHY Bringup*
*************************************************************************/
static int VO_TEST_BRINGUP_DSI_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1080x1920x30P;
#if 1
    dispCtl->total_size.Width = 1254;//1340;  1125 
    dispCtl->total_size.Height = 1958;//1958;//1938???  2200
    dispCtl->disp_start.Width = 20 + 20;
    dispCtl->disp_stop.Width = 1080 + 20 + 20;
    dispCtl->disp_start.Height = (5+8+1);   //14
    dispCtl->disp_stop.Height = 1920 + (5+8+1);  // 1958 - 1920 - 14 = 24
#else
    dispCtl->total_size.Width = 1125 ;//1340;  1125 
    dispCtl->total_size.Height = 2200;//1958;//1938???  2200
    dispCtl->disp_start.Width = (5+20+20+1);
    dispCtl->disp_stop.Width = 1080 +(5+20+20+1);
    dispCtl->disp_start.Height = (5+8+1);
    dispCtl->disp_stop.Height = 1920 + (5+8+1);
#endif
#if 1
    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;                                //TRUE  zhaoshuai  use picture true or  full red  FALSE
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;       //VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = 1080;//1920;
    layer0Ctl->active_size.Height = 1920;//1080;
    layer0Ctl->out_size.Width = 1080; //1920
    layer0Ctl->out_size.Height = 1920; //1080
    layer0Ctl->ctl_offset.Width = 46;//198;
    layer0Ctl->ctl_offset.Height = 14;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    
    layer0Ctl->layerMix_glbalp = 0xff;

    layer0Ctl->bufInfo.yAddr0= 0x01000000;
    layer0Ctl->bufInfo.yAddr1= 0x01000000;
    layer0Ctl->bufInfo.uvAddr0= 0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= 0x01000000 + 1920*1080;

    layer0Ctl->bufInfo.hsize_stride= 1080/8 -1;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 1920;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
#else
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width =1080;//1920;
    layer0Ctl->active_size.Height = 720;//1080;
    layer0Ctl->out_size.Width = 1080;//1080; //1920
    layer0Ctl->out_size.Height = 720;//1920; //1080
    layer0Ctl->ctl_offset.Width = 46;//198;
    layer0Ctl->ctl_offset.Height = 14;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= ISP_BUF_MAIN_Y;//0x01000000;
    layer0Ctl->bufInfo.yAddr1= ISP_BUF_MAIN_Y;//0x01000000;
    layer0Ctl->bufInfo.uvAddr0= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.hsize_stride= ISP_BUF_MAIN_Y_STRIDE/8 -1;//1080/8 -1;//1080/8 -1;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 1920;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
#endif
/*
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width =1080;//1920;
    layer0Ctl->active_size.Height = 720;//1080;
    layer0Ctl->out_size.Width = 1080;//1080; //1920
    layer0Ctl->out_size.Height = 720;//1920; //1080
    layer0Ctl->ctl_offset.Width = 46;//198;
    layer0Ctl->ctl_offset.Height = 14;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= 0x01000000;
    layer0Ctl->bufInfo.yAddr1= 0x01000000;//0x01000000;
    layer0Ctl->bufInfo.uvAddr0= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.uvAddr1= ISP_BUF_MAIN_UV;//0x01000000 + 1920*1080;
    layer0Ctl->bufInfo.hsize_stride= 1080/8 -1;//1080/8 -1;//1080/8 -1;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 1920;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
*/
   

    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = TRUE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->osdtype = OSD_RGB_32BIT;//OSD_MONOCHROME_8BIT;
    layer4osd0Ctl->alphatpye = OSD_FIXED_VALUE;
    layer4osd0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer4osd0Ctl->active_size.Width = 640;
    layer4osd0Ctl->active_size.Height = 480;
    layer4osd0Ctl->ctl_offset.Width = 220 + 46;
    layer4osd0Ctl->ctl_offset.Height = 720;
    layer4osd0Ctl->osdBufInfo.alp_addr0= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.alp_addr1= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.alpstride= 2560/8;
    layer4osd0Ctl->osdBufInfo.vlu_addr0= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.vlu_addr1= 0x1fe00000;
    layer4osd0Ctl->osdBufInfo.osdstride= 2560/8;
    layer4osd0Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer4osd0Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer4osd0Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer5osd1Ctl->alphatpye = OSD_FIXED_VALUE;
    layer5osd1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer5osd1Ctl->active_size.Width = 216;
    layer5osd1Ctl->active_size.Height = 960;
    layer5osd1Ctl->ctl_offset.Width = 800;
    layer5osd1Ctl->ctl_offset.Height = 200;
    layer5osd1Ctl->osdBufInfo.alp_addr0= 0x20200100;
    layer5osd1Ctl->osdBufInfo.alp_addr1= 0x20200100;
    layer5osd1Ctl->osdBufInfo.alpstride= 256/8;
    layer5osd1Ctl->osdBufInfo.vlu_addr0= 0x20200100;
    layer5osd1Ctl->osdBufInfo.vlu_addr1= 0x20200100;
    layer5osd1Ctl->osdBufInfo.osdstride= 256/8;
    layer5osd1Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer5osd1Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer5osd1Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0xff;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
}

/************************************************************************
*IRS238C*
*************************************************************************/
static int VO_TEST_IRS238C_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;

    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = TRUE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer4osd0Ctl->alphatpye = OSD_FIXED_VALUE;
    layer4osd0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer4osd0Ctl->active_size.Width = 216;
    layer4osd0Ctl->active_size.Height = 172;
    layer4osd0Ctl->ctl_offset.Width = 400;
    layer4osd0Ctl->ctl_offset.Height = 200;
    layer4osd0Ctl->osdBufInfo.alp_addr0= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.alp_addr1= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.alpstride= 256/8;
    layer4osd0Ctl->osdBufInfo.vlu_addr0= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.vlu_addr1= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.osdstride= 256/8;
    layer4osd0Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer4osd0Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer4osd0Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = TRUE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer5osd1Ctl->alphatpye = OSD_FIXED_VALUE;
    layer5osd1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer5osd1Ctl->active_size.Width = 216;
    layer5osd1Ctl->active_size.Height = 172;
    layer5osd1Ctl->ctl_offset.Width = 800;
    layer5osd1Ctl->ctl_offset.Height = 200;
    layer5osd1Ctl->osdBufInfo.alp_addr0= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.alp_addr1= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.alpstride= 256/8;
    layer5osd1Ctl->osdBufInfo.vlu_addr0= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.vlu_addr1= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.osdstride= 256/8;
    layer5osd1Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer5osd1Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer5osd1Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0xff;
    dispBackGroudInfo->v = 0x00;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/************************************************************************
*LAYER0*
*************************************************************************/
static int VO_TEST_LAYER0_1920x1080_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x437;//0;
	layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = FALSE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = FALSE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = FALSE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = FALSE;
    layer4osd0Ctl->layerMix_en = FALSE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = FALSE;
    layer5osd1Ctl->layerMix_en = FALSE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = FALSE;
    layer6osd2Ctl->layerMix_en = FALSE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/*
 *
 */
static int VO_TEST_LAYER0_1280x720_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = 1280;//VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = 720;//VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = 1280;//VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = 720;//VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x437;//0;
	layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = FALSE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = FALSE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = FALSE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = FALSE;
    layer4osd0Ctl->layerMix_en = FALSE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = FALSE;
    layer5osd1Ctl->layerMix_en = FALSE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = FALSE;
    layer6osd2Ctl->layerMix_en = FALSE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/*
*
*/
static int VO_TEST_LAYER0_IRS238C_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = 1280;//VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = 720;//VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = 1280;//VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = 720;//VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0;
	layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = FALSE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = FALSE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = FALSE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = TRUE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer4osd0Ctl->alphatpye = OSD_FIXED_VALUE;
    layer4osd0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer4osd0Ctl->active_size.Width = 216;
    layer4osd0Ctl->active_size.Height = 172;
    layer4osd0Ctl->ctl_offset.Width = 1280 + 200;
    layer4osd0Ctl->ctl_offset.Height = 200;
    layer4osd0Ctl->osdBufInfo.alp_addr0= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.alp_addr1= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.alpstride= 256/8;
    layer4osd0Ctl->osdBufInfo.vlu_addr0= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.vlu_addr1= TOF_BUF_DEPTH + 0x100;//0x20000100;
    layer4osd0Ctl->osdBufInfo.osdstride= 256/8;
    layer4osd0Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer4osd0Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer4osd0Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = TRUE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer5osd1Ctl->alphatpye = OSD_FIXED_VALUE;
    layer5osd1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer5osd1Ctl->active_size.Width = 216;
    layer5osd1Ctl->active_size.Height = 172;
    layer5osd1Ctl->ctl_offset.Width = 1280 + 200;//800;
    layer5osd1Ctl->ctl_offset.Height = 500;//200;
    layer5osd1Ctl->osdBufInfo.alp_addr0= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.alp_addr1= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.alpstride= 256/8;
    layer5osd1Ctl->osdBufInfo.vlu_addr0= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.vlu_addr1= TOF_BUF_GRAY + 0x100;//0x20200100;
    layer5osd1Ctl->osdBufInfo.osdstride= 256/8;
    layer5osd1Ctl->osdDmaInfo.dmarequestlen = 0xf;
    layer5osd1Ctl->osdDmaInfo.dmamap = OSD_ORIGINAL_ORDER;
    layer5osd1Ctl->osdDmaInfo.rgbrev = OSD_RGB_REV_R;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = FALSE;
    layer6osd2Ctl->layerMix_en = FALSE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0xff;
    dispBackGroudInfo->v = 0x00;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/*
*
*/
static int VO_TEST_LAYER0_1920x1080_YUV420_1280x720_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = 1280;// VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = 720;//VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x437;//0; 
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
//
    return 0;
}
/*
*
*/
static int VO_TEST_LAYER0_MFBD_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = TRUE;//FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//TRUE;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x437;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/************************************************************************
*LAYER1_1920x1080_YUV420*
*************************************************************************/
/*
*
*/
static int VO_TEST_LAYER1_1920x1080_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->layerMix_en = FALSE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = TRUE;
    layer1Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer1Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer1Ctl->uvswap = TRUE;
    layer1Ctl->active_size.Width = 1920;
    layer1Ctl->active_size.Height = 1080;
    layer1Ctl->ctl_offset.Width = 198;
    layer1Ctl->ctl_offset.Height = 42;
    layer1Ctl->size_offset.Width = 0x0;
    layer1Ctl->size_offset.Height = 0x0;
    layer1Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer1Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer1Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer1Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer1Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer1Ctl->bufInfo.vsize_stride= 0x437;//0;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    layer2Ctl->layerMix_en = FALSE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = FALSE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = FALSE;
    layer4osd0Ctl->layerMix_en = FALSE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = FALSE;
    layer5osd1Ctl->layerMix_en = FALSE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = FALSE;
    layer6osd2Ctl->layerMix_en = FALSE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;//TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/************************************************************************
*LAYER2_1920x1080_YUV420*
*************************************************************************/
/*
*
*/
static int VO_TEST_LAYER2_1920x1080_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE; 
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = TRUE;
    layer2Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer2Ctl->uvswap = FALSE;//TRUE;
    layer2Ctl->active_size.Width = 1920;
    layer2Ctl->active_size.Height = 1080;
    layer2Ctl->ctl_offset.Width = 198;
    layer2Ctl->ctl_offset.Height = 42;
    layer2Ctl->size_offset.Width = 0x0;
    layer2Ctl->size_offset.Height = 0x0;
    layer2Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer2Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer2Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer2Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer2Ctl->bufInfo.hsize_stride= 0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer2Ctl->bufInfo.vsize_stride= 0x437;//0;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE; 
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    // 
    voCtl->yuv2rgb_ctl_en = TRUE;//FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
    return 0;
}
/************************************************************************
*LAYER2_DS0_1080x720_YUV420*
*************************************************************************/
/*
*
*/
static int VO_TEST_LAYER2_DS0_1080x720_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1280x720x30P;//VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0xce4;//0x898;
    dispCtl->total_size.Height = 0x2ee;//0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = TRUE;
    layer2Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer2Ctl->uvswap = TRUE;
    layer2Ctl->active_size.Width = 1280;//1920;
    layer2Ctl->active_size.Height = 720;//1080;
    layer2Ctl->ctl_offset.Width = 198;
    layer2Ctl->ctl_offset.Height = 42;
    layer2Ctl->size_offset.Width = 0x0;
    layer2Ctl->size_offset.Height = 0x0;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;

    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
    return 0;
}
/************************************************************************
*LAYER_420_DS_OUT_ALL_YUV420*
*************************************************************************/
/*
*
*/
static int VO_TEST_LAYER_420_DS_OUT_ALL_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //layer0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->uvswap = TRUE;//FALSE;
    layer0Ctl->active_size.Width = 1920;
    layer0Ctl->active_size.Height = 1080;
    layer0Ctl->out_size.Width = 1920;
    layer0Ctl->out_size.Height = 1080;
    layer0Ctl->ctl_offset.Width = 198;
    layer0Ctl->ctl_offset.Height = 42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr1;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr1;
    layer0Ctl->bufInfo.hsize_stride= 0xff;//2048;VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x437;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //layer1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = TRUE;
    layer1Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer1Ctl->endianuv = VO_VIDEO_LAYER_Y_ENDIAN_MODE2;
    layer1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer1Ctl->uvswap = FALSE;//TRUE;
    layer1Ctl->active_size.Width = 320;//1920;
    layer1Ctl->active_size.Height = 240;//1080;
    layer1Ctl->ctl_offset.Width = 198 + 1400;
    layer1Ctl->ctl_offset.Height = 100;
    layer1Ctl->size_offset.Width = 0x0;
    layer1Ctl->size_offset.Height = 0x0;
    layer1Ctl->bufInfo.yAddr0= LAYER1_Y_BASEAddr0;
    layer1Ctl->bufInfo.yAddr1= LAYER1_Y_BASEAddr0;
    layer1Ctl->bufInfo.uvAddr0= LAYER1_UV_BASEaddr0;
    layer1Ctl->bufInfo.uvAddr1= LAYER1_UV_BASEaddr0;
    layer1Ctl->bufInfo.hsize_stride= VIDEO_LAYER2_RD_STRIDE/8-1;//0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer1Ctl->bufInfo.vsize_stride= 0xef;//0;//0x437;//0; 
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //layer2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = TRUE;
    layer2Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer2Ctl->uvswap = FALSE;//TRUE;
    layer2Ctl->active_size.Width = 320;//1920;
    layer2Ctl->active_size.Height = 240;//1080;
    layer2Ctl->ctl_offset.Width = 198 + 1400;
    layer2Ctl->ctl_offset.Height = 500;
    layer2Ctl->size_offset.Width = 0x0;
    layer2Ctl->size_offset.Height = 0x0;
    layer2Ctl->bufInfo.yAddr0= LAYER2_Y_BASEAddr0;
    layer2Ctl->bufInfo.yAddr1= LAYER2_Y_BASEAddr0;
    layer2Ctl->bufInfo.uvAddr0= LAYER2_UV_BASEaddr0;
    layer2Ctl->bufInfo.uvAddr1= LAYER2_UV_BASEaddr0;
    layer2Ctl->bufInfo.hsize_stride= VIDEO_LAYER2_RD_STRIDE/8-1;//2048;//0xff;//;
    layer2Ctl->bufInfo.vsize_stride= 0xef;//0;//0x437;//0;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //layer3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = TRUE;
    layer3Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer3Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer3Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer3Ctl->uvswap = FALSE;//TRUE;
    layer3Ctl->active_size.Width = 320;//1920;
    layer3Ctl->active_size.Height = 240;//1080;
    layer3Ctl->ctl_offset.Width = 198;
    layer3Ctl->ctl_offset.Height = 42;
    layer3Ctl->size_offset.Width = 0x0;
    layer3Ctl->size_offset.Height = 0x0;
    layer3Ctl->bufInfo.yAddr0= 0x22000000;//LAYER2_Y_BASEAddr0;
    layer3Ctl->bufInfo.yAddr1= 0x22000000;//LAYER2_Y_BASEAddr0;
    layer3Ctl->bufInfo.uvAddr0= 0x22400000;//LAYER2_UV_BASEaddr0;
    layer3Ctl->bufInfo.uvAddr1= 0x22400000;//LAYER2_UV_BASEaddr0;
    layer3Ctl->bufInfo.hsize_stride= 0xff;//2048;//0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer3Ctl->bufInfo.vsize_stride= 0xef;//0;//0x437;//0; 
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
    return 0;
}
/************************************************************************
*ALL_LAYERS*
*************************************************************************/
static int VO_TEST_LAYER_420_DS_FRAME_DRAW_YUV420_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//TRUE;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr1;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr1;
    layer0Ctl->bufInfo.hsize_stride= 2048;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x0;//0;
    layer0Ctl->layerMix_en = TRUE;
    layer0Ctl->layerMix_glbalp = 0xff;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = TRUE;
    layer1Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer1Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer1Ctl->uvswap = TRUE;
    layer1Ctl->active_size.Width = 320;
    layer1Ctl->active_size.Height = 240;
    layer1Ctl->ctl_offset.Width = 198;
    layer1Ctl->ctl_offset.Height = 800;
    layer1Ctl->size_offset.Width = 0x0;
    layer1Ctl->size_offset.Height = 0x0;
    layer1Ctl->bufInfo.yAddr0= LAYER1_Y_BASEAddr0;
    layer1Ctl->bufInfo.yAddr1= LAYER1_Y_BASEAddr0;
    layer1Ctl->bufInfo.uvAddr0= LAYER1_UV_BASEaddr0;
    layer1Ctl->bufInfo.uvAddr1= LAYER1_UV_BASEaddr0;
    layer1Ctl->bufInfo.hsize_stride= 2048;//VIDEO_LAYER2_RD_STRIDE;
    layer1Ctl->bufInfo.vsize_stride= 0x0;//0;
    layer1Ctl->layerMix_en = TRUE;
    layer1Ctl->layerMix_glbalp = 0xff;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = TRUE;
    layer2Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer2Ctl->uvswap = TRUE;
    layer2Ctl->active_size.Width = 320;
    layer2Ctl->active_size.Height = 240;
    layer2Ctl->ctl_offset.Width = 1100;
    layer2Ctl->ctl_offset.Height = 800;
    layer2Ctl->size_offset.Width = 0x0;
    layer2Ctl->size_offset.Height = 0x0;
    layer2Ctl->bufInfo.yAddr0= LAYER2_Y_BASEAddr0;
    layer2Ctl->bufInfo.yAddr1= LAYER2_Y_BASEAddr0;
    layer2Ctl->bufInfo.uvAddr0= LAYER2_UV_BASEaddr0;
    layer2Ctl->bufInfo.uvAddr1= LAYER2_UV_BASEaddr0;
    layer2Ctl->bufInfo.hsize_stride= 2048;//VIDEO_LAYER2_RD_STRIDE;
    layer2Ctl->bufInfo.vsize_stride= 0x0;//0;
    layer2Ctl->layerMix_en = TRUE;
    layer2Ctl->layerMix_glbalp = 0xff;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    layer3Ctl->layerMix_en = TRUE;
    layer3Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->layerMix_en = TRUE;
    layer4osd0Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    layer5osd1Ctl->osdrgb2yuvEn = TRUE;
    layer5osd1Ctl->layerMix_en = TRUE;
    layer5osd1Ctl->layerMix_glbalp = 0xff;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    layer6osd2Ctl->osdrgb2yuvEn = TRUE;
    layer6osd2Ctl->layerMix_en = TRUE;
    layer6osd2Ctl->layerMix_glbalp = 0xff;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x00;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = FALSE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;

    return 0;
}
/************************************************************************
**
*************************************************************************/
static int VO_Test_Layer0_1080P_IN_1080P_OUT_BT1120_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = FALSE;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = TRUE;
    layer2Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE3;
    layer2Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer2Ctl->uvswap = TRUE;
    layer2Ctl->active_size.Width = 1920;
    layer2Ctl->active_size.Height = 1080;
    layer2Ctl->ctl_offset.Width = 198;
    layer2Ctl->ctl_offset.Height = 42;
    layer2Ctl->size_offset.Width = 0x0;
    layer2Ctl->size_offset.Height = 0x0;
    layer2Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer2Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr0;
    layer2Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer2Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr0;
    layer2Ctl->bufInfo.hsize_stride= 2048;//0xff;//VIDEO_LAYER2_RD_STRIDE;
    layer2Ctl->bufInfo.vsize_stride= 0x0;//0x437;//0;  
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = TRUE;
    layer4osd0Ctl->osdrgb2yuvEn = TRUE;
    layer4osd0Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer4osd0Ctl->alphatpye = OSD_FIXED_VALUE;
    layer4osd0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer4osd0Ctl->active_size.Width = 320;
    layer4osd0Ctl->active_size.Height = 240;
    layer4osd0Ctl->ctl_offset.Width = 400;
    layer4osd0Ctl->ctl_offset.Height = 200;
    layer4osd0Ctl->osdBufInfo.alp_addr0= 0x20000000;
    layer4osd0Ctl->osdBufInfo.alp_addr1= 0x20000000;
    layer4osd0Ctl->osdBufInfo.alpstride= 2048/8;
    layer4osd0Ctl->osdBufInfo.vlu_addr0= 0x20000000;
    layer4osd0Ctl->osdBufInfo.vlu_addr1= 0x20000000;
    layer4osd0Ctl->osdBufInfo.osdstride= 2048/8;
    //
    VO_LAYER_OSD_CTL_INFO_S   *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = TRUE;
    layer5osd1Ctl->osdrgb2yuvEn = FALSE;
    layer5osd1Ctl->osdtype = OSD_MONOCHROME_8BIT;
    layer5osd1Ctl->alphatpye = OSD_FIXED_VALUE;
    layer5osd1Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer5osd1Ctl->active_size.Width = 216;
    layer5osd1Ctl->active_size.Height = 172;
    layer5osd1Ctl->ctl_offset.Width = 800;
    layer5osd1Ctl->ctl_offset.Height = 200;
    layer5osd1Ctl->osdBufInfo.alp_addr0= 0x20200000;
    layer5osd1Ctl->osdBufInfo.alp_addr1= 0x20200000;
    layer5osd1Ctl->osdBufInfo.alpstride= 2048/8;
    layer5osd1Ctl->osdBufInfo.vlu_addr0= 0x20200000;
    layer5osd1Ctl->osdBufInfo.vlu_addr1= 0x20200000;
    layer5osd1Ctl->osdBufInfo.osdstride= 2048/8;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0x80;
    dispBackGroudInfo->u = 0x80;
    dispBackGroudInfo->v = 0x80;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;
    return 0; 
}
/************************************************************************
**
*************************************************************************/
static int VO_TestLayer0_1080x1920_DSI_LINE_DRAW_GetCtl(VO_CTL_S *voCtl)
{
    VO_CHECK_POINTER(voCtl);
    memset(voCtl,0x0,sizeof(voCtl));
    //
    VO_DISP_CTL_INFO_S *dispCtl= &voCtl->dispCtl;
    dispCtl->Disp_en = TRUE;
    dispCtl->SyncMode = VO_SYSTEM_MODE_1920x1080x30P;
    dispCtl->total_size.Width = 0x898;
    dispCtl->total_size.Height = 0x465;
    dispCtl->disp_start.Width = 46;//VIDEO_DISP_ZONE_X_START;
    dispCtl->disp_stop.Width = 46 + 1080;//VIDEO_DISP_ZONE_X_STOP;
    dispCtl->disp_start.Height = 14;//VIDEO_DISP_ZONE_Y_START;
    dispCtl->disp_stop.Height = 14 + 1920;//VIDEO_DISP_ZONE_Y_STOP;
    //
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    layer0Ctl->layer_en = TRUE;
    layer0Ctl->layer0_mfbd_en = FALSE;
    layer0Ctl->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer0Ctl->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE3
    layer0Ctl->uvswap = FALSE;//TRUE;
    layer0Ctl->ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
    layer0Ctl->active_size.Width = 1080;//VIDEO_LAYER0_H_IN_SIZE;//1920;
    layer0Ctl->active_size.Height = 1920;//VIDEO_LAYER0_V_IN_SIZE;//1080;
    layer0Ctl->out_size.Width = 1080;//VIDEO_LAYER0_H_OUT_SIZE; //1920
    layer0Ctl->out_size.Height = 1920;//VIDEO_LAYER0_V_OUT_SIZE; //1080
    layer0Ctl->ctl_offset.Width = 46;//VIDEO_LAYER0_H_POSITION;//198;
    layer0Ctl->ctl_offset.Height = 14;//VIDEO_LAYER0_V_POSITION;//42;
    layer0Ctl->size_offset.Width = 0x0;
    layer0Ctl->size_offset.Height = 0x0;
    layer0Ctl->bufInfo.yAddr0= LAYER0_Y_BASEAddr0;
    layer0Ctl->bufInfo.yAddr1= LAYER0_Y_BASEAddr1;
    layer0Ctl->bufInfo.uvAddr0= LAYER0_UV_BASEaddr0;
    layer0Ctl->bufInfo.uvAddr1= LAYER0_UV_BASEaddr1;
    layer0Ctl->bufInfo.hsize_stride= 1080;//VIDEO_LAYER2_RD_STRIDE;
    layer0Ctl->bufInfo.vsize_stride= 0x0;//0;
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    layer1Ctl->layer_en = FALSE;
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    layer2Ctl->layer_en = FALSE;
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    layer3Ctl->layer_en = FALSE;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    layer4osd0Ctl->layer_en = FALSE;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    layer5osd1Ctl->layer_en = FALSE;
    //
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl = &voCtl->layer6osd2Ctl;
    layer6osd2Ctl->layer_en = FALSE;
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &voCtl->dispBackGroudInfo;
    dispBackGroudInfo->y = 0xff;
    dispBackGroudInfo->u = 0xff;
    dispBackGroudInfo->v = 0xff;
    //
    voCtl->yuv2rgb_ctl_en = TRUE;
    voCtl->ditherctlen = TRUE;
    voCtl->clutctlen = FALSE;    
    return 0;
}
/************************************************************************
*ALL_LAYERS*
*************************************************************************/
/*
*
*/
static int VO_TEST_ALL_LAYERS(VO_CTL_S *voCtl,VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(voCtl);
    VO_CHECK_POINTER(voCoreInfo);

    memset(voCoreInfo,0x0,sizeof(voCoreInfo));

    VO_DISP_MIX_INFO_S  *dispMixCtlInfo = &voCoreInfo->dispMixCtlInfo;
    //
    //unsigned int disp_En = TRUE;
    VO_DISP_CTL_INFO_S  *dispCtl = &voCtl->dispCtl;
    VO_DISP_INFO_S *dispInfo = &voCoreInfo->dispInfo;
    VO_TEST_SetDisp(dispCtl,dispInfo);
    //LAYER0
    VO_LAYER_CTL_INFO_S *layer0Ctl = &voCtl->layer0Ctl;
    VO_LAYER0_INFO_S *layer0Info = &voCoreInfo->layer0Info;
    VO_MIX_INFO_S *layer0MixInfo = &dispMixCtlInfo->layerMixInfo[0];
    VO_TEST_SetLayer0(layer0Ctl,layer0Info,layer0MixInfo);
    //LAYER1
    VO_LAYER_CTL_INFO_S *layer1Ctl = &voCtl->layer1Ctl;
    VO_LAYER1_INFO_S *layer1Info = &voCoreInfo->layer1Info;
    VO_MIX_INFO_S *layer1MixInfo = &dispMixCtlInfo->layerMixInfo[1];
    VO_TEST_SetLayer1(layer1Ctl,layer1Info,layer1MixInfo);
    //LAYER2
    VO_LAYER_CTL_INFO_S *layer2Ctl = &voCtl->layer2Ctl;
    VO_LAYER2_INFO_S *layer2Info = &voCoreInfo->layer2Info;
    VO_MIX_INFO_S *layer2MixInfo = &dispMixCtlInfo->layerMixInfo[2];
    VO_TEST_SetLayer2(layer2Ctl,layer2Info,layer2MixInfo);
    //LAYER3
    VO_LAYER_CTL_INFO_S *layer3Ctl = &voCtl->layer3Ctl;
    VO_LAYER3_INFO_S *layer3Info = &voCoreInfo->layer3Info;
    VO_MIX_INFO_S *layer3MixInfo = &dispMixCtlInfo->layerMixInfo[3];
    VO_TEST_SetLayer3(layer3Ctl,layer3Info,layer3MixInfo);
    //LAYER4OSD0
    VO_LAYER_OSD_CTL_INFO_S *layer4osd0Ctl = &voCtl->layer4osd0Ctl;
    VO_OSD0_INFO_S *osd0Info = &voCoreInfo->osd0Info;
    VO_MIX_INFO_S *layer4osd0MixInfo = &dispMixCtlInfo->layerMixInfo[4];
    VO_TEST_SetLayer4Osd0(layer4osd0Ctl,osd0Info,layer4osd0MixInfo);
    //LAYER5OSD1
    VO_LAYER_OSD_CTL_INFO_S *layer5osd1Ctl = &voCtl->layer5osd1Ctl;
    VO_OSD1_INFO_S *osd1Info = &voCoreInfo->osd1Info;
    VO_MIX_INFO_S *layer5osd1MixInfo = &dispMixCtlInfo->layerMixInfo[5];
    VO_TEST_SetLayer5Osd1(layer5osd1Ctl,osd1Info,layer5osd1MixInfo);
    //LAYER6OSD2
    VO_LAYER_OSD_CTL_INFO_S *layer6osd2Ctl= &voCtl->layer6osd2Ctl;
    VO_OSD2_INFO_S *osd2Info = &voCoreInfo->osd2Info;
    VO_MIX_INFO_S *layer6osd2MixInfo = &dispMixCtlInfo->layerMixInfo[6];
    VO_TEST_SetLayer6Osd2(layer6osd2Ctl,osd2Info,layer6osd2MixInfo);
    //
    unsigned int yuv2rgb_ctl_en = voCtl->yuv2rgb_ctl_en;//FALSE;
    VO_YUV2RGB_INFO_S *yuv2rgbInfo  = &voCoreInfo->yuv2rgbInfo;
    VO_TEST_SetYuv2RgbInfo(yuv2rgb_ctl_en,yuv2rgbInfo);
    //
    VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo = &voCoreInfo->osdRgb2YuvInfo;
    VO_TEST_SetOsdRgb2YuvInfo(osdRgb2YuvInfo);
    //
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &dispMixCtlInfo->dispBackGroudInfo;
    dispBackGroudInfo->y = voCtl->dispBackGroudInfo.y;//0x00;
    dispBackGroudInfo->u = voCtl->dispBackGroudInfo.u;//0xff;//0x80;
    dispBackGroudInfo->v = voCtl->dispBackGroudInfo.v;//0x00;//0x80;
    //
    voCoreInfo->ditherctlen = voCtl->ditherctlen ;//TRUE;
    voCoreInfo->clutctlen = voCtl->clutctlen ;//FALSE; //gamma
    //
    VO_WB_Y_INFO_S *wbInfo= &voCoreInfo->wbInfo;

    return 0;
}
/************************************************************************
**
*************************************************************************/
static int VO_TEST_Core(VO_TEST_CASE_E voTestCase,VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(voCoreInfo);
    //printf("zhudalei:VO_TEST_Core start!!!\n");
    VO_CTL_S voCtl;
    switch(voTestCase)
    {
        case VO_BT1120_HDMI_BRINGUP:
            //use background only to bringup VO/BT1120/HDMI path
			//Need poweron bt1120 daughter board?
            VO_TEST_BRINGUP_BT1120_GetCtl(&voCtl);
            break;
        case VO_DSI_MIPI_BRINGUP:
            //use background only to bringup VO/DSI/DPHY.
            //aml550_power_on_seq();

            VO_TEST_BRINGUP_DSI_GetCtl(&voCtl);
            break;
        case VO_DSI_MIPI_800x1280 :

            VO_TEST_800x1280_GetCtl(&voCtl);
            break;
        case LAYER0_420_IRS238C:
            VO_TEST_IRS238C_GetCtl(&voCtl);
           // VO_TEST_IRS238C(&voCtl,voCoreInfo);
            break;            
        case VO_CASE_LAYER0_420_1920x1080_1920x1080_ENDIAN:
            VO_TEST_LAYER0_1920x1080_YUV420_GetCtl(&voCtl);
            //VO_TEST_LAYER0_1920x1080(&voCtl,voCoreInfo);
            break;
        case LAYER0_420_1920x1080_1280x720_YUV420:
            VO_TEST_LAYER0_1920x1080_YUV420_1280x720_GetCtl(&voCtl);
            //VO_TEST_LAYER0_1920x1080(&voCtl,voCoreInfo);
            break;
        case LAYER1_420_1920x1080_YUV420:
            VO_TEST_LAYER1_1920x1080_YUV420_GetCtl(&voCtl);
            //VO_TEST_LAYER1_1920x1080(&voCtl,voCoreInfo);
            break;
        case LAYER2_420_1920x1080_YUV420:
            //ImgInDataMode = VO_VIDEO_LAYER_YUV_MODE_420;
            VO_TEST_LAYER2_1920x1080_YUV420_GetCtl(&voCtl);
            //VO_TEST_LAYER2_1920x1080(&voCtl,voCoreInfo);
            break;
        case LAYER2_420_DS0_1080x720_YUV420:
            VO_TEST_LAYER2_DS0_1080x720_YUV420_GetCtl(&voCtl);
            //VO_TEST_LAYER2_DS0_1080x720(&voCtl,voCoreInfo);
            break;
        case LAYER_420_DS_OUT_ALL_YUV420:
            VO_TEST_LAYER_420_DS_OUT_ALL_YUV420_GetCtl(&voCtl);
            //VO_TEST_LAYER_420_DS_OUT_ALL_YUV420(&voCtl,voCoreInfo);
            //VO_TEST_ALL_LAYERS(&voCtl,voCoreInfo);
            break;
        case LAYER_420_DS_FRAME_DRAW_YUV420:
            VO_TEST_LAYER_420_DS_FRAME_DRAW_YUV420_GetCtl(&voCtl);
            break;
        case VO_CASE_LAYER0_MFBD:
        	VO_TEST_LAYER0_MFBD_GetCtl(&voCtl);
        	break;
        case LAYER0_420_BT1120:
            VO_Test_Layer0_1080P_IN_1080P_OUT_BT1120_GetCtl(&voCtl);
            break;
        case LAYER0_420_1080x1920_YUV420_DSI:
            VO_TestLayer0_1080x1920_DSI_LINE_DRAW_GetCtl(&voCtl);
            break;
        case VO_CASE_LAYER0_LINE_DRAW:
        	VO_TEST_LAYER0_1920x1080_YUV420_GetCtl(&voCtl);
        	break;
        case VO_CASE_LAYER0_420_1280x720_1920x1080:
        	VO_TEST_LAYER0_1280x720_YUV420_GetCtl(&voCtl);
        	break;
        case VO_CASE_LAYER0_420_F23S_IRS238C:
        	VO_TEST_LAYER0_IRS238C_GetCtl(&voCtl);
        	break;
        default:
            break;
    }
    VO_TEST_ALL_LAYERS(&voCtl,voCoreInfo);
    //
    VO_DISP_IRQ_INFO_S *dispIrqInfo = &voCoreInfo->dispIrqInfo;
    VO_TEST_SetDispIrqInfo(dispIrqInfo);
    //
    VO_TEST_SetCore(voCoreInfo);
    //printf("zhudalei:VO_TEST_Core end!!!\n");
    return 0;
}
/******************************************************************************
 *  wrap *
******************************************************************************/
static int VO_TEST_Wrap(void)
{
    VO_TEST_SetWrap();  
    return 0;
}
/******************************************************************************
 *  REMAP *
******************************************************************************/
/*
*DSI
*/
static int VO_TEST_Remap_DSI_Setcmd(VO_REMAP_CMD_INFO_S *CmdInfo)
{
    VO_CHECK_POINTER(CmdInfo);
    CmdInfo->image_active_h = 0x437;
    CmdInfo->fill_en_rgb = TRUE;
    CmdInfo->image_active_v = 0x77f;
    CmdInfo->fill_fill_en_yuv = FALSE;
    return 0;
}

static int VO_TEST_Remap_DSI_SetArea0(VO_REMAP_CTRL_INFO_S *CtlInfo)
{
    VO_CHECK_POINTER(CtlInfo);

    CtlInfo->line_draw_en 		= TRUE;
    CtlInfo->v_line_r_en      	= TRUE;
    CtlInfo->v_line_l_en      	= TRUE;
    CtlInfo->h_line_b_en      	= TRUE;
    CtlInfo->v_line_u_en      	= TRUE;
    CtlInfo->line_start_pos_x 	= 256;
    CtlInfo->line_end_pos_x	  	= CtlInfo->line_start_pos_x + 719;
    CtlInfo->line_start_pos_y 	= 256;
    CtlInfo->line_end_pos_y	  	= CtlInfo->line_start_pos_y + 240;
    CtlInfo->line_width_l 		= 4;
    CtlInfo->line_width_h 		= 0;
    CtlInfo->fill_value_cr 		= 226;
    CtlInfo->fill_value_cb 		= 104;
    CtlInfo->fill_value_y  		= 47;
    CtlInfo->fill_alpha  		= 0; 

    return 0;
}

static int VO_TEST_Remap_DSI_SetArea1(VO_REMAP_CTRL_INFO_S *CtlInfo)
{
    VO_CHECK_POINTER(CtlInfo);

    CtlInfo->line_draw_en 		= TRUE;
    CtlInfo->v_line_r_en      	= TRUE;
    CtlInfo->v_line_l_en      	= TRUE;
    CtlInfo->h_line_b_en      	= TRUE;
    CtlInfo->v_line_u_en      	= TRUE;
    CtlInfo->line_start_pos_x 	= 356;
    CtlInfo->line_end_pos_x	  	= CtlInfo->line_start_pos_x + 729;
    CtlInfo->line_start_pos_y 	= 356;
    CtlInfo->line_end_pos_y	  	= CtlInfo->line_start_pos_y + 240;
    CtlInfo->line_width_l 		= 4;
    CtlInfo->line_width_h 		= 0;
    CtlInfo->fill_value_cr 		= 226;
    CtlInfo->fill_value_cb 		= 104;
    CtlInfo->fill_value_y  		= 47;
    CtlInfo->fill_alpha  		= 0; 

    return 0;
}

static int VO_TEST_Remap_DSI_SetArea2(VO_REMAP_CTRL_INFO_S *CtlInfo)
{
    VO_CHECK_POINTER(CtlInfo);

    CtlInfo->line_draw_en 		= TRUE;
    CtlInfo->v_line_r_en      	= TRUE;
    CtlInfo->v_line_l_en      	= TRUE;
    CtlInfo->h_line_b_en      	= TRUE;
    CtlInfo->v_line_u_en      	= TRUE;
    CtlInfo->line_start_pos_x 	= 456;
    CtlInfo->line_end_pos_x	  	= CtlInfo->line_start_pos_x + 720;
    CtlInfo->line_start_pos_y 	= 456;
    CtlInfo->line_end_pos_y	  	= CtlInfo->line_start_pos_y + 239;
    CtlInfo->line_width_l 		= 4;
    CtlInfo->line_width_h 		= 0;
    CtlInfo->fill_value_cr 		= 226;
    CtlInfo->fill_value_cb 		= 104;
    CtlInfo->fill_value_y  		= 47;
    CtlInfo->fill_alpha  		= 0; 

    return 0;
}

static int VO_TEST_Remap_DSI_SetArea3(VO_REMAP_CTRL_INFO_S *CtlInfo)
{
    VO_CHECK_POINTER(CtlInfo);

    CtlInfo->line_draw_en 		= TRUE;
    CtlInfo->v_line_r_en      	= TRUE;
    CtlInfo->v_line_l_en      	= TRUE;
    CtlInfo->h_line_b_en      	= TRUE;
    CtlInfo->v_line_u_en      	= TRUE;
    CtlInfo->line_start_pos_x 	= 555;
    CtlInfo->line_end_pos_x	  	= CtlInfo->line_start_pos_x + 719;
    CtlInfo->line_start_pos_y 	= 556;
    CtlInfo->line_end_pos_y	  	= CtlInfo->line_start_pos_y + 239;
    CtlInfo->line_width_l 		= 4;
    CtlInfo->line_width_h 		= 0;
    CtlInfo->fill_value_cr 		= 226;
    CtlInfo->fill_value_cb 		= 104;
    CtlInfo->fill_value_y  		= 47;
    CtlInfo->fill_alpha  		= 0; 

    return 0;
}

static int VO_TEST_Remap_DSI(VO_REMAP_INFO_S *voRemapInfo)
{
    VO_CHECK_POINTER(voRemapInfo);
    unsigned int draw_num;
    //
    VO_REMAP_CMD_INFO_S *CmdInfo = &voRemapInfo->CmdInfo;
    VO_TEST_Remap_DSI_Setcmd(CmdInfo);
    //
    draw_num = 0;
    VO_REMAP_CTRL_INFO_S *CtlInfo = &voRemapInfo->CtlInfo[draw_num];
    VO_TEST_Remap_DSI_SetArea0(CtlInfo);
    VO_TEST_SetRemap(draw_num,voRemapInfo); 
    msleep(10000); 
    //
    draw_num = 1;
    CtlInfo = &voRemapInfo->CtlInfo[draw_num];
    VO_TEST_Remap_DSI_SetArea1(CtlInfo);
    VO_TEST_SetRemap(draw_num,voRemapInfo); 
    msleep(10000); 
    //
    draw_num = 2;
    CtlInfo = &voRemapInfo->CtlInfo[draw_num];
    VO_TEST_Remap_DSI_SetArea2(CtlInfo);
    VO_TEST_SetRemap(draw_num,voRemapInfo); 
    msleep(10000); 
    //
    draw_num = 3;
    CtlInfo = &voRemapInfo->CtlInfo[draw_num];
    VO_TEST_Remap_DSI_SetArea3(CtlInfo);
    VO_TEST_SetRemap(draw_num,voRemapInfo); 

    return 0;
}
/*
*
*/
static int VO_TEST_Remap_Main(VO_REMAP_INFO_S *voRemapInfo)
{
    VO_CHECK_POINTER(voRemapInfo);
    unsigned int draw_num;
    VO_REMAP_CTRL_INFO_S *CtlInfo = NULL;
    //
    VO_REMAP_CMD_INFO_S *CmdInfo = &voRemapInfo->CmdInfo;
    CmdInfo->image_active_h = 0x77f;
    CmdInfo->fill_en_rgb = FALSE;
    CmdInfo->image_active_v = 0x437;
    CmdInfo->fill_fill_en_yuv = TRUE;
    //
    for(draw_num = 0;draw_num<= 10; draw_num++)
    {
        CtlInfo = &voRemapInfo->CtlInfo[draw_num];
		CtlInfo->line_draw_en 		= TRUE;
		CtlInfo->v_line_r_en      	= TRUE;
		CtlInfo->v_line_l_en      	= TRUE;
		CtlInfo->h_line_b_en      	= TRUE;
		CtlInfo->v_line_u_en      	= TRUE;
		CtlInfo->line_start_pos_x 	= 12 + draw_num *100;
		CtlInfo->line_end_pos_x	  	= CtlInfo->line_start_pos_x + 181;
		CtlInfo->line_start_pos_y 	= 42 + draw_num *10;
		CtlInfo->line_end_pos_y	  	= CtlInfo->line_start_pos_y + 180;
		CtlInfo->line_width_l 		= 3;
		CtlInfo->line_width_h 		= 0;
		CtlInfo->fill_value_cr 		= 251;
		CtlInfo->fill_value_cb 		= 98;
		CtlInfo->fill_value_y  		= 70;
		CtlInfo->fill_alpha  		= 0; 
        VO_TEST_SetRemap(draw_num,voRemapInfo);
        msleep(20);
        printf("test ISP_DRV_CORE_MainDrawLineSet draw_num = %line_start_pos_x = %d!\n\n",draw_num,CtlInfo->line_start_pos_x);        
    }
    return 0;
}


static int VO_TEST_Remap_Bringup(VO_REMAP_INFO_S *voRemapInfo)
{
    VO_CHECK_POINTER(voRemapInfo);
    unsigned int draw_num;
    VO_REMAP_CTRL_INFO_S *CtlInfo = NULL;
    //
    VO_REMAP_CMD_INFO_S *CmdInfo = &voRemapInfo->CmdInfo;
    CmdInfo->image_active_h = 0x7f;
    CmdInfo->fill_en_rgb = FALSE;
    CmdInfo->image_active_v = 0x7f;
    CmdInfo->fill_fill_en_yuv = TRUE;
    //
    for(draw_num = 0;draw_num<= 10; draw_num++)
    {
        CtlInfo = &voRemapInfo->CtlInfo[draw_num];
        CtlInfo->line_draw_en       = TRUE;
        CtlInfo->v_line_r_en        = TRUE;
        CtlInfo->v_line_l_en        = TRUE;
        CtlInfo->h_line_b_en        = TRUE;
        CtlInfo->v_line_u_en        = TRUE;
        CtlInfo->line_start_pos_x   = 5 + draw_num *5;
        CtlInfo->line_end_pos_x     = CtlInfo->line_start_pos_x + 60;
        CtlInfo->line_start_pos_y   = 5 + draw_num *5;
        CtlInfo->line_end_pos_y     = CtlInfo->line_start_pos_y + 60;
        CtlInfo->line_width_l       = 3;
        CtlInfo->line_width_h       = 0;
        CtlInfo->fill_value_cr      = 251;
        CtlInfo->fill_value_cb      = 98;
        CtlInfo->fill_value_y       = 70;
        CtlInfo->fill_alpha         = 0; 
        VO_TEST_SetRemap(draw_num,voRemapInfo);
        msleep(20);
        printf("test ISP_DRV_CORE_MainDrawLineSet draw_num = %line_start_pos_x = %d!\n\n",draw_num,CtlInfo->line_start_pos_x);        
    }
    return 0;
}

/*
*
*/
static int VO_TEST_Remap(VO_TEST_CASE_E voTestCase,VO_REMAP_INFO_S *voRemapInfo)
{
    VO_CHECK_POINTER(voRemapInfo);

    switch(voTestCase)
    {
        case LAYER0_420_1080x1920_YUV420_DSI:
            VO_TEST_Remap_DSI(voRemapInfo);
            break;
        case VO_CASE_LAYER0_LINE_DRAW:
            VO_TEST_Remap_Main(voRemapInfo);
            break;
        case VO_BT1120_HDMI_BRINGUP:
            VO_TEST_Remap_Bringup(voRemapInfo);
            break;
        default:
            break;
    }
    return 0;
}
/*
*/
static int dsi_init(VO_TEST_CASE_E voTestCase)
{
    switch(voTestCase)
    {
        case VO_DSI_MIPI_BRINGUP:
     //       aml550_power_on_seq();

//            display_gpio_reset();
            dsi_init_1080x1920();
            break;
        case VO_DSI_MIPI_800x1280:
            dsi_init_800x1280();

            break;

        default:
            break;
    }
    return 0;
}

/*
*/
int VO_TEST_VideoOut(VO_TEST_CASE_E voTestCase)
{
    int hpd_state = 0;
    int lcd_id = 0;
    VO_INFO_S voInfo;

    //
    VO_TEST_Init();
    //table
    VO_TABLE_init();
    //wrap
    VO_TEST_Wrap();
    //core
    VO_CORE_INFO_S *voCoreInfo = &voInfo.voCoreInfo;
    VO_TEST_Core(voTestCase,voCoreInfo);

    //enable dsi output
    dsi_init(voTestCase);

    hpd_state = lt9611_get_hpd_state();
    lcd_id = get_lcd_id();
    if (hpd_state) {
        *(uint32_t *)0x92700118 = 0x80;
        set_bootcmd("k510-hdmi.dtb");
        display_switch_hdmi_gpio();
    } else if (lcd_id == 0x0C9983 || lcd_id == 0x1C9983 || lcd_id == 0x46593) {
        VO_TEST_Start();
        set_bootcmd("k510.dtb");
    } else {
        *(uint32_t *)0x92700118 = 0x80;
        set_bootcmd("k510-hdmi.dtb");
        display_switch_hdmi_gpio();
    }

    VO_PRINTF_FUNC("Display Config done!\n");
    return 0;
}
