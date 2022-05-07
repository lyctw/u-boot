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
#include <k510.h>
#include <cache.h>
#include <interrupt.h>
#include <sleep.h>
#include <i2c.h>
#include <muxpin.h>
#include <gpio.h>

#include <video/video_subsystem_addr.h>

#include "hw_dev/inc/dev_reg.h"
#include "hw_dev/inc/ext_ctl_hw.h"
#include "hw_dev/inc/fpga_system.h"
#include "sensor/sensor.h"

extern BOOL g_use_f23s;
extern BOOL g_use_opn8008;
extern BOOL g_use_bt1120;
extern BOOL g_use_f23s_imx385;
extern BOOL g_use_irs238c;
/*
*
*/
static unsigned int hdmi_data[] = 
{
    0x150001,
    0x16003e,
    0x550020,
    0x1a0004,
    0x1b0000,
    0x1c0000,
    0x1d0000,
    0x1e001d,
    0x1f00b9,
    0x20001d,
    0x2100ad,
    0x220004,
    0x230000,
    0x24001e,
    0x25006c,
    0x260001,
    0x2700f3,
    0x280000,
    0x290000,
    0x2a0004,
    0x2b0000,
    0x2c0008,
    0x2d0021,
    0x2e001b,
    0x2f00f0,
    0x400080,
    0x410010,
    0x480000,
    0x4900a8,
    0x560008,
    0x940080,
    0x960080,
    0x980003,
    0x990002,
    0x9c0030,
    0x9d0061,
    0xa200a4,
    0xa300a4,
    0xaf0014,
    0xba0060,
    0xde0010,
    0xfa007d,
    0x9a00e0,
    0xe000d0,
    0x1800e4,
    0x19008f,

};
/*
*imx385
*/
void hmdi_init(void)
{
 //   int hdmi_config_done = 0;
#ifdef CANAAN_ISP
    //confirm hdmi id, 0x72 or 0x7a!!!???
//    i2c_init(I2C_DEVICE_1,0x72>>1, 7, 100000);
    msleep(10);

    //confirm imx385 id, 0x8c!!!???
    i2c_init(I2C_DEVICE_0,0x1a, 7, 100000);
    msleep(10);

#if 0
    //config hdmi
    printf("config hdmi with i2c\n");
    msleep(100);
    int i=0;
    for(i=0; i< sizeof(hdmi_data)/4; i++)
    {
        unsigned char data[2];
        data[0] = (hdmi_data[i] >> 16) & 0xff;
        data[1] = hdmi_data[i] & 0xff;
#ifdef USE_GPIO_I2C
        i2c_gpio_write_reg(1,0x72 >> 1,data[0],&data[1],1);
#else        
        i2c_send_data(I2C_DEVICE_1, data, 2);
#endif
        msleep(5);
    }
    printf("hdmi config done\n");
#endif   
#else
    Dev_config_apb25MHZ(0x01,0x1a,1);
    Start_Config(0x01);
    while(hdmi_config_done != 0x01)
    {
        msleep(1);
        hdmi_config_done = DevRegRd(HDMI_CONFIG_DONE_OFFSET);
    }
#endif    
    Release_imx385_fpga_reset_n();
    sleep(1);
    return;
}
/*
*os4a10
*/
void hmdi_init_4k(void)
{
#ifdef CANAAN_ISP
#else
    int hdmi_config_done = 0;
    Dev_config_apb25MHZ(0x01,0x36,5);
    Start_Config(0x01);
    while(hdmi_config_done != 0x01)
    {
        msleep(1);
        hdmi_config_done = DevRegRd(HDMI_CONFIG_DONE_OFFSET);
    }
#endif
    return;
}
/*
*tof
*/

void hmdi_init_tof(void)
{
#ifdef CANAAN_ISP
    //confirm hdmi id, 0x72 or 0x7a!!!???
    i2c_init(I2C_DEVICE_1,0x72>>1, 7, 100000);
    msleep(10);

    //confirm opn8008 id, 0x3d!!!???
    i2c_init(I2C_DEVICE_0,0x3d, 7, 100000);
    msleep(10);

    //config hdmi
    printf("config hdmi with i2c\n");
#if 1    
    msleep(100);
    int i=0;
    for(i=0; i< sizeof(hdmi_data)/4; i++)
    {
        unsigned char data[2];
        data[0] = (hdmi_data[i] >> 16) & 0xff;
        data[1] = hdmi_data[i] & 0xff;
#ifdef USE_GPIO_I2C
        i2c_gpio_write_reg(1,0x72 >> 1,data[0],&data[1],1);
#else 
      
        i2c_send_data(I2C_DEVICE_1, data, 2);
#endif
        msleep(5);
    }
#endif    
    printf("hdmi config done\n");
    
        
#else

    int hdmi_config_done = 0;
    Dev_config_apb25MHZ(0x00,0x3D,16);
    DevRegWr(40,0x01);
    //Start_Config(0x01);
    while(hdmi_config_done != 0x01)
    {
        msleep(1);
        hdmi_config_done = DevRegRd(HDMI_CONFIG_DONE_OFFSET);
    }
    

#endif    
    return;
}
/*
*jxf23s & imx385
*/
void init_jxf23_imx385(void)
{
#ifdef CANAAN_ISP
    #ifdef USE_GPIO_I2C
        //
    #else
        //confirm hdmi id, 0x72 or 0x7a!!!???
        i2c_init(I2C_DEVICE_1,0x72>>1, 7, 100000);
        msleep(10);
        //confirm f23s id, 0x8c!!!???
        i2c_init(I2C_DEVICE_0,0x8c>>1, 7, 100000);
        msleep(10);

    #endif    
    
        //config hdmi
        printf("config hdmi with i2c\n");
        msleep(100);
        int i=0;
        for(i=0; i< sizeof(hdmi_data)/4; i++)
        {
            unsigned char data[2];
            data[0] = (hdmi_data[i] >> 16) & 0xff;
            data[1] = hdmi_data[i] & 0xff;
    #ifdef USE_GPIO_I2C
            i2c_gpio_write_reg(1,0x72 >> 1,data[0],&data[1],1);
    #else       
            i2c_send_data(I2C_DEVICE_1, data, 2);
    #endif
            msleep(5);
        }
    //    printf("hdmi config done\n");
#else
    int hdmi_config_done = 0;
    
    Start_Config(0x01);
    hdmi_config_done = 0;
    while(hdmi_config_done != 0x01)
    {
        sleep(1);
        hdmi_config_done = DevRegRd(HDMI_CONFIG_DONE_OFFSET);
    }
//  #if 1
    /*config jxf23s*/
    Dev_config_apb25MHZ(0x00,0x46,3);
#endif
    Release_f23s_fpga_rst_n();
    sleep(1);
    Release_f23s_fpga_pwdn();
    g_use_f23s_imx385 = 0;
    jxf23s_sensor_init();
    jxf23s_sensor_Rd();
    sleep(1);
    printf("config jxf23s done\n");
//  #endif
    
    /*config imx385*/
#ifdef CANAAN_ISP
    //confirm imx385 id, 0x8c!!!???
    i2c_init(I2C_DEVICE_2,0x1a, 7, 100000);

    msleep(10); 
#else
    Dev_config_apb25MHZ(0x01,0x1a,1);
#endif
    g_use_f23s_imx385 = 1;

    Active_imx385_fpga_reset_n();
    sleep(2);
    Release_imx385_fpga_reset_n();
    sleep(2);
    Imx385_init();
    Imx385_Rd_DisableAuto();
    printf("config imx385 done\n");

    return;
}
/*
*jxf23s
*/
void hmdi_init_jxf23s(void)
{
#ifdef CANAAN_ISP
    
#ifdef USE_GPIO_I2C
        //
#else
        //confirm hdmi id, 0x72 or 0x7a!!!???
        i2c_init(I2C_DEVICE_1,0x72>>1, 7, 100000);
        msleep(10);
        //confirm f23s id, 0x8c!!!???
        i2c_init(I2C_DEVICE_0,0x8c>>1, 7, 100000);
        msleep(10);
#endif    
    
        //config hdmi
        printf("config hdmi with i2c\n");
        msleep(100);
        int i=0;
        for(i=0; i< sizeof(hdmi_data)/4; i++)
        {
            unsigned char data[2];
            data[0] = (hdmi_data[i] >> 16) & 0xff;
            data[1] = hdmi_data[i] & 0xff;
#ifdef USE_GPIO_I2C
            i2c_gpio_write_reg(1,0x72 >> 1,data[0],&data[1],1);
#else 
    
           
            i2c_send_data(I2C_DEVICE_1, data, 2);
#endif
            msleep(5);
        }
        printf("hdmi config done\n");
        
#else


    int hdmi_config_done = 0;
    Dev_config_apb25MHZ(0x00,0x46,3);
    Start_Config(0x01);
    while(hdmi_config_done != 0x01)
    {
        msleep(1);
        hdmi_config_done = DevRegRd(HDMI_CONFIG_DONE_OFFSET);
    }
#endif    
    Release_f23s_fpga_rst_n();
    sleep(1);
    Release_f23s_fpga_pwdn();
    sleep(1);
    return;
}
/*
*bt1120
*/
void hmdi_init_bt1120(void)
{
#ifdef CANAAN_ISP
    //confirm cv8788 id, 0x72 or 0x7a!!!???
    i2c_init(I2C_DEVICE_1,0x3d, 7, 100000);
    msleep(10);

    //confirm opn8008 id, 0x3d!!!???
    i2c_init(I2C_DEVICE_0,0x3d, 7, 100000);
    msleep(10);

    printf("hdmi config done\n");
    
        
#else

    int hdmi_config_done = 0;
//    Dev_config_apb25MHZ(0x01,0x3D,17);
    Dev_config_apb25MHZ(0x01,0x1a,1);

    Set_manu(0x01);
    Set_manu(0x00);
    //DevRegWr(40,0x01);
    //Start_Config(0x01);
    //while(hdmi_config_done != 0x01)
    {
    //    msleep(1);
    //    hdmi_config_done = DevRegRd(HDMI_CONFIG_DONE_OFFSET);
    }
    

#endif    
    return;
}
/*
*
*/
void hmdi_init_jxf23s_irs238c(void)
{
#ifdef CANAAN_ISP
    //confirm hdmi id, 0x72 or 0x7a!!!???
    i2c_init(I2C_DEVICE_1,0x72>>1, 7, 100000);
    msleep(10);

    //confirm f23s id, 0x8c!!!???
    i2c_init(I2C_DEVICE_0,0x8c>>1, 7, 100000);
    msleep(10);

    //confirm irs238c id, 0x3d!!!???
    i2c_init(I2C_DEVICE_2,0x3d, 7, 100000);
    msleep(10);
#endif

    //config hdmi
    printf("config hdmi with i2c\n");

    msleep(100);
    int i=0;
    for(i=0; i< sizeof(hdmi_data)/4; i++)
    {
        unsigned char data[2];
        data[0] = (hdmi_data[i] >> 16) & 0xff;
        data[1] = hdmi_data[i] & 0xff;
        i2c_send_data(I2C_DEVICE_1, data, 2);
        msleep(5);
    }

    printf("hmdi_init_jxf23s_irs238c config done\n");


    Release_f23s_fpga_rst_n();
    sleep(1);
    Release_f23s_fpga_pwdn();
    sleep(1);
    return;
}
/*
*
*/
void fpga_system_init(BOOL isJxf23s)
{
#ifndef _SIMU
    SysRstActive();
    if(FALSE == isJxf23s)
    {
        Active_imx385_fpga_reset_n();
    }
    sleep(1);
    SysRstnRelease();
    #if 0
    RegWr32(0xa0000008,0x0);
    printf("0xa0000008:%d \n",RegRd32(0xa0000008));
    RegWr32(0xa000000c,0x0);
    printf("0xa000000c:%d \n",RegRd32(0xa000000c));
    RegWr32(0xa0000180,0x0);
    printf("0xa0000180:%d \n",RegRd32(0xa0000180));
    RegWr32(0xa000018c,0x0);
    printf("0xa000018c:%d \n",RegRd32(0xa000018c));
    #endif
#endif    
    return;
}
