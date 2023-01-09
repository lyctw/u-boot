// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2023 Andes Technology Corporation
 */
#include <common.h>
#include <asm/encoding.h>
#include <asm/sbi.h>
#include <asm/arch-andes/sbi.h>

long sbi_andes_get_cache_ctl_status(void)
{
	struct sbiret ret;

	ret = sbi_ecall(SBI_EXT_ANDES, SBI_EXT_ANDES_GET_MCACHE_CTL_STATUS, 0, 0, 0, 0, 0, 0);

	if (!ret.error)
		if (ret.value)
			return ret.value;

	return -ENOTSUPP;
}

void sbi_andes_enable_icache(void)
{
	sbi_ecall(SBI_EXT_ANDES, SBI_EXT_ANDES_ICACHE_OP, 1, 0, 0, 0, 0, 0);
}

void sbi_andes_disable_icache(void)
{
	sbi_ecall(SBI_EXT_ANDES, SBI_EXT_ANDES_ICACHE_OP, 0, 0, 0, 0, 0, 0);
}

void sbi_andes_enable_dcache(void)
{
	sbi_ecall(SBI_EXT_ANDES, SBI_EXT_ANDES_DCACHE_OP, 1, 0, 0, 0, 0, 0);
}

void sbi_andes_disable_dcache(void)
{
	sbi_ecall(SBI_EXT_ANDES, SBI_EXT_ANDES_DCACHE_OP, 0, 0, 0, 0, 0, 0);
}

void sbi_andes_dcache_wbinval_all(void)
{
	sbi_ecall(SBI_EXT_ANDES, SBI_EXT_ANDES_DCACHE_WBINVAL_ALL, 0, 0, 0, 0, 0, 0);
}
