// Main file for Queue Abstract Data Type demo
// Marc Chee, April 2020

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
	printf("Creating the Queue for Ice Cream.\n");
	Queue iceQueue = queueCreate();
	int id = 1;
	printf("Person %d joins the queue!\n", id);
	queueAdd(iceQueue, id);
	id = 2;
	printf("Person %d joins the queue!\n", id);
	queueAdd(iceQueue, id);
	id = 3;
	printf("Person %d joins the queue!\n", id);
	queueAdd(iceQueue, id);

	
	while (queueSize (iceQueue) > 0) {
		printf("Person %d just got their ice cream!\n", queueRemove(iceQueue));
		printf("There are %d people left in the queue\n", queueSize(iceQueue));
	}
	printf("Person %d just got their ice cream!\n", queueRemove(iceQueue));
	printf("There are %d people left in the queue\n", queueSize(iceQueue));
	//queueFree(iceQueue);
	
    return 0;
}
