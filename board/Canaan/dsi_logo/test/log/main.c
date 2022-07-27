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
#include "controler/sysctl_clk.h"
#include "controler/sysctl_boot.h"
#include "hw_dev/inc/display_hardware_init.h"
#include "vo/vo.h"
#include "ws2812/ws2812.h"


void SYSCTL_DRV_Init(void)
{
    //1. init csi pix clk
    //a. enable clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_0_PIXEL, TRUE);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_1_PIXEL, TRUE);
    
    //b. set pix clk to 74.25M by default
    sysctl_clk_set_leaf_div(SYSCTL_CLK_CSI_0_PIXEL,1, 8);
    sysctl_clk_set_leaf_div(SYSCTL_CLK_CSI_1_PIXEL,1, 8);

    //2. init csi system clk    
    //a. enable clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_0_SYSTEM, TRUE);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_1_SYSTEM, TRUE);
    
    //b. set system clk to 166M by default
    sysctl_clk_set_leaf_div(SYSCTL_CLK_CSI_0_SYSTEM,1, 2);
    sysctl_clk_set_leaf_div(SYSCTL_CLK_CSI_1_SYSTEM,1, 2);

    //3. init dsi pix clk    
    //a. enable clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISPLAY_PIXEL, TRUE);
    
    //b. set pix clk to 74.25M by default
    sysctl_clk_set_leaf_div(SYSCTL_CLK_DISPLAY_PIXEL,1, 8);   /// p30 594 / 8   594 / 4 = 148.5 p60  
    
    //4. init dsi system clk    
    //a. enable clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM, TRUE);
    
    //b. set system clk to 166M by default, all display subsystem apb clk will be set to 166M together.
    sysctl_clk_set_leaf_div(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV,1, 2);

    //5. init tpg pix clk
    //a. enable clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_TPG_PIXEL, TRUE);
    
    //b. set tpg pix clk to 594/5=118.8M by default
    sysctl_clk_set_leaf_div(SYSCTL_CLK_TPG_PIXEL,1, 5);

    //6. enable video subsystem apb and axi clk
    //enable video apb clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_0_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_1_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_2_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_3_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_F2K_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_R2K_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TOF_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VI_APB, 1);
    

    //enable video axi clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VI_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_AXI, 1); 

    //7. enable display subsystem apb and axi clk
    //enable display apb clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB, 1);

    //enable display axi clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VO_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
}
/*
*
*/

void fill_ddr(void)
{
#if 1
        int cnt=0;
        for(cnt = 0;cnt < 0x30000;cnt=cnt+4)
        {
            *(volatile unsigned int *)(0x01000000 + cnt) = 0x33333333;
            usleep(1);
            *(volatile unsigned int *)(0x02000000 + cnt) = 0x33333333;
    
        }    
#endif

}


#define DSI_LOG_LOAD_CMD_SD "ext2load mmc 1:2 0x1fe00000 /etc/uboot_dsi_logo.gbr.bmp.argb"
#define DSI_LOG_LOAD_CMD_EMMC "ext2load mmc 0:3 0x1fe00000 /etc/uboot_dsi_logo.gbr.bmp.argb"

int load_dsi_logo_to_ddr()
{
	// mmc read file to ddr
	//tftpboot 0xxxx a.bin;
	//fatload mmc 1:1 0x600000 bootm-bbl.img ;
	char *pcmd = DSI_LOG_LOAD_CMD_EMMC;
	sysctl_boot_mode_e boot_media = sysctl_boot_get_boot_mode();
	
		
	if(  boot_media == SYSCTL_BOOT_SDCARD ){
		pcmd = DSI_LOG_LOAD_CMD_SD;
	}
		
	run_command(pcmd, 0);

	return 0;
}

int main_logo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned long time;

	*(uint32_t *)0x970E00FC = 0x0fffff00;// (0x2 << 8) | (0x2 << 12) | (0x2 << 16) | (0x2 << 20) | (0x2 << 24);
	*(uint32_t *)0x970E0100 = 0x000000ff;// (0x3 << 4) | 0x3;
	*(uint32_t *)0x970E00F4 = 0x00550000;// (0x5 << 16) | (0x5 << 20);

	load_dsi_logo_to_ddr();
	printf("dsi logo start");
	time = get_timer(0);

    // hardware init
    display_gpio_init();


    SYSCTL_DRV_Init();
    
    mipi_rxdphy_init(RXDPHY_SPEED_MODE_1500M, RXDPHY_CHCFG_1X4);

    mipi_txdphy_init();

    VO_DRV_Init();

    VO_TEST_VideoOut(VO_DSI_MIPI_BRINGUP);

	time = get_timer(time);
	printf("dsi logo end use %lu msec\n", time);
    return 0;

}

DECLARE_GLOBAL_DATA_PTR;
ulong board_get_usable_ram_top(ulong total_size)
{
#ifdef CONFIG_SYS_SDRAM_BASE
	/*
	 * Detect whether we have so much RAM that it goes past the end of our
	 * 32-bit address space. If so, clip the usable RAM so it doesn't.
	 */
	if (gd->ram_top < CONFIG_SYS_SDRAM_BASE)
		/*
		 * Will wrap back to top of 32-bit space when reservations
		 * are made.
		 */
		return 0;
#endif
	return gd->ram_top - 0x200000;
}                                                   

#define WS2812_PIN 122

static void ws2812_init(void)
{
    ws2812_info *ws_info;
    ws2812_init_spi(WS2812_PIN);
    ws_info = ws2812_get_buf(1);
    ws2812_set_data(ws_info, 0, NONE);
    ws2812_send_data_spi(ws_info);
}

int board_late_init(void)
{
    ws2812_init();
	main_logo(0,0,0,0);
	return 0;
}


U_BOOT_CMD(
	wjx_logo,   2,   1,     main_logo,
	"logo dsi",
	"logo dsi\n"
	"    - enable, disable, or flush data (writethrough) cache"
);

