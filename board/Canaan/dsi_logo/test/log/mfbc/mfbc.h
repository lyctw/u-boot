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

#ifndef _MFBC_DEF_H_
#define _MFBC_DEF_H_

#include <video/isp_com.h>
#include <video/video_subsystem_addr.h>
#include <video/mfbc/wrap/mfbc_wrap_drv.h>
#include <video/mfbc/core/mfbc_core_drv.h>

enum MFBC_WRAP_OUT_SEL_E{
    MFBC_ISP_F_4K,
    MFBC_ISP_F_2K,
    MFBC_ISP_R_2K,
};

typedef struct _MFBC_WRAP_INT_MASK_INFO_S
{
    unsigned int ydonemask;
    unsigned int uvdonemask;
    unsigned int headdonemask;
}MFBC_WRAP_INT_MASK_INFO_S;

typedef struct _MFBC_WRAP_INFO_S
{
    unsigned int mfbc_chl_sel;
    MFBC_WRAP_INT_MASK_INFO_S stIntMask;
}MFBC_WRAP_INFO_S;
/*
*
*/
typedef struct _MFBC_CORE_Y_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_Y_BUF_INFO_S;

typedef struct _MFBC_CORE_Y_HEAD_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_Y_HEAD_BUF_INFO_S;

typedef struct _MFBC_CORE_UV_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_UV_BUF_INFO_S;

typedef struct _MFBC_CORE_UV_HEAD_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_UV_HEAD_BUF_INFO_S;

typedef struct _MFBC_CORE_BUF_INFO_S
{
    MFBC_CORE_Y_BUF_INFO_S          stYBufInfo;
    MFBC_CORE_Y_HEAD_BUF_INFO_S     stYHeadBufInfo;
    MFBC_CORE_UV_BUF_INFO_S         stUVBufInfo;
    MFBC_CORE_UV_HEAD_BUF_INFO_S    stUVHeadBufInfo;
}MFBC_CORE_BUF_INFO_S;

typedef struct _MFBC_CORE_SIZE_INFO_S
{
    unsigned int                input_width;
    unsigned int                input_height;
}MFBC_CORE_SIZE_INFO_S;

typedef struct _MFBC_CORE_INFO_S
{
    unsigned char           yuv420_en;
    MFBC_CORE_SIZE_INFO_S   stSizeInfo;     
    MFBC_CORE_BUF_INFO_S    stBufInfo;
}MFBC_CORE_INFO_S;

typedef struct _MFBC_INFO_S
{
    MFBC_WRAP_INFO_S mfbcWrapInfo;
    MFBC_CORE_INFO_S mfbcCoreInfo;
}MFBC_INFO_S;
//
typedef struct _MFBC_CTL_INFO_S
{
	unsigned int yuv420_en;
	unsigned int width;
	unsigned int height;
}MFBC_CTL_INFO_S;

int MFBC_DRV_Init(void);
//int mfbc_config(MFBC_INFO_S *mfbcInfo);
int MFBC_TEST_SetWrap(MFBC_WRAP_INFO_S *mfbcWrapInfo);
int MFBC_TEST_SetCore(MFBC_CORE_INFO_S *mfbcCoreInfo);
//
int MFBC_TEST(MFBC_CTL_INFO_S *ctlInfo);

#endif /*_MFBC_DEF_H_*/
