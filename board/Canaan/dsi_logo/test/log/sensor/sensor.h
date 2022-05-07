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
#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <video/isp_com.h>

//imx385
void Imx385_init(void);
void Imx385_Rd(void);
void Imx385_Rd_DisableAuto(void);
void imx385_wdr2f_12p5fps_12bit_2lane(void);
void imx385_wdr3f_6p25fps_12bit_2lane(void);
void imx_385_2k_normal_vi_isp_config(void);
void imx_385_2k_normal_sensor(BOOL enInt);
//irs238c
void irs238c_init(void);
//jfx23s
void jxf23s_sensor_init_15fps(void);
void jxf23s_sensor_init(void);
void jxf23s_sensor_Rd(void);
void irs238c_tof_sensor_config(void);
//opn8008
void opn8008_init(void);
void opn8008_rd(void);
void opn8008_tof_sensor_config(void);
//os8a10
void os8a10_init(void);
void os8a10_4k_sensor_config(void);
#endif /*_SENSOR_H_*/
