# SPDX-License-Identifier: GPL-2.0+

dtb-$(CONFIG_TARGET_AX25_AE350) += ae350_32.dtb ae350_64.dtb
dtb-$(CONFIG_TARGET_K510_EVB_LP3_V1_0) += k510_evb_lp3_v1_0.dtb
dtb-$(CONFIG_TARGET_K510_EVB_LP3_V1_1) += k510_evb_lp3_v1_1.dtb
dtb-$(CONFIG_TARGET_K510_EVB_LP4) += k510_evb_lp4.dtb
dtb-$(CONFIG_TARGET_K510_CRB_LP3_V0_1) += k510_crb_lp3_v0_1.dtb
dtb-$(CONFIG_TARGET_K510_CRB_LP3_V1_2) += k510_crb_lp3_v1_2.dtb
dtb-$(CONFIG_TARGET_SIFIVE_FU540) += hifive-unleashed-a00.dtb

targets += $(dtb-y)

DTC_FLAGS += -R 4 -p 0x1000

PHONY += dtbs
dtbs: $(addprefix $(obj)/, $(dtb-y))
	@:

clean-files := *.dtb
