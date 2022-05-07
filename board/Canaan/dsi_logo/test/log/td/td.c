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

#include <video/td/wrap/td_wrap_reg.h>
#include <video/td/core/td_core_reg.h>
#include <video/td/core/td_core_drv.h>
#include <video/td/wrap/td_wrap_drv.h>
#include <video/td/table/td_table_drv.h>
#include "td/td.h"

/****************************************************************************
 * 	*
 ****************************************************************************/
static int TD_DRV_Remap( )
{
    TD_DRV_Table_Remap( );
    TD_DRV_Wrap_Remap( );
    TD_DRV_Core_Remap( );
    return 0;
}
/****************************************************************************
 * 											*
 ****************************************************************************/
void * osal_td_memset(void *str,int c,int count)
{
    return memset(str, c, count);
}
/****************************************************************************
 * 											*
 ****************************************************************************/
int TD_DRV_Init(void)
{
    int Ret = SUCCESS;
    //int DevIndex = 0;
	
    Ret = TD_DRV_Remap( );

    if(FAILURE == Ret)
    {
        return Ret;
    }
    
  //  for(DevIndex=0; DevIndex<ISP_MAX_DEV_NUM; DevIndex++)
  //  {
  //      osal_isp_memset(&g_astispDrvCtx[DevIndex], 0, sizeof(ISP_DRV_CTL_S));
  //  }	
	
    return Ret;
}
/****************************************************************************
 *wrap 											*
 ****************************************************************************/
/*
*rst 
*/
static int TD_TEST_GetRst(TD_WRAP_SWRST_S *swrst)
{
    TD_CHECK_POINTER(swrst);

    swrst->rotationrw = 1;
    swrst->mixerrw = 1;
    swrst->axiwr   = 1;
    swrst->axird   = 1;
    
    return 0;
}
/*
*clk en 
*/
static int TD_TEST_GetClkEn(TD_WRAP_CLK_INFO_S *clkInfo,TD_WRAP_CLK_EN_S *clk_en)
{
    TD_CHECK_POINTER(clkInfo);
    TD_CHECK_POINTER(clk_en);

    clk_en->ch0rd = 1;//clkInfo->ch0rd;
    clk_en->ch1rd = 1;//clkInfo->ch1rd;
    clk_en->ch2rd = 1;//clkInfo->ch2rd;
    clk_en->ch3rd = 1;//clkInfo->ch3rd;
    clk_en->ch4rd = 1;//clkInfo->ch4rd;
    clk_en->ch5rd = 1;//clkInfo->ch5rd;
    clk_en->ch0wr = 1;//clkInfo->ch0wr;
    clk_en->ch1wr = 1;//clkInfo->ch1wr;
    clk_en->ch2wr = 1;//clkInfo->ch2wr;
    clk_en->axiwr = 1;//clkInfo->axiwr;
    clk_en->axird = 1;//clkInfo->axird;

    return 0;
}
/*
*dma 
*/
static int TD_TEST_GetDmaInfo(TD_WRAP_DMA_CTL_S *dma_ctl)
{
    TD_CHECK_POINTER(dma_ctl);
    //
    TD_WRAP_DMA_ARB_MODE_S    *arb_mode = &dma_ctl->arb_mode;
    arb_mode->rd = 1;
    arb_mode->wr = 1;
    //
    TD_WRAP_DMA_WEIGHT_WR_S   *weight_wr = &dma_ctl->weight_wr;
    weight_wr->ch0 = 1;
    weight_wr->ch1 = 1;
    weight_wr->ch2 = 1;
    weight_wr->ch3 = 1;
    weight_wr->ch4 = 1;
    weight_wr->ch5 = 1;
    weight_wr->ch6 = 1;
    weight_wr->ch7 = 1;    
    //
    TD_WRAP_DMA_WEIGHT_RD_S   *weight_rd = &dma_ctl->weight_rd;
    weight_rd->ch0 = 1;
    weight_rd->ch1 = 1;
    weight_rd->ch2 = 1;
    weight_rd->ch3 = 1;
    weight_rd->ch4 = 1;
    weight_rd->ch5 = 1;
    weight_rd->ch6 = 1;
    weight_rd->ch7 = 1;    
    //
    TD_WRAP_DMA_PRIORITY_WR_S *prior_wr = &dma_ctl->prior_wr;
    prior_wr->ch0 = 7;
    prior_wr->ch1 = 6;
    prior_wr->ch2 = 5;
    prior_wr->ch3 = 4;
    prior_wr->ch4 = 3;
    prior_wr->ch5 = 2;
    prior_wr->ch6 = 1;
    prior_wr->ch7 = 0;  
    //
    TD_WRAP_DMA_PRIORITY_RD_S *prior_rd = &dma_ctl->prior_rd;
    prior_rd->ch0 = 7;
    prior_rd->ch1 = 6;
    prior_rd->ch2 = 5;
    prior_rd->ch3 = 4;
    prior_rd->ch4 = 3;
    prior_rd->ch5 = 2;
    prior_rd->ch6 = 1;
    prior_rd->ch7 = 0; 
    //
    TD_WRAP_DMA_ID_WR_S       *id_wr = &dma_ctl->id_wr;
    id_wr->ch0 = 0;
    id_wr->ch1 = 1;
    id_wr->ch2 = 2;
    id_wr->ch3 = 3;
    id_wr->ch4 = 4;
    id_wr->ch5 = 5;
    id_wr->ch6 = 6;
    id_wr->ch7 = 7;     
    //
    TD_WRAP_DMA_ID_RD_S       *id_rd = &dma_ctl->id_rd;
    id_rd->ch0 = 0;
    id_rd->ch1 = 1;
    id_rd->ch2 = 2;
    id_rd->ch3 = 3;
    id_rd->ch4 = 4;
    id_rd->ch5 = 5;
    id_rd->ch6 = 6;
    id_rd->ch7 = 7;  

    return 0;
}
/*
*int 
*/
static int TD_TEST_GetIntMask(TD_WRAP_INT_MASK_S *int_mask)
{
    TD_CHECK_POINTER(int_mask);

    int_mask->mixerdone_mask = 1;
    int_mask->rotationdone_mask = 1;
    int_mask->rotationtimeout_mask = 1;

    return 0;
}
/*
*config done 
*/
static int TD_TEST_GetCfgDone(TD_WRAP_CFG_S  *cfg_done)
{
    TD_CHECK_POINTER(cfg_done);

    cfg_done->done = 1;

    return 0;
}
/*
*
*/
int TD_TEST_SetWrap(TD_WRAP_INFO_S *wrapInfo)
{
    TD_CHECK_POINTER(wrapInfo);
    TD_WRAP_CTL_S tdWrapCtl;

    TD_WRAP_SWRST_S *swrst = &tdWrapCtl.swrst;
    TD_TEST_GetRst(swrst);
    //
    TD_WRAP_CLK_INFO_S *clkInfo = &wrapInfo->clkInfo;
    TD_WRAP_CLK_EN_S *clk_en  = &tdWrapCtl.clk_en;
    TD_TEST_GetClkEn(clkInfo,clk_en);
    //
    TD_WRAP_DMA_CTL_S *dma_ctl = &tdWrapCtl.dma_ctl;
    TD_TEST_GetDmaInfo(dma_ctl);
    //
    TD_WRAP_INT_MASK_S *int_mask = &tdWrapCtl.int_mask;
    TD_TEST_GetIntMask(int_mask);
    //
    TD_WRAP_CFG_S  *cfg_done = &tdWrapCtl.cfg_done;
    TD_TEST_GetCfgDone(cfg_done);
    //
    TD_DRV_SetWrap(&tdWrapCtl);
    return 0;
}
/****************************************************************************
 *core 											*
 ****************************************************************************/
/*
*rotation
*/
static int TD_TEST_GetRotAllInfo(TD_ROT_ALL_INFO_S *rotAllInfo,TD_ROT_ALL_CTL_S *rotAllCtl)
{
    TD_CHECK_POINTER(rotAllInfo);
    TD_CHECK_POINTER(rotAllCtl);
    //
    TD_ROT_INFO_S       *rotInfo =  &rotAllInfo->rotInfo;
    TD_ROT_CTL_S *rotCtl = &rotAllCtl->rotCtl ;
    rotCtl->rotmode     =  rotInfo->rotmode;
    rotCtl->pixformat   =  rotInfo->pixformat;
    rotCtl->Inswap      =  rotInfo->Inswap;
    rotCtl->endianInEn  =  rotInfo->endianInEn;
    rotCtl->Outswap     =  rotInfo->Outswap;
    rotCtl->endianOutEn =  rotInfo->endianOutEn;
    rotCtl->otmaxrd     =  rotInfo->otmaxrd;
    rotCtl->otmaxwr     =  rotInfo->otmaxwr;
    //
    TD_ROT_SIZE_INFO_S  *imgSizeInfo =  &rotAllInfo->imgSize;
    TD_ROT_IMG_SIZE_S *imgSize = &rotAllCtl->imgSize ;
    imgSize->hor  = imgSizeInfo->hor;
    imgSize->ver  = imgSizeInfo->ver;
    //
    TD_ROT_Y_BUF_INFO_S *yBufInfo =  &rotAllInfo->yBufInfo;
    TD_ROT_Y_S *yBufCtl = &rotAllCtl->yBufCtl ;
    yBufCtl->y_src_addr = yBufInfo->y_src_addr;
    yBufCtl->src_stride = yBufInfo->src_stride;
    yBufCtl->y_des_addr = yBufInfo->y_src_addr;
    yBufCtl->des_stride = yBufInfo->src_stride;
    //
    TD_ROT_U_BUF_INFO_S *uBufInfo =  &rotAllInfo->uBufInfo;
    TD_ROT_U_S *uBufCtl = &rotAllCtl->uBufCtl ;
    uBufCtl->u_src_addr = uBufInfo->u_src_addr;
    uBufCtl->src_stride = uBufInfo->src_stride;
    uBufCtl->u_des_addr = uBufInfo->u_des_addr;
    uBufCtl->des_stride = uBufInfo->src_stride;
    //
    TD_ROT_V_BUF_INFO_S *vBufInfo =  &rotAllInfo->vBufInfo;
    TD_ROT_V_S *vBufCtl = &rotAllCtl->vBufCtl ;
    vBufCtl->v_src_addr = vBufInfo->v_src_addr;
    vBufCtl->src_stride = vBufInfo->src_stride;
    vBufCtl->v_des_addr = vBufInfo->v_des_addr;
    vBufCtl->des_stride = vBufInfo->des_stride;
    //
	rotAllCtl->rot_framestart = rotAllInfo->rot_framestart;
    rotAllCtl->timeout_val = rotAllInfo->timeout_val;

    return 0;
}
/*
*rst 
*/
static int TD_TEST_GetRstInfo(TD_SOFT_RST_INFO_S *rstInfo,TD_SOFT_RST_CTL_S *rstCtl)
{
    TD_CHECK_POINTER(rstInfo);
    TD_CHECK_POINTER(rstCtl);

    rstCtl->mix  = 1;
    rstCtl->axi  = 1;
    rstCtl->apb  = 1;
    rstCtl->core = 1;

    return 0;
}
/*
*sw
*/
static int TD_TEST_GetSwInfo(TD_DMA_SW_INFO_S *swInfo,TD_DMA_SW_CTL_S *swCtl)
{
    TD_CHECK_POINTER(swInfo);
    TD_CHECK_POINTER(swCtl);

    swCtl->reqrd = 1;
    swCtl->reqwr = 1;

    return 0;
}
/*
*disp
*/
static int TD_TEST_GetDispInfo(TD_DISP_INFO_S *dispInfo,TD_DISP_CTL_S *dispCtl)
{
    TD_CHECK_POINTER(dispInfo);
    TD_CHECK_POINTER(dispCtl);

    dispCtl->framesyncdly = dispInfo->framesyncdly;
    dispCtl->secndfoffset = dispInfo->secndfoffset;
    dispCtl->vcntbit0     = dispInfo->vcntbit0;
    return 0;
}
/*
*Layer0
*/
static int TD_TEST_GetLayer0Info(TD_LAYER0_INFO_S *layer0Info,TD_LAYER0_CTL_S *layer0Ctl)
{
    TD_CHECK_POINTER(layer0Info);
    TD_CHECK_POINTER(layer0Ctl);

    layer0Ctl->ctlen = layer0Info->ctlen;
    layer0Ctl->layer0en = layer0Info->layer0en;
    layer0Ctl->layer0enhs = layer0Info->layer0enhs;
    layer0Ctl->layer0Wenhs = layer0Info->layer0Wenhs; 
    layer0Ctl->layer0Scalerblen = layer0Info->layer0Scalerblen;
    //
    TD_BD_INFO_S                 *layer0Line0BDInfo =  &layer0Info->layer0Line0BDInfo;
    TD_BD_CTL_S                 *layer0Line0BDCtl =  &layer0Ctl->layer0Line0BDCtl;
    layer0Line0BDCtl->limiten = layer0Line0BDInfo->limiten;
    layer0Line0BDCtl->outstand = layer0Line0BDInfo->outstand;
    //
    TD_BD_INFO_S                 *layer0Line1BDInfo =  &layer0Info->layer0Line1BDInfo;
    TD_BD_CTL_S                 *layer0Line1BDCtl =  &layer0Ctl->layer0Line1BDCtl;
    layer0Line1BDCtl->limiten = layer0Line1BDInfo->limiten;
    layer0Line1BDCtl->outstand = layer0Line1BDInfo->outstand;
    //
    TD_BD_INFO_S                 *layer0Line2BDInfo =  &layer0Info->layer0Line2BDInfo;
    TD_BD_CTL_S                 *layer0Line2BDCtl =  &layer0Ctl->layer0Line2BDCtl;
    layer0Line2BDCtl->limiten = layer0Line2BDInfo->limiten;
    layer0Line2BDCtl->outstand = layer0Line2BDInfo->outstand;
    //
    TD_BD_INFO_S                 *layer0Line3BDInfo =  &layer0Info->layer0Line3BDInfo;  
    TD_BD_CTL_S                 *layer0Line3BDCtl =  &layer0Ctl->layer0Line3BDCtl;
    layer0Line3BDCtl->limiten = layer0Line3BDInfo->limiten;
    layer0Line3BDCtl->outstand = layer0Line3BDInfo->outstand;
    //
    TD_AREA_INFO_S               *layer0XInfo =  &layer0Info->layer0XInfo;   
    TD_AREA_CTL_S               *layer0XCtl =  &layer0Ctl->layer0XCtl;
    layer0XCtl->start = layer0XInfo->start;
    layer0XCtl->stop = layer0XInfo->stop;
    //
    TD_AREA_INFO_S               *layer0YInfo=  &layer0Info->layer0YInfo;
    TD_AREA_CTL_S               *layer0YCtl =  &layer0Ctl->layer0YCtl;
    layer0YCtl->start = layer0YInfo->start;
    layer0YCtl->stop = layer0YInfo->stop;   
    //
    TD_LAYER0_IMG_MODE_INFO_S    *imgInDatModeInfo =  &layer0Info->imgInDatModeInfo;
    TD_LAYER0_IMG_IN_DAT_MODE_S *imgInDatMode =  &layer0Ctl->imgInDatMode;
    imgInDatMode->datmode = imgInDatModeInfo->datmode;
    imgInDatMode->endiany = imgInDatModeInfo->endiany;
    imgInDatMode->endianuv = imgInDatModeInfo->endianuv;
    imgInDatMode->swapuv = imgInDatModeInfo->swapuv;
    //
    layer0Ctl->y_addr =  layer0Info->y_addr;
    layer0Ctl->uv_addr = layer0Info->uv_addr;
    //
    TD_LAYER0_SIZE_INFO_S        *imgInSizeInfo =  &layer0Info->imgInSizeInfo;
    TD_LAYER0_SIZE_S            *imgInSize =  &layer0Ctl->imgInSize;
    imgInSize->hsize = imgInSizeInfo->hsize;
    imgInSize->vsize = imgInSizeInfo->vsize;
    //
    TD_LAYER0_SIZE_INFO_S        *imgOutSizeInfo =  &layer0Info->imgOutSizeInfo;
    TD_LAYER0_SIZE_S            *imgOutSize =  &layer0Ctl->imgOutSize;
    imgOutSize->hsize = imgOutSizeInfo->hsize;
    imgOutSize->vsize = imgOutSizeInfo->vsize;
    //
    TD_LAYER0_SIZE_INFO_S        *imgInStrideInfo =  &layer0Info->imgInStrideInfo;
    TD_LAYER0_SIZE_S            *imgInStride =  &layer0Ctl->imgInStride;
    imgInStride->hsize = imgInStrideInfo->hsize;
    imgInStride->vsize = imgInStrideInfo->vsize;
    //
    TD_LAYER0_SIZE_INFO_S        *imgInOffsetInfo =  &layer0Info->imgOutSizeInfo;
    TD_LAYER0_SIZE_S            *imgInOffset =  &layer0Ctl->imgOutSize;
    imgInOffset->hsize = imgInOffsetInfo->hsize;
    imgInOffset->vsize = imgInOffsetInfo->vsize;
    //
    TD_LAYER0_SCALE_INFO_S       *vScaleInfo =  &layer0Info->vScaleInfo;
    TD_LAYER0_SCALE_CTL_S       *vScaleCtl =  &layer0Ctl->vScaleCtl;
    vScaleCtl->dstep = vScaleInfo->dstep;
    vScaleCtl->pstep = vScaleInfo->pstep;
    vScaleCtl->pstep_st = vScaleInfo->pstep_st;
    //
    TD_LAYER0_SCALE_INFO_S       *hScaleInfo =  &layer0Info->hScaleInfo;
    TD_LAYER0_SCALE_CTL_S       *hScaleCtl =  &layer0Ctl->hScaleCtl;
    hScaleCtl->dstep = hScaleInfo->dstep;
    hScaleCtl->pstep = hScaleInfo->pstep;
    hScaleCtl->pstep_st = hScaleInfo->pstep_st;
    //
    TD_LAYER0_BASE_MODE_INFO_S   *baseModeInfo =  &layer0Info->baseModeInfo;
    TD_LAYER0_BASE_MODE_S       *baseMode =  &layer0Ctl->baseMode;
    baseMode->addrflag = baseModeInfo->addrflag;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;
    return 0;
}
/*
*Layer4osd
*/
static int TD_TEST_GetLayer4OsdInfo(TD_LAYER4_OSD_INFO_S *layer4OsdInfo,TD_LAYER4_OSD_CTL_S *layer4OsdCtl)
{
    TD_CHECK_POINTER(layer4OsdInfo);
    TD_CHECK_POINTER(layer4OsdCtl);
    //
    layer4OsdCtl->layer4en =  layer4OsdInfo->layer4en;
    layer4OsdCtl->layer4enhs =  layer4OsdInfo->layer4enhs;
    layer4OsdCtl->layer4Wenhs =  layer4OsdInfo->layer4Wenhs;
    //
    TD_BD_INFO_S        *layer4BDInfo =  &layer4OsdInfo->layer4BDInfo;
    TD_BD_CTL_S       *layer4BDCtl =  &layer4OsdCtl->layer4BDCtl;
    layer4BDCtl->limiten = layer4BDInfo->limiten;
    layer4BDCtl->outstand = layer4BDInfo->outstand;
    //
    TD_AREA_INFO_S      *layer4XInfo =  &layer4OsdInfo->layer4XInfo;
    TD_AREA_CTL_S     *layer4XCtl =  &layer4OsdCtl->layer4XCtl;
    layer4XCtl->start = layer4XInfo->start;
    layer4XCtl->stop = layer4XInfo->stop;
    //
    TD_AREA_INFO_S      *layer4YInfo =  &layer4OsdInfo->layer4YInfo;
    TD_AREA_CTL_S     *layer4YCtl =  &layer4OsdCtl->layer4YCtl;
    layer4YCtl->start = layer4YInfo->start;
    layer4YCtl->stop = layer4YInfo->stop;
    //
    TD_OSD0_INFO_S      *osd0Info =  &layer4OsdInfo->osd0Info;
    TD_OSD0_CTL_S     *osd0Ctl =  &layer4OsdCtl->osd0Ctl;
    osd0Ctl->alphatpye = osd0Info->alphatpye;
    osd0Ctl->osdtype = osd0Info->osdtype;
    //
    TD_OSD0_SIZE_INFO_S *osd0SizeInfo =  &layer4OsdInfo->osd0SizeInfo;
    TD_OSD0_SIZE_S    *osd0Size =  &layer4OsdCtl->osd0Size;
    osd0Size->width = osd0SizeInfo->width;
    osd0Size->height = osd0SizeInfo->height;
    //
    TD_OSD0_DMA_INFO_S  *osd0DmaInfo =  &layer4OsdInfo->osd0DmaInfo;
    TD_OSD0_DMA_CTL_S *osd0DmaCtl =  &layer4OsdCtl->osd0DmaCtl;
    osd0DmaCtl->dmamap = osd0DmaInfo->dmamap;
    osd0DmaCtl->dmarequestlen = osd0DmaInfo->dmamap;
    osd0DmaCtl->rgbrev = osd0DmaInfo->rgbrev;
    //
    TD_OSD0_ADDR_INFO_S *osd0AddrInfo =  &layer4OsdInfo->osd0AddrInfo;
    TD_OSD0_ADDR_S    *osd0Addr =  &layer4OsdCtl->osd0Addr;
    osd0Addr->alp_addr = osd0AddrInfo->alp_addr;
    osd0Addr->alpstride = osd0AddrInfo->alpstride;
    osd0Addr->vlu_addr = osd0AddrInfo->vlu_addr;
    osd0Addr->osdstride = osd0AddrInfo->osdstride;
    //
    TD_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo =  &layer4OsdInfo->osdRgb2YuvInfo;
    TD_OSD_RGB2YUV_S  *osdRgb2Yuv =  &layer4OsdCtl->osdRgb2Yuv;
    osdRgb2Yuv->osd0en = osdRgb2YuvInfo->osd0en;
    osdRgb2Yuv->osd1en = osdRgb2YuvInfo->osd1en;
    osdRgb2Yuv->osd2en = osdRgb2YuvInfo->osd2en;
    osdRgb2Yuv->osdrgb2yuv_coeff[0][0] = osdRgb2YuvInfo->osdrgb2yuv_coeff[0][0];
    osdRgb2Yuv->osdrgb2yuv_coeff[0][1] = osdRgb2YuvInfo->osdrgb2yuv_coeff[0][1];
    osdRgb2Yuv->osdrgb2yuv_coeff[0][2] = osdRgb2YuvInfo->osdrgb2yuv_coeff[0][2];
    osdRgb2Yuv->osdrgb2yuv_coeff[0][3] = osdRgb2YuvInfo->osdrgb2yuv_coeff[0][3];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][0] = osdRgb2YuvInfo->osdrgb2yuv_coeff[1][0];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][1] = osdRgb2YuvInfo->osdrgb2yuv_coeff[1][1];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][2] = osdRgb2YuvInfo->osdrgb2yuv_coeff[1][2];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][3] = osdRgb2YuvInfo->osdrgb2yuv_coeff[1][3];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][0] = osdRgb2YuvInfo->osdrgb2yuv_coeff[2][0];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][1] = osdRgb2YuvInfo->osdrgb2yuv_coeff[2][1];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][2] = osdRgb2YuvInfo->osdrgb2yuv_coeff[2][2];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][3] = osdRgb2YuvInfo->osdrgb2yuv_coeff[2][3];
    return 0;
}
/*
*yuv2rgb
*/
static int TD_TEST_GetYuv2RgbInfo(TD_YUV2RGB_INFO_S *yuv2rgbInfo,TD_YUV2RGB_S *yuv2rgb)
{
    TD_CHECK_POINTER(yuv2rgbInfo);
    TD_CHECK_POINTER(yuv2rgb);

    yuv2rgb->yuv2rgb_ctl_en = yuv2rgbInfo->yuv2rgb_ctl_en;
    yuv2rgb->yuv2rgb_coeff[0][0] = yuv2rgbInfo->yuv2rgb_coeff[0][0];
    yuv2rgb->yuv2rgb_coeff[0][1] = yuv2rgbInfo->yuv2rgb_coeff[0][1];
    yuv2rgb->yuv2rgb_coeff[0][2] = yuv2rgbInfo->yuv2rgb_coeff[0][2];
    yuv2rgb->yuv2rgb_coeff[0][3] = yuv2rgbInfo->yuv2rgb_coeff[0][3];
    yuv2rgb->yuv2rgb_coeff[1][0] = yuv2rgbInfo->yuv2rgb_coeff[1][0];
    yuv2rgb->yuv2rgb_coeff[1][1] = yuv2rgbInfo->yuv2rgb_coeff[1][1];
    yuv2rgb->yuv2rgb_coeff[1][2] = yuv2rgbInfo->yuv2rgb_coeff[1][2];
    yuv2rgb->yuv2rgb_coeff[1][3] = yuv2rgbInfo->yuv2rgb_coeff[1][3];
    yuv2rgb->yuv2rgb_coeff[2][0] = yuv2rgbInfo->yuv2rgb_coeff[2][0];
    yuv2rgb->yuv2rgb_coeff[2][1] = yuv2rgbInfo->yuv2rgb_coeff[2][1];
    yuv2rgb->yuv2rgb_coeff[2][2] = yuv2rgbInfo->yuv2rgb_coeff[2][2];
    yuv2rgb->yuv2rgb_coeff[2][3] = yuv2rgbInfo->yuv2rgb_coeff[2][3];

    return 0;
}
/*
*disp mix
*/
static int TD_TEST_GetDispMixInfo(TD_DISP_MIX_INFO_S *dispMixInfo,TD_DISP_MIX_CTL_S *dispMixCtl)
{
    TD_CHECK_POINTER(dispMixInfo);
    TD_CHECK_POINTER(dispMixCtl);

    dispMixCtl->layer0sel = dispMixInfo->layer0sel;
    dispMixCtl->layer1sel = dispMixInfo->layer1sel;
    dispMixCtl->layer0glbalp = dispMixInfo->layer0glbalp;
    dispMixCtl->layer4glbalp = dispMixInfo->layer0glbalp;
    dispMixCtl->backGroud.y = dispMixInfo->backGroudInfo.y;
    dispMixCtl->backGroud.u = dispMixInfo->backGroudInfo.u;
    dispMixCtl->backGroud.v = dispMixInfo->backGroudInfo.v;

    return 0;
}
/*
*disp irq
*/
static int TD_TEST_GetDispIrqInfo(TD_DISP_IRQ_ALL_INFO_S *dispAllIrqInfo,TD_DISP_IRQ_S *dispIrqCtl)
{
    TD_CHECK_POINTER(dispAllIrqInfo);
    TD_CHECK_POINTER(dispIrqCtl);

    dispIrqCtl->irq0Ctl.en = dispAllIrqInfo->irq0Info.en;
    dispIrqCtl->irq0Ctl.underrundcnt = dispAllIrqInfo->irq0Info.underrundcnt;
    dispIrqCtl->irq1Ctl.en = dispAllIrqInfo->irq1Info.en;
    dispIrqCtl->irq1Ctl.underrundcnt = dispAllIrqInfo->irq1Info.underrundcnt;
    dispIrqCtl->irq2Ctl.en = dispAllIrqInfo->irq2Info.en;
    dispIrqCtl->irq2Ctl.underrundcnt = dispAllIrqInfo->irq2Info.underrundcnt;

    return 0;
}
/*
*wb
*/
static int TD_TEST_GetWBInfo(TD_WB_INFO_S *wbInfo,TD_WB_CTL_S *wbCtl)
{
    TD_CHECK_POINTER(wbInfo);
    TD_CHECK_POINTER(wbCtl);

	wbCtl->wb_en = wbInfo->wb_en;
    wbCtl->input_mode = wbInfo->input_mode;
	wbCtl->buffersize = wbInfo->buffersize;
	wbCtl->v_size_out = wbInfo->v_size_out;
	wbCtl->h_size_out = wbInfo->h_size_out;
    //
	TD_WB_Y_BUF_INFO_S        *yBufInfo = &wbInfo->yBufInfo;	
	TD_WB_Y_BUF_S            *yBuf = &wbCtl->yBuf;
    yBuf->y_en = yBufInfo->y_en;
    yBuf->addr0 = yBufInfo->addr0;
    yBuf->addr1 = yBufInfo->addr1;
    yBuf->hstride = yBufInfo->hstride;
    //
    TD_WB_UV_BUF_INFO_S       *uvBufInfo = &wbInfo->uvBufInfo;
	TD_WB_UV_BUF_S           *uvBuf = &wbCtl->uvBuf;
    uvBuf->uv_en = uvBufInfo->uv_en;
    uvBuf->addr0 = uvBufInfo->addr0;
    uvBuf->addr1 = uvBufInfo->addr1;
    uvBuf->hstride = uvBufInfo->hstride;
    //
	TD_WB_PIXEL_FORMAT_OUT_INFO_S  *PixelFormatOutInfo = &wbInfo->PixelFormatOutInfo;
	TD_WB_PIXEL_FORMAT_OUT_S *PixelFormatOut = &wbCtl->PixelFormatOut;
    PixelFormatOut->formatsel = PixelFormatOutInfo->formatsel;
    PixelFormatOut->inputformat = PixelFormatOutInfo->inputformat;
    PixelFormatOut->outputformat = PixelFormatOutInfo->outputformat;
    PixelFormatOut->pixelorder422 = PixelFormatOutInfo->pixelorder422;
    PixelFormatOut->rgbpixelwidth = PixelFormatOutInfo->rgbpixelwidth;
    //
	TD_WB_CH_INFO_S            *ch0Info = &wbInfo->ch0Info;
	TD_WB_CH_CTL_S           *ch0Ctl = &wbCtl->ch0Ctl;
    ch0Ctl->request = ch0Info->request;
    ch0Ctl->err_unit = ch0Info->err_unit;
    ch0Ctl->err_threshold = ch0Info->err_threshold;
    ch0Ctl->dmaMode.blen = ch0Info->dmaModeInfo.blen;
    ch0Ctl->dmaMode.continuousmode = ch0Info->dmaModeInfo.continuousmode;
    ch0Ctl->dmaMode.errdetecten = ch0Info->dmaModeInfo.errdetecten;
    ch0Ctl->dmaMode.otnum = ch0Info->dmaModeInfo.otnum;
    ch0Ctl->dmaMode.swap = ch0Info->dmaModeInfo.swap;
    ch0Ctl->infoClr.fifoerrclear = ch0Info->infoClrInfo.fifoerrclear;
    ch0Ctl->infoClr.frmcntclear = ch0Info->infoClrInfo.frmcntclear;
    ch0Ctl->infoClr.maxbw = ch0Info->infoClrInfo.maxbw;
    ch0Ctl->infoClr.totalbw = ch0Info->infoClrInfo.totalbw;
    //
	TD_WB_CH_INFO_S            *ch1Info = &wbInfo->ch0Info;
	TD_WB_CH_CTL_S           *ch1Ctl = &wbCtl->ch1Ctl;
    ch1Ctl->request = ch1Info->request;
    ch1Ctl->err_unit = ch1Info->err_unit;
    ch1Ctl->err_threshold = ch1Info->err_threshold;
    ch1Ctl->dmaMode.blen = ch1Info->dmaModeInfo.blen;
    ch1Ctl->dmaMode.continuousmode = ch1Info->dmaModeInfo.continuousmode;
    ch1Ctl->dmaMode.errdetecten = ch1Info->dmaModeInfo.errdetecten;
    ch1Ctl->dmaMode.otnum = ch1Info->dmaModeInfo.otnum;
    ch1Ctl->dmaMode.swap = ch1Info->dmaModeInfo.swap;
    ch1Ctl->infoClr.fifoerrclear = ch1Info->infoClrInfo.fifoerrclear;
    ch1Ctl->infoClr.frmcntclear = ch1Info->infoClrInfo.frmcntclear;
    ch1Ctl->infoClr.maxbw = ch1Info->infoClrInfo.maxbw;
    ch1Ctl->infoClr.totalbw = ch1Info->infoClrInfo.totalbw;
    return 0;
}
/*
*
*/
int TD_TEST_SetCore(TD_CORE_INFO_S *tdCoreInfo)
{
    TD_CHECK_POINTER(tdCoreInfo);
    TD_CORE_CTL_S tdCoreCtl;
    //
    TD_ROT_ALL_INFO_S     *rotAllInfo = &tdCoreInfo->rotAllInfo;
    TD_ROT_ALL_CTL_S     *rotAllCtl = &tdCoreCtl.rotAllCtl;
    TD_TEST_GetRotAllInfo(rotAllInfo,rotAllCtl);
    //
    TD_SOFT_RST_INFO_S    *rstInfo =  &tdCoreInfo->rstInfo;
    TD_SOFT_RST_CTL_S    *rstCtl = &tdCoreCtl.rstCtl;
    TD_TEST_GetRstInfo(rstInfo,rstCtl);
    //
    TD_DMA_SW_INFO_S      *swInfo =  &tdCoreInfo->swInfo;
    TD_DMA_SW_CTL_S      *swCtl = &tdCoreCtl.swCtl;
    TD_TEST_GetSwInfo(swInfo,swCtl);
    //
    TD_DISP_INFO_S    *dispInfo =  &tdCoreInfo->dispInfo;
    TD_DISP_CTL_S     *dispCtl = &tdCoreCtl.dispAllCtl.dispCtl;
    TD_TEST_GetDispInfo(dispInfo,dispCtl);
    //
    TD_LAYER0_INFO_S      *layer0Info =  &tdCoreInfo->layer0Info;
    TD_LAYER0_CTL_S      *layer0Ctl = &tdCoreCtl.layer0Ctl;
    TD_TEST_GetLayer0Info(layer0Info,layer0Ctl);    
    //
    TD_LAYER4_OSD_INFO_S  *layer4OsdInfo =  &tdCoreInfo->layer4OsdInfo;
    TD_LAYER4_OSD_CTL_S  *layer4OsdCtl = &tdCoreCtl.layer4OsdCtl;
    TD_TEST_GetLayer4OsdInfo(layer4OsdInfo,layer4OsdCtl);
    //
    TD_YUV2RGB_INFO_S     *yuv2rgbInfo =  &tdCoreInfo->yuv2rgbInfo;
    TD_YUV2RGB_S         *yuv2rgb = &tdCoreCtl.yuv2rgb;
    TD_TEST_GetYuv2RgbInfo(yuv2rgbInfo,yuv2rgb);
    //
    TD_DISP_MIX_INFO_S    *dispMixInfo =  &tdCoreInfo->dispMixInfo;
    TD_DISP_MIX_CTL_S    *dispMixCtl = &tdCoreCtl.dispMixCtl;
    TD_TEST_GetDispMixInfo(dispMixInfo,dispMixCtl);
    //
    TD_DISP_IRQ_ALL_INFO_S   *dispAllIrqInfo =  &tdCoreInfo->dispIrqAllInfo;
    TD_DISP_IRQ_S        *dispIrqCtl = &tdCoreCtl.dispIrqCtl;
    TD_TEST_GetDispIrqInfo(dispAllIrqInfo,dispIrqCtl);
    //
    TD_WB_INFO_S          *wbInfo =  &tdCoreInfo->wbInfo;
    TD_WB_CTL_S          *wbCtl = &tdCoreCtl.wbCtl;
    TD_TEST_GetWBInfo(wbInfo,wbCtl);
    //
    TD_DRV_SetCore(&tdCoreCtl);
    return 0;
}
