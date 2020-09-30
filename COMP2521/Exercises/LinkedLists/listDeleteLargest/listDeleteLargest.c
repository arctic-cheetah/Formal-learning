//A program that deletes the largest entry in a list


#include "list.h"

int listDeleteLargest(List l) {
	int largest = 0;
	//Check if the head of the list is not NULL;
	if (l->head != NULL && l->head->next != NULL) {
		struct node *curr = l->head;
		struct node *prev = curr;
		
		while (curr != NULL) {
			if (curr->value >= largest) {
				largest = curr->value;
			}
			prev = curr;
			curr = curr->next;
		}
		//find the first instance of the largest number
		curr = l->head;
		prev = curr;
		while (curr->value != largest) {
			prev = curr;
			curr = curr->next;
		}
		//Check if removing the head
		if (l->head == curr) {
			l->head = curr->next;
			prev = l->head;
			free(curr);
		}
		else {
			prev->next = curr->next;
			free(curr);
		}
		return largest;
	}
	//Case 2 HEAD: [X]->NULL
	else if (l->head != NULL && l->head->next == NULL) {
		largest = l->head->value;
		struct node *curr2 = l->head;
		l->head = NULL;
		free(curr2);
		return largest;
	}
	//Case 3 HEAD: NULL
	else {
		return 0;
	}
}

