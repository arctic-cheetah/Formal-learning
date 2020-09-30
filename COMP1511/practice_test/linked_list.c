// Linked list revision
// Base code: Elizabeth Willer 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};


struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);
int sum_list(struct node *head);
struct node *find_item(struct node *head, int item);
int find_last(struct node *head);
int find_nth(struct node *head, int nth);
struct node *add_last(struct node *head, int item);
struct node *add_first(struct node *head, int item);
struct node *add_nth(struct node *head, int item, int nth);
struct node *remove_first(struct node *head);
struct node *remove_last(struct node *head);
struct node *remove_nth(struct node *head, int nth);
struct node *remove_item(struct node *head, int item);
void free_list(struct node *head);
struct node *create_node(int data);



int main(int argc, char *argv[]) {
   // TODO: Write some test cases for your functions  
   char *list1[] = {"2", "4", "8", "16", "3", "5", "4"};
   struct node *head1 = strings_to_list(7, list1);
   print_list(head1);
   printf("The sum is %d\n", sum_list(head1));
   find_item (head1, 2);
   printf("The last element is: %d\n", find_last(head1) );
   printf("The nth item is: %d\n", find_nth(head1, 3));
   add_last(head1, 7);
   print_list(head1);
   /*
   head1 = remove_last(head1);
   print_list(head1);
   head1 = remove_item(head1, 2);
   print_list(head1);
   */
   head1 = remove_nth(head1, 1);
   print_list(head1);
   
   /*
   char *list2[] = {"1", "2", "3", "4"};
   struct node *head2 = strings_to_list(4, list2);
   print_list(head2);
   */
   return 0;
}




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
        i = i-1;
    }
    return head;
}

struct node *create_node(int data) {
	struct node *newNode = malloc (sizeof (struct node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}


// print linked list in python style (i.e. [1, 2, 3, 4])
void print_list(struct node *head) {
    if (head == NULL) {
    	printf("Entered an empty list!\n");
    	exit(1);
    }
    struct node *curr = head;
    printf("[");
    while (curr != NULL) {
    	printf("%d", curr->data);
    	if (curr->next != NULL) {
    		printf(", ");
    	}
    	curr = curr->next;
    }
    printf("]\n");
}


//calculate sum of a list
int sum_list(struct node *head) {
	if (head == NULL) {
    	printf("Entered an empty list!\n");
    	exit(1);
    }
    struct node *curr = head;
    int sumCount = 0;
    while (curr != NULL) {
    	sumCount = sumCount + curr->data;
    	curr = curr->next;
    }
    return sumCount;
}


//find an item (say 25) in a list (return pointer to that item)
struct node *find_item(struct node *head, int item) {
	if (head == NULL) {
    	printf("Entered an empty list!\n");
    	exit(1);
    }
    struct node *curr = head;
    
    while (curr != NULL) {
    	if (curr->data == item) {
			printf("Successfully found the item in the list\n");
			return curr;
    	}
    	curr = curr->next;
    }
	printf("Item not found in the list\n");
	return head;
}

//find last item in a list (return the value of that item)
int find_last(struct node *head) {
	if (head == NULL) {
    	printf("Entered an empty list!\n");
    	exit(1);
    }
    struct node *curr = head;
    while (curr->next != NULL) {
    	curr = curr->next;
    }
    return curr->data;
}

//find nth item in a list (return the value of that item)
int find_nth(struct node *head, int nth) {
	if (head == NULL) {
    	printf("Entered an empty list!\n");
    	exit(1);
    }
    struct node *curr = head;
    for (int k = 1; k < nth; k++) {
    	curr = curr->next;
    }
    return curr->data;
}

//add item at the end of the list (return a pointer to the head of the list)
struct node *add_last(struct node *head, int item) {
    struct node *curr = head;
    while (curr->next != NULL) {
    	curr = curr->next;
    }
    curr->next = create_node(item);
    return head;
}
//Add a node to the nth position
//This assumes that the input are valid
struct node *add_nth(struct node *head, int item, int nth) {
	struct node *curr = head;
	struct node *prev = head;
	struct node *newNode = create_node(item);
	int position = 1;
	// Conisder if list is inserted at the beginning
	if (nth == 1) {
		newNode->next = head;
		return newNode;
	}
	
	while (curr != NULL && position < nth) {
		prev = curr;
		curr = curr->next;
		position++;
	}
	newNode->next = curr;
	prev->next = newNode;
	return head;
}

//remove first item from a list (return a pointer to the head of the list)
struct node *remove_first(struct node *head) {
    struct node *curr = head;
    head = head->next;
    free(curr);
    return head;
}

//remove last item from a list (return a pointer to the head of the list)
struct node *remove_last(struct node *head) {
    struct node *curr = head;
    struct node *prev = NULL;
    while (curr->next != NULL) {
    	prev = curr;
    	curr = curr->next;
    }
    prev->next = NULL;
    free(curr);
    return head;
}


//remove a given item (say 25) from a list (return a pointer to the head of the list)
struct node *remove_item(struct node *head, int item) {
    struct node *curr = head;
    struct node *prev = head;
    //consider three cases   
    //removal of a node at the beginning, in between or object was not found.
    //Removal of a linked list at the middle or end
    while (curr != NULL && curr->data != item) {
		prev = curr;
    	curr = curr->next;
    }
    if (curr != NULL) {
		if (curr->data == item && curr == head) {
			curr = curr->next;
			free (prev);
			return curr;
		}
		else if (curr->data == item) {
			prev->next = curr->next;
			free(curr);
			return head;
		}
	}
	else {
		printf("Desired data was not found\n");
	}
    return head;

}
//Removes a node at the nth position.
//This assumes all input are valid
struct node *remove_nth(struct node *head, int nth) {
	struct node *curr = head;
	struct node *prev = head;
	if (nth == 1) {
		curr = curr->next;
		free(head);
		return curr;
	}
	int position = 1;
	while (position < nth && curr->next != NULL) {
		prev = curr;
		curr = curr->next;
		position++;
	}
	prev->next = curr->next;
	free(curr);
	return head;
}

// free the memory used by the linked list
void free_list(struct node *head) {
    // TODO: complete this function
    
}
