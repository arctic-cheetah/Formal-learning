//A function that determines whether a list is palindromic

#include "list.h"

bool listIsPalindromic(List l) {
	
	int IsPalindromic;
	
	if (l->first != NULL) { 
		struct node *start = l->first;
		struct node *last = l->last;
		
		//check if list size is odd or even
		if (l->size % 2 == 0) {
			int i = 1;
			while (i < (l->size / 2) && (start->value == last->value) ) {
				start = start->next;
				last = last->prev;
				i++;
			}
			if (start->value == last->value) {
				IsPalindromic = 1;
			}
			else {
				IsPalindromic = 0;
			}
		}
		else {
			while (start != last && start->value == last->value) {
				start = start->next;
				last = last->prev;
			}
			if (start->value != last->value) {
				IsPalindromic = 0;
			}
			else {
				IsPalindromic = 1;
			}
		}
		
		
		return IsPalindromic;
		
	}
	
	IsPalindromic = 1;
	return IsPalindromic;
}

