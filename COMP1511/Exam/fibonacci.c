#include <stdio.h>
#include <stdlib.h>

int main () {
	int i = 0;
	printf ("Enter the number of iterations: ");
	scanf("%d", &i);
	int counter = 0;
	int x = 1;
	int y = 2;
	int z = 0;
	
	while (counter < i) {
		z = y + x;
		x = y;
		y = z;
		printf("%d ", z);
		counter++;
	}
	

}






































































