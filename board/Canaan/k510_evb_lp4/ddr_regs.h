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
#ifndef _DDR_REG_H
#define _DDR_REG_H

#define DDRC_REGS_BASE 0x98000000
#define DDR_BASE_ADDR  0x98000000
#define DDR_PHY_REGS_OFF 0x1000

/*DDR controller registers*/
#define DENALI_CTL_245 245
#define DENALI_CTL_339 339
#define DENALI_CTL_346 346
#define DENALI_CTL_212 212
#define DENALI_CTL_213 213
#define DENALI_CTL_214 214
#define DENALI_CTL_215 215
#define DENALI_CTL_190 190
#define DENALI_CTL_078 78

/*DDR PHY registers*/
#define PLL_CTRL1_ADDR       0x000   // cfg word addresses
#define PLL_CTRL2_ADDR       0x004
#define PLL_DLL_CTRL1_ADDR   0x008
#define DLL_CTRL1_ADDR       0x00C
#define DLL_CTRL2_ADDR       0x010
#define DLL_CTRL3_ADDR       0x014
#define DLL_CTRL4_ADDR       0x018
#define DLL_CTRL5_ADDR       0x01C
#define DLL_CTRL6_ADDR       0x020
#define DLL_CTRL7_ADDR       0x024
#define DLL_CTRL8_ADDR       0x028
#define DLL_CTRL9_ADDR       0x02C
#define DLL_CTRL10_ADDR      0x030
#define DLL_CTRL11_ADDR      0x034
#define DLL_CTRL12_ADDR      0x038
#define DLL_CTRL13_ADDR      0x03C
#define DLL_CTRL14_ADDR      0x040
#define DLL_CTRL15_ADDR      0x044
#define DLL_CTRL16_ADDR      0x048
#define DLL_CTRL17_ADDR      0x04C
#define DLL_CTRL18_ADDR      0x050
#define DLL_CTRL19_ADDR      0x054
#define DLL_CTRL20_ADDR      0x058
#define DLL_CTRL21_ADDR      0x05C
#define DLL_CTRL22_ADDR      0x060
#define RGDLY_ADDR           0x064
#define RGDLY_ADJ_ADDR       0x068
#define IO_CAL0_ADDR         0x06C
#define DSX8_IO_CTRL_ADDR    0x070
#define CAX10_IO_CTRL_ADDR   0x074
#define PHY_CFG_ADDR         0x078
#define PHY_DSDIS_ADDR       0x07C
#define TRAINING_CTRL1_ADDR  0x080
#define TRAINING_CTRL2_ADDR  0x084
#define TRAINING_CTRL3_ADDR  0x088
#define TRAINING_CTRL4_ADDR  0x08C
#define TRAINING_CTRL5_ADDR  0x090
#define TRAINING_CTRL6_ADDR  0x094
#define CADQ_ADDR            0x098
#define RBURST_0_P0_ADDR     0x09C
#define RBURST_0_P1_ADDR     0x0A0
#define RBURST_0_P2_ADDR     0x0A4
#define RBURST_0_P3_ADDR     0x0A8
#define RBURST_1_P0_ADDR     0x0AC
#define RBURST_1_P1_ADDR     0x0B0
#define RBURST_1_P2_ADDR     0x0B4
#define RBURST_1_P3_ADDR     0x0B8
#define BIT_RDLY_DS0_ADDR    0x0BC
#define BIT_WDLY_DS0_ADDR    0x0C0
#define BIT_RDLY_DS1_ADDR    0x0C4
#define BIT_WDLY_DS1_ADDR    0x0C8
#define BIT_RDLY_DS2_ADDR    0x0CC
#define BIT_WDLY_DS2_ADDR    0x0D0
#define BIT_RDLY_DS3_ADDR    0x0D4
#define BIT_WDLY_DS3_ADDR    0x0D8
#define BIT_WDLY_CA0_ADDR    0x0DC
#define BIT_WDLY_CA1_ADDR    0x0E0
#define BIT_WDLY_CA2_ADDR    0x0E4
#define BIT_WDLY_CACK_ADDR   0x0E8
#define DQS_DRIFT_GAIN_ADDR  0x0EC
#define DQS_DRIFT_CFG_ADDR   0x0F0
#define DQS_DRIFT_COR_ADDR   0x0F4
#define DQS_DRIFT_COR_EXT_ADDR   0x0F8
#define INTERRUPT_MASK_ADDR    0x0FC
#define INTERRUPT_STATUS_ADDR  0x100
#define BIST_CTRL1_ADDR       0x104
#define BIST_CTRL2_ADDR       0x108
#define BIST_STATUS1_ADDR     0x10C
#define BIST_STATUS2_ADDR     0x110
#define LP_STATUS_CTRL_ADDR   0x114
#define RDQS_DETC_CNTR_ADDR   0x118
#define SPARE_ADDR            0x11c

//sysctl for low power function
#define SYSCTL_START_ADDR    0x97000000
#define MEM_CTL_DFS_CFG     SYSCTL_START_ADDR+0x116C
#define MEM_CTL_CMD_FIFO    SYSCTL_START_ADDR+0x1160
#define MEM_CTL_CLK_CFG     SYSCTL_START_ADDR+0x1168
#define PLL3_CFG0           SYSCTL_START_ADDR+0x0030
#define PLL3_CTL            SYSCTL_START_ADDR+0x0038
#define PLL3_STAT           SYSCTL_START_ADDR+0x003c
#define INT2_RAW            SYSCTL_START_ADDR+0x00b0
#define MCTL_PWR_CTL        SYSCTL_START_ADDR+0x30f0
#define MCTL_PWR_STAT       SYSCTL_START_ADDR+0x30f8
#define PLL3_CFG1           SYSCTL_START_ADDR+0x0034
#define MCTL_RST_CTL        SYSCTL_START_ADDR+0x20f4
#define MCTL_RST_TIM        SYSCTL_START_ADDR+0x20f0
#define PHY_RST_CTL         SYSCTL_START_ADDR+0x2198

//mailbox control
#define MAILBOX_BASE 0x970E0000
#define DDR_WCOBUF  MAILBOX_BASE +0xf0
#define DDR_INIT_COMPLETE  MAILBOX_BASE +0x164
#endif