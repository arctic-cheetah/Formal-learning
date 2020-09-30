#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    int          data;
};

void print_list(struct node *head);

struct node *strings_to_list(int len, char *strings[]);

int main(int argc, char *argv[]) {
   // TODO: Write some test cases for your functions  
   char *list1[] = {"2", "4", "8", "16"};
   struct node *head1 = strings_to_list(4, list1);
   print_list(head1);
   char *list2[] = {"1", "2", "3", "4"};
   struct node *head2 = strings_to_list(4, list2);
   print_list(head2);
   

   return 0;
}

struct node *strings_to_list(int len, char *strings[]) {
	struct node *head = NULL;
	for (int j = len; j > 0; j--) {
		struct node *newNode = malloc (sizeof (struct node)); 
		newNode->data = atoi(strings[j]);
		newNode->next = head;
	}
	
	return head;	
}

//Prints a linked list, in increasing order
void print_list(struct node *head) {
	struct node *curr = head
	
	

}




























