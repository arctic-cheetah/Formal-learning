// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"

int item = 0;
int DQ = 0;

/////////////////////////////////////////////////////////////////////////
///Helper functions
//A function that returns the number of nodes reachable from v in a graph
//Excluding the current vertex
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
                AdjList head = GraphInIncident(g, t);

                //Add all the valid vertices, in accordance to weight
                AdjList c1 = head;
                while (c1 != NULL) {
                    PQInsert(pq, c1->v, c1->weight);
                    c1 = c1->next;
                }
                //OBTAIN the number of paths that pass through v
                //from node s to t 
                //Return the number of paths that pass via v
                //Check that v is connected to s and t
                //Check that v is a predecessor of t
                //Check that v is not s nor t
                while (!PQIsEmpty(pq)) {
                    int v = PQDequeue(pq);

                    if (v != t && v != s && isPred(sp.pred[t], v)) {
                        int numPaths = numShortPath(sp.pred[v]);
                        //calculate centrality
                        nvs.values[v] += 1.0 * numPaths / numSP;
                        //printf("v %d: %lf\n", v, 1.0 * numPaths / numSP);
                        item +=1;
                    }
                    DQ +=1;
                }
                PQFree(pq);
            }
            t +=1;
        }
        freeShortestPaths(sp);
        s +=1;
    }
    printf("Items: %d\n", item);
    printf("DQ: %d\n", DQ);
	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	NodeValues nvs = {0};
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