//A program that takes the union of two lists and excludes duplicates
//13-09-2020

#include "list.h"

int is_duplicate (List l, int value);

List listSetUnion(List s1, List s2) {
	//check if s1 and s2 are empty
	
	//Create a new list
	struct list *UnionList = newList();
	
	if (s1->head != NULL || s2->head != NULL) {
		
		//Create a new Node by checking whether s1 or s2 are empty
		
		if (s1->head != NULL) {
			UnionList->head = newNode(s1->head->value);
		}
		else if (s2->head != NULL) {
			UnionList->head = newNode(s2->head->value);
		}
		
		//Assign pointers to s1 and s2
		struct node *curr1 = s1->head;
		
		struct node *curr2 = s2->head;
		
		//Assign a pointer to the newList
		struct node *Ucurr = UnionList->head;
		
		//Loop through both lists and only add an entry to the new list if there
		// are no duplicates 
		while (curr1 != NULL) {
			
			if (is_duplicate(UnionList, curr1->value) == 0) {
				Ucurr->next = newNode(curr1->value);
				Ucurr = Ucurr->next;
			}
			
			curr1 = curr1->next;
		}
		while (curr2 != NULL) {
			
			if (is_duplicate(UnionList, curr2->value) == 0) {
				Ucurr->next = newNode(curr2->value);
				Ucurr = Ucurr->next;
			}
			
			curr2 = curr2->next;
		}
		//printListSet(UnionList);
		return UnionList;
		
	}
	
	UnionList->head = NULL;
	
	return UnionList;
}

//A helper function that checks for duplicate input in the list
//returns 1 if true,
//returns 0 if false
int is_duplicate (List l, int value) {
	struct node *curr = l->head;
	struct node *prev = curr;
	int Duplicate = 0;
	while (curr != NULL && prev->value != value) {
		prev = curr;
		curr = curr->next;
	}
	Duplicate = (prev->value == value) ? 1 : 0;
	return Duplicate;
}















