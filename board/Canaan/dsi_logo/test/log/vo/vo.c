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
#include "common.h"
#include <k510.h>
#include <video/vo/core/vo_core_reg.h>
#include <video/vo/remap/vo_remap_reg.h>
#include <video/vo/core/vo_core_drv.h>
#include <video/vo/remap/vo_remap_drv.h>
#include <video/vo/table/vo_table_drv.h>

#include "vo/vo.h"

//unsigned int  *reg_vo_core_base  = NULL;
//unsigned int  *reg_vo_remap_base  = NULL;
//unsigned int  *reg_vo_v_scale_table_base  = NULL;
//unsigned int  *reg_vo_h_scale_table_base  = NULL;
//unsigned int  *reg_vo_gamma_table_base  = NULL;

/****************************************************************************
 * 											*
 ****************************************************************************/
static int VO_DRV_Remap( )
{
	VO_DRV_Core_Remap( );
	VO_DRV_DrawLine_Remap( );
	VO_DRV_Table_Remap( );

    return 0;
}
/****************************************************************************
 * 										*
 ****************************************************************************/
void * osal_vo_memset(void *str,int c,int count)
{
    return memset(str, c, count);
}
/****************************************************************************
 * 										*
 ****************************************************************************/
int VO_DRV_Init( )
{
    int Ret = SUCCESS;

	
    Ret = VO_DRV_Remap( );

    if(FAILURE == Ret)
    {
        return Ret;
    }
    
  //  int DevIndex = 0;
 //   for(DevIndex=0; DevIndex<ISP_MAX_DEV_NUM; DevIndex++)
  //  {
  //      osal_isp_memset(&g_astispDrvCtx[DevIndex], 0, sizeof(ISP_DRV_CTL_S));
  //  }
	
    return Ret;
}
/****************************************************************************
 * wrap											*
 ****************************************************************************/
/*
*rst
*/
static int VO_TEST_GetRST(VO_SOFT_RST_CTL_S  *rstCtl)
{
    VO_CHECK_POINTER(rstCtl);

    rstCtl->apb = 1;
    rstCtl->core = 1;
    rstCtl->disp = 1;
    rstCtl->vo = 1;

    return 0;
}
/*
*load ctl
*/
static int VO_TEST_GetLoadCtl(VO_LOAD_CTL_S *loadCtl)
{
    VO_CHECK_POINTER(loadCtl);

    loadCtl->regfirstload = 1;
    loadCtl->regready     = 1;

    return 0;
}
/*
*dma ctl
*/
static int VO_TEST_GetDmaCtl(VO_DMA_CTL_S *dmaCtl)
{
    VO_CHECK_POINTER(dmaCtl);
    //
	VO_DMA_SW_CTL_S  *sw_ctl=  &dmaCtl->sw_ctl;
    sw_ctl->reqrd  = 1;
    sw_ctl->reqwr  =1;
    //
//	VO_DMA_RD_CTL_OUT_S *rd_ctl_out=  &dmaCtl->rd_ctl_out;
//    rd_ctl_out->rdst = 0;
//    rd_ctl_out->rdrstrdy =0;
//    rd_ctl_out->wrst = 0;
//    rd_ctl_out->wrrstrdy =1;
    //
	VO_DMA_ARB_MODE_S  *arb_mode=  &dmaCtl->arb_mode;
    arb_mode->wr_arb_mode = 0;
    arb_mode->rd_arb_mode = 0;
    //
	VO_DMA_WEIGHT_RD_S *weight_rd=  &dmaCtl->weight_rd;
    weight_rd->chl0=  0x1;
    weight_rd->chl1=  0x1;
    weight_rd->chl2=  0x1;
    weight_rd->chl3=  0x1;
    weight_rd->chl4=  0x1;
    weight_rd->chl5=  0x1;
    weight_rd->chl6=  0x1;
    weight_rd->chl7=  0x1;
    weight_rd->chl8 =  0x1;
    weight_rd->chl9 =  0x1;
    weight_rd->chl10=  0x1;
    weight_rd->chl11=  0x1;
    weight_rd->chl12=  0x1;
    weight_rd->chl13=  0x1;
    weight_rd->chl14=  0x1;
    weight_rd->chl15=  0x1;
    //
	VO_DMA_PRIORITY_RD_S *prior_rd=  &dmaCtl->prior_rd;
    prior_rd->chl0=  0x0;
    prior_rd->chl1=  0x1;
    prior_rd->chl2=  0x2;
    prior_rd->chl3=  0x3;
    prior_rd->chl4=  0x4;
    prior_rd->chl5=  0x5;
    prior_rd->chl6=  0x6;
    prior_rd->chl7=  0x7;
    prior_rd->chl8 =  0x8;
    prior_rd->chl9 =  0x9;
    prior_rd->chl10=  0xa;
    prior_rd->chl11=  0xb;
    prior_rd->chl12=  0xc;
    prior_rd->chl13=  0xd;
    prior_rd->chl14=  0xe;
    prior_rd->chl15=  0xf;
    //
	VO_DMA_ID_RD_S *id_rd=  &dmaCtl->id_rd;
    id_rd->chl0=  0x0;
    id_rd->chl1=  0x1;
    id_rd->chl2=  0x2;
    id_rd->chl3=  0x3;
    id_rd->chl4=  0x4;
    id_rd->chl5=  0x5;
    id_rd->chl6=  0x6;
    id_rd->chl7=  0x7;
    id_rd->chl8 =  0x8;
    id_rd->chl9 =  0x9;
    id_rd->chl10=  0xa;
    id_rd->chl11=  0xb;
    id_rd->chl12=  0xc;
    id_rd->chl13=  0xd;
    id_rd->chl14=  0xe;
    id_rd->chl15=  0xf;

    return 0;
}
/*
*BD LAYER ctl
*/
static int VO_TEST_GetBDCtlCtl(VO_BD_LAYER_CTL_S *bdLayerCtl)
{
    VO_CHECK_POINTER(bdLayerCtl);
    //
	VO_BD_CTL_S	*layer0_line0_bd_ctl=  &bdLayerCtl->layer0_line0_bd_ctl;
    layer0_line0_bd_ctl->limiten = 1;
    layer0_line0_bd_ctl->outstand = 7;
    //    
	VO_BD_CTL_S	*layer0_line1_bd_ctl=  &bdLayerCtl->layer0_line1_bd_ctl;
    layer0_line1_bd_ctl->limiten = 1;
    layer0_line1_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer0_line2_bd_ctl=  &bdLayerCtl->layer0_line2_bd_ctl;
    layer0_line2_bd_ctl->limiten = 1;
    layer0_line2_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer0_line3_bd_ctl=  &bdLayerCtl->layer0_line3_bd_ctl;
    layer0_line3_bd_ctl->limiten = 1;
    layer0_line3_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer1_bd_ctl=  &bdLayerCtl->layer1_bd_ctl;
    layer1_bd_ctl->limiten = 1;
    layer1_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer2_bd_ctl=  &bdLayerCtl->layer2_bd_ctl;
    layer2_bd_ctl->limiten = 1;
    layer2_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer3_bd_ctl=  &bdLayerCtl->layer3_bd_ctl;
    layer3_bd_ctl->limiten = 1;
    layer3_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer4_bd_ctl=  &bdLayerCtl->layer4_bd_ctl;
    layer4_bd_ctl->limiten = 1;
    layer4_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer5_bd_ctl=  &bdLayerCtl->layer5_bd_ctl;
    layer5_bd_ctl->limiten = 1;
    layer5_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer6_bd_ctl=  &bdLayerCtl->layer6_bd_ctl;
    layer6_bd_ctl->limiten = 1;
    layer6_bd_ctl->outstand = 7;

    return 0;
}
/*
*
*/
int VO_TEST_SetWrap(void)
{
    VO_WRAP_ATTR_S voWrapAttr;
    //
    VO_SOFT_RST_CTL_S  *rstCtl=  &voWrapAttr.rstCtl;
    VO_TEST_GetRST(rstCtl);
    //
    VO_DMA_CTL_S       *dmaCtl=  &voWrapAttr.dmaCtl;
    VO_TEST_GetDmaCtl(dmaCtl);
    //
    VO_BD_LAYER_CTL_S  *bdLayerCtl=  &voWrapAttr.bdLayerCtl;
    VO_TEST_GetBDCtlCtl(bdLayerCtl);
    //
    VO_LOAD_CTL_S      *loadCtl=  &voWrapAttr.loadCtl;
    VO_TEST_GetLoadCtl(loadCtl);
    //
    VO_DRV_SetWrap(&voWrapAttr);
    return 0;
}
/****************************************************************************
 * core											*
 ****************************************************************************/
/*
*disp
*/
static int VO_TEST_GetDispInfo(VO_DISP_INFO_S  *dispInfo,VO_DISP_CTL_S *dispCtl)
{
    VO_CHECK_POINTER(dispInfo);
    VO_CHECK_POINTER(dispCtl);

    dispCtl->dispEnable = dispInfo->dispEnable;
    //
    VO_AREA_CTL_S  *xZoneCtl = &dispCtl->xZoneCtl;
    xZoneCtl->start = dispInfo->xZoneCtl_start;
    xZoneCtl->stop  = dispInfo->xZoneCtl_stop;
    //
    VO_AREA_CTL_S  *yZoneCtl = &dispCtl->yZoneCtl;
    yZoneCtl->start = dispInfo->yZoneCtl_start;
    yZoneCtl->stop  = dispInfo->yZoneCtl_stop;
    //
    VO_AREA_CTL_S  *dispHsyncCtl = &dispCtl->dispHsyncCtl;
    dispHsyncCtl->start = dispInfo->dispHsyncCtl_start;
    dispHsyncCtl->stop  = dispInfo->dispHsyncCtl_stop;
    //
    VO_AREA_CTL_S  *dispHsync1Ctl = &dispCtl->dispHsync1Ctl;
    dispHsync1Ctl->start = dispInfo->dispHsync1Ctl_start;
    dispHsync1Ctl->stop  = dispInfo->dispHsync1Ctl_stop;
    //
    VO_AREA_CTL_S  *dispVsync1Ctl = &dispCtl->dispVsync1Ctl;
    dispVsync1Ctl->start = dispInfo->dispVsync1Ctl_start;
    dispVsync1Ctl->stop  = dispInfo->dispVsync1Ctl_stop;
    //
    VO_AREA_CTL_S  *dispHsync2Ctl = &dispCtl->dispHsync2Ctl;
    dispHsync2Ctl->start = dispInfo->dispHsync2Ctl_start;
    dispHsync2Ctl->stop  = dispInfo->dispHsync2Ctl_stop;
    //
    VO_AREA_CTL_S  *dispVsync2Ctl = &dispCtl->dispVsync2Ctl;
    dispVsync2Ctl->start = dispInfo->dispVsync2Ctl_start;
    dispVsync2Ctl->stop  = dispInfo->dispVsync2Ctl_stop;
    //
    VO_DISP_CTL0_S *dispCtl0 = &dispCtl->dispCtl0;
    dispCtl0->framesyncdly = dispInfo->framesyncdly;
    dispCtl0->secndfoffset = dispInfo->secndfoffset;
    dispCtl0->vcntbit0     = dispInfo->vcntbit0;
    //
    VO_DISP_SIZE_S *dispSize = &dispCtl->dispSize; 
    dispSize->hsize = dispInfo->hsize;
    dispSize->vsize = dispInfo->vsize;
    return 0;
}
/*
*layer0
*/
/*
*MFBD
*/
static int VO_TEST_GetMfbdInfo(VO_LAYER0_MFBD_INFO_S *mfbdInfo,VO_LAYER0_MFBD_CTL_S  *layer0MfbdCtl)
{
    VO_CHECK_POINTER(mfbdInfo);
    VO_CHECK_POINTER(layer0MfbdCtl);

    layer0MfbdCtl->mfbd_en = mfbdInfo->mfbd_en;
    //y
    layer0MfbdCtl->mfbdYBuf.y_addr0 = mfbdInfo->y_addr0;
    layer0MfbdCtl->mfbdYBuf.y_addr1 = mfbdInfo->y_addr1;
    layer0MfbdCtl->mfbdYBuf.y_stride0 = mfbdInfo->y_stride0;
    layer0MfbdCtl->mfbdYBuf.y_stride1 = mfbdInfo->y_stride1;
    //y head
    layer0MfbdCtl->mfbdYHeadBuf.y_head_addr0 = mfbdInfo->y_head_addr0;
    layer0MfbdCtl->mfbdYHeadBuf.y_head_addr1 = mfbdInfo->y_head_addr1;
    layer0MfbdCtl->mfbdYHeadBuf.y_head_stride0 = mfbdInfo->y_head_stride0;
    layer0MfbdCtl->mfbdYHeadBuf.y_head_stride1 = mfbdInfo->y_head_stride1;
    //uv
    layer0MfbdCtl->mfbdUVBuf.uv_addr0 = mfbdInfo->uv_addr0;
    layer0MfbdCtl->mfbdUVBuf.uv_addr1 = mfbdInfo->uv_addr1;
    layer0MfbdCtl->mfbdUVBuf.uv_stride0 = mfbdInfo->uv_stride0;
    layer0MfbdCtl->mfbdUVBuf.uv_stride1 = mfbdInfo->uv_stride1;
    //uv head
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_addr0 = mfbdInfo->uv_head_addr0;
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_addr1 = mfbdInfo->uv_head_addr1;
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_stride0 = mfbdInfo->uv_head_stride0;
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_stride1 = mfbdInfo->uv_head_stride1;

    return 0;
}
/*
*
*/
static int VO_TEST_GetLayer0Info(VO_LAYER0_INFO_S  *layer0Info,VO_LAYER0_CTL_S *layer0Ctl)
{
    VO_CHECK_POINTER(layer0Info);
    VO_CHECK_POINTER(layer0Ctl);
    //
    layer0Ctl->layer0DispEn = layer0Info->layer0DispEn;
    layer0Ctl->layer0En = layer0Info->layer0En; 
    layer0Ctl->scalerBlen = layer0Info->scalerBlen; 
    //
    VO_LAYER0_DAT_MODE_INFO_S *datModeInfo  = &layer0Info->datModeInfo;
    VO_LAYER0_IMG_IN_DAT_MODE_S *imgInDatMode = &layer0Ctl->imgInDatMode; 
    imgInDatMode->datmode = datModeInfo->datmode;
    imgInDatMode->endianuv = datModeInfo->endianuv;
    imgInDatMode->endiany = datModeInfo->endiany;
    imgInDatMode->swi = datModeInfo->swi;
    //    
    VO_LAYER_AREA_INFO_S  *areaInfo = &layer0Info->areaInfo;
    VO_LAYER0_AREA_CTL_S  *areaCtl = &layer0Ctl->areaCtl;    
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop = areaInfo->xCtl_stop;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop = areaInfo->yCtl_stop;

    //
    VO_YUV_BUF_INFO_S    *bufInfo = &layer0Info->bufInfo;
    VO_YUV_BUF_S          *yuvBuf = &layer0Ctl->yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride;
    yuvBuf->stride.vsize = bufInfo->vsize_stride;
    //
    VO_LAYER0_SCALE_INFO_S *scaleInfo = &layer0Info->scaleInfo;
    VO_LAYER0_SCALE_S     *scaleCtl = &layer0Ctl->scaleCtl;
    scaleCtl->hScaleCtl.dstep = scaleInfo->h_dstep;
    scaleCtl->hScaleCtl.pstep = scaleInfo->h_pstep;
    scaleCtl->hScaleCtl.pstep_st = scaleInfo->h_pstep_st;
    scaleCtl->vScaleCtl.dstep = scaleInfo->v_dstep;
    scaleCtl->vScaleCtl.pstep = scaleInfo->v_pstep;
    scaleCtl->vScaleCtl.pstep_st = scaleInfo->v_pstep_st;
    //
    VO_LAYER0_SIZE_INFO_S *sizeInfo = &layer0Info->sizeInfo;
    VO_LAYER0_SIZE_S      *sizeCtl = &layer0Ctl->sizeCtl;
    sizeCtl->imgInSize.hsize = sizeInfo->in_hsize;
    sizeCtl->imgInSize.vsize = sizeInfo->in_vsize;
    sizeCtl->imgOffset.hsize = sizeInfo->offset_hsize;
    sizeCtl->imgOffset.vsize = sizeInfo->offset_vsize;
    sizeCtl->imgOutSize.hsize = sizeInfo->out_hsize;
    sizeCtl->imgOutSize.vsize = sizeInfo->out_vsize;
    //
    VO_BASE_MODE_INFO_S   *baseModeInfo = &layer0Info->baseModeInfo;
    VO_BASE_MODE_S        *baseMode = &layer0Ctl->baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;
    //
    VO_LAYER0_MFBD_INFO_S *mfbdInfo = &layer0Info->mfbdInfo;
    VO_LAYER0_MFBD_CTL_S  *layer0MfbdCtl = &layer0Ctl->layer0MfbdCtl;
    VO_TEST_GetMfbdInfo(mfbdInfo,layer0MfbdCtl);

    return 0;
}
/*
*layer1
*/
static int VO_TEST_GetLayer1Info(VO_LAYER1_INFO_S  *layer1Info,VO_LAYER1_CTL_S *layer1Ctl)
{
    VO_CHECK_POINTER(layer1Info);
    VO_CHECK_POINTER(layer1Ctl);

    layer1Ctl->layer1DispEn = layer1Info->layer1DispEn;
    //
    VO_LAYER_INFO_S *layerInfo = &layer1Info->layerInfo;
    VO_LAYER_CTL_S     *layerCtl = &layer1Ctl->layerCtl;
    layerCtl->enable    = layerInfo->enable;
    layerCtl->yuv422en  = layerInfo->yuv422en;
    layerCtl->yuv420en  = layerInfo->yuv420en;
    layerCtl->endiany   = layerInfo->endiany;        
    layerCtl->endianuv  = layerInfo->endianuv;        
    layerCtl->uvswap    = layerInfo->uvswap;      
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer1Info->areaInfo;
    VO_AREA_S          *areaCtl = &layer1Ctl->areaCtl;
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop =  areaInfo->xCtl_stop;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop =  areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer1Info->bufInfo;
    VO_YUV_BUF_S       *yuvBuf = &layer1Ctl->yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride;
    yuvBuf->stride.vsize = bufInfo->vsize_stride;
    //
    VO_LAYER_SIZE_INFO_S *layer1SizeInfo = &layer1Info->layer1SizeInfo; 
    VO_LAYER_SIZE_S    *sizeCtl = &layer1Ctl->sizeCtl;
    sizeCtl->imgInPixSize.hsize = layer1SizeInfo->in_hsize;
    sizeCtl->imgInPixSize.vsize = layer1SizeInfo->in_vsize;
    sizeCtl->imgOffset.hsize = layer1SizeInfo->offset_hsize;
    sizeCtl->imgOffset.vsize = layer1SizeInfo->offset_vsize;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer1Info->imgInBlenthInfo;
    VO_IMG_IN_BLENTH_S *imgInBlen = &layer1Ctl->imgInBlen; 
    imgInBlen->blen = imgInBlenthInfo->blen;
    imgInBlen->voffset = imgInBlenthInfo->voffset;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer1Info->baseModeInfo;
    VO_BASE_MODE_S     *baseMode = &layer1Ctl->baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;
    return 0;
}
/*
*layer2
*/
static int VO_TEST_GetLayer2Info(VO_LAYER2_INFO_S  *layer2Info,VO_LAYER2_CTL_S *layer2Ctl)
{
    VO_CHECK_POINTER(layer2Info);
    VO_CHECK_POINTER(layer2Ctl);

    layer2Ctl->layer2DispEn = layer2Info->layer2DispEn;
    //
    VO_LAYER_INFO_S *layerInfo = &layer2Info->layerInfo;
    VO_LAYER_CTL_S     *layerCtl = &layer2Ctl->layerCtl;
    layerCtl->enable    = layerInfo->enable;
    layerCtl->yuv422en  = layerInfo->yuv422en;
    layerCtl->yuv420en  = layerInfo->yuv420en;
    layerCtl->endiany   = layerInfo->endiany;        
    layerCtl->endianuv  = layerInfo->endianuv;        
    layerCtl->uvswap    = layerInfo->uvswap;      
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer2Info->areaInfo;
    VO_AREA_S          *areaCtl = &layer2Ctl->areaCtl;
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop =  areaInfo->xCtl_stop;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop =  areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer2Info->bufInfo;
    VO_YUV_BUF_S       *yuvBuf = &layer2Ctl->yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride;
    yuvBuf->stride.vsize = bufInfo->vsize_stride;
    //
    VO_LAYER_SIZE_INFO_S *layer2SizeInfo = &layer2Info->layer2SizeInfo; 
    VO_LAYER_SIZE_S    *sizeCtl = &layer2Ctl->sizeCtl;
    sizeCtl->imgInPixSize.hsize = layer2SizeInfo->in_hsize;
    sizeCtl->imgInPixSize.vsize = layer2SizeInfo->in_vsize;
    sizeCtl->imgOffset.hsize = layer2SizeInfo->offset_hsize;  
    sizeCtl->imgOffset.vsize = layer2SizeInfo->offset_vsize;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer2Info->imgInBlenthInfo;
    VO_IMG_IN_BLENTH_S *imgInBlen = &layer2Ctl->imgInBlen; 
    imgInBlen->blen = imgInBlenthInfo->blen;
    imgInBlen->voffset = imgInBlenthInfo->voffset;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer2Info->baseModeInfo;
    VO_BASE_MODE_S     *baseMode = &layer2Ctl->baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;

    return 0;
}
/*
*layer3
*/
static int VO_TEST_GetLayer3Info(VO_LAYER3_INFO_S  *layer3Info,VO_LAYER3_CTL_S *layer3Ctl)
{
    VO_CHECK_POINTER(layer3Info);
    VO_CHECK_POINTER(layer3Ctl);

    layer3Ctl->layer3DispEn = layer3Info->layer3DispEn;
    //
    VO_LAYER_INFO_S *layerInfo = &layer3Info->layerInfo;
    VO_LAYER_CTL_S     *layerCtl = &layer3Ctl->layerCtl;
    layerCtl->enable    = layerInfo->enable;
    layerCtl->yuv422en  = layerInfo->yuv422en;
    layerCtl->yuv420en  = layerInfo->yuv420en;
    layerCtl->endiany   = layerInfo->endiany;        
    layerCtl->endianuv  = layerInfo->endianuv;        
    layerCtl->uvswap    = layerInfo->uvswap;      
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer3Info->areaInfo;
    VO_AREA_S          *areaCtl = &layer3Ctl->areaCtl;
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop =  areaInfo->xCtl_stop;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop =  areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer3Info->bufInfo;
    VO_YUV_BUF_S       *yuvBuf = &layer3Ctl->yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride;
    yuvBuf->stride.vsize = bufInfo->vsize_stride;
    //
    VO_LAYER_SIZE_INFO_S *layer3SizeInfo = &layer3Info->layer3SizeInfo; 
    VO_LAYER_SIZE_S    *sizeCtl = &layer3Ctl->sizeCtl; 
    sizeCtl->imgInPixSize.hsize = layer3SizeInfo->in_hsize;
    sizeCtl->imgInPixSize.vsize = layer3SizeInfo->in_vsize;
    sizeCtl->imgOffset.hsize = layer3SizeInfo->offset_hsize;  
    sizeCtl->imgOffset.vsize = layer3SizeInfo->offset_vsize;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer3Info->imgInBlenthInfo;
    VO_IMG_IN_BLENTH_S *imgInBlen = &layer3Ctl->imgInBlen; 
    imgInBlen->blen = imgInBlenthInfo->blen;
    imgInBlen->voffset = imgInBlenthInfo->voffset;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer3Info->baseModeInfo;
    VO_BASE_MODE_S     *baseMode = &layer3Ctl->baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;
    return 0;
}
/*
*osd0
*/
static int VO_TEST_GetOsd0Info(VO_OSD0_INFO_S *osd0Info,VO_OSD0_CTL_S *osd0Ctl)
{
    VO_CHECK_POINTER(osd0Info);
    VO_CHECK_POINTER(osd0Ctl);

    osd0Ctl->osdLayer4DispEn = osd0Info->osdLayer4DispEn;
    osd0Ctl->osdrgb2yuvEn = osd0Info->osdrgb2yuvEn;
    //
    VO_OSD_CTL_S    *osdCtl = &osd0Ctl->osdCtl;
    osdCtl->alphatpye = osd0Info->alphatpye;
    osdCtl->osdtype = osd0Info->osdtype;
    //
    VO_LAYER_AREA_INFO_S *osd0AreaInfo = &osd0Info->osd0AreaInfo;
    VO_AREA_S       *osdArea = &osd0Ctl->osdArea;
    osdArea->xCtl.start = osd0AreaInfo->xCtl_start;
    osdArea->xCtl.stop = osd0AreaInfo->xCtl_stop;
    osdArea->yCtl.start = osd0AreaInfo->yCtl_start;
    osdArea->yCtl.stop = osd0AreaInfo->yCtl_stop;
    //
    VO_OSD_SIZE_INFO_S   *osd0SizeInfo = &osd0Info->osd0SizeInfo;
    VO_OSD_SIZE_S   *osdSize = &osd0Ctl->osdSize;
    osdSize->width = osd0SizeInfo->width;
    osdSize->height= osd0SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S    *osd0BufInfo = &osd0Info->osd0BufInfo;
    VO_OSD_BUF_S    *osdBuf = &osd0Ctl->osdBuf;
    osdBuf->alp_addr0 = osd0BufInfo->alp_addr0;
    osdBuf->alp_addr1 = osd0BufInfo->alp_addr1;
    osdBuf->alpstride = osd0BufInfo->alpstride;
    osdBuf->vlu_addr0 = osd0BufInfo->vlu_addr0;
    osdBuf->vlu_addr1 = osd0BufInfo->vlu_addr1;
    osdBuf->osdstride = osd0BufInfo->osdstride;
    //
    VO_OSD_DMA_INFO_S    *osd0DmaInfo = &osd0Info->osd0DmaInfo;
    VO_OSD_DMA_CTL_S *osdDmaCtl = &osd0Ctl->osdDmaCtl;
    osdDmaCtl->dmamap = osd0DmaInfo->dmamap;
    osdDmaCtl->dmarequestlen = osd0DmaInfo->dmarequestlen;
    osdDmaCtl->rgbrev = osd0DmaInfo->rgbrev;
//printf("zxj, osdDmaCtl->rgbrev = %d\n", osdDmaCtl->rgbrev);
    
    //    
    VO_BASE_MODE_INFO_S  *osd0BaseModeInfo = &osd0Info->osd0BaseModeInfo;
    VO_BASE_MODE_S  *baseMode = &osd0Ctl->baseMode;    
    baseMode->base0mask = osd0BaseModeInfo->base0mask;
    baseMode->base1mask = osd0BaseModeInfo->base1mask;
    baseMode->mode = osd0BaseModeInfo->mode;
    return 0;
}
/*
*osd1
*/
static int VO_TEST_GetOsd1Info(VO_OSD1_INFO_S *osd1Info,VO_OSD1_CTL_S *osd1Ctl)
{
    VO_CHECK_POINTER(osd1Info);
    VO_CHECK_POINTER(osd1Ctl);
    osd1Ctl->osdLayer5DispEn = osd1Info->osdLayer5DispEn;
    osd1Ctl->osdrgb2yuvEn = osd1Info->osdrgb2yuvEn;
    //
    VO_OSD_CTL_S    *osdCtl = &osd1Ctl->osdCtl;
    osdCtl->alphatpye = osd1Info->alphatpye;
    osdCtl->osdtype = osd1Info->osdtype;
    //
    VO_LAYER_AREA_INFO_S *osd1AreaInfo = &osd1Info->osd1AreaInfo;
    VO_AREA_S       *osdArea = &osd1Ctl->osdArea;
    osdArea->xCtl.start = osd1AreaInfo->xCtl_start;
    osdArea->xCtl.stop = osd1AreaInfo->xCtl_stop;
    osdArea->yCtl.start = osd1AreaInfo->yCtl_start;
    osdArea->yCtl.stop = osd1AreaInfo->yCtl_stop;
    //
    VO_OSD_SIZE_INFO_S   *osd1SizeInfo = &osd1Info->osd1SizeInfo;
    VO_OSD_SIZE_S   *osdSize = &osd1Ctl->osdSize;
    osdSize->width = osd1SizeInfo->width;
    osdSize->height= osd1SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S    *osd1BufInfo = &osd1Info->osd1BufInfo;
    VO_OSD_BUF_S    *osdBuf = &osd1Ctl->osdBuf;
    osdBuf->alp_addr0 = osd1BufInfo->alp_addr0;
    osdBuf->alp_addr1 = osd1BufInfo->alp_addr1;
    osdBuf->alpstride = osd1BufInfo->alpstride;
    osdBuf->vlu_addr0 = osd1BufInfo->vlu_addr0;
    osdBuf->vlu_addr1 = osd1BufInfo->vlu_addr1;
    osdBuf->osdstride = osd1BufInfo->osdstride;
    //
    VO_OSD_DMA_INFO_S    *osd1DmaInfo = &osd1Info->osd1DmaInfo;
    VO_OSD_DMA_CTL_S *osdDmaCtl = &osd1Ctl->osdDmaCtl;
    osdDmaCtl->dmamap = osd1DmaInfo->dmamap;
    osdDmaCtl->dmarequestlen = osd1DmaInfo->dmarequestlen;
    osdDmaCtl->rgbrev = osd1DmaInfo->rgbrev;
    //    
    VO_BASE_MODE_INFO_S  *osd1BaseModeInfo = &osd1Info->osd1BaseModeInfo;
    VO_BASE_MODE_S  *baseMode = &osd1Ctl->baseMode;    
    baseMode->base0mask = osd1BaseModeInfo->base0mask;
    baseMode->base1mask = osd1BaseModeInfo->base1mask;
    baseMode->mode = osd1BaseModeInfo->mode;
    return 0;
}
/*
*osd2
*/
static int VO_TEST_GetOsd2Info(VO_OSD2_INFO_S *osd2Info,VO_OSD2_CTL_S *osd2Ctl)
{
    VO_CHECK_POINTER(osd2Info);
    VO_CHECK_POINTER(osd2Ctl);
    osd2Ctl->osdLayer6DispEn = osd2Info->osdLayer6DispEn;
    osd2Ctl->osdrgb2yuvEn = osd2Info->osdrgb2yuvEn;
    //
    VO_OSD_CTL_S    *osdCtl = &osd2Ctl->osdCtl;
    osdCtl->alphatpye = osd2Info->alphatpye;
    osdCtl->osdtype = osd2Info->osdtype;
    //
    VO_LAYER_AREA_INFO_S *osd2AreaInfo = &osd2Info->osd2AreaInfo;
    VO_AREA_S       *osdArea = &osd2Ctl->osdArea;
    osdArea->xCtl.start = osd2AreaInfo->xCtl_start;
    osdArea->xCtl.stop = osd2AreaInfo->xCtl_stop;
    osdArea->yCtl.start = osd2AreaInfo->yCtl_start;
    osdArea->yCtl.stop = osd2AreaInfo->yCtl_stop;
    //
    VO_OSD_SIZE_INFO_S   *osd2SizeInfo = &osd2Info->osd2SizeInfo;
    VO_OSD_SIZE_S   *osdSize = &osd2Ctl->osdSize;
    osdSize->width = osd2SizeInfo->width;
    osdSize->height= osd2SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S    *osd2BufInfo = &osd2Info->osd2BufInfo;
    VO_OSD_BUF_S    *osdBuf = &osd2Ctl->osdBuf;
    osdBuf->alp_addr0 = osd2BufInfo->alp_addr0;
    osdBuf->alp_addr1 = osd2BufInfo->alp_addr1;
    osdBuf->alpstride = osd2BufInfo->alpstride;
    osdBuf->vlu_addr0 = osd2BufInfo->vlu_addr0;
    osdBuf->vlu_addr1 = osd2BufInfo->vlu_addr1;
    osdBuf->osdstride = osd2BufInfo->osdstride;
    //
    VO_OSD_DMA_INFO_S    *osd2DmaInfo = &osd2Info->osd2DmaInfo;
    VO_OSD_DMA_CTL_S *osdDmaCtl = &osd2Ctl->osdDmaCtl;
    osdDmaCtl->dmamap = osd2DmaInfo->dmamap;
    osdDmaCtl->dmarequestlen = osd2DmaInfo->dmarequestlen;
    osdDmaCtl->rgbrev = osd2DmaInfo->rgbrev;
    //    
    VO_BASE_MODE_INFO_S  *osd2BaseModeInfo = &osd2Info->osd2BaseModeInfo;
    VO_BASE_MODE_S  *baseMode = &osd2Ctl->baseMode;    
    baseMode->base0mask = osd2BaseModeInfo->base0mask;
    baseMode->base1mask = osd2BaseModeInfo->base1mask;
    baseMode->mode = osd2BaseModeInfo->mode;

    return 0;
}
/*
*Osd Rgb2Yuv
*/
static int VO_TEST_GetOsdRgb2YuvInfo(VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo,VO_OSD_RGB2YUV_S  *osdRgb2Yuv)
{
    VO_CHECK_POINTER(osdRgb2YuvInfo);
    VO_CHECK_POINTER(osdRgb2Yuv);

    osdRgb2Yuv->osdrgb2yuv_coeff[0][0]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][0];
    osdRgb2Yuv->osdrgb2yuv_coeff[0][1]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][1];
    osdRgb2Yuv->osdrgb2yuv_coeff[0][2]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][2];
    osdRgb2Yuv->osdrgb2yuv_coeff[0][3]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][3];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][0]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][0];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][1]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][1];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][2]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][2];
    osdRgb2Yuv->osdrgb2yuv_coeff[1][3]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][3];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][0]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][0];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][1]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][1];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][2]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][2];
    osdRgb2Yuv->osdrgb2yuv_coeff[2][3]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][3];
    return 0;
}
/*
*Yuv2Rgb
*/
static int VO_TEST_GetYuv2RgbInfo(VO_YUV2RGB_INFO_S *yuv2rgbInfo,VO_YUV2RGB_S *yuv2rgb)
{
    VO_CHECK_POINTER(yuv2rgbInfo);
    VO_CHECK_POINTER(yuv2rgb);

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
*Disp Mix
*/
static int VO_TEST_GetDispMixCtlInfo(VO_DISP_MIX_INFO_S *dispMixCtlInfo,VO_DISP_MIX_CTL_S *dispMixCtl)
{
    VO_CHECK_POINTER(dispMixCtlInfo);
    VO_CHECK_POINTER(dispMixCtl);
    //
    VO_MIX_INFO_S        *layerMixInfo = &dispMixCtlInfo->layerMixInfo[0];
    VO_MIX_CTL_S         *layer0mix = &dispMixCtl->layer0mix;
    layer0mix->glben  =  layerMixInfo[0].glben;
    layer0mix->sel    =  layerMixInfo[0].sel;
    layer0mix->glbalp =  layerMixInfo[0].glbalp;
    //
    VO_MIX_CTL_S         *layer1mix = &dispMixCtl->layer1mix;
    layer1mix->glben  =  layerMixInfo[1].glben;
    layer1mix->sel    =  layerMixInfo[1].sel;
    layer1mix->glbalp =  layerMixInfo[1].glbalp;
    //
    VO_MIX_CTL_S         *layer2mix = &dispMixCtl->layer2mix;
    layer2mix->glben  =  layerMixInfo[2].glben;
    layer2mix->sel    =  layerMixInfo[2].sel;
    layer2mix->glbalp =  layerMixInfo[2].glbalp;
    //
    VO_MIX_CTL_S         *layer3mix = &dispMixCtl->layer3mix;
    layer3mix->glben  =  layerMixInfo[3].glben;
    layer3mix->sel    =  layerMixInfo[3].sel;
    layer3mix->glbalp =  layerMixInfo[3].glbalp;
    //
    VO_MIX_CTL_S         *layer4mix = &dispMixCtl->layer4mix;
    layer4mix->glben  =  layerMixInfo[4].glben;
    layer4mix->sel    =  layerMixInfo[4].sel;
    layer4mix->glbalp =  layerMixInfo[4].glbalp;
    //
    VO_MIX_CTL_S         *layer5mix = &dispMixCtl->layer5mix;
    layer5mix->glben  =  layerMixInfo[5].glben;
    layer5mix->sel    =  layerMixInfo[5].sel;
    layer5mix->glbalp =  layerMixInfo[5].glbalp;
    //
    VO_MIX_CTL_S         *layer6mix = &dispMixCtl->layer6mix;
    layer6mix->glben  =  layerMixInfo[6].glben;
    layer6mix->sel    =  layerMixInfo[6].sel;
    layer6mix->glbalp =  layerMixInfo[6].glbalp;
    // 
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &dispMixCtlInfo->dispBackGroudInfo;
    VO_DISP_BACK_GROUD_S *backGroud = &dispMixCtl->backGroud;	
    backGroud->y = dispBackGroudInfo->y;
    backGroud->u = dispBackGroudInfo->u;
    backGroud->v = dispBackGroudInfo->v;

    return 0;
}
/*
*Disp iRQ
*/
static int VO_TEST_GetDispIrqInfo(VO_DISP_IRQ_INFO_S *dispIrqInfo,VO_DISP_IRQ_CTL_S *dispIrqCtl)
{
    VO_CHECK_POINTER(dispIrqInfo);
    VO_CHECK_POINTER(dispIrqCtl);
    //
    dispIrqCtl->en0 = dispIrqInfo->en0;
    dispIrqCtl->underrundcnt0 = dispIrqInfo->underrundcnt0;
    //
    dispIrqCtl->en1 = dispIrqInfo->en1;
    dispIrqCtl->underrundcnt1 = dispIrqInfo->underrundcnt1;
    //
    dispIrqCtl->en2 = dispIrqInfo->en2;
    dispIrqCtl->underrundcnt2 = dispIrqInfo->underrundcnt2;
    return 0;
}
/*
*WB
*/
static int VO_TEST_GetWBInfo(VO_WB_INFO_S *wbInfo,VO_WB_CTL_S *wbCtl)
{
    VO_CHECK_POINTER(wbInfo);
    VO_CHECK_POINTER(wbCtl);
    //
    wbCtl->wben = wbInfo->wb_en;
    wbCtl->inchmode = wbInfo->inchmode;
	wbCtl->buffersize = wbInfo->buffersize;
	wbCtl->v_size_out = wbInfo->v_size_out;
	wbCtl->h_size_out = wbInfo->h_size_out;
    //
    VO_WB_BUF_INFO_S *wbBufInfo = &wbInfo->wbBufInfo;
    VO_WB_BUF_S  *BufCtl = &wbCtl->BufCtl;
    BufCtl->yBufCtl.y_en = wbBufInfo->wbYInfo.y_en;
    BufCtl->yBufCtl.addr0 = wbBufInfo->wbYInfo.addr0;
    BufCtl->yBufCtl.addr1 = wbBufInfo->wbYInfo.addr1;
    BufCtl->yBufCtl.hstride = wbBufInfo->wbYInfo.hstride;
    BufCtl->uvBufCtl.uv_en = wbBufInfo->wbUVInfo.uv_en;
    BufCtl->uvBufCtl.addr0 = wbBufInfo->wbUVInfo.addr0;
    BufCtl->uvBufCtl.addr1 = wbBufInfo->wbUVInfo.addr1;
    BufCtl->uvBufCtl.hstride = wbBufInfo->wbUVInfo.hstride;
    //
    VO_WB_PIXEL_FORMAT_OUT_INFO_S *wbPixelFormatOutInfo = &wbInfo->wbPixelFormatOutInfo;
    VO_WB_PIXEL_FORMAT_OUT_S  *PixelFormatOut = &wbCtl->PixelFormatOut;
    PixelFormatOut->formatsel = wbPixelFormatOutInfo->formatsel;
    PixelFormatOut->inputformat = wbPixelFormatOutInfo->inputformat;
    PixelFormatOut->outputformat = wbPixelFormatOutInfo->outputformat;
    PixelFormatOut->pixelorder422 = wbPixelFormatOutInfo->pixelorder422;
    PixelFormatOut->rgbpixelwidth = wbPixelFormatOutInfo->rgbpixelwidth;
    //
    VO_WB_CH_INFO_S *ch0Info = &wbInfo->ch0Info;
    VO_WB_CH_CTL_S *ch0Ctl = &wbCtl->ch0Ctl;
    ch0Ctl->err_unit = ch0Info->err_unit;
    ch0Ctl->err_threshold = ch0Info->err_threshold;
    ch0Ctl->request = ch0Info->request;
    //
    ch0Ctl->dmaMode.blen = ch0Info->wbDmaInfo.blen;
    ch0Ctl->dmaMode.continuousmode = ch0Info->wbDmaInfo.continuousmode;
    ch0Ctl->dmaMode.errdetecten = ch0Info->wbDmaInfo.errdetecten;
    ch0Ctl->dmaMode.otnum = ch0Info->wbDmaInfo.otnum;
    ch0Ctl->dmaMode.swap = ch0Info->wbDmaInfo.swap;
    //
    ch0Ctl->infoClr.totalbw = ch0Info->wbInfoClr.totalbw;
    ch0Ctl->infoClr.maxbw = ch0Info->wbInfoClr.maxbw;
    ch0Ctl->infoClr.frmcntclear = ch0Info->wbInfoClr.frmcntclear;
    ch0Ctl->infoClr.fifoerrclear = ch0Info->wbInfoClr.fifoerrclear;
    //
    VO_WB_CH_INFO_S *ch1Info = &wbInfo->ch1Info;
    VO_WB_CH_CTL_S *ch1Ctl = &wbCtl->ch1Ctl;
    ch1Ctl->err_unit = ch1Info->err_unit;
    ch1Ctl->err_threshold = ch1Info->err_threshold;
    ch1Ctl->request = ch1Info->request;
    //
    ch1Ctl->dmaMode.blen = ch1Info->wbDmaInfo.blen;
    ch1Ctl->dmaMode.continuousmode = ch1Info->wbDmaInfo.continuousmode;
    ch1Ctl->dmaMode.errdetecten = ch1Info->wbDmaInfo.errdetecten;
    ch1Ctl->dmaMode.otnum = ch1Info->wbDmaInfo.otnum;
    ch1Ctl->dmaMode.swap = ch1Info->wbDmaInfo.swap;
    //
    ch1Ctl->infoClr.totalbw = ch1Info->wbInfoClr.totalbw;
    ch1Ctl->infoClr.maxbw = ch1Info->wbInfoClr.maxbw;
    ch1Ctl->infoClr.frmcntclear = ch1Info->wbInfoClr.frmcntclear;
    ch1Ctl->infoClr.fifoerrclear = ch1Info->wbInfoClr.fifoerrclear;

    return 0;
}
/*
*
*/
int VO_TEST_Init(void)
{
	unsigned int dispEnable = 0x0;

	VO_DRV_SetDispEn(dispEnable);
	return 0;
}
/*
*
*/
int VO_TEST_Start(void)
{
    VO_LOAD_CTL_S loadCtl;
    loadCtl.regfirstload = 1;
    loadCtl.regready = 1;
    VO_DRV_SetInit(&loadCtl);
	return 0;
}
/*
*
*/
int VO_TEST_SetCore(VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(voCoreInfo);

    VO_CORE_ATTR_S voCoreAttr;
    memset(&voCoreAttr,0x0,sizeof(voCoreAttr));
    //
    VO_DISP_INFO_S    *dispInfo = &voCoreInfo->dispInfo;
    VO_DISP_CTL_S     *dispCtl=  &voCoreAttr.dispCtl;
    VO_TEST_GetDispInfo(dispInfo,dispCtl);
    //
    VO_LAYER0_INFO_S  *layer0Info = &voCoreInfo->layer0Info;
    VO_LAYER0_CTL_S   *layer0Ctl=  &voCoreAttr.layer0Ctl;
    VO_TEST_GetLayer0Info(layer0Info,layer0Ctl);
    //
    VO_LAYER1_INFO_S  *layer1Info = &voCoreInfo->layer1Info;
    VO_LAYER1_CTL_S   *layer1Ctl=  &voCoreAttr.layer1Ctl;
    VO_TEST_GetLayer1Info(layer1Info,layer1Ctl);
    //
    VO_LAYER2_INFO_S  *layer2Info = &voCoreInfo->layer2Info;
    VO_LAYER2_CTL_S   *layer2Ctl=  &voCoreAttr.layer2Ctl;
    VO_TEST_GetLayer2Info(layer2Info,layer2Ctl);
    //
    VO_LAYER3_INFO_S  *layer3Info = &voCoreInfo->layer3Info;
    VO_LAYER3_CTL_S   *layer3Ctl=  &voCoreAttr.layer3Ctl;
    VO_TEST_GetLayer3Info(layer3Info,layer3Ctl);
    //
    VO_OSD0_INFO_S    *osd0Info = &voCoreInfo->osd0Info;
    VO_OSD0_CTL_S     *osd0Ctl=  &voCoreAttr.osd0Ctl;
    VO_TEST_GetOsd0Info(osd0Info,osd0Ctl);
    //
    VO_OSD1_INFO_S    *osd1Info = &voCoreInfo->osd1Info;
    VO_OSD1_CTL_S     *osd1Ctl=  &voCoreAttr.osd1Ctl;
    VO_TEST_GetOsd1Info(osd1Info,osd1Ctl);
    //
    VO_OSD2_INFO_S    *osd2Info = &voCoreInfo->osd2Info;
    VO_OSD2_CTL_S     *osd2Ctl=  &voCoreAttr.osd2Ctl;
    VO_TEST_GetOsd2Info(osd2Info,osd2Ctl);
    //
    VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo = &voCoreInfo->osdRgb2YuvInfo;
    VO_OSD_RGB2YUV_S  *osdRgb2Yuv=  &voCoreAttr.osdRgb2Yuv;
    VO_TEST_GetOsdRgb2YuvInfo(osdRgb2YuvInfo,osdRgb2Yuv);
    //
    VO_YUV2RGB_INFO_S   *yuv2rgbInfo = &voCoreInfo->yuv2rgbInfo; 
    VO_YUV2RGB_S      *yuv2rgb=  &voCoreAttr.yuv2rgb;
    VO_TEST_GetYuv2RgbInfo(yuv2rgbInfo,yuv2rgb);
    // 
    VO_DISP_MIX_INFO_S  *dispMixCtlInfo = &voCoreInfo->dispMixCtlInfo; 
    VO_DISP_MIX_CTL_S *dispMixCtl=  &voCoreAttr.dispMixCtl;
    VO_TEST_GetDispMixCtlInfo(dispMixCtlInfo,dispMixCtl);
    //
    voCoreAttr.ditherctlen = voCoreInfo->ditherctlen;
    voCoreAttr.clutctlen = voCoreInfo->clutctlen;
    //
    VO_DISP_IRQ_INFO_S  *dispIrqInfo = &voCoreInfo->dispIrqInfo;
    VO_DISP_IRQ_CTL_S *dispIrqCtl=  &voCoreAttr.dispIrqCtl;
    VO_TEST_GetDispIrqInfo(dispIrqInfo,dispIrqCtl);
    //
    VO_WB_INFO_S      *wbInfo = &voCoreInfo->wbInfo; 
    VO_WB_CTL_S       *wbCtl=  &voCoreAttr.wbCtl;
    VO_TEST_GetWBInfo(wbInfo,wbCtl);
    //
    VO_DRV_SetCore(&voCoreAttr);

    writel(1079 + (1 << 15) + (1919 << 16) + (0 << 31), 0x92700780);

    //writel(0x30,ISP_VO_BASE_ADDR+0x3c0);
#if 0
	writel(0x0,    0x927000c8);
	writel(0x0,    0x927000cc);
	writel(0x0,    0x927000d0);
	writel(0x0,    0x927000d4);
	writel(0x0,    0x927000d8);
	writel(0x0,    0x927000dc);
	writel(0x0,    0x927000e0);
	writel(0x0,    0x927000e4);
	writel(0x0,    0x927000f8);
	writel(0x0,    0x927000fc);
#endif

#if 0
	writel(0xf,    0x92700144);
	writel(0x3108, 0x92700148);
	writel(0x0,    0x92700154);
	writel(0x0,    0x92700158);
	writel(0x0,    0x9270015c);
	writel(0x0,    0x92700160);
	writel(0x0,    0x9270016c);
	writel(0x0,    0x9270017c);
	writel(0x100,  0x92700184);
#endif

#if 0
	writel(0x31100,0x927001c0);
	writel(0x0,    0x927001d0);
	writel(0x0,    0x927001e0);
	writel(0x100,  0x927001e4);

	writel(0x31100,0x92700200);
	writel(0x0,    0x92700208);
	writel(0x0,    0x9270020c);
	writel(0x0,    0x92700210);
	writel(0x0,    0x9270021c);
	writel(0x0,    0x92700220);
	writel(0x31100,0x92700240);
	writel(0x0,    0x92700244);
	writel(0x0,    0x92700248);
	writel(0x0,    0x9270024c);
	writel(0x0,    0x92700250);
	writel(0x0,    0x92700254);
	writel(0x0,    0x9270025c);
	writel(0x0,    0x92700260);
	writel(0x0,    0x927002a0);
	writel(0x0,    0x927002e0);

	writel(0x0,    0x92700300);
	writel(0x0,    0x92700304);
	writel(0x0,    0x92700308);
	writel(0x0,    0x9270030c);
	writel(0x0,    0x92700310);
	writel(0x0,    0x92700314);
	writel(0x7,    0x92700318);
	writel(0x0,    0x9270031c);
	writel(0x100,  0x92700320);
#endif
//	writel(0x10101,0x92700340);
//	writel(0x7f,   0x927003c0);
//	writel(0x9,    0x927003e4);
//	writel(0x100000,0x927003e8);
#if 0
	writel(0x0,    0x9270040c);
	writel(0x0,    0x92700410);
	writel(0x0,    0x92700414);
	writel(0x0,    0x92700418);
	writel(0x0,    0x9270041c);
	writel(0x0,    0x92700420);
	writel(0x0,    0x92700424);
	writel(0x0,    0x92700428);
	writel(0x0,    0x9270042c);
	writel(0x0,    0x92700440);
	writel(0x0,    0x92700444;
	writel(0x0,    0x92700448);
	writel(0x0,    0x92700464);
	writel(0x0,    0x92700468);
	writel(0x0,    0x9270046c);
#endif
    //debug
    VO_DRV_GetCoreRegsVal( );
    return 0;
}
/****************************************************************************
 * remap											*
 ****************************************************************************/
int VO_TEST_SetRemap(unsigned int draw_num,VO_REMAP_INFO_S *voRemapInfo)
{
    VO_CHECK_POINTER(voRemapInfo);
    VO_REMAP_CTL_S pstVoRemap;
    //unsigned int draw_num;
    //
    memset(&pstVoRemap,0x0,sizeof(pstVoRemap));
    //
    VO_REMAP_CMD_INFO_S  *CmdInfo = &voRemapInfo->CmdInfo;
    VO_REMAP_CTRL_FILL_CMD_S   *fillCmd = &pstVoRemap.fillCmd;
    fillCmd->fill_en_rgb       = CmdInfo->fill_en_rgb;
    fillCmd->fill_fill_en_yuv  = CmdInfo->fill_fill_en_yuv;
    fillCmd->image_active_h    = CmdInfo->image_active_h;
    fillCmd->image_active_v    = CmdInfo->image_active_v;
    //
    VO_REMAP_CTRL_INFO_S *CtlInfo = &voRemapInfo->CtlInfo[0]; 
    VO_REMAP_CTRL_FILL_CTL_S *fillCtl = &pstVoRemap.fillCtl[0];
 //   for(draw_num = VO_LINE_DRAW_AREA_0;draw_num < VO_LINE_DRAW_AREA_MAX;draw_num++)
    {
		fillCtl[draw_num].line_draw_en      = CtlInfo[draw_num].line_draw_en;
		fillCtl[draw_num].v_line_r_en       = CtlInfo[draw_num].v_line_r_en;
		fillCtl[draw_num].v_line_l_en       = CtlInfo[draw_num].v_line_l_en;
		fillCtl[draw_num].h_line_b_en       = CtlInfo[draw_num].h_line_b_en;
		fillCtl[draw_num].v_line_u_en       = CtlInfo[draw_num].v_line_u_en;
		fillCtl[draw_num].line_start_pos_x  = CtlInfo[draw_num].line_start_pos_x;
		fillCtl[draw_num].line_end_pos_x	= CtlInfo[draw_num].line_end_pos_x;
		fillCtl[draw_num].line_start_pos_y  = CtlInfo[draw_num].line_start_pos_y;
		fillCtl[draw_num].line_end_pos_y	= CtlInfo[draw_num].line_end_pos_y;		
		fillCtl[draw_num].line_width_l 		= CtlInfo[draw_num].line_width_l;
		fillCtl[draw_num].line_width_h 		= CtlInfo[draw_num].line_width_h;		
		fillCtl[draw_num].fill_value_cr 	= CtlInfo[draw_num].fill_value_cr;
		fillCtl[draw_num].fill_value_cb 	= CtlInfo[draw_num].fill_value_cb;
		fillCtl[draw_num].fill_value_y  	= CtlInfo[draw_num].fill_value_y;
		fillCtl[draw_num].fill_alpha  		= CtlInfo[draw_num].fill_alpha;
    }
    //
    VO_DRV_SetRemap(draw_num,&pstVoRemap);
    //debug
    VO_DRV_GetRemapRegsVal( );
    return 0;
}
