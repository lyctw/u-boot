// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 */

#include <common.h>
#if defined(CONFIG_FTMAC100) && !defined(CONFIG_DM_ETH)
#include <netdev.h>
#endif
#include <linux/io.h>
#include <faraday/ftsmc020.h>
#include <fdtdec.h>
#include <dm.h>
#include <spl.h>
#include "sysctl_boot.h"
#include "sysctl_clk.h"

#include <env.h>
#include <env_internal.h>

DECLARE_GLOBAL_DATA_PTR;

extern phys_addr_t prior_stage_fdt_address;

/*yangguang: add iomux_init*/
void iomux_init(void)
{
  volatile uint32_t* iomux_reg = (void*)0x97040000;
//  volatile uint32_t* iomux_reg = (void*)0x97050000;
  int i;
  printf("yangguang: iomux_init \n");
//  for(i = 0; i < 200; i++)
  for(i = 7; i < 127; i++)
  {
      iomux_reg[i] = 0xFF0C00;
  }

}

void sysctl_enable_all_leaf_clk(void)
{
	sysctl_clk_node_e node;
	uint32_t freq = 0;
	uint32_t i;
	uint32_t *i2c_icclk_cfg_base = 0x970010b8;

	for(node = SYSCTL_CLK_AX25M_SRC; node < SYSCTL_CLK_NODE_MAX; node ++)
	{
		sysctl_clk_set_leaf_en(node,true);
	}

	sysctl_clk_set_leaf_en(SYSCTL_CLK_GNNE_SYS,false);
        sysctl_clk_set_leaf_en(SYSCTL_CLK_GNNE_AXI,false);

        sysctl_boot_set_root_clk_freq(SYSCTL_CLK_ROOT_PLL1, 63, 0, 0);

        sysctl_clk_set_leaf_parent(SYSCTL_CLK_GNNE_SYS, SYSCTL_CLK_ROOT_PLL1_DIV_2);
        sysctl_clk_set_leaf_parent(SYSCTL_CLK_GNNE_AXI, SYSCTL_CLK_ROOT_PLL1_DIV_2);

        sysctl_clk_set_leaf_div(SYSCTL_CLK_GNNE_SYS,3,6);
        sysctl_clk_set_leaf_en(SYSCTL_CLK_GNNE_SYS,true);

        freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_GNNE_SYS);
        printf("GNNE sys clock freq changed: %d \r\n", freq);

        sysctl_clk_set_leaf_div(SYSCTL_CLK_GNNE_AXI,3,6);
        sysctl_clk_set_leaf_en(SYSCTL_CLK_GNNE_AXI,true);

        freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_GNNE_AXI);
        printf("GNNE AXI clock freq changed: %d \r\n", freq);

        writel(0x0f000f00,(void *)0x97001000);//792M
		//writel(0x0f000f60,(void *)0x97001000);//396M
        // writel(0x0f000f10,(void *)0x97001000);		//726M

        printf("CPU freq %d MHZ\n", sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25M_SRC) / 1000000);

	/*set i2c clock to 12.5MHZ, as workaround of the i2c timedout issue*/
	for(i=0;i<7;i++)
	    *(uint32_t *)(i2c_icclk_cfg_base + i*4) = 0x1000301;

	/* set spi0 clk to 250MHZ(spi_0_ssiclk_sel: 1(PLL0 1GHZ) , spi_0_ssiclk_div: 3(1/4 division)) */
	*(uint32_t *)0x97001074 = 0x3000031;

}

/*
 * Miscellaneous platform dependent initializations
 */
extern uint32_t ddr_training_task(void);
extern int lpddr3_init_training(void);

static int display_boot_media(void)
{
	char *env_file_name = NULL;
	char *boot_media_name = NULL;

	sysctl_boot_mode_e boot_media = sysctl_boot_get_boot_mode();
	switch (boot_media)
	{
	case SYSCTL_BOOT_DOWNLOAD:
		env_file_name = "none";
		boot_media_name = "download";
		break;
	case SYSCTL_BOOT_SDCARD:
		env_file_name = "uboot-sd.env";
		boot_media_name = "sdcard";
		break;
	case SYSCTL_BOOT_FLASH:
		env_file_name = "uboot-nand.env";
		boot_media_name = "nand";
		break;
	case SYSCTL_BOOT_EMMC:
		env_file_name = "uboot-emmc.env";
		boot_media_name = "emmc";
		break;
	default:
		env_file_name = "unknown";
		boot_media_name = "unknown";
		break;
	}

	printf("\n\nboot_media = %s %s\n\n", boot_media_name ,env_file_name);
	return 0;
}

enum env_location env_get_location(enum env_operation op, int prio)
{
        sysctl_boot_mode_e boot_media = sysctl_boot_get_boot_mode();

	if (prio)
                return ENVL_UNKNOWN;

        switch (boot_media) {
        case SYSCTL_BOOT_DOWNLOAD:
		return ENVL_UNKNOWN;
        case SYSCTL_BOOT_SDCARD:
        case SYSCTL_BOOT_EMMC:
                return ENVL_FAT;
        case SYSCTL_BOOT_FLASH:
                return ENVL_SPINAND;

	default:
                return ENVL_NOWHERE;
        }

}


int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM_0 + 0x400;

	display_boot_media();

	sysctl_enable_all_leaf_clk();
	iomux_init();

        *(uint32_t *)0x970E00FC = (0x2 << 8) | (0x2 << 12) | (0x2 << 16) | (0x2 << 20) | (0x2 << 24);
        *(uint32_t *)0x970E0100 = (0x3 << 4) | 0x3;
        *(uint32_t *)0x970E00F4 = (0x5 << 16) | (0x5 << 20);

	return 0;
}

int dram_init(void)
{
	// ddr_init();
	lpddr3_init_training();
	ddr_training_task();
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

#if defined(CONFIG_FTMAC100) && !defined(CONFIG_DM_ETH)
int board_eth_init(bd_t *bd)
{
	return ftmac100_initialize(bd);
}
#endif

ulong board_flash_get_legacy(ulong base, int banknum, flash_info_t *info)
{
	return 0;
}

void *board_fdt_blob_setup(void)
{
	return (void *)CONFIG_SYS_FDT_BASE;
}

int smc_init(void)
{
	int node = -1;
	const char *compat = "andestech,atfsmc020";
	void *blob = (void *)gd->fdt_blob;
	fdt_addr_t addr;
	struct ftsmc020_bank *regs;

	node = fdt_node_offset_by_compatible(blob, -1, compat);
	if (node < 0)
		return -FDT_ERR_NOTFOUND;

	addr = fdtdec_get_addr(blob, node, "reg");

	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	regs = (struct ftsmc020_bank *)addr;
	regs->cr &= ~FTSMC020_BANK_WPROT;

	return 0;
}

static void v5l2_init(void)
{
	struct udevice *dev;

	uclass_get_device(UCLASS_CACHE, 0, &dev);
}

#ifdef CONFIG_BOARD_EARLY_INIT_F
int board_early_init_f(void)
{
	smc_init();
	v5l2_init();

	return 0;
}
#endif

#ifdef CONFIG_SPL
void board_boot_order(u32 *spl_boot_list)
{
	u8 i;
	u32 boot_devices[] = {
#ifdef CONFIG_SPL_RAM_SUPPORT
		BOOT_DEVICE_RAM,
#endif
#ifdef CONFIG_SPL_MMC_SUPPORT
		BOOT_DEVICE_MMC1,
#endif
	};

	for (i = 0; i < ARRAY_SIZE(boot_devices); i++)
		spl_boot_list[i] = boot_devices[i];
}
#endif

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* boot using first FIT config */
	return 0;
}
#endif

#ifdef FAT_ENV_DEV_PART_DYNMIC
#define FAT_ENV_PART_SD "1:1"
#define FAT_ENV_PART_EMMC "0:2"
char * fat_get_env_dev_and_part_dynamic(void )
{
        char *dev_part_str = FAT_ENV_PART_EMMC;
        sysctl_boot_mode_e boot_media = sysctl_boot_get_boot_mode();


        if(  boot_media == SYSCTL_BOOT_SDCARD ){
                dev_part_str = FAT_ENV_PART_SD;
        }
        //printf("boot_media=%x %s\n", boot_media ,dev_part_str);
        return dev_part_str;
}

#define ENV_FAT_FILE_SD "uboot-sd.env"
#define ENV_FAT_FILE_EMMC "uboot-emmc.env"

char * fat_get_env_file_name_dynamic(void)
{
        char *env_file_name = ENV_FAT_FILE_EMMC;
        sysctl_boot_mode_e boot_media = sysctl_boot_get_boot_mode();

        if(  boot_media == SYSCTL_BOOT_SDCARD ){
            env_file_name = ENV_FAT_FILE_SD;
        }

        //printf("boot_media=%x %s\n", boot_media ,env_file_name);
        return env_file_name;
}
//CONFIG_LAST_STAGE_INIT
int last_stage_init(void)
{
	run_command("mii write 0 0x1e 0xa003; mii write  0 0x1f 0x01 ;", 0);
}

#ifdef CONFIG_RESET_PHY_R 
#include "gpio.h"
#include "muxpin.h"
void	reset_phy     (void)
{

	muxpin_set_function(31, FUNC_GPIO18);
	gpio_set_drive_mode(18, GPIO_DM_OUTPUT);//GPIO_DM_OUTPUT
	gpio_set_pin(18, GPIO_PV_LOW);//GPIO_PV_LOW
	mdelay(20);
	gpio_set_pin(18, GPIO_PV_HIGH);//GPIO_PV_HIGH
	udelay(10);
	gpio_set_pin(18, GPIO_PV_LOW);//GPIO_PV_LOW
	mdelay(20);
	gpio_set_pin(18, GPIO_PV_HIGH);//GPIO_PV_HIGH
	mdelay(200);
	return 0;
}
#endif 
#endif


