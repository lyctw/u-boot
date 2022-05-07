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

unsigned int  *reg_bt1120_wrap_base  = NULL;
/*
*
*/
static int BT1120_DRV_Remap( )
{
	reg_bt1120_wrap_base  		  = (unsigned int *)BT1120_WRAP_BASE; 
    return 0;
}
/*
*
*/
void * osal_bt1120_memset(void *str,int c,int count)
{
    return memset(str, c, count);
}
/*
*
*/
int BT1120_DRV_Init(void )
{
    int Ret = SUCCESS;
    int DevIndex = 0;
	
    Ret = BT1120_DRV_Remap( );

    if(FAILURE == Ret)
    {
        return Ret;
    }  

    return Ret;
}
/******************************************************************************
*bt1120*
 ******************************************************************************/
/*
*size
*/
static BT1120_TEST_GetSize(BT1120_WRAP_INFO_S *stBt1120WrapInfo,BT1120_WRAP_CTL_S *stBt1120Wrap)
{
    BT1120_CHECK_POINTER(stBt1120WrapInfo);
    BT1120_CHECK_POINTER(stBt1120Wrap);

    stBt1120Wrap->bt_sav_start = stBt1120WrapInfo->bt_sav_start;
    //
    BT_CTRL_VBIT_INFO_S     *stCtrlVbitInfo = &stBt1120WrapInfo->stCtrlVbitInfo;
    BT_CTRL_VBIT_S          *stCtrlVbit = &stBt1120Wrap->stCtrlVbit;
    stCtrlVbit->bt_vbit_start = stCtrlVbitInfo->bt_vbit_start;
    stCtrlVbit->bt_vbit_end   = stCtrlVbitInfo->bt_vbit_end;
    //
    BT_IMAGE_SIZE_TOTAL_INFO_S   *stSizeTotalInfo = &stBt1120WrapInfo->stSizeTotalInfo;
    BT_IMAGE_SIZE_TOTAL_S   *stSizeTotal = &stBt1120Wrap->stSizeTotal;
    stSizeTotal->img_hsize_total = stSizeTotal->img_hsize_total;
    stSizeTotal->img_vsize_total = stSizeTotal->img_vsize_total;
    //
    BT_IMAGE_SIZE_ACTIVE_INFO_S  *stSizeActiveInfo =  &stBt1120WrapInfo->stSizeActiveInfo;
    BT_IMAGE_SIZE_ACTIVE_S  *stSizeActive = &stBt1120Wrap->stSizeActive;
    stSizeActive->img_hsize_active = stSizeActiveInfo->img_hsize_active;
    stSizeActive->img_vsize_active = stSizeActiveInfo->img_vsize_active;

    return 0;
}
/*
*ctl
*/
static BT1120_TEST_GetCtl(BT1120_WRAP_INFO_S *stBt1120WrapInfo,BT1120_WRAP_CTL_S *stBt1120Wrap)
{
    BT1120_CHECK_POINTER(stBt1120WrapInfo);
    BT1120_CHECK_POINTER(stBt1120Wrap);

    stBt1120Wrap->bt_in_sel = stBt1120WrapInfo->bt_in_sel;
    //
    BT_CTRL_MODE_INFO_S *stCtrlModeInfo = &stBt1120WrapInfo->stCtrlModeInfo;
    BT_CTRL_MODE_S  *stCtrlMode = &stBt1120Wrap->stCtrlMode;
    stCtrlMode->bt_en = stCtrlModeInfo->bt_en;
    stCtrlMode->crc_init_val = stCtrlModeInfo->crc_init_val;
    stCtrlMode->crc_order = stCtrlModeInfo->crc_order;
    stCtrlMode->yc_reorder = stCtrlModeInfo->yc_reorder;

    return 0;
}
/*
*
*/
int BT1120_TEST_SetBt1120(BT1120_INFO_S *bt1120Info)
{
    BT1120_CHECK_POINTER(bt1120Info);
    BT1120_WRAP_CTL_S  stBt1120Wrap;

    BT1120_WRAP_INFO_S *stBt1120WrapInfo = &bt1120Info->stWrapInfo;
    BT1120_TEST_GetSize(stBt1120WrapInfo,&stBt1120Wrap);
    //
    BT1120_TEST_GetCtl(stBt1120WrapInfo,&stBt1120Wrap);
    //
    stBt1120Wrap.stConfigDone.wp_clr = 1;
    stBt1120Wrap.stConfigDone.config_done = 1;
    //
    BT1120_DRV_SetBt1120(&stBt1120Wrap);

    return 0;
}
