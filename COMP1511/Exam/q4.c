#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int overlap(struct node *head1, struct node *head2);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = overlap(head1, head2);
    printf("%d\n", result);

    return 0;
}

// overlap should return 1 if any value occurs in both lists
// overlap should return 0 otherwise
int overlap(struct node *head1, struct node *head2) {
	struct node *curr1 = head1;
	struct node *curr2 = head2;
	
	//Account for any empty lists
	if (head1 == NULL && head2 != NULL) {
		return 0;
	}
	else if (head1 != NULL && head2 == NULL) {
		return 0;
	}
	else if (head1 == NULL && head2 == NULL) {
		return 0;
	}
	
	//Loop through linked list #1
	while (curr1 != NULL) {
		
		//Loop and check in linked list #2
		
		//reset the counter
		curr2 = head2;
		while (curr2 != NULL) {
			if (curr2->data == curr1->data) {
				return 1;
			}
			curr2 = curr2->next;		
		}
		
		curr1 = curr1->next;
	}
	
    
    return 0;

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
