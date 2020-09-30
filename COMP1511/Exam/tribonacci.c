#include <stdio.h>
#include <stdlib.h>

int main () {
	int i = 0;
	printf ("Enter the number of iterations: ");
	scanf("%d", &i);
	int counter = 0;
	int x = 1;
	int y = 1;
	int z = 1;
	int a = 0;
	
	while (counter < i) {
		a = z + y + x;
		x = y;
		y = z;
		z = a;
		printf("%d ", a);
		counter++;
	}
	

}






































































