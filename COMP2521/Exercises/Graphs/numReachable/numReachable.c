
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

//Find the number of reachable nodes via DFS algorithm

void print_array (int *array, int length) {
	for (int i = 0; i < length; i +=1) {
		printf("%d ", array[i]);
	}
	printf("\n");
}


void DFS (Graph g, Vertex v, int *hasVisited) {
	int nV = GraphNumVertices(g); 
	int i = 0;
	//mark the current node as visited
	hasVisited[v] = 1;
	while (i < nV) {
		//Continue searching only if the node is adjacent and hasn't been
		//visited
		if (!hasVisited[i] && GraphIsAdjacent(g, v, i)) {
			DFS(g, i, hasVisited);
		}
		i +=1;
	}
	
}


int numReachable(Graph g, int src) {
	
	int nV = GraphNumVertices(g);
	int *hasVisited = calloc(nV , sizeof(Vertex));
	DFS(g, src, hasVisited);
	int i = 0;
	int reachable = 0;
	while (i < nV) {
		if (hasVisited[i]) {
			reachable +=1;
		}
		i+=1;
	}
	
	//print_array(hasVisited, nV);
	free(hasVisited);
	return reachable;
}

