#include <stdio.h>
#include <stdlib.h>


struct stack {
	struct node *head;
	int size;
	
};

struct node {
	struct node *next;
	char data;
};

struct node *create_node (char c);
struct node *add_node (struct node *head, char c);
void check_data (struct node *head, int *Validp);
//void corrected_invalid(struct node *head);

int main() {
	int Valid = 0;
	int *Validp = &Valid;
	char c = getchar();
	struct node *head = NULL;
	int i = 0;
	while (c != EOF) {
		//Check if c is any of the brackets
		if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' 
														|| c == '<' || c == '>') {
			//Create a head only if it is NULL 
			if (head == NULL) {
				head = create_node(c);
			}
			//Store in the linked list
			else {
				head = add_node(head, c);
				check_data(head, Validp);
			}
			//Check the list for correct brackets
			
			//printf("Test\n");
		}
		c = getchar();
		i++;
	}
	
	if (Valid == 1) {
		printf("Valid Sequence!\n");
	} 
	else {
		printf("Invalid Sequence, the correct closing sequence is: \n");
		//corrected_invalid(head);
	}
	
    return 0;
}

//This function creates a new node
struct node *create_node (char c) {
	struct node *newNode = malloc (sizeof(struct node));
	newNode->next = NULL;
	newNode->data = c;
	//printf("%c\n", newNode->data);
	return newNode;
}

//This adds a node the brackets
struct node *add_node (struct node *head, char c) {
	struct node* curr = head;
	struct node* newNode = create_node(c);
	
	//Get to the end of the list
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = newNode;
	return head;
}

//Check the linked list
void check_data (struct node *head, int *Validp) {
	//curr checks for opening brackets
	struct node *curr = head;
	//check checks for closed brackets
	struct node *check = head->next;
	int ThisValid = 1;
	
	//Check if the linked list begins with the closing bracket
	if (head->data == ')') {
		//Return invalid
		ThisValid = 0;	
	}
	else if (head->data == '}') {
		ThisValid = 0;	
	}
	else if (head->data == ']') {
		ThisValid = 0;	
	}
	else if (head->data == '>') {
		ThisValid = 0;	
	}
	
	//Check if linked list is of size one and only begins with an opening bracket
	if (head->next == NULL) {
		*Validp = 0;
	}
	
	
	while (curr->next != NULL )) {
		while (curr->next != NULL && ( curr->next->data != ')' && curr->next->data != '}' 
		&& curr->next->data != ']' && curr->next->data != '>') ) {
			curr = curr->next;
		}
		
	//Loop through the Linked list to search for the closing bracket
		while (check != NULL) {
			//consider cases for the brackets
			if (curr->data == '(' && check->data != ')') {
				ThisValid = 0;
			}
			else if (curr->data == '[' && check->data != ']') {
				ThisValid = 0;
			}
			else if (curr->data == '{' && check->data != '}') {
				ThisValid = 0;
			}
			else if (curr->data == '<' && check->data != '>') {
				ThisValid = 0;
			}
			
			
			check = check->next;
		}
		curr = curr->next;
	}
	//May need to add conditional statements here
	if (ThisValid == 0) {
		*Validp = 0;
	}
	else {
		*Validp = 1;
	}
}
/*
void corrected_invalid(struct node *head) {
	struct node *curr = head;
	struct node *check = head;
	
	//Check if the linked list begins with the closing bracket and is of size 1
	if (head->data == ')') {
		//Return invalid
		printf("(\n");	
	}
	else if (head->data == '}') {
		printf("{\n");	
	}
	else if (head->data == ']') {
		printf("[\n");
	}
	else if (head->data == '>') {
		printf("<\n");
	}
	
	//Check if linked list is of size one and only begins with an opening bracket
	if (head->next == NULL) {
		if (head->data == '(') {
		//Return invalid
			printf(")\n");
		}
		else if (head->data == '{') {
			printf("}\n");
		}
		else if (head->data == '[') {
			printf("]\n");	
		}
		else if (head->data == '<') {
			printf(">\n");
		}
	
	}
	
	
	while (curr->next != NULL) {
	//Loop through the Linked list to search for the closing bracket
		while (check->next != NULL) {
			//consider cases for the brackets
			if (curr->data == '(' && check->data != ')') {
				printf(")\n");
			}
			else if (curr->data == '[' && check->data != ']') {
				printf("]\n");
			}
			else if (curr->data == '{' && check->data != '}') {
				printf("}\n");
			}
			else if (curr->data == '<' && check->data != '>') {
				printf(">\n");
			}
			
			check = check->next;
		}
		curr = curr->next;
	}

}

*/
































