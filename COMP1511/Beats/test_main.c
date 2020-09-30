//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 20T1 COMP1511: CS bEats
// test_main.c
//
// You must not change this file.
//
// Version 1.0.0: Release
// Version 1.0.1: Fix Typo, and quit when error is found.

#include "test_beats.h"
#include <stdio.h>
#include <stdlib.h>


void print_success(int is_success);

int main(void) {
    printf("========================[CS bEats Test Suite]=======================\n");
    printf("This test suite is designed to check your program complies with all \n");
    printf("the rules in the specification. We will test your tests by compiling\n");
    printf("it with multiple solutions in which one specific function is broken.\n");
    printf("Your task is to fill in the functions so we know which is broken.   \n");
    printf("====================================================================\n");

    printf("add_note_to_beat: \n");
    print_success(test_add_note_to_beat());
    printf("count_notes_in_octave: \n");
    print_success(test_count_notes_in_octave());
    printf("add_beat_to_track: \n");
    print_success(test_add_beat_to_track());
    printf("remove_selected_beat: \n");
    print_success(test_remove_selected_beat());
    printf("add_musical_note_to_beat: \n");
    print_success(test_add_musical_note_to_beat());
}

// Prints the message that's shown when you pass or fail.
void print_success(int is_success) {
    if (is_success) {
        printf("... [Passed]\n");
    }
    else {
        printf("... [Failed] - exiting\n");
        exit(0);
    }
}
