//A program that returns the intersection of two Linked Lists

#include "list.h"

List listSetIntersection(List s1, List s2) {
	//Create a list that holds the intersection of s1 and s2
	struct list *IntersectList = newList();
	
	// Check if s1 and s2 are empty
	if (s1->head != NULL && s2->head != NULL) {
		
		
		//assign pointers to s1 and s2
		struct node *curr1 = s1->head;
		struct node *curr2 = s2->head;
		
		struct node *Icurr = NULL;
		
		//loop through s1 then check each entry in s2 
		//Only add an element if there is an intersection
		while (curr1 != NULL) {
			curr2 = s2->head;
			
			while (curr2 != NULL) {
				if (curr1->value == curr2->value) {
					//Check if head is empty
					if (IntersectList->head == NULL) {
						Icurr = newNode(curr1->value);
						IntersectList->head = Icurr;
					}
					else {
						Icurr->next = newNode(curr1->value);
						Icurr = Icurr->next;
					}
				}
				
				curr2 = curr2->next;
			}
			
			curr1 = curr1->next;
		}
		
		return IntersectList;
	}
	
	IntersectList->head = NULL;
	
	return IntersectList;
}

