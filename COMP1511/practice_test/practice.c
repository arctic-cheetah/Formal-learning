//This program is a practice on the algorithm selection sort
// 05/05/2020
#include <stdio.h>

#define MAX_LENGTH 1023

void selection_sort (int *array, int size);
void swap (int *a, int *b);

int main () {
	int size;
	printf("Enter the size of the array: ");
	scanf("%d", &size);
	
	int array[size];
	int k = 0;
	printf("Enter an array of numbers: ");
	while (k < size) {
		scanf("%d", &array[k]);
		k++;
	}
	selection_sort(array, size);
	int i = 0;
	while (i < size) {
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");
	return 0;
}

void selection_sort (int *array, int size) {
	//Consider if array is of size 1
	if (size != 1) {
		int sorted = 0;
		int unsorted = 1;
		int min_idx = 0;
		while (sorted < size - 1) {
			min_idx = sorted;
			unsorted = sorted + 1;
			while (unsorted < size) {
				if (array[sorted] > array[unsorted]) {
					min_idx = unsorted;
					swap (&array[sorted], &array[min_idx]);
				}
				unsorted++;
			}
			sorted++;
		}
	}

}

void swap (int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
































































