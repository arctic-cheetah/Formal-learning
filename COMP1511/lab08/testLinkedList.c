//Practice linked lists


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100


struct player {
	char name[MAX_LENGTH];
	struct player *next; 
};


struct player *createPlayer (char newName[], struct player *next);
void printData(struct player *head);
struct player *insertPlayer (struct player *insertionPoint, char newName[]);

int main(){

	struct player *head = createPlayer ("Jar", NULL); 
	head = createPlayer("Tess", head);
	head = createPlayer("Steve", head);
	head = createPlayer("Juliah", head);
	head = createPlayer("Rob", head);
	head = insertPlayer( head ,"Dala");

	printData(head);

	return 0;
}


// Creates and allocates memory for a player struct
//Return a pointer to that struct
struct player *createPlayer (char newName[], struct player *newNext) {

	struct player *newPlayer = malloc(sizeof(struct player));
	strcpy(newPlayer->name, newName);
	newPlayer->next = newNext;
	return newPlayer;
}

//Loops through all players in the list
//Prints the name of the player 
void printData(struct player *head){
	struct player *current = head;
	while (current != NULL){
		printf("%s\n", current->name);
		current = current->next;
	}
}

//Insert a player into the list of players
//Insert after the insertion point player
//Returns insertion point unless it was null.
//in which case we return a pointer to the new player
struct player *insertPlayer (struct player *insertionPoint, char newName[]){
	struct player *newPlayer = createPlayer(newName, NULL);
	
	if(insertionPoint == NULL){//The list is NULL
		insertionPoint = newPlayer;
	
	}
	else{//The insertPos is a node and can add a list to the end, beginning
	//or middle of a list
		newPlayer->next = insertionPoint->next;
		insertionPoint->next = newPlayer;
		//C
	}
	return insertionPoint;
}






































