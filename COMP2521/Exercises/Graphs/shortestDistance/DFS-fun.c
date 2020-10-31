
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

void DFS (Graph g, Vertex v, int *hasVisited, int *dist, int distance) {
	int i = 0;
	int nV = GraphNumVertices(g);
	
	hasVisited[v] = 1;
	dist[v] = distance;
	while (i < nV) {
		if (!hasVisited[i] && GraphIsAdjacent(g, v, i)) {
			DFS (g, i, hasVisited, dist, distance + 1);
		}
		i+=1;
	}
}

//Need to use Dijkstra's algorithm

int shortestDistance(Graph g, int src, int dest) {
	int nV = GraphNumVertices(g);
	int *hasVisited = calloc(nV, sizeof(Vertex));
	int *dist = calloc(nV, sizeof(Vertex));
	
	DFS(g, src, hasVisited, dist, 0);
	
	print_array(dist, nV);
	print_array(hasVisited, nV);
	
	for (int i = 0; i < nV; i +=1) {
		if (!dist[i]) {
			dist[i] = -1;
		}
	}
	dist[src] = 0;
	print_array(dist, nV);
	print_array(hasVisited, nV);
	
	
	return 0;
}	



























