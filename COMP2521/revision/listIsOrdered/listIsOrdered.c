
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//A function that calculates the length of the list
int list_len (Node n) {
	//base case
	if (n == NULL) {
		return 0;
	}
	return 1 + list_len(n->next);
}

bool listIsOrdered(List l) {
	
	int length = list_len(l->head);
	bool isAscending = 1;
	bool isDescending = 1;
	//Cases:
	//Empty list
	if (length == 0) {
		return true;
	}
	// Check for ascending order
	Node curr = l->head;
	Node prev = curr;
	while (curr != NULL) {
		//prev is greater than the next value
		if (prev->value > curr->value) {
			isAscending = 0;
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	
	//Check for descending
	curr = l->head;
	prev = curr;
	while (curr != NULL) {
		//prev is less than the next value
		if (prev->value < curr->value) {
			isDescending = 0;
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	
	//not ordered
	return (isDescending | isAscending);
}


