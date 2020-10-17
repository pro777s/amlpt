#ifndef _MMC_PARTS_A9_H
#define _MMC_PARTS_A9_H

#include "mmcpart.h"

void init_parts();
int mmc_partition_tbl_checksum_calc(struct partitions *part, int part_num);

#endif