// This program prints out all the ASCII characters
//Excluding the control characters
#include <stdio.h>


int main () {
	
	int i = 32;
	while (i < 127) {
		if (i < 100) {
			printf(" %d 0x%x %c\n", i, i, i);
		}
		else {
			printf("%d 0x%x %c\n", i, i, i);
		}
		i++;
	}
	
	return 0;
}









































