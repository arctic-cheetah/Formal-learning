//A program that returns the set difference between l1 and l2 ie; l1 - l2

#include "list.h"

int is_duplicate (List l, int value);

List listSetUnion(List l1, List l2) {
	//check if l1 and l2 are empty
	
	//Create a new list
	struct list *UnionList = newList();
	
	if (l1->head != NULL || l2->head != NULL) {
		
		//Create a new Node by checking whether l1 or l2 are empty
		
		if (l1->head != NULL) {
			UnionList->head = newNode(l1->head->value);
		}
		else if (l2->head != NULL) {
			UnionList->head = newNode(l2->head->value);
		}
		
		//Assign pointers to l1 and l2
		struct node *curr1 = l1->head;
		
		struct node *curr2 = l2->head;
		
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

//A helper function that removes the current node
struct node *rm_node (struct list *DifferenceList, struct node *curr, struct node *prev) {
	struct node *newCurr = NULL;
	if (curr == DifferenceList->head) {
		DifferenceList->head = curr->next;
		free(curr);
		prev = DifferenceList->head;
		newCurr = prev;
	}
	else {
		prev->next = curr->next;
		free(curr);
		newCurr = prev->next;
	}
	return newCurr;
}


List listSetDifference(List l1, List l2) {
	struct list *DifferenceList;
	//Check if either l1 or l2 is empty
	if (l1->head != NULL && l2->head != NULL) {
		//Obtain the union of the list
		DifferenceList = listSetUnion(l1, l2);
		//printListSet(DifferenceList);
		//Assign pointers to l1 and UnionList for comparison
		struct node *curr = l2->head;
		struct node *Dcurr = DifferenceList->head;
		struct node *Dprev = Dcurr;
		
		//loop through l2 and compare with DifferenceList
		while (curr != NULL) {
			Dcurr = DifferenceList->head;
			Dprev = Dcurr;
			while (Dcurr != NULL) {
				if (curr->value == Dcurr->value) {
					//Remove the target node
					Dcurr = rm_node(DifferenceList, Dcurr, Dprev);
					if (Dcurr == NULL) {
						Dcurr = DifferenceList->head;
					}
				}
				//printListSet(DifferenceList);
				if (Dcurr == NULL){
					break;
				}
				Dprev = Dcurr;
				Dcurr = Dcurr->next;
			}
			curr = curr->next;
		}
		
		
	}
	else if (l1->head == NULL && l2->head != NULL) {
		DifferenceList = l2;
	}
	else if (l1->head != NULL && l2->head == NULL) {
		DifferenceList = l1;
	}
	else {
		DifferenceList = NULL;
	}
	return DifferenceList;
}








