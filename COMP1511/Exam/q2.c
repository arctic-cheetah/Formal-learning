#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int have_smalls(struct node *head1, struct node *head2);
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

    int result = have_smalls(head1, head2);
    printf("%d\n", result);

    return 0;
}

// have_smalls should return 0 if neither list contains small numbers.
// have_smalls should return 1 one list contains a small number, but the other doesn't.
// have_smalls should return 2 if both lists contain at least one small number.
// a small number is a number that is less 10.
int have_smalls(struct node *head1, struct node *head2) {
	struct node *curr1 = head1;
	struct node *curr2 = head2;
	int smallNum1 = 0;
	int smallNum2 = 0;
	
	
	//Consider when head1 null
	if (head1 != NULL) {
		while (curr1 != NULL) {
			if (curr1->data < 10) {
				smallNum1 = 1;
			}
			curr1 = curr1->next;
		}
    } 
    else {
    	smallNum1 = 0;
    }
    
    //Consider when head2 is Null
    if (head2 != NULL) {
    	while (curr2 != NULL) {
			if (curr2->data < 10) {
				smallNum2 = 1;
			}
			curr2 = curr2->next;
		}
    } 
    else {
    	smallNum2 = 0;
    }
    
    if (smallNum1 == 1 && smallNum2 == 1) {
    	return 2;
    }
    else if (smallNum1 == 0 && smallNum2 == 1) {
    	return 1;
    }
    else if (smallNum1 == 1 && smallNum2 == 0) {
    	return 1;
    }
    else {
    	return 0;
    }
    

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
