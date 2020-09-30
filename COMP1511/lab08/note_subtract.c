

// This program was written by Jeremy Mang z5312813
// on 09/04/2020

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// A struct note * IS a Note
typedef struct note *Note;

//There are 10 octaves (0 to 9) and 12 notes (0 to 11)
struct note {
    int octave;
    int key;
    Note next;
};

Note note_subtract(Note higher, Note lower);
void print_note(Note n);

int main(void) {
    int octave, key;
    scanf("%d %d", &octave, &key);
    // NOTE: the {octave, key, NULL} syntax is short for
    // a.octave = octave; a.key = key; a.next = NULL;
    struct note a = {octave, key, NULL};
    scanf("%d %d", &octave, &key);
    struct note b = {octave, key, NULL};
    Note diff = note_subtract(&a, &b);
    print_note(diff);
    free(diff);
    return 0;
}

// For a note with octave 0, and note 9,
// `print_note` should print:
// "0 09\n"
void print_note(Note n) {
    if(n->key < 10){
        printf("%d 0%d\n", n->octave, n->key);
    }
    else{
        printf("%d %d\n", n->octave, n->key);
    }
}


//Returns a pointer to a malloced struct containing the difference between a 
//higher and a lower note
Note note_subtract(Note higher, Note lower) {
    // TODO: This should return a struct created with malloc.
    Note difference = malloc(sizeof(Note));
    difference->octave = higher->octave - lower->octave;
    difference->key = higher->key - lower->key;

    if (difference->key < 0){
        difference->octave --;
        difference->key +=12;
    }
    
    return difference;

}
