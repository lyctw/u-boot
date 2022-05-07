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
#include "hw_dev/inc/dev_reg.h"
#include "hw_dev/inc/dev_hw.h"
#include <sleep.h>
#include <stdio.h>
#include <i2c.h>
#include <video/isp_com.h>

extern BOOL g_use_f23s;
extern BOOL g_use_opn8008;
extern BOOL g_use_f23s_imx385;
extern BOOL g_use_irs238c;
extern BOOL g_use_f23s_irs238c;
extern BOOL g_f23s_config;
extern BOOL g_use_imx385;
/*
*
*/
void DevRegWr(int addr,int data)
{
    int offset_addr = SENSOR_ADV7511CTRL_BASEADDR +(addr <<2);
    RegWr32(offset_addr,data) ;
}
/*
*
*/
int  DevRegRd(int addr)
{
    int offset_addr =0;
    offset_addr = SENSOR_ADV7511CTRL_BASEADDR +(addr <<2);
    return(RegRd32(offset_addr));
}
/*
*
*/
void  Dev_config_apb25MHZ(int byte_mode_config,int sensor_dev_addr,int dev_sel)
{
    DevRegWr(BYTE_MODE_CONFIG_OFFSET,byte_mode_config);
    DevRegWr(SENSOR_DEV_ADDR_OFFSET,sensor_dev_addr);
    int apb_clk_cnt = (10000/40);
    DevRegWr(I2C_CLK_PRIOD_OFFSET,apb_clk_cnt);
    DevRegWr(I2C_SEL_OFFSET,1<<dev_sel);
}
/*
*
*/
void  Dev_config_apb100MHZ(int byte_mode_config,int sensor_dev_addr,int dev_sel)
{
    DevRegWr(BYTE_MODE_CONFIG_OFFSET,byte_mode_config);
    DevRegWr(SENSOR_DEV_ADDR_OFFSET,sensor_dev_addr);
    int apb_clk_cnt = (10000/10);
    DevRegWr(I2C_CLK_PRIOD_OFFSET,apb_clk_cnt);
    DevRegWr(I2C_SEL_OFFSET,1<<dev_sel);
}
/*
*
*/
void  Set_manu(int enable)
{
#ifdef CANAAN_ISP
#else
    DevRegWr(SENSOR_MANU_OP_OFFSET,enable);
#endif
}
/*
*
*/
void  Set_auto(int enable)
{
#ifdef CANAAN_ISP
#else

    DevRegWr(SENSOR_AUTO_OP_OFFSET,enable);
#endif
}
/*
*
*/
void  Start_Config(int start_flag)
{
#ifdef CANAAN_ISP
#else

    DevRegWr(START_CONFIG_OFFSET,start_flag);
#endif
}
/*
*
*/
void  I2cWr(int addr,int data)
{
#ifdef CANAAN_ISP
    //dedicate for sensor i2c write
    if(g_use_f23s)
    {
        if(g_use_f23s_imx385)
        {
            unsigned char buf[3];
            buf[0] = (addr >> 8) & 0xff;
            buf[1] = addr & 0xff;
            buf[2] = data;
#ifdef USE_GPIO_I2C
            
            i2c_gpio_write_reg(0,0x1a,buf[0],&buf[1],1);
            
#else    
            i2c_send_data(I2C_DEVICE_2, buf, 3);
#endif

        }
        else
        {
            unsigned char buf[2];
            buf[0] = (addr >> 8) & 0xff;
            buf[1] = data;
#ifdef USE_GPIO_I2C
            
            i2c_gpio_write_reg(0,0x8c >> 1,buf[0],&buf[1],2);
            
#else    
            i2c_send_data(I2C_DEVICE_0, buf, 2);
#endif
        }
    }

    if(g_use_opn8008)
    {
        unsigned char buf[2];
        buf[0] = (addr >> 8) & 0xff;
        buf[1] = data;
#ifdef USE_GPIO_I2C
        
        i2c_gpio_write_reg(0,0x3d,buf[0],&buf[1],2);
        
#else    
        i2c_send_data(I2C_DEVICE_0, buf, 2);
#endif


    }

    if(g_use_irs238c)
    {
        unsigned char buf[4];
        buf[0] = (addr >> 8) & 0xff;
        buf[1] = addr & 0xff;
        buf[2] = (data >> 8) & 0xff;
        buf[3] = data & 0xff;
   
        i2c_send_data(I2C_DEVICE_0, buf, 4);

    }

    if(g_use_f23s_irs238c)
    {
    	if(g_f23s_config) //f23s
    	{
            unsigned char buf[2];
            buf[0] = (addr >> 8) & 0xff;
            buf[1] = data;
            i2c_send_data(I2C_DEVICE_0, buf, 2);
    	}
    	else //irs238c
    	{
            unsigned char buf[4];
            buf[0] = (addr >> 8) & 0xff;
            buf[1] = addr & 0xff;
            buf[2] = (data >> 8) & 0xff;
            buf[3] = data & 0xff;

            i2c_send_data(I2C_DEVICE_2, buf, 4);
    	}
    }

    if(g_use_imx385)
    {
        unsigned char buf[3];
        buf[0] = (addr >> 8) & 0xff;
        buf[1] = addr & 0xff;
        buf[2] = data;
#ifdef USE_GPIO_I2C
        
        i2c_gpio_write_reg(0,0x1a,buf[0],&buf[1],1);
        
#else    
        i2c_send_data(I2C_DEVICE_0, buf, 3);
#endif
    }
#else

    DevRegWr(SENSOR_ADDR_OFFSET,((addr<<16) +(data<<8)));
    DevRegWr(SENSOR_LATCH_OFFSET,0x01);
    DevRegWr(SENSOR_LATCH_OFFSET,0x00);
    DevRegWr(SENSOR_UPDATE_REQ_OFFSET,0x01);
    DevRegWr(SENSOR_UPDATE_REQ_OFFSET,0x00);
#endif
}
/*
*
*/
void  I2cRd(int addr)
{
#ifdef CANAAN_ISP
    unsigned char rddata =0; 

    if(g_use_f23s)
    {
        //dedicate for sensor i2c read
        if(g_use_f23s_imx385)
        {
            unsigned char reg[2];
            reg[0] = (addr >> 8) & 0xff;
            reg[1] = addr & 0xff;
#ifdef USE_GPIO_I2C
            i2c_gpio_read_reg(0,0x1a, reg,&rddata,1);
            printf("we have problem here to use gpio sim i2c for two bytes address!!!!,fix me\n");
#else
            i2c_recv_data(I2C_DEVICE_2, &reg, 2, &rddata, 1);
#endif
        }

        else
        {
            unsigned char reg = (addr >> 8) & 0xff;
#ifdef USE_GPIO_I2C
            i2c_gpio_read_reg(0,0x8c >> 1, reg,&rddata,1);
#else
            i2c_recv_data(I2C_DEVICE_0, &reg, 1, &rddata, 1);
#endif
        }
    }

    if(g_use_opn8008)
    {
        //dedicate for sensor i2c read

        unsigned char reg = (addr >> 8) & 0xff;
#ifdef USE_GPIO_I2C
        i2c_gpio_read_reg(0,0x3d, reg,&rddata,1);
#else
        i2c_recv_data(I2C_DEVICE_0, &reg, 1, &rddata, 1);
#endif
    }        

    if(g_use_irs238c)
    {
        unsigned char rdata[2]={0};
        //dedicate for sensor i2c read
        unsigned char reg[2];
        reg[0] = (addr >> 8) & 0xff;
        reg[1] = addr & 0xff;

        i2c_recv_data(I2C_DEVICE_0, reg, 2, rdata, 2);
        printf("irs3218c addr:%x data:%x\n",addr,(rdata[0]<< 8) | rdata[1]);

    }

    if(g_use_f23s_irs238c)
    {
    	if(g_f23s_config) //f23s
    	{
            unsigned char reg = (addr >> 8) & 0xff;
            i2c_recv_data(I2C_DEVICE_0, &reg, 1, &rddata, 1);
    	}
    	else //irs238c
    	{
            unsigned char rdata[2]={0};
            //dedicate for sensor i2c read
            unsigned char reg[2];
            reg[0] = (addr >> 8) & 0xff;
            reg[1] = addr & 0xff;

            i2c_recv_data(I2C_DEVICE_2, reg, 2, rdata, 2);
            printf("irs3218c addr:%x data:%x\n",addr,(rdata[0]<< 8) | rdata[1]);
    	}
    }

    if(g_use_imx385)
    {
        
        unsigned char reg[2];
        reg[0] = (addr >> 8) & 0xff;
        reg[1] = addr & 0xff;
#ifdef USE_GPIO_I2C
        i2c_gpio_read_reg(0,0x1a, reg,&rddata,1);
        printf("we have problem here to use gpio sim i2c for two bytes address!!!!,fix me\n");
#else
        i2c_recv_data(I2C_DEVICE_0, &reg, 2, &rddata, 1);
#endif

    }

    if(!g_use_irs238c)    
        printf("addr:%x data:%x\n",addr,rddata);

#else

    DevRegWr(SENSOR_ADDR_OFFSET,(addr<<16));
    DevRegWr(SENSOR_LATCH_OFFSET,0x01);
    DevRegWr(SENSOR_LATCH_OFFSET,0x00);
    DevRegWr(SENSOR_READ_REQ_OFFSET,0x01);
    DevRegWr(SENSOR_READ_REQ_OFFSET,0x00);
    msleep(1);
    int rddata = DevRegRd(SENSOR_READ_DATA_OFFSET)&0x00ff;
    printf("addr:%x data:%x\n",addr,rddata);

#endif   
    
}
/*
*
*/
void  HdmiI2cWr(int addr,int data)
{
 DevRegWr(HDMI_ADDR_DATA_OFFSET,((addr<<16) +(data<<8)));
 DevRegWr(HDMI_LATCH_OFFSET,0x01);
 DevRegWr(HDMI_LATCH_OFFSET,0x00);
 DevRegWr(HDMI_UPDATE_REQ_OFFSET,0x01);
 DevRegWr(HDMI_UPDATE_REQ_OFFSET,0x00);
}
/*
*
*/
void  HdmiI2cRd(int addr)
{

 DevRegWr(HDMI_ADDR_DATA_OFFSET,(addr<<16));
 DevRegWr(HDMI_LATCH_OFFSET,0x01);
 DevRegWr(HDMI_LATCH_OFFSET,0x00);
 DevRegWr(HDMI_READ_REQ_OFFSET,0x01);
 DevRegWr(HDMI_READ_REQ_OFFSET,0x00);
 msleep(1);
 int rddata = DevRegRd(HDMI_READ_DATA_OFFSET)&0x00ff;
 printf("addr:%x data:%x\n",addr,rddata);
}
/*
*
*/
void  Cv8788I2cWr(int addr,int data)
{
#ifdef CANAAN_ISP
    //dedicate for cv8788 write

    unsigned char buf[3];
    buf[0] = (addr >> 8) & 0xff;
    buf[1] = addr & 0xff;
    buf[2] = data;
    
    
    i2c_send_data(I2C_DEVICE_1, buf, 3);
#else

    DevRegWr(SENSOR_ADDR_OFFSET,((addr<<16) +(data<<8)));
    DevRegWr(SENSOR_LATCH_OFFSET,0x01);
    DevRegWr(SENSOR_LATCH_OFFSET,0x00);
    DevRegWr(SENSOR_UPDATE_REQ_OFFSET,0x01);
    DevRegWr(SENSOR_UPDATE_REQ_OFFSET,0x00);    
#endif
}
/*
*
*/
void  Cv8788I2cRd(int addr)
{

#ifdef CANAAN_ISP
    unsigned char rddata =0; 

    //dedicate for cv8788 read

    unsigned char reg[2];
    reg[0] = (addr >> 8) & 0xff;
    reg[1] = addr & 0xff;

    i2c_recv_data(I2C_DEVICE_1, &reg, 2, &rddata, 1);
    
#else

    DevRegWr(SENSOR_ADDR_OFFSET,(addr<<16));
    DevRegWr(SENSOR_LATCH_OFFSET,0x01);
    DevRegWr(SENSOR_LATCH_OFFSET,0x00);
    DevRegWr(SENSOR_READ_REQ_OFFSET,0x01);
    DevRegWr(SENSOR_READ_REQ_OFFSET,0x00);
    msleep(1);
    int rddata = DevRegRd(SENSOR_READ_DATA_OFFSET)&0x00ff;

#endif
    printf("addr:%x data:%x\n",addr,rddata);
}