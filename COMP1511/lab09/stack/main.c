// Abstract Data Types Demo
// Using a stack
// Marc Chee, April 2019

#include <stdio.h>

#include "stack.h"

int main(void) {
    Stack deck = stackCreate();
    int card = 42;
    printf("Pushing %d on top of the deck.\n", card);
    stackPush(deck, card);
    card = 37;
    printf("Pushing %d on top of the deck.\n", card);
    stackPush(deck, card);
    card = 13;
    printf("Pushing %d on top of the deck.\n", card);
    stackPush(deck, card);
    
    while (stackSize(deck) != 0) { 
		printf("Taking %d off the top of the deck.\n", stackPop(deck));
		printf("There are %d cards remaining on the deck\n", stackSize(deck));
	}
	
}

