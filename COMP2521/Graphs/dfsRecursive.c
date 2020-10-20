#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

#define MAX_NODES 1000

int visited[MAX_NODES];  // array to store visiting order
                         // indexed by vertex 0..nV-1

bool dfsPathCheck(Graph g, int nV, Vertex v, Vertex dest) {
	//Mark the src as visited
	//Loop through all the adjacent vertices
	int i = 0;
	while (i < nV) {
		if (adjacent(g, i, v) && visited[i] == -1) {
			visited[i] = v;
			if (i == dest) {
				return true;
			}
			else if (dfsPathCheck(g, nV, i, dest)) {
				return true;
			}
		}
		
		i +=1;
	}
	return false;
}

bool findPathDFS(Graph g, int nV, Vertex src, Vertex dest) {
	
	for (int i = 0; i < nV; i+=1) {
		visited[i] = -1;
	}
   
	visited[src] = src;
	   
   return dfsPathCheck(g, nV, src, dest);
}

int main(void) {
   int V = 6;
   Graph g = newGraph(V);

   Edge e;
   e.v = 0; e.w = 1; insertEdge(g, e);
   e.v = 0; e.w = 4; insertEdge(g, e);
   e.v = 0; e.w = 5; insertEdge(g, e);
   e.v = 5; e.w = 4; insertEdge(g, e);
   e.v = 4; e.w = 2; insertEdge(g, e);
   e.v = 4; e.w = 3; insertEdge(g, e);
   e.v = 5; e.w = 3; insertEdge(g, e);
   e.v = 1; e.w = 2; insertEdge(g, e);
   e.v = 3; e.w = 2; insertEdge(g, e);

   int src = 0, dest = 5;
   if (findPathDFS(g, V, src, dest)) {
      Vertex v = dest;
      while (v != src) {
	 printf("%d - ", v);
	 v = visited[v];
      }
      printf("%d\n", src);
   }
   return 0;
}
