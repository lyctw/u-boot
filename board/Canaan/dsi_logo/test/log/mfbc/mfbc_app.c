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
/******************************************************************************
* wrap*
******************************************************************************/
static int MFBC_TEST_Wrap(MFBC_WRAP_INFO_S *mfbcWrapInfo)
{
	MFBC_CHECK_POINTER(mfbcWrapInfo);

	mfbcWrapInfo->mfbc_chl_sel = MFBC_ISP_F_2K;

	MFBC_TEST_SetWrap(mfbcWrapInfo);
	return 0;
}
/******************************************************************************
* core*
******************************************************************************/
static int MFBC_TEST_Core(MFBC_CTL_INFO_S *ctlInfo,MFBC_CORE_INFO_S *mfbcCoreInfo)
{
	  MFBC_CHECK_POINTER(mfbcCoreInfo);

	  mfbcCoreInfo->yuv420_en = ctlInfo->yuv420_en;

    MFBC_CORE_SIZE_INFO_S   *stSizeInfo = &mfbcCoreInfo->stSizeInfo;
    stSizeInfo->input_width = ctlInfo->width;
    stSizeInfo->input_height = ctlInfo->height;

    MFBC_CORE_BUF_INFO_S    *stBufInfo = &mfbcCoreInfo->stBufInfo;
    MFBC_CORE_Y_BUF_INFO_S          *stYBufInfo = &stBufInfo->stYBufInfo;
    stYBufInfo->Addr0 = MFBC_Y_DATA_WR_ADDR0;
    stYBufInfo->Addr1 = MFBC_Y_DATA_WR_ADDR1;
    stYBufInfo->Stride = MFBC_DATA_STRIDE*4;
    stYBufInfo->WrBlen = 7;

    MFBC_CORE_Y_HEAD_BUF_INFO_S     *stYHeadBufInfo = &stBufInfo->stYHeadBufInfo;
    stYHeadBufInfo->Addr0 = MFBC_Y_HEAD_WR_ADDR0;
    stYHeadBufInfo->Addr1 = MFBC_Y_HEAD_WR_ADDR1;
    stYHeadBufInfo->Stride = MFBC_DATA_STRIDE*4/32;
    stYHeadBufInfo->WrBlen = 3;

    MFBC_CORE_UV_BUF_INFO_S         *stUVBufInfo = &stBufInfo->stUVBufInfo;
    stUVBufInfo->Addr0 = MFBC_UV_DATA_WR_ADDR0;
    stUVBufInfo->Addr1 = MFBC_UV_DATA_WR_ADDR1;
    stUVBufInfo->Stride = MFBC_DATA_STRIDE*4;
    stUVBufInfo->WrBlen = 7;
    MFBC_CORE_UV_HEAD_BUF_INFO_S    *stUVHeadBufInfo = &stBufInfo->stUVHeadBufInfo;
    stUVHeadBufInfo->Addr0 = MFBC_UV_HEAD_WR_ADDR0;
    stUVHeadBufInfo->Addr1 = MFBC_UV_HEAD_WR_ADDR1;
    stUVHeadBufInfo->Stride = MFBC_DATA_STRIDE*4/32;
    stUVHeadBufInfo->WrBlen = 3;
    //
    MFBC_TEST_SetCore(mfbcCoreInfo);
    return 0;
}
/*
 *
 */
int MFBC_TEST(MFBC_CTL_INFO_S *ctlInfo)
{
	MFBC_INFO_S mfbcInfo;
	//
	MFBC_WRAP_INFO_S *mfbcWrapInfo = &mfbcInfo.mfbcWrapInfo;
	MFBC_TEST_Wrap(mfbcWrapInfo);
	//
	MFBC_CORE_INFO_S *mfbcCoreInfo = &mfbcInfo.mfbcCoreInfo;
	MFBC_TEST_Core(ctlInfo,mfbcCoreInfo);
	return 0;
}
