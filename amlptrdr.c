#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "mmcparts_a9.h"

int read_mmcparts();
int mmc_verify_partition_tbl(struct mmc_partitions_fmt *pt_fmt);
int show_mmc_partitions(struct mmc_partitions_fmt *pt_fmt);
  
int main() 
{ 
    read_mmcparts();
    int ret = mmc_verify_partition_tbl(&g_mmcparts);
    show_mmc_partitions(&g_mmcparts);

    return 0; 
}
  
int read_mmcparts() 
{ 
  
    // pointer to FILE 
    FILE* fmp; 
  
    // Creates a file "demo_file" 
    // with file acccess as write-plus mode 
    fmp = fopen("mmc_parts.bin", "r"); 
  
    // read content from the file 
    fread(&g_mmcparts, sizeof(struct mmc_partitions_fmt), 1, fmp);
  
    // closes the file pointed by demo 
    fclose(fmp); 
  
    return 0; 
}


int mmc_verify_partition_tbl(struct mmc_partitions_fmt *pt_fmt)
{
    int ret = 0;

    if ((strncmp(pt_fmt->magic,
		MMC_PARTITIONS_MAGIC,
		sizeof(pt_fmt->magic)) == 0) /* the same */
	    && (pt_fmt->part_num > 0)
	    && (pt_fmt->part_num <= MAX_MMC_PART_NUM)
	    && (pt_fmt->checksum ==
		mmc_partition_tbl_checksum_calc(
		    pt_fmt->partitions,
		    pt_fmt->part_num))) {

	ret = 0; /* everything is OK now */

    } else {
	if (strncmp(pt_fmt->magic, MMC_PARTITIONS_MAGIC,
		    sizeof(pt_fmt->magic)) != 0) {

	    printf("magic error: %s\n",
		    (pt_fmt->magic)?pt_fmt->magic:"NULL");

	} else if ((pt_fmt->part_num < 0)
		|| (pt_fmt->part_num > MAX_MMC_PART_NUM)) {

	    printf("partition number error: %d\n",
		    pt_fmt->part_num);

	} else {
	    printf(
		"checksum error: pt_fmt->checksum=%d,calc_result=%d\n",
		pt_fmt->checksum,
		mmc_partition_tbl_checksum_calc(
		    pt_fmt->partitions,
		    pt_fmt->part_num));
	}

	printf("[%s]: partition verified error\n", __func__);
	ret = -1; /* the partition information is invalid */
    }

    printf("[%s] mmc read partition %s!\n",
	    __func__, (ret == 0) ? "OK" : "ERROR");

    return ret;
}

int show_mmc_partitions(struct mmc_partitions_fmt *pt_fmt)
{
    unsigned int i;
    //struct hd_struct *ret = NULL;
    uint64_t offset, size, cap;
    struct partitions *pp;

    printf("show_mmc_partitions\n");

    cap = 16777216;// 8Gb //get_capacity(disk); /* unit:512 bytes */
    for (i = 0; i < pt_fmt->part_num; i++) {
	pp = &(pt_fmt->partitions[i]);
	offset = pp->offset >> 9; /* unit:512 bytes */
	size = pp->size >> 9; /* unit:512 bytes */
	if ((offset + size) <= cap) {
	    //ret = add_emmc_each_part(disk, 1+i, offset,
		//    size, 0, pp->name);

	    /*printf("[disk p%02d] %20s  offset 0x%012llx bytes, size 0x%012llx bytes\n",
		    1+i,
		    pp->name, offset<<9,
		    size<<9);*/
	    /*printf("[disk p%02d] %20s  offset %ld sec, size %ld sec\n",
		    1+i,
		    pp->name, offset,
		    size);*/
	    printf("[disk p%02d] %20s  offset %d Mb, size %d Mb\n",
		    /*disk->disk_name,*/ 1+i,
		    pp->name, pp->offset / SZ_1M,
		    pp->size / SZ_1M/*, IS_ERR(ret) ? "add fail":""*/);
	} else {
	    //printf("[%s] %s: partition exceeds device capacity:\n",
		//    __func__, pp->name);

	    printf("%20s	offset 0x%012llx, size 0x%012llx\n",
		    pp->name, offset<<9, size<<9);

	    break;
	}
    }

    return 0;
}