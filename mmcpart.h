#ifndef _EMMC_PARTITIONS_H
#define _EMMC_PARTITIONS_H

#include <stdint.h>

#define     MAX_PART_NAME_LEN               16
#define     MAX_MMC_PART_NUM                32

/* MMC Partition Table */
#define     MMC_PARTITIONS_MAGIC            "MPT"
#define     MMC_RESERVED_NAME               "reserved"

#define     SZ_1M                           0x00100000

/* the size of bootloader partition */
#define     MMC_BOOT_PARTITION_SIZE         (4*SZ_1M)

/* the size of reserve space behind bootloader partition */
#define     MMC_BOOT_PARTITION_RESERVED     (32*SZ_1M)

#define     RESULT_OK                       0
#define     RESULT_FAIL                     1


struct partitions {
    /* identifier string */
    char name[MAX_PART_NAME_LEN];
    /* partition size, byte unit */
    uint64_t size;
    /* offset within the master space, byte unit */
    uint64_t offset;
    /* master flags to mask out for this partition */
    unsigned mask_flags;
};

struct mmc_partitions_fmt {
    char magic[4];
    unsigned char version[12];
    int part_num;
    int checksum;
    struct partitions partitions[MAX_MMC_PART_NUM];
};

struct mmc_partitions_fmt g_mmcparts;

#endif