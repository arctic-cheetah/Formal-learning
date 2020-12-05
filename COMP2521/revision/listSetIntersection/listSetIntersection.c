#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List listSetIntersection(List s1, List s2) {
	
	List s3 = newList();
	//Check for empty list
	if (s1->head == NULL || s2->head == NULL) {
		return s3;
	}
	
	Node curr1 = s1->head;
	Node currNew = s3->head;
	//Go through the elements of the first list
	//And compare them with the second list
	while (curr1 != NULL) {
	
		Node curr2 = s2->head;
		while (curr2 != NULL) {
			
			//Add the value to the list 
			if (curr2->value == curr1->value) {
				//Check if head is NULL;
				if (s3->head == NULL) {
					s3->head = newNode(curr1->value);
					currNew = s3->head;
				}
				else {
					currNew->next = newNode(curr1->value);
					currNew = currNew->next;
				}
				//printf("%d ", curr1->value);
			}
			
			curr2 = curr2->next;
		}
	
		curr1 = curr1->next;
	}
	
	return s3;
}

