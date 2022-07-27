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
//#include <cpu/k510.h>
//#include <cpu/cache.h>
#include <cpu/interrupt.h>
#include <cpu/sleep.h>
#include <controler/i2c.h>
#include <controler/muxpin.h>
#include <controler/gpio.h>
#include <video/mipi/csi/mipi_csi.h>
#include <video/mipi/dsi/cnds_dsi_define.h>
#include <video/mipi/dsi/cnds_dsi_hw.h>
#include <video/mipi/dphy/mipi_corner.h>
#include <video/mipi/dphy/mipi_rxdphy.h>
#include "pcal6416.h"
#include  "controler/sysctl_clk.h"
#include  "controler/sysctl_boot.h"

#define MIPI_SWITCH_OE_PIN  32
#define MIPI_SWITCH_SEL_PIN 34
#define LCD_BACKLIGHT_PIN   79
#define LCD_RESET_PIN       78
#define HDMI_RESET_PIN      97

#define MIPI_SWITCH_OE_IO   22
#define MIPI_SWITCH_SEL_IO  21
#define LCD_BACKLIGHT_IO    20
#define LCD_RESET_IO        19
#define HDMI_RESET_IO       15

// screen reset , 1 high , 0 : low
void display_gpio_reset(void)
{

#ifdef CONFIG_TARGET_K510_CRB_LP3_V0_1
    // K510_EVB_LP3_V1_1 
    pcal6416_mipi_dsi_reset(1);
    msleep(100);
    pcal6416_mipi_dsi_reset(0);
    msleep(100);
    pcal6416_mipi_dsi_reset(1);
#endif

#ifdef CONFIG_TARGET_K510_CRB_LP3_V1_2
    gpio_set_pin(LCD_RESET_IO, GPIO_PV_HIGH);
    msleep(200);
    gpio_set_pin(LCD_RESET_IO, GPIO_PV_LOW);
    msleep(200);
    gpio_set_pin(LCD_RESET_IO, GPIO_PV_HIGH);
    msleep(200);
#endif
}

// screen open 22v backlight
void display_gpio_poweron(void)
{

#ifdef CONFIG_TARGET_K510_CRB_LP3_V0_1
    // K510_EVB_LP3_V1_1  
    pcal6416_gpio_dsi_en(1);
#endif

#ifdef CONFIG_TARGET_K510_CRB_LP3_V1_2
    gpio_set_pin(LCD_BACKLIGHT_IO, GPIO_PV_HIGH);
#endif
}

void lt9611_reset(void)
{
    gpio_set_pin(HDMI_RESET_IO, GPIO_PV_LOW);
    msleep(100);
    gpio_set_pin(HDMI_RESET_IO, GPIO_PV_HIGH);
}

// gpio init 
int mipi_select_value = 0;
void display_switch_lcd_gpio(void)
{
    gpio_set_drive_mode(MIPI_SWITCH_SEL_IO, GPIO_DM_OUTPUT);
    gpio_set_pin(MIPI_SWITCH_SEL_IO, mipi_select_value);
}

void display_switch_hdmi_gpio(void)
{
    gpio_set_drive_mode(MIPI_SWITCH_SEL_IO, GPIO_DM_OUTPUT);
    gpio_set_pin(MIPI_SWITCH_SEL_IO, !mipi_select_value);
}

void display_gpio_init(void)
{

#ifdef CONFIG_TARGET_K510_CRB_LP3_V0_1
    // K510_EVB_LP3_V1_1  gpio init
    pcal6416_init(0);
    //open bacnlight
    display_gpio_poweron();
    msleep(100);
    // rst gpio 
    display_gpio_reset();
#endif

#ifdef CONFIG_TARGET_K510_CRB_LP3_V1_2

    muxpin_set_function(MIPI_SWITCH_OE_PIN, FUNC_GPIO0 + MIPI_SWITCH_OE_IO);
    gpio_set_drive_mode(MIPI_SWITCH_OE_IO, GPIO_DM_OUTPUT);
    gpio_set_pin(MIPI_SWITCH_OE_IO,  GPIO_PV_LOW);

    muxpin_set_function(HDMI_RESET_PIN, FUNC_GPIO0 + HDMI_RESET_IO);
    gpio_set_drive_mode(HDMI_RESET_IO, GPIO_DM_OUTPUT);
    gpio_set_pin(HDMI_RESET_IO, GPIO_PV_HIGH);

    muxpin_set_function(MIPI_SWITCH_SEL_PIN, FUNC_GPIO0 + MIPI_SWITCH_OE_IO);
    gpio_set_drive_mode(MIPI_SWITCH_OE_IO, GPIO_DM_INPUT);
    mipi_select_value = gpio_get_pin(MIPI_SWITCH_OE_IO);

    muxpin_set_function(LCD_RESET_PIN, FUNC_GPIO0 + LCD_RESET_IO);
    gpio_set_drive_mode(LCD_RESET_IO, GPIO_DM_OUTPUT);

    muxpin_set_function(LCD_BACKLIGHT_PIN, FUNC_GPIO0 + LCD_BACKLIGHT_IO);
    gpio_set_drive_mode(LCD_BACKLIGHT_IO, GPIO_DM_OUTPUT);

    lt9611_reset();

    display_gpio_reset();

    display_gpio_poweron();

#endif

}




