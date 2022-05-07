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

#ifndef _BT1120_DEF_H_
#define _BT1120_DEF_H_

#include <video/isp_com.h>
#include <video/video_subsystem_addr.h>
#include <video/bt1120/bt1120_drv.h>
#include <video/bt1120/bt1120_reg.h>

#include "bt1120/bt1120.h"


typedef enum _BT1120_IN_SEL
{
    SEL_VO = 0,
    SEL_ISP_F_4K = 1,
    SEL_ISP_F_2K = 2,
    SEL_ISP_R_2K = 3,
    SEL_ISP_TOF =4,
}BT1120_IN_SEL;

#define   BT1120_WRAP_BASE               BT1120_BASE_ADDR + 0x0000

typedef struct  _BT_CTRL_MODE_INFO_S                       
{                                        
        unsigned int    bt_en             ;
        unsigned int    yc_reorder        ;
        unsigned int    crc_order         ;
        unsigned int    crc_init_val      ;
} BT_CTRL_MODE_INFO_S;  

typedef struct  _BT_CTRL_VBIT_INFO_S                        
{                                         
        unsigned int    bt_vbit_start     ;
        unsigned int    bt_vbit_end       ;
       
} BT_CTRL_VBIT_INFO_S;                     
										  
typedef struct  _BT_IMAGE_SIZE_TOTAL_INFO_S                             
{                                         
        unsigned int    img_vsize_total   ;
        unsigned int    img_hsize_total   ;
} BT_IMAGE_SIZE_TOTAL_INFO_S;                 
										 
typedef struct  _BT_IMAGE_SIZE_ACTIVE_INFO_S                          
{                                         
        unsigned int    img_vsize_active  ;
        unsigned int    img_hsize_active  ;

} BT_IMAGE_SIZE_ACTIVE_INFO_S;               
										 
typedef struct _BT1120_WRAP_INFO_S
{
    unsigned int                 bt_in_sel;
    unsigned int                 bt_sav_start;
    BT_CTRL_MODE_INFO_S          stCtrlModeInfo;
    BT_CTRL_VBIT_INFO_S          stCtrlVbitInfo;
    BT_IMAGE_SIZE_TOTAL_INFO_S   stSizeTotalInfo;
    BT_IMAGE_SIZE_ACTIVE_INFO_S  stSizeActiveInfo;
} BT1120_WRAP_INFO_S;

typedef struct _BT1120_INFO_S
{
    BT1120_WRAP_INFO_S  stWrapInfo;
}BT1120_INFO_S;

typedef struct _BT1120_CFG_S
{
    BT1120_IN_SEL in_sel;
    IMAGE_SIZE in_size;
}BT1120_CFG_S;

int BT1120_DRV_Init(void );
//int BT1120_config(BT1120_INFO_S *bt1120Info);
//int BT1120_Enable(unsigned int enable );void
int BT1120_TEST_SetBt1120(BT1120_INFO_S *bt1120Info);
//int BT1120_TEST(void);
int BT1120_TEST(BT1120_CFG_S *bt1120_cfg);
#endif /*_BT1120_DEF_H_*/
