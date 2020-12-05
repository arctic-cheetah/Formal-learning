
#include "list.h"

void reverseDLList(List l) {
	//empty list
	if (l->first == NULL) {
		return;
	}
	
	
	
	Node curr = l->first;
	Node prev = curr->prev;
	
	//Set the first as the last and vice versa
	l->first = l->last;
	l->last = curr;
	
	
	while (curr != NULL) {
		Node next = curr->next;
		curr->prev = next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	
}

