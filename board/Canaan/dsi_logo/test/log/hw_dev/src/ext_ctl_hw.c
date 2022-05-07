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
#include "hw_dev/inc/ext_ctl_reg.h"
#include "hw_dev/inc/ext_ctl_hw.h"
#include <sleep.h>
#include <stdio.h>
#include <k510.h>
#include <video/isp_com.h>
#include "pcal6416.h"
extern BOOL g_use_f23s_irs238c;
/*
*
*/
void RegWr32(int addr,int data)
{

	writel(data, addr);
	//msleep(2);
}
/*
*
*/
int  RegRd32( int addr )
{
	return ( readl(addr) );
}
/*
*
*/
void ExtCtlRegWr(int addr,int data)
{
    int offset_addr = EXTER_CTL_START + (addr <<2);
	RegWr32(offset_addr,data) ;
}
/*
*
*/
int ExtCtlRegRd(int addr)
{
     int offset_addr = EXTER_CTL_START +(addr <<2);
	 return(RegRd32(offset_addr));
}
/*
*
*/
void AxibusRstnActive()
{
    ExtCtlRegWr(0x0,0x00);
}
/*
*
*/
void AxibusRstnRelease()
{
    ExtCtlRegWr(0x0,0x01);
}
/*
*
*/
void IspRstnActive()
{
    ExtCtlRegWr(0x01,0x00);
}
/*
*
*/
void IspRstnRelease()
{
    ExtCtlRegWr(0x01,0x01);
}
/*
*
*/
void VideoInRstnActive()
{
    ExtCtlRegWr(0x02,0x00);
}
/*
*
*/
void VideoInRstnRelease()
{
    ExtCtlRegWr(0x02,0x01);
}
/*
*
*/
void SensorRstnActive()
{
	ExtCtlRegWr(0x04,0x00);
}
/*
*
*/
void SensorRstnRelease()
{
    ExtCtlRegWr(0x04,0x01);
}
/*
*
*/
void VideoOutRstnActive()
{
	ExtCtlRegWr(0x05,0x00);
}
/*
*
*/
void VideoOutRstnRelease()
{
	ExtCtlRegWr(0x05,0x01);
}
/*
*
*/
void format_conver_RstnRelease()
{
#ifdef CANAAN_ISP
#else
	ExtCtlRegWr(0x06,0x01);
#endif
}
/*
*
*/
int  SysIsReady()
{
	return(ExtCtlRegRd(0xff));
}
/*
*
*/
extern int g_use_f23s_imx385;
void Release_imx385_fpga_reset_n()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset
    if(g_use_f23s_imx385)
        gpio_set_pin(2 , 1);
    else       
        gpio_set_pin(0 , 1);    
#else
    //on EVB
    gpio_set_pin(11 , 1);
#endif
#else
    ExtCtlRegWr(36,0x01);
#endif

}
/*
*
*/
void Active_imx385_fpga_reset_n()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset
    
    if(g_use_f23s_imx385)
        gpio_set_pin(2 , 0);
    else
        gpio_set_pin(0 , 0);
#else
    //on EVB
    gpio_set_pin(11 , 0);
#endif
#else
    
    ExtCtlRegWr(36,0x00);
#endif

}
/*
*
*/
void Release_f23s_fpga_rst_n()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset
    gpio_set_pin(0 , 1);
#else
#ifdef _EVBLP4
    //on EVB LP4
    gpio_set_pin(9 , 1);
#else
    //on EVB LP3
    pcal6416_set_dvp_reset(1);
#endif
#endif
#else
    ExtCtlRegWr(31,0x01);
#endif

}
/*
*
*/
void Release_f23s_fpga_pwdn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to set pwdn
    gpio_set_pin(1,0);
#else
    //on EVB
    gpio_set_pin(8 , 0);
#endif
#else

    ExtCtlRegWr(32,0x00);
#endif
}
/*
*
*/
void  SysRstnRelease()
{
#ifdef CANAAN_ISP
    
#else

	while (SysIsReady() != 0x01 )
	{
		printf("%x\n",SysIsReady());
	}
	printf("system is ready to Release rst_n\n");
	AxibusRstnRelease();
	IspRstnRelease();
	VideoInRstnRelease();
	VideoOutRstnRelease();
#endif    
	printf("system rst_n  has all release\n");

}
/*
*
*/
void  SysRstActive()
{
	printf("system is ready to Release rst_n\n");
#ifdef CANAAN_ISP

#else
	AxibusRstnActive();
	msleep(1);
	IspRstnActive();
	msleep(1);
	VideoInRstnActive();
	msleep(1);
	VideoOutRstnActive();
	msleep(1);
#endif
	printf("system rst_n  has all release\n");

}
/*
*
*/
void Release_os8a10_rstn()
{
   int rdata =ExtCtlRegRd(44);
   ExtCtlRegWr(44,rdata | 0x00000001);
}
/*
*
*/
void Active_os8a10_rstn()
{
	int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata & 0xfffffffe);
}
/*
*
*/
void Release_os8a10_pwdn()
{
	int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata | 0x00000002);
}
/*
*
*/
void  Active_os8a10_pwdn()
{
	int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata & 0xfffffffd);
}
/*
*
*/
void Release_opn8008_rstn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset op8008
    gpio_set_pin(0,1);
#else
    //on EVB
    gpio_set_pin(13,1);
#endif
#else

    int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata | 0x00000004);
#endif
}
/*
*
*/
void Active_opn8008_rstn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset op8008
    gpio_set_pin(0,0);
#else
    //on EVB
    gpio_set_pin(13,0);
#endif
#else

    int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata & 0xfffffffb);
#endif
}
/*
*
*/
void Release_irs238c_rstn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset irs3218c
    //gpio_set_pin(0,1);
    if(g_use_f23s_irs238c)
    {
        gpio_set_pin(2,1);
    }
    else
    {
        gpio_set_pin(0,1);
    }
#else
    //on EVB
    gpio_set_pin(13,1);
#endif
#else

    int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata | 0x00000020);
#endif
}
/*
*
*/
void Active_irs238c_rstn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset irs3218c
    //gpio_set_pin(0,0);
    if(g_use_f23s_irs238c)
    {
        gpio_set_pin(2,0);
    }
    else
    {
        gpio_set_pin(0,0);
    }
#else
    //on EVB
    gpio_set_pin(13,0);
#endif
#else

    int rdata =ExtCtlRegRd(44);
    ExtCtlRegWr(44,rdata & 0xffffffdf);
#endif
}
/*
*
*/
void aml550_1v8_power_en()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to en 1v8
    
#else
    //no io control of 1v8 on EVB, just use a jumper  
//    gpio_set_pin(27,1);
    gpio_set_pin(1,1);

       

#endif
#else

    ExtCtlRegWr(37,0x01);
#endif
}
/*
*
*/
void aml550_2v8_power_en()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to ev 2v8
    gpio_set_pin(2,1);
#else
    //no io control of 2v8 on EVB, just use a jumper  
//    gpio_set_pin(28,1);
    gpio_set_pin(2,1);

#endif

#else

    ExtCtlRegWr(38,0x01);
#endif
}
/*
*
*/
void Release_aml550_fpga_reset()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to release reset aml550
    gpio_set_pin(3,1);
#else
    //on EVB, lcd reset is controlled by io expander PCAL6418 P0_3.
    //wait for io expander IC driver ready
    //add code here !!!
    pcal6416_mipi_dsi_reset(1);    
#endif
#else

    ExtCtlRegWr(39,0x01);
#endif
}
/*
*
*/
void Active_aml550_fpga_reset()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset aml550
    gpio_set_pin(3,0);
#else
    //on EVB, lcd reset is controlled by io expander PCAL6418 P0_3.
    //wait for io expander IC driver ready
    //add code here !!!
    pcal6416_mipi_dsi_reset(0);
#endif

#else

    ExtCtlRegWr(39,0x00);
#endif
}
/*
*
*/
void aml550_22v_power_en()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to en 22v
    gpio_set_pin(4,1);
#else
    //on EVB, lcd reset is controlled by io expander PCAL6418 P1_4.
    //wait for io expander IC driver ready
    //add code here !!!
    pcal6416_mipi_dsi_io(1);
#endif
#else

    ExtCtlRegWr(40,0x01);
#endif
}
/*
*
*/
void aml550_22v_power_off()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to disable 22v
    gpio_set_pin(4,0);
#else
    //on EVB, lcd reset is controlled by io expander PCAL6418 P1_4.
    //wait for io expander IC driver ready
    //add code here !!!
    pcal6416_mipi_dsi_io(0);
#endif
#else

    ExtCtlRegWr(40,0x00);
#endif
}
/*
*
*/
void dsi_power_en(void)
{
    //on EVB, need to enable dsi daughter board 5v power, io expander P0_5
    //wait for io expander IC driver ready
    //add code here !!!
    pcal6416_gpio_dsi_en(1);

}

void dsi_power_dis(void)
{
    //on EVB, need to enable dsi daughter board 5v power, io expander P0_5
    //wait for io expander IC driver ready
    //add code here !!!
   pcal6416_gpio_dsi_en(0);

}

void csi_power_en(void)
{
    //on EVB, need to enable csi daughter board 5v power, io expander P0_5
    //wait for io expander IC driver ready
    //add code here !!!
    pcal6416_gpio_csi_en(1);

}

void csi_power_dis(void)
{
    //on EVB, need to enable csi daughter board 5v power, io expander P0_5
    //wait for io expander IC driver ready
    //add code here !!!
   pcal6416_gpio_csi_en(0);

}

/*
*
*/
void aml550_power_on_seq()
{
#ifndef _SIMU
#if defined(_EVBLP3) || defined(_EVBLP4) 
     pcal6416_init(0);

     dsi_power_en();
//     sleep(1);
#endif     
     aml550_1v8_power_en();
//     sleep(1);
     aml550_2v8_power_en();
//     sleep(1);
     Release_aml550_fpga_reset();
//     sleep(1);
     Active_aml550_fpga_reset();
//     sleep(1);
     Release_aml550_fpga_reset();
//     sleep(1);
     aml550_22v_power_en();
//     sleep(1);
#else
    //do nothing for simu     
#endif     
}
/*
*
*/
void Active_Cv8788_rstn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset
    gpio_set_pin(5 , 0);
#else
    //use power-on reset on EVB for now
#endif
#else
    
    ExtCtlRegWr(50,0x00);
#endif

}
/*
*
*/
void Release_Cv8788_rstn()
{
#ifdef CANAAN_ISP
#ifdef _FPGA
    //use gpio to reset
    gpio_set_pin(5 , 1);
#else
    //use power-on reset on EVB for now
#endif
        
#else
    
    ExtCtlRegWr(50,0x1);
#endif
}




