#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 200

struct stack {
	struct node *head;
	struct node *tail;
	int size;
};

struct node {
	struct node *next;
	struct node *prev;
	char data;
};


struct node *create_node (char c);
struct stack *stackCreate();
void stack_push (struct stack *openBracketStack, char c);
void stack_pop (struct stack *BracketStack);
void print_stack (struct stack *s);
void check_data (struct stack *openBracket, struct stack *closedBracket, int *Validp);

int main() {
	int Valid = 1;
	int *Validp = &Valid;
	char c = getchar();
	struct stack *openBracketStack = stackCreate();
	struct stack *closedBracket = stackCreate();
	while (c != EOF) {
		//Check if c is any of the opening brackets brackets
		if (c == '(' || c == '{' || c == '[' || c == '<') {
			stack_push(openBracketStack, c);
		}
		//Check for closed brackets
		else if ( c == ')' || c == '}' || c == '>' || c == ']' ) {
			stack_push(closedBracket, c);
		}
		c = getchar();
	}
	//print_stack(openBracketStack);
	//print_stack(closedBracket);
	check_data(openBracketStack, closedBracket, Validp);
	//Compare the inputs
	if (Valid == 1) {
		printf("Valid Sequence!\n");
	} 
	else {
		printf("Invalid Sequence, the correct closing sequence is: \n");
		//corrected_invalid(head);
	}
	
    return 0;
}

//Create a stack
struct stack *stackCreate() {
	struct stack *newStack = malloc (sizeof (struct stack));
	newStack->size = 0;
	newStack->head = NULL;
	newStack->tail = NULL;
	return newStack;
}

//Add elements to the stack
void stack_push (struct stack *BracketStack, char c) {
	struct node *newNode = malloc (sizeof(struct node));
	newNode->data = c;
	//If the stack was empty
	//Make the first element
	if (BracketStack->tail == NULL) {
		BracketStack->head = newNode;
		BracketStack->tail = newNode;
		newNode->prev = NULL;
	}
	//if not empty, push to the stack
	else {
		BracketStack->tail->next = newNode;
		newNode->prev = BracketStack->tail;
	}
	newNode->next = NULL;
	BracketStack->tail = newNode;
	BracketStack->size++;
}

//Remove a node from the top of the stack
void stack_pop (struct stack *BracketStack) {
	
	if (BracketStack->tail->prev == NULL) {
		
	}
	//Account for removal of the last element
	else if (BracketStack->tail->next == NULL) {
		free(BracketStack->tail);
		BracketStack->tail = NULL;
	}
	//Otherwise
	else {
		BracketStack->tail = BracketStack->tail->prev;
		free(BracketStack->tail->next);
		BracketStack->tail->next = NULL;
	}
	BracketStack->size--;
}

void print_stack (struct stack *s) {
	struct node *curr = s->head;
	printf("%d\n", s->size);
	while (curr != NULL) {
		printf("%c\n", curr->data);
		curr = curr->next;
	}
}

//Check the both stacks
void check_data (struct stack *openBracket, struct stack *closedBracket, int *Validp) {
	struct node *curr1 = openBracket->tail;// THIS IS THE TOP OF THE STACK
	struct node *curr2 = closedBracket->head;
	int Valid = 1;
	
	//Account if both are empty
	if (curr1->prev == NULL && curr2->next == NULL) {
		Valid = 1;
	}
	else {
		while (curr1->prev != NULL && curr2->next != NULL) {
		
			if (curr1->data == '(' && curr2->data != ')') {
				Valid = 0;
			}
			else if (curr1->data == '[' && curr2->data != ']') {
				Valid = 0;
			}
			else if (curr1->data == '{' && curr2->data != '}') {
				Valid = 0;
			}
			else if (curr1->data == '<' && curr2->data != '>') {
				Valid = 0;
			}
			//stack_pop(openBracket);
			curr1 = curr1->prev;
			curr2 = curr2->next;
		}
		
		if (curr1->prev == NULL && curr2->next != NULL) {
			Valid = 0;
		}
		else if (curr1->prev != NULL && curr2->next == NULL) {
			Valid = 0;
		}
		if (Valid == 1) {
			*Validp = 1;
		}
	}
	
}







