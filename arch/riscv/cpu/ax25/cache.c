// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 */

#include <common.h>
#include <cache.h>
#include <cpu_func.h>
#include <dm.h>

void enable_caches(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_CACHE,
					  DM_DRIVER_GET(v5l2_cache),
					  &dev);
	if (ret) {
		log_debug("Cannot enable v5l2 cache\n");
	} else {
		ret = cache_enable(dev);
		if (ret)
			log_debug("v5l2 cache enable failed\n");
	}
}
