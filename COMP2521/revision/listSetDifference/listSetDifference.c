#include <stdlib.h>
#include <stdio.h>
#include "list.h"

//A helper function that gets the intersection
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
			}
			
			curr2 = curr2->next;
		}
	
		curr1 = curr1->next;
	}
	return s3;
}


////A helper function that checks whether a value is present 
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



List listSetDifference(List s1, List s2) {
	//If l2 == NULL, l1 - l2 == l1
	if (s1 != NULL && s2 == NULL) {
		return listSortedCopy(s1);
	}
	List s3 = newList();
	Node curr3 = NULL;
	
	//Get the intersection of the set
	List intersect = listSetIntersection(s1, s2);
	
	//Check if the intersection overlaps with s1
	Node curr1 = s1->head;
	while (curr1 != NULL) {
		
		//Add the element if not present
		if (!isPresent(intersect, curr1->value)) {
			if (s3->head == NULL) {
				s3->head = newNode(curr1->value);
				curr3 = s3->head;
			}
			else {
				curr3->next = newNode(curr1->value);
				curr3 = curr3->next;
			}
		}
		curr1 = curr1->next;
	}
	freeList(intersect);
	
	return s3;
}


























