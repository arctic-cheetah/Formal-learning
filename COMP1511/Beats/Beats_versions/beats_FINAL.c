// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by Jeremy Mang
// on 10/04/2020
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.
#include <string.h>
#include "beats.h"

// Add your own #defines here.

#define MAX_LENGTH 122

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {
    struct beat *current; // Points to the selected beat in a track
    struct beat *head; //The first beat in a track
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.
    struct note *notes; // points to the next note in the beat
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.
int octave_num_check  (char musicArray[]);
int key_num_check (char musicArray []);
int music_to_beat(Beat beat, int octave, int key);


// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {// We need to somehow check if the user entered an input greater than before...
    //printf("add_note_to_beat not implemented yet.\n");
    struct note *newNote = malloc(sizeof(struct note));
	struct note *prev = NULL;
	struct note *curr = beat->notes;
	int returnVal = VALID_NOTE; // This variable checks for a valid note
	
	//Check if User input is valid
    if(0 <= octave && octave < 10){
    	if( 0 <= key && key < 12){
    		returnVal = VALID_NOTE;
    	}
    	else{
    		free(newNote);
    		return INVALID_KEY;
    	}
    }
   	else{
   		free(newNote);
   		return INVALID_OCTAVE;
   	}

	if(beat->notes != NULL){
		//Check previous Octave/Key size to the user input
		//For ascending order
		while(curr != NULL){
			prev = curr;
			curr = curr->next;
		}
		//Go to the last note and check
		if (prev->octave < octave){
			returnVal = VALID_NOTE;
		}
		else if (prev->octave == octave){
			if(prev->key < key){
				returnVal = VALID_NOTE;
			}
			else{
				free(newNote);
				return NOT_HIGHEST_NOTE;
			}
		}
		else{
			free(newNote);
			return NOT_HIGHEST_NOTE;
		}
	}
	//Assign octave/key values to the note after checking
	newNote->key = key;
	newNote->octave = octave; 
	
    if(beat->notes == NULL){//Check if a beat does not have a note
    	beat->notes = newNote;
    	newNote->next = NULL;
    }
    else{//If a beat has a note, add a new note to 
    	//the end of the linked list
    	prev = NULL;
    	curr = beat->notes;   
    	while(curr != NULL){
			prev = curr;
			curr = curr->next;
    	}
    	prev->next = newNote;
    	newNote->next = NULL;	
    } 
    return returnVal;
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    struct note *curr = beat->notes;
    int noteCount = 0;
	while (curr != NULL){
		if(noteCount > 0) {
			printf(" | ");
		}
		if(curr->key >= 10) {
			printf("%d %d", curr->octave, curr->key);
		}
		else {
			printf("%d 0%d", curr->octave, curr->key);
		}
		
		curr = curr->next;
		noteCount++;
	}
    printf("\n");
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    int octaveCount = 0;
    struct note *curr = beat->notes;
    
    while (curr != NULL){   	
    	if(curr->octave == octave){
    		octaveCount++;
    	}   	
    	curr = curr->next;
    }
    return octaveCount;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    // Note: there is no fprintf in this function, as the
    // Stage 1 autotests call create_track but expect it to return NULL
    // (so this function should do nothing in Stage 1).
    
    struct track *newTrack = malloc(sizeof(struct track));
    assert(newTrack != NULL);
	newTrack->head = NULL;
	newTrack->current = NULL;
	
    return newTrack;
}

// Add a beat after the current beat in a track.
//If a beat exists after the track
//Add the beat after the first beat and so on.
//Otherwise, add the beat to the track
void add_beat_to_track(Track track, Beat beat) { //Check this logic JEREMY!
    //int beatCount = 0; //This counts the number of beats in a Track
    if (track->head == NULL){
    	track->head = beat;
    	//beatCount = 1;
    }
    else{
		struct beat *newBeat = beat; //These were my error//create_beat(); //malloc (sizeof (struct beat));
		struct beat *curr = newBeat;
		
		//Add the beat as the first element
		//of the linked list if no beat
		//is selected
    	if(track->current == NULL) {
			newBeat->next = track->head;
    		track->head = newBeat;
    	}
    	else {//Add the beat after the selected beat
    		curr = track->current;
    		newBeat->next = curr->next;
    		curr->next = newBeat;

    	}
    	//Testing for the length of the list
		/*while(curr != NULL) {
			curr = curr->next;
			beatCount++;
		}
		printf("There are/is %d beat\n", beatCount);
		*///Remember to remove the scaffold
    }
    
}

//Set a track's current beat to the next beat.
//By changing the Track's "current" pointer
//to the next beat
int select_next_beat(Track track) {
    //Move to the next beat 
    struct beat *curr = track->head;
    
    if(track->current == NULL){
    	if (track->head == NULL){
    		track->current = track->head;
    		return TRACK_STOPPED;
    	}
    	else {
			track->current = track->head;
			return TRACK_PLAYING;
    	}
    }
    else{
		curr = track->current;
		track->current = curr->next;
		//Check if current pointer is pointing an NULL 
		//Or a beat
		//Then return a value
		if(track->current == NULL) {
			//printf("Track Stopped\n");
			return TRACK_STOPPED;
		}
		else{
			//printf("Track Playing\n");
			return TRACK_PLAYING;
		}
    }
    
}

// Print the contents of a track.
void print_track(Track track) {
	int beatCount = 1;
    struct beat *currBeat = track->head;
    while (currBeat != NULL){
    	//print out the selected beat
    	if(track->current == currBeat) {
    		printf(">");
    	}
    	else {
    		printf(" ");
    	}
    	//print out the beat
    	printf("[%d] ", beatCount);
    	
    	int noteCount = 0;
    	//print out the notes  	
    	struct note *currNote = currBeat->notes;
    	while (currNote != NULL) {
    		if (noteCount > 0){
    			printf(" | ");
    		}
    		
    		if (currNote->key >= 10){
    			printf("%d %d", currNote->octave, currNote->key);
    		}
    		else {
    			printf("%d 0%d", currNote->octave, currNote->key);
    		}
    		
    		noteCount++;
    		currNote = currNote->next;
    	}
    	
    	printf("\n");
		currBeat = currBeat->next;
		beatCount++;
    }
    
    return;
}

// Count the number beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    //printf("count_beats_left_in_track not implemented yet.\n");
    int beatCount = 0;
    struct beat *curr = track->current;    
    if(curr != NULL){
    	curr = curr->next;
		while (curr != NULL){			
			curr = curr->next;
			beatCount++;
		}
    }
    else {
    	curr = track->head;
    	while (curr != NULL){
    		curr = curr->next;
    		beatCount++;
    	}
    }
    
    return beatCount;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_beat but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than exit).
    
    struct note *curr, *prev;
    curr = beat->notes;
    beat->notes = NULL;
    //Free all the notes
    while (curr != NULL) {
    	prev = curr;
    	curr = curr->next;
    	free (prev);
    }
    // Then free the beat
	free (beat);
    
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_track but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than print an error).
    
    struct beat *curr, *prev;
    curr = track->head;
    track->head = NULL;
    
    //Go to each beat,
    //and free each note,
    //then repeat until curr reaches NULL
    while (curr != NULL) { 	
    	prev = curr;
    	curr = curr->next;
    	//Free beat and all the notes associated with that beat
    	free_beat(prev);
    }
    free (track);
    
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    //printf("remove_selected_beat not implemented yet.");
    if(track->current == NULL){ //check if the track has stopped
    	return TRACK_STOPPED;
    }
    //begin deletion of a beat if a beat is selected
    else {
    	//loop through the list of beats
		struct beat *curr = track->head;
		struct beat *prev = curr;
		
		while (curr != track->current){
			prev = curr;
			curr = curr->next;
		}
		//need to consider removal of the 1st beat
		// and if the 1st beat is the last or not
		if (curr == track->head){
			int i = 0;
			// move the pointer by 1 element in the list
			while (i < 1){
				prev = curr;
				curr = curr->next;
				i++;
			}
			track->head = curr;
			//consider if the 1st beat is also the last
			if( track->head == NULL) {
				free_beat (prev);
				track->current = NULL;
			}
			else {
				free_beat (prev);
				track->current = curr;
			}		
		}
		// delete the selected beat other than than the first
		else {
			prev->next = curr->next;
			free_beat (curr);
			track->current = prev->next;
		}
		if (track->current != NULL)	{
			return TRACK_PLAYING;
		}
		else {
			return TRACK_STOPPED;
		}
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
	
	//max number of character is 122
	//and max #'s are 120
	//Because 9 11 is the highest number that can be made 
	//using letters and #'s
	int hashtagCount = 0;
    int returnVal = 0;
    int octave = 0;
    int key = 0;
    char musicArray [MAX_LENGTH];
    strncpy (musicArray, musical_notation, MAX_LENGTH);
    
    if ('0' <= musicArray[0] && musicArray[0] <= '9' ) {
    	returnVal = VALID_NOTE;
    	octave = octave_num_check (musicArray);
    }
    else {
    	return INVALID_MUSICAL_NOTE;
    }
    
    if ( 'A' <= musicArray[1] && musicArray[1] <= 'G') {
    	returnVal = VALID_NOTE;
    	key = key_num_check (musicArray);
    }
    else {
    	return INVALID_MUSICAL_NOTE;
    }
    
    //loop to check if # is present in the array
    int i = 2;
    while (i < MAX_LENGTH && musicArray [i] != '\0') {
    		
		if (musicArray [i] == '#') {
			hashtagCount++;
		}
    	i++;
    }
    key = key + hashtagCount;
   	//Check if note value is out of bounds
    if (key > 11) {
    	octave = octave + key / 11 ;
    	key = (key % 11) - 1 ;
    }
    
   	returnVal = music_to_beat (beat, octave, key);
   	
    printf("Number of #'s are %d\n", hashtagCount);
    printf("%d\n", octave);
    printf("%d\n", key);
    
    return returnVal;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    //printf("cut_range_to_end not implemented yet.");
    struct beat *initialCurr = track->current;
    struct beat *initialPrev = initialCurr;//track->current;
    struct beat *lastCurr = track->current;
    struct beat *lastPrev = track->current;
    struct beat *listCount = track->current;
    int i = 1;
    int list_remain = 0;
    
    
    while (listCount != NULL) {
		listCount = listCount->next;
		list_remain++;
	}
	printf("%d\n", list_remain);
		//If the range_length is greater than the length of the remaining list
		//Then stop
	if (range_length >= list_remain) {
		return;
	}
	else if (range_length == 0 || range_length < 0) {
		return;
	}
    
    if (track->head != track->current) {
    	struct beat *holdCurr = track->head;
    	
    	while (holdCurr->next != initialCurr) {
    		holdCurr = holdCurr->next;
    	}
		//Get all the pointers required to shift
		//In position pt1
		while ( i < range_length) {
			initialCurr = initialCurr->next;
			i++;
		}
		//Get all the pointers required to shift
		//In position pt2
		while (lastCurr != NULL) {
			lastPrev = lastCurr;
			lastCurr = lastCurr->next;
		}   
		holdCurr->next = initialCurr->next;
		lastPrev->next = initialPrev;
		initialCurr->next = lastCurr;
    	
    }
    else {
    	//Get all the pointers required to shift
		//In position pt1
		while ( i < range_length) {
			initialCurr = initialCurr->next;
			i++;
		}
		//Get all the pointers required to shift
		//In position pt2
		while (lastCurr != NULL) {
			lastPrev = lastCurr;
			lastCurr = lastCurr->next;
		}   
		track->head = initialCurr->next;
		lastPrev->next = initialPrev;
		initialCurr->next = lastCurr;
    }
    printf("%d\n", i);
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {

    struct beat *finalPoint = track->current;
    struct beat *listCount = track->current;
    struct beat *next = NULL;
    struct beat *curr = track->current;
    struct beat *prev = NULL;
    int i = 1;
    int list_remain = 0;
    int beat_change = range_length - 1;
    
    
    while (listCount != NULL) {
		listCount = listCount->next;
		list_remain++;
	}
	//printf("%d\n", list_remain);
		//If the range_length is greater than the length of the remaining list
		//Then stop
	if (range_length >= list_remain) {
		beat_change = list_remain - 1;
	}
	else if (range_length == 0 || range_length < 0) {
		return 0;
	}
	
	
	while ( i <= range_length ) {
		finalPoint = finalPoint->next;
		i++;
	}

	if (track->head != track->current) {
		struct beat *holdInitial = track->head;
		while (holdInitial->next != curr) {
			holdInitial = holdInitial->next;
		}
		
		//holdLast stores the last element of a linked list
		prev = finalPoint;
		while (curr != finalPoint) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		holdInitial->next = prev;
	}
	
	else {
		prev = finalPoint;
		while (curr != finalPoint) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		track->head = prev;
	}
	
    return beat_change;
}

////////////////////////////////////////////////////////////////////////
//                         Jeremy's Functions                         //
////////////////////////////////////////////////////////////////////////

int octave_num_check  (char musicArray[]) {
	int octave = 0;
	if (musicArray[0] == '0'){
		octave = 0;
	}
	else if (musicArray[0] == '1'){
		octave = 1;
	}
	else if (musicArray[0] == '2'){
		octave = 2;
	}
	else if (musicArray[0] == '3'){
		octave = 3;
	}
	else if (musicArray[0] == '4'){
		octave = 4;
	}
	else if (musicArray[0] == '5'){
		octave = 5;
	}
	else if (musicArray[0] == '6'){
		octave = 6;
	}
	else if (musicArray[0] == '7'){
		octave = 7;
	}
	else if (musicArray[0] == '8'){
		octave = 8;
	}
	else if (musicArray[0] == '9'){
		octave = 9;
	}
	return octave;
}

int key_num_check (char musicArray []) {
	int key = 0;	
	if (musicArray[1] == 'A'){
		key = 0;
	}
	else if (musicArray[1] == 'B'){
		key = 2;
	}
	else if (musicArray[1] == 'C'){
		key = 3;
	}
	else if (musicArray[1] == 'D'){
		key = 5;
	}
	else if (musicArray[1] == 'E'){
		key = 7;
	}
	else if (musicArray[1] == 'F'){
		key = 8;
	}
	else if (musicArray[1] == 'G'){
		key = 10;
	}
	return key;
}

// Add a note to the end of a beat.
int music_to_beat(Beat beat, int octave, int key) {
// We need to somehow check if the user entered an input greater than before...
    //printf("add_note_to_beat not implemented yet.\n");
    struct note *newNote = malloc(sizeof(struct note));
	struct note *prev = NULL;
	struct note *curr = beat->notes;
	int returnVal = VALID_NOTE; // This variable checks for a valid note
	
	//Check for valid input, and also ensures octave and key are in their
	//boundaries
	if(0 <= octave && octave < 10){
    	if( 0 <= key && key < 12){
    		returnVal = VALID_NOTE;
    	}
    	else{
    		free(newNote);
    		return INVALID_MUSICAL_NOTE;
    	}
    }
   	else{
   		free(newNote);
   		return INVALID_MUSICAL_NOTE;
   	}
   	newNote->key = key;
	newNote->octave = octave; 
	
	//Check if a beat does not have a note
	//and needs to be placed at the beginning of a linked list
    if(beat->notes == NULL){
    	beat->notes = newNote;
    	newNote->next = NULL;
    	return returnVal;
    }	
    
    //Check if there are any duplicate notes
    //By looping through the list
    while (curr != NULL) {
    	if(curr->octave == octave) {
    		if (curr->key == key) {
    			free (newNote);
    			return INVALID_MUSICAL_NOTE;
    		}
    	}
    	prev = curr;
    	curr = curr->next;	
    }
    curr = beat->notes;
    prev = NULL;
    
    //Check previous Octave/Key size to the user input
	//and insert in the correct position
	while(curr != NULL) 
	{
		
		if ( curr->octave > octave) 
		{
			//consider the case if newNote is inserted
			//At the beginning of the list
			if (prev == NULL) 
			{
				beat->notes = newNote;
				newNote->next = curr;
				return returnVal;
			} 	
			prev->next = newNote;
			newNote->next = curr;
			return returnVal;
			
		}
		else if ( curr->octave == octave) 
		{
			struct note *currKey = curr;
			prev = currKey;		
			if (currKey == NULL) 
			{
				prev->next = newNote;
				newNote->next = currKey;
				return returnVal;
			}
			else 
			{
			//check if key > currKey.
			//Assuming that newNote is inserted between
			//the same octaves
				while ( currKey->key < key || currKey->next == NULL)
				{
					//Check if octave may be less than
					//the next octave
					if ( curr->octave > octave ) 
					{	
						prev->next = newNote;
						newNote->next = curr;
						return returnVal;
					}
					prev = currKey;
					currKey = currKey->next;
					curr = currKey;
					if (currKey == NULL) 
					{
						prev->next = newNote;
						newNote->next = currKey;
						return returnVal;
					}
				}
				
				prev->next = newNote;
				newNote->next = currKey;
				return returnVal;
			}
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = newNote;
	newNote->next = curr;
    
    return returnVal;
}























