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
// #include <common.h>
#include "ws2812.h"
#include "controler/sysctl_clk.h"
#include "controler/sysctl_rst.h"
#include "controler/muxpin.h"
#include "controler/gpio.h"
#include "cpu/cache.h"
#include "controler/spi.h"


ws2812_info *ws2812_get_buf(uint32_t num)
{
    ws2812_info *ws = malloc(sizeof(ws2812_info));

    if (ws == NULL)
        return NULL;
    ws->ws_num = num;
    ws->ws_buf = malloc(num * sizeof(ws2812_data));
    if (ws->ws_buf == NULL) {
        free(ws);
        return NULL;
    }
    memset(ws->ws_buf, 0, num * sizeof(ws2812_data));
    return ws;
}

bool ws2812_set_data(ws2812_info *ws, uint32_t num, uint32_t color)
{
    if (ws == NULL)
        return false;

    if (ws->ws_buf == NULL)
        return false;
    if (num >= ws->ws_num)
        return false;
    printf("led color is 0x%08x\n", color);
    (ws->ws_buf + num)->red = (uint8_t)(color >> 16);
    (ws->ws_buf + num)->green = (uint8_t)(color >> 8);
    (ws->ws_buf + num)->blue = (uint8_t)color;

    return true;
}

void ws2812_init_spi(uint8_t pin)
{
    muxpin_set_function(pin, FUNC_SPI1_D0);

    sysctl_clk_set_leaf_en(SYSCTL_CLK_SPI1_SCLK, false);
    usleep(10);
    sysctl_clk_set_leaf_parent(SYSCTL_CLK_SPI1_SCLK,SYSCTL_CLK_ROOT_PLL0);
    usleep(10);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_SPI1_SCLK, true);
    usleep(10);
    sysctl_clk_set_leaf_div(SYSCTL_CLK_SPI1_SCLK, 1, 2);  //1G/16=62.5MHz
    usleep(10);
    sysctl_reset(SYSCTL_RESET_PERI_DMA);
    sysctl_reset(SYSCTL_RESET_SPI1);

    spi_init(1, 18);
}

bool ws2812_send_data_spi(ws2812_info *ws)
{
    uint32_t resbit;

    if (ws == NULL)
        return false;

    if (ws->ws_buf == NULL)
        return false;

    size_t ws_cnt = ws->ws_num;
    uint32_t *ws_data = (uint32_t *)ws->ws_buf;

    uint32_t freq_spi_src = sysctl_clk_get_leaf_freq(SYSCTL_CLK_SPI1_SCLK);

    uint32_t freq_spi = freq_spi_src / 18;//31250000

    double clk_time = 1e9 / freq_spi;   // ns per clk

    resbit = (500000 / clk_time);   // > 300us 312

    uint32_t spi_send_cnt = ws_cnt * 24 ; //加最后的reset
    uint32_t reset_cnt = resbit / 32;      //先reset
    uint32_t len = (reset_cnt + spi_send_cnt + reset_cnt) * 4;
    uint32_t *tmp_spi_data = malloc(len);

    if (tmp_spi_data == NULL)
        return false;

    memset(tmp_spi_data, 0, len);
    uint32_t *spi_data = tmp_spi_data;

    spi_data += reset_cnt;

    uint32_t highvalue  =   0xFFFFFC00;
    uint32_t lowvalue   =   0xFF800000;

    for (int i = 0; i < ws_cnt; i++) {

        for (uint32_t mask = 0x800000; mask > 0; mask >>= 1) {

            if (ws_data[i] & mask) {
                *(spi_data) = highvalue;
            } else{
                *(spi_data) = lowvalue;
            }
            spi_data++;
        }
    }
    cache_wb_all();
    spi_send_data_dma(1, tmp_spi_data, len);

    free(tmp_spi_data);
    return true;
}
