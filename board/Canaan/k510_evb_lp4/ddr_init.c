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
#include <linux/io.h>
#include "ddr_param.h"
#include "ddr_regs.h"
#include "ddr_init.h"

#define DEBUG


uint32_t * mem_addr = 0x00000000;
#define MEM_BYTE_CNT     (256)
uint32_t mem_wdata[MEM_BYTE_CNT / 4] = {0x0, 0x0, 0x0, 0x0};
uint32_t mem_rdata[MEM_BYTE_CNT / 4] = {0x0, 0x0, 0x0, 0x0};
int read_dqs_sadj;
int read_dqs_b_sadj;
int MAX_READ_DQS_B_SADJ = 49;
int MAX_READ_DQS_SADJ = 49;
int    val_rb_0_p0;
int    val_rb_0_p1;
int    val_rb_0_p2;
int    val_rb_0_p3;
int    val_rb_1_p0;
int    val_rb_1_p1;
int    val_rb_1_p2;
int    val_rb_1_p3;

int    incr_data;
int    incr_good_avg;
int    incr_good_min;
int    incr_good_max;
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

int         found_pass;

uint8_t     wl_train_error0;
uint8_t     wl_train_error1;
uint8_t     wl_stop_incr;
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

static uint32_t read_register(uint32_t reg_off, uint32_t is_dfi_reg)
{
    uint32_t *reg_addr;

    if(is_dfi_reg)
        reg_addr = (uint32_t *)((uint64_t)(DDR_BASE_ADDR + DDR_PHY_REGS_OFF + reg_off));
    else
        reg_addr = (uint32_t *)((uint64_t)(DDR_BASE_ADDR + reg_off * 4));

    return *reg_addr;
}

static uint32_t write_register(uint32_t reg_off, uint32_t value, uint32_t is_dfi_reg)
{
    uint32_t *reg_addr;

    if(is_dfi_reg)
        reg_addr = (uint32_t *)((uint64_t)(DDR_BASE_ADDR + DDR_PHY_REGS_OFF + reg_off));
    else
        reg_addr = (uint32_t *)((uint64_t)(DDR_BASE_ADDR + reg_off*4));

    reg_addr[0] = value;

    return 0;
}

static int Read_Gate_training(void)
{
    int regdata = 0;
    // uint64_t value = 0;

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
    double rg_train_ds_cntr[4][32];

    int    detc_cntr0c;
    int    detc_cntr1c;
    int    detc_cntr2c;
    int    detc_cntr3c;

    debug("Begin LPDDR4 Read Gate Training\n");
//#ifndef CHIP_GLS_RTL
//    /* Write DENALI_CTL_661 RDLAT_ADJ_F1 */
//    regdata = read_register(661, 0);
//    bit_set_field(regdata, 8, 8, 0xe);
//    bit_set_field(regdata, 8, 0, 0x24); // 1025
//    write(661, regdata, 0);
//
//    // why two times?
//    regdata = read_register(661, 0);
//    bit_set_field(regdata, 8, 8, 0xe);
//    bit_set_field(regdata, 8, 0, 0x24); // 1025
//    write(661, regdata, 0);
//
//    regdata = read_register(661, 0);
//#endif
    mem_addr = (uint32_t *)0;

    /* What's this ? zzx */
    // `ifndef DFI_AGENT
    //                   mem_addr  = 32'h00000000;
    //                   //  Turn off axi_scoreboard compares for the Read Gate
    //                   //  Training reads.
    //                   p_sequencer.m_axi_scoreboard.set_compare(1'b0);
    // `else
    //                   //Turn dfi_scoreboard off for the  read gate training reads
    //                   p_sequencer.dfi_sb.set_compare(1'b0);

    //                   `uvm_create_on(act4_wrapper_seq, p_sequencer.dfi_sequencer);
    //                   act4_wrapper_seq.addr_s = 20'h00001;
    //                   `uvm_send(act4_wrapper_seq);
    // `endif

    /*
        Step 0a of 5 for LPDDR4 Read Gate Training
        To initiate read gate training, write 1 to to
        Read Gate Training Request (bit [0]) of the
        TRAINING_CTRL1 registers.  Also set DS_FRC_RG to 0 so
        as to not use Read Gate Delay Configuration Registers "
        Read Gate Delay, but instead use Internal Training
        Registers to set Read Gate Delay.
    */

    regdata = read_register(DSX8_IO_CTRL_ADDR, 1);
    bit_set_bit(regdata, 7);
    write_register(DSX8_IO_CTRL_ADDR, regdata, 1);


    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set Read Gate Training Request (bit[0]) to 1.
    bit_set_bit(regdata, 0);
    //  Set Read Gate Auto Training Enable (bit[8]) to = 0.
    bit_clr_bit(regdata, 8);
    //  Set DS_FRC_RG (bit[9]) to = 1.
    bit_set_bit(regdata, 9);
    bit_set_bit(regdata, 10);
    //  Now write the new value to the TRAINING_CTRL1 register to
    //  start read gate training.
    write_register(TRAINING_CTRL1_ADDR, regdata, 1);

    /*
        "Step x of y for LPDDR4 Read Gate Training ",
        "w/o Bit Deskew or VREF Training",
        "Set extend read gate bits."
    */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);

    // Adjust Read gate deassertion.
    regdata &= ~(0x3 << 28);
    regdata &= ~(0x3 << 20);
    regdata &= ~(0x3 << 12);
    regdata &= ~(0x3 << 4);

    //  Adjust start of Read Gate assertion.
    regdata &= ~(0xf << 24);
    regdata &= ~(0xf << 16);
    regdata &= ~(0xf << 8);
    regdata &= ~(0xf << 0);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    //  Loop until Read Gate Training Complete bit (bit 1) in the
    //  TRAINING_CTRL1 register is set or a Read Gate Training
    //  error status bit (bits [27:24]) is set.

        // threshpass = 12;
        // threshpassa = 13.5;

        threshpass = 15;
        threshpassa = 16.5;

      //  threshpass = 11;
      //  threshpassa = 12.5;

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

        /* Set RG_DLY = 0 */
        regdata = read_register(RGDLY_ADDR, 1);
        //  Set the value Read Gate assertion
        regdata = 0;

        regdata |= (incr_data & 0xff) << 24;   // Default = 4'h0.
        regdata |= (incr_data & 0xff) << 16;   // Default = 4'h0.
        regdata |= (incr_data & 0xff) << 8;    // Default = 4'h0.
        regdata |= (incr_data & 0xff) << 0;    // Default = 4'h0.
        write_register(RGDLY_ADDR, regdata, 1);

    /*
        Step 0b of 5 for LPDDR4 Read Gate Training
        Read address location 0 of the DRAM in a continuous
        loop until the PHY signals successful completion of
        Read Gate Training.
    */

    continue_training = 1;
    // uint32_t cnt = 0;
    while (continue_training == 1)
    {
        /*
            Step 1 of 5 for LPDDR4 Read Gate Training
            Using AXI read address location = 0.
        */
#ifndef DFI_AGENT
        // memory_read(mem_addr, mem_rdata, 1'b0);
        // memcpy((void *)mem_rdata, mem_addr, MEM_BYTE_CNT);
        mem_rdata[0] = *(mem_addr);
      //  mem_rdata[1] = *(mem_addr + 1);
      //  mem_rdata[2] = *(mem_addr + 2);
      //  mem_rdata[3] = *(mem_addr + 3);
#else
        /* What's this ? zzx */
/*         `uvm_create_on(rd4_s, p_sequencer.dfi_sequencer)
        assert(rd4_s.randomize());
        rd4_s.addr_s = 0;
        rd4_s.bank = 0;
        rd4_s.lp4_ap = 0;
        rd4_s.lp4_otf_bl = 1;
        //$display("svt_dfi_wr_read_basic_wrapper_seq::READ Sending the read sequence %0p", rd4_s);
        `uvm_send(rd4_s);

        //Wait between reads
        #100ns; */
#endif
        //  Read the value of the RDQS_DETC_CNTR register.
        #define RDQS_DETC_CNTR_ADDR  0x118
        regdata = read_register(RDQS_DETC_CNTR_ADDR, 1);

        detc_cntr0c = bit_get_field(regdata, 5, 0);
        detc_cntr1c = bit_get_field(regdata, 5, 8);
        detc_cntr2c = bit_get_field(regdata, 5, 16);
        detc_cntr3c = bit_get_field(regdata, 5, 24);

        rg_train_ds_cntr[0][incr_data] = detc_cntr0c;
        rg_train_ds_cntr[1][incr_data] = detc_cntr1c;
        rg_train_ds_cntr[2][incr_data] = detc_cntr2c;
        rg_train_ds_cntr[3][incr_data] = detc_cntr3c;
        /*
            Step 2 of 5 for LPDDR4 Read Gate Training
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
                    avgw0 = (rg_train_ds_cntr[0][incr_data] + rg_train_ds_cntr[0][incr_data-1] + rg_train_ds_cntr[0][incr_data-2] + rg_train_ds_cntr[0][incr_data-3] + rg_train_ds_cntr[0][incr_data-4])/5.0;
                }
            }
            else if(pass0 < 2)
            {
                pass0 = 0;
			    detc0 = 0;
            }

            if(bit_check_bit(regdata, 25) == 0)
            {
                pass1 = pass1 + 1;
			    detc1 = detc1 + detc_cntr1c;
			    avg1 = ((double)detc1)/((double)pass1);
                if(pass1 >=5 )
                {
                    avgw1 = (rg_train_ds_cntr[1][incr_data] + rg_train_ds_cntr[1][incr_data-1] + rg_train_ds_cntr[1][incr_data-2] + rg_train_ds_cntr[1][incr_data-3] + rg_train_ds_cntr[1][incr_data-4])/5.0;
                }
            }
            else if(pass1 < 2)
            {
			    pass1 = 0;
			    detc1 = 0;
            }

            if(bit_check_bit(regdata, 26) == 0)
            {
                pass2 = pass2 + 1;
			    detc2 = detc2 + detc_cntr2c;
			    avg2 = ((double)detc2)/((double)pass2);
                if(pass2 >= 5)
                {
                    avgw2 = (rg_train_ds_cntr[2][incr_data] + rg_train_ds_cntr[2][incr_data-1] + rg_train_ds_cntr[2][incr_data-2] + rg_train_ds_cntr[2][incr_data-3] + rg_train_ds_cntr[2][incr_data-4])/5.0;
                }
            }
            else if(pass2 < 2)
            {
                pass2 = 0;
                detc2 = 0;
            }

            if(bit_check_bit(regdata, 27) == 0)
            {
                pass3 = pass3 + 1;
                detc3 = detc3 + detc_cntr3c;
                avg3 = ((double)detc3)/((double)pass3);
                if(pass3 >= 5)
                {
                    avgw3 = (rg_train_ds_cntr[3][incr_data] + rg_train_ds_cntr[3][incr_data-1] + rg_train_ds_cntr[3][incr_data-2] + rg_train_ds_cntr[3][incr_data-3] + rg_train_ds_cntr[3][incr_data-4])/5.0;
                }
            }
            else if(pass3 < 2)
            {
                pass3 = 0;
                detc3 = 0;
            }

            if( (incr_data < 31) )
            {
                 continue_training = 1;
                //  Read the value of the RDQS_DETC_CNTR register.
                regdata = read_register(RDQS_DETC_CNTR_ADDR, 1);
                if((pass0 >= 5) && (bit_get_field(regdata, 5, 0) >= threshpass) && (avgw0 <= threshpassa) && (finalpass0 == 0))
                {
                    detc_cntr0 = 13;
                    rg_dly0 = incr_data;
                    finalpass0 = 1;
                }

                if((pass1 >= 5) && (bit_get_field(regdata, 5, 8) >= threshpass) && (avgw1 <= threshpassa) && (finalpass1 == 0))
                {
                    detc_cntr1 = 13;
			        rg_dly1 = incr_data;
			        finalpass1=1;
                }

                if((pass2 >= 5) && (bit_get_field(regdata, 5, 16) >= threshpass) && (avgw2 <= threshpassa) && (finalpass2 == 0))
                {
                    detc_cntr2 = 13;
                    rg_dly2 = incr_data;
                    finalpass2=1;
                }

                if((pass3 >= 5) && (bit_get_field(regdata, 5, 24) >= threshpass) && (avgw3 <= threshpassa) && (finalpass3 == 0))
                {
                    detc_cntr3 = 13;
                    rg_dly3 = incr_data;
                    finalpass3=1;
                }

                if((finalpass0 == 1) && (finalpass1 == 1) && (finalpass2 == 1) && (finalpass3 == 1))
                {
			        continue_training = 0;
			    }

                incr_data += 1;

                debug("incr_data==%0d  \n",incr_data);
                //add by hyg for check incr_data
                regdata = read_register(RGDLY_ADDR, 1);
            //  Set the value Read Gate assertion

                regdata = 0;
                regdata |= (incr_data & 0xff) << 24;
                regdata |= (incr_data & 0xff) << 16;
                regdata |= (incr_data & 0xff) << 8;
                regdata |= (incr_data & 0xff) << 0;
                write_register(RGDLY_ADDR, regdata, 1);

                regdata = read_register(TRAINING_CTRL1_ADDR, 1);
                debug(">>>> TRAINING CTL 1  ==  0x%08X\n", regdata);




            } // if ( (incr_data < 20) )
            else
            {
                continue_training = 0;
            } // else: !if( (incr_data < 20) )

        } // if ((regdata[1] == 1'b1) && (regdata[5:2] !== 4'b0000))
        else if( (incr_data < 31) )
        {
			continue_training = 1;
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
        }
        else if( (incr_data = 31) )
        {
            continue_training = 0;
        }
#if 0   // yangguang add?
        if(bit_check_bit(regdata, 1))
        {
            continue_training = 0;
        }
        else if((bit_get_field(regdata, 4, 24)))    // modify from yangguang
        {
            regdata = read_register(661, 0);
            regdata = (regdata & (~0xFF)) | ((regdata + 1) & 0xFF);
            write_register(661, regdata, 0);
            cnt++;
            if(cnt > 1000)
            {
                debug("ERR: TRAINING_CTRL1_ADDR bits (bits 27:24) are not 0.\n");
                return -1;
            }
        }
#endif
        // if(bit_check_bit(regdata, 1) || (bit_get_field(regdata, 4, 24)))
        // {
        //     continue_training = 0;
        //     /*
        //         Step 3 of 5 for LPDDR4 Read Gate Training
        //         } Read Gate Training Calibration Loop.
        //     */
        // }
    } // while (continue_training == 1)

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
        "Step 1 of 5 for LPDDR4 Read Gate Training",
        "Using AXI read address location = 0."
    */
#ifndef DFI_AGENT
    mem_rdata[0] = *(mem_addr);
   // mem_rdata[1] = *(mem_addr + 1);
   // mem_rdata[2] = *(mem_addr + 2);
   // mem_rdata[3] = *(mem_addr + 3);
#else

#endif

    /*
        Step 4 of 5 for LPDDR4 Read Gate Training
        After } of last MRR read burst wait until tWR +
        TRPpb is satisfied.
    */
    // #100ns
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    //  Verfity that all of the Individual Read Gate Training
    //  Completed per Data Slice bits are 1.
    if(bit_get_field(regdata, 4, 2) != 0xF)     /* 杩欓噷鏈夐棶棰樺惂锛宺egdata 鍝潵鐨勶紵zzx */
    {
        debug("ERR: All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are not 1.\n");
        return -1;
    }
    else
    {
        debug("All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are correctly set.\n");
    }

    //  Verify that the Read Gate Training error status
    //  bits (bits 27:24) are 0.
    if(bit_get_field(regdata, 4, 24))
    {
        debug("ERR: Some of the Read Gate Training error status bits (bit 27:24) are 1.\n");
        return -1;
    }
    else
    {
        debug("None of the Read Gate Training error status its (bit 27:24) are set.\n");
    }

    /*
        Step 4b of 5 for LPDDR4 Read Gate Training
        To exit read gate training, write 0 to to
        (bit[0] & bit[9]) and 1 to bit[8] set auto read gate training mode
        TRAINING_CTRL1 registers.
    */
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Clear the Read Gate Training Request bit (bit[0]).
    bit_clr_bit(regdata, 0);
    //  Set the Read Gate Auto Training bit (bit[8]).
    bit_set_bit(regdata, 8);
    //  Set ds_frc_rg = 0.
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
        Step 5 of 5 for LPDDR4 Read Gate Training
        Continue with regular DRAM commands.
    */
    debug("LPDDR4 Read Gate Training Complete\n");

    return 0;
}

int ddr_init(void)
{
    volatile uint32_t regdata = 0;
    volatile uint32_t rdata =0;
    volatile uint32_t wdata = 0;
    /* PLL3 poweroff */

    writel(0x01000001, PLL3_CTL);
    while(1)
    {
        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 0 PLL3 poweroff */
        if(((rdata >> 4) & 0x3) == 0)
            break;
    }

    /*******sysctl module control **********/

    // rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata = 0;//= readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFU);
    rdata |= 0x3f;
    rdata |= (1 << 28);
    // rdata |= (1 << 29) | (2 << 16); /* ref_div = 1 */
    writel(rdata, PLL3_CFG0);

    // rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata = 0;//= readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x20;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    // rdata = readl(PLL3_CTL);
    rdata = 0;//= readl(PLL3_CTL);
    rdata |= (1 << 20);
    rdata |= (1 << 28);
    writel(rdata, PLL3_CTL);
    writel(((1 << 25) | (1 << 4)), PLL3_CTL); /* PLL3 init */

    while(1)
    {
        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 2 PLL3 ready */
        if(((rdata >> 4) & 0x3) == 0x2)
            break;
    }

    // rdata = readl(MEM_CTL_CLK_CFG);
    rdata = 0;//= readl(MEM_CTL_CLK_CFG);
    rdata |= 0x3;   //800Mhz from PLL3
    rdata |= (0x3 << 4); //1/4 division
    rdata |= (0x3 << 16);
    writel(rdata, MEM_CTL_CLK_CFG);

    // rdata = readl(MEM_CTL_DFS_CFG);
    rdata = 0;//= readl(MEM_CTL_DFS_CFG);
    rdata |= 0x1;
    rdata |= (1 << 20);
    writel(rdata, MEM_CTL_DFS_CFG);

     //cfg the mctl port clk enable
    // rdata = readl(MEM_CTL_CLK_CFG);
    rdata = 0;//= readl(MEM_CTL_CLK_CFG);
    rdata &= ~(0x3F << 8);
    rdata |= (0x3F << 19);
    writel(rdata, MEM_CTL_CLK_CFG);

    // soft-reset and then initialization
    wdata = 0;
    wdata &= ~(0xF);
    wdata &= ~(0xF << 8);
    wdata &= ~(0x3 << 24);
    wdata |= 0x8;
    wdata |= (0x8 << 8);
    wdata |= (0x3 << 24);
    writel(wdata, MCTL_RST_TIM);

    //conduct controller core reset
    writel(1, MCTL_RST_CTL);

    // rdata = readl(MEM_CTL_CLK_CFG);
    rdata = 0;//= readl(MEM_CTL_CLK_CFG);
    rdata |= (0x3F << 8);
    rdata |= (0x3F << 19);
    writel(rdata, MEM_CTL_CLK_CFG);
    rdata = readl(MCTL_RST_CTL);
    if(rdata & (1 << 31))
    {
        debug("systctl_rest have been removed\n");
    }
    else
    {
        printf("sysctl_reset not removed");
        // return;
    }

    // Conduct phy reset
    writel(1, PHY_RST_CTL);

    //clear memory controller reseting done status
    writel(0x80000000, MCTL_RST_CTL);

    // dump_ddrphy_regs();

    #ifndef DENALI_PHY

        #ifdef TB_DDR3

        #else

            #ifdef TB_LPDDR3

            #else  //TB_LPDDR4
                //==============================================================================
                //  Config PHY for LPDDR4
                //==============================================================================
                //$display("\t\t\t\tWRITING LPDDR4 MODE TO PHY  time:%0t ", $time);
                reg_write((0x98008000 + PHY_CFG_ADDR), 0x00000002);
                ///  Config PHY for LPDDR4
                //==============================================================================
                //  Setup some default 'trained' values so that we do not need to do training
                //  right away can remove when design gets tested more and is more mature.
                //==============================================================================
                //  Reset value set in the RTL.
                //  With valid values that we need to set to at cfg time .

                reg_write((0x98008000 + TRAINING_CTRL3_ADDR), (1 << 22)); //use Configuration Registers as Write Level SADJ source

                //CFG_DLL_MADJ_RESET

                //  DLL Master Delay Adjustment for all DLLs f0.
                reg_write((0x98008000 + DLL_CTRL1_ADDR), 0x00000031);

                //  DLL Master Delay Adjustment for all DLLs f1.
                reg_write((0x98008000 + DLL_CTRL10_ADDR), 0x00000031);

                // Training ctrl6 vref  bit2: 0 range0  1 range1  bit0-1: 3 lpddr4
                // reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x05050503);
                reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x72323207); //range1 42%
                // reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x59191907); //range1 32%
                // reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x40000007); //range1 22%
                // reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x4d0d0d07); //range1 27%
                // reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x4d0d0d07); //range1 27%
                // reg_write((0x98008000 + TRAINING_CTRL6_ADDR), 0x53131307); //range1 29.6%

                //CFG_RD_DQS_RESET
                //CFG_RD_DQSB_RESET
                //CFG_WR_DQS_RESET
                //CFG_WR_DQ_RESET
                // `ifdef MBPS_800
                // reg_write(({16'h9800,7'h40, DLL_CTRL2_ADDR}), 32'h0000_0000); //32'h0800_0813); //32'h0800_0816);
                reg_write((0x98008000 + DLL_CTRL2_ADDR), 0);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                // reg_write(({16'h9800,7'h40, DLL_CTRL3_ADDR}), 32'h0000_0000); //32'h0800_0813); //32'h0800_0816);
                reg_write((0x98008000 + DLL_CTRL3_ADDR), 0);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                // reg_write(({16'h9800,7'h40, DLL_CTRL4_ADDR}), 32'h0000_0000); //32'h0800_0813); //32'h0800_0816);
                reg_write((0x98008000 + DLL_CTRL4_ADDR), 0);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                // reg_write(({16'h9800,7'h40, DLL_CTRL5_ADDR}), 32'h0000_0000); //32'h0800_0813); //32'h0800_0816);
                reg_write((0x98008000 + DLL_CTRL5_ADDR), 0);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj
                // `endif

                reg_write((0x98008000 + DLL_CTRL11_ADDR), 0); //0x08000816); //0x08000814); //0x08000816);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                reg_write((0x98008000 + DLL_CTRL12_ADDR), 0); //0x08000816); //0x08000814); //0x08000816);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                reg_write((0x98008000 + DLL_CTRL13_ADDR), 0); //0x08000816); //0x08000814); //0x08000816);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                reg_write((0x98008000 + DLL_CTRL14_ADDR), 0); //0x08000816); //0x08000814); //0x08000816);
                /// [31:24]  Read DQS DLL slave adj
                /// [23:16]  Write DQS Dll slave delay adj
                /// [15:8]   Read DQS_B DLL slave delay adj
                /// [7:0]    Write DQ DLL slave Dealy adj

                //CFG_WR_WL_RESET
                // reg_write((0x98008000 + DLL_CTRL6_ADDR), 0x0c0c0c0c); //changed by hyg for jump write leveling training

                // reg_read(0x98008000 + TRAINING_CTRL1_ADDR, rdata);
                // rdata |= 1 << 10;
                // reg_write((0x98008000 + TRAINING_CTRL1_ADDR), rdata);

                reg_write((0x98008000 + DLL_CTRL6_ADDR), 0x11151F16);
                /// [31:24]  Write Level SADJ 3  F0
                /// [23:16]  Write Level SADJ 2
                /// [15:8]   Write Level SADJ 1
                /// [7:0]    Write Level SADJ 0

                reg_write((0x98008000 + DLL_CTRL15_ADDR), 0x11151F16);
                /// [31:24]  Write Level SADJ 3  F1
                /// [23:16]  Write Level SADJ 2
                /// [15:8]   Write Level SADJ 1
                /// [7:0]    Write Level SADJ 0
                // rdata &= ~(1 << 10);
                // reg_write((0x98008000 + TRAINING_CTRL1_ADDR), rdata);

                //CFG_RD_RFE_RESET
                reg_write((0x98008000 + DLL_CTRL19_ADDR), 0x08080808);
                /// [31:24]  Read FIFO clk edge delay slice 3
                /// [23:16]  Read FIFO clk edge delay slice 2
                /// [15:8]   Read FIFO clk edge delay slice 2
                /// [7:0]    Read FIFO clk edge delay slice 0

                //CFG_CA_CA_RESET
                reg_write((0x98008000 + DLL_CTRL7_ADDR), 0x002c2c2c); //0x001e1e1e); //0x0011_1111);
                /// [31:24]  Reserved    F0
                /// [23:16]  CA SADJ 2
                /// [15:8]   CA SADJ 1
                /// [7:0]    CA SADJ 0

                reg_write((0x98008000 + DLL_CTRL16_ADDR), 0x002c2c2c); // 0x00000000);
                /// [31:24]  Reserved   F1
                /// [23:16]  CA SADJ 2
                /// [15:8]   CA SADJ 1
                /// [7:0]    CA SADJ 0

                // CFG_CA_CACK_RESET
                // reg_write((0x98008000 + DLL_CTRL9_ADDR), 0x00000000);
                // reg_write((0x98008000 + DLL_CTRL9_ADDR), 0x000c0c0c); //change by hyg for jump ca training
                reg_write((0x98008000 + DLL_CTRL9_ADDR), 0x0a0a0a); //change by hyg for jump ca training
                /// [31:24]  Reserved    F0
                /// [23:16]  CA CK SADJ 2
                /// [15:8]   CA CK SADJ 1
                /// [7:0]    CA CK SADJ 0

                reg_write((0x98008000 + DLL_CTRL18_ADDR), 0x0a0a0a); //0x00000000);
                /// [31:24]  Reserved    F1
                /// [23:16]  CA CK SADJ 2
                /// [15:8]   CA CK SADJ 1
                /// [7:0]    CA CK SADJ 0

                // CFG_CA_CAWL_RESET
                reg_write((0x98008000 + DLL_CTRL8_ADDR), 0x00080808);
                /// [31:24]  Reserved    F0
                /// [23:16]  Write Level DLL CA slave delay adj slice 2
                /// [15:8]   Write Level DLL CA slave delay adj slice 1
                /// [7:0]    Write Level DLL CA slave delay adj slice 0

                reg_write((0x98008000 + DLL_CTRL17_ADDR), 0x00080808);
                /// [31:24] Reserved    F1
                /// [23:16]  Write Level DLL CA slave delay adj slice 2
                /// [15:8]   Write Level DLL CA slave delay adj slice 1
                /// [7:0]    Write Level DLL CA slave delay adj slice 0

               // reg_write((0x98008000 + DLL_CTRL20_ADDR),  0x05050505);
                reg_write((0x98008000 + DLL_CTRL20_ADDR),  0x00000000);  //changed by hyg from 0x5 to 0x0 (DQ extention) for 800Mbps.
                /// [31:24]  Reserved [27:26] F1 DS3, [25:24] F0 DS3
                /// [23:16]  Reserved [19:18] F1 DS2, [17:16] F0 DS2
                /// [15:8]   Reserved [11:10] F1 DS1, [9:8] F0 DS1
                /// [7:0]    Reserved [3:2] F1 DS0, [1:0] F0 DS0

                /// [31:24] Reserved    F1
                /// [23:16]  Write Level DLL CA slave delay adj slice 2
                /// [15:8]   Write Level DLL CA slave delay adj slice 1
                /// [7:0]    Write Level DLL CA slave delay adj slice 0

                //CFG LPDDR4 DQ SADJ Limit Auto WL SADJ LIMIT  JJD
                // I muck with dqs_dq_sadj_limit for basic block verification
                // reg_write({16'h9800,7'h40,DLL_CTRL22_ADDR}, 32'h3636_481D); //1009
                reg_write((0x98008000 + DLL_CTRL22_ADDR), 0x3636481D);
                /// [31:24]  CAX10 Write Path SADJ Select
                /// [23:16]  DSX8 Write Path SADJ Select
                /// [15:8]   DQS DQ SADJ LIMIT
                /// [7:0]    WL SADJ LIMIT
                //==============================================================================

                //==============================================================================

                // reg_write((0x98008000 + DSX8_IO_CTRL_ADDR), 0x3); // 00:34  01:40  02:48  03:60  04:80  05:120  06:240
                reg_write((0x98008000 + CAX10_IO_CTRL_ADDR), 0x3); // 00:34  01:40  02:48  03:60  04:80  05:120  06:240
                // reg_write((0x98008000 + CAX10_IO_CTRL_ADDR), 0x1); // 00:34  01:40  02:48  03:60  04:80  05:120  06:240

                // reg_write((0x98008000 + DSX8_IO_CTRL_ADDR), 0x83); // 00:34  01:40  02:48  03:60  04:80  05:120  06:240
                // reg_write((0x98008000 + CAX10_IO_CTRL_ADDR), 0x83); // 00:34  01:40  02:48  03:60  04:80  05:120  06:240

                /*  */
                reg_write((0x98008000 + IO_CAL0_ADDR), (1 << 25)); //

                reg_write((0x98008000 + TRAINING_CTRL1_ADDR), 0x00000300);
                //0x0000_0200);
                /// training ctrl bit 8 -> 0 bit 9 -> 1  DS_FRC_RG use cfg regs for Read Gate
                // bit 8 -- auto read gate training

                /// readgate delay set to 0x14 for NoRandomDelay
                ///reg_write((0x98008000 + RGDLY_ADDR), 0x01414_1414);
                reg_write((0x98008000 + RGDLY_ADJ_ADDR), 0x2D2D2D2D); //0x08080808);

                //unmask all interrupts
                reg_write((0x98008000 + INTERRUPT_MASK_ADDR), 0x00000000);
                ////  This is the end of the LPDDR4 PHY setup
            #endif   //TB_LPDDR3
        #endif   //TB_DDR3
    #endif   //not DENALI_PHY

    // dump_ddrphy_regs();
    //==============================================================================

    //==============================================================================

    #ifndef DFI_AGENT

        #ifdef DENALI_CTL_00_DATA

        reg_write(DDR_BASE_ADDR+4*0,DENALI_CTL_00_DATA);

        #endif

        #ifdef DENALI_CTL_01_DATA

        reg_write(DDR_BASE_ADDR+4*1,DENALI_CTL_01_DATA);

        #endif

        #ifdef DENALI_CTL_02_DATA

        reg_write(DDR_BASE_ADDR+4*2,DENALI_CTL_02_DATA);

        #endif

        #ifdef DENALI_CTL_03_DATA

        reg_write(DDR_BASE_ADDR+4*3,DENALI_CTL_03_DATA);

        #endif

        #ifdef DENALI_CTL_04_DATA

        reg_write(DDR_BASE_ADDR+4*4,DENALI_CTL_04_DATA);

        #endif

        #ifdef DENALI_CTL_05_DATA

        reg_write(DDR_BASE_ADDR+4*5,DENALI_CTL_05_DATA);

        #endif

        #ifdef DENALI_CTL_06_DATA

        reg_write(DDR_BASE_ADDR+4*6,DENALI_CTL_06_DATA);

        #endif

        #ifdef DENALI_CTL_07_DATA

        reg_write(DDR_BASE_ADDR+4*7,DENALI_CTL_07_DATA);

        #endif

        #ifdef DENALI_CTL_08_DATA

        reg_write(DDR_BASE_ADDR+4*8,DENALI_CTL_08_DATA);

        #endif

        #ifdef DENALI_CTL_09_DATA

        reg_write(DDR_BASE_ADDR+4*9,DENALI_CTL_09_DATA);

        #endif

        #ifdef DENALI_CTL_10_DATA

        reg_write(DDR_BASE_ADDR+4*10,DENALI_CTL_10_DATA);

        #endif

        #ifdef DENALI_CTL_11_DATA

        reg_write(DDR_BASE_ADDR+4*11,DENALI_CTL_11_DATA);

        #endif

        #ifdef DENALI_CTL_12_DATA

        reg_write(DDR_BASE_ADDR+4*12,DENALI_CTL_12_DATA);

        #endif

        #ifdef DENALI_CTL_13_DATA

        reg_write(DDR_BASE_ADDR+4*13,DENALI_CTL_13_DATA);

        #endif

        #ifdef DENALI_CTL_14_DATA

        reg_write(DDR_BASE_ADDR+4*14,DENALI_CTL_14_DATA);

        #endif

        #ifdef DENALI_CTL_15_DATA

        reg_write(DDR_BASE_ADDR+4*15,DENALI_CTL_15_DATA);

        #endif

        #ifdef DENALI_CTL_16_DATA

        reg_write(DDR_BASE_ADDR+4*16,DENALI_CTL_16_DATA);

        #endif

        #ifdef DENALI_CTL_17_DATA

        reg_write(DDR_BASE_ADDR+4*17,DENALI_CTL_17_DATA);

        #endif

        #ifdef DENALI_CTL_18_DATA

        reg_write(DDR_BASE_ADDR+4*18,DENALI_CTL_18_DATA);

        #endif

        #ifdef DENALI_CTL_19_DATA

        reg_write(DDR_BASE_ADDR+4*19,DENALI_CTL_19_DATA);

        #endif

        #ifdef DENALI_CTL_20_DATA

        reg_write(DDR_BASE_ADDR+4*20,DENALI_CTL_20_DATA);

        #endif

        #ifdef DENALI_CTL_21_DATA

        reg_write(DDR_BASE_ADDR+4*21,DENALI_CTL_21_DATA);

        #endif

        #ifdef DENALI_CTL_22_DATA

        reg_write(DDR_BASE_ADDR+4*22,DENALI_CTL_22_DATA);

        #endif

        #ifdef DENALI_CTL_23_DATA

        reg_write(DDR_BASE_ADDR+4*23,DENALI_CTL_23_DATA);

        #endif

        #ifdef DENALI_CTL_24_DATA

        reg_write(DDR_BASE_ADDR+4*24,DENALI_CTL_24_DATA);

        #endif

        #ifdef DENALI_CTL_25_DATA

        reg_write(DDR_BASE_ADDR+4*25,DENALI_CTL_25_DATA);

        #endif

        #ifdef DENALI_CTL_26_DATA

        reg_write(DDR_BASE_ADDR+4*26,DENALI_CTL_26_DATA);

        #endif

        #ifdef DENALI_CTL_27_DATA

        reg_write(DDR_BASE_ADDR+4*27,DENALI_CTL_27_DATA);

        #endif

        #ifdef DENALI_CTL_28_DATA

        reg_write(DDR_BASE_ADDR+4*28,DENALI_CTL_28_DATA);

        #endif

        #ifdef DENALI_CTL_29_DATA

        reg_write(DDR_BASE_ADDR+4*29,DENALI_CTL_29_DATA);

        #endif

        #ifdef DENALI_CTL_30_DATA

        reg_write(DDR_BASE_ADDR+4*30,DENALI_CTL_30_DATA);

        #endif

        #ifdef DENALI_CTL_31_DATA

        reg_write(DDR_BASE_ADDR+4*31,DENALI_CTL_31_DATA);

        #endif

        #ifdef DENALI_CTL_32_DATA

        reg_write(DDR_BASE_ADDR+4*32,DENALI_CTL_32_DATA);

        #endif

        #ifdef DENALI_CTL_33_DATA

        reg_write(DDR_BASE_ADDR+4*33,DENALI_CTL_33_DATA);

        #endif

        #ifdef DENALI_CTL_34_DATA

        reg_write(DDR_BASE_ADDR+4*34,DENALI_CTL_34_DATA);

        #endif

        #ifdef DENALI_CTL_35_DATA

        reg_write(DDR_BASE_ADDR+4*35,DENALI_CTL_35_DATA);

        #endif

        #ifdef DENALI_CTL_36_DATA

        reg_write(DDR_BASE_ADDR+4*36,DENALI_CTL_36_DATA);

        #endif

        #ifdef DENALI_CTL_37_DATA

        reg_write(DDR_BASE_ADDR+4*37,DENALI_CTL_37_DATA);

        #endif

        #ifdef DENALI_CTL_38_DATA

        reg_write(DDR_BASE_ADDR+4*38,DENALI_CTL_38_DATA);

        #endif

        #ifdef DENALI_CTL_39_DATA

        reg_write(DDR_BASE_ADDR+4*39,DENALI_CTL_39_DATA);

        #endif

        #ifdef DENALI_CTL_40_DATA

        reg_write(DDR_BASE_ADDR+4*40,DENALI_CTL_40_DATA);

        #endif

        #ifdef DENALI_CTL_41_DATA

        reg_write(DDR_BASE_ADDR+4*41,DENALI_CTL_41_DATA);

        #endif

        #ifdef DENALI_CTL_42_DATA

        reg_write(DDR_BASE_ADDR+4*42,DENALI_CTL_42_DATA);

        #endif

        #ifdef DENALI_CTL_43_DATA

        reg_write(DDR_BASE_ADDR+4*43,DENALI_CTL_43_DATA);

        #endif

        #ifdef DENALI_CTL_44_DATA

        reg_write(DDR_BASE_ADDR+4*44,DENALI_CTL_44_DATA);

        #endif

        #ifdef DENALI_CTL_45_DATA

        reg_write(DDR_BASE_ADDR+4*45,DENALI_CTL_45_DATA);

        #endif

        #ifdef DENALI_CTL_46_DATA

        reg_write(DDR_BASE_ADDR+4*46,DENALI_CTL_46_DATA);

        #endif

        #ifdef DENALI_CTL_47_DATA

        reg_write(DDR_BASE_ADDR+4*47,DENALI_CTL_47_DATA);

        #endif

        #ifdef DENALI_CTL_48_DATA

        reg_write(DDR_BASE_ADDR+4*48,DENALI_CTL_48_DATA);

        #endif

        #ifdef DENALI_CTL_49_DATA

        reg_write(DDR_BASE_ADDR+4*49,DENALI_CTL_49_DATA);

        #endif

        #ifdef DENALI_CTL_50_DATA

        reg_write(DDR_BASE_ADDR+4*50,DENALI_CTL_50_DATA);

        #endif

        #ifdef DENALI_CTL_51_DATA

        reg_write(DDR_BASE_ADDR+4*51,DENALI_CTL_51_DATA);

        #endif

        #ifdef DENALI_CTL_52_DATA

        reg_write(DDR_BASE_ADDR+4*52,DENALI_CTL_52_DATA);

        #endif

        #ifdef DENALI_CTL_53_DATA

        reg_write(DDR_BASE_ADDR+4*53,DENALI_CTL_53_DATA);

        #endif

        #ifdef DENALI_CTL_54_DATA

        reg_write(DDR_BASE_ADDR+4*54,DENALI_CTL_54_DATA);

        #endif

        #ifdef DENALI_CTL_55_DATA

        reg_write(DDR_BASE_ADDR+4*55,DENALI_CTL_55_DATA);

        #endif

        #ifdef DENALI_CTL_56_DATA

        reg_write(DDR_BASE_ADDR+4*56,DENALI_CTL_56_DATA);

        #endif

        #ifdef DENALI_CTL_57_DATA

        reg_write(DDR_BASE_ADDR+4*57,DENALI_CTL_57_DATA);

        #endif

        #ifdef DENALI_CTL_58_DATA

        reg_write(DDR_BASE_ADDR+4*58,DENALI_CTL_58_DATA);

        #endif

        #ifdef DENALI_CTL_59_DATA

        reg_write(DDR_BASE_ADDR+4*59,DENALI_CTL_59_DATA);

        #endif

        #ifdef DENALI_CTL_60_DATA

        reg_write(DDR_BASE_ADDR+4*60,DENALI_CTL_60_DATA);

        #endif

        #ifdef DENALI_CTL_61_DATA

        reg_write(DDR_BASE_ADDR+4*61,DENALI_CTL_61_DATA);

        #endif

        #ifdef DENALI_CTL_62_DATA

        reg_write(DDR_BASE_ADDR+4*62,DENALI_CTL_62_DATA);

        #endif

        #ifdef DENALI_CTL_63_DATA

        reg_write(DDR_BASE_ADDR+4*63,DENALI_CTL_63_DATA);

        #endif

        #ifdef DENALI_CTL_64_DATA

        reg_write(DDR_BASE_ADDR+4*64,DENALI_CTL_64_DATA);

        #endif

        #ifdef DENALI_CTL_65_DATA

        reg_write(DDR_BASE_ADDR+4*65,DENALI_CTL_65_DATA);

        #endif

        #ifdef DENALI_CTL_66_DATA

        reg_write(DDR_BASE_ADDR+4*66,DENALI_CTL_66_DATA);

        #endif

        #ifdef DENALI_CTL_67_DATA

        reg_write(DDR_BASE_ADDR+4*67,DENALI_CTL_67_DATA);

        #endif

        #ifdef DENALI_CTL_68_DATA

        reg_write(DDR_BASE_ADDR+4*68,DENALI_CTL_68_DATA);

        #endif

        #ifdef DENALI_CTL_69_DATA

        reg_write(DDR_BASE_ADDR+4*69,DENALI_CTL_69_DATA);

        #endif

        #ifdef DENALI_CTL_70_DATA

        reg_write(DDR_BASE_ADDR+4*70,DENALI_CTL_70_DATA);

        #endif

        #ifdef DENALI_CTL_71_DATA

        reg_write(DDR_BASE_ADDR+4*71,DENALI_CTL_71_DATA);

        #endif

        #ifdef DENALI_CTL_72_DATA

        reg_write(DDR_BASE_ADDR+4*72,DENALI_CTL_72_DATA);

        #endif

        #ifdef DENALI_CTL_73_DATA

        reg_write(DDR_BASE_ADDR+4*73,DENALI_CTL_73_DATA);

        #endif

        #ifdef DENALI_CTL_74_DATA

        reg_write(DDR_BASE_ADDR+4*74,DENALI_CTL_74_DATA);

        #endif

        #ifdef DENALI_CTL_75_DATA

        reg_write(DDR_BASE_ADDR+4*75,DENALI_CTL_75_DATA);

        #endif

        #ifdef DENALI_CTL_76_DATA

        reg_write(DDR_BASE_ADDR+4*76,DENALI_CTL_76_DATA);

        #endif

        #ifdef DENALI_CTL_77_DATA

        reg_write(DDR_BASE_ADDR+4*77,DENALI_CTL_77_DATA);

        #endif

        #ifdef DENALI_CTL_78_DATA

        reg_write(DDR_BASE_ADDR+4*78,DENALI_CTL_78_DATA);

        #endif

        #ifdef DENALI_CTL_79_DATA

        reg_write(DDR_BASE_ADDR+4*79,DENALI_CTL_79_DATA);

        #endif

        #ifdef DENALI_CTL_80_DATA

        reg_write(DDR_BASE_ADDR+4*80,DENALI_CTL_80_DATA);

        #endif

        #ifdef DENALI_CTL_81_DATA

        reg_write(DDR_BASE_ADDR+4*81,DENALI_CTL_81_DATA);

        #endif

        #ifdef DENALI_CTL_82_DATA

        reg_write(DDR_BASE_ADDR+4*82,DENALI_CTL_82_DATA);

        #endif

        #ifdef DENALI_CTL_83_DATA

        reg_write(DDR_BASE_ADDR+4*83,DENALI_CTL_83_DATA);

        #endif

        #ifdef DENALI_CTL_84_DATA

        reg_write(DDR_BASE_ADDR+4*84,DENALI_CTL_84_DATA);

        #endif

        #ifdef DENALI_CTL_85_DATA

        reg_write(DDR_BASE_ADDR+4*85,DENALI_CTL_85_DATA);

        #endif

        #ifdef DENALI_CTL_86_DATA

        reg_write(DDR_BASE_ADDR+4*86,DENALI_CTL_86_DATA);

        #endif

        #ifdef DENALI_CTL_87_DATA

        reg_write(DDR_BASE_ADDR+4*87,DENALI_CTL_87_DATA);

        #endif

        #ifdef DENALI_CTL_88_DATA

        reg_write(DDR_BASE_ADDR+4*88,DENALI_CTL_88_DATA);

        #endif

        #ifdef DENALI_CTL_89_DATA

        reg_write(DDR_BASE_ADDR+4*89,DENALI_CTL_89_DATA);

        #endif

        #ifdef DENALI_CTL_90_DATA

        reg_write(DDR_BASE_ADDR+4*90,DENALI_CTL_90_DATA);

        #endif

        #ifdef DENALI_CTL_91_DATA

        reg_write(DDR_BASE_ADDR+4*91,DENALI_CTL_91_DATA);

        #endif

        #ifdef DENALI_CTL_92_DATA

        reg_write(DDR_BASE_ADDR+4*92,DENALI_CTL_92_DATA);

        #endif

        #ifdef DENALI_CTL_93_DATA

        reg_write(DDR_BASE_ADDR+4*93,DENALI_CTL_93_DATA);

        #endif

        #ifdef DENALI_CTL_94_DATA

        reg_write(DDR_BASE_ADDR+4*94,DENALI_CTL_94_DATA);

        #endif

        #ifdef DENALI_CTL_95_DATA

        reg_write(DDR_BASE_ADDR+4*95,DENALI_CTL_95_DATA);

        #endif

        #ifdef DENALI_CTL_96_DATA

        reg_write(DDR_BASE_ADDR+4*96,DENALI_CTL_96_DATA);

        #endif

        #ifdef DENALI_CTL_97_DATA

        reg_write(DDR_BASE_ADDR+4*97,DENALI_CTL_97_DATA);

        #endif

        #ifdef DENALI_CTL_98_DATA

        reg_write(DDR_BASE_ADDR+4*98,DENALI_CTL_98_DATA);

        #endif

        #ifdef DENALI_CTL_99_DATA

        reg_write(DDR_BASE_ADDR+4*99,DENALI_CTL_99_DATA);

        #endif

        #ifdef DENALI_CTL_100_DATA

        reg_write(DDR_BASE_ADDR+4*100,DENALI_CTL_100_DATA);

        #endif

        reg_write(PHY_RST_CTL,0);

        #ifdef DENALI_CTL_101_DATA

        reg_write(DDR_BASE_ADDR+4*101,DENALI_CTL_101_DATA);

        #endif

        #ifdef DENALI_CTL_102_DATA

        reg_write(DDR_BASE_ADDR+4*102,DENALI_CTL_102_DATA);

        #endif

        #ifdef DENALI_CTL_103_DATA

        reg_write(DDR_BASE_ADDR+4*103,DENALI_CTL_103_DATA);

        #endif

        #ifdef DENALI_CTL_104_DATA

        reg_write(DDR_BASE_ADDR+4*104,DENALI_CTL_104_DATA);

        #endif

        #ifdef DENALI_CTL_105_DATA

        reg_write(DDR_BASE_ADDR+4*105,DENALI_CTL_105_DATA);

        #endif

        #ifdef DENALI_CTL_106_DATA

        reg_write(DDR_BASE_ADDR+4*106,DENALI_CTL_106_DATA);

        #endif

        #ifdef DENALI_CTL_107_DATA

        reg_write(DDR_BASE_ADDR+4*107,DENALI_CTL_107_DATA);

        #endif

        #ifdef DENALI_CTL_108_DATA

        reg_write(DDR_BASE_ADDR+4*108,DENALI_CTL_108_DATA);

        #endif

        #ifdef DENALI_CTL_109_DATA

        reg_write(DDR_BASE_ADDR+4*109,DENALI_CTL_109_DATA);

        #endif

        #ifdef DENALI_CTL_110_DATA

        reg_write(DDR_BASE_ADDR+4*110,DENALI_CTL_110_DATA);

        #endif

        #ifdef DENALI_CTL_111_DATA

        reg_write(DDR_BASE_ADDR+4*111,DENALI_CTL_111_DATA);

        #endif

        #ifdef DENALI_CTL_112_DATA

        reg_write(DDR_BASE_ADDR+4*112,DENALI_CTL_112_DATA);

        #endif

        #ifdef DENALI_CTL_113_DATA

        reg_write(DDR_BASE_ADDR+4*113,DENALI_CTL_113_DATA);

        #endif

        #ifdef DENALI_CTL_114_DATA

        reg_write(DDR_BASE_ADDR+4*114,DENALI_CTL_114_DATA);

        #endif

        #ifdef DENALI_CTL_115_DATA

        reg_write(DDR_BASE_ADDR+4*115,DENALI_CTL_115_DATA);

        #endif

        #ifdef DENALI_CTL_116_DATA

        reg_write(DDR_BASE_ADDR+4*116,DENALI_CTL_116_DATA);

        #endif

        #ifdef DENALI_CTL_117_DATA

        reg_write(DDR_BASE_ADDR+4*117,DENALI_CTL_117_DATA);

        #endif

        #ifdef DENALI_CTL_118_DATA

        reg_write(DDR_BASE_ADDR+4*118,DENALI_CTL_118_DATA);

        #endif

        #ifdef DENALI_CTL_119_DATA

        reg_write(DDR_BASE_ADDR+4*119,DENALI_CTL_119_DATA);

        #endif

        #ifdef DENALI_CTL_120_DATA

        reg_write(DDR_BASE_ADDR+4*120,DENALI_CTL_120_DATA);

        #endif

        #ifdef DENALI_CTL_121_DATA

        reg_write(DDR_BASE_ADDR+4*121,DENALI_CTL_121_DATA);

        #endif

        #ifdef DENALI_CTL_122_DATA

        reg_write(DDR_BASE_ADDR+4*122,DENALI_CTL_122_DATA);

        #endif

        #ifdef DENALI_CTL_123_DATA

        reg_write(DDR_BASE_ADDR+4*123,DENALI_CTL_123_DATA);

        #endif

        #ifdef DENALI_CTL_124_DATA

        reg_write(DDR_BASE_ADDR+4*124,DENALI_CTL_124_DATA);

        #endif

        #ifdef DENALI_CTL_125_DATA

        reg_write(DDR_BASE_ADDR+4*125,DENALI_CTL_125_DATA);

        #endif

        #ifdef DENALI_CTL_126_DATA

        reg_write(DDR_BASE_ADDR+4*126,DENALI_CTL_126_DATA);

        #endif

        #ifdef DENALI_CTL_127_DATA

        reg_write(DDR_BASE_ADDR+4*127,DENALI_CTL_127_DATA);

        #endif

        #ifdef DENALI_CTL_128_DATA

        reg_write(DDR_BASE_ADDR+4*128,DENALI_CTL_128_DATA);

        #endif

        #ifdef DENALI_CTL_129_DATA

        reg_write(DDR_BASE_ADDR+4*129,DENALI_CTL_129_DATA);

        #endif

        #ifdef DENALI_CTL_130_DATA

        reg_write(DDR_BASE_ADDR+4*130,DENALI_CTL_130_DATA);

        #endif

        #ifdef DENALI_CTL_131_DATA

        reg_write(DDR_BASE_ADDR+4*131,DENALI_CTL_131_DATA);

        #endif

        #ifdef DENALI_CTL_132_DATA

        reg_write(DDR_BASE_ADDR+4*132,DENALI_CTL_132_DATA);

        #endif

        #ifdef DENALI_CTL_133_DATA

        reg_write(DDR_BASE_ADDR+4*133,DENALI_CTL_133_DATA);

        #endif

        #ifdef DENALI_CTL_134_DATA

        reg_write(DDR_BASE_ADDR+4*134,DENALI_CTL_134_DATA);

        #endif

        #ifdef DENALI_CTL_135_DATA

        reg_write(DDR_BASE_ADDR+4*135,DENALI_CTL_135_DATA);

        #endif

        #ifdef DENALI_CTL_136_DATA

        reg_write(DDR_BASE_ADDR+4*136,DENALI_CTL_136_DATA);

        #endif

        #ifdef DENALI_CTL_137_DATA

        reg_write(DDR_BASE_ADDR+4*137,DENALI_CTL_137_DATA);

        #endif

        #ifdef DENALI_CTL_138_DATA

        reg_write(DDR_BASE_ADDR+4*138,DENALI_CTL_138_DATA);

        #endif

        #ifdef DENALI_CTL_139_DATA

        reg_write(DDR_BASE_ADDR+4*139,DENALI_CTL_139_DATA);

        #endif

        #ifdef DENALI_CTL_140_DATA

        reg_write(DDR_BASE_ADDR+4*140,DENALI_CTL_140_DATA);

        #endif

        #ifdef DENALI_CTL_141_DATA

        reg_write(DDR_BASE_ADDR+4*141,DENALI_CTL_141_DATA);

        #endif

        #ifdef DENALI_CTL_142_DATA

        reg_write(DDR_BASE_ADDR+4*142,DENALI_CTL_142_DATA);

        #endif

        #ifdef DENALI_CTL_143_DATA

        reg_write(DDR_BASE_ADDR+4*143,DENALI_CTL_143_DATA);

        #endif

        #ifdef DENALI_CTL_144_DATA

        reg_write(DDR_BASE_ADDR+4*144,DENALI_CTL_144_DATA);

        #endif

        #ifdef DENALI_CTL_145_DATA

        reg_write(DDR_BASE_ADDR+4*145,DENALI_CTL_145_DATA);

        #endif

        #ifdef DENALI_CTL_146_DATA

        reg_write(DDR_BASE_ADDR+4*146,DENALI_CTL_146_DATA);

        #endif

        #ifdef DENALI_CTL_147_DATA

        reg_write(DDR_BASE_ADDR+4*147,DENALI_CTL_147_DATA);

        #endif

        #ifdef DENALI_CTL_148_DATA

        reg_write(DDR_BASE_ADDR+4*148,DENALI_CTL_148_DATA);

        #endif

        #ifdef DENALI_CTL_149_DATA

        reg_write(DDR_BASE_ADDR+4*149,DENALI_CTL_149_DATA);

        #endif

        #ifdef DENALI_CTL_150_DATA

        reg_write(DDR_BASE_ADDR+4*150,DENALI_CTL_150_DATA);

        #endif

        #ifdef DENALI_CTL_151_DATA

        reg_write(DDR_BASE_ADDR+4*151,DENALI_CTL_151_DATA);

        #endif

        #ifdef DENALI_CTL_152_DATA

        reg_write(DDR_BASE_ADDR+4*152,DENALI_CTL_152_DATA);

        #endif

        #ifdef DENALI_CTL_153_DATA

        reg_write(DDR_BASE_ADDR+4*153,DENALI_CTL_153_DATA);

        #endif

        #ifdef DENALI_CTL_154_DATA

        reg_write(DDR_BASE_ADDR+4*154,DENALI_CTL_154_DATA);

        #endif

        #ifdef DENALI_CTL_155_DATA

        reg_write(DDR_BASE_ADDR+4*155,DENALI_CTL_155_DATA);

        #endif

        #ifdef DENALI_CTL_156_DATA

        reg_write(DDR_BASE_ADDR+4*156,DENALI_CTL_156_DATA);

        #endif

        #ifdef DENALI_CTL_157_DATA

        reg_write(DDR_BASE_ADDR+4*157,DENALI_CTL_157_DATA);

        #endif

        #ifdef DENALI_CTL_158_DATA

        reg_write(DDR_BASE_ADDR+4*158,DENALI_CTL_158_DATA);

        #endif

        #ifdef DENALI_CTL_159_DATA

        reg_write(DDR_BASE_ADDR+4*159,DENALI_CTL_159_DATA);

        #endif

        #ifdef DENALI_CTL_160_DATA

        reg_write(DDR_BASE_ADDR+4*160,DENALI_CTL_160_DATA);

        #endif

        #ifdef DENALI_CTL_161_DATA

        reg_write(DDR_BASE_ADDR+4*161,DENALI_CTL_161_DATA);

        #endif

        #ifdef DENALI_CTL_162_DATA

        reg_write(DDR_BASE_ADDR+4*162,DENALI_CTL_162_DATA);

        #endif

        #ifdef DENALI_CTL_163_DATA

        reg_write(DDR_BASE_ADDR+4*163,DENALI_CTL_163_DATA);

        #endif

        #ifdef DENALI_CTL_164_DATA

        reg_write(DDR_BASE_ADDR+4*164,DENALI_CTL_164_DATA);

        #endif

        #ifdef DENALI_CTL_165_DATA

        reg_write(DDR_BASE_ADDR+4*165,DENALI_CTL_165_DATA);

        #endif

        #ifdef DENALI_CTL_166_DATA

        reg_write(DDR_BASE_ADDR+4*166,DENALI_CTL_166_DATA);

        #endif

        #ifdef DENALI_CTL_167_DATA

        reg_write(DDR_BASE_ADDR+4*167,DENALI_CTL_167_DATA);

        #endif

        #ifdef DENALI_CTL_168_DATA

        reg_write(DDR_BASE_ADDR+4*168,DENALI_CTL_168_DATA);

        #endif

        #ifdef DENALI_CTL_169_DATA

        reg_write(DDR_BASE_ADDR+4*169,DENALI_CTL_169_DATA);

        #endif

        #ifdef DENALI_CTL_170_DATA

        reg_write(DDR_BASE_ADDR+4*170,DENALI_CTL_170_DATA);

        #endif

        #ifdef DENALI_CTL_171_DATA

        reg_write(DDR_BASE_ADDR+4*171,DENALI_CTL_171_DATA);

        #endif

        #ifdef DENALI_CTL_172_DATA

        reg_write(DDR_BASE_ADDR+4*172,DENALI_CTL_172_DATA);

        #endif

        #ifdef DENALI_CTL_173_DATA

        reg_write(DDR_BASE_ADDR+4*173,DENALI_CTL_173_DATA);

        #endif

        #ifdef DENALI_CTL_174_DATA

        reg_write(DDR_BASE_ADDR+4*174,DENALI_CTL_174_DATA);

        #endif

        #ifdef DENALI_CTL_175_DATA

        reg_write(DDR_BASE_ADDR+4*175,DENALI_CTL_175_DATA);

        #endif

        #ifdef DENALI_CTL_176_DATA

        reg_write(DDR_BASE_ADDR+4*176,DENALI_CTL_176_DATA);

        #endif

        #ifdef DENALI_CTL_177_DATA

        reg_write(DDR_BASE_ADDR+4*177,DENALI_CTL_177_DATA);

        #endif

        #ifdef DENALI_CTL_178_DATA

        reg_write(DDR_BASE_ADDR+4*178,DENALI_CTL_178_DATA);

        #endif

        #ifdef DENALI_CTL_179_DATA

        reg_write(DDR_BASE_ADDR+4*179,DENALI_CTL_179_DATA);

        #endif

        #ifdef DENALI_CTL_180_DATA

        reg_write(DDR_BASE_ADDR+4*180,DENALI_CTL_180_DATA);

        #endif

        #ifdef DENALI_CTL_181_DATA

        reg_write(DDR_BASE_ADDR+4*181,DENALI_CTL_181_DATA);

        #endif

        #ifdef DENALI_CTL_182_DATA

        reg_write(DDR_BASE_ADDR+4*182,DENALI_CTL_182_DATA);

        #endif

        #ifdef DENALI_CTL_183_DATA

        reg_write(DDR_BASE_ADDR+4*183,DENALI_CTL_183_DATA);

        #endif

        #ifdef DENALI_CTL_184_DATA

        reg_write(DDR_BASE_ADDR+4*184,DENALI_CTL_184_DATA);

        #endif

        #ifdef DENALI_CTL_185_DATA

        reg_write(DDR_BASE_ADDR+4*185,DENALI_CTL_185_DATA);

        #endif

        #ifdef DENALI_CTL_186_DATA

        reg_write(DDR_BASE_ADDR+4*186,DENALI_CTL_186_DATA);

        #endif

        #ifdef DENALI_CTL_187_DATA

        reg_write(DDR_BASE_ADDR+4*187,DENALI_CTL_187_DATA);

        #endif

        #ifdef DENALI_CTL_188_DATA

        reg_write(DDR_BASE_ADDR+4*188,DENALI_CTL_188_DATA);

        #endif

        #ifdef DENALI_CTL_189_DATA

        reg_write(DDR_BASE_ADDR+4*189,DENALI_CTL_189_DATA);

        #endif

        #ifdef DENALI_CTL_190_DATA

        reg_write(DDR_BASE_ADDR+4*190,DENALI_CTL_190_DATA);

        #endif

        #ifdef DENALI_CTL_191_DATA

        reg_write(DDR_BASE_ADDR+4*191,DENALI_CTL_191_DATA);

        #endif

        #ifdef DENALI_CTL_192_DATA

        reg_write(DDR_BASE_ADDR+4*192,DENALI_CTL_192_DATA);

        #endif

        #ifdef DENALI_CTL_193_DATA

        reg_write(DDR_BASE_ADDR+4*193,DENALI_CTL_193_DATA);

        #endif

        #ifdef DENALI_CTL_194_DATA

        reg_write(DDR_BASE_ADDR+4*194,DENALI_CTL_194_DATA);

        #endif

        #ifdef DENALI_CTL_195_DATA

        reg_write(DDR_BASE_ADDR+4*195,DENALI_CTL_195_DATA);

        #endif

        #ifdef DENALI_CTL_196_DATA

        reg_write(DDR_BASE_ADDR+4*196,DENALI_CTL_196_DATA);

        #endif

        #ifdef DENALI_CTL_197_DATA

        reg_write(DDR_BASE_ADDR+4*197,DENALI_CTL_197_DATA);

        #endif

        #ifdef DENALI_CTL_198_DATA

        reg_write(DDR_BASE_ADDR+4*198,DENALI_CTL_198_DATA);

        #endif

        #ifdef DENALI_CTL_199_DATA

        reg_write(DDR_BASE_ADDR+4*199,DENALI_CTL_199_DATA);

        #endif

        #ifdef DENALI_CTL_200_DATA

        reg_write(DDR_BASE_ADDR+4*200,DENALI_CTL_200_DATA);

        #endif

        #ifdef DENALI_CTL_201_DATA

        reg_write(DDR_BASE_ADDR+4*201,DENALI_CTL_201_DATA);

        #endif

        #ifdef DENALI_CTL_202_DATA

        reg_write(DDR_BASE_ADDR+4*202,DENALI_CTL_202_DATA);

        #endif

        #ifdef DENALI_CTL_203_DATA

        reg_write(DDR_BASE_ADDR+4*203,DENALI_CTL_203_DATA);

        #endif

        #ifdef DENALI_CTL_204_DATA

        reg_write(DDR_BASE_ADDR+4*204,DENALI_CTL_204_DATA);

        #endif

        #ifdef DENALI_CTL_205_DATA

        reg_write(DDR_BASE_ADDR+4*205,DENALI_CTL_205_DATA);

        #endif

        #ifdef DENALI_CTL_206_DATA

        reg_write(DDR_BASE_ADDR+4*206,DENALI_CTL_206_DATA);

        #endif

        #ifdef DENALI_CTL_207_DATA

        reg_write(DDR_BASE_ADDR+4*207,DENALI_CTL_207_DATA);

        #endif

        #ifdef DENALI_CTL_208_DATA

        reg_write(DDR_BASE_ADDR+4*208,DENALI_CTL_208_DATA);

        #endif

        #ifdef DENALI_CTL_209_DATA

        reg_write(DDR_BASE_ADDR+4*209,DENALI_CTL_209_DATA);

        #endif

        #ifdef DENALI_CTL_210_DATA

        reg_write(DDR_BASE_ADDR+4*210,DENALI_CTL_210_DATA);

        #endif

        #ifdef DENALI_CTL_211_DATA

        reg_write(DDR_BASE_ADDR+4*211,DENALI_CTL_211_DATA);

        #endif

        #ifdef DENALI_CTL_212_DATA

        reg_write(DDR_BASE_ADDR+4*212,DENALI_CTL_212_DATA);

        #endif

        #ifdef DENALI_CTL_213_DATA

        reg_write(DDR_BASE_ADDR+4*213,DENALI_CTL_213_DATA);

        #endif

        #ifdef DENALI_CTL_214_DATA

        reg_write(DDR_BASE_ADDR+4*214,DENALI_CTL_214_DATA);

        #endif

        #ifdef DENALI_CTL_215_DATA

        reg_write(DDR_BASE_ADDR+4*215,DENALI_CTL_215_DATA);

        #endif

        #ifdef DENALI_CTL_216_DATA

        reg_write(DDR_BASE_ADDR+4*216,DENALI_CTL_216_DATA);

        #endif

        #ifdef DENALI_CTL_217_DATA

        reg_write(DDR_BASE_ADDR+4*217,DENALI_CTL_217_DATA);

        #endif

        #ifdef DENALI_CTL_218_DATA

        reg_write(DDR_BASE_ADDR+4*218,DENALI_CTL_218_DATA);

        #endif

        #ifdef DENALI_CTL_219_DATA

        reg_write(DDR_BASE_ADDR+4*219,DENALI_CTL_219_DATA);

        #endif

        #ifdef DENALI_CTL_220_DATA

        reg_write(DDR_BASE_ADDR+4*220,DENALI_CTL_220_DATA);

        #endif

        #ifdef DENALI_CTL_221_DATA

        reg_write(DDR_BASE_ADDR+4*221,DENALI_CTL_221_DATA);

        #endif

        #ifdef DENALI_CTL_222_DATA

        reg_write(DDR_BASE_ADDR+4*222,DENALI_CTL_222_DATA);

        #endif

        #ifdef DENALI_CTL_223_DATA

        reg_write(DDR_BASE_ADDR+4*223,DENALI_CTL_223_DATA);

        #endif

        #ifdef DENALI_CTL_224_DATA

        reg_write(DDR_BASE_ADDR+4*224,DENALI_CTL_224_DATA);

        #endif

        #ifdef DENALI_CTL_225_DATA

        reg_write(DDR_BASE_ADDR+4*225,DENALI_CTL_225_DATA);

        #endif

        #ifdef DENALI_CTL_226_DATA

        reg_write(DDR_BASE_ADDR+4*226,DENALI_CTL_226_DATA);

        #endif

        #ifdef DENALI_CTL_227_DATA

        reg_write(DDR_BASE_ADDR+4*227,DENALI_CTL_227_DATA);

        #endif

        #ifdef DENALI_CTL_228_DATA

        reg_write(DDR_BASE_ADDR+4*228,DENALI_CTL_228_DATA);

        #endif

        #ifdef DENALI_CTL_229_DATA

        reg_write(DDR_BASE_ADDR+4*229,DENALI_CTL_229_DATA);

        #endif

        #ifdef DENALI_CTL_230_DATA

        reg_write(DDR_BASE_ADDR+4*230,DENALI_CTL_230_DATA);

        #endif

        #ifdef DENALI_CTL_231_DATA

        reg_write(DDR_BASE_ADDR+4*231,DENALI_CTL_231_DATA);

        #endif

        #ifdef DENALI_CTL_232_DATA

        reg_write(DDR_BASE_ADDR+4*232,DENALI_CTL_232_DATA);

        #endif

        #ifdef DENALI_CTL_233_DATA

        reg_write(DDR_BASE_ADDR+4*233,DENALI_CTL_233_DATA);

        #endif

        #ifdef DENALI_CTL_234_DATA

        reg_write(DDR_BASE_ADDR+4*234,DENALI_CTL_234_DATA);

        #endif

        #ifdef DENALI_CTL_235_DATA

        reg_write(DDR_BASE_ADDR+4*235,DENALI_CTL_235_DATA);

        #endif

        #ifdef DENALI_CTL_236_DATA

        reg_write(DDR_BASE_ADDR+4*236,DENALI_CTL_236_DATA);

        #endif

        #ifdef DENALI_CTL_237_DATA

        reg_write(DDR_BASE_ADDR+4*237,DENALI_CTL_237_DATA);

        #endif

        #ifdef DENALI_CTL_238_DATA

        reg_write(DDR_BASE_ADDR+4*238,DENALI_CTL_238_DATA);

        #endif

        #ifdef DENALI_CTL_239_DATA

        reg_write(DDR_BASE_ADDR+4*239,DENALI_CTL_239_DATA);

        #endif

        #ifdef DENALI_CTL_240_DATA

        reg_write(DDR_BASE_ADDR+4*240,DENALI_CTL_240_DATA);

        #endif

        #ifdef DENALI_CTL_241_DATA

        reg_write(DDR_BASE_ADDR+4*241,DENALI_CTL_241_DATA);

        #endif

        #ifdef DENALI_CTL_242_DATA

        reg_write(DDR_BASE_ADDR+4*242,DENALI_CTL_242_DATA);

        #endif

        #ifdef DENALI_CTL_243_DATA

        reg_write(DDR_BASE_ADDR+4*243,DENALI_CTL_243_DATA);

        #endif

        #ifdef DENALI_CTL_244_DATA

        reg_write(DDR_BASE_ADDR+4*244,DENALI_CTL_244_DATA);

        #endif

        #ifdef DENALI_CTL_245_DATA

        reg_write(DDR_BASE_ADDR+4*245,DENALI_CTL_245_DATA);

        #endif

        #ifdef DENALI_CTL_246_DATA

        reg_write(DDR_BASE_ADDR+4*246,DENALI_CTL_246_DATA);

        #endif

        #ifdef DENALI_CTL_247_DATA

        reg_write(DDR_BASE_ADDR+4*247,DENALI_CTL_247_DATA);

        #endif

        #ifdef DENALI_CTL_248_DATA

        reg_write(DDR_BASE_ADDR+4*248,DENALI_CTL_248_DATA);

        #endif

        #ifdef DENALI_CTL_249_DATA

        reg_write(DDR_BASE_ADDR+4*249,DENALI_CTL_249_DATA);

        #endif

        #ifdef DENALI_CTL_250_DATA

        reg_write(DDR_BASE_ADDR+4*250,DENALI_CTL_250_DATA);

        #endif

        #ifdef DENALI_CTL_251_DATA

        reg_write(DDR_BASE_ADDR+4*251,DENALI_CTL_251_DATA);

        #endif

        #ifdef DENALI_CTL_252_DATA

        reg_write(DDR_BASE_ADDR+4*252,DENALI_CTL_252_DATA);

        #endif

        #ifdef DENALI_CTL_253_DATA

        reg_write(DDR_BASE_ADDR+4*253,DENALI_CTL_253_DATA);

        #endif

        #ifdef DENALI_CTL_254_DATA

        reg_write(DDR_BASE_ADDR+4*254,DENALI_CTL_254_DATA);

        #endif

        #ifdef DENALI_CTL_255_DATA

        reg_write(DDR_BASE_ADDR+4*255,DENALI_CTL_255_DATA);

        #endif

        #ifdef DENALI_CTL_256_DATA

        reg_write(DDR_BASE_ADDR+4*256,DENALI_CTL_256_DATA);

        #endif

        #ifdef DENALI_CTL_257_DATA

        reg_write(DDR_BASE_ADDR+4*257,DENALI_CTL_257_DATA);

        #endif

        #ifdef DENALI_CTL_258_DATA

        reg_write(DDR_BASE_ADDR+4*258,DENALI_CTL_258_DATA);

        #endif

        #ifdef DENALI_CTL_259_DATA

        reg_write(DDR_BASE_ADDR+4*259,DENALI_CTL_259_DATA);

        #endif

        #ifdef DENALI_CTL_260_DATA

        reg_write(DDR_BASE_ADDR+4*260,DENALI_CTL_260_DATA);

        #endif

        #ifdef DENALI_CTL_261_DATA

        reg_write(DDR_BASE_ADDR+4*261,DENALI_CTL_261_DATA);

        #endif

        #ifdef DENALI_CTL_262_DATA

        reg_write(DDR_BASE_ADDR+4*262,DENALI_CTL_262_DATA);

        #endif

        #ifdef DENALI_CTL_263_DATA

        reg_write(DDR_BASE_ADDR+4*263,DENALI_CTL_263_DATA);

        #endif

        #ifdef DENALI_CTL_264_DATA

        reg_write(DDR_BASE_ADDR+4*264,DENALI_CTL_264_DATA);

        #endif

        #ifdef DENALI_CTL_265_DATA

        reg_write(DDR_BASE_ADDR+4*265,DENALI_CTL_265_DATA);

        #endif

        #ifdef DENALI_CTL_266_DATA

        reg_write(DDR_BASE_ADDR+4*266,DENALI_CTL_266_DATA);

        #endif

        #ifdef DENALI_CTL_267_DATA

        reg_write(DDR_BASE_ADDR+4*267,DENALI_CTL_267_DATA);

        #endif

        #ifdef DENALI_CTL_268_DATA

        reg_write(DDR_BASE_ADDR+4*268,DENALI_CTL_268_DATA);

        #endif

        #ifdef DENALI_CTL_269_DATA

        reg_write(DDR_BASE_ADDR+4*269,DENALI_CTL_269_DATA);

        #endif

        #ifdef DENALI_CTL_270_DATA

        reg_write(DDR_BASE_ADDR+4*270,DENALI_CTL_270_DATA);

        #endif

        #ifdef DENALI_CTL_271_DATA

        reg_write(DDR_BASE_ADDR+4*271,DENALI_CTL_271_DATA);

        #endif

        #ifdef DENALI_CTL_272_DATA

        reg_write(DDR_BASE_ADDR+4*272,DENALI_CTL_272_DATA);

        #endif

        #ifdef DENALI_CTL_273_DATA

        reg_write(DDR_BASE_ADDR+4*273,DENALI_CTL_273_DATA);

        #endif

        #ifdef DENALI_CTL_274_DATA

        reg_write(DDR_BASE_ADDR+4*274,DENALI_CTL_274_DATA);

        #endif

        #ifdef DENALI_CTL_275_DATA

        reg_write(DDR_BASE_ADDR+4*275,DENALI_CTL_275_DATA);

        #endif

        #ifdef DENALI_CTL_276_DATA

        reg_write(DDR_BASE_ADDR+4*276,DENALI_CTL_276_DATA);

        #endif

        #ifdef DENALI_CTL_277_DATA

        reg_write(DDR_BASE_ADDR+4*277,DENALI_CTL_277_DATA);

        #endif

        #ifdef DENALI_CTL_278_DATA

        reg_write(DDR_BASE_ADDR+4*278,DENALI_CTL_278_DATA);

        #endif

        #ifdef DENALI_CTL_279_DATA

        reg_write(DDR_BASE_ADDR+4*279,DENALI_CTL_279_DATA);

        #endif

        #ifdef DENALI_CTL_280_DATA

        reg_write(DDR_BASE_ADDR+4*280,DENALI_CTL_280_DATA);

        #endif

        #ifdef DENALI_CTL_281_DATA

        reg_write(DDR_BASE_ADDR+4*281,DENALI_CTL_281_DATA);

        #endif

        #ifdef DENALI_CTL_282_DATA

        reg_write(DDR_BASE_ADDR+4*282,DENALI_CTL_282_DATA);

        #endif

        #ifdef DENALI_CTL_283_DATA

        reg_write(DDR_BASE_ADDR+4*283,DENALI_CTL_283_DATA);

        #endif

        #ifdef DENALI_CTL_284_DATA

        reg_write(DDR_BASE_ADDR+4*284,DENALI_CTL_284_DATA);

        #endif

        #ifdef DENALI_CTL_285_DATA

        reg_write(DDR_BASE_ADDR+4*285,DENALI_CTL_285_DATA);

        #endif

        #ifdef DENALI_CTL_286_DATA

        reg_write(DDR_BASE_ADDR+4*286,DENALI_CTL_286_DATA);

        #endif

        #ifdef DENALI_CTL_287_DATA

        reg_write(DDR_BASE_ADDR+4*287,DENALI_CTL_287_DATA);

        #endif

        #ifdef DENALI_CTL_288_DATA

        reg_write(DDR_BASE_ADDR+4*288,DENALI_CTL_288_DATA);

        #endif

        #ifdef DENALI_CTL_289_DATA

        reg_write(DDR_BASE_ADDR+4*289,DENALI_CTL_289_DATA);

        #endif

        #ifdef DENALI_CTL_290_DATA

        reg_write(DDR_BASE_ADDR+4*290,DENALI_CTL_290_DATA);

        #endif

        #ifdef DENALI_CTL_291_DATA

        reg_write(DDR_BASE_ADDR+4*291,DENALI_CTL_291_DATA);

        #endif

        #ifdef DENALI_CTL_292_DATA

        reg_write(DDR_BASE_ADDR+4*292,DENALI_CTL_292_DATA);

        #endif

        #ifdef DENALI_CTL_293_DATA

        reg_write(DDR_BASE_ADDR+4*293,DENALI_CTL_293_DATA);

        #endif

        #ifdef DENALI_CTL_294_DATA

        reg_write(DDR_BASE_ADDR+4*294,DENALI_CTL_294_DATA);

        #endif

        #ifdef DENALI_CTL_295_DATA

        reg_write(DDR_BASE_ADDR+4*295,DENALI_CTL_295_DATA);

        #endif

        #ifdef DENALI_CTL_296_DATA

        reg_write(DDR_BASE_ADDR+4*296,DENALI_CTL_296_DATA);

        #endif

        #ifdef DENALI_CTL_297_DATA

        reg_write(DDR_BASE_ADDR+4*297,DENALI_CTL_297_DATA);

        #endif

        #ifdef DENALI_CTL_298_DATA

        reg_write(DDR_BASE_ADDR+4*298,DENALI_CTL_298_DATA);

        #endif

        #ifdef DENALI_CTL_299_DATA

        reg_write(DDR_BASE_ADDR+4*299,DENALI_CTL_299_DATA);

        #endif

        #ifdef DENALI_CTL_300_DATA

        reg_write(DDR_BASE_ADDR+4*300,DENALI_CTL_300_DATA);

        #endif

        #ifdef DENALI_CTL_301_DATA

        reg_write(DDR_BASE_ADDR+4*301,DENALI_CTL_301_DATA);

        #endif

        #ifdef DENALI_CTL_302_DATA

        reg_write(DDR_BASE_ADDR+4*302,DENALI_CTL_302_DATA);

        #endif

        #ifdef DENALI_CTL_303_DATA

        reg_write(DDR_BASE_ADDR+4*303,DENALI_CTL_303_DATA);

        #endif

        #ifdef DENALI_CTL_304_DATA

        reg_write(DDR_BASE_ADDR+4*304,DENALI_CTL_304_DATA);

        #endif

        #ifdef DENALI_CTL_305_DATA

        reg_write(DDR_BASE_ADDR+4*305,DENALI_CTL_305_DATA);

        #endif

        #ifdef DENALI_CTL_306_DATA

        reg_write(DDR_BASE_ADDR+4*306,DENALI_CTL_306_DATA);

        #endif

        #ifdef DENALI_CTL_307_DATA

        reg_write(DDR_BASE_ADDR+4*307,DENALI_CTL_307_DATA);

        #endif

        #ifdef DENALI_CTL_308_DATA

        reg_write(DDR_BASE_ADDR+4*308,DENALI_CTL_308_DATA);

        #endif

        #ifdef DENALI_CTL_309_DATA

        reg_write(DDR_BASE_ADDR+4*309,DENALI_CTL_309_DATA);

        #endif

        #ifdef DENALI_CTL_310_DATA

        reg_write(DDR_BASE_ADDR+4*310,DENALI_CTL_310_DATA);

        #endif

        #ifdef DENALI_CTL_311_DATA

        reg_write(DDR_BASE_ADDR+4*311,DENALI_CTL_311_DATA);

        #endif

        #ifdef DENALI_CTL_312_DATA

        reg_write(DDR_BASE_ADDR+4*312,DENALI_CTL_312_DATA);

        #endif

        #ifdef DENALI_CTL_313_DATA

        reg_write(DDR_BASE_ADDR+4*313,DENALI_CTL_313_DATA);

        #endif

        #ifdef DENALI_CTL_314_DATA

        reg_write(DDR_BASE_ADDR+4*314,DENALI_CTL_314_DATA);

        #endif

        #ifdef DENALI_CTL_315_DATA

        reg_write(DDR_BASE_ADDR+4*315,DENALI_CTL_315_DATA);

        #endif

        #ifdef DENALI_CTL_316_DATA

        reg_write(DDR_BASE_ADDR+4*316,DENALI_CTL_316_DATA);

        #endif

        #ifdef DENALI_CTL_317_DATA

        reg_write(DDR_BASE_ADDR+4*317,DENALI_CTL_317_DATA);

        #endif

        #ifdef DENALI_CTL_318_DATA

        reg_write(DDR_BASE_ADDR+4*318,DENALI_CTL_318_DATA);

        #endif

        #ifdef DENALI_CTL_319_DATA

        reg_write(DDR_BASE_ADDR+4*319,DENALI_CTL_319_DATA);

        #endif

        #ifdef DENALI_CTL_320_DATA

        reg_write(DDR_BASE_ADDR+4*320,DENALI_CTL_320_DATA);

        #endif

        #ifdef DENALI_CTL_321_DATA

        reg_write(DDR_BASE_ADDR+4*321,DENALI_CTL_321_DATA);

        #endif

        #ifdef DENALI_CTL_322_DATA

        reg_write(DDR_BASE_ADDR+4*322,DENALI_CTL_322_DATA);

        #endif

        #ifdef DENALI_CTL_323_DATA

        reg_write(DDR_BASE_ADDR+4*323,DENALI_CTL_323_DATA);

        #endif

        #ifdef DENALI_CTL_324_DATA

        reg_write(DDR_BASE_ADDR+4*324,DENALI_CTL_324_DATA);

        #endif

        #ifdef DENALI_CTL_325_DATA

        reg_write(DDR_BASE_ADDR+4*325,DENALI_CTL_325_DATA);

        #endif

        #ifdef DENALI_CTL_326_DATA

        reg_write(DDR_BASE_ADDR+4*326,DENALI_CTL_326_DATA);

        #endif

        #ifdef DENALI_CTL_327_DATA

        reg_write(DDR_BASE_ADDR+4*327,DENALI_CTL_327_DATA);

        #endif

        #ifdef DENALI_CTL_328_DATA

        reg_write(DDR_BASE_ADDR+4*328,DENALI_CTL_328_DATA);

        #endif

        #ifdef DENALI_CTL_329_DATA

        reg_write(DDR_BASE_ADDR+4*329,DENALI_CTL_329_DATA);

        #endif

        #ifdef DENALI_CTL_330_DATA

        reg_write(DDR_BASE_ADDR+4*330,DENALI_CTL_330_DATA);

        #endif

        #ifdef DENALI_CTL_331_DATA

        reg_write(DDR_BASE_ADDR+4*331,DENALI_CTL_331_DATA);

        #endif

        #ifdef DENALI_CTL_332_DATA

        reg_write(DDR_BASE_ADDR+4*332,DENALI_CTL_332_DATA);

        #endif

        #ifdef DENALI_CTL_333_DATA

        reg_write(DDR_BASE_ADDR+4*333,DENALI_CTL_333_DATA);

        #endif

        #ifdef DENALI_CTL_334_DATA

        reg_write(DDR_BASE_ADDR+4*334,DENALI_CTL_334_DATA);

        #endif

        #ifdef DENALI_CTL_335_DATA

        reg_write(DDR_BASE_ADDR+4*335,DENALI_CTL_335_DATA);

        #endif

        #ifdef DENALI_CTL_336_DATA

        reg_write(DDR_BASE_ADDR+4*336,DENALI_CTL_336_DATA);

        #endif

        #ifdef DENALI_CTL_337_DATA

        reg_write(DDR_BASE_ADDR+4*337,DENALI_CTL_337_DATA);

        #endif

        #ifdef DENALI_CTL_338_DATA

        reg_write(DDR_BASE_ADDR+4*338,DENALI_CTL_338_DATA);

        #endif

        #ifdef DENALI_CTL_339_DATA

        reg_write(DDR_BASE_ADDR+4*339,DENALI_CTL_339_DATA);

        #endif

        #ifdef DENALI_CTL_340_DATA

        reg_write(DDR_BASE_ADDR+4*340,DENALI_CTL_340_DATA);

        #endif

        #ifdef DENALI_CTL_341_DATA

        reg_write(DDR_BASE_ADDR+4*341,DENALI_CTL_341_DATA);

        #endif

        #ifdef DENALI_CTL_342_DATA

        reg_write(DDR_BASE_ADDR+4*342,DENALI_CTL_342_DATA);

        #endif

        #ifdef DENALI_CTL_343_DATA

        reg_write(DDR_BASE_ADDR+4*343,DENALI_CTL_343_DATA);

        #endif

        #ifdef DENALI_CTL_344_DATA

        reg_write(DDR_BASE_ADDR+4*344,DENALI_CTL_344_DATA);

        #endif

        #ifdef DENALI_CTL_345_DATA

        reg_write(DDR_BASE_ADDR+4*345,DENALI_CTL_345_DATA);

        #endif

        #ifdef DENALI_CTL_346_DATA

        reg_write(DDR_BASE_ADDR+4*346,DENALI_CTL_346_DATA);

        #endif

        #ifdef DENALI_CTL_347_DATA

        reg_write(DDR_BASE_ADDR+4*347,DENALI_CTL_347_DATA);

        #endif

        #ifdef DENALI_CTL_348_DATA

        reg_write(DDR_BASE_ADDR+4*348,DENALI_CTL_348_DATA);

        #endif

        #ifdef DENALI_CTL_349_DATA

        reg_write(DDR_BASE_ADDR+4*349,DENALI_CTL_349_DATA);

        #endif

        #ifdef DENALI_CTL_350_DATA

        reg_write(DDR_BASE_ADDR+4*350,DENALI_CTL_350_DATA);

        #endif

        #ifdef DENALI_CTL_351_DATA

        reg_write(DDR_BASE_ADDR+4*351,DENALI_CTL_351_DATA);

        #endif

        #ifdef DENALI_CTL_352_DATA

        reg_write(DDR_BASE_ADDR+4*352,DENALI_CTL_352_DATA);

        #endif

        #ifdef DENALI_CTL_353_DATA

        reg_write(DDR_BASE_ADDR+4*353,DENALI_CTL_353_DATA);

        #endif

        #ifdef DENALI_CTL_354_DATA

        reg_write(DDR_BASE_ADDR+4*354,DENALI_CTL_354_DATA);

        #endif

        #ifdef DENALI_CTL_355_DATA

        reg_write(DDR_BASE_ADDR+4*355,DENALI_CTL_355_DATA);

        #endif

        #ifdef DENALI_CTL_356_DATA

        reg_write(DDR_BASE_ADDR+4*356,DENALI_CTL_356_DATA);

        #endif

        #ifdef DENALI_CTL_357_DATA

        reg_write(DDR_BASE_ADDR+4*357,DENALI_CTL_357_DATA);

        #endif

        #ifdef DENALI_CTL_358_DATA

        reg_write(DDR_BASE_ADDR+4*358,DENALI_CTL_358_DATA);

        #endif

        #ifdef DENALI_CTL_359_DATA

        reg_write(DDR_BASE_ADDR+4*359,DENALI_CTL_359_DATA);

        #endif

        #ifdef DENALI_CTL_360_DATA

        reg_write(DDR_BASE_ADDR+4*360,DENALI_CTL_360_DATA);

        #endif

        #ifdef DENALI_CTL_361_DATA

        reg_write(DDR_BASE_ADDR+4*361,DENALI_CTL_361_DATA);

        #endif

        #ifdef DENALI_CTL_362_DATA

        reg_write(DDR_BASE_ADDR+4*362,DENALI_CTL_362_DATA);

        #endif

        #ifdef DENALI_CTL_363_DATA

        reg_write(DDR_BASE_ADDR+4*363,DENALI_CTL_363_DATA);

        #endif

        #ifdef DENALI_CTL_364_DATA

        reg_write(DDR_BASE_ADDR+4*364,DENALI_CTL_364_DATA);

        #endif

        #ifdef DENALI_CTL_365_DATA

        reg_write(DDR_BASE_ADDR+4*365,DENALI_CTL_365_DATA);

        #endif

        #ifdef DENALI_CTL_366_DATA

        reg_write(DDR_BASE_ADDR+4*366,DENALI_CTL_366_DATA);

        #endif

        #ifdef DENALI_CTL_367_DATA

        reg_write(DDR_BASE_ADDR+4*367,DENALI_CTL_367_DATA);

        #endif

        #ifdef DENALI_CTL_368_DATA

        reg_write(DDR_BASE_ADDR+4*368,DENALI_CTL_368_DATA);

        #endif

        #ifdef DENALI_CTL_369_DATA

        reg_write(DDR_BASE_ADDR+4*369,DENALI_CTL_369_DATA);

        #endif

        #ifdef DENALI_CTL_370_DATA

        reg_write(DDR_BASE_ADDR+4*370,DENALI_CTL_370_DATA);

        #endif

        #ifdef DENALI_CTL_371_DATA

        reg_write(DDR_BASE_ADDR+4*371,DENALI_CTL_371_DATA);

        #endif

        #ifdef DENALI_CTL_372_DATA

        reg_write(DDR_BASE_ADDR+4*372,DENALI_CTL_372_DATA);

        #endif

        #ifdef DENALI_CTL_373_DATA

        reg_write(DDR_BASE_ADDR+4*373,DENALI_CTL_373_DATA);

        #endif

        #ifdef DENALI_CTL_374_DATA

        reg_write(DDR_BASE_ADDR+4*374,DENALI_CTL_374_DATA);

        #endif

        #ifdef DENALI_CTL_375_DATA

        reg_write(DDR_BASE_ADDR+4*375,DENALI_CTL_375_DATA);

        #endif

        #ifdef DENALI_CTL_376_DATA

        reg_write(DDR_BASE_ADDR+4*376,DENALI_CTL_376_DATA);

        #endif

        #ifdef DENALI_CTL_377_DATA

        reg_write(DDR_BASE_ADDR+4*377,DENALI_CTL_377_DATA);

        #endif

        #ifdef DENALI_CTL_378_DATA

        reg_write(DDR_BASE_ADDR+4*378,DENALI_CTL_378_DATA);

        #endif

        #ifdef DENALI_CTL_379_DATA

        reg_write(DDR_BASE_ADDR+4*379,DENALI_CTL_379_DATA);

        #endif

        #ifdef DENALI_CTL_380_DATA

        reg_write(DDR_BASE_ADDR+4*380,DENALI_CTL_380_DATA);

        #endif

        #ifdef DENALI_CTL_381_DATA

        reg_write(DDR_BASE_ADDR+4*381,DENALI_CTL_381_DATA);

        #endif

        #ifdef DENALI_CTL_382_DATA

        reg_write(DDR_BASE_ADDR+4*382,DENALI_CTL_382_DATA);

        #endif

        #ifdef DENALI_CTL_383_DATA

        reg_write(DDR_BASE_ADDR+4*383,DENALI_CTL_383_DATA);

        #endif

        #ifdef DENALI_CTL_384_DATA

        reg_write(DDR_BASE_ADDR+4*384,DENALI_CTL_384_DATA);

        #endif

        #ifdef DENALI_CTL_385_DATA

        reg_write(DDR_BASE_ADDR+4*385,DENALI_CTL_385_DATA);

        #endif

        #ifdef DENALI_CTL_386_DATA

        reg_write(DDR_BASE_ADDR+4*386,DENALI_CTL_386_DATA);

        #endif

        #ifdef DENALI_CTL_387_DATA

        reg_write(DDR_BASE_ADDR+4*387,DENALI_CTL_387_DATA);

        #endif

        #ifdef DENALI_CTL_388_DATA

        reg_write(DDR_BASE_ADDR+4*388,DENALI_CTL_388_DATA);

        #endif

        #ifdef DENALI_CTL_389_DATA

        reg_write(DDR_BASE_ADDR+4*389,DENALI_CTL_389_DATA);

        #endif

        #ifdef DENALI_CTL_390_DATA

        reg_write(DDR_BASE_ADDR+4*390,DENALI_CTL_390_DATA);

        #endif

        #ifdef DENALI_CTL_391_DATA

        reg_write(DDR_BASE_ADDR+4*391,DENALI_CTL_391_DATA);

        #endif

        #ifdef DENALI_CTL_392_DATA

        reg_write(DDR_BASE_ADDR+4*392,DENALI_CTL_392_DATA);

        #endif

        #ifdef DENALI_CTL_393_DATA

        reg_write(DDR_BASE_ADDR+4*393,DENALI_CTL_393_DATA);

        #endif

        #ifdef DENALI_CTL_394_DATA

        reg_write(DDR_BASE_ADDR+4*394,DENALI_CTL_394_DATA);

        #endif

        #ifdef DENALI_CTL_395_DATA

        reg_write(DDR_BASE_ADDR+4*395,DENALI_CTL_395_DATA);

        #endif

        #ifdef DENALI_CTL_396_DATA

        reg_write(DDR_BASE_ADDR+4*396,DENALI_CTL_396_DATA);

        #endif

        #ifdef DENALI_CTL_397_DATA

        reg_write(DDR_BASE_ADDR+4*397,DENALI_CTL_397_DATA);

        #endif

        #ifdef DENALI_CTL_398_DATA

        reg_write(DDR_BASE_ADDR+4*398,DENALI_CTL_398_DATA);

        #endif

        #ifdef DENALI_CTL_399_DATA

        reg_write(DDR_BASE_ADDR+4*399,DENALI_CTL_399_DATA);

        #endif

        #ifdef DENALI_CTL_400_DATA

        reg_write(DDR_BASE_ADDR+4*400,DENALI_CTL_400_DATA);

        #endif

        #ifdef DENALI_CTL_401_DATA

        reg_write(DDR_BASE_ADDR+4*401,DENALI_CTL_401_DATA);

        #endif

        #ifdef DENALI_CTL_402_DATA

        reg_write(DDR_BASE_ADDR+4*402,DENALI_CTL_402_DATA);

        #endif

        #ifdef DENALI_CTL_403_DATA

        reg_write(DDR_BASE_ADDR+4*403,DENALI_CTL_403_DATA);

        #endif

        #ifdef DENALI_CTL_404_DATA

        reg_write(DDR_BASE_ADDR+4*404,DENALI_CTL_404_DATA);

        #endif

        #ifdef DENALI_CTL_405_DATA

        reg_write(DDR_BASE_ADDR+4*405,DENALI_CTL_405_DATA);

        #endif

        #ifdef DENALI_CTL_406_DATA

        reg_write(DDR_BASE_ADDR+4*406,DENALI_CTL_406_DATA);

        #endif

        #ifdef DENALI_CTL_407_DATA

        reg_write(DDR_BASE_ADDR+4*407,DENALI_CTL_407_DATA);

        #endif

        #ifdef DENALI_CTL_408_DATA

        reg_write(DDR_BASE_ADDR+4*408,DENALI_CTL_408_DATA);

        #endif

        #ifdef DENALI_CTL_409_DATA

        reg_write(DDR_BASE_ADDR+4*409,DENALI_CTL_409_DATA);

        #endif

        #ifdef DENALI_CTL_410_DATA

        reg_write(DDR_BASE_ADDR+4*410,DENALI_CTL_410_DATA);

        #endif

        #ifdef DENALI_CTL_411_DATA

        reg_write(DDR_BASE_ADDR+4*411,DENALI_CTL_411_DATA);

        #endif

        #ifdef DENALI_CTL_412_DATA

        reg_write(DDR_BASE_ADDR+4*412,DENALI_CTL_412_DATA);

        #endif

        #ifdef DENALI_CTL_413_DATA

        reg_write(DDR_BASE_ADDR+4*413,DENALI_CTL_413_DATA);

        #endif

        #ifdef DENALI_CTL_414_DATA

        reg_write(DDR_BASE_ADDR+4*414,DENALI_CTL_414_DATA);

        #endif

        #ifdef DENALI_CTL_415_DATA

        reg_write(DDR_BASE_ADDR+4*415,DENALI_CTL_415_DATA);

        #endif

        #ifdef DENALI_CTL_416_DATA

        reg_write(DDR_BASE_ADDR+4*416,DENALI_CTL_416_DATA);

        #endif

        #ifdef DENALI_CTL_417_DATA

        reg_write(DDR_BASE_ADDR+4*417,DENALI_CTL_417_DATA);

        #endif

        #ifdef DENALI_CTL_418_DATA

        reg_write(DDR_BASE_ADDR+4*418,DENALI_CTL_418_DATA);

        #endif

        #ifdef DENALI_CTL_419_DATA

        reg_write(DDR_BASE_ADDR+4*419,DENALI_CTL_419_DATA);

        #endif

        #ifdef DENALI_CTL_420_DATA

        reg_write(DDR_BASE_ADDR+4*420,DENALI_CTL_420_DATA);

        #endif

        #ifdef DENALI_CTL_421_DATA

        reg_write(DDR_BASE_ADDR+4*421,DENALI_CTL_421_DATA);

        #endif

        #ifdef DENALI_CTL_422_DATA

        reg_write(DDR_BASE_ADDR+4*422,DENALI_CTL_422_DATA);

        #endif

        #ifdef DENALI_CTL_423_DATA

        reg_write(DDR_BASE_ADDR+4*423,DENALI_CTL_423_DATA);

        #endif

        #ifdef DENALI_CTL_424_DATA

        reg_write(DDR_BASE_ADDR+4*424,DENALI_CTL_424_DATA);

        #endif

        #ifdef DENALI_CTL_425_DATA

        reg_write(DDR_BASE_ADDR+4*425,DENALI_CTL_425_DATA);

        #endif

        #ifdef DENALI_CTL_426_DATA

        reg_write(DDR_BASE_ADDR+4*426,DENALI_CTL_426_DATA);

        #endif

        #ifdef DENALI_CTL_427_DATA

        reg_write(DDR_BASE_ADDR+4*427,DENALI_CTL_427_DATA);

        #endif

        #ifdef DENALI_CTL_428_DATA

        reg_write(DDR_BASE_ADDR+4*428,DENALI_CTL_428_DATA);

        #endif

        #ifdef DENALI_CTL_429_DATA

        reg_write(DDR_BASE_ADDR+4*429,DENALI_CTL_429_DATA);

        #endif

        #ifdef DENALI_CTL_430_DATA

        reg_write(DDR_BASE_ADDR+4*430,DENALI_CTL_430_DATA);

        #endif

        #ifdef DENALI_CTL_431_DATA

        reg_write(DDR_BASE_ADDR+4*431,DENALI_CTL_431_DATA);

        #endif

        #ifdef DENALI_CTL_432_DATA

        reg_write(DDR_BASE_ADDR+4*432,DENALI_CTL_432_DATA);

        #endif

        #ifdef DENALI_CTL_433_DATA

        reg_write(DDR_BASE_ADDR+4*433,DENALI_CTL_433_DATA);

        #endif

        #ifdef DENALI_CTL_434_DATA

        reg_write(DDR_BASE_ADDR+4*434,DENALI_CTL_434_DATA);

        #endif

        #ifdef DENALI_CTL_435_DATA

        reg_write(DDR_BASE_ADDR+4*435,DENALI_CTL_435_DATA);

        #endif

        #ifdef DENALI_CTL_436_DATA

        reg_write(DDR_BASE_ADDR+4*436,DENALI_CTL_436_DATA);

        #endif

        #ifdef DENALI_CTL_437_DATA

        reg_write(DDR_BASE_ADDR+4*437,DENALI_CTL_437_DATA);

        #endif

        #ifdef DENALI_CTL_438_DATA

        reg_write(DDR_BASE_ADDR+4*438,DENALI_CTL_438_DATA);

        #endif

        #ifdef DENALI_CTL_439_DATA

        reg_write(DDR_BASE_ADDR+4*439,DENALI_CTL_439_DATA);

        #endif

        #ifdef DENALI_CTL_440_DATA

        reg_write(DDR_BASE_ADDR+4*440,DENALI_CTL_440_DATA);

        #endif

        #ifdef DENALI_CTL_441_DATA

        reg_write(DDR_BASE_ADDR+4*441,DENALI_CTL_441_DATA);

        #endif

        #ifdef DENALI_CTL_442_DATA

        reg_write(DDR_BASE_ADDR+4*442,DENALI_CTL_442_DATA);

        #endif

        #ifdef DENALI_CTL_443_DATA

        reg_write(DDR_BASE_ADDR+4*443,DENALI_CTL_443_DATA);

        #endif

        #ifdef DENALI_CTL_444_DATA

        reg_write(DDR_BASE_ADDR+4*444,DENALI_CTL_444_DATA);

        #endif

        #ifdef DENALI_CTL_445_DATA

        reg_write(DDR_BASE_ADDR+4*445,DENALI_CTL_445_DATA);

        #endif

        #ifdef DENALI_CTL_446_DATA

        reg_write(DDR_BASE_ADDR+4*446,DENALI_CTL_446_DATA);

        #endif

        #ifdef DENALI_CTL_447_DATA

        reg_write(DDR_BASE_ADDR+4*447,DENALI_CTL_447_DATA);

        #endif

        #ifdef DENALI_CTL_448_DATA

        reg_write(DDR_BASE_ADDR+4*448,DENALI_CTL_448_DATA);

        #endif

        #ifdef DENALI_CTL_449_DATA

        reg_write(DDR_BASE_ADDR+4*449,DENALI_CTL_449_DATA);

        #endif

        #ifdef DENALI_CTL_450_DATA

        reg_write(DDR_BASE_ADDR+4*450,DENALI_CTL_450_DATA);

        #endif

        #ifdef DENALI_CTL_451_DATA

        reg_write(DDR_BASE_ADDR+4*451,DENALI_CTL_451_DATA);

        #endif

        #ifdef DENALI_CTL_452_DATA

        reg_write(DDR_BASE_ADDR+4*452,DENALI_CTL_452_DATA);

        #endif

        #ifdef DENALI_CTL_453_DATA

        reg_write(DDR_BASE_ADDR+4*453,DENALI_CTL_453_DATA);

        #endif

        #ifdef DENALI_CTL_454_DATA

        reg_write(DDR_BASE_ADDR+4*454,DENALI_CTL_454_DATA);

        #endif

        #ifdef DENALI_CTL_455_DATA

        reg_write(DDR_BASE_ADDR+4*455,DENALI_CTL_455_DATA);

        #endif

        #ifdef DENALI_CTL_456_DATA

        reg_write(DDR_BASE_ADDR+4*456,DENALI_CTL_456_DATA);

        #endif

        #ifdef DENALI_CTL_457_DATA

        reg_write(DDR_BASE_ADDR+4*457,DENALI_CTL_457_DATA);

        #endif

        #ifdef DENALI_CTL_458_DATA

        reg_write(DDR_BASE_ADDR+4*458,DENALI_CTL_458_DATA);

        #endif

        #ifdef DENALI_CTL_459_DATA

        reg_write(DDR_BASE_ADDR+4*459,DENALI_CTL_459_DATA);

        #endif

        #ifdef DENALI_CTL_460_DATA

        reg_write(DDR_BASE_ADDR+4*460,DENALI_CTL_460_DATA);

        #endif

        #ifdef DENALI_CTL_461_DATA

        reg_write(DDR_BASE_ADDR+4*461,DENALI_CTL_461_DATA);

        #endif

        #ifdef DENALI_CTL_462_DATA

        reg_write(DDR_BASE_ADDR+4*462,DENALI_CTL_462_DATA);

        #endif

        #ifdef DENALI_CTL_463_DATA

        reg_write(DDR_BASE_ADDR+4*463,DENALI_CTL_463_DATA);

        #endif

        #ifdef DENALI_CTL_464_DATA

        reg_write(DDR_BASE_ADDR+4*464,DENALI_CTL_464_DATA);

        #endif

        #ifdef DENALI_CTL_465_DATA

        reg_write(DDR_BASE_ADDR+4*465,DENALI_CTL_465_DATA);

        #endif

        #ifdef DENALI_CTL_466_DATA

        reg_write(DDR_BASE_ADDR+4*466,DENALI_CTL_466_DATA);

        #endif

        #ifdef DENALI_CTL_467_DATA

        reg_write(DDR_BASE_ADDR+4*467,DENALI_CTL_467_DATA);

        #endif

        #ifdef DENALI_CTL_468_DATA

        reg_write(DDR_BASE_ADDR+4*468,DENALI_CTL_468_DATA);

        #endif

        #ifdef DENALI_CTL_469_DATA

        reg_write(DDR_BASE_ADDR+4*469,DENALI_CTL_469_DATA);

        #endif

        #ifdef DENALI_CTL_470_DATA

        reg_write(DDR_BASE_ADDR+4*470,DENALI_CTL_470_DATA);

        #endif

        #ifdef DENALI_CTL_471_DATA

        reg_write(DDR_BASE_ADDR+4*471,DENALI_CTL_471_DATA);

        #endif

        #ifdef DENALI_CTL_472_DATA

        reg_write(DDR_BASE_ADDR+4*472,DENALI_CTL_472_DATA);

        #endif

        #ifdef DENALI_CTL_473_DATA

        reg_write(DDR_BASE_ADDR+4*473,DENALI_CTL_473_DATA);

        #endif

        #ifdef DENALI_CTL_474_DATA

        reg_write(DDR_BASE_ADDR+4*474,DENALI_CTL_474_DATA);

        #endif

        #ifdef DENALI_CTL_475_DATA

        reg_write(DDR_BASE_ADDR+4*475,DENALI_CTL_475_DATA);

        #endif

        #ifdef DENALI_CTL_476_DATA

        reg_write(DDR_BASE_ADDR+4*476,DENALI_CTL_476_DATA);

        #endif

        #ifdef DENALI_CTL_477_DATA

        reg_write(DDR_BASE_ADDR+4*477,DENALI_CTL_477_DATA);

        #endif

        #ifdef DENALI_CTL_478_DATA

        reg_write(DDR_BASE_ADDR+4*478,DENALI_CTL_478_DATA);

        #endif

        #ifdef DENALI_CTL_479_DATA

        reg_write(DDR_BASE_ADDR+4*479,DENALI_CTL_479_DATA);

        #endif

        #ifdef DENALI_CTL_480_DATA

        reg_write(DDR_BASE_ADDR+4*480,DENALI_CTL_480_DATA);

        #endif

        #ifdef DENALI_CTL_481_DATA

        reg_write(DDR_BASE_ADDR+4*481,DENALI_CTL_481_DATA);

        #endif

        #ifdef DENALI_CTL_482_DATA

        reg_write(DDR_BASE_ADDR+4*482,DENALI_CTL_482_DATA);

        #endif

        #ifdef DENALI_CTL_483_DATA

        reg_write(DDR_BASE_ADDR+4*483,DENALI_CTL_483_DATA);

        #endif

        #ifdef DENALI_CTL_484_DATA

        reg_write(DDR_BASE_ADDR+4*484,DENALI_CTL_484_DATA);

        #endif

        #ifdef DENALI_CTL_485_DATA

        reg_write(DDR_BASE_ADDR+4*485,DENALI_CTL_485_DATA);

        #endif

        #ifdef DENALI_CTL_486_DATA

        reg_write(DDR_BASE_ADDR+4*486,DENALI_CTL_486_DATA);

        #endif

        #ifdef DENALI_CTL_487_DATA

        reg_write(DDR_BASE_ADDR+4*487,DENALI_CTL_487_DATA);

        #endif

        #ifdef DENALI_CTL_488_DATA

        reg_write(DDR_BASE_ADDR+4*488,DENALI_CTL_488_DATA);

        #endif

        #ifdef DENALI_CTL_489_DATA

        reg_write(DDR_BASE_ADDR+4*489,DENALI_CTL_489_DATA);

        #endif

        #ifdef DENALI_CTL_490_DATA

        reg_write(DDR_BASE_ADDR+4*490,DENALI_CTL_490_DATA);

        #endif

        #ifdef DENALI_CTL_491_DATA

        reg_write(DDR_BASE_ADDR+4*491,DENALI_CTL_491_DATA);

        #endif

        #ifdef DENALI_CTL_492_DATA

        reg_write(DDR_BASE_ADDR+4*492,DENALI_CTL_492_DATA);

        #endif

        #ifdef DENALI_CTL_493_DATA

        reg_write(DDR_BASE_ADDR+4*493,DENALI_CTL_493_DATA);

        #endif

        #ifdef DENALI_CTL_494_DATA

        reg_write(DDR_BASE_ADDR+4*494,DENALI_CTL_494_DATA);

        #endif

        #ifdef DENALI_CTL_495_DATA

        reg_write(DDR_BASE_ADDR+4*495,DENALI_CTL_495_DATA);

        #endif

        #ifdef DENALI_CTL_496_DATA

        reg_write(DDR_BASE_ADDR+4*496,DENALI_CTL_496_DATA);

        #endif

        #ifdef DENALI_CTL_497_DATA

        reg_write(DDR_BASE_ADDR+4*497,DENALI_CTL_497_DATA);

        #endif

        #ifdef DENALI_CTL_498_DATA

        reg_write(DDR_BASE_ADDR+4*498,DENALI_CTL_498_DATA);

        #endif

        #ifdef DENALI_CTL_499_DATA

        reg_write(DDR_BASE_ADDR+4*499,DENALI_CTL_499_DATA);

        #endif

        #ifdef DENALI_CTL_500_DATA

        reg_write(DDR_BASE_ADDR+4*500,DENALI_CTL_500_DATA);

        #endif

        #ifdef DENALI_CTL_501_DATA

        reg_write(DDR_BASE_ADDR+4*501,DENALI_CTL_501_DATA);

        #endif

        #ifdef DENALI_CTL_502_DATA

        reg_write(DDR_BASE_ADDR+4*502,DENALI_CTL_502_DATA);

        #endif

        #ifdef DENALI_CTL_503_DATA

        reg_write(DDR_BASE_ADDR+4*503,DENALI_CTL_503_DATA);

        #endif

        #ifdef DENALI_CTL_504_DATA

        reg_write(DDR_BASE_ADDR+4*504,DENALI_CTL_504_DATA);

        #endif

        #ifdef DENALI_CTL_505_DATA

        reg_write(DDR_BASE_ADDR+4*505,DENALI_CTL_505_DATA);

        #endif

        #ifdef DENALI_CTL_506_DATA

        reg_write(DDR_BASE_ADDR+4*506,DENALI_CTL_506_DATA);

        #endif

        #ifdef DENALI_CTL_507_DATA

        reg_write(DDR_BASE_ADDR+4*507,DENALI_CTL_507_DATA);

        #endif

        #ifdef DENALI_CTL_508_DATA

        reg_write(DDR_BASE_ADDR+4*508,DENALI_CTL_508_DATA);

        #endif

        #ifdef DENALI_CTL_509_DATA

        reg_write(DDR_BASE_ADDR+4*509,DENALI_CTL_509_DATA);

        #endif

        #ifdef DENALI_CTL_510_DATA

        reg_write(DDR_BASE_ADDR+4*510,DENALI_CTL_510_DATA);

        #endif

        #ifdef DENALI_CTL_511_DATA

        reg_write(DDR_BASE_ADDR+4*511,DENALI_CTL_511_DATA);

        #endif

        #ifdef DENALI_CTL_512_DATA

        reg_write(DDR_BASE_ADDR+4*512,DENALI_CTL_512_DATA);

        #endif

        #ifdef DENALI_CTL_513_DATA

        reg_write(DDR_BASE_ADDR+4*513,DENALI_CTL_513_DATA);

        #endif

        #ifdef DENALI_CTL_514_DATA

        reg_write(DDR_BASE_ADDR+4*514,DENALI_CTL_514_DATA);

        #endif

        #ifdef DENALI_CTL_515_DATA

        reg_write(DDR_BASE_ADDR+4*515,DENALI_CTL_515_DATA);

        #endif

        #ifdef DENALI_CTL_516_DATA

        reg_write(DDR_BASE_ADDR+4*516,DENALI_CTL_516_DATA);

        #endif

        #ifdef DENALI_CTL_517_DATA

        reg_write(DDR_BASE_ADDR+4*517,DENALI_CTL_517_DATA);

        #endif

        #ifdef DENALI_CTL_518_DATA

        reg_write(DDR_BASE_ADDR+4*518,DENALI_CTL_518_DATA);

        #endif

        #ifdef DENALI_CTL_519_DATA

        reg_write(DDR_BASE_ADDR+4*519,DENALI_CTL_519_DATA);

        #endif

        #ifdef DENALI_CTL_520_DATA

        reg_write(DDR_BASE_ADDR+4*520,DENALI_CTL_520_DATA);

        #endif

        #ifdef DENALI_CTL_521_DATA

        reg_write(DDR_BASE_ADDR+4*521,DENALI_CTL_521_DATA);

        #endif

        #ifdef DENALI_CTL_522_DATA

        reg_write(DDR_BASE_ADDR+4*522,DENALI_CTL_522_DATA);

        #endif

        #ifdef DENALI_CTL_523_DATA

        reg_write(DDR_BASE_ADDR+4*523,DENALI_CTL_523_DATA);

        #endif

        #ifdef DENALI_CTL_524_DATA

        reg_write(DDR_BASE_ADDR+4*524,DENALI_CTL_524_DATA);

        #endif

        #ifdef DENALI_CTL_525_DATA

        reg_write(DDR_BASE_ADDR+4*525,DENALI_CTL_525_DATA);

        #endif

        #ifdef DENALI_CTL_526_DATA

        reg_write(DDR_BASE_ADDR+4*526,DENALI_CTL_526_DATA);

        #endif

        #ifdef DENALI_CTL_527_DATA

        reg_write(DDR_BASE_ADDR+4*527,DENALI_CTL_527_DATA);

        #endif

        #ifdef DENALI_CTL_528_DATA

        reg_write(DDR_BASE_ADDR+4*528,DENALI_CTL_528_DATA);

        #endif

        #ifdef DENALI_CTL_529_DATA

        reg_write(DDR_BASE_ADDR+4*529,DENALI_CTL_529_DATA);

        #endif

        #ifdef DENALI_CTL_530_DATA

        reg_write(DDR_BASE_ADDR+4*530,DENALI_CTL_530_DATA);

        #endif

        #ifdef DENALI_CTL_531_DATA

        reg_write(DDR_BASE_ADDR+4*531,DENALI_CTL_531_DATA);

        #endif

        #ifdef DENALI_CTL_532_DATA

        reg_write(DDR_BASE_ADDR+4*532,DENALI_CTL_532_DATA);

        #endif

        #ifdef DENALI_CTL_533_DATA

        reg_write(DDR_BASE_ADDR+4*533,DENALI_CTL_533_DATA);

        #endif

        #ifdef DENALI_CTL_534_DATA

        reg_write(DDR_BASE_ADDR+4*534,DENALI_CTL_534_DATA);

        #endif

        #ifdef DENALI_CTL_535_DATA

        reg_write(DDR_BASE_ADDR+4*535,DENALI_CTL_535_DATA);

        #endif

        #ifdef DENALI_CTL_536_DATA

        reg_write(DDR_BASE_ADDR+4*536,DENALI_CTL_536_DATA);

        #endif

        #ifdef DENALI_CTL_537_DATA

        reg_write(DDR_BASE_ADDR+4*537,DENALI_CTL_537_DATA);

        #endif

        #ifdef DENALI_CTL_538_DATA

        reg_write(DDR_BASE_ADDR+4*538,DENALI_CTL_538_DATA);

        #endif

        #ifdef DENALI_CTL_539_DATA

        reg_write(DDR_BASE_ADDR+4*539,DENALI_CTL_539_DATA);

        #endif

        #ifdef DENALI_CTL_540_DATA

        reg_write(DDR_BASE_ADDR+4*540,DENALI_CTL_540_DATA);

        #endif

        #ifdef DENALI_CTL_541_DATA

        reg_write(DDR_BASE_ADDR+4*541,DENALI_CTL_541_DATA);

        #endif

        #ifdef DENALI_CTL_542_DATA

        reg_write(DDR_BASE_ADDR+4*542,DENALI_CTL_542_DATA);

        #endif

        #ifdef DENALI_CTL_543_DATA

        reg_write(DDR_BASE_ADDR+4*543,DENALI_CTL_543_DATA);

        #endif

        #ifdef DENALI_CTL_544_DATA

        reg_write(DDR_BASE_ADDR+4*544,DENALI_CTL_544_DATA);

        #endif

        #ifdef DENALI_CTL_545_DATA

        reg_write(DDR_BASE_ADDR+4*545,DENALI_CTL_545_DATA);

        #endif

        #ifdef DENALI_CTL_546_DATA

        reg_write(DDR_BASE_ADDR+4*546,DENALI_CTL_546_DATA);

        #endif

        #ifdef DENALI_CTL_547_DATA

        reg_write(DDR_BASE_ADDR+4*547,DENALI_CTL_547_DATA);

        #endif

        #ifdef DENALI_CTL_548_DATA

        reg_write(DDR_BASE_ADDR+4*548,DENALI_CTL_548_DATA);

        #endif

        #ifdef DENALI_CTL_549_DATA

        reg_write(DDR_BASE_ADDR+4*549,DENALI_CTL_549_DATA);

        #endif

        #ifdef DENALI_CTL_550_DATA

        reg_write(DDR_BASE_ADDR+4*550,DENALI_CTL_550_DATA);

        #endif

        #ifdef DENALI_CTL_551_DATA

        reg_write(DDR_BASE_ADDR+4*551,DENALI_CTL_551_DATA);

        #endif

        #ifdef DENALI_CTL_552_DATA

        reg_write(DDR_BASE_ADDR+4*552,DENALI_CTL_552_DATA);

        #endif

        #ifdef DENALI_CTL_553_DATA

        reg_write(DDR_BASE_ADDR+4*553,DENALI_CTL_553_DATA);

        #endif

        #ifdef DENALI_CTL_554_DATA

        reg_write(DDR_BASE_ADDR+4*554,DENALI_CTL_554_DATA);

        #endif

        #ifdef DENALI_CTL_555_DATA

        reg_write(DDR_BASE_ADDR+4*555,DENALI_CTL_555_DATA);

        #endif

        #ifdef DENALI_CTL_556_DATA

        reg_write(DDR_BASE_ADDR+4*556,DENALI_CTL_556_DATA);

        #endif

        #ifdef DENALI_CTL_557_DATA

        reg_write(DDR_BASE_ADDR+4*557,DENALI_CTL_557_DATA);

        #endif

        #ifdef DENALI_CTL_558_DATA

        reg_write(DDR_BASE_ADDR+4*558,DENALI_CTL_558_DATA);

        #endif

        #ifdef DENALI_CTL_559_DATA

        reg_write(DDR_BASE_ADDR+4*559,DENALI_CTL_559_DATA);

        #endif

        #ifdef DENALI_CTL_560_DATA

        reg_write(DDR_BASE_ADDR+4*560,DENALI_CTL_560_DATA);

        #endif

        #ifdef DENALI_CTL_561_DATA

        reg_write(DDR_BASE_ADDR+4*561,DENALI_CTL_561_DATA);

        #endif

        #ifdef DENALI_CTL_562_DATA

        reg_write(DDR_BASE_ADDR+4*562,DENALI_CTL_562_DATA);

        #endif

        #ifdef DENALI_CTL_563_DATA

        reg_write(DDR_BASE_ADDR+4*563,DENALI_CTL_563_DATA);

        #endif

        #ifdef DENALI_CTL_564_DATA

        reg_write(DDR_BASE_ADDR+4*564,DENALI_CTL_564_DATA);

        #endif

        #ifdef DENALI_CTL_565_DATA

        reg_write(DDR_BASE_ADDR+4*565,DENALI_CTL_565_DATA);

        #endif

        #ifdef DENALI_CTL_566_DATA

        reg_write(DDR_BASE_ADDR+4*566,DENALI_CTL_566_DATA);

        #endif

        #ifdef DENALI_CTL_567_DATA

        reg_write(DDR_BASE_ADDR+4*567,DENALI_CTL_567_DATA);

        #endif

        #ifdef DENALI_CTL_568_DATA

        reg_write(DDR_BASE_ADDR+4*568,DENALI_CTL_568_DATA);

        #endif

        #ifdef DENALI_CTL_569_DATA

        reg_write(DDR_BASE_ADDR+4*569,DENALI_CTL_569_DATA);

        #endif

        #ifdef DENALI_CTL_570_DATA

        reg_write(DDR_BASE_ADDR+4*570,DENALI_CTL_570_DATA);

        #endif

        #ifdef DENALI_CTL_571_DATA

        reg_write(DDR_BASE_ADDR+4*571,DENALI_CTL_571_DATA);

        #endif

        #ifdef DENALI_CTL_572_DATA

        reg_write(DDR_BASE_ADDR+4*572,DENALI_CTL_572_DATA);

        #endif

        #ifdef DENALI_CTL_573_DATA

        reg_write(DDR_BASE_ADDR+4*573,DENALI_CTL_573_DATA);

        #endif

        #ifdef DENALI_CTL_574_DATA

        reg_write(DDR_BASE_ADDR+4*574,DENALI_CTL_574_DATA);

        #endif

        #ifdef DENALI_CTL_575_DATA

        reg_write(DDR_BASE_ADDR+4*575,DENALI_CTL_575_DATA);

        #endif

        #ifdef DENALI_CTL_576_DATA

        reg_write(DDR_BASE_ADDR+4*576,DENALI_CTL_576_DATA);

        #endif

        #ifdef DENALI_CTL_577_DATA

        reg_write(DDR_BASE_ADDR+4*577,DENALI_CTL_577_DATA);

        #endif

        #ifdef DENALI_CTL_578_DATA

        reg_write(DDR_BASE_ADDR+4*578,DENALI_CTL_578_DATA);

        #endif

        #ifdef DENALI_CTL_579_DATA

        reg_write(DDR_BASE_ADDR+4*579,DENALI_CTL_579_DATA);

        #endif

        #ifdef DENALI_CTL_580_DATA

        reg_write(DDR_BASE_ADDR+4*580,DENALI_CTL_580_DATA);

        #endif

        #ifdef DENALI_CTL_581_DATA

        reg_write(DDR_BASE_ADDR+4*581,DENALI_CTL_581_DATA);

        #endif

        #ifdef DENALI_CTL_582_DATA

        reg_write(DDR_BASE_ADDR+4*582,DENALI_CTL_582_DATA);

        #endif

        #ifdef DENALI_CTL_583_DATA

        reg_write(DDR_BASE_ADDR+4*583,DENALI_CTL_583_DATA);

        #endif

        #ifdef DENALI_CTL_584_DATA

        reg_write(DDR_BASE_ADDR+4*584,DENALI_CTL_584_DATA);

        #endif

        #ifdef DENALI_CTL_585_DATA

        reg_write(DDR_BASE_ADDR+4*585,DENALI_CTL_585_DATA);

        #endif

        #ifdef DENALI_CTL_586_DATA

        reg_write(DDR_BASE_ADDR+4*586,DENALI_CTL_586_DATA);

        #endif

        #ifdef DENALI_CTL_587_DATA

        reg_write(DDR_BASE_ADDR+4*587,DENALI_CTL_587_DATA);

        #endif

        #ifdef DENALI_CTL_588_DATA

        reg_write(DDR_BASE_ADDR+4*588,DENALI_CTL_588_DATA);

        #endif

        #ifdef DENALI_CTL_589_DATA

        reg_write(DDR_BASE_ADDR+4*589,DENALI_CTL_589_DATA);

        #endif

        #ifdef DENALI_CTL_590_DATA

        reg_write(DDR_BASE_ADDR+4*590,DENALI_CTL_590_DATA);

        #endif

        #ifdef DENALI_CTL_591_DATA

        reg_write(DDR_BASE_ADDR+4*591,DENALI_CTL_591_DATA);

        #endif

        #ifdef DENALI_CTL_592_DATA

        reg_write(DDR_BASE_ADDR+4*592,DENALI_CTL_592_DATA);

        #endif

        #ifdef DENALI_CTL_593_DATA

        reg_write(DDR_BASE_ADDR+4*593,DENALI_CTL_593_DATA);

        #endif

        #ifdef DENALI_CTL_594_DATA

        reg_write(DDR_BASE_ADDR+4*594,DENALI_CTL_594_DATA);

        #endif

        #ifdef DENALI_CTL_595_DATA

        reg_write(DDR_BASE_ADDR+4*595,DENALI_CTL_595_DATA);

        #endif

        #ifdef DENALI_CTL_596_DATA

        reg_write(DDR_BASE_ADDR+4*596,DENALI_CTL_596_DATA);

        #endif

        #ifdef DENALI_CTL_597_DATA

        reg_write(DDR_BASE_ADDR+4*597,DENALI_CTL_597_DATA);

        #endif

        #ifdef DENALI_CTL_598_DATA

        reg_write(DDR_BASE_ADDR+4*598,DENALI_CTL_598_DATA);

        #endif

        #ifdef DENALI_CTL_599_DATA

        reg_write(DDR_BASE_ADDR+4*599,DENALI_CTL_599_DATA);

        #endif

        #ifdef DENALI_CTL_600_DATA

        reg_write(DDR_BASE_ADDR+4*600,DENALI_CTL_600_DATA);

        #endif

        #ifdef DENALI_CTL_601_DATA

        reg_write(DDR_BASE_ADDR+4*601,DENALI_CTL_601_DATA);

        #endif

        #ifdef DENALI_CTL_602_DATA

        reg_write(DDR_BASE_ADDR+4*602,DENALI_CTL_602_DATA);

        #endif

        #ifdef DENALI_CTL_603_DATA

        reg_write(DDR_BASE_ADDR+4*603,DENALI_CTL_603_DATA);

        #endif

        #ifdef DENALI_CTL_604_DATA

        reg_write(DDR_BASE_ADDR+4*604,DENALI_CTL_604_DATA);

        #endif

        #ifdef DENALI_CTL_605_DATA

        reg_write(DDR_BASE_ADDR+4*605,DENALI_CTL_605_DATA);

        #endif

        #ifdef DENALI_CTL_606_DATA

        reg_write(DDR_BASE_ADDR+4*606,DENALI_CTL_606_DATA);

        #endif

        #ifdef DENALI_CTL_607_DATA

        reg_write(DDR_BASE_ADDR+4*607,DENALI_CTL_607_DATA);

        #endif

        #ifdef DENALI_CTL_608_DATA

        reg_write(DDR_BASE_ADDR+4*608,DENALI_CTL_608_DATA);

        #endif

        #ifdef DENALI_CTL_609_DATA

        reg_write(DDR_BASE_ADDR+4*609,DENALI_CTL_609_DATA);

        #endif

        #ifdef DENALI_CTL_610_DATA

        reg_write(DDR_BASE_ADDR+4*610,DENALI_CTL_610_DATA);

        #endif

        #ifdef DENALI_CTL_611_DATA

        reg_write(DDR_BASE_ADDR+4*611,DENALI_CTL_611_DATA);

        #endif

        #ifdef DENALI_CTL_612_DATA

        reg_write(DDR_BASE_ADDR+4*612,DENALI_CTL_612_DATA);

        #endif

        #ifdef DENALI_CTL_613_DATA

        reg_write(DDR_BASE_ADDR+4*613,DENALI_CTL_613_DATA);

        #endif

        #ifdef DENALI_CTL_614_DATA

        reg_write(DDR_BASE_ADDR+4*614,DENALI_CTL_614_DATA);

        #endif

        #ifdef DENALI_CTL_615_DATA

        reg_write(DDR_BASE_ADDR+4*615,DENALI_CTL_615_DATA);

        #endif

        #ifdef DENALI_CTL_616_DATA

        reg_write(DDR_BASE_ADDR+4*616,DENALI_CTL_616_DATA);

        #endif

        #ifdef DENALI_CTL_617_DATA

        reg_write(DDR_BASE_ADDR+4*617,DENALI_CTL_617_DATA);

        #endif

        #ifdef DENALI_CTL_618_DATA

        reg_write(DDR_BASE_ADDR+4*618,DENALI_CTL_618_DATA);

        #endif

        #ifdef DENALI_CTL_619_DATA

        reg_write(DDR_BASE_ADDR+4*619,DENALI_CTL_619_DATA);

        #endif

        #ifdef DENALI_CTL_620_DATA

        reg_write(DDR_BASE_ADDR+4*620,DENALI_CTL_620_DATA);

        #endif

        #ifdef DENALI_CTL_621_DATA

        reg_write(DDR_BASE_ADDR+4*621,DENALI_CTL_621_DATA);

        #endif

        #ifdef DENALI_CTL_622_DATA

        reg_write(DDR_BASE_ADDR+4*622,DENALI_CTL_622_DATA);

        #endif

        #ifdef DENALI_CTL_623_DATA

        reg_write(DDR_BASE_ADDR+4*623,DENALI_CTL_623_DATA);

        #endif

        #ifdef DENALI_CTL_624_DATA

        reg_write(DDR_BASE_ADDR+4*624,DENALI_CTL_624_DATA);

        #endif

        #ifdef DENALI_CTL_625_DATA

        reg_write(DDR_BASE_ADDR+4*625,DENALI_CTL_625_DATA);

        #endif

        #ifdef DENALI_CTL_626_DATA

        reg_write(DDR_BASE_ADDR+4*626,DENALI_CTL_626_DATA);

        #endif

        #ifdef DENALI_CTL_627_DATA

        reg_write(DDR_BASE_ADDR+4*627,DENALI_CTL_627_DATA);

        #endif

        #ifdef DENALI_CTL_628_DATA

        reg_write(DDR_BASE_ADDR+4*628,DENALI_CTL_628_DATA);

        #endif

        #ifdef DENALI_CTL_629_DATA

        reg_write(DDR_BASE_ADDR+4*629,DENALI_CTL_629_DATA);

        #endif

        #ifdef DENALI_CTL_630_DATA

        reg_write(DDR_BASE_ADDR+4*630,DENALI_CTL_630_DATA);

        #endif

        #ifdef DENALI_CTL_631_DATA

        reg_write(DDR_BASE_ADDR+4*631,DENALI_CTL_631_DATA);

        #endif

        #ifdef DENALI_CTL_632_DATA

        reg_write(DDR_BASE_ADDR+4*632,DENALI_CTL_632_DATA);

        #endif

        #ifdef DENALI_CTL_633_DATA

        reg_write(DDR_BASE_ADDR+4*633,DENALI_CTL_633_DATA);

        #endif

        #ifdef DENALI_CTL_634_DATA

        reg_write(DDR_BASE_ADDR+4*634,DENALI_CTL_634_DATA);

        #endif

        #ifdef DENALI_CTL_635_DATA

        reg_write(DDR_BASE_ADDR+4*635,DENALI_CTL_635_DATA);

        #endif

        #ifdef DENALI_CTL_636_DATA

        reg_write(DDR_BASE_ADDR+4*636,DENALI_CTL_636_DATA);

        #endif

        #ifdef DENALI_CTL_637_DATA

        reg_write(DDR_BASE_ADDR+4*637,DENALI_CTL_637_DATA);

        #endif

        #ifdef DENALI_CTL_638_DATA

        reg_write(DDR_BASE_ADDR+4*638,DENALI_CTL_638_DATA);

        #endif

        #ifdef DENALI_CTL_639_DATA

        reg_write(DDR_BASE_ADDR+4*639,DENALI_CTL_639_DATA);

        #endif

        #ifdef DENALI_CTL_640_DATA

        reg_write(DDR_BASE_ADDR+4*640,DENALI_CTL_640_DATA);

        #endif

        #ifdef DENALI_CTL_641_DATA

        reg_write(DDR_BASE_ADDR+4*641,DENALI_CTL_641_DATA);

        #endif

        #ifdef DENALI_CTL_642_DATA

        reg_write(DDR_BASE_ADDR+4*642,DENALI_CTL_642_DATA);

        #endif

        #ifdef DENALI_CTL_643_DATA

        reg_write(DDR_BASE_ADDR+4*643,DENALI_CTL_643_DATA);

        #endif

        #ifdef DENALI_CTL_644_DATA

        reg_write(DDR_BASE_ADDR+4*644,DENALI_CTL_644_DATA);

        #endif

        #ifdef DENALI_CTL_645_DATA

        reg_write(DDR_BASE_ADDR+4*645,DENALI_CTL_645_DATA);

        #endif

        #ifdef DENALI_CTL_646_DATA

        reg_write(DDR_BASE_ADDR+4*646,DENALI_CTL_646_DATA);

        #endif

        #ifdef DENALI_CTL_647_DATA

        reg_write(DDR_BASE_ADDR+4*647,DENALI_CTL_647_DATA);

        #endif

        #ifdef DENALI_CTL_648_DATA

        reg_write(DDR_BASE_ADDR+4*648,DENALI_CTL_648_DATA);

        #endif

        #ifdef DENALI_CTL_649_DATA

        reg_write(DDR_BASE_ADDR+4*649,DENALI_CTL_649_DATA);

        #endif

        #ifdef DENALI_CTL_650_DATA

        reg_write(DDR_BASE_ADDR+4*650,DENALI_CTL_650_DATA);

        #endif

        #ifdef DENALI_CTL_651_DATA

        reg_write(DDR_BASE_ADDR+4*651,DENALI_CTL_651_DATA);

        #endif

        #ifdef DENALI_CTL_652_DATA

        reg_write(DDR_BASE_ADDR+4*652,DENALI_CTL_652_DATA);

        #endif

        #ifdef DENALI_CTL_653_DATA

        reg_write(DDR_BASE_ADDR+4*653,DENALI_CTL_653_DATA);

        #endif

        #ifdef DENALI_CTL_654_DATA

        reg_write(DDR_BASE_ADDR+4*654,DENALI_CTL_654_DATA);

        #endif

        #ifdef DENALI_CTL_655_DATA

        reg_write(DDR_BASE_ADDR+4*655,DENALI_CTL_655_DATA);

        #endif

        #ifdef DENALI_CTL_656_DATA

        reg_write(DDR_BASE_ADDR+4*656,DENALI_CTL_656_DATA);

        #endif

        #ifdef DENALI_CTL_657_DATA

        reg_write(DDR_BASE_ADDR+4*657,DENALI_CTL_657_DATA);

        #endif

        #ifdef DENALI_CTL_658_DATA

        reg_write(DDR_BASE_ADDR+4*658,DENALI_CTL_658_DATA);

        #endif

        #ifdef DENALI_CTL_659_DATA

        reg_write(DDR_BASE_ADDR+4*659,DENALI_CTL_659_DATA);

        #endif

        #ifdef DENALI_CTL_660_DATA

        reg_write(DDR_BASE_ADDR+4*660,DENALI_CTL_660_DATA);

        #endif

        #ifdef DENALI_CTL_661_DATA

        reg_write(DDR_BASE_ADDR+4*661,DENALI_CTL_661_DATA);

        #endif

        #ifdef DENALI_CTL_662_DATA

        reg_write(DDR_BASE_ADDR+4*662,DENALI_CTL_662_DATA);

        #endif

        #ifdef DENALI_CTL_663_DATA

        reg_write(DDR_BASE_ADDR+4*663,DENALI_CTL_663_DATA);

        #endif

        #ifdef DENALI_CTL_664_DATA

        reg_write(DDR_BASE_ADDR+4*664,DENALI_CTL_664_DATA);

        #endif

        #ifdef DENALI_CTL_665_DATA

        reg_write(DDR_BASE_ADDR+4*665,DENALI_CTL_665_DATA);

        #endif

        #ifdef DENALI_CTL_666_DATA

        reg_write(DDR_BASE_ADDR+4*666,DENALI_CTL_666_DATA);

        #endif

        #ifdef DENALI_CTL_667_DATA

        reg_write(DDR_BASE_ADDR+4*667,DENALI_CTL_667_DATA);

        #endif

        #ifdef DENALI_CTL_668_DATA

        reg_write(DDR_BASE_ADDR+4*668,DENALI_CTL_668_DATA);

        #endif

        #ifdef DENALI_CTL_669_DATA

        reg_write(DDR_BASE_ADDR+4*669,DENALI_CTL_669_DATA);

        #endif

        #ifdef DENALI_CTL_670_DATA

        reg_write(DDR_BASE_ADDR+4*670,DENALI_CTL_670_DATA);

        #endif

        #ifdef DENALI_CTL_671_DATA

        reg_write(DDR_BASE_ADDR+4*671,DENALI_CTL_671_DATA);

        #endif

        #ifdef DENALI_CTL_672_DATA

        reg_write(DDR_BASE_ADDR+4*672,DENALI_CTL_672_DATA);

        #endif

        #ifdef DENALI_CTL_673_DATA

        reg_write(DDR_BASE_ADDR+4*673,DENALI_CTL_673_DATA);

        #endif

        #ifdef DENALI_CTL_674_DATA

        reg_write(DDR_BASE_ADDR+4*674,DENALI_CTL_674_DATA);

        #endif

        #ifdef DENALI_CTL_675_DATA

        reg_write(DDR_BASE_ADDR+4*675,DENALI_CTL_675_DATA);

        #endif

        #ifdef DENALI_CTL_676_DATA

        reg_write(DDR_BASE_ADDR+4*676,DENALI_CTL_676_DATA);

        #endif

        #ifdef DENALI_CTL_677_DATA

        reg_write(DDR_BASE_ADDR+4*677,DENALI_CTL_677_DATA);

        #endif

        #ifdef DENALI_CTL_678_DATA

        reg_write(DDR_BASE_ADDR+4*678,DENALI_CTL_678_DATA);

        #endif

        #ifdef DENALI_CTL_679_DATA

        reg_write(DDR_BASE_ADDR+4*679,DENALI_CTL_679_DATA);

        #endif

        #ifdef DENALI_CTL_680_DATA

        reg_write(DDR_BASE_ADDR+4*680,DENALI_CTL_680_DATA);

        #endif

        #ifdef DENALI_CTL_681_DATA

        reg_write(DDR_BASE_ADDR+4*681,DENALI_CTL_681_DATA);

        #endif

        #ifdef DENALI_CTL_682_DATA

        reg_write(DDR_BASE_ADDR+4*682,DENALI_CTL_682_DATA);

        #endif

        #ifdef DENALI_CTL_683_DATA

        reg_write(DDR_BASE_ADDR+4*683,DENALI_CTL_683_DATA);

        #endif

        #ifdef DENALI_CTL_684_DATA

        reg_write(DDR_BASE_ADDR+4*684,DENALI_CTL_684_DATA);

        #endif

        #ifdef DENALI_CTL_685_DATA

        reg_write(DDR_BASE_ADDR+4*685,DENALI_CTL_685_DATA);

        #endif

        #ifdef DENALI_CTL_686_DATA

        reg_write(DDR_BASE_ADDR+4*686,DENALI_CTL_686_DATA);

        #endif

        #ifdef DENALI_CTL_687_DATA

        reg_write(DDR_BASE_ADDR+4*687,DENALI_CTL_687_DATA);

        #endif

        #ifdef DENALI_CTL_688_DATA

        reg_write(DDR_BASE_ADDR+4*688,DENALI_CTL_688_DATA);

        #endif

        #ifdef DENALI_CTL_689_DATA

        reg_write(DDR_BASE_ADDR+4*689,DENALI_CTL_689_DATA);

        #endif

        #ifdef DENALI_CTL_690_DATA

        reg_write(DDR_BASE_ADDR+4*690,DENALI_CTL_690_DATA);

        #endif

        #ifndef DENALI_PHY

            //==============================================================================

            //  Make Memory Controller configuration register changes here.

            //==============================================================================

            #ifdef TB_DDR3
            #else
                #ifdef TB_LPDDR3
                #else    //TB_LPDDR4
                    //  Memory Controller configuration changes for LPDDR4 memory
                    regdata = DENALI_CTL_653_DATA;
                    bit_set_field(regdata, 8, 8, 0x4); //changed by hyg from 0x5 to be 0x4
                    bit_set_field(regdata, 8, 0, 0x8);
                    reg_write(DDR_BASE_ADDR+4*653,regdata);

                    // regdata = DENALI_CTL_235_DATA;
                    // regdata[5:3] = 3'b001;
                    // regdata[2:0] = 3'b000;
                    // reg_write(DDR_BASE_ADDR+4*235,regdata);
                    regdata = DENALI_CTL_679_DATA;
                    // regdata[26:24] = 3'b010;                    //TDFI_PHY_WRDATA_F3
                    bit_set_field(regdata, 3, 24, 0x2);
                    // regdata[18:16] = 3'b010;                    //TDFI_PHY_WRDATA_F2
                    bit_set_field(regdata, 3, 16, 0x2);
                    // regdata[10:8]  = 3'b010;                    //TDFI_PHY_WRDATA_F1
                    bit_set_field(regdata, 3, 8, 0x2);
                    // regdata[2:0]   = 3'b010;                    //TDFI_PHY_WRDATA_F0
                    bit_set_field(regdata, 3, 0, 0x2);
                    reg_write(DDR_BASE_ADDR+4*679,regdata);

                    //  ODT Control .. disable ODT
                    regdata = DENALI_CTL_254_DATA;
                    // regdata[31:24] = 8'h00;                    //MR11_DATA was 0x3
                    bit_clr_bits(regdata, 8, 24);
                    reg_write(DDR_BASE_ADDR+4*254,regdata);

                    // regdata = DENALI_CTL_178_DATA;
                    // regdata[31:24] = 8'h08;                    //CKSRE_F0
                    // reg_write(DDR_BASE_ADDR+4*178,regdata);

                    regdata = DENALI_CTL_110_DATA;
                    // regdata[20:16] = 5'h1f;                    //tCKCKEL_F0  //modify by hyg
                    bit_set_bits(regdata, 5, 16);
                    reg_write(DDR_BASE_ADDR+4*110,regdata);

                    // twrlat dram we cmd to data?
                    // regdata = DENALI_CTL_48_DATA;
                    // regdata[14:8] = 7'h11;                    //WRLAT_F0 was 0x10
                    // reg_write(DDR_BASE_ADDR+4*48,regdata);

                    // 4/1/20  KAM added after state maching updates in RTL to increase delay
                    //between write2write commands....

                    regdata = DENALI_CTL_375_DATA;
                    // regdata[12:8] = 5'h06;                             //w2w_samecs_dly
                    bit_set_field(regdata, 5, 8, 0x06);
                    reg_write(DDR_BASE_ADDR+4*375,regdata);

                    regdata = DENALI_CTL_373_DATA;
                    // regdata[28:24] = 5'h04;                             //r2r_samecs_dly
                    bit_set_field(regdata, 5, 24, 0x04);
                    reg_write(DDR_BASE_ADDR+4*373,regdata);

                    // regdata = DENALI_CTL_375_DATA;
                    // regdata[4:0] = 5'h6;                    //W2R_SAMECS_DLY
                    // reg_write(DDR_BASE_ADDR+4*375,regdata);

                    regdata = DENALI_CTL_51_DATA;
                    // regdata[23:16] = 8'h14;                             //trrd_f0
                    bit_set_field(regdata, 8, 16, 0x14);
                    reg_write(DDR_BASE_ADDR+4*51,regdata);

                    // regdata = DENALI_CTL_329_DATA;
                    // regdata[8] = 1;                             //write dbi and read dbi enable
                    // regdata[16]= 1;
                    // reg_write(DDR_BASE_ADDR+4*329,regdata);
                    // r2w_samecs_dly

                    regdata = DENALI_CTL_374_DATA;
                    // regdata[4:0] = 5'hc;                    //
                    bit_set_field(regdata, 5, 0, 0xc);
                    reg_write(DDR_BASE_ADDR+4*374,regdata);

                    #ifdef DM_EN
                        regdata = DENALI_CTL_77_DATA;  //disable_memory_mask_write setting 1
                        //   regdata[8] = 0;
                        bit_clr_bit(regdata, 8);
                        reg_write(DDR_BASE_ADDR+4*77,regdata);
                        reg_read(DDR_BASE_ADDR+4*682,regdata);
                        //   regdata[16] = 0;  //disable_memory_mask_write setting 1
                        bit_clr_bit(regdata, 16);
                        reg_write(DDR_BASE_ADDR+4*682,regdata);
                    #endif

                    #ifdef BOF
                        //   REGREAD(682);
                        reg_read(DDR_BASE_ADDR+4*682,regdata);
                        // regdata[24] = 1;      //enable burst on the fly
                        bit_set_bit(regdata, 24);
                        reg_write(DDR_BASE_ADDR+4*682,regdata);
                    #endif

                    // regdata = DENALI_CTL_682_DATA;  //disable_memory_mask_write setting 1
                    // regdata[16] = 0;
                    // reg_write(DDR_BASE_ADDR+4*682,regdata);

                    //This is the end of the LPDDR4 section
                #endif   //TB_LPDDR3
            #endif   //TB_DDR3
        #else   ///DENALI_PHY

        #endif   //DENALI_PHY

        /**/

        //==============================================================================
        //==============================================================================

        //#ifndef PERF_EVAL
        // #define IN_ORDER_ACCEPT_OFFSET         16                   //
        // #define IN_ORDER_ACCEPT_WIDTH          1                    //
        // #define DISABLE_RW_GROUP_W_BNK_CONFLICT_OFFSET 8                    //
        // #define DISABLE_RW_GROUP_W_BNK_CONFLICT_WIDTH 2                    //
        // #define DISABLE_RW_GROUP_W_BNK_CONFLICT_ADDR    323                  //
        // #define IN_ORDER_ACCEPT_ADDR                    326                  //

        //  Force in-order accept to help guarantee this.
        // reg_read(DDR_BASE_ADDR+4*IN_ORDER_ACCEPT_ADDR,regdata);
        // regdata[IN_ORDER_ACCEPT_OFFSET+IN_ORDER_ACCEPT_WIDTH-1:IN_ORDER_ACCEPT_OFFSET]=1'b1;
        // bit_set_bit(regdata, 16);
        // reg_write(DDR_BASE_ADDR+4*IN_ORDER_ACCEPT_ADDR,regdata);

        //  Disable special R/W group switches so that R/W group placement is always
        //  at END of R/W group.
        // reg_read(DDR_BASE_ADDR+4*DISABLE_RW_GROUP_W_BNK_CONFLICT_ADDR,regdata);
        // regdata[DISABLE_RW_GROUP_W_BNK_CONFLICT_OFFSET+DISABLE_RW_GROUP_W_BNK_CONFLICT_WIDTH-1:DISABLE_RW_GROUP_W_BNK_CONFLICT_OFFSET]=1'b0;
        // bit_clr_bit(regdata, 8);
        // reg_write(DDR_BASE_ADDR+4*DISABLE_RW_GROUP_W_BNK_CONFLICT_ADDR,regdata) ;

        //#endif

        // #define DFIBUS_FREQ_INIT_OFFSET        24                   //
        // #define DFIBUS_FREQ_INIT_WIDTH         2                    //
        #define DFIBUS_FREQ_INIT_ADDR          29                   //

        //  Keep the init freq same as boot freq.
        reg_read(DDR_BASE_ADDR+4*DFIBUS_FREQ_INIT_ADDR,regdata) ;
        // regdata[DFIBUS_FREQ_INIT_OFFSET+DFIBUS_FREQ_INIT_WIDTH-1:DFIBUS_FREQ_INIT_OFFSET]=DFIBUS_FREQ_INIT_WIDTH'h0;
        bit_clr_bits(regdata, 2, 24);
        reg_write(DDR_BASE_ADDR+4*DFIBUS_FREQ_INIT_ADDR, regdata);

        /////    *****************************************************************
        /////    *****************************************************************
        ////   *****************  ADDED from latest SOC team reg_init.v file  1/28/20
        // disable refreshes while the dfi_phymstr_req and dfi_phymstr_ack signals are  asserted
        regdata=DENALI_CTL_161_DATA;
        //    regdata[24] =1'b1;
        bit_set_bit(regdata, 24);
        reg_write(DDR_BASE_ADDR+4*161,regdata);

        // disable automatic controller-initiated update on the DFI interface
        regdata=DENALI_CTL_327_DATA;
        //    regdata[16] =1'b0;
        bit_clr_bit(regdata, 16);
        reg_write(DDR_BASE_ADDR+4*327,regdata);
        /////    *****************************************************************
        /////    *****************************************************************
        /////    *****************************************************************

        // No auto mrr init
        // Disable MRR commands during initialization/ set 1 to disable
        // reg_read(`DDR_BASE_ADDR+4*27,regdata);
        reg_read(DDR_BASE_ADDR+4*27, regdata);
        // regdata[24]=1;
        bit_clr_bit(regdata, 24);
        // reg_write(`DDR_BASE_ADDR+4*27,regdata);
        reg_write(DDR_BASE_ADDR+4*27, regdata);

        // #define START_OFFSET                   24                   //
        // #define START_WIDTH                    1                    //
        #define START_ADDR                     0                    //

        reg_read(DDR_BASE_ADDR+4*START_ADDR,regdata);
        // regdata[START_OFFSET+START_WIDTH-1:START_OFFSET] = START_WIDTH'b1;
        bit_set_bit(regdata, 24);
        reg_write(DDR_BASE_ADDR+4*START_ADDR,regdata);

    // #3us;
    #endif  //DFI_AGENT

    // dump_ddrphy_regs();
    // reg_read(DDR_BASE_ADDR+4*641,regdata);
    // debug("DENALY_CTRL_641 0x%08X\n", regdata);

    while(1)
    {
        udelay(50);
        regdata = readl(DDR_BASE_ADDR + 4 * 338);
        if((regdata & 0x200))
            break;
    }

    Read_Gate_training();

    return 0;
}
