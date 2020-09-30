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
void stack_push (struct stack *BracketStack, char c);
char stack_pop (struct stack *BracketStack);
void print_stack (struct stack *s);
int check_data (struct stack *BracketStack);
struct stack *back_up (struct stack *BracketStack);
void corrected_invalid(struct stack *BracketStack);

int main() {
	int Valid = 1;
	char c = getchar();
	struct stack *BracketStack = stackCreate();
	while (c != EOF) {
		//Check if c is any of the brackets
		if (c == '(' || c == '{' || c == '[' || c == '<' || c == ')' || c == '}' 															|| c == '>' || c == ']') 
		{
			stack_push(BracketStack, c);
		}
		
		c = getchar();
	}
	//Compare the inputs
	struct stack *backUp = back_up(BracketStack);
	Valid = check_data(BracketStack);
	if (Valid == 1) {
		printf("Valid Sequence!\n");
	} 
	else {
		printf("Invalid Sequence, the correct closing sequence is: \n");
		corrected_invalid(backUp);
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

char stack_pop (struct stack *BracketStack) {
	
	if (BracketStack->tail == NULL) {
		return '\0';
	}
	char returnChar = BracketStack->tail->data;
	//Account for removal of the last element
	if (BracketStack->tail->prev == NULL) {
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
	return returnChar;
}

void print_stack (struct stack *s) {
	struct node *curr = s->head;
	printf("%d\n", s->size);
	while (curr != NULL) {
		printf("%c\n", curr->data);
		curr = curr->next;
	}
}

//Copy the stack
struct stack *back_up (struct stack *BracketStack) {
	struct stack *newStack = stackCreate();
	struct node *copycur = BracketStack->head;
	
	while (copycur != NULL) {
		stack_push(newStack, copycur->data);
		copycur = copycur->next;
	}
	//print_stack(newStack);
	return newStack;
}



int check_data (struct stack *BracketStack) {
	if (BracketStack->head == NULL) {
		return 1;
	}
	struct node *curr = BracketStack->head;
	struct stack *openBracket = stackCreate();
	int c;
	while (curr != NULL) {
		if (curr->data == '(' || curr->data == '{' || curr->data == '[' 													|| curr->data == '<') 
		{
			stack_push(openBracket, curr->data);
		}
		//This checks for closing brackets
		else if (curr->data == ')' || curr->data == '}' || curr->data == ']' 													|| curr->data == '>') 
		{
			c = stack_pop(openBracket);
			if (c == '(' && curr->data != ')') {
				return 0;
			}
			else if (c == '[' && curr->data != ']') {
				return 0;
			}
			else if (c == '{' && curr->data != '}') {
				return 0;
			}
			else if (c == '<' && curr->data != '>') {
				return 0;
			}
			else if (c == '\0') {
				return 0;
			}
		
		}
		//Check if there are remaining open brackets
		curr = curr->next;
		
	}
	if (openBracket->size != 0) {
		return 0;
	}
	return 1;
}


void corrected_invalid (struct stack *BracketStack) {
	struct node *curr = BracketStack->head;
	struct stack *openBracket = stackCreate();
	int c;
	while (curr != NULL) {
		if (curr->data == '(' || curr->data == '{' || curr->data == '[' 													|| curr->data == '<') 
		{
			stack_push(openBracket, curr->data);
		}
		
		else if (curr->data == ')' || curr->data == '}' || curr->data == ']' 													|| curr->data == '>') 
		{
			c = stack_pop(openBracket);
			if (c == '(' && curr->data != ')') {
				printf(")\n");
			}
			else if (c == '[' && curr->data != ']') {
				printf("]\n");
			}
			else if (c == '{' && curr->data != '}') {
				printf("}\n");
			}
			else if (c == '<' && curr->data != '>') {
				printf(">\n");
			}
		
		}
		
		curr = curr->next;
	}
	//printf("%d\n", openBracket->size);
	if (openBracket->size != 0) {
		char c2;
		//printf("%d\n", openBracket->size);
		while (openBracket->size != 0) {
			c2 = stack_pop(openBracket);
			if (c2 == '(') {
				printf(")\n");
			}
			else if (c2 == '[') {
				printf("]\n");
			}
			else if (c2 == '{') {
				printf("}\n");
			}
			else if (c2 == '<') {
				printf(">\n");
			}
		}
	}
}









































/*
//Check the both stacks
void check_data (struct stack *openBracket, struct stack *closedBracket, int *Validp) {
	struct node *curr1 = openBracket->tail;// THIS IS THE TOP OF THE STACK
	struct node *curr2 = closedBracket->head;
	int Valid = 1;
	
	//Account if both are empty
	if (curr1 == NULL && curr2 == NULL) {
		Valid = 1;
	}
	while (curr1 != NULL && curr2 != NULL) {
	
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
		curr1 = curr1->prev;
		curr2 = curr2->next;
	
	}
	
	if (curr1 == NULL && curr2 != NULL) {
		Valid = 0;
	}
	else if (curr1 != NULL && curr2 == NULL) {
		Valid = 0;
	}
	
	if (Valid == 1) {
		*Validp = 1;
	}
	else {
		*Validp = 0;
	}
	
}*/


