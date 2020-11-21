//Used adjacency matrix algorithm
//needs reworking

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Dijkstra.h"

#define INF 9999

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


//A function that creates a new PredNode
PredNode *new_node (int newNode) {
	PredNode *n = malloc(sizeof(PredNode));
	n->v = newNode;
	n->next = NULL;
	return n;
}

//Allocate memory for an array of  predecessor  lists
PredNode **newPred (Vertex src, int nV) {
	PredNode **pred = malloc(sizeof(PredNode) * nV);
	//Set all nodes to NULL
	for (int i = 0; i < nV; i +=1) {
		pred[i] = NULL;
	}
	return pred;
}


//A function that appends a node to the linked list PredNode
PredNode *insertNode (PredNode *headList, int newNode) {

	if (headList == NULL) {
		return new_node(newNode);
	}

	PredNode *curr = headList;
	PredNode *prev = headList;

	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = new_node(newNode);
	return headList;
}

//A function that frees a PredNode node
PredNode *freeNode (PredNode *n) {
	free(n);
	return NULL;
}

//A function that frees the entire pred list
PredNode *freeList (PredNode *headList) {
	PredNode *curr = headList;
	PredNode *prev = headList;
	headList = NULL;

	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		prev = freeNode(prev);
	}
	free(prev);
	return headList;
}


//A function which returns the weight from node curr to j
int distance (AdjList node, int next) {
	if (node == NULL) {
		return 0;
	}
	AdjList curr = node;

	while (curr != NULL && curr->v != next) {
		curr = curr->next;
	}
	//Debugging
	if (curr == NULL) {
		return 0;
	}

	return curr->weight;
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
			int currToJ = distance(GraphOutIncident(g, curr), j);
			int newDist = currToJ + dist[curr]; 

			//Relaxation
			//Consider multiple
			//predecessor nodes in the linked list
			if (!hasVisited[j] && currToJ) {

				if (newDist < dist[j]) {
					dist[j] = newDist;
					//Cases:
					//pred[j] = curr;

					//There could be an empty pred list
					//In which case simply APPEND aka insert 
					if (pred[j] == NULL) {
						pred[j] = insertNode(pred[j], curr);
					}
					//Or a pred list with nodes
					//then FREE the current list
					//and APPEND the newNode
					else if (pred[j] != NULL) {
						pred[j] = freeList(pred[j]);
						pred[j] = insertNode(pred[j], curr);
					}

				}
				else if (newDist <= dist[j]) {
					//Only one case:
					//APPEND the node as an alternative pred
					//in the list
					pred[j] = insertNode(pred[j], curr);
				}
			}
			
			j +=1;
		}
		i +=1;
	}
	
	//Set the distance of any unreachable vertices to 0
	for (int k = 0; k < nV; k +=1) {
		if (dist[k] == INF) {
			dist[k] = 0;
		}
	}

	//free(dist);
	//free(pred);
    free(hasVisited);

    return sp;
}



void showShortestPaths(ShortestPaths sps);

void freeShortestPaths(ShortestPaths sps) {
	free(sps.dist);
    //free pred linked list first
    for (int i = 0; i < sps.numNodes; i +=1) {
        freeList(sps.pred[i]);
    }
    //free pred array
    free(sps.pred);
}