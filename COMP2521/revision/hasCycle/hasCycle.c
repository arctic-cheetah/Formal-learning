
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

#define NOT_VISITED -1

//A helper function that return 1 if a cycle exits
int DFS (Graph g, int src, int prev, int *hasVisited) {
	int nV = GraphNumVertices(g);
	hasVisited[src] = 1;
	
	for (int w = 0; w < nV; w +=1) {
		if (GraphIsAdjacent(g, src, w)) {
			if (hasVisited[w] == -1) {
				if (DFS(g, w, src, hasVisited)) {
					return true;
				}
			}
			//You have indeed visited another vertex
			else if (w != prev) {
				return true;
			}
		}
	}
	return false;
}

bool hasCycle(Graph g) {
	int nV = GraphNumVertices(g);
	bool result = false;
	int *hasVisited = (int *) calloc(nV, sizeof(int));
	//Check each vertex
	for (int i = 0; i < nV; i +=1) {
		// reset the visited array
		for (int i = 0; i < nV; i +=1) {
			hasVisited[i] = NOT_VISITED;
		}
		if (DFS(g, i, i, hasVisited)) {
			result = true;
			break;
		}
	}
	free(hasVisited);
	
	return result;
}

