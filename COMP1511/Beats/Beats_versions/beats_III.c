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

#include "beats.h"

// Add your own #defines here.

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
    	track->current = track->head;
    	return TRACK_PLAYING;
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
    return TRACK_STOPPED;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    printf("add_musical_note_to_beat not implemented yet.");
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    printf("cut_range_to_end not implemented yet.");
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    printf("reverse_range not implemented yet.");
    return 0;
}

////////////////////////////////////////////////////////////////////////
//                         Jeremy's Functions                         //
////////////////////////////////////////////////////////////////////////

























