
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

static void testQueue1(void);
static void testQueue2(void);
static void testQueue3(void);
static void testQueue4(void);
static void testQueue5(void);
static void testQueue6(void);
static void testQueue7(void);
static void testQueue8(void);
static void testQueue9(void);
static void testQueue10(void);
static void testQueue11(void);
static void testQueue12(void);

int main(void) {
	testQueue1();
	testQueue2();
	testQueue3();
	testQueue4();
	testQueue5(); 
	testQueue6();
	testQueue7();
	testQueue8();
	testQueue9();
	testQueue10();
	testQueue11();
	testQueue12();
	
	printf("All tests passed!\n");
}

// tests general enqueueing and dequeueing
static void testQueue1(void) {
	Queue q = QueueNew();
	
	// enqueue 1 to 10
	for (int i = 1; i <= 10; i++) {
		QueueEnqueue(q, i);
		assert(QueueSize(q) == i);
	}
	
	// dequeue 1 to 5
	for (int j = 1; j <= 5; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 5);
	
	// enqueue 11 to 20, dequeue 6 to 15
	for (int i = 11, j = 6; i <= 20; i++, j++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 5);
	
	// dequeue 16 to 20
	for (int j = 16; j <= 20; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 0);
	assert(QueueIsEmpty(q));
	
	// enqueue a number
	QueueEnqueue(q, 21);
	assert(QueueFront(q) == 21);
	QueueFree(q);
}

// tests enqueueing and dequeueing at capacity
static void testQueue2(void) {
	Queue q = QueueNew();
	
	// enqueue 1 to 16
	for (int i = 1; i <= 16; i++) {
		QueueEnqueue(q, i);
		assert(QueueSize(q) == i);
	}
	
	// dequeue 1 to 8, enqueue 17 to 24
	for (int i = 17, j = 1; i <= 24; i++, j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 16);
	QueueFree(q);
}
//Issue lies here 
// tests resizing of the queue----FIXED
static void testQueue3(void) {
	Queue q = QueueNew();
	// enqueue 1 to 24
	//Stuck at inserting 17
	for (int i = 1; i <= 24; i++) {
		QueueEnqueue(q, i);
	}
	// dequeue 1 to 8
	for (int j = 1; j <= 8; j++) {
		assert(QueueDequeue(q) == j);
	}
	
	// dequeue 9 to 72, enqueue 25 to 88
	for (int i = 25, j = 9; i <= 88; i++, j++) {
		QueueEnqueue(q, i);
		assert(QueueDequeue(q) == j);
	}
}


//MY TESTS
//Testing Wrapping around and reallocation of memory at the middle
static void testQueue4(void) {
	Queue q = QueueNew();
	
	
	for (int i = 1; i <= 16; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 16);
	// dequeue 1 to 4
	for (int j = 1; j <= 4; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 12);
	// Enqueue 17 to 25 (9 elements REMEMBER INCLUSIVITY)
	// This forces the queue to wrap around and reallocate new memory
	for (int i = 17; i <= 25; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 21);
	
	for (int i = 26; i <= 99; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 95);
	//printf("FRONT: %d\n", QueueFront(q));
	assert(QueueDequeue(q) == 5);
	
	QueueFree(q);
}

//Test Wrapping around and reallocation of memory when frontIndex is
//in the middle but not at the end or beginning of the array
static void testQueue5(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 16; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 16);
	
	// dequeue 1 to 6
	for (int j = 1; j <= 6; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 10);
	// Enqueue 17 to 43 (27 elements REMEMBER INCLUSIVITY)
	for (int i = 17; i <= 43; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 37);
	
	// Enqueue 44 to 70 (27 elements REMEMBER INCLUSIVITY)
	for (int i = 44; i <= 70; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 64);
	assert(QueueFront(q) == 7);
	
	//RearIndex is one unit behind frontIndex
	//Check if reallocation is successfull
	for (int i = 71; i <= 71; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 65);
	
	QueueFree(q);
}

//Test Wrapping around and reallocation of memory when frontIndex is at the
//end of the array
static void testQueue6(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 16; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 16);
	
	// dequeue 1 to 15
	for (int j = 1; j <= 15; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 1);
	
	// frontIndex is at the end of the array now
	// enqueue 17 to 31 (Add 15 elements)
	for (int i = 17; i <= 31; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 16);
	
	// rearIndex is one unit behind frontIndex
	for (int i = 32; i <= 32; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 17);
	
	QueueFree(q);
}


//Test frontIndex is at the end of the array and deletion
static void testQueue7(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 16; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 16);
	
	// dequeue 1 to 15
	for (int j = 1; j <= 15; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 1);
	
	// frontIndex is at the end of the array now
	// enqueue 17 to 31 (Add 15 elements)
	for (int i = 17; i <= 31; i++) {
		QueueEnqueue(q, i);
	}
	assert(QueueSize(q) == 16);
	
	// dequeue 16
	for (int j = 16; j <= 16; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueFront(q) == 17);
	assert(QueueSize(q) == 15);
	
	QueueFree(q);
}


//Test memory reallocation
static void testQueue8(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 10000; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 10000);
	QueueFree(q);
}

//Test Deletion and reallocation
static void testQueue9(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 10000; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 10000);
	
	for (int j = 1; j <= 10000; j++) {
		assert(QueueFront(q) == j);
		assert(QueueDequeue(q) == j);
	}
	assert(QueueSize(q) == 0);
	
	QueueFree(q);
}


//Test1 Enqueue
static void testQueue10(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 30000; i++) {
		QueueEnqueue(q, i);
		assert(QueueFront(q) == 1);
	}
	assert(QueueSize(q) == 30000);
	QueueFree(q);
}

//Test2 Enqueue and Dequeue
static void testQueue11(void) {
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
static void testQueue12(void) {
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














