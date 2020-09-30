
#include "list.h"

bool listIsOrdered(List l) {
	// TODO
	
	//Check for empty list
	if (l != NULL && l->head != NULL) {
		struct node *curr = l->head->next;
		struct node *prev = l->head;
		int ascending, descending;
		
		//Check if sequence is ascending
		while (curr != NULL && curr->value >= prev->value) {
			prev = curr;
			curr = curr->next;
		}
		ascending = (curr == NULL) ? 1 : 0;
		
		if (ascending == 1) {
			return true;
		}
		curr = l->head->next;
		prev = l->head;
		//Check if sequence is descending
		while (curr != NULL && prev->value >= curr->value) {
			prev = curr;
			curr = curr->next;
		}
		descending = (curr == NULL) ? 1 : 0;
		if (descending == 1) {
			return true;
		}
		else {
			return false;
		}
		
	}
	else {
		return true;
	}
}

