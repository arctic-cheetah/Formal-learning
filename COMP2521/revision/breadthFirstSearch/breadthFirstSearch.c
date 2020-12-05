
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"
#define NOT_VISITED -1

void breadthFirstSearch(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *hasVisited = (int *) calloc(nV, sizeof(int));
	
	for (int i = 0; i < nV; i+=1) {
		hasVisited[i] = NOT_VISITED;
	}
	//Mark the source as visited
	hasVisited[src] = src;
	
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	
	while (!QueueIsEmpty(q)) {
		int curr = QueueDequeue(q);
		printf("%d ", curr);
		for (int w = 0; w < nV; w +=1) {
			if (GraphIsAdjacent(g, curr, w) && hasVisited[w] == NOT_VISITED) {
				hasVisited[w] = curr;
				QueueEnqueue(q, w);
			}
		}
	}
	QueueFree(q);
	free(hasVisited);
}

