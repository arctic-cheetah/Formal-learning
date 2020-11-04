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

//A function that returns the current node
//based on the smallest weight in terms of number of flights
//and distance
int currNode(Graph g, int *path, int *hasVisited, int *nF, int max) {
	int minDist = INF;
	int minFlight = INF;
	int curr = 0;
	
	for (int i = 0; i < g->nV; i +=1) {
		if (path[i] < minDist && !hasVisited[i] && nF[i] < minFlight) {
			if (path[i] < max) {
				minDist = path[i];
				minFlight = nF[i];
				curr = i;
			}
		}
	}
	
	return curr;
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
	//and the number of flights
	int *nF = calloc(g->nV, sizeof(int));
	int *hasVisited = calloc(g->nV, sizeof(int));
	
	//Set all distances to inf
	for (int i = 0; i < g->nV; i +=1) {
		path[i] = INF;
	}
	
	//Find the number of flights from src to dest
	//via dfs
	path[src] = 0;
	nF[src] = 0;
	
	int i = 0;
	while (i < g->nV) {
		int curr = currNode(g, path, hasVisited, nF);
		hasVisited[curr] = 1;
		
		int v = 0;
		while (v < g->nV) {
			int newDist = path[curr] + g->edges[curr][v];
			int newFli = nF[curr] + nF[v];
			if (newFli < nF[v] && newDist < g->edges[curr][v]
							   && !hasVisited[v]) {
			   path[v] = newDist;
			   newFli
			}
		}
	
		i +=1;
	}
	
	// TODO
	return 0;
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

