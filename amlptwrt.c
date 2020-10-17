#include <stdio.h> 
#include <stdlib.h> 
#include "mmcparts_a9.h"

int write_mmcparts();
  
int main() 
{ 
    init_parts();
    write_mmcparts();

    return 0; 
}
  
int write_mmcparts() 
{ 
  
    // pointer to FILE 
    FILE* fmp; 
  
    // Creates a file "demo_file" 
    // with file acccess as write-plus mode 
    fmp = fopen("mmc_parts.bin", "w"); 
  
    // adds content to the file 
    fwrite(&g_mmcparts, sizeof(struct mmc_partitions_fmt), 1, fmp);
  
    // closes the file pointed by demo 
    fclose(fmp); 
  
    return 0; 
}