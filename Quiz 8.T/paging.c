#include <stdio.h>

#define PAGE_SIZE 1024
#define NUM_PAGES 4

//Fix page table

int page_table[NUM_PAGES] = {5, 2, 9, 1};

void translate(int logical_address) {
	int page = logical_address / PAGE_SIZE;
	int offset = logical_address % PAGE_SIZE;

	if (page < 0 || page >= NUM_PAGES) {
		printf("Logical: %d | INVALID (out of range)\n", logical_address);
	}else{
		int frame = page_table[page];
		int physical = (frame * PAGE_SIZE) + offset;
		printf("Logical: %d | Page: %d | Offset: %d |  Frame: %d | Physical: %d\n", logical_address, page, offset, frame, physical);
	}
}

int main() {
	int n;
	printf("Enter number of logical addresses (N):\n");
	if (scanf("%d", &n) != 1) return 1;

	printf("Enter logical address(es), one per line:\n");
	for (int i = 0; i < n; i++) {
		int address;
		if (scanf("%d", &address) == 1) {
			translate(address);
		}
	}
return 0;
}
