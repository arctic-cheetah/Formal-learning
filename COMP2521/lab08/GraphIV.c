// Implementation of the undirected weighted graph ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

#define MAXCITIES 40
#define MAXNAME   20
#define INF 0x7FFFFF00

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;      // #vertices
	int nE;      // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

static int validVertex(Graph g, Vertex v);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV)
{
	assert(nV > 0);

	Graph new = malloc(sizeof(*new));
	assert(new != NULL);
	new->nV = nV;
	new->nE = 0;

	new->edges = calloc(nV, sizeof(int *));
	assert(new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc(nV, sizeof(int));
		assert(new->edges[v] != 0);
	}

	return new;
}

void GraphFree(Graph g)
{
	assert(g != NULL);
	for (int v = 0; v < g->nV; v++)
		free(g->edges[v]);
	free(g->edges);
	free(g);
}

////////////////////////////////////////////////////////////////////////

void GraphInsertEdge(Graph g, Vertex v, Vertex w, int weight)
{
	assert(g != NULL && validVertex(g, v) && validVertex(g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		return; // an edge already exists; do nothing.

	g->edges[v][w] = weight;
	g->edges[w][v] = weight;
	g->nE++;
}

void GraphRemoveEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validVertex(g, v) && validVertex(g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		return; // the edge doesn't exist; do nothing.

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

////////////////////////////////////////////////////////////////////////

void print_array(int *array, int length) {
	for (int i = 0; i < length; i +=1) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

/**
 * Finds  the  shortest path (in terms of the number of hops) from `src`
 * to `dest` such that no edge on the path has weight larger than `max`.
 * Stores  the  path  in the given `path` array including both `src` and
 * `dest` and returns the number of vertices stored in the  path  array.
 * Returns 0 if there is no such path.
 */
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	if (g == NULL) {
		printf("The graph was empty!\n");
		assert(g != NULL);
	}
	//Create an array that tracks if a city has been visited
	int *hasVisited = calloc(g->nV, sizeof(int));
	int *subGraph = hasVisited;
	int *backTrack = calloc(g->nV, sizeof(int));
	//Set all visited to zero
	for (int i = 0; i < g->nV; i +=1) {
		hasVisited[i] = -1;
	}
	hasVisited[src] = src;
	int found = 0;
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	
	//Perform a BFS on the edges which are close
	while (!QueueIsEmpty(q) && !found) {
		int curr = QueueDequeue(q);
		
		if (curr == dest) {
			found = 1;
		}
		int i = 0;
		while (i < g->nV) {
			//Only add edges if they are within range
			if (g->edges[curr][i] && hasVisited[i] == -1
				&& g->edges[curr][i] < max) {
				hasVisited[i] = curr;
				QueueEnqueue(q, i);
			}
			i +=1;
		}
		
	}
	//print_array(hasVisited, g->nV);
	
	//Check if src-dest exists
	if (subGraph[dest] == -1) {
		return 0;
	}
	
	
	int flights = 0;
	backTrack[flights] = dest;
	int maxFlight = g->nV - 1;
	
	//Back track via the subgraph
	int i = 0;
	//(n - 1) iterations
	
	while (maxFlight >= 0 && i <= g->nV) {
		
		//Add to the path
		if (subGraph[backTrack[flights]] == i) {
			flights +=1;
			backTrack[flights] = i;
		}
		if (backTrack[flights] == src) {
			//printf("test!\n");
			break;
		}
		//We go from n-1 to zero, n-1 times.
		if (i == maxFlight) {
			i = 0;
			maxFlight -=1;
		}
		i +=1;
	}
	//This means we have O((n-1)^2) = O(n^2)
	
	
	flights+=1;
	//print_array(backTrack, flights);
	int j = flights - 1;
	//Copy all the contents backwards
	for (int k = 0; k < flights && j >= 0; k +=1) {
		path[k] = backTrack[j];
		j -=1;
	}
	
	
	free(backTrack);
	free(hasVisited);
	QueueFree(q);
	
	return flights;
}

////////////////////////////////////////////////////////////////////////

void GraphShow(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

static int validVertex(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

