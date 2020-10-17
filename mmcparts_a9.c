#include <string.h>
#include "mmcparts_a9.h"

//int mmc_partition_tbl_checksum_calc(struct partitions *part, int part_num);

void init_parts() 
{
    memset(&g_mmcparts, 0, sizeof(struct mmc_partitions_fmt));
    strcpy(g_mmcparts.magic, MMC_PARTITIONS_MAGIC);

    struct partitions logo;
    strcpy(logo.name, "logo");
    logo.size = 0x800000;
    logo.offset = 0x2800000;
    logo.mask_flags = 0x1;

    struct partitions recovery;
    strcpy(recovery.name, "recovery");
    recovery.size = 0x1800000;
    recovery.offset = logo.offset + logo.size;
    recovery.mask_flags = 0x1;

    struct partitions misc;
    strcpy(misc.name, "misc");
    misc.size = 0x800000;
    misc.offset = recovery.offset + recovery.size;
    misc.mask_flags = 0x1;

    struct partitions dtbo;
    strcpy(dtbo.name, "dtbo");
    dtbo.size = 0x800000;
    dtbo.offset = misc.offset + misc.size;
    dtbo.mask_flags = 0x1;

    struct partitions cri_data;
    strcpy(cri_data.name, "cri_data");
    cri_data.size = 0x800000;
    cri_data.offset = dtbo.offset + dtbo.size;
    cri_data.mask_flags = 0x1;

    struct partitions rsv;
    strcpy(rsv.name, "rsv");
    rsv.size = 0x1000000;
    rsv.offset = cri_data.offset + cri_data.size;
    rsv.mask_flags = 0x1;

    struct partitions metadata;
    strcpy(metadata.name, "metadata");
    metadata.size = 0x1000000;
    metadata.offset = rsv.offset + rsv.size;
    metadata.mask_flags = 0x1;

    struct partitions vbmeta;
    strcpy(vbmeta.name, "vbmeta");
    vbmeta.size = 0x200000;
    vbmeta.offset = metadata.offset + metadata.size;
    vbmeta.mask_flags = 0x1;

    struct partitions param;
    strcpy(param.name, "param");
    param.size = 0x1000000;
    param.offset = vbmeta.offset + vbmeta.size;
    param.mask_flags = 0x1;

    struct partitions boot;
    strcpy(boot.name, "boot");
    boot.size = 0x1000000;
    boot.offset = param.offset + param.size;
    boot.mask_flags = 0x1;

    struct partitions tee;
    strcpy(tee.name, "tee");
    tee.size = 0x2000000;
    tee.offset = boot.offset + boot.size;
    tee.mask_flags = 0x1;

    struct partitions vendor;
    strcpy(vendor.name, "vendor");
    vendor.size = 0x14000000;
    vendor.offset = tee.offset + tee.size;
    vendor.mask_flags = 0x1;

    struct partitions odm;
    strcpy(odm.name, "odm");
    odm.size = 0x8000000;
    odm.offset = vendor.offset + vendor.size;
    odm.mask_flags = 0x1;

    struct partitions system;
    strcpy(system.name, "system");
    system.size = 0x62c00000;
    system.offset = odm.offset + odm.size;
    system.mask_flags = 0x1;

    struct partitions product;
    strcpy(product.name, "product");
    product.size = 0x8000000;
    product.offset = system.offset + system.size;
    product.mask_flags = 0x1;

    struct partitions cache;
    strcpy(cache.name, "cache");
    cache.size = 0x46000000;
    cache.offset = product.offset + product.size;
    cache.mask_flags = 0x2;

    struct partitions data;
    strcpy(data.name, "data");
    //data.size = 0xffffffff;
    //data.size = 3470 * SZ_1M;
    data.size = 0xe2c00000;
    data.offset = cache.offset + cache.size;
    data.mask_flags = 0x4;

    /*struct partitions ;
    strcpy(.name, "");
    .size = 0x800000;
    .offset = 0;
    .mask_flags = 0x1;*/

    struct partitions mmc_parts[] = { logo, recovery, misc, dtbo, cri_data, rsv,
	metadata, vbmeta, param, boot, tee, vendor, odm, system, product, cache, data };

    int mmc_parts_count = 17;

    for(int i = 0; i < mmc_parts_count; i++) 
    {
	g_mmcparts.partitions[i] = mmc_parts[i];
    }
    g_mmcparts.part_num = mmc_parts_count;
    g_mmcparts.checksum = mmc_partition_tbl_checksum_calc(mmc_parts, mmc_parts_count);
}

int mmc_partition_tbl_checksum_calc(struct partitions *part, int part_num)
{
    int i, j;
    uint32_t checksum = 0, *p;

    for (i = 0; i < part_num; i++) {
	p = (uint32_t *)part;

	for (j = sizeof(struct partitions)/sizeof(checksum);
		j > 0; j--) {
	    checksum += *p;
	    p++;
	}
    }

    return checksum;
}