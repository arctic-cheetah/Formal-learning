
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define INF 0xFFFFFFF

int unexploredSet(Graph g, int *hasVisited, int *dist) {
	int nV = GraphNumVertices(g);
	int currDist = INF;
	int v = 0;
	
	for (int i = 0; i < nV; i +=1) {
		if (dist[i] < currDist && !hasVisited[i]) {
			v = i;
			currDist = dist[i];
		}
	}
	
	return v;
}

//Use Dijkstra's algorithm
int furthestReachable(Graph g, int src) {
	int nV = GraphNumVertices(g);
	
	int *hasVisited = (int *)calloc(nV, sizeof(int));
	int *dist = (int *)calloc(nV, sizeof(int));
	for (int i = 0; i < nV; i +=1) {
		dist[i] = INF;
	}
	
	dist[src] = 0;
	
	for (int i = 0; i < nV; i +=1) {
		int curr = unexploredSet(g, hasVisited, dist);
		hasVisited[curr] = 1;
		
		for (int w = 0; w < nV; w +=1) {
			int newDist = dist[curr] + GraphIsAdjacent(g, curr, w);
			if (newDist < dist[w] && !hasVisited[w] 
				&& GraphIsAdjacent(g, curr, w)) {
				dist[w] = newDist;
			}
			
		}
	}
	//Set all dist from inf to -1
	for (int i = 0; i < nV; i +=1) {
		if (dist[i] == INF) {
			dist[i] = -1;
		}
	}
	
	//Fetch the furthest reachable vertex
	int furthest = 0;
	for (int i = 0; i < nV; i +=1) {
		if (dist[i] >= dist[furthest]) {
			furthest = i;
		}
	}
	
	
	free(dist);
	free(hasVisited);
	return furthest;
}

