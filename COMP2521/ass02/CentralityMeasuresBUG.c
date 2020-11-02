// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"

#define LOWPRIORITY 0x7FFFFFFF

/////////////////////////////////////////////////////////////////////////
///Helper functions
//A function that returns the number of nodes reachable from v in a graph
//Excluding the current vertex (n)
int reachableNodes (ShortestPaths sp, int v) {
    int i = 0;
    int reachable = 0;
    while (i < sp.numNodes) {
        //Don't add vertices which are unreachable
        //or the src vertex
        if (i != v && sp.dist[i]) {
            reachable += 1;
        }
        i +=1;
    }
    return reachable;
}

//A function that sums all the distance reachable from v in a graph

//Isolated vertices and unreachable have been covered,
//they are marked as zero
int sumOfAllDist (ShortestPaths sp, int v) {
    int sum = 0;
    for (int i = 0; i < sp.numNodes; i +=1) {
        sum += sp.dist[i];
    }
    return sum;
}

//A function that returns the sum of all the shortest paths
//from s to t by using the predecessor list
int numShortPath (PredNode *head) {
    PredNode *curr = head;
    int sum = 0;
    while (curr != NULL) {
        sum +=1;
        curr = curr->next;
    }
    return sum;
}

//A function that checks if node v is a predecessor of node t
//returns 1 if true, false otherwise
int isPred (PredNode *head, int v) {
    PredNode *curr = head;
    while (curr != NULL) {
        if (curr->v == v) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

//A function which enqueues predecessor vertices
//and returns the number of nodes it enqueues
int addPredNode (ShortestPaths sp, PQ pq, int v) {
    PredNode *curr = sp.pred[v];
    int i = 0;
    while (curr != NULL) {
        PQInsert(pq, curr->v, LOWPRIORITY);
        curr = curr->next;
        i +=1;
    }
    return i;
}

/////////////////////////////////////////////////////////////////////////
/**
 * Finds the closeness centrality for each vertex in the given graph and
 * returns the results in a NodeValues structure.
 */

NodeValues closenessCentrality(Graph g) {
	NodeValues nvs;
    nvs.numNodes = GraphNumVertices(g);
    nvs.values = malloc(nvs.numNodes * sizeof(double));

    //set array of values to 0.0 for safety
    for (int i = 0; i < nvs.numNodes; i +=1) {
        nvs.values[i] = 0.0;
    }

    //Find the centrality value for all nodes
    int v = 0;
    while (v < nvs.numNodes) {
        ShortestPaths sp = dijkstra(g, v);
        //Fetch the number of vertices reachable from v
        //and the sum of all dist from v
        int reachable = reachableNodes(sp, v);
        int sum = sumOfAllDist(sp, v);

        //Check if reachable or sum is zero
        //Ensure N-1 is not zero!
        if (sum && reachable && (nvs.numNodes - 1)) {
            double x = 1.0 * reachable / (nvs.numNodes - 1);
            double y = 1.0 * reachable / sum;
            nvs.values[v] = x*y;
        }
        else {
            nvs.values[v] = 0.0;
        }
        //Free sp
        freeShortestPaths(sp);
        v +=1;
    }

	return nvs;
}

NodeValues betweennessCentrality(Graph g) {
    NodeValues nvs;
    nvs.numNodes = GraphNumVertices(g);
    nvs.values = malloc(nvs.numNodes * sizeof(double));

    //set array of values to 0.0 for safety
    for (int i = 0; i < nvs.numNodes; i +=1) {
        nvs.values[i] = 0.0;
    }

    int s = 0; 
    while (s < nvs.numNodes) {
        ShortestPaths sp = dijkstra(g, s);
        //Loop through the pred list,
        int t = 0;
        while (t < nvs.numNodes) {
            //Ensure node t is not isolated;
            if (sp.dist[t] && t != s) {
                //FETCH number of shortest paths for each target node,
                int numSP = numShortPath(sp.pred[t]);

                PQ pq = PQNew();
                addPredNode(sp, pq, t);
                /*
                AdjList head = GraphInIncident(g, t);

                //Add all the valid vertices, in accordance to weight
                AdjList c1 = head;
                while (c1 != NULL) {
                    PQInsert(pq, c1->v, c1->weight);
                    c1 = c1->next;
                }
                */
                //OBTAIN the number of paths that pass through v
                //from node s to t 
                //By starting from t and returning to s.

                //Check that v is connected to s and t
                //Check that v is a predecessor of t
                //Check that v is not s nor t
                int vPrev = t;
                while (!PQIsEmpty(pq)) {
                    int v = PQDequeue(pq);
                    int nodeAdded = addPredNode(sp, pq, v);
                    //LINE is here
                    if (v != t && v != s && isPred(sp.pred[vPrev], v)) {
                        int numPaths = numShortPath(sp.pred[v]);
                        //calculate centrality
                        nvs.values[v] += 1.0 * numPaths / numSP;
                        if (nodeAdded < 2) {
                            vPrev = v;
                        }
                    }
                }
                PQFree(pq);
            }
            t +=1;
        }
        freeShortestPaths(sp);
        s +=1;
    }
	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	NodeValues nvs = betweennessCentrality(g);
    int v = 0;
    while (v < nvs.numNodes) {
        ShortestPaths sp = dijkstra(g, v);
        int n = nvs.numNodes;
        nvs.values[v] *= 1.0/(n - 1) * 1.0/(n - 2);
        freeShortestPaths(sp);
        v +=1;
    }

	return nvs;
}

//Print out the NodeValues struct
void showNodeValues(NodeValues nvs) {
    for (int i = 0; i < nvs.numNodes; i +=1) {
        printf("%d: %lf\n", i, nvs.values[i]);
    }
}

void freeNodeValues(NodeValues nvs) {
    free(nvs.values);
}