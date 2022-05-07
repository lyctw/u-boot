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
/*
*
*/
void ADV7511_init(void)
{
    Set_manu(0x01);
    Set_manu(0x00);
    I2cWr(0x1500,0x01);
    msleep(1);
    I2cRd(0x1500);
    msleep(1);
    I2cWr(0x1600,0x3e);
    msleep(1);
    I2cRd(0x1600);
    msleep(1);
    I2cWr(0x5500,0x20);
    msleep(1);
    I2cRd(0x5500);
    msleep(1);
    I2cWr(0x1a00,0x04);
    msleep(1);
    //I2cRd(0x1a00);
    msleep(1);
    I2cWr(0x1b00,0x00);
    msleep(1);
    I2cWr(0x1c00,0x00);
    msleep(1);
    I2cWr(0x1d00,0x00);
    msleep(1);
    I2cWr(0x1e00,0x1d);
    msleep(1);
    I2cWr(0x1f00,0xb9);
    msleep(1);
    I2cWr(0x2000,0x1d);
    msleep(1);
    I2cWr(0x2100,0xad);
    msleep(1);
    I2cWr(0x2200,0x04);
    msleep(1);
    I2cWr(0x2300,0x00);
    msleep(1);
    I2cWr(0x2400,0x1e);
    msleep(1);
    I2cWr(0x2500,0x6c);
    msleep(1);
    I2cWr(0x2600,0x01);
    msleep(1);
    I2cWr(0x2700,0xf3);
    msleep(1);
    I2cWr(0x2800,0x00);
    msleep(1);
    I2cWr(0x2900,0x00);
    msleep(1);
    I2cWr(0x2a00,0x04);
    msleep(1);
    I2cWr(0x2b00,0x00);
    msleep(1);
    I2cWr(0x2c00,0x08);
    msleep(1);
    I2cWr(0x2d00,0x21);
    msleep(1);
    I2cWr(0x2e00,0x1b);
    msleep(1);
    I2cWr(0x2f00,0xf0);
    msleep(1);
    I2cWr(0x4000,0x80);
    msleep(1);
    I2cWr(0x4100,0x10);
    msleep(1);
    I2cWr(0x4800,0x00);
    msleep(1);
    I2cWr(0x4900,0xa8);
    msleep(1);
    I2cWr(0x5600,0x08);
    msleep(1);
    I2cWr(0x9400,0x80);
    msleep(1);
    I2cWr(0x9600,0x80);
    msleep(1);
    I2cWr(0x9800,0x03);
    msleep(1);
    I2cWr(0x9900,0x02);
    msleep(1);
    I2cWr(0x9c00,0x30);
    msleep(1);
    I2cWr(0x9d00,0x61);
    msleep(1);
    I2cWr(0xa200,0xa4);
    msleep(1);
    I2cWr(0xa300,0xa4);
    msleep(1);
    I2cWr(0xaf00,0x14);
    msleep(1);
    I2cWr(0xba00,0x60);
    msleep(1);
    I2cWr(0xde00,0x10);
    msleep(1);
    I2cWr(0xfa00,0x7d);
    msleep(1);
    I2cWr(0x9a00,0xe0);
    msleep(1);
    I2cWr(0xe000,0xd0);
    msleep(1);
    I2cWr(0x1800,0xe4);
    msleep(1);
    I2cWr(0x1900,0x8f);
    msleep(1);
    I2cRd(0x1900);
    msleep(3);
    Set_auto(0x01);
    Set_auto(0x00);
    msleep(3);
}