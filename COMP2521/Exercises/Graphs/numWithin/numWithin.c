
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define INF 9999

void print_array(int *array, int length) {
	for (int i = 0; i < length && array[i] >= 0; i +=1) {
		printf("%d ", array[i]);
	}
	printf("\n");
} 

//A helper function that gets the node with the smallest distance
int smallDist (Graph g, int *hasVisited, int *dist) {
	int nV = GraphNumVertices(g);
	int minDist = INF;
	int curr = 0;
	for (int i = 0; i < nV; i +=1) {
		if (dist[i] < minDist && !hasVisited[i]) {
			minDist = dist[i];
			curr = i;
		}
	}
	return curr;
}

//Using djikstra's algorithm
//Count the number of nodes within a distance
int numWithin(Graph g, int src, int distVert) {
	int nV = GraphNumVertices(g);
	int *hasVisited = calloc(nV, sizeof(Vertex));
	int *dist = calloc(nV, sizeof(Vertex));
	
	// set all the distance of the vertices to infinity
	for (int i = 0; i < nV; i +=1) {
		dist[i] = INF;
	}
	dist[src] = 0;
	
	int i = 0;
	while (i < nV) {
		//get the current node
		int curr = smallDist(g, hasVisited, dist);
		//Remove the curr node from the unexplored set
		hasVisited[curr] = 1;
		int j = 0;
		while (j < nV) {
		
			int newDist = GraphIsAdjacent(g, curr, j) + dist[curr]; 
			if (newDist < dist[j] && !hasVisited[j] 
			    && GraphIsAdjacent(g, curr, j)) {
				dist[j] = newDist;
			}
			
			j +=1;
		}
		i +=1;
	}
	//Get all the vertices that are less that distVert
	i = 0;
	int numVert = 0;
	while (i < nV) {
		if (dist[i] <= distVert) {
			numVert +=1;
		}
		i +=1;
	}
	
	/*
	print_array(hasVisited, nV);
	print_array(dist, nV);
	*/
	free(hasVisited);
	free(dist);
	
	return numVert;
}












































