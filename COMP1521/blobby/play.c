#include <stdio.h>
#include <stdlib.h>

int main () {
	int *array = (int *)malloc(0xFFFFFFF * sizeof(char));
}
