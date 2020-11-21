//Used priority queue to traverse the graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Dijkstra.h"
#include "PQ.h"

#define INF 0x7FFFFFFF

///////////////////////////////////////////////////////////////////
//Function prototypes:
int smallDist (Graph g, int *hasVisited, int *dist);
PredNode *new_node (int newNode);
PredNode **newPred (Vertex src, int nV);
PredNode *insertNode (PredNode *headList, int newNode);
PredNode *freeNode (PredNode *n);
PredNode *freeList (PredNode *headList);
int distance (AdjList node, int next);

/////////////////////////////////////////////////////////////////////////
//Assignment functions

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
	
	//This loop as well as the inner loop 
	//takes O(n^2)
	int i = 0;
	while (i < nV) {
		//get the current node,
		int curr = smallDist(g, hasVisited, dist);
		//Remove the curr node from the unexplored set
		hasVisited[curr] = 1;
		
		//Use a priority queue,

		//Obtain all outgoing edges from curr
		PQ pq = PQNew();
		AdjList head = GraphOutIncident(g, curr);

		AdjList c1 = head;
		while (c1 != NULL) {
			PQInsert(pq, c1->v, c1->weight);
			c1 = c1->next;
		}
		//Priority Queue uses an array
		//The worst case is that the graph is dense
		//and all the vertices are connected then it will be
		//O(n)
		while (!PQIsEmpty(pq)) {
			int j = PQDequeue(pq);
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
					//There exists pred list with nodes 
                    //with a longer distance
					//FREE the current list
					//APPEND the newNode
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
		}
		PQFree(pq);
		i +=1;
	}

    //Set the distance of any unreachable vertices to 0
	for (int k = 0; k < nV; k +=1) {
		if (dist[k] == INF) {
			dist[k] = 0;
		}
	}


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



///////////////////////////////////////////////////////////////////
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

    //Get to the end of the list
	while (curr != NULL && curr->v != next) {
		curr = curr->next;
	}

	if (curr == NULL) {
		return 0;
	}

	return curr->weight;
}