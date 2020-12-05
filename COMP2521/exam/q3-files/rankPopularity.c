// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#define NOT_VISITED -1

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/
//Helper functions
void DFS(Graph g, int src, int prev, int *hasVisited, double *mnV);
int inDeg (Graph g, int src);
int outDeg (Graph g, int src);
double calculateRank (Graph g, int src);

//
void rankPopularity(Graph g, int src, double *mnV) {
	int *hasVisited = calloc(g->nV, sizeof(int));
	
	//Set the visited array to not visited;
	for (int i = 0; i < g->nV; i +=1) {
		hasVisited[i] = NOT_VISITED;
	}
	DFS(g, src, src, hasVisited, mnV);
	free(hasVisited);
}


//Perform DFS
void DFS(Graph g, int src, int prev, int *hasVisited, double *mnV) {
	//Base case
	hasVisited[src] = prev;
	
	//Calculate the popularity rank
	mnV[src] = calculateRank(g, src);
	
	//Recursive case
	for (int w = 0; w < g->nV; w +=1) {
		if (hasVisited[w] == -1 && adjacent(g, src, w)) {
			//Traverse the graph
			DFS(g, w, src, hasVisited, mnV);
		}
	}
}

//Calculate the popularity rank
double calculateRank (Graph g, int src) {
	int in = inDeg(g, src);
	int out = outDeg(g, src);
	//You can't both have out and in to be 0
	//Because DFS has already gotten to this src node!
	//It's ok
	if (out == 0) {
		return (double)in / 0.5;
	}
	else if (in == 0) {
		return 0.0;
	}
	return (1.0 * in) / (1.0 * out);
}
//Twins of functions that calculate the in / out degree
int inDeg (Graph g, int src) {
	int in = 0;
	for (int i = 0; i < g->nV; i +=1) {
		if (g->edges[i][src]) {
			in +=1;
		}
	}
	return in;
}

int outDeg (Graph g, int src) {
	int out = 0;
	for (int i = 0; i < g->nV; i +=1) {
		if (g->edges[src][i]) {
			out += 1;
		}
	}
	return out;
}





































