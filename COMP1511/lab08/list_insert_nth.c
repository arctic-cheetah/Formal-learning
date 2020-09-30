//z5312813 Jeremy Mang
//Inserts a linked list at a desired position
//09/04/2020

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *insert_nth(int n, int value, struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int value;
    scanf("%d", &value);
    // create linked list from command line arguments
    struct node *head = NULL;
    if (argc > 1) {
        // list has elements
        head = strings_to_list(argc - 1, &argv[1]);
    }

    struct node *new_head = insert_nth(n, value, head);
    print_list(new_head);

    return 0;
}


// Insert a new node containing value at position n of the linked list.
// if n == 0, node is inserted at start of list
// if n >= length of list, node is appended at the end of list
// The head of the new list is returned.
struct node *insert_nth(int n, int value, struct node *head) {
	int nodeCount = 0;
	struct node *newNode = malloc(sizeof(struct node));
	struct node *curr = head;
	struct node *prev = NULL;
	
	newNode->data = value;
	//Count the number of nodes
	while(curr != NULL){
		prev = curr;
		curr = curr->next;
		nodeCount++;
	}
	//Check if n is inserted at a position
	//greater than the length of the list
	if(n > nodeCount){
		n = nodeCount;
	}
	//Match the node number	
	curr = head;
	prev = NULL;
	int i = 0;
	while(i < n){
		prev = curr;
		curr = curr->next;	
		i++;
	}//stop looping until curr is on the desired node
	
	if(prev == NULL){//Insertion of a node at the first position
		newNode->next = curr;
		head = newNode;
	}
	else{//Insertion of somewhere in the list
		newNode->next = curr;
		prev->next = newNode;
	}
    return head;

}


// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        i -= 1;
    }   
    return head;
}

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
