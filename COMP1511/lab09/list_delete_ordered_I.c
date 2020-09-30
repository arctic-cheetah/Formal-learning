#include <stdio.h>
#include <stdlib.h>

// Do not edit this struct. You may use it exactly as
// it is but you cannot make changes to it

// A node in a linked list
struct node {
    int data;
    struct node *next;
};

// ADD ANY FUNCTION DECLARATIONS YOU WISH TO USE HERE

int ascendingCheck (struct node* head) {
    int ascending = 1;
    struct node *ascendingCurr = head->next;
    struct node *ascendingPrev = head;
    if (head->next != NULL) {
    	if (ascendingPrev->data == ascendingCurr->data){
    		return ascending;
    	}
		while (ascendingCurr->next != NULL && ascendingPrev->data < ascendingCurr->data) {
		    ascendingPrev = ascendingCurr;
		    ascendingCurr = ascendingCurr->next;
		}
		if (ascendingPrev->data < ascendingCurr->data) {
		    ascending = 1;
		}
		else {
		    ascending = 0;
		}
    }
    return ascending;
}

int length(struct node *head) {
    int listCount = 0;
    struct node *curr = head;
    
    if (head == NULL) {
        return 0;
    }
    
    while (curr != NULL) {
        listCount++;
        curr = curr->next;
    }  
    return listCount;
}

struct node *remove_disorder(struct node *head) {
    struct node *curr = head;
    struct node *prev = head;
    //loop prev and curr pointers to the end
    	
    while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
    }
    //Check for ascending order
    while (ascendingCheck (head) == 0){
        //loop prev pointer
        while (curr->data < prev->data && prev->next != NULL) {
			//if(listLength != 1){
		    	prev->next = NULL;
		    	prev = head;
        }
        if(curr->data > prev->data) {
        	curr = prev;
        	while (curr->next != NULL) {
		        prev = curr;
		        curr = curr->next;
    		}
        }
		//If curr is the smallest out of the list
		//It must become the head
	  	if (curr->data < prev->data && prev == head) {
		    head = curr;
		}
		//Otherwise if curr is larger than prev
		else {
			prev->next = curr;
		}
    }
    
    return head;
}

/*
// Remove any nodes in a list that are higher 
// than the node directly after them.
// Return the head of the list.
// The returned list must have no disorder in it!
struct node *remove_disorder(struct node *head) {
    struct node *curr = head;
    struct node *prev = head;
    //loop prev and curr pointers to the end
    	
    while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
    }
    //Check for ascending order
    while (ascendingCheck (head) == 0){
        //Count the length of the list
        int listLength = length(head);
        
        //loop prev pointer and check if it is less that curr
        while (curr->data < prev->data && prev->next != NULL) {
			
			if(listLength != 1){
		    	prev->next = NULL;
		    	prev = head;
        	}
        	else {
        		break;
        	}
        }
        
		//If curr is the smallest out of the list
		//It must become the head
	  	if (curr->data < prev->data && prev == head) {
		    head = curr;
		}
		//Otherwise if curr is not the smallest/
		else {
			prev->next = curr;
		}
    }
    
    return head;
}
*/

// These helper functions are for the main below and will
// have no effect on your remove_disorder. They do not
// need to be modified.
struct node *make_list(int a, int b, int c);
void printList(struct node *head);

// This is a main function which could be used
// to test your remove_disorder function.
// It will not be marked.
// Only your remove_disorder function will be marked.
//
// It's recommended to change the int values in this
// main to test whether your remove_disorder is working.
int main(void) {
    // test an ordered list
    
    struct node *ordered = make_list(1, 2, 3);
    ordered = remove_disorder(ordered);
    printList(ordered);
    
    // test removing one element out of order
    ordered = make_list(1, 1, 2);
    ordered = remove_disorder(ordered);
    printList(ordered);
    
    // test a completely disordered list
    ordered = make_list(3, 2, 1);
    ordered = remove_disorder(ordered);
    printList(ordered);
    // test with the first removal causing more disorder
    ordered = make_list(2, 3, 1);
    ordered = remove_disorder(ordered);
    printList(ordered);
        
    return 0;
}

// A simple function to make a linked list with 3 elements
// This function is purely for the main above
// You will be tested with lists that are more and less
// than 3 elements long
struct node *make_list(int a, int b, int c) {
    struct node *head = malloc(sizeof (struct node));
    struct node *n = head;
    n->data = a;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = b;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = c;
    n->next = NULL;
    
    return head;
}

void printList(struct node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
// ADD ANY FUNCTION DEFINITIONS YOU WISH TO USE HERE


