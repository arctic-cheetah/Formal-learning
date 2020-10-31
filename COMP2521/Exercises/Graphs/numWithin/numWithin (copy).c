
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void print_array(int *array, int length) {
	for (int i = 0; i < length && array[i] >= 0; i +=1) {
		printf("%d ", array[i]);
	}
	printf("\n");
} 
//https://stackoverflow.com/questions/23243831/optimal-way-to-calculate-all-nodes-at-distance-less-than-k-from-m-given-nodes
int numWithin(Graph g, int src, int dist) {
	//Track all the visited nodes
	int nV = GraphNumVertices(g);
	int *hasVisited = calloc(nV, sizeof(Vertex));
	int *hasChecked = calloc(nV, sizeof(Vertex));
	hasChecked[src] = 1;
	
	Queue q = QueueNew();
	
	//Begin from the source
	QueueEnqueue(q, src);
	int distFromSrc = -1;
	int curr;
	
	while (QueueSize(q) && distFromSrc < dist) {
		
		//Mark the current node as visited
		curr = QueueDequeue(q);
		hasVisited[curr] = 1;
		distFromSrc +=1;
		
		//add all the adjacent vertices of the current node
		int i = 0;
		while (i < nV) {
			if (GraphIsAdjacent(g, curr, i) && !hasVisited[i]) {
				hasChecked[i] = 1;
				QueueEnqueue(q, i);
			}
			i +=1;
		}
	}
	int inRange = 0;
	int i = 0;
	while (i < nV) {
		if (hasChecked[i]) {
			inRange +=1;
		}
		i +=1;
	}
	
	print_array(hasVisited, nV);
	print_array(hasChecked, nV);	
		
	free(hasVisited);
	QueueFree(q);
	return inRange;
}

