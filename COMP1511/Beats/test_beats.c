// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by Jeremy Mang
// on 10/04/2020
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"

#define MAX_LENGTH 124


// Test function for `add_note_to_beat`
int test_add_note_to_beat(void) {
    // Test 1: Rejecting negative inputs.
    Beat test_beat = create_beat();
    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 2: Boundary cases for  0 < octave < 10 and  0 < key < 12
    if (add_note_to_beat(test_beat, 0, 0) != VALID_NOTE) {
    	return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 10, 1) != INVALID_OCTAVE) {
    	return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, 12) != INVALID_KEY) {
    	return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 100, 100) != INVALID_OCTAVE) {
    	return DOES_NOT_MEET_SPEC;
    }
    // Test 3: Test for ascendency (increasing order)
	if ( add_note_to_beat(test_beat, 5, 5) != VALID_NOTE ) {
		return DOES_NOT_MEET_SPEC;
	}
	if ( add_note_to_beat(test_beat, 5, 5) != NOT_HIGHEST_NOTE ) {
		return DOES_NOT_MEET_SPEC;
	}
	if ( add_note_to_beat(test_beat, 5, 6) != VALID_NOTE ) {
		return DOES_NOT_MEET_SPEC;
	}

	free_beat(test_beat);
    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`
int test_count_notes_in_octave(void){
	Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 1, 1);
    add_note_to_beat(test_beat, 1, 5);
    // Test 1: Counting invalid octaves.
    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 2: Count non-existent octaves.
    if (count_notes_in_octave(test_beat, 9) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    //Test 3: Check for the correct number of cases
    if (count_notes_in_octave(test_beat, 1) != 2 ) {
    	return DOES_NOT_MEET_SPEC;
    }
    //Test 4: Check for beats with zero notes
    //Beat test_beat = create_beat();
    if (count_notes_in_octave(test_beat, 5) != 0 ) {
    	return DOES_NOT_MEET_SPEC;
    }
    free_beat(test_beat);
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    // Test 1: Check if a beat is added successfully
    Track test_track = create_track();
	Beat test_beatQ = create_beat();
    add_note_to_beat (test_beatQ, 1, 1);
    add_note_to_beat (test_beatQ, 1, 5);
    add_beat_to_track (test_track, test_beatQ);
    
    if (count_beats_left_in_track (test_track) != 1) {
    	return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: Check if track selection works
    if (select_next_beat (test_track) != TRACK_PLAYING) {
    	return DOES_NOT_MEET_SPEC;
    }
    // Test 3: Check if selecting the next beat works
    Beat test_beatK = create_beat();
    add_note_to_beat (test_beatK, 2, 4);
    add_beat_to_track (test_track, test_beatK);
    
    Beat test_beatL = create_beat();
    add_note_to_beat (test_beatL, 3, 7);
    add_beat_to_track (test_track, test_beatL);
    
    select_next_beat (test_track);
    if (count_beats_left_in_track (test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 4: Check if a beat is inserted in the correct position
    //Given that a beat is selected
    Beat test_beatJ = create_beat();
    add_note_to_beat (test_beatJ, 4, 0);
    add_beat_to_track (test_track, test_beatJ);
    
    if (count_beats_left_in_track (test_track) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    free_beat(test_beatJ);
    free_beat(test_beatL);
    free_beat(test_beatK);
    free_beat(test_beatQ);
    
    // Test 5: Check if the correct number of beats is given to a track
    Track test_trackI = create_track();
    Beat test_beata = create_beat();
    Beat test_beatb = create_beat();
    Beat test_beatc = create_beat();
    add_note_to_beat(test_beata, 2, 5);
    add_beat_to_track(test_trackI, test_beata);
    add_note_to_beat(test_beatb, 3, 5);
    add_beat_to_track(test_trackI, test_beatb);
    add_note_to_beat(test_beatc, 1, 0);
    add_beat_to_track(test_trackI, test_beatc);
    if (count_beats_left_in_track (test_trackI) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    free_beat(test_beata);
    free_beat(test_beatb);
    free_beat(test_beatc);
    
    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    // Test 1: Check if there are no beats
    // 'track stopped' is displayed
    Track test_trackL = create_track();
    if (remove_selected_beat (test_trackL) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: Check if a lone beat is deleted
    // 'track stopped' is displayed
    Track test_trackN = create_track();
	Beat test_beatN = create_beat();
    add_note_to_beat(test_beatN, 1, 1);
    add_note_to_beat(test_beatN, 1, 5);
    add_beat_to_track(test_trackN, test_beatN);
    
    select_next_beat (test_trackN);
    if (remove_selected_beat (test_trackN) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 3: Check if the track is playing if there were three beats
    //and one beat was removed at the middle.
    Track test_trackU = create_track();
    Beat test_beat1 = create_beat();
    Beat test_beat2 = create_beat();
    Beat test_beat3 = create_beat();
    add_note_to_beat(test_beat1, 2, 5);
    add_beat_to_track(test_trackU, test_beat1);
    add_note_to_beat(test_beat2, 3, 5);
    add_beat_to_track(test_trackU, test_beat2);
    add_note_to_beat(test_beat3, 1, 0);
    add_beat_to_track(test_trackU, test_beat3);
    select_next_beat (test_trackU);
    select_next_beat (test_trackU);
    
    if (remove_selected_beat (test_trackU) == TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 4: Check if the track is playing if there were three beats
    //and one beat was removed at the beginning.
    Track test_trackD = create_track();
    Beat test_beat4 = create_beat();
    Beat test_beat5 = create_beat();
    Beat test_beat6 = create_beat();
    add_note_to_beat(test_beat4, 2, 5);
    add_beat_to_track(test_trackD, test_beat4);
    add_note_to_beat(test_beat5, 3, 5);
    add_beat_to_track(test_trackD, test_beat5);
    add_note_to_beat(test_beat6, 1, 0);
    add_beat_to_track(test_trackD, test_beat6);
    select_next_beat (test_trackD);
    if (remove_selected_beat (test_trackD) == TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 5: Check if after deleting all of the beats
    // 'track stopped' is displayed
    Track test_trackP = create_track();
    Beat test_beat7 = create_beat();
    Beat test_beat8 = create_beat();
    Beat test_beat9 = create_beat();
    add_note_to_beat(test_beat7, 2, 5);
    add_beat_to_track(test_trackP, test_beat7);
    add_note_to_beat(test_beat8, 3, 5);
    add_beat_to_track(test_trackP, test_beat8);
    add_note_to_beat(test_beat9, 1, 0);
    add_beat_to_track(test_trackP, test_beat9);
    remove_selected_beat (test_trackP);
    remove_selected_beat (test_trackP);
    if (remove_selected_beat (test_trackP) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 6: Check if the selected beat was deleted correctly
    Track test_trackB = create_track();
    Beat test_beat10 = create_beat();
    Beat test_beat11 = create_beat();
    Beat test_beat12 = create_beat();
    add_note_to_beat(test_beat10, 2, 5);
    add_beat_to_track(test_trackB, test_beat10);
    add_note_to_beat(test_beat11, 3, 5);
    add_beat_to_track(test_trackB, test_beat11);
    add_note_to_beat(test_beat12, 1, 0);
    add_beat_to_track(test_trackB, test_beat12);
    select_next_beat (test_trackB);
    remove_selected_beat (test_trackB); 
    if ( count_beats_left_in_track (test_trackB) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: Check if input accepts #'s
    Beat test_beatR = create_beat();
    char musical_note1[MAX_LENGTH] = "m 4A##" ;
	if ( add_musical_note_to_beat (test_beatR, musical_note1) != VALID_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}

    // Test 2: Check if function rejects replicated input
    
    char musical_note2[MAX_LENGTH] = "m 4A##";
    if ( add_musical_note_to_beat (test_beatR, musical_note2) != INVALID_MUSICAL_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}

    // Test 3: Check if function rejects invalid input
    char musical_note3[MAX_LENGTH] = "m -1C##";
    if ( add_musical_note_to_beat (test_beatR, musical_note3) != INVALID_MUSICAL_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}
	char musical_note4[MAX_LENGTH] = "m 10A##";
	if ( add_musical_note_to_beat (test_beatR, musical_note4) != INVALID_MUSICAL_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}
	char musical_note4b[MAX_LENGTH] = "m 10F";
	if ( add_musical_note_to_beat (test_beatR, musical_note4b) != INVALID_MUSICAL_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}
	
	// Test 3.5: Check if function accepts valid input
	char musical_note4a[MAX_LENGTH] = "m 9F";
	if ( add_musical_note_to_beat (test_beatR, musical_note4a) != VALID_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}
	char musical_note4c[MAX_LENGTH] = "m 0G";
	if ( add_musical_note_to_beat (test_beatR, musical_note4c) != VALID_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}
	
	// Test 4: Check if input can accept wrapping of #'s
	
	char musical_note5[MAX_LENGTH] = "m 0A#######################################################################################################################";
	//This is 119 #'s which equates to 9 11.
	if ( add_musical_note_to_beat (test_beatR, musical_note5) != VALID_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}
	char musical_note5a[MAX_LENGTH] = "m 0G##";
	if ( add_musical_note_to_beat (test_beatR, musical_note5a) != VALID_NOTE ) {
	    return DOES_NOT_MEET_SPEC;
	}

    return MEETS_SPEC;
}l_note
