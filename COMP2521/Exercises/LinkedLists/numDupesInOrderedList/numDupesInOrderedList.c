//A program that returns the number of duplicate entries


#include "list.h"

int numDupesInOrderedList(List l) {

	if (l->head != NULL) {
		// TODO
		int Distinct[MAX_LINE_LEN];
		Distinct[0] = 0;
		struct node *curr = l->head;
		int i = 1;
		Distinct[i] = curr->value;
		while (curr != NULL) {
			int j = 0;
			while (j < i) {
				if (Distinct[j] != curr->value && j == i - 1) {
					Distinct[i] = curr->value;
					i++;
				}
				j++;
			}
			curr = curr->next;
		}
		i -=1;
		curr = l->head;
		int list_length = 0;
		while (curr != NULL) {
			list_length++;
			curr = curr->next;
		}
		//for(int k = 1; k < i; k++) printf("%d \n", Distinct[k]);
		
		return list_length - i;
	}
	else {
		return 0;
	}
}

