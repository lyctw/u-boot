// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 Stefan Roese <sr@denx.de>
 *
 * Derived from drivers/mtd/nand/spi/micron.c
 *   Copyright (c) 2016-2017 Micron Technology, Inc.
 */

#ifndef __UBOOT__
#include <linux/device.h>
#include <linux/kernel.h>
#endif
#include <linux/mtd/spinand.h>

#define SPINAND_MFR_GIGADEVICE			0xC8
#define GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS	(1 << 4)
#define GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS	(3 << 4)

#define GD5FXGQ4XEXXG_REG_STATUS2		0xf0

#define GD5FXGQ4UXFXXG_STATUS_ECC_MASK          (7 << 4)
#define GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFLIPS   (0 << 4)
#define GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFLIPS  (1 << 4)
#define GD5FXGQ4UXFXXG_STATUS_ECC_UNCOR_ERROR   (7 << 4)

#define GD5FXGQ4XBXXG_STATUS_ECC_MASK           (0xF)
#define GD5FXGQ4XBXXG_STATUS_ECC_UNCOR_ERROR    (0x2)
#define GD5FXGQ4XBXXG_STATUS_ECC_8_BITFLIPS     (0x3)

static SPINAND_OP_VARIANTS(gd5fxgq4xbxxg_read_cache_variants,
    SPINAND_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 1, NULL, 0),
    SPINAND_PAGE_READ_FROM_CACHE_X4_OP(0, 1, NULL, 0),
    SPINAND_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, NULL, 0),
    SPINAND_PAGE_READ_FROM_CACHE_X2_OP(0, 1, NULL, 0),
    SPINAND_PAGE_READ_FROM_CACHE_OP(true, 0, 1, NULL, 0),
    SPINAND_PAGE_READ_FROM_CACHE_OP(false, 0, 1, NULL, 0));

static SPINAND_OP_VARIANTS(gd5fxgq4xbxxg_update_cache_variants,
    SPINAND_PROG_LOAD_QUADIO_OP(0, NULL, 0),
    SPINAND_PROG_LOAD_X4(false, 0, NULL, 0),
    SPINAND_PROG_LOAD(false, 0, NULL, 0));

static SPINAND_OP_VARIANTS(read_cache_variants,
		SPINAND_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 2, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_X4_OP(0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_X2_OP(0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_OP(true, 0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_OP(false, 0, 1, NULL, 0));

static SPINAND_OP_VARIANTS(write_cache_variants,
		SPINAND_PROG_LOAD_X4(true, 0, NULL, 0),
		SPINAND_PROG_LOAD(true, 0, NULL, 0));

static SPINAND_OP_VARIANTS(update_cache_variants,
		SPINAND_PROG_LOAD_X4(false, 0, NULL, 0),
		SPINAND_PROG_LOAD(false, 0, NULL, 0));

static int gd5fxgq4xexxg_ooblayout_ecc(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *region)
{
	if (section)
		return -ERANGE;

	region->offset = 64;
	region->length = 64;

	return 0;
}

static int gd5fxgq4xexxg_ooblayout_free(struct mtd_info *mtd, int section,
					struct mtd_oob_region *region)
{
	if (section)
		return -ERANGE;

	/* Reserve 1 bytes for the BBM. */
	region->offset = 1;
	region->length = 63;

	return 0;
}

static int gd5fxgq4xexxg_ecc_get_status(struct spinand_device *spinand,
					u8 status)
{
	u8 status2;
	struct spi_mem_op op = SPINAND_GET_FEATURE_OP(GD5FXGQ4XEXXG_REG_STATUS2,
						      &status2);
	int ret;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS:
		/*
		 * Read status2 register to determine a more fine grained
		 * bit error status
		 */
		ret = spi_mem_exec_op(spinand->slave, &op);
		if (ret)
			return ret;

		/*
		 * 4 ... 7 bits are flipped (1..4 can't be detected, so
		 * report the maximum of 4 in this case
		 */
		/* bits sorted this way (3...0): ECCS1,ECCS0,ECCSE1,ECCSE0 */
		return ((status & STATUS_ECC_MASK) >> 2) |
			((status2 & STATUS_ECC_MASK) >> 4);

	case GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS:
		return 8;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	default:
		break;
	}

	return -EINVAL;
}

static const struct mtd_ooblayout_ops gd5fxgq4xexxg_ooblayout = {
	.ecc = gd5fxgq4xexxg_ooblayout_ecc,
	.free = gd5fxgq4xexxg_ooblayout_free,
};

static int gd5fxgq4xbxxg_ecc_get_status(struct spinand_device *spinand,
                                        u8 status)
{
    uint8_t mask = (status >> 4) & GD5FXGQ4XBXXG_STATUS_ECC_MASK;
    if (mask & 0x3) {
        if ((mask & 0x3) == GD5FXGQ4XBXXG_STATUS_ECC_UNCOR_ERROR) {
            return -EBADMSG;
        }
        else if ((mask & 0x3) == GD5FXGQ4XBXXG_STATUS_ECC_8_BITFLIPS) {
            return 8;
        }
        else {
            return (mask >> 2) + 4; // 4-7 bit errors were detected and corrected
        }
    }
    else {
        return 0;
    }

    return -EINVAL;

}

static const struct spinand_info gigadevice_spinand_table[] = {
	SPINAND_INFO("GD5F1GQ4UExxG", 0xd1,
		     NAND_MEMORG(1, 2048, 128, 64, 1024, 1, 1, 1),
		     NAND_ECCREQ(8, 512),
		     SPINAND_INFO_OP_VARIANTS(&gd5fxgq4xbxxg_read_cache_variants,
					      &write_cache_variants,
					      &gd5fxgq4xbxxg_update_cache_variants),
		     0,
		     SPINAND_ECCINFO(&gd5fxgq4xexxg_ooblayout,
				     gd5fxgq4xexxg_ecc_get_status)),
        SPINAND_INFO("GD5F1GQ4RBxIG", 0xC1,
                     NAND_MEMORG(1, 2048, 128, 64, 1024, 1, 1, 1),
                     NAND_ECCREQ(8, 512),
                     SPINAND_INFO_OP_VARIANTS(&gd5fxgq4xbxxg_read_cache_variants,
                                              &write_cache_variants,
                                              &gd5fxgq4xbxxg_update_cache_variants),
                     0,
                     SPINAND_ECCINFO(&gd5fxgq4xexxg_ooblayout,
                                     gd5fxgq4xbxxg_ecc_get_status)),
};

#if 0
static int gigadevice_spinand_detect(struct spinand_device *spinand)
{
	u8 *id = spinand->id.data;
	int ret;

	/*
	 * For GD NANDs, There is an address byte needed to shift in before IDs
	 * are read out, so the first byte in raw_id is dummy.
	 */
	if (id[1] != SPINAND_MFR_GIGADEVICE)
		return 0;

	ret = spinand_match_and_init(spinand, gigadevice_spinand_table,
				     ARRAY_SIZE(gigadevice_spinand_table),
				     id[2]);
	if (ret)
		return ret;

	return 1;
}
#endif

static int gigadevice_spinand_detect(struct spinand_device *spinand)
{
        u8 *id = spinand->id.data;
        u16 did;
        int ret;

        /*
         * Earlier GDF5-series devices (A,E) return [0][MID][DID]
         * Later (F) devices return [MID][DID1][DID2]
         */
        printf("gigadevice_spinand_detect: %x %x %x %x\n", id[0], id[1], id[2], id[3]);

        if (id[0] == SPINAND_MFR_GIGADEVICE){
                if (id[1] == 0xC1)
                    did = id[1];
                else
                    did = (id[1] << 8) + id[2];
        }
        else if (id[0] == 0 && id[1] == SPINAND_MFR_GIGADEVICE)
                did = id[2];
        else
                return 0;

        ret = spinand_match_and_init(spinand, gigadevice_spinand_table,
                                     ARRAY_SIZE(gigadevice_spinand_table),
                                     did);
        if (ret)
                return ret;

        return 1;
}

static const struct spinand_manufacturer_ops gigadevice_spinand_manuf_ops = {
	.detect = gigadevice_spinand_detect,
};

const struct spinand_manufacturer gigadevice_spinand_manufacturer = {
	.id = SPINAND_MFR_GIGADEVICE,
	.name = "GigaDevice",
	.ops = &gigadevice_spinand_manuf_ops,
};
