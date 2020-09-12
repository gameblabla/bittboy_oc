#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

#include <sys/statvfs.h>
#include <errno.h>

// #include <sys/fcntl.h> //for battery

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/mman.h>
#include <sys/time.h>   /* for settimeofday() */

#include "octable.h"

int memdev = 0;
volatile uint32_t *memregs;

int main(int argc, char* argv[])
{
	int mhz;

	memregs = (uint32_t*)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, memdev, 0x01c20000);
	
	mhz = 900;
	printf("Search for Megahertz %d\n", mhz);
	
	uint32_t x, v;
	uint32_t total=sizeof(oc_table)/sizeof(uint32_t);

    for(x=0; x<total; x++){
      if((oc_table[x] >> 16) >= mhz){
        v = memregs[0];
        printf("memregs[0] %d\n", memregs[0]);
        v&= 0xffff0000;
        v|= (oc_table[x] &  0x0000ffff);
        memregs[0] = v;
        printf("Final memregs[0] %d\n", memregs[0]);
        break;
      }
    }
    
    printf("oc_table[x] >> 16 = %d\n", oc_table[x] >> 16);

	printf("Set CPU clock: %d(0x%08x)\n", mhz, v);
		
	if (memdev > 0) {
		memregs = NULL;
		close(memdev);
	}
		
	return 0;
}


