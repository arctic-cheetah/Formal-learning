//A program that performs a breadth first search on a graph using a queue
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void print_array(int *array, int length) {
	for (int i = 0; i < length && array[i] >= 0; i +=1) {
		printf("%d ", array[i]);
	}
} 


void breadthFirstSearch(Graph g, int src) {
	int NumVertex = GraphNumVertices(g);
	//Create an array to track each vertex
	int trackIndex = 1;
	int *track = calloc(GraphNumVertices(g), sizeof(int));
	track[0] = src;
	
	Queue q = QueueNew();
	int i = 0;
	//Loop through each horizontal index for the starting vertex
	//and add it to the queue
	while (i < NumVertex) {
		if (GraphIsAdjacent(g, src, i)) {
			track[trackIndex] = i;
			trackIndex +=1;
			QueueEnqueue(q, i);
		}
		i++;
	}
	//Loop through until the queue is empty
	int currVertex;
	while (QueueSize(q) != 0) {
		currVertex = QueueDequeue(q);
		int j = 0;
		
		//Check any edges in the current vertex
		while (j < NumVertex) {
			//Only add adjacent vertices to track if the number does not exist
			if (GraphIsAdjacent(g, currVertex, j)) {
				int k = 0;
				int HasVisited = 0;
				//Check if a vertex has been visited
				while (k < trackIndex) {
					if (track[k] == j) {
						HasVisited = 1;
						break;
					}
					k++;
				}
				if (HasVisited == 0) {
					track[trackIndex] = j;
					trackIndex +=1;
					QueueEnqueue(q, j);
				}
			}
			j++;
		}
	}
	//Set any vacant spaces for in track to -1.
	i = trackIndex;
	while (i < NumVertex) {
		track[i] = -1;
		i++;
	}
	print_array(track, NumVertex);
	free(track);
	QueueFree(q);
}





















