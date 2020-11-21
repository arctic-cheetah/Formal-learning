// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"

#define LOWPRIORITY 0x7FFFFFFF



float n1 = 0;
float n2 = 0;

/////////////////////////////////////////////////////////////////////////
///Helper functions

//A function that calculates the min 
int min (int a, int b) {
    return a > b ? b : a;
}

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

//A function which enqueues predecessor vertices
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

//A function that returns the number of predecessors to a node
int numPred (PredNode *head) {
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


//A function that returns the sum of all the shortest paths
//By backtracking from t to s using BFS
//BUG we are double COUNTING!
int numShortPathST (ShortestPaths sp, int s, int t, int **hasVisitedST) {
    int count = 1;
    PQ pq = PQNew();
    addPredNode(sp, pq, t);
    int vPrev = t;
    while (!PQIsEmpty(pq)) {
        int v = PQDequeue(pq);
        //Add the number of possible paths by checking the predecessor node
        int backTrack = numPred(sp.pred[vPrev]) - 1;
        //v or vPrev?
        //A route must not be seen, and must not have been visited
        if (backTrack > 0 && (!hasVisitedST[vPrev][t] 
                          || !hasVisitedST[s][t] ) 
                          ) {
            count +=backTrack;
        }
        vPrev = v;
        addPredNode(sp, pq, v);
        
    }
    PQFree(pq);
    return count;
}
//A function that returns the sum of all the shortest paths
//By backtracking from t to s using DFS
/*
int numShortPathDFS (ShortestPaths sp, int s, int t) {
    int count = 0;
    
    //base case:
    if (t == via) {
        count +=1;
    }
    else if (t == s) {
        return 0;
    }

    //Recursive case:
    //Continue searching
    PredNode *currTar = sp.pred[t];
    while (currTar != NULL) {
        count += numShortPathDFS(sp, s, currTar->v);
        currTar = currTar->next;
    }
    return count;
}
*/
//Return the number of paths that go through the node via from target to src.
//By using a back tracking DFS
int numShortPathVia (ShortestPaths sp, int s, int t, int via) {
    int count = 0;
    
    //base case:
    if (t == via) {
        count +=1;
    }
    else if (t == s) {
        return 0;
    }

    //Recursive case:
    //Continue searching
    PredNode *currTar = sp.pred[t];
    while (currTar != NULL) {
        count += numShortPathVia(sp, s, currTar->v, via);
        currTar = currTar->next;
    }
    return count;
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
    //st = source target 2d array
    int **hasVisitedST = (int**) calloc(nvs.numNodes, sizeof(int*));

    for (int i = 0; i < nvs.numNodes; i +=1) {
        hasVisitedST[i] = calloc(nvs.numNodes, sizeof(int));
    }

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
            //Ensure node t is not isolated and is not the source
            if (sp.dist[t] && t != s) {
                //FETCH number of shortest paths for each target node,

                PQ pq = PQNew();
                addPredNode(sp, pq, t);
                //OBTAIN the number of paths that pass through v
                //from node s to t 
                //By backtracking from t and returning to s.

                //Use BFS to backtrack through to s
                //and add edges on the shortest path
                //We may be missing edges

                if (s == 66 && t == 49) {
                        //printf("source %d, target %d\n", s, t);
                }
                //Don't double count paths..
                int numSP = numShortPathST(sp, s, t, hasVisitedST);
                while (!PQIsEmpty(pq)) {
                    
                    int v = PQDequeue(pq);
                    //Check that v is connected to s and t on SP
                    //Check that v is a predecessor of vPrev
                    //Check that v is not s nor t
                    if (v != t && v != s && (v == 47)) {
                        //PQShow(pq);
                        //printf("Target %d\n\n", t);
                        int numST = numShortPathVia(sp, s, t, v);
                        int numST2 = numShortPathST(sp, s, v, hasVisitedST);
                        //n1 = numShortPathVia(sp, s, t, v);
                        n2 += 1.0 * numST2 / numSP;
                        n1 += 1.0 * numST / numSP;
                        //calculate centrality
                        nvs.values[v] += 1.0 * numST / numSP;
                        printf("source %d, target %d\n", s, t);
                        //printf("numShortPathVia %d\n", n1);
                        //printf("numShortPathST %d\n", n2);
                        printf("number of paths %d\n", numSP);
                        //printf("v %d: %lf\n", v, 1.0 * n1 / numSP);
                        printf("v %d: %lf\n", v, 1.0 * n1);
                        printf("v %d: %lf\n", v, 1.0 * numST / numSP);
                        printf("v %d: %lf\n", v, 1.0 * numST2 / numSP);
                        printf("v %d: %lf\n", v, n2);
                        printf("v %d: %lf\n\n", v, nvs.values[v]);
                        //printf("vPrev %d, curr %d\n\n", vPrev, v);
                        addPredNode(sp, pq, v);
                        hasVisitedST[s][t] = 1;
                        
                        
                    }
                    else if (v != s && v != t) {
                        int numPaths = numShortPathVia(sp, s, t, v);
                        //calculate centrality
                        nvs.values[v] += 1.0 * numPaths / numSP;
                        addPredNode(sp, pq, v);
                        hasVisitedST[s][t] = 1;
                        
                    }
                }
                PQFree(pq);
            }
            t +=1;
        }
        freeShortestPaths(sp);
        s +=1;
    }

    for (int i = 0; i < nvs.numNodes; i +=1) {
        free(hasVisitedST[i]);
    }
    free(hasVisitedST);
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