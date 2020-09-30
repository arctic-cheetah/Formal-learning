// Battle Royale Player List Organiser

// Keeps track of players in a game
// where they can be eliminated one by one

// Also a demo of the basic functionality
// of Linked Lists

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

struct player {
    char name[MAX_NAME_LENGTH];
    struct player *next;
};

struct player *createPlayer(char newName[], struct player *newNext);
int printPlayers(struct player *head);
struct player *insertPlayer(struct player *insertionPoint, char newName[]);
struct player *insertAlpha (struct player *head, char newName[]);
struct player *removePlayer(struct player *head, char remName[]);
void freePlayers (struct player *head);

int main() {
    struct player *head = NULL;
    head = insertAlpha(head, "Marc");
    head = insertAlpha(head, "Tom");
    head = insertAlpha(head, "Goku");
    head = insertAlpha(head, "Bulma");
    head = insertAlpha(head, "Master Roshi");
        
    //printPlayers(head);
	
	while(printPlayers(head) > 1){
		char koName[MAX_NAME_LENGTH];
		printf("Who got knocked out?");
		fgets(koName, MAX_NAME_LENGTH, stdin);
		koName[strlen(koName) - 1] = '\0';
		//scanf("%s", koName);
		head = removePlayer(head, koName);
		printf("-----------------\n");
	}
	printf("The winner is %s\n", head->name);
}

// Create and allocate memory for a player struct
// return a pointer to that struct
struct player *createPlayer(char newName[], struct player *newNext) {
    struct player *newPlayer = malloc(sizeof(struct player));
    strcpy(newPlayer->name, newName);
    newPlayer->next = newNext;
    return newPlayer;
}

// Loop through all players in the list starting
// at head and print out their names
// return the number of remaining players
int printPlayers(struct player *head) {
    struct player *current = head;
    int count = 0;
    while (current != NULL) { // have printed out nodes up to current
        printf("%s\n", current->name);
        current = current->next;
        count++;
    }
    return count;
}

// Insert a player into a list of players
// Insert after the insertion point player
// return the insertion point (unless it was NULL)
// in which case we return a pointer to the new
// player
struct player *insertPlayer(struct player *insertionPoint, char newName[]) {
    struct player *newPlayer = createPlayer(newName, NULL);
    
    if (insertionPoint == NULL) { // the list is NULL or is at the beginning
        insertionPoint = newPlayer;
    } 
    else { // the insertionPoint is a node
        newPlayer->next = insertionPoint->next;
        insertionPoint->next = newPlayer;
    }
    return insertionPoint;    
}


//Find the point in the list where newName fits alphabetical order
//Create and insert a new player into the list with a correct order
struct player *insertAlpha (struct player *head, char newName[]){
	//find the alphabetically correct position
	struct player *current = head;
	struct player *prev = NULL;
	while(current != NULL && strcmp(newName, current->name) > 0){
		//Loops while newName is less than current name
		prev = current;
		current = current -> next;
	}// current name is the first string higher than new name in the list
	
	//insert newName in the correct position
	struct player *insertPoint = insertPlayer (prev, newName);
	if(prev == NULL){// If it is at the start of the list
		insertPoint->next = head;
		head = insertPoint;
	}
	//insertPlayer(prev, newName);
	
	//return the head of the list
	return head;
	
}


//Look throught the list given in head until a name matches remName
// Remove the node from the list and free it 
//return the head of the list (may be a different node)
struct player *removePlayer(struct player *head, char remName[]){
	//Find the the node to remove
	struct player *current = head;
	struct player *prev = NULL;
	while (current != NULL && strcmp(remName, current->name) != 0 ) {
		
		prev = current;
		current = current->next;
	}// This loop stops when the removal target is found
	
	if(current == NULL){// We are at the end of the list
		//Removal target name was not found
		return head;
	}	
	
	if(current == head){//This is in the start of the list
		head = current->next; 
	}else{
		prev->next = current->next;
	}
	//Remove and free the node
	//free(current);
	//Return the head
	return head;
}

//Free all the players in memory
void freePlayers (struct player *head){
	struct player *current = head;
	struct player *prev = NULL;
	while(current != NULL){
		
		prev = current;
		current = current->next;
		//free(prev);
	}

}





































