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
#include <video/isp_com.h>
#include "bt1120/bt1120.h"

int BT1120_TEST(BT1120_CFG_S *bt1120_cfg)
{
    BT1120_INFO_S bt1120Info;

    BT1120_WRAP_INFO_S  *stWrapInfo = &bt1120Info.stWrapInfo;

//	#ifndef _FPGA
    stWrapInfo->bt_in_sel = bt1120_cfg->in_sel;//SEL_VO;
//	#else
//   stWrapInfo->bt_in_sel = bt1120_cfg->in_sel;//SEL_ISP_F_4K;// fpga fixed
//	#endif
    //
    stWrapInfo->stCtrlModeInfo.bt_en = TRUE;
    stWrapInfo->stCtrlModeInfo.crc_init_val = 1;
    stWrapInfo->stCtrlModeInfo.crc_order = 0;
    stWrapInfo->stCtrlModeInfo.yc_reorder = 0;
    //
    stWrapInfo->bt_sav_start = 0x113;
    //
    stWrapInfo->stCtrlVbitInfo.bt_vbit_start = 0x0;
    stWrapInfo->stCtrlVbitInfo.bt_vbit_end = 0x2d;
    //
    stWrapInfo->stSizeTotalInfo.img_hsize_total = 2200-1;//0x897;
    stWrapInfo->stSizeTotalInfo.img_vsize_total = 1125-1;//0x464;
    //
    stWrapInfo->stSizeActiveInfo.img_hsize_active = bt1120_cfg->in_size.Width -1;//1920-1;//0x77F;
    stWrapInfo->stSizeActiveInfo.img_vsize_active = bt1120_cfg->in_size.Height -1;//1080-1;//0x437;

    BT1120_TEST_SetBt1120(&bt1120Info);

    return 0;
}
