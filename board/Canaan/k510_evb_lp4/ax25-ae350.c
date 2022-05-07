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

#include "sysctl_clk.h"

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

void sysctl_enable_all_leaf_clk()
{
	sysctl_clk_node_e node;
	uint32_t freq = 0;

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

}

/*
 * Miscellaneous platform dependent initializations
 */

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM_0 + 0x400;

//	sysctl_enable_all_leaf_clk();
	iomux_init();
	return 0;
}

int dram_init(void)
{
	ddr_init();
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
