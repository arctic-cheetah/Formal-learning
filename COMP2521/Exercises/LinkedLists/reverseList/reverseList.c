//A program that reverses a singly linked list


#include "list.h"

void listReverse(List l) {
	struct node *curr = l->head;
	struct node *prev = NULL;
	struct node *next = NULL;
	
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	l->head = prev;
}

