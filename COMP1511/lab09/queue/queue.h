// Abstract Data Type Queue demo
// Marc Chee, April 2019

// This file describes the interface to a queue of ints
// It must be included in other code files to be of use

// ======================================================
// The type "Queue" refers to a queue_internals pointer.
// In other files, programs can use Queue, but they will
// not get direct access to the Queue's internal workings
// nor will they know exactly what they are
typedef struct queueInternals *Queue;

// ======================================================
// These functions are the only way external code can
// manipulate a Queue.

// functions to create and destroy Queues
Queue queueCreate();
void queueFree(Queue q);

// Add and remove items from queues
// Removing the item returns the item for use
void queueAdd(Queue q, int item);
int queueRemove(Queue q);

// Check on the size of the queue
int queueSize(Queue q);
