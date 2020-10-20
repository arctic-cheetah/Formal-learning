
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define MAX 9999

//A helper function that gets the smallest vertex
int nextNode(Graph g, int nV, int *dist, int *hasVisited) {
	int curr = 0;
	int min = MAX;
	
	int i = 0;
	while (i < nV) {
		if (!hasVisited[i] && dist[i] < min) {
			min = dist[i];
			curr = i;
		}
		i +=1;
	}
	
	return curr;
}

//A helper function to print an array
void print_array (int *array, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int furthestReachable(Graph g, int src) {
	int nV = GraphNumVertices(g);
	
	int *hasVisited = calloc(nV, sizeof(Vertex));
	int *dist = calloc(nV, sizeof(Vertex));
	
	for (int i = 0; i < nV; i +=1) {
		dist[i] = MAX;
	}
	
	dist[src] = 0;
	
	int i = 0;
	while (i < nV) {
	
		int curr = nextNode(g, nV, dist, hasVisited);
		hasVisited[curr] = 1;
		
		int j = 0;
		while (j < nV) {
			int newDist = GraphIsAdjacent(g, j, curr) + dist[curr];
			if (newDist < dist[j] && GraphIsAdjacent(g, j, curr) 
				&& !hasVisited[j]) {
				dist[j] = newDist;
			}
			
			j +=1;
		}
	
		i+=1;
	}
	
	
	for (int j = 0; j < nV; j +=1) {
		if (dist[j] == MAX) {
			dist[j] = -1;
		}
	}
	
	//print_array(dist, nV);
	
	//Obtain the vertex with the greatest distance
	i = 0;
	int max = 0;
	int maxDist = 0;
	while (i < nV) {
		if (dist[i] >= maxDist) {
			maxDist = dist[i];
			max = i;
		}
		i +=1;
	}
	
	free(hasVisited);
	free(dist);
	
	return max;
}

