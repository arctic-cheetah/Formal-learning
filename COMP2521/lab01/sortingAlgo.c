//A program that demonstrates different sorting algorithms

#include <stdio.h>

#define MAX_LENGTH 1023

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_array(int *array, int length){
	for(int i = 0; i < length; i++){
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
		}
		else {
			temp[k] = array[j];
			j++;	
		}
		k++;
	}
	
	while (i <= mid) {
		temp[k] = array[i];
		i++;
		k++;
	}
	while (j <= right) {
		temp[k] = array[j];
		j++;
		k++;
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

//Hoare's partition
int partition(int *array, int left, int right){
	
	int mid = left + (right - left) / 2;
	if (array[mid] > array[left]) {
		swap(&array[mid], &array[left]);
	}
	if (array[mid] > array[right]) {
		swap(&array[mid], &array[right]);
	}
	if (array[right] > array[left]) {
		swap(&array[right], &array[left]);
	}
	
	int pivot = array[right];
	int start = left;
	int end = right;
	
	while (start < end) {
		while (array[start] < pivot) {
			start++;
		}
		while (array[end] > pivot) {
			end--;
		}
		//DO something if there are identical entries
		if (array[start] == array[end]) {
			return end;
		}
		if (start >= end) {
			return end;
		}
		swap(&array[start], &array[end]);
	}
}


void quickSort(int *array, int left, int right){
	if (left < right) {
		int mid = partition(array, left, right);
		quickSort(array, left, mid - 1);
		quickSort(array, mid + 1, right);
	}
}





int main(){
	int myNum = 0;
	int array[MAX_LENGTH];
	int length = 0;
	while (scanf("%d", &myNum) != EOF) {
		array[length] = myNum;
		length++;
	}
	
	//mergeSort(array, 0, MAX_LENGTH - 1);
	
	quickSort(array, 0, length - 1);
	print_array(array, length);
	
}






/*
//Lumoto's partition
int partition(int *array, int left, int right){
	int mid = left + (right - left) / 2;
	if (array[mid] > array[left]) {
		swap(&array[mid], &array[left]);
	}
	if (array[mid] > array[right]) {
		swap(&array[mid], &array[right]);
	}
	if (array[right] > array[left]) {
		swap(&array[right], &array[left]);
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
	swap(&array[part], &array[right]);
	return part;	
}
*/




































