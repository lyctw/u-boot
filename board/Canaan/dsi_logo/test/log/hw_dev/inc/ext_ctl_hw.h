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
#ifndef _EXT_CTL_HW_H_
#define _EXT_CTL_HW_H_

void RegWr32(int addr,int data);
int  RegRd32( int addr );

void ExtCtlRegWr(int addr,int data);
int ExtCtlRegRd(int addr);

void AxibusRstnActive();
void AxibusRstnRelease();

void IspRstnActive();
void IspRstnRelease();

void VideoInRstnActive();
void VideoInRstnRelease();
void SensorRstnActive();
void SensorRstnRelease();

void VideoOutRstnActive();
void VideoOutRstnRelease();
int  SysIsReady();

void Release_imx385_fpga_reset_n();
void Active_imx385_fpga_reset_n();

void Release_f23s_fpga_rst_n();
void Release_f23s_fpga_pwdn();

void  SysRstnRelease();
void  SysRstActive();

void Release_os8a10_rstn();
void Active_os8a10_rstn();
void Release_os8a10_pwdn();
void Active_os8a10_pwdn();

void aml550_1v8_power_en();
void aml550_2v8_power_en();
void Release_aml550_fpga_reset();
void Active_aml550_fpga_reset();
void aml550_22v_power_en();
void aml550_22v_power_off();
void aml550_power_on_seq();

void dsi_power_en();
void dsi_power_dis();
void csi_power_en();
void csi_power_dis();

void Active_opn8008_rstn();
void Release_opn8008_rstn();

void Release_Cv8878_rstn();
void Active_Cv8878_rstn();
#endif /* _EXT_CTL_HW_H_ */
