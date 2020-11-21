// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"


//DEFINES EXIST HERE
//#define INF 0x7FFFFFFF
#define INF 10
#define NO_DIAGONAL = 9
#define INTERSECTION_NODE -1

/////////////////////////////////////////////////////////////////
//Function prototypes
Dendrogram newDNode (int n);
double **newDistArray (int nV);
void setDist(double **dist, Graph g);
int getWeight (AdjList l, int dest);
int max(int a, int b);
int min(int a, int b);
Dendrogram mergeCluster(Dendrogram x, Dendrogram y);
void singleLink(Graph g, double **dist, Dendrogram *dendA, int x, int y);
void completeLink(Graph g, double **dist, Dendrogram *dendA, int x, int y);
int length_of_dendA (Dendrogram *dendA, int nV);

void print_array (double **array, int length) {
    for (int i = 0; i < length; i+=1) {
        printf("[   ");
        for (int j = 0; j < length; j +=1) {
            printf("%.3f   ", array[i][j]);
        }
        printf("]\n");
    }
}

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
    //O(n^2)
    setDist(dist, g);

    //print_array(dist, nV);

    //Follow Lance-williams HAC algorithm
    //SINGLE-linkage
    //or complete-linkage
    //O(n^3)

    //Single-linkage
    int i = 0;
    while (i < nV) {
        //Find two closest clusters
        double min = INF;
        double max = INF;
        int x = INF;
        int y = INF;

        int j = 0;
        while (j < nV) {
            int k = 0;
            while (k < nV && dendA[j]) {
                //Select the appropriate linkage
                if (method == SINGLE_LINKAGE) {
                    if (min > dist[j][k] && dendA[k]) {
                        min = dist[j][k];
                        x = j;
                        y = k;
                        //printf("\n\n");
                        //print_array(dist, nV);
                    }
                }
                else {
                    if (max < dist[j][k] && dendA[k]) {
                        max = dist[j][k];
                        x = j;
                        y = k;
                    }
                }
                k +=1;
            }
            j +=1;
        }

        //assert(x != INF);
        //assert(y != INF);
        if (x != INF && y != INF) {
            //Merge the y cluster with the x cluster
            dendA[x] = mergeCluster(dendA[x], dendA[y]);

            //Update the distance using chosen method
            if (method == SINGLE_LINKAGE) {
                singleLink(g, dist, dendA, x, y);
            } 
            else {
                completeLink(g, dist, dendA, x, y);
            } 
            //Remove the y cluster from dendA
            dendA[y] = NULL;
        }

        i+=1;
    }

    //Fetch the head of the dendrogram
    int head = 0;
    while (head < nV) {
        if (dendA[head]) {
            root = dendA[head];
            break;
        }
        head +=1;
    }

    //Connect any disconnected clusters to the root of the 
    //dendrogram
    for (int m = 0; m < nV; m +=1) {
        if (dendA[head] && dendA[m]) {
            root = mergeCluster(dendA[head], dendA[m]);
        }
    }

    //Free the distance array & dendA
    for (int m = 0; m < nV; m +=1) {
        free(dist[m]);
        /*
        if (m != head) {
            free(dendA[m]);
        }*/
    }
    free(dist);
    free(dendA);

    return root;
}

/**
 * Frees all memory associated with the given Dendrogram structure.
 */
void freeDendrogram(Dendrogram d) {

}

///////////////////////////////////////////////////////////////////////
//Helper functions

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

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
    for (int i = 0; i < nV; i +=1) {
        for (int j = 0; j < nV; j +=1) {
            dist[i][j] = INF;
        }
    }

    return dist;
}

//A function that fetchces the dist (1/wt) from a vertex  
//and stores it in the dist array

//For each vertex, get the maximum edge weight (wt) between
//a pair of vertices v and w

//The distance between them is 1/(wt).

//If there are two directed links, then consider 1 / (max())
void setDist(double **dist, Graph g) {
    int nV = GraphNumVertices(g);

    for (int i = 0; i < nV; i +=1) {
        for (int j = 0; j < nV; j +=1) {
            //Get the weight
            int in = getWeight(GraphInIncident(g, i), j); 
            int out = getWeight(GraphOutIncident(g, i), j); 

            //Avoid division by zero
            if (in || out) {
                //This matrix will be symmetrical!
                dist[i][j] = 1.0 / (double) max(in, out);
            }
            
        }
    }
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

//A function that merges two clusters
Dendrogram mergeCluster(Dendrogram x, Dendrogram y) {
    Dendrogram intersection = newDNode(INTERSECTION_NODE);
    intersection->right = x;
    intersection->left = y;
    return intersection;
}

//A function that returns the number of non-null elements 
//in the dendA array
int length_of_dendA (Dendrogram *dendA, int nV) {
    int count = 0;
    int i = 0;
    while (i < nV) {
        if (dendA[i]) {
            count +=1;
        }
        i +=1;
    }
    return count;
}

//A function that updates the distance of the clusters array by using the 
//single linkage algorithm
void singleLink(Graph g, double **dist, Dendrogram *dendA, int x, int y){
    int nV = GraphNumVertices(g);
    //Merge the shortest distance from y to x;
    //This will be the new cluster
    int j = 0;
    while (j < nV && dendA[j]) {
        //Beware if a bug exists here
        if (dist[j][x] > dist[j][y] && (j != y) && (j != x)) {
            dist[j][x] = dist[j][y];
        }
        j +=1;
    }

    j = 0;
    while (j < nV && dendA[j]) {
        //Beware if a bug exists here
        if (dist[x][j] > dist[y][j] && (j != y) && (j != x)) {
            dist[x][j] = dist[y][j];
        }
        j +=1;
    }
}

//A function that updates the distance of the clusters array by using the 
//complete linkage algorithm
void completeLink(Graph g, double **dist, Dendrogram *dendA, int x, int y){
    int nV = GraphNumVertices(g);

    //Need to perform typecast for INF in case of inaccuracies
    //with floatin point comparison
    double inf = INF;


    //Merge the longest distance from y to x with x
    //This will be the new cluster
    //Apply to the vertical
    int j = 0;
    while (j < nV && dendA[j]) {
        //don't replace the max distances if they are inf
        //Don't replace the diagonal (trace in linear algebra)
        if (dist[j][x] < dist[j][y] && (j != y) && (j != x)
            && dist[j][x] != inf && dist[j][y] != inf) {
            dist[j][x] = dist[j][y];
        }
        j +=1;
    }

    //Repeat for the horizontal
    j = 0;
    while (j < nV && dendA[j]) {
        if (dist[x][j] < dist[y][j] && (j != y) && (j != x)
            && dist[x][j] != inf && dist[y][j] != inf) {
            dist[x][j] = dist[y][j];
        }
        j +=1;
    }

}