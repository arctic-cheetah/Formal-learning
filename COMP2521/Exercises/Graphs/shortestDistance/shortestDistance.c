
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define INF 9999

//https://stackoverflow.com/questions/41821033/find-distance-between-two-nodes-in-an-undirected-and-unweighted-graph/45659508


//A helper function to print the array
void print_array (int *array, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

//Find a vertex which has not been visited to find the minimum distance
int MinDistance(int *NodeDistance, int *HasVisited, int size) {
	int min = INF;
	int min_index = 0;
	
	for (int i = 0; i < size; i +=1) {
		if (!HasVisited[i] && NodeDistance[i] <= min) {
			min = NodeDistance[i];
			min_index = i;
		}
	}
	
	return min_index;	
}


//Need to use Dijkstra's algorithm

int shortestDistance(Graph g, int src, int dest) {

	//
	if (src == dest) {
		return 0;
	}
	
	//Remember we count from zero
	int size = GraphNumVertices(g);

	int *HasVisited = calloc(GraphNumVertices(g), sizeof(Vertex));
	int *NodeDistance = calloc(GraphNumVertices(g), sizeof(Vertex));
	int *pred = calloc(GraphNumVertices(g), sizeof(Vertex));
	//Set the distance of all the nodes to INF except starting vertex
	for (int i = 0; i < size; i +=1) {
		NodeDistance[i] = INF;
	}
	NodeDistance[src] = 0;
	
	//Loop until all the vertices have been visited
	int i = 0;
	while (i < size) {
	
		//Obtain a vertex that has not been visited
		int v = MinDistance(NodeDistance, HasVisited, size);
		//Mark the visited vertex
		HasVisited[v] = 1;
		
		int j = 0;
		while (j < size) {
			int newDist =  NodeDistance[v] + GraphIsAdjacent(g, v, j);
			//Update the distance of the selected vertex
			if (!HasVisited[j] && GraphIsAdjacent(g, v, j)
				&& newDist < NodeDistance[j]
				) {
				pred[j] = v;
				NodeDistance[j] = newDist;
			}
			
			j +=1;
		}
		
		i +=1;
	}
	int distance;
	printf("\n\n");
	//print_array(NodeDistance, size);
	//print_array(HasVisited, size);
	//print_array(pred, size);
	if (NodeDistance[dest] == INF) {
		distance = -1;
	}
	else {
		distance = NodeDistance[dest];
	} 
	free(HasVisited);
	free(NodeDistance);
	free(pred);
	return distance;
}



























