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
#include <common.h>
#include <cpu/sleep.h>
#include <controler/i2c.h>
#include <controler/muxpin.h>
#include <controler/gpio.h>
#include  "controler/sysctl_clk.h"
#include  "controler/sysctl_boot.h"

#define LT9611_ADDR (0x76>>1)

int lt9611_i2c_init(void)
{
    muxpin_set_function(117, FUNC_I2C3_SCLK);
    muxpin_set_function(116, FUNC_I2C3_SDA);
    i2c_init(I2C_DEVICE_3, LT9611_ADDR, 7, 100000);
}

int lt9611_write_byte(uint8_t reg_addr, uint8_t reg_val)
{
    uint8_t buf[2] = {reg_addr, reg_val};
    i2c_send_data(I2C_DEVICE_3, buf, 2);

    return 0;
}

uint8_t lt9611_read_byte(uint8_t reg_addr)
{
    uint8_t reg_val = 0x00;

    i2c_recv_data(I2C_DEVICE_3, &reg_addr, 1, &reg_val, 1);

    return reg_val;
}

uint8_t lt9611_read_id(void)
{
    lt9611_write_byte(0xff, 0x80);
    lt9611_write_byte(0xee, 0x01);
    printf("LT9611 ID %02x %02x\n", lt9611_read_byte(0x00), lt9611_read_byte(0x01));
}

int lt9611_get_hpd_state(void)
{
    uint8_t reg_val = 0;
    int hpd_state = 0;

    lt9611_i2c_init();
    lt9611_read_id();
    lt9611_write_byte(0xff, 0x82);
    reg_val = lt9611_read_byte(0x5e);
    hpd_state = reg_val & 0x04;
    return hpd_state;
}

