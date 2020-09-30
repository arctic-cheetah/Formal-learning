//An implementation on reversing a Doubly linked list
//13/09/2020


#include "list.h"

void reverseDLList(List l) {
	struct node *curr = l->first;
	struct node *Prev = NULL;
	struct node *Next = NULL;
	struct node *Last = l->first;
	
	while (curr != NULL) {
		Next = curr->next;
		curr->next = Prev;
		curr->prev = Next;
		Prev = curr;
		curr = Next;
	}
	l->first = Prev;
	l->last = Last;
	
}

