
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define INF 9999


//A helper function to print the array
void print_array (int *array, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int MinDistance (int length, int *NodeDistance, int *HasVisited) {
	//Find a vertex which has not been visited to find the minimum distance
	int min = INF;
	int currNode;
	for (int i = 0; i < length; i+=1) {
		if (NodeDistance[i] <= min && !HasVisited[i]) {
			min = NodeDistance[i];
			currNode = i; 
		}
	}
	return currNode;
}


//Need to use Dijkstra's algorithm

int shortestDistance(Graph g, int src, int dest) {

	if (src == dest && GraphIsAdjacent(g, src, dest) ) {
		return 0;
	}
	
	int NumOfVertex = GraphNumVertices(g);
	int *NodeDistance = calloc(NumOfVertex, sizeof(Vertex) );
	int *HasVisited = calloc(NumOfVertex, sizeof(Vertex) );
	
	for (int i = 0; i < NumOfVertex; i +=1) {
		NodeDistance[i] = INF;
	}
	NodeDistance[src] = 0;
	
	int i = 0;
	while (i < NumOfVertex) {
		
		//Find the the current node with the smallest distance
		//This will always initally be the src vertex 
		int currNode = MinDistance(NumOfVertex, NodeDistance, HasVisited);
		HasVisited[currNode] = 1;
		
		int j = 0;
		while (j < NumOfVertex) {
			
			int newDist = GraphIsAdjacent(g, currNode, j) + NodeDistance[currNode];
			if (newDist < NodeDistance[j] 
			&& GraphIsAdjacent(g, currNode, j)  && !HasVisited[j]
			) {
				NodeDistance[j] = newDist;
			}

			j +=1;
		}
		
		i +=1;
	}
	
	//print_array(NodeDistance, NumOfVertex);
	
	int distance;
	if (NodeDistance[dest] == INF) {
		distance = -1;
	}
	else {
		distance = NodeDistance[dest];
	}
	free(NodeDistance);
	free(HasVisited);
	
	return distance;
}	



























