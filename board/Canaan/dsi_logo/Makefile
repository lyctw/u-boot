# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (C) 2017 Andes Technology Corporation.
# Rick Chen, Andes Technology Corporation <rick@andestech.oom>

EXTRA_CFLAGS += -D_EVBLP3 -I${src}/bsp/include   \
				-I${src}/bsp/include/controler \
				-I${src}/bsp/include/cpu -I${src}/bsp/include/utils \
				-I${src}/test/device_driver/pcal6416  -I${src}/test/log 

obj-y	:=  \
 test/log/main.o \
 bsp/controler/muxpin.o \
 bsp/controler/gpio.o \
 bsp/controler/video/mipi/dphy/mipi_rxdphy.o \
 bsp/controler/video/mipi/dphy/mipi_txdphy.o \
 test/log/vo/vo.o \
 test/log/vo/vo_app.o \
 test/log/debug.o \
 bsp/cpu/sleep.o \
 bsp/controler/i2c.o \
 test/log/hw_dev/src/ext_ctl_hw.o \
 test/log/hw_dev/src/display_hardware_init.o \
 test/log/hw_dev/src/lt9611.o \
 test/log/vo/vo_calc.o \
 bsp/controler/spi.o \
 bsp/cpu/cache.o \
 bsp/cpu/interrupt.o \
 test/log/ws2812/ws2812.o \
 bsp/cpu/k510.o \
 bsp/utils/utils.o \
 bsp/controler/video/mipi/dphy/mipi_corner.o \
 bsp/controler/video/vo/core/vo_core_drv.o \
 bsp/controler/video/vo/core/vo_core_reg.o \
 bsp/controler/dmac.o \
 bsp/controler/video/vo/remap/vo_remap_drv.o \
 bsp/controler/video/vo/remap/vo_remap_reg.o \
 bsp/controler/video/vo/table/vo_table_drv.o \
 bsp/controler/sysctl_rst.o \
 bsp/controler/video/vo/table/vo_table_coeff.o \
 bsp/controler/video/mipi/dsi/cnds_dsi_test.o \
 bsp/controler/video/mipi/dsi/cnds_dsi_hw.o \
 test/device_driver/pcal6416/pcal6416.o 

 



