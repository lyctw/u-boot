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
#include "mfbc/mfbc.h"
#include <video/mfbc/wrap/mfbc_wrap_reg.h>
#include <video/mfbc/core/mfbc_core_reg.h>

//unsigned int  *reg_mfbc_wrap_base  = NULL;
//unsigned int  *reg_mfbc_core_base  = NULL;

/*
*
*/
static int MFBC_DRV_Remap(void)
{
	MFBC_DRV_Wrap_Remap( );
	MFBC_DRV_Core_Remap( );

    return 0;
}
/*
*
*/
void * osal_mfbc_memset(void *str,int c,int count)
{
    memset(str, c, count);
//    return ;
}
/*
*
*/
int MFBC_DRV_Init(void)
{
    int Ret = SUCCESS;
  //  int DevIndex = 0;
	
    Ret = MFBC_DRV_Remap( );

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
/******************************************************************************
* wrap*
******************************************************************************/
/*
*rst
*/
static int MFBC_TEST_GetRst(MFBC_WRAP_RST_S *stSwRst)
{
    MFBC_CHECK_POINTER(stSwRst);

    stSwRst->ch0ywr   =  1;
    stSwRst->ch1uvwr  =  1;
    stSwRst->ch2headwr=  1;
    stSwRst->axiwr    =  1;
    stSwRst->axird    =  1;

    return 0;
}
/*
*clk 
*/
static int MFBC_TEST_GetClk(MFBC_WRAP_CLK_EN_S *stClkEn)
{
    MFBC_CHECK_POINTER(stClkEn);

    stClkEn->ch0ywr   =  1;
    stClkEn->ch1uvwr  =  1;
    stClkEn->ch2headwr=  1;
    stClkEn->axiwr    =  1;
    stClkEn->axird    =  1;

    return 0;
}
/*
*int mask 
*/
static int MFBC_TEST_GetIntMask(MFBC_WRAP_INT_MASK_INFO_S *stIntMaskInfo,MFBC_WRAP_INT_MASK_S *stIntMsk)
{
    MFBC_CHECK_POINTER(stIntMaskInfo);
    MFBC_CHECK_POINTER(stIntMsk);

    stIntMaskInfo->headdonemask = stIntMsk->headdonemask;
    stIntMaskInfo->uvdonemask = stIntMsk->uvdonemask;
    stIntMaskInfo->ydonemask = stIntMsk->ydonemask;
    return 0;
}
/*
*DMA  
*/
static int MFBC_TEST_GetDma(MFBC_WRAP_DMA_S *stDma)
{
    MFBC_CHECK_POINTER(stDma);
    //
	MFBC_WRAP_ARBMODE_S   *arb_mode=  &stDma->arb_mode;
    arb_mode->arbmode_rd = 1;
    arb_mode->arbmode_wr = 1;
	MFBC_WRAP_WEIGHT_WR_S *weight_wr=  &stDma->weight_wr;
	weight_wr->weight_wr_ch0= 1;
	weight_wr->weight_wr_ch1= 1;
	weight_wr->weight_wr_ch2= 1;
	weight_wr->weight_wr_ch3= 1;
	weight_wr->weight_wr_ch4= 1;
	weight_wr->weight_wr_ch5= 1;
	weight_wr->weight_wr_ch6= 1;
	weight_wr->weight_wr_ch7= 1;  
    //
	MFBC_WRAP_WEIGHT_RD_S *weight_rd=  &stDma->weight_rd;
	weight_rd->weight_rd_ch0= 1;
	weight_rd->weight_rd_ch1= 1;
	weight_rd->weight_rd_ch2= 1;
	weight_rd->weight_rd_ch3= 1;
	weight_rd->weight_rd_ch4= 1;
	weight_rd->weight_rd_ch5= 1;
	weight_rd->weight_rd_ch6= 1;
	weight_rd->weight_rd_ch7= 1;
    //
	MFBC_WRAP_PRIOR_WR_S  *prior_wr=  &stDma->prior_wr;
	prior_wr->wr_ch0= 7;
	prior_wr->wr_ch1= 6;
	prior_wr->wr_ch2= 5;
	prior_wr->wr_ch3= 4;
	prior_wr->wr_ch4= 3;
	prior_wr->wr_ch5= 2;
	prior_wr->wr_ch6= 1;
	prior_wr->wr_ch7= 0;
    //
	MFBC_WRAP_PRIOR_RD_S  *prior_rd=  &stDma->prior_rd;
	prior_rd->rd_ch0= 7;
	prior_rd->rd_ch1= 6;
	prior_rd->rd_ch2= 5;
	prior_rd->rd_ch3= 4;
	prior_rd->rd_ch4= 3;
	prior_rd->rd_ch5= 2;
	prior_rd->rd_ch6= 1;
	prior_rd->rd_ch7= 0;
    //
	MFBC_WRAP_WR_ID_S     *wr_id=  &stDma->wr_id;
    wr_id->wr_ch0= 0;
    wr_id->wr_ch1= 1;
    wr_id->wr_ch2= 2;
    wr_id->wr_ch3= 3;
    wr_id->wr_ch4= 4;
    wr_id->wr_ch5= 5;
    wr_id->wr_ch6= 6;
    wr_id->wr_ch7= 7;
    //
	MFBC_WRAP_RD_ID_S     *rd_id=  &stDma->rd_id;
	rd_id->rd_ch0= 0;
	rd_id->rd_ch1= 1;
	rd_id->rd_ch2= 2;
	rd_id->rd_ch3= 3;
	rd_id->rd_ch4= 4;
	rd_id->rd_ch5= 5;
	rd_id->rd_ch6= 6;
	rd_id->rd_ch7= 7;

    return 0;
}
/*
*
*/
int MFBC_TEST_SetWrap(MFBC_WRAP_INFO_S *mfbcWrapInfo)
{
    MFBC_CHECK_POINTER(mfbcWrapInfo);
    MFBC_WRAP_ATTR_S stMfbcWrap;
    //
    MFBC_WRAP_RST_S *stSwRst = &stMfbcWrap.stSwRst;
    MFBC_TEST_GetRst(stSwRst);
    //
    stMfbcWrap.mfbc_chl_sel = mfbcWrapInfo->mfbc_chl_sel;
    //
    MFBC_WRAP_CLK_EN_S *stClkEn = &stMfbcWrap.stClkEn;
    MFBC_TEST_GetClk(stClkEn);
    //
    stMfbcWrap.stCfgdDone.done = 1;
    //
    MFBC_WRAP_INT_MASK_INFO_S *stIntMaskInfo = &mfbcWrapInfo->stIntMask;
    MFBC_WRAP_INT_MASK_S *stIntMsk = &stMfbcWrap.stIntMsk;
    MFBC_TEST_GetIntMask(stIntMaskInfo,stIntMsk);
    //
    MFBC_WRAP_DMA_S  *stDma = &stMfbcWrap.stDma;
    MFBC_TEST_GetDma(stDma);
    //
    MFBC_DRV_SetWrap(&stMfbcWrap);
    //debug
    MFBC_DRV_GetWrapRegsVal();
    return 0;
}
/******************************************************************************
* core*
******************************************************************************/
/*
*buf
*/
static int MFBC_TEST_GetBufInfo(MFBC_CORE_BUF_INFO_S *stBufInfo,MFBC_CORE_BUF_S *stMfbcBuf)
{
    MFBC_CHECK_POINTER(stBufInfo);
    MFBC_CHECK_POINTER(stMfbcBuf);
    //
    MFBC_CORE_Y_BUF_INFO_S       *stYBufInfo= &stBufInfo->stYBufInfo;
    MFBC_CORE_Y_BUF_S       *stYBuf= &stMfbcBuf->stYBuf;
    stYBuf->Addr0 = stYBufInfo->Addr0;
    stYBuf->Addr1 = stYBufInfo->Addr1;
    stYBuf->Stride = stYBufInfo->Stride;
    stYBuf->WrBlen = stYBufInfo->WrBlen;
    //
    MFBC_CORE_Y_HEAD_BUF_INFO_S  *stYHeadBufInfo= &stBufInfo->stYHeadBufInfo;
    MFBC_CORE_Y_HEAD_BUF_S  *stYHeadBuf= &stMfbcBuf->stYHeadBuf;
    stYHeadBuf->Addr0 = stYHeadBufInfo->Addr0;
    stYHeadBuf->Addr1 = stYHeadBufInfo->Addr1;
    stYHeadBuf->Stride = stYHeadBufInfo->Stride;
    stYHeadBuf->WrBlen = stYHeadBufInfo->WrBlen;
    //
    MFBC_CORE_UV_BUF_INFO_S *stUVBufInfo= &stBufInfo->stUVBufInfo;
    MFBC_CORE_UV_BUF_S      *stUVBuf= &stMfbcBuf->stUVBuf;
    stUVBuf->Addr0 = stUVBufInfo->Addr0;
    stUVBuf->Addr1 = stUVBufInfo->Addr1;
    stUVBuf->Stride = stUVBufInfo->Stride;
    stUVBuf->WrBlen = stUVBufInfo->WrBlen;
    //
    MFBC_CORE_UV_HEAD_BUF_INFO_S *stUVHeadBufInfo= &stBufInfo->stUVHeadBufInfo;
    MFBC_CORE_UV_HEAD_BUF_S *stUVHeadBuf= &stMfbcBuf->stUVHeadBuf;
    stUVHeadBuf->Addr0 = stUVHeadBufInfo->Addr0;
    stUVHeadBuf->Addr1 = stUVHeadBufInfo->Addr1;
    stUVHeadBuf->Stride = stUVHeadBufInfo->Stride;
    stUVHeadBuf->WrBlen = stUVHeadBufInfo->WrBlen;

    return 0;
}
/*
*
*/
int MFBC_TEST_SetCore(MFBC_CORE_INFO_S *mfbcCoreInfo)
{
    MFBC_CHECK_POINTER(mfbcCoreInfo);
    MFBC_CORE_ATTR_S stMfbcCore;
    //
    stMfbcCore.yuv420_en = mfbcCoreInfo->yuv420_en;
    //
    MFBC_CORE_SIZE_INFO_S  *stSizeInfo = &mfbcCoreInfo->stSizeInfo;
    MFBC_CORE_SIZE_S *stMfbcSize = &stMfbcCore.stMfbcSize;
    stMfbcSize->input_width = stSizeInfo->input_width;
    stMfbcSize->input_height = stSizeInfo->input_height;
    //
    MFBC_CORE_BUF_INFO_S *stBufInfo = &mfbcCoreInfo->stBufInfo;
    MFBC_CORE_BUF_S *stMfbcBuf = &stMfbcCore.stMfbcBuf;
    MFBC_TEST_GetBufInfo(stBufInfo,stMfbcBuf);
    //
    MFBC_DRV_SetCore(&stMfbcCore);
    //debug
    MFBC_DRV_GetCoreRegsVal();
    return 0;
}
