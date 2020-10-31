#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Dijkstra.h"

#define INF 9999

int main () {

}

//Helper functions:
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

//Print an array
void print_array(int *array, int length) {
	for (int i = 0; i < length && array[i] >= 0; i +=1) {
		printf("%d ", array[i]);
	}
	printf("\n");
} 

//Allocate memory for an array  of  predecessor  lists
PredNode **newPred (Vertex src, int nV) {
	PredNode **pred = malloc(sizeof(struct PredNode) * nV);

	for (int i = 0; i < nV; i +=1) {
		pred[i]->v = i;
		pred[i]->next = NULL;
	}
	return pred;
}


ShortestPaths dijkstra(Graph g, Vertex src) {

	//Allocate memory for fields in ShortestPaths
	int nV = GraphNumVertices(g);
	int *hasVisited = calloc(nV, sizeof(Vertex));
	int *dist = calloc(nV, sizeof(Vertex));
	PredNode **pred = newPred(src, nV);

	//Set fields for ShortestPaths
    ShortestPaths sp;
	sp.numNodes = GraphNumVertices(g);
	sp.src = src;
	sp.dist = dist;
	sp.pred = pred;
	
	// set all the distance of the vertices to infinity
	for (int i = 0; i < nV; i +=1) {
		dist[i] = INF;
	}
	dist[src] = 0;
	
	int i = 0;
	while (i < nV) {
		//get the current node,
		int curr = smallDist(g, hasVisited, dist);
		//Remove the curr node from the unexplored set
		hasVisited[curr] = 1;
		int j = 0;
		while (j < nV) {
			
			//Relaxation
			int newDist = GraphIsAdjacent(g, curr, j) + dist[curr]; 

			//Consider multiple
			//predecessor nodes in the linked list
			if (!hasVisited[j] && GraphIsAdjacent(g, curr, j)) {
				if (newDist < dist[j]) {
					dist[j] = newDist;
					//Cases:

					//There could be a pred list with 
					//nodes

					//Or an empty pred list

					//pred[j] = curr;
				}
				else if (newDist <= dist[j]) {
					//Only one case:
					//Add the node as an alternative predecessor 
				}
			}
			
			j +=1;
		}
		i +=1;
	}
	
	//free(dist);
	//free(pred);
    //free(hasVisited);

    return sp;
}


void showShortestPaths(ShortestPaths sps);

void freeShortestPaths(ShortestPaths sps);