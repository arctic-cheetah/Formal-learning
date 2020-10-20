
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define MAX 1023

//Find the number of reachable nodes via Dijkstra's algorithm

//A helper function that returns the next node in Dijkstra's algorithm
int getNextNode(int *HasVisited, int *vSet, int numVertex){
	
	int currNode = 0;
	int smallDist = MAX;
	
	for (int i = 0; i < numVertex; i +=1) {
		if (vSet[i] <= smallDist && !HasVisited[i]) {
			smallDist = vSet[i];
			currNode = i;
		}
	}
	return currNode;
}

void print_array (int *array, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int numReachable(Graph g, int src) {
	//create a vertex set
	int numVertex = GraphNumVertices(g);
	//the vertex set that holds the distance from the source
	int *vSet = calloc(numVertex, sizeof(Vertex));
	//The set that tracks the explored vertices
	int *HasVisited = calloc(numVertex, sizeof(Vertex));
	
	for (int i = 0; i < numVertex; i +=1) {
		vSet[i] = MAX;
	}	
	
	vSet[src] = 0;
	
	int i = 0;
	while (i < numVertex) {
		
		int curr = getNextNode(HasVisited, vSet, numVertex);
		HasVisited[curr] = 1;
		
		//j is the neighbour
		int j = 0;
		while (j < numVertex) {
			int newDist = vSet[curr] + GraphIsAdjacent(g, curr, j);
			
			if (newDist < vSet[j] && !HasVisited[j] 
				&& GraphIsAdjacent(g, curr, j)) {
				
				vSet[j] = newDist;
			}
			
			j +=1;
		}
		i +=1;
	}
	
	i = 0;
	int reachable = 0;
	while (i < numVertex) {
		if (vSet[i] != MAX) {
			reachable +=1;
		}
		i +=1;
	}
	free(vSet);
	free(HasVisited);
	
	return reachable;
}

