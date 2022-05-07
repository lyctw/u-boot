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
// #include <k510.h>
#include "common.h"
#include "ddrc.h"
// #include <cache.h>

uint8_t  cur_read_gate_delay_0;
uint8_t  cur_read_gate_delay_1;
uint8_t  cur_read_gate_delay_2;
uint8_t  cur_read_gate_delay_3;

uint8_t  cur_f0_read_dqs_sadj_0;
uint8_t  cur_f0_read_dqs_sadj_1;
uint8_t  cur_f0_read_dqs_sadj_2;
uint8_t  cur_f0_read_dqs_sadj_3;

uint8_t  cur_f0_write_dqs_sadj_0;
uint8_t  cur_f0_write_dqs_sadj_1;
uint8_t  cur_f0_write_dqs_sadj_2;
uint8_t  cur_f0_write_dqs_sadj_3;

uint8_t  cur_f0_read_dqs_b_sadj_0;
uint8_t  cur_f0_read_dqs_b_sadj_1;
uint8_t  cur_f0_read_dqs_b_sadj_2;
uint8_t  cur_f0_read_dqs_b_sadj_3;

uint8_t  cur_f0_write_dq_ext_sadj_0;
uint8_t  cur_f0_write_dq_ext_sadj_1;
uint8_t  cur_f0_write_dq_ext_sadj_2;
uint8_t  cur_f0_write_dq_ext_sadj_3;

uint8_t  cur_f0_write_dq_sadj_0;
uint8_t  cur_f0_write_dq_sadj_1;
uint8_t  cur_f0_write_dq_sadj_2;
uint8_t  cur_f0_write_dq_sadj_3;

uint8_t  cur_f0_write_level_sadj_0;
uint8_t  cur_f0_write_level_sadj_1;
uint8_t  cur_f0_write_level_sadj_2;
uint8_t  cur_f0_write_level_sadj_3;

uint8_t  cur_f0_ca_sadj_0;
uint8_t  cur_f0_ca_sadj_1;
uint8_t  cur_f0_ca_sadj_2;

uint8_t  cur_f0_ca_write_level_sadj_0;
uint8_t  cur_f0_ca_write_level_sadj_1;
uint8_t  cur_f0_ca_write_level_sadj_2;

uint8_t  cur_f0_ca_ck_sadj_0;
uint8_t  cur_f0_ca_ck_sadj_1;
uint8_t  cur_f0_ca_ck_sadj_2;


uint8_t  cur_f1_read_dqs_sadj_0;
uint8_t  cur_f1_read_dqs_sadj_1;
uint8_t  cur_f1_read_dqs_sadj_2;
uint8_t  cur_f1_read_dqs_sadj_3;

uint8_t  cur_f1_write_dqs_sadj_0;
uint8_t  cur_f1_write_dqs_sadj_1;
uint8_t  cur_f1_write_dqs_sadj_2;
uint8_t  cur_f1_write_dqs_sadj_3;

uint8_t  cur_f1_read_dqs_b_sadj_0;
uint8_t  cur_f1_read_dqs_b_sadj_1;
uint8_t  cur_f1_read_dqs_b_sadj_2;
uint8_t  cur_f1_read_dqs_b_sadj_3;

uint8_t  cur_f1_write_dq_ext_sadj_0;
uint8_t  cur_f1_write_dq_ext_sadj_1;
uint8_t  cur_f1_write_dq_ext_sadj_2;
uint8_t  cur_f1_write_dq_ext_sadj_3;

uint8_t  cur_f1_write_dq_sadj_0;
uint8_t  cur_f1_write_dq_sadj_1;
uint8_t  cur_f1_write_dq_sadj_2;
uint8_t  cur_f1_write_dq_sadj_3;

uint8_t  cur_f1_write_level_sadj_0;
uint8_t  cur_f1_write_level_sadj_1;
uint8_t  cur_f1_write_level_sadj_2;
uint8_t  cur_f1_write_level_sadj_3;

uint8_t  cur_f1_ca_sadj_0;
uint8_t  cur_f1_ca_sadj_1;
uint8_t  cur_f1_ca_sadj_2;

uint8_t  cur_f1_ca_write_level_sadj_0;
uint8_t  cur_f1_ca_write_level_sadj_1;
uint8_t  cur_f1_ca_write_level_sadj_2;

uint8_t  cur_f1_ca_ck_sadj_0;
uint8_t  cur_f1_ca_ck_sadj_1;
uint8_t  cur_f1_ca_ck_sadj_2;

uint8_t  cur_rfe_sadj_0;
uint8_t  cur_rfe_sadj_1;
uint8_t  cur_rfe_sadj_2;
uint8_t  cur_rfe_sadj_3;

uint8_t        cur_dll_frequency_bank_select;

uint8_t  cur_ds3_dqs_cur_sadj;
uint8_t  cur_ds2_dqs_cur_sadj;
uint8_t  cur_ds1_dqs_cur_sadj;
uint8_t  cur_ds0_dqs_cur_sadj;

// pre_data

uint8_t  pre_read_gate_delay_0;
uint8_t  pre_read_gate_delay_1;
uint8_t  pre_read_gate_delay_2;
uint8_t  pre_read_gate_delay_3;

uint8_t  pre_f0_read_dqs_sadj_0;
uint8_t  pre_f0_read_dqs_sadj_1;
uint8_t  pre_f0_read_dqs_sadj_2;
uint8_t  pre_f0_read_dqs_sadj_3;

uint8_t  pre_f0_write_dqs_sadj_0;
uint8_t  pre_f0_write_dqs_sadj_1;
uint8_t  pre_f0_write_dqs_sadj_2;
uint8_t  pre_f0_write_dqs_sadj_3;

uint8_t  pre_f0_read_dqs_b_sadj_0;
uint8_t  pre_f0_read_dqs_b_sadj_1;
uint8_t  pre_f0_read_dqs_b_sadj_2;
uint8_t  pre_f0_read_dqs_b_sadj_3;

uint8_t  pre_f0_write_dq_ext_sadj_0;
uint8_t  pre_f0_write_dq_ext_sadj_1;
uint8_t  pre_f0_write_dq_ext_sadj_2;
uint8_t  pre_f0_write_dq_ext_sadj_3;

uint8_t  pre_f0_write_dq_sadj_0;
uint8_t  pre_f0_write_dq_sadj_1;
uint8_t  pre_f0_write_dq_sadj_2;
uint8_t  pre_f0_write_dq_sadj_3;

uint8_t  pre_f0_write_level_sadj_0;
uint8_t  pre_f0_write_level_sadj_1;
uint8_t  pre_f0_write_level_sadj_2;
uint8_t  pre_f0_write_level_sadj_3;

uint8_t  pre_f0_ca_sadj_0;
uint8_t  pre_f0_ca_sadj_1;
uint8_t  pre_f0_ca_sadj_2;

uint8_t  pre_f0_ca_write_level_sadj_0;
uint8_t  pre_f0_ca_write_level_sadj_1;
uint8_t  pre_f0_ca_write_level_sadj_2;

uint8_t  pre_f0_ca_ck_sadj_0;
uint8_t  pre_f0_ca_ck_sadj_1;
uint8_t  pre_f0_ca_ck_sadj_2;


uint8_t  pre_f1_read_dqs_sadj_0;
uint8_t  pre_f1_read_dqs_sadj_1;
uint8_t  pre_f1_read_dqs_sadj_2;
uint8_t  pre_f1_read_dqs_sadj_3;

uint8_t  pre_f1_write_dqs_sadj_0;
uint8_t  pre_f1_write_dqs_sadj_1;
uint8_t  pre_f1_write_dqs_sadj_2;
uint8_t  pre_f1_write_dqs_sadj_3;

uint8_t  pre_f1_read_dqs_b_sadj_0;
uint8_t  pre_f1_read_dqs_b_sadj_1;
uint8_t  pre_f1_read_dqs_b_sadj_2;
uint8_t  pre_f1_read_dqs_b_sadj_3;

uint8_t  pre_f1_write_dq_ext_sadj_0;
uint8_t  pre_f1_write_dq_ext_sadj_1;
uint8_t  pre_f1_write_dq_ext_sadj_2;
uint8_t  pre_f1_write_dq_ext_sadj_3;

uint8_t  pre_f1_write_dq_sadj_0;
uint8_t  pre_f1_write_dq_sadj_1;
uint8_t  pre_f1_write_dq_sadj_2;
uint8_t  pre_f1_write_dq_sadj_3;

uint8_t  pre_f1_write_level_sadj_0;
uint8_t  pre_f1_write_level_sadj_1;
uint8_t  pre_f1_write_level_sadj_2;
uint8_t  pre_f1_write_level_sadj_3;

uint8_t  pre_f1_ca_sadj_0;
uint8_t  pre_f1_ca_sadj_1;
uint8_t  pre_f1_ca_sadj_2;

uint8_t  pre_f1_ca_write_level_sadj_0;
uint8_t  pre_f1_ca_write_level_sadj_1;
uint8_t  pre_f1_ca_write_level_sadj_2;

uint8_t  pre_f1_ca_ck_sadj_0;
uint8_t  pre_f1_ca_ck_sadj_1;
uint8_t  pre_f1_ca_ck_sadj_2;

uint8_t  pre_rfe_sadj_0;
uint8_t  pre_rfe_sadj_1;
uint8_t  pre_rfe_sadj_2;
uint8_t  pre_rfe_sadj_3;

uint8_t        pre_dll_frequency_bank_select;

uint8_t  pre_ds3_dqs_cur_sadj;
uint8_t  pre_ds2_dqs_cur_sadj;
uint8_t  pre_ds1_dqs_cur_sadj;
uint8_t  pre_ds0_dqs_cur_sadj;


// init_data

uint8_t  init_read_gate_delay_0;
uint8_t  init_read_gate_delay_1;
uint8_t  init_read_gate_delay_2;
uint8_t  init_read_gate_delay_3;

uint8_t  init_f0_read_dqs_sadj_0;
uint8_t  init_f0_read_dqs_sadj_1;
uint8_t  init_f0_read_dqs_sadj_2;
uint8_t  init_f0_read_dqs_sadj_3;

uint8_t  init_f0_write_dqs_sadj_0;
uint8_t  init_f0_write_dqs_sadj_1;
uint8_t  init_f0_write_dqs_sadj_2;
uint8_t  init_f0_write_dqs_sadj_3;

uint8_t  init_f0_read_dqs_b_sadj_0;
uint8_t  init_f0_read_dqs_b_sadj_1;
uint8_t  init_f0_read_dqs_b_sadj_2;
uint8_t  init_f0_read_dqs_b_sadj_3;

uint8_t  init_f0_write_dq_ext_sadj_0;
uint8_t  init_f0_write_dq_ext_sadj_1;
uint8_t  init_f0_write_dq_ext_sadj_2;
uint8_t  init_f0_write_dq_ext_sadj_3;

uint8_t  init_f0_write_dq_sadj_0;
uint8_t  init_f0_write_dq_sadj_1;
uint8_t  init_f0_write_dq_sadj_2;
uint8_t  init_f0_write_dq_sadj_3;

uint8_t  init_f0_write_level_sadj_0;
uint8_t  init_f0_write_level_sadj_1;
uint8_t  init_f0_write_level_sadj_2;
uint8_t  init_f0_write_level_sadj_3;

uint8_t  init_f0_ca_sadj_0;
uint8_t  init_f0_ca_sadj_1;
uint8_t  init_f0_ca_sadj_2;

uint8_t  init_f0_ca_write_level_sadj_0;
uint8_t  init_f0_ca_write_level_sadj_1;
uint8_t  init_f0_ca_write_level_sadj_2;

uint8_t  init_f0_ca_ck_sadj_0;
uint8_t  init_f0_ca_ck_sadj_1;
uint8_t  init_f0_ca_ck_sadj_2;


uint8_t  init_f1_read_dqs_sadj_0;
uint8_t  init_f1_read_dqs_sadj_1;
uint8_t  init_f1_read_dqs_sadj_2;
uint8_t  init_f1_read_dqs_sadj_3;

uint8_t  init_f1_write_dqs_sadj_0;
uint8_t  init_f1_write_dqs_sadj_1;
uint8_t  init_f1_write_dqs_sadj_2;
uint8_t  init_f1_write_dqs_sadj_3;

uint8_t  init_f1_read_dqs_b_sadj_0;
uint8_t  init_f1_read_dqs_b_sadj_1;
uint8_t  init_f1_read_dqs_b_sadj_2;
uint8_t  init_f1_read_dqs_b_sadj_3;

uint8_t  init_f1_write_dq_ext_sadj_0;
uint8_t  init_f1_write_dq_ext_sadj_1;
uint8_t  init_f1_write_dq_ext_sadj_2;
uint8_t  init_f1_write_dq_ext_sadj_3;

uint8_t  init_f1_write_dq_sadj_0;
uint8_t  init_f1_write_dq_sadj_1;
uint8_t  init_f1_write_dq_sadj_2;
uint8_t  init_f1_write_dq_sadj_3;

uint8_t  init_f1_write_level_sadj_0;
uint8_t  init_f1_write_level_sadj_1;
uint8_t  init_f1_write_level_sadj_2;
uint8_t  init_f1_write_level_sadj_3;

uint8_t  init_f1_ca_sadj_0;
uint8_t  init_f1_ca_sadj_1;
uint8_t  init_f1_ca_sadj_2;

uint8_t  init_f1_ca_write_level_sadj_0;
uint8_t  init_f1_ca_write_level_sadj_1;
uint8_t  init_f1_ca_write_level_sadj_2;

uint8_t  init_f1_ca_ck_sadj_0;
uint8_t  init_f1_ca_ck_sadj_1;
uint8_t  init_f1_ca_ck_sadj_2;

uint8_t  init_rfe_sadj_0;
uint8_t  init_rfe_sadj_1;
uint8_t  init_rfe_sadj_2;
uint8_t  init_rfe_sadj_3;

uint8_t        init_dll_frequency_bank_select;

uint8_t  init_ds3_dqs_cur_sadj;
uint8_t  init_ds2_dqs_cur_sadj;
uint8_t  init_ds1_dqs_cur_sadj;
uint8_t  init_ds0_dqs_cur_sadj;


void initialize_init_data()
{
    init_read_gate_delay_0 = 0xff;
    init_read_gate_delay_1 = 0xff;
    init_read_gate_delay_2 = 0xff;
    init_read_gate_delay_3 = 0xff;

    init_f0_read_dqs_sadj_0 = 0xff;
    init_f0_read_dqs_sadj_1 = 0xff;
    init_f0_read_dqs_sadj_2 = 0xff;
    init_f0_read_dqs_sadj_3 = 0xff;

    init_f0_write_dqs_sadj_0 = 0xff;
    init_f0_write_dqs_sadj_1 = 0xff;
    init_f0_write_dqs_sadj_2 = 0xff;
    init_f0_write_dqs_sadj_3 = 0xff;

    init_f0_read_dqs_b_sadj_0 = 0xff;
    init_f0_read_dqs_b_sadj_1 = 0xff;
    init_f0_read_dqs_b_sadj_2 = 0xff;
    init_f0_read_dqs_b_sadj_3 = 0xff;

    init_f0_write_dq_ext_sadj_0 = 0x0;
    init_f0_write_dq_ext_sadj_1 = 0x0;
    init_f0_write_dq_ext_sadj_2 = 0x0;
    init_f0_write_dq_ext_sadj_3 = 0x0;

    init_f0_write_dq_sadj_0 = 0xff;
    init_f0_write_dq_sadj_1 = 0xff;
    init_f0_write_dq_sadj_2 = 0xff;
    init_f0_write_dq_sadj_3 = 0xff;

    init_f0_write_level_sadj_0 = 0xff;
    init_f0_write_level_sadj_1 = 0xff;
    init_f0_write_level_sadj_2 = 0xff;
    init_f0_write_level_sadj_3 = 0xff;

    init_f0_ca_sadj_0 = 0xff;
    init_f0_ca_sadj_1 = 0xff;
    init_f0_ca_sadj_2 = 0xff;

    init_f0_ca_write_level_sadj_0 = 0xff;
    init_f0_ca_write_level_sadj_1 = 0xff;
    init_f0_ca_write_level_sadj_2 = 0xff;

    init_f0_ca_ck_sadj_0 = 0xff;
    init_f0_ca_ck_sadj_1 = 0xff;
    init_f0_ca_ck_sadj_2 = 0xff;

    init_f1_read_dqs_sadj_0 = 0xff;
    init_f1_read_dqs_sadj_1 = 0xff;
    init_f1_read_dqs_sadj_2 = 0xff;
    init_f1_read_dqs_sadj_3 = 0xff;

    init_f1_write_dqs_sadj_0 = 0xff;
    init_f1_write_dqs_sadj_1 = 0xff;
    init_f1_write_dqs_sadj_2 = 0xff;
    init_f1_write_dqs_sadj_3 = 0xff;

    init_f1_read_dqs_b_sadj_0 = 0xff;
    init_f1_read_dqs_b_sadj_1 = 0xff;
    init_f1_read_dqs_b_sadj_2 = 0xff;
    init_f1_read_dqs_b_sadj_3 = 0xff;

    init_f1_write_dq_ext_sadj_0 = 0x0;
    init_f1_write_dq_ext_sadj_1 = 0x0;
    init_f1_write_dq_ext_sadj_2 = 0x0;
    init_f1_write_dq_ext_sadj_3 = 0x0;

    init_f1_write_dq_sadj_0 = 0xff;
    init_f1_write_dq_sadj_1 = 0xff;
    init_f1_write_dq_sadj_2 = 0xff;
    init_f1_write_dq_sadj_3 = 0xff;

    init_f1_write_level_sadj_0 = 0xff;
    init_f1_write_level_sadj_1 = 0xff;
    init_f1_write_level_sadj_2 = 0xff;
    init_f1_write_level_sadj_3 = 0xff;

    init_f1_ca_sadj_0 = 0xff;
    init_f1_ca_sadj_1 = 0xff;
    init_f1_ca_sadj_2 = 0xff;

    init_f1_ca_write_level_sadj_0 = 0xff;
    init_f1_ca_write_level_sadj_1 = 0xff;
    init_f1_ca_write_level_sadj_2 = 0xff;

    init_f1_ca_ck_sadj_0 = 0xff;
    init_f1_ca_ck_sadj_1 = 0xff;
    init_f1_ca_ck_sadj_2 = 0xff;

    init_rfe_sadj_0 = 0xff;
    init_rfe_sadj_1 = 0xff;
    init_rfe_sadj_2 = 0xff;
    init_rfe_sadj_3 = 0xff;

    init_dll_frequency_bank_select = 0x1;

    init_ds3_dqs_cur_sadj = 0xff;
    init_ds2_dqs_cur_sadj = 0xff;
    init_ds1_dqs_cur_sadj = 0xff;
    init_ds0_dqs_cur_sadj = 0xff;
}


   //===========================================================================
   //  read_dll_ctrl_registers
   //===========================================================================
void read_dll_ctrl_registers()
{
    int           rd_data;
    k510_logi("\n");
    rd_data = read_register(RGDLY_ADDR, 1);
    cur_read_gate_delay_3 = (rd_data >> 24) & 0xff;
    cur_read_gate_delay_2 = (rd_data >> 16) & 0xff;
    cur_read_gate_delay_1 = (rd_data >> 8) & 0xff;
    cur_read_gate_delay_0 = rd_data & 0xff;
    k510_logi("rgdly_registers:          %20s  @0x%08X = 0x%08X\n",
        "RGDLY", RGDLY_ADDR, rd_data);

    rd_data = read_register(RGDLY_ADJ_ADDR, 1);
    k510_logi("rgdly_registers:          %20s  @0x%08X = 0x%08X\n",
        "RGDLY ADJ", RGDLY_ADJ_ADDR, rd_data);

    rd_data = read_register(DLL_CTRL2_ADDR, 1);
    cur_f0_read_dqs_sadj_0   = (rd_data >> 24) & 0xff;
    cur_f0_write_dqs_sadj_0  = (rd_data >> 16) & 0xff;
    cur_f0_read_dqs_b_sadj_0 = (rd_data >> 8) & 0xff;
    cur_f0_write_dq_sadj_0   = rd_data & 0xff;
    k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
        "DLL_CTRL2", DLL_CTRL2_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL3_ADDR, 1);
      cur_f0_read_dqs_sadj_1   = (rd_data >> 24) & 0xff;
      cur_f0_write_dqs_sadj_1  = (rd_data >> 16) & 0xff;
      cur_f0_read_dqs_b_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f0_write_dq_sadj_1   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL3", DLL_CTRL3_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL4_ADDR, 1);
      cur_f0_read_dqs_sadj_2   = (rd_data >> 24) & 0xff;
      cur_f0_write_dqs_sadj_2  = (rd_data >> 16) & 0xff;
      cur_f0_read_dqs_b_sadj_2 = (rd_data >> 8) & 0xff;
      cur_f0_write_dq_sadj_2   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL4", DLL_CTRL4_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL5_ADDR, 1);
      cur_f0_read_dqs_sadj_3   = (rd_data >> 24) & 0xff;
      cur_f0_write_dqs_sadj_3  = (rd_data >> 16) & 0xff;
      cur_f0_read_dqs_b_sadj_3 = (rd_data >> 8) & 0xff;
      cur_f0_write_dq_sadj_3   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL5", DLL_CTRL5_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL6_ADDR, 1);
      cur_f0_write_level_sadj_3 = (rd_data >> 24) & 0xff;
      cur_f0_write_level_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f0_write_level_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f0_write_level_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL6", DLL_CTRL6_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL7_ADDR, 1);
      cur_f0_ca_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f0_ca_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f0_ca_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL7", DLL_CTRL7_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL8_ADDR, 1);
      cur_f0_ca_write_level_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f0_ca_write_level_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f0_ca_write_level_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL8", DLL_CTRL8_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL9_ADDR, 1);
      cur_f0_ca_ck_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f0_ca_ck_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f0_ca_ck_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL9", DLL_CTRL9_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL11_ADDR, 1);
      cur_f1_read_dqs_sadj_0   = (rd_data >> 24) & 0xff;;
      cur_f1_write_dqs_sadj_0  = (rd_data >> 16) & 0xff;;
      cur_f1_read_dqs_b_sadj_0 = (rd_data >> 8) & 0xff;
      cur_f1_write_dq_sadj_0   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL11", DLL_CTRL11_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL12_ADDR, 1);
      cur_f1_read_dqs_sadj_1   = (rd_data >> 24) & 0xff;;
      cur_f1_write_dqs_sadj_1  = (rd_data >> 16) & 0xff;;
      cur_f1_read_dqs_b_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f1_write_dq_sadj_1   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL12", DLL_CTRL12_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL13_ADDR, 1);
      cur_f1_read_dqs_sadj_2   = (rd_data >> 24) & 0xff;
      cur_f1_write_dqs_sadj_2  = (rd_data >> 16) & 0xff;
      cur_f1_read_dqs_b_sadj_2 = (rd_data >> 8) & 0xff;
      cur_f1_write_dq_sadj_2   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL13", DLL_CTRL13_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL14_ADDR, 1);
      cur_f1_read_dqs_sadj_3   = (rd_data >> 24) & 0xff;
      cur_f1_write_dqs_sadj_3  = (rd_data >> 16) & 0xff;
      cur_f1_read_dqs_b_sadj_3 = (rd_data >> 8) & 0xff;
      cur_f1_write_dq_sadj_3   = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL14", DLL_CTRL14_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL15_ADDR, 1);
      cur_f1_write_level_sadj_3 = (rd_data >> 24) & 0xff;
      cur_f1_write_level_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f1_write_level_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f1_write_level_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL15", DLL_CTRL15_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL16_ADDR, 1);
      cur_f1_ca_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f1_ca_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f1_ca_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL16", DLL_CTRL16_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL17_ADDR, 1);
      cur_f1_ca_write_level_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f1_ca_write_level_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f1_ca_write_level_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL17", DLL_CTRL17_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL18_ADDR, 1);
      cur_f1_ca_ck_sadj_2 = (rd_data >> 16) & 0xff;
      cur_f1_ca_ck_sadj_1 = (rd_data >> 8) & 0xff;
      cur_f1_ca_ck_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL18", DLL_CTRL18_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL19_ADDR, 1);
      cur_rfe_sadj_3 = (rd_data >> 24) & 0xff;
      cur_rfe_sadj_2 = (rd_data >> 16) & 0xff;
      cur_rfe_sadj_1 = (rd_data >> 8) & 0xff;
      cur_rfe_sadj_0 = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL19", DLL_CTRL19_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL20_ADDR, 1);
      cur_f1_write_dq_ext_sadj_3 = (rd_data >> 26) & 0x3;
      cur_f0_write_dq_ext_sadj_3 = (rd_data >> 24) & 0x3;
      cur_f1_write_dq_ext_sadj_2 = (rd_data >> 18) & 0x3;
      cur_f0_write_dq_ext_sadj_2 = (rd_data >> 16) & 0x3;
      cur_f1_write_dq_ext_sadj_1 = (rd_data >> 10) & 0x3;
      cur_f0_write_dq_ext_sadj_1 = (rd_data >> 8) & 0x3;
      cur_f1_write_dq_ext_sadj_0 = (rd_data >> 2) & 0x3;
      cur_f0_write_dq_ext_sadj_0 = (rd_data >> 0) & 0x3;

      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL20", DLL_CTRL20_ADDR, rd_data);


      rd_data = read_register(DLL_CTRL21_ADDR, 1);
      cur_dll_frequency_bank_select = rd_data & 0x1;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DLL_CTRL21", DLL_CTRL21_ADDR, rd_data);


      rd_data = read_register(DQS_DRIFT_COR_ADDR, 1);
      cur_ds3_dqs_cur_sadj = (rd_data >> 24) & 0xff;
      cur_ds2_dqs_cur_sadj = (rd_data >> 16) & 0xff;
      cur_ds1_dqs_cur_sadj = (rd_data >> 8) & 0xff;
      cur_ds0_dqs_cur_sadj = rd_data & 0xff;
      k510_logi("read_dll_ctrl_registers:  %20s  @0x%08X = 0x%08X\n",
         "DQS_DRIFT_COR", DQS_DRIFT_COR_ADDR, rd_data);

    k510_logi("\n");
} // read_dll_ctrl_registers


   //===========================================================================
   //  update_init_data
   //===========================================================================
void update_init_data()
{
    init_read_gate_delay_0 = cur_read_gate_delay_0;
    init_read_gate_delay_1 = cur_read_gate_delay_1;
    init_read_gate_delay_2 = cur_read_gate_delay_2;
    init_read_gate_delay_3 = cur_read_gate_delay_3;

    init_f0_read_dqs_sadj_0 = cur_f0_read_dqs_sadj_0;
    init_f0_read_dqs_sadj_1 = cur_f0_read_dqs_sadj_1;
    init_f0_read_dqs_sadj_2 = cur_f0_read_dqs_sadj_2;
    init_f0_read_dqs_sadj_3 = cur_f0_read_dqs_sadj_3;

    init_f0_write_dqs_sadj_0 = cur_f0_write_dqs_sadj_0;
    init_f0_write_dqs_sadj_1 = cur_f0_write_dqs_sadj_1;
    init_f0_write_dqs_sadj_2 = cur_f0_write_dqs_sadj_2;
    init_f0_write_dqs_sadj_3 = cur_f0_write_dqs_sadj_3;

    init_f0_read_dqs_b_sadj_0 = cur_f0_read_dqs_b_sadj_0;
    init_f0_read_dqs_b_sadj_1 = cur_f0_read_dqs_b_sadj_1;
    init_f0_read_dqs_b_sadj_2 = cur_f0_read_dqs_b_sadj_2;
    init_f0_read_dqs_b_sadj_3 = cur_f0_read_dqs_b_sadj_3;

    init_f0_write_dq_ext_sadj_0 = cur_f0_write_dq_ext_sadj_0;
    init_f0_write_dq_ext_sadj_1 = cur_f0_write_dq_ext_sadj_1;
    init_f0_write_dq_ext_sadj_2 = cur_f0_write_dq_ext_sadj_2;
    init_f0_write_dq_ext_sadj_3 = cur_f0_write_dq_ext_sadj_3;

    init_f0_write_dq_sadj_0 = cur_f0_write_dq_sadj_0;
    init_f0_write_dq_sadj_1 = cur_f0_write_dq_sadj_1;
    init_f0_write_dq_sadj_2 = cur_f0_write_dq_sadj_2;
    init_f0_write_dq_sadj_3 = cur_f0_write_dq_sadj_3;

    init_f0_write_level_sadj_0 = cur_f0_write_level_sadj_0;
    init_f0_write_level_sadj_1 = cur_f0_write_level_sadj_1;
    init_f0_write_level_sadj_2 = cur_f0_write_level_sadj_2;
    init_f0_write_level_sadj_3 = cur_f0_write_level_sadj_3;

    init_f0_ca_sadj_0 = cur_f0_ca_sadj_0;
    init_f0_ca_sadj_1 = cur_f0_ca_sadj_1;
    init_f0_ca_sadj_2 = cur_f0_ca_sadj_2;

    init_f0_ca_write_level_sadj_0 = cur_f0_ca_write_level_sadj_0;
    init_f0_ca_write_level_sadj_1 = cur_f0_ca_write_level_sadj_1;
    init_f0_ca_write_level_sadj_2 = cur_f0_ca_write_level_sadj_2;

    init_f0_ca_ck_sadj_0 = cur_f0_ca_ck_sadj_0;
    init_f0_ca_ck_sadj_1 = cur_f0_ca_ck_sadj_1;
    init_f0_ca_ck_sadj_2 = cur_f0_ca_ck_sadj_2;

    init_f1_read_dqs_sadj_0 = cur_f1_read_dqs_sadj_0;
    init_f1_read_dqs_sadj_1 = cur_f1_read_dqs_sadj_1;
    init_f1_read_dqs_sadj_2 = cur_f1_read_dqs_sadj_2;
    init_f1_read_dqs_sadj_3 = cur_f1_read_dqs_sadj_3;

    init_f1_write_dqs_sadj_0 = cur_f1_write_dqs_sadj_0;
    init_f1_write_dqs_sadj_1 = cur_f1_write_dqs_sadj_1;
    init_f1_write_dqs_sadj_2 = cur_f1_write_dqs_sadj_2;
    init_f1_write_dqs_sadj_3 = cur_f1_write_dqs_sadj_3;

    init_f1_read_dqs_b_sadj_0 = cur_f1_read_dqs_b_sadj_0;
    init_f1_read_dqs_b_sadj_1 = cur_f1_read_dqs_b_sadj_1;
    init_f1_read_dqs_b_sadj_2 = cur_f1_read_dqs_b_sadj_2;
    init_f1_read_dqs_b_sadj_3 = cur_f1_read_dqs_b_sadj_3;

    init_f1_write_dq_ext_sadj_0 = cur_f1_write_dq_ext_sadj_0;
    init_f1_write_dq_ext_sadj_1 = cur_f1_write_dq_ext_sadj_1;
    init_f1_write_dq_ext_sadj_2 = cur_f1_write_dq_ext_sadj_2;
    init_f1_write_dq_ext_sadj_3 = cur_f1_write_dq_ext_sadj_3;

    init_f1_write_dq_sadj_0 = cur_f1_write_dq_sadj_0;
    init_f1_write_dq_sadj_1 = cur_f1_write_dq_sadj_1;
    init_f1_write_dq_sadj_2 = cur_f1_write_dq_sadj_2;
    init_f1_write_dq_sadj_3 = cur_f1_write_dq_sadj_3;

    init_f1_write_level_sadj_0 = cur_f1_write_level_sadj_0;
    init_f1_write_level_sadj_1 = cur_f1_write_level_sadj_1;
    init_f1_write_level_sadj_2 = cur_f1_write_level_sadj_2;
    init_f1_write_level_sadj_3 = cur_f1_write_level_sadj_3;

    init_f1_ca_sadj_0 = cur_f1_ca_sadj_0;
    init_f1_ca_sadj_1 = cur_f1_ca_sadj_1;
    init_f1_ca_sadj_2 = cur_f1_ca_sadj_2;

    init_f1_ca_write_level_sadj_0 = cur_f1_ca_write_level_sadj_0;
    init_f1_ca_write_level_sadj_1 = cur_f1_ca_write_level_sadj_1;
    init_f1_ca_write_level_sadj_2 = cur_f1_ca_write_level_sadj_2;

    init_f1_ca_ck_sadj_0 = cur_f1_ca_ck_sadj_0;
    init_f1_ca_ck_sadj_1 = cur_f1_ca_ck_sadj_1;
    init_f1_ca_ck_sadj_2 = cur_f1_ca_ck_sadj_2;

    init_rfe_sadj_0 = cur_rfe_sadj_0;
    init_rfe_sadj_1 = cur_rfe_sadj_1;
    init_rfe_sadj_2 = cur_rfe_sadj_2;
    init_rfe_sadj_3 = cur_rfe_sadj_3;

    init_dll_frequency_bank_select = cur_dll_frequency_bank_select;

    init_ds3_dqs_cur_sadj = cur_ds3_dqs_cur_sadj;
    init_ds2_dqs_cur_sadj = cur_ds2_dqs_cur_sadj;
    init_ds1_dqs_cur_sadj = cur_ds1_dqs_cur_sadj;
    init_ds0_dqs_cur_sadj = cur_ds0_dqs_cur_sadj;
}


   //===========================================================================
   //  update_pre_data
   //===========================================================================
void update_pre_data()
{
      pre_read_gate_delay_0 = cur_read_gate_delay_0;
      pre_read_gate_delay_1 = cur_read_gate_delay_1;
      pre_read_gate_delay_2 = cur_read_gate_delay_2;
      pre_read_gate_delay_3 = cur_read_gate_delay_3;

      pre_f0_read_dqs_sadj_0 = cur_f0_read_dqs_sadj_0;
      pre_f0_read_dqs_sadj_1 = cur_f0_read_dqs_sadj_1;
      pre_f0_read_dqs_sadj_2 = cur_f0_read_dqs_sadj_2;
      pre_f0_read_dqs_sadj_3 = cur_f0_read_dqs_sadj_3;

      pre_f0_write_dqs_sadj_0 = cur_f0_write_dqs_sadj_0;
      pre_f0_write_dqs_sadj_1 = cur_f0_write_dqs_sadj_1;
      pre_f0_write_dqs_sadj_2 = cur_f0_write_dqs_sadj_2;
      pre_f0_write_dqs_sadj_3 = cur_f0_write_dqs_sadj_3;

      pre_f0_read_dqs_b_sadj_0 = cur_f0_read_dqs_b_sadj_0;
      pre_f0_read_dqs_b_sadj_1 = cur_f0_read_dqs_b_sadj_1;
      pre_f0_read_dqs_b_sadj_2 = cur_f0_read_dqs_b_sadj_2;
      pre_f0_read_dqs_b_sadj_3 = cur_f0_read_dqs_b_sadj_3;

      pre_f0_write_dq_ext_sadj_0 = cur_f0_write_dq_ext_sadj_0;
      pre_f0_write_dq_ext_sadj_1 = cur_f0_write_dq_ext_sadj_1;
      pre_f0_write_dq_ext_sadj_2 = cur_f0_write_dq_ext_sadj_2;
      pre_f0_write_dq_ext_sadj_3 = cur_f0_write_dq_ext_sadj_3;

      pre_f0_write_dq_sadj_0 = cur_f0_write_dq_sadj_0;
      pre_f0_write_dq_sadj_1 = cur_f0_write_dq_sadj_1;
      pre_f0_write_dq_sadj_2 = cur_f0_write_dq_sadj_2;
      pre_f0_write_dq_sadj_3 = cur_f0_write_dq_sadj_3;

      pre_f0_write_level_sadj_0 = cur_f0_write_level_sadj_0;
      pre_f0_write_level_sadj_1 = cur_f0_write_level_sadj_1;
      pre_f0_write_level_sadj_2 = cur_f0_write_level_sadj_2;
      pre_f0_write_level_sadj_3 = cur_f0_write_level_sadj_3;

      pre_f0_ca_sadj_0 = cur_f0_ca_sadj_0;
      pre_f0_ca_sadj_1 = cur_f0_ca_sadj_1;
      pre_f0_ca_sadj_2 = cur_f0_ca_sadj_2;

      pre_f0_ca_write_level_sadj_0 = cur_f0_ca_write_level_sadj_0;
      pre_f0_ca_write_level_sadj_1 = cur_f0_ca_write_level_sadj_1;
      pre_f0_ca_write_level_sadj_2 = cur_f0_ca_write_level_sadj_2;

      pre_f0_ca_ck_sadj_0 = cur_f0_ca_ck_sadj_0;
      pre_f0_ca_ck_sadj_1 = cur_f0_ca_ck_sadj_1;
      pre_f0_ca_ck_sadj_2 = cur_f0_ca_ck_sadj_2;

      pre_f1_read_dqs_sadj_0 = cur_f1_read_dqs_sadj_0;
      pre_f1_read_dqs_sadj_1 = cur_f1_read_dqs_sadj_1;
      pre_f1_read_dqs_sadj_2 = cur_f1_read_dqs_sadj_2;
      pre_f1_read_dqs_sadj_3 = cur_f1_read_dqs_sadj_3;

      pre_f1_write_dqs_sadj_0 = cur_f1_write_dqs_sadj_0;
      pre_f1_write_dqs_sadj_1 = cur_f1_write_dqs_sadj_1;
      pre_f1_write_dqs_sadj_2 = cur_f1_write_dqs_sadj_2;
      pre_f1_write_dqs_sadj_3 = cur_f1_write_dqs_sadj_3;

      pre_f1_read_dqs_b_sadj_0 = cur_f1_read_dqs_b_sadj_0;
      pre_f1_read_dqs_b_sadj_1 = cur_f1_read_dqs_b_sadj_1;
      pre_f1_read_dqs_b_sadj_2 = cur_f1_read_dqs_b_sadj_2;
      pre_f1_read_dqs_b_sadj_3 = cur_f1_read_dqs_b_sadj_3;

      pre_f1_write_dq_ext_sadj_0 = cur_f1_write_dq_ext_sadj_0;
      pre_f1_write_dq_ext_sadj_1 = cur_f1_write_dq_ext_sadj_1;
      pre_f1_write_dq_ext_sadj_2 = cur_f1_write_dq_ext_sadj_2;
      pre_f1_write_dq_ext_sadj_3 = cur_f1_write_dq_ext_sadj_3;

      pre_f1_write_dq_sadj_0 = cur_f1_write_dq_sadj_0;
      pre_f1_write_dq_sadj_1 = cur_f1_write_dq_sadj_1;
      pre_f1_write_dq_sadj_2 = cur_f1_write_dq_sadj_2;
      pre_f1_write_dq_sadj_3 = cur_f1_write_dq_sadj_3;

      pre_f1_write_level_sadj_0 = cur_f1_write_level_sadj_0;
      pre_f1_write_level_sadj_1 = cur_f1_write_level_sadj_1;
      pre_f1_write_level_sadj_2 = cur_f1_write_level_sadj_2;
      pre_f1_write_level_sadj_3 = cur_f1_write_level_sadj_3;

      pre_f1_ca_sadj_0 = cur_f1_ca_sadj_0;
      pre_f1_ca_sadj_1 = cur_f1_ca_sadj_1;
      pre_f1_ca_sadj_2 = cur_f1_ca_sadj_2;

      pre_f1_ca_write_level_sadj_0 = cur_f1_ca_write_level_sadj_0;
      pre_f1_ca_write_level_sadj_1 = cur_f1_ca_write_level_sadj_1;
      pre_f1_ca_write_level_sadj_2 = cur_f1_ca_write_level_sadj_2;

      pre_f1_ca_ck_sadj_0 = cur_f1_ca_ck_sadj_0;
      pre_f1_ca_ck_sadj_1 = cur_f1_ca_ck_sadj_1;
      pre_f1_ca_ck_sadj_2 = cur_f1_ca_ck_sadj_2;

      pre_rfe_sadj_0 = cur_rfe_sadj_0;
      pre_rfe_sadj_1 = cur_rfe_sadj_1;
      pre_rfe_sadj_2 = cur_rfe_sadj_2;
      pre_rfe_sadj_3 = cur_rfe_sadj_3;

      pre_dll_frequency_bank_select = cur_dll_frequency_bank_select;

      pre_ds3_dqs_cur_sadj = cur_ds3_dqs_cur_sadj;
      pre_ds2_dqs_cur_sadj = cur_ds2_dqs_cur_sadj;
      pre_ds1_dqs_cur_sadj = cur_ds1_dqs_cur_sadj;
      pre_ds0_dqs_cur_sadj = cur_ds0_dqs_cur_sadj;
}


   //===========================================================================
   //  print_pre_vs_cur_data
   //===========================================================================
void print_pre_vs_cur_data()
{
    k510_logi("\n\t");
      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "read_gate_delay_0",
         pre_read_gate_delay_0,
         cur_read_gate_delay_0);
      if (pre_read_gate_delay_0 != cur_read_gate_delay_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "read_gate_delay_1",
         pre_read_gate_delay_1,
         cur_read_gate_delay_1);
      if (pre_read_gate_delay_1 != cur_read_gate_delay_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "read_gate_delay_2",
         pre_read_gate_delay_2,
         cur_read_gate_delay_2);
      if (pre_read_gate_delay_2 != cur_read_gate_delay_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "read_gate_delay_3",
         pre_read_gate_delay_3,
         cur_read_gate_delay_3);
      if (pre_read_gate_delay_3 != cur_read_gate_delay_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_sadj_0",
         pre_f0_read_dqs_sadj_0,
         cur_f0_read_dqs_sadj_0);
      if (pre_f0_read_dqs_sadj_0 != cur_f0_read_dqs_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_sadj_1",
         pre_f0_read_dqs_sadj_1,
         cur_f0_read_dqs_sadj_1);
      if (pre_f0_read_dqs_sadj_1 != cur_f0_read_dqs_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_sadj_2",
         pre_f0_read_dqs_sadj_2,
         cur_f0_read_dqs_sadj_2);
      if (pre_f0_read_dqs_sadj_2 != cur_f0_read_dqs_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_sadj_3",
         pre_f0_read_dqs_sadj_3,
         cur_f0_read_dqs_sadj_3);
      if (pre_f0_read_dqs_sadj_3 != cur_f0_read_dqs_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dqs_sadj_0",
         pre_f0_write_dqs_sadj_0,
         cur_f0_write_dqs_sadj_0);
      if (pre_f0_write_dqs_sadj_0 != cur_f0_write_dqs_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dqs_sadj_1",
         pre_f0_write_dqs_sadj_1,
         cur_f0_write_dqs_sadj_1);
      if (pre_f0_write_dqs_sadj_1 != cur_f0_write_dqs_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dqs_sadj_2",
         pre_f0_write_dqs_sadj_2,
         cur_f0_write_dqs_sadj_2);
      if (pre_f0_write_dqs_sadj_2 != cur_f0_write_dqs_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dqs_sadj_3",
         pre_f0_write_dqs_sadj_3,
         cur_f0_write_dqs_sadj_3);
      if (pre_f0_write_dqs_sadj_3 != cur_f0_write_dqs_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_b_sadj_0",
         pre_f0_read_dqs_b_sadj_0,
         cur_f0_read_dqs_b_sadj_0);
      if (pre_f0_read_dqs_b_sadj_0 != cur_f0_read_dqs_b_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_b_sadj_1",
         pre_f0_read_dqs_b_sadj_1,
         cur_f0_read_dqs_b_sadj_1);
      if (pre_f0_read_dqs_b_sadj_1 != cur_f0_read_dqs_b_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_b_sadj_2",
         pre_f0_read_dqs_b_sadj_2,
         cur_f0_read_dqs_b_sadj_2);
      if (pre_f0_read_dqs_b_sadj_2 != cur_f0_read_dqs_b_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_read_dqs_b_sadj_3",
         pre_f0_read_dqs_b_sadj_3,
         cur_f0_read_dqs_b_sadj_3);
      if (pre_f0_read_dqs_b_sadj_3 != cur_f0_read_dqs_b_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_sadj_0",
         pre_f0_write_dq_sadj_0,
         cur_f0_write_dq_sadj_0);
      if (pre_f0_write_dq_sadj_0 != cur_f0_write_dq_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_sadj_1",
         pre_f0_write_dq_sadj_1,
         cur_f0_write_dq_sadj_1);
      if (pre_f0_write_dq_sadj_1 != cur_f0_write_dq_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_sadj_2",
         pre_f0_write_dq_sadj_2,
         cur_f0_write_dq_sadj_2);
      if (pre_f0_write_dq_sadj_2 != cur_f0_write_dq_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_sadj_3",
         pre_f0_write_dq_sadj_3,
         cur_f0_write_dq_sadj_3);
      if (pre_f0_write_dq_sadj_3 != cur_f0_write_dq_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_level_sadj_0",
         pre_f0_write_level_sadj_0,
         cur_f0_write_level_sadj_0);
      if (pre_f0_write_level_sadj_0 != cur_f0_write_level_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_level_sadj_1",
         pre_f0_write_level_sadj_1,
         cur_f0_write_level_sadj_1);
      if (pre_f0_write_level_sadj_1 != cur_f0_write_level_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_level_sadj_2",
         pre_f0_write_level_sadj_2,
         cur_f0_write_level_sadj_2);
      if (pre_f0_write_level_sadj_2 != cur_f0_write_level_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_level_sadj_3",
         pre_f0_write_level_sadj_3,
         cur_f0_write_level_sadj_3);
      if (pre_f0_write_level_sadj_3 != cur_f0_write_level_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_sadj_0",
         pre_f0_ca_sadj_0,
         cur_f0_ca_sadj_0);
      if (pre_f0_ca_sadj_0 != cur_f0_ca_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_sadj_1",
         pre_f0_ca_sadj_1,
         cur_f0_ca_sadj_1);
      if (pre_f0_ca_sadj_1 != cur_f0_ca_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_sadj_2",
         pre_f0_ca_sadj_2,
         cur_f0_ca_sadj_2);
      if (pre_f0_ca_sadj_2 != cur_f0_ca_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_write_level_sadj_0",
         pre_f0_ca_write_level_sadj_0,
         cur_f0_ca_write_level_sadj_0);
      if (pre_f0_ca_write_level_sadj_0 != cur_f0_ca_write_level_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_write_level_sadj_1",
         pre_f0_ca_write_level_sadj_1,
         cur_f0_ca_write_level_sadj_1);
      if (pre_f0_ca_write_level_sadj_1 != cur_f0_ca_write_level_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_write_level_sadj_2",
         pre_f0_ca_write_level_sadj_2,
         cur_f0_ca_write_level_sadj_2);
      if (pre_f0_ca_write_level_sadj_2 != cur_f0_ca_write_level_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_ck_sadj_0",
         pre_f0_ca_ck_sadj_0,
         cur_f0_ca_ck_sadj_0);
      if (pre_f0_ca_ck_sadj_0 != cur_f0_ca_ck_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_ck_sadj_1",
         pre_f0_ca_ck_sadj_1,
         cur_f0_ca_ck_sadj_1);
      if (pre_f0_ca_ck_sadj_1 != cur_f0_ca_ck_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_ca_ck_sadj_2",
         pre_f0_ca_ck_sadj_2,
         cur_f0_ca_ck_sadj_2);
      if (pre_f0_ca_ck_sadj_2 != cur_f0_ca_ck_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_sadj_0",
         pre_f1_read_dqs_sadj_0,
         cur_f1_read_dqs_sadj_0);
      if (pre_f1_read_dqs_sadj_0 != cur_f1_read_dqs_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_sadj_1",
         pre_f1_read_dqs_sadj_1,
         cur_f1_read_dqs_sadj_1);
      if (pre_f1_read_dqs_sadj_1 != cur_f1_read_dqs_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_sadj_2",
         pre_f1_read_dqs_sadj_2,
         cur_f1_read_dqs_sadj_2);
      if (pre_f1_read_dqs_sadj_2 != cur_f1_read_dqs_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_sadj_3",
         pre_f1_read_dqs_sadj_3,
         cur_f1_read_dqs_sadj_3);
      if (pre_f1_read_dqs_sadj_3 != cur_f1_read_dqs_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dqs_sadj_0",
         pre_f1_write_dqs_sadj_0,
         cur_f1_write_dqs_sadj_0);
      if (pre_f1_write_dqs_sadj_0 != cur_f1_write_dqs_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dqs_sadj_1",
         pre_f1_write_dqs_sadj_1,
         cur_f1_write_dqs_sadj_1);
      if (pre_f1_write_dqs_sadj_1 != cur_f1_write_dqs_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dqs_sadj_2",
         pre_f1_write_dqs_sadj_2,
         cur_f1_write_dqs_sadj_2);
      if (pre_f1_write_dqs_sadj_2 != cur_f1_write_dqs_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dqs_sadj_3",
         pre_f1_write_dqs_sadj_3,
         cur_f1_write_dqs_sadj_3);
      if (pre_f1_write_dqs_sadj_3 != cur_f1_write_dqs_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_b_sadj_0",
         pre_f1_read_dqs_b_sadj_0,
         cur_f1_read_dqs_b_sadj_0);
      if (pre_f1_read_dqs_b_sadj_0 != cur_f1_read_dqs_b_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_b_sadj_1",
         pre_f1_read_dqs_b_sadj_1,
         cur_f1_read_dqs_b_sadj_1);
      if (pre_f1_read_dqs_b_sadj_1 != cur_f1_read_dqs_b_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_b_sadj_2",
         pre_f1_read_dqs_b_sadj_2,
         cur_f1_read_dqs_b_sadj_2);
      if (pre_f1_read_dqs_b_sadj_2 != cur_f1_read_dqs_b_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_read_dqs_b_sadj_3",
         pre_f1_read_dqs_b_sadj_3,
         cur_f1_read_dqs_b_sadj_3);
      if (pre_f1_read_dqs_b_sadj_3 != cur_f1_read_dqs_b_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_sadj_0",
         pre_f1_write_dq_sadj_0,
         cur_f1_write_dq_sadj_0);
      if (pre_f1_write_dq_sadj_0 != cur_f1_write_dq_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_sadj_1",
         pre_f1_write_dq_sadj_1,
         cur_f1_write_dq_sadj_1);
      if (pre_f1_write_dq_sadj_1 != cur_f1_write_dq_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_sadj_2",
         pre_f1_write_dq_sadj_2,
         cur_f1_write_dq_sadj_2);
      if (pre_f1_write_dq_sadj_2 != cur_f1_write_dq_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_sadj_3",
         pre_f1_write_dq_sadj_3,
         cur_f1_write_dq_sadj_3);
      if (pre_f1_write_dq_sadj_3 != cur_f1_write_dq_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_level_sadj_0",
         pre_f1_write_level_sadj_0,
         cur_f1_write_level_sadj_0);
      if (pre_f1_write_level_sadj_0 != cur_f1_write_level_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_level_sadj_1",
         pre_f1_write_level_sadj_1,
         cur_f1_write_level_sadj_1);
      if (pre_f1_write_level_sadj_1 != cur_f1_write_level_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_level_sadj_2",
         pre_f1_write_level_sadj_2,
         cur_f1_write_level_sadj_2);
      if (pre_f1_write_level_sadj_2 != cur_f1_write_level_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_level_sadj_3",
         pre_f1_write_level_sadj_3,
         cur_f1_write_level_sadj_3);
      if (pre_f1_write_level_sadj_3 != cur_f1_write_level_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_sadj_0",
         pre_f1_ca_sadj_0,
         cur_f1_ca_sadj_0);
      if (pre_f1_ca_sadj_0 != cur_f1_ca_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_sadj_1",
         pre_f1_ca_sadj_1,
         cur_f1_ca_sadj_1);
      if (pre_f1_ca_sadj_1 != cur_f1_ca_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_sadj_2",
         pre_f1_ca_sadj_2,
         cur_f1_ca_sadj_2);
      if (pre_f1_ca_sadj_2 != cur_f1_ca_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_write_level_sadj_0",
         pre_f1_ca_write_level_sadj_0,
         cur_f1_ca_write_level_sadj_0);
      if (pre_f1_ca_write_level_sadj_0 != cur_f1_ca_write_level_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_write_level_sadj_1",
         pre_f1_ca_write_level_sadj_1,
         cur_f1_ca_write_level_sadj_1);
      if (pre_f1_ca_write_level_sadj_1 != cur_f1_ca_write_level_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_write_level_sadj_2",
         pre_f1_ca_write_level_sadj_2,
         cur_f1_ca_write_level_sadj_2);
      if (pre_f1_ca_write_level_sadj_2 != cur_f1_ca_write_level_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_ck_sadj_0",
         pre_f1_ca_ck_sadj_0,
         cur_f1_ca_ck_sadj_0);
      if (pre_f1_ca_ck_sadj_0 != cur_f1_ca_ck_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_ck_sadj_1",
         pre_f1_ca_ck_sadj_1,
         cur_f1_ca_ck_sadj_1);
      if (pre_f1_ca_ck_sadj_1 != cur_f1_ca_ck_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_ca_ck_sadj_2",
         pre_f1_ca_ck_sadj_2,
         cur_f1_ca_ck_sadj_2);
      if (pre_f1_ca_ck_sadj_2 != cur_f1_ca_ck_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "rfe_sadj_0",
         pre_rfe_sadj_0,
         cur_rfe_sadj_0);
      if (pre_rfe_sadj_0 != cur_rfe_sadj_0)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "rfe_sadj_1",
         pre_rfe_sadj_1,
         cur_rfe_sadj_1);
      if (pre_rfe_sadj_1 != cur_rfe_sadj_1)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "rfe_sadj_2",
         pre_rfe_sadj_2,
         cur_rfe_sadj_2);
      if (pre_rfe_sadj_2 != cur_rfe_sadj_2)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "rfe_sadj_3",
         pre_rfe_sadj_3,
         cur_rfe_sadj_3);
      if (pre_rfe_sadj_3 != cur_rfe_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_ext_sadj_0",
         pre_f1_write_dq_ext_sadj_0,
         cur_f1_write_dq_ext_sadj_0);
      if (pre_f1_write_dq_ext_sadj_0 != cur_f1_write_dq_ext_sadj_0)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_ext_sadj_1",
         pre_f1_write_dq_ext_sadj_1,
         cur_f1_write_dq_ext_sadj_1);
      if (pre_f1_write_dq_ext_sadj_1 != cur_f1_write_dq_ext_sadj_1)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_ext_sadj_2",
         pre_f1_write_dq_ext_sadj_2,
         cur_f1_write_dq_ext_sadj_2);
      if (pre_f1_write_dq_ext_sadj_2 != cur_f1_write_dq_ext_sadj_2)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f1_write_dq_ext_sadj_3",
         pre_f1_write_dq_ext_sadj_3,
         cur_f1_write_dq_ext_sadj_3);
      if (pre_f1_write_dq_ext_sadj_3 != cur_f1_write_dq_ext_sadj_3)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_ext_sadj_0",
         pre_f0_write_dq_ext_sadj_0,
         cur_f0_write_dq_ext_sadj_0);
      if (pre_f0_write_dq_ext_sadj_0 != cur_f0_write_dq_ext_sadj_0)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_ext_sadj_1",
         pre_f0_write_dq_ext_sadj_1,
         cur_f0_write_dq_ext_sadj_1);
      if (pre_f0_write_dq_ext_sadj_1 != cur_f0_write_dq_ext_sadj_1)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_ext_sadj_2",
         pre_f0_write_dq_ext_sadj_2,
         cur_f0_write_dq_ext_sadj_2);
      if (pre_f0_write_dq_ext_sadj_2 != cur_f0_write_dq_ext_sadj_2)
         k510_logi( "  Different");

      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "f0_write_dq_ext_sadj_3",
         pre_f0_write_dq_ext_sadj_3,
         cur_f0_write_dq_ext_sadj_3);
      if (pre_f0_write_dq_ext_sadj_3 != cur_f0_write_dq_ext_sadj_3)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "dll_frequency_bank_select",
         pre_dll_frequency_bank_select,
         cur_dll_frequency_bank_select);
      if (pre_dll_frequency_bank_select != cur_dll_frequency_bank_select)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "ds3_dqs_cur_sadj",
         pre_ds3_dqs_cur_sadj,
         cur_ds3_dqs_cur_sadj);
      if (pre_ds3_dqs_cur_sadj != cur_ds3_dqs_cur_sadj)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "ds2_dqs_cur_sadj",
         pre_ds2_dqs_cur_sadj,
         cur_ds2_dqs_cur_sadj);
      if (pre_ds2_dqs_cur_sadj != cur_ds2_dqs_cur_sadj)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "ds1_dqs_cur_sadj",
         pre_ds1_dqs_cur_sadj,
         cur_ds1_dqs_cur_sadj);
      if (pre_ds1_dqs_cur_sadj != cur_ds1_dqs_cur_sadj)
         k510_logi( "  Different");


      k510_logi(
         "\n\tCompare DLL_CTRL %30s:  pre = 0x%02X => 0x%02X = cur",
         "ds0_dqs0_cur_sadj",
         pre_ds0_dqs_cur_sadj,
         cur_ds0_dqs_cur_sadj);
      if (pre_ds0_dqs_cur_sadj != cur_ds0_dqs_cur_sadj)
         k510_logi( "  Different");

    k510_logi("\n\n");
}

uint32_t read_register(uint32_t reg_off, uint32_t is_dfi_reg)
{
    volatile uint32_t *reg_addr;

    if(is_dfi_reg)
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + DDR_PHY_REGS_OFF + reg_off));
    else
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + reg_off*4));

    return *reg_addr;
}

uint32_t write_register(uint32_t reg_off, uint32_t value, uint32_t is_dfi_reg)
{
    volatile uint32_t *reg_addr;

    if(is_dfi_reg)
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + DDR_PHY_REGS_OFF + reg_off));
    else
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + reg_off*4));

    reg_addr[0] = value;

    return 0;
}

uint64_t read_mode_register(uint8_t mod_register, uint64_t *value)
{
    volatile uint32_t regdata = 0;

    /* Clear INT_STATUS_MODE bits in DENALI_CTL_339 by writing 1 to the
       corresponding INT_ACK_MODE bits in DENALI_CTL_346.
       bit[3] Clear MRW completed interrupt.
       bit[2] Clear MRR completed interrupt.
       bit[0] Clear MRR error interrupt.
    */
    regdata |= 1<<3 | 1<<2 | 1;
    write_register(DENALI_CTL_346, regdata, 0);

    /* Verify the INT_STATUS_MODE bits in DENALI_CTL_339 are clear.
       bit[3] MRW completed.
       bit[2] MRR completed.
       bit[0] MRR error occurred.
    */
    regdata = read_register(DENALI_CTL_339, 0);
    if(regdata & 0xd){
        /////mask for currently k510_logd("Unexpected INT_STATUS_MODE bit set in DENALI_CTL_%0d = 0x%x", DENALI_CTL_339, regdata);
        return 1;
    }

    /*  DENALI_CTL_213
    //  [31:25] - RSVD
    //  [24:8]  - READ_MODEREG
    //  [7:0]   - MRW_STATUS
    //
    //  READMODE_REG
    //  [24]   =>field[16]    - Trigger the mode register read.
    //  [23:16]=>field[15:8]  - chip select for which to read the
    //                          command.
    //  [15:8] =>field[7:0]   - mode register number being
    //                          requested (MRz).
    //  MRW_STATUS
    //  [7:5]  =>field[7:5]   - RSVD
    //  [4]    =>field[4]     - For LPDDR4
    //  [3]    =>field[3]     - Self-refresh or deep power-down error.
    //  [2]    =>field[2]     - RSVD
    //  [1]    =>field[1]     - yada-yada
    //  [0]    =>field[0]     - write_modereg parameter
    //                          programming error.
    =========================================================*/
    /* "Initiate the MRR by writing to READMODE_REG bits in DENALI_CTL_213.",
       "bit[24]    - Trigger the mode register read.",
       "bit[23:16] - Chip select for which to read the command.",
       "bit[15:8]  - Mode register number being requested (MRz).");
    */

    regdata = 0x0;
    regdata |= 1<<24 | mod_register << 8;
    write_register(DENALI_CTL_213, regdata, 0);

    /*  DENALI_CTL_339
    /   Check mode register read complete bit is set in
    /  int_status_mode.
    */
    while(1){
        regdata = read_register(DENALI_CTL_339, 0);
        if((regdata & (0x1 << 2)) || (regdata & 0x1)){
            if(!(regdata & 0x1))
                break;
            else {
                /////mask for currently k510_logd("MRR MR%d Mode register read error\n", DENALI_CTL_339);
                return 1;
            }
        }
       // else
            //usleep(1);
    }


    /*  Get the data from the MRR. */
    *value = read_register(DENALI_CTL_214, 0);
    *value |= (((uint64_t)(read_register(DENALI_CTL_215, 0) & 0xff)) << 32);

    return 0;
}


uint64_t read_mode_register_only(uint8_t mode_register, uint64_t *value)
{
    volatile uint32_t regdata = 0;

    /* Clear INT_STATUS_MODE bits in DENALI_CTL_339 by writing 1 to the
       corresponding INT_ACK_MODE bits in DENALI_CTL_346.
       bit[3] Clear MRW completed interrupt.
       bit[2] Clear MRR completed interrupt.
       bit[0] Clear MRR error interrupt.
    */
    regdata |= 1<<3 | 1<<2 | 1;
    write_register(DENALI_CTL_346, regdata, 0);

    /* Verify the INT_STATUS_MODE bits in DENALI_CTL_339 are clear.
       bit[3] MRW completed.
       bit[2] MRR completed.
       bit[0] MRR error occurred.
    */
/*
    regdata = read_register(DENALI_CTL_339, 0);
    if(!(regdata & 0xd)){
        /////mask for currently k510_logd("Unexpected INT_STATUS_MODE bit set in DENALI_CTL_%0d = 0x%8h",
            DENALI_CTL_339, regdata);
        return 1;
    }
*/
    /*  DENALI_CTL_213
    //  [31:25] - RSVD
    //  [24:8]  - READ_MODEREG
    //  [7:0]   - MRW_STATUS
    //
    //  READMODE_REG
    //  [24]   =>field[16]    - Trigger the mode register read.
    //  [23:16]=>field[15:8]  - chip select for which to read the
    //                          command.
    //  [15:8] =>field[7:0]   - mode register number being
    //                          requested (MRz).
    //  MRW_STATUS
    //  [7:5]  =>field[7:5]   - RSVD
    //  [4]    =>field[4]     - For LPDDR4
    //  [3]    =>field[3]     - Self-refresh or deep power-down error.
    //  [2]    =>field[2]     - RSVD
    //  [1]    =>field[1]     - yada-yada
    //  [0]    =>field[0]     - write_modereg parameter
    //                          programming error.
    =========================================================*/
    /* "Initiate the MRR by writing to READMODE_REG bits in DENALI_CTL_213.",
       "bit[24]    - Trigger the mode register read.",
       "bit[23:16] - Chip select for which to read the command.",
       "bit[15:8]  - Mode register number being requested (MRz).");
    */

    regdata = 0x0;
    regdata |= 1<<24 | mode_register << 8;
    write_register(DENALI_CTL_213, regdata, 0);

    /*  DENALI_CTL_339
    /   Check mode register read complete bit is set in
    /  int_status_mode.
    */
/*
    while(1){
        regdata = read_register(DENALI_CTL_339, 0);
        if(regdata & 0x3){
            if(!(regdata & 0x1))
                break;
            else {
                /////mask for currently k510_logd("MRR MR%0d Mode register read error\n", DENALI_CTL_339);
                return 1;
            }
        }
        else
            //usleep(1);
    }
*/
    //usleep(1);

    /*  Get the data from the MRR. */
    *value = read_register(DENALI_CTL_214, 0);
    *value |= (((uint64_t)(read_register(DENALI_CTL_215, 0) & 0xff)) << 32);

    return 0;
}

uint32_t write_mode_register(uint8_t mode_register, uint32_t value)
{
    volatile uint32_t regdata = 0;

    /* The value to write to the mode register is written to
       mrsingle_data_0 (bits 16:0) in DENALI_CTL_245.
       DENALI_CTL_245:",
           bits[16:0] MRSINGLE_DATA_0 - Data to program into memory mode
           register single write to chip select 0.
    */
    write_register(DENALI_CTL_245, value, 0);

    /* Before performing the mode register write, clear any
       INT_STATUS_MODE bits that are set.
    */
    regdata = read_register(DENALI_CTL_339, 0);
    if(regdata & 0xd){
        write_register(DENALI_CTL_346, regdata, 0);

        if(read_register(DENALI_CTL_339, 0) & 0xd){
            /////mask for currently k510_logd("INT_STATUS_MODE bits were not cleared.\n");
            return 1;
        }
    }

    /*  DENALI_CTL_212
    /  [26:0] WRITE_MODEREG - Write memory mode register data to
    /  the DRAMs.
    /  [26] - Trigger FSP register write.  Only valid for LPDDR4.
    /  [25] - Trigger the MRW sequence.
    /  [24] - Write all chip selects.
    /  [23:16] - Mode register write type.  Bit 23 = Write a
    /            single MRz.
    /            Bits[22:16] = MODEREG Parameter fields.
    /  [15:8] - Chip select number to be written.When bit 24 = 0.
    /  [7:0] - Mode register to be written.  When bit 23 = 1.
    */
    regdata = 0;
    regdata |= 0x7 << 23 | mode_register;
    write_register(DENALI_CTL_212, regdata, 0);

    /* Verify that the INT_STATUS_MODE MRW completed (bit 3) in
       DENALI_CTL_339 is set.
       bit[3] MRW completed.
       bit[2] MRR completed.
       bit[0] MRR error.
    */
    while(1){
        regdata = read_register(DENALI_CTL_339, 0);
        if(regdata & 0x8)
            break;
       // else
            //usleep(1);
    }

    /* DENALI_CTL_213
    /  [7:0] MRW_STATUS
    /
    /  Verify MRW_STATUS WRITE_MODEREG parameter error (bit 0) in
    /  DENALI_CTL_213 is not set.
    */
    if(read_register(DENALI_CTL_213, 0) & 0x1){
        /////mask for currently k510_logd("WRITE_MODEREG error occurred!\n");
        return 1;
    }

    return 0;
}

void dump_ddrphy_regs(void)
{
    printf("\n>>>>    Show all DDR register    <<<<\n");
    for(uint32_t i = 0; i < 22; i++)
    {
        printf(">>>>    DLL_CTRL%d_ADDR          = 0x%08X\n", i + 1, read_register(DLL_CTRL1_ADDR + i*4, 1));
    }
    printf(">>>>    RGDLY_ADDR               = 0x%08X\n", read_register(RGDLY_ADDR, 1));
    printf(">>>>    RGDLY_ADJ_ADDR           = 0x%08X\n", read_register(RGDLY_ADJ_ADDR, 1));
    printf(">>>>    IO_CAL0_ADDR             = 0x%08X\n", read_register(IO_CAL0_ADDR, 1));
    printf(">>>>    DSX8_IO_CTRL_ADDR        = 0x%08X\n", read_register(DSX8_IO_CTRL_ADDR, 1));
    printf(">>>>    CAX10_IO_CTRL_ADDR       = 0x%08X\n", read_register(CAX10_IO_CTRL_ADDR, 1));
    printf(">>>>    PHY_CFG_ADDR             = 0x%08X\n", read_register(PHY_CFG_ADDR         , 1));
    printf(">>>>    PHY_DSDIS_ADDR           = 0x%08X\n", read_register(PHY_DSDIS_ADDR       , 1));
    printf(">>>>    TRAINING_CTRL1_ADDR      = 0x%08X\n", read_register(TRAINING_CTRL1_ADDR  , 1));
    printf(">>>>    TRAINING_CTRL2_ADDR      = 0x%08X\n", read_register(TRAINING_CTRL2_ADDR  , 1));
    printf(">>>>    TRAINING_CTRL3_ADDR      = 0x%08X\n", read_register(TRAINING_CTRL3_ADDR  , 1));
    printf(">>>>    TRAINING_CTRL4_ADDR      = 0x%08X\n", read_register(TRAINING_CTRL4_ADDR  , 1));
    printf(">>>>    TRAINING_CTRL5_ADDR      = 0x%08X\n", read_register(TRAINING_CTRL5_ADDR  , 1));
    printf(">>>>    TRAINING_CTRL6_ADDR      = 0x%08X\n", read_register(TRAINING_CTRL6_ADDR  , 1));
    printf(">>>>    CADQ_ADDR                = 0x%08X\n", read_register(CADQ_ADDR            , 1));
    printf(">>>>    RBURST_0_P0_ADDR         = 0x%08X\n", read_register(RBURST_0_P0_ADDR     , 1));
    printf(">>>>    RBURST_0_P1_ADDR         = 0x%08X\n", read_register(RBURST_0_P1_ADDR     , 1));
    printf(">>>>    RBURST_0_P2_ADDR         = 0x%08X\n", read_register(RBURST_0_P2_ADDR     , 1));
    printf(">>>>    RBURST_0_P3_ADDR         = 0x%08X\n", read_register(RBURST_0_P3_ADDR     , 1));
    printf(">>>>    RBURST_1_P0_ADDR         = 0x%08X\n", read_register(RBURST_1_P0_ADDR     , 1));
    printf(">>>>    RBURST_1_P1_ADDR         = 0x%08X\n", read_register(RBURST_1_P1_ADDR     , 1));
    printf(">>>>    RBURST_1_P2_ADDR         = 0x%08X\n", read_register(RBURST_1_P2_ADDR     , 1));
    printf(">>>>    RBURST_1_P3_ADDR         = 0x%08X\n", read_register(RBURST_1_P3_ADDR     , 1));
    printf(">>>>    BIT_RDLY_DS0_ADDR        = 0x%08X\n", read_register(BIT_RDLY_DS0_ADDR    , 1));
    printf(">>>>    BIT_WDLY_DS0_ADDR        = 0x%08X\n", read_register(BIT_WDLY_DS0_ADDR    , 1));
    printf(">>>>    BIT_RDLY_DS1_ADDR        = 0x%08X\n", read_register(BIT_RDLY_DS1_ADDR    , 1));
    printf(">>>>    BIT_WDLY_DS1_ADDR        = 0x%08X\n", read_register(BIT_WDLY_DS1_ADDR    , 1));
    printf(">>>>    BIT_RDLY_DS2_ADDR        = 0x%08X\n", read_register(BIT_RDLY_DS2_ADDR    , 1));
    printf(">>>>    BIT_WDLY_DS2_ADDR        = 0x%08X\n", read_register(BIT_WDLY_DS2_ADDR    , 1));
    printf(">>>>    BIT_RDLY_DS3_ADDR        = 0x%08X\n", read_register(BIT_RDLY_DS3_ADDR    , 1));
    printf(">>>>    BIT_WDLY_DS3_ADDR        = 0x%08X\n", read_register(BIT_WDLY_DS3_ADDR    , 1));
    printf(">>>>    BIT_WDLY_CA0_ADDR        = 0x%08X\n", read_register(BIT_WDLY_CA0_ADDR    , 1));
    printf(">>>>    BIT_WDLY_CA1_ADDR        = 0x%08X\n", read_register(BIT_WDLY_CA1_ADDR    , 1));
    printf(">>>>    BIT_WDLY_CA2_ADDR        = 0x%08X\n", read_register(BIT_WDLY_CA2_ADDR    , 1));
    printf(">>>>    BIT_WDLY_CACK_ADDR       = 0x%08X\n", read_register(BIT_WDLY_CACK_ADDR   , 1));
    printf(">>>>    DQS_DRIFT_GAIN_ADDR      = 0x%08X\n", read_register(DQS_DRIFT_GAIN_ADDR  , 1));
    printf(">>>>    DQS_DRIFT_CFG_ADDR       = 0x%08X\n", read_register(DQS_DRIFT_CFG_ADDR   , 1));
    printf(">>>>    DQS_DRIFT_COR_ADDR       = 0x%08X\n", read_register(DQS_DRIFT_COR_ADDR   , 1));
    printf(">>>>    DQS_DRIFT_COR_EXT_ADDR   = 0x%08X\n", read_register(DQS_DRIFT_COR_EXT_ADDR, 1));
    printf(">>>>    INTERRUPT_MASK_ADDR      = 0x%08X\n", read_register(INTERRUPT_MASK_ADDR  , 1));
    printf(">>>>    INTERRUPT_STATUS_ADDR    = 0x%08X\n", read_register(INTERRUPT_STATUS_ADDR, 1));
    printf(">>>>    BIST_CTRL1_ADDR          = 0x%08X\n", read_register(BIST_CTRL1_ADDR      , 1));
    printf(">>>>    BIST_CTRL2_ADDR          = 0x%08X\n", read_register(BIST_CTRL2_ADDR      , 1));
    printf(">>>>    BIST_STATUS1_ADDR        = 0x%08X\n", read_register(BIST_STATUS1_ADDR    , 1));
    printf(">>>>    BIST_STATUS2_ADDR        = 0x%08X\n", read_register(BIST_STATUS2_ADDR    , 1));
    printf(">>>>    LP_STATUS_CTRL_ADDR      = 0x%08X\n", read_register(LP_STATUS_CTRL_ADDR  , 1));
    printf(">>>>    RDQS_DETC_CNTR_ADDR      = 0x%08X\n", read_register(RDQS_DETC_CNTR_ADDR  , 1));
    printf(">>>>    SPARE_ADDR               = 0x%08X\n", read_register(SPARE_ADDR           , 1));
    printf("\n");
}

void set_read_dqs_sadj(int s0_data, int s1_data, int s2_data, int s3_data)
{
    volatile int regdata;

    //  READ DQS SADJ Data Slice 0
    regdata = read_register(DLL_CTRL2_ADDR, 1);
    bit_set_field(regdata, 8, 24, s0_data);
    write_register(DLL_CTRL2_ADDR, regdata, 1);

    //  READ DQS SADJ Data Slice 1
    regdata = read_register(DLL_CTRL3_ADDR, 1);
    bit_set_field(regdata, 8, 24, s1_data);
    write_register(DLL_CTRL3_ADDR, regdata, 1);

    //  READ DQS SADJ Data Slice 2
    regdata = read_register(DLL_CTRL4_ADDR, 1);
    bit_set_field(regdata, 8, 24, s2_data);
    write_register(DLL_CTRL4_ADDR, regdata, 1);

    //  READ DQS SADJ Data Slice 3
    regdata = read_register(DLL_CTRL5_ADDR, 1);
    bit_set_field(regdata, 8, 24, s3_data);
    write_register(DLL_CTRL5_ADDR, regdata, 1);

}

void set_read_dqs_b_sadj(int s0_data, int s1_data, int s2_data, int s3_data)
{
    int regdata;

    //  READ DQS SADJ Data Slice 0
    regdata = read_register(DLL_CTRL2_ADDR, 1);
    bit_set_field(regdata, 8, 8, s0_data);
    write_register(DLL_CTRL2_ADDR, regdata, 1);

    //  READ DQS SADJ Data Slice 1
    regdata = read_register(DLL_CTRL3_ADDR, 1);
    bit_set_field(regdata, 8, 8, s1_data);
    write_register(DLL_CTRL3_ADDR, regdata, 1);

    //  READ DQS SADJ Data Slice 2
    regdata = read_register(DLL_CTRL4_ADDR, 1);
    bit_set_field(regdata, 8, 8, s2_data);
    write_register(DLL_CTRL4_ADDR, regdata, 1);

    //  READ DQS SADJ Data Slice 3
    regdata = read_register(DLL_CTRL5_ADDR, 1);
    bit_set_field(regdata, 8, 8, s3_data);
    write_register(DLL_CTRL5_ADDR, regdata, 1);
}

void lpddr3_probe_desity(void)
{
    /* Read Mode Register */
    uint64_t mode_reg_value;
    int regdata = -1;
    read_mode_register(8, &mode_reg_value);
    k510_logi("Mode Register 8 is 0x%lX\n", mode_reg_value);
    uint8_t ddr_density = 0;
    switch((mode_reg_value >> 2) & 0xf)
    {
        case 0x4:   //1Gb
            ddr_density = 1;
            regdata = 0x03040000;
        break;
        case 0x5:   //2Gb
            ddr_density = 2;
            regdata = 0x03030000;
        break;
        case 0x6:   //4Gb
            ddr_density = 4;
            regdata = 0x02030000;
        break;
        case 0xE:   //6Gb
            ddr_density = 6;
            regdata = 0x02020000;
        break;
        case 0x7:   //8Gb
            ddr_density = 8;
            regdata = 0x02020000;
        break;
        case 0xD:   //12Gb
            ddr_density = 12;
            regdata = 0x01020000;
        break;
        case 0x8:   //16Gb
            ddr_density = 16;
            regdata = 0x01020000;
        break;
        case 0x9:   //32Gb
            ddr_density = 32;
            k510_loge("####! ERR: 32Gb TBD\n");
        break;
        default:
            k510_loge("####! ERR: We don't get the correct density\n");
            return;
        break;
    }

    REGWR(DDR_BASE_ADDR+4*319,regdata);
    regdata = REGREAD(DDR_BASE_ADDR+4*319);
    printf("DDR density is %d Gb, DENALY_319 = 0x%08X\n", ddr_density, regdata);
}

void ddr_read_gate_training_auto(void)
{
    int regdata;
    /* Enable Read Gate Training during all reads on all Data Slices */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata |=0x100;
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);
}

void ddr_init_regs_data(void)
{
    initialize_init_data();
    read_dll_ctrl_registers();
    update_init_data();
    update_pre_data();
    dump_ddrphy_regs();
}

void ddr_update_regs_data(void)
{
#ifndef _SIMU
    read_dll_ctrl_registers();
    print_pre_vs_cur_data();
    update_pre_data();
    dump_ddrphy_regs();
#endif
}

#define random(x) (rand()%x)
void ddr_bit_delay(uint32_t test_lenth, uint32_t loop_cnt)
{
    uint8_t w_val;
    uint8_t val;
    uint8_t result = 0;
    uint32_t count = 0;
    uint32_t dly_cnt = 0;
    uint32_t regdata = 0;
    uint8_t  dlay = 0;
    uint8_t  addr_offset;
    while(1)
    {
        if(count > loop_cnt)
            return;

        k510_logi("Bit Dlay Loop %d\n", count++);
        for(uint32_t i = 0; i < test_lenth; i++)
        {
            w_val = random(256);
            writeb(w_val, (void *)i);
            val = readb((void *)i);
            if(val != w_val)
            {
                k510_loge("Addr 0x%08X  0x%02X  expected  0x%02X\n", i, val, w_val);
                result = val ^ w_val;
                addr_offset = i % 4;
                for(uint32_t i = 0; i < 8; i++)
                {
                    if((result >> i) & 1)
                    {
                        regdata = read_register(BIT_RDLY_DS0_ADDR + addr_offset * 8, 1);
                        dlay = ((regdata >> (i * 3)) & 0x7);
                        k510_logi("BIT_RDLY_DS%d_ADDR 0x%08X bit%d:%d is 0x%02X\n", addr_offset, regdata, i*3, i*3+2, dlay);
                        if(dlay < 7)
                        {
                            dlay ++;
                            regdata &= ~(0x3 << (i * 3));
                            regdata |= dlay << (i * 3);
                            write_register(BIT_RDLY_DS0_ADDR + addr_offset * 8, regdata, 1);
                            k510_logi("BIT_RDLY_DS0_ADDR 0x%08X\n", read_register(BIT_RDLY_DS0_ADDR, 1));
                            k510_logi("BIT_RDLY_DS1_ADDR 0x%08X\n", read_register(BIT_RDLY_DS1_ADDR, 1));
                            k510_logi("BIT_RDLY_DS2_ADDR 0x%08X\n", read_register(BIT_RDLY_DS2_ADDR, 1));
                            k510_logi("BIT_RDLY_DS3_ADDR 0x%08X\n", read_register(BIT_RDLY_DS3_ADDR, 1));
                        }
                    }
                }
                // break;
            }
        }
    }
}

void ddr_bit_delay_cache(uint32_t test_lenth, uint32_t loop_cnt)
{
   //  uint8_t w_val;
   //  uint8_t val;
   //  uint8_t result = 0;
   //  uint32_t count = 0;
   //  uint32_t dly_cnt = 0;
   //  uint32_t regdata = 0;
   //  uint8_t  dlay = 0;
   //  uint8_t  addr_offset;
   //  uint8_t pattern;

   //  cache_enable();
   //  while(1)
   //  {
   //      if(count > loop_cnt)
   //      {
   //          cache_flush_disable();
   //          return;
   //      }

   //      k510_logi("Cache Bit Dlay Loop %d\n", count++);

   //      if(count % 2)
   //      {
   //          pattern = 0x55;
   //      }
   //      else
   //      {
   //          pattern = 0xaa;
   //      }

   //      memset(0, pattern, test_lenth);
   //      cache_flush();

   //      for(uint32_t i = 0; i < test_lenth; i++)
   //      {
   //          w_val = pattern;
   //          val = readb(i);
   //          if(val != w_val)
   //          {
   //              k510_loge("Addr 0x%08X  0x%02X  expected  0x%02X\n", i, val, w_val);
   //              // break;
   //          }
   //      }
   //  }
   //  cache_flush_disable();
}

void lpddr4_probe_desity(void)
{
    /* Read Mode Register */
    uint32_t regdata = 0;
    uint64_t mode_reg_value;
    read_mode_register(8, &mode_reg_value);
    k510_logi("Mode Register 8 is 0x%lX\n", mode_reg_value);
    uint8_t ddr_density = 0;
    switch((mode_reg_value >> 2) & 0xf)
    {
        case 0x0:   //4Gb
            ddr_density = 4;
            regdata = 0x02030000;
        break;
        case 0x1:   //6Gb
            ddr_density = 6;
            regdata = 0x02020000;
        break;
        case 0x2:   //8Gb
            ddr_density = 8;
            regdata = 0x02020000;
        break;
        case 0x3:   //12Gb
            ddr_density = 12;
            regdata = 0x02010000;
        break;
        case 0x4:   //16Gb
            ddr_density = 16;
            regdata = 0x02010000;
        break;
        case 0x5:   //24Gb
            ddr_density = 24;
            regdata = 0x02000000;
        break;
        case 0x6:   //32Gb
            ddr_density = 32;
            regdata = 0x02000000;
        break;
        default:
            k510_loge("####! ERR: We don't get the correct density\n");
        break;
    }

    writel(regdata, DDR_BASE_ADDR+4*319);
    regdata = UBOOTRD(DDR_BASE_ADDR+4*319);
    k510_logi("DDR density is %d Gb, DENALY_319 = 0x%08X\n", ddr_density, regdata);
}

void ddr_show_dqs_drift_regs(void)
{
    int regdata;

    k510_logi("\n\n======= Show dqs drift regs value =======\n");
    regdata = read_register(DLL_CTRL2_ADDR, 1);
    k510_logd(">>>>    DLL_CTRL2 = 0x%08x \n", regdata);
    k510_logd("DLL_CTRL2   DS0 read_dqs_sadj   =  0x%x\n", bit_get_field(regdata, 8, 24));
    k510_logd("DLL_CTRL2   DS0 write_dqs_sadj  =  0x%x\n", bit_get_field(regdata, 8, 16));
    k510_logd("DLL_CTRL2   DS0 read_dqs_b_sadj =  0x%x\n", bit_get_field(regdata, 8, 8) );
    k510_logd("DLL_CTRL2   DS0 write_dq_sadj   =  0x%x\n", bit_get_field(regdata, 8, 0) );
    regdata = read_register(DLL_CTRL3_ADDR, 1);
    k510_logd(">>>>    DLL_CTRL3 = 0x%08x \n", regdata);
    k510_logd("DLL_CTRL3   DS1 read_dqs_sadj   =  0x%x\n", bit_get_field(regdata, 8, 24));
    k510_logd("DLL_CTRL3   DS1 write_dqs_sadj  =  0x%x\n", bit_get_field(regdata, 8, 16));
    k510_logd("DLL_CTRL3   DS1 read_dqs_b_sadj =  0x%x\n", bit_get_field(regdata, 8, 8) );
    k510_logd("DLL_CTRL3   DS1 write_dq_sadj   =  0x%x\n", bit_get_field(regdata, 8, 0) );

    regdata = read_register(DLL_CTRL4_ADDR, 1);
    k510_logd(">>>>    DLL_CTRL4 = 0x%08x \n", regdata);
    k510_logd("DLL_CTRL4   DS2 read_dqs_sadj   =  0x%x\n", bit_get_field(regdata, 8, 24));
    k510_logd("DLL_CTRL4   DS2 write_dqs_sadj  =  0x%x\n", bit_get_field(regdata, 8, 16));
    k510_logd("DLL_CTRL4   DS2 read_dqs_b_sadj =  0x%x\n", bit_get_field(regdata, 8, 8) );
    k510_logd("DLL_CTRL4   DS2 write_dq_sadj   =  0x%x\n", bit_get_field(regdata, 8, 0) );

    regdata = read_register(DLL_CTRL5_ADDR, 1);
    k510_logd(">>>>    DLL_CTRL5 = 0x%08x \n", regdata);
    k510_logd("DLL_CTRL5   DS3 read_dqs_sadj   =  0x%x\n", bit_get_field(regdata, 8, 24));
    k510_logd("DLL_CTRL5   DS3 write_dqs_sadj  =  0x%x\n", bit_get_field(regdata, 8, 16));
    k510_logd("DLL_CTRL5   DS3 read_dqs_b_sadj =  0x%x\n", bit_get_field(regdata, 8, 8) );
    k510_logd("DLL_CTRL5   DS3 write_dq_sadj   =  0x%x\n", bit_get_field(regdata, 8, 0) );

    regdata = read_register(DLL_CTRL20_ADDR, 1);
    k510_logd(">>>>    DLL_CTRL20 = 0x%08x \n", regdata);
    k510_logd("DLL_CTRL20   write_dq_sadj_f1 ds3 =  0x%x\n", bit_get_field(regdata, 2, 26));
    k510_logd("DLL_CTRL20   write_dq_sadj_f0 ds3 =  0x%x\n", bit_get_field(regdata, 2, 24));
    k510_logd("DLL_CTRL20   write_dq_sadj_f1 ds2 =  0x%x\n", bit_get_field(regdata, 2, 18));
    k510_logd("DLL_CTRL20   write_dq_sadj_f0 ds2 =  0x%x\n", bit_get_field(regdata, 2, 16));
    k510_logd("DLL_CTRL20   write_dq_sadj_f1 ds1 =  0x%x\n", bit_get_field(regdata, 2, 10));
    k510_logd("DLL_CTRL20   write_dq_sadj_f0 ds1 =  0x%x\n", bit_get_field(regdata, 2, 8));
    k510_logd("DLL_CTRL20   write_dq_sadj_f1 ds0 =  0x%x\n", bit_get_field(regdata, 2, 2));
    k510_logd("DLL_CTRL20   write_dq_sadj_f0 ds0 =  0x%x\n", bit_get_field(regdata, 2, 0));

    k510_logi(">>>>    DQS_DRIFT_GAIN_ADDR      = 0x%08X\n", read_register(DQS_DRIFT_GAIN_ADDR  , 1));
    k510_logi(">>>>    DQS_DRIFT_CFG_ADDR       = 0x%08X\n", read_register(DQS_DRIFT_CFG_ADDR   , 1));
    k510_logi(">>>>    DQS_DRIFT_COR_ADDR       = 0x%08X\n", read_register(DQS_DRIFT_COR_ADDR   , 1));
    k510_logi(">>>>    DQS_DRIFT_COR_EXT_ADDR   = 0x%08X\n", read_register(DQS_DRIFT_COR_EXT_ADDR, 1));
    k510_logi(">>>>    INTERRUPT_MASK_ADDR      = 0x%08X\n", read_register(INTERRUPT_MASK_ADDR  , 1));

    regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
    k510_logi(">>>>    INTERRUPT_STATUS_ADDR    = 0x%08X\n", read_register(INTERRUPT_STATUS_ADDR, 1));

    if(bit_check_bit(regdata, 8))
    {
        k510_logd(">>>>    SAW PHY is Master over memory interface interrupt!\n");
    }
    if(bit_check_bit(regdata, 5))
    {
        k510_logi(">>>>    Saw DQS Correction Complete interrupt!\n");
    }
    if(bit_check_bit(regdata, 4))
    {
        k510_logi(">>>>    Saw DQS Correction Error interrupt!\n");
    }
    write_register(INTERRUPT_STATUS_ADDR, regdata, 1);
    k510_logi(">>>>    After clear interrupt INTERRUPT_STATUS_ADDR    = 0x%08X\n", read_register(INTERRUPT_STATUS_ADDR, 1));

    regdata = read_register(DENALI_CTL_336, 0);
    k510_logi(">>>>    DENALI_CTL_336    = 0x%08X\n", regdata);

    if(bit_check_bit(regdata, 14))
    {
        k510_logd(">>>>    Overflow interrupt bit was set int_status_training\n");
    }
    if(bit_check_bit(regdata, 13))
    {
        k510_logd(">>>>    Oscillator has updated base values\n");
    }
    if(bit_check_bit(regdata, 12))
    {
        k510_logd(">>>>    software-requested DQS Oscillator measurement has completed\n");
    }
    if(bit_check_bit(regdata, 15))
    {
        k510_logd(">>>>    DQS oscillator meaurement has been detected out of variance - phy should respond\n");
    }

    k510_logd(">>>>    Clearing all interrupts in int_status_training of controller\n");

    write_register(DENALI_CTL_343, regdata, 0);
    k510_logi(">>>>    After clear interrupt DENALI_CTL_336    = 0x%08X\n", read_register(DENALI_CTL_336, 0));

    uint64_t mode_reg_value;
    read_mode_register(18, &mode_reg_value);
    k510_logi("Mode Register 18 is 0x%lX\n", mode_reg_value);
    read_mode_register(19, &mode_reg_value);
    k510_logi("Mode Register 19 is 0x%lX\n", mode_reg_value);
}

int ddr_dqs_drift_enable(void)
{
    int regdata;
/*
    //disable DQS OSC
    regdata = read_register(DENALI_CTL_038, 0);
    bit_clr_bit(regdata, 16);
    write_register(DENALI_CTL_038, regdata, 0);
*/

    //enable DQS OSC
    regdata = read_register(DENALI_CTL_038, 0);
    bit_set_bit(regdata, 16);
    write_register(DENALI_CTL_038, regdata, 0);
    k510_logd("====>    DQS DRIFT: Set DENALI_CTL_38 ->       0x%08X\n", regdata);

    write_register(DQS_DRIFT_CFG_ADDR, 0x01000000, 1);
    k510_logd("====>    DQS DRIFT: Set DQS_DRIFT_CFG ->       0x%08X\n", read_register(DQS_DRIFT_CFG_ADDR, 1));

    return 0;
}
