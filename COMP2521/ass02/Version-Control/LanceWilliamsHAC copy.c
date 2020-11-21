// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"


//DEFINES EXIST HERE
#define INF 0x7FFFFFFF

//My structs


/////////////////////////////////////////////////////////////////
//Function prototypes
Dendrogram newDNode (int n);
double **newDistArray (int nV);
int getDist(double **dist, Dendrogram *dendA, Graph g);


/**
 * Generates  a Dendrogram using the Lance-Williams algorithm (discussed
 * in the spec) for the given graph  g  and  the  specified  method  for
 * agglomerative  clustering. The method can be either SINGLE_LINKAGE or
 * COMPLETE_LINKAGE (you only need to implement these two methods).
 * 
 * The function returns a 'Dendrogram' structure.
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    Dendrogram root;

    int nV = GraphNumVertices(g);

    //Initialse a dist array
    double **dist = newDistArray(nV);

    //Initialise an array of pointers to each node
    Dendrogram *dendA = (Dendrogram*) calloc(nV, sizeof(Dendrogram*));

    //Initialise the dendrogram nodes
    for (int i = 0; i < nV; i +=1) {
        dendA[i] = newDNode(i);
    }
    
    //Calculate the distance (1/wt) of a vertex to all other vertices
    //CONSIDER BOTH DIRECTIONS






    //Follow Lance-williams HAC algorithm
    //SINGLE-linkage
    //or complete-linkage



    //Free the distance array
    for (int i = 0; i < nV; i +=1) {
        free(dist[i]);
    }
    free(dist);

    return NULL;
}

/**
 * Frees all memory associated with the given Dendrogram structure.
 */
void freeDendrogram(Dendrogram d) {

}

///////////////////////////////////////////////////////////////////////////
//Helper functions

//A function that initialises a dendrogram node
Dendrogram newDNode(int n) {
    Dendrogram newNode = malloc(sizeof(struct DNode));
    newNode->vertex = n;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//A helper function that initialises a dist array
double **newDistArray (int nV) {
    //Initialise 2D array
    double **dist = (double**) calloc(nV, sizeof(double*));
    //Initialse "columns"
    for (int i = 0; i < nV; i +=1) {
        dist[i] = (double*) calloc(nV, sizeof(double));
    }

    //Initialise the dist array to inf
    //but the diagonals to nothing
    for (int i = 0; i < nV; i +=1) {
        for (int j = 0; j < nV; j +=1) {
            if (i != j) {
                dist[i][j] = INF;
            }
            else {
                dist[i][j] = -1;
            }
        }
    }

    return dist;
}

//A function that fetchces the dist (1/wt) from a vertex  
//and stores it in the dist array
int getDist(double **dist, Dendrogram *dendA, Graph g) {
    int nV = GraphNumVertices(g);
    //For each vertex, get the maximum edge weight (wt) between
    //a pair of vertices v and w
    for (int i = 0; i < nV; i +=1) {
        for (int j = 0; j < nV; j +=1) {
            //Get the weight

            //Consider if there are incoming and outgoing edges
            int incom = GraphIsAdjacent(g, i, j);
            int outgo = GraphIsAdjacent(g, j, i);

            if (incom && outgo) {
                AdjList in = GraphInIncident(g, i); 
                AdjList out = GraphOutIncident(g, i); 
            }
            else if (!incom && outgo) {
                
            }
            else if (incom && !outgo) {
                
            }

        }
    }

    //The distance between them is 1/(wt).

    //If there are two directed links, then consider 1 / (max())

    

}

//Returns the weight to the destination node
int getWeight (AdjList l, int dest) {
    //Base case
    if (l == NULL) {
        return 0;
    }
    else if (l->v == dest) {
        return l->weight;
    }
    //We haven't found
    return getWeight(l->next, dest);
}

