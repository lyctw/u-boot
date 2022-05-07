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

#include <video/video_subsystem_addr.h>
#include "vi/vi.h"
#include "isp/isp.h"
#include "isp_3d/isp_3d.h"

extern unsigned int  *reg_isp_2k_wrap_base;
extern unsigned int  *reg_isp_2k_core_base;
extern unsigned int  *reg_isp_2k_ds_base;
extern unsigned int  *reg_isp_2k_table_base;
extern unsigned int  *reg_isp_2k_mfbc_base;
extern unsigned int  *reg_isp_2k_mfbd_base;
extern unsigned int  *reg_isp_2k_remap_base;

#define D_VI_WRAP_DEBUG_OPEN
#define D_VI_PIPE_DEBUG_OPEN
//#define D_ISP_WRAP_DEBUG_OPEN
//#define D_ISP_CORE_DEBUG_OPEN
//#define D_ISP_DS_DEBUG_OPEN
//#define D_ISP_MFBC_DEBUG_OPEN
//#define D_ISP_MFBD_DEBUG_OPEN
//#define D_ISP_REMAP_DEBUG_OPEN
#define D_TOF_WRAP_DEBUG_OPEN
#define D_TOF_CORE_DEBUG_OPEN
//#define D_SOC_DEBUG_OPEN
#define D_VO_CORE_DEBUG_OPEN
#define D_VO_REMAP_DEBUG_OPEN
//#define D_TD_DEBUG_OPEN
#define D_DSI_DEBUG_OPEN

void video_debug(void)
{
    printf("dump regs!\n");

    #ifdef D_DSI_DEBUG_OPEN
    for(int i =0;i<0x200;i=i+4)  //0x49c
    {
    	printf("DSI REG:Reg[0x%x]= 0x%x\n", VIDEO_DSI_BASE_ADDR+i, *(volatile unsigned int *)(VIDEO_DSI_BASE_ADDR+i));
    }
	#endif

    #ifdef D_VO_CORE_DEBUG_OPEN
    for(int i =0;i<0x4A0;i=i+4)  //0x49c
    {
    	printf("VO REG:Reg[0x%x]= 0x%x\n", ISP_VO_BASE_ADDR+i, *(volatile unsigned int *)(ISP_VO_BASE_ADDR+i));
    }
	#endif

    #ifdef D_VO_REMAP_DEBUG_OPEN
    for(int i =0;i<0x184;i=i+4)  //0x49c
    {
    	printf("VO REMAP REG:Reg[0x%x]= 0x%x\n", ISP_VO_BASE_ADDR+0x600+i, *(volatile unsigned int *)(ISP_VO_BASE_ADDR+0x600+i));
    }
	#endif

    #ifdef D_TD_DEBUG_OPEN
    for(int i =0;i<0x4A0;i=i+4)  //0x49c
    {
    	printf("TD REG:Reg[0x%x]= 0x%x\n", TD_BASE_ADDR+i, *(volatile unsigned int *)(TD_BASE_ADDR+i));
    }
	#endif

    #ifdef D_VI_WRAP_DEBUG_OPEN
    for(int i =0;i<0x80;i=i+4)  //0x49c
    {
    	printf("VI WRAP REG:Reg[0x%x]= 0x%x\n", VI_WRAP_REG_BASE+i, *(volatile unsigned int *)(VI_WRAP_REG_BASE+i));
    }
	#endif

    #ifdef D_VI_PIPE_DEBUG_OPEN
    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI00 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_0_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_0_0_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI01 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_0_1_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_0_1_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI02 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_0_2_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_0_2_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI10 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_1_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_1_0_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE DVP0 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_DVP_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_DVP_0_REG_BASE+i));
    }
	#endif

    #ifdef D_ISP_WRAP_DEBUG_OPEN
    for(int i =0;i<0x3C8;i=i+4)  //0x49c
    {
    	printf("ISP WRAP REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_wrap_base+i, *(volatile unsigned int *)(reg_isp_2k_wrap_base+i));
    }
	#endif

    #ifdef D_ISP_CORE_DEBUG_OPEN
    for(int i =0;i<0x32C;i=i+4)  //0x49c
    {
    	printf("ISP CORE REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_core_base+i, *(volatile unsigned int *)(reg_isp_2k_core_base+i));
    }
	#endif

    #ifdef D_ISP_DS_DEBUG_OPEN
    for(int i =0;i<0x368;i=i+4)  //0x49c
    {
    	printf("ISP DS REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_ds_base+i, *(volatile unsigned int *)(reg_isp_2k_ds_base+i));
    }
	#endif  

    #ifdef D_ISP_MFBC_DEBUG_OPEN
    for(int i =0;i<0x70;i=i+4)  //0x49c
    {
    	printf("ISP MFBC REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_mfbc_base+i, *(volatile unsigned int *)(reg_isp_2k_mfbc_base+i));
    }
	#endif

    #ifdef D_ISP_MFBD_DEBUG_OPEN
    for(int i =0;i<0x68;i=i+4)  //0x49c
    {
    	printf("ISP MFBD REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_mfbd_base+i, *(volatile unsigned int *)(reg_isp_2k_mfbd_base+i));
    }
	#endif

    #ifdef D_ISP_REMAP_DEBUG_OPEN
    for(int i =0;i<0x180;i=i+4)  //0x49c
    {
    	printf("ISP REMAP REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_remap_base+i, *(volatile unsigned int *)(reg_isp_2k_remap_base+i));
    }
	#endif

    #ifdef D_TOF_WRAP_DEBUG_OPEN
    for(int i =0;i<0x388;i=i+4)  //0x49c
    {
    	printf("ISP 3D WRAP REG:Reg[0x%x]= 0x%x\n", TOF_WRAP_REG_BASE+i, *(volatile unsigned int *)(TOF_WRAP_REG_BASE+i));
    }
	#endif

    #ifdef D_TOF_CORE_DEBUG_OPEN
    for(int i =0;i<0x328;i=i+4)  //0x49c
    {
    	printf("ISP 3D CORE REG:Reg[0x%x]= 0x%x\n", TOF_CORE_REG_BASE+i, *(volatile unsigned int *)(TOF_CORE_REG_BASE+i));
    }
	#endif

    #ifdef D_SOC_DEBUG_OPEN
    for(int i =0;i<0x70;i=i+4)  //0x49c
    {
    	printf("SOC MFBC REG:Reg[0x%x]= 0x%x\n", MFBC_BASE_ADDR+i, *(volatile unsigned int *)(MFBC_BASE_ADDR+i));
    }
	#endif

 
}
