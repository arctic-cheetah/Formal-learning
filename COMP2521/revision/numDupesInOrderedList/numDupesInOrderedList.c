
#include "list.h"
#include <stdio.h>
#define NON_NUM 0xFFFF

//Returns the length of the list
int list_len(Node n) {
	//base case
	if (n == NULL) {
		return 0;
	}
	return 1 + list_len(n->next);
}

int isDup (int size, int *array, int target) {
	for (int i = 0; i < size; i +=1) {
		if (target == array[i]) {
			return 1;
		}
	}
	return 0;
}



int numDupesInOrderedList(List l) {
	
	int len = list_len(l->head);
	
	//Empty list
	if (l->head == NULL) {
		return 0;
	}
	
	//"Remember duplicate values"
	int *memory = calloc(len, sizeof(int));
	
	
	
	Node curr1 = l->head;
	int size = 0;
	//Place all distinct values into the array
	while (curr1 != NULL) {
	
		//Add the first value to memory
		if (!isDup(size, memory, curr1->value)) {
			memory[size] = curr1->value;
			size +=1;
		}
		curr1 = curr1->next;
	}
	//Check for duplicate value
	//Exclude the size of the array
	int numDup = 0;
	curr1 = l->head;
	while (curr1 != NULL) {
		if (isDup(size, memory, curr1->value)) {
			numDup +=1;
		}
		curr1 = curr1->next;
	}
	free(memory);
	return numDup - size;
}

























