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
#include "ddr_param.h"
#include "ddrc.h"
#include "sysctl_boot.h"
#include "sysctl_clk.h"

#if DDR_800
#include "lpddr3_800.h"
uint32_t freq_f0 = 800;
#endif
#if DDR_1066
#include "lpddr3_1066.h"
uint32_t freq_f0 = 1066;
#endif
#if DDR_1333
#include "lpddr3_1333.h"
uint32_t freq_f0 = 1333;
#endif
#if DDR_1600
#include "lpddr3_1600.h"
uint32_t freq_f0 = 1600;
#endif
#if DDR_1866
#include "lpddr3_1866.h"
uint32_t freq_f0 = 1866;
#endif
#if DDR_2133
#include "lpddr3_2133.h"
uint32_t freq_f0 = 2133;
#endif
// #include <sleep.h>

/* 96Bytes pattern */
uint32_t pattern[] = {
0xCCCCCCCC, 0x33333333, 0x33333333, 0x96969696,
0xCCCCCCCC, 0x96969696, 0x69696969, 0x69696969,
0xCCCCCCCC, 0x33333333, 0x33333333, 0x96969696,
0xCCCCCCCC, 0x69696969, 0x96969696, 0x96969696,
0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555,
0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
};
uint32_t * mem_addr = 0x100000000;
#define MEM_BYTE_CNT     (256)
uint32_t mem_wdata[MEM_BYTE_CNT / 4] = {0x0, 0x0, 0x0, 0x0};
uint32_t mem_rdata[MEM_BYTE_CNT / 4] = {0x0, 0x0, 0x0, 0x0};
int read_dqs_sadj;
int read_dqs_b_sadj;
uint8_t rd_dqs_sadj[4];
uint8_t rd_dqs_b_sadj[4];
int MAX_READ_DQS_B_SADJ = 82;
int MAX_READ_DQS_SADJ = 82;
int    val_rb_0_p0;
int    val_rb_0_p1;
int    val_rb_0_p2;
int    val_rb_0_p3;
int    val_rb_1_p0;
int    val_rb_1_p1;
int    val_rb_1_p2;
int    val_rb_1_p3;

int    val_rb_0_p0_even;
int    val_rb_0_p1_even;
int    val_rb_0_p2_even;
int    val_rb_0_p3_even;
int    val_rb_1_p0_even;
int    val_rb_1_p1_even;
int    val_rb_1_p2_even;
int    val_rb_1_p3_even;

int    val_rb_0_p0_odd;
int    val_rb_0_p1_odd;
int    val_rb_0_p2_odd;
int    val_rb_0_p3_odd;
int    val_rb_1_p0_odd;
int    val_rb_1_p1_odd;
int    val_rb_1_p2_odd;
int    val_rb_1_p3_odd;

int    cval_rb_0_p0;
int    cval_rb_0_p1;
int    cval_rb_0_p2;
int    cval_rb_0_p3;
int    cval_rb_1_p0;
int    cval_rb_1_p1;
int    cval_rb_1_p2;
int    cval_rb_1_p3;
int    cval_rb_0_p0_odd;
int    cval_rb_0_p1_odd;
int    cval_rb_0_p2_odd;
int    cval_rb_0_p3_odd;
int    cval_rb_1_p0_odd;
int    cval_rb_1_p1_odd;
int    cval_rb_1_p2_odd;
int    cval_rb_1_p3_odd;
int    cval_rb_0_p0_even;
int    cval_rb_0_p1_even;
int    cval_rb_0_p2_even;
int    cval_rb_0_p3_even;
int    cval_rb_1_p0_even;
int    cval_rb_1_p1_even;
int    cval_rb_1_p2_even;
int    cval_rb_1_p3_even;

int    incr_data;
int    incr_good_avg;
int    incr_good_min;
int    incr_good_max;
int    incr_good_avg0;
int    incr_good_min0;
int    incr_good_max0;
int    incr_good_avg1;
int    incr_good_min1;
int    incr_good_max1;
int    incr_good_avg2;
int    incr_good_min2;
int    incr_good_max2;
int    incr_good_avg3;
int    incr_good_min3;
int    incr_good_max3;
int    incr_good_avg4;
int    incr_good_min4;
int    incr_good_max4;

int    incr_good_avg_dqs_p0;
int    incr_good_avg_dqs_p1;
int    incr_good_avg_dqs_p2;
int    incr_good_avg_dqs_p3;
int    incr_good_avg_dqs_n0;
int    incr_good_avg_dqs_n1;
int    incr_good_avg_dqs_n2;
int    incr_good_avg_dqs_n3;

char    bit_rdly_A[32];
char    bit_rdly_B[32];
int     bit_rdly_pass[32];
int     bit_rdly_fail[32];
char    bit_rdly_min[32];

int 	  p0_delay0;
int 	  p0_delay1;
int 	  p0_delay2;
int 	  p0_delay3;
int 	  p2_delay0;
int 	  p2_delay1;
int 	  p2_delay2;
int 	  p2_delay3;

int         found_pass;
int         found_pass0;
int         found_pass1;
int         found_pass2;
int         found_pass3;

int         found_stop0;
int         found_stop1;
int         found_stop2;
int         found_stop3;

uint8_t     wl_train_error0;
uint8_t     wl_train_error1;
// uint8_t     wl_stop_incr;

// uint8_t wl_train_error0[4];
// uint8_t wl_train_error1[4];
uint8_t wl_end[4];
uint32_t wl_strt_incr[4];
uint32_t wl_stop_incr[4];
uint32_t wl_train_avg[4];
uint8_t wl_train_lane[4][100];

uint8_t     wl_lane_value[4];
int         lane_num;
int         index_msb, index_lsb;
int         cadq_wl_value;

uint8_t     continue_loop;
uint8_t     continue_training;

uint8_t     isEqual;
uint8_t     isEqual_ds0, isEqual_ds1, isEqual_ds2, isEqual_ds3;

int         ctrl6_value;
int8_t      ctrl6_byte_value;

char continue_loop_lp4[4];
int    incr_data_lp4[4];
int    incr_good_avg_lp4[4];
int    incr_good_min_lp4[4];
int    incr_good_max_lp4[4];
int    incr_wr_dq_sadj_f0_1_lp4[4];
int    incr_wr_dq_sadj_f0_1_lp4_avg[4];

char   found_pass_lp4[4];
int    wr_dq_sadj_f0_1_N_lp4_minus_1[4];
char   found_fail_after_pass_lp4[4];
int    wr_dq_sadj_f0_1_N_lp4[4];
double         avg_real_lp4[4];

int    incr_wr_dq_sadj_f0_1;
int    incr_wr_dq_sadj_f0_1_avg;
// char    found_pass;
int    wr_dq_sadj_f0_1_N_minus_1;
char    found_fail_after_pass;
int    wr_dq_sadj_f0_1_N;
int    MADJ;
int    Midpoint;
int    TotalWindowPass;

uint32_t CA_training(void)
{
    uint32_t regdata;

    k510_logi("Begin LPDDR3 CA Training\n");

    /* Step 1 of 23 - LPDDR3 CA Training
       Disable low power modes.
    */
    regdata = read_register(DENALI_CTL_190, 0);
//    /////mask for currently k510_logd("CA-1\n");
    regdata &= ~(1 << 8);
    regdata &= ~(0x3f);
    write_register(DENALI_CTL_190, regdata, 0);
//    /////mask for currently k510_logd("CA-2\n");

    /* Step 2 of 23 - LPDDR3 CA Training
       Initiate the MR41 CA training operation by issuing
       to the memory controller Mode Register Write to MR41
    */
    if(write_mode_register(41, 0x000000a4)){
        k510_logd("write_mode_register return failure, Step 2 of 23 - LPDDR3 CA Training\n");
        return 1;
    }

    /* Step 3 of 23 - LPDDR3 CA Training
       Write to the DDR PHY AHB Register TRAINING_CTRL2 LPDDR3
       CA.
    */
//    /////mask for currently k510_logd("CA-3\n");
     regdata = 0x02aa0155;
     write_register(TRAINING_CTRL2_ADDR, regdata, 1);
//    /////mask for currently k510_logd("CA-4\n");

    /* CA to DQ mapping.  This is overly complex and confusing
    /  in the specification.
    /  CADQ Mapping:
    */
    uint32_t value;
    value = 0x0;
    value |= ((regdata >> 24) & 0x1) << 15;
    value |= ((regdata >> 8) & 0x1) << 14;
    value |= ((regdata >> 23) & 0x1) << 13;
    value |= ((regdata >> 7) & 0x1) << 12;
    value |= ((regdata >> 22) & 0x1) << 11;
    value |= ((regdata >> 6) & 0x1) << 10;
    value |= ((regdata >> 21) & 0x1) << 9;
    value |= ((regdata >> 5) & 0x1) << 8;
    value |= ((regdata >> 19) & 0x1) << 7;
    value |= ((regdata >> 3) & 0x1) << 6;
    value |= ((regdata >> 18) & 0x1) << 5;
    value |= ((regdata >> 2) & 0x1) << 4;
    value |= ((regdata >> 17) & 0x1) << 3;
    value |= ((regdata >> 1) & 0x1) << 2;
    value |= ((regdata >> 16) & 0x1) << 1;
    value |= ((regdata) & 0x1);

    /////mask for currently k510_logd("compare map value = %x", value);

    /* Step 4 of 23 - LPDDR3 CA Training
       Write to the DDR PHY AHB Register TRAINING_CTRL1 LPDDR3
       CA. Set SADJ WRT (bit[10]) bit to 1'b1.
    */


// auto refresh closed by hyg
    regdata = read_register(DENALI_CTL_078, 0);

    /* Clear bit 0. */
    bit_clr_bit(regdata, 0);

    /* Now write the value back into the register. */
    write_register(DENALI_CTL_078, regdata, 0);

    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
 //   /////mask for currently k510_logd("CA-5\n");

    /*  Set SADJ WRT bit to 1. */
    regdata |= 0x1 << 10;

    /*  Set ca_cke_low = 1. */
    regdata |= 0x1 << 18;

    write_register(TRAINING_CTRL1_ADDR, regdata, 1);
//    /////mask for currently k510_logd("CA-6\n");

    /* Step 5 of 23 - LPDDR3 CA Training
       Set DLL_CTRL7 CA SADJ 0,1,2 to 0.
    */

    write_register(DLL_CTRL7_ADDR, 0x0, 1);

    /* Verify Interrupt Status CADQ Updated (bit[6]) is
       NOT set to 1.
    */
    if(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x40){
        k510_logi("Interrupt Status CADQ Updated (bit[6]) was set to 1.\n");
        return 1;
    }
    else{
        /////mask for currently k510_logd("Interrupt Status CADQ Updated (bit[6]) was NOT set to 1. \n");
    }

    /* Step 6 of 23 - LPDDR3 CA Training
       Start Loop 1.
    */
    uint32_t incr_data = 0;
    uint32_t incr_good_min = 99;
    uint32_t incr_good_max = 0;
    uint32_t found_pass = 0;
    uint32_t incr_good_avg = 0;

    /////mask for currently k510_logd("CA Start loop 1\n");
    while(1){
        /* Step 7 of 23 - LPDDR3 CA Training
           Write to the DDR PHY AHB Register TRAINING_CTRL1 LPDDR3
           CA. Set CA_XMT (bit[16]) and SADJ WRT (bit[10]) bits
           to 1'b1.
        */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /*  Set CA_XMT bit to 1. */
        regdata |= 0x1 << 16;

        /*  Set SADJ WRT bit to 1. */
        regdata |= 0x1 << 10;

        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        /* Wait for CA training sequence to
           complete (CA_XMT bit is cleared).
        */
        while(1){
            //usleep(1);
            if(!(read_register(TRAINING_CTRL1_ADDR, 1) & (0x1 << 16)))
                break;
        }

        /* Verify Interrupt Status CADQ Updated (bit[6]) is
           set to 1.  A 1 indicates the CADQ registers have
           been updated for CA training.
        */
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(regdata & (0x1 << 6)){
            /* Interrupt Status CADQ Updated (bit[6]) was correctly
               set to 1.
               Now write 1 to the sticky CADQ Updated (bit[6]) to
               clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status CADQ Updated (bit[6]) is now
               cleared to 0.
            */
            if(read_register(INTERRUPT_STATUS_ADDR, 1) & (0x1 << 6)){
                k510_logi("Interrupt Status CADQ Updated (bit[6]) was NOT cleared to 0.\n");
                return 1;
            }
        }
        else {
            k510_logd("Interrupt Status CADQ Updated (bit[6]) was NOT set to 1.\n");
            return 1;
        }

        /* Step 8 of 23 - LPDDR3 CA Training
           Read from the DDR PHY AHB Register CADQ.
        */
        regdata = read_register(CADQ_ADDR, 1);
        k510_logi("CA loop1 >>>>>    incr_data = 0x%08X, CADQ = 0x%08X, right value = 0x%08X\n", incr_data, regdata, value);

        // k510_logi(">>>>>    incr_data is 0x%08X\n", incr_data);
        // k510_logi(">>>>>    CADQ is 0x%08X\n", regdata);
        // k510_logi(">>>>>    vaule is 0x%08X\n", value);

        /* Step 9 of 23 - LPDDR3 CA Training
           Compare result TRAINING_CTRL2 LPDDR3 CA to CADQ map.
        */
        if((regdata & 0xffff) == value){
            if (incr_data < incr_good_min){
                incr_good_min  = incr_data;
                found_pass = 1;
            }

            if (incr_data > incr_good_max)
                incr_good_max  = incr_data;
        }
        else {
            if (found_pass == 1)
                break;
        }

        /* Step 10 of 23 - LPDDR3 CA Training
           Increment DLL_CTRL7 CA SADJ 0,1,2 by +1 and return
           to start of loop 1 until CA SADJ reaches maximum
           allowed value.
        */
        incr_data += 1;
        if (incr_data <= 82){
            regdata = (incr_data & 0xff);
            regdata |= (incr_data & 0xff) << 8;
            regdata |= (incr_data & 0xff) << 16;

            write_register(DLL_CTRL7_ADDR, regdata, 1);
        }
        else {
            break;
        }
    }

    /*added 1*/
    k510_logd("\nFinal:  LPDDR3 CA Training Loop 1 \n");
    k510_logd("CA loop1 incr_good_min  = 0x%x,  ", incr_good_min);
    k510_logd("CA loop1 incr_good_max  = 0x%x,  \n", incr_good_max);
    //    /////mask for currently k510_logd("incr_good_avg  = 0x%x \n", ((incr_good_min + incr_good_max)/2));

     //incr_good_avg=((incr_good_min+incr_good_max)/2);
     // 06/18/2021 eq correction
     //
     incr_good_avg= (incr_good_min + (incr_good_max - incr_good_min)/2);
     regdata = ((incr_good_avg & 0xff) << 16) |  ((incr_good_avg & 0xff) << 8) |  (incr_good_avg & 0xff);
     write_register(DLL_CTRL7_ADDR, regdata, 1);

//    /////mask for currently k510_logd("CA-7\n");
    /*  Verify that the CA Training was successful. */
    if (incr_good_min == 99){
        k510_logd("LPDDR3 CA Training Loop 1 Failed!\n");
        return 1;
    }

    /* Step 10a of 23 - LPDDR3 CA Training
       Set ca_cke_low = 0.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata &= ~(0x1 << 18);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 11 of 23 - LPDDR3 CA Training
       Save minimum CA SADJ and maximum CA SADJ for matching
       values.
    */
    uint32_t incr_good_min1 = incr_good_min;
    uint32_t incr_good_max1 = incr_good_max;

    /* Step 12 of 23 - LPDDR3 CA Training
       Initiate the MR48 CA training operation by issuing to
       the memory Mode Register Write to MR48.
    */
    regdata = 0xc0;
    if(write_mode_register(48, regdata)){
        k510_logd("write_mode_register return failure, Step 12 of 23 - LPDDR3 CA Training\n");
        return 1;
    }

    /* Step 13 of 23 - LPDDR3 CA Training
       Write to the DDR PHY AHB Register TRAINING_CTRL2 LPDDR3
       CA.
    */
    regdata = 0x02aa0155;
    write_register(TRAINING_CTRL2_ADDR, regdata, 1);

    value = 0x0;
    value |= ((regdata >> 25) & 0x1) << 9;
    value |= ((regdata >> 9) & 0x1) << 8;
    value |= ((regdata >> 20) & 0x1) << 1;
    value |= ((regdata >> 4) & 0x1);

    /* Step 14 of 23 - LPDDR3 CA Training
       Write to the DDR PHY AHB Register TRAINING_CTRL1 LPDDR3
       CA. Set SADJ WRT (bit[10]) bit to 1'b1.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata |= 0x1 << 10;
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 15 of 23 - LPDDR3 CA Training
       Set DLL_CTRL7 CA SADJ 0,1,2 to 0.
    */
    regdata = 0x0;
    write_register(DLL_CTRL7_ADDR, regdata, 1);

    /* Verify Interrupt Status CADQ Updated (bit[6]) is
       NOT set to 1.
    */
    regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
    if (!(regdata & (0x1 << 6))){
//        /////mask for currently k510_logd("Interrupt Status CADQ Updated (bit[6]) is not set to 1.\n");
    }
    else {
        k510_logd("ERR: Interrupt Status CADQ Updated (bit[6]) was set to 1.\n");
        return 1;
    }

    /* Step 16 of 23 - LPDDR3 CA Training
       Start Loop 2.
    */
    incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    while(1){
        /* Step 17 of 23 - LPDDR3 CA Training
           Write to the DDR PHY AHB Register TRAINING_CTRL1 LPDDR3
           CA. Set CA_XMT (bit[16]) and SADJ WRT (bit[10]) bits
           to 1'b1.
        */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /*  Set ca_cke_low = 1. */
        regdata |= 0x1 << 18;

        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        /*  Set CA_XMT bit to 1. */
        regdata |= 0x1 << 16;

        /*  Set SADJ WRT bit to 1.*/
        regdata |= 0x1 << 10;

        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        /* Wait for CA training sequence to
           complete (CA_XMT bit is cleared).
        */
        while(1){
            //usleep(1);
            if(!(read_register(TRAINING_CTRL1_ADDR, 1) & 0x10000))
                break;
        }

        /* Verify Interrupt Status CADQ Updated (bit[6]) is
           set to 1.  A 1 indicates the CADQ registers have
           been updated for CA training.
        */
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        if(regdata & (0x1 << 6)){
            /* Interrupt Status CADQ Updated (bit[6]) was correctly
               set to 1.
               Now write 1 to the sticky CADQ Updated (bit[6]) to
               clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status CADQ Updated (bit[6]) is now
               cleared to 0.
            */
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

            if(!(regdata & (0x1 << 6))){
//                /////mask for currently k510_logd("Interrupt Status CADQ Updated (bit[6]) was correctly cleared to 0.\n");
            }
            else {
                k510_logd("Interrupt Status CADQ Updated (bit[6]) was NOT cleared to 0.\n");
                return 1;
            }
        }
        else {
            k510_logd("Interrupt Status CADQ Updated (bit[6]) was NOT set to 1.\n");
            return 1;
        }

        /* Step 18 of 23 - LPDDR3 CA Training
           Read from the DDR PHY AHB Register CADQ.
        */
        regdata = read_register(CADQ_ADDR, 1);
        k510_logi("CA loop2 >>>>>    incr_data = 0x%08X, CADQ = 0x%08X, right value = 0x%08X\n", incr_data, regdata, value);
        // k510_logd("========= cadq_wl_value = 0x%08x\n", regdata);

        /* Step 19 of 23 - LPDDR3 CA Training
           Compare result to TRAINING_CTRL2 LPDDR3 CA Pattern
           to CADQ map.
        */

        if((regdata & 0xffff) == value){
            if(incr_data < incr_good_min){
                incr_good_min = incr_data;
                found_pass = 1;
            }

            if(incr_data > incr_good_max)
                incr_good_max = incr_data;

        }
        else {
            if(found_pass == 1)
                break;
        }

        /* Step 20 of 23 - LPDDR3 CA Training
           Increment DLL_CTRL7 CA SADJ 0,1,2 by +1 and return
           to start of Loop 2 until CA SADJ reaches maximum
           allowed value.
        */
        incr_data += 1;

        if(incr_data <= 82){
            regdata = (incr_data & 0xff);
            regdata |= (incr_data & 0xff) << 8;
            regdata |= (incr_data & 0xff) << 16;

            write_register(DLL_CTRL7_ADDR, regdata, 1);
        }
        else
            break;
    }

    k510_logd("\nFinal:  LPDDR3 CA Training Loop 2 \n");
    k510_logd("CA loop2 incr_good_min  = 0x%x,  ", incr_good_min);
    k510_logd("CA loop2 incr_good_max  = 0x%x,  ", incr_good_max);
    //    /////mask for currently k510_logd("incr_good_avg  = 0x%x \n", ((incr_good_min + incr_good_max)/2));

    /* Verify that the CA Training was successful. */
    if(incr_good_min == 99){
        k510_logd("LPDDR3 CA Training Loop 2 Failed! \n");
        return 1;
    }

    /* Step 20a of 23 - LPDDR3 CA Training
       Set ca_cke_low = 0.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata &= ~(0x1 << 18);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 21 of 23 - LPDDR3 CA Training
       Adjust CA SADJ and maximum CA SADJ for matching values.
    */


    /* Step 23 of 23 - LPDDR3 CA Training
       Write DDR PHY Register DLL_CTRL7 with CA SADJ 0,1,2
       average of minimum and maximum result for each.
    */
    uint32_t incr_good_min2 = incr_good_min;
    uint32_t incr_good_max2 = incr_good_max;
//    /////mask for currently k510_logd("=======0x%x  0x%x  0x%x  0x%x \n", incr_good_min1,incr_good_max1,incr_good_min2,incr_good_max2);

    if(incr_good_min1 > incr_good_min2)
        incr_good_min = incr_good_min1;
    else
        incr_good_min = incr_good_min2;

    if(incr_good_max1 < incr_good_max2)
        incr_good_max = incr_good_max1;
    else
        incr_good_max = incr_good_max2;

    k510_logd("Final:  LPDDR3 CA Training  \n");
    k510_logd("incr_good_min1 = 0x%x,  \n", incr_good_min1);
    k510_logd("incr_good_max1 = 0x%x,  \n", incr_good_max1);
    k510_logd("incr_good_min2 = 0x%x,  \n", incr_good_min2);
    k510_logd("incr_good_max2 = 0x%x,  \n", incr_good_max2);
    k510_logd("incr_good_min = 0x%x,  \n", incr_good_min);
    k510_logd("incr_good_max = 0x%x,  \n", incr_good_max);

    //incr_data = ((incr_good_min & 0xff) + (incr_good_max & 0xff))/2;
    // 06/18/2021 eq correction
    incr_data = (((incr_good_min & 0xff) + ((incr_good_max - incr_good_min) & 0xff) / 2));
    regdata = (incr_data & 0xff);
    regdata |= (incr_data & 0xff) << 8;
    regdata |= (incr_data & 0xff) << 16;

//    /////mask for currently k510_logd("incr_data_ave = 0x%x,  \n", incr_data);
    k510_logd("DLL_CTRL7 and ca finish: train data = 0x%x,  \n", regdata);

    write_register(DLL_CTRL7_ADDR, regdata, 1);

    /* Step 22 of 23 - LPDDR3 CA Training
       Initiate the MR42 CA training exit operation by issuing
       to the memory controller Mode Regsier Write to MR42.
    */
    regdata = 0x000000a8;
    if(write_mode_register(42, regdata)){
       k510_logd("write_mode_register return failure, Step 22 of 23 - LPDDR3 CA Training \n");
        return 1;
    }

    // auto refresh enable by hyg
    regdata = read_register(DENALI_CTL_078, 0);
    /* Clear bit 0. */
    bit_set_bit(regdata, 0);
    /* Now write the value back into the register. */
    write_register(DENALI_CTL_078, regdata, 0);

    k510_logi("LPDDR3 CA Training Complete");

    return 0;
}

#if DDR_RE_TRAINING_OLD
uint32_t Read_eye_training(void)
{
    uint32_t regdata = 0;
    uint64_t value = 0;
    int32_t i;

    k510_logd("Begin LPDDR3 Read Eye Training \n");

    /* Step 0 of 29 - LPDDR3 Read Eye Training
       Issue a MR32 Mode Register Read (Pattern A) operation
       to access the predefined pattern registers.
    */
    if(read_mode_register(32, &value)){
        k510_logd("read_mode_register return failure, Step 0 of 29 - LPDDR3 Read Eye Training");
        return 1;
    }

    /* Step 1 of 29 - LPDDR3 Read Eye Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and set
       to 1.
    */
    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 1. */
    regdata |= 0x1 << 17;

    /*  Set SADJ WRT (bit[10]) to 1. */
    regdata |= 0x1 << 10;

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 2 of 29 - LPDDR3 Read Eye Training
       Set READ DQS DLL and READ DQS_B DSS SADJ = 0 using the
       DLL_CTRL registers through the DDR PHY AHB.
    */
    for(i=0;i<4;i++){
        regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

        /*  READ DQS DLL SADJ */
        regdata &= ~(0xff << 24);

        /*  READ DQS_B DLL SADJ */
        regdata &= ~(0xff << 8);

        write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
    }

    /* Step 2a of 29 - LPDDR3 Read Eye Training
       Set extend read gate bits.
    */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);

#if DDR_800
    /* Extend read gate deassertion by 2 clks. */
    regdata |= 0x1 << 29;
    regdata &= ~(0x1 << 28);
    regdata |= 0x1 << 21;
    regdata &= ~(0x1 << 20);
    regdata |= 0x1 << 13;
    regdata &= ~(0x1 << 12);
    regdata |= 0x1 << 5;
    regdata &= ~(0x1 << 4);
#endif

#if DDR_1066
    /* Extend read gate deassertion by 2 clks. */
    regdata |= 0x1 << 29;
    regdata &= ~(0x1 << 28);
    regdata |= 0x1 << 21;
    regdata &= ~(0x1 << 20);
    regdata |= 0x1 << 13;
    regdata &= ~(0x1 << 12);
    regdata |= 0x1 << 5;
    regdata &= ~(0x1 << 4);
#endif

#if DDR_1333
    /* Extend read gate deassertion by 2 clks. */
    regdata |= 0x1 << 29;
    regdata &= ~(0x1 << 28);
    regdata |= 0x1 << 21;
    regdata &= ~(0x1 << 20);
    regdata |= 0x1 << 13;
    regdata &= ~(0x1 << 12);
    regdata |= 0x1 << 5;
    regdata &= ~(0x1 << 4);
#endif

#if DDR_1600
    /* Extend read gate deassertion by 2 clks. */
    regdata |= 0x1 << 29;
    regdata &= ~(0x1 << 28);
    regdata |= 0x1 << 21;
    regdata &= ~(0x1 << 20);
    regdata |= 0x1 << 13;
    regdata &= ~(0x1 << 12);
    regdata |= 0x1 << 5;
    regdata &= ~(0x1 << 4);
#endif

#if DDR_1866
    /* Extend read gate deassertion by 2 clks. */
    regdata |= 0x1 << 29;
    regdata &= ~(0x1 << 28);
    regdata |= 0x1 << 21;
    regdata &= ~(0x1 << 20);
    regdata |= 0x1 << 13;
    regdata &= ~(0x1 << 12);
    regdata |= 0x1 << 5;
    regdata &= ~(0x1 << 4);
#endif

#if DDR_2133
    /* Extend read gate deassertion by 2 clks. */
    regdata |= 0x1 << 29;
    regdata &= ~(0x1 << 28);
    regdata |= 0x1 << 21;
    regdata &= ~(0x1 << 20);
    regdata |= 0x1 << 13;
    regdata &= ~(0x1 << 12);
    regdata |= 0x1 << 5;
    regdata &= ~(0x1 << 4);
#endif
    write_register(RGDLY_ADJ_ADDR, regdata, 1);
    /* Step 3 of 29 - LPDDR3 Read Eye Training
       Start of READ EYE Training Loop 1.
    */
    uint32_t incr_data = 0;
    uint32_t incr_good_min = 99;
    uint32_t incr_good_max = 0;
    uint32_t found_pass = 0;
    uint32_t val_rb[8] = {0,0,0,0,0,0,0,0};


    /////mask for currently k510_logd("Start READ EYE Training Loop 1 \n");

    while(1){
        /* Step 4 of 29 - LPDDR3 Read Eye Training
           Issue MRR MR32 through the controller.
        */
        if(read_mode_register_only(32, &value)){
            k510_logd("read_mode_register_only return failure, Step 4 of 29 - LPDDR3 Read Eye Training \n");
            return 1;
        }

        k510_logd("=====incr_data = 0x%08X    MR32 is %08x====\n", incr_data, value);
        /* Step 5 of 29 - LPDDR3 Read Eye Training
           After RL + RU(tDWSCKMAX/tCK) + 8.2 - WL clock
           cycle, DRAM bursts out the predefined Read
           Calibration Pattern.
        */
        /* Step 6 of 29 - LPDDR3 Read Eye Training
           Ensure that tMRR >= 8.
        */
        //usleep(1);

        /* Verify Interrupt Status RBURST Captured (bit[7]) is
           set to 1.  A 1 indicates the RBURST registers have
           been updated.
        */
        usleep(10);
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(regdata & 0x80)
        {
            /* Interrupt Status RBURST Captured (bit[7]) was
               correctly set to 1.
               Now write 1 to the sticky RBURST Captured (bit[7])
               to clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is
               now cleared to 0.
            */
            if(!(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
            {
             //   k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                if((read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
                {
                    k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0. \n");
                    return 1;
                }
            }
        }
        else
        {
            k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return 1;
        }

        /* Step 7 of 29 - LPDDR3 Read Eye Training
           Read AHB Registers RBURST_0/1_P0/1/2/3 and Compare
           to Pattern A.
        */
        for(i=0;i<8;i++)
        {
            val_rb[i] = read_register(RBURST_0_P0_ADDR + i*4, 1);
            k510_logd("Loop1 >>>>    val_rb[%d] = 0x%08X\n", i, val_rb[i]);
        }

        /*  First read the value of the TRAINING_CTRL1 register. */
        /*  Check if CRDB (bit[17] has been cleared. */
        if(!(read_register(TRAINING_CTRL1_ADDR, 1) & (0x1 << 17))){
            if((val_rb[0] == 0xffffffff) && \
               (val_rb[1] == 0x00000000) && \
               (val_rb[2] == 0xffffffff) && \
               (val_rb[3] == 0x00000000) && \
               (val_rb[4] == 0xffffffff) && \
               (val_rb[5] == 0x00000000) && \
               (val_rb[6] == 0xffffffff) && \
               (val_rb[7] == 0x00000000)){

                if(incr_data < incr_good_min){
                    incr_good_min  = incr_data;
                    found_pass = 1;
                }

                if(incr_data > incr_good_max)
                    incr_good_max  = incr_data;

             }
             else{
                 if(found_pass == 1)
                     break;
             }
        }

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb[0]);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb[1]);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb[2]);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb[3]);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb[4]);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb[5]);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb[6]);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb[7]);

        /* Step 8 of 29 - LPDDR3 Read Eye Training
           Continue READ EYE Training Calibration Loop 1 by
           incrementing the values of READ DQS DLL SADJ and
           READ DQS_B SADJ until SADJ = max value, when max
           value is arrived at, end Training Loop.
        */

        if(incr_data < 72){
            incr_data += 1;

            for(i=0;i<4;i++){
                regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

                /*  READ DQS DLL SADJ */
                regdata &= ~(0xff << 24);
                regdata |= (incr_data & 0xff) << 24;

                /*  READ DQS_B DLL SADJ */
                regdata &= ~(0xff << 8);
                regdata |= (incr_data & 0xff) << 8;

                write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
                k510_logd("Loop1 >>>>    DLL_CTRL%d_ADDR  0x%08X\n", i+2, regdata);
                k510_loge("Loop1 >>>>    DLL_CTRL%d_ADDR  0x%08X\n", i+2, read_register(DLL_CTRL2_ADDR + i*4, 1));
            }

            /* Step 8b = Repeat Step 1
               Step 1 of 29 - LPDDR3 Read Eye Training
               Write AHB Register TRAINING_CTRL1 SADJ_WRT and ",
               set to 1.
            */
            /*  First read the value of the TRAINING_CTRL1 register. */
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);

            /*  Set CRDB (bit[17] to 1. */
            regdata |= 0x1 << 17;

            /*  Set SADJ WRT (bit[10]) to 1. */
            regdata |= 0x1 << 10;

            /*  Now write the new value to the TRAINING_CTRL1 register. */
            write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        }
        else
            break;

    }

    /////mask for currently k510_logd("Final:  LPDDR3 Read Eye Training Loop 1  \n");
    k510_logd("loop1 incr_good_min  = 0x%x \n", incr_good_min);
    k510_logd("loop1 incr_good_max  = 0x%x \n", incr_good_max);
    /////mask for currently k510_logd("incr_good_avg  = 0x%x \n", ((incr_good_min + incr_good_max)/2));


    /*  Verify that the Read Eye Training was successful. */
    if(incr_good_min == 99){
        k510_logd("ERR : LPDDR3 Read Eye Training Loop 1 Failed!\n");
        return 1;
    }

    /* Step 9 of 29 - LPDDR3 Read Eye Training
       Set READ DQS_B DLL SADJ = AVG of MIN and MAX Pass
       values from Training Loop 1.
    */

    /* Step 10 of 29 - LPDDR3 Read Eye Training
       Set READ DQS DLL SADJ = 0 using the DLL_CTRL2,3,4,5
       registers through the DDR PHY AHB.
    */
    /*  Perform Step 9 and Step 10 at the same time. */

    for(i=0;i<4;i++){
        regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

        /*  READ DQS DLL SADJ */
        regdata &= ~(0xff << 24);

        /*  READ DQS_B DLL SADJ */
        regdata &= ~(0xff << 8);
        //regdata |= (((incr_good_min + incr_good_max)/2) & 0xff) << 8;
        // 06/08/2021 eq correction
        regdata |= ((incr_good_min + (incr_good_max - incr_good_min)/2) & 0xff) <<8;

        write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
        k510_logd("Loop1 over >>>> DLL_CTRL%d_ADDR  0x%08X\n", i + 2, regdata);
    }

    /* Make sure CRDB bit is cleared before starting the next
       training loop..
    */
    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 0. */
//    regdata &= ~(0x1 << 17);
//    /*added 2*/
    regdata |= 0x1 << 17;

    /*  Set SADJ WRT (bit[10]) to 0. */
    regdata &= ~(0x1 << 10);

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 11 of 29 - LPDDR3 Read Eye Training
       Start of READ EYE Training Loop 2.
    */

    /* Step 11b = Repeat Step 1
       Step 1 of 29 - LPDDR3 Read Eye Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and
       set to 1.
    */

    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 1. */
    regdata |= 0x1 << 17;

    /*  Set SADJ WRT (bit[10]) to 1. */
    regdata |= 0x1 << 10;

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);


    incr_data = 10;
    // incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    /////mask for currently k510_logd("READ EYE Training Loop 2 \n");

    while(1){
        /* Step 12 of 29 - LPDDR3 Read Eye Training
           Issue MRR MR32 through the controller.
        */
        if(read_mode_register_only(32, &value)){
            k510_logd("read_mode_register_only return failure, \
                Step 12 of 29 - LPDDR3 Read Eye Training \n");
            return 1;
        }

        k510_logd("=====incr_data = 0x%08X    MR32 is %08x====\n", incr_data, value);
        /* Step 13 of 29 - LPDDR3 Read Eye Training
           After RL + RU(tDQSCKMAX/tCK) + 8.2 + 1 - WL clock
           cycles, DRAM bursts out the predefined Read
           Calibration Pattern.
        */
        /* Step 14 of 29 - LPDDR3 Read Eye Training
           Ensure that tMRR > 8.
        */
        //usleep(1);

        /* Verify Interrupt Status RBURST Captured (bit[7]) is
           set to 1.  A 1 indicates the RBURST registers have
           been updated.
        */
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        if(regdata & 0x80){
            /* Interrupt Status RBURST Captured (bit[7]) was
               correctly set to 1.
               Now write 1 to the sticky RBURST Captured (bit[7])
               to clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is
               now cleared to 0.
            */
            if(!(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
             {} /////mask for currently k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            else{
            if((read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80)){
                k510_logd("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
                return 1;
             }
            }
        }
        else{
            k510_logd("ERR1: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            k510_logi("RG_TRAIN_ERR : 0x%X\n", (read_register(TRAINING_CTRL1_ADDR, 1) >> 24) & 0xf);
            return 1;
        }

        /* Step 15 of 29 - LPDDR3 Read Eye Training
           Read AHB Registers RBURST_0/1_P0/1/2/3 and Compare
           to Pattern A.
        */
        for(i=0;i<8;i++)
        {
            val_rb[i] = read_register(RBURST_0_P0_ADDR + i*4, 1);
            k510_logd("Loop2 >>>>    val_rb[%d] = 0x%08X\n", i, val_rb[i]);
        }

        /*  First read the value of the TRAINING_CTRL1 register. */
        /*  Check if CRDB (bit[17] has been cleared. */
        if(!(read_register(TRAINING_CTRL1_ADDR, 1) & (0x1 << 17))){
            if((val_rb[0] == 0xffffffff) && \
               (val_rb[1] == 0x00000000) && \
               (val_rb[2] == 0xffffffff) && \
               (val_rb[3] == 0x00000000) && \
               (val_rb[4] == 0xffffffff) && \
               (val_rb[5] == 0x00000000) && \
               (val_rb[6] == 0xffffffff) && \
               (val_rb[7] == 0x00000000)){

                if(incr_data < incr_good_min){
                    incr_good_min  = incr_data;
                    found_pass = 1;
                }

                if(incr_data > incr_good_max)
                    incr_good_max  = incr_data;

             }
             else{
                 if(found_pass == 1)
                     break;
             }
        }

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb[0]);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb[1]);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb[2]);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb[3]);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb[4]);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb[5]);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb[6]);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb[7]);

        /* Step 16 of 29 - LPDDR3 Read Eye Training
           Continue READ EYE Training Calibration Loop by
           incrementing the values of READ DQS DLL SADJ until
           SADJ = max value, when max value is arrived at
           end Training Loop.
        */

        if(incr_data < 72){
            incr_data += 1;

            for(i=0;i<4;i++){
                regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

                /*  READ DQS DLL SADJ */
                regdata &= ~(0xff << 24);
                regdata |= (incr_data & 0xff) << 24;

                /*  READ DQS_B DLL SADJ */
                //regdata |= (incr_data & 0xff) << 8;

                write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
                k510_logd("Loop2 >>>>    DLL_CTRL%d_ADDR  0x%08X\n", i + 2, regdata);
            }

            /* Step 16b = Repeat Step 1
               Step 1 of 29 - LPDDR3 Read Eye Training
               Write AHB Register TRAINING_CTRL1 SADJ_WRT and ",
               set to 1.
            */
            /*  First read the value of the TRAINING_CTRL1 register. */
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);

            /*  Set CRDB (bit[17] to 1. */
            regdata |= 0x1 << 17;

            /*  Set SADJ WRT (bit[10]) to 1. */
            regdata |= 0x1 << 10;

            /*  Now write the new value to the TRAINING_CTRL1 register. */
            write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        }
        else
            break;

    } // while (continue_loop == 1'b1)

    /////mask for currently k510_logd("Final:  LPDDR3 Read Eye Training Loop 2  \n");
     k510_logd("loop2 incr_good_min  = 0x%x  \n", incr_good_min);
     k510_logd("loop2 incr_good_max  = 0x%x  \n", incr_good_max);
    /////mask for currently k510_logd("incr_good_avg  = 0x%x  \n", ((incr_good_min + incr_good_max)/2));

    /*  Verify that the Read Eye Training was successful. */
    if(incr_good_min == 99){
        k510_logd("ERR: LPDDR3 Read Eye Training Loop 2 Failed! \n");
        return 1;
    }

    /* Step 17 of 29 - LPDDR3 Read Eye Training
       Set READ DQS DLL SADJ = AVG of MIN and MAX Pass
       values from Training Loop 2.
    */

    /* Step 18 of 29 - LPDDR3 Read Eye Training
       Set READ DQS DLL SADJ = AVG of MIN and MAX Pass
       values from Training Loop 2.
    */

    /* Step 19 of 29 - LPDDR3 Read Eye Training
       Set READ DQS_B DLL SADJ = 0 using the DLL_CTRL2,3,4,5
       registers through the DDR PHY AHB.
    */

    /*  Perform Step 18 and Step 19 at the same time. */

    for(i=0;i<4;i++){
        regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

        /*  READ DQS DLL SADJ */
        regdata &= ~(0xff << 24);
        //regdata |= (((incr_good_min + incr_good_max)/2) & 0xff) << 24;
        // 06/18/2021 eq correction
        regdata |= ((incr_good_min + (incr_good_max - incr_good_min) / 2) & 0xff) <<24;

        /*  READ DQS_B DLL SADJ */
        regdata &= ~(0xff << 8);

        write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
        k510_logi("Loop2 over >>>> DLL_CTRL%d_ADDR 0x%08X\n", i + 2, regdata);
    }

    /* Make sure CRDB bit is cleared before starting the next
       training loop..
    */
    /*  First read the value of the TRAINING_CTRL1 register. */

    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 0. */
//    regdata &= ~(0x1 << 17);
//    /*added 2*/
    regdata |= 0x1 << 17;

    /*  Set SADJ WRT (bit[10]) to 0. */
    regdata &= ~(0x1 << 10);

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 20 of 29 - LPDDR3 Read Eye Training
       Start of READ EYE Training Loop 3.
    */

    /* Step 20b = Repeat Step 1
       Step 1 of 29 - LPDDR3 Read Eye Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and
       set to 1.
    */
    /*  First read the value of the TRAINING_CTRL1 register */

    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 1. */
    regdata |= 0x1 << 17;

    /*  Set SADJ WRT (bit[10]) to 1. */
    regdata |= 0x1 << 10;

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    incr_data = 10;
    // incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    /////mask for currently k510_logd("READ EYE Training Loop 3 \n");

    while(1)
    {
        /* Step 21 of 29 - LPDDR3 Read Eye Training
           Issue MRR MR32 through the controller.
        */
        if(read_mode_register_only(32, &value)){
            k510_logd("read_mode_register_only return failure, \
                       Step 21 of 29 - LPDDR3 Read Eye Training \n");
            return 1;
        }

        k510_logd("=====incr_data = 0x%08X    MR32 is %08x====\n", incr_data, value);
        /* Step 22 of 29 - LPDDR3 Read Eye Training
           After RL + RU(tDQSCKMAX/tCK) + 8.2 + 1 - WL clock
           cycles, DRAM bursts out the predefined Read
           Calibration Pattern.
        */
        /* Step 23 of 29 - LPDDR3 Read Eye Training
           Ensure that tMRR > 8.
        */
        //usleep(1);

        /* Verify Interrupt Status RBURST Captured (bit[7]) is
           set to 1.  A 1 indicates the RBURST registers have
           been updated.
        */
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        if(regdata & 0x80){
            /* Interrupt Status RBURST Captured (bit[7]) was
               correctly set to 1.
               Now write 1 to the sticky RBURST Captured (bit[7])
               to clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is
               now cleared to 0.
            */
            if(!(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
            {}
                /////mask for currently k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            else{
                k510_logd("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
                return 1;
             }
        }
          else{
            k510_logd("ERR2: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            k510_logi("RG_TRAIN_ERR : 0x%X\n", (read_register(TRAINING_CTRL1_ADDR, 1) >> 24) & 0xf);
            return 1;
        }

        /* Step 24 of 29 - LPDDR3 Read Eye Training
           Read AHB Registers RBURST_0/1_P0/1/2/3 and Compare
           to Pattern A.
        */
        for(i=0;i<8;i++)
            val_rb[i] = read_register(RBURST_0_P0_ADDR + i*4, 1);

        /*  First read the value of the TRAINING_CTRL1 register. */
        /*  Check if CRDB (bit[17] has been cleared. */
        if(!(read_register(TRAINING_CTRL1_ADDR, 1) & (0x1 << 17))){
            if((val_rb[0] == 0xffffffff) && \
               (val_rb[1] == 0x00000000) && \
               (val_rb[2] == 0xffffffff) && \
               (val_rb[3] == 0x00000000) && \
               (val_rb[4] == 0xffffffff) && \
               (val_rb[5] == 0x00000000) && \
               (val_rb[6] == 0xffffffff) && \
               (val_rb[7] == 0x00000000)){

                if(incr_data < incr_good_min){
                    incr_good_min  = incr_data;
                    found_pass = 1;
                }

                if(incr_data > incr_good_max)
                    incr_good_max  = incr_data;

             }
             else{
                 if(found_pass == 1)
                     break;
             }
        }

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb[0]);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb[1]);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb[2]);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb[3]);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb[4]);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb[5]);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb[6]);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb[7]);

        /* Step 25 of 29 - LPDDR3 Read Eye Training
           Continue READ EYE Training Calibration Loop by
           incrementing the values of READ DQS_B DLL SADJ until
           SADJ = max value, when max value is arrived at
           end Training Loop.
        */

        if(incr_data < 72)
        {
            incr_data += 1;

            for(i=0;i<4;i++){
                regdata = read_register(DLL_CTRL2_ADDR + i*4,  1);

                /*  READ DQS DLL SADJ */
                //regdata |= (incr_data & 0xff) << 24;

                /*  READ DQS_B DLL SADJ */
                regdata &= ~(0xff << 8);
                regdata |= (incr_data & 0xff) << 8;

                write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
                k510_logd("Loop3 >>>>    DLL_CTRL%d_ADDR  0x%08X\n", i + 2, regdata);
            }

            /* Step 25b = Repeat Step 1
               Step 1 of 29 - LPDDR3 Read Eye Training
               Write AHB Register TRAINING_CTRL1 SADJ_WRT and ",
               set to 1.
            */
            /*  First read the value of the TRAINING_CTRL1 register. */
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);

            /*  Set CRDB (bit[17] to 1. */
            regdata |= 0x1 << 17;

            /*  Set SADJ WRT (bit[10]) to 1. */
            regdata |= 0x1 << 10;

            /*  Now write the new value to the TRAINING_CTRL1 register. */
            write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        }
        else
            break;


    } // while (continue_loop == 1'b1)

    /////mask for currently k510_logd("Final:  LPDDR3 Read Eye Training Loop 3  \n");
    /////mask for currently k510_logd("incr_good_min  = 0x%x  \n", incr_good_min);
    /////mask for currently k510_logd("incr_good_max  = 0x%x  \n", incr_good_max);
    /////mask for currently k510_logd("incr_good_avg  = 0x%x  \n", ((incr_good_min + incr_good_max)/2));

    /*  Verify that the Read Eye Training was successful. */
    if(incr_good_min == 99){
        k510_logd("ERR: LPDDR3 Read Eye Training Loop 3 Failed! \n");
        return 1;
    }

    k510_logd("loop3 incr_good_min  = 0x%x \n", incr_good_min);
    k510_logd("loop3 incr_good_max  = 0x%x \n", incr_good_max);

    /* Step 26 of 29 - LPDDR3 Read Eye Training
       Set READ DQS_B DLL SADJ = AVG of MIN and MAX Pass
       values from Training Loop 3.
    */
    for(i=0;i<4;i++){
        regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

        /*  READ DQS DLL SADJ */
        //regdata &= ~(0xff<< 24);

        /*  READ DQS_B DLL SADJ */
        regdata &= ~(0xff<< 8);
        //regdata |= (((incr_good_min + incr_good_max)/2) & 0xff)<< 8;
        // 06/18/2021 eq correction
        regdata |= ((incr_good_min + (incr_good_max - incr_good_min)/2) & 0xff) <<8;
        k510_logi("     ====dll_ctrl info: %08x",regdata);
        // regdata = regdata - 0x0a000a00;         // sub a?
        // k510_logci("==Sub 0xa ====dll_ctrl info: %08x",regdata);
#if DDR_1333
        // k510_logd("regdata result  = 0x%x \n", regdata);
        // regdata = regdata - 0x06000600;
        // k510_logd("regdata after reduce  = 0x%x \n", regdata);
#endif
        write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
        k510_logi("Loop3 over >>>> DLL_CTRL%d_ADDR 0x%08X\n", i + 2, regdata);
    }

    /* Step 27 of 29 - LPDDR3 Read Eye Training
       After end of last MRR read burst, wait until
       tWR + TRPpb is satisfied.
    */

    /* Step 28 of 29 - LPDDR3 Read Eye Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and
       set to 0.
    */
    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 0. */
    regdata &= ~(0x1 << 17);

    /*  Set SADJ WRT (bit[10]) to 0. */
    regdata &= ~(0x1 << 10);

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);


    /*  The following is not one of the steps, I added
        it to show the final SADJ values.
    */

     k510_logd("DLL_CTRL2 = 0x%x \n", read_register(DLL_CTRL2_ADDR, 1));
     k510_logd("DLL_CTRL3 = 0x%x \n", read_register(DLL_CTRL3_ADDR, 1));
     k510_logd("DLL_CTRL4 = 0x%x \n", read_register(DLL_CTRL4_ADDR, 1));
     k510_logd("DLL_CTRL5 = 0x%x \n", read_register(DLL_CTRL5_ADDR, 1));

     k510_logd("LPDDR3 Read Eye Complete \n");

     /* Step 29 of 29 - LPDDR3 Read Eye Training
        Continue with regular DRAM commands.
     */
     return 0;
}
#endif

#if DDR_RE_TRAINING_NEW
uint32_t Read_eye_training(void)
{
    uint32_t regdata = 0;
    uint64_t value = 0;
    // int32_t i;
    // cache_enable();

    k510_logi("Begin LPDDR3 Read Eye Training  "
              "w/o Bit Deskew or VREF Training\n");

    /* Step 0 of 29 - LPDDR3 Read Eye Training
    Issue a MR32 Mode Register Read (Pattern A) operation
    to access the predefined pattern registers.
    */
    if(read_mode_register(32, &value)){
        k510_logd("read_mode_register return failure, Step 0 of 29 - LPDDR3 Read Eye Training");
        return 1;
    }

    k510_logv(
        "Step 0 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Issue an AXI READ of Address location 0 (note this "
        "location has been pre-written with a known value at "
        "low frequency prior to this operation.\n"
    );
    // memory_read(mem_addr, mem_rdata, .compare(0)); /* What's this ? */
    // memcpy((void *)mem_rdata, mem_addr, MEM_BYTE_CNT);
    // mem_rdata[0] = *(mem_addr);
    // mem_rdata[1] = *(mem_addr + 1);
    // mem_rdata[2] = *(mem_addr + 2);
    // mem_rdata[3] = *(mem_addr + 3);

    // cache_inval(0, 0, 128, L1_DCACHE);

    // for(uint32_t i = 0; i < 32; i++)
    // {
    //     mem_rdata[i] = *(mem_addr + i);
    // }

    k510_logv(
        "Step 1 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set DFI frequency = 800 MHz for Memory operation "
        "of 3200Mbs.\n"
    );

    k510_logv(
        "Step 2 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_set_bit(regdata, 17);
    bit_set_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 3 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set READ DQS DLL and READ DQS_B DLL SADJ=0 using the "
        "DLL_CTRL registers through the DDR PHY AHB. \n"
        "a. DLL_CTRL2 affects Data Slice 0\n"
        "b. DLL_CTRL3 affects Data Slice 1\n"
        "c. DLL_CTRL4 affects Data Slice 2\n"
        "d. DLL_CTRL5 affects Data Slice 3\n"
    );
    set_read_dqs_sadj(0,0,0,0);         /* function is OK? zzx */
    set_read_dqs_b_sadj(0,0,0,0);

    /* Starting with all bit delays at 0 */
    // write_register(BIT_RDLY_DS0_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS0_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0x00FFFFFF, 1);

    k510_logv(
        "Step 4 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set extend read gate bits.\n"
    );

    /* Extend read gate deassertion by 2 clks. */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);   // shorten the extension
    bit_set_field(regdata, 2, 28, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 20, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 12, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 4,  DDR_READ_GATE_DELAY_DEASSERTION);
    // bit_set_field(regdata, 2, 28, 0x3);
    // bit_set_field(regdata, 2, 20, 0x3);
    // bit_set_field(regdata, 2, 12, 0x3);
    // bit_set_field(regdata, 2, 4,  0x3);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    cval_rb_0_p0 = 0xffffffff;
    cval_rb_0_p1 = 0x00000000;
    cval_rb_0_p2 = 0xffffffff;
    cval_rb_0_p3 = 0x00000000;
    cval_rb_1_p0 = 0xffffffff;
    cval_rb_1_p1 = 0x00000000;
    cval_rb_1_p2 = 0xffffffff;
    cval_rb_1_p3 = 0x00000000;

    k510_logi("---------------- %s Loop1 start ----------------\n", __func__);
    k510_logv(
        "Step 5 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 1 "
        "(find center of EYE for DQS/DQS_B).\n"
    );
    incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 1 :  single cycle start *****************\n");

        /* Step 4 of 29 - LPDDR3 Read Eye Training
           Issue MRR MR32 through the controller.
        */
        if(read_mode_register_only(32, &value)){
            k510_logd("read_mode_register_only return failure, Step 4 of 29 - LPDDR3 Read Eye Training \n");
            return 1;
        }

        k510_logd("=====incr_data = 0x%08X    MR32 is %08x====\n", incr_data, value);

        /* Verify Interrupt Status RBURST Captured (bit[7]) is
           set to 1.  A 1 indicates the RBURST registers have
           been updated.
        */
        usleep(10);
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(regdata & 0x80)
        {
            /* Interrupt Status RBURST Captured (bit[7]) was
               correctly set to 1.
               Now write 1 to the sticky RBURST Captured (bit[7])
               to clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is
               now cleared to 0.
            */
            if(!(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
            {
             //   k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                if((read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
                {
                    k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0. \n");
                    return 1;
                }
            }
        }
        else
        {
            k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return 1;
        }

        // k510_logv(
        //     "Step 6 of 28 for LPDDR3 Read Eye Training "
        //     "w/o Bit Deskew or VREF Training\n"
        //     "Issue an AXI READ of address location 0 to access "
        //     "known data pattern.\n"
        // );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        // for(uint32_t i = 0; i < 32; i++)
        // {
        //     mem_rdata[i] = *(mem_addr + i);
        // }

        // k510_logv(
        //     "Step 7 of 28 for LPDDR3 Read Eye Training "
        //     "w/o Bit Deskew or VREF Training\n"
        //     "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare to "
        //     "pattern A. "
        //     "Save pass/fail results.\n"
        // );

        // /* read the value of the TRAINING_CTRL1 register. */
        // regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        // while(bit_check_bit(regdata, 17) != 0)
        // {
        //     regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        // }

        // k510_logv(
        //     "Verify Interrupt Status RBURST Captured (bit[7]) is "
        //     "set to 1.  A 1 indicates the RBURST registers have "
        //     "been updated.\n"
        // );
        // regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        // if(bit_check_bit(regdata, 7))
        // {
        //     k510_logv(
        //         "Interrupt Status RBURST Captured (bit[7]) was "
        //         "correctly set to 1.\n"
        //         "Now write 1 to the sticky RBURST Captured (bit[7]) "
        //         "to clear it.\n"
        //     );
        //     write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

        //     /* Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0. */
        //     regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        //     if(bit_check_bit(regdata, 7) == 0)
        //     {
        //         k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
        //     }
        //     else
        //     {
        //         k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
        //         return -1;
        //     }
        // }
        // else
        // {
        //     k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
        //     return -1;
        // }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(val_rb_0_p0, 8, 0) == bit_get_field(cval_rb_0_p0, 8, 0)) &&
                (bit_get_field(val_rb_0_p1, 8, 0) == bit_get_field(cval_rb_0_p1, 8, 0)) &&
                (bit_get_field(val_rb_0_p2, 8, 0) == bit_get_field(cval_rb_0_p2, 8, 0)) &&
                (bit_get_field(val_rb_0_p3, 8, 0) == bit_get_field(cval_rb_0_p3, 8, 0)) &&
                (bit_get_field(val_rb_1_p0, 8, 0) == bit_get_field(cval_rb_1_p0, 8, 0)) &&
                (bit_get_field(val_rb_1_p1, 8, 0) == bit_get_field(cval_rb_1_p1, 8, 0)) &&
                (bit_get_field(val_rb_1_p2, 8, 0) == bit_get_field(cval_rb_1_p2, 8, 0)) &&
                (bit_get_field(val_rb_1_p3, 8, 0) == bit_get_field(cval_rb_1_p3, 8, 0))
            )
            {
                k510_logd("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 8) == bit_get_field(cval_rb_0_p0, 8, 8)) &&
                (bit_get_field(val_rb_0_p1, 8, 8) == bit_get_field(cval_rb_0_p1, 8, 8)) &&
                (bit_get_field(val_rb_0_p2, 8, 8) == bit_get_field(cval_rb_0_p2, 8, 8)) &&
                (bit_get_field(val_rb_0_p3, 8, 8) == bit_get_field(cval_rb_0_p3, 8, 8)) &&
                (bit_get_field(val_rb_1_p0, 8, 8) == bit_get_field(cval_rb_1_p0, 8, 8)) &&
                (bit_get_field(val_rb_1_p1, 8, 8) == bit_get_field(cval_rb_1_p1, 8, 8)) &&
                (bit_get_field(val_rb_1_p2, 8, 8) == bit_get_field(cval_rb_1_p2, 8, 8)) &&
                (bit_get_field(val_rb_1_p3, 8, 8) == bit_get_field(cval_rb_1_p3, 8, 8))
            )
            {
                k510_logd("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 16) == bit_get_field(cval_rb_0_p0, 8, 16)) &&
                (bit_get_field(val_rb_0_p1, 8, 16) == bit_get_field(cval_rb_0_p1, 8, 16)) &&
                (bit_get_field(val_rb_0_p2, 8, 16) == bit_get_field(cval_rb_0_p2, 8, 16)) &&
                (bit_get_field(val_rb_0_p3, 8, 16) == bit_get_field(cval_rb_0_p3, 8, 16)) &&
                (bit_get_field(val_rb_1_p0, 8, 16) == bit_get_field(cval_rb_1_p0, 8, 16)) &&
                (bit_get_field(val_rb_1_p1, 8, 16) == bit_get_field(cval_rb_1_p1, 8, 16)) &&
                (bit_get_field(val_rb_1_p2, 8, 16) == bit_get_field(cval_rb_1_p2, 8, 16)) &&
                (bit_get_field(val_rb_1_p3, 8, 16) == bit_get_field(cval_rb_1_p3, 8, 16))
            )
            {
                k510_logd("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 24) == bit_get_field(cval_rb_0_p0, 8, 24)) &&
                (bit_get_field(val_rb_0_p1, 8, 24) == bit_get_field(cval_rb_0_p1, 8, 24)) &&
                (bit_get_field(val_rb_0_p2, 8, 24) == bit_get_field(cval_rb_0_p2, 8, 24)) &&
                (bit_get_field(val_rb_0_p3, 8, 24) == bit_get_field(cval_rb_0_p3, 8, 24)) &&
                (bit_get_field(val_rb_1_p0, 8, 24) == bit_get_field(cval_rb_1_p0, 8, 24)) &&
                (bit_get_field(val_rb_1_p1, 8, 24) == bit_get_field(cval_rb_1_p1, 8, 24)) &&
                (bit_get_field(val_rb_1_p2, 8, 24) == bit_get_field(cval_rb_1_p2, 8, 24)) &&
                (bit_get_field(val_rb_1_p3, 8, 24) == bit_get_field(cval_rb_1_p3, 8, 24))
            )
            {
                k510_logd("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else // is it right ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);

        k510_logv(
            "Step 8 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop 1 by "
            "incrementing the values of READ DQS DLL SADJ and "
            "READ DQS_B SADJ until SADJ = max value.  End "
            "Training Loop 1 when max value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 1: incr_data is %d\n", __func__, incr_data);
        read_dqs_sadj = incr_data;
        read_dqs_b_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0));
            set_read_dqs_b_sadj(bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0));
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }

        k510_logv(
            "Step 8b = Repeat Step 1\n"
            "Step 1 of 29 - LPDDR3 Read Eye Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logd("**************** Loop 1 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 1 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 1 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 9 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 10 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 1.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg,incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1,incr_good_avg0); //avg3 -> avg0 invert avg0 -> avg3 ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);
    k510_logi("---------------- %s Loop1 end ----------------\n", __func__);
    k510_logi("---------------- %s Loop2 start ----------------\n", __func__);
    k510_logv(
        "Step 11 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB.\n"
    );
    set_read_dqs_sadj(0,0,0,0);

    k510_logv(
        "Step 12 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 2 (find center of "
        "EYE for DQS while holding DQS_B fixed).\n"
    );

    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop  = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 2 :  single cycle start *****************\n");
        k510_logv(
            "Step 13 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 register. */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);
        /* Step 4 of 29 - LPDDR3 Read Eye Training
           Issue MRR MR32 through the controller.
        */
        if(read_mode_register_only(32, &value)){
            k510_logd("read_mode_register_only return failure, Step 4 of 29 - LPDDR3 Read Eye Training \n");
            return 1;
        }

        k510_logd("=====incr_data = 0x%08X    MR32 is %08x====\n", incr_data, value);
        /* Step 5 of 29 - LPDDR3 Read Eye Training
           After RL + RU(tDWSCKMAX/tCK) + 8.2 - WL clock
           cycle, DRAM bursts out the predefined Read
           Calibration Pattern.
        */
        /* Step 6 of 29 - LPDDR3 Read Eye Training
           Ensure that tMRR >= 8.
        */
        //usleep(1);

        /* Verify Interrupt Status RBURST Captured (bit[7]) is
           set to 1.  A 1 indicates the RBURST registers have
           been updated.
        */
        usleep(10);
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(regdata & 0x80)
        {
            /* Interrupt Status RBURST Captured (bit[7]) was
               correctly set to 1.
               Now write 1 to the sticky RBURST Captured (bit[7])
               to clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is
               now cleared to 0.
            */
            if(!(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
            {
             //   k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                if((read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
                {
                    k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0. \n");
                    return 1;
                }
            }
        }
        else
        {
            k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return 1;
        }
        // k510_logv(
        //     "Step 14 of 28 for LPDDR3 Read Eye Training "
        //     "w/o Bit Deskew or VREF Training\n"
        //     "Issue and AXI READ of address location 0 to access "
        //     "known data pattern.\n"
        // );
        // // memory_read(mem_addr, mem_rdata, .compare(0));
        // for(uint32_t i = 0; i < 32; i++)
        // {
        //     mem_rdata[i] = *(mem_addr + i);
        // }

        // k510_logv(
        //     "Step 15 of 28 for LPDDR3 Read Eye Training "
        //     "w/o Bit Deskew or VREF Training\n"
        //     "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare "
        //     "to pattern A. "
        //     "Save pass/fail results.\n"
        // );

        // /* read the value of the TRAINING_CTRL1 register. */
        // regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        // while(bit_check_bit(regdata, 17) != 0)
        // {
        //     regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        // }

        // k510_logv(
        //     "Verify Interrupt Status RBURST Captured (bit[7]) is "
        //     "set to 1.  A 1 indicates the RBURST registers have "
        //     "been updated.\n"
        // );
        // regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        // if(bit_check_bit(regdata, 7))
        // {
        //     k510_logv(
        //         "Interrupt Status RBURST Captured (bit[7]) was "
        //         "correctly set to 1.\n"
        //         "Now write 1 to the sticky RBURST Captured (bit[7]) "
        //         "to clear it.\n"
        //     );
        //     write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

        //     k510_logv("Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0.\n");

        //     regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        //     if(bit_check_bit(regdata, 7) == 0)
        //     {
        //         k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
        //     }
        //     else
        //     {
        //         k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
        //         return -1;
        //     }
        // }
        // else
        // {
        //     k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1\n");
        //     return -1;
        // }


        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(val_rb_0_p0, 8, 0) == bit_get_field(cval_rb_0_p0, 8, 0)) &&
                (bit_get_field(val_rb_0_p1, 8, 0) == bit_get_field(cval_rb_0_p1, 8, 0)) &&
                (bit_get_field(val_rb_0_p2, 8, 0) == bit_get_field(cval_rb_0_p2, 8, 0)) &&
                (bit_get_field(val_rb_0_p3, 8, 0) == bit_get_field(cval_rb_0_p3, 8, 0)) &&
                (bit_get_field(val_rb_1_p0, 8, 0) == bit_get_field(cval_rb_1_p0, 8, 0)) &&
                (bit_get_field(val_rb_1_p1, 8, 0) == bit_get_field(cval_rb_1_p1, 8, 0)) &&
                (bit_get_field(val_rb_1_p2, 8, 0) == bit_get_field(cval_rb_1_p2, 8, 0)) &&
                (bit_get_field(val_rb_1_p3, 8, 0) == bit_get_field(cval_rb_1_p3, 8, 0))
            )
            {
                k510_logv("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 8) == bit_get_field(cval_rb_0_p0, 8, 8)) &&
                (bit_get_field(val_rb_0_p1, 8, 8) == bit_get_field(cval_rb_0_p1, 8, 8)) &&
                (bit_get_field(val_rb_0_p2, 8, 8) == bit_get_field(cval_rb_0_p2, 8, 8)) &&
                (bit_get_field(val_rb_0_p3, 8, 8) == bit_get_field(cval_rb_0_p3, 8, 8)) &&
                (bit_get_field(val_rb_1_p0, 8, 8) == bit_get_field(cval_rb_1_p0, 8, 8)) &&
                (bit_get_field(val_rb_1_p1, 8, 8) == bit_get_field(cval_rb_1_p1, 8, 8)) &&
                (bit_get_field(val_rb_1_p2, 8, 8) == bit_get_field(cval_rb_1_p2, 8, 8)) &&
                (bit_get_field(val_rb_1_p3, 8, 8) == bit_get_field(cval_rb_1_p3, 8, 8))
            )
            {
                k510_logv("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 16) == bit_get_field(cval_rb_0_p0, 8, 16)) &&
                (bit_get_field(val_rb_0_p1, 8, 16) == bit_get_field(cval_rb_0_p1, 8, 16)) &&
                (bit_get_field(val_rb_0_p2, 8, 16) == bit_get_field(cval_rb_0_p2, 8, 16)) &&
                (bit_get_field(val_rb_0_p3, 8, 16) == bit_get_field(cval_rb_0_p3, 8, 16)) &&
                (bit_get_field(val_rb_1_p0, 8, 16) == bit_get_field(cval_rb_1_p0, 8, 16)) &&
                (bit_get_field(val_rb_1_p1, 8, 16) == bit_get_field(cval_rb_1_p1, 8, 16)) &&
                (bit_get_field(val_rb_1_p2, 8, 16) == bit_get_field(cval_rb_1_p2, 8, 16)) &&
                (bit_get_field(val_rb_1_p3, 8, 16) == bit_get_field(cval_rb_1_p3, 8, 16))
            )
            {
                k510_logv("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 24) == bit_get_field(cval_rb_0_p0, 8, 24)) &&
                (bit_get_field(val_rb_0_p1, 8, 24) == bit_get_field(cval_rb_0_p1, 8, 24)) &&
                (bit_get_field(val_rb_0_p2, 8, 24) == bit_get_field(cval_rb_0_p2, 8, 24)) &&
                (bit_get_field(val_rb_0_p3, 8, 24) == bit_get_field(cval_rb_0_p3, 8, 24)) &&
                (bit_get_field(val_rb_1_p0, 8, 24) == bit_get_field(cval_rb_1_p0, 8, 24)) &&
                (bit_get_field(val_rb_1_p1, 8, 24) == bit_get_field(cval_rb_1_p1, 8, 24)) &&
                (bit_get_field(val_rb_1_p2, 8, 24) == bit_get_field(cval_rb_1_p2, 8, 24)) &&
                (bit_get_field(val_rb_1_p3, 8, 24) == bit_get_field(cval_rb_1_p3, 8, 24))
            )
            {
                k510_logv("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);

        k510_logv(
            "Step 16 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by  "
            "incrementing the values of READ DQS DLL SADJ until  "
            "SADJ = max value.  End Training Loop 2 when the  "
            "max value is reached\n"
        );

        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 2: incr_data is %d\n", __func__, incr_data);
        read_dqs_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(read_dqs_sadj & 0xFF, read_dqs_sadj & 0xFF,
                    read_dqs_sadj & 0xFF, read_dqs_sadj & 0xFF);
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 2 :  single cycle end ****************\n");
    } //while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 2 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 2 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 17 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1\n"
    );

     //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set CRDB (bit[17] to 1.
    // regdata[17] = 1'b1;
    bit_set_bit(regdata, 17);
    //  Set SADJ WRT (bit[10]) to 1.
    // regdata[10] = 1'b1;
    bit_set_bit(regdata, 10);
    //  Clear DS_FRC_RG
    // ngb regdata[9] = 1'b0;
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    k510_logv(
        "Step 18 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = AVE of MIN and MAX pass values "
        "from Training Loop 2\n"
    );
    // set_read_dqs_sadj(incr_good_avg, incr_good_avg,
    //                  incr_good_avg, incr_good_avg);
    // set_read_dqs_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop2 end ----------------\n", __func__);

    incr_good_avg_dqs_p3 = incr_good_avg3;
    incr_good_avg_dqs_p2 = incr_good_avg2;
    incr_good_avg_dqs_p1 = incr_good_avg1;
    incr_good_avg_dqs_p0 = incr_good_avg0;

    k510_logi("---------------- %s Loop3 start ----------------\n", __func__);
    k510_logv(
        "Step 19 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB\n"
    );
    set_read_dqs_b_sadj(0,0,0,0);

    k510_logv(
        "Step 20 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Start of READ EYE Training Loop 3 (find center of EYE "
        "for DQS_B hold DQS fixed).\n"
    );
    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop  = 1;
    while (continue_loop == 1)
    {
        k510_logd("**************** Loop 3 :  single cycle start *****************\n");
        k510_logv(
            "Step 21 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1\n"
        );
         //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        // regdata[17] = 1'b1;
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        // regdata[10] = 1'b1;
        bit_set_bit(regdata, 10);
        //  Clear DS_FRC_RG
        // ngb regdata[9] = 1'b0;
        //  Now write the new value to the TRAINING_CTRL1 register.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        /* Step 4 of 29 - LPDDR3 Read Eye Training
           Issue MRR MR32 through the controller.
        */
        if(read_mode_register_only(32, &value)){
            k510_logd("read_mode_register_only return failure, Step 4 of 29 - LPDDR3 Read Eye Training \n");
            return 1;
        }

        k510_logd("=====incr_data = 0x%08X    MR32 is %08x====\n", incr_data, value);
        /* Step 5 of 29 - LPDDR3 Read Eye Training
           After RL + RU(tDWSCKMAX/tCK) + 8.2 - WL clock
           cycle, DRAM bursts out the predefined Read
           Calibration Pattern.
        */
        /* Step 6 of 29 - LPDDR3 Read Eye Training
           Ensure that tMRR >= 8.
        */
        //usleep(1);

        /* Verify Interrupt Status RBURST Captured (bit[7]) is
           set to 1.  A 1 indicates the RBURST registers have
           been updated.
        */
        usleep(10);
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(regdata & 0x80)
        {
            /* Interrupt Status RBURST Captured (bit[7]) was
               correctly set to 1.
               Now write 1 to the sticky RBURST Captured (bit[7])
               to clear it.
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is
               now cleared to 0.
            */
            if(!(read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
            {
             //   k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                if((read_register(INTERRUPT_STATUS_ADDR, 1) & 0x80))
                {
                    k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0. \n");
                    return 1;
                }
            }
        }
        else
        {
            k510_loge("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return 1;
        }

        // k510_logv(
        //     "Step 22 of 28 for LPDDR3 Read Eye Training "
        //     "w/o Bit Deskew or VREF Training\n"
        //     "Issue AXI READ of address location 0 to accesss"
        //     "known data pattern\n"
        // );
        // // memory_read(mem_addr, mem_rdata, .compare(0));
        // for(uint32_t i = 0; i < 32; i++)
        // {
        //     mem_rdata[i] = *(mem_addr + i);
        // }

        // k510_logv(
        //     "Step 23 of 28 for LPDDR3 Read Eye Training "
        //     "w/o Bit Deskew or VREF Training\n"
        //     "Read AHB registers RBURST_0/1_P0/1/2/3 and compare "
        //     "to pattern A."
        //     "Save pass/fail results\n"
        // );
        // //  read the value of the TRAINING_CTRL1 register.
        // // while(regdata[17] !== 0)
        // // read_register("TRAINING_CTRL1",TRAINING_CTRL1_ADDR,
        // // regdata, 1'b1);
        // regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        // while(bit_check_bit(regdata, 17))
        // {
        //     regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        // }

        // k510_logv(
        //     "Verify Interrupt Status RBURST Captured (bit[7]) is "
        //     "set to 1.  A 1 indicates the RBURST registers have "
        //     "been updated\n"
        // );
        // regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        // if(bit_check_bit(regdata, 7))
        // {
        //     k510_logv(
        //         "Interrupt Status RBURST Captured (bit[7]) was "
        //         "correctly set to 1.\n"
        //         "Now write 1 to the sticky RBURST Captured (bit[7]) "
        //         "to clear it\n"
        //     );
        //     write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

        //     k510_logv(
        //         "Verify Interrupt Status RBURST Captured (bit[7]) is "
        //         "now cleared to 0\n"
        //     );
        //     regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        //     if(bit_check_bit(regdata, 7) == 0)
        //     {
        //         k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0\n");
        //     }
        //     else
        //     {
        //         k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
        //         return -1;
        //     }
        // }
        // else
        // {
        //     k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
        //     return -1;
        // }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Check if CRDB (bit[17] has been cleared.
        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(val_rb_0_p0, 8, 0) == bit_get_field(cval_rb_0_p0, 8, 0)) &&
                (bit_get_field(val_rb_0_p1, 8, 0) == bit_get_field(cval_rb_0_p1, 8, 0)) &&
                (bit_get_field(val_rb_0_p2, 8, 0) == bit_get_field(cval_rb_0_p2, 8, 0)) &&
                (bit_get_field(val_rb_0_p3, 8, 0) == bit_get_field(cval_rb_0_p3, 8, 0)) &&
                (bit_get_field(val_rb_1_p0, 8, 0) == bit_get_field(cval_rb_1_p0, 8, 0)) &&
                (bit_get_field(val_rb_1_p1, 8, 0) == bit_get_field(cval_rb_1_p1, 8, 0)) &&
                (bit_get_field(val_rb_1_p2, 8, 0) == bit_get_field(cval_rb_1_p2, 8, 0)) &&
                (bit_get_field(val_rb_1_p3, 8, 0) == bit_get_field(cval_rb_1_p3, 8, 0))
            )
            {
                k510_logv("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 8) == bit_get_field(cval_rb_0_p0, 8, 8)) &&
                (bit_get_field(val_rb_0_p1, 8, 8) == bit_get_field(cval_rb_0_p1, 8, 8)) &&
                (bit_get_field(val_rb_0_p2, 8, 8) == bit_get_field(cval_rb_0_p2, 8, 8)) &&
                (bit_get_field(val_rb_0_p3, 8, 8) == bit_get_field(cval_rb_0_p3, 8, 8)) &&
                (bit_get_field(val_rb_1_p0, 8, 8) == bit_get_field(cval_rb_1_p0, 8, 8)) &&
                (bit_get_field(val_rb_1_p1, 8, 8) == bit_get_field(cval_rb_1_p1, 8, 8)) &&
                (bit_get_field(val_rb_1_p2, 8, 8) == bit_get_field(cval_rb_1_p2, 8, 8)) &&
                (bit_get_field(val_rb_1_p3, 8, 8) == bit_get_field(cval_rb_1_p3, 8, 8))
            )
            {
                k510_logv("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 16) == bit_get_field(cval_rb_0_p0, 8, 16)) &&
                (bit_get_field(val_rb_0_p1, 8, 16) == bit_get_field(cval_rb_0_p1, 8, 16)) &&
                (bit_get_field(val_rb_0_p2, 8, 16) == bit_get_field(cval_rb_0_p2, 8, 16)) &&
                (bit_get_field(val_rb_0_p3, 8, 16) == bit_get_field(cval_rb_0_p3, 8, 16)) &&
                (bit_get_field(val_rb_1_p0, 8, 16) == bit_get_field(cval_rb_1_p0, 8, 16)) &&
                (bit_get_field(val_rb_1_p1, 8, 16) == bit_get_field(cval_rb_1_p1, 8, 16)) &&
                (bit_get_field(val_rb_1_p2, 8, 16) == bit_get_field(cval_rb_1_p2, 8, 16)) &&
                (bit_get_field(val_rb_1_p3, 8, 16) == bit_get_field(cval_rb_1_p3, 8, 16))
            )
            {
                k510_logv("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 24) == bit_get_field(cval_rb_0_p0, 8, 24)) &&
                (bit_get_field(val_rb_0_p1, 8, 24) == bit_get_field(cval_rb_0_p1, 8, 24)) &&
                (bit_get_field(val_rb_0_p2, 8, 24) == bit_get_field(cval_rb_0_p2, 8, 24)) &&
                (bit_get_field(val_rb_0_p3, 8, 24) == bit_get_field(cval_rb_0_p3, 8, 24)) &&
                (bit_get_field(val_rb_1_p0, 8, 24) == bit_get_field(cval_rb_1_p0, 8, 24)) &&
                (bit_get_field(val_rb_1_p1, 8, 24) == bit_get_field(cval_rb_1_p1, 8, 24)) &&
                (bit_get_field(val_rb_1_p2, 8, 24) == bit_get_field(cval_rb_1_p2, 8, 24)) &&
                (bit_get_field(val_rb_1_p3, 8, 24) == bit_get_field(cval_rb_1_p3, 8, 24))
            )
            {
                k510_logv("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 == %d\n", incr_good_min0);
        k510_logd("incr_good_max0 == %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 == %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 == %d\n", incr_good_min1);
        k510_logd("incr_good_max1 == %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 == %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 == %d\n", incr_good_min2);
        k510_logd("incr_good_max2 == %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 == %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 == %d\n", incr_good_min3);
        k510_logd("incr_good_max3 == %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 == %d\n", incr_good_avg3);

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);

        k510_logv(
            "Step 24 of 28 for LPDDR3 Read Eye Training"
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by"
            "incrementing the values of READ DQS_B DLL SADJ until"
            "SADJ = max value.  End Training Loop 3 when the max"
            "value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 3: incr_data is %d\n", __func__, incr_data);
        read_dqs_b_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_B_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_b_sadj(bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0));
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 3 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 3 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 3 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 25 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 26 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 3.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg, incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop3 end ----------------\n", __func__);
    k510_logv(
        "Step 27 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 0.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_clr_bit(regdata, 17);
    bit_clr_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 28 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Continue with regular DRAM commands.\n"
    );

    /*
        The DRAM accesses are performed by the test sequence,
        not this training_sequence.
    */

    // cache_flush_disable();

#if 0
    /* Bit Deskew */
    /* Set Pattern A(0x55555555) to Addr 0 - 512*/
#define BIT_DLY_MAX (7)

    uint32_t patternA = 0x55555555;
    for(int i = 0; i < 32; i++)
    {
        *(mem_addr + i) = patternA; // PATTERN A
    }

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Starting with all bit delays at 0 */
    write_register(BIT_RDLY_DS0_ADDR, 0, 1);
    write_register(BIT_RDLY_DS1_ADDR, 0, 1);
    write_register(BIT_RDLY_DS2_ADDR, 0, 1);
    write_register(BIT_RDLY_DS3_ADDR, 0, 1);

    continue_loop = 1;
    incr_data = 0;
    while(continue_loop == 1)
    {
         //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        // regdata[17] = 1'b1;
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        // regdata[10] = 1'b1;
        bit_set_bit(regdata, 10);
        //  Clear DS_FRC_RG
        // ngb regdata[9] = 1'b0;
        //  Now write the new value to the TRAINING_CTRL1 register.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        /*
            "Step 22 of 28 for LPDDR3 Read Eye Training ",
            "w/o Bit Deskew or VREF Training",
            "Issue AXI READ of address location 0 to accesss",
            "known data pattern."
        */
        // cache_inval(0, 0, 128, L1_DCACHE);

        for(uint32_t i = 0; i < 32; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        /*
            "Step 23 of 28 for LPDDR3 Read Eye Training ",
            "w/o Bit Deskew or VREF Training",
            "Read AHB registers RBURST_0/1_P0/1/2/3 and compare ",
            "to pattern A.",
            "Save pass/fail results."
        */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17))
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        /*
            "Verify Interrupt Status RBURST Captured (bit[7]) is ",
            "set to 1.  A 1 indicates the RBURST registers have ",
            "been updated."
        */
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            /*
                "Interrupt Status RBURST Captured (bit[7]) was ",
                "correctly set to 1.",
                "Now write 1 to the sticky RBURST Captured (bit[7]) ",
                "to clear it."
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /*
                "Verify Interrupt Status RBURST Captured (bit[7]) is ",
                "now cleared to 0."
            */
           regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
           if(bit_check_bit(regdata, 7) == 0)
           {
               k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0\n");
           }
           else
           {
               k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
               return -1;
           }
        }
        else
        {
            k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            for(uint32_t i = 0; i < 32; i++)    /* 32bits */
            {
                if(
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternA >> i) & 1))
                )
                {
                    bit_rdly_pass[i] = 1;
                    bit_rdly_A[i] = incr_data;
                }
            }
        }

        incr_data ++;
        if(incr_data > BIT_DLY_MAX)
        {
            continue_loop = 0;
        }
        else
        {
            /* Set BIT_RDLY */
            regdata = (incr_data << 21) | (incr_data << 18) | (incr_data << 15) | (incr_data << 12) |
                      (incr_data << 9) | (incr_data << 6) | (incr_data << 3) | (incr_data << 0);
            write_register(BIT_RDLY_DS0_ADDR, regdata, 1);
            write_register(BIT_RDLY_DS1_ADDR, regdata, 1);
            write_register(BIT_RDLY_DS2_ADDR, regdata, 1);
            write_register(BIT_RDLY_DS3_ADDR, regdata, 1);
            k510_logd("====> BIT_RDLY_DS0_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS0_ADDR, 1));
            k510_logd("====> BIT_RDLY_DS1_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS1_ADDR, 1));
            k510_logd("====> BIT_RDLY_DS2_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS2_ADDR, 1));
            k510_logd("====> BIT_RDLY_DS3_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS3_ADDR, 1));
        }

    } // continue_loop == 1

    for(uint32_t i = 0; i < 32; i++)
    {
        k510_logd("PatternA bit_rdly_A %d == %d\n", i, bit_rdly_A[i]);
    }

    /* PATTERN B */
    uint32_t patternB = 0xAAAAAAAA;
    for(int i = 0; i < 32; i++)
    {
        *(mem_addr + i) = patternB; // PATTERN B
    }

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Starting with all bit delays at 0 */
    write_register(BIT_RDLY_DS0_ADDR, 0, 1);
    write_register(BIT_RDLY_DS1_ADDR, 0, 1);
    write_register(BIT_RDLY_DS2_ADDR, 0, 1);
    write_register(BIT_RDLY_DS3_ADDR, 0, 1);

    continue_loop = 1;
    incr_data = 0;
    while(continue_loop == 1)
    {
        k510_logd("********** Bit rdly patternA single cycle start, incr_data is %d **********\n", incr_data);
         //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        // regdata[17] = 1'b1;
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        // regdata[10] = 1'b1;
        bit_set_bit(regdata, 10);
        //  Clear DS_FRC_RG
        // ngb regdata[9] = 1'b0;
        //  Now write the new value to the TRAINING_CTRL1 register.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        /*
            "Step 22 of 28 for LPDDR3 Read Eye Training ",
            "w/o Bit Deskew or VREF Training",
            "Issue AXI READ of address location 0 to accesss",
            "known data pattern."
        */
        // cache_inval(0, 0, 128, L1_DCACHE);

        for(uint32_t i = 0; i < 32; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        /*
            "Step 23 of 28 for LPDDR3 Read Eye Training ",
            "w/o Bit Deskew or VREF Training",
            "Read AHB registers RBURST_0/1_P0/1/2/3 and compare ",
            "to pattern A.",
            "Save pass/fail results."
        */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17))
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        /*
            "Verify Interrupt Status RBURST Captured (bit[7]) is ",
            "set to 1.  A 1 indicates the RBURST registers have ",
            "been updated."
        */
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            /*
                "Interrupt Status RBURST Captured (bit[7]) was ",
                "correctly set to 1.",
                "Now write 1 to the sticky RBURST Captured (bit[7]) ",
                "to clear it."
            */
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /*
                "Verify Interrupt Status RBURST Captured (bit[7]) is ",
                "now cleared to 0."
            */
           regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
           if(bit_check_bit(regdata, 7) == 0)
           {
               k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0\n");
           }
           else
           {
               k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
               return -1;
           }
        }
        else
        {
            k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            for(uint32_t i = 0; i < 32; i++)    /* 32bits */
            {
                if(
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1)) &&
                    (((val_rb_0_p0 >> i) & 1) == ((patternB >> i) & 1))
                )
                {
                    bit_rdly_pass[i] = 1;
                    bit_rdly_B[i] = incr_data;
                }
            }
        }

        incr_data ++;
        if(incr_data > BIT_DLY_MAX)
        {
            continue_loop = 0;
        }
        else
        {
            /* Set BIT_RDLY */
            regdata = (incr_data << 21) | (incr_data << 18) | (incr_data << 15) | (incr_data << 12) |
                      (incr_data << 9) | (incr_data << 6) | (incr_data << 3) | (incr_data << 0);
            write_register(BIT_RDLY_DS0_ADDR, regdata, 1);
            write_register(BIT_RDLY_DS1_ADDR, regdata, 1);
            write_register(BIT_RDLY_DS2_ADDR, regdata, 1);
            write_register(BIT_RDLY_DS3_ADDR, regdata, 1);
            k510_logd("====> BIT_RDLY_DS0_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS0_ADDR, 1));
            k510_logd("====> BIT_RDLY_DS1_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS1_ADDR, 1));
            k510_logd("====> BIT_RDLY_DS2_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS2_ADDR, 1));
            k510_logd("====> BIT_RDLY_DS3_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS3_ADDR, 1));
        }
        k510_logd("********** Bit rdly patternA single cycle end **********\n");
    } // continue_loop == 1

    for(uint32_t i = 0; i < 32; i++)
    {
        k510_logd("PatternA bit_rdly_B %d == %d\n", i, bit_rdly_B[i]);
    }

    /*
        Pattern A and B complete
        Set the READ bit delay line value = to the minimum of the two values saved from Loop 4 and 5
        for each data bit
    */
    for(uint32_t i = 0; i < 32; i++)
    {
        if(bit_rdly_A[i] > bit_rdly_B[i])
        {
            bit_rdly_min[i] = bit_rdly_B[i];
        }
        else
        {
            bit_rdly_min[i] = bit_rdly_A[i];
        }
        k510_logd("PatternA bit_rdly_min %d == %d\n", i, bit_rdly_min[i]);
    }

    for(uint32_t i = 0; i < 4; i++)
    {
        regdata = 0;
        for(uint32_t j = 0; j < 8; j++)
        {
            regdata |= bit_rdly_min[i] << ((j % 8) * 3);
        }
        write_register((BIT_RDLY_DS0_ADDR + i * 8), regdata, 1);
    }

    k510_logd("final :> BIT_RDLY_DS0_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS0_ADDR, 1));
    k510_logd("final :> BIT_RDLY_DS1_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS1_ADDR, 1));
    k510_logd("final :> BIT_RDLY_DS2_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS2_ADDR, 1));
    k510_logd("final :> BIT_RDLY_DS3_ADDR == 0x%08X\n", read_register(BIT_RDLY_DS3_ADDR, 1));

    /* end */
#endif
#if 0
    /* Loop 2 & 3 again */
    if(read_eye_loop2_loop3())
    {
        return -1;
    }
#endif
    k510_logi("LPDDR3 Read Eye Training Complete\n");
    // read_dll_ctrl_registers();
    k510_logi("\nCompare DLL_CTRL After Read Eye Training\n");
    // print_pre_vs_cur_data();
    // update_pre_data();

    return 0;
}
#endif

#if 0
uint32_t Read_eye_training(void)
{
    uint32_t regdata = 0;
    // uint64_t value = 0;
    // int32_t i;
    // cache_enable();

    k510_logi("Begin LPDDR3 Read Eye Training  "
              "w/o Bit Deskew or VREF Training\n");

    k510_logv(
        "Step 0 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Issue an AXI READ of Address location 0 (note this "
        "location has been pre-written with a known value at "
        "low frequency prior to this operation.\n"
    );
    // memory_read(mem_addr, mem_rdata, .compare(0)); /* What's this ? */
    // memcpy((void *)mem_rdata, mem_addr, MEM_BYTE_CNT);
    // mem_rdata[0] = *(mem_addr);
    // mem_rdata[1] = *(mem_addr + 1);
    // mem_rdata[2] = *(mem_addr + 2);
    // mem_rdata[3] = *(mem_addr + 3);

    // cache_inval(0, 0, 128, L1_DCACHE);

    for(uint32_t i = 0; i < 8; i++)
    {
        mem_rdata[i] = *(mem_addr + i);
    }

    k510_logv(
        "Step 1 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set DFI frequency = 800 MHz for Memory operation "
        "of 3200Mbs.\n"
    );

    k510_logv(
        "Step 2 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_set_bit(regdata, 17);
    bit_set_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 3 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set READ DQS DLL and READ DQS_B DLL SADJ=0 using the "
        "DLL_CTRL registers through the DDR PHY AHB. \n"
        "a. DLL_CTRL2 affects Data Slice 0\n"
        "b. DLL_CTRL3 affects Data Slice 1\n"
        "c. DLL_CTRL4 affects Data Slice 2\n"
        "d. DLL_CTRL5 affects Data Slice 3\n"
    );
    set_read_dqs_sadj(0,0,0,0);         /* function is OK? zzx */
    set_read_dqs_b_sadj(0,0,0,0);

    /* Starting with all bit delays at 0 */
    // write_register(BIT_RDLY_DS0_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS0_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0x00FFFFFF, 1);

    k510_logv(
        "Step 4 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set extend read gate bits.\n"
    );
    /* Extend read gate deassertion by 2 clks. */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);   // shorten the extension
    bit_set_field(regdata, 2, 28, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 20, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 12, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 4,  DDR_READ_GATE_DELAY_DEASSERTION);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    cval_rb_0_p0 = pattern[0];
    cval_rb_0_p1 = pattern[1];
    cval_rb_0_p2 = pattern[2];
    cval_rb_0_p3 = pattern[3];
    cval_rb_1_p0 = pattern[4];
    cval_rb_1_p1 = pattern[5];
    cval_rb_1_p2 = pattern[6];
    cval_rb_1_p3 = pattern[7];

    k510_logi("---------------- %s Loop1 start ----------------\n", __func__);
    k510_logv(
        "Step 5 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 1 "
        "(find center of EYE for DQS/DQS_B).\n"
    );
    incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 1 :  single cycle start *****************\n");
        k510_logv(
            "Step 6 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue an AXI READ of address location 0 to access "
            "known data pattern.\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 8; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 7 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare to "
            "pattern A. "
            "Save pass/fail results.\n"
        );

        /* read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17) != 0)
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated.\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it.\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0. */
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
                return -1;
            }
        }
        else
        {
            k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(val_rb_0_p0, 8, 0) == bit_get_field(cval_rb_0_p0, 8, 0)) &&
                (bit_get_field(val_rb_0_p1, 8, 0) == bit_get_field(cval_rb_0_p1, 8, 0)) &&
                (bit_get_field(val_rb_0_p2, 8, 0) == bit_get_field(cval_rb_0_p2, 8, 0)) &&
                (bit_get_field(val_rb_0_p3, 8, 0) == bit_get_field(cval_rb_0_p3, 8, 0)) &&
                (bit_get_field(val_rb_1_p0, 8, 0) == bit_get_field(cval_rb_1_p0, 8, 0)) &&
                (bit_get_field(val_rb_1_p1, 8, 0) == bit_get_field(cval_rb_1_p1, 8, 0)) &&
                (bit_get_field(val_rb_1_p2, 8, 0) == bit_get_field(cval_rb_1_p2, 8, 0)) &&
                (bit_get_field(val_rb_1_p3, 8, 0) == bit_get_field(cval_rb_1_p3, 8, 0))
            )
            {
                k510_logd("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 8) == bit_get_field(cval_rb_0_p0, 8, 8)) &&
                (bit_get_field(val_rb_0_p1, 8, 8) == bit_get_field(cval_rb_0_p1, 8, 8)) &&
                (bit_get_field(val_rb_0_p2, 8, 8) == bit_get_field(cval_rb_0_p2, 8, 8)) &&
                (bit_get_field(val_rb_0_p3, 8, 8) == bit_get_field(cval_rb_0_p3, 8, 8)) &&
                (bit_get_field(val_rb_1_p0, 8, 8) == bit_get_field(cval_rb_1_p0, 8, 8)) &&
                (bit_get_field(val_rb_1_p1, 8, 8) == bit_get_field(cval_rb_1_p1, 8, 8)) &&
                (bit_get_field(val_rb_1_p2, 8, 8) == bit_get_field(cval_rb_1_p2, 8, 8)) &&
                (bit_get_field(val_rb_1_p3, 8, 8) == bit_get_field(cval_rb_1_p3, 8, 8))
            )
            {
                k510_logd("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 16) == bit_get_field(cval_rb_0_p0, 8, 16)) &&
                (bit_get_field(val_rb_0_p1, 8, 16) == bit_get_field(cval_rb_0_p1, 8, 16)) &&
                (bit_get_field(val_rb_0_p2, 8, 16) == bit_get_field(cval_rb_0_p2, 8, 16)) &&
                (bit_get_field(val_rb_0_p3, 8, 16) == bit_get_field(cval_rb_0_p3, 8, 16)) &&
                (bit_get_field(val_rb_1_p0, 8, 16) == bit_get_field(cval_rb_1_p0, 8, 16)) &&
                (bit_get_field(val_rb_1_p1, 8, 16) == bit_get_field(cval_rb_1_p1, 8, 16)) &&
                (bit_get_field(val_rb_1_p2, 8, 16) == bit_get_field(cval_rb_1_p2, 8, 16)) &&
                (bit_get_field(val_rb_1_p3, 8, 16) == bit_get_field(cval_rb_1_p3, 8, 16))
            )
            {
                k510_logd("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 24) == bit_get_field(cval_rb_0_p0, 8, 24)) &&
                (bit_get_field(val_rb_0_p1, 8, 24) == bit_get_field(cval_rb_0_p1, 8, 24)) &&
                (bit_get_field(val_rb_0_p2, 8, 24) == bit_get_field(cval_rb_0_p2, 8, 24)) &&
                (bit_get_field(val_rb_0_p3, 8, 24) == bit_get_field(cval_rb_0_p3, 8, 24)) &&
                (bit_get_field(val_rb_1_p0, 8, 24) == bit_get_field(cval_rb_1_p0, 8, 24)) &&
                (bit_get_field(val_rb_1_p1, 8, 24) == bit_get_field(cval_rb_1_p1, 8, 24)) &&
                (bit_get_field(val_rb_1_p2, 8, 24) == bit_get_field(cval_rb_1_p2, 8, 24)) &&
                (bit_get_field(val_rb_1_p3, 8, 24) == bit_get_field(cval_rb_1_p3, 8, 24))
            )
            {
                k510_logd("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else // is it right ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);

        k510_logv(
            "Step 8 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop 1 by "
            "incrementing the values of READ DQS DLL SADJ and "
            "READ DQS_B SADJ until SADJ = max value.  End "
            "Training Loop 1 when max value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 1: incr_data is %d\n", __func__, incr_data);
        read_dqs_sadj = incr_data;
        read_dqs_b_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0));
            set_read_dqs_b_sadj(bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0));
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }

        k510_logv(
            "Step 8b = Repeat Step 1\n"
            "Step 1 of 29 - LPDDR3 Read Eye Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logd("**************** Loop 1 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 1 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 1 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 9 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 10 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 1.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg,incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1,incr_good_avg0); //avg3 -> avg0 invert avg0 -> avg3 ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);
    k510_logi("---------------- %s Loop1 end ----------------\n", __func__);
    k510_logi("---------------- %s Loop2 start ----------------\n", __func__);
    k510_logv(
        "Step 11 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB.\n"
    );
    set_read_dqs_sadj(0,0,0,0);

    k510_logv(
        "Step 12 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 2 (find center of "
        "EYE for DQS while holding DQS_B fixed).\n"
    );

    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop  = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 2 :  single cycle start *****************\n");
        k510_logv(
            "Step 13 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 register. */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logv(
            "Step 14 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue and AXI READ of address location 0 to access "
            "known data pattern.\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 8; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 15 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare "
            "to pattern A. "
            "Save pass/fail results.\n"
        );

        /* read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17) != 0)
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated.\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it.\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            k510_logv("Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0.\n");

            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
                return -1;
            }
        }
        else
        {
            k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1\n");
            return -1;
        }


        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(val_rb_0_p0, 8, 0) == bit_get_field(cval_rb_0_p0, 8, 0)) &&
                (bit_get_field(val_rb_0_p1, 8, 0) == bit_get_field(cval_rb_0_p1, 8, 0)) &&
                (bit_get_field(val_rb_0_p2, 8, 0) == bit_get_field(cval_rb_0_p2, 8, 0)) &&
                (bit_get_field(val_rb_0_p3, 8, 0) == bit_get_field(cval_rb_0_p3, 8, 0)) &&
                (bit_get_field(val_rb_1_p0, 8, 0) == bit_get_field(cval_rb_1_p0, 8, 0)) &&
                (bit_get_field(val_rb_1_p1, 8, 0) == bit_get_field(cval_rb_1_p1, 8, 0)) &&
                (bit_get_field(val_rb_1_p2, 8, 0) == bit_get_field(cval_rb_1_p2, 8, 0)) &&
                (bit_get_field(val_rb_1_p3, 8, 0) == bit_get_field(cval_rb_1_p3, 8, 0))
            )
            {
                k510_logv("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 8) == bit_get_field(cval_rb_0_p0, 8, 8)) &&
                (bit_get_field(val_rb_0_p1, 8, 8) == bit_get_field(cval_rb_0_p1, 8, 8)) &&
                (bit_get_field(val_rb_0_p2, 8, 8) == bit_get_field(cval_rb_0_p2, 8, 8)) &&
                (bit_get_field(val_rb_0_p3, 8, 8) == bit_get_field(cval_rb_0_p3, 8, 8)) &&
                (bit_get_field(val_rb_1_p0, 8, 8) == bit_get_field(cval_rb_1_p0, 8, 8)) &&
                (bit_get_field(val_rb_1_p1, 8, 8) == bit_get_field(cval_rb_1_p1, 8, 8)) &&
                (bit_get_field(val_rb_1_p2, 8, 8) == bit_get_field(cval_rb_1_p2, 8, 8)) &&
                (bit_get_field(val_rb_1_p3, 8, 8) == bit_get_field(cval_rb_1_p3, 8, 8))
            )
            {
                k510_logv("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 16) == bit_get_field(cval_rb_0_p0, 8, 16)) &&
                (bit_get_field(val_rb_0_p1, 8, 16) == bit_get_field(cval_rb_0_p1, 8, 16)) &&
                (bit_get_field(val_rb_0_p2, 8, 16) == bit_get_field(cval_rb_0_p2, 8, 16)) &&
                (bit_get_field(val_rb_0_p3, 8, 16) == bit_get_field(cval_rb_0_p3, 8, 16)) &&
                (bit_get_field(val_rb_1_p0, 8, 16) == bit_get_field(cval_rb_1_p0, 8, 16)) &&
                (bit_get_field(val_rb_1_p1, 8, 16) == bit_get_field(cval_rb_1_p1, 8, 16)) &&
                (bit_get_field(val_rb_1_p2, 8, 16) == bit_get_field(cval_rb_1_p2, 8, 16)) &&
                (bit_get_field(val_rb_1_p3, 8, 16) == bit_get_field(cval_rb_1_p3, 8, 16))
            )
            {
                k510_logv("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 24) == bit_get_field(cval_rb_0_p0, 8, 24)) &&
                (bit_get_field(val_rb_0_p1, 8, 24) == bit_get_field(cval_rb_0_p1, 8, 24)) &&
                (bit_get_field(val_rb_0_p2, 8, 24) == bit_get_field(cval_rb_0_p2, 8, 24)) &&
                (bit_get_field(val_rb_0_p3, 8, 24) == bit_get_field(cval_rb_0_p3, 8, 24)) &&
                (bit_get_field(val_rb_1_p0, 8, 24) == bit_get_field(cval_rb_1_p0, 8, 24)) &&
                (bit_get_field(val_rb_1_p1, 8, 24) == bit_get_field(cval_rb_1_p1, 8, 24)) &&
                (bit_get_field(val_rb_1_p2, 8, 24) == bit_get_field(cval_rb_1_p2, 8, 24)) &&
                (bit_get_field(val_rb_1_p3, 8, 24) == bit_get_field(cval_rb_1_p3, 8, 24))
            )
            {
                k510_logv("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);

        k510_logv(
            "Step 16 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by  "
            "incrementing the values of READ DQS DLL SADJ until  "
            "SADJ = max value.  End Training Loop 2 when the  "
            "max value is reached\n"
        );

        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 2: incr_data is %d\n", __func__, incr_data);
        read_dqs_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(read_dqs_sadj & 0xFF, read_dqs_sadj & 0xFF,
                    read_dqs_sadj & 0xFF, read_dqs_sadj & 0xFF);
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 2 :  single cycle end ****************\n");
    } //while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 2 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 2 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 17 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1\n"
    );

     //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set CRDB (bit[17] to 1.
    // regdata[17] = 1'b1;
    bit_set_bit(regdata, 17);
    //  Set SADJ WRT (bit[10]) to 1.
    // regdata[10] = 1'b1;
    bit_set_bit(regdata, 10);
    //  Clear DS_FRC_RG
    // ngb regdata[9] = 1'b0;
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    k510_logv(
        "Step 18 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = AVE of MIN and MAX pass values "
        "from Training Loop 2\n"
    );
    // set_read_dqs_sadj(incr_good_avg, incr_good_avg,
    //                  incr_good_avg, incr_good_avg);
    // set_read_dqs_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop2 end ----------------\n", __func__);

    incr_good_avg_dqs_p3 = incr_good_avg3;
    incr_good_avg_dqs_p2 = incr_good_avg2;
    incr_good_avg_dqs_p1 = incr_good_avg1;
    incr_good_avg_dqs_p0 = incr_good_avg0;

    k510_logi("---------------- %s Loop3 start ----------------\n", __func__);
    k510_logv(
        "Step 19 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB\n"
    );
    set_read_dqs_b_sadj(0,0,0,0);

    k510_logv(
        "Step 20 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Start of READ EYE Training Loop 3 (find center of EYE "
        "for DQS_B hold DQS fixed).\n"
    );
    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop  = 1;
    while (continue_loop == 1)
    {
        k510_logd("**************** Loop 3 :  single cycle start *****************\n");
        k510_logv(
            "Step 21 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1\n"
        );
         //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        // regdata[17] = 1'b1;
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        // regdata[10] = 1'b1;
        bit_set_bit(regdata, 10);
        //  Clear DS_FRC_RG
        // ngb regdata[9] = 1'b0;
        //  Now write the new value to the TRAINING_CTRL1 register.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        k510_logv(
            "Step 22 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue AXI READ of address location 0 to accesss"
            "known data pattern\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 8; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 23 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB registers RBURST_0/1_P0/1/2/3 and compare "
            "to pattern A."
            "Save pass/fail results\n"
        );
        //  read the value of the TRAINING_CTRL1 register.
        // while(regdata[17] !== 0)
        // read_register("TRAINING_CTRL1",TRAINING_CTRL1_ADDR,
        // regdata, 1'b1);
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17))
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            k510_logv(
                "Verify Interrupt Status RBURST Captured (bit[7]) is "
                "now cleared to 0\n"
            );
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0\n");
            }
            else
            {
                k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
                return -1;
            }
        }
        else
        {
            k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Check if CRDB (bit[17] has been cleared.
        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(val_rb_0_p0, 8, 0) == bit_get_field(cval_rb_0_p0, 8, 0)) &&
                (bit_get_field(val_rb_0_p1, 8, 0) == bit_get_field(cval_rb_0_p1, 8, 0)) &&
                (bit_get_field(val_rb_0_p2, 8, 0) == bit_get_field(cval_rb_0_p2, 8, 0)) &&
                (bit_get_field(val_rb_0_p3, 8, 0) == bit_get_field(cval_rb_0_p3, 8, 0)) &&
                (bit_get_field(val_rb_1_p0, 8, 0) == bit_get_field(cval_rb_1_p0, 8, 0)) &&
                (bit_get_field(val_rb_1_p1, 8, 0) == bit_get_field(cval_rb_1_p1, 8, 0)) &&
                (bit_get_field(val_rb_1_p2, 8, 0) == bit_get_field(cval_rb_1_p2, 8, 0)) &&
                (bit_get_field(val_rb_1_p3, 8, 0) == bit_get_field(cval_rb_1_p3, 8, 0))
            )
            {
                k510_logv("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 8) == bit_get_field(cval_rb_0_p0, 8, 8)) &&
                (bit_get_field(val_rb_0_p1, 8, 8) == bit_get_field(cval_rb_0_p1, 8, 8)) &&
                (bit_get_field(val_rb_0_p2, 8, 8) == bit_get_field(cval_rb_0_p2, 8, 8)) &&
                (bit_get_field(val_rb_0_p3, 8, 8) == bit_get_field(cval_rb_0_p3, 8, 8)) &&
                (bit_get_field(val_rb_1_p0, 8, 8) == bit_get_field(cval_rb_1_p0, 8, 8)) &&
                (bit_get_field(val_rb_1_p1, 8, 8) == bit_get_field(cval_rb_1_p1, 8, 8)) &&
                (bit_get_field(val_rb_1_p2, 8, 8) == bit_get_field(cval_rb_1_p2, 8, 8)) &&
                (bit_get_field(val_rb_1_p3, 8, 8) == bit_get_field(cval_rb_1_p3, 8, 8))
            )
            {
                k510_logv("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 16) == bit_get_field(cval_rb_0_p0, 8, 16)) &&
                (bit_get_field(val_rb_0_p1, 8, 16) == bit_get_field(cval_rb_0_p1, 8, 16)) &&
                (bit_get_field(val_rb_0_p2, 8, 16) == bit_get_field(cval_rb_0_p2, 8, 16)) &&
                (bit_get_field(val_rb_0_p3, 8, 16) == bit_get_field(cval_rb_0_p3, 8, 16)) &&
                (bit_get_field(val_rb_1_p0, 8, 16) == bit_get_field(cval_rb_1_p0, 8, 16)) &&
                (bit_get_field(val_rb_1_p1, 8, 16) == bit_get_field(cval_rb_1_p1, 8, 16)) &&
                (bit_get_field(val_rb_1_p2, 8, 16) == bit_get_field(cval_rb_1_p2, 8, 16)) &&
                (bit_get_field(val_rb_1_p3, 8, 16) == bit_get_field(cval_rb_1_p3, 8, 16))
            )
            {
                k510_logv("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(val_rb_0_p0, 8, 24) == bit_get_field(cval_rb_0_p0, 8, 24)) &&
                (bit_get_field(val_rb_0_p1, 8, 24) == bit_get_field(cval_rb_0_p1, 8, 24)) &&
                (bit_get_field(val_rb_0_p2, 8, 24) == bit_get_field(cval_rb_0_p2, 8, 24)) &&
                (bit_get_field(val_rb_0_p3, 8, 24) == bit_get_field(cval_rb_0_p3, 8, 24)) &&
                (bit_get_field(val_rb_1_p0, 8, 24) == bit_get_field(cval_rb_1_p0, 8, 24)) &&
                (bit_get_field(val_rb_1_p1, 8, 24) == bit_get_field(cval_rb_1_p1, 8, 24)) &&
                (bit_get_field(val_rb_1_p2, 8, 24) == bit_get_field(cval_rb_1_p2, 8, 24)) &&
                (bit_get_field(val_rb_1_p3, 8, 24) == bit_get_field(cval_rb_1_p3, 8, 24))
            )
            {
                k510_logv("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 == %d\n", incr_good_min0);
        k510_logd("incr_good_max0 == %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 == %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 == %d\n", incr_good_min1);
        k510_logd("incr_good_max1 == %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 == %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 == %d\n", incr_good_min2);
        k510_logd("incr_good_max2 == %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 == %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 == %d\n", incr_good_min3);
        k510_logd("incr_good_max3 == %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 == %d\n", incr_good_avg3);

        k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);

        k510_logv(
            "Step 24 of 28 for LPDDR3 Read Eye Training"
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by"
            "incrementing the values of READ DQS_B DLL SADJ until"
            "SADJ = max value.  End Training Loop 3 when the max"
            "value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 3: incr_data is %d\n", __func__, incr_data);
        read_dqs_b_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_B_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_b_sadj(bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0));
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 3 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 3 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 3 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 25 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 26 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 3.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg, incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop3 end ----------------\n", __func__);
    k510_logv(
        "Step 27 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 0.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_clr_bit(regdata, 17);
    bit_clr_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 28 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Continue with regular DRAM commands.\n"
    );

    k510_logi("LPDDR3 Read Eye Training Complete\n");
    return 0;
}
#endif

#if 0
#if DDR_RE_TRAINING_READ_PATTERN
uint32_t Read_eye_training(void)
{
    uint32_t regdata = 0;
    // uint64_t value = 0;
    // int32_t i;
    // cache_enable();

    k510_logi("Begin LPDDR3 Read Eye Training  "
              "w/o Bit Deskew or VREF Training by Read pattern\n");

    k510_logv(
        "Step 0 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Issue an AXI READ of Address location 0 (note this "
        "location has been pre-written with a known value at "
        "low frequency prior to this operation.\n"
    );
    // memory_read(mem_addr, mem_rdata, .compare(0)); /* What's this ? */
    // memcpy((void *)mem_rdata, mem_addr, MEM_BYTE_CNT);
    // mem_rdata[0] = *(mem_addr);
    // mem_rdata[1] = *(mem_addr + 1);
    // mem_rdata[2] = *(mem_addr + 2);
    // mem_rdata[3] = *(mem_addr + 3);

    // cache_inval(0, 0, 128, L1_DCACHE);

    for(uint32_t i = 0; i < 24; i++)
    {
        mem_rdata[i] = *(mem_addr + i);
    }

    k510_logv(
        "Step 1 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set DFI frequency = 800 MHz for Memory operation "
        "of 3200Mbs.\n"
    );

    k510_logv(
        "Step 2 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_set_bit(regdata, 17);
    bit_set_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 3 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set READ DQS DLL and READ DQS_B DLL SADJ=0 using the "
        "DLL_CTRL registers through the DDR PHY AHB. \n"
        "a. DLL_CTRL2 affects Data Slice 0\n"
        "b. DLL_CTRL3 affects Data Slice 1\n"
        "c. DLL_CTRL4 affects Data Slice 2\n"
        "d. DLL_CTRL5 affects Data Slice 3\n"
    );
    set_read_dqs_sadj(0,0,0,0);         /* function is OK? zzx */
    set_read_dqs_b_sadj(0,0,0,0);

    /* Starting with all bit delays at 0 */
    // write_register(BIT_RDLY_DS0_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS0_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0x00FFFFFF, 1);

    k510_logv(
        "Step 4 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set extend read gate bits.\n"
    );
    /* Extend read gate deassertion by 2 clks. */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);   // shorten the extension
    bit_set_field(regdata, 2, 28, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 20, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 12, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 4,  DDR_READ_GATE_DELAY_DEASSERTION);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    cval_rb_0_p0 = pattern[0];
    cval_rb_0_p1 = pattern[1];
    cval_rb_0_p2 = pattern[2];
    cval_rb_0_p3 = pattern[3];
    cval_rb_1_p0 = pattern[4];
    cval_rb_1_p1 = pattern[5];
    cval_rb_1_p2 = pattern[6];
    cval_rb_1_p3 = pattern[7];

    k510_logi("---------------- %s Loop1 start ----------------\n", __func__);
    k510_logv(
        "Step 5 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 1 "
        "(find center of EYE for DQS/DQS_B).\n"
    );
    incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 1 :  single cycle start *****************\n");
        k510_logv(
            "Step 6 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue an AXI READ of address location 0 to access "
            "known data pattern.\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 7 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare to "
            "pattern A. "
            "Save pass/fail results.\n"
        );

        /* read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17) != 0)
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated.\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it.\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0. */
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
                return -1;
            }
        }
        else
        {
            k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(mem_rdata[0], 8, 0)  == bit_get_field(pattern[0], 8, 0)) &&
                (bit_get_field(mem_rdata[1], 8, 0)  == bit_get_field(pattern[1], 8, 0)) &&
                (bit_get_field(mem_rdata[2], 8, 0)  == bit_get_field(pattern[2], 8, 0)) &&
                (bit_get_field(mem_rdata[3], 8, 0)  == bit_get_field(pattern[3], 8, 0)) &&
                (bit_get_field(mem_rdata[4], 8, 0)  == bit_get_field(pattern[4], 8, 0)) &&
                (bit_get_field(mem_rdata[5], 8, 0)  == bit_get_field(pattern[5], 8, 0)) &&
                (bit_get_field(mem_rdata[6], 8, 0)  == bit_get_field(pattern[6], 8, 0)) &&
                (bit_get_field(mem_rdata[7], 8, 0)  == bit_get_field(pattern[7], 8, 0)) &&
                (bit_get_field(mem_rdata[8], 8, 0)  == bit_get_field(pattern[8], 8, 0)) &&
                (bit_get_field(mem_rdata[9], 8, 0)  == bit_get_field(pattern[9], 8, 0)) &&
                (bit_get_field(mem_rdata[10], 8, 0) == bit_get_field(pattern[10], 8, 0)) &&
                (bit_get_field(mem_rdata[11], 8, 0) == bit_get_field(pattern[11], 8, 0)) &&
                (bit_get_field(mem_rdata[12], 8, 0) == bit_get_field(pattern[12], 8, 0)) &&
                (bit_get_field(mem_rdata[13], 8, 0) == bit_get_field(pattern[13], 8, 0)) &&
                (bit_get_field(mem_rdata[14], 8, 0) == bit_get_field(pattern[14], 8, 0)) &&
                (bit_get_field(mem_rdata[15], 8, 0) == bit_get_field(pattern[15], 8, 0)) &&
                (bit_get_field(mem_rdata[16], 8, 0) == bit_get_field(pattern[16], 8, 0)) &&
                (bit_get_field(mem_rdata[17], 8, 0) == bit_get_field(pattern[17], 8, 0)) &&
                (bit_get_field(mem_rdata[18], 8, 0) == bit_get_field(pattern[18], 8, 0)) &&
                (bit_get_field(mem_rdata[19], 8, 0) == bit_get_field(pattern[19], 8, 0)) &&
                (bit_get_field(mem_rdata[20], 8, 0) == bit_get_field(pattern[20], 8, 0)) &&
                (bit_get_field(mem_rdata[21], 8, 0) == bit_get_field(pattern[21], 8, 0)) &&
                (bit_get_field(mem_rdata[22], 8, 0) == bit_get_field(pattern[22], 8, 0)) &&
                (bit_get_field(mem_rdata[23], 8, 0) == bit_get_field(pattern[23], 8, 0))
            )
            {
                k510_logd("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 8)  == bit_get_field(pattern[0], 8, 8)) &&
                (bit_get_field(mem_rdata[1], 8, 8)  == bit_get_field(pattern[1], 8, 8)) &&
                (bit_get_field(mem_rdata[2], 8, 8)  == bit_get_field(pattern[2], 8, 8)) &&
                (bit_get_field(mem_rdata[3], 8, 8)  == bit_get_field(pattern[3], 8, 8)) &&
                (bit_get_field(mem_rdata[4], 8, 8)  == bit_get_field(pattern[4], 8, 8)) &&
                (bit_get_field(mem_rdata[5], 8, 8)  == bit_get_field(pattern[5], 8, 8)) &&
                (bit_get_field(mem_rdata[6], 8, 8)  == bit_get_field(pattern[6], 8, 8)) &&
                (bit_get_field(mem_rdata[7], 8, 8)  == bit_get_field(pattern[7], 8, 8)) &&
                (bit_get_field(mem_rdata[8], 8, 8)  == bit_get_field(pattern[8], 8, 8)) &&
                (bit_get_field(mem_rdata[9], 8, 8)  == bit_get_field(pattern[9], 8, 8)) &&
                (bit_get_field(mem_rdata[10], 8, 8) == bit_get_field(pattern[10], 8, 8)) &&
                (bit_get_field(mem_rdata[11], 8, 8) == bit_get_field(pattern[11], 8, 8)) &&
                (bit_get_field(mem_rdata[12], 8, 8) == bit_get_field(pattern[12], 8, 8)) &&
                (bit_get_field(mem_rdata[13], 8, 8) == bit_get_field(pattern[13], 8, 8)) &&
                (bit_get_field(mem_rdata[14], 8, 8) == bit_get_field(pattern[14], 8, 8)) &&
                (bit_get_field(mem_rdata[15], 8, 8) == bit_get_field(pattern[15], 8, 8)) &&
                (bit_get_field(mem_rdata[16], 8, 8) == bit_get_field(pattern[16], 8, 8)) &&
                (bit_get_field(mem_rdata[17], 8, 8) == bit_get_field(pattern[17], 8, 8)) &&
                (bit_get_field(mem_rdata[18], 8, 8) == bit_get_field(pattern[18], 8, 8)) &&
                (bit_get_field(mem_rdata[19], 8, 8) == bit_get_field(pattern[19], 8, 8)) &&
                (bit_get_field(mem_rdata[20], 8, 8) == bit_get_field(pattern[20], 8, 8)) &&
                (bit_get_field(mem_rdata[21], 8, 8) == bit_get_field(pattern[21], 8, 8)) &&
                (bit_get_field(mem_rdata[22], 8, 8) == bit_get_field(pattern[22], 8, 8)) &&
                (bit_get_field(mem_rdata[23], 8, 8) == bit_get_field(pattern[23], 8, 8))
            )
            {
                k510_logd("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 16)  == bit_get_field(pattern[0], 8, 16)) &&
                (bit_get_field(mem_rdata[1], 8, 16)  == bit_get_field(pattern[1], 8, 16)) &&
                (bit_get_field(mem_rdata[2], 8, 16)  == bit_get_field(pattern[2], 8, 16)) &&
                (bit_get_field(mem_rdata[3], 8, 16)  == bit_get_field(pattern[3], 8, 16)) &&
                (bit_get_field(mem_rdata[4], 8, 16)  == bit_get_field(pattern[4], 8, 16)) &&
                (bit_get_field(mem_rdata[5], 8, 16)  == bit_get_field(pattern[5], 8, 16)) &&
                (bit_get_field(mem_rdata[6], 8, 16)  == bit_get_field(pattern[6], 8, 16)) &&
                (bit_get_field(mem_rdata[7], 8, 16)  == bit_get_field(pattern[7], 8, 16)) &&
                (bit_get_field(mem_rdata[8], 8, 16)  == bit_get_field(pattern[8], 8, 16)) &&
                (bit_get_field(mem_rdata[9], 8, 16)  == bit_get_field(pattern[9], 8, 16)) &&
                (bit_get_field(mem_rdata[10], 8, 16) == bit_get_field(pattern[10], 8, 16)) &&
                (bit_get_field(mem_rdata[11], 8, 16) == bit_get_field(pattern[11], 8, 16)) &&
                (bit_get_field(mem_rdata[12], 8, 16) == bit_get_field(pattern[12], 8, 16)) &&
                (bit_get_field(mem_rdata[13], 8, 16) == bit_get_field(pattern[13], 8, 16)) &&
                (bit_get_field(mem_rdata[14], 8, 16) == bit_get_field(pattern[14], 8, 16)) &&
                (bit_get_field(mem_rdata[15], 8, 16) == bit_get_field(pattern[15], 8, 16)) &&
                (bit_get_field(mem_rdata[16], 8, 16) == bit_get_field(pattern[16], 8, 16)) &&
                (bit_get_field(mem_rdata[17], 8, 16) == bit_get_field(pattern[17], 8, 16)) &&
                (bit_get_field(mem_rdata[18], 8, 16) == bit_get_field(pattern[18], 8, 16)) &&
                (bit_get_field(mem_rdata[19], 8, 16) == bit_get_field(pattern[19], 8, 16)) &&
                (bit_get_field(mem_rdata[20], 8, 16) == bit_get_field(pattern[20], 8, 16)) &&
                (bit_get_field(mem_rdata[21], 8, 16) == bit_get_field(pattern[21], 8, 16)) &&
                (bit_get_field(mem_rdata[22], 8, 16) == bit_get_field(pattern[22], 8, 16)) &&
                (bit_get_field(mem_rdata[23], 8, 16) == bit_get_field(pattern[23], 8, 16))
            )
            {
                k510_logd("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 24)  == bit_get_field(pattern[0], 8, 24)) &&
                (bit_get_field(mem_rdata[1], 8, 24)  == bit_get_field(pattern[1], 8, 24)) &&
                (bit_get_field(mem_rdata[2], 8, 24)  == bit_get_field(pattern[2], 8, 24)) &&
                (bit_get_field(mem_rdata[3], 8, 24)  == bit_get_field(pattern[3], 8, 24)) &&
                (bit_get_field(mem_rdata[4], 8, 24)  == bit_get_field(pattern[4], 8, 24)) &&
                (bit_get_field(mem_rdata[5], 8, 24)  == bit_get_field(pattern[5], 8, 24)) &&
                (bit_get_field(mem_rdata[6], 8, 24)  == bit_get_field(pattern[6], 8, 24)) &&
                (bit_get_field(mem_rdata[7], 8, 24)  == bit_get_field(pattern[7], 8, 24)) &&
                (bit_get_field(mem_rdata[8], 8, 24)  == bit_get_field(pattern[8], 8, 24)) &&
                (bit_get_field(mem_rdata[9], 8, 24)  == bit_get_field(pattern[9], 8, 24)) &&
                (bit_get_field(mem_rdata[10], 8, 24) == bit_get_field(pattern[10], 8, 24)) &&
                (bit_get_field(mem_rdata[11], 8, 24) == bit_get_field(pattern[11], 8, 24)) &&
                (bit_get_field(mem_rdata[12], 8, 24) == bit_get_field(pattern[12], 8, 24)) &&
                (bit_get_field(mem_rdata[13], 8, 24) == bit_get_field(pattern[13], 8, 24)) &&
                (bit_get_field(mem_rdata[14], 8, 24) == bit_get_field(pattern[14], 8, 24)) &&
                (bit_get_field(mem_rdata[15], 8, 24) == bit_get_field(pattern[15], 8, 24)) &&
                (bit_get_field(mem_rdata[16], 8, 24) == bit_get_field(pattern[16], 8, 24)) &&
                (bit_get_field(mem_rdata[17], 8, 24) == bit_get_field(pattern[17], 8, 24)) &&
                (bit_get_field(mem_rdata[18], 8, 24) == bit_get_field(pattern[18], 8, 24)) &&
                (bit_get_field(mem_rdata[19], 8, 24) == bit_get_field(pattern[19], 8, 24)) &&
                (bit_get_field(mem_rdata[20], 8, 24) == bit_get_field(pattern[20], 8, 24)) &&
                (bit_get_field(mem_rdata[21], 8, 24) == bit_get_field(pattern[21], 8, 24)) &&
                (bit_get_field(mem_rdata[22], 8, 24) == bit_get_field(pattern[22], 8, 24)) &&
                (bit_get_field(mem_rdata[23], 8, 24) == bit_get_field(pattern[23], 8, 24))
            )
            {
                k510_logd("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            #if !DDR_READ_EYE_LOOP_ALL
            else // is it right ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
            #endif
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        // k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        // k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        // k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        // k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        // k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        // k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        // k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        // k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);
        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd("mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 8 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop 1 by "
            "incrementing the values of READ DQS DLL SADJ and "
            "READ DQS_B SADJ until SADJ = max value.  End "
            "Training Loop 1 when max value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 1: incr_data is %d\n", __func__, incr_data);
        read_dqs_sadj = incr_data;
        read_dqs_b_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0), bit_get_field(read_dqs_sadj, 8, 0));
            set_read_dqs_b_sadj(bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0));
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }

        k510_logv(
            "Step 8b = Repeat Step 1\n"
            "Step 1 of 29 - LPDDR3 Read Eye Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logd("**************** Loop 1 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 1 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 1 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 9 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 10 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 1.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg,incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1,incr_good_avg0); //avg3 -> avg0 invert avg0 -> avg3 ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);
    k510_logi("---------------- %s Loop1 end ----------------\n", __func__);
    k510_logi("---------------- %s Loop2 start ----------------\n", __func__);
    k510_logv(
        "Step 11 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB.\n"
    );
    set_read_dqs_sadj(0,0,0,0);

    k510_logv(
        "Step 12 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 2 (find center of "
        "EYE for DQS while holding DQS_B fixed).\n"
    );

    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop  = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 2 :  single cycle start *****************\n");
        k510_logv(
            "Step 13 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 register. */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logv(
            "Step 14 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue and AXI READ of address location 0 to access "
            "known data pattern.\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 15 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare "
            "to pattern A. "
            "Save pass/fail results.\n"
        );

        /* read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17) != 0)
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated.\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it.\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            k510_logv("Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0.\n");

            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
                return -1;
            }
        }
        else
        {
            k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1\n");
            return -1;
        }


        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(mem_rdata[0], 8, 0)  == bit_get_field(pattern[0], 8, 0)) &&
                (bit_get_field(mem_rdata[1], 8, 0)  == bit_get_field(pattern[1], 8, 0)) &&
                (bit_get_field(mem_rdata[2], 8, 0)  == bit_get_field(pattern[2], 8, 0)) &&
                (bit_get_field(mem_rdata[3], 8, 0)  == bit_get_field(pattern[3], 8, 0)) &&
                (bit_get_field(mem_rdata[4], 8, 0)  == bit_get_field(pattern[4], 8, 0)) &&
                (bit_get_field(mem_rdata[5], 8, 0)  == bit_get_field(pattern[5], 8, 0)) &&
                (bit_get_field(mem_rdata[6], 8, 0)  == bit_get_field(pattern[6], 8, 0)) &&
                (bit_get_field(mem_rdata[7], 8, 0)  == bit_get_field(pattern[7], 8, 0)) &&
                (bit_get_field(mem_rdata[8], 8, 0)  == bit_get_field(pattern[8], 8, 0)) &&
                (bit_get_field(mem_rdata[9], 8, 0)  == bit_get_field(pattern[9], 8, 0)) &&
                (bit_get_field(mem_rdata[10], 8, 0) == bit_get_field(pattern[10], 8, 0)) &&
                (bit_get_field(mem_rdata[11], 8, 0) == bit_get_field(pattern[11], 8, 0)) &&
                (bit_get_field(mem_rdata[12], 8, 0) == bit_get_field(pattern[12], 8, 0)) &&
                (bit_get_field(mem_rdata[13], 8, 0) == bit_get_field(pattern[13], 8, 0)) &&
                (bit_get_field(mem_rdata[14], 8, 0) == bit_get_field(pattern[14], 8, 0)) &&
                (bit_get_field(mem_rdata[15], 8, 0) == bit_get_field(pattern[15], 8, 0)) &&
                (bit_get_field(mem_rdata[16], 8, 0) == bit_get_field(pattern[16], 8, 0)) &&
                (bit_get_field(mem_rdata[17], 8, 0) == bit_get_field(pattern[17], 8, 0)) &&
                (bit_get_field(mem_rdata[18], 8, 0) == bit_get_field(pattern[18], 8, 0)) &&
                (bit_get_field(mem_rdata[19], 8, 0) == bit_get_field(pattern[19], 8, 0)) &&
                (bit_get_field(mem_rdata[20], 8, 0) == bit_get_field(pattern[20], 8, 0)) &&
                (bit_get_field(mem_rdata[21], 8, 0) == bit_get_field(pattern[21], 8, 0)) &&
                (bit_get_field(mem_rdata[22], 8, 0) == bit_get_field(pattern[22], 8, 0)) &&
                (bit_get_field(mem_rdata[23], 8, 0) == bit_get_field(pattern[23], 8, 0))
            )
            {
                k510_logv("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 8)  == bit_get_field(pattern[0], 8, 8)) &&
                (bit_get_field(mem_rdata[1], 8, 8)  == bit_get_field(pattern[1], 8, 8)) &&
                (bit_get_field(mem_rdata[2], 8, 8)  == bit_get_field(pattern[2], 8, 8)) &&
                (bit_get_field(mem_rdata[3], 8, 8)  == bit_get_field(pattern[3], 8, 8)) &&
                (bit_get_field(mem_rdata[4], 8, 8)  == bit_get_field(pattern[4], 8, 8)) &&
                (bit_get_field(mem_rdata[5], 8, 8)  == bit_get_field(pattern[5], 8, 8)) &&
                (bit_get_field(mem_rdata[6], 8, 8)  == bit_get_field(pattern[6], 8, 8)) &&
                (bit_get_field(mem_rdata[7], 8, 8)  == bit_get_field(pattern[7], 8, 8)) &&
                (bit_get_field(mem_rdata[8], 8, 8)  == bit_get_field(pattern[8], 8, 8)) &&
                (bit_get_field(mem_rdata[9], 8, 8)  == bit_get_field(pattern[9], 8, 8)) &&
                (bit_get_field(mem_rdata[10], 8, 8) == bit_get_field(pattern[10], 8, 8)) &&
                (bit_get_field(mem_rdata[11], 8, 8) == bit_get_field(pattern[11], 8, 8)) &&
                (bit_get_field(mem_rdata[12], 8, 8) == bit_get_field(pattern[12], 8, 8)) &&
                (bit_get_field(mem_rdata[13], 8, 8) == bit_get_field(pattern[13], 8, 8)) &&
                (bit_get_field(mem_rdata[14], 8, 8) == bit_get_field(pattern[14], 8, 8)) &&
                (bit_get_field(mem_rdata[15], 8, 8) == bit_get_field(pattern[15], 8, 8)) &&
                (bit_get_field(mem_rdata[16], 8, 8) == bit_get_field(pattern[16], 8, 8)) &&
                (bit_get_field(mem_rdata[17], 8, 8) == bit_get_field(pattern[17], 8, 8)) &&
                (bit_get_field(mem_rdata[18], 8, 8) == bit_get_field(pattern[18], 8, 8)) &&
                (bit_get_field(mem_rdata[19], 8, 8) == bit_get_field(pattern[19], 8, 8)) &&
                (bit_get_field(mem_rdata[20], 8, 8) == bit_get_field(pattern[20], 8, 8)) &&
                (bit_get_field(mem_rdata[21], 8, 8) == bit_get_field(pattern[21], 8, 8)) &&
                (bit_get_field(mem_rdata[22], 8, 8) == bit_get_field(pattern[22], 8, 8)) &&
                (bit_get_field(mem_rdata[23], 8, 8) == bit_get_field(pattern[23], 8, 8))
            )
            {
                k510_logv("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 16)  == bit_get_field(pattern[0], 8, 16)) &&
                (bit_get_field(mem_rdata[1], 8, 16)  == bit_get_field(pattern[1], 8, 16)) &&
                (bit_get_field(mem_rdata[2], 8, 16)  == bit_get_field(pattern[2], 8, 16)) &&
                (bit_get_field(mem_rdata[3], 8, 16)  == bit_get_field(pattern[3], 8, 16)) &&
                (bit_get_field(mem_rdata[4], 8, 16)  == bit_get_field(pattern[4], 8, 16)) &&
                (bit_get_field(mem_rdata[5], 8, 16)  == bit_get_field(pattern[5], 8, 16)) &&
                (bit_get_field(mem_rdata[6], 8, 16)  == bit_get_field(pattern[6], 8, 16)) &&
                (bit_get_field(mem_rdata[7], 8, 16)  == bit_get_field(pattern[7], 8, 16)) &&
                (bit_get_field(mem_rdata[8], 8, 16)  == bit_get_field(pattern[8], 8, 16)) &&
                (bit_get_field(mem_rdata[9], 8, 16)  == bit_get_field(pattern[9], 8, 16)) &&
                (bit_get_field(mem_rdata[10], 8, 16) == bit_get_field(pattern[10], 8, 16)) &&
                (bit_get_field(mem_rdata[11], 8, 16) == bit_get_field(pattern[11], 8, 16)) &&
                (bit_get_field(mem_rdata[12], 8, 16) == bit_get_field(pattern[12], 8, 16)) &&
                (bit_get_field(mem_rdata[13], 8, 16) == bit_get_field(pattern[13], 8, 16)) &&
                (bit_get_field(mem_rdata[14], 8, 16) == bit_get_field(pattern[14], 8, 16)) &&
                (bit_get_field(mem_rdata[15], 8, 16) == bit_get_field(pattern[15], 8, 16)) &&
                (bit_get_field(mem_rdata[16], 8, 16) == bit_get_field(pattern[16], 8, 16)) &&
                (bit_get_field(mem_rdata[17], 8, 16) == bit_get_field(pattern[17], 8, 16)) &&
                (bit_get_field(mem_rdata[18], 8, 16) == bit_get_field(pattern[18], 8, 16)) &&
                (bit_get_field(mem_rdata[19], 8, 16) == bit_get_field(pattern[19], 8, 16)) &&
                (bit_get_field(mem_rdata[20], 8, 16) == bit_get_field(pattern[20], 8, 16)) &&
                (bit_get_field(mem_rdata[21], 8, 16) == bit_get_field(pattern[21], 8, 16)) &&
                (bit_get_field(mem_rdata[22], 8, 16) == bit_get_field(pattern[22], 8, 16)) &&
                (bit_get_field(mem_rdata[23], 8, 16) == bit_get_field(pattern[23], 8, 16))
            )
            {
                k510_logv("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 24)  == bit_get_field(pattern[0], 8, 24)) &&
                (bit_get_field(mem_rdata[1], 8, 24)  == bit_get_field(pattern[1], 8, 24)) &&
                (bit_get_field(mem_rdata[2], 8, 24)  == bit_get_field(pattern[2], 8, 24)) &&
                (bit_get_field(mem_rdata[3], 8, 24)  == bit_get_field(pattern[3], 8, 24)) &&
                (bit_get_field(mem_rdata[4], 8, 24)  == bit_get_field(pattern[4], 8, 24)) &&
                (bit_get_field(mem_rdata[5], 8, 24)  == bit_get_field(pattern[5], 8, 24)) &&
                (bit_get_field(mem_rdata[6], 8, 24)  == bit_get_field(pattern[6], 8, 24)) &&
                (bit_get_field(mem_rdata[7], 8, 24)  == bit_get_field(pattern[7], 8, 24)) &&
                (bit_get_field(mem_rdata[8], 8, 24)  == bit_get_field(pattern[8], 8, 24)) &&
                (bit_get_field(mem_rdata[9], 8, 24)  == bit_get_field(pattern[9], 8, 24)) &&
                (bit_get_field(mem_rdata[10], 8, 24) == bit_get_field(pattern[10], 8, 24)) &&
                (bit_get_field(mem_rdata[11], 8, 24) == bit_get_field(pattern[11], 8, 24)) &&
                (bit_get_field(mem_rdata[12], 8, 24) == bit_get_field(pattern[12], 8, 24)) &&
                (bit_get_field(mem_rdata[13], 8, 24) == bit_get_field(pattern[13], 8, 24)) &&
                (bit_get_field(mem_rdata[14], 8, 24) == bit_get_field(pattern[14], 8, 24)) &&
                (bit_get_field(mem_rdata[15], 8, 24) == bit_get_field(pattern[15], 8, 24)) &&
                (bit_get_field(mem_rdata[16], 8, 24) == bit_get_field(pattern[16], 8, 24)) &&
                (bit_get_field(mem_rdata[17], 8, 24) == bit_get_field(pattern[17], 8, 24)) &&
                (bit_get_field(mem_rdata[18], 8, 24) == bit_get_field(pattern[18], 8, 24)) &&
                (bit_get_field(mem_rdata[19], 8, 24) == bit_get_field(pattern[19], 8, 24)) &&
                (bit_get_field(mem_rdata[20], 8, 24) == bit_get_field(pattern[20], 8, 24)) &&
                (bit_get_field(mem_rdata[21], 8, 24) == bit_get_field(pattern[21], 8, 24)) &&
                (bit_get_field(mem_rdata[22], 8, 24) == bit_get_field(pattern[22], 8, 24)) &&
                (bit_get_field(mem_rdata[23], 8, 24) == bit_get_field(pattern[23], 8, 24))
            )
            {
                k510_logv("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            #if !DDR_READ_EYE_LOOP_ALL
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
            #endif
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        // k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        // k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        // k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        // k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        // k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        // k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        // k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        // k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);
        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd("mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 16 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by  "
            "incrementing the values of READ DQS DLL SADJ until  "
            "SADJ = max value.  End Training Loop 2 when the  "
            "max value is reached\n"
        );

        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 2: incr_data is %d\n", __func__, incr_data);
        read_dqs_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(read_dqs_sadj & 0xFF, read_dqs_sadj & 0xFF,
                    read_dqs_sadj & 0xFF, read_dqs_sadj & 0xFF);
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 2 :  single cycle end ****************\n");
    } //while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 2 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 2 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 17 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1\n"
    );

     //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set CRDB (bit[17] to 1.
    // regdata[17] = 1'b1;
    bit_set_bit(regdata, 17);
    //  Set SADJ WRT (bit[10]) to 1.
    // regdata[10] = 1'b1;
    bit_set_bit(regdata, 10);
    //  Clear DS_FRC_RG
    // ngb regdata[9] = 1'b0;
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    k510_logv(
        "Step 18 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = AVE of MIN and MAX pass values "
        "from Training Loop 2\n"
    );
    // set_read_dqs_sadj(incr_good_avg, incr_good_avg,
    //                  incr_good_avg, incr_good_avg);
    // set_read_dqs_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop2 end ----------------\n", __func__);

    incr_good_avg_dqs_p3 = incr_good_avg3;
    incr_good_avg_dqs_p2 = incr_good_avg2;
    incr_good_avg_dqs_p1 = incr_good_avg1;
    incr_good_avg_dqs_p0 = incr_good_avg0;

    k510_logi("---------------- %s Loop3 start ----------------\n", __func__);
    k510_logv(
        "Step 19 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB\n"
    );
    set_read_dqs_b_sadj(0,0,0,0);

    k510_logv(
        "Step 20 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Start of READ EYE Training Loop 3 (find center of EYE "
        "for DQS_B hold DQS fixed).\n"
    );
    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    continue_loop  = 1;
    while (continue_loop == 1)
    {
        k510_logd("**************** Loop 3 :  single cycle start *****************\n");
        k510_logv(
            "Step 21 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1\n"
        );
         //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        // regdata[17] = 1'b1;
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        // regdata[10] = 1'b1;
        bit_set_bit(regdata, 10);
        //  Clear DS_FRC_RG
        // ngb regdata[9] = 1'b0;
        //  Now write the new value to the TRAINING_CTRL1 register.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        k510_logv(
            "Step 22 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue AXI READ of address location 0 to accesss"
            "known data pattern\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 23 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB registers RBURST_0/1_P0/1/2/3 and compare "
            "to pattern A."
            "Save pass/fail results\n"
        );
        //  read the value of the TRAINING_CTRL1 register.
        // while(regdata[17] !== 0)
        // read_register("TRAINING_CTRL1",TRAINING_CTRL1_ADDR,
        // regdata, 1'b1);
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17))
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            k510_logv(
                "Verify Interrupt Status RBURST Captured (bit[7]) is "
                "now cleared to 0\n"
            );
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0\n");
            }
            else
            {
                k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
                return -1;
            }
        }
        else
        {
            k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Check if CRDB (bit[17] has been cleared.
        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(mem_rdata[0], 8, 0)  == bit_get_field(pattern[0], 8, 0)) &&
                (bit_get_field(mem_rdata[1], 8, 0)  == bit_get_field(pattern[1], 8, 0)) &&
                (bit_get_field(mem_rdata[2], 8, 0)  == bit_get_field(pattern[2], 8, 0)) &&
                (bit_get_field(mem_rdata[3], 8, 0)  == bit_get_field(pattern[3], 8, 0)) &&
                (bit_get_field(mem_rdata[4], 8, 0)  == bit_get_field(pattern[4], 8, 0)) &&
                (bit_get_field(mem_rdata[5], 8, 0)  == bit_get_field(pattern[5], 8, 0)) &&
                (bit_get_field(mem_rdata[6], 8, 0)  == bit_get_field(pattern[6], 8, 0)) &&
                (bit_get_field(mem_rdata[7], 8, 0)  == bit_get_field(pattern[7], 8, 0)) &&
                (bit_get_field(mem_rdata[8], 8, 0)  == bit_get_field(pattern[8], 8, 0)) &&
                (bit_get_field(mem_rdata[9], 8, 0)  == bit_get_field(pattern[9], 8, 0)) &&
                (bit_get_field(mem_rdata[10], 8, 0) == bit_get_field(pattern[10], 8, 0)) &&
                (bit_get_field(mem_rdata[11], 8, 0) == bit_get_field(pattern[11], 8, 0)) &&
                (bit_get_field(mem_rdata[12], 8, 0) == bit_get_field(pattern[12], 8, 0)) &&
                (bit_get_field(mem_rdata[13], 8, 0) == bit_get_field(pattern[13], 8, 0)) &&
                (bit_get_field(mem_rdata[14], 8, 0) == bit_get_field(pattern[14], 8, 0)) &&
                (bit_get_field(mem_rdata[15], 8, 0) == bit_get_field(pattern[15], 8, 0)) &&
                (bit_get_field(mem_rdata[16], 8, 0) == bit_get_field(pattern[16], 8, 0)) &&
                (bit_get_field(mem_rdata[17], 8, 0) == bit_get_field(pattern[17], 8, 0)) &&
                (bit_get_field(mem_rdata[18], 8, 0) == bit_get_field(pattern[18], 8, 0)) &&
                (bit_get_field(mem_rdata[19], 8, 0) == bit_get_field(pattern[19], 8, 0)) &&
                (bit_get_field(mem_rdata[20], 8, 0) == bit_get_field(pattern[20], 8, 0)) &&
                (bit_get_field(mem_rdata[21], 8, 0) == bit_get_field(pattern[21], 8, 0)) &&
                (bit_get_field(mem_rdata[22], 8, 0) == bit_get_field(pattern[22], 8, 0)) &&
                (bit_get_field(mem_rdata[23], 8, 0) == bit_get_field(pattern[23], 8, 0))
            )
            {
                k510_logv("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 8)  == bit_get_field(pattern[0], 8, 8)) &&
                (bit_get_field(mem_rdata[1], 8, 8)  == bit_get_field(pattern[1], 8, 8)) &&
                (bit_get_field(mem_rdata[2], 8, 8)  == bit_get_field(pattern[2], 8, 8)) &&
                (bit_get_field(mem_rdata[3], 8, 8)  == bit_get_field(pattern[3], 8, 8)) &&
                (bit_get_field(mem_rdata[4], 8, 8)  == bit_get_field(pattern[4], 8, 8)) &&
                (bit_get_field(mem_rdata[5], 8, 8)  == bit_get_field(pattern[5], 8, 8)) &&
                (bit_get_field(mem_rdata[6], 8, 8)  == bit_get_field(pattern[6], 8, 8)) &&
                (bit_get_field(mem_rdata[7], 8, 8)  == bit_get_field(pattern[7], 8, 8)) &&
                (bit_get_field(mem_rdata[8], 8, 8)  == bit_get_field(pattern[8], 8, 8)) &&
                (bit_get_field(mem_rdata[9], 8, 8)  == bit_get_field(pattern[9], 8, 8)) &&
                (bit_get_field(mem_rdata[10], 8, 8) == bit_get_field(pattern[10], 8, 8)) &&
                (bit_get_field(mem_rdata[11], 8, 8) == bit_get_field(pattern[11], 8, 8)) &&
                (bit_get_field(mem_rdata[12], 8, 8) == bit_get_field(pattern[12], 8, 8)) &&
                (bit_get_field(mem_rdata[13], 8, 8) == bit_get_field(pattern[13], 8, 8)) &&
                (bit_get_field(mem_rdata[14], 8, 8) == bit_get_field(pattern[14], 8, 8)) &&
                (bit_get_field(mem_rdata[15], 8, 8) == bit_get_field(pattern[15], 8, 8)) &&
                (bit_get_field(mem_rdata[16], 8, 8) == bit_get_field(pattern[16], 8, 8)) &&
                (bit_get_field(mem_rdata[17], 8, 8) == bit_get_field(pattern[17], 8, 8)) &&
                (bit_get_field(mem_rdata[18], 8, 8) == bit_get_field(pattern[18], 8, 8)) &&
                (bit_get_field(mem_rdata[19], 8, 8) == bit_get_field(pattern[19], 8, 8)) &&
                (bit_get_field(mem_rdata[20], 8, 8) == bit_get_field(pattern[20], 8, 8)) &&
                (bit_get_field(mem_rdata[21], 8, 8) == bit_get_field(pattern[21], 8, 8)) &&
                (bit_get_field(mem_rdata[22], 8, 8) == bit_get_field(pattern[22], 8, 8)) &&
                (bit_get_field(mem_rdata[23], 8, 8) == bit_get_field(pattern[23], 8, 8))
            )
            {
                k510_logv("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 16)  == bit_get_field(pattern[0], 8, 16)) &&
                (bit_get_field(mem_rdata[1], 8, 16)  == bit_get_field(pattern[1], 8, 16)) &&
                (bit_get_field(mem_rdata[2], 8, 16)  == bit_get_field(pattern[2], 8, 16)) &&
                (bit_get_field(mem_rdata[3], 8, 16)  == bit_get_field(pattern[3], 8, 16)) &&
                (bit_get_field(mem_rdata[4], 8, 16)  == bit_get_field(pattern[4], 8, 16)) &&
                (bit_get_field(mem_rdata[5], 8, 16)  == bit_get_field(pattern[5], 8, 16)) &&
                (bit_get_field(mem_rdata[6], 8, 16)  == bit_get_field(pattern[6], 8, 16)) &&
                (bit_get_field(mem_rdata[7], 8, 16)  == bit_get_field(pattern[7], 8, 16)) &&
                (bit_get_field(mem_rdata[8], 8, 16)  == bit_get_field(pattern[8], 8, 16)) &&
                (bit_get_field(mem_rdata[9], 8, 16)  == bit_get_field(pattern[9], 8, 16)) &&
                (bit_get_field(mem_rdata[10], 8, 16) == bit_get_field(pattern[10], 8, 16)) &&
                (bit_get_field(mem_rdata[11], 8, 16) == bit_get_field(pattern[11], 8, 16)) &&
                (bit_get_field(mem_rdata[12], 8, 16) == bit_get_field(pattern[12], 8, 16)) &&
                (bit_get_field(mem_rdata[13], 8, 16) == bit_get_field(pattern[13], 8, 16)) &&
                (bit_get_field(mem_rdata[14], 8, 16) == bit_get_field(pattern[14], 8, 16)) &&
                (bit_get_field(mem_rdata[15], 8, 16) == bit_get_field(pattern[15], 8, 16)) &&
                (bit_get_field(mem_rdata[16], 8, 16) == bit_get_field(pattern[16], 8, 16)) &&
                (bit_get_field(mem_rdata[17], 8, 16) == bit_get_field(pattern[17], 8, 16)) &&
                (bit_get_field(mem_rdata[18], 8, 16) == bit_get_field(pattern[18], 8, 16)) &&
                (bit_get_field(mem_rdata[19], 8, 16) == bit_get_field(pattern[19], 8, 16)) &&
                (bit_get_field(mem_rdata[20], 8, 16) == bit_get_field(pattern[20], 8, 16)) &&
                (bit_get_field(mem_rdata[21], 8, 16) == bit_get_field(pattern[21], 8, 16)) &&
                (bit_get_field(mem_rdata[22], 8, 16) == bit_get_field(pattern[22], 8, 16)) &&
                (bit_get_field(mem_rdata[23], 8, 16) == bit_get_field(pattern[23], 8, 16))
            )
            {
                k510_logv("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 24)  == bit_get_field(pattern[0], 8, 24)) &&
                (bit_get_field(mem_rdata[1], 8, 24)  == bit_get_field(pattern[1], 8, 24)) &&
                (bit_get_field(mem_rdata[2], 8, 24)  == bit_get_field(pattern[2], 8, 24)) &&
                (bit_get_field(mem_rdata[3], 8, 24)  == bit_get_field(pattern[3], 8, 24)) &&
                (bit_get_field(mem_rdata[4], 8, 24)  == bit_get_field(pattern[4], 8, 24)) &&
                (bit_get_field(mem_rdata[5], 8, 24)  == bit_get_field(pattern[5], 8, 24)) &&
                (bit_get_field(mem_rdata[6], 8, 24)  == bit_get_field(pattern[6], 8, 24)) &&
                (bit_get_field(mem_rdata[7], 8, 24)  == bit_get_field(pattern[7], 8, 24)) &&
                (bit_get_field(mem_rdata[8], 8, 24)  == bit_get_field(pattern[8], 8, 24)) &&
                (bit_get_field(mem_rdata[9], 8, 24)  == bit_get_field(pattern[9], 8, 24)) &&
                (bit_get_field(mem_rdata[10], 8, 24) == bit_get_field(pattern[10], 8, 24)) &&
                (bit_get_field(mem_rdata[11], 8, 24) == bit_get_field(pattern[11], 8, 24)) &&
                (bit_get_field(mem_rdata[12], 8, 24) == bit_get_field(pattern[12], 8, 24)) &&
                (bit_get_field(mem_rdata[13], 8, 24) == bit_get_field(pattern[13], 8, 24)) &&
                (bit_get_field(mem_rdata[14], 8, 24) == bit_get_field(pattern[14], 8, 24)) &&
                (bit_get_field(mem_rdata[15], 8, 24) == bit_get_field(pattern[15], 8, 24)) &&
                (bit_get_field(mem_rdata[16], 8, 24) == bit_get_field(pattern[16], 8, 24)) &&
                (bit_get_field(mem_rdata[17], 8, 24) == bit_get_field(pattern[17], 8, 24)) &&
                (bit_get_field(mem_rdata[18], 8, 24) == bit_get_field(pattern[18], 8, 24)) &&
                (bit_get_field(mem_rdata[19], 8, 24) == bit_get_field(pattern[19], 8, 24)) &&
                (bit_get_field(mem_rdata[20], 8, 24) == bit_get_field(pattern[20], 8, 24)) &&
                (bit_get_field(mem_rdata[21], 8, 24) == bit_get_field(pattern[21], 8, 24)) &&
                (bit_get_field(mem_rdata[22], 8, 24) == bit_get_field(pattern[22], 8, 24)) &&
                (bit_get_field(mem_rdata[23], 8, 24) == bit_get_field(pattern[23], 8, 24))
            )
            {
                k510_logv("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            #if !DDR_READ_EYE_LOOP_ALL
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
            #endif
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 == %d\n", incr_good_min0);
        k510_logd("incr_good_max0 == %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 == %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 == %d\n", incr_good_min1);
        k510_logd("incr_good_max1 == %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 == %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 == %d\n", incr_good_min2);
        k510_logd("incr_good_max2 == %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 == %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 == %d\n", incr_good_min3);
        k510_logd("incr_good_max3 == %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 == %d\n", incr_good_avg3);

        // k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        // k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        // k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        // k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        // k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        // k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        // k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        // k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);
        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd("mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 24 of 28 for LPDDR3 Read Eye Training"
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by"
            "incrementing the values of READ DQS_B DLL SADJ until"
            "SADJ = max value.  End Training Loop 3 when the max"
            "value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 3: incr_data is %d\n", __func__, incr_data);
        read_dqs_b_sadj = incr_data;
        if (incr_data > MAX_READ_DQS_B_SADJ)
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_b_sadj(bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0), bit_get_field(read_dqs_b_sadj, 8, 0));
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 3 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 3 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 3 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 25 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 26 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 3.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg, incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop3 end ----------------\n", __func__);
    k510_logv(
        "Step 27 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 0.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_clr_bit(regdata, 17);
    bit_clr_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 28 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Continue with regular DRAM commands.\n"
    );

    k510_logi("LPDDR3 Read Eye Training Complete\n");
    return 0;
}
#endif
#endif

#if 1
#if DDR_RE_TRAINING_READ_PATTERN
uint32_t Read_eye_training(void)
{
    uint32_t regdata = 0;
    // uint64_t value = 0;
    // int32_t i;
    // cache_enable();

    k510_logi("Begin LPDDR3 Read Eye Training  "
              "w/o Bit Deskew or VREF Training by Read pattern\n");

    k510_logv(
        "Step 0 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Issue an AXI READ of Address location 0 (note this "
        "location has been pre-written with a known value at "
        "low frequency prior to this operation.\n"
    );
    // memory_read(mem_addr, mem_rdata, .compare(0)); /* What's this ? */
    // memcpy((void *)mem_rdata, mem_addr, MEM_BYTE_CNT);
    // mem_rdata[0] = *(mem_addr);
    // mem_rdata[1] = *(mem_addr + 1);
    // mem_rdata[2] = *(mem_addr + 2);
    // mem_rdata[3] = *(mem_addr + 3);

    // cache_inval(0, 0, 128, L1_DCACHE);

    for(uint32_t i = 0; i < 24; i++)
    {
        mem_rdata[i] = *(mem_addr + i);
    }

    k510_logv(
        "Step 1 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set DFI frequency = 800 MHz for Memory operation "
        "of 3200Mbs.\n"
    );

    k510_logv(
        "Step 2 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_set_bit(regdata, 17);
    bit_set_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 3 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Set READ DQS DLL and READ DQS_B DLL SADJ=0 using the "
        "DLL_CTRL registers through the DDR PHY AHB. \n"
        "a. DLL_CTRL2 affects Data Slice 0\n"
        "b. DLL_CTRL3 affects Data Slice 1\n"
        "c. DLL_CTRL4 affects Data Slice 2\n"
        "d. DLL_CTRL5 affects Data Slice 3\n"
    );
    set_read_dqs_sadj(0,0,0,0);         /* function is OK? zzx */
    set_read_dqs_b_sadj(0,0,0,0);

    /* Starting with all bit delays at 0 */
    // write_register(BIT_RDLY_DS0_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0, 1);
    // write_register(BIT_RDLY_DS0_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS1_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS2_ADDR, 0x00FFFFFF, 1);
    // write_register(BIT_RDLY_DS3_ADDR, 0x00FFFFFF, 1);

    k510_logv(
        "Step 4 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set extend read gate bits.\n"
    );
    /* Extend read gate deassertion by 2 clks. */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);   // shorten the extension
    bit_set_field(regdata, 2, 28, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 20, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 12, DDR_READ_GATE_DELAY_DEASSERTION);
    bit_set_field(regdata, 2, 4,  DDR_READ_GATE_DELAY_DEASSERTION);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    cval_rb_0_p0 = pattern[0];
    cval_rb_0_p1 = pattern[1];
    cval_rb_0_p2 = pattern[2];
    cval_rb_0_p3 = pattern[3];
    cval_rb_1_p0 = pattern[4];
    cval_rb_1_p1 = pattern[5];
    cval_rb_1_p2 = pattern[6];
    cval_rb_1_p3 = pattern[7];

    k510_logi("---------------- %s Loop1 start ----------------\n", __func__);
    k510_logv(
        "Step 5 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 1 "
        "(find center of EYE for DQS/DQS_B).\n"
    );
    incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    found_stop0 = 0;
    found_stop1 = 0;
    found_stop2 = 0;
    found_stop3 = 0;

    continue_loop = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 1 :  single cycle start *****************\n");
        k510_logv(
            "Step 6 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue an AXI READ of address location 0 to access "
            "known data pattern.\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 7 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare to "
            "pattern A. "
            "Save pass/fail results.\n"
        );

        /* read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17) != 0)
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated.\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it.\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            /* Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0. */
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
                return -1;
            }
        }
        else
        {
            k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(mem_rdata[0], 8, 0)  == bit_get_field(pattern[0], 8, 0)) &&
                (bit_get_field(mem_rdata[1], 8, 0)  == bit_get_field(pattern[1], 8, 0)) &&
                (bit_get_field(mem_rdata[2], 8, 0)  == bit_get_field(pattern[2], 8, 0)) &&
                (bit_get_field(mem_rdata[3], 8, 0)  == bit_get_field(pattern[3], 8, 0)) &&
                (bit_get_field(mem_rdata[4], 8, 0)  == bit_get_field(pattern[4], 8, 0)) &&
                (bit_get_field(mem_rdata[5], 8, 0)  == bit_get_field(pattern[5], 8, 0)) &&
                (bit_get_field(mem_rdata[6], 8, 0)  == bit_get_field(pattern[6], 8, 0)) &&
                (bit_get_field(mem_rdata[7], 8, 0)  == bit_get_field(pattern[7], 8, 0)) &&
                (bit_get_field(mem_rdata[8], 8, 0)  == bit_get_field(pattern[8], 8, 0)) &&
                (bit_get_field(mem_rdata[9], 8, 0)  == bit_get_field(pattern[9], 8, 0)) &&
                (bit_get_field(mem_rdata[10], 8, 0) == bit_get_field(pattern[10], 8, 0)) &&
                (bit_get_field(mem_rdata[11], 8, 0) == bit_get_field(pattern[11], 8, 0)) &&
                (bit_get_field(mem_rdata[12], 8, 0) == bit_get_field(pattern[12], 8, 0)) &&
                (bit_get_field(mem_rdata[13], 8, 0) == bit_get_field(pattern[13], 8, 0)) &&
                (bit_get_field(mem_rdata[14], 8, 0) == bit_get_field(pattern[14], 8, 0)) &&
                (bit_get_field(mem_rdata[15], 8, 0) == bit_get_field(pattern[15], 8, 0)) &&
                (bit_get_field(mem_rdata[16], 8, 0) == bit_get_field(pattern[16], 8, 0)) &&
                (bit_get_field(mem_rdata[17], 8, 0) == bit_get_field(pattern[17], 8, 0)) &&
                (bit_get_field(mem_rdata[18], 8, 0) == bit_get_field(pattern[18], 8, 0)) &&
                (bit_get_field(mem_rdata[19], 8, 0) == bit_get_field(pattern[19], 8, 0)) &&
                (bit_get_field(mem_rdata[20], 8, 0) == bit_get_field(pattern[20], 8, 0)) &&
                (bit_get_field(mem_rdata[21], 8, 0) == bit_get_field(pattern[21], 8, 0)) &&
                (bit_get_field(mem_rdata[22], 8, 0) == bit_get_field(pattern[22], 8, 0)) &&
                (bit_get_field(mem_rdata[23], 8, 0) == bit_get_field(pattern[23], 8, 0)) && found_stop0 == 0
            )
            {
                k510_logd("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }
            else
            {
                if(found_pass0)
                {
                    found_stop0 = 1;     //DS0 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 8)  == bit_get_field(pattern[0], 8, 8)) &&
                (bit_get_field(mem_rdata[1], 8, 8)  == bit_get_field(pattern[1], 8, 8)) &&
                (bit_get_field(mem_rdata[2], 8, 8)  == bit_get_field(pattern[2], 8, 8)) &&
                (bit_get_field(mem_rdata[3], 8, 8)  == bit_get_field(pattern[3], 8, 8)) &&
                (bit_get_field(mem_rdata[4], 8, 8)  == bit_get_field(pattern[4], 8, 8)) &&
                (bit_get_field(mem_rdata[5], 8, 8)  == bit_get_field(pattern[5], 8, 8)) &&
                (bit_get_field(mem_rdata[6], 8, 8)  == bit_get_field(pattern[6], 8, 8)) &&
                (bit_get_field(mem_rdata[7], 8, 8)  == bit_get_field(pattern[7], 8, 8)) &&
                (bit_get_field(mem_rdata[8], 8, 8)  == bit_get_field(pattern[8], 8, 8)) &&
                (bit_get_field(mem_rdata[9], 8, 8)  == bit_get_field(pattern[9], 8, 8)) &&
                (bit_get_field(mem_rdata[10], 8, 8) == bit_get_field(pattern[10], 8, 8)) &&
                (bit_get_field(mem_rdata[11], 8, 8) == bit_get_field(pattern[11], 8, 8)) &&
                (bit_get_field(mem_rdata[12], 8, 8) == bit_get_field(pattern[12], 8, 8)) &&
                (bit_get_field(mem_rdata[13], 8, 8) == bit_get_field(pattern[13], 8, 8)) &&
                (bit_get_field(mem_rdata[14], 8, 8) == bit_get_field(pattern[14], 8, 8)) &&
                (bit_get_field(mem_rdata[15], 8, 8) == bit_get_field(pattern[15], 8, 8)) &&
                (bit_get_field(mem_rdata[16], 8, 8) == bit_get_field(pattern[16], 8, 8)) &&
                (bit_get_field(mem_rdata[17], 8, 8) == bit_get_field(pattern[17], 8, 8)) &&
                (bit_get_field(mem_rdata[18], 8, 8) == bit_get_field(pattern[18], 8, 8)) &&
                (bit_get_field(mem_rdata[19], 8, 8) == bit_get_field(pattern[19], 8, 8)) &&
                (bit_get_field(mem_rdata[20], 8, 8) == bit_get_field(pattern[20], 8, 8)) &&
                (bit_get_field(mem_rdata[21], 8, 8) == bit_get_field(pattern[21], 8, 8)) &&
                (bit_get_field(mem_rdata[22], 8, 8) == bit_get_field(pattern[22], 8, 8)) &&
                (bit_get_field(mem_rdata[23], 8, 8) == bit_get_field(pattern[23], 8, 8)) && found_stop1 == 0
            )
            {
                k510_logd("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }
            else
            {
                if(found_pass1)
                {
                    found_stop1 = 1;     //DS1 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 16)  == bit_get_field(pattern[0], 8, 16)) &&
                (bit_get_field(mem_rdata[1], 8, 16)  == bit_get_field(pattern[1], 8, 16)) &&
                (bit_get_field(mem_rdata[2], 8, 16)  == bit_get_field(pattern[2], 8, 16)) &&
                (bit_get_field(mem_rdata[3], 8, 16)  == bit_get_field(pattern[3], 8, 16)) &&
                (bit_get_field(mem_rdata[4], 8, 16)  == bit_get_field(pattern[4], 8, 16)) &&
                (bit_get_field(mem_rdata[5], 8, 16)  == bit_get_field(pattern[5], 8, 16)) &&
                (bit_get_field(mem_rdata[6], 8, 16)  == bit_get_field(pattern[6], 8, 16)) &&
                (bit_get_field(mem_rdata[7], 8, 16)  == bit_get_field(pattern[7], 8, 16)) &&
                (bit_get_field(mem_rdata[8], 8, 16)  == bit_get_field(pattern[8], 8, 16)) &&
                (bit_get_field(mem_rdata[9], 8, 16)  == bit_get_field(pattern[9], 8, 16)) &&
                (bit_get_field(mem_rdata[10], 8, 16) == bit_get_field(pattern[10], 8, 16)) &&
                (bit_get_field(mem_rdata[11], 8, 16) == bit_get_field(pattern[11], 8, 16)) &&
                (bit_get_field(mem_rdata[12], 8, 16) == bit_get_field(pattern[12], 8, 16)) &&
                (bit_get_field(mem_rdata[13], 8, 16) == bit_get_field(pattern[13], 8, 16)) &&
                (bit_get_field(mem_rdata[14], 8, 16) == bit_get_field(pattern[14], 8, 16)) &&
                (bit_get_field(mem_rdata[15], 8, 16) == bit_get_field(pattern[15], 8, 16)) &&
                (bit_get_field(mem_rdata[16], 8, 16) == bit_get_field(pattern[16], 8, 16)) &&
                (bit_get_field(mem_rdata[17], 8, 16) == bit_get_field(pattern[17], 8, 16)) &&
                (bit_get_field(mem_rdata[18], 8, 16) == bit_get_field(pattern[18], 8, 16)) &&
                (bit_get_field(mem_rdata[19], 8, 16) == bit_get_field(pattern[19], 8, 16)) &&
                (bit_get_field(mem_rdata[20], 8, 16) == bit_get_field(pattern[20], 8, 16)) &&
                (bit_get_field(mem_rdata[21], 8, 16) == bit_get_field(pattern[21], 8, 16)) &&
                (bit_get_field(mem_rdata[22], 8, 16) == bit_get_field(pattern[22], 8, 16)) &&
                (bit_get_field(mem_rdata[23], 8, 16) == bit_get_field(pattern[23], 8, 16)) && found_stop2 == 0
            )
            {
                k510_logd("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }
            else
            {
                if(found_pass2)
                {
                    found_stop2 = 1;     //DS2 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 24)  == bit_get_field(pattern[0], 8, 24)) &&
                (bit_get_field(mem_rdata[1], 8, 24)  == bit_get_field(pattern[1], 8, 24)) &&
                (bit_get_field(mem_rdata[2], 8, 24)  == bit_get_field(pattern[2], 8, 24)) &&
                (bit_get_field(mem_rdata[3], 8, 24)  == bit_get_field(pattern[3], 8, 24)) &&
                (bit_get_field(mem_rdata[4], 8, 24)  == bit_get_field(pattern[4], 8, 24)) &&
                (bit_get_field(mem_rdata[5], 8, 24)  == bit_get_field(pattern[5], 8, 24)) &&
                (bit_get_field(mem_rdata[6], 8, 24)  == bit_get_field(pattern[6], 8, 24)) &&
                (bit_get_field(mem_rdata[7], 8, 24)  == bit_get_field(pattern[7], 8, 24)) &&
                (bit_get_field(mem_rdata[8], 8, 24)  == bit_get_field(pattern[8], 8, 24)) &&
                (bit_get_field(mem_rdata[9], 8, 24)  == bit_get_field(pattern[9], 8, 24)) &&
                (bit_get_field(mem_rdata[10], 8, 24) == bit_get_field(pattern[10], 8, 24)) &&
                (bit_get_field(mem_rdata[11], 8, 24) == bit_get_field(pattern[11], 8, 24)) &&
                (bit_get_field(mem_rdata[12], 8, 24) == bit_get_field(pattern[12], 8, 24)) &&
                (bit_get_field(mem_rdata[13], 8, 24) == bit_get_field(pattern[13], 8, 24)) &&
                (bit_get_field(mem_rdata[14], 8, 24) == bit_get_field(pattern[14], 8, 24)) &&
                (bit_get_field(mem_rdata[15], 8, 24) == bit_get_field(pattern[15], 8, 24)) &&
                (bit_get_field(mem_rdata[16], 8, 24) == bit_get_field(pattern[16], 8, 24)) &&
                (bit_get_field(mem_rdata[17], 8, 24) == bit_get_field(pattern[17], 8, 24)) &&
                (bit_get_field(mem_rdata[18], 8, 24) == bit_get_field(pattern[18], 8, 24)) &&
                (bit_get_field(mem_rdata[19], 8, 24) == bit_get_field(pattern[19], 8, 24)) &&
                (bit_get_field(mem_rdata[20], 8, 24) == bit_get_field(pattern[20], 8, 24)) &&
                (bit_get_field(mem_rdata[21], 8, 24) == bit_get_field(pattern[21], 8, 24)) &&
                (bit_get_field(mem_rdata[22], 8, 24) == bit_get_field(pattern[22], 8, 24)) &&
                (bit_get_field(mem_rdata[23], 8, 24) == bit_get_field(pattern[23], 8, 24)) && found_stop3 == 0
            )
            {
                k510_logd("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else
            {
                if(found_pass3)
                {
                    found_stop3 = 1;     //DS3 stop training
                }
            }

            #if !DDR_READ_EYE_LOOP_ALL
            else // is it right ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
            #endif
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        // k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        // k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        // k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        // k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        // k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        // k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        // k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        // k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);
        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd("mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 8 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop 1 by "
            "incrementing the values of READ DQS DLL SADJ and "
            "READ DQS_B SADJ until SADJ = max value.  End "
            "Training Loop 1 when max value is reached.\n"
        );
        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 1: incr_data is %d\n", __func__, incr_data);
        // read_dqs_sadj = incr_data;
        // read_dqs_b_sadj = incr_data;
        if(found_stop0 == 0)
        {
            rd_dqs_sadj[0] = incr_data;
            rd_dqs_b_sadj[0] = incr_data;
        }
        if(found_stop1 == 0)
        {
            rd_dqs_sadj[1] = incr_data;
            rd_dqs_b_sadj[1] = incr_data;
        }
        if(found_stop2 == 0)
        {
            rd_dqs_sadj[2] = incr_data;
            rd_dqs_b_sadj[2] = incr_data;
        }
        if(found_stop3 == 0)
        {
            rd_dqs_sadj[3] = incr_data;
            rd_dqs_b_sadj[3] = incr_data;
        }

        if ((incr_data > MAX_READ_DQS_SADJ) || (found_stop0 && found_stop1 && found_stop2 && found_stop3))
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(rd_dqs_sadj[0], rd_dqs_sadj[1], rd_dqs_sadj[2], rd_dqs_sadj[3]);
            set_read_dqs_b_sadj(rd_dqs_b_sadj[0], rd_dqs_b_sadj[1], rd_dqs_b_sadj[2], rd_dqs_b_sadj[3]);
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }

        k510_logv(
            "Step 8b = Repeat Step 1\n"
            "Step 1 of 29 - LPDDR3 Read Eye Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logd("**************** Loop 1 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 1 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 1 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 1 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 9 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 10 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 1.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg,incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1,incr_good_avg0); //avg3 -> avg0 invert avg0 -> avg3 ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);
    k510_logi("---------------- %s Loop1 end ----------------\n", __func__);
    k510_logi("---------------- %s Loop2 start ----------------\n", __func__);
    k510_logv(
        "Step 11 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB.\n"
    );
    set_read_dqs_sadj(0,0,0,0);

    k510_logv(
        "Step 12 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Start of READ EYE Training Loop 2 (find center of "
        "EYE for DQS while holding DQS_B fixed).\n"
    );

    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    found_stop0 = 0;
    found_stop1 = 0;
    found_stop2 = 0;
    found_stop3 = 0;

    continue_loop  = 1;

    while(continue_loop == 1)
    {
        k510_logd("**************** Loop 2 :  single cycle start *****************\n");
        k510_logv(
            "Step 13 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        /* Set CRDB (bit[17] to 1. */
        bit_set_bit(regdata, 17);
        /* Set SADJ WRT (bit[10]) to 1. */
        bit_set_bit(regdata, 10);
        /* Now write the new value to the TRAINING_CTRL1 register. */
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        k510_logv(
            "Step 14 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue and AXI READ of address location 0 to access "
            "known data pattern.\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 15 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB Registers RBURST_0/1_P0/1/2/3 and compare "
            "to pattern A. "
            "Save pass/fail results.\n"
        );

        /* read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17) != 0)
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated.\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);

        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it.\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            k510_logv("Verify Interrupt Status RBURST Captured (bit[7]) is now cleared to 0.\n");

            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0.\n");
            }
            else
            {
                k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0\n");
                return -1;
            }
        }
        else
        {
            k510_logi("ERR: Interrupt Status RBURST Captured (bit[7]) was NOT set to 1\n");
            return -1;
        }


        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(mem_rdata[0], 8, 0)  == bit_get_field(pattern[0], 8, 0)) &&
                (bit_get_field(mem_rdata[1], 8, 0)  == bit_get_field(pattern[1], 8, 0)) &&
                (bit_get_field(mem_rdata[2], 8, 0)  == bit_get_field(pattern[2], 8, 0)) &&
                (bit_get_field(mem_rdata[3], 8, 0)  == bit_get_field(pattern[3], 8, 0)) &&
                (bit_get_field(mem_rdata[4], 8, 0)  == bit_get_field(pattern[4], 8, 0)) &&
                (bit_get_field(mem_rdata[5], 8, 0)  == bit_get_field(pattern[5], 8, 0)) &&
                (bit_get_field(mem_rdata[6], 8, 0)  == bit_get_field(pattern[6], 8, 0)) &&
                (bit_get_field(mem_rdata[7], 8, 0)  == bit_get_field(pattern[7], 8, 0)) &&
                (bit_get_field(mem_rdata[8], 8, 0)  == bit_get_field(pattern[8], 8, 0)) &&
                (bit_get_field(mem_rdata[9], 8, 0)  == bit_get_field(pattern[9], 8, 0)) &&
                (bit_get_field(mem_rdata[10], 8, 0) == bit_get_field(pattern[10], 8, 0)) &&
                (bit_get_field(mem_rdata[11], 8, 0) == bit_get_field(pattern[11], 8, 0)) &&
                (bit_get_field(mem_rdata[12], 8, 0) == bit_get_field(pattern[12], 8, 0)) &&
                (bit_get_field(mem_rdata[13], 8, 0) == bit_get_field(pattern[13], 8, 0)) &&
                (bit_get_field(mem_rdata[14], 8, 0) == bit_get_field(pattern[14], 8, 0)) &&
                (bit_get_field(mem_rdata[15], 8, 0) == bit_get_field(pattern[15], 8, 0)) &&
                (bit_get_field(mem_rdata[16], 8, 0) == bit_get_field(pattern[16], 8, 0)) &&
                (bit_get_field(mem_rdata[17], 8, 0) == bit_get_field(pattern[17], 8, 0)) &&
                (bit_get_field(mem_rdata[18], 8, 0) == bit_get_field(pattern[18], 8, 0)) &&
                (bit_get_field(mem_rdata[19], 8, 0) == bit_get_field(pattern[19], 8, 0)) &&
                (bit_get_field(mem_rdata[20], 8, 0) == bit_get_field(pattern[20], 8, 0)) &&
                (bit_get_field(mem_rdata[21], 8, 0) == bit_get_field(pattern[21], 8, 0)) &&
                (bit_get_field(mem_rdata[22], 8, 0) == bit_get_field(pattern[22], 8, 0)) &&
                (bit_get_field(mem_rdata[23], 8, 0) == bit_get_field(pattern[23], 8, 0)) && found_stop0 == 0
            )
            {
                k510_logd("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }
            else
            {
                if(found_pass0)
                {
                    found_stop0 = 1;     //DS0 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 8)  == bit_get_field(pattern[0], 8, 8)) &&
                (bit_get_field(mem_rdata[1], 8, 8)  == bit_get_field(pattern[1], 8, 8)) &&
                (bit_get_field(mem_rdata[2], 8, 8)  == bit_get_field(pattern[2], 8, 8)) &&
                (bit_get_field(mem_rdata[3], 8, 8)  == bit_get_field(pattern[3], 8, 8)) &&
                (bit_get_field(mem_rdata[4], 8, 8)  == bit_get_field(pattern[4], 8, 8)) &&
                (bit_get_field(mem_rdata[5], 8, 8)  == bit_get_field(pattern[5], 8, 8)) &&
                (bit_get_field(mem_rdata[6], 8, 8)  == bit_get_field(pattern[6], 8, 8)) &&
                (bit_get_field(mem_rdata[7], 8, 8)  == bit_get_field(pattern[7], 8, 8)) &&
                (bit_get_field(mem_rdata[8], 8, 8)  == bit_get_field(pattern[8], 8, 8)) &&
                (bit_get_field(mem_rdata[9], 8, 8)  == bit_get_field(pattern[9], 8, 8)) &&
                (bit_get_field(mem_rdata[10], 8, 8) == bit_get_field(pattern[10], 8, 8)) &&
                (bit_get_field(mem_rdata[11], 8, 8) == bit_get_field(pattern[11], 8, 8)) &&
                (bit_get_field(mem_rdata[12], 8, 8) == bit_get_field(pattern[12], 8, 8)) &&
                (bit_get_field(mem_rdata[13], 8, 8) == bit_get_field(pattern[13], 8, 8)) &&
                (bit_get_field(mem_rdata[14], 8, 8) == bit_get_field(pattern[14], 8, 8)) &&
                (bit_get_field(mem_rdata[15], 8, 8) == bit_get_field(pattern[15], 8, 8)) &&
                (bit_get_field(mem_rdata[16], 8, 8) == bit_get_field(pattern[16], 8, 8)) &&
                (bit_get_field(mem_rdata[17], 8, 8) == bit_get_field(pattern[17], 8, 8)) &&
                (bit_get_field(mem_rdata[18], 8, 8) == bit_get_field(pattern[18], 8, 8)) &&
                (bit_get_field(mem_rdata[19], 8, 8) == bit_get_field(pattern[19], 8, 8)) &&
                (bit_get_field(mem_rdata[20], 8, 8) == bit_get_field(pattern[20], 8, 8)) &&
                (bit_get_field(mem_rdata[21], 8, 8) == bit_get_field(pattern[21], 8, 8)) &&
                (bit_get_field(mem_rdata[22], 8, 8) == bit_get_field(pattern[22], 8, 8)) &&
                (bit_get_field(mem_rdata[23], 8, 8) == bit_get_field(pattern[23], 8, 8)) && found_stop1 == 0
            )
            {
                k510_logd("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }
            else
            {
                if(found_pass1)
                {
                    found_stop1 = 1;     //DS1 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 16)  == bit_get_field(pattern[0], 8, 16)) &&
                (bit_get_field(mem_rdata[1], 8, 16)  == bit_get_field(pattern[1], 8, 16)) &&
                (bit_get_field(mem_rdata[2], 8, 16)  == bit_get_field(pattern[2], 8, 16)) &&
                (bit_get_field(mem_rdata[3], 8, 16)  == bit_get_field(pattern[3], 8, 16)) &&
                (bit_get_field(mem_rdata[4], 8, 16)  == bit_get_field(pattern[4], 8, 16)) &&
                (bit_get_field(mem_rdata[5], 8, 16)  == bit_get_field(pattern[5], 8, 16)) &&
                (bit_get_field(mem_rdata[6], 8, 16)  == bit_get_field(pattern[6], 8, 16)) &&
                (bit_get_field(mem_rdata[7], 8, 16)  == bit_get_field(pattern[7], 8, 16)) &&
                (bit_get_field(mem_rdata[8], 8, 16)  == bit_get_field(pattern[8], 8, 16)) &&
                (bit_get_field(mem_rdata[9], 8, 16)  == bit_get_field(pattern[9], 8, 16)) &&
                (bit_get_field(mem_rdata[10], 8, 16) == bit_get_field(pattern[10], 8, 16)) &&
                (bit_get_field(mem_rdata[11], 8, 16) == bit_get_field(pattern[11], 8, 16)) &&
                (bit_get_field(mem_rdata[12], 8, 16) == bit_get_field(pattern[12], 8, 16)) &&
                (bit_get_field(mem_rdata[13], 8, 16) == bit_get_field(pattern[13], 8, 16)) &&
                (bit_get_field(mem_rdata[14], 8, 16) == bit_get_field(pattern[14], 8, 16)) &&
                (bit_get_field(mem_rdata[15], 8, 16) == bit_get_field(pattern[15], 8, 16)) &&
                (bit_get_field(mem_rdata[16], 8, 16) == bit_get_field(pattern[16], 8, 16)) &&
                (bit_get_field(mem_rdata[17], 8, 16) == bit_get_field(pattern[17], 8, 16)) &&
                (bit_get_field(mem_rdata[18], 8, 16) == bit_get_field(pattern[18], 8, 16)) &&
                (bit_get_field(mem_rdata[19], 8, 16) == bit_get_field(pattern[19], 8, 16)) &&
                (bit_get_field(mem_rdata[20], 8, 16) == bit_get_field(pattern[20], 8, 16)) &&
                (bit_get_field(mem_rdata[21], 8, 16) == bit_get_field(pattern[21], 8, 16)) &&
                (bit_get_field(mem_rdata[22], 8, 16) == bit_get_field(pattern[22], 8, 16)) &&
                (bit_get_field(mem_rdata[23], 8, 16) == bit_get_field(pattern[23], 8, 16)) && found_stop2 == 0
            )
            {
                k510_logd("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }
            else
            {
                if(found_pass2)
                {
                    found_stop2 = 1;     //DS2 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 24)  == bit_get_field(pattern[0], 8, 24)) &&
                (bit_get_field(mem_rdata[1], 8, 24)  == bit_get_field(pattern[1], 8, 24)) &&
                (bit_get_field(mem_rdata[2], 8, 24)  == bit_get_field(pattern[2], 8, 24)) &&
                (bit_get_field(mem_rdata[3], 8, 24)  == bit_get_field(pattern[3], 8, 24)) &&
                (bit_get_field(mem_rdata[4], 8, 24)  == bit_get_field(pattern[4], 8, 24)) &&
                (bit_get_field(mem_rdata[5], 8, 24)  == bit_get_field(pattern[5], 8, 24)) &&
                (bit_get_field(mem_rdata[6], 8, 24)  == bit_get_field(pattern[6], 8, 24)) &&
                (bit_get_field(mem_rdata[7], 8, 24)  == bit_get_field(pattern[7], 8, 24)) &&
                (bit_get_field(mem_rdata[8], 8, 24)  == bit_get_field(pattern[8], 8, 24)) &&
                (bit_get_field(mem_rdata[9], 8, 24)  == bit_get_field(pattern[9], 8, 24)) &&
                (bit_get_field(mem_rdata[10], 8, 24) == bit_get_field(pattern[10], 8, 24)) &&
                (bit_get_field(mem_rdata[11], 8, 24) == bit_get_field(pattern[11], 8, 24)) &&
                (bit_get_field(mem_rdata[12], 8, 24) == bit_get_field(pattern[12], 8, 24)) &&
                (bit_get_field(mem_rdata[13], 8, 24) == bit_get_field(pattern[13], 8, 24)) &&
                (bit_get_field(mem_rdata[14], 8, 24) == bit_get_field(pattern[14], 8, 24)) &&
                (bit_get_field(mem_rdata[15], 8, 24) == bit_get_field(pattern[15], 8, 24)) &&
                (bit_get_field(mem_rdata[16], 8, 24) == bit_get_field(pattern[16], 8, 24)) &&
                (bit_get_field(mem_rdata[17], 8, 24) == bit_get_field(pattern[17], 8, 24)) &&
                (bit_get_field(mem_rdata[18], 8, 24) == bit_get_field(pattern[18], 8, 24)) &&
                (bit_get_field(mem_rdata[19], 8, 24) == bit_get_field(pattern[19], 8, 24)) &&
                (bit_get_field(mem_rdata[20], 8, 24) == bit_get_field(pattern[20], 8, 24)) &&
                (bit_get_field(mem_rdata[21], 8, 24) == bit_get_field(pattern[21], 8, 24)) &&
                (bit_get_field(mem_rdata[22], 8, 24) == bit_get_field(pattern[22], 8, 24)) &&
                (bit_get_field(mem_rdata[23], 8, 24) == bit_get_field(pattern[23], 8, 24)) && found_stop3 == 0
            )
            {
                k510_logd("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else
            {
                if(found_pass3)
                {
                    found_stop3 = 1;     //DS3 stop training
                }
            }
            #if !DDR_READ_EYE_LOOP_ALL
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
            #endif
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 = %d\n", incr_good_min0);
        k510_logd("incr_good_max0 = %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 = %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 = %d\n", incr_good_min1);
        k510_logd("incr_good_max1 = %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 = %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 = %d\n", incr_good_min2);
        k510_logd("incr_good_max2 = %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 = %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 = %d\n", incr_good_min3);
        k510_logd("incr_good_max3 = %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 = %d\n", incr_good_avg3);

        // k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        // k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        // k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        // k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        // k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        // k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        // k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        // k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);
        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd("mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 16 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by  "
            "incrementing the values of READ DQS DLL SADJ until  "
            "SADJ = max value.  End Training Loop 2 when the  "
            "max value is reached\n"
        );

        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 2: incr_data is %d\n", __func__, incr_data);
        if(found_stop0 == 0)
        {
            rd_dqs_sadj[0] = incr_data;
        }
        if(found_stop1 == 0)
        {
            rd_dqs_sadj[1] = incr_data;
        }
        if(found_stop2 == 0)
        {
            rd_dqs_sadj[2] = incr_data;
        }
        if(found_stop3 == 0)
        {
            rd_dqs_sadj[3] = incr_data;
        }
        // read_dqs_sadj = incr_data;
        if ((incr_data > MAX_READ_DQS_SADJ) || (found_stop0 && found_stop1 && found_stop2 && found_stop3))
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_sadj(rd_dqs_sadj[0], rd_dqs_sadj[1], rd_dqs_sadj[2], rd_dqs_sadj[3]);
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 2 :  single cycle end ****************\n");
    } //while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 2 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 2 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 2 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 17 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1\n"
    );

     //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set CRDB (bit[17] to 1.
    // regdata[17] = 1'b1;
    bit_set_bit(regdata, 17);
    //  Set SADJ WRT (bit[10]) to 1.
    // regdata[10] = 1'b1;
    bit_set_bit(regdata, 10);
    //  Clear DS_FRC_RG
    // ngb regdata[9] = 1'b0;
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    k510_logv(
        "Step 18 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS DLL SADJ = AVE of MIN and MAX pass values "
        "from Training Loop 2\n"
    );
    // set_read_dqs_sadj(incr_good_avg, incr_good_avg,
    //                  incr_good_avg, incr_good_avg);
    // set_read_dqs_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop2 end ----------------\n", __func__);

    incr_good_avg_dqs_p3 = incr_good_avg3;
    incr_good_avg_dqs_p2 = incr_good_avg2;
    incr_good_avg_dqs_p1 = incr_good_avg1;
    incr_good_avg_dqs_p0 = incr_good_avg0;

    k510_logi("---------------- %s Loop3 start ----------------\n", __func__);
    k510_logv(
        "Step 19 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = 0 using the DLL_CTRL2,3,4,5 "
        "registers through the DDR PHY AHB\n"
    );
    set_read_dqs_b_sadj(0,0,0,0);

    k510_logv(
        "Step 20 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training \n"
        "Start of READ EYE Training Loop 3 (find center of EYE "
        "for DQS_B hold DQS fixed).\n"
    );
    incr_data      = 0;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    incr_good_min0  = 99;
    incr_good_max0  = 0;
    found_pass0 = 0;
    incr_good_min1  = 99;
    incr_good_max1  = 0;
    found_pass1 = 0;
    incr_good_min2  = 99;
    incr_good_max2  = 0;
    found_pass2 = 0;
    incr_good_min3  = 99;
    incr_good_max3  = 0;
    found_pass3 = 0;

    found_stop0 = 0;
    found_stop1 = 0;
    found_stop2 = 0;
    found_stop3 = 0;

    continue_loop  = 1;
    while (continue_loop == 1)
    {
        k510_logd("**************** Loop 3 :  single cycle start *****************\n");
        k510_logv(
            "Step 21 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1\n"
        );
         //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        // regdata[17] = 1'b1;
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        // regdata[10] = 1'b1;
        bit_set_bit(regdata, 10);
        //  Clear DS_FRC_RG
        // ngb regdata[9] = 1'b0;
        //  Now write the new value to the TRAINING_CTRL1 register.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        k510_logv(
            "Step 22 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Issue AXI READ of address location 0 to accesss"
            "known data pattern\n"
        );
        // memory_read(mem_addr, mem_rdata, .compare(0));
        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        k510_logv(
            "Step 23 of 28 for LPDDR3 Read Eye Training "
            "w/o Bit Deskew or VREF Training\n"
            "Read AHB registers RBURST_0/1_P0/1/2/3 and compare "
            "to pattern A."
            "Save pass/fail results\n"
        );
        //  read the value of the TRAINING_CTRL1 register.
        // while(regdata[17] !== 0)
        // read_register("TRAINING_CTRL1",TRAINING_CTRL1_ADDR,
        // regdata, 1'b1);
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        while(bit_check_bit(regdata, 17))
        {
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        }

        k510_logv(
            "Verify Interrupt Status RBURST Captured (bit[7]) is "
            "set to 1.  A 1 indicates the RBURST registers have "
            "been updated\n"
        );
        regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
        if(bit_check_bit(regdata, 7))
        {
            k510_logv(
                "Interrupt Status RBURST Captured (bit[7]) was "
                "correctly set to 1.\n"
                "Now write 1 to the sticky RBURST Captured (bit[7]) "
                "to clear it\n"
            );
            write_register(INTERRUPT_STATUS_ADDR, regdata, 1);

            k510_logv(
                "Verify Interrupt Status RBURST Captured (bit[7]) is "
                "now cleared to 0\n"
            );
            regdata = read_register(INTERRUPT_STATUS_ADDR, 1);
            if(bit_check_bit(regdata, 7) == 0)
            {
                k510_logd("Interrupt Status RBURST Captured (bit[7]) was correctly cleared to 0\n");
            }
            else
            {
                k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT cleared to 0.\n");
                return -1;
            }
        }
        else
        {
            k510_loge("Interrupt Status RBURST Captured (bit[7]) was NOT set to 1.\n");
            return -1;
        }

        val_rb_0_p0 = read_register(RBURST_0_P0_ADDR, 1);
        val_rb_0_p1 = read_register(RBURST_0_P1_ADDR, 1);
        val_rb_0_p2 = read_register(RBURST_0_P2_ADDR, 1);
        val_rb_0_p3 = read_register(RBURST_0_P3_ADDR, 1);
        val_rb_1_p0 = read_register(RBURST_1_P0_ADDR, 1);
        val_rb_1_p1 = read_register(RBURST_1_P1_ADDR, 1);
        val_rb_1_p2 = read_register(RBURST_1_P2_ADDR, 1);
        val_rb_1_p3 = read_register(RBURST_1_P3_ADDR, 1);

        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Check if CRDB (bit[17] has been cleared.
        /* Check if CRDB (bit[17] has been cleared. */
        if(bit_check_bit(regdata, 17) == 0)
        {
            if(
                (bit_get_field(mem_rdata[0], 8, 0)  == bit_get_field(pattern[0], 8, 0)) &&
                (bit_get_field(mem_rdata[1], 8, 0)  == bit_get_field(pattern[1], 8, 0)) &&
                (bit_get_field(mem_rdata[2], 8, 0)  == bit_get_field(pattern[2], 8, 0)) &&
                (bit_get_field(mem_rdata[3], 8, 0)  == bit_get_field(pattern[3], 8, 0)) &&
                (bit_get_field(mem_rdata[4], 8, 0)  == bit_get_field(pattern[4], 8, 0)) &&
                (bit_get_field(mem_rdata[5], 8, 0)  == bit_get_field(pattern[5], 8, 0)) &&
                (bit_get_field(mem_rdata[6], 8, 0)  == bit_get_field(pattern[6], 8, 0)) &&
                (bit_get_field(mem_rdata[7], 8, 0)  == bit_get_field(pattern[7], 8, 0)) &&
                (bit_get_field(mem_rdata[8], 8, 0)  == bit_get_field(pattern[8], 8, 0)) &&
                (bit_get_field(mem_rdata[9], 8, 0)  == bit_get_field(pattern[9], 8, 0)) &&
                (bit_get_field(mem_rdata[10], 8, 0) == bit_get_field(pattern[10], 8, 0)) &&
                (bit_get_field(mem_rdata[11], 8, 0) == bit_get_field(pattern[11], 8, 0)) &&
                (bit_get_field(mem_rdata[12], 8, 0) == bit_get_field(pattern[12], 8, 0)) &&
                (bit_get_field(mem_rdata[13], 8, 0) == bit_get_field(pattern[13], 8, 0)) &&
                (bit_get_field(mem_rdata[14], 8, 0) == bit_get_field(pattern[14], 8, 0)) &&
                (bit_get_field(mem_rdata[15], 8, 0) == bit_get_field(pattern[15], 8, 0)) &&
                (bit_get_field(mem_rdata[16], 8, 0) == bit_get_field(pattern[16], 8, 0)) &&
                (bit_get_field(mem_rdata[17], 8, 0) == bit_get_field(pattern[17], 8, 0)) &&
                (bit_get_field(mem_rdata[18], 8, 0) == bit_get_field(pattern[18], 8, 0)) &&
                (bit_get_field(mem_rdata[19], 8, 0) == bit_get_field(pattern[19], 8, 0)) &&
                (bit_get_field(mem_rdata[20], 8, 0) == bit_get_field(pattern[20], 8, 0)) &&
                (bit_get_field(mem_rdata[21], 8, 0) == bit_get_field(pattern[21], 8, 0)) &&
                (bit_get_field(mem_rdata[22], 8, 0) == bit_get_field(pattern[22], 8, 0)) &&
                (bit_get_field(mem_rdata[23], 8, 0) == bit_get_field(pattern[23], 8, 0)) && found_stop0 == 0
            )
            {
                k510_logd("RBURST DS0 is Matched\n");
                if(incr_data < incr_good_min0)
                {
                    incr_good_min0 = incr_data;
                    found_pass0 = 1;
                }

                if(incr_data > incr_good_max0)
                {
                    incr_good_max0 = incr_data;
                }
            }
            else
            {
                if(found_pass0)
                {
                    found_stop0 = 1;     //DS0 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 8)  == bit_get_field(pattern[0], 8, 8)) &&
                (bit_get_field(mem_rdata[1], 8, 8)  == bit_get_field(pattern[1], 8, 8)) &&
                (bit_get_field(mem_rdata[2], 8, 8)  == bit_get_field(pattern[2], 8, 8)) &&
                (bit_get_field(mem_rdata[3], 8, 8)  == bit_get_field(pattern[3], 8, 8)) &&
                (bit_get_field(mem_rdata[4], 8, 8)  == bit_get_field(pattern[4], 8, 8)) &&
                (bit_get_field(mem_rdata[5], 8, 8)  == bit_get_field(pattern[5], 8, 8)) &&
                (bit_get_field(mem_rdata[6], 8, 8)  == bit_get_field(pattern[6], 8, 8)) &&
                (bit_get_field(mem_rdata[7], 8, 8)  == bit_get_field(pattern[7], 8, 8)) &&
                (bit_get_field(mem_rdata[8], 8, 8)  == bit_get_field(pattern[8], 8, 8)) &&
                (bit_get_field(mem_rdata[9], 8, 8)  == bit_get_field(pattern[9], 8, 8)) &&
                (bit_get_field(mem_rdata[10], 8, 8) == bit_get_field(pattern[10], 8, 8)) &&
                (bit_get_field(mem_rdata[11], 8, 8) == bit_get_field(pattern[11], 8, 8)) &&
                (bit_get_field(mem_rdata[12], 8, 8) == bit_get_field(pattern[12], 8, 8)) &&
                (bit_get_field(mem_rdata[13], 8, 8) == bit_get_field(pattern[13], 8, 8)) &&
                (bit_get_field(mem_rdata[14], 8, 8) == bit_get_field(pattern[14], 8, 8)) &&
                (bit_get_field(mem_rdata[15], 8, 8) == bit_get_field(pattern[15], 8, 8)) &&
                (bit_get_field(mem_rdata[16], 8, 8) == bit_get_field(pattern[16], 8, 8)) &&
                (bit_get_field(mem_rdata[17], 8, 8) == bit_get_field(pattern[17], 8, 8)) &&
                (bit_get_field(mem_rdata[18], 8, 8) == bit_get_field(pattern[18], 8, 8)) &&
                (bit_get_field(mem_rdata[19], 8, 8) == bit_get_field(pattern[19], 8, 8)) &&
                (bit_get_field(mem_rdata[20], 8, 8) == bit_get_field(pattern[20], 8, 8)) &&
                (bit_get_field(mem_rdata[21], 8, 8) == bit_get_field(pattern[21], 8, 8)) &&
                (bit_get_field(mem_rdata[22], 8, 8) == bit_get_field(pattern[22], 8, 8)) &&
                (bit_get_field(mem_rdata[23], 8, 8) == bit_get_field(pattern[23], 8, 8)) && found_stop1 == 0
            )
            {
                k510_logd("RBURST DS1 is Matched\n");
                if(incr_data < incr_good_min1)
                {
                    incr_good_min1 = incr_data;
                    found_pass1 = 1;
                }

                if(incr_data > incr_good_max1)
                {
                    incr_good_max1 = incr_data;
                }
            }
            else
            {
                if(found_pass1)
                {
                    found_stop1 = 1;     //DS1 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 16)  == bit_get_field(pattern[0], 8, 16)) &&
                (bit_get_field(mem_rdata[1], 8, 16)  == bit_get_field(pattern[1], 8, 16)) &&
                (bit_get_field(mem_rdata[2], 8, 16)  == bit_get_field(pattern[2], 8, 16)) &&
                (bit_get_field(mem_rdata[3], 8, 16)  == bit_get_field(pattern[3], 8, 16)) &&
                (bit_get_field(mem_rdata[4], 8, 16)  == bit_get_field(pattern[4], 8, 16)) &&
                (bit_get_field(mem_rdata[5], 8, 16)  == bit_get_field(pattern[5], 8, 16)) &&
                (bit_get_field(mem_rdata[6], 8, 16)  == bit_get_field(pattern[6], 8, 16)) &&
                (bit_get_field(mem_rdata[7], 8, 16)  == bit_get_field(pattern[7], 8, 16)) &&
                (bit_get_field(mem_rdata[8], 8, 16)  == bit_get_field(pattern[8], 8, 16)) &&
                (bit_get_field(mem_rdata[9], 8, 16)  == bit_get_field(pattern[9], 8, 16)) &&
                (bit_get_field(mem_rdata[10], 8, 16) == bit_get_field(pattern[10], 8, 16)) &&
                (bit_get_field(mem_rdata[11], 8, 16) == bit_get_field(pattern[11], 8, 16)) &&
                (bit_get_field(mem_rdata[12], 8, 16) == bit_get_field(pattern[12], 8, 16)) &&
                (bit_get_field(mem_rdata[13], 8, 16) == bit_get_field(pattern[13], 8, 16)) &&
                (bit_get_field(mem_rdata[14], 8, 16) == bit_get_field(pattern[14], 8, 16)) &&
                (bit_get_field(mem_rdata[15], 8, 16) == bit_get_field(pattern[15], 8, 16)) &&
                (bit_get_field(mem_rdata[16], 8, 16) == bit_get_field(pattern[16], 8, 16)) &&
                (bit_get_field(mem_rdata[17], 8, 16) == bit_get_field(pattern[17], 8, 16)) &&
                (bit_get_field(mem_rdata[18], 8, 16) == bit_get_field(pattern[18], 8, 16)) &&
                (bit_get_field(mem_rdata[19], 8, 16) == bit_get_field(pattern[19], 8, 16)) &&
                (bit_get_field(mem_rdata[20], 8, 16) == bit_get_field(pattern[20], 8, 16)) &&
                (bit_get_field(mem_rdata[21], 8, 16) == bit_get_field(pattern[21], 8, 16)) &&
                (bit_get_field(mem_rdata[22], 8, 16) == bit_get_field(pattern[22], 8, 16)) &&
                (bit_get_field(mem_rdata[23], 8, 16) == bit_get_field(pattern[23], 8, 16)) && found_stop2 == 0
            )
            {
                k510_logd("RBURST DS2 is Matched\n");
                if(incr_data < incr_good_min2)
                {
                    incr_good_min2 = incr_data;
                    found_pass2 = 1;
                }

                if(incr_data > incr_good_max2)
                {
                    incr_good_max2 = incr_data;
                }
            }
            else
            {
                if(found_pass2)
                {
                    found_stop2 = 1;     //DS2 stop training
                }
            }

            if(
                (bit_get_field(mem_rdata[0], 8, 24)  == bit_get_field(pattern[0], 8, 24)) &&
                (bit_get_field(mem_rdata[1], 8, 24)  == bit_get_field(pattern[1], 8, 24)) &&
                (bit_get_field(mem_rdata[2], 8, 24)  == bit_get_field(pattern[2], 8, 24)) &&
                (bit_get_field(mem_rdata[3], 8, 24)  == bit_get_field(pattern[3], 8, 24)) &&
                (bit_get_field(mem_rdata[4], 8, 24)  == bit_get_field(pattern[4], 8, 24)) &&
                (bit_get_field(mem_rdata[5], 8, 24)  == bit_get_field(pattern[5], 8, 24)) &&
                (bit_get_field(mem_rdata[6], 8, 24)  == bit_get_field(pattern[6], 8, 24)) &&
                (bit_get_field(mem_rdata[7], 8, 24)  == bit_get_field(pattern[7], 8, 24)) &&
                (bit_get_field(mem_rdata[8], 8, 24)  == bit_get_field(pattern[8], 8, 24)) &&
                (bit_get_field(mem_rdata[9], 8, 24)  == bit_get_field(pattern[9], 8, 24)) &&
                (bit_get_field(mem_rdata[10], 8, 24) == bit_get_field(pattern[10], 8, 24)) &&
                (bit_get_field(mem_rdata[11], 8, 24) == bit_get_field(pattern[11], 8, 24)) &&
                (bit_get_field(mem_rdata[12], 8, 24) == bit_get_field(pattern[12], 8, 24)) &&
                (bit_get_field(mem_rdata[13], 8, 24) == bit_get_field(pattern[13], 8, 24)) &&
                (bit_get_field(mem_rdata[14], 8, 24) == bit_get_field(pattern[14], 8, 24)) &&
                (bit_get_field(mem_rdata[15], 8, 24) == bit_get_field(pattern[15], 8, 24)) &&
                (bit_get_field(mem_rdata[16], 8, 24) == bit_get_field(pattern[16], 8, 24)) &&
                (bit_get_field(mem_rdata[17], 8, 24) == bit_get_field(pattern[17], 8, 24)) &&
                (bit_get_field(mem_rdata[18], 8, 24) == bit_get_field(pattern[18], 8, 24)) &&
                (bit_get_field(mem_rdata[19], 8, 24) == bit_get_field(pattern[19], 8, 24)) &&
                (bit_get_field(mem_rdata[20], 8, 24) == bit_get_field(pattern[20], 8, 24)) &&
                (bit_get_field(mem_rdata[21], 8, 24) == bit_get_field(pattern[21], 8, 24)) &&
                (bit_get_field(mem_rdata[22], 8, 24) == bit_get_field(pattern[22], 8, 24)) &&
                (bit_get_field(mem_rdata[23], 8, 24) == bit_get_field(pattern[23], 8, 24)) && found_stop3 == 0
            )
            {
                k510_logd("RBURST DS3 is Matched\n");
                if(incr_data < incr_good_min3)
                {
                    incr_good_min3 = incr_data;
                    found_pass3 = 1;
                }

                if(incr_data > incr_good_max3)
                {
                    incr_good_max3 = incr_data;
                }
            }
            else
            {
                if(found_pass3)
                {
                    found_stop3 = 1;     //DS3 stop training
                }
            }
            #if !DDR_READ_EYE_LOOP_ALL
            else // ?!
            {
                if ((found_pass0 == 1) && (found_pass1 == 1) && (found_pass2 == 1) && (found_pass3 == 1))
                {
                    continue_loop = 0;
                }
            }
            #endif
        }

        incr_good_avg0 = incr_good_min0 +((incr_good_max0 - incr_good_min0) / 2);
        k510_logd("incr_good_min0 == %d\n", incr_good_min0);
        k510_logd("incr_good_max0 == %d\n", incr_good_max0);
        k510_logd("incr_good_avg0 == %d\n", incr_good_avg0);
        incr_good_avg1 = incr_good_min1 +((incr_good_max1 - incr_good_min1) / 2);
        k510_logd("incr_good_min1 == %d\n", incr_good_min1);
        k510_logd("incr_good_max1 == %d\n", incr_good_max1);
        k510_logd("incr_good_avg1 == %d\n", incr_good_avg1);
        incr_good_avg2 = incr_good_min2 +((incr_good_max2 - incr_good_min2) / 2);
        k510_logd("incr_good_min2 == %d\n", incr_good_min2);
        k510_logd("incr_good_max2 == %d\n", incr_good_max2);
        k510_logd("incr_good_avg2 == %d\n", incr_good_avg2);
        incr_good_avg3 = incr_good_min3 +((incr_good_max3 - incr_good_min3) / 2);
        k510_logd("incr_good_min3 == %d\n", incr_good_min3);
        k510_logd("incr_good_max3 == %d\n", incr_good_max3);
        k510_logd("incr_good_avg3 == %d\n", incr_good_avg3);

        // k510_logd("RBURST_0_P0: @0x%08x = 0x%08x\n", RBURST_0_P0_ADDR, val_rb_0_p0);
        // k510_logd("RBURST_0_P1: @0x%08x = 0x%08x\n", RBURST_0_P1_ADDR, val_rb_0_p1);
        // k510_logd("RBURST_0_P2: @0x%08x = 0x%08x\n", RBURST_0_P2_ADDR, val_rb_0_p2);
        // k510_logd("RBURST_0_P3: @0x%08x = 0x%08x\n", RBURST_0_P3_ADDR, val_rb_0_p3);
        // k510_logd("RBURST_1_P0: @0x%08x = 0x%08x\n", RBURST_1_P0_ADDR, val_rb_1_p0);
        // k510_logd("RBURST_1_P1: @0x%08x = 0x%08x\n", RBURST_1_P1_ADDR, val_rb_1_p1);
        // k510_logd("RBURST_1_P2: @0x%08x = 0x%08x\n", RBURST_1_P2_ADDR, val_rb_1_p2);
        // k510_logd("RBURST_1_P3: @0x%08x = 0x%08x\n", RBURST_1_P3_ADDR, val_rb_1_p3);
        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd("mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 24 of 28 for LPDDR3 Read Eye Training"
            "w/o Bit Deskew or VREF Training\n"
            "Continue READ EYE Training Calibration Loop by"
            "incrementing the values of READ DQS_B DLL SADJ until"
            "SADJ = max value.  End Training Loop 3 when the max"
            "value is reached.\n"
        );

        incr_data += 1;
        k510_logi("%s:>>>>>> Loop 3: incr_data is %d\n", __func__, incr_data);

        if(found_stop0 == 0)
        {
            rd_dqs_b_sadj[0] = incr_data;
        }
        if(found_stop1 == 0)
        {
            rd_dqs_b_sadj[1] = incr_data;
        }
        if(found_stop2 == 0)
        {
            rd_dqs_b_sadj[2] = incr_data;
        }
        if(found_stop3 == 0)
        {
            rd_dqs_b_sadj[3] = incr_data;
        }
        // read_dqs_b_sadj = incr_data;

        if ((incr_data > MAX_READ_DQS_B_SADJ) || (found_stop0 && found_stop1 && found_stop2 && found_stop3))
        {
            continue_loop = 0;
        }
        else
        {
            set_read_dqs_b_sadj(rd_dqs_b_sadj[0], rd_dqs_b_sadj[1], rd_dqs_b_sadj[2], rd_dqs_b_sadj[3]);
            k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
            k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
            k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
            k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        }
        k510_logd("**************** Loop 3 :  single cycle end ****************\n");
    } // while(continue_loop == 1)

    /* Final:  LPDDR3 Read Eye Training Loop 3 */
    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS0\n");
    k510_logd("incr_good_min0 = %d  0x%08X\n", incr_good_min0, incr_good_min0);
    k510_logd("incr_good_max0 = %d  0x%08X\n", incr_good_max0, incr_good_max0);
    k510_logd("incr_good_avg0 = %d  0x%08X\n", incr_good_avg0, incr_good_avg0);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS1\n");
    k510_logd("incr_good_min1 = %d  0x%08X\n", incr_good_min1, incr_good_min1);
    k510_logd("incr_good_max1 = %d  0x%08X\n", incr_good_max1, incr_good_max1);
    k510_logd("incr_good_avg1 = %d  0x%08X\n", incr_good_avg1, incr_good_avg1);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS2\n");
    k510_logd("incr_good_min2 = %d  0x%08X\n", incr_good_min2, incr_good_min2);
    k510_logd("incr_good_max2 = %d  0x%08X\n", incr_good_max2, incr_good_max2);
    k510_logd("incr_good_avg2 = %d  0x%08X\n", incr_good_avg2, incr_good_avg2);

    k510_logi("Final:  LPDDR3 Read Eye Training Loop 3 DS3\n");
    k510_logd("incr_good_min3 = %d  0x%08X\n", incr_good_min3, incr_good_min3);
    k510_logd("incr_good_max3 = %d  0x%08X\n", incr_good_max3, incr_good_max3);
    k510_logd("incr_good_avg3 = %d  0x%08X\n", incr_good_avg3, incr_good_avg3);

    /* Verify that the Read Eye Training was successful. */
    if ((incr_good_min0 == 99) || (incr_good_min1 == 99) || (incr_good_min2 == 99) || (incr_good_min3 == 99))
    {
        k510_logi("ERR: LPDDR3 Read Eye Training Loop 3 Failed!\n");
        return -1;
    }

    k510_logv(
        "Step 25 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );

    /* First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    /* Set CRDB (bit[17] to 1. */
    bit_set_bit(regdata, 17);
    /* Set SADJ WRT (bit[10]) to 1. */
    bit_set_bit(regdata, 10);
    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 26 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Set READ DQS_B DLL SADJ = AVG of MIN and MAX pass "
        "values from Training Loop 3.\n"
    );
    // set_read_dqs_b_sadj(incr_good_avg, incr_good_avg, incr_good_avg, incr_good_avg);
    // set_read_dqs_b_sadj(incr_good_avg3, incr_good_avg2, incr_good_avg1, incr_good_avg0); // ?!
    set_read_dqs_b_sadj(incr_good_avg0, incr_good_avg1, incr_good_avg2, incr_good_avg3);

    k510_logi("---------------- %s Loop3 end ----------------\n", __func__);
    k510_logv(
        "Step 27 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 0.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_clr_bit(regdata, 17);
    bit_clr_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logv(
        "Step 28 of 28 for LPDDR3 Read Eye Training "
        "w/o Bit Deskew or VREF Training\n"
        "Continue with regular DRAM commands.\n"
    );

    k510_logi("LPDDR3 Read Eye Training Complete\n");
    return 0;
}
#endif
#endif

#if DDR_RG_TRAINING_OLD
/* Modify 1020 */
static uint32_t Read_Gate_training(void)
{
    uint32_t regdata = 0;
    uint64_t value = 0;

    uint8_t continue_training;
    int    incr_data;
    double    threshpass;
    int    pass0;
    int    pass1;
    int    pass2;
    int    pass3;
    int    detc0;
    int    detc1;
    int    detc2;
    int    detc3;
    int    detc_cntr0;
    int    detc_cntr1;
    int    detc_cntr2;
    int    detc_cntr3;
    int    rg_dly0;
    int    rg_dly1;
    int    rg_dly2;
    int    rg_dly3;
    // real   avg0;
    // real   avg1;
    // real   avg2;
    // real   avg3;

    k510_logd("Begin LPDDR3 Read Gate Training \n");

    /*
        Set SADJ WRT in TRAINING_CTRL1
    */
    //  First read the value of the TRAINING_CTRL1 register.

    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    // set SADJ WRT
    regdata |= (1 << 10);
    //  Now write the new value to the TRAINING_CTRL1 register to
    //  start read gate training.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /*
        Set IO_DS_PU in DSX8_IO_CTRL
    */
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(DSX8_IO_CTRL_ADDR, 1);
    // set IO_DS_PU
    regdata |= (1 << 7);
    //  Now write the new value to the DSX8_IO_CTRL register to
    //  start read gate training.
    write_register(DSX8_IO_CTRL_ADDR,regdata, 1);

    /* Step 0 of 6 for LPDDR3 Read Gate Training
       w/o Bit Deskew or VREF Training
       Set extend read gate bits.
    */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);

     /* Adjust Read gate deassertion. */

    regdata &= ~(0x3 << 28);
    regdata &= ~(0x3 << 20);
    regdata &= ~(0x3 << 12);
    regdata &= ~(0x3 << 4);

    //  Adjust start of Read Gate assertion.
    regdata &= ~(0xf << 24);   // Default = 4'h6. changed to 4'ha JJD
    regdata &= ~(0xf << 16);   // Default = 4'h6.
    regdata &= ~(0xf << 8);    // Default = 4'h6.
    regdata &= ~(0xf << 0);    // Default = 4'h6.

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    //  Loop until Read Gate Training Complete bit (bit 1) in the
    //  TRAINING_CTRL1 register is set or a Read Gate Training
    //  error status bit (bits 927:24]) is set.

// NOTE this threshold for pass needs to be updated to using a windowing average to find the proper point this is a patch to get the testbenches to pass
    #ifdef CHIP_GLS_SSG
        threshpass = 13; //SSG
    #elif CHIP_GLS_FFG
        threshpass = 13; //TT and FFG
    #else
#if DDR_800
        threshpass = 12; // updata by hyg
#endif

#if DDR_1066
        threshpass = 13;
#endif

#if DDR_1333
        threshpass = 13;
#endif

#if DDR_1600
        threshpass = 14;
#endif

#if DDR_1866
        threshpass = 14;
#endif

#if DDR_2133
        threshpass = 14;
#endif
    #endif

    incr_data = 0;
    pass0 = 0;
    pass1 = 0;
    pass2 = 0;
    pass3 = 0;
    detc_cntr0 = 0;
    detc_cntr1 = 0;
    detc_cntr2 = 0;
    detc_cntr3 = 0;
    rg_dly0 = 0;
    rg_dly1 = 0;
    rg_dly2 = 0;
    rg_dly3 = 0;

    /* Set RG_DLY = 0 */
    regdata = read_register(RGDLY_ADDR, 1);
    //  Set the value Read Gate assertion
    regdata = 0;

    regdata |= (incr_data & 0xff) << 24;   // Default = 4'h0.
    regdata |= (incr_data & 0xff) << 16;   // Default = 4'h0.
    regdata |= (incr_data & 0xff) << 8;    // Default = 4'h0.
    regdata |= (incr_data & 0xff) << 0;    // Default = 4'h0.
    write_register(RGDLY_ADDR, regdata, 1);

    continue_training = 1;
    while (continue_training == 1)
    {
        /*
            Force RG_DLY value = 1, Put PHY into read gate training mode bit[0] = 1 in TRAINING_CTRL1
        */
        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set bit 0 to 1.
        regdata |= (1 << 0);
        //  Set ds_frc_rg = 1.
        regdata |= (1 << 9);
        //  Now write the new value to the TRAINING_CTRL1 register to
        //  start read gate training.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        /*
            "Step 1 of 6 for LPDDR3 Read Gate Training",
            "Issue MRR MR32"
        */
    #ifndef DFI_AGENT
        read_mode_register(32, &value);  /*  */
        k510_logd("====read data is %08x\n===",value);
    #else
    #endif
        /*
            "Step 2 of 6 for LPDDR3 Read Gate Training",
            "After RL + RU(tDQSCKMAX/tCK) + 8.2 + 1 - WL clock ",
            "cycles, DRAM bursts out the predefined Read",
            "Calibration Pattern"
        */
        // #100ns

        /*
            "Step 3 of 6 for LPDDR3 Read Gate Training",
            "Ensure the tMRR >= 8"
        */
        // #100ns

        /*
            "Step 4 of 6 for LPDDR3 Read Gate Training",
            "Continue Gate Training Calibration Loop until",
            "read gate training is signalled complete by.",
            "Monitoring the TRAINING_CTRL1 Register on the AHB",
            "interface to the PHY."
        */

        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        if(((regdata >> 1) & 1) && (regdata & (0xf << 2)))
        {
            if( (incr_data < 20) )
            {
			    continue_training = 1;
                //  Read the value of the RDQS_DETC_CNTR register.
                regdata = read_register(RDQS_DETC_CNTR_ADDR, 1);
                if(((regdata & 0x1F) <= threshpass) && (pass0 != 1))
                {
                    detc_cntr0 = regdata & 0x1F;
                    rg_dly0 = incr_data;
                    pass0 = 1;
                }
                if((((regdata >> 8) & 0x1F) <= threshpass) && pass1 != 1)
                {
			      detc_cntr1 = (regdata >> 8) & 0x1F;
			      rg_dly1 = incr_data;
			      pass1 = 1;
			    }
                if((((regdata >> 16) & 0x1F) <= threshpass) && (pass2 != 1))
                {
			      detc_cntr2 = (regdata >> 16) & 0x1F;
			      rg_dly2 = incr_data;
			      pass2 = 1;
			    }
                if((((regdata >> 24) & 0x1F) <= threshpass) && (pass3 != 1))
                {
			      detc_cntr3 = (regdata >> 24) & 0x1F;
			      rg_dly3 = incr_data;
			      pass3 = 1;
                }
                if((pass0 == 1) && (pass1 == 1) && (pass2 == 1) && (pass3 == 1))
                {
			      continue_training = 0;
                }
                incr_data += 1;
                /* Set RG_DLY = +1 */
                regdata = read_register(RGDLY_ADDR, 1);
                //  Set the value Read Gate assertion

                regdata = 0;
                regdata |= (incr_data & 0xff) << 24;
                regdata |= (incr_data & 0xff) << 16;
                regdata |= (incr_data & 0xff) << 8;
                regdata |= (incr_data & 0xff) << 0;

                write_register(RGDLY_ADDR, regdata, 1);
            }// if ( (incr_data < 20) )
            else
            {
                continue_training = 0;
            }// else: !if( (incr_data < 20) )
        }// if ((regdata[1] == 1'b1) && (regdata[5:2] !== 4'b0000))
        else if(incr_data < 20)
        {
            continue_training = 1;
            incr_data += 1;
            /* Set RG_DLY = +1 */
            /* Wait 100ns for read gate training to finish. CONTINUE LOOP */
            //  #100ns; //??
            regdata = read_register(RGDLY_ADDR, 1);
            //  Set the value Read Gate assertion
            regdata = 0;
            regdata |= (incr_data & 0xff) << 24;
            regdata |= (incr_data & 0xff) << 16;
            regdata |= (incr_data & 0xff) << 8;
            regdata |= (incr_data & 0xff) << 0;
            write_register(RGDLY_ADDR, regdata, 1);
        }
        else if(incr_data == 20)
        {
            continue_training = 0;
            /* Wait 100ns for read gate training to finish.  END LOOP */
            // #100ns;
        }

    }// while (continue_training == 1)

    // setup final read gate training using the trained values
	// REN

    /* Set RG_DLY to final trained values */
    regdata = read_register(RGDLY_ADDR, 1);
    //  Set the value Read Gate assertion
    regdata = 0;
    regdata |= (rg_dly3 & 0xff) << 24;
    regdata |= (rg_dly2 & 0xff) << 16;
    regdata |= (rg_dly1 & 0xff) << 8;
    regdata |= (rg_dly0 & 0xff) << 0;
    write_register(RGDLY_ADDR, regdata, 1);

    /*
        "Perform FINAL READ GATE Training with final trained value ",
        "w/ final detc_cntr assigned to each RGDLY_ADJ assertion"
    */

    regdata = read_register(RGDLY_ADJ_ADDR, 1);
    // Adjust Read gate deassertion.
    regdata &= ~((0x3 << 28) | (0x3 << 20) | (0x3 << 12) | (0x3 << 4));
    regdata |= (0x2 << 28) | (0x2 << 20) | (0x2 << 12) | (0x2 << 4);

    //  Adjust start of Read Gate assertion.
    regdata &= ~((0xf << 24) | (0xf << 16) | (0xf << 8) | (0xf << 0));
    regdata |= ((detc_cntr3 & 0xf) << 24) | ((detc_cntr2 & 0xf) << 16) | ((detc_cntr1 & 0xf) << 8) | ((detc_cntr0 & 0xf) << 0);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    k510_logi("\n");
    k510_logi("rg_dly0 0x%08X\n", rg_dly0);
    k510_logi("rg_dly1 0x%08X\n", rg_dly1);
    k510_logi("rg_dly2 0x%08X\n", rg_dly2);
    k510_logi("rg_dly3 0x%08X\n", rg_dly3);

    k510_logi("detc_cntr0 0x%08X\n", detc_cntr0);
    k510_logi("detc_cntr1 0x%08X\n", detc_cntr1);
    k510_logi("detc_cntr2 0x%08X\n", detc_cntr2);
    k510_logi("detc_cntr3 0x%08X\n", detc_cntr3);

    k510_logi("threshpass %lf\n", threshpass);

    /* Force RG_DLY value = 1, Put PHY into read gate training mode bit[0] = 1 in TRAINING_CTRL1 */
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set bit 0 to 1.
    regdata |= (1 << 0);
    //  Set ds_frc_rg = 1.
    regdata |= (1 << 9);
    //  Now write the new value to the TRAINING_CTRL1 register to
    //  start read gate training.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /*
        "Step 1 of 6 for LPDDR3 Read Gate Training",
        "Issue MRR MR32"
    */
#ifndef DFI_AGENT
    read_mode_register(32, &value);
#else

#endif

    /*
        "Step 2 of 6 for LPDDR3 Read Gate Training",
        "After RL + RU(tDQSCKMAX/tCK) + 8.2 + 1 - WL clock ",
        "cycles, DRAM bursts out the predefined Read",
        "Calibration Pattern"
    */
    // #100ns

    /*
        "Step 3 of 6 for LPDDR3 Read Gate Training",
        "Ensure the tMRR >= 8"
    */
    // #100ns

    /*
        "Step 4 of 6 for LPDDR3 Read Gate Training",
        "Continue Gate Training Calibration Loop until",
        "read gate training is signalled complete by.",
        "Monitoring the TRAINING_CTRL1 Register on the AHB",
        "interface to the PHY."
    */
    //  Read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    //  Verify that all of the Individual Read Gate Training
    //  Completed per Data Slice bits are 1.
    if(((regdata >> 2) & 0xf) != 0xf)
    {
        k510_logd("All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are not 1.\n");
        return -1;
    }
    else
    {
        k510_logd("All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are correctly set.\n");
    }

    //  Verify that the Read Gate Training error status
    //  bits (bits 27:24) are 0.
    if((regdata >> 24) & 0xF)
    {
        k510_logd("Some of the Read Gate Training error status bits (bit 27:24) are 1.\n");
        return -1;
    }
    else
    {
        k510_logd("None of the Read Gate Training error status bits (bit 27:24) are set. Exiting Read Gate Training and setting read gate auto training mode\n");
    }

    //  Now write the new value to the TRAINING_CTRL1 register to
    //  clear the read gate training request bit and set continuous mode read gate training
    // this should load the rg_dly value as the default start point for auto training
    // set SADJ WRT = 1 and DS_FRC_RG = 0
    regdata &= ~(1 << 0);
    regdata &= ~(1 << 9);
    regdata &= ~(1 << 8);
    regdata |= (1 << 10);

    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    //  Read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
  //  regdata |= (1 << 8);
#if DDR_1066
    regdata |= (1 << 8);
#endif

#if DDR_1333
    regdata |= (1 << 8);
#endif

#if DDR_1600
    regdata |= (1 << 8);
#endif

#if DDR_1866
    regdata |= (1 << 8);
#endif

#if DDR_2133
    regdata |= (1 << 8);
#endif
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /*
        "Step 5 of 6 for LPDDR3 Read Gate Training",
        "After end of last MRR read burst, wait until ",
        "tWR + TRPpb is satisfied."
    */
    // #100ns

    /* LPDDR3 Read Gate Complete */

    /*
        "Step 6 of 6 for LPDDR3 Read Gate Training",
        "Continue with regular DRAM commands."
    */

    k510_logd("LPDDR3 Read Gate Complete\n");

    return 0;
}
#endif

#if DDR_RG_TRAINING_NEW
static uint32_t Read_Gate_training(void)
{
    int regdata = 0;
    int regdata1 =0;
    uint64_t value = 0;

    uint8_t continue_training;
    int    incr_data;
    double    threshpass;
    double    threshpassa;
    int    pass0;
    int    pass1;
    int    pass2;
    int    pass3;
    int    detc0;
    int    detc1;
    int    detc2;
    int    detc3;
    int    detc_cntr0;
    int    detc_cntr1;
    int    detc_cntr2;
    int    detc_cntr3;
    int    rg_dly0;
    int    rg_dly1;
    int    rg_dly2;
    int    rg_dly3;
    int    finalpass0;
    int    finalpass1;
    int    finalpass2;
    int    finalpass3;
    double   avg0;
    double   avg1;
    double   avg2;
    double   avg3;
    double   avgw0;
    double   avgw1;
    double   avgw2;
    double   avgw3;
    int rg_train_ds_cntr[4][32];

    int    detc_cntr0c;
    int    detc_cntr1c;
    int    detc_cntr2c;
    int    detc_cntr3c;
    int    loop_over;

	int	  rg_not_found = 1;
	int	  rdlat_offset = 0;
    int   rdlat_adj_f0;

    int foundfail0 = 0;
    int foundfail1 = 0;
    int foundfail2 = 0;
    int foundfail3 = 0;

// #if DDR_800
//     int backoff=3;
// #endif

// #if DDR_1066
//     int backoff=3;
// #endif

// #if DDR_1333
//     int backoff=4;
// #endif

// #if DDR_1600
//     // int backoff=2;
//     int backoff=3;
//     // int backoff=4;
//     // int backoff=5;
//     // int backoff=6;
// #endif
    int backoff = DDR_RG_BACKOFF;

    k510_logi("Begin LPDDR3 Read Gate Training\n");

    //DENALI CTL 653 setting 0x10 for 1600/1866

    regdata=read_register(DENALI_CTL_653,0);
    regdata &= ~(0xff);
#if DDR_800
    regdata |= 0x0a;
#else
    regdata |= 0x0f;
#endif
    rdlat_adj_f0 = regdata & 0xff;

    k510_logi("====First read:: DENALI_CTL_653: 0x%08x ===== \n", regdata);
    write_register(DENALI_CTL_653,regdata,0);
    regdata1=read_register(DENALI_CTL_653,0);
    k510_logi("====second read after write: DENALI_CTL_653: 0x%08x ===== \n", regdata1);
    incr_data=0;

    uint32_t loop_start = 0;
    while (rg_not_found == 1)
    {
        regdata=read_register(DENALI_CTL_653,0);
        k510_logi("\n\n>===============================================================<\n");
        if(loop_start == 0)
        {
            loop_start = 1;
            k510_logi("DENALI_CTL_653 First Started: 0x%08x ===== \n", regdata);
        }
        else
        {
            k510_logi("DENALI_CTL_653 Previous Loop: 0x%08x ===== \n", regdata);
            k510_logi("DENALI_CTL_653 Increase By One: 0x%08x ===== \n", regdata + 1);
        }
        //  Update to the new value and then write it to the register.
        regdata &= ~(0xff);
        regdata |= (rdlat_adj_f0 + rdlat_offset) & 0xff;
        k510_logi("rdlat_adj_f0 + rdlat_offset: 0x%08x ===== \n", regdata & 0xFF);
        write_register(DENALI_CTL_653,regdata,0);

        // First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set Read Gate Auto Training Enable (bit[8]) to = 0.
        //  bit_clr_bit(regdata, 8);
        //  Set DS_FRC_RG (bit[9]) to = 1.
        bit_set_bit(regdata, 10);
        //  Now write the new value to the TRAINING_CTRL1 register to
        //  start read gate training.
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);



        regdata = read_register(DSX8_IO_CTRL_ADDR, 1);
        bit_set_bit(regdata, 7);
        write_register(DSX8_IO_CTRL_ADDR, regdata, 1);

        regdata = read_register(RGDLY_ADJ_ADDR, 1);

        // Adjust Read gate deassertion.
        regdata &= ~(0x3 << 28);
        regdata &= ~(0x3 << 20);
        regdata &= ~(0x3 << 12);
        regdata &= ~(0x3 << 4);

        regdata |= (DDR_READ_GATE_DELAY_DEASSERTION << 28);
        regdata |= (DDR_READ_GATE_DELAY_DEASSERTION << 20);
        regdata |= (DDR_READ_GATE_DELAY_DEASSERTION << 12);
        regdata |= (DDR_READ_GATE_DELAY_DEASSERTION << 4);

        //  Adjust start of Read Gate assertion.
        regdata &= ~(0xf << 24);
        regdata &= ~(0xf << 16);
        regdata &= ~(0xf << 8);
        regdata &= ~(0xf << 0);

        write_register(RGDLY_ADJ_ADDR, regdata, 1);

#if DDR_800
        threshpass = 12;
        threshpassa = 13.5;
#endif

#if DDR_1066
        threshpass = 12;
        threshpassa = 13.5;
#endif

#if DDR_1333
        threshpass = 12;
        threshpassa = 13.5;
#endif

#if DDR_1600
        threshpass = 12;
        threshpassa = 13.5;
        // threshpass = 9;
        // threshpassa = 10.5;
#endif

#if DDR_1866
        threshpass = 12;
        threshpassa = 13.5;
#endif

#if DDR_2133
        threshpass = 12;
        threshpassa = 13.5;
#endif

            incr_data = 0;
            pass0 = 0;
            pass1 = 0;
            pass2 = 0;
            pass3 = 0;
            finalpass0 = 0;
            finalpass1 = 0;
            finalpass2 = 0;
            finalpass3 = 0;
            detc0 = 0;
            detc1 = 0;
            detc2 = 0;
            detc3 = 0;
            avg0 = 0;
            avg1 = 0;
            avg2 = 0;
            avg3 = 0;
            detc_cntr0 = 0;
            detc_cntr1 = 0;
            detc_cntr2 = 0;
            detc_cntr3 = 0;
            rg_dly0 = 0;
            rg_dly1 = 0;
            rg_dly2 = 0;
            rg_dly3 = 0;

            foundfail0 = 0;
            foundfail1 = 0;
            foundfail2 = 0;
            foundfail3 = 0;


            k510_logi(">>>>    threshpass  = %lf\n", threshpass);
            k510_logi(">>>>    threshpassa = %lf\n", threshpassa);
            k510_logi(">>>>    backoff = %d\n", backoff);
            /* Set RG_DLY = 0 */
            regdata = read_register(RGDLY_ADDR, 1);
            //  Set the value Read Gate assertion
            regdata = 0;

            regdata |= (incr_data & 0xff) << 24;   // Default = 4'h0.
            regdata |= (incr_data & 0xff) << 16;   // Default = 4'h0.
            regdata |= (incr_data & 0xff) << 8;    // Default = 4'h0.
            regdata |= (incr_data & 0xff) << 0;    // Default = 4'h0.
            write_register(RGDLY_ADDR, regdata, 1);





        continue_training = 1;
        uint32_t cnt = 0;
        while (continue_training == 1)
        {

            /*
                Step 1 of 5 for LPDDR3 Read Gate Training
                Using AXI read address location = 0.
            */

            //  First read the value of the TRAINING_CTRL1 register.
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);
            //  Set Read Gate Training Request (bit[0]) to 1.
            bit_set_bit(regdata, 0);
            //  Set DS_FRC_RG (bit[9]) to = 1.
            bit_set_bit(regdata, 9);
            write_register(TRAINING_CTRL1_ADDR, regdata, 1);


            // read operation
            read_mode_register(32, &value);




            //  Read the value of the RDQS_DETC_CNTR register.
            regdata = read_register(RDQS_DETC_CNTR_ADDR, 1);

            detc_cntr0c = bit_get_field(regdata, 5, 0);
            detc_cntr1c = bit_get_field(regdata, 5, 8);
            detc_cntr2c = bit_get_field(regdata, 5, 16);
            detc_cntr3c = bit_get_field(regdata, 5, 24);

            rg_train_ds_cntr[0][incr_data] = detc_cntr0c;
            rg_train_ds_cntr[1][incr_data] = detc_cntr1c;
            rg_train_ds_cntr[2][incr_data] = detc_cntr2c;
            rg_train_ds_cntr[3][incr_data] = detc_cntr3c;

            k510_logi(">>>>    rg_train_ds_cntr[0][%d] == 0x%08X\n", incr_data, detc_cntr0c);
            k510_logi(">>>>    rg_train_ds_cntr[1][%d] == 0x%08X\n", incr_data, detc_cntr1c);
            k510_logi(">>>>    rg_train_ds_cntr[2][%d] == 0x%08X\n", incr_data, detc_cntr2c);
            k510_logi(">>>>    rg_train_ds_cntr[3][%d] == 0x%08X\n", incr_data, detc_cntr3c);

            /*
                Step 2 of 5 for LPDDR3 Read Gate Training
                Continue Read Gate Training Calibration loop until
                read gate training is signalled complete by
                by monitoring the TRAINING_CTRL1 register on the
                AHB interface to the PHY.
            */

            //  Read the value of the TRAINING_CTRL1 register.
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);

            if(bit_check_bit(regdata, 1) && (bit_get_field(regdata, 4, 2) != 0))
            {
                if(bit_check_bit(regdata, 24) == 0)
                {
                    pass0 = pass0 + 1;
                    detc0 = detc0 + detc_cntr0c;
                    avg0 = ((double)detc0)/((double)pass0);
                    if(pass0 >= 5)
                    {
                        avgw0 = (rg_train_ds_cntr[0][incr_data] +
                                rg_train_ds_cntr[0][incr_data-1] +
                                rg_train_ds_cntr[0][incr_data-2] +
                                rg_train_ds_cntr[0][incr_data-3] +
                                rg_train_ds_cntr[0][incr_data-4])/5.0;


                    }
                   // k510_logi("/---------------/\n");
                    k510_logi("   rgdly=0x%08x,detc_cntr0=0x%08x,running total=0x%08x,pass0 =0x%08x,avg0=%08f,avgw0 = %08f\n",
                                incr_data,detc_cntr0c,detc0,pass0,avg0,avgw0);
                }
                else if(pass0 < 2)
                {
                    pass0 = 0;
                    detc0 = 0;
                }

                /* Ron 0408 */
                // if((regdata & (1 << 24)) && (pass0 >= 5) && (detc_cntr0c == 25))
                if((regdata & (1 << 24)) && (pass0 >= 5) && (detc_cntr0c == 25) && (foundfail0 == 0))
                {
                    foundfail0 = incr_data;
                    k510_logi("%s rgdly = 0x%08x detc_cntr = 0x%08x FOUND STOP\n", "Data Slice 0 ", incr_data, detc_cntr0c);
                }
                /* End */
                if(bit_check_bit(regdata, 25) == 0)
                {
                    pass1 = pass1 + 1;
                    detc1 = detc1 + detc_cntr1c;
                    avg1 = ((double)detc1)/((double)pass1);
                    if(pass1 >=5 )
                    {
                        avgw1 = (rg_train_ds_cntr[1][incr_data] +
                                rg_train_ds_cntr[1][incr_data-1] +
                                rg_train_ds_cntr[1][incr_data-2] +
                                rg_train_ds_cntr[1][incr_data-3] +
                                rg_train_ds_cntr[1][incr_data-4])/5.0;

                    }
                                k510_logi("   rgdly=0x%08x,detc_cntr1=0x%08x,running total=0x%08x,pass1 =0x%08x,avg1=%08f,avgw1 = %08f\n",
                                incr_data,detc_cntr1c,detc1,pass1,avg1,avgw1);

                }
                else if(pass1 < 2)
                {
                    pass1 = 0;
                    detc1 = 0;
                }
                /* Ron */
                // if((regdata & (1 << 25)) && (pass1 >= 5) && (detc_cntr1c == 25))
                if((regdata & (1 << 25)) && (pass1 >= 5) && (detc_cntr1c == 25) && (foundfail1 == 0))
                {
                    foundfail1 = incr_data;
                    k510_logi("%s rgdly = 0x%08x detc_cntr = 0x%08x FOUND STOP\n", "Data Slice 1 ", incr_data, detc_cntr1c);
                }
                /* End */
                if(bit_check_bit(regdata, 26) == 0)
                {
                    pass2 = pass2 + 1;
                    detc2 = detc2 + detc_cntr2c;
                    avg2 = ((double)detc2)/((double)pass2);
                    if(pass2 >= 5)
                    {
                        avgw2 = (rg_train_ds_cntr[2][incr_data] +
                                rg_train_ds_cntr[2][incr_data-1] +
                                rg_train_ds_cntr[2][incr_data-2] +
                                rg_train_ds_cntr[2][incr_data-3] +
                                rg_train_ds_cntr[2][incr_data-4])/5.0;
                    }
                                k510_logi("   rgdly=0x%08x,detc_cntr2=0x%08x,running total=0x%08x,pass2 =0x%08x,avg2=%08f,avgw2 = %08f\n",
                                incr_data,detc_cntr2c,detc2,pass2,avg2,avgw2);

                }
                else if(pass2 < 2)
                {
                    pass2 = 0;
                    detc2 = 0;
                }
                /* Ron */
                // if((regdata & (1 << 26)) && (pass2 >= 5) && (detc_cntr2c == 25))
                if((regdata & (1 << 26)) && (pass2 >= 5) && (detc_cntr2c == 25) && (foundfail2 == 0))
                {
                    foundfail2 = incr_data;
                    k510_logi("%s rgdly = 0x%08x detc_cntr = 0x%08x FOUND STOP\n", "Data Slice 2 ", incr_data, detc_cntr2c);
                }
                /* End */
                if(bit_check_bit(regdata, 27) == 0)
                {
                    pass3 = pass3 + 1;
                    detc3 = detc3 + detc_cntr3c;
                    avg3 = ((double)detc3)/((double)pass3);
                    if(pass3 >= 5)
                    {
                        avgw3 = (rg_train_ds_cntr[3][incr_data] +
                                rg_train_ds_cntr[3][incr_data-1] +
                                rg_train_ds_cntr[3][incr_data-2] +
                                rg_train_ds_cntr[3][incr_data-3] +
                                rg_train_ds_cntr[3][incr_data-4])/5.0;
                    }
                                k510_logi("   rgdly=0x%08x,detc_cntr2=0x%08x,running total=0x%08x,pass2 =0x%08x,avg2=%08f,avgw2 = %08f\n",
                                incr_data,detc_cntr3c,detc3,pass3,avg3,avgw3);

                }
                else if(pass3 < 2)
                {
                    pass3 = 0;
                    detc3 = 0;
                }
                /* Ron */
                // if((regdata & (1 << 27)) && (pass3 >= 5) && (detc_cntr3c == 25))
                if((regdata & (1 << 27)) && (pass3 >= 5) && (detc_cntr3c == 25) && (foundfail3 == 0))
                {
                    foundfail3 = incr_data;
                    k510_logi("%s rgdly = 0x%08x detc_cntr = 0x%08x FOUND STOP\n", "Data Slice 3 ", incr_data, detc_cntr3c);
                }
                /* End */

#if 1
                /* End */
                // if( incr_data < 20 )
                if( incr_data < 20 )
                {
                    continue_training = 1;
                    //  Read the value of the RDQS_DETC_CNTR register.
                    regdata = read_register(RDQS_DETC_CNTR_ADDR, 1);

                    k510_logi("  intermedia flow:\n");
                    k510_logi("    rg_dly: 0x%08X\n", incr_data);
                    k510_logi("    ------RDQS_DETC_CNTR DS0 = 0x%08X  Number pass=0x%08X  avg0 detect cnt=%08f\n", bit_get_field(regdata, 5, 0),pass0,avg0);
                    k510_logi("    ------RDQS_DETC_CNTR DS1 = 0x%08X  Number pass=0x%08X  avg1 detect cnt=%08f\n", bit_get_field(regdata, 5, 8),pass1,avg1);
                    k510_logi("    ------RDQS_DETC_CNTR DS2 = 0x%08X  Number pass=0x%08X  avg2 detect cnt=%08f\n", bit_get_field(regdata, 5, 16),pass2,avg2);
                    k510_logi("    ------RDQS_DETC_CNTR DS3 = 0x%08X  Number pass=0x%08X  avg3 detect cnt=%08f\n\n", bit_get_field(regdata, 5, 24),pass3,avg3);
                    k510_logi("/********************************************************************/\n");

                    if((pass0 >= 5) && (bit_get_field(regdata, 5, 0) >= threshpass) && (avgw0 <= threshpassa) && (finalpass0 == 0))
                    {
                        detc_cntr0 = bit_get_field(regdata, 5, 0);
                        rg_dly0 = incr_data;
                        finalpass0 = 1;
                        k510_logi("     --final DS0---:RDQS_DETC_CNTR detc_cntr0 = 0x%08x rg_dly0 = 0x%08x pass0 = 0x%08X avgw0 = %08f\n",
                                detc_cntr0,rg_dly0,pass0,avg0);
                    }

                    if((pass1 >= 5) && (bit_get_field(regdata, 5, 8) >= threshpass) && (avgw1 <= threshpassa) && (finalpass1 == 0))
                    {
                        detc_cntr1 = bit_get_field(regdata, 5, 8);
                        rg_dly1 = incr_data;
                        finalpass1=1;
                        k510_logi("     --final DS1---:RDQS_DETC_CNTR detc_cntr1 = 0x%08x rg_dly1 = 0x%08x pass1 = 0x%08X avgw1 = %08f\n",
                                detc_cntr1,rg_dly1,pass1,avg1);
                    }

                    if((pass2 >= 5) && (bit_get_field(regdata, 5, 16) >= threshpass) && (avgw2 <= threshpassa) && (finalpass2 == 0))
                    {
                        detc_cntr2 = bit_get_field(regdata, 5, 16);
                        rg_dly2 = incr_data;
                        finalpass2=1;
                        k510_logi("     --final DS2---:RDQS_DETC_CNTR detc_cntr2 = 0x%08x rg_dly2 = 0x%08x pass2 = 0x%08X avgw2 = %08f\n",
                                detc_cntr2,rg_dly2,pass2,avg2);
                    }

                    if((pass3 >= 5) && (bit_get_field(regdata, 5, 24) >= threshpass) && (avgw3 <= threshpassa) && (finalpass3 == 0))
                    {
                        detc_cntr3 = bit_get_field(regdata, 5, 24);
                        rg_dly3 = incr_data;
                        finalpass3=1;
                        k510_logi("    --final DS3---:RDQS_DETC_CNTR detc_cntr3 = 0x%08x rg_dly3 = 0x%08x pass3 = 0x%08X avgw3 = %08f\n",
                                detc_cntr3,rg_dly3,pass3,avg3);
                    }

                    // if((finalpass0 == 1) && (finalpass1 == 1) && (finalpass2 == 1) && (finalpass3 == 1)) /* Ron */
                    if((foundfail0 > 0) && (foundfail1 > 0) && (foundfail2 > 0) && (foundfail3 > 0))
                    {
                        continue_training = 0;
                        rg_not_found = 0;
                    }

                    incr_data += 1;

                    //k510_logi("incr_data==%0d  \n",incr_data);
                    //add by hyg for check incr_data
                    regdata = read_register(RGDLY_ADDR, 1);
                    //  Set the value Read Gate assertion

                    regdata = 0;
                    regdata |= (incr_data & 0xff) << 24;
                    regdata |= (incr_data & 0xff) << 16;
                    regdata |= (incr_data & 0xff) << 8;
                    regdata |= (incr_data & 0xff) << 0;
                    write_register(RGDLY_ADDR, regdata, 1);
                }   // if ( (incr_data < 20) )
                else
                {
                    continue_training = 0;
                }   // else: !if( (incr_data < 20) )

            } // if ((regdata[1] == 1'b1) && (regdata[5:2] !== 4'b0000))
            // else if( (incr_data < 19) )
            else if( (incr_data < 19) )
            {
                continue_training = 1;
                incr_data += 1;

                /* Set RG_DLY = +1 */
                regdata = read_register(RGDLY_ADDR, 1);
                //  Set the value Read Gate assertion

                // regdata = 0;
                if(foundfail3 == 0)
                {
                    regdata &= ~(0xff << 24);
                    regdata |= (incr_data & 0xff) << 24;
                }
                if(foundfail2 == 0)
                {
                    regdata &= ~(0xff << 16);
                    regdata |= (incr_data & 0xff) << 16;
                }
                if(foundfail1 == 0)
                {
                    regdata &= ~(0xff << 8);
                    regdata |= (incr_data & 0xff) << 8;
                }
                if(foundfail0 == 0)
                {
                    regdata &= ~(0xff << 0);
                    regdata |= (incr_data & 0xff) << 0;
                }

                write_register(RGDLY_ADDR, regdata, 1);
            }
            // else if( (incr_data == 20) )
            else if( (incr_data ==20 ) )
            {
                continue_training = 0;
            }
        }
#endif
        rdlat_offset += 1;
    }
        // /* Set RG_DLY to final trained values */
        // regdata = read_register(RGDLY_ADDR, 1);
        // //  Set the value Read Gate assertion
        // regdata = 0;
        // regdata |= (rg_dly3 & 0xff) << 24;
        // regdata |= (rg_dly2 & 0xff) << 16;
        // regdata |= (rg_dly1 & 0xff) << 8;
        // regdata |= (rg_dly0 & 0xff) << 0;
        // write_register(RGDLY_ADDR, regdata, 1);

        /* Set RG_DLY to final trained values */
        regdata = read_register(RGDLY_ADDR, 1);
        //  Set the value Read Gate assertion
        regdata = 0;
        regdata |= ((foundfail3 - backoff) & 0xff) << 24;
        regdata |= ((foundfail2 - backoff) & 0xff) << 16;
        regdata |= ((foundfail1 - backoff) & 0xff) << 8;
        regdata |= ((foundfail0 - backoff) & 0xff) << 0;
        rg_dly3 = foundfail3 - backoff;
        rg_dly2 = foundfail2 - backoff;
        rg_dly1 = foundfail1 - backoff;
        rg_dly0 = foundfail0 - backoff;
        write_register(RGDLY_ADDR, regdata, 1);


        regdata = read_register(RGDLY_ADJ_ADDR, 1);
        // Adjust Read gate deassertion.
        regdata &= ~((0x3 << 28) | (0x3 << 20) | (0x3 << 12) | (0x3 << 4));
        regdata |= (DDR_READ_GATE_DELAY_DEASSERTION << 28) | (DDR_READ_GATE_DELAY_DEASSERTION << 20) | (DDR_READ_GATE_DELAY_DEASSERTION << 12) | (DDR_READ_GATE_DELAY_DEASSERTION << 4);

        //  Adjust start of Read Gate assertion.
        regdata &= ~((0xf << 24) | (0xf << 16) | (0xf << 8) | (0xf << 0));
        // regdata |= ((detc_cntr3 & 0xf) << 24) | ((detc_cntr2 & 0xf) << 16) | ((detc_cntr1 & 0xf) << 8) | ((detc_cntr0 & 0xf) << 0);
        regdata |= ((rg_train_ds_cntr[3][rg_dly3] & 0xf) << 24) | ((rg_train_ds_cntr[2][rg_dly2] & 0xf) << 16) | ((rg_train_ds_cntr[1][rg_dly1] & 0xf) << 8) | ((rg_train_ds_cntr[0][rg_dly0] & 0xf) << 0);

        k510_logi(">>>>>>>>>>final result:      rg_dly3 == 0x%08X\n", rg_dly3);
        k510_logi(">>>>>>>>>>final result:      rg_dly2 == 0x%08X\n", rg_dly2);
        k510_logi(">>>>>>>>>>final result:      rg_dly1 == 0x%08X\n", rg_dly1);
        k510_logi(">>>>>>>>>>final result:      rg_dly0 == 0x%08X\n", rg_dly0);
        k510_logi(">>>>>>>>>>final result:      rg_train_ds_cntr[3][rg_dly3] == 0x%08X\n", rg_train_ds_cntr[3][rg_dly3]);
        k510_logi(">>>>>>>>>>final result:      rg_train_ds_cntr[2][rg_dly2] == 0x%08X\n", rg_train_ds_cntr[2][rg_dly2]);
        k510_logi(">>>>>>>>>>final result:      rg_train_ds_cntr[1][rg_dly1] == 0x%08X\n", rg_train_ds_cntr[1][rg_dly1]);
        k510_logi(">>>>>>>>>>final result:      rg_train_ds_cntr[0][rg_dly0] == 0x%08X\n", rg_train_ds_cntr[0][rg_dly0]);
        k510_logi(">>>>>>>>>>final result:      RGDLY Value = 0x%08X\n", regdata);
        write_register(RGDLY_ADJ_ADDR, regdata, 1);

        /* Force RG_DLY value = 1, Put PHY into read gate training mode bit[0] = 1 in TRAINING_CTRL1 */
        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set bit 0 to 1.
        regdata |= (1 << 0);
        //  Set ds_frc_rg = 1.
        regdata |= (1 << 9);
        //  Now write the new value to the TRAINING_CTRL1 register to
        //  start read gate training.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        /*
            "Step 1 of 5 for LPDDR3 Read Gate Training",
            "Using AXI read address location = 0."
        */

        read_mode_register(32, &value);

        /*
            Step 4 of 5 for LPDDR3 Read Gate Training
            After } of last MRR read burst wait until tWR +
            TRPpb is satisfied.
        */
        // #100ns
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        //  Verfity that all of the Individual Read Gate Training
        //  Completed per Data Slice bits are 1.
        if(bit_get_field(regdata, 4, 2) != 0xF)     /* 杩欓噷鏈夐棶棰樺惂锛宺egdata 鍝潵鐨勶紵zzx */
        {
            k510_logi("ERR: All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are not 1.\n");
            return -1;
        }
        else
        {
            k510_logi("All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are correctly set.\n");
        }

        //  Verify that the Read Gate Training error status
        //  bits (bits 27:24) are 0.
        if(bit_get_field(regdata, 4, 24))
        {
            k510_logi("ERR: Some of the Read Gate Training error status bits (bit 27:24) are 1.\n");
            return -1;
        }
        else
        {
            k510_logi("None of the Read Gate Training error status its (bit 27:24) are set.\n");
        }

        /*
            Step 4b of 5 for LPDDR3 Read Gate Training
            To exit read gate training, write 0 to to
            (bit[0] & bit[9]) and 1 to bit[8] set auto read gate training mode
            TRAINING_CTRL1 registers.
        */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Clear the Read Gate Training Request bit (bit[0]).
        bit_clr_bit(regdata, 0);

#if DDR_READ_GATE_AUTO_TRAINING
        //  Set the Read Gate Auto Training bit (bit[8]).
        bit_set_bit(regdata, 8);
#else
        // ron modified to turn off read gate auto training CLR
        bit_clr_bit(regdata, 8);
#endif
        //  Set ds_frc_rg = 0.  // ron modifed to turn off read gate auto training SET
        bit_clr_bit(regdata, 9);
        bit_set_bit(regdata, 10);
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        /* What's this zzx */
        // `ifndef DFI_AGENT
        //                   //  Turn on axi_scoreboard compares for the reads after
        //                   //  Read Gate Training has completed.
        //                   p_sequencer.m_axi_scoreboard.set_compare(1'b1);
        // `else
        //                  `uvm_do_on(pre4_seq, p_sequencer.dfi_sequencer);
        //                  $display("\t\t\t\tSENDING PRE %0p @%0t", pre4_seq, $time);
        //                         //Turn DFI scoreboard back on
        //                  p_sequencer.dfi_sb.set_compare(1'b1);
        // `endif

        /*
            Step 5 of 5 for LPDDR3 Read Gate Training
            Continue with regular DRAM commands.
        */
        k510_logi("LPDDR3 Read Gate Training Complete\n\n");

    // read_dll_ctrl_registers();
    k510_logi("\nCompare DLL_CTRL After Read Gate Training:\n");
    // print_pre_vs_cur_data();
    // update_pre_data();

        return 0;
}

#endif

#if DDR_WE_TRAINING_OLD
uint32_t Write_eye_training(void)
{
    uint32_t regdata = 0;
    uint32_t i;
    // uint32_t patdata[4] = {0xffffffff, 0x00000000, 0xffffffff, 0x00000000};
    uint32_t patdata[4] = {0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555};
    uint32_t readpat[4] = {0, 0, 0, 0};
    uint32_t *pddr_addr = 0;

    uint32_t incr_data;
    uint32_t incr_good_min;
    uint32_t incr_good_max;
    uint32_t found_pass;

    uint32_t isEqual;

    k510_logd("Begin LPDDR3 Write Eye Training \n");

    /* Step 1 of 11 for LPDDR3 Write Eye Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to 1.
    */

    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 1. */
    regdata |= 0x1 << 17;

    /*  Set SADJ WRT (bit[10]) to 1. */
    regdata |= 0x1 << 10;

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 2 of 11 for LPDDR3 Write Eye Training
       Set WRITE DQ DLL SADJ = 0 using the DLL_CTRL registers
       through the DDR PHY AHB.
    */
    for(i=0;i<4;i++){
        regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

        /*  WRITE DQ DLL SADJ */
        regdata &= ~(0xff);

        write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
    }

    /* Step 3 of 11 for LPDDR3 Write Eye Training
       Use the following byte wise data 8'b01010101 as the
       initial training pattern.
    */

    /* Step 4 of 11 for LPDDR3 Write Eye Training
       Start of WRITE Eye Training Loop.
    */
    incr_data = 10;
    // incr_data = 0;
    incr_good_min = 99;
    incr_good_max = 0;
    found_pass = 0;

    while(1){

        /* Step 5 of 11 for LPDDR3 Write Eye Training
           Instruct the Memory Controller to WRITE the training
           pattern to the DDR Memory device using ADDRESS = 0
           across the AXI interface to the Controller.
        */

        for(i=0;i<4;i++)
            pddr_addr[i] = patdata[i];

        /* Step 6 of 11 for LPDDR3 Write Eye Training
           Instruct the Memory Controller to READ the ADDRESS = 0 location back.
        */
        //usleep(1);
        for(i=0;i<4;i++)
            readpat[i] = pddr_addr[i];

        for(uint32_t i = 0; i < 4; i++)
        {
            if(readpat[i] != patdata[i])
                k510_logd(">>>>    read_data[%d] = 0x%08X  pattern_data[%d] = 0x%08X [fail]\n", i, readpat[i], i, patdata[i]);
            else
                k510_logd(">>>>    read_data[%d] = pattern_data[%d] = 0x%08X         [pass]\n", i, i, readpat[i]);
        }
        /* Step 7 of 11 for LPDDR3 Write Eye Training
           Compare the resulting READ pattern to the WRITE pattern.
        */

        isEqual=1;
        for(int i = 0; i < 4; i++){
            if(readpat[i] != patdata[i])
            {
                isEqual = 0;
            }
        }

        if (isEqual == 1){
            if(incr_data < incr_good_min){
                incr_good_min = incr_data;
                found_pass = 1;
            }

            if(incr_data > incr_good_max)
                incr_good_max = incr_data;

        }
        else{
            if(found_pass == 1)
                break;
        }

        /* Step 8 of 11 for LPDDR3 Write Eye Training
           Increment +1 the WRITE DQ DLL SADJ using
           DLL_CTRL2,3,4,5  register through the DDR PHY AHB
           until SADJ  = max, then end loop.
        */

        if(incr_data < 82){ //72 -> 82
            incr_data += 1;

            for(i=0;i<4;i++){
                regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

                /*  WRITE DQ DLL SADJ */
                regdata &= ~(0xff);
                regdata |= incr_data & 0xff;

                write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
            }

            /* Step 8b of 11 for LPDDR3 Write Eye Training
               Repeat Step 1
               Step 1 of 11 for LPDDR3 Write Eye Training
               Write AHB Register TRAINING_CTRL1 SADJ_WRT and
               set to 1.
            */
            /*  First read the value of the TRAINING_CTRL1 register. */
            regdata = read_register(TRAINING_CTRL1_ADDR, 1);

            /*  Set CRDB (bit[17] to 1. */
            regdata |= 0x1 << 17;

            /*  Set SADJ WRT (bit[10]) to 1. */
            regdata |= 0x1 << 10;

            /*  Now write the new value to the TRAINING_CTRL1 register. */
            write_register(TRAINING_CTRL1_ADDR, regdata, 1);

        }
        else{
            break;
        }


    } // while (1)


    /////mask for currently k510_logd("Final:  LPDDR3 Write Eye Training Loop  \n");
    k510_logd("incr_good_min  = 0x%x \n ", incr_good_min);
    k510_logd("incr_good_max  = 0x%x \n ", incr_good_max);
    /////mask for currently k510_logd("incr_good_avg  = 0x%x \n ", ((incr_good_min + incr_good_max)/2));

    /*  Verify that the Write Eye Training was successful. */
    if(incr_good_min == 99){
        k510_logd("ERR: LPDDR3 Write Eye Training Failed! \n");
        return 1;
    }

    /* Step 9 of 11 for LPDDR3 Write Eye Training
       Calculate the Average SADJ value for each data slice
       for a passing result as the final value.
    */

    /* Step 10 of 11 for LPDDR3 Write Eye Training
       Write the final result into the DDR PHY registers
       DLL_CTRL2,3,4,5 for WRITE DQ DLL SADJ for each Data Slice.
    */

    /*  Perform steps 9 and 10 at the same time. */

    for(i=0;i<4;i++)
    {
        regdata = read_register(DLL_CTRL2_ADDR + i*4, 1);

        /*  WRITE DQ DLL SADJ */
        regdata &= ~(0xff);
        regdata |= ( 0x10 ) & 0xff;
        //regdata |= ((incr_good_min + incr_good_max)/2) & 0xff;
        //06/18/2021 eq correction
        //regdata |= ((incr_good_min + (incr_good_max - incr_good_min)/2) & 0xff);
      //  regdata =regdata -4;
     //    write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);
     //    write_register(DLL_CTRL2_ADDR + i*4, 0x18001818, 1); // not steady
     //   write_register(DLL_CTRL2_ADDR + i*4, 0x18001810, 1);  // one transaction failed, not very steady

        write_register(DLL_CTRL2_ADDR + i*4, regdata, 1);

        // k510_logi("DLL_CTRL2_ADDR + %d = 0x%08X\n", i, read_register(DLL_CTRL2_ADDR + i*4, 1));

        //    write_register(DLL_CTRL2_ADDR + i*4, 0x18001824, 1);
        //    k510_logi("DLL_CTRL2_ADDR + %d = 0x%08X\n", i, read_register(DLL_CTRL2_ADDR + i*4, 1));
    }

    /* Step 11 of 11 for LPDDR3 Write Eye Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to 0.
    */
    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 0. */
    regdata &= ~(0x1 << 17);

    /*  Set SADJ WRT (bit[10]) to 0. */
    regdata &= ~(0x1 << 10);

    /*  Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logd("LPDDR3 Write Eye Complete \n");

    return 0;

}
#endif

#if DDR_WE_TRAINING_NEW
int Write_eye_training(void)
{
    int regdata;

    // cache_enable(); /* enable cache */

    MADJ = 0x50;
    /* Begin LPDDR3 Write Eye Training */
    k510_logi("Begin LPDDR3 Write Eye Training\n");

    k510_logv(
        "Step 1 of 15 for LPDDR3 Write Eye Training\n"
        "Set LPDDR3 Memory Model tdqs2dq and tdqs2dq_ch_b to 200ps "
        "and 800ps respectively\n"
        "Note this can be randomized but the value must be "
        "between 200 and 800 ps.  For the purposes of the "
        "initial test bench, please use the values above. "
        "DO NOT set the DRAM to update DQSOSCRandom\n"
    );

    k510_logv(
        "Step 2 of 15 for LPDDR3 Write Eye Training\n"
        "Write AHB register TRAINING_CTRL1 SADJ_WRT and set to 1. "
        "at 1600Mb/s\n"
    );
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set SADJ WRT (bit[10]) to 1.
    bit_set_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    for(uint32_t h = 0; h < 4; h++)
    {
        incr_wr_dq_sadj_f0_1_lp4[h] = 0; //2'b00;
    }

    k510_logv(
        "Step 3 of 15 for LPDDR3 Write Eye Training\n"
        "SetDQ DLL Extension to 0 in DLL_CTRL20 through the "
        "DDR PHY AHB.\n"
        "a.  Write DQ SADJ F0 DS0 = 0\n"
        "b.  Write DQ SADJ F1 DS0 = 0\n"
        "c.  Write DQ SADJ F0 DS1 = 0\n"
        "d.  Write DQ SADJ F1 DS1 = 0\n"
        "e.  Write DQ SADJ F0 DS2 = 0\n"
        "f.  Write DQ SADJ F1 DS2 = 0\n"
        "g.  Write DQ SADJ F0 DS3 = 0\n"
        "h.  Write DQ SADJ F1 DS3 = 0\n"
    );
    //  read_register("DLL_CTRL20",DLL_CTRL20_ADDR,regdata,
    //      1'b1);
    regdata = read_register(DLL_CTRL20_ADDR, 1);
    //  WRITE DQ SADJ F1 DS3.
    // regdata[27:26] = incr_wr_dq_sadj_f0_1_lp4[3];
    bit_set_field(regdata, 2, 26, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
    //  WRITE DQ SADJ F0 DS3.
    // regdata[25:24] = incr_wr_dq_sadj_f0_1_lp4[3];
    bit_set_field(regdata, 2, 24, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
    //  WRITE DQ SADJ F1 DS2.
    // regdata[19:18] = incr_wr_dq_sadj_f0_1_lp4[2];
    bit_set_field(regdata, 2, 18, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
    //  WRITE DQ SADJ F0 DS2.
    // regdata[17:16] = incr_wr_dq_sadj_f0_1_lp4[2];
    bit_set_field(regdata, 2, 16, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
    //  WRITE DQ SADJ F1 DS1.
    // regdata[11:10] = incr_wr_dq_sadj_f0_1_lp4[1];
    bit_set_field(regdata, 2, 10, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
    //  WRITE DQ SADJ F0 DS1.
    // regdata[9:8] = incr_wr_dq_sadj_f0_1_lp4[1];
    bit_set_field(regdata, 2, 8, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
    //  WRITE DQ SADJ F1 DS0.
    // regdata[3:2] = incr_wr_dq_sadj_f0_1_lp4[0];
    bit_set_field(regdata, 2, 2, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
    //  WRITE DQ SADJ F0 DS0.
    // regdata[1:0] = incr_wr_dq_sadj_f0_1_lp4[0];
    bit_set_field(regdata, 2, 0, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
    //  Now write the new value to the DLL_CTRL20 register.
    // write_register("DLL_CTRL20",DLL_CTRL20_ADDR,regdata,
    //     1'b1);
    write_register(DLL_CTRL20_ADDR, regdata, 1);

    k510_logv(
        "Step 4 of 15 for LPDDR3 Write Eye Training\n"
        "Set WRITE DQ DLL SADJ = 0 using the DLL_CTRL registers "
        "through the DDR PHY AHB. \n"
        "   a.  DLL_CTRL2 affects Data Slice 0\n"
        "   b.  DLL_CTRL3 affects Data Slice 1\n"
        "   c.  DLL_CTRL4 affects Data Slice 2\n"
        "   d.  DLL_CTRL5 affects Data Slice 3\n"
    );  // REN - this should start at h0A
    // read_register("DLL_CTRL2", DLL_CTRL2_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL2_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0); // REN - this should start at h0A
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL2", DLL_CTRL2_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL2_ADDR, regdata, 1);

    // read_register("DLL_CTRL3", DLL_CTRL3_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL3_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0);
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL3", DLL_CTRL3_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL3_ADDR, regdata, 1); // REN - this should start at h0A

    // read_register("DLL_CTRL4", DLL_CTRL4_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL4_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0);// REN - this should start at h0A
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL4", DLL_CTRL4_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL4_ADDR, regdata, 1);

    // read_register("DLL_CTRL5", DLL_CTRL5_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL5_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0); // REN - this should start at h0A
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL5", DLL_CTRL5_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL5_ADDR, regdata, 1);

    k510_logv(
        "Step 5 of 15 for LPDDR3 Write Eye Training\n"
        "Use the following byte wise data pattern A=8'b01010101 "
        "as the initial training pattern\n"
    );

    k510_logv(
        "Step 6 of 15 for LPDDR3 Write Eye Training\n"
        "Start of WRITE EYE Training Loop\n"
    );
    for(uint32_t h = 0; h < 4; h++)
    {
        incr_data_lp4[h]      = 0;  // REN - this should start at h0A
        // incr_data_lp4[h]      = 0xA;  // REN - this should start at h0A
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        incr_good_min_lp4[h]  = 99;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        incr_good_max_lp4[h]  = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        found_pass_lp4[h] = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        wr_dq_sadj_f0_1_N_lp4_minus_1[h] = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        found_fail_after_pass_lp4[h] = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        wr_dq_sadj_f0_1_N_lp4[h] = 0;
    }

    continue_loop = 1;

    for(uint32_t h = 0; h < 4; h++)
    {
        continue_loop_lp4[h] = 1;
    }

    uint32_t write_addr = 0;

    while(continue_loop == 1)
    {

        for(uint32_t i = 0; i < 4; i++)
        {
            k510_logd("==== incr_data_lp4[%d] = 0x%08X ====\n", i, incr_data_lp4[i]);
        }

        k510_logv(
            "Step 7 of 15 for LPDDR3 Write Eye Training\n"
            "Instruct the Memory Controller to WRITE the training "
            "pattern to the DDR Memory device using Address = 0 "
            "across the AXI interface to the Controller\n"
        );
        // mem_addr = (uint32_t *)0;
        mem_addr += 8;

        k510_logd("==== Write Eye test addr is 0x%08X ====\n", mem_addr);

        // mem_wdata[0] = 0x01234567;
        // mem_wdata[1] = 0x89abcdef;
        // mem_wdata[2] = 0xfedcba98;
        // mem_wdata[3] = 0x76543210;
        mem_wdata[0] = pattern[0];
        mem_wdata[1] = pattern[1];
        mem_wdata[2] = pattern[2];
        mem_wdata[3] = pattern[3];

     //   for(uint32_t i = 0; i < 8; i++)
        for(uint32_t i = 0; i < 2; i++)
        {
            *(mem_addr + i * 4) = mem_wdata[0];
            *(mem_addr + i * 4 + 1) = mem_wdata[1];
            *(mem_addr + i * 4 + 2) = mem_wdata[2];
            *(mem_addr + i * 4 + 3) = mem_wdata[3];
        }

        // cache_wbinval(0, 0, 256);   /* cache flush 0->256 */
        k510_logv(
            "Step 8 of 15 for LPDDR3 Write Eye Training\n"
            "Instruct the Memory Controller to READ the Address = 0 "
            "back\n"
        );

        for(uint32_t i = 0; i < 8; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        for(uint32_t i = 0; i < 4; i++)
        {
            k510_logd(">>>> mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 9 of 15 for LPDDR3 Write Eye Training\n"
            "Compare the resulting read pattern to the WRITE pattern.\n"
            "a.  Save Pass/Fail results for each Data Slice\n"
        );
        isEqual_ds0 = 1;
        isEqual_ds1 = 1;
        isEqual_ds2 = 1;
        isEqual_ds3 = 1;

        for(uint32_t j = 0; j < 4; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 0) != bit_get_field(mem_wdata[j], 8, 0))
            {
                isEqual_ds0 = 0;
                k510_logd("DS0 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], mem_wdata[j]);
            }
        }

        for(uint32_t j = 0; j < 4; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 8) != bit_get_field(mem_wdata[j], 8, 8))
            {
                isEqual_ds1 = 0;
                k510_logd("DS1 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], mem_wdata[j]);
            }
        }

        for(uint32_t j = 0; j < 4; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 16) != bit_get_field(mem_wdata[j], 8, 16))
            {
                isEqual_ds2 = 0;
                k510_logd("DS2 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], mem_wdata[j]);
            }
        }

        for(uint32_t j = 0; j < 4; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 24) != bit_get_field(mem_wdata[j], 8, 24))
            {
                isEqual_ds3 = 0;
                k510_logd("DS3 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], mem_wdata[j]);
            }
        }

        k510_logi("isEqual_ds0 = %0d isEqual_ds1 = %0d isEqual_ds2 = %0d isEqual_ds3 = %0d\n",
                                                             isEqual_ds0,isEqual_ds1,isEqual_ds2,isEqual_ds3);

        if (isEqual_ds0 == 1 || isEqual_ds1 == 1 || isEqual_ds2 == 1 || isEqual_ds3 == 1)
        {
            if(isEqual_ds0 == 1)
            {
                if (incr_data_lp4[0] < incr_good_min_lp4[0])
                {
                    incr_good_min_lp4[0] = incr_data_lp4[0];
                    incr_good_max_lp4[0] = incr_data_lp4[0];
                    found_pass_lp4[0] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[0] = incr_wr_dq_sadj_f0_1_lp4[0];
                }
                else if (incr_data_lp4[0] > incr_good_max_lp4[0])
                {
                    incr_good_max_lp4[0] = incr_data_lp4[0];
                }
            }

            if(isEqual_ds1 == 1)
            {
                if (incr_data_lp4[1] < incr_good_min_lp4[1])
                {
                    incr_good_min_lp4[1] = incr_data_lp4[1];
                    incr_good_max_lp4[1] = incr_data_lp4[1];
                    found_pass_lp4[1] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[1] = incr_wr_dq_sadj_f0_1_lp4[1];
                } else if (incr_data_lp4[1] > incr_good_max_lp4[1])
                    incr_good_max_lp4[1] = incr_data_lp4[1];
            }
            if(isEqual_ds2 == 1)
            {
                if (incr_data_lp4[2] < incr_good_min_lp4[2])
                {
                    incr_good_min_lp4[2] = incr_data_lp4[2];
                    incr_good_max_lp4[2] = incr_data_lp4[2];
                    found_pass_lp4[2] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[2] = incr_wr_dq_sadj_f0_1_lp4[2];
                } else if (incr_data_lp4[2] > incr_good_max_lp4[2])
                    incr_good_max_lp4[2] = incr_data_lp4[2];
            }
            if(isEqual_ds3 == 1)
            {
                if (incr_data_lp4[3] < incr_good_min_lp4[3])
                {
                    incr_good_min_lp4[3] = incr_data_lp4[3];
                    incr_good_max_lp4[3] = incr_data_lp4[3];
                    found_pass_lp4[3] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[3] = incr_wr_dq_sadj_f0_1_lp4[3];
                } else if (incr_data_lp4[3] > incr_good_max_lp4[3])
                    incr_good_max_lp4[3] = incr_data_lp4[3];
            }
        }
        else
        {
            for(int h = 0; h < 4; h++)
            {
                if (found_pass_lp4[h] == 1)
                {
                    found_fail_after_pass_lp4[h] = 1;
                    wr_dq_sadj_f0_1_N_lp4[h] = incr_wr_dq_sadj_f0_1_lp4[h];
                    continue_loop_lp4[h]  = 0;
                }
            }
        }

        // for (int h = 0; h <4; h++) {
        //         k510_logd("%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h",
        //         "incr_wr_dq_sadj_f0_1_lp4 ", h,incr_wr_dq_sadj_f0_1_lp4[h],
        //         incr_wr_dq_sadj_f0_1_lp4[h],
        //         "incr_data_lp4            ", h, incr_data_lp4[h], incr_data_lp4[h],
        //         "incr_good_min_lp4        ", h, incr_good_min_lp4[h], incr_good_min_lp4[h],
        //         "incr_good_max_lp4        ", h, incr_good_max_lp4[h], incr_good_max_lp4[h],
        //         "incr_good_avg_lp4        ", h, ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2),
        //         ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2));
        // }

        k510_logv(
            "Step 10 of 15 for LPDDR3 Write Eye Training\n"
            "Increment +1 the WRITE DQ DLL SADJ using DLL_CTRL2,3,4, "
            "5 registers through  "
            "the DDR PHY AHB until SADJ = max value, then end loop.\n"
            "a.  If SADJ[data slice] = MADJ, reset SADJ[data slice] "
            "= 0 and increment \n"
            "WRITE DQ SADJ F0/1[data slice] + 1 "
            "(maximum allowed value for this is 3)\n"
        );
        for(int h = 0; h < 4; h++)
        {
            if (incr_data_lp4[h] <= MADJ)  // REN this value should be MADJ + h0A
            {
                incr_data_lp4[h] += 1;

                if (h == 0)
                {   //DS0
                    regdata = read_register(DLL_CTRL2_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[0];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[0] & 0xFF);
                    write_register(DLL_CTRL2_ADDR, regdata, 1);
                }

                if(h == 1)
                {   //DS1
                    regdata = read_register(DLL_CTRL3_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[1];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[1] & 0xFF);
                    write_register(DLL_CTRL3_ADDR, regdata, 1);
                }

                if(h == 2)
                {   //DS2
                    regdata = read_register(DLL_CTRL4_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[2];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[2] & 0xFF);
                    write_register(DLL_CTRL4_ADDR, regdata, 1);
                }

                if(h == 3)
                { //DS3
                    regdata = read_register(DLL_CTRL5_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[3];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[3] & 0xFF);
                    write_register(DLL_CTRL5_ADDR, regdata, 1);
                }
            }
            else
            {
                if (found_pass_lp4[h] == 0)
                {
                    if (incr_wr_dq_sadj_f0_1_lp4[h] < 3)
                    {
                        incr_data_lp4[h] = 0;
                        incr_wr_dq_sadj_f0_1_lp4[h] += 1;

                        k510_logd("%s = %3d = 0x%8x",
                            "Increment WRITE_DQ_SADJ_F0/1\n",
                            incr_wr_dq_sadj_f0_1_lp4[h],
                            incr_wr_dq_sadj_f0_1_lp4[h]);
                    }
                    else
                    {   //if
                        continue_loop_lp4[h] = 0;
                    //   foreach(continue_loop_lp4[h]) $display("continue_loop_lp4[%0d] = %0d", h, continue_loop_lp4[h]);
                    }
                    //  First read the value of the DLL_CTRL20 register.
                    regdata = read_register(DLL_CTRL20_ADDR,1);
                    //  WRITE DQ SADJ F1 DS3.
                    //   regdata[27:26] = incr_wr_dq_sadj_f0_1_lp4[3];
                    bit_set_field(regdata, 2, 26, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
                        //  WRITE DQ SADJ F0 DS3.
                    //   regdata[25:24] = incr_wr_dq_sadj_f0_1_lp4[3];
                    bit_set_field(regdata, 2, 24, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
                        //  WRITE DQ SADJ F1 DS2.
                    //   regdata[19:18] = incr_wr_dq_sadj_f0_1_lp4[2];
                    bit_set_field(regdata, 2, 18, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
                        //  WRITE DQ SADJ F0 DS2.
                    //   regdata[17:16] = incr_wr_dq_sadj_f0_1_lp4[2];
                    bit_set_field(regdata, 2, 16, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
                        //  WRITE DQ SADJ F1 DS1.
                    //   regdata[11:10] = incr_wr_dq_sadj_f0_1_lp4[1];
                    bit_set_field(regdata, 2, 10, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
                        //  WRITE DQ SADJ F0 DS1.
                    //   regdata[9:8] = incr_wr_dq_sadj_f0_1_lp4[1];
                    bit_set_field(regdata, 2, 8, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
                        //  WRITE DQ SADJ F1 DS0.
                    //   regdata[3:2] = incr_wr_dq_sadj_f0_1_lp4[0];
                    bit_set_field(regdata, 2, 2, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
                        //  WRITE DQ SADJ F0 DS0.
                    //   regdata[1:0] = incr_wr_dq_sadj_f0_1_lp4[0];
                    bit_set_field(regdata, 2, 0, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
                        //  Now write the new value to the DLL_CTRL20
                        // register.

                    write_register(DLL_CTRL20_ADDR, regdata, 1);

                    //   msg = $sformatf("%s%s\n\t%s\n\t%s\n\t%s\n\t%s",
                    //   "Set WRITE DQ DLL SADJ = 0 using the DLL_CTRL ",
                    //      "registers through the DDR PHY AHB. ",
                    //      "\ta.  DLL_CTRL2 affects Data Slice 0",
                    //      "\tb.  DLL_CTRL3 affects Data Slice 1",
                    //      "\tc.  DLL_CTRL4 affects Data Slice 2",
                    //      "\td.  DLL_CTRL5 affects Data Slice 3");
                    //   `uvm_info(report_id, msg, UVM_NONE ) //UVM_MEDIUM)

                    regdata = read_register(DLL_CTRL2_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL2_ADDR, regdata, 1);

                    regdata = read_register(DLL_CTRL3_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL3_ADDR, regdata, 1);

                    regdata = read_register(DLL_CTRL4_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL4_ADDR, regdata, 1);

                    regdata = read_register(DLL_CTRL5_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL5_ADDR, regdata, 1);
                }
                else
                {
                    continue_loop = 0;
                }
            } // if (found_pass_lp4 == 1'b0)
        }

        k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
        k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
        k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
        k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        k510_logd("DLL_CTRL20 = 0x%08x \n", read_register(DLL_CTRL20_ADDR, 1));

        if(!(continue_loop_lp4[0] | continue_loop_lp4[1] | continue_loop_lp4[2] | continue_loop_lp4[3]))
        {
            continue_loop = 0;
        }
    } // while(continue_loop == 1)

    //  Verify that the LPDDR3 Write Eye Training was successful.
    if (incr_good_min_lp4[0] == 99 || incr_good_min_lp4[1] == 99 ||
        incr_good_min_lp4[2] == 99 ||incr_good_min_lp4[3] == 99 )
    {
        k510_loge("LPDDR3 Write Eye Training Loop Failed!");
        return -1;
    }

    k510_logv(
        "Step 11 of 15 for LPDDR3 Write Eye Training"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to "
        "1"
    );
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR,1);
    //  Set SADJ WRT (bit[10]) to 1.
    // regdata[10] = 1'b1;
    bit_set_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    k510_logv(
        "Step 12 of 15 for LPDDR3 Write Eye Training\n"
        "Calculate the Average SADJ value for each data slice "
        "for a passing result as the final value\n"
    );
    for(int h = 0; h < 4; h++)
    {
        if (wr_dq_sadj_f0_1_N_lp4_minus_1[h] != wr_dq_sadj_f0_1_N_lp4[h])
        {

            TotalWindowPass = MADJ - incr_good_min_lp4[h] + incr_good_max_lp4[h];
            Midpoint = TotalWindowPass / 2;  // ?! what is this?

            if ((incr_good_min_lp4[h] + Midpoint) >= MADJ) {
            incr_good_avg_lp4[h] = incr_good_min_lp4[h] + Midpoint - MADJ;
            incr_wr_dq_sadj_f0_1_lp4_avg[h] = wr_dq_sadj_f0_1_N_lp4[h];
            }

        }
        else
        {
            incr_good_avg_lp4[h] = ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2);

            avg_real_lp4[h] = ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2.0);

            k510_logd("incr_good_min_lp4[%d] == %d  0x%08X\n", h, incr_good_min_lp4[h], incr_good_min_lp4[h]);
            k510_logd("incr_good_max_lp4[%d] == %d  0x%08X\n", h, incr_good_max_lp4[h], incr_good_max_lp4[h]);
            k510_logd("incr_good_avg_lp4[%0d] = %0d, avg_real_lp4[%0d] = %3.3f\n",
                      h, incr_good_avg_lp4[h], h, avg_real_lp4[h]);

            if ((avg_real_lp4[h] - incr_good_avg_lp4[h]) >= 0.5)
            incr_good_avg_lp4[h] +=1;

            k510_logd("round incr_good_avg_lp4[%0d] = %0d, avg_real_lp4[%0d] = %3.3f\n",
            h, incr_good_avg_lp4[h], h, avg_real_lp4[h]);

            incr_wr_dq_sadj_f0_1_lp4_avg[h] = wr_dq_sadj_f0_1_N_lp4_minus_1[h];
        }
    }

    k510_logv(
        "Step 13 of 15 for LPDDR3 Write Eye Training\n"
        "Write the final result into the DDR PHY registers "
        "DLL_CTRL2,3,4,5 for WRITE DQ DLL SADJ for each "
        "data slice\n"
    );

    /* Add for because training with ODT write eye fail, but sub 8 can pass */
    // incr_good_avg_lp4[0] -= 8;
    // incr_good_avg_lp4[1] -= 8;
    // incr_good_avg_lp4[2] -= 8;
    // incr_good_avg_lp4[3] -= 8;

    regdata = read_register(DLL_CTRL2_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[0];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[0] & 0xff);
    write_register(DLL_CTRL2_ADDR, regdata, 1);

    regdata = read_register(DLL_CTRL3_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[1];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[1] & 0xff);
    write_register(DLL_CTRL3_ADDR, regdata, 1);

    regdata = read_register(DLL_CTRL4_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[2];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[2] & 0xff);
    write_register(DLL_CTRL4_ADDR, regdata, 1);

    regdata = read_register(DLL_CTRL5_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[3];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[3] & 0xff);
    write_register(DLL_CTRL5_ADDR, regdata, 1);

    // for(int h = 0; h < 4; h++) {

    //     msg = $sformatf("%-42s",
    //         "Final:  LPDDR3 Write Eye Training Loop ");
    //     msg = {msg, "\tSADJ DLL_CTRL2,3,4,5"};
    //     msg = {msg, $sformatf("\tincr_good_min_lp4  = %3d = 0x%8h,  ",
    //         incr_good_min_lp4[h], incr_good_min_lp4[h])};
    //     msg = {msg, $sformatf("incr_good_max_lp4  = %3d = 0x%8h,  ",
    //         incr_good_max_lp4[h], incr_good_max_lp4[h])};
    //     msg = {msg, $sformatf("incr_good_avg_lp4  = %3d = 0x%8h",
    //         incr_good_avg_lp4[h], incr_good_avg_lp4[h])};
    //     `uvm_info(report_id, msg, UVM_NONE ) //UVM_MEDIUM)
    // }

    for(int h = 0; h < 4; h++) {
        k510_logd("Final:  LPDDR3 Write Eye Training Loop\n");
        k510_logd("\t\tWRITE DQ SADJ F0/1[%0d]  = %3d = 0x%08x\n",
            h, incr_wr_dq_sadj_f0_1_lp4_avg[h], incr_wr_dq_sadj_f0_1_lp4_avg[h]);
    }

    k510_logv(
        "Step 14 of 15 for LPDDR3 Write Eye Training\n"
        "Write the final result into the DDR PHY registers "
        "DLL_CTRL20 WRITE DQ \n\tDLL SADJ F0/1 DS[3:0] for each "
        "data slice\n"
    );

    //  First read the value of the DLL_CTRL20 register.
    regdata = read_register(DLL_CTRL20_ADDR, 1);
    //  WRITE DQ SADJ F1 DS3.
    // regdata[27:26] = incr_wr_dq_sadj_f0_1_lp4_avg[3];
    bit_set_field(regdata, 2, 26, incr_wr_dq_sadj_f0_1_lp4_avg[3] & 0x3);
    //  WRITE DQ SADJ F0 DS3.
    // regdata[25:24] = incr_wr_dq_sadj_f0_1_lp4_avg[3];
    bit_set_field(regdata, 2, 24, incr_wr_dq_sadj_f0_1_lp4_avg[3] & 0x3);
    //  WRITE DQ SADJ F1 DS2.
    // regdata[19:18] = incr_wr_dq_sadj_f0_1_lp4_avg[2];
    bit_set_field(regdata, 2, 18, incr_wr_dq_sadj_f0_1_lp4_avg[2] & 0x3);
    //  WRITE DQ SADJ F0 DS2.
    // regdata[17:16] = incr_wr_dq_sadj_f0_1_lp4_avg[2];
    bit_set_field(regdata, 2, 16, incr_wr_dq_sadj_f0_1_lp4_avg[2] & 0x3);
    //  WRITE DQ SADJ F1 DS1.
    // regdata[11:10] = incr_wr_dq_sadj_f0_1_lp4_avg[1];
    bit_set_field(regdata, 2, 10, incr_wr_dq_sadj_f0_1_lp4_avg[1] & 0x3);
    //  WRITE DQ SADJ F0 DS1.
    // regdata[9:8] = incr_wr_dq_sadj_f0_1_lp4_avg[1];
    bit_set_field(regdata, 2, 8, incr_wr_dq_sadj_f0_1_lp4_avg[1] & 0x3);
    //  WRITE DQ SADJ F1 DS0.
    // regdata[3:2] = incr_wr_dq_sadj_f0_1_lp4_avg[0];
    bit_set_field(regdata, 2, 2, incr_wr_dq_sadj_f0_1_lp4_avg[0] & 0x3);
    //  WRITE DQ SADJ F0 DS0.
    // regdata[1:0] = incr_wr_dq_sadj_f0_1_lp4_avg[0];
    bit_set_field(regdata, 2, 0, incr_wr_dq_sadj_f0_1_lp4_avg[0] & 0x3);
    //  Now write the new value to the DLL_CTRL20
    // register.
    write_register(DLL_CTRL20_ADDR,regdata, 1);

    k510_logv(
        "Step 15 of 15 for LPDDR3 Write Eye Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to "
        "0\n"
    );
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set SADJ WRT (bit[10]) to 0.
    // regdata[10] = 1'b0;
    bit_clr_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /* LPDDR3 Write Eye Complete */
    k510_logi("LPDDR3 Write Eye Complete\n");

    // read_dll_ctrl_registers();
    k510_logi("\nCompare DLL_CTRL After Write Eye Training\n");
    // print_pre_vs_cur_data();
    // update_pre_data();

    // cache_flush_disable();

    return 0;
}

#endif

#if DDR_WE_TRAINING_WRITE_PATTERN
int Write_eye_training(void)
{
    int regdata;

    // cache_enable(); /* enable cache */

    MADJ = 0x50;
    /* Begin LPDDR3 Write Eye Training */
    k510_logi("Begin LPDDR3 Write Eye Training by Write pattern\n");

    k510_logv(
        "Step 1 of 15 for LPDDR3 Write Eye Training\n"
        "Set LPDDR3 Memory Model tdqs2dq and tdqs2dq_ch_b to 200ps "
        "and 800ps respectively\n"
        "Note this can be randomized but the value must be "
        "between 200 and 800 ps.  For the purposes of the "
        "initial test bench, please use the values above. "
        "DO NOT set the DRAM to update DQSOSCRandom\n"
    );

    k510_logv(
        "Step 2 of 15 for LPDDR3 Write Eye Training\n"
        "Write AHB register TRAINING_CTRL1 SADJ_WRT and set to 1. "
        "at 1600Mb/s\n"
    );
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set SADJ WRT (bit[10]) to 1.
    bit_set_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    for(uint32_t h = 0; h < 4; h++)
    {
        incr_wr_dq_sadj_f0_1_lp4[h] = 0; //2'b00;
    }

    k510_logv(
        "Step 3 of 15 for LPDDR3 Write Eye Training\n"
        "SetDQ DLL Extension to 0 in DLL_CTRL20 through the "
        "DDR PHY AHB.\n"
        "a.  Write DQ SADJ F0 DS0 = 0\n"
        "b.  Write DQ SADJ F1 DS0 = 0\n"
        "c.  Write DQ SADJ F0 DS1 = 0\n"
        "d.  Write DQ SADJ F1 DS1 = 0\n"
        "e.  Write DQ SADJ F0 DS2 = 0\n"
        "f.  Write DQ SADJ F1 DS2 = 0\n"
        "g.  Write DQ SADJ F0 DS3 = 0\n"
        "h.  Write DQ SADJ F1 DS3 = 0\n"
    );
    //  read_register("DLL_CTRL20",DLL_CTRL20_ADDR,regdata,
    //      1'b1);
    regdata = read_register(DLL_CTRL20_ADDR, 1);
    //  WRITE DQ SADJ F1 DS3.
    // regdata[27:26] = incr_wr_dq_sadj_f0_1_lp4[3];
    bit_set_field(regdata, 2, 26, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
    //  WRITE DQ SADJ F0 DS3.
    // regdata[25:24] = incr_wr_dq_sadj_f0_1_lp4[3];
    bit_set_field(regdata, 2, 24, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
    //  WRITE DQ SADJ F1 DS2.
    // regdata[19:18] = incr_wr_dq_sadj_f0_1_lp4[2];
    bit_set_field(regdata, 2, 18, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
    //  WRITE DQ SADJ F0 DS2.
    // regdata[17:16] = incr_wr_dq_sadj_f0_1_lp4[2];
    bit_set_field(regdata, 2, 16, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
    //  WRITE DQ SADJ F1 DS1.
    // regdata[11:10] = incr_wr_dq_sadj_f0_1_lp4[1];
    bit_set_field(regdata, 2, 10, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
    //  WRITE DQ SADJ F0 DS1.
    // regdata[9:8] = incr_wr_dq_sadj_f0_1_lp4[1];
    bit_set_field(regdata, 2, 8, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
    //  WRITE DQ SADJ F1 DS0.
    // regdata[3:2] = incr_wr_dq_sadj_f0_1_lp4[0];
    bit_set_field(regdata, 2, 2, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
    //  WRITE DQ SADJ F0 DS0.
    // regdata[1:0] = incr_wr_dq_sadj_f0_1_lp4[0];
    bit_set_field(regdata, 2, 0, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
    //  Now write the new value to the DLL_CTRL20 register.
    // write_register("DLL_CTRL20",DLL_CTRL20_ADDR,regdata,
    //     1'b1);
    write_register(DLL_CTRL20_ADDR, regdata, 1);

    k510_logv(
        "Step 4 of 15 for LPDDR3 Write Eye Training\n"
        "Set WRITE DQ DLL SADJ = 0 using the DLL_CTRL registers "
        "through the DDR PHY AHB. \n"
        "   a.  DLL_CTRL2 affects Data Slice 0\n"
        "   b.  DLL_CTRL3 affects Data Slice 1\n"
        "   c.  DLL_CTRL4 affects Data Slice 2\n"
        "   d.  DLL_CTRL5 affects Data Slice 3\n"
    );  // REN - this should start at h0A
    // read_register("DLL_CTRL2", DLL_CTRL2_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL2_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0); // REN - this should start at h0A
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL2", DLL_CTRL2_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL2_ADDR, regdata, 1);

    // read_register("DLL_CTRL3", DLL_CTRL3_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL3_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0);
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL3", DLL_CTRL3_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL3_ADDR, regdata, 1); // REN - this should start at h0A

    // read_register("DLL_CTRL4", DLL_CTRL4_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL4_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0);// REN - this should start at h0A
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL4", DLL_CTRL4_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL4_ADDR, regdata, 1);

    // read_register("DLL_CTRL5", DLL_CTRL5_ADDR, regdata, 1'b1);
    regdata = read_register(DLL_CTRL5_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = 0;
    bit_clr_bits(regdata, 8, 0); // REN - this should start at h0A
    // bit_set_field(regdata, 8, 0, 0xA);
    // write_register("DLL_CTRL5", DLL_CTRL5_ADDR, regdata, 1'b1);
    write_register(DLL_CTRL5_ADDR, regdata, 1);

    k510_logv(
        "Step 5 of 15 for LPDDR3 Write Eye Training\n"
        "Use the following byte wise data pattern A=8'b01010101 "
        "as the initial training pattern\n"
    );

    k510_logv(
        "Step 6 of 15 for LPDDR3 Write Eye Training\n"
        "Start of WRITE EYE Training Loop\n"
    );
    for(uint32_t h = 0; h < 4; h++)
    {
        incr_data_lp4[h]      = 0;  // REN - this should start at h0A
        // incr_data_lp4[h]      = 0xA;  // REN - this should start at h0A
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        incr_good_min_lp4[h]  = 99;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        incr_good_max_lp4[h]  = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        found_pass_lp4[h] = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        wr_dq_sadj_f0_1_N_lp4_minus_1[h] = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        found_fail_after_pass_lp4[h] = 0;
    }

    for(uint32_t h = 0; h < 4; h++)
    {
        wr_dq_sadj_f0_1_N_lp4[h] = 0;
    }

    continue_loop = 1;

    for(uint32_t h = 0; h < 4; h++)
    {
        continue_loop_lp4[h] = 1;
    }

    uint32_t write_addr = 0;

    while(continue_loop == 1)
    {

        for(uint32_t i = 0; i < 4; i++)
        {
            k510_logd("==== incr_data_lp4[%d] = 0x%08X ====\n", i, incr_data_lp4[i]);
        }

        k510_logv(
            "Step 7 of 15 for LPDDR3 Write Eye Training\n"
            "Instruct the Memory Controller to WRITE the training "
            "pattern to the DDR Memory device using Address = 0 "
            "across the AXI interface to the Controller\n"
        );
        // mem_addr = (uint32_t *)0;
        mem_addr += 8;

        k510_logd("==== Write Eye test addr is 0x%08X ====\n", mem_addr);

        // mem_wdata[0] = 0x01234567;
        // mem_wdata[1] = 0x89abcdef;
        // mem_wdata[2] = 0xfedcba98;
        // mem_wdata[3] = 0x76543210;
        // mem_wdata[0] = pattern[0];
        // mem_wdata[1] = pattern[1];
        // mem_wdata[2] = pattern[2];
        // mem_wdata[3] = pattern[3];

     //   for(uint32_t i = 0; i < 8; i++)
        // for(uint32_t i = 0; i < 2; i++)
        // {
        //     *(mem_addr + i * 4) = mem_wdata[0];
        //     *(mem_addr + i * 4 + 1) = mem_wdata[1];
        //     *(mem_addr + i * 4 + 2) = mem_wdata[2];
        //     *(mem_addr + i * 4 + 3) = mem_wdata[3];
        // }

        for(uint32_t i = 0; i < 24; i++)
        {
            *(mem_addr + i) = pattern[i];
        }

        // cache_wbinval(0, 0, 256);   /* cache flush 0->256 */
        k510_logv(
            "Step 8 of 15 for LPDDR3 Write Eye Training\n"
            "Instruct the Memory Controller to READ the Address = 0 "
            "back\n"
        );

        for(uint32_t i = 0; i < 24; i++)
        {
            mem_rdata[i] = *(mem_addr + i);
        }

        for(uint32_t i = 0; i < 24; i++)
        {
            k510_logd(">>>> mem_rdata[%d] = 0x%08X\n", i, mem_rdata[i]);
        }

        k510_logv(
            "Step 9 of 15 for LPDDR3 Write Eye Training\n"
            "Compare the resulting read pattern to the WRITE pattern.\n"
            "a.  Save Pass/Fail results for each Data Slice\n"
        );
        isEqual_ds0 = 1;
        isEqual_ds1 = 1;
        isEqual_ds2 = 1;
        isEqual_ds3 = 1;

        for(uint32_t j = 0; j < 24; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 0) != bit_get_field(pattern[j], 8, 0))
            {
                isEqual_ds0 = 0;
                k510_logd("DS0 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], pattern[j]);
            }
        }

        for(uint32_t j = 0; j < 24; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 8) != bit_get_field(pattern[j], 8, 8))
            {
                isEqual_ds1 = 0;
                k510_logd("DS1 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], pattern[j]);
            }
        }

        for(uint32_t j = 0; j < 24; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 16) != bit_get_field(pattern[j], 8, 16))
            {
                isEqual_ds2 = 0;
                k510_logd("DS2 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], pattern[j]);
            }
        }

        for(uint32_t j = 0; j < 24; j++)
        {
            if(bit_get_field(mem_rdata[j], 8, 24) != bit_get_field(pattern[j], 8, 24))
            {
                isEqual_ds3 = 0;
                k510_logd("DS3 ERR: mem_rdata[%d] = 0x%0X but should be 0x%08X\n", j, mem_rdata[j], pattern[j]);
            }
        }

        k510_logi("isEqual_ds0 = %0d isEqual_ds1 = %0d isEqual_ds2 = %0d isEqual_ds3 = %0d\n",
                                                             isEqual_ds0,isEqual_ds1,isEqual_ds2,isEqual_ds3);

        if (isEqual_ds0 == 1 || isEqual_ds1 == 1 || isEqual_ds2 == 1 || isEqual_ds3 == 1)
        {
            if(isEqual_ds0 == 1)
            {
                if (incr_data_lp4[0] < incr_good_min_lp4[0])
                {
                    incr_good_min_lp4[0] = incr_data_lp4[0];
                    incr_good_max_lp4[0] = incr_data_lp4[0];
                    found_pass_lp4[0] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[0] = incr_wr_dq_sadj_f0_1_lp4[0];
                }
                else if (incr_data_lp4[0] > incr_good_max_lp4[0])
                {
                    incr_good_max_lp4[0] = incr_data_lp4[0];
                }
            }

            if(isEqual_ds1 == 1)
            {
                if (incr_data_lp4[1] < incr_good_min_lp4[1])
                {
                    incr_good_min_lp4[1] = incr_data_lp4[1];
                    incr_good_max_lp4[1] = incr_data_lp4[1];
                    found_pass_lp4[1] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[1] = incr_wr_dq_sadj_f0_1_lp4[1];
                } else if (incr_data_lp4[1] > incr_good_max_lp4[1])
                    incr_good_max_lp4[1] = incr_data_lp4[1];
            }
            if(isEqual_ds2 == 1)
            {
                if (incr_data_lp4[2] < incr_good_min_lp4[2])
                {
                    incr_good_min_lp4[2] = incr_data_lp4[2];
                    incr_good_max_lp4[2] = incr_data_lp4[2];
                    found_pass_lp4[2] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[2] = incr_wr_dq_sadj_f0_1_lp4[2];
                } else if (incr_data_lp4[2] > incr_good_max_lp4[2])
                    incr_good_max_lp4[2] = incr_data_lp4[2];
            }
            if(isEqual_ds3 == 1)
            {
                if (incr_data_lp4[3] < incr_good_min_lp4[3])
                {
                    incr_good_min_lp4[3] = incr_data_lp4[3];
                    incr_good_max_lp4[3] = incr_data_lp4[3];
                    found_pass_lp4[3] = 1;
                    wr_dq_sadj_f0_1_N_lp4_minus_1[3] = incr_wr_dq_sadj_f0_1_lp4[3];
                } else if (incr_data_lp4[3] > incr_good_max_lp4[3])
                    incr_good_max_lp4[3] = incr_data_lp4[3];
            }
        }
        else
        {
            for(int h = 0; h < 4; h++)
            {
                if (found_pass_lp4[h] == 1)
                {
                    found_fail_after_pass_lp4[h] = 1;
                    wr_dq_sadj_f0_1_N_lp4[h] = incr_wr_dq_sadj_f0_1_lp4[h];
                    continue_loop_lp4[h]  = 0;
                }
            }
        }

        // for (int h = 0; h <4; h++) {
        //         k510_logd("%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h\n\t%s[%0d]= %3d = 0x%8h",
        //         "incr_wr_dq_sadj_f0_1_lp4 ", h,incr_wr_dq_sadj_f0_1_lp4[h],
        //         incr_wr_dq_sadj_f0_1_lp4[h],
        //         "incr_data_lp4            ", h, incr_data_lp4[h], incr_data_lp4[h],
        //         "incr_good_min_lp4        ", h, incr_good_min_lp4[h], incr_good_min_lp4[h],
        //         "incr_good_max_lp4        ", h, incr_good_max_lp4[h], incr_good_max_lp4[h],
        //         "incr_good_avg_lp4        ", h, ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2),
        //         ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2));
        // }

        k510_logv(
            "Step 10 of 15 for LPDDR3 Write Eye Training\n"
            "Increment +1 the WRITE DQ DLL SADJ using DLL_CTRL2,3,4, "
            "5 registers through  "
            "the DDR PHY AHB until SADJ = max value, then end loop.\n"
            "a.  If SADJ[data slice] = MADJ, reset SADJ[data slice] "
            "= 0 and increment \n"
            "WRITE DQ SADJ F0/1[data slice] + 1 "
            "(maximum allowed value for this is 3)\n"
        );
        for(int h = 0; h < 4; h++)
        {
            if (incr_data_lp4[h] <= MADJ)  // REN this value should be MADJ + h0A
            {
                incr_data_lp4[h] += 1;

                if (h == 0)
                {   //DS0
                    regdata = read_register(DLL_CTRL2_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[0];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[0] & 0xFF);
                    write_register(DLL_CTRL2_ADDR, regdata, 1);
                }

                if(h == 1)
                {   //DS1
                    regdata = read_register(DLL_CTRL3_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[1];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[1] & 0xFF);
                    write_register(DLL_CTRL3_ADDR, regdata, 1);
                }

                if(h == 2)
                {   //DS2
                    regdata = read_register(DLL_CTRL4_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[2];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[2] & 0xFF);
                    write_register(DLL_CTRL4_ADDR, regdata, 1);
                }

                if(h == 3)
                { //DS3
                    regdata = read_register(DLL_CTRL5_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    // regdata[7:0] = incr_data_lp4[3];
                    bit_set_field(regdata, 8, 0, incr_data_lp4[3] & 0xFF);
                    write_register(DLL_CTRL5_ADDR, regdata, 1);
                }
            }
            else
            {
                if (found_pass_lp4[h] == 0)
                {
                    if (incr_wr_dq_sadj_f0_1_lp4[h] < 3)
                    {
                        incr_data_lp4[h] = 0;
                        incr_wr_dq_sadj_f0_1_lp4[h] += 1;

                        k510_logd("%s = %3d = 0x%8x",
                            "Increment WRITE_DQ_SADJ_F0/1\n",
                            incr_wr_dq_sadj_f0_1_lp4[h],
                            incr_wr_dq_sadj_f0_1_lp4[h]);
                    }
                    else
                    {   //if
                        continue_loop_lp4[h] = 0;
                    //   foreach(continue_loop_lp4[h]) $display("continue_loop_lp4[%0d] = %0d", h, continue_loop_lp4[h]);
                    }
                    //  First read the value of the DLL_CTRL20 register.
                    regdata = read_register(DLL_CTRL20_ADDR,1);
                    //  WRITE DQ SADJ F1 DS3.
                    //   regdata[27:26] = incr_wr_dq_sadj_f0_1_lp4[3];
                    bit_set_field(regdata, 2, 26, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
                        //  WRITE DQ SADJ F0 DS3.
                    //   regdata[25:24] = incr_wr_dq_sadj_f0_1_lp4[3];
                    bit_set_field(regdata, 2, 24, incr_wr_dq_sadj_f0_1_lp4[3] & 0x3);
                        //  WRITE DQ SADJ F1 DS2.
                    //   regdata[19:18] = incr_wr_dq_sadj_f0_1_lp4[2];
                    bit_set_field(regdata, 2, 18, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
                        //  WRITE DQ SADJ F0 DS2.
                    //   regdata[17:16] = incr_wr_dq_sadj_f0_1_lp4[2];
                    bit_set_field(regdata, 2, 16, incr_wr_dq_sadj_f0_1_lp4[2] & 0x3);
                        //  WRITE DQ SADJ F1 DS1.
                    //   regdata[11:10] = incr_wr_dq_sadj_f0_1_lp4[1];
                    bit_set_field(regdata, 2, 10, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
                        //  WRITE DQ SADJ F0 DS1.
                    //   regdata[9:8] = incr_wr_dq_sadj_f0_1_lp4[1];
                    bit_set_field(regdata, 2, 8, incr_wr_dq_sadj_f0_1_lp4[1] & 0x3);
                        //  WRITE DQ SADJ F1 DS0.
                    //   regdata[3:2] = incr_wr_dq_sadj_f0_1_lp4[0];
                    bit_set_field(regdata, 2, 2, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
                        //  WRITE DQ SADJ F0 DS0.
                    //   regdata[1:0] = incr_wr_dq_sadj_f0_1_lp4[0];
                    bit_set_field(regdata, 2, 0, incr_wr_dq_sadj_f0_1_lp4[0] & 0x3);
                        //  Now write the new value to the DLL_CTRL20
                        // register.

                    write_register(DLL_CTRL20_ADDR, regdata, 1);

                    //   msg = $sformatf("%s%s\n\t%s\n\t%s\n\t%s\n\t%s",
                    //   "Set WRITE DQ DLL SADJ = 0 using the DLL_CTRL ",
                    //      "registers through the DDR PHY AHB. ",
                    //      "\ta.  DLL_CTRL2 affects Data Slice 0",
                    //      "\tb.  DLL_CTRL3 affects Data Slice 1",
                    //      "\tc.  DLL_CTRL4 affects Data Slice 2",
                    //      "\td.  DLL_CTRL5 affects Data Slice 3");
                    //   `uvm_info(report_id, msg, UVM_NONE ) //UVM_MEDIUM)

                    regdata = read_register(DLL_CTRL2_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL2_ADDR, regdata, 1);

                    regdata = read_register(DLL_CTRL3_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL3_ADDR, regdata, 1);

                    regdata = read_register(DLL_CTRL4_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL4_ADDR, regdata, 1);

                    regdata = read_register(DLL_CTRL5_ADDR, 1);
                    //  WRITE DQ DLL SADJ
                    //   regdata[7:0] = 0;
                    bit_clr_bits(regdata, 8, 0);
                    write_register(DLL_CTRL5_ADDR, regdata, 1);
                }
                else
                {
                    continue_loop = 0;
                }
            } // if (found_pass_lp4 == 1'b0)
        }

        k510_logd("DLL_CTRL2 = 0x%08x \n", read_register(DLL_CTRL2_ADDR, 1));
        k510_logd("DLL_CTRL3 = 0x%08x \n", read_register(DLL_CTRL3_ADDR, 1));
        k510_logd("DLL_CTRL4 = 0x%08x \n", read_register(DLL_CTRL4_ADDR, 1));
        k510_logd("DLL_CTRL5 = 0x%08x \n", read_register(DLL_CTRL5_ADDR, 1));
        k510_logd("DLL_CTRL20 = 0x%08x \n", read_register(DLL_CTRL20_ADDR, 1));

        if(!(continue_loop_lp4[0] | continue_loop_lp4[1] | continue_loop_lp4[2] | continue_loop_lp4[3]))
        {
            continue_loop = 0;
        }
    } // while(continue_loop == 1)

    //  Verify that the LPDDR3 Write Eye Training was successful.
    if (incr_good_min_lp4[0] == 99 || incr_good_min_lp4[1] == 99 ||
        incr_good_min_lp4[2] == 99 ||incr_good_min_lp4[3] == 99 )
    {
        k510_loge("LPDDR3 Write Eye Training Loop Failed!");
        return -1;
    }

    k510_logv(
        "Step 11 of 15 for LPDDR3 Write Eye Training"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to "
        "1"
    );
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR,1);
    //  Set SADJ WRT (bit[10]) to 1.
    // regdata[10] = 1'b1;
    bit_set_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    k510_logv(
        "Step 12 of 15 for LPDDR3 Write Eye Training\n"
        "Calculate the Average SADJ value for each data slice "
        "for a passing result as the final value\n"
    );
    for(int h = 0; h < 4; h++)
    {
        if (wr_dq_sadj_f0_1_N_lp4_minus_1[h] != wr_dq_sadj_f0_1_N_lp4[h])
        {

            TotalWindowPass = MADJ - incr_good_min_lp4[h] + incr_good_max_lp4[h];
            Midpoint = TotalWindowPass / 2;  // ?! what is this?

            if ((incr_good_min_lp4[h] + Midpoint) >= MADJ) {
            incr_good_avg_lp4[h] = incr_good_min_lp4[h] + Midpoint - MADJ;
            incr_wr_dq_sadj_f0_1_lp4_avg[h] = wr_dq_sadj_f0_1_N_lp4[h];
            }

        }
        else
        {
            incr_good_avg_lp4[h] = ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2);

            avg_real_lp4[h] = ((incr_good_min_lp4[h] + incr_good_max_lp4[h])/2.0);

            k510_logd("incr_good_min_lp4[%d] == %d  0x%08X\n", h, incr_good_min_lp4[h], incr_good_min_lp4[h]);
            k510_logd("incr_good_max_lp4[%d] == %d  0x%08X\n", h, incr_good_max_lp4[h], incr_good_max_lp4[h]);
            k510_logd("incr_good_avg_lp4[%0d] = %0d, avg_real_lp4[%0d] = %3.3f\n",
                      h, incr_good_avg_lp4[h], h, avg_real_lp4[h]);

            if ((avg_real_lp4[h] - incr_good_avg_lp4[h]) >= 0.5)
            incr_good_avg_lp4[h] +=1;

            k510_logd("round incr_good_avg_lp4[%0d] = %0d, avg_real_lp4[%0d] = %3.3f\n",
            h, incr_good_avg_lp4[h], h, avg_real_lp4[h]);

            incr_wr_dq_sadj_f0_1_lp4_avg[h] = wr_dq_sadj_f0_1_N_lp4_minus_1[h];
        }
    }

    k510_logv(
        "Step 13 of 15 for LPDDR3 Write Eye Training\n"
        "Write the final result into the DDR PHY registers "
        "DLL_CTRL2,3,4,5 for WRITE DQ DLL SADJ for each "
        "data slice\n"
    );

    /* Add for because training with ODT write eye fail, but sub 8 can pass */
    // incr_good_avg_lp4[0] -= 8;
    // incr_good_avg_lp4[1] -= 8;
    // incr_good_avg_lp4[2] -= 8;
    // incr_good_avg_lp4[3] -= 8;

    regdata = read_register(DLL_CTRL2_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[0];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[0] & 0xff);
    write_register(DLL_CTRL2_ADDR, regdata, 1);

    regdata = read_register(DLL_CTRL3_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[1];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[1] & 0xff);
    write_register(DLL_CTRL3_ADDR, regdata, 1);

    regdata = read_register(DLL_CTRL4_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[2];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[2] & 0xff);
    write_register(DLL_CTRL4_ADDR, regdata, 1);

    regdata = read_register(DLL_CTRL5_ADDR, 1);
    //  WRITE DQ DLL SADJ
    // regdata[7:0] = incr_good_avg_lp4[3];
    bit_set_field(regdata, 8, 0, incr_good_avg_lp4[3] & 0xff);
    write_register(DLL_CTRL5_ADDR, regdata, 1);

    // for(int h = 0; h < 4; h++) {

    //     msg = $sformatf("%-42s",
    //         "Final:  LPDDR3 Write Eye Training Loop ");
    //     msg = {msg, "\tSADJ DLL_CTRL2,3,4,5"};
    //     msg = {msg, $sformatf("\tincr_good_min_lp4  = %3d = 0x%8h,  ",
    //         incr_good_min_lp4[h], incr_good_min_lp4[h])};
    //     msg = {msg, $sformatf("incr_good_max_lp4  = %3d = 0x%8h,  ",
    //         incr_good_max_lp4[h], incr_good_max_lp4[h])};
    //     msg = {msg, $sformatf("incr_good_avg_lp4  = %3d = 0x%8h",
    //         incr_good_avg_lp4[h], incr_good_avg_lp4[h])};
    //     `uvm_info(report_id, msg, UVM_NONE ) //UVM_MEDIUM)
    // }

    for(int h = 0; h < 4; h++) {
        k510_logd("Final:  LPDDR3 Write Eye Training Loop\n");
        k510_logd("\t\tWRITE DQ SADJ F0/1[%0d]  = %3d = 0x%08x\n",
            h, incr_wr_dq_sadj_f0_1_lp4_avg[h], incr_wr_dq_sadj_f0_1_lp4_avg[h]);
    }

    k510_logv(
        "Step 14 of 15 for LPDDR3 Write Eye Training\n"
        "Write the final result into the DDR PHY registers "
        "DLL_CTRL20 WRITE DQ \n\tDLL SADJ F0/1 DS[3:0] for each "
        "data slice\n"
    );

    //  First read the value of the DLL_CTRL20 register.
    regdata = read_register(DLL_CTRL20_ADDR, 1);
    //  WRITE DQ SADJ F1 DS3.
    // regdata[27:26] = incr_wr_dq_sadj_f0_1_lp4_avg[3];
    bit_set_field(regdata, 2, 26, incr_wr_dq_sadj_f0_1_lp4_avg[3] & 0x3);
    //  WRITE DQ SADJ F0 DS3.
    // regdata[25:24] = incr_wr_dq_sadj_f0_1_lp4_avg[3];
    bit_set_field(regdata, 2, 24, incr_wr_dq_sadj_f0_1_lp4_avg[3] & 0x3);
    //  WRITE DQ SADJ F1 DS2.
    // regdata[19:18] = incr_wr_dq_sadj_f0_1_lp4_avg[2];
    bit_set_field(regdata, 2, 18, incr_wr_dq_sadj_f0_1_lp4_avg[2] & 0x3);
    //  WRITE DQ SADJ F0 DS2.
    // regdata[17:16] = incr_wr_dq_sadj_f0_1_lp4_avg[2];
    bit_set_field(regdata, 2, 16, incr_wr_dq_sadj_f0_1_lp4_avg[2] & 0x3);
    //  WRITE DQ SADJ F1 DS1.
    // regdata[11:10] = incr_wr_dq_sadj_f0_1_lp4_avg[1];
    bit_set_field(regdata, 2, 10, incr_wr_dq_sadj_f0_1_lp4_avg[1] & 0x3);
    //  WRITE DQ SADJ F0 DS1.
    // regdata[9:8] = incr_wr_dq_sadj_f0_1_lp4_avg[1];
    bit_set_field(regdata, 2, 8, incr_wr_dq_sadj_f0_1_lp4_avg[1] & 0x3);
    //  WRITE DQ SADJ F1 DS0.
    // regdata[3:2] = incr_wr_dq_sadj_f0_1_lp4_avg[0];
    bit_set_field(regdata, 2, 2, incr_wr_dq_sadj_f0_1_lp4_avg[0] & 0x3);
    //  WRITE DQ SADJ F0 DS0.
    // regdata[1:0] = incr_wr_dq_sadj_f0_1_lp4_avg[0];
    bit_set_field(regdata, 2, 0, incr_wr_dq_sadj_f0_1_lp4_avg[0] & 0x3);
    //  Now write the new value to the DLL_CTRL20
    // register.
    write_register(DLL_CTRL20_ADDR,regdata, 1);

    k510_logv(
        "Step 15 of 15 for LPDDR3 Write Eye Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to "
        "0\n"
    );
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set SADJ WRT (bit[10]) to 0.
    // regdata[10] = 1'b0;
    bit_clr_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /* LPDDR3 Write Eye Complete */
    k510_logi("LPDDR3 Write Eye Complete\n");

    // read_dll_ctrl_registers();
    k510_logi("\nCompare DLL_CTRL After Write Eye Training\n");
    // print_pre_vs_cur_data();
    // update_pre_data();

    // cache_flush_disable();

    return 0;
}

#endif

#if 0
uint32_t Write_leveling_training(void)
{
    uint32_t regdata = 0;
    uint32_t incr_data      = 0;
    uint32_t incr_good_min  = 99;
    uint32_t incr_good_max  = 0;
    uint32_t found_pass = 0;
    uint32_t continue_loop = 1;
    uint32_t cadq_wl_value = 0;
    uint32_t lane_num = 0;
    uint32_t j,h;
    uint32_t ctrl6_value;
    uint32_t ctrl6_byte_value = 0;

    uint32_t wl_train_error0 = 0;
    uint32_t wl_train_error1 = 0;
    uint32_t wl_stop_incr = 0;
    uint32_t wl_lane_value = 0;

    k510_logd("Begin LPDDR3 Write Level Training \n");

    /* Step 1 of 20 for LPDDR3 Write Level Training
       Disable low power modes.
    */
    regdata = read_register(DENALI_CTL_190, 0);

    /*  Disable the dfi_lpi_ctrl_req signal. */
    regdata &= ~(0x1 << 8);
    regdata &= ~(0x3f);
    write_register(DENALI_CTL_190, regdata, 0);

    /* Step 2 of 20 for LPDDR3 Write Level Training.
       Issue AHB write to the DDR PHY TRAINING_CTRL3 register
       and set bit[6] = 1'b1 to enable write level FW training mode.
    */
    regdata =  read_register(TRAINING_CTRL3_ADDR, 1);
    regdata |= 0x1 << 6;
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

    /* Step 3 of 20 for LPDDR3 Write Level Training.
       Issue AHB write to the DDR PHY TRAINING_CTRL3 register
       and set bit[22] = 1'b1 to enable FRC_WL.
    */
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);
    regdata |= 0x1 << 22;
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

    /* Step 4 of 20 for LPDDR3 Write Level Training.
       Issue MR2 write setting MR2[7] = 1.  ODT must be off.
    */
   // regdata = 0x0000001e; //for 2133Mbps
#if DDR_800
    regdata = 0x00000014;   //for 800Mbps  this should be 14 not 06
#endif

#if DDR_1066
    regdata = 0x00000016; // this should be 16 not 19
#endif

#if DDR_1333
    regdata = 0x00000018;  // this should be 18 not 1c
#endif

#if DDR_1600
    regdata = 0x0000001c;  // this should be 1a not 1c
#endif

#if DDR_1866
    regdata = 0x0000001c;
#endif

#if DDR_2133
    regdata = 0x0000001e; // this should be 1e not 1c
#endif
    regdata |= 0x1 << 7;
    if(write_mode_register(2, regdata)){
        k510_logd("ERR: write_mode_register return failure, Step 1 of 4 for LPDDR3 Write Level Training \n");
        return 1;
    }

    /* Step 5 of 20 - LPDDR3 Write Level Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to 1.
    */
    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 1. */
    regdata |= 0x1 << 17;

    /* Set SADJ WRT (bit[10]) to 1. */
    regdata |= 0x1 << 10;

    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 6 of 20 for LPDDR3 Write Level Training.
       Set DLL_CTRL6 register to 0.
    */
//    regdata = read_register(DLL_CTRL6_ADDR, 1);
    regdata = 0x00000000;
    write_register(DLL_CTRL6_ADDR,regdata, 1);
    ctrl6_value = regdata;

    /* Step 7 of 20 for LPDDR3 Write Level Training.
       Set DLL_CTRL8 register to 0.
    */
//    regdata = read_register(DLL_CTRL8_ADDR, 1);
    // regdata = 0x00000000;
    // write_register(DLL_CTRL8_ADDR, regdata, 1);

    /* Step 8 of 20 for LPDDR3 Write Level Training
       Start of WRITE LEVEL Training Loop
    */

    while(continue_loop){
        /* Step 9 of 20 for LPDDR3 Write Level Training.
           Issue AHB write to the DDR PHY TRAINING_CTRL3 register
           and set bit[0] = 1'b1 to start write level training.
        */
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        regdata &= ~(0x1 << 7);
        regdata |= 0x1;
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);

        /* Step 10 of 20 for LPDDR3 Write Level Training.
           Issue AHB write to the DDR PHY TRAINING_CTRL3 register
           and set bit[7] = 1'b1 to enable write level xmit DQS.
        */
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        regdata |= 0x1 << 7;
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);

        /* Step 11 of 20 for LPDDR3 Write Level Training.
           Monitor bit[1] of TRAINING_CTRL3 register
           for completion of write level training.
        */
        while(1){
            regdata = read_register(TRAINING_CTRL3_ADDR, 1);

            if((regdata & (0xf<<24)) || (regdata & 0x2))
                break;

        }


        //mask for currently    if(regdata & 0x2)
        //mask for currently        /////mask for currently k510_logd("LPDDR3 Write Level Training completed. \n");
        //mask for currently
        if(((regdata>>2)&0xf) == 0xf)
            k510_logv("LPDDR3 Write Level Training completed for all Data Slices.\n");
        else{
            k510_loge("ERR: LPDDR3 Write Level Training was NOT completed for all Data Slices.\n");
            return 1;
        }

        if(regdata & (0xf << 24)){
            /*  Fail if a training error was detected. */
            k510_logd("WL_TRAINING_ERR = 0x%x", (regdata >> 24) | 0xf);
            k510_logd("A Write Level training error has been detected. \n");
            return 1;
        }
        //mask for currently    else
         //mask for currently        /////mask for currently k510_logd("No Write Level training errors have been detected. \n");

        /* Step 12  of 20 - LPDDR3 Write Level Training
           Read CADQ bits [24], [16], [8], [0] which
           is the DQS sampled value of the memory Clock
           X=0,1,2,3 0 = lane 0 CHA, 1 = lane 1 CHA
           2 = lane0 CHB, 3 = lane1 CHB
        */
        cadq_wl_value = read_register(CADQ_ADDR, 1);

        /* Step 13 of 20 for LPDDR3 Write Level Training.
           Clear TRAINING_CTRL3 register
           bit[0] Write Level Training Request.
        */
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        /* clear write level xmit dqs bit otherwise
           it will toggle the bit and auto clear
        */
        regdata &= ~(0x1 << 7);
        regdata &= ~(0x1);
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);

        if(read_register(TRAINING_CTRL3_ADDR, 1) & 0x1){
            k510_logd("LPDDR3 Write Level Training Request (bit[0] was NOT cleared when written to 0 over the AHB bus to exit Write Level Training. \n");
            return 1;
        }

        /* For each CADq bit [24], [16], [8], [0]
           If ctrl6 = 0 and CADq bit = 1  -- WL train error 0 for lane X
           If ctrl6 >0 & CADQ bit = 1   == stop incrementing CTRL6 value for lane X
           If ctrl6 >=0 and result == 0   increment ctrl6 for lane X
           If ctrl6 == MADJ (0x48) and result == 0 -- WL train error 1 for lnae X
        */
        lane_num = 0;

        k510_logd("incr_data = 0x%08X ========= cadq_wl_value = 0x%08x\n", incr_data, cadq_wl_value);

        for(j=0;j<32;j=j+8){

//            k510_logd("j=%d, j/8=%d, lane_num=%d \n", j, j/8, lane_num);

            switch(j)
            {
                case 0:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value & 0xff);
                       break;
                case 8:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 8) & 0xff;
                       break;
                case 16:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 16) & 0xff;
                       break;
                case 24:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 24) & 0xff;
                       break;
                default:
                        break;
            }

//            k510_logd("ctrl6_byte_value = 0x%x \n", ctrl6_byte_value);

                if(!(wl_stop_incr & (0x1 << (j/8)))){
                    if(!(wl_train_error0 & (0x1 << (j/8))) && !(wl_train_error1 & (0x1 << (j/8)))){
                        if(!ctrl6_byte_value && (cadq_wl_value & (0x1 << j))){
                            wl_stop_incr |= 0x1 << lane_num;
                            wl_train_error0 |= 0x1 << lane_num;
                        }
                        else {
                            if (ctrl6_byte_value > 0x00 && (cadq_wl_value & (0x1 << j))){
                                wl_stop_incr |= 0x1 << lane_num;
                                wl_lane_value &= ~(0xff << lane_num*8);
                                wl_lane_value |= (ctrl6_byte_value & 0xff) << (lane_num*8);
                            }
                            else {
                                 if (ctrl6_byte_value == 0x48 && !(cadq_wl_value & (0x1 << j))){
                                     wl_stop_incr |= 0x1 << lane_num;
                                     wl_train_error1 |= 0x1 << lane_num;
                                 }
                                 // otherwise ctrl6 >=0 and result == 0
                            }
                        }
                    }
                }
            lane_num++;
        }

//        k510_logd("wl_train_error0=0x%x, wl_train_error1=0x%x, wl_stop_incr=0x%x, wl_lane_value=0x%x \n", wl_train_error0, wl_train_error1, wl_stop_incr, wl_lane_value);

        /* Step 14 of 20 for LPDDR3 Write Level Training
           Continue WRITE LEVEL Training Calibration Loop by
           incrementing the values of DLL_CTRL6 WRITE LEVEL SADJ
           until SADJ = max value or all lanes trained and lane increment stopped.
           End Training Loop when max value is reached or all lanes trained.
        */
//        k510_logd("ctrl6_value=0x%x, before: incr_data=%d \n", ctrl6_value, incr_data);

        incr_data += 1;

//        k510_logd("after: incr_data=%d \n", incr_data);

        lane_num = 0;

        for(h = 0; h < 32; h= h+8){

//            k510_logd("h=%d, h/8=%d \n", h, h/8);

            switch(h)
            {
                case 0:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value & 0xff);
                       break;
                case 8:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 8) & 0xff;
                       break;
                case 16:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 16) & 0xff;
                       break;
                case 24:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 24) & 0xff;
                       break;
                default:
                        break;
            }

            if(!(wl_stop_incr & (0x1 << (h/8))))
            {
                if(!(wl_train_error0 & (0x1 << (h/8))) && !(wl_train_error1 & (0x1 << (h/8))))
                {
                    wl_lane_value &= ~(0xff << lane_num*8);
                    wl_lane_value |= (incr_data & 0xff) << (lane_num*8);
                }
            }
            else
            {
                if(ctrl6_byte_value)
                {
                    wl_lane_value &= ~((0xff) << (lane_num*8));
                    wl_lane_value |= (ctrl6_byte_value & 0xff) << (lane_num*8);
                }
                else
                {
                    wl_lane_value &= ~((0xff) << (lane_num*8));
                    wl_lane_value |= (ctrl6_byte_value & 0xff) << (lane_num*8);
                }
            }
            lane_num++;
        }

//        k510_logd("After : wl_lane_value=0x%x \n", wl_lane_value);

        regdata = wl_lane_value;

        if(incr_data > 0x48 || wl_train_error0 == 0xf || wl_train_error1 == 0xf || wl_stop_incr == 0xf){
            continue_loop = 0;
        }
        else {
            write_register(DLL_CTRL6_ADDR, regdata, 1);
            ctrl6_value = regdata;
        }

//        k510_logd("ctrl6_value=0x%x \n", ctrl6_value);

        /* Step 15 of 20 - LPDDR3 Write Level Training
           Write AHB Register TRAINING_CTRL1 SADJ_WRT and
           set to 1.
        */
        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Set CRDB (bit[17] to 1. */
        regdata |= 0x1 << 17;

        /* Set SADJ WRT (bit[10]) to 1. */
        regdata |= 0x1 << 10;

        /* Now write the new value to the TRAINING_CTRL1 register.*/
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);
    }

    if(wl_train_error0  || wl_train_error1)
    {
        k510_logd("Write Level Training  has errors and has failed! \n");
        k510_logd("wl_train_error0=%x, wl_train_error1=%x \n", wl_train_error0, wl_train_error1);
//        return 1;
    }

    /* Step 16 of 20 for LPDDR3 Write Level Training.
       Set TRAINING_CTRL1 SADJ_WRT bit[10] = 1'b1 to write to DLL regs.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata |= 0x1 << 10;
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 17 of 20 for LPDDR3 Write Level Training.
       Update DLL_CTRL6 register with CADq values.
    */
//    regdata = read_register(DLL_CTRL6_ADDR, 1);
    regdata = wl_lane_value;
    /* REN */
    // // //force
    // regdata = 0x12191113;
    // regdata = 0x13111913;
#if DDR_1866
    // regdata = 0x0D0E1814;
#endif
    /* REN */
    write_register(DLL_CTRL6_ADDR, regdata, 1);
    k510_logi(">>>>    DLL_CTRL6_ADDR = 0x%08X\n", regdata);

    /* Step 18 of 20 for LPDDR3 Write Level Training.
       Issue MR2 write setting MR2[7] = 0.
    */
    //regdata = 0x0000001e; //for 2133Mbps

#if DDR_800
      regdata = 0x6;  //for 800Mbps
#endif

#if DDR_1066
    regdata = 0x19;
#endif

#if DDR_1333
    regdata = 0x1c;
#endif

#if DDR_1600
    regdata = 0x1c;
#endif

#if DDR_1866
    regdata = 0x1c;
#endif

#if DDR_2133
    regdata = 0x1e;
#endif
    regdata &= ~(0x1 << 7);
    if(write_mode_register(2, regdata)){
        k510_logd("write_mode_register return failure, Step 18 of 20 for LPDDR3 Write Level Training \n");
        return 1;
    }

    /* Step 19 of 20 for LPDDR3 Write Level Training.
       Clear TRAINING_CTRL1 SADJ_WRT bit[10] = 1'b0 to disable write to DLL regs.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata &= ~(0x1 << 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 20 of 20 for LPDDR3 Write Level Training.
       Issue AHB write to the DDR PHY TRAINING_CTRL3 register
       to clear bit[22] to disable FRC_WL and to
       clear bit[7] to disable write level FW training mode.
    */
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);

    /* write 1 to clear write level xmit dqs bit */
    regdata |= 0x1 << 7;
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);


    k510_logi("LPDDR3 Write Level Complete \n");

    return 0;

}
#endif

#if DDR_WL_TRAINING_OLD
/*
    dfs: 0 f0,  1 f1
*/
uint32_t Write_leveling_training(uint32_t freq, uint8_t dfs)
{
    uint32_t regdata = 0;
    uint32_t incr_data      = 0;
    uint32_t incr_good_min  = 99;
    uint32_t incr_good_max  = 0;
    uint32_t found_pass = 0;
    uint32_t continue_loop = 1;
    uint32_t cadq_wl_value = 0;
    uint32_t lane_num = 0;
    uint32_t j,h;
    uint32_t ctrl6_value;
    uint32_t ctrl6_byte_value = 0;

    uint32_t wl_train_error0 = 0;
    uint32_t wl_train_error1 = 0;
    uint32_t wl_stop_incr = 0;
    uint32_t wl_lane_value = 0;

    k510_logd("Begin LPDDR3 Write Level Training \n");

    /* Step 1 of 20 for LPDDR3 Write Level Training
       Disable low power modes.
    */
    regdata = read_register(DENALI_CTL_190, 0);

    /*  Disable the dfi_lpi_ctrl_req signal. */
    regdata &= ~(0x1 << 8);
    regdata &= ~(0x3f);
    write_register(DENALI_CTL_190, regdata, 0);

    /* Step 2 of 20 for LPDDR3 Write Level Training.
       Issue AHB write to the DDR PHY TRAINING_CTRL3 register
       and set bit[6] = 1'b1 to enable write level FW training mode.
    */
    regdata =  read_register(TRAINING_CTRL3_ADDR, 1);
    regdata |= 0x1 << 6;
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

    /* Step 3 of 20 for LPDDR3 Write Level Training.
       Issue AHB write to the DDR PHY TRAINING_CTRL3 register
       and set bit[22] = 1'b1 to enable FRC_WL.
    */
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);
    regdata |= 0x1 << 22;
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

    /* Step 4 of 20 for LPDDR3 Write Level Training.
       Issue MR2 write setting MR2[7] = 1.  ODT must be off.
    */
   // regdata = 0x0000001e; //for 2133Mbps

    switch(freq)
    {
        case 800:
            regdata = 0x00000006;
        break;
        case 1066:
            regdata = 0x00000016; // this should be 16 not 19
        break;
        case 1333:
            regdata = 0x00000018;  // this should be 18 not 1c
        break;
        case 1600:
            regdata = 0x0000001c;  // this should be 1a not 1c
        break;
        case 1866:
            regdata = 0x0000001c;
        break;
        case 2133:
            regdata = 0x0000001e; // this should be 1e not 1c
        break;
        default:
            k510_loge("ERR:> Don't support freq %d\n", freq);
            return 1;
        break;
    }

    regdata |= 0x1 << 7;
    if(write_mode_register(2, regdata)){
        k510_logd("ERR: write_mode_register return failure, Step 1 of 4 for LPDDR3 Write Level Training \n");
        return 1;
    }

    /* Step 5 of 20 - LPDDR3 Write Level Training
       Write AHB Register TRAINING_CTRL1 SADJ_WRT and set to 1.
    */
    /*  First read the value of the TRAINING_CTRL1 register. */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    /*  Set CRDB (bit[17] to 1. */
    regdata |= 0x1 << 17;

    /* Set SADJ WRT (bit[10]) to 1. */
    regdata |= 0x1 << 10;

    /* Now write the new value to the TRAINING_CTRL1 register. */
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 6 of 20 for LPDDR3 Write Level Training.
       Set DLL_CTRL6 register to 0.
    */
//    regdata = read_register(DLL_CTRL6_ADDR, 1);
    regdata = 0x00000000;
    if(dfs == 0)
        write_register(DLL_CTRL6_ADDR,regdata, 1);
    else
        write_register(DLL_CTRL15_ADDR,regdata, 1);
    ctrl6_value = regdata;

    /* Step 7 of 20 for LPDDR3 Write Level Training.
       Set DLL_CTRL8 register to 0.
    */
//    regdata = read_register(DLL_CTRL8_ADDR, 1);
    // regdata = 0x00000000;
    // write_register(DLL_CTRL8_ADDR, regdata, 1);

    /* Step 8 of 20 for LPDDR3 Write Level Training
       Start of WRITE LEVEL Training Loop
    */

    while(continue_loop){
        /* Step 9 of 20 for LPDDR3 Write Level Training.
           Issue AHB write to the DDR PHY TRAINING_CTRL3 register
           and set bit[0] = 1'b1 to start write level training.
        */
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        regdata &= ~(0x1 << 7);
        regdata |= 0x1;
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);

        /* Step 10 of 20 for LPDDR3 Write Level Training.
           Issue AHB write to the DDR PHY TRAINING_CTRL3 register
           and set bit[7] = 1'b1 to enable write level xmit DQS.
        */
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        regdata |= 0x1 << 7;
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);

        /* Step 11 of 20 for LPDDR3 Write Level Training.
           Monitor bit[1] of TRAINING_CTRL3 register
           for completion of write level training.
        */
        while(1){
            regdata = read_register(TRAINING_CTRL3_ADDR, 1);

            if((regdata & (0xf<<24)) || (regdata & 0x2))
                break;

        }


        //mask for currently    if(regdata & 0x2)
        //mask for currently        /////mask for currently k510_logd("LPDDR3 Write Level Training completed. \n");
        //mask for currently
        if(((regdata>>2)&0xf) == 0xf)
            k510_logv("LPDDR3 Write Level Training completed for all Data Slices.\n");
        else{
            k510_loge("ERR: LPDDR3 Write Level Training was NOT completed for all Data Slices.\n");
            return 1;
        }

        if(regdata & (0xf << 24)){
            /*  Fail if a training error was detected. */
            k510_logd("WL_TRAINING_ERR = 0x%x", (regdata >> 24) | 0xf);
            k510_logd("A Write Level training error has been detected. \n");
            return 1;
        }
        //mask for currently    else
         //mask for currently        /////mask for currently k510_logd("No Write Level training errors have been detected. \n");

        /* Step 12  of 20 - LPDDR3 Write Level Training
           Read CADQ bits [24], [16], [8], [0] which
           is the DQS sampled value of the memory Clock
           X=0,1,2,3 0 = lane 0 CHA, 1 = lane 1 CHA
           2 = lane0 CHB, 3 = lane1 CHB
        */
        cadq_wl_value = read_register(CADQ_ADDR, 1);

        /* Step 13 of 20 for LPDDR3 Write Level Training.
           Clear TRAINING_CTRL3 register
           bit[0] Write Level Training Request.
        */
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        /* clear write level xmit dqs bit otherwise
           it will toggle the bit and auto clear
        */
        regdata &= ~(0x1 << 7);
        regdata &= ~(0x1);
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);

        if(read_register(TRAINING_CTRL3_ADDR, 1) & 0x1){
            k510_logd("LPDDR3 Write Level Training Request (bit[0] was NOT cleared when written to 0 over the AHB bus to exit Write Level Training. \n");
            return 1;
        }

        /* For each CADq bit [24], [16], [8], [0]
           If ctrl6 = 0 and CADq bit = 1  -- WL train error 0 for lane X
           If ctrl6 >0 & CADQ bit = 1   == stop incrementing CTRL6 value for lane X
           If ctrl6 >=0 and result == 0   increment ctrl6 for lane X
           If ctrl6 == MADJ (0x48) and result == 0 -- WL train error 1 for lnae X
        */
        lane_num = 0;

        k510_logd("incr_data = 0x%08X ========= cadq_wl_value = 0x%08x\n", incr_data, cadq_wl_value);

        for(j=0;j<32;j=j+8){

//            k510_logd("j=%d, j/8=%d, lane_num=%d \n", j, j/8, lane_num);

            switch(j)
            {
                case 0:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value & 0xff);
                       break;
                case 8:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 8) & 0xff;
                       break;
                case 16:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 16) & 0xff;
                       break;
                case 24:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 24) & 0xff;
                       break;
                default:
                        break;
            }

//            k510_logd("ctrl6_byte_value = 0x%x \n", ctrl6_byte_value);

                if(!(wl_stop_incr & (0x1 << (j/8)))){
                    if(!(wl_train_error0 & (0x1 << (j/8))) && !(wl_train_error1 & (0x1 << (j/8)))){
                        if(!ctrl6_byte_value && (cadq_wl_value & (0x1 << j))){
                            wl_stop_incr |= 0x1 << lane_num;
                            wl_train_error0 |= 0x1 << lane_num;
                        }
                        else {
                            if (ctrl6_byte_value > 0x00 && (cadq_wl_value & (0x1 << j))){
                                wl_stop_incr |= 0x1 << lane_num;
                                wl_lane_value &= ~(0xff << lane_num*8);
                                wl_lane_value |= (ctrl6_byte_value & 0xff) << (lane_num*8);
                            }
                            else {
                                 if (ctrl6_byte_value == 0x48 && !(cadq_wl_value & (0x1 << j))){
                                     wl_stop_incr |= 0x1 << lane_num;
                                     wl_train_error1 |= 0x1 << lane_num;
                                 }
                                 // otherwise ctrl6 >=0 and result == 0
                            }
                        }
                    }
                }
            lane_num++;
        }

//        k510_logd("wl_train_error0=0x%x, wl_train_error1=0x%x, wl_stop_incr=0x%x, wl_lane_value=0x%x \n", wl_train_error0, wl_train_error1, wl_stop_incr, wl_lane_value);

        /* Step 14 of 20 for LPDDR3 Write Level Training
           Continue WRITE LEVEL Training Calibration Loop by
           incrementing the values of DLL_CTRL6 WRITE LEVEL SADJ
           until SADJ = max value or all lanes trained and lane increment stopped.
           End Training Loop when max value is reached or all lanes trained.
        */
//        k510_logd("ctrl6_value=0x%x, before: incr_data=%d \n", ctrl6_value, incr_data);

        incr_data += 1;

//        k510_logd("after: incr_data=%d \n", incr_data);

        lane_num = 0;

        for(h = 0; h < 32; h= h+8){

//            k510_logd("h=%d, h/8=%d \n", h, h/8);

            switch(h)
            {
                case 0:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value & 0xff);
                       break;
                case 8:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 8) & 0xff;
                       break;
                case 16:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 16) & 0xff;
                       break;
                case 24:
                       ctrl6_byte_value = 0;
                       ctrl6_byte_value |= (ctrl6_value >> 24) & 0xff;
                       break;
                default:
                        break;
            }

            if(!(wl_stop_incr & (0x1 << (h/8))))
            {
                if(!(wl_train_error0 & (0x1 << (h/8))) && !(wl_train_error1 & (0x1 << (h/8))))
                {
                    wl_lane_value &= ~(0xff << lane_num*8);
                    wl_lane_value |= (incr_data & 0xff) << (lane_num*8);
                }
            }
            else
            {
                if(ctrl6_byte_value)
                {
                    wl_lane_value &= ~((0xff) << (lane_num*8));
                    wl_lane_value |= (ctrl6_byte_value & 0xff) << (lane_num*8);
                }
                else
                {
                    wl_lane_value &= ~((0xff) << (lane_num*8));
                    wl_lane_value |= (ctrl6_byte_value & 0xff) << (lane_num*8);
                }
            }
            lane_num++;
        }

//        k510_logd("After : wl_lane_value=0x%x \n", wl_lane_value);

        regdata = wl_lane_value;

        if(incr_data > 0x48 || wl_train_error0 == 0xf || wl_train_error1 == 0xf || wl_stop_incr == 0xf){
            continue_loop = 0;
        }
        else {
            if(dfs == 0)
                write_register(DLL_CTRL6_ADDR, regdata, 1);
            else
                write_register(DLL_CTRL15_ADDR, regdata, 1);
            ctrl6_value = regdata;
        }

//        k510_logd("ctrl6_value=0x%x \n", ctrl6_value);

        /* Step 15 of 20 - LPDDR3 Write Level Training
           Write AHB Register TRAINING_CTRL1 SADJ_WRT and
           set to 1.
        */
        /* First read the value of the TRAINING_CTRL1 register. */
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        /* Set CRDB (bit[17] to 1. */
        regdata |= 0x1 << 17;

        /* Set SADJ WRT (bit[10]) to 1. */
        regdata |= 0x1 << 10;

        /* Now write the new value to the TRAINING_CTRL1 register.*/
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);
    }

    if(wl_train_error0  || wl_train_error1)
    {
        k510_logd("Write Level Training  has errors and has failed! \n");
        k510_logd("wl_train_error0=%x, wl_train_error1=%x \n", wl_train_error0, wl_train_error1);
//        return 1;
    }

    /* Step 16 of 20 for LPDDR3 Write Level Training.
       Set TRAINING_CTRL1 SADJ_WRT bit[10] = 1'b1 to write to DLL regs.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata |= 0x1 << 10;
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 17 of 20 for LPDDR3 Write Level Training.
       Update DLL_CTRL6 register with CADq values.
    */
//    regdata = read_register(DLL_CTRL6_ADDR, 1);
    regdata = wl_lane_value;
    /* REN */
    // // //force
    // regdata = 0x12191113;
    // regdata = 0x13111913;
#if DDR_1866
    // regdata = 0x0D0E1814;
#endif
    /* REN */
    if(dfs == 0)
    {
        write_register(DLL_CTRL6_ADDR, regdata, 1);
        k510_logi(">>>>    DLL_CTRL6_ADDR = 0x%08X\n", regdata);
    }
    else
    {
        write_register(DLL_CTRL15_ADDR, regdata, 1);
        k510_logi(">>>>    DLL_CTRL15_ADDR = 0x%08X\n", regdata);
    }


    /* Step 18 of 20 for LPDDR3 Write Level Training.
       Issue MR2 write setting MR2[7] = 0.
    */
    //regdata = 0x0000001e; //for 2133Mbps
    switch(freq)
    {
        case 800:
            regdata = 0x00000006;
        break;
        case 1066:
            regdata = 0x19;
        break;
        case 1333:
            regdata = 0x1c;
        break;
        case 1600:
            regdata = 0x1c;
        break;
        case 1866:
            regdata = 0x1c;
        break;
        case 2133:
            regdata = 0x0000001e; // this should be 1e not 1c
        break;
        default:
            k510_loge("ERR:>  don't support freq %d\n", freq);
            return 1;
        break;
    }

    regdata &= ~(0x1 << 7);
    if(write_mode_register(2, regdata)){
        k510_logd("write_mode_register return failure, Step 18 of 20 for LPDDR3 Write Level Training \n");
        return 1;
    }

    /* Step 19 of 20 for LPDDR3 Write Level Training.
       Clear TRAINING_CTRL1 SADJ_WRT bit[10] = 1'b0 to disable write to DLL regs.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    regdata &= ~(0x1 << 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /* Step 20 of 20 for LPDDR3 Write Level Training.
       Issue AHB write to the DDR PHY TRAINING_CTRL3 register
       to clear bit[22] to disable FRC_WL and to
       clear bit[7] to disable write level FW training mode.
    */
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);

    /* write 1 to clear write level xmit dqs bit */
    regdata |= 0x1 << 7;
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);


    k510_logi("LPDDR3 Write Level Complete \n");

    return 0;

}
#endif

#if DDR_WL_TRAINING_NEW

int Write_leveling_training(void)
{
    int regdata = 0;

    // cache_enable();     //modify by zzx for enable cache to speed up

    k510_logi("Begin LPDDR3 Write Level Training\n");

   // // disable the auto-refresh commands to the DRAMs add from yangguang   //masked by hyg for auto-refresh
   // regdata = read_register(DENALI_CTL_078, 0);
   // /* set bit 0. */
   // bit_clr_bit(regdata, 0);
   // /* Now write the value back into the register. */
   // write_register(DENALI_CTL_078, regdata, 0);

    k510_logd(
        "Step 1 of 20 for LPDDR3 Write Level Training\n"
        "Disable low power modes.\n"
    );

    /* Just for watch vref settings */
    // regdata=0x10101003;
    // write_register(TRAINING_CTRL6_ADDR, regdata, 1);
    // regdata = read_register(TRAINING_CTRL6_ADDR, 1);
    // k510_logi("==========Training_ctrl6=======%08x\n",regdata);

    regdata = read_register(DENALI_CTL_190, 0);
    bit_clr_bit(regdata, 8);
    bit_clr_bits(regdata, 6, 0);
    write_register(DENALI_CTL_190, regdata, 0);

    k510_logd(
        "Step 2 of 20 for LPDDR3 Write Level Training.\n"
        "Issue AHB write to the DDR PHY TRAINING_CTRL3 register "
        "and set bit[6] = 1'b1 to enable write level FW training mode.\n"
    );
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);
    bit_set_bit(regdata, 6);
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

    k510_logd(
        "Step 3 of 20 for LPDDR3 Write Level Training.\n"
        "Issue AHB write to the DDR PHY TRAINING_CTRL3 register "
        "and set bit[22] = 1'b1 to enable FRC_WL.\n"
    );
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);
    bit_set_bit(regdata, 22);
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

    k510_logd(
        "Step 4 of 20 for LPDDR3 Write Level Training.\n"
        "Issue MR2 write setting MR2[7] = 1.  ODT must be off.\n"
    );
  //  regdata = 0x36;
  //  regdata = 0x2d;  //changed by hyg for RL[2:0]=101  WL[5:3]=101
    regdata = 0x1c;  //changed by hyg for RL[2:0]=001  WL[5:3]=001 for 800Mbps
    bit_set_bit(regdata, 7);
    write_mode_register(2, regdata);

    k510_logd(
        "Step 5 of 20 - LPDDR3 Write Level Training\n"
        "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
        "set to 1.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_set_bit(regdata, 17);
    bit_set_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logd(
        "Step 6 of 20 for LPDDR3 Write Level Training.\n"
        "Set DLL_CTRL6 register to 0.\n"
    );
  //  write_register(DLL_CTRL6_ADDR, 0, 1);
  //  write_register(DLL_CTRL6_ADDR, 9, 1);  //modify by hyg for conduct more short time in 9 Trefi
    // write_register(DLL_CTRL6_ADDR, 0, 1);  //modify by hyg for conduct more short time in 9 Trefi  @800Mbps
    write_register(DLL_CTRL6_ADDR, 0x0a0a0a0a, 1);  //modify by hyg for conduct more short time in 9 Trefi  @800Mbps

    //  ctrl6_value = 0; /* ?anything */  //modify by hyg
    ctrl6_value = 0x0a0a0a0a; /* ?anything */  //modify by hyg

    k510_logd(
        "Step 7 of 20 for LPDDR3 Write Level Training.\n"
        "Set DLL_CTRL8 register to 0.\n"
    );
    // write_register(DLL_CTRL8_ADDR, 0x080808, 1);  //modify by hyg for not update write level DLL ca slice in write leveling mode, if you want, pls update that in the CA training flow cke low status.
    // write_register(DLL_CTRL8_ADDR, 0, 1);  //modify by hyg for not update write level DLL ca slice in write leveling mode, if you want, pls update that in the CA training flow cke low status.

    k510_logd(
        "Step 8 of 20 for LPDDR3 Write Level Training\n"
        "Start of WRITE LEVEL Training Loop\n"
    );

    incr_data      = 0xa;
    incr_good_min  = 99;
    incr_good_max  = 0;
    found_pass = 0;

    wl_end[0] = 0;
    wl_end[1] = 0;
    wl_end[2] = 0;
    wl_end[3] = 0;
    wl_strt_incr[0] = 99;
    wl_strt_incr[1] = 99;
    wl_strt_incr[2] = 99;
    wl_strt_incr[3] = 99;
    wl_stop_incr[0] = 0;
    wl_stop_incr[1] = 0;
    wl_stop_incr[2] = 0;
    wl_stop_incr[3] = 0;

    continue_loop  = 1;
    while (continue_loop == 1)
    {
        k510_logd(
            "Step 9 of 20 for LPDDR3 Write Level Training.\n"
            "Issue AHB write to the DDR PHY TRAINING_CTRL3 register "
            "and set bit[0] = 1'b1 to start write level training.\n"
        );
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        //clear write level xmit dqs bit otherwise it will toggle the bit and auto clear...
        bit_clr_bit(regdata, 7);
        bit_set_bit(regdata, 0);
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);
        //PHY will drive DQS bus low and wait for
        //Write Level Xmit DQS to be written '1'

        k510_logd(
            "Step 10 of 20 for LPDDR3 Write Level Training.\n"
            "Issue AHB write to the DDR PHY TRAINING_CTRL3 register "
            "and set bit[7] = 1'b1 to enable write level xmit DQS.\n"
        );
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        bit_set_bit(regdata, 7);
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);
        //PHY will send two DQS pulses to the DRAM.
        //After tWLO the PHY will sample the DQ bus
        //dq prime bit and store it in the CADQ lsb
        //per slice.  PHY will set Write Level
        //Complete

        k510_logd(
            "Step 11 of 20 for LPDDR3 Write Level Training.\n"
            "Monitor bit[1] of TRAINING_CTRL3 register "
            "for completion of write level training.\n"
        );
        continue_training = 1;
        while (continue_training == 1)
        {
            regdata = read_register(TRAINING_CTRL3_ADDR, 1);
            if((bit_get_field(regdata, 4, 24)) || (bit_check_bit(regdata, 1)))
            {
                continue_training = 0;
            }
            else
            {
                /* Wait 1 ns for write level training. */
            }
        }

        if(bit_check_bit(regdata, 1))
        {
            k510_logd("LPDDR3 Write Level Training completed.\n");
        }

        if(bit_get_field(regdata, 4, 2) == 0xF)
        {
            k510_logv("LPDDR3 Write Level Training completed for all Data Slices.\n");
        }
        else
        {
            k510_loge("Err: LPDDR3 Write Level Training was NOT completed for all Data Slices.\n");
            return -1;
        }

        //  Fail if a training error was detected.
        if(bit_get_field(regdata, 4, 24))
        {
            k510_logi("WL_TRAINING_ERR = 0x%X, A Write Level training error has been detected.\n", bit_get_field(regdata, 4, 24));
            return -1;
        }
        else
        {
            k510_logd("WL_TRAINING_ERR = 0x%X, No Write Level training errors have been detected.\n", bit_get_field(regdata, 4, 24));
        }

        k510_logd(
            "Step 12  of 20 - LPDDR3 Write Level Training\n"
            "Read CADQ bits [24], [16], [8], [0] which "
            "is the DQS sampled value of the memory Clock "
            "X=0,1,2,3 0 = lane 0 CHA, 1 = lane 1 CHA "
            "2 = lane0 CHB, 3 = lane1 CHB\n"
        );
        regdata = read_register(CADQ_ADDR, 1);
        cadq_wl_value = regdata;

        k510_logd(
            "Step 13 of 20 for LPDDR3 Write Level Training.\n"
            "Clear TRAINING_CTRL3 register "
            "bit[0] Write Level Training Request.\n"
        );
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);
        //clear write level xmit dqs bit otherwise it will toggle the bit and auto clear...
        bit_clr_bit(regdata, 7);
        bit_clr_bit(regdata, 0);
        write_register(TRAINING_CTRL3_ADDR, regdata, 1);
        regdata = read_register(TRAINING_CTRL3_ADDR, 1);

        if(bit_check_bit(regdata, 0))
        {
            k510_logi("ERR: LPDDR3 Write Level Training Request (bit[0]\
                       was NOT cleared when written to 0 over the\
                       AHB bus to exit Write Level Training.\n");
            return -1;
        }

        lane_num = 0;

        k510_logd("incr_data = 0x%08X ========= cadq_wl_value = 0x%08x\n", incr_data, cadq_wl_value);

        for(uint32_t j = 0; j < 32; j+=8)
        {
            k510_logd("==== j = %d ====\n", j);
            k510_logd("==== lane_num = 0x%d ====\n", lane_num);
            index_msb = j+7;
            index_lsb = j;
            switch(j)
            {
                case 0:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 0);
                    break;
                }
                case 8:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 8);
                    break;
                }
                case 16:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 16);
                    break;
                }
                case 24:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 24);
                    break;
                }
            }
            k510_logd("ctrl6_byte_value= 0x%02x\n", ctrl6_byte_value);

            /* Ron 20210518 */
            // if(bit_check_bit(wl_stop_incr, j / 8) == 0)
            if(incr_data <= 0x50 /* 51 */)
            {
                if((bit_check_bit(wl_train_error0, j / 8) == 0)  && (bit_check_bit(wl_train_error1, j / 8) == 0))
                {
                    if((ctrl6_byte_value == 0) && (bit_check_bit(cadq_wl_value, j) == 1))
                    {
                        wl_strt_incr[lane_num] = incr_data;
                        wl_end[lane_num] = 0;
                        wl_train_lane[lane_num][incr_data] = 1;
                        bit_set_bit(wl_train_error0, lane_num);
                    }

                    if(ctrl6_byte_value == 0 && (bit_check_bit(cadq_wl_value, j) == 0))
                    {
			            wl_train_lane[lane_num][incr_data] = 0;
                    }
                    else
                    {
                        if((ctrl6_byte_value > 0) && (bit_check_bit(cadq_wl_value, j) == 1))
                        {
                            if(wl_strt_incr[lane_num] == 99)
                            {
                                wl_strt_incr[lane_num] = incr_data;
                                k510_logd("wl_strt_incr %d = 0x%08X\n", lane_num, wl_strt_incr[lane_num]);
                            }
                            wl_end[lane_num] = 0;
                            wl_train_lane[lane_num][incr_data] = 1;
                            wl_lane_value[lane_num] = ctrl6_byte_value;
                        }
                        if((ctrl6_byte_value > 0) && (bit_check_bit(cadq_wl_value, j) == 0))
                        {
                            if(wl_end[lane_num] == 0 && wl_strt_incr[lane_num] != 99)
                            {
                                wl_end[lane_num] =1;
                                wl_stop_incr[lane_num] = incr_data;
				                k510_logd("wl_stop_incr %d = 0x%08X\n", lane_num, wl_stop_incr[lane_num]);
                            }
				            wl_train_lane[lane_num][incr_data] = 0;
                            wl_lane_value[lane_num] = ctrl6_byte_value;
                        }
                        else
                        {
                            /* 认为最大值时cadq_wl_value必为0 */
                            // if((ctrl6_byte_value == 0x50 /* 0x33 */ /* 0x3b */ /* 0x31 */) && (bit_check_bit(cadq_wl_value, j) == 1) &&  wl_end[lane_num] == 0)
                            if((ctrl6_byte_value == 0x50 /* 0x33 */ /* 0x3b */ /* 0x31 */) && (bit_check_bit(cadq_wl_value, j) == 1))
                            {
                                wl_stop_incr[lane_num] = incr_data;
                                // bit_set_bit(wl_train_error1, lane_num);
                                // k510_logd("!!!! wl_train_error1 = 0x%02X !\n", wl_train_error1);
                            }
                        }// else: !if(ctrl6_byte_value > 8'h00 && cadq_wl_value[j] == 1'b0)
                    }// else: !if(ctrl6_byte_value == 8'h00 && cadq_wl_value[j] == 1'b0)
                }// if (wl_train_error0[j] == 0  && wl_train_error1[j] == 0)
            }// if (incr_data <= 59)
            lane_num++;
        }//for(uint32_t j = 0; j < 32; j+=8)

        k510_logi("wl_train_error0 = 0x%02x \n", wl_train_error0);
        k510_logi("wl_train_error1 = 0x%02x \n", wl_train_error1);

        for(uint32_t i = 0; i < 4; i++)
        {
            k510_logd("wl_strt_incr[%d] = 0x%08X\n", i, wl_strt_incr[i]);
            k510_logd("wl_end[%d] = 0x%02X\n", i, wl_end[i]);
            k510_logd("wl_lane_value[%d] = 0x%02X\n", i, wl_lane_value[i]);
            k510_logd("wl_stop_incr[%d] = 0x%08x \n", i, wl_stop_incr[i]);
        }

        k510_logd(
            "Step 14 of 20 for LPDDR3 Write Level Training\n"
            "Continue WRITE LEVEL Training Calibration Loop by "
            "incrementing the values of DLL_CTRL6 WRITE LEVEL SADJ "
            "until SADJ = max value or all lanes trained and lane increment stopped.\n"
            "End Training Loop when max value is reached or all lanes trained.\n"
        );
        k510_logd("ctrl6_value = 0x%08x\n", ctrl6_value);
        k510_logd("Before: incr_data = 0x%08x\n", incr_data);
        incr_data += 1;
        k510_logd("After: incr_data = 0x%x\n", incr_data);
        lane_num = 0;
        for(int h = 0; h < 32; h= h+8)
        {
            k510_logi("h = %d\t h/8 = %d\n", h, (h/8));
            switch(h)
            {
                case 0:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 0);
                    break;
                }
                case 8:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 8);
                    break;
                }
                case 16:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 16);
                    break;
                }
                case 24:
                {
                    ctrl6_byte_value = bit_get_field(ctrl6_value, 8, 24);
                    break;
                }
            }

            wl_lane_value[lane_num]  = bit_get_field(incr_data, 8, 0);
            // if(bit_check_bit(wl_stop_incr, h / 8) == 0)
            // {
            //     if((bit_check_bit(wl_train_error0, h / 8) == 0) && (bit_check_bit(wl_train_error1, h / 8) == 0))
            //         wl_lane_value[lane_num]  = bit_get_field(incr_data, 8, 0);
            // }
            // else
            // {
            //     if(bit_get_field(ctrl6_byte_value, 8, 0) != 0)
            //     {
            //         wl_lane_value[lane_num]  = bit_get_field(ctrl6_byte_value, 8, 0);
            //     }
            //     else
            //     {
            //         wl_lane_value[lane_num]  = bit_get_field(ctrl6_byte_value, 8, 0);
            //     }

            // }
            lane_num++;
        }//for(int h = 0; h < 32; h= h+8)

        for(uint32_t i = 0; i < 4; i++)
        {
            k510_logd("After: wl_lane_value[%0d] = 0x%02x\n", i, wl_lane_value[i]);
        }

        regdata = (wl_lane_value[3] << 24) | (wl_lane_value[2] << 16) | (wl_lane_value[1] << 8) | wl_lane_value[0];
        k510_logd("regdata = 0x%08x\n", regdata);
        if((incr_data > 0x50 /* 0x33 */ /* 0x3b *//* 0x31 */) || (wl_train_error0 == 0xf) || (wl_train_error1 == 0xf) || (wl_stop_incr == 0xf))
        {
            continue_loop = 0;
        }
        else
        {
            write_register(DLL_CTRL6_ADDR, regdata, 1);
            ctrl6_value = regdata;
            k510_logi(">>>>    ctrl6_value  0x%08X\n", ctrl6_value);
        }

        k510_logd("ctrl6_value = 0x%08x\n", ctrl6_value);

        k510_logd(
            "Step 15 of 20 - LPDDR3 Write Level Training\n"
            "Write AHB Register TRAINING_CTRL1 SADJ_WRT and "
            "set to 1.\n"
        );
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set CRDB (bit[17] to 1.
        bit_set_bit(regdata, 17);
        //  Set SADJ WRT (bit[10]) to 1.
        bit_set_bit(regdata, 10);
        //  Now write the new value to the TRAINING_CTRL1
        //  register.
        write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    } // while (continue_loop == 1)

    if((wl_train_error0 != 0)  || (wl_train_error1 != 0))
    {
        k510_logi("ERR: Write Level Training  has errors and has failed!\n");
        return -1;
    }

    k510_logd(
        "Step 16 of 20 for LPDDR3 Write Level Training.\n"
        "Set TRAINING_CTRL1 SADJ_WRT "
        "bit[10] = 1'b1 to write to DLL regs.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_set_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    wl_train_avg[0] = wl_strt_incr[0] + (wl_stop_incr[0] - wl_strt_incr[0] -1)/2;
    wl_train_avg[1] = wl_strt_incr[1] + (wl_stop_incr[1] - wl_strt_incr[1] -1)/2;
    wl_train_avg[2] = wl_strt_incr[2] + (wl_stop_incr[2] - wl_strt_incr[2] -1)/2;
    wl_train_avg[3] = wl_strt_incr[3] + (wl_stop_incr[3] - wl_strt_incr[3] -1)/2;

    for(uint32_t i = 0; i < 4; i++)
    {
        k510_logi("====> wl_strt_incr[%d] = 0x%08X\n", i, wl_strt_incr[i]);
        k510_logi("====> wl_stop_incr[%d] = 0x%08X\n", i, wl_stop_incr[i]);
        k510_logi("====> wl_train_avg[%d] = 0x%08X\n", i, wl_train_avg[i]);
    }

    k510_logd(
        "Step 17 of 20 for LPDDR3 Write Level Training.\n"
        "Update DLL_CTRL6 register "
        "with CADq values.\n"
    );
    regdata = read_register(DLL_CTRL6_ADDR, 1);
    bit_set_field(regdata, 8, 24,  wl_train_avg[3]);
    bit_set_field(regdata, 8, 16,  wl_train_avg[2]);
    bit_set_field(regdata, 8, 8,   wl_train_avg[1]);
    bit_set_field(regdata, 8, 0,   wl_train_avg[0]);
    write_register(DLL_CTRL6_ADDR, regdata, 1);
    k510_logi(">>>>    DLL_CTRL6_ADDR = 0x%08X\n", regdata);

    k510_logd(
        "Step 18 of 20 for LPDDR3 Write Level Training.\n"
        "Issue MR2 write setting MR2[7] = 0.\n"
    );
   // regdata = 0x0000002d;  //changed by hyg for wl /rl updated
    regdata = 0x0000001c;  //changed by hyg for wl /rl updated @800Mbps
    bit_clr_bit(regdata, 7);
    write_mode_register(2, regdata);

    k510_logd(
        "Step 19 of 20 for LPDDR3 Write Level Training.\n"
        "Clear TRAINING_CTRL1 SADJ_WRT "
        "bit[10] = 1'b0 to disable write to DLL regs.\n"
    );
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    bit_clr_bit(regdata, 10);
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    k510_logd(
        "Step 20 of 20 for LPDDR3 Write Level Training.\n"
        "Issue AHB write to the DDR PHY TRAINING_CTRL3 register "
        "to clear bit[22] to disable FRC_WL and to "
        "clear bit[7] to disable write level FW training mode.\n"
    );
    regdata = read_register(TRAINING_CTRL3_ADDR, 1);
    bit_set_bit(regdata, 7); //write 1 to clear write level xmit dqs bit
    write_register(TRAINING_CTRL3_ADDR, regdata, 1);

  //  // enable the auto-refresh commands to the DRAMs  //modify by hyg for auto refresh mask
  //  regdata = read_register(DENALI_CTL_078, 0);
  //  /* set bit 0. */
  //  bit_set_bit(regdata, 0);
  //  /* Now write the value back into the register. */
  //  write_register(DENALI_CTL_078, regdata, 0);

    k510_logi("Write Level Complete\n");

    // read_dll_ctrl_registers();
    k510_logi("\nCompare DLL_CTRL After Write Level Training\n");
    // print_pre_vs_cur_data();
    // update_pre_data();

    // cache_flush_disable();       //modify by zzx for cache disable

    dump_ddrphy_regs();

    return 0;
}

#endif

void ddr_switch_to_800(void)
{
#if 1
// #if 0
    uint32_t regdata = 0;
    uint32_t rdata;
    uint32_t wdata;
    uint32_t freq;

/*  switch to 800  */
    regdata=read_register(DENALI_CTL_181,0);
    regdata |= (0xf << 24);
    regdata |= (0xf << 16);
    regdata &= ~(0xf << 8);
    regdata |= (0x1 << 8);
    write_register(DENALI_CTL_181,regdata,0);

    /* MCTL ddr controller reg copy.Defines which frequency-dependent timing registers and mode registers to use.Default value TBD. */
    regdata=readl(MEM_CTL_CLK_CFG);
    bit_set_field(regdata, 2, 6, 1);    // down freq set to 1
    bit_set_bit(regdata,18);
    writel(regdata,MEM_CTL_CLK_CFG);

#if 1
    /* Change to 800M */
    /*******sysctl module control **********/
    rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFFFFFU);
    rdata |= 0x3f;
    rdata |= (1 << 28);
    rdata |= (1 << 29);
    rdata |= (1 << 30);
    writel(rdata, PLL3_CFG0);

    rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x20;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    rdata = readl(MEM_CTL_CLK_CFG);
    rdata |= 0x3;   //800Mhz from PLL3
    rdata |= (0x3 << 4); //1/4 division
    rdata |= (0x3 << 16);
    writel(rdata, MEM_CTL_CLK_CFG);

    // auto refresh disable
    regdata=read_register(DENALI_CTL_078,0);
    bit_clr_bits(regdata,1,0);
    //rdata[0]=0;   //disable the auto-refresh command to the SRAM at the interval TREF
    write_register(DENALI_CTL_078,regdata,0);

    // cache_enable(); //zzx 20210914

    rdata = readl(MEM_CTL_DFS_CFG);
    rdata |= (1 << 1);
    rdata &= ~(0xffff << 4);
    rdata |= (0x1fff << 4);
    rdata |= (1 << 21);
    rdata |= (1 << 23);
    writel(rdata, MEM_CTL_DFS_CFG);

    write_register(DLL_CTRL21_ADDR,0x1,1);

    while(1)
    {
        rdata = readl(DDR_BASE_ADDR+4*191);
    //     k510_logi(">>>> DENALI_CTL_191      is 0x%08X\n", rdata);
    //     k510_logi(">>>> LP_STATUS_CTRL_ADDR is 0x%08X\n", read_register(LP_STATUS_CTRL_ADDR, 1));

        if(((rdata >> 24) & 0x7f) == 0x45)
        {
            k510_logi("ddr in self refresh now\n");
            rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
            rdata |= (1 << 3);
            write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);
            break;
        }
    }
    // cache_flush_disable();  //zzx 20210914

    rdata = readl(MEM_CTL_DFS_CFG);
    rdata |= (1 << 3);
    rdata |= (1 << 24);
    writel(rdata, MEM_CTL_DFS_CFG);

    while(1)
    {
        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 2 PLL3 ready */
        // if(((rdata >> 4) & 0x3) == 0x1)
        // {
        //     k510_logi(">>>> PLL3 RESET STAT\n");
        //     rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
        //     rdata |= (1 << 3);
        //     write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);
        // }
        if(((rdata >> 4) & 0x3) == 0x2)
            break;
    }

    rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
    rdata &= ~(1 << 3);
    write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);

    // rdata = readl(MEM_CTL_DFS_CFG);
    // rdata |= 0x1;
    // rdata |= (1 << 20);
    // writel(rdata, MEM_CTL_DFS_CFG);



    //  //cfg the mctl port clk enable
    // rdata = readl(MEM_CTL_CLK_CFG);
    // rdata &= ~(0x3F << 8);
    // rdata |= (0x3F << 19);
    // writel(rdata, MEM_CTL_CLK_CFG);

    // // soft-reset and then initialization
    // wdata = 0;
    // wdata &= ~(0xF);
    // wdata &= ~(0xF << 8);
    // wdata &= ~(0x3 << 24);
    // wdata |= 0x8;
    // wdata |= (0x8 << 8);
    // wdata |= (0x3 << 24);
    // writel(wdata, MCTL_RST_TIM);

    // //conduct controller core reset
    // writel(1, MCTL_RST_CTL);

    // rdata = readl(MEM_CTL_CLK_CFG);
    // rdata |= (0x3F << 8);
    // rdata |= (0x3F << 19);
    // writel(rdata, MEM_CTL_CLK_CFG);

    // while(!(readl(MCTL_RST_CTL) & (1 << 31)));

#endif


    // regdata=readl(MEM_CTL_DFS_CFG);
    // bit_set_field(regdata, 1, 1, 1);
    // bit_set_field(regdata, 1, 21, 1);
    // writel(regdata,MEM_CTL_DFS_CFG);

    // write_register(DLL_CTRL21_ADDR,0X0,1);


    while(1) {
        regdata = readl(INT2_RAW);
        if(1 == bit_get_field(regdata,1,7)) {
            k510_logi("ERR: <<<<<<<<< to 800Mbps dfs fail!<<<<<<<<<<\n");
            break;
        }
        if(1 == bit_get_field(regdata,1,6)) {
            k510_logi("3: <<<<<<<<< to 800Mbps dfs success<<<<<<<<<<!\n");
            break;
        }
    }

    regdata = readl(INT2_RAW);
    bit_set_field(regdata,2,7,3);
    writel(regdata,INT2_RAW);

    regdata = read_register(DENALI_CTL_078,0);
    bit_set_bit(regdata,0);
    write_register(DENALI_CTL_078,regdata,0);

    freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_DDR_CONTROLLER_CORE);
    k510_logi("Memctl freq is %d HZ, %lf Mbps\n", freq, freq * 4.0 / 1000000);

    // ddr_update_regs_data();

/*  end  */
#endif
}

#if 0
void ddr_switch_to_2133(void)
{
#if 1
// #if 0
    uint32_t regdata = 0;
    uint32_t rdata;
    uint32_t wdata;
    uint32_t freq;

/*  switch to 2133  */
    rdata = readl(MEM_CTL_DFS_CFG);
    rdata &= ~(1 << 1);
    rdata |= (1 << 21);
    writel(rdata, MEM_CTL_DFS_CFG);

    // auto refresh disable
    regdata=read_register(DENALI_CTL_078,0);
    bit_clr_bits(regdata,1,0);
    //rdata[0]=0;   //disable the auto-refresh command to the SRAM at the interval TREF
    write_register(DENALI_CTL_078,regdata,0);

    regdata=read_register(DENALI_CTL_181,0);
    regdata |= (0xf << 24);
    regdata |= (0xf << 16);
    regdata &= ~(0xf << 8);
    regdata |= (0x1 << 8);
    write_register(DENALI_CTL_181,regdata,0);

    /* MCTL ddr controller reg copy.Defines which frequency-dependent timing registers and mode registers to use.Default value TBD. */
    regdata=readl(MEM_CTL_CLK_CFG);
    bit_set_field(regdata, 2, 6, 0);    // up freq set to 0
    bit_set_bit(regdata,18);
    writel(regdata,MEM_CTL_CLK_CFG);

#if 1
    // /* Change to 2133M */
    rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFU);
    rdata |= 0x7f;
    rdata |= (1 << 28);
    writel(rdata, PLL3_CFG0);

    rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x3f;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    rdata = 0;
    rdata |= 0x2;   //2133Mhz from PLL3
    rdata |= (0x1 << 4); //1/2 division
    rdata |= (0x3 << 16);
    writel(rdata, MEM_CTL_CLK_CFG);

    cache_enable();

    rdata = readl(MEM_CTL_DFS_CFG);
    rdata |= (1 << 1);
    rdata &= ~(0xffff << 4);
    rdata |= (0x1fff << 4);
    rdata |= (1 << 21);
    rdata |= (1 << 23);
    writel(rdata, MEM_CTL_DFS_CFG);

    write_register(DLL_CTRL21_ADDR,0x0,1);

    while(1)
    {
        rdata = readl(DDR_BASE_ADDR+4*191);
    //     k510_logi(">>>> DENALI_CTL_191      is 0x%08X\n", rdata);
    //     k510_logi(">>>> LP_STATUS_CTRL_ADDR is 0x%08X\n", read_register(LP_STATUS_CTRL_ADDR, 1));

        if(((rdata >> 24) & 0x7f) == 0x45)
        {
            k510_logi("ddr in self refresh now\n");
            rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
            rdata |= (1 << 3);
            write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);
            break;
        }
    }
    cache_flush_disable();

    rdata = readl(MEM_CTL_DFS_CFG);
    rdata |= (1 << 3);
    rdata |= (1 << 24);
    writel(rdata, MEM_CTL_DFS_CFG);

    while(1)
    {
        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 2 PLL3 ready */
        // if(((rdata >> 4) & 0x3) == 0x1)
        // {
        //     k510_logi(">>>> PLL3 RESET STAT\n");
        //     rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
        //     rdata |= (1 << 3);
        //     write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);
        // }
        if(((rdata >> 4) & 0x3) == 0x2)
            break;
    }

    rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
    rdata &= ~(1 << 3);
    write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);

    // rdata = readl(MEM_CTL_DFS_CFG);
    // rdata |= 0x1;
    // rdata |= (1 << 20);
    // writel(rdata, MEM_CTL_DFS_CFG);



    //  //cfg the mctl port clk enable
    // rdata = readl(MEM_CTL_CLK_CFG);
    // rdata &= ~(0x3F << 8);
    // rdata |= (0x3F << 19);
    // writel(rdata, MEM_CTL_CLK_CFG);

    // // soft-reset and then initialization
    // wdata = 0;
    // wdata &= ~(0xF);
    // wdata &= ~(0xF << 8);
    // wdata &= ~(0x3 << 24);
    // wdata |= 0x8;
    // wdata |= (0x8 << 8);
    // wdata |= (0x3 << 24);
    // writel(wdata, MCTL_RST_TIM);

    // //conduct controller core reset
    // writel(1, MCTL_RST_CTL);

    // rdata = readl(MEM_CTL_CLK_CFG);
    // rdata |= (0x3F << 8);
    // rdata |= (0x3F << 19);
    // writel(rdata, MEM_CTL_CLK_CFG);

    // while(!(readl(MCTL_RST_CTL) & (1 << 31)));

#endif


    // regdata=readl(MEM_CTL_DFS_CFG);
    // bit_set_field(regdata, 1, 1, 1);
    // bit_set_field(regdata, 1, 21, 1);
    // writel(regdata,MEM_CTL_DFS_CFG);

    // write_register(DLL_CTRL21_ADDR,0X0,1);


    while(1) {
        regdata = readl(INT2_RAW);
        if(1 == bit_get_field(regdata,1,7)) {
            k510_logci("ERR: <<<<<<<<< 800Mbps to 2133Mbps dfs fail!<<<<<<<<<<\n");
            break;
        }
        if(1 == bit_get_field(regdata,1,6)) {
            k510_logci("3: <<<<<<<<< 800Mbps to 2133Mbps dfs success<<<<<<<<<<!\n");
            break;
        }
    }

    regdata = readl(INT2_RAW);
    bit_set_field(regdata,2,7,3);
    writel(regdata,INT2_RAW);

    regdata = read_register(DENALI_CTL_078,0);
    bit_set_bit(regdata,0);
    write_register(DENALI_CTL_078,regdata,0);

    freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_DDR_CONTROLLER_CORE);
    k510_logi("Memctl freq is %d HZ, %lf Mbps\n", freq, freq * 4.0 / 1000000);

    ddr_update_regs_data();

/*  end  */
#endif
}
#endif

void ddr_switch_to_high_freq(void)
{
#if 1
// #if 0
    uint32_t regdata = 0;
    uint32_t rdata;
    uint32_t wdata;
    uint32_t freq;

/*  switch to 2133  */
    rdata = readl(MEM_CTL_DFS_CFG);
    rdata &= ~(1 << 1);
    rdata |= (1 << 21);
    writel(rdata, MEM_CTL_DFS_CFG);

    // auto refresh disable
    regdata=read_register(DENALI_CTL_078,0);
    bit_clr_bits(regdata,1,0);
    //rdata[0]=0;   //disable the auto-refresh command to the SRAM at the interval TREF
    write_register(DENALI_CTL_078,regdata,0);

    regdata=read_register(DENALI_CTL_181,0);
    regdata |= (0xf << 24);
    regdata |= (0xf << 16);
    regdata &= ~(0xf << 8);
    regdata |= (0x1 << 8);
    write_register(DENALI_CTL_181,regdata,0);

    /* MCTL ddr controller reg copy.Defines which frequency-dependent timing registers and mode registers to use.Default value TBD. */
    regdata=readl(MEM_CTL_CLK_CFG);
    bit_set_field(regdata, 2, 6, 0);    // up freq set to 0
    bit_set_bit(regdata,18);
    writel(regdata,MEM_CTL_CLK_CFG);

#if DDR_1600
    /* Change to 1600M */
    rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFU);
    rdata |= 0x7f;
    rdata |= (1 << 28);
    writel(rdata, PLL3_CFG0);

    rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x3f;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    rdata = 0;
    rdata |= 0x3;
    rdata |= (0x3 << 4);
    rdata |= (0x3 << 16);
    writel(rdata, MEM_CTL_CLK_CFG);
#endif

#if DDR_1866

    rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFFFFFU);
    rdata |= 0x4A;      // real 1875
    rdata |= (1 << 28);
    writel(rdata, PLL3_CFG0);

    rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x14;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    rdata = 0;
    rdata |= 0x3;   //1866 Mhz from PLL3
    rdata |= (0x1 << 4); //1/2 division
    rdata |= (0x3 << 16);
    writel(rdata, MEM_CTL_CLK_CFG);
#endif

#if DDR_2133
    /* Change to 2133M */
    rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFU);
    rdata |= 0x7f;
    rdata |= (1 << 28);
    writel(rdata, PLL3_CFG0);

    rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x3f;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    rdata = 0;
    rdata |= 0x2;   //2133Mhz from PLL3
    rdata |= (0x1 << 4); //1/2 division
    rdata |= (0x3 << 16);
    writel(rdata, MEM_CTL_CLK_CFG);
#endif

    // cache_enable();  // zzx 20210914

    rdata = readl(MEM_CTL_DFS_CFG);
    rdata |= (1 << 1);
    rdata &= ~(0xffff << 4);
    rdata |= (0x1fff << 4);
    rdata |= (1 << 21);
    rdata |= (1 << 23);
    writel(rdata, MEM_CTL_DFS_CFG);

    write_register(DLL_CTRL21_ADDR,0x0,1);

    while(1)
    {
        rdata = readl(DDR_BASE_ADDR+4*191);
    //     k510_logi(">>>> DENALI_CTL_191      is 0x%08X\n", rdata);
    //     k510_logi(">>>> LP_STATUS_CTRL_ADDR is 0x%08X\n", read_register(LP_STATUS_CTRL_ADDR, 1));

        if(((rdata >> 24) & 0x7f) == 0x45)
        {
            k510_logi("ddr in self refresh now\n");
            rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
            rdata |= (1 << 3);
            write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);
            break;
        }
    }
    // cache_flush_disable();  //zzx 20210914

    rdata = readl(MEM_CTL_DFS_CFG);
    rdata |= (1 << 3);
    rdata |= (1 << 24);
    writel(rdata, MEM_CTL_DFS_CFG);

    while(1)
    {
        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 2 PLL3 ready */
        // if(((rdata >> 4) & 0x3) == 0x1)
        // {
        //     k510_logi(">>>> PLL3 RESET STAT\n");
        //     rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
        //     rdata |= (1 << 3);
        //     write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);
        // }
        if(((rdata >> 4) & 0x3) == 0x2)
            break;
    }

    rdata = read_register(PLL_DLL_CTRL1_ADDR, 1);
    rdata &= ~(1 << 3);
    write_register(PLL_DLL_CTRL1_ADDR, rdata, 1);

    while(1) {
        regdata = readl(INT2_RAW);
        if(1 == bit_get_field(regdata,1,7)) {
            k510_logi("ERR: <<<<<<<<< 800Mbps to high dfs fail!<<<<<<<<<<\n");
            break;
        }
        if(1 == bit_get_field(regdata,1,6)) {
            k510_logi("3: <<<<<<<<< 800Mbps to high dfs success<<<<<<<<<<!\n");
            break;
        }
    }

    regdata = readl(INT2_RAW);
    bit_set_field(regdata,2,7,3);
    writel(regdata,INT2_RAW);

    regdata = read_register(DENALI_CTL_078,0);
    bit_set_bit(regdata,0);
    write_register(DENALI_CTL_078,regdata,0);

    freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_DDR_CONTROLLER_CORE);
    k510_logi("Memctl freq is %d HZ, %lf Mbps\n", freq, freq * 4.0 / 1000000);

    // ddr_update_regs_data();

/*  end  */
#endif
}

// void ddr_write_pattern(void)
// {
//     for(uint32_t i = 0; i < sizeof(pattern)/sizeof(uint32_t); i++)
//     {
//         writel(pattern[i], i * 4);      /* Write pattern to 0 - 96 */
//     }
// }

void ddr_write_pattern(void)
{
    for(uint32_t i = 0; i < sizeof(pattern)/sizeof(uint32_t); i++)
    {
        *(mem_addr + i) = pattern[i];      /* Write pattern to 0 - 96 */
    }
}

uint32_t ddr_training_task(void)
{
    // ddr_init_regs_data();

#if DDR_CA_TRAINING
    if(CA_training()){
        /////mask for currently k510_logd("Training task failure: CA_training \n");
        return 1;
    }
    // ddr_update_regs_data();
#endif

    // start = read_cycle();
#if DDR_WL_TRAINING
    if(Write_leveling_training(freq_f0, 0)){ // 2133 F0
        /////mask for currently k510_logd("Training task failure: Write_leveling_training \n");
        return 1;
    }
    // ddr_update_regs_data();
#endif

#if (DDR_1600 || DDR_1866 || DDR_2133)
    /* change to 800 */
    ddr_switch_to_800();

    if(Write_leveling_training(800, 1)){ // 800 F1
        /////mask for currently k510_logd("Training task failure: Write_leveling_training \n");
        return 1;
    }
#endif

    /* Write pattern */
    ddr_write_pattern();

#if (DDR_1600 || DDR_1866 || DDR_2133)
    /* change to high freq */
    ddr_switch_to_high_freq();
#endif

#if DDR_RG_TRAINING
    if(Read_Gate_training()){
        /////mask for currently k510_logd("Training task failure: Gate_training \n");
        return 1;
    }
    // ddr_update_regs_data();
#endif

#if DDR_RE_TRAINING
    if(Read_eye_training()){
        /////mask for currently k510_logd("Training task failure: Read_eye_training \n");
        return 1;
    }
    // ddr_update_regs_data();
#endif

#if DDR_WE_TRAINING
    if(Write_eye_training()){
        /////mask for currently k510_logd("Training task failure: Write_eye_training \n");
        return 1;
    }
    // ddr_update_regs_data();
#endif

    dump_ddrphy_regs();

    lpddr3_probe_desity();

    k510_logi("Lpddr3 all training complete ! \n");
    return 0;
}
