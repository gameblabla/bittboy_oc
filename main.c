#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "octable.h"

int main(int argc, char* argv[])
{
	int mhz;
	if (argc < 2)
	{
		printf("Bittboy CPU OC calculator\n");
		printf("executable mhz_value\n");
		return 1;
	}
	
	mhz = atoi (argv[1]);
	printf("Search for Megahertz %d\n", mhz);
	
	uint32_t x, v;
	uint32_t total=sizeof(oc_table)/sizeof(uint32_t);

    for(x=0; x<total; x++){
      if((oc_table[x] >> 16) >= mhz){
        //v = memregs[0];
        v&= 0xffff0000;
        v|= (oc_table[x] &  0x0000ffff);
        //memregs[0] = v;
        break;
      }
    }
    
    printf("oc_table[x] >> 16 = %d\n", oc_table[x] >> 16);
    if (oc_table[x] >> 16 != mhz) printf("Mhz is not equal to oc_table, please fix\n");
    
	printf("Set CPU clock: %d(0x%08x)\n", mhz, v);
		
	return 0;
}


