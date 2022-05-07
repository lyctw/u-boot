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
#include "hw_dev/inc/dev_hw.h"
#include "hw_dev/inc/ext_ctl_hw.h"
#include "sensor/sensor.h"

#include "sysctl_clk.h" 

/*
*
*/
void opn8008_init(void)
{

    I2cWr(0x0400,0xCB);
    msleep(1);
    I2cWr(0x0500,0x80);
    msleep(1);
    I2cWr(0x0D00,0x0A);
    msleep(1);
    I2cWr(0x0E00,0x08);
    msleep(1);
    I2cWr(0x0F00,0x04);
    msleep(1);
    I2cWr(0x1000,0x01);
    msleep(1);
    I2cWr(0x1100,0x95);
    msleep(1);
    I2cWr(0x1200,0x11);
    msleep(1);
    I2cWr(0x1300,0x5C);
    msleep(1);
    I2cWr(0x1600,0x0E);
    msleep(1);
    I2cWr(0x1700,0x71);
    msleep(1);
    I2cWr(0x1E00,0x0E);
    msleep(1);
    I2cWr(0x1F00,0x72);
    msleep(1);
    I2cWr(0x2000,0x11);
    msleep(1);
    I2cWr(0x2100,0x5A);
    msleep(1);
    I2cWr(0x2200,0x0E);
    msleep(1);
    I2cWr(0x2300,0x70);
    msleep(1);
    I2cWr(0x2400,0x11);
    msleep(1);
    I2cWr(0x2500,0x5C);
    msleep(1);
    I2cWr(0x2800,0x00);
    msleep(1);
    I2cWr(0x2900,0x01);
    msleep(1);
    I2cWr(0x2A00,0x00);
    msleep(1);
    I2cWr(0x2B00,0x6F);
    msleep(1);
    I2cWr(0x2D00,0x00);
    msleep(1);
    I2cWr(0x2E00,0x3D);
    msleep(1);
    I2cWr(0x2F00,0x8D);
    msleep(1);
    I2cWr(0x3000,0x00);
    msleep(1);
    I2cWr(0x3100,0x01);
    msleep(1);
    I2cWr(0x3200,0x00);
    msleep(1);
    I2cWr(0x3300,0x27);
    msleep(1);
    I2cWr(0x3400,0x00);
    msleep(1);
    I2cWr(0x3500,0x01);
    msleep(1);
    I2cWr(0x3600,0x00);
    msleep(1);
    I2cWr(0x3700,0x0D);
    msleep(1);
    I2cWr(0x3800,0x00);
    msleep(1);
    I2cWr(0x3900,0x0E);
    msleep(1);
    I2cWr(0x3A00,0x00);
    msleep(1);
    I2cWr(0x3B00,0x0D);
    msleep(1);
    I2cWr(0x3C00,0x00);
    msleep(1);
    I2cWr(0x3D00,0x1B);
    msleep(1);
    I2cWr(0x3E00,0x00);
    msleep(1);
    I2cWr(0x3F00,0x0D);
    msleep(1);
    I2cWr(0x4100,0x0C);
    msleep(1);
    I2cWr(0x4300,0x1A);
    msleep(1);
    I2cWr(0x4400,0x80);
    msleep(1);
    I2cWr(0x4600,0x44);
    msleep(1);
    I2cWr(0x6100,0x1C);
    msleep(1);
    I2cWr(0xA500,0x80);
    msleep(1);
    I2cWr(0xA800,0x3c);
    msleep(1);
    I2cWr(0xB800,0x0c);
    msleep(1);
    I2cWr(0xA700,0x95);
    msleep(1);
    I2cWr(0xB000,0x88);
    msleep(1);
    I2cWr(0xB100,0x60);
    msleep(1);
    I2cWr(0x0500,0xFF);
    msleep(1);
    I2cWr(0x0600,0x7f);
    msleep(1);
}
/*
*
*/
void opn8008_rd(void)
{
    I2cRd(0x0400);
    msleep(1);
    I2cRd(0x0500);
    I2cRd(0x0D00);
    msleep(1);
    I2cRd(0x0E00);
    msleep(1);
    I2cRd(0x0F00);
    msleep(1);
    I2cRd(0x1000);
    msleep(1);
    I2cRd(0x1100);
    msleep(1);
    I2cRd(0x1200);
    msleep(1);
    I2cRd(0x1300);
    msleep(1);
    I2cRd(0x1600);
    msleep(1);
    I2cRd(0x1700);
    msleep(1);
    I2cRd(0x1E00);
    msleep(1);
    I2cRd(0x1F00);
    msleep(1);
    I2cRd(0x2000);
    msleep(1);
    I2cRd(0x2100);
    msleep(1);
    I2cRd(0x2200);
    msleep(1);
    I2cRd(0x2300);
    msleep(1);
    I2cRd(0x2400);
    msleep(1);
    I2cRd(0x2500);
    msleep(1);
    I2cRd(0x2800);
    msleep(1);
    I2cRd(0x2900);
    msleep(1);
    I2cRd(0x2A00);
    msleep(1);
    I2cRd(0x2B00);
    msleep(1);
    I2cRd(0x2D00);
    msleep(1);
    I2cRd(0x2E00);
    msleep(1);
    I2cRd(0x2F00);
    msleep(1);
    I2cRd(0x3000);
    msleep(1);
    I2cRd(0x3100);
    msleep(1);
    I2cRd(0x3200);
    msleep(1);
    I2cRd(0x3300);
    msleep(1);
    I2cRd(0x3400);
    msleep(1);
    I2cRd(0x3500);
    msleep(1);
    I2cRd(0x3600);
    msleep(1);
    I2cRd(0x3700);
    msleep(1);
    I2cRd(0x3800);
    msleep(1);
    I2cRd(0x3900);
    msleep(1);
    I2cRd(0x3A00);
    msleep(1);
    I2cRd(0x3B00);
    msleep(1);
    I2cRd(0x3C00);
    msleep(1);
    I2cRd(0x3D00);
    msleep(1);
    I2cRd(0x3E00);
    msleep(1);
    I2cRd(0x3F00);
    msleep(1);
    I2cRd(0x4100);
    msleep(1);
    I2cRd(0x4300);
    msleep(1);
    I2cRd(0x4400);
    msleep(1);
    I2cRd(0x4600);
    msleep(1);
    I2cRd(0x6100);
    msleep(1);
    I2cRd(0xA200);
    msleep(1);
    I2cRd(0xA500);
    msleep(1);
    I2cRd(0xA600);
    msleep(1);
    I2cRd(0xA800);
    msleep(1);
    I2cRd(0xB800);
    msleep(1);
    I2cRd(0xA700);
    msleep(1);
    I2cRd(0xB000);
    msleep(1);
    I2cRd(0xB100);
    msleep(1);
}

void opn8008_tof_sensor_config(void)
{
    Release_opn8008_rstn();
    sleep(1);
    Set_manu(0x01);
    Set_manu(0x00);
    opn8008_init();
    opn8008_rd();
    return;
}


