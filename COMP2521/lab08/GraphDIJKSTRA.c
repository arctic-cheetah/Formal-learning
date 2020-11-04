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
int currNode(Graph g, int *dist, int *hasVisited) {
	int minDist = INF;
	int curr = 0;
	
	for (int i = 0; i < g->nV; i +=1) {
		if (dist[i] < minDist && !hasVisited[i]) {
			minDist = dist[i];
			curr = i;
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
	int *hasVisited = calloc(g->nV, sizeof(int));
	int *dist = calloc(g->nV, sizeof(int));
	//Set all distances to inf
	for (int i = 0; i < g->nV; i +=1) {
		dist[i] = INF;
	}
	
	dist[src] = 0;
	
	int i = 0;
	while (i < g->nV) {
		//Get the next node
		int curr = currNode(g, dist, hasVisited);
		hasVisited[curr] = 1;
		
		int v = 0;
		while (v < g->nV) {
			int newDist = dist[curr] + (g->edges[curr][v] & 1);
			if (newDist < dist[v] && !hasVisited[v] 
				&& g->edges[curr][v] && g->edges[curr][v] < max) {
			   	dist[v] = newDist;
			}
			v +=1;
		}
	
		i +=1;
	}
	
	//Check for the number of paths that does not exist
	int nPath = 0;
	for (int i = 0; i < g->nV; i +=1) {
		if (dist[i] == INF) {
			nPath +=1;
		}
	}
	if (nPath == (g->nV - 1)) {
		return 0;
	}
	
	//Dist array will give the shortest dist 
	//from the src to all the vertices.
	
	//Sort the graph in numeric ID
	int j = 0;
	int k = 0;
	while (k <= dest && j < g->nV) {
		if (dist[j] == k) {
			path[k] = j;
			k +=1;
			j = 0;
		}
		j +=1;
	}
	
	return nPath;
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

