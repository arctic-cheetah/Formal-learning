//A program that utilises depth first search with recursion
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
void DFS(Graph g, int src, int *track) {
	int vertices = GraphNumVertices(g); //O(1)
	//An array that tracks each node;
	printf("%d ", src);
	track[src] = 1;
	int i = 0;
	while (i < vertices) {
		//Check if recursion is needed
		if (GraphIsAdjacent(g, src, i) && !track[i]) {
			DFS(g, i, track);
		}
		i +=1;
	}
}

void depthFirstSearch(Graph g, int src) {
	int nV = GraphNumVertices(g);
	int *track = malloc(sizeof(int) * vertices);

	//set track to zero
	for (int i = 0; i < vertices; i +=1) {
		track[i] = 0;
	}
	//An array that tracks each node;
	DFS(g, src, track);
	free(track);
}
