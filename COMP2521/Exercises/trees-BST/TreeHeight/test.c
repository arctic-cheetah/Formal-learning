#include <stdio.h>

int main () {
	int mynum = 0;
	int *p = &mynum;
	
	while (*p < 10) {
		(*p)++;
	}
	
	printf("%d\n", mynum);
}


