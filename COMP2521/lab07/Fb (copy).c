
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "Map.h"
#include "Queue.h"

#define MAX_PEOPLE 128
#define MAX_RECOMM 20

struct fb {
    int   numPeople;

    char *names[MAX_PEOPLE]; // the id of a person is simply the index
                             // that contains their name in this array
    
    Map   nameToId;
    // maps names to ids
    // question to think about: why do we have this when
    // the names array already provides this information? 
    
    //Answer:
    //Using an array to map string names to id would be O(n) time. Using 
    //an AVL tree to store the mapping can reduce the search time to
    //O(logn) and is superior than to using an array when there is a large
    //amount of users on FB
	
	//This is the matrix which stores the friendship status 
	//"edges" between two people
    bool  friends[MAX_PEOPLE][MAX_PEOPLE];
};

static char *myStrdup(char *s);
static int   nameToId(Fb fb, char *name);

////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb   FbNew(void) {
    Fb fb = malloc(sizeof(*fb));//What's the size of the pointer?
    if (fb == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->nameToId = MapNew();

    for (int i = 0; i < MAX_PEOPLE; i++) {
        for (int j = 0; j < MAX_PEOPLE; j++) {
            fb->friends[i][j] = false;
        }
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }

    MapFree(fb->nameToId);
    free(fb);
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == MAX_PEOPLE) {
        fprintf(stderr, "error: could not add more people\n");
        exit(EXIT_FAILURE);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = myStrdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (!fb->friends[id1][id2]) {
        fb->friends[id1][id2] = true;
        fb->friends[id2][id1] = true;
        return true;
    } else {
        return false;
    }
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (fb->friends[id1][id2]) {
        fb->friends[id1][id2] = false;
        fb->friends[id2][id1] = false;
        return true;
    } else {
        return false;
    }
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return fb->friends[id1][id2];
}

List FbGetFriends(Fb fb, char *name) {
    int id1 = nameToId(fb, name);
    
    List l = ListNew();
    for (int id2 = 0; id2 < fb->numPeople; id2++) {
        if (fb->friends[id1][id2]) {
            ListAppend(l, fb->names[id2]);
        }
    }
    return l;
}

int  FbNumFriends(Fb fb, char *name) {
    int id1 = nameToId(fb, name);
    
    int numFriends = 0;
    for (int id2 = 0; id2 < fb->numPeople; id2++) {
        if (fb->friends[id1][id2]) {
            numFriends++;
        }
    }
    return numFriends;
}

////////////////////////////////////////////////////////////////////////
// Your tasks

//A function which returns a list of mutual friends between two people
List FbMutualFriends(Fb fb, char *name1, char *name2) {
    List l = ListNew();
    
    //REMEMBER:
    //A person is considered a mutual friend if they are friends
    //with both name1 and name2.
    
    List numPeople = FbGetPeople(fb);
	int nP = ListSize(numPeople);
    
    //Convert name to ID
    //O(logn)
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    
    //An array to store all the common friends
    int *common = calloc(nP, sizeof(int));
    
    //Find all the common friends between ID1 and ID2 O(n^2)
    //By indexing via 2d array
    //Store the common friends into an array
	for (int i = 0; i < nP; i +=1) {
		if (fb->friends[id1][i] == true) {
			//Check if id1's friends overlap with id2's friends
			//May want to use the implemented functions
			for (int j = 0; j < nP; j +=1) {
				if (fb->friends[id1][i] == fb->friends[id2][j] && i == j) {
					common[i] = 1;
				}
			}
		}
	}
	//Exclude name1 and name2 as being common friends
	//For the sake of fetching mutual friends
	common[id1] = 0;
	common[id2] = 0;
    
    //Convert the id to strings O(n)
    for (int i = 0; i < MAX_PEOPLE; i +=1) {
    	//Add common friends to the list
    	if (common[i] == 1) {
    		ListAppend(l, fb->names[i]);
    	}
    }
    
    free(common);
    ListFree(numPeople);
    
    return l;
}

//Generates and prints friend recommendations for a person.

///////////////////////////////////////////////////////////////
//Is the worst case O((n)^(n-2))? 
//We have to go through the array of length n, k times.
//Where k is the number of friends and is between 0 to n-2

void FbFriendRecs1(Fb fb, char *name) {
	//Fetch the number of people in Fb
	List numPeople = FbGetPeople(fb);
	int nP = ListSize(numPeople);
	
	//Fetch the number of "non-friends", and store them in an array
	int *mutual = calloc(nP, sizeof(int));
	
	//Get the number of mutual friends and store them in the array mutual
	int mutualNum = 0;
	
	//The loop alone is O(n)
	//Due to the use of strcmp, it becomes O(nk)
	for (int j = 0; j < nP; j +=1) {
		if (!FbIsFriend(fb, name, fb->names[j]) 
			&& strcmp(name, fb->names[j]) 
			) {
			
			List l = FbMutualFriends(fb, name, fb->names[j]);
			//Only add mutual friends
			if (ListSize(l)) {
				mutual[j] = ListSize(l);
				mutualNum +=1;
			}
			free(l);
		}
	}
	
	
	printf("%s's friend recommendations\n", name);
	
	//Number of mutual friends is between 0 to n-2
	int maxMutual = MAX_PEOPLE - 2;
	
	int i = 0;
	//(n-2) iterations
	while (maxMutual > 0) {
		//Print anybody with the same number mutual friends as maxMutual
		if (mutual[i] == maxMutual) {
			printf("\t%-20s%4d mutual friends\n", fb->names[i], mutual[i]);
		}
		//If the end of the array is reached, end until maxMutual == 0, ie;
		//n operations

		if (i == (nP - 1)) {
			i = 0;
			maxMutual -=1;
		}
		
		i +=1;
	}
	
	//Overall, we have the terms O((n-2) * (n-2) + n^2)
	//Simplifying this leaves us with O(n^2)
	
	free(mutual);
    
}

//Prints  friend  recommendations for a person based on the distance
void FbFriendRecs2(Fb fb, char *name) {
	//Use BFS
	
	int id = nameToId(fb, name);
	
	//Don't revisit the same vertex
	//Worst case is that the number of people = MAX_PEOPLE
	List numPeople = FbGetPeople(fb);
	int nP = ListSize(numPeople);
	//O(n)
	int *hasVisited = calloc(nP, sizeof(int));
	
	//Create a new queue and add the first person
	Queue q = QueueNew();
	QueueEnqueue(q, id);//O(1)
	
	//The starting person has been seen
	hasVisited[id] = 1;
	
	printf("%s's friend recommendations\n", name);
	
	int Recomm = 0;
	//Worst case, is that we queue O((n-1)) people
	while (QueueSize(q) != 0 && Recomm < MAX_RECOMM) {
		int currNode = QueueDequeue(q);
		int j = 0;
		//Bear in mind nP could be the same as MAX_PEOPLE
		//Ergo O(n(n-1)) = O(n^2)
		while (j < nP && Recomm < MAX_RECOMM) {
			if (!hasVisited[j]) {
				//Don't print nodes which are connected to the src
				if (fb->friends[id][j] && currNode == id) {
					QueueEnqueue(q, j);//O(1)
					hasVisited[j] = 1;
					
				}
				else if (fb->friends[currNode][j]) {
					printf("\t%s\n", fb->names[j]);
					QueueEnqueue(q, j); //O(1)
					Recomm +=1;
					hasVisited[j] = 1;
				} 
			}
			j +=1;	
		}
	}
	QueueFree(q);
    free(hasVisited);
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Converts a name to an ID. Raises an error if the name doesn't exist.
// O(logn)
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}

