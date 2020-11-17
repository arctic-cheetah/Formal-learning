// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define UNUSED -1
#define INF_TIME 0xFFFFFF

// represent an entry in a simple inverted page table

typedef struct ipt_entry {
    int virtual_page;        // == -1 if physical page free
    int last_access_time;
} ipt_entry_t;


void lru(int n_physical_pages, int n_virtual_pages);
void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


void lru(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof *ipt);
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++) {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
    }

    int virtual_page;
    for (int access_time = 0; scanf("%d", &virtual_page) == 1; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        access_page(virtual_page, access_time, n_physical_pages, ipt);
    }
}


// if virtual_page is not in ipt, the first free page is used
// if there is no free page, the least-recently-used page is evicted
//
// a single line of output describing the page access is always printed
// the last_access_time in ipt is always updated

void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt) {

    // PUT YOUR CODE HERE TO HANDLE THE 3 cases
    //
    // 1) The virtual page is already in a physical page
    //
    // 2) The virtual page is not in a physical page,
    //    and there is free physical page
    //
    // 3) The virtual page is not in a physical page,
    //    and there is no free physical page
    //
	
    //1)
    int isInPage = 0;
    for (int i = 0; i < n_physical_pages; i +=1) {
    	if (ipt[i].virtual_page == virtual_page) {
    		printf("Time %d: virtual page %d -> physical page %d\n", 				access_time, virtual_page, i);
    		//Update the access time
    		ipt[i].last_access_time = access_time;
    		isInPage = 1;
    		break;
    	}
    }
    //2)
    int isVacant = 0;
    for (int j = 0; j < n_physical_pages && !isInPage; j +=1) {
    	if (ipt[j].virtual_page == UNUSED) {
    		printf("Time %d: virtual page %d loaded to physical page %d\n", 			access_time, virtual_page, j);
    		//Store the virtual page in the physical page
    		ipt[j].virtual_page = virtual_page;
    		ipt[j].last_access_time = access_time;
    		isVacant = 1;
    		break;
    	}
    }
    
    //3)
    //Get the lowest time. This represents the least accessed page (lap)
    if (!isVacant && !isInPage) {
    	int i = 0;
    	int minTime = INF_TIME;
    	int lap = UNUSED;
    	int pageEntry = 0;
		while (i < n_physical_pages) {
			int pageTime = ipt[i].last_access_time;
			int page = ipt[i].virtual_page;
			if (minTime > pageTime && page != -1 && pageTime != -1) {
				minTime = pageTime;
				//Update the page entry and least accessed page
				lap = page;
				pageEntry = i;
			}
			i +=1;
		}
		//Replace the least accessed page with the desired page
		//and update the last access time
		ipt[pageEntry].virtual_page = virtual_page;
		ipt[pageEntry].last_access_time = access_time;
		printf("Time %d: virtual page %d  - virtual page %d evicted - loaded to physical page %d\n", access_time, virtual_page, lap, pageEntry);
		
    }
    
    
    // don't forgot to update the last_access_time of the virtual_page
    
}

























