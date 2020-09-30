#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Queue.h"

static void testQueue1(void);
static void testQueue2(void);
static void testQueue3(void);
void time_trial (void);

	// TODO
	// Write a benchmark test to demonstrate the difference between
	// ArrayQueue and CircularArrayQueue

int main(void) {
	time_trial();
}
//A function which returns the duration of time to execute a program
void time_trial (void) {

	clock_t test = clock();
	testQueue1();
	test = clock() - test;
	double time_taken = ((double)test) / CLOCKS_PER_SEC;
	printf("Test 1 took %f seconds to execute\n\n", time_taken);
	
	test = clock();
	testQueue2();
	test = clock() - test;
	time_taken = ((double)test) / CLOCKS_PER_SEC;
	printf("Test 2 took %f seconds to execute\n\n", time_taken);
	
	test = clock();
	testQueue3();
	test = clock() - test;
	time_taken = ((double)test) / CLOCKS_PER_SEC;
	printf("Test 3 took %f seconds to execute\n\n", time_taken);
}

//Test1 Enqueue
static void testQueue1(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 30000; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 30000);
	QueueFree(q);
}

//Test2 Enqueue and Dequeue
static void testQueue2(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 30000; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 30000);
	
	for (int j = 1; j <= 30000; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 0);
	
	QueueFree(q);
}

//Test3 Enqueue and Dequeue in an alternating fashion
static void testQueue3(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 30000; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 30000);
	
	for (int j = 1; j <= 15000; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	
	for (int i = 30001; i <= 45000; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 30000);
	
	for (int j = 15001; j <= 45000; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	
	QueueFree(q);
}









