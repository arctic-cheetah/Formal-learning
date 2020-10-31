
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

//Find all connected components of the graph
void print_array (int *array, int length) {
	for (int i = 0; i < length; i +=1) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

//A helper function that explores the components of a graph
void dfsComponent(Graph g, int *component, Vertex v, int compID) {
	component[v] = compID;
	int nV = GraphNumVertices(g);
	for (int i = 0; i < nV; i +=1) {
		if ( (component[i] == -1) && GraphIsAdjacent(g, i, v) ) {
			dfsComponent(g, component, i, compID);
		}
	}
}
//A function that modifies an array to return the components of a graph
void num_components(Graph g, int *component) {
	int nV = GraphNumVertices(g);
	
	for (int i = 0; i < nV; i +=1) {
		component[i] = -1;
	}
	//Store all connected components in an array
	int compID = 0;
	for (int i = 0; i < nV; i +=1) {
		if (component[i] == -1) {
			dfsComponent(g, component, i, compID);
			compID +=1;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

//A DFS function that checks if there is a cycle in a graph
bool dfsCycleCheck (Graph g, Vertex curr, Vertex prev, int *HasVisited) {
	HasVisited[curr] = 1;
	int nV = GraphNumVertices(g);
	for (int i = 0; i < nV; i +=1) {
		if (GraphIsAdjacent(g, curr, i)) {
			//A vertex has not been met,
			if (!HasVisited[i]) {
				//need to check if a cycle exists
				if (dfsCycleCheck(g, i, curr, HasVisited) ) {
					return true;
				}
			}
			//A previous vertex has been visited
			else if (prev != i) {
				return true;
			}
			//Otherwise the search has returned where the curr = prev vertex
			//continue searching
		}
	}
	return false;
}


//Check for cycles in each component using DFS
bool hasCycle(Graph g) {
	int nV = GraphNumVertices(g);
	int *component = malloc(sizeof(Vertex) * nV);
	num_components(g, component);
	
	//print_array(component, nV);
	
	int *HasVisited = calloc (nV, sizeof(Vertex));
	bool result = false;
	//Check that all the connected components do not have cycles
	//YOU MUST CHECK EACH VERTEX.
	//CONISIDER A PENDENT VERTEX
	for (int i = 0; i < nV; i +=1) {
		//Reset the array which tracks the vertices that have been visited
		for (int j = 0; j < nV; j +=1) {
			HasVisited[j] = 0;
		}
		if (dfsCycleCheck(g, i, i, HasVisited)) {
			result = true;
			break;
		}
	}
	free(component);
	free(HasVisited);
	return result;
}


