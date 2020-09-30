//  Written 3/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Crack a caesar cipher, by calculating log-likelihood of each possible shift
//  of the encrypted_text based on statistics from the supplied example text.

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define NOT_A_LETTER (-1)
#define ALPHABET_SIZE 26
#define MAX_FILENAME 1000
#define MAX_ENCRYPTED_TEXT 10000

int get_best_shift(char encrypted_text[MAX_ENCRYPTED_TEXT],
                   int encrypted_text_length, int letter_count[ALPHABET_SIZE],
                   int n_letters_read);

double get_shift_score(int shift, char encrypted_text[MAX_ENCRYPTED_TEXT],
                       int encrypted_text_length,
                       int letter_count[ALPHABET_SIZE], int n_letters_read);

void print_decrypted_text(int shift, char encrypted_text[MAX_ENCRYPTED_TEXT],
                          int encrypted_text_length);

int encrypt(int character, int shift);
int get_encrypted_text(char encrypted_text[MAX_ENCRYPTED_TEXT]);
int get_letter_frequencies(FILE *stream, int letter_count[ALPHABET_SIZE]);
int letter_index(int character);

int main(void) {
    char file[MAX_FILENAME];
    fgets(file, MAX_FILENAME, stdin);
    // strip the \n from the end of file
    file[strlen(file) - 1] = '\0';

    FILE *stream = fopen(file, "r");

    if (stream == NULL) {
        perror(file); // prints why the open failed
        return 1;
    }

    // 1 array element for each English letter
    int letter_count[ALPHABET_SIZE] = {0};
    int n_letters_read = get_letter_frequencies(stream, letter_count);
    assert(n_letters_read > 0);

    char encrypted_text[MAX_ENCRYPTED_TEXT];
    int encrypted_text_length = get_encrypted_text(encrypted_text);

    int best_shift = get_best_shift(encrypted_text, encrypted_text_length,
                                    letter_count, n_letters_read);

    print_decrypted_text(best_shift, encrypted_text, encrypted_text_length);

    return 0;
}

// find most likely shift

int get_best_shift(char encrypted_text[MAX_ENCRYPTED_TEXT],
                   int encrypted_text_length, int letter_count[ALPHABET_SIZE],
                   int n_letters_read) {
    double best_score;
    int best_shift;

    int shift = 0;
    while (shift < ALPHABET_SIZE) {
        double score =
            get_shift_score(shift, encrypted_text, encrypted_text_length,
                            letter_count, n_letters_read);
        if (shift == 0 || score > best_score) {
            best_shift = shift;
            best_score = score;
        }

        shift = shift + 1;
    }
    return best_shift;
}

// calculate log-likelihood of encrypted_text based on supplied example text
// many scoring functions would work here - log-likelihood is optimal given some very-restrictive assumptions

double get_shift_score(int shift, char encrypted_text[MAX_ENCRYPTED_TEXT],
                       int encrypted_text_length,
                       int letter_count[ALPHABET_SIZE], int n_letters_read) {
    double score = 0;
    int i = 0;
    while (i < encrypted_text_length) {
        int character = encrypt(encrypted_text[i], shift);
        int index = letter_index(character);
        if (index != NOT_A_LETTER) {
            score += log(letter_count[index] / (double)n_letters_read);
        }
        i = i + 1;
    }
    return score;
}

void print_decrypted_text(int shift, char encrypted_text[MAX_ENCRYPTED_TEXT],
                          int encrypted_text_length) {
    int i = 0;
    while (i < encrypted_text_length) {
        int character = encrypt(encrypted_text[i], shift);
        putchar(character);
        i = i + 1;
    }
}

int encrypt(int character, int shift) {
    if (character >= 'A' && character <= 'Z') {
        return 'A' + (character - 'A' + shift) % ALPHABET_SIZE;
    } else if (character >= 'a' && character <= 'z') {
        return 'a' + (character - 'a' + shift) % ALPHABET_SIZE;
    } else {
        return character;
    }
}

int get_encrypted_text(char encrypted_text[MAX_ENCRYPTED_TEXT]) {
    int character = getchar();
    int n_characters_read = 0;
    while (character != EOF && n_characters_read < MAX_ENCRYPTED_TEXT) {
        encrypted_text[n_characters_read] = character;
        n_characters_read = n_characters_read + 1;
        character = getchar();
    }
    return n_characters_read;
}

int get_letter_frequencies(FILE *stream, int letter_count[ALPHABET_SIZE]) {
    int character = fgetc(stream);
    int n_letters_read = 0;

    while (character != EOF) {
        int index = letter_index(character);
        if (index != NOT_A_LETTER) {
            letter_count[index] = letter_count[index] + 1;
        }
        character = fgetc(stream);
        n_letters_read = n_letters_read + 1;
    }

    return n_letters_read;
}

// return position of letter in English  alphabet (0..25)
// for lower case and upper case letter
// return NOT_A_LETTER for other characters

int letter_index(int character) {
    if (character >= 'A' && character <= 'Z') {
        return character - 'A';
    } else if (character >= 'a' && character <= 'z') {
        return character - 'a';
    } else {
        return NOT_A_LETTER;
    }
}
