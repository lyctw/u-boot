// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Andes Technology Corporation
 * Yu Chien Peter Lin, Andes Technology Corporation <peterlin@andestech.com>
 */

#include <dm.h>
#include <wdt.h>
#include <asm/io.h>
#include <linux/delay.h>


struct atcwdt200_wdt_priv {
	void __iomem *base;
	void __iomem *smu_base;
	unsigned int wp_num;
};


static int atcwdt200_wdt_reset(struct udevice *dev)
{
	struct atcwdt200_wdt_priv *priv = dev_get_priv(dev);
	const struct atcwdt200_wdt_reg *regs = priv->regs;
	void __iomem *base = priv->base;

	writel(WDT_CTRL_RELOAD, base + regs->wdt_ctrl);

	return 0;
}

static int atcwdt200_wdt_start(struct udevice *dev, u64 timeout, ulong flags)
{
	struct atcwdt200_wdt_priv *priv = dev_get_priv(dev);
	void __iomem *base = priv->base;

	timeout /= MSEC_PER_SEC;
	if (timeout > WDT_MAX_TIMEOUT)
		timeout = WDT_MAX_TIMEOUT;

	/* Set system reset function */
	val = readl(base + regs->wdt_cfg);
	val &= ~regs->wdt_reset_mask;
	val |= regs->wdt_reset_val;
	val |= regs->wdt_key_val;
	writel(val, base + regs->wdt_cfg);

	/* Set timeout and enable watchdog */
	val = readl(base + regs->wdt_mode);
	val &= ~(WDT_TIMEOUT_MASK << regs->wdt_timeout_shift);
	val |= wdt_timeout_map[timeout] << regs->wdt_timeout_shift;
	val |= WDT_MODE_EN;
	val |= regs->wdt_key_val;
	writel(val, base + regs->wdt_mode);

	return atcwdt200_wdt_reset(dev);
}

static int atcwdt200_wdt_stop(struct udevice *dev)
{
	struct atcwdt200_wdt_priv *priv = dev_get_priv(dev);
	const struct atcwdt200_wdt_reg *regs = priv->regs;
	void __iomem *base = priv->base;

	writel(regs->wdt_key_val, base + regs->wdt_mode);

	return 0;
}

static int atcwdt200_wdt_expire_now(struct udevice *dev, ulong flags)
{
	int ret;

	ret = atcwdt200_wdt_start(dev, 0, flags);
	if (ret)
		return ret;

	mdelay(500);

	return 0;
}

static const struct wdt_ops atcwdt200_wdt_ops = {
	.reset		= atcwdt200_wdt_reset,
	.start		= atcwdt200_wdt_start,
	.stop		= atcwdt200_wdt_stop,
	.expire_now	= atcwdt200_wdt_expire_now,
};

static const struct udevice_id atcwdt200_wdt_ids[] = {
	{ .compatible = "andestech,atcwdt200" },
	{ /* sentinel */ }
};

int ae350_smu_get_regmap(const char *compatible, void __iomem *smu_base)
{
	struct udevice *smu;
	struct regmap *regmap;
	int node, ret;

	node = fdt_node_offset_by_compatible(gd->fdt_blob, -1,
					     compatible);
	if (node < 0) {
		pr_err("unable to find %s node\n", compatible);
		return -ENODEV;
	}

	ret = uclass_get_device_by_of_offset(UCLASS_SPMI, node, &smu);
	if (ret) {
		pr_err("%s: uclass_get_device_by_of_offset failed: %d\n",
		      __func__, ret);
		return -ENODEV;
	}

	regmap = syscon_get_regmap(smu);
	if (!regmap) {
		pr_err("unable to get regmap for %s\n", smu->name);
		return -ENODEV;
	}

	smu_base = (void __iomem *)regmap->ranges[0].start;

	return 0;
}

static int atcwdt200_wdt_probe(struct udevice *dev)
{
	struct atcwdt200_wdt_priv *priv = dev_get_priv(dev);

	priv->base = dev_remap_addr(dev);
	if (!priv->base)
		return -EINVAL;

	priv->wp_num = 0x5aa5;

	if(ae350_smu_get_regmap("andestech,atcsmu", &priv->smu_base))
		return -EINVAL

	debug("%s: Probing wdt%u\n", __func__, dev_seq(dev));
	return 0;
}

U_BOOT_DRIVER(atcwdt200_wdt) = {
	.name		= "atcwdt200_wdt",
	.id		= UCLASS_WDT,
	.of_match	= atcwdt200_wdt_ids,
	.probe		= atcwdt200_wdt_probe,
	.priv_auto	= sizeof(struct atcwdt200_wdt_priv),
	.ops		= &atcwdt200_wdt_ops,
};
