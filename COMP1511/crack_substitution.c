// crack_substitution.c
// Andrew Bennett
// 2018-04-15
// Edited by Marc Chee (21/10/2019)

// Write a C program crack_substitution.c which decrypts text encrypted
// by an unknown cipher.
// Your program should make no assumptions about the language of the
// original text - don't assume it's English. In other words don't hard
// code English properties into your program, extract the statistical
// properties from the sample plain text. However, you can assume the
// English alphabet ('a'..'z').
//
// Your program will be given as a command-line argument the name of a
// file containing a large amount of unencrypted text in the same
// language as the encrypted text.
//
// Your program will be given the encrypted text on standard input. You
// may read it all before printing the decryption.
//
// You may assume the encrypted text contains at most 10000 characters.

// The key idea behind this approach is based around "n-grams" --
// collections of n letters. The frequency of n-grams in English is
// useful in determining whether we've managed to decode our ciphertext
// into something English -- i.e. we know that "the" / "ing" are far
// more likely to be valid n-grams (in this case trigrams) than say
// "jwq".
//
// With this, we don't need a word list containing possible valid
// English words -- this is especially important given that the words
// in the ciphertext may not appear in our corpus at all.

// Approach:
//   - calculate n-grams for the known unencrypted text
//   - generate a random "key" for the cipher; apply it to the ciphertext
//   - calculate n-grams for that deciphered text
//   - compare its n-grams with the "base" n-grams; calculate a
//     "goodness" score
//   - change the key by swapping every possible pair of characters;
//     keep track of the "best" result
//   - rinse and repeat until we're unable to get a "better" result
//
// This won't always find the correct decryption, so we repeat the entire
// process multiple times, keeping track of the very best overall key,
// and using that at the end to print our final result.

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Set this to 1 if you'd like to see the "progress" (it's pretty cool
// to watch)
#define DEBUG 0

#define MAX_FILENAME 1000
#define MAX_CIPHER_SIZE 10001
#define MAX_WORD_SIZE 1001
#define N_LETTERS 26

#define END_OF_INDICES -1

#define TRUE 1
#define FALSE 0

#define MAX_ATTEMPTS 20

#define REALLY_BAD -1000000

// used when deciding if two doubles are "equal"
#define EPSILON 0.000001

// Getting the ciphertext (from stdin)

void get_ciphertext(char raw_ciphertext[MAX_CIPHER_SIZE],
                    char ciphertext[MAX_CIPHER_SIZE]);
void print_ciphertext(char ciphertext[MAX_CIPHER_SIZE]);

// Reading (and processing) the unencrypted corpus

void process_corpus_ngrams(
    char *filename, double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]);

void get_corpus_ngrams(char *filename, int corpus_unigrams[N_LETTERS],
                       int corpus_bigrams[N_LETTERS][N_LETTERS],
                       int corpus_trigrams[N_LETTERS][N_LETTERS][N_LETTERS]);

void count_ngrams(int unigrams[N_LETTERS], int *total_unigrams,
                  int bigrams[N_LETTERS][N_LETTERS], int *total_bigrams,
                  int trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
                  int *total_trigrams);

void calculate_ngram_log_frequencies(
        double unigrams_lf[N_LETTERS], int unigrams[N_LETTERS], int total_unigrams,
        double bigrams_lf[N_LETTERS][N_LETTERS], int bigrams[N_LETTERS][N_LETTERS],
        int total_bigrams, double trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS],
        int trigrams[N_LETTERS][N_LETTERS][N_LETTERS], int total_trigrams);

// Extract the next word from the input stream / ciphertext array.

int get_word(FILE *input, int indices[MAX_WORD_SIZE]);
int get_next_ciphertext_word(char ciphertext[MAX_CIPHER_SIZE],
                             int indices[MAX_WORD_SIZE], int upto);
int get_index(int c);
void print_indices(int indices[MAX_WORD_SIZE]);

// Calculating the n-grams for a given word

void determine_ngrams(int unigrams[N_LETTERS],
                      int bigrams[N_LETTERS][N_LETTERS],
                      int trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
                      int indices[MAX_WORD_SIZE]);

void print_ngrams(int unigrams[N_LETTERS],
                  int bigrams[N_LETTERS][N_LETTERS],
                  int trigrams[N_LETTERS][N_LETTERS][N_LETTERS]);

void get_guess_ngrams(int key[N_LETTERS], char ciphertext[MAX_CIPHER_SIZE],
                      int guess_unigrams[N_LETTERS],
                      int guess_bigrams[N_LETTERS][N_LETTERS],
                      int guess_trigrams[N_LETTERS][N_LETTERS][N_LETTERS]);

void cipher_indices(int key[N_LETTERS], int indices[MAX_WORD_SIZE],
                    int ciphered_indices[MAX_WORD_SIZE]);

// Cracking the cipher!

void determine_key(char ciphertext[MAX_CIPHER_SIZE], int key[N_LETTERS],
                   double corpus_unigrams_lf[N_LETTERS],
                   double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
                   double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]);

double do_one_attempt(
    int best_key[N_LETTERS], char ciphertext[MAX_CIPHER_SIZE],
    double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]);

double get_best_permutation(
    int best_key[N_LETTERS], double best_goodness,
    char ciphertext[MAX_CIPHER_SIZE], double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]);

// Calculate the "goodness" of a given guess

double calculate_goodness(
    int key[N_LETTERS], char ciphertext[MAX_CIPHER_SIZE],
    double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]);

double compare_ngrams(
    int guess_unigrams[N_LETTERS],
    int guess_bigrams[N_LETTERS][N_LETTERS],
    int guess_trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
    double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]);

double log_frequency(int count_ngram, double log10_total_ngrams);

// Decode the ciphertext!

void decode_ciphertext(char ciphertext[MAX_CIPHER_SIZE], int key[N_LETTERS]);

int decode(char c, int key[N_LETTERS]);

// Misc helper functions

void print_key(int key[N_LETTERS]);
void copy_key(int key_to[N_LETTERS], int key_from[N_LETTERS]);
void generate_random_permutation(int key[N_LETTERS]);
void flip(int key[N_LETTERS], int i, int j);
int is_lowercase(char c);
int goodness_equals(double a, double b);

int main(void) {
    // Step 0: Read filename
    char file[MAX_FILENAME];
    fgets(file, MAX_FILENAME, stdin);
    // strip the \n from the end of file
    file[strlen(file) - 1] = '\0';
    
    // Step 1: get the ciphertext.
    //
    // Store two different "versions" of the ciphertext:
    //   - a processed version with only spaces and lowercase letters
    //     (uppercase letters are converted to lowercase)
    //
    //   - the "raw" ciphertext -- exactly character-for-character what
    //     we read from stdin.
    //
    // This means that we can do operations on the simplified version,
    // without ever having to worry again about what case is it, is it a
    // valid letter, etc etc.
    //
    // But, since we need to print out the deciphered version of the
    // full original plaintext (punctuation and all), we need to store
    // the "raw" ciphertext, which we will apply the deciphering to
    // later.
    char ciphertext[MAX_CIPHER_SIZE];
    char raw_ciphertext[MAX_CIPHER_SIZE];
    get_ciphertext(raw_ciphertext, ciphertext);

    // Step 2: Calculate some statistics about the unencrypted text.
    //
    // We intentionally don't store the text itself, and just read it
    // from the file as necessary to generate statistics -- this is
    // because we might have a HUGE corpus that wouldn't fit in memory,
    // but from which we could still get useful data.
    //
    // Specifically, we calculate the log-frequency of each of the
    // n-grams in the provided corpus of unencrypted text.
    // We store these directly, rather than storing the count of
    // n-grams, since it will save us a lot of CPU time later.
    double corpus_unigrams_lf[N_LETTERS] = {0};
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS] = {{0}};
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS] = {{{0}}};
    process_corpus_ngrams(file, corpus_unigrams_lf, corpus_bigrams_lf,
                          corpus_trigrams_lf);

    // Step 3: Calculate the "key" for our ciphertext.
    //
    // This is the mapping of letters, i.e. 'a' in the encrypted text is
    // 'r' in the original plaintext (etc).
    //
    // To make it simpler, we store the numbers 0-25 rather than the
    // letters 'a' to 'z'.
    //
    // So, if key[0] was 5, that means that 'a' (the first letter of the
    // alphabet) maps to 'f' (the sixth letter of the alphabet).

    int key[N_LETTERS] = {0};
    determine_key(ciphertext, key, corpus_unigrams_lf, corpus_bigrams_lf,
                  corpus_trigrams_lf);

    // Step 4: Decode the (raw) ciphertext back into the original
    // plaintext.
    decode_ciphertext(raw_ciphertext, key);

    return 0;
}

////////////////////////////////////////////////////////////////////////
//              GETTING THE CIPHERTEXT (FROM STDIN)                   //
////////////////////////////////////////////////////////////////////////

// Get the ciphertext (from standard input), and store two versions of
// it into the provided arrays -- "raw_ciphertext" is the raw,
// unprocessed version of the text we read in, "ciphertext" is the
// processed version (with punctuation etc removed, and all letters
// lowercase).
void get_ciphertext(char raw_ciphertext[MAX_CIPHER_SIZE],
                    char ciphertext[MAX_CIPHER_SIZE]) {

    // Keep track of where we're up to in the "raw ciphertext", as well
    // as where we're up to in the processed ciphertext.
    //
    // We need two separate variables because we don't want to leave
    // gaps in the processed version where we've removed characters from
    // the raw version.
    int i = 0;
    int c_upto = 0;

    int c;
    while (i < MAX_CIPHER_SIZE - 1 && (c = getchar()) != EOF) {
        raw_ciphertext[i] = c;
        // If it's a space or a letter, copy it to our processed
        // ciphertext array.
        if (isspace(c) || isalpha(c)) {
            // tolower will make uppercase lower, and leave lowercase
            // and space unchanged.
            ciphertext[c_upto] = tolower(c);
            c_upto++;
        }
        i++;
    }
    // Put a null terminator at the end of our strings, so that we know
    // where they end!
    ciphertext[c_upto] = '\0';
    raw_ciphertext[i] = '\0';
}

// A simple function to print out the ciphertext -- always useful to
// check that you've correctly obtained your input before you move on
// any further with your code.
void print_ciphertext(char ciphertext[MAX_CIPHER_SIZE]) {
    fputs(ciphertext, stdout);
}

////////////////////////////////////////////////////////////////////////
//           READING + PROCESSING THE UNENCRYPTED CORPUS              //
////////////////////////////////////////////////////////////////////////

// Calculate some statistics about the provided unencrypted text
// ("corpus").
// We intentionally don't store the text itself, and just read it
// from the file as necessary to generate statistics -- this is
// because we might have a HUGE corpus that wouldn't fit in memory,
// but from which we could still get useful data.
//
// We process the plaintext word-by-word (because we care about trigrams
// within a word -- the spaces between words are important!), and so
// this function will extract the next word from the input stream, and
// process its trigrams, then extract the next word and process it, etc
// etc.
void process_corpus_ngrams(
    char *filename, double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]) {

    // Arrays to store the n-grams in.
    int corpus_unigrams[N_LETTERS] = {0};
    int corpus_bigrams[N_LETTERS][N_LETTERS] = {{0}};
    int corpus_trigrams[N_LETTERS][N_LETTERS][N_LETTERS] = {{{0}}};

    // Actually get the input, and calculate the ngrams.
    get_corpus_ngrams(filename, corpus_unigrams, corpus_bigrams,
                      corpus_trigrams);

    // Now, calculate the log-frequencies of each n-gram, i.e.
    // log(count_of_this_ngram / total_ngrams).
    //
    // In order to do that, we need to know how many n-grams we have...
    // It's much nicer to be able to count the ngrams all in one go --
    // but to return three values, we need to use pointers (or structs)
    int total_unigrams = 0;
    int total_bigrams = 0;
    int total_trigrams = 0;
    count_ngrams(corpus_unigrams, &total_unigrams,
                 corpus_bigrams, &total_bigrams,
                 corpus_trigrams, &total_trigrams);

    // And, finally, calculate the log-frequencies of each n-gram.
    // These get stored in the corpus ngram log-frequency arrays we were
    // passed into this function.
    calculate_ngram_log_frequencies(
        corpus_unigrams_lf, corpus_unigrams, total_unigrams,
        corpus_bigrams_lf, corpus_bigrams, total_bigrams,
        corpus_trigrams_lf, corpus_trigrams, total_trigrams);
}

// Work through the input, calculating the n-grams for each word.
void get_corpus_ngrams(char *filename, int corpus_unigrams[N_LETTERS],
                       int corpus_bigrams[N_LETTERS][N_LETTERS],
                       int corpus_trigrams[N_LETTERS][N_LETTERS][N_LETTERS]) {

    FILE *input = fopen(filename, "r");

    // When calculating the statistics, we don't actually care about
    // the letters being letters -- so we turn letters into numbers
    // between 0 and 25, where 0 is lowercase or uppercase 'a', and 25
    // is 'z' or 'Z'.
    int indices[MAX_WORD_SIZE] = {0};

    // We only consider one word at a time -- since we care about
    // identifying words in our ciphertext (spaces are important!)
    //
    // This will get a word from stdin, then fill the `indices` array
    // with the indexes for that word (i.e. 'a'/'A' would be represented
    // with a 0, etc.
    //
    // We then calculate the trigrams for that word, updating the
    // results in our trigrams array we've passed in from main.
    while (get_word(input, indices) != EOF) {
        // Update our n-gram statistics with the n-grams from the
        // current word.
        determine_ngrams(corpus_unigrams,
                         corpus_bigrams,
                         corpus_trigrams, indices);
    }

    // print_ngrams(corpus_unigrams, corpus_bigrams, corpus_trigrams);
}

// Count the number of unigrams/bigrams/trigrams in the text.
void count_ngrams(int unigrams[N_LETTERS], int *total_unigrams,
                  int bigrams[N_LETTERS][N_LETTERS], int *total_bigrams,
                  int trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
                  int *total_trigrams) {

    // Something particularly noteworthy here -- we don't run the inner
    // loop to check for bigrams starting with `i`, unless we have any
    // unigrams of `i`; and we don't run the inner-inner loop to check
    // for trigrams starting with `ij` unless we have any bigrams of
    // `ij`.
    // This cuts down on a LOT of extra processing overhead -- for
    // example, let's say we're looking at trigrams that start with
    // "zx". If there aren't any trigrams at all that start with "zx",
    // then we've wasted our time doing 26 unnecessary inner iterations
    // checking for "zxa" "zxb" "zxc" etc.
    // This might not sound like much, but its adds up -- adding the
    // check here to not try counting trigrams unless we have bigrams
    // made the code run about twice as fast. :+1:
    int i = 0;
    while (i < N_LETTERS) {
        // If we do actually have any unigrams of `i` (aka `i` appeared
        // in the plaintext at all), then increase our counter and check
        // for bigrams
        if (unigrams[i]) {
            // *total_unigrams, because total_unigrams is a pointer to
            // the variable back in the "process_corpus_ngrams" function.
            *total_unigrams += unigrams[i];
            int j = 0;
            while (j < N_LETTERS) {
                // If we do actually have any bigrams of [i][j] (aka the
                // letters "ij" appeared together at any point in the
                // plaintext), then keep looking for trigrams.
                if (bigrams[i][j]) {
                    *total_bigrams += bigrams[i][j];
                    int k = 0;
                    while (k < N_LETTERS) {
                        if (trigrams[i][j][k]) {
                            *total_trigrams += trigrams[i][j][k];
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }
}

// Go through all of the corpus's ngrams that we've now counted,
// and calculate the log-frequency for each of those ngrams.
//
// (note: this function prototype/signature is SO GROSS -- nine
// parameters??? split across more than nine lines??!?? this is why I
// used a struct in my original code, so that I could pass around a
// struct pointer rather than having to have such massively long
// function signatures. bleh.)
//
// On the bright side, pre-calculating these rather than trying to
// calculate them over and over again each time we calculate the
// "goodness" of a guess makes things a lot faster.
void calculate_ngram_log_frequencies(
        // unigrams
        double unigrams_lf[N_LETTERS],
        int unigrams[N_LETTERS],
        int total_unigrams,
        // bigrams
        double bigrams_lf[N_LETTERS][N_LETTERS],
        int bigrams[N_LETTERS][N_LETTERS],
        int total_bigrams,
        // trigrams
        double trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS],
        int trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
        int total_trigrams) {

    double log10_unigrams = log10(total_unigrams);
    double log10_bigrams = log10(total_bigrams);
    double log10_trigrams = log10(total_trigrams);

    int i = 0;
    while (i < N_LETTERS) {
        // Calculate the log-frequency of these unigrams
        unigrams_lf[i] = log_frequency(unigrams[i], log10_unigrams);

        // Check for bigrams
        int j = 0;
        while (j < N_LETTERS) {
            bigrams_lf[i][j] = log_frequency(bigrams[i][j], log10_bigrams);

            // Check for trigrams
            int k = 0;
            while (k < N_LETTERS) {
                trigrams_lf[i][j][k] =
                    log_frequency(trigrams[i][j][k], log10_trigrams);
                k++;
            }
            j++;
        }
        i++;
    }
}

////////////////////////////////////////////////////////////////////////
//              EXTRACT WORDS FROM THE INPUT/CIPHERTEXT               //
////////////////////////////////////////////////////////////////////////

// Get the next word from `input`, returns length of word or EOF
// word = letters, converted to lowercase
// any non-letters are ignored
// any whitespace terminates the word (and is not included)
int get_word(FILE *input, int indices[MAX_WORD_SIZE]) {

    int i = 0;
    int done = FALSE;
    int found_eof = FALSE;
    while (i < MAX_WORD_SIZE - 1 && !done) {
        // Get the next character.
        int c = fgetc(input);

        // If it's EOF, we're done with all of the text.
        if (c == EOF) {
            found_eof = TRUE;
            break;
        }

        // If it's whitespace, we're at the end of the word.
        if (isspace(c)) {
            done = TRUE;
            // Note that we can't null terminate our indices array,
            // because 0 is a valid value (i.e. the letter a).
            // Instead, we have a "custom" null terminator equivalent.
            indices[i] = END_OF_INDICES;
        }

        // If it's alpha, add it to the word
        // If it's not alpha, do nothing.
        if (isalpha(c)) {
            indices[i] = get_index(c);
            i++;
        }
    }

    // We already did this above -- if we hit the end of the loop
    // because we got more than MAX_WORD_SIZE then we didn't do it, so
    // let's do it again just to be safe..
    indices[i] = END_OF_INDICES;

    // i = word length
    if (found_eof) {
        i = EOF;
    }
    return i;
}

// Get the next word from the ciphertext. Takes in the ciphertext
// overall, the position we're up to within the ciphertext, and an
// "indices" array to fill with the indices for the word we extract
// (where "indices" is a mapping of A->0, B->1, .. Z->25.
int get_next_ciphertext_word(char ciphertext[MAX_CIPHER_SIZE],
                             int indices[MAX_WORD_SIZE], int upto) {

    // We're currently up to "upto", so look from here until we find a
    // word. Words are terminated by spaces -- we're working from our
    // processed ciphertext, and so we know it only has lowercase
    // letters and spaces (and a null terminator at the end).

    // Keeps track of where we're up to in the indices array.
    int i = 0;

    while (ciphertext[upto] != '\0' && !isspace(ciphertext[upto])) {
        indices[i] = get_index(ciphertext[upto]);
        upto++;
        i++;
    }

    // Don't forget to put the terminator back on the word!
    indices[i] = END_OF_INDICES;

    if (ciphertext[upto] == '\0') {
        upto = END_OF_INDICES;
    } else {
        // Move `upto` along to the start of the next word.
        upto++;
    }

    return upto;
}

// Takes in a letter (uppercase or lowercase), returns the index of that
// letter within the alphabet (i.e. 'a' / 'A' is 0, 'z' / 'Z' is 25).
int get_index(int c) {
    // Make it lowercase -- easier to deal with just one case
    // (avoids needing an if statement to check whether upper/lowercase
    // and subtracting 'A' or 'a')
    c = tolower(c);

    // Subtract 'a' from the letter: so 'a' - 'a' is 0, 'b' - 'a' is 1,
    // 'z' - 'a' is 25, etc.
    return c - 'a';
}

// Print out the indices, as numbers.
void print_indices(int indices[MAX_WORD_SIZE]) {
    int i = 0;
    while (indices[i] != END_OF_INDICES) {
        printf("%d ", indices[i]);
        i++;
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////
//             CALCULATING THE N-GRAMS FOR A GIVEN WORD               //
////////////////////////////////////////////////////////////////////////

// Returns the length of the word it's processed
void determine_ngrams(int unigrams[N_LETTERS],
                      int bigrams[N_LETTERS][N_LETTERS],
                      int trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
                      int indices[MAX_WORD_SIZE]) {

    // Store the current letter, the previous letter, and the
    // previous-previous (prev1) letter.
    int curr = -1;
    int prev = -1;
    int prev1 = -1;

    int i = 0;
    while (indices[i] != END_OF_INDICES) {
        curr = indices[i];

        unigrams[curr] += 1;

        // If prev is positive, then we've hit our second letter.
        if (prev >= 0) {
            bigrams[prev][curr] += 1;
        }

        // If prev1 is positive, then we've hit our third letter.
        if (prev1 >= 0) {
            trigrams[prev1][prev][curr] += 1;
        }

        // Shuffle them along, so our current letter is now our previous
        // letter, and our previous letter is now our previous-previous
        // letter.
        prev1 = prev;
        prev = curr;
        i++;
    }
}

// Always useful to be able to sanity check that the data we've gathered
// looks correct.
void print_ngrams(int unigrams[N_LETTERS],
                  int bigrams[N_LETTERS][N_LETTERS],
                  int trigrams[N_LETTERS][N_LETTERS][N_LETTERS]) {

    printf("looking at unigrams:\n");

    int i = 0;
    while (i < N_LETTERS) {
        if (unigrams[i]) {
            printf("%c: %d\n", i + 'a', unigrams[i]);
        }
        i++;
    }

    printf("looking at bigrams:\n");
    i = 0;
    while (i < N_LETTERS) {
        int j = 0;
        while (j < N_LETTERS) {
            if (bigrams[i][j]) {
                printf("%c%c: %d\n", i + 'a', j + 'a', bigrams[i][j]);
            }
            j++;
        }
        i++;
    }

    printf("looking at trigrams:\n");
    i = 0;
    while (i < N_LETTERS) {
        int j = 0;
        while (j < N_LETTERS) {
            int k = 0;
            while (k < N_LETTERS) {
                if (trigrams[i][j][k]) {
                    printf("%c%c%c: %d\n", i + 'a', j + 'a', k + 'a',
                           trigrams[i][j][k]);
                }
                k++;
            }
            j++;
        }
        i++;
    }
}

// Work out the n-grams for our current guess, given a key and the
// ciphertext (and some arrays to store the ngrams in).
// This applies the decryption key to the ciphertext, and then calls the
// pre-existing "determine_ngrams" function that we've already used for
// the provided unencrypted text.
void get_guess_ngrams(int key[N_LETTERS], char ciphertext[MAX_CIPHER_SIZE],
                      int guess_unigrams[N_LETTERS],
                      int guess_bigrams[N_LETTERS][N_LETTERS],
                      int guess_trigrams[N_LETTERS][N_LETTERS][N_LETTERS]) {

    // We have our current guess: the ciphertext, and a key
    // (mapping of A->Z).
    //
    // We need to get a word to pass to our determine_ngrams function.
    //
    // A "word" means the next word we're up to in the ciphertext,
    // permuted with the key.
    //
    // So -- get the next word out, get the indices for it,
    // apply the permutation to those, pass that into determine_ngrams
    //
    // The only underlying difference is in how it gets a word
    // -- and at the end of the day, we really just want an indices
    // array.

    int indices[MAX_WORD_SIZE] = {0};
    int ciphered_indices[MAX_WORD_SIZE] = {0};

    int upto = 0;
    int done = FALSE;
    while (!done) {
        // Get the next word, and store it in the "indices" array.
        // returns the starting position of the next word in the array,
        // or END_OF_INDICES if we've reached the end of the ciphertext.
        upto = get_next_ciphertext_word(ciphertext, indices, upto);

        if (upto == END_OF_INDICES) {
            done = TRUE;
        } else {
            cipher_indices(key, indices, ciphered_indices);

            determine_ngrams(guess_unigrams, guess_bigrams, guess_trigrams,
                             ciphered_indices);
        }
    }
}

// Apply the cipher (key) to each of the indices in the array, storing
// them in the "ciphered_indices" array.
void cipher_indices(int key[N_LETTERS], int indices[MAX_WORD_SIZE],
                    int ciphered_indices[MAX_WORD_SIZE]) {

    // key is an array of size 26, where key[0] is what A should
    // be, key[1] is what B should be, etc.
    //
    // We want to thus "cipher" each index as appropriate -- i.e.
    // work out which value it should be according to our key.

    int i = 0;
    while (indices[i] != END_OF_INDICES) {
        ciphered_indices[i] = key[indices[i]];
        i++;
    }
    // Make sure we put the terminator back on!
    ciphered_indices[i] = END_OF_INDICES;
}

////////////////////////////////////////////////////////////////////////
//               CRACKING THE CIPHER!                                 //
////////////////////////////////////////////////////////////////////////

// Works out the correct decryption key for the ciphertext, and puts it
// in "key".
//
// To calculate the "correct key", we start out by generating some
// random key, and then flipping every possible pair of characters to
// form a new key.
// We then measure how "good" a given key is, and use the best of the
// keys to continue on, and flip every possible pair of characters in
// that key, etc etc, until we can't find a better solution.
//
// However, this doesn't always get us the correct answer, so we repeat
// this overall process some number of times, keeping track of the
// overall best key we've found.
//
// The number of iterations we do there is determined by the time limit
// we have when running under `dcc --valgrind` -- I think we can get
// away with 5 attempts?
void determine_key(char ciphertext[MAX_CIPHER_SIZE], int key[N_LETTERS],
                   double corpus_unigrams_lf[N_LETTERS],
                   double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
                   double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]) {

    // Seed the random number generator.
    srand(time(NULL));

    double best_goodness = REALLY_BAD;
    int current_attempt = 0;
    // Try to generate a key several times, to increase the likelihood
    // of actually getting the right answer.
    while (current_attempt < MAX_ATTEMPTS) {
        // Do one overall attempt -- i.e. generate a random key, and
        // iterate over that key until we can't make it any better.

        // Store the best key we've found in this attempt.
        int best_key[N_LETTERS];
        double goodness =
            do_one_attempt(best_key, ciphertext, corpus_unigrams_lf,
                           corpus_bigrams_lf, corpus_trigrams_lf);

        // If the new key we've found is better than our overall best
        // key, update our overall best key.
        if (goodness > best_goodness) {
            best_goodness = goodness;
            copy_key(key, best_key);
        }

        if (DEBUG) {
            decode_ciphertext(ciphertext, key);
            printf("\n\n");
        }
        current_attempt++;
    }
}

// This does an overall attempt (which we do a few of, since one doesn't
// always do the best)
double do_one_attempt(
        int best_key[N_LETTERS], char ciphertext[MAX_CIPHER_SIZE],
        double corpus_unigrams_lf[N_LETTERS],
        double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
        double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]) {

    // Current mapping of A-Z
    int current_key[N_LETTERS];

    // fill this with a randomly generated key
    generate_random_permutation(current_key);

    // Start out with some impossibly-bad initial value for our "best goodness",
    // so that we know as soon as we do our first calculation it will be the
    // best so far.
    double best_goodness = REALLY_BAD;
    int attempt = 0;
    int done = 0;

    while (!done) {
        // Do one iteration over this current key -- i.e. try swapping
        // every possible pair of characters within the key.
        double goodness = get_best_permutation(
            current_key, best_goodness, ciphertext, corpus_unigrams_lf,
            corpus_bigrams_lf, corpus_trigrams_lf);

        if (DEBUG) {
            // printf("KEY: "); print_key(current_key);
            // printf("GOODNESS: %lf\n", goodness);
        }
        // If this is the same as our current best, then we've found the
        // best that we can (i.e. the "local maxima") -- it might not be
        // the best solution overall, but we're not going to find
        // anything better.
        if (goodness_equals(goodness, best_goodness)) {
            if (DEBUG)
                printf("DONE!\n");
            done = TRUE;
        }

        // If we've the key we've found is better than the best, then
        // use this one -- but we know that we've gotten the best key
        // back from `inner` so this is unnecessary?
        if (goodness > best_goodness) {
            best_goodness = goodness;
            // copy the best key into the default
            copy_key(best_key, current_key);
            if (DEBUG)
                decode_ciphertext(ciphertext, best_key);
        }

        attempt++;
    }
    return best_goodness;
}

// Needs to have the key that it's starting from, and the key that it's
// temporarily working with (which it can store itself?)
// Need to store the starting key (which can also be the best key?)
// separately (because we need to be able to update)
double get_best_permutation(
    int best_key[N_LETTERS], double best_goodness,
    char ciphertext[MAX_CIPHER_SIZE], double corpus_unigrams_lf[N_LETTERS],
    double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
    double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]) {

    int current_guess[N_LETTERS];
    // Start out with the best key we know about thus far, and iterate
    // on that.
    copy_key(current_guess, best_key);

    // Try flipping every possible pair of letters.
    int i = 0;
    while (i < N_LETTERS) {
        int j = 0;
        while (j < N_LETTERS) {
            if (i != j) {
                // Flip the indexes at pos i, j.
                flip(current_guess, i, j);

                // Determine the "goodness" of this current guess, based
                // on how well the n-gram distribution matches that of
                // the unencrypted corpus we were given.
                double goodness = calculate_goodness(
                    current_guess, ciphertext, corpus_unigrams_lf,
                    corpus_bigrams_lf, corpus_trigrams_lf);

                // If this current guess is better, update our
                // best_goodness and copy it into best_key.
                // note that we're comparing to the overall goodness
                // across this attempt, since we want to be getting
                // better each time, rather than starting from scratch.
                if (goodness > best_goodness) {
                    copy_key(best_key, current_guess);
                    best_goodness = goodness;
                }
                // Flip them back, so that we're starting from scratch
                // with our next attempt.
                flip(current_guess, j, i);
            }
            j++;
        }
        i++;
    }

    // Return the new best goodness that we've found, so that the parent
    // function can decide whether to use this new key.
    return best_goodness;
}

////////////////////////////////////////////////////////////////////////
//           CALCULATING THE "GOODNESS" OF A GIVEN GUESS              //
////////////////////////////////////////////////////////////////////////

// Calculates the "goodness" of the current guess. This is done by
// comparing the frequencies of the ngram distribution of this
// ciphertext vs the frequencies of the provided corpus of unencrypted
// text.
double calculate_goodness(
        int key[N_LETTERS], char ciphertext[MAX_CIPHER_SIZE],
        double corpus_unigrams_lf[N_LETTERS],
        double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
        double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]) {

    int guess_unigrams[N_LETTERS] = {0};
    int guess_bigrams[N_LETTERS][N_LETTERS] = {{0}};
    int guess_trigrams[N_LETTERS][N_LETTERS][N_LETTERS] = {{{0}}};

    get_guess_ngrams(key, ciphertext, guess_unigrams, guess_bigrams,
                     guess_trigrams);

    double goodness = compare_ngrams(guess_unigrams, guess_bigrams,
                                     guess_trigrams, corpus_unigrams_lf,
                                     corpus_bigrams_lf, corpus_trigrams_lf);

    return goodness;
}

// Compare the unigram distribution in the guess to the unigram
// distribution in the corpus of unencrypted text.
// This works by summing (the log-frequency of that unigram in the
// corpus of unencrypted text) for each unigram in the ciphertext.
// (That wasn't explained very well, so just bear with me....)
double
compare_ngrams(int guess_unigrams[N_LETTERS],
               int guess_bigrams[N_LETTERS][N_LETTERS],
               int guess_trigrams[N_LETTERS][N_LETTERS][N_LETTERS],
               double corpus_unigrams_lf[N_LETTERS],
               double corpus_bigrams_lf[N_LETTERS][N_LETTERS],
               double corpus_trigrams_lf[N_LETTERS][N_LETTERS][N_LETTERS]) {

    double difference = 0;

    // Time for another one of these fantastic massive n^3 loops....
    int i = 0;
    while (i < N_LETTERS) {
        // Only keep going if we have this unigram in the guess
        if (guess_unigrams[i]) {
            difference += corpus_unigrams_lf[i] * guess_unigrams[i];
            int j = 0;
            while (j < N_LETTERS) {
                // Only keep going if we have this bigram in the guess
                if (guess_bigrams[i][j]) {
                    difference += corpus_bigrams_lf[i][j] * guess_bigrams[i][j];
                    int k = 0;
                    while (k < N_LETTERS) {
                        if (guess_trigrams[i][j][k]) {
                            difference += corpus_trigrams_lf[i][j][k] *
                                          guess_trigrams[i][j][k];
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }
    return difference;
}

// Calculate log10 of the frequency of this ngram -- the number of times
// this ngram occurred divided by the total ngrams.
double log_frequency(int count_ngram, double log10_total_ngrams) {
    double value = count_ngram;
    if (count_ngram == 0) {
        value = 0.01;
    }

    // The calculation here is log10(value/total_ngrams).
    // We speed this up in two ways:
    //   - log10(value) - log10(total_ngrams)
    //   - pre-calculating log10(total_ngrams) rather than recalculating
    return log10(value) - log10_total_ngrams;
}

////////////////////////////////////////////////////////////////////////
//                 DECODE THE CIPHERTEXT!                             //
////////////////////////////////////////////////////////////////////////

// Run through the entire ciphertext, decoding it with the specified key.
void decode_ciphertext(char ciphertext[MAX_CIPHER_SIZE], int key[N_LETTERS]) {
    int i = 0;
    while (i < MAX_CIPHER_SIZE && ciphertext[i] != '\0') {
        int x = decode(ciphertext[i], key);
        putchar(x);
        i++;
    }
}

// Decode a single character 'c', given the key.
int decode(char c, int key[N_LETTERS]) {
    // The decoded character is the character itself, unless...
    int decoded = c;

    // ... it's a letter, in which case we do need to decode it.
    if (isalpha(c)) {
        if (is_lowercase(c)) {
            int index = c - 'a';
            decoded = key[index] + 'a';
        } else {
            int index = c - 'A';
            decoded = key[index] + 'A';
        }
    }
    return decoded;
}

////////////////////////////////////////////////////////////////////////
//                MISC HELPER FUNCTIONS                               //
////////////////////////////////////////////////////////////////////////

// Print out a key, converting the numbers to letters.
void print_key(int key[N_LETTERS]) {
    int i = 0;
    while (i < N_LETTERS) {
        printf("%c", 'a' + key[i]);
        i++;
    }
    printf("\n");
}

// Copy the values from one key to another.
void copy_key(int key_to[N_LETTERS], int key_from[N_LETTERS]) {
    int i = 0;
    while (i < N_LETTERS) {
        key_to[i] = key_from[i];
        i++;
    }
}

// Generates a random permutation of values; stores it in "key".
// The random permutation is done using the "Fisher–Yates shuffle".
void generate_random_permutation(int key[N_LETTERS]) {
    int i = 0;
    while (i < N_LETTERS) {
        key[i] = i;
        i++;
    }

    i = 0;
    while (i < N_LETTERS) {
        int rand_index = rand() % (N_LETTERS - i) + i;
        int tmp = key[rand_index];
        key[rand_index] = key[i];
        key[i] = tmp;
        i++;
    }
}

// Swaps the elements at index i and j.
void flip(int key[N_LETTERS], int i, int j) {
    int tmp = key[i];
    key[i] = key[j];
    key[j] = tmp;
}

int is_lowercase(char c) {
    return (c >= 'a' && c <= 'z');
}

// Since we can't compare doubles for equality, instead we check if
// they're "close enough".
int goodness_equals(double a, double b) {
    return (a - b) < EPSILON;
}
