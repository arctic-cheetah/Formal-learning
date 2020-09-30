//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.h
//
// You must not change this file.
//
// Version 1.0.0: Release
// Version 1.0.1: Update 'two' to 'three'


#define MEETS_SPEC 1
#define DOES_NOT_MEET_SPEC 0

///////////////////////////////////////////////////////////
// Test whether add_note_to_beat returns the right values.
//
// For this function, the add_note_to_beat function may
// be broken. All other functions are implemented as normal.
// You should return `MEETS_SPEC` if `add_note_to_function`
// is working as the spec describes. If it doesn't do what
// the spec says it should, return `DOES_NOT_MEET_SPEC`.
//
// For full marks in this function, you should test at least
// three ways the `add_note_to_beat` function could fail.
// One test has already been provided to you, which you may
// keep or modify. It counts towards the three ways you are
// supposed to test.
// For instance:
//  - What if `add_note_to_beat` is given a negative key?
//  - What if `add_note_to_beat` doesn't check for if a
//    beat already exists?
//
// You should only need if statements and the functions in
// `beat.h` to test it, though you may use any C language
// features you have learned. You do not need to free memory.
int test_add_note_to_beat(void);


///////////////////////////////////////////////////////////
// Test whether count_notes_in_octave returns the correct values.
//
// For this function, the count_notes_in_octave function may
// be broken. All other functions are implemented as normal.
// You should return `MEETS_SPEC` if `count_notes_in_octave`
// is working as the spec describes. If it doesn't do what
// the spec says it should, return `DOES_NOT_MEET_SPEC`.
//
// For full marks in this function, you should test at least
// three ways the `count_notes_in_octave` function could fail.
// One test has already been provided to you, which you may
// keep or modify. It counts towards the three ways you are
// supposed to test.
// For instance:
//  - What if `count_notes_in_octave` is given a Beat with no
//    Notes?
//  - What if `count_notes_in_octave` is given a Beat with
//    no Notes of the right octave.
//  - What if `count_notes_in_octave` is given an invalid octave.
//
// You should only need if statements and the functions in
// `beat.h` to test it, though you may use any C lanugage
// features you have learned. You do not need to free memory.
int test_count_notes_in_octave(void);


///////////////////////////////////////////////////////////
// Test whether add_beat_to_track does add a note to the
// track.
//
// For this function, the `add_beat_to_track` function may
// be broken. All other functions are implemented as normal.
// You should return `MEETS_SPEC` if `add_beat_to_track`
// is working as the spec describes. If it doesn't do what
// the spec says it should, return `DOES_NOT_MEET_SPEC`.
//
// For full marks in this function, you should test at least
// three ways the `add_beat_to_track` function could fail.
// For instance:
//  - What if `add_beat_to_track` doesn't add anything to the
//    Track?
//  - Does it work differently with the first, or last beats?
//  - What if `add_beat_to_track` changes the current beat?
//
// Hint: Are there functions that tell you how many beats
// are in a track, or what the selected beat is?
//
// You should only need if statements and the functions in
// `beat.h` to test it, though you may use any C lanugage
// features you have learned. You do not need to free memory.
int test_add_beat_to_track(void);

///////////////////////////////////////////////////////////
// Test whether remove_selected_beat removes the current Beat.
//
// For this function, the remove_selected_beat function may
// be broken. All other functions are implemented as normal.
// You should return `MEETS_SPEC` if `remove_selected_beat`
// is working as the spec describes. If it doesn't do what
// the spec says it should, return `DOES_NOT_MEET_SPEC`.
//
// For full marks in this function, you should test at least
// three ways the `remove_selected_beat` function could fail.
// For instance:
//  - What if `remove_selected_beat` doesn't remove a beat?
//  - Does it work differently with the first or last beats?
//  - What if `remove_selected_beat` deletes multiple beats?
//
// You should only need if statements and the functions in
// `beat.h` to test it, though you may use any C lanugage
// features you have learned. You do not need to free memory.
int test_remove_selected_beat(void);

///////////////////////////////////////////////////////////
// Test whether add_musical_note_to_beat correctly adds
// musical notes.
//
// For this function, the add_musical_note function may
// be broken. All other functions are implemented as normal.
// You should return `MEETS_SPEC` if `add_musical_note`
// is working as the spec describes. If it doesn't do what
// the spec says it should, return `DOES_NOT_MEET_SPEC`.
//
// For full marks in this function, you should test at least
// three ways the `add_musical_note` function could fail.
// For instance:
//  - Does it recognise a valid musical note?
//  - Does it reject an invalid musical note?
//  - Does it actually add a correct musical note?
//
// You should only need if statements and the functions in
// `beat.h` to test it, though you may use any C lanugage
// features you have learned. You do not need to free memory.
int test_add_musical_note_to_beat(void);
