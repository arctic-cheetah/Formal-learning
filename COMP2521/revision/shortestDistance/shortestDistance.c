
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define NOT_VISITED -1
#define INF 0xffff

//A helper function to fetch an unvisited node
int unexploredSet(Graph g, int *hasVisited, int *dist) {
	int nV = GraphNumVertices(g);
	int vertex = 0;
	int currDist = INF;
	for (int i = 0; i < nV; i +=1) {
		if (dist[i] < currDist && !hasVisited[i]) {
			currDist = dist[i];
			vertex = i;
		}
		
	}
	
	return vertex;
}

int shortestDistance(Graph g, int src, int dest) {
	int nV = GraphNumVertices(g);
	
	int *hasVisited = (int *)calloc(nV, sizeof(int));
	int *dist = (int *)calloc(nV, sizeof(int));
	int *pred = (int *)calloc(nV, sizeof(int));
	
	for (int i = 0; i < nV; i +=1) {
		dist[i] = INF;
		pred[i] = NOT_VISITED;
	}
	//Mark the src node with a dist of 0
	dist[src] = 0; 
	pred[src] = src;
	
	for (int i = 0; i < nV; i +=1) {
		int curr = unexploredSet(g, hasVisited, dist);
		hasVisited[curr] = 1;
		
		for (int w = 0; w < nV; w +=1) {
			int newDist = dist[curr] + GraphIsAdjacent(g, curr, w);
			if (newDist < dist[w] && GraphIsAdjacent(g, curr, w) 
				&& !hasVisited[w]) {
				dist[w] = newDist;
				pred[w] = curr;
			}
			
		}
	}
	int target = dist[dest];
	free(dist);
	free(hasVisited);
	free(pred);
	if (target == INF) {
		return -1;
	}
	
	return target;
}

