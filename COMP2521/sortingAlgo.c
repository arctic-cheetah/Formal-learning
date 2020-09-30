//Different types of sorting algorithms
#include <stdio.h>

#define MAX_LENGTH 8

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_array(int *array, int length){
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}


void merge(int *array, int left, int mid, int right){
	int i = left;
	int j = mid + 1;
	int k = left;
	int temp[MAX_LENGTH];
	
	while (i <= mid && j <= right) {
		if (array[i] <= array[j]) {
			temp[k] = array[i];
			i++;
			k++;
		}
		else {
			temp[k] = array[j];
			j++;
			k++;
		}
	}
	
	while (i <= mid) {
		temp[k] = array[i];
		k++;
		i++;
	}
	while (j <= right) {
		temp[k] = array[j];
		k++;
		j++;
	}
	
	for (int m = left; m <= right; m++) {
		array[m] = temp[m];
	}
	
}

void mergeSort(int *array, int left, int right){
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);
		merge(array, left, mid, right);
	}
}

//Lumoto's partition
int partition(int *array, int left, int right){
	int mid = left + (right - left) / 2;
	if (array[left] > array[mid]) {
		swap(&array[mid], &array[left]);
	}
	if (array[right] > array[left]) {
		swap(&array[right], &array[left]);
	}
	if (array[mid] > array[right]) {
		swap(&array[right], &array[mid]);
	}

	int pivot = array[right];
	int i = left;
	int part = left;
	
	while (i < right) {
		if (array[i] <= pivot) {
			swap(&array[i], &array[part]);
			part++;
		}
		i++;
	}
	
	//Need to resolve issue with duplicate entries while swapping the pivot
	swap(&array[part], &array[right]);
	
	return part;
}


	
void quickSort(int *array, int left, int right){
	if (left < right) {
		int mid = partition(array, left, right);
		quickSort(array, left, mid - 1);
		quickSort(array, mid + 1, right);
	}
	
}



int main(){
	int array[MAX_LENGTH] = {1, 51, 64, 64, 64, 64, 64, 89};
	quickSort(array, 0, MAX_LENGTH - 1);
	print_array(array, MAX_LENGTH);
}












/*
//Hoare's parititon
int partition(int *array, int left, int right){
	int mid = left + (right - left) / 2;
	if (array[left] > array[mid]) {
		swap(&array[mid], &array[left]);
	}
	if (array[right] > array[left]) {
		swap(&array[right], &array[left]);
	}
	if (array[mid] > array[right]) {
		swap(&array[right], &array[mid]);
	}

	int pivot = array[right];
	int start = left;
	int end = right;
	
	while (start < end) {
		while (array[start] < pivot) {
			start++;
		}
		while (array[end] > pivot){
			end--;
		}
		if (start >= end) {
			return end;
		}
		//need to account for case where there are duplicate entries
		if (array[start] == array[end]) {
			return end;
		}
		swap(&array[start], &array[end]);
		
	}
}
*/



































