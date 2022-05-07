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
#ifndef _EXT_CTL_REG_H_
#define _EXT_CTL_REG_H_

#include <video/video_subsystem_addr.h>

#define  EXTER_CTL_START  ISP_EXTCTRL_BASE_ADDR

void RegWr32(int addr,int data);
int  RegRd32( int addr );
//no use
/*
#define  AXI_RST_N_0FFSET             EXTER_CTL_START+ (0x00*4)
#define  ISP_CORE_IN_WARP_RSTN_0FFSET EXTER_CTL_START+ (0x01*4)
#define  VIDEO_IN_WARP_RSTN_0FFSET    EXTER_CTL_START+ (0x02*4)
#define  DEVICE_CTRL_RSTN_0FFSET      EXTER_CTL_START+ (0x04*4)
#define  VIDEO_OUT_RSTN_0FFSET        EXTER_CTL_START+ (0x05*4)
#define  FORMAT_CONVER_RSTN_0FFSET    EXTER_CTL_START+ (0x06*4)
#define  SYSTEM_READY_0FFSET          EXTER_CTL_START+ (0xff*4)
*/
#endif /* _EXT_CTL_REG_H_ */
