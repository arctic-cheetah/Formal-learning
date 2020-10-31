
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

//A DFS function that searches for the number of vertices
//within a distance

//ISSUE, it will double count due to loops
int DFS (Graph g, Vertex prev, Vertex curr, 
		 int *hasVisited, int dist, int currDist) {
	int inRange = 0;
	hasVisited[curr] = 1;
	//Base case: if the currDist is == dist
 	if (currDist >= dist) {
 		return inRange;
 	}
	int nV = GraphNumVertices(g);
	
	//Recursive case: continue searching for other vertices
	int i = 0; 
	while (i < nV) {
		if (GraphIsAdjacent(g, curr, i) && !hasVisited[i]) {
			inRange += DFS(g, curr, i, hasVisited, dist, currDist + 1) + 1;
		}
		
		i +=1;
	}
	
	return inRange;
}

//Use DFS to find the number of vertices
int numWithin(Graph g, int src, int dist) {
	//Track all the visited nodes
	int nV = GraphNumVertices(g);
	int *hasVisited = calloc(nV, sizeof(Vertex));
	hasVisited[src] = 1;
	
	if (dist == 0) {
		return 1;
	}
	
	int inRange = DFS(g, src, src, hasVisited, dist, 0) + 1;
	
	return inRange;
}

