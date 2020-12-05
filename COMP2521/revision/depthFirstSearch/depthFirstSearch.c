
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#define NOT_VISITED -1

//A helper function for DFS
void DFS (Graph g, int src, int prev, int *hasVisited) {
	//base case
	int nV = GraphNumVertices(g);
	hasVisited[src] = prev;
	printf("%d ", src);
	//recursive case
	for (int w = 0; w < nV; w +=1) {
		if (GraphIsAdjacent(g, src, w) && hasVisited[w] == NOT_VISITED) {
			DFS(g, w, src, hasVisited);
		}
	}
}

void depthFirstSearch(Graph g, int src) {
	int nV = GraphNumVertices(g);
	
	int *hasVisited = (int *)calloc(nV, sizeof(int));
	for (int i = 0; i < nV; i +=1) {
		hasVisited[i] = NOT_VISITED;
	}
	DFS(g, src, src, hasVisited);
	free(hasVisited);
}

