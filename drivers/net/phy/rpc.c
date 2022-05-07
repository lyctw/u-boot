// SPDX-License-Identifier: GPL-2.0+
/*
 * rpc8211 PHY drivers
 *
 * Base code from drivers/net/phy/smsc.c
 */

#include <common.h>
#include <miiphy.h>

#define PHY_SPEC_STATUS_REG	0x11
#define MMD_ACCESS_CTL_REG	0x0D
#define MMD_ACCESS_DAT_REG	0x0E
#define EXT_ADDR_REG		0x1E
#define EXT_DATA_REG		0x1F
#define LED_GEN_CFG_REG		0xA00B
#define LED0_CFG_REG		0xA00C
#define LED1_CFG_REG		0xA00D
#define LED2_CFG_REG		0xA00E
#define LED_BLINK_CFG_REG	0xA00F


static int rpc_readext(struct phy_device *phydev, int addr, int devad, int reg)
{
	int val;

	phy_write(phydev, MDIO_DEVAD_NONE, EXT_ADDR_REG, reg);
	val = phy_read(phydev, MDIO_DEVAD_NONE, EXT_DATA_REG);

	return val;
}

static int rpc_writeext(struct phy_device *phydev, int addr, int devad, int reg, u16 val)
{
	phy_write(phydev, MDIO_DEVAD_NONE, EXT_ADDR_REG, reg);
	phy_write(phydev, MDIO_DEVAD_NONE, EXT_DATA_REG, val);

	return 0;
}

static int rpc_read_mmd(struct phy_device *phydev, int devad, int reg)
{
	int val;

	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_CTL_REG, devad & 0x1F);
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_DAT_REG, reg);
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_CTL_REG, 0x4000 | (devad & 0x1F));
	val = phy_read(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_DAT_REG);
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_CTL_REG, 0);

	return val;
}

static int rpc_write_mmd(struct phy_device *phydev, int devad, int reg, u16 val)
{
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_CTL_REG, devad & 0x1F);
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_DAT_REG, reg);
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_CTL_REG, 0x4000 | (devad & 0x1F));
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_DAT_REG, val);
	phy_write(phydev, MDIO_DEVAD_NONE, MMD_ACCESS_CTL_REG, 0);

	return 0;
}

static int rpc_update_link(struct phy_device *phydev)
{
	unsigned int mii_reg;

	/*
	 * Wait if the link is up, and autonegotiation is in progress
	 * (ie - we're capable and it's not done)
	 */
	mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMSR);

	/*
	 * If we already saw the link up, and it hasn't gone down, then
	 * we don't need to wait for autoneg again
	 */
	if (phydev->link && mii_reg & BMSR_LSTATUS)
		return 0;

	if ((phydev->autoneg == AUTONEG_ENABLE) &&
	    !(mii_reg & BMSR_ANEGCOMPLETE)) {
		int i = 0;

		printf("%s Waiting for PHY auto negotiation to complete",
		       phydev->dev->name);
		while (!(mii_reg & BMSR_ANEGCOMPLETE)) {
			/*
			 * Timeout reached ?
			 */
			if (i > PHY_ANEG_TIMEOUT) {
				printf(" TIMEOUT !\n");
				phydev->link = 0;
				return -ETIMEDOUT;
			}

			if (ctrlc()) {
				puts("user interrupt!\n");
				phydev->link = 0;
				return -EINTR;
			}

			if ((i++ % 10) == 0)
				printf(".");

			mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
			if (!(mii_reg & BMCR_ANENABLE))
				phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, BMCR_ANENABLE | BMCR_ANRESTART);

			mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMSR);
			mdelay(50);	/* 50 ms */
		}
		printf(" done\n");
		phydev->link = 1;
	} else {
		/* Read the link a second time to clear the latched state */
		mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMSR);

		if (mii_reg & BMSR_LSTATUS)
			phydev->link = 1;
		else
			phydev->link = 0;
	}

	return 0;
}

static int rpc_parse_status(struct phy_device *phydev)
{
	int mii_reg;

	mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, PHY_SPEC_STATUS_REG);
	phydev->speed = SPEED_10 * (mii_reg >> 14);
	phydev->duplex = (mii_reg >> 13) & 1;

	return 0;
}

static int rpc_startup(struct phy_device *phydev)
{
	int ret;

	ret = rpc_update_link(phydev);
	if (ret)
		return ret;

	return rpc_parse_status(phydev);
}

static int rpc_config(struct phy_device *phydev)
{
	rpc_writeext(phydev, phydev->addr, MDIO_DEVAD_NONE, LED1_CFG_REG, 0x0060);
	rpc_writeext(phydev, phydev->addr, MDIO_DEVAD_NONE, LED2_CFG_REG, 0x2600);

	phy_write(phydev, MDIO_DEVAD_NONE, 0x04, 0x1DE1);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x07, 0x2801);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x09, 0x0200);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x10, 0x0062);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x14, 0x082C);
	phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, BMCR_ANENABLE | BMCR_ANRESTART);

	return 0;
}

static struct phy_driver rpc8211fs_driver = {
	.name = "RPCOM RPC8211FS",
	.uid = 0x0000011A,
	.mask = 0xffff0,
	.features = PHY_BASIC_FEATURES | SUPPORTED_1000baseT_Full |
		SUPPORTED_Pause | SUPPORTED_Asym_Pause,
	.config = &rpc_config,
	.startup = &rpc_startup,
	.shutdown = &genphy_shutdown,
	.readext = &rpc_readext,
	.writeext = &rpc_writeext,
	.read_mmd = &rpc_read_mmd,
	.write_mmd = &rpc_write_mmd,
};

int phy_rpc_init(void)
{
	phy_register(&rpc8211fs_driver);

	return 0;
}
