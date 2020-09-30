//z5312813 Jeremy Mang
//determines whether a linked list is increasing
//or not
//15/04/2020

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ASCENDING 1
#define NEITHER 0


struct node {
    struct node *next;
    int          data;
};

int increasing(struct node *head);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = increasing(head);
    printf("%d\n", result);

    return 0;
}


// return 1 if values in a linked list are in increasing order,
// return 0, otherwise

int increasing(struct node *head) {
	if(head != NULL) {
		struct node *curr = head->next;
		struct node *prev = head;
		while (curr != NULL) {
			if (prev->data >= curr->data) {
				return NEITHER;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	else {
		return ASCENDING;
	}
    // PUT YOUR CODE HERE (change the next line!)
    return ASCENDING;

}


// DO NOT CHANGE THIS FUNCTION

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
