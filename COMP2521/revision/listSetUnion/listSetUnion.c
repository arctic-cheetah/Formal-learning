#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//A helper function that checks whether a value is present 
//In a set

int isPresent (List s, int data) {
	if (s->head == NULL) {
		return 0;
	}
	Node curr = s->head;
	
	while (curr != NULL) {
		if (curr->value == data) {
			return 1;
		}
		curr = curr->next;
	}
	//Data not found
	return 0;
}


List listSetUnion(List s1, List s2) {

	List s3 = newList();
	Node curr3 = NULL;
	//Add all the elements from s1
	Node curr1 = s1->head;
	
	while (curr1 != NULL) {
		if (s3->head == NULL) {
			s3->head = newNode(curr1->value);
			curr3 = s3->head;
		}
		else {
			curr3->next = newNode(curr1->value);
			curr3 = curr3->next;
		}
		
		curr1 = curr1->next;
	}
	
	//Add all elements that are absent in s1 to s3
	Node curr2 = s2->head;
	
	while (curr2 != NULL) {
		//Add the element if it is absent from s3
		if (!isPresent(s3, curr2->value)) {
			if (s3->head == NULL) {
				s3->head = newNode(curr2->value);
				curr3 = s3->head;
			}
			else {
				curr3->next = newNode(curr2->value);
				curr3 = curr3->next;
			}
		}
		curr2 = curr2->next;
	}
	
	
	return s3;
}




