
#include "list.h"

bool listIsOrdered(List l) {
	// TODO
	
	if (l != NULL) {
		struct node *curr = l->head->next;
		struct node *prev = l->head;
		int ascending, descending, truth;
		
		//Check if sequence is ascending or descending by looking
		//At first two values
		if (prev->value >= curr->value) {
			ascending = 0;
			descending = 1;
		}
		else if (prev->value <= curr->value) {
			ascending = 1;
			descending = 0;
		}
		
		if (ascending == 1) {
			//Break out from loop if list is not ascending
			while (curr != NULL && curr->value >= prev->value) {
				curr = curr->next;
				prev = curr;
			}
			
		}
		else if (descending == 1) {
			while (curr != NULL && prev->value >= curr->value) {
				curr = curr->next;
				prev = curr;
			}
			
		}
		truth = (curr == NULL) ? 1 : 0;
		return truth;
		
	}
	else {
		return 1;
	}
}

