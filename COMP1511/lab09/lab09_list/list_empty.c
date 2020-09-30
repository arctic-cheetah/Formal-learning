// implements functions in list.h
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

// ======= W10 Tut Problems ========
// returns a copy of the linked list
struct node *copy(struct node *head) {
    if (head == NULL) {
    	return NULL;
    }
    struct node *curr = head->next;
    struct node *copy = create_node(head->data);
    struct node *copyCurr = copy;
    while (curr != NULL) {
    	copyCurr->next = create_node(curr->data);
    	copyCurr = copyCurr->next;
    	curr = curr->next;
    }
    copyCurr->next = NULL;
    return copy;
}

// returns 1 if the two lists are identical, otherwise returns 0
int identical(struct node *head1, struct node *head2) {
    if (head1 == NULL) {
    	if (head2 == NULL) {
    		return 1;
    	}
    	return 0;
    }
    if (head2 == NULL) {
    	if (head1 == NULL) {
    		return 1;
    	}
    	return 0;
    }
    struct node *curr1 = head1;
    struct node *curr2 = head2;
    while (curr1 != NULL && curr2 != NULL) {
    	
		if (curr2->data != curr1->data) {
			return 0;
		}
		curr2 = curr2->next;
    	curr1 = curr1->next;
    }
    if (curr1 == NULL && curr2 == NULL) {
    	return 1;
    }
    return 0;
}

// returns 1 if list is in strictly increasing order, otherwise returns 0
int ordered(struct node *head) {
	if (head == NULL) {
		return 1;
	}
	struct node *curr = head;
	while (curr->next != NULL) {
		if (curr->data >= curr->next->data) {
			return 0;
		}
		curr = curr->next;
	}
    return 1;   
}

// given two lists in strictly increasing order,
// return a new linked list (in strictly increasing order) of the elements in both set1 and set2
struct node *set_intersection(struct node *set1, struct node *set2) {
	if (set1 == NULL || set2 == NULL) {
		return NULL;
	}
	struct node *curr1 = set1;
	struct node *curr2 = set2;
	struct node *intersect = NULL;
	struct node *tail = NULL;
	
	
	while (curr1 != NULL && curr2 != NULL) {
		if (curr1->data == curr2->data) {
			if (intersect == NULL) {
				intersect = create_node(curr1->data);
				tail = intersect;
			}
			else {
				tail->next = create_node(curr1->data);
				tail = tail->next;
			}
		}
		if (curr1->data < curr2->data) {
			curr1 = curr1->next;
		} 
		else {
			curr2 = curr2->next;
		}
		
	}
	
	
	
	
	
	
	
	
	

	
	
	
	/* Jeremy's way of finding the intersection of a list.
	while (curr1 != NULL) {
		while (curr2 != NULL) {
			if (curr1->data == curr2->data) {
				//Consider if this is the first new element being copied
				if (intersect == NULL) {
					intersect = create_node(curr1->data);
					tail = intersect;
				}
				//otherwise, only move the tail
				else {
					tail->next = create_node(curr1->data);
					tail = tail->next;
				}
			}
			curr2 = curr2->next;
		}
		curr2 = set2; 
		curr1 = curr1->next;
	}
	*/
	//print_list(intersect);
	
    return intersect;
}

// given two linked lists in strictly increasing order,
// return a new linked list (in strictly increasing order) of the elements in either set1 or set2
// no duplicates (only include them once)
struct node *set_union(struct node *set1, struct node *set2) {
	if (set1 == NULL && set2 == NULL) {
		return NULL;
	}
	struct node *intersect = set_intersection(set1, set2);
	struct node *curr1 = set1;
	struct node *prev = set1;
	
    return set1;
}

// =================================

// given an array of integer values for data items
// returns the head of a linked list with these values
// in the order as they appear in the array
// size gives the size of the array
struct node *create_list(int values[], int size) {
    int i = 0;

    if (size <= 0) {
        // empty linked list (or invalid size)
        return NULL;
    }

    struct node *head = NULL;   // head of the linked list
    struct node *tmp = NULL;    // temporary item we're working with
    struct node *curr = NULL;   // current node we're looking at in the linked list

    while (i < size) {
        tmp = create_node(values[i]);

        // link this node onto our list
        if (head == NULL) {
            // this is the first node in the list
            head = tmp;
            curr = head;
        } else {
            // this is not the first node in the list
            // add it to the end, i.e. after curr
            curr->next = tmp;

            // reset curr to point at the new last node
            curr = tmp;
        }
        i = i + 1;
    }

    return head;
}

// creates a struct node with the given data value
// returns a pointer to this node
struct node *create_node(int dat) {
    struct node *new = malloc(sizeof(struct node));
    assert(new != NULL);
    new->data = dat;
    new->next = NULL;

    return new;
}

// prints out the list given the head of a list
void print_list(struct node *head) {
    struct node *curr;
    curr = head;

    while (curr != NULL) {
        printf("[ %d ]-->", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");

}

// frees all the elements in a linked list
void free_list(struct node *head) {
    if (head == NULL) {
        return;
    }
    free_list(head->next);
    free(head);
}

// return the number of items in the linked list
int num_items(struct node *head) {
    struct node *curr = head;
    int count = 0;

    while (curr != NULL) {
        count = count + 1;
        curr = curr->next;
    }

    return count;
}
