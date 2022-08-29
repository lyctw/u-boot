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
/*
 * cnds_dsi_test.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Administrator
 */
#include "video/mipi/dsi/cnds_dsi_define.h"
#include "video/mipi/dsi/cnds_dsi_hw.h"
#include <sleep.h>
#include <stdio.h>
#include <stdio.h>
#include <io.h>
#include "sysctl_clk.h"
#include "sysctl_rst.h"

#include "k510.h"

void wait_phy_pll_locked()
{
	while (1)
	{
		if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x01) == 0x01)
		{     break;}
	}
}

void wait_cklane_rdy()
{
	while (1)
	{
		if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x02) == 0x02)
		{     break;}
	}
}




void wait_dat1_rdy()
{
	while (1)
	{
		if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x04) == 0x04)
		{     break;}
	}
}



void wait_dat2_rdy()
{
	while (1)
	{
		if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x08) == 0x08)
		{     break;}
	}
}




void wait_dat3_rdy()
{
	while (1)
	{
		if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x10) == 0x10)
		{     break;}
	}
}




void wait_dat4_rdy()
{
	while (1)
	{
		if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x20) == 0x20)
		{     break;}
	}
}


void  dsc_cmd_send(int par, int data1, int data2)
{
	int cmd_sts =0;
	if(par == 0)
	{
		//                DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x02) //[1]enable  write_completed_en
		DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01020500); //[24] cmd_lp_en  =1
		//[23:14] cmd_size  =cmd_size. 1 or 2           2
		//[13:8] cmd_head  =0x39
		//[3 ] cmd_longnotshort  =0x1
		//[2:0] cmd_nat : 3'b000:write command
		//                3'b001:read command
		//                3'b100:TE request
		//                3'b101:trigger request
		//                3'b110:BTA request
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,data1);// DATA
		DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
		while((cmd_sts & 0x02 )!= 0x02)
		{
			cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		}
		DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
	}
	else  if(par == 1)
	{
		//DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x02) //[1]enable  write_completed_en
		DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01011500); //[24] cmd_lp_en  =1
		//[23:14] cmd_size  =cmd_size. 1 or 2
		//[13:8] cmd_head  =0x39
		//[3 ] cmd_longnotshort  =0x1
		//[2:0] cmd_nat : 3'b000:write command
		//                3'b001:read command
		//                3'b100:TE request
		//                3'b101:trigger request
		//                3'b110:BTA request
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data2<<8)+data1));// DATA
		DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
		while((cmd_sts & 0x02) != 0x02)
		{
			cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		}
		DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
	}
	else if(par == 2)
	{
		DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01023908); //[24] cmd_lp_en  =1              0x01023908
		//[23:14] cmd_size  =cmd_size. 1 or 2
		//[13:8] cmd_head  =0x39
		//[3 ] cmd_longnotshort  =0x1
		//[2:0] cmd_nat : 3'b000:write command
		//                3'b001:read command
		//                3'b100:TE request
		//                3'b101:trigger request
		//                3'b110:BTA request
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data2<<8)+data1));// DATA
		DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
		while((cmd_sts & 0x02 )!= 0x02)
		{
			cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		}
		DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed

	}
}

void  dsc_cmd_hs_send(int par, int data1, int data2)
{
	int cmd_sts =0;
	if(par == 0)
	{
		//                DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x02) //[1]enable  write_completed_en
		DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x00020500); //[24] cmd_lp_en  =1
		//[23:14] cmd_size  =cmd_size. 1 or 2           2
		//[13:8] cmd_head  =0x39
		//[3 ] cmd_longnotshort  =0x1
		//[2:0] cmd_nat : 3'b000:write command
		//                3'b001:read command
		//                3'b100:TE request
		//                3'b101:trigger request
		//                3'b110:BTA request
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,data1);// DATA
		DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
		while((cmd_sts & 0x02 )!= 0x02)
		{
			cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		}
		DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
	}
	else  if(par == 1)
	{
		//DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x02) //[1]enable  write_completed_en
		DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x00011500); //[24] cmd_lp_en  =1
		//[23:14] cmd_size  =cmd_size. 1 or 2
		//[13:8] cmd_head  =0x39
		//[3 ] cmd_longnotshort  =0x1
		//[2:0] cmd_nat : 3'b000:write command
		//                3'b001:read command
		//                3'b100:TE request
		//                3'b101:trigger request
		//                3'b110:BTA request
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data2<<8)+data1));// DATA
		DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
		while((cmd_sts & 0x02) != 0x02)
		{
			cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		}
		DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
	}
	else if(par == 2)
	{
		DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x00023908); //[24] cmd_lp_en  =1              0x01023908
		//[23:14] cmd_size  =cmd_size. 1 or 2
		//[13:8] cmd_head  =0x39
		//[3 ] cmd_longnotshort  =0x1
		//[2:0] cmd_nat : 3'b000:write command
		//                3'b001:read command
		//                3'b100:TE request
		//                3'b101:trigger request
		//                3'b110:BTA request
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data2<<8)+data1));// DATA
		DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
		while((cmd_sts & 0x02 )!= 0x02)
		{
			cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		}
		DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed

	}
}

void dsc_cmd_read(int addr)
{
	int cmd_sts =0;
	int data = 0;
	int size;
	int err;
	int reg = 0;

	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0xffffffff);
	DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);

	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01010601);           //[24] cmd_lp_en  =1            0x01010601
	//[23:16] cmd_size  =cmd_size. 1 or 2
	//[14:15] cmd_type  0 write  1 read                     1
	//[13:8] cmd_head  =0x5                                 6
	//[3 ] cmd_longnotshort  =0x1                           1
	//[2:0] cmd_nat : 3'b000:write command                  01
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request

	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET, addr);

	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0xffffffff); // cmd send


	while((cmd_sts & 0x08 )!= 0x08)                                 //wait read success
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}

	err = DsiRegRd(DIRECT_CMD_RD_STS_OFFSET);                   //read err
	size = DsiRegRd(DIRECT_CMD_RD_PROPERTY_OFFSET);             // read size [16 - 23]
	data = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);                   //read data ;

	k510_logci("err is 0x%8x, size is 0x%8x, data is 0x%8x \n", err, size, data);
}

void dsc_cmd_hs_read(int addr)
{
	int cmd_sts =0;
	int data = 0;
	int size;
	int err;
	int reg = 0;

	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0xffffffff);
	DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);

	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x00010601);           //[24] cmd_lp_en  =1            0x01010601
	//[23:16] cmd_size  =cmd_size. 1 or 2
	//[14:15] cmd_type  0 write  1 read                     1
	//[13:8] cmd_head  =0x5                                 6
	//[3 ] cmd_longnotshort  =0x1                           1
	//[2:0] cmd_nat : 3'b000:write command                  01
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request

	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET, addr);

	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0xffffffff); // cmd send


	while((cmd_sts & 0x08 )!= 0x08)                                 //wait read success
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}

	err = DsiRegRd(DIRECT_CMD_RD_STS_OFFSET);                   //read err
	size = DsiRegRd(DIRECT_CMD_RD_PROPERTY_OFFSET);             // read size [16 - 23]
	data = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);                   //read data ;

	k510_logci("err is 0x%8x, size is 0x%8x, data is 0x%8x \n", err, size, data);
}

void  aml_lcd_init()
{
	DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0);//0x02); //[1]enable  write_completed_en
	k510_logci("lcd init 1\n");

	dsc_cmd_send(2,0xFF,0x01);

	//       dsc_cmd_read(0x0d);

	k510_logci("lcd init 2\n");

	dsc_cmd_send(2,0xFB,0x01);

	k510_logci("lcd init 3\n");

	dsc_cmd_send(2,0xFF,0x02);
	k510_logci("lcd init 4\n");

	dsc_cmd_send(2,0xFB,0x01);
	k510_logci("lcd init 5\n");


	dsc_cmd_send(2,0xFF,0x03);

	k510_logci("lcd init 6\n");
	dsc_cmd_send(2,0xFB,0x01);
	k510_logci("lcd init 7\n");

	dsc_cmd_send(2,0xFF,0x04);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0xFF,0x05);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0xD7,0x31);
	dsc_cmd_send(2,0xD8,0x7E);
	//Delay(100);
#ifndef _SIMU
	msleep(100);
#endif
	dsc_cmd_send(2,0xFF,0x00);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0xBA,0x03);
	dsc_cmd_send(2,0x36,0x00);
	dsc_cmd_send(2,0xB0,0x00);
	dsc_cmd_send(2,0xD3,0x08);
	dsc_cmd_send(2,0xD4,0x0E);
	dsc_cmd_send(2,0xD5,0x0F);
	dsc_cmd_send(2,0xD6,0x48);
	dsc_cmd_send(2,0xD7,0x00);
	dsc_cmd_send(2,0xD9,0x00);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0xFF,0xEE);
	dsc_cmd_send(2,0x40,0x00);
	dsc_cmd_send(2,0x41,0x00);
	dsc_cmd_send(2,0x42,0x00);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0xFF,0x01);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0x01,0x55);
	dsc_cmd_send(2,0x04,0x0C);
	dsc_cmd_send(2,0x05,0x3A);
	dsc_cmd_send(2,0x06,0x50);
	dsc_cmd_send(2,0x07,0xD0);
	dsc_cmd_send(2,0x0A,0x0F);
	dsc_cmd_send(2,0x0C,0x06);
	dsc_cmd_send(2,0x0D,0x7F);
	dsc_cmd_send(2,0x0E,0x7F);
	dsc_cmd_send(2,0x0F,0x70);
	dsc_cmd_send(2,0x10,0x63);
	dsc_cmd_send(2,0x11,0x3C);
	dsc_cmd_send(2,0x12,0x5C);
	dsc_cmd_send(2,0x13,0x5A);
	dsc_cmd_send(2,0x14,0x5A);
	dsc_cmd_send(2,0x15,0x60);
	dsc_cmd_send(2,0x16,0x15);
	dsc_cmd_send(2,0x17,0x15);
	dsc_cmd_send(2,0x23,0x00);
	dsc_cmd_send(2,0x24,0x00);
	dsc_cmd_send(2,0x25,0x00);
	dsc_cmd_send(2,0x26,0x00);
	dsc_cmd_send(2,0x27,0x00);
	dsc_cmd_send(2,0x28,0x00);
	dsc_cmd_send(2,0x44,0x00);
	dsc_cmd_send(2,0x45,0x00);
	dsc_cmd_send(2,0x46,0x00);
	dsc_cmd_send(2,0x5B,0xCA);
	dsc_cmd_send(2,0x5C,0x00);
	dsc_cmd_send(2,0x5D,0x00);
	dsc_cmd_send(2,0x5E,0x2D);
	dsc_cmd_send(2,0x5F,0x1B);
	dsc_cmd_send(2,0x60,0xD5);
	dsc_cmd_send(2,0x61,0xF7);
	dsc_cmd_send(2,0x6C,0xAB);
	dsc_cmd_send(2,0x6D,0x44);
	//dsc_cmd_send(2,0x6E,0x80);
	dsc_cmd_send(2,0xFF,0x05);
	dsc_cmd_send(2,0xFB,0x01);
	dsc_cmd_send(2,0x00,0x3F);
	dsc_cmd_send(2,0x01,0x3F);
	dsc_cmd_send(2,0x02,0x3F);
	dsc_cmd_send(2,0x03,0x3F);
	dsc_cmd_send(2,0x04,0x38);
	dsc_cmd_send(2,0x05,0x3F);
	dsc_cmd_send(2,0x06,0x3F);
	dsc_cmd_send(2,0x07,0x19);
	dsc_cmd_send(2,0x08,0x1D);
	dsc_cmd_send(2,0x09,0x3F);
	dsc_cmd_send(2,0x0A,0x3F);
	dsc_cmd_send(2,0x0B,0x1B);
	dsc_cmd_send(2,0x0C,0x17);
	dsc_cmd_send(2,0x0D,0x3F);
	dsc_cmd_send(2,0x0E,0x3F);
	dsc_cmd_send(2,0x0F,0x08);
	dsc_cmd_send(2,0x10,0x3F);
	dsc_cmd_send(2,0x11,0x10);
	dsc_cmd_send(2,0x12,0x3F);
	dsc_cmd_send(2,0x13,0x3F);
	dsc_cmd_send(2,0x14,0x3F);
	dsc_cmd_send(2,0x15,0x3F);
	dsc_cmd_send(2,0x16,0x3F);
	dsc_cmd_send(2,0x17,0x3F);
	dsc_cmd_send(2,0x18,0x38);
	dsc_cmd_send(2,0x19,0x18);
	dsc_cmd_send(2,0x1A,0x1C);
	dsc_cmd_send(2,0x1B,0x3F);
	dsc_cmd_send(2,0x1C,0x3F);
	dsc_cmd_send(2,0x1D,0x1A);
	dsc_cmd_send(2,0x1E,0x16);
	dsc_cmd_send(2,0x1F,0x3F);
	dsc_cmd_send(2,0x20,0x3F);
	dsc_cmd_send(2,0x21,0x3F);
	dsc_cmd_send(2,0x22,0x3F);
	dsc_cmd_send(2,0x23,0x06);
	dsc_cmd_send(2,0x24,0x3F);
	dsc_cmd_send(2,0x25,0x0E);
	dsc_cmd_send(2,0x26,0x3F);
	dsc_cmd_send(2,0x27,0x3F);
	dsc_cmd_send(2,0x54,0x06);
	dsc_cmd_send(2,0x55,0x05);
	dsc_cmd_send(2,0x56,0x04);
	dsc_cmd_send(2,0x58,0x03);
	dsc_cmd_send(2,0x59,0x1B);
	dsc_cmd_send(2,0x5A,0x1B);
	dsc_cmd_send(2,0x5B,0x01);
	dsc_cmd_send(2,0x5C,0x32);
	dsc_cmd_send(2,0x5E,0x18);
	dsc_cmd_send(2,0x5F,0x20);
	dsc_cmd_send(2,0x60,0x2B);
	dsc_cmd_send(2,0x61,0x2C);
	dsc_cmd_send(2,0x62,0x18);
	dsc_cmd_send(2,0x63,0x01);
	dsc_cmd_send(2,0x64,0x32);
	dsc_cmd_send(2,0x65,0x00);
	dsc_cmd_send(2,0x66,0x44);
	dsc_cmd_send(2,0x67,0x11);
	dsc_cmd_send(2,0x68,0x01);
	dsc_cmd_send(2,0x69,0x01);
	dsc_cmd_send(2,0x6A,0x04);
	dsc_cmd_send(2,0x6B,0x2C);
	dsc_cmd_send(2,0x6C,0x08);
	dsc_cmd_send(2,0x6D,0x08);
	dsc_cmd_send(2,0x78,0x00);
	dsc_cmd_send(2,0x79,0x00);
	dsc_cmd_send(2,0x7E,0x00);
	dsc_cmd_send(2,0x7F,0x00);
	dsc_cmd_send(2,0x80,0x00);
	dsc_cmd_send(2,0x81,0x00);
	dsc_cmd_send(2,0x8D,0x00);
	dsc_cmd_send(2,0x8E,0x00);
	dsc_cmd_send(2,0x8F,0xC0);
	dsc_cmd_send(2,0x90,0x73);
	dsc_cmd_send(2,0x91,0x10);
	dsc_cmd_send(2,0x92,0x07);
	dsc_cmd_send(2,0x96,0x11);
	dsc_cmd_send(2,0x97,0x14);
	dsc_cmd_send(2,0x98,0x00);
	dsc_cmd_send(2,0x99,0x00);
	dsc_cmd_send(2,0x9A,0x00);
	dsc_cmd_send(2,0x9B,0x61);
	dsc_cmd_send(2,0x9C,0x15);
	dsc_cmd_send(2,0x9D,0x30);
	dsc_cmd_send(2,0x9F,0x0F);
	dsc_cmd_send(2,0xA2,0xB0);
	dsc_cmd_send(2,0xA7,0x0A);
	dsc_cmd_send(2,0xA9,0x00);
	dsc_cmd_send(2,0xAA,0x70);
	dsc_cmd_send(2,0xAB,0xDA);
	dsc_cmd_send(2,0xAC,0xFF);
	dsc_cmd_send(2,0xAE,0xF4);
	dsc_cmd_send(2,0xAF,0x40);
	dsc_cmd_send(2,0xB0,0x7F);
	dsc_cmd_send(2,0xB1,0x16);
	dsc_cmd_send(2,0xB2,0x53);
	dsc_cmd_send(2,0xB3,0x00);
	dsc_cmd_send(2,0xB4,0x2A);
	dsc_cmd_send(2,0xB5,0x3A);
	dsc_cmd_send(2,0xB6,0xF0);
	dsc_cmd_send(2,0xBC,0x85);
	dsc_cmd_send(2,0xBD,0xF4);
	dsc_cmd_send(2,0xBE,0x33);
	dsc_cmd_send(2,0xBF,0x13);
	dsc_cmd_send(2,0xC0,0x77);
	dsc_cmd_send(2,0xC1,0x77);
	dsc_cmd_send(2,0xC2,0x77);
	dsc_cmd_send(2,0xC3,0x77);
	dsc_cmd_send(2,0xC4,0x77);
	dsc_cmd_send(2,0xC5,0x77);
	dsc_cmd_send(2,0xC6,0x77);
	dsc_cmd_send(2,0xC7,0x77);
	dsc_cmd_send(2,0xC8,0xAA);
	dsc_cmd_send(2,0xC9,0x2A);
	dsc_cmd_send(2,0xCA,0x00);
	dsc_cmd_send(2,0xCB,0xAA);
	dsc_cmd_send(2,0xCC,0x92);
	dsc_cmd_send(2,0xCD,0x00);
	dsc_cmd_send(2,0xCE,0x18);
	dsc_cmd_send(2,0xCF,0x88);
	dsc_cmd_send(2,0xD0,0xAA);
	dsc_cmd_send(2,0xD1,0x00);
	dsc_cmd_send(2,0xD2,0x00);
	dsc_cmd_send(2,0xD3,0x00);
	dsc_cmd_send(2,0xD6,0x02);
	dsc_cmd_send(2,0xED,0x00);
	dsc_cmd_send(2,0xEE,0x00);
	dsc_cmd_send(2,0xEF,0x70);
	dsc_cmd_send(2,0xFA,0x03);
	dsc_cmd_send(2,0xFF,0x00);

	////page selection cmd start
	dsc_cmd_send(2,0xFF,0x01);
	dsc_cmd_send(2,0xFB,0x01);
	////page selection cmd end
	////R(+) MCR cmd
	dsc_cmd_send(2,0x75,0x00);
	dsc_cmd_send(2,0x76,0x00);
	dsc_cmd_send(2,0x77,0x00);
	dsc_cmd_send(2,0x78,0x2C);
	dsc_cmd_send(2,0x79,0x00);
	dsc_cmd_send(2,0x7A,0x4F);
	dsc_cmd_send(2,0x7B,0x00);
	dsc_cmd_send(2,0x7C,0x69);
	dsc_cmd_send(2,0x7D,0x00);
	dsc_cmd_send(2,0x7E,0x7F);
	dsc_cmd_send(2,0x7F,0x00);
	dsc_cmd_send(2,0x80,0x92);
	dsc_cmd_send(2,0x81,0x00);
	dsc_cmd_send(2,0x82,0xA3);
	dsc_cmd_send(2,0x83,0x00);
	dsc_cmd_send(2,0x84,0xB3);
	dsc_cmd_send(2,0x85,0x00);
	dsc_cmd_send(2,0x86,0xC1);
	dsc_cmd_send(2,0x87,0x00);
	dsc_cmd_send(2,0x88,0xF3);
	dsc_cmd_send(2,0x89,0x01);
	dsc_cmd_send(2,0x8A,0x1B);
	dsc_cmd_send(2,0x8B,0x01);
	dsc_cmd_send(2,0x8C,0x5A);
	dsc_cmd_send(2,0x8D,0x01);
	dsc_cmd_send(2,0x8E,0x8B);
	dsc_cmd_send(2,0x8F,0x01);
	dsc_cmd_send(2,0x90,0xD9);
	dsc_cmd_send(2,0x91,0x02);
	dsc_cmd_send(2,0x92,0x16);
	dsc_cmd_send(2,0x93,0x02);
	dsc_cmd_send(2,0x94,0x18);
	dsc_cmd_send(2,0x95,0x02);
	dsc_cmd_send(2,0x96,0x4E);
	dsc_cmd_send(2,0x97,0x02);
	dsc_cmd_send(2,0x98,0x88);
	dsc_cmd_send(2,0x99,0x02);
	dsc_cmd_send(2,0x9A,0xAC);
	dsc_cmd_send(2,0x9B,0x02);
	dsc_cmd_send(2,0x9C,0xDD);
	dsc_cmd_send(2,0x9D,0x03);
	dsc_cmd_send(2,0x9E,0x01);
	dsc_cmd_send(2,0x9F,0x03);
	dsc_cmd_send(2,0xA0,0x2E);
	dsc_cmd_send(2,0xA2,0x03);
	dsc_cmd_send(2,0xA3,0x3C);
	dsc_cmd_send(2,0xA4,0x03);
	dsc_cmd_send(2,0xA5,0x4C);
	dsc_cmd_send(2,0xA6,0x03);
	dsc_cmd_send(2,0xA7,0x5D);
	dsc_cmd_send(2,0xA9,0x03);
	dsc_cmd_send(2,0xAA,0x70);
	dsc_cmd_send(2,0xAB,0x03);
	dsc_cmd_send(2,0xAC,0x88);
	dsc_cmd_send(2,0xAD,0x03);
	dsc_cmd_send(2,0xAE,0xA8);
	dsc_cmd_send(2,0xAF,0x03);
	dsc_cmd_send(2,0xB0,0xC8);
	dsc_cmd_send(2,0xB1,0x03);
	dsc_cmd_send(2,0xB2,0xFF);
	////R(-) MCR cmd
	dsc_cmd_send(2,0xB3,0x00);
	dsc_cmd_send(2,0xB4,0x00);
	dsc_cmd_send(2,0xB5,0x00);
	dsc_cmd_send(2,0xB6,0x2C);
	dsc_cmd_send(2,0xB7,0x00);
	dsc_cmd_send(2,0xB8,0x4F);
	dsc_cmd_send(2,0xB9,0x00);
	dsc_cmd_send(2,0xBA,0x69);
	dsc_cmd_send(2,0xBB,0x00);
	dsc_cmd_send(2,0xBC,0x7F);
	dsc_cmd_send(2,0xBD,0x00);
	dsc_cmd_send(2,0xBE,0x92);
	dsc_cmd_send(2,0xBF,0x00);
	dsc_cmd_send(2,0xC0,0xA3);
	dsc_cmd_send(2,0xC1,0x00);
	dsc_cmd_send(2,0xC2,0xB3);
	dsc_cmd_send(2,0xC3,0x00);
	dsc_cmd_send(2,0xC4,0xC1);
	dsc_cmd_send(2,0xC5,0x00);
	dsc_cmd_send(2,0xC6,0xF3);
	dsc_cmd_send(2,0xC7,0x01);
	dsc_cmd_send(2,0xC8,0x1B);
	dsc_cmd_send(2,0xC9,0x01);
	dsc_cmd_send(2,0xCA,0x5A);
	dsc_cmd_send(2,0xCB,0x01);
	dsc_cmd_send(2,0xCC,0x8B);
	dsc_cmd_send(2,0xCD,0x01);
	dsc_cmd_send(2,0xCE,0xD9);
	dsc_cmd_send(2,0xCF,0x02);
	dsc_cmd_send(2,0xD0,0x16);
	dsc_cmd_send(2,0xD1,0x02);
	dsc_cmd_send(2,0xD2,0x18);
	dsc_cmd_send(2,0xD3,0x02);
	dsc_cmd_send(2,0xD4,0x4E);
	dsc_cmd_send(2,0xD5,0x02);
	dsc_cmd_send(2,0xD6,0x88);
	dsc_cmd_send(2,0xD7,0x02);
	dsc_cmd_send(2,0xD8,0xAC);
	dsc_cmd_send(2,0xD9,0x02);
	dsc_cmd_send(2,0xDA,0xDD);
	dsc_cmd_send(2,0xDB,0x03);
	dsc_cmd_send(2,0xDC,0x01);
	dsc_cmd_send(2,0xDD,0x03);
	dsc_cmd_send(2,0xDE,0x2E);
	dsc_cmd_send(2,0xDF,0x03);
	dsc_cmd_send(2,0xE0,0x3C);
	dsc_cmd_send(2,0xE1,0x03);
	dsc_cmd_send(2,0xE2,0x4C);
	dsc_cmd_send(2,0xE3,0x03);
	dsc_cmd_send(2,0xE4,0x5D);
	dsc_cmd_send(2,0xE5,0x03);
	dsc_cmd_send(2,0xE6,0x70);
	dsc_cmd_send(2,0xE7,0x03);
	dsc_cmd_send(2,0xE8,0x88);
	dsc_cmd_send(2,0xE9,0x03);
	dsc_cmd_send(2,0xEA,0xA8);
	dsc_cmd_send(2,0xEB,0x03);
	dsc_cmd_send(2,0xEC,0xC8);
	dsc_cmd_send(2,0xED,0x03);
	dsc_cmd_send(2,0xEE,0xFF);
	////G(+) MCR cmd
	dsc_cmd_send(2,0xEF,0x00);
	dsc_cmd_send(2,0xF0,0x00);
	dsc_cmd_send(2,0xF1,0x00);
	dsc_cmd_send(2,0xF2,0x2C);
	dsc_cmd_send(2,0xF3,0x00);
	dsc_cmd_send(2,0xF4,0x4F);
	dsc_cmd_send(2,0xF5,0x00);
	dsc_cmd_send(2,0xF6,0x69);
	dsc_cmd_send(2,0xF7,0x00);
	dsc_cmd_send(2,0xF8,0x7F);
	dsc_cmd_send(2,0xF9,0x00);
	dsc_cmd_send(2,0xFA,0x92);
	////page selection cmd start
	dsc_cmd_send(2,0xFF,0x02);
	dsc_cmd_send(2,0xFB,0x01);
	////page selection cmd end
	dsc_cmd_send(2,0x00,0x00);
	dsc_cmd_send(2,0x01,0xA3);
	dsc_cmd_send(2,0x02,0x00);
	dsc_cmd_send(2,0x03,0xB3);
	dsc_cmd_send(2,0x04,0x00);
	dsc_cmd_send(2,0x05,0xC1);
	dsc_cmd_send(2,0x06,0x00);
	dsc_cmd_send(2,0x07,0xF3);
	dsc_cmd_send(2,0x08,0x01);
	dsc_cmd_send(2,0x09,0x1B);
	dsc_cmd_send(2,0x0A,0x01);
	dsc_cmd_send(2,0x0B,0x5A);
	dsc_cmd_send(2,0x0C,0x01);
	dsc_cmd_send(2,0x0D,0x8B);
	dsc_cmd_send(2,0x0E,0x01);
	dsc_cmd_send(2,0x0F,0xD9);
	dsc_cmd_send(2,0x10,0x02);
	dsc_cmd_send(2,0x11,0x16);
	dsc_cmd_send(2,0x12,0x02);
	dsc_cmd_send(2,0x13,0x18);
	dsc_cmd_send(2,0x14,0x02);
	dsc_cmd_send(2,0x15,0x4E);
	dsc_cmd_send(2,0x16,0x02);
	dsc_cmd_send(2,0x17,0x88);
	dsc_cmd_send(2,0x18,0x02);
	dsc_cmd_send(2,0x19,0xAC);
	dsc_cmd_send(2,0x1A,0x02);
	dsc_cmd_send(2,0x1B,0xDD);
	dsc_cmd_send(2,0x1C,0x03);
	dsc_cmd_send(2,0x1D,0x01);
	dsc_cmd_send(2,0x1E,0x03);
	dsc_cmd_send(2,0x1F,0x2E);
	dsc_cmd_send(2,0x20,0x03);
	dsc_cmd_send(2,0x21,0x3C);
	dsc_cmd_send(2,0x22,0x03);
	dsc_cmd_send(2,0x23,0x4C);
	dsc_cmd_send(2,0x24,0x03);
	dsc_cmd_send(2,0x25,0x5D);
	dsc_cmd_send(2,0x26,0x03);
	dsc_cmd_send(2,0x27,0x70);
	dsc_cmd_send(2,0x28,0x03);
	dsc_cmd_send(2,0x29,0x88);
	dsc_cmd_send(2,0x2A,0x03);
	dsc_cmd_send(2,0x2B,0xA8);
	dsc_cmd_send(2,0x2D,0x03);
	dsc_cmd_send(2,0x2F,0xC8);
	dsc_cmd_send(2,0x30,0x03);
	dsc_cmd_send(2,0x31,0xFF);
	////G(-) MCR cmd
	dsc_cmd_send(2,0x32,0x00);
	dsc_cmd_send(2,0x33,0x00);
	dsc_cmd_send(2,0x34,0x00);
	dsc_cmd_send(2,0x35,0x2C);
	dsc_cmd_send(2,0x36,0x00);
	dsc_cmd_send(2,0x37,0x4F);
	dsc_cmd_send(2,0x38,0x00);
	dsc_cmd_send(2,0x39,0x69);
	dsc_cmd_send(2,0x3A,0x00);
	dsc_cmd_send(2,0x3B,0x7F);
	dsc_cmd_send(2,0x3D,0x00);
	dsc_cmd_send(2,0x3F,0x92);
	dsc_cmd_send(2,0x40,0x00);
	dsc_cmd_send(2,0x41,0xA3);
	dsc_cmd_send(2,0x42,0x00);
	dsc_cmd_send(2,0x43,0xB3);
	dsc_cmd_send(2,0x44,0x00);
	dsc_cmd_send(2,0x45,0xC1);
	dsc_cmd_send(2,0x46,0x00);
	dsc_cmd_send(2,0x47,0xF3);
	dsc_cmd_send(2,0x48,0x01);
	dsc_cmd_send(2,0x49,0x1B);
	dsc_cmd_send(2,0x4A,0x01);
	dsc_cmd_send(2,0x4B,0x5A);
	dsc_cmd_send(2,0x4C,0x01);
	dsc_cmd_send(2,0x4D,0x8B);
	dsc_cmd_send(2,0x4E,0x01);
	dsc_cmd_send(2,0x4F,0xD9);
	dsc_cmd_send(2,0x50,0x02);
	dsc_cmd_send(2,0x51,0x16);
	dsc_cmd_send(2,0x52,0x02);
	dsc_cmd_send(2,0x53,0x18);
	dsc_cmd_send(2,0x54,0x02);
	dsc_cmd_send(2,0x55,0x4E);
	dsc_cmd_send(2,0x56,0x02);
	dsc_cmd_send(2,0x58,0x88);
	dsc_cmd_send(2,0x59,0x02);
	dsc_cmd_send(2,0x5A,0xAC);
	dsc_cmd_send(2,0x5B,0x02);
	dsc_cmd_send(2,0x5C,0xDD);
	dsc_cmd_send(2,0x5D,0x03);
	dsc_cmd_send(2,0x5E,0x01);
	dsc_cmd_send(2,0x5F,0x03);
	dsc_cmd_send(2,0x60,0x2E);
	dsc_cmd_send(2,0x61,0x03);
	dsc_cmd_send(2,0x62,0x3C);
	dsc_cmd_send(2,0x63,0x03);
	dsc_cmd_send(2,0x64,0x4C);
	dsc_cmd_send(2,0x65,0x03);
	dsc_cmd_send(2,0x66,0x5D);
	dsc_cmd_send(2,0x67,0x03);
	dsc_cmd_send(2,0x68,0x70);
	dsc_cmd_send(2,0x69,0x03);
	dsc_cmd_send(2,0x6A,0x88);
	dsc_cmd_send(2,0x6B,0x03);
	dsc_cmd_send(2,0x6C,0xA8);
	dsc_cmd_send(2,0x6D,0x03);
	dsc_cmd_send(2,0x6E,0xC8);
	dsc_cmd_send(2,0x6F,0x03);
	dsc_cmd_send(2,0x70,0xFF);
	////B(+) MCR cmd
	dsc_cmd_send(2,0x71,0x00);
	dsc_cmd_send(2,0x72,0x00);
	dsc_cmd_send(2,0x73,0x00);
	dsc_cmd_send(2,0x74,0x2C);
	dsc_cmd_send(2,0x75,0x00);
	dsc_cmd_send(2,0x76,0x4F);
	dsc_cmd_send(2,0x77,0x00);
	dsc_cmd_send(2,0x78,0x69);
	dsc_cmd_send(2,0x79,0x00);
	dsc_cmd_send(2,0x7A,0x7F);
	dsc_cmd_send(2,0x7B,0x00);
	dsc_cmd_send(2,0x7C,0x92);
	dsc_cmd_send(2,0x7D,0x00);
	dsc_cmd_send(2,0x7E,0xA3);
	dsc_cmd_send(2,0x7F,0x00);
	dsc_cmd_send(2,0x80,0xB3);
	dsc_cmd_send(2,0x81,0x00);
	dsc_cmd_send(2,0x82,0xC1);
	dsc_cmd_send(2,0x83,0x00);
	dsc_cmd_send(2,0x84,0xF3);
	dsc_cmd_send(2,0x85,0x01);
	dsc_cmd_send(2,0x86,0x1B);
	dsc_cmd_send(2,0x87,0x01);
	dsc_cmd_send(2,0x88,0x5A);
	dsc_cmd_send(2,0x89,0x01);
	dsc_cmd_send(2,0x8A,0x8B);
	dsc_cmd_send(2,0x8B,0x01);
	dsc_cmd_send(2,0x8C,0xD9);
	dsc_cmd_send(2,0x8D,0x02);
	dsc_cmd_send(2,0x8E,0x16);
	dsc_cmd_send(2,0x8F,0x02);
	dsc_cmd_send(2,0x90,0x18);
	dsc_cmd_send(2,0x91,0x02);
	dsc_cmd_send(2,0x92,0x4E);
	dsc_cmd_send(2,0x93,0x02);
	dsc_cmd_send(2,0x94,0x88);
	dsc_cmd_send(2,0x95,0x02);
	dsc_cmd_send(2,0x96,0xAC);
	dsc_cmd_send(2,0x97,0x02);
	dsc_cmd_send(2,0x98,0xDD);
	dsc_cmd_send(2,0x99,0x03);
	dsc_cmd_send(2,0x9A,0x01);
	dsc_cmd_send(2,0x9B,0x03);
	dsc_cmd_send(2,0x9C,0x2E);
	dsc_cmd_send(2,0x9D,0x03);
	dsc_cmd_send(2,0x9E,0x3C);
	dsc_cmd_send(2,0x9F,0x03);
	dsc_cmd_send(2,0xA0,0x4C);
	dsc_cmd_send(2,0xA2,0x03);
	dsc_cmd_send(2,0xA3,0x5D);
	dsc_cmd_send(2,0xA4,0x03);
	dsc_cmd_send(2,0xA5,0x70);
	dsc_cmd_send(2,0xA6,0x03);
	dsc_cmd_send(2,0xA7,0x88);
	dsc_cmd_send(2,0xA9,0x03);
	dsc_cmd_send(2,0xAA,0xA8);
	dsc_cmd_send(2,0xAB,0x03);
	dsc_cmd_send(2,0xAC,0xC8);
	dsc_cmd_send(2,0xAD,0x03);
	dsc_cmd_send(2,0xAE,0xFF);
	////B(-) MCR cmd
	dsc_cmd_send(2,0xAF,0x00);
	dsc_cmd_send(2,0xB0,0x00);
	dsc_cmd_send(2,0xB1,0x00);
	dsc_cmd_send(2,0xB2,0x2C);
	dsc_cmd_send(2,0xB3,0x00);
	dsc_cmd_send(2,0xB4,0x4F);
	dsc_cmd_send(2,0xB5,0x00);
	dsc_cmd_send(2,0xB6,0x69);
	dsc_cmd_send(2,0xB7,0x00);
	dsc_cmd_send(2,0xB8,0x7F);
	dsc_cmd_send(2,0xB9,0x00);
	dsc_cmd_send(2,0xBA,0x92);
	dsc_cmd_send(2,0xBB,0x00);
	dsc_cmd_send(2,0xBC,0xA3);
	dsc_cmd_send(2,0xBD,0x00);
	dsc_cmd_send(2,0xBE,0xB3);
	dsc_cmd_send(2,0xBF,0x00);
	dsc_cmd_send(2,0xC0,0xC1);
	dsc_cmd_send(2,0xC1,0x00);
	dsc_cmd_send(2,0xC2,0xF3);
	dsc_cmd_send(2,0xC3,0x01);
	dsc_cmd_send(2,0xC4,0x1B);
	dsc_cmd_send(2,0xC5,0x01);
	dsc_cmd_send(2,0xC6,0x5A);
	dsc_cmd_send(2,0xC7,0x01);
	dsc_cmd_send(2,0xC8,0x8B);
	dsc_cmd_send(2,0xC9,0x01);
	dsc_cmd_send(2,0xCA,0xD9);
	dsc_cmd_send(2,0xCB,0x02);
	dsc_cmd_send(2,0xCC,0x16);
	dsc_cmd_send(2,0xCD,0x02);
	dsc_cmd_send(2,0xCE,0x18);
	dsc_cmd_send(2,0xCF,0x02);
	dsc_cmd_send(2,0xD0,0x4E);
	dsc_cmd_send(2,0xD1,0x02);
	dsc_cmd_send(2,0xD2,0x88);
	dsc_cmd_send(2,0xD3,0x02);
	dsc_cmd_send(2,0xD4,0xAC);
	dsc_cmd_send(2,0xD5,0x02);
	dsc_cmd_send(2,0xD6,0xDD);
	dsc_cmd_send(2,0xD7,0x03);
	dsc_cmd_send(2,0xD8,0x01);
	dsc_cmd_send(2,0xD9,0x03);
	dsc_cmd_send(2,0xDA,0x2E);
	dsc_cmd_send(2,0xDB,0x03);
	dsc_cmd_send(2,0xDC,0x3C);
	dsc_cmd_send(2,0xDD,0x03);
	dsc_cmd_send(2,0xDE,0x4C);
	dsc_cmd_send(2,0xDF,0x03);
	dsc_cmd_send(2,0xE0,0x5D);
	dsc_cmd_send(2,0xE1,0x03);
	dsc_cmd_send(2,0xE2,0x70);
	dsc_cmd_send(2,0xE3,0x03);
	dsc_cmd_send(2,0xE4,0x88);
	dsc_cmd_send(2,0xE5,0x03);
	dsc_cmd_send(2,0xE6,0xA8);
	dsc_cmd_send(2,0xE7,0x03);
	dsc_cmd_send(2,0xE8,0xC8);
	dsc_cmd_send(2,0xE9,0x03);
	dsc_cmd_send(2,0xEA,0xFF);

	dsc_cmd_send(2,0xFF,0x00);
	dsc_cmd_send(2,0xFB,0x01);

	dsc_cmd_send(2,0x11,0x00);

#ifndef _SIMU
	msleep(100);
#endif
	dsc_cmd_send(2,0x29,0x00);
#ifndef _SIMU
	msleep(100) ;
#endif
};


#if 1
void  dsc_cmd_send_4(int data1, int data2, int data3,int data4)
{
	int cmd_sts =0;
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01043908); //[24] cmd_lp_en  =1    0x01043908
	//[23:14] cmd_size  =cmd_size. 1 or 2   //write 4
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x1
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request

	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data4<<24) + (data3<<16) + (data2<<8) + data1));// DATA
	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}


void dis_get_err_status(void)
{
	uint32_t dsi_err;
	uint32_t dphy_err;

	dsi_err = readl(CNDS_DSI_REG_START + 0x28);
	k510_logci(" mctl_dphy_err is %x \n", dsi_err);
	/*
	   dsi_err = readl(CNDS_DSI_REG_START + 0x2c);
	   k510_logci(" mctl_lane_sts is %x \n", dsi_err);

	   dsi_err = readl(CNDS_DSI_REG_START + 0x24);
	   k510_logci(" mctl_main_sts is %x \n", dsi_err);

	   dsi_err = readl(CNDS_DSI_REG_START + 0x78);
	   k510_logci(" cmd_mode_sts is %x \n", dsi_err);

	   dsi_err = readl(CNDS_DSI_REG_START + 0x04);
	   k510_logci("  mctl_main_data_ctl is %x \n", dsi_err);

	   dsi_err = readl(CNDS_DSI_REG_START + 0x88);
	   k510_logci("  direct_cmd_sts is %x \n", dsi_err);

	   dsi_err = readl(CNDS_DSI_REG_START + 0xa8);
	   k510_logci("  direct_cmd_rd_sts is %x \n", dsi_err);

	   dsi_err = readl(CNDS_DSI_REG_START + 0xf0);
	   k510_logci("  vid_mode_sts is %x \n", dsi_err);
	 */
}


void mipi_select_lan1()
{

	uint32_t wdata, rdata;

	rdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
	//power-down mipi pll and reset pll
	wdata = (rdata & 0xffe00000)
		| (1 << 19) /*lane0_sel */
		| (0 << 17) /*lane1_sel */
		| (2 << 15) /*lane2_sel */
		| (3 << 13) /*lane3_sel */;

	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

}


void mipi_select_lan2()
{

	uint32_t wdata, rdata;

	rdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
	//power-down mipi pll and reset pll
	wdata = (rdata & 0xffe00000)
		| (2 << 19) /*lane0_sel */
		| (1 << 17) /*lane1_sel */
		| (0 << 15) /*lane2_sel */
		| (3 << 13) /*lane3_sel */;

	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

}

void mipi_select_lan3()
{

	uint32_t wdata, rdata;

	rdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
	//power-down mipi pll and reset pll
	wdata = (rdata & 0xffe00000)
		| (3 << 19) /*lane0_sel */
		| (1 << 17) /*lane1_sel */
		| (2 << 15) /*lane2_sel */
		| (0 << 13) /*lane3_sel */;

	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

}

void ILI7807_lcd_init(void)
{
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x01);			// write page 1
	//        mipi_select_lan1();
	dsc_cmd_send(2, 0x42, 0x11);
	//        mipi_select_lan2();
	//        while(1)
	//        {
	//               dis_get_err_status();
	//       }



	dsc_cmd_send(2, 0x43, 0xB2);		//VGH_CLP = 11.0V
	//       mipi_select_lan3();
	//       dsc_cmd_read(0x43);
	dsc_cmd_send(2, 0x44, 0x94);		//VGL_CLP = -7.0V
	dsc_cmd_send(2, 0x4A, 0x15);
	dsc_cmd_send(2, 0x4B, 0x15);
	dsc_cmd_send(2, 0x50, 0x73);		//GVDDP = 5.3V
	dsc_cmd_send(2, 0x51, 0x73);		//GVDDN = - 5.3V
	dsc_cmd_send(2, 0x5A, 0x33);		//LVD
	dsc_cmd_send(2, 0xA0, 0x10);
	dsc_cmd_send(2, 0xA2, 0x01);		//VCOM1 = - 0.35V
	dsc_cmd_send(2, 0xA3, 0x22);		//VCOM1 = - 0.35V
	dsc_cmd_send(2, 0xB3, 0x60);
	dsc_cmd_send(2, 0xB4, 0x60);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x01);			// write page 1
	dsc_cmd_send(2, 0x22, 0x06);
	dsc_cmd_send(2, 0x36, 0x00);
	dsc_cmd_send(2, 0x60, 0x0A);
	dsc_cmd_send(2, 0x64, 0x08);
	dsc_cmd_send(2, 0x6C, 0x45);		//PRC & PRCB
	dsc_cmd_send(2, 0x35, 0x22);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x07);			// write page 7
	dsc_cmd_send(2, 0x37, 0x00);
	dsc_cmd_send(2, 0x12, 0x22);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x08);			// write page 8 for GIP

	dsc_cmd_send(2, 0x09, 0x0e);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x06);			// write page 8 for GIP
	dsc_cmd_send(2, 0x00, 0x42);
	dsc_cmd_send(2, 0x01, 0x04);
	dsc_cmd_send(2, 0x02, 0x0B);
	dsc_cmd_send(2, 0x03, 0x03);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x00);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x00);
	dsc_cmd_send(2, 0x08, 0x81);
	dsc_cmd_send(2, 0x09, 0x05);
	dsc_cmd_send(2, 0x0a, 0x70);
	dsc_cmd_send(2, 0x0b, 0x00);
	dsc_cmd_send(2, 0x0c, 0x0B);
	dsc_cmd_send(2, 0x0d, 0x0B);
	dsc_cmd_send(2, 0x0e, 0x03);
	dsc_cmd_send(2, 0x0f, 0x03);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x12, 0x00);
	dsc_cmd_send(2, 0x13, 0x00);
	dsc_cmd_send(2, 0x14, 0x00);
	dsc_cmd_send(2, 0x15, 0x00);
	dsc_cmd_send(2, 0x31, 0x22);
	dsc_cmd_send(2, 0x32, 0x27);
	dsc_cmd_send(2, 0x33, 0x07);
	dsc_cmd_send(2, 0x34, 0x08);
	dsc_cmd_send(2, 0x35, 0x10);
	dsc_cmd_send(2, 0x36, 0x16);
	dsc_cmd_send(2, 0x37, 0x14);
	dsc_cmd_send(2, 0x38, 0x12);
	dsc_cmd_send(2, 0x39, 0x07);
	dsc_cmd_send(2, 0x3a, 0x07);
	dsc_cmd_send(2, 0x3b, 0x07);
	dsc_cmd_send(2, 0x3c, 0x28);
	dsc_cmd_send(2, 0x3d, 0x29);
	dsc_cmd_send(2, 0x3e, 0x2a);
	dsc_cmd_send(2, 0x3f, 0x07);
	dsc_cmd_send(2, 0x40, 0x07);
	dsc_cmd_send(2, 0x41, 0x22);
	dsc_cmd_send(2, 0x42, 0x27);
	dsc_cmd_send(2, 0x43, 0x07);
	dsc_cmd_send(2, 0x44, 0x09);
	dsc_cmd_send(2, 0x45, 0x11);
	dsc_cmd_send(2, 0x46, 0x17);
	dsc_cmd_send(2, 0x47, 0x15);
	dsc_cmd_send(2, 0x48, 0x13);
	dsc_cmd_send(2, 0x49, 0x07);
	dsc_cmd_send(2, 0x4a, 0x07);
	dsc_cmd_send(2, 0x4b, 0x07);
	dsc_cmd_send(2, 0x4c, 0x28);
	dsc_cmd_send(2, 0x4d, 0x29);
	dsc_cmd_send(2, 0x4e, 0x2a);
	dsc_cmd_send(2, 0x4f, 0x07);
	dsc_cmd_send(2, 0x50, 0x07);
	dsc_cmd_send(2, 0x61, 0x22);
	dsc_cmd_send(2, 0x62, 0x27);
	dsc_cmd_send(2, 0x63, 0x07);
	dsc_cmd_send(2, 0x64, 0x09);
	dsc_cmd_send(2, 0x65, 0x13);
	dsc_cmd_send(2, 0x66, 0x15);
	dsc_cmd_send(2, 0x67, 0x17);
	dsc_cmd_send(2, 0x68, 0x11);
	dsc_cmd_send(2, 0x69, 0x07);
	dsc_cmd_send(2, 0x6a, 0x07);
	dsc_cmd_send(2, 0x6b, 0x07);
	dsc_cmd_send(2, 0x6c, 0x28);
	dsc_cmd_send(2, 0x6d, 0x29);
	dsc_cmd_send(2, 0x6e, 0x2a);
	dsc_cmd_send(2, 0x6f, 0x07);

	dsc_cmd_send(2, 0x70, 0x07);
	dsc_cmd_send(2, 0x71, 0x22);
	dsc_cmd_send(2, 0x72, 0x27);
	dsc_cmd_send(2, 0x73, 0x07);
	dsc_cmd_send(2, 0x74, 0x08);
	dsc_cmd_send(2, 0x75, 0x12);
	dsc_cmd_send(2, 0x76, 0x14);
	dsc_cmd_send(2, 0x77, 0x16);
	dsc_cmd_send(2, 0x78, 0x10);
	dsc_cmd_send(2, 0x79, 0x07);
	dsc_cmd_send(2, 0x7a, 0x07);
	dsc_cmd_send(2, 0x7b, 0x07);
	dsc_cmd_send(2, 0x7c, 0x28);
	dsc_cmd_send(2, 0x7d, 0x29);
	dsc_cmd_send(2, 0x7e, 0x2a);
	dsc_cmd_send(2, 0x7f, 0x07);
	dsc_cmd_send(2, 0x80, 0x07);

	dsc_cmd_send(2, 0xd0, 0x01);

	dsc_cmd_send(2, 0xdb, 0x40);
	dsc_cmd_send(2, 0xdc, 0x04);
	dsc_cmd_send(2, 0xdd, 0x00);

	dsc_cmd_send(2, 0xa0, 0x13);
	dsc_cmd_send(2, 0xa1, 0x00);
	dsc_cmd_send(2, 0xa2, 0x05);
	dsc_cmd_send(2, 0xa3, 0x20);
	dsc_cmd_send(2, 0xa6, 0x00);
	dsc_cmd_send(2, 0xa7, 0x00);

	dsc_cmd_send(2, 0x97, 0x22);

	dsc_cmd_send(2, 0xD1, 0x01);
	dsc_cmd_send(2, 0xD2, 0x00);
	dsc_cmd_send(2, 0xDF, 0x00);
	dsc_cmd_send(2, 0xE5, 0x10);
	dsc_cmd_send(2, 0xE6, 0x00);
	dsc_cmd_send(2, 0xD6, 0x10);
	dsc_cmd_send(2, 0xD7, 0x20);
	dsc_cmd_send(2, 0xD8, 0x14);
	dsc_cmd_send(2, 0xD9, 0x00);
	dsc_cmd_send(2, 0xDA, 0x00);

	dsc_cmd_send(2, 0xB2, 0x00);
	dsc_cmd_send(2, 0xB3, 0x00);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x02);	 //page 02
	dsc_cmd_send(2, 0x00, 0x00);
	dsc_cmd_send(2, 0x01, 0x30);
	dsc_cmd_send(2, 0x02, 0x00);
	dsc_cmd_send(2, 0x03, 0x4A);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x6F);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x8B);
	dsc_cmd_send(2, 0x08, 0x00);
	dsc_cmd_send(2, 0x09, 0xA1);
	dsc_cmd_send(2, 0x0A, 0x00);
	dsc_cmd_send(2, 0x0B, 0xB4);
	dsc_cmd_send(2, 0x0C, 0x0C);
	dsc_cmd_send(2, 0x0D, 0xC5);
	dsc_cmd_send(2, 0x0E, 0x00);
	dsc_cmd_send(2, 0x0F, 0xD5);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x11, 0xE2);
	dsc_cmd_send(2, 0x12, 0x01);
	dsc_cmd_send(2, 0x13, 0x10);
	dsc_cmd_send(2, 0x14, 0x01);
	dsc_cmd_send(2, 0x15, 0x34);
	dsc_cmd_send(2, 0x16, 0x01);
	dsc_cmd_send(2, 0x17, 0x6D);
	dsc_cmd_send(2, 0x18, 0x01);
	dsc_cmd_send(2, 0x19, 0x9A);
	dsc_cmd_send(2, 0x1A, 0x01);
	dsc_cmd_send(2, 0x1B, 0xE2);
	dsc_cmd_send(2, 0x1C, 0x02);
	dsc_cmd_send(2, 0x1D, 0x1B);
	dsc_cmd_send(2, 0x1E, 0x02);
	dsc_cmd_send(2, 0x1F, 0x1C);
	dsc_cmd_send(2, 0x20, 0x02);
	dsc_cmd_send(2, 0x21, 0x52);
	dsc_cmd_send(2, 0x22, 0x02);
	dsc_cmd_send(2, 0x23, 0x8F);
	dsc_cmd_send(2, 0x24, 0x02);
	dsc_cmd_send(2, 0x25, 0xB7);
	dsc_cmd_send(2, 0x26, 0x02);
	dsc_cmd_send(2, 0x27, 0xEC);
	dsc_cmd_send(2, 0x28, 0x03);
	dsc_cmd_send(2, 0x29, 0x0E);
	dsc_cmd_send(2, 0x2A, 0x03);
	dsc_cmd_send(2, 0x2B, 0x3A);
	dsc_cmd_send(2, 0x2C, 0x03);
	dsc_cmd_send(2, 0x2D, 0x47);
	dsc_cmd_send(2, 0x2E, 0x03);
	dsc_cmd_send(2, 0x2F, 0x55);
	dsc_cmd_send(2, 0x30, 0x03);
	dsc_cmd_send(2, 0x31, 0x65);
	dsc_cmd_send(2, 0x32, 0x03);
	dsc_cmd_send(2, 0x33, 0x76);
	dsc_cmd_send(2, 0x34, 0x03);
	dsc_cmd_send(2, 0x35, 0x8A);
	dsc_cmd_send(2, 0x36, 0x03);
	dsc_cmd_send(2, 0x37, 0xA3);
	dsc_cmd_send(2, 0x38, 0x03);
	dsc_cmd_send(2, 0x39, 0xC4);
	dsc_cmd_send(2, 0x3A, 0x03);
	dsc_cmd_send(2, 0x3B, 0xD1);

	dsc_cmd_send(2, 0x3C, 0x00);
	dsc_cmd_send(2, 0x3D, 0x30);
	dsc_cmd_send(2, 0x3E, 0x00);
	dsc_cmd_send(2, 0x3F, 0x4A);
	dsc_cmd_send(2, 0x40, 0x00);
	dsc_cmd_send(2, 0x41, 0x6F);
	dsc_cmd_send(2, 0x42, 0x00);
	dsc_cmd_send(2, 0x43, 0x8B);
	dsc_cmd_send(2, 0x44, 0x00);
	dsc_cmd_send(2, 0x45, 0xA1);
	dsc_cmd_send(2, 0x46, 0x00);
	dsc_cmd_send(2, 0x47, 0xB4);
	dsc_cmd_send(2, 0x48, 0x00);
	dsc_cmd_send(2, 0x49, 0xC5);
	dsc_cmd_send(2, 0x4A, 0x00);
	dsc_cmd_send(2, 0x4B, 0xD5);
	dsc_cmd_send(2, 0x4C, 0x00);
	dsc_cmd_send(2, 0x4D, 0xE2);
	dsc_cmd_send(2, 0x4E, 0x01);
	dsc_cmd_send(2, 0x4F, 0x10);
	dsc_cmd_send(2, 0x50, 0x01);
	dsc_cmd_send(2, 0x51, 0x34);
	dsc_cmd_send(2, 0x52, 0x01);
	dsc_cmd_send(2, 0x53, 0x6D);
	dsc_cmd_send(2, 0x54, 0x01);
	dsc_cmd_send(2, 0x55, 0x9A);
	dsc_cmd_send(2, 0x56, 0x01);
	dsc_cmd_send(2, 0x57, 0xE2);
	dsc_cmd_send(2, 0x58, 0x02);
	dsc_cmd_send(2, 0x59, 0x1B);
	dsc_cmd_send(2, 0x5A, 0x02);
	dsc_cmd_send(2, 0x5B, 0x1C);
	dsc_cmd_send(2, 0x5C, 0x02);
	dsc_cmd_send(2, 0x5D, 0x52);
	dsc_cmd_send(2, 0x5E, 0x02);
	dsc_cmd_send(2, 0x5F, 0x8F);
	dsc_cmd_send(2, 0x60, 0x02);
	dsc_cmd_send(2, 0x61, 0xB7);
	dsc_cmd_send(2, 0x62, 0x02);
	dsc_cmd_send(2, 0x63, 0xEC);
	dsc_cmd_send(2, 0x64, 0x03);
	dsc_cmd_send(2, 0x65, 0x0E);
	dsc_cmd_send(2, 0x66, 0x03);
	dsc_cmd_send(2, 0x67, 0x3A);
	dsc_cmd_send(2, 0x68, 0x03);
	dsc_cmd_send(2, 0x69, 0x47);
	dsc_cmd_send(2, 0x6A, 0x03);
	dsc_cmd_send(2, 0x6B, 0x55);
	dsc_cmd_send(2, 0x6C, 0x03);
	dsc_cmd_send(2, 0x6D, 0x65);
	dsc_cmd_send(2, 0x6E, 0x03);
	dsc_cmd_send(2, 0x6F, 0x76);
	dsc_cmd_send(2, 0x70, 0x03);
	dsc_cmd_send(2, 0x71, 0x8A);
	dsc_cmd_send(2, 0x72, 0x03);
	dsc_cmd_send(2, 0x73, 0xA3);
	dsc_cmd_send(2, 0x74, 0x03);
	dsc_cmd_send(2, 0x75, 0xC4);
	dsc_cmd_send(2, 0x76, 0x03);
	dsc_cmd_send(2, 0x77, 0xD1);

	dsc_cmd_send(2, 0x78, 0x01);
	dsc_cmd_send(2, 0x79, 0x01);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x03);	// page3
	dsc_cmd_send(2, 0x00, 0x00);
	dsc_cmd_send(2, 0x01, 0x30);
	dsc_cmd_send(2, 0x02, 0x00);
	dsc_cmd_send(2, 0x03, 0x4A);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x6F);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x8B);
	dsc_cmd_send(2, 0x08, 0x00);
	dsc_cmd_send(2, 0x09, 0xA1);
	dsc_cmd_send(2, 0x0A, 0x00);
	dsc_cmd_send(2, 0x0B, 0xB4);
	dsc_cmd_send(2, 0x0C, 0x00);
	dsc_cmd_send(2, 0x0D, 0xC5);
	dsc_cmd_send(2, 0x0E, 0x00);
	dsc_cmd_send(2, 0x0F, 0xD5);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x11, 0xE2);
	dsc_cmd_send(2, 0x12, 0x01);
	dsc_cmd_send(2, 0x13, 0x10);
	dsc_cmd_send(2, 0x14, 0x01);
	dsc_cmd_send(2, 0x15, 0x34);
	dsc_cmd_send(2, 0x16, 0x01);
	dsc_cmd_send(2, 0x17, 0x6D);
	dsc_cmd_send(2, 0x18, 0x01);
	dsc_cmd_send(2, 0x19, 0x9A);
	dsc_cmd_send(2, 0x1A, 0x01);
	dsc_cmd_send(2, 0x1B, 0xE2);
	dsc_cmd_send(2, 0x1C, 0x02);
	dsc_cmd_send(2, 0x1D, 0x1B);
	dsc_cmd_send(2, 0x1E, 0x02);
	dsc_cmd_send(2, 0x1F, 0x1C);
	dsc_cmd_send(2, 0x20, 0x02);
	dsc_cmd_send(2, 0x21, 0x52);
	dsc_cmd_send(2, 0x22, 0x02);
	dsc_cmd_send(2, 0x23, 0x8F);
	dsc_cmd_send(2, 0x24, 0x02);
	dsc_cmd_send(2, 0x25, 0xB7);
	dsc_cmd_send(2, 0x26, 0x02);
	dsc_cmd_send(2, 0x27, 0xEC);
	dsc_cmd_send(2, 0x28, 0x03);
	dsc_cmd_send(2, 0x29, 0x0E);
	dsc_cmd_send(2, 0x2A, 0x03);
	dsc_cmd_send(2, 0x2B, 0x3A);
	dsc_cmd_send(2, 0x2C, 0x03);
	dsc_cmd_send(2, 0x2D, 0x47);
	dsc_cmd_send(2, 0x2E, 0x03);
	dsc_cmd_send(2, 0x2F, 0x55);
	dsc_cmd_send(2, 0x30, 0x03);
	dsc_cmd_send(2, 0x31, 0x65);
	dsc_cmd_send(2, 0x32, 0x03);
	dsc_cmd_send(2, 0x33, 0x76);
	dsc_cmd_send(2, 0x34, 0x03);
	dsc_cmd_send(2, 0x35, 0x8A);
	dsc_cmd_send(2, 0x36, 0x03);
	dsc_cmd_send(2, 0x37, 0xA3);
	dsc_cmd_send(2, 0x38, 0x03);
	dsc_cmd_send(2, 0x39, 0xC4);
	dsc_cmd_send(2, 0x3A, 0x03);
	dsc_cmd_send(2, 0x3B, 0xD1);

	dsc_cmd_send(2, 0x3C, 0x00);
	dsc_cmd_send(2, 0x3D, 0x30);
	dsc_cmd_send(2, 0x3E, 0x00);
	dsc_cmd_send(2, 0x3F, 0x4A);
	dsc_cmd_send(2, 0x40, 0x00);
	dsc_cmd_send(2, 0x41, 0x6F);
	dsc_cmd_send(2, 0x42, 0x00);
	dsc_cmd_send(2, 0x43, 0x8B);
	dsc_cmd_send(2, 0x44, 0x00);
	dsc_cmd_send(2, 0x45, 0xA1);
	dsc_cmd_send(2, 0x46, 0x00);
	dsc_cmd_send(2, 0x47, 0xB4);
	dsc_cmd_send(2, 0x48, 0x00);
	dsc_cmd_send(2, 0x49, 0xC5);
	dsc_cmd_send(2, 0x4A, 0x00);
	dsc_cmd_send(2, 0x4B, 0xD5);
	dsc_cmd_send(2, 0x4C, 0x00);
	dsc_cmd_send(2, 0x4D, 0xE2);
	dsc_cmd_send(2, 0x4E, 0x01);
	dsc_cmd_send(2, 0x4F, 0x10);
	dsc_cmd_send(2, 0x50, 0x01);
	dsc_cmd_send(2, 0x51, 0x34);
	dsc_cmd_send(2, 0x52, 0x01);
	dsc_cmd_send(2, 0x53, 0x6D);
	dsc_cmd_send(2, 0x54, 0x01);
	dsc_cmd_send(2, 0x55, 0x9A);
	dsc_cmd_send(2, 0x56, 0x01);
	dsc_cmd_send(2, 0x57, 0xE2);
	dsc_cmd_send(2, 0x58, 0x02);
	dsc_cmd_send(2, 0x59, 0x1B);
	dsc_cmd_send(2, 0x5A, 0x02);
	dsc_cmd_send(2, 0x5B, 0x1C);
	dsc_cmd_send(2, 0x5C, 0x02);
	dsc_cmd_send(2, 0x5D, 0x52);
	dsc_cmd_send(2, 0x5E, 0x02);
	dsc_cmd_send(2, 0x5F, 0x8F);
	dsc_cmd_send(2, 0x60, 0x02);
	dsc_cmd_send(2, 0x61, 0xB7);
	dsc_cmd_send(2, 0x62, 0x02);
	dsc_cmd_send(2, 0x63, 0xEC);
	dsc_cmd_send(2, 0x64, 0x03);
	dsc_cmd_send(2, 0x65, 0x0E);
	dsc_cmd_send(2, 0x66, 0x03);
	dsc_cmd_send(2, 0x67, 0x3A);
	dsc_cmd_send(2, 0x68, 0x03);
	dsc_cmd_send(2, 0x69, 0x47);
	dsc_cmd_send(2, 0x6A, 0x03);
	dsc_cmd_send(2, 0x6B, 0x55);
	dsc_cmd_send(2, 0x6C, 0x03);
	dsc_cmd_send(2, 0x6D, 0x65);
	dsc_cmd_send(2, 0x6E, 0x03);
	dsc_cmd_send(2, 0x6F, 0x76);
	dsc_cmd_send(2, 0x70, 0x03);
	dsc_cmd_send(2, 0x71, 0x8A);
	dsc_cmd_send(2, 0x72, 0x03);
	dsc_cmd_send(2, 0x73, 0xA3);
	dsc_cmd_send(2, 0x74, 0x03);
	dsc_cmd_send(2, 0x75, 0xC4);
	dsc_cmd_send(2, 0x76, 0x03);
	dsc_cmd_send(2, 0x77, 0xD1);

	dsc_cmd_send(2, 0x78, 0x01);
	dsc_cmd_send(2, 0x79, 0x01);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x04); // pagetr for 04
	dsc_cmd_send(2, 0x00, 0x00);
	dsc_cmd_send(2, 0x01, 0x30);
	dsc_cmd_send(2, 0x02, 0x00);
	dsc_cmd_send(2, 0x03, 0x4A);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x6F);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x8B);
	dsc_cmd_send(2, 0x08, 0x00);
	dsc_cmd_send(2, 0x09, 0xA1);
	dsc_cmd_send(2, 0x0A, 0x00);
	dsc_cmd_send(2, 0x0B, 0xB4);
	dsc_cmd_send(2, 0x0C, 0x00);
	dsc_cmd_send(2, 0x0D, 0xC5);
	dsc_cmd_send(2, 0x0E, 0x00);
	dsc_cmd_send(2, 0x0F, 0xD5);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x11, 0xE2);
	dsc_cmd_send(2, 0x12, 0x01);
	dsc_cmd_send(2, 0x13, 0x10);
	dsc_cmd_send(2, 0x14, 0x01);
	dsc_cmd_send(2, 0x15, 0x34);
	dsc_cmd_send(2, 0x16, 0x01);
	dsc_cmd_send(2, 0x17, 0x6D);
	dsc_cmd_send(2, 0x18, 0x01);
	dsc_cmd_send(2, 0x19, 0x9A);
	dsc_cmd_send(2, 0x1A, 0x01);
	dsc_cmd_send(2, 0x1B, 0xE2);
	dsc_cmd_send(2, 0x1C, 0x02);
	dsc_cmd_send(2, 0x1D, 0x1B);
	dsc_cmd_send(2, 0x1E, 0x02);
	dsc_cmd_send(2, 0x1F, 0x1C);
	dsc_cmd_send(2, 0x20, 0x02);
	dsc_cmd_send(2, 0x21, 0x52);
	dsc_cmd_send(2, 0x22, 0x02);
	dsc_cmd_send(2, 0x23, 0x8F);
	dsc_cmd_send(2, 0x24, 0x02);
	dsc_cmd_send(2, 0x25, 0xB7);
	dsc_cmd_send(2, 0x26, 0x02);
	dsc_cmd_send(2, 0x27, 0xEC);
	dsc_cmd_send(2, 0x28, 0x03);
	dsc_cmd_send(2, 0x29, 0x0E);
	dsc_cmd_send(2, 0x2A, 0x03);
	dsc_cmd_send(2, 0x2B, 0x3A);
	dsc_cmd_send(2, 0x2C, 0x03);
	dsc_cmd_send(2, 0x2D, 0x47);
	dsc_cmd_send(2, 0x2E, 0x03);
	dsc_cmd_send(2, 0x2F, 0x55);
	dsc_cmd_send(2, 0x30, 0x03);
	dsc_cmd_send(2, 0x31, 0x65);
	dsc_cmd_send(2, 0x32, 0x03);
	dsc_cmd_send(2, 0x33, 0x76);
	dsc_cmd_send(2, 0x34, 0x03);
	dsc_cmd_send(2, 0x35, 0x8A);
	dsc_cmd_send(2, 0x36, 0x03);
	dsc_cmd_send(2, 0x37, 0xA3);
	dsc_cmd_send(2, 0x38, 0x03);
	dsc_cmd_send(2, 0x39, 0xC4);
	dsc_cmd_send(2, 0x3A, 0x03);
	dsc_cmd_send(2, 0x3B, 0xD1);

	dsc_cmd_send(2, 0x3C, 0x00);
	dsc_cmd_send(2, 0x3D, 0x30);
	dsc_cmd_send(2, 0x3E, 0x00);
	dsc_cmd_send(2, 0x3F, 0x4A);
	dsc_cmd_send(2, 0x40, 0x00);
	dsc_cmd_send(2, 0x41, 0x6F);
	dsc_cmd_send(2, 0x42, 0x00);
	dsc_cmd_send(2, 0x43, 0x8B);
	dsc_cmd_send(2, 0x44, 0x00);
	dsc_cmd_send(2, 0x45, 0xA1);
	dsc_cmd_send(2, 0x46, 0x00);
	dsc_cmd_send(2, 0x47, 0xB4);
	dsc_cmd_send(2, 0x48, 0x00);
	dsc_cmd_send(2, 0x49, 0xC5);
	dsc_cmd_send(2, 0x4A, 0x00);
	dsc_cmd_send(2, 0x4B, 0xD5);
	dsc_cmd_send(2, 0x4C, 0x00);
	dsc_cmd_send(2, 0x4D, 0xE2);
	dsc_cmd_send(2, 0x4E, 0x01);
	dsc_cmd_send(2, 0x4F, 0x10);
	dsc_cmd_send(2, 0x50, 0x01);
	dsc_cmd_send(2, 0x51, 0x34);
	dsc_cmd_send(2, 0x52, 0x01);
	dsc_cmd_send(2, 0x53, 0x6D);
	dsc_cmd_send(2, 0x54, 0x01);
	dsc_cmd_send(2, 0x55, 0x9A);
	dsc_cmd_send(2, 0x56, 0x01);
	dsc_cmd_send(2, 0x57, 0xE2);
	dsc_cmd_send(2, 0x58, 0x02);
	dsc_cmd_send(2, 0x59, 0x1B);
	dsc_cmd_send(2, 0x5A, 0x02);
	dsc_cmd_send(2, 0x5B, 0x1C);
	dsc_cmd_send(2, 0x5C, 0x02);
	dsc_cmd_send(2, 0x5D, 0x52);
	dsc_cmd_send(2, 0x5E, 0x02);
	dsc_cmd_send(2, 0x5F, 0x8F);
	dsc_cmd_send(2, 0x60, 0x02);
	dsc_cmd_send(2, 0x61, 0xB7);
	dsc_cmd_send(2, 0x62, 0x02);
	dsc_cmd_send(2, 0x63, 0xEC);
	dsc_cmd_send(2, 0x64, 0x03);
	dsc_cmd_send(2, 0x65, 0x0E);
	dsc_cmd_send(2, 0x66, 0x03);
	dsc_cmd_send(2, 0x67, 0x3A);
	dsc_cmd_send(2, 0x68, 0x03);
	dsc_cmd_send(2, 0x69, 0x47);
	dsc_cmd_send(2, 0x6A, 0x03);
	dsc_cmd_send(2, 0x6B, 0x55);
	dsc_cmd_send(2, 0x6C, 0x03);
	dsc_cmd_send(2, 0x6D, 0x65);
	dsc_cmd_send(2, 0x6E, 0x03);
	dsc_cmd_send(2, 0x6F, 0x76);
	dsc_cmd_send(2, 0x70, 0x03);
	dsc_cmd_send(2, 0x71, 0x8A);
	dsc_cmd_send(2, 0x72, 0x03);
	dsc_cmd_send(2, 0x73, 0xA3);
	dsc_cmd_send(2, 0x74, 0x03);
	dsc_cmd_send(2, 0x75, 0xC4);
	dsc_cmd_send(2, 0x76, 0x03);
	dsc_cmd_send(2, 0x77, 0xD1);

	dsc_cmd_send(2, 0x78, 0x01);
	dsc_cmd_send(2, 0x79, 0x01);

	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x00);

	dsc_cmd_send(2, 0x11, 0x00);
	msleep(150);
	dsc_cmd_send(2, 0x29, 0x00);
	msleep(50);

}
#endif




#if 1
void  dsc_cmd_send_3(int data1, int data2, int data3)
{
	int cmd_sts =0;
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01033908); //[24] cmd_lp_en  =1                   0x01033908
	//[23:14] cmd_size  =cmd_size. 1 or 2   //write 4
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x1
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request

	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data3<<16) + (data2<<8) + data1));// DATA
	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}

#if 1
void dsc_cmd_send_buff(uint8_t *buff, uint32_t len)
{
	uint32_t reg, val, val2;
	int cmd_sts;
	uint8_t i = 0;

	reg = 0x01003908 | (len << 16);                 //0x01003908
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,reg); //[24] cmd_lp_en  =1    0x01043908
	//[23:14] cmd_size  cmd_size = len
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x1
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request
	val = len / 4;
	for(i = 0; i < val; i++)
	{
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * i) + 3]<<24) + (buff[(4 * i) + 2]<<16) + (buff[(4 * i) + 1]<<8) + buff[(4 * i)]));// DATA
	}
	val2 = len % 4;
	if(val2 == 1)
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,buff[(4 * val)]);// DATA
	else if(val2 == 2)
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * val) + 1]<<8) + buff[(4 * val)]));// DATA
	else if(val2 == 3)
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * val) + 2]<<16) + (buff[(4 * val) + 1]<<8) + buff[(4 * val)]));// DATA

	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}
#else
void dsc_cmd_send_buff(uint8_t *buff, uint32_t len)
{
	uint32_t reg, val, val2;
	int cmd_sts;
	uint8_t i = 0;

	reg = 0x01003908 | (len << 16);
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,reg); //[24] cmd_lp_en  =1    0x01043908
	//[23:14] cmd_size  cmd_size = len
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x1
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request
	val = len / 4;
	for(i = 0; i < val; i++)
	{
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * i) ]<<24) + (buff[(4 * i) + 1]<<16) + (buff[(4 * i) + 2]<<8) + buff[(4 * i) + 3]));// DATA
	}
	val2 = len % 4;
	if(val2 == 1)
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,buff[(4 * val) + 1]);// DATA
	else if(val2 == 2)
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * val) + 1]<<8) + buff[(4 * val) + 2]));// DATA
	else if(val2 == 3)
		DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * val) +1]<<16) + (buff[(4 * val) + 2]<<8) + buff[(4 * val) + 3]));// DATA

	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}
#endif
void dsc_cmd_send_short_pag(uint8_t val)
{
	uint8_t reg = 0;
	int cmd_sts;

	// reg = 0x01000500 | (val << 16);
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01010500); //[24] cmd_lp_en  =1    0x01010500
	//[23:14] cmd_size  =cmd_size. 1 or 2   //write 4
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x0  short pkg
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request
	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,val);                         // DATA            ???

	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send

	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}

void dsc_cmd_hs_send_short_pag(uint8_t val)
{
	uint8_t reg = 0;
	int cmd_sts;

	// reg = 0x01000500 | (val << 16);
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x00010500); //[24] cmd_lp_en  =1    0x01010500
	//[23:14] cmd_size  =cmd_size. 1 or 2   //write 4
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x0  short pkg
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request
	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,val);                         // DATA            ???

	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send

	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}

void  dsc_cmd_send_37(uint8_t val)
{
	int cmd_sts =0;


	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01013700); //[24] cmd_lp_en  =1              0x01023908
	//[23:14] cmd_size  =cmd_size. 1 or 2
	//[13:8] cmd_head  =0x39
	//[3 ] cmd_longnotshort  =0x1
	//[2:0] cmd_nat : 3'b000:write command
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request
	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,val);                         // DATA            ???
	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed


}

void hx8399_c_read_data(uint32_t addr, uint32_t len)
{
	int cmd_sts =0;
	int data = 0;
	int size;
	int err;
	int reg = 0;
	int i = 0;
	int cut = 0;

	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0xffffffff);
	DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);



	reg = 0x01000601 | (1 << 16);
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,reg);                   //[24] cmd_lp_en  =1            0x01010601          0x01020501
	//[23:16] cmd_size  =cmd_size. 1 or 2
	//[14:15] cmd_type  0 write  1 read                     1
	//[13:8] cmd_head  =0x5                                 6
	//[3 ] cmd_longnotshort  =0x1                           1
	//[2:0] cmd_nat : 3'b000:write command                  01
	//                3'b001:read command
	//                3'b100:TE request
	//                3'b101:trigger request
	//                3'b110:BTA request

	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET, addr);
	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0xffffffff); // cmd send

	while((cmd_sts & 0x08 )!= 0x08)                                 //wait read success
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}

	err = DsiRegRd(DIRECT_CMD_RD_STS_OFFSET);                   //read err
	size = DsiRegRd(DIRECT_CMD_RD_PROPERTY_OFFSET);             // read size [16 - 23]
	//        data = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);                   //read data

	k510_logci("addr is %x err is 0x%8x, size is 0x%8x, \n", addr, err, size);

	for(i = 0; i < len / 4; i++)
	{
		data = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);                   //read data
		k510_logci("i is %d addr is %x ,  data is 0x%8x \n" ,i, addr, data);
	}
	if((len % 4) != 0)
	{
		data = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);                   //read data
		k510_logci("addr is %x ,  data is 0x%8x \n", addr, data);
	}
	k510_logci("\n");
	//        k510_logci("addr is %x err is 0x%8x, size is 0x%8x, data is 0x%8x \n", addr, err, size, data);
}

int32_t hx8399_read_id(void)
{
	int32_t reg;
	int32_t cmd_sts = 0;
	int32_t err;
	int32_t size;
	int32_t id;
	int32_t retry = 5;

	dsc_cmd_send_37(3);

	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET, 0xffffffff);
	DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);
	DsiRegWr(DIRECT_CMD_FIFO_RST_OFFSET, 0xffffffff);

	reg = 0x01000601 | (1 << 16);
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET, reg);
	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET, 0x04);
	DsiRegWr(DIRECT_CMD_SEND_OFFSET, 0xffffffff);

	while ((cmd_sts & 0x08) != 0x08) {
		usleep(1000);
		retry--;
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		if (retry == 0)
			return -1;
	}

	err = DsiRegRd(DIRECT_CMD_RD_STS_OFFSET);
	size = DsiRegRd(DIRECT_CMD_RD_PROPERTY_OFFSET);
	id = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);
	printf("lcd_id [%02x]\n", id);

	return id;
}

void hx8399_v2_init(void)
{
	uint8_t param1[] = {0xB9, 0xFF, 0x83, 0x99};
	uint8_t param21[] = {0xD2, 0xAA};
	uint8_t param2[] = {0xB1, 0x02, 0x04, 0x71, 0x91, 0x01, 0x32, 0x33, 0x11, 0x11, 0xab, 0x4d, 0x56, 0x73, 0x02, 0x02};
	uint8_t param3[] = {0xB2, 0x00, 0x80, 0x80, 0xae, 0x05, 0x07, 0x5a, 0x11, 0x00, 0x00, 0x10, 0x1e, 0x70, 0x03, 0xd4};
	uint8_t param4[] = {0xB4, 0x00, 0xFF, 0x02, 0xC0, 0x02, 0xc0, 0x00, 0x00, 0x08, 0x00, 0x04, 0x06, 0x00, 0x32, 0x04, 0x0a, 0x08, 0x21, 0x03, 0x01, 0x00, 0x0f, 0xb8, 0x8b, 0x02, 0xc0, 0x02, 0xc0, 0x00, 0x00, 0x08, 0x00, 0x04, 0x06, 0x00, 0x32, 0x04, 0x0a, 0x08, 0x01, 0x00, 0x0f, 0xb8, 0x01};
	uint8_t param5[] = {0xD3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x05, 0x05, 0x07, 0x00, 0x00, 0x00, 0x05, 0x40};
	uint8_t param6[] = {0xD5, 0x18, 0x18, 0x19, 0x19, 0x18, 0x18, 0x21, 0x20, 0x01, 0x00, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x2f, 0x2f, 0x30, 0x30, 0x31, 0x31, 0x18, 0x18, 0x18, 0x18};
	uint8_t param7[] = {0xD6, 0x18, 0x18, 0x19, 0x19, 0x40, 0x40, 0x20, 0x21, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x2f, 0x2f, 0x30, 0x30, 0x31, 0x31, 0x40, 0x40, 0x40, 0x40};
	uint8_t param8[] = {0xD8, 0xa2, 0xaa, 0x02, 0xa0, 0xa2, 0xa8, 0x02, 0xa0, 0xb0, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00};
	uint8_t param9[] = {0xBD, 0x01};
	uint8_t param10[] = {0xD8, 0xB0, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0xE2, 0xAA, 0x03, 0xF0, 0xE2, 0xAA, 0x03, 0xF0};
	uint8_t param11[] = {0xBD, 0x02};
	uint8_t param12[] = {0xD8, 0xE2, 0xAA, 0x03, 0xF0, 0xE2, 0xAA, 0x03, 0xF0};
	uint8_t param13[] = {0xBD, 0x00};
	uint8_t param14[] = {0xB6, 0x8D, 0x8D};
	uint8_t param15[] = {0xCC, 0x04};
	uint8_t param16[] = {0xC6, 0xFF, 0xF9};
	uint8_t param22[] = {0xE0, 0x00, 0x12, 0x1f, 0x1a, 0x40, 0x4a, 0x59, 0x55, 0x5e, 0x67, 0x6f, 0x75, 0x7a, 0x82, 0x8b, 0x90, 0x95, 0x9f, 0xa3, 0xad, 0xa2, 0xb2, 0xB6, 0x5e, 0x5a, 0x65, 0x77, 0x00, 0x12, 0x1f, 0x1a, 0x40, 0x4a, 0x59, 0x55, 0x5e, 0x67, 0x6f, 0x75, 0x7a, 0x82, 0x8b, 0x90, 0x95, 0x9f, 0xa3, 0xad, 0xa2, 0xb2, 0xB6, 0x5e, 0x5a, 0x65, 0x77};
	dsc_cmd_send_buff(param1, sizeof(param1));
	msleep(2);
	dsc_cmd_send_buff(param21, sizeof(param21));
	msleep(2);
	dsc_cmd_send_buff(param2, sizeof(param2));
	msleep(2);
	dsc_cmd_send_buff(param3, sizeof(param3));
	msleep(2);
	dsc_cmd_send_buff(param4, sizeof(param4));
	msleep(2);
	dsc_cmd_send_buff(param5, sizeof(param5));
	msleep(2);
	dsc_cmd_send_buff(param6, sizeof(param6));
	msleep(2);
	dsc_cmd_send_buff(param7, sizeof(param7));
	msleep(2);
	dsc_cmd_send_buff(param8, sizeof(param8));
	msleep(2);
	dsc_cmd_send_buff(param9, sizeof(param9));
	msleep(2);
	dsc_cmd_send_buff(param10, sizeof(param10));
	msleep(2);
	dsc_cmd_send_buff(param11, sizeof(param11));
	msleep(2);
	dsc_cmd_send_buff(param12, sizeof(param12));
	msleep(2);
	dsc_cmd_send_buff(param13, sizeof(param13));
	msleep(2);
	dsc_cmd_send_buff(param14, sizeof(param14));
	msleep(2);
	dsc_cmd_send_buff(param15, sizeof(param15));
	msleep(2);
	dsc_cmd_send_buff(param16, sizeof(param16));
	msleep(2);
	dsc_cmd_send_buff(param22, sizeof(param22));
	msleep(2);

	dsc_cmd_send_short_pag(0x11);
	msleep(300);
	dsc_cmd_send_short_pag(0x29);
	msleep(100);
}

void hx8399_c_init(void)
{
	uint8_t pag1[5] = {0xB9, 0xFF, 0x83, 0x99};
	uint8_t pag2[20] = {0xB1, 0x02, 0x04, 0x70, 0x90, 0x01, 0x32, 0x33, 0x11, 0x11, 0x4D, 0x57, 0x56, 0x73, 0x02, 0x02};           // 0x10
	uint8_t pag3[20] = {0xB2, 0x00, 0x80, 0x80, 0xAE, 0x05, 0x07, 0x5A, 0x11, 0x10, 0x10, 0x00};                     // 0c
	//      uint8_t pag3[20] = {0xB2, 0x00, 0x80, 0x80, 0xAE, 0x05, 0x00, 0x5A, 0x11, 0x10, 0x10, 0x00};                     // 0c  0x3b- > 0b  03

	uint8_t pag4[50] = {0xB4, 0x00, 0xFF, 0x04, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x24, 0x02, 0x04, 0x09, 0x21, 0x03, 0x00, 0x00, 0x0A, 0x90, 0x88, 0x04, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x24, 0x02, 0x04, 0x08, 0x00, 0x00, 0x02, 0x88, 0x00, 0x08};
	uint8_t pag5[50] = {0xD3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x32, 0x10, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x05, 0x05, 0x13, 0x00, 0x00, 0x00, 0x05, 0x40, 0x00, 0x00, 0x00, 0x05, 0x20, 0x80};
	uint8_t pag6[50] = {0xD5, 0x00, 0x00, 0x21, 0x20, 0x19, 0x19, 0x18, 0x18, 0x00, 0x00, 0x01, 0x00, 0x18, 0x18, 0x03, 0x02, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x31, 0x30, 0x30, 0x2F, 0x2F};
	uint8_t pag7[50] = {0xD6, 0x40, 0x40, 0x20, 0x21, 0x18, 0x18, 0x19, 0x19, 0x40, 0x40, 0x02, 0x03, 0x18, 0x18, 0x00, 0x01, 0x19, 0x19, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x31, 0x31, 0x30, 0x30, 0x2F, 0x2F};
	uint8_t pag8[20] = {0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t pag9[5] = {0xBD, 0x01};
	uint8_t pag10[20] = {0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t pag11[5] = {0xBD, 0x02};
	uint8_t pag12[20] = {0xD8, 0xAA, 0xAE, 0xEA, 0xAA, 0xAA, 0xAE, 0xEA, 0xAA};
	uint8_t pag13[5] = {0xBD, 0x00};
	uint8_t pag14[60] = {0xE0, 0x01, 0x15, 0x22, 0x1E, 0x46, 0x51, 0x5E, 0x5A, 0x63, 0x6A, 0x71, 0x76, 0x7B, 0x82, 0x88, 0x8D, 0x92, 0x9C, 0xA0, 0xAB, 0xA2, 0xB5, 0xBD, 0x63, 0x61, 0x6E, 0x7A, 0x01, 0x15, 0x22, 0x1E, 0x46, 0x51, 0x5E, 0x5A, 0x63, 0x6A, 0x71, 0x76, 0x7B, 0x82, 0x89, 0x8E, 0x92, 0x9C, 0xA0, 0xAB, 0xA2, 0xB5, 0xBD, 0x63, 0x61, 0x6E, 0x7A};
	uint8_t pag15[5] = {0xC0, 0x25, 0x5A};
	uint8_t pag16[5] = {0xB6, 0x91, 0x91};
	uint8_t pag17[50] = {0xD2, 0x66};
	uint8_t pag18[50] = {0xCC, 0x08};
	uint8_t pag19[50] = {0x36, 0x08};

	//       uint8_t pag20[50] = {0xB2, 0x0b, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44};               // 蓝色
	//       uint8_t pag20[50] = {0xB2, 0x0b, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33};               // green  ok
	//       uint8_t pag20[50] = {0xB2, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};               //白色   ok

	//       uint8_t pag20[50] = {0xB2, 0x0b, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77};               // Color Bar  ok

	uint8_t pag20[50] = {0xB2, 0x0b, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22};                // red

	//       uint8_t pag20[50] = {0xB2, 0x0b, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb};               // Cross-Talk: black square in white pattern
	//       uint8_t pag20[50] = {0xB2, 0x0b, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};               // ross-Talk: white square in black pattern

	//        uint8_t pag20[50] = {0xB2, 0x0b, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88};               // H-Grayscale Gradation
	//        uint8_t pag20[50] = {0xB2, 0x0b, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99};               // V-Grayscale Gradation

	//        uint8_t pag20[50] = {0xB2, 0x0b, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc};               // Dot Checker: 2x2
	//        uint8_t pag20[50] = {0xB2, 0x0b, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd};               // Dot Checker: 1 * 1
	//        uint8_t pag20[50] = {0xB2, 0x0b, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};               // heisie

	// liange short pag
	//05 11 00 XX
	// 05 29 00 XX


	dsc_cmd_send_buff(pag1, 4);                             // access the extension commands.
	msleep(2);
	dsc_cmd_send_buff(pag2, 16);          //Set power related register
	msleep(2);
	dsc_cmd_send_buff(pag3, 12);          // Set display related register
	msleep(2);
	dsc_cmd_send_buff(pag4, 46);
	msleep(2);
	dsc_cmd_send_buff(pag5, 40);
	msleep(2);
	dsc_cmd_send_buff(pag6, 33);
	msleep(2);
	dsc_cmd_send_buff(pag7, 33);
	msleep(2);
	dsc_cmd_send_buff(pag8, 17);
	msleep(2);
	dsc_cmd_send(2, 0xBD, 0x01);

	//        dsc_cmd_send(2, 0xb2, 0xc8);
	//        dsc_cmd_send_buff(pag20, 10);                   // test  mode

	dsc_cmd_send_buff(pag10, 17);
	msleep(2);
	dsc_cmd_send(2, 0xBD, 0x02);
	msleep(2);
	dsc_cmd_send_buff(pag12, 9);
	msleep(2);
	dsc_cmd_send(2, 0xBD, 0x00);
	msleep(2);
	dsc_cmd_send_buff(pag14, 55);
	msleep(2);
	//        dsc_cmd_send_3(0xC0, 0x25, 0x5A);
	dsc_cmd_send_buff(pag15, 3);
	msleep(2);
	dsc_cmd_send_buff(pag16, 3);
	//        dsc_cmd_send_3(0xB6, 0x91, 0x91);
	msleep(2);
	//        dsc_cmd_send_3(0xB6, 0x61, 0x03);                       // set 2 lan

	dsc_cmd_send(2, 0xD2, 0x66);
	msleep(2);
	dsc_cmd_send(2, 0xCC, 0x00);
	msleep(2);
	dsc_cmd_send(2, 0x36, 0x01);
	msleep(2);

	dsc_cmd_send_short_pag(0x11);
	msleep(300);
	dsc_cmd_send_short_pag(0x29);
	msleep(100);

	/*
	   hx8399_c_read_data(0x06, 1);
	   hx8399_c_read_data(0x07, 1);
	   hx8399_c_read_data(0x08, 1);
	   hx8399_c_read_data(0x09, 1);
	   hx8399_c_read_data(0x0a, 1);
	   hx8399_c_read_data(0x0b, 1);
	   hx8399_c_read_data(0x0f, 1);
	   hx8399_c_read_data(0x0d, 1);
	   hx8399_c_read_data(0x0c, 1);
	 */

#if 0
	dsc_cmd_send_37(4);                            // set read data len
	hx8399_c_read_data(0xB9, 4);

	dsc_cmd_send_37(16);                            // set read data len
	hx8399_c_read_data(0xB1, 16);

	dsc_cmd_send_37(12);                            // set read data len           多个1f
	hx8399_c_read_data(0xB2, 11);
#endif

	/*
	   dsc_cmd_send_37(46);                            // set read data len
	   hx8399_c_read_data(0xB4, 46);

	   dsc_cmd_send_37(40);                            // set read data len
	   hx8399_c_read_data(0xd3, 40);

	   dsc_cmd_send_37(33);                            // set read data len
	   hx8399_c_read_data(0xd5, 33);

	   dsc_cmd_send_37(33);                            // set read data len
	   hx8399_c_read_data(0xd6, 33);

	   dsc_cmd_send_37(17);                            // set read data len
	   hx8399_c_read_data(0xd8, 17);
	 */
	/*
	   dsc_cmd_send_37(55);                            // set read data len
	   hx8399_c_read_data(0xe0, 55);

	   dsc_cmd_send_37(4);                            // set read data len
	   hx8399_c_read_data(0xc0, 3);

	   dsc_cmd_send_37(4);                            // set read data len
	   hx8399_c_read_data(0xb6, 3);

	   dsc_cmd_send_37(4);                            // set read data len
	   hx8399_c_read_data(0xd2, 2);

	   dsc_cmd_send_37(4);                            // set read data len
	   hx8399_c_read_data(0xcc, 2);

	   dsc_cmd_send_37(4);                            // set read data len
	   hx8399_c_read_data(0x36, 2);
	 */
}

#endif


void test(void)
{
	int i = 0;
	uint32_t reg = 0;
	uint32_t wdata;
	int cmd_sts =0;
#if 1
	//        sysctl_reset(SYSCTL_RESET_DSI);

	/*****************reset d-phy*****************/
#if 1
	sleep(1);
	DsiRegWr(MCTL_DPHY_CFG0_OFFSET,0xf0600);                // dsi reset dphy

	wdata = 0xda036000;                                     // set d-phy
	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

	wdata = 0x3b01e;                                        // set d-phy
	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x4);

	wdata = 0x9a036000;                                     // set d-phy
	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);            //0x92718000

#if 0
	while((cmd_sts & 0x9a036000 )!= 0x9a036000)                             // 读取0x88 是读取4 还是 1
	{
		cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
	}

	while((cmd_sts & 0x08 )!= 0x08)                             // 读取0x88 是读取4 还是 1
	{
		cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
	}

	while((cmd_sts & 0x08 )!= 0x00)                             // 读取0x88 是读取4 还是 1
	{
		cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
	}

	while((cmd_sts & 0x04 )!= 0x04)                             // 读取0x88 是读取4 还是 1
	{
		cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
	}

	while((cmd_sts & 0x04 )!= 0xf0600)                             // 读取0x88 是读取4 还是 1
	{
		cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
	}
#endif

	//是不是需要读取1_8014 的状态，0x04 和 0xf0600  这两个

	sleep(1);
	DsiRegWr(MCTL_DPHY_CFG0_OFFSET, 0x1f0600);              // dsi reset dphy
#if 1
	sleep(1);
#ifndef _FPGA
	k510_logci("before SYSCTL_DRV_Init\n");

	//        SYSCTL_DRV_Init();

	k510_logci("SYSCTL_DRV_Init done\n");
	//        mipi_rxdphy_init(RXDPHY_SPEED_MODE_1500M, RXDPHY_CHCFG_1X4);
	k510_logci("mipi_rxdphy_init done\n");

	mipi_txdphy_init();
	//        mipi_txdphy_init_10M();

	k510_logci("mipi_txdphy_init done\n");
#endif

	//       VI_DRV_Init();

	k510_logci("ISP_DRV_InitInterrupt done\n");
	//
	/*
	   VO_DRV_Init();

	   TOF_DRV_Init();
	   MFBC_DRV_Init();
	   TD_DRV_Init();
	   BT1120_DRV_Init();
	   k510_logci("BT1120_DRV_Init done\n");
	 */
#endif

#endif

#if 0
	/**************config dsi****************************/

	wdata = 0xf180000;                                     // set d-phy
	writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

	DsiRegWr(MCTL_DPHY_TIMEOUT1_OFFSET,0xafffb);                // dsi reset dphy   0x14
	DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0xbfe7);                // dsi reset dphy     0x08
	DsiRegWr(MCTL_MAIN_EN_OFFSET,0x40f9);                // dsi reset dphy          0xc
	DsiRegWr(MCTL_DPHY_TIMEOUT2_OFFSET,0xffff);                // dsi reset dphy    0x18
	DsiRegWr(MCTL_ULPOUT_TIME_OFFSET,0x3ab05);                // dsi reset dphy     0x1c
	DsiRegWr(VID_ERR_COLOR1_OFFSET,0xccaa);                // dsi reset dphy        0xe0
	DsiRegWr(VID_ERR_COLOR2_OFFSET,0xee55);                // dsi reset dphy        0xe4
	DsiRegWr(MCTL_DPHY_CFG0_OFFSET,0x1f0600);                // dsi reset dphy      0x10
	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x23);                // dsi reset dphy      0x4

	DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x80);                // dsi reset dphy      0x138
	DsiRegWr(VID_VCA_SETTING2_OFFSET,0x17dc0000);                // dsi reset dphy  0xf8
	DsiRegWr(VID_VSIZE1_OFFSET,0x9145);                // dsi reset dphy            0xb4
	DsiRegWr(VID_VSIZE2_OFFSET,0x438);                // dsi reset dphy             0xb8
	DsiRegWr(VID_HSIZE1_OFFSET,0x6c002e);                // dsi reset dphy          0xc0
	DsiRegWr(VID_HSIZE2_OFFSET,0xea1680);                // dsi reset dphy          0xc4

	DsiRegWr(VID_BLKSIZE1_OFFSET,0xb400000);                // dsi reset dphy       0xcc
	DsiRegWr(VID_BLKSIZE2_OFFSET,0x17e2);                // dsi reset dphy          0xd0
	DsiRegWr(VID_PCK_TIME_OFFSET,0x5a2);                // dsi reset dphy           0xd8
	DsiRegWr(VID_DPHY_TIME_OFFSET,0x1e05fa);                // dsi reset dphy       0xdc
	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x6e027);                // dsi reset dphy   0x4
	DsiRegWr(VID_MAIN_CTL_OFFSET,0x8218fe00);                // dsi reset dphy      0xb0

	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0xe027);                // dsi reset dphy    0x4
	DsiRegWr(VID_MAIN_CTL_OFFSET,0x8218fe00);                // dsi reset dphy      0xb0
	DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x20003fe7);                // dsi reset dphy      0x08

	//        DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x2003fe7);          // dsi reset dphy

	wait_phy_pll_locked();
	k510_logci("phy pll locked ");

	wait_cklane_rdy();
	k510_logci("cklane  is ready!!! ");
	wait_dat1_rdy();
	k510_logci("dat1  is ready!!! ");
	wait_dat2_rdy();
	k510_logci("dat2  is ready!!! ");
	wait_dat3_rdy();
	k510_logci("dat3  is ready!!! ");
	wait_dat4_rdy();
	k510_logci("dat4  is ready!!! ");


	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x6e027);                // dsi reset dphy   0x4
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0xffffffff);             // dsi reset dphy   0x158
	DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);         // dsi reset dphy   0x15c

	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x3010505);        // dsi reset dphy   0x84
	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0xffffffff);                // dsi reset dphy   0x80


	while((cmd_sts & 0x04 )!= 0x04)                             // 读取0x88 是读取4 还是 1
	{
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}

#endif


#endif

#if 0
	for(i = 0; i < 127; i++)
	{

		reg = DsiRegRd(i * 4);
		k510_logci("reg 0x%04x is 0x%08x \n", i * 4, reg) ;
	}
#endif

#if 0
	k510_logci("\n\n SYSCTL_CLK_MIPI_REF out clk freq is %d \r\n\n",sysctl_clk_get_leaf_freq(SYSCTL_CLK_MIPI_REF));
	sleep(1);

	DsiRegWr(DPI_IRQ_EN_OFFSET, 0); //enable dpi overflow int

	DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x3C17);    //[6]  lane1_ulp_en = 1
	//[4]  clk_continuous  =1
	//[2]  lane4_en =1
	//[1]  lane3_en =1
	//[0]  lane2_en =1
	DsiRegWr(MCTL_DPHY_TIMEOUT1_OFFSET,0xed8afffb);
	DsiRegWr(MCTL_DPHY_TIMEOUT2_OFFSET,0xf30fffff);
	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x2e027); //[6] tvg_sel = 1  test video generator enabled   //default 0x27
	//[5] vid_en = 1   enable the video stream generator
	//[3:2] vid_if_select =2'b00  00:sdi;01:dpi��10:DSC
	//[1] sdi_if_vid_mode = 1  select video mode
	//[0] link_en = 1; // enable link
	DsiRegWr(MCTL_MAIN_EN_OFFSET,0x40f9);
	//[15]   if3_en: enable dsc interface
	//[14]   if2_en: enable dpi interface   =1
	//[13]   if1_en: enable sdi interface
	//[9]   lane1_ulp_req =1
	//[7]   dat4_en
	//[6]   dat3_en
	//[5]   dat2_en
	//[4]   dat1_en
	//[3]   cklane_en


	//disable status detection
	unsigned int data = DsiRegRd(CMD_MODE_STS_CTL_OFFSET);
	k510_logci("CMD_MODE_STS_CTL_OFFSET data 0x%x\n",data);
	data &= ~ (1 << 0);
	DsiRegWr(CMD_MODE_STS_CTL_OFFSET,data );


	wait_phy_pll_locked();
	k510_logci("phy pll locked ");

	wait_cklane_rdy();
	k510_logci("cklane  is ready!!! ");
	wait_dat1_rdy();
	k510_logci("dat1  is ready!!! ");
	wait_dat2_rdy();
	k510_logci("dat2  is ready!!! ");
	wait_dat3_rdy();
	k510_logci("dat3  is ready!!! ");
	wait_dat4_rdy();
	k510_logci("dat4  is ready!!! ");
	// will init lcd
	DsiRegWr(MCTL_ULPOUT_TIME_OFFSET,0x0003ab05);
#if 0
	for(i = 0; i < 127; i++)
	{

		reg = DsiRegRd(i * 4);
		k510_logci("reg 0x%04x is 0x%08x \n", i * 4, reg) ;
	}
#endif
#endif
	//        sleep(5);
	//       aml_lcd_init();
	//        ILI7807_lcd_init();

}

void dsi_prepare(void)
{
	DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,
			0x3C07); //[6]  lane1_ulp_en = 1   正常的   0x3C17 clk_continuous
	//[4]  clk_continuous  =1
	//[2]  lane4_en =1
	//[1]  lane3_en =1
	//[0]  lane2_en =1

	//[0]  lane2_en =1

	DsiRegWr(MCTL_DPHY_TIMEOUT1_OFFSET, 0xed8afffb);
	DsiRegWr(MCTL_DPHY_TIMEOUT2_OFFSET, 0xf30fffff);
	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,
			0x2e027); //[6] tvg_sel = 1  test video generator enabled   //default
	//0x27                         0x2e067 [5] vid_en = 1
	//enable the video stream generator [3:2] vid_if_select
	//=2'b00  00:sdi;01:dpi��10:DSC [1] sdi_if_vid_mode = 1
	//select video mode [0] link_en = 1; // enable link

	DsiRegWr(MCTL_MAIN_EN_OFFSET,
			0x40f9); // 4 lan
	//[15]   if3_en: enable dsc interface
	//[14]   if2_en: enable dpi interface   =1
	//[13]   if1_en: enable sdi interface
	//[9]   lane1_ulp_req =1
	//[7]   dat4_en
	//[6]   dat3_en
	//[5]   dat2_en
	//[4]   dat1_en
	//[3]   cklane_en

	// disable status detection
	unsigned int data = DsiRegRd(CMD_MODE_STS_CTL_OFFSET);
	k510_logci("CMD_MODE_STS_CTL_OFFSET data 0x%x\n", data);
	data &= ~(1 << 0);
	DsiRegWr(CMD_MODE_STS_CTL_OFFSET, data);

	wait_phy_pll_locked();
	k510_logci("phy pll locked ");

	wait_cklane_rdy();
	k510_logci("cklane  is ready!!! ");
	wait_dat1_rdy();
	k510_logci("dat1  is ready!!! ");
	wait_dat2_rdy();
	k510_logci("dat2  is ready!!! ");

	wait_dat3_rdy();
	k510_logci("dat3  is ready!!! ");
	wait_dat4_rdy();
	k510_logci("dat4  is ready!!! ");

	// will init lcd
	DsiRegWr(MCTL_ULPOUT_TIME_OFFSET, 0x0003ab05);
	/*
	//fork  hs_skewcal_force_en
	reg = DsiRegRd(MCTL_MAIN_PHY_CTL_OFFSET);
	reg = reg | (1 << 29);
	DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET, reg);
	reg = DsiRegRd(MCTL_MAIN_PHY_CTL_OFFSET);
	k510_logci("reg is %x \n", reg);
	 */
}

static int32_t lcd_id = 0;
int32_t get_lcd_id(void)
{
	return lcd_id;
}

int32_t get_panel_id(void)
{
	int32_t reg;
	int32_t cmd_sts = 0;
	int32_t err;
	int32_t size;
	int32_t retry = 5;

	dsi_prepare();
	DsiRegWr(DPI_IRQ_EN_OFFSET, 1); // enable dpi overflow int
	msleep(100);

	dsc_cmd_send_37(3);

	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET, 0xffffffff);
	DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);
	DsiRegWr(DIRECT_CMD_FIFO_RST_OFFSET, 0xffffffff);

	reg = 0x01000601 | (1 << 16);
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET, reg);
	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET, 0x04);
	DsiRegWr(DIRECT_CMD_SEND_OFFSET, 0xffffffff);

	while ((cmd_sts & 0x08) != 0x08) {
		usleep(1000);
		retry--;
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
		if (retry == 0) {
			lcd_id = -1;
			return -1;
		}
	}

	err = DsiRegRd(DIRECT_CMD_RD_STS_OFFSET);
	size = DsiRegRd(DIRECT_CMD_RD_PROPERTY_OFFSET);
	lcd_id = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);
	printf("panel_id [%02X]\n", lcd_id);
	return lcd_id;
}

void dsi_init_1080x1920()
{
	int HACT = 1080;
	int VACT = 1920;
	int HSA = 20;
	int HBP = 20;
	int HFP = 134;

	int VSA = 5;
	int VBP = 8;
	int VFP = 5;

	int i = 0;
	uint32_t reg = 0;
	uint32_t val = 0;

	if (lcd_id == -1) {
		sysctl_reset(SYSCTL_RESET_DSI);
		mipi_txdphy_init();
		dsi_prepare();
	} else if (lcd_id == 0x1C9983)
		hx8399_v2_init();
	else
		hx8399_c_init();

	k510_logci("lcd init  ok!!! ");

	DsiRegWr(TVG_IMG_SIZE_OFFSET, (VACT << 16) + HACT * 3);
	DsiRegWr(TVG_COLOR1_OFFSET, (0 << 12) + 255); //[23:12] col1_green
	//[11:0]  col1_red
	DsiRegWr(TVG_COLOR1_BIS_OFFSET, 0);           //[11:0]  col1_blue
	DsiRegWr(TVG_COLOR2_OFFSET, (0 << 12) + 0);   //[23:12] col2_green
	//[11:0]  col2_red
	DsiRegWr(TVG_COLOR2_BIS_OFFSET, 255);         //[11:0]  col2_blue

	DsiRegWr(VID_VSIZE1_OFFSET, (VFP << 12) + (VBP << 6) + VSA);
	//[19:12] vfp_length
	//[11:6]  vbp_length
	//[5:0]   vsa_length
	DsiRegWr(VID_MODE_STS_CTL_OFFSET, 0); // 0xffffffff);
	DsiRegWr(VID_VSIZE2_OFFSET, VACT);    //[12:0] vact_length
	DsiRegWr(VID_HSIZE1_OFFSET, ((HBP * 3 - 12) << 16) + (HSA * 3 - 14));
	//[31:16] hbp_length  =(dpi_hbp*24/8-12)
	//[9:0]   hsa_length  =(dpi_hsa*24/8-14)

	DsiRegWr(VID_HSIZE2_OFFSET, ((HFP * 3 - 6) << 16) + (HACT * 3));
	//[26:16] hfp_length  =(dpi_hfp*24/8-6) >hss+hsa+hse+hbp
	//[14:0] rgb_size
	DsiRegWr(VID_BLKSIZE2_OFFSET,
			(HSA + HBP + HFP + HACT) * 3 - 20 - (HSA * 3 - 14));
	//[14:0] blkline_pulse_pck =
	//(dpi_hsa+dpi_hbp+dpi_hact+dpi_hfp)*24/8-20-((dpi_hsa*24/8)-14)=3342
	//  (1080+20+15+72)*3-20= 3541
	DsiRegWr(VID_DPHY_TIME_OFFSET, (0x38 << 17) +
			((HSA + HBP + HFP + HACT) * 3 / 4) -
			((HSA * 3 - 14) / 4));
	//[16:0] reg_line_duration =(line_total_)
	//[27:17] reg_wakeup_time
	DsiRegWr(VID_VCA_SETTING1_OFFSET, (0x000000));
	DsiRegWr(VID_VCA_SETTING2_OFFSET,
			((HSA + HBP + HFP + HACT) * 3 - 20 - (HSA * 3 - 14) - 6) << 16);

	//[31:16] max_line_limit = gen_blkline_pulse_pck-6;
	DsiRegWr(VID_MAIN_CTL_OFFSET,
			(0x1 << 31) + (0x1 << 25) + (0x0 << 21) + (1 << 20) + (1 << 19) +
			(3 << 14) + (0x3e << 8) +
			0); // 0x1 << 21
	//[31] vid_ignore_miss_vsync =1
	//[26:25] recovery_mode
	//[24:23] reg_blkeol_mode : same as reg_blkline_mode but
	//using in burst mode [22:21] reg_blkline_mode : 1x: LP
	//                            01: blanking packet
	//                            00: null packet

	//[20] sync_pulse_horizontal:syncs are pulse(1) or event(0)
	//[19] sync_pulse_active :1
	//[18] burst mode
	//[17:14] vid_pixel_mode  0000: 16 bits RGB
	//                        0001: 18 bits RGB
	//                        0010: 18 bits RGB(loose)
	//                        0011: 24 bits RGB
	//                        0100: 30 bits RGB
	//                        0101: 36 bits RGB
	//                        1000: 12 bits YCbCr
	//                        1001: 16 bits YCbCr
	//                        1010: 20 bits YCbCr
	//                        1011: 24 bits YCbCr
	//                        1100: DSC Compressed
	//[13:0] Header:  Datatype of RGB packets "0x3e  rgb24
	//[1:0]  start mode:start_mode=0
}

void gd9365da_800x1280(void)
{
	dsc_cmd_hs_read(0x04);

	dsc_cmd_hs_send(2,0xE1,0x93);

	dsc_cmd_hs_send(2,0xE2,0x65);
	dsc_cmd_hs_send(2,0xE3,0xF8);
	dsc_cmd_hs_send(2,0x80,0x03);

	dsc_cmd_hs_send(2,0xE0,0x01);

	//   dsc_cmd_hs_send(2,0x4a,0x35);      // test mode ??

	dsc_cmd_hs_send(2,0x00,0x00);
	dsc_cmd_hs_send(2,0x01,0x2A);
	dsc_cmd_hs_send(2,0x03,0x00);
	dsc_cmd_hs_send(2,0x04,0x30);
	dsc_cmd_hs_send(2,0x17,0x00);
	dsc_cmd_hs_send(2,0x18,0xE7);
	dsc_cmd_hs_send(2,0x19,0x00);
	dsc_cmd_hs_send(2,0x1A,0x00);
	dsc_cmd_hs_send(2,0x1B,0xE7);
	dsc_cmd_hs_send(2,0x1C,0x00);
	dsc_cmd_hs_send(2,0x35,0x23);
	dsc_cmd_hs_send(2,0x37,0x09);
	dsc_cmd_hs_send(2,0x38,0x04);
	dsc_cmd_hs_send(2,0x39,0x08);
	dsc_cmd_hs_send(2,0x3A,0x12);
	dsc_cmd_hs_send(2,0x3C,0x78);
	dsc_cmd_hs_send(2,0x3D,0xFF);
	dsc_cmd_hs_send(2,0x3E,0xFF);
	dsc_cmd_hs_send(2,0x3F,0xFF);
	dsc_cmd_hs_send(2,0x40,0x06);
	dsc_cmd_hs_send(2,0x41,0xA0);
	dsc_cmd_hs_send(2,0x43,0x14);
	dsc_cmd_hs_send(2,0x44,0x0F);
	dsc_cmd_hs_send(2,0x45,0x30);

	dsc_cmd_hs_send(2,0x4B,0x04);
	dsc_cmd_hs_send(2,0x55,0x02);
	dsc_cmd_hs_send(2,0x57,0x65);
	dsc_cmd_hs_send(2,0x59,0x0A);
	dsc_cmd_hs_send(2,0x5A,0x28);
	dsc_cmd_hs_send(2,0x5B,0x15);
	dsc_cmd_hs_send(2,0x5D,0x7C);
	dsc_cmd_hs_send(2,0x5E,0x5A);
	dsc_cmd_hs_send(2,0x5F,0x45);
	dsc_cmd_hs_send(2,0x60,0x36);
	dsc_cmd_hs_send(2,0x61,0x2F);
	dsc_cmd_hs_send(2,0x62,0x20);
	dsc_cmd_hs_send(2,0x63,0x24);
	dsc_cmd_hs_send(2,0x64,0x0F);
	dsc_cmd_hs_send(2,0x65,0x2C);
	dsc_cmd_hs_send(2,0x66,0x2E);
	dsc_cmd_hs_send(2,0x67,0x31);
	dsc_cmd_hs_send(2,0x68,0x52);
	dsc_cmd_hs_send(2,0x69,0x40);
	dsc_cmd_hs_send(2,0x6A,0x49);
	dsc_cmd_hs_send(2,0x6B,0x3E);
	dsc_cmd_hs_send(2,0x6C,0x3B);
	dsc_cmd_hs_send(2,0x6D,0x30);
	dsc_cmd_hs_send(2,0x6E,0x21);
	dsc_cmd_hs_send(2,0x6F,0x0C);
	dsc_cmd_hs_send(2,0x70,0x7C);
	dsc_cmd_hs_send(2,0x71,0x5A);
	dsc_cmd_hs_send(2,0x72,0x45);
	dsc_cmd_hs_send(2,0x73,0x36);
	dsc_cmd_hs_send(2,0x74,0x2F);
	dsc_cmd_hs_send(2,0x75,0x20);
	dsc_cmd_hs_send(2,0x76,0x24);
	dsc_cmd_hs_send(2,0x77,0x0F);
	dsc_cmd_hs_send(2,0x78,0x2C);
	dsc_cmd_hs_send(2,0x79,0x2E);
	dsc_cmd_hs_send(2,0x7A,0x31);
	dsc_cmd_hs_send(2,0x7B,0x52);
	dsc_cmd_hs_send(2,0x7C,0x40);
	dsc_cmd_hs_send(2,0x7D,0x49);
	dsc_cmd_hs_send(2,0x7E,0x3E);
	dsc_cmd_hs_send(2,0x7F,0x3B);
	dsc_cmd_hs_send(2,0x80,0x30);
	dsc_cmd_hs_send(2,0x81,0x21);
	dsc_cmd_hs_send(2,0x82,0x0C);

	dsc_cmd_hs_send(2,0xE0,0x02);
	dsc_cmd_hs_send(2,0x00,0x5F);
	dsc_cmd_hs_send(2,0x01,0x5F);
	dsc_cmd_hs_send(2,0x02,0x53);
	dsc_cmd_hs_send(2,0x03,0x51);
	dsc_cmd_hs_send(2,0x04,0x4B);
	dsc_cmd_hs_send(2,0x05,0x49);
	dsc_cmd_hs_send(2,0x06,0x47);
	dsc_cmd_hs_send(2,0x07,0x45);
	dsc_cmd_hs_send(2,0x08,0x41);
	dsc_cmd_hs_send(2,0x09,0x43);
	dsc_cmd_hs_send(2,0x0A,0x5F);
	dsc_cmd_hs_send(2,0x0B,0x5F);
	dsc_cmd_hs_send(2,0x0C,0x5F);
	dsc_cmd_hs_send(2,0x0D,0x5F);
	dsc_cmd_hs_send(2,0x0E,0x5F);
	dsc_cmd_hs_send(2,0x0F,0x5F);
	dsc_cmd_hs_send(2,0x10,0x5F);
	dsc_cmd_hs_send(2,0x11,0x5F);
	dsc_cmd_hs_send(2,0x12,0x5F);
	dsc_cmd_hs_send(2,0x13,0x5F);
	dsc_cmd_hs_send(2,0x14,0x5F);
	dsc_cmd_hs_send(2,0x15,0x5F);
	dsc_cmd_hs_send(2,0x16,0x5F);
	dsc_cmd_hs_send(2,0x17,0x5F);
	dsc_cmd_hs_send(2,0x18,0x52);
	dsc_cmd_hs_send(2,0x19,0x50);
	dsc_cmd_hs_send(2,0x1A,0x4A);
	dsc_cmd_hs_send(2,0x1B,0x48);
	dsc_cmd_hs_send(2,0x1C,0x46);
	dsc_cmd_hs_send(2,0x1D,0x44);
	dsc_cmd_hs_send(2,0x1E,0x40);
	dsc_cmd_hs_send(2,0x1F,0x42);
	dsc_cmd_hs_send(2,0x20,0x5F);
	dsc_cmd_hs_send(2,0x21,0x5F);
	dsc_cmd_hs_send(2,0x22,0x5F);
	dsc_cmd_hs_send(2,0x23,0x5F);
	dsc_cmd_hs_send(2,0x24,0x5F);
	dsc_cmd_hs_send(2,0x25,0x5F);
	dsc_cmd_hs_send(2,0x26,0x5F);
	dsc_cmd_hs_send(2,0x27,0x5F);
	dsc_cmd_hs_send(2,0x28,0x5F);
	dsc_cmd_hs_send(2,0x29,0x5F);
	dsc_cmd_hs_send(2,0x2A,0x5F);
	dsc_cmd_hs_send(2,0x2B,0x5F);
	dsc_cmd_hs_send(2,0x2C,0x1F);
	dsc_cmd_hs_send(2,0x2D,0x1F);
	dsc_cmd_hs_send(2,0x2E,0x00);
	dsc_cmd_hs_send(2,0x2F,0x02);
	dsc_cmd_hs_send(2,0x30,0x08);
	dsc_cmd_hs_send(2,0x31,0x0A);
	dsc_cmd_hs_send(2,0x32,0x04);
	dsc_cmd_hs_send(2,0x33,0x06);
	dsc_cmd_hs_send(2,0x34,0x12);
	dsc_cmd_hs_send(2,0x35,0x10);
	dsc_cmd_hs_send(2,0x36,0x1F);
	dsc_cmd_hs_send(2,0x37,0x1F);
	dsc_cmd_hs_send(2,0x38,0x1F);
	dsc_cmd_hs_send(2,0x39,0x1F);
	dsc_cmd_hs_send(2,0x3A,0x1F);
	dsc_cmd_hs_send(2,0x3B,0x1F);
	dsc_cmd_hs_send(2,0x3C,0x1F);
	dsc_cmd_hs_send(2,0x3D,0x1F);
	dsc_cmd_hs_send(2,0x3E,0x1F);
	dsc_cmd_hs_send(2,0x3F,0x1F);
	dsc_cmd_hs_send(2,0x40,0x1F);
	dsc_cmd_hs_send(2,0x41,0x1F);
	dsc_cmd_hs_send(2,0x42,0x1F);
	dsc_cmd_hs_send(2,0x43,0x1F);
	dsc_cmd_hs_send(2,0x44,0x01);
	dsc_cmd_hs_send(2,0x45,0x03);
	dsc_cmd_hs_send(2,0x46,0x09);
	dsc_cmd_hs_send(2,0x47,0x0B);
	dsc_cmd_hs_send(2,0x48,0x05);
	dsc_cmd_hs_send(2,0x49,0x07);
	dsc_cmd_hs_send(2,0x4A,0x13);
	dsc_cmd_hs_send(2,0x4B,0x11);
	dsc_cmd_hs_send(2,0x4C,0x1F);
	dsc_cmd_hs_send(2,0x4D,0x1F);
	dsc_cmd_hs_send(2,0x4E,0x1F);
	dsc_cmd_hs_send(2,0x4F,0x1F);
	dsc_cmd_hs_send(2,0x50,0x1F);
	dsc_cmd_hs_send(2,0x51,0x1F);
	dsc_cmd_hs_send(2,0x52,0x1F);
	dsc_cmd_hs_send(2,0x53,0x1F);
	dsc_cmd_hs_send(2,0x54,0x1F);
	dsc_cmd_hs_send(2,0x55,0x1F);
	dsc_cmd_hs_send(2,0x56,0x1F);
	dsc_cmd_hs_send(2,0x57,0x1F);
	dsc_cmd_hs_send(2,0x58,0x40);
	dsc_cmd_hs_send(2,0x59,0x00);
	dsc_cmd_hs_send(2,0x5A,0x00);
	dsc_cmd_hs_send(2,0x5B,0x30);
	dsc_cmd_hs_send(2,0x5C,0x09);
	dsc_cmd_hs_send(2,0x5D,0x30);
	dsc_cmd_hs_send(2,0x5E,0x01);
	dsc_cmd_hs_send(2,0x5F,0x02);
	dsc_cmd_hs_send(2,0x60,0x30);
	dsc_cmd_hs_send(2,0x61,0x03);
	dsc_cmd_hs_send(2,0x62,0x04);
	dsc_cmd_hs_send(2,0x63,0x1C);
	dsc_cmd_hs_send(2,0x64,0x6A);
	dsc_cmd_hs_send(2,0x65,0x75);
	dsc_cmd_hs_send(2,0x66,0x0D);
	dsc_cmd_hs_send(2,0x67,0x72);
	dsc_cmd_hs_send(2,0x68,0x0C);
	dsc_cmd_hs_send(2,0x69,0x1C);
	dsc_cmd_hs_send(2,0x6A,0x6A);
	dsc_cmd_hs_send(2,0x6B,0x08);
	dsc_cmd_hs_send(2,0x6C,0x00);
	dsc_cmd_hs_send(2,0x6D,0x00);
	dsc_cmd_hs_send(2,0x6E,0x00);
	dsc_cmd_hs_send(2,0x6F,0x88);
	dsc_cmd_hs_send(2,0x70,0x00);
	dsc_cmd_hs_send(2,0x71,0x00);
	dsc_cmd_hs_send(2,0x72,0x06);
	dsc_cmd_hs_send(2,0x73,0x7B);
	dsc_cmd_hs_send(2,0x74,0x00);
	dsc_cmd_hs_send(2,0x75,0xBB);
	dsc_cmd_hs_send(2,0x76,0x01);
	dsc_cmd_hs_send(2,0x77,0x0D);
	dsc_cmd_hs_send(2,0x78,0x24);
	dsc_cmd_hs_send(2,0x79,0x00);
	dsc_cmd_hs_send(2,0x7A,0x00);
	dsc_cmd_hs_send(2,0x7B,0x00);
	dsc_cmd_hs_send(2,0x7C,0x00);
	dsc_cmd_hs_send(2,0x7D,0x03);
	dsc_cmd_hs_send(2,0x7E,0x7B);

	dsc_cmd_hs_send(2,0xE0,0x04);
	dsc_cmd_hs_send(2,0x00,0x0E);
	dsc_cmd_hs_send(2,0x02,0xB3);
	dsc_cmd_hs_send(2,0x0E,0x4A);

	dsc_cmd_hs_send(2,0xE0,0x00);
	dsc_cmd_hs_send(2,0xE6,0x02);
	dsc_cmd_hs_send(2,0xE7,0x0C);

	dsc_cmd_hs_send_short_pag(0x11);  	// SLPOUT
	msleep(120);

	dsc_cmd_hs_send_short_pag(0x29);  	// DSPON
	msleep(5);

	dsc_cmd_hs_send(2,0x35,0x00);
}

//b cnds_dsi_test.c:901
void dsi_init_800x1280()
{
#if 1
	int HACT = 800;
	int HSA = 24;
	int HBP = 24 ;
	int HFP = 30 ;

	int VACT = 1280;
	int VSA = 4;
	int VBP = 12;
	int VFP = 8;
#else
	int  HACT=800;
	int  VACT=1280;
	int  HSA=20;
	int  HBP=20;
	int  HFP=120;//220;    //144

	int  VSA=5;
	int  VBP=8;
	int  VFP=5;
#endif
	printf("dsi for lcd init start\n");

	gd9365da_800x1280();

	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET, 0x1e021);
	DsiRegWr(MCTL_MAIN_EN_OFFSET, 0x40f9);
	//[6] tvg_sel = 1  test video generator enabled
	//[5] vid_en = 1   enable the video stream generator
	//[3:2] vid_if_select =2'b00  00:sdi;01:dpi��10:DSC
	//[1] sdi_if_vid_mode = 1  select video mode
	//[0] link_en = 1; // enable link

	DsiRegWr(TVG_IMG_SIZE_OFFSET, (VACT << 16) + HACT * 3);
	DsiRegWr(TVG_COLOR1_OFFSET, (0xFFF << 12) + 0); //[23:12] col1_green
	//[11:0]  col1_red
	DsiRegWr(TVG_COLOR1_BIS_OFFSET, 0);             //[11:0]  col1_blue
	DsiRegWr(TVG_COLOR2_OFFSET, (0x000 << 12) + 0x000);     //[23:12] col2_green
	//[11:0]  col2_red
	DsiRegWr(TVG_COLOR2_BIS_OFFSET, 0xFFF);         //[11:0]  col2_blue

	DsiRegWr(VID_VSIZE1_OFFSET, (VFP << 12) + (VBP << 6) + VSA);
	//[19:12] vfp_length
	//[11:6]  vbp_length
	//[5:0]   vsa_length
	DsiRegWr(VID_VSIZE2_OFFSET, VACT); //[12:0] vact_length
	DsiRegWr(VID_HSIZE1_OFFSET, ((HBP * 3 - 12) << 16) + (HSA * 3 - 14));
	//[31:16] hbp_length  =(dpi_hbp*24/8-12)
	//[9:0]   hsa_length  =(dpi_hsa*24/8-14)

	DsiRegWr(VID_HSIZE2_OFFSET, ((HFP * 3 - 6) << 16) + (HACT * 3));
	//[26:16] hfp_length  =(dpi_hfp*24/8-6) >hss+hsa+hse+hbp
	//[14:0] rgb_size
	DsiRegWr(VID_BLKSIZE2_OFFSET, (HBP + HFP + HACT) * 3 - 6);
	//[14:0] blkline_pulse_pck = (dpi_hsa+dpi_hbp+dpi_hact+dpi_hfp)*24/8-20-((dpi_hsa*24/8)-14)=3342
	// DsiRegWr(VID_DPHY_TIME_OFFSET, (0x38 << 17) + (((HBP + HFP + HACT) * 3 + 3) / 4));
	DsiRegWr(VID_DPHY_TIME_OFFSET, (0x38 << 17) + ((HSA + HBP + HFP + HACT) * 3 / 4) - ((HSA * 3 - 14) / 4));
	//[16:0] reg_line_duration =(line_total_)
	//[27:17] reg_wakeup_time
	DsiRegWr(VID_VCA_SETTING1_OFFSET, 0);
	DsiRegWr(VID_VCA_SETTING2_OFFSET, (((HBP + HFP + HACT) * 3 - 6 - 6) << 16));
	//[31:16] max_line_limit = gen_blkline_pulse_pck-6;
	DsiRegWr(VID_MAIN_CTL_OFFSET, (0x1 << 31) + (0x1 << 25) + (0x0 << 21) + (1 << 20) + (1 << 19) + (3 << 14) + (0x3e << 8) + 0);
	//[31] vid_ignore_miss_vsync =1
	//[26:25] recovery_mode
	//[24:23] reg_blkeol_mode : same as reg_blkline_mode but using in burst mode
	//[22:21] reg_blkline_mode : 1x: LP
	//                            01: blanking packet
	//                            00: null packet
	//[20] sync_pulse_horizontal:syncs are pulse(1) or event(0)
	//[19] sync_pulse_active :1
	//[18] burst mode
	//[17:14] vid_pixel_mode  0000: 16 bits RGB
	//                        0001: 18 bits RGB
	//                        0010: 18 bits RGB(loose)
	//                        0011: 24 bits RGB
	//                        0100: 30 bits RGB
	//                        0101: 36 bits RGB
	//                        1000: 12 bits YCbCr
	//                        1001: 16 bits YCbCr
	//                        1010: 20 bits YCbCr
	//                        1011: 24 bits YCbCr
	//                        1100: DSC Compressed
	//[13:0] Header:  Datatype of RGB packets "0x3e  rgb24
	//[1:0]  start mode:start_mode=0
	//         DsiRegWr(TVG_CTL_OFFSET,(6<<5)+(2<<3) + (2<<1) + 1 ) ;//[7:5]tvg_stripe_size
	//[4:3] tvg_mode 00:single color
	//                01:reserved
	//                10:verical  stripes
	//                11:horizontal  stripes
	//[2:1] tvg_stopmode  00: at the end of frame
	//                     01: at the end of line
	//                      1x: immediate
	//[0]   tvg run

	printf("dsi for lcd init done\n");

	printf("TVG start\n");
#if 0
	//test mode
	DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET, 0x1e061);    //test mode
	volatile uint8_t test_mode = 3;
	DsiRegWr(TVG_CTL_OFFSET, (6 << 5) + (test_mode << 3) + (0 << 1) + 1);
#endif
	// sleep(2);
	//  while (1);
	// DsiRegWr(TVG_CTL_OFFSET, (3 << 5) + (2 << 3) + (0 << 1) + 0);
	// DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET, 0x1e000);
	// DsiRegWr(VID_MODE_STS_CLR_OFFSET, 0x7ff);
	// DsiRegWr(TG_STS_CLR_OFFSET, 0x1);
	// msleep(100);
	// DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET, 0x1e021);
	// printf("TVG stop\n");
}
