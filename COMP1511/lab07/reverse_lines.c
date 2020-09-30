//  Written 3/5/2018 by Andrew Taylor (andrewt@unsw.edu.au)
//  Reads lines and writes them out with the characters of each line in reverse order.
//  Stop when it reaches the end of input.

#include <stdio.h>

#define MAX_LINE_CHARS 4096

int main(void) {
    char line[MAX_LINE_CHARS];

    // get the lines
    while (fgets(line, MAX_LINE_CHARS, stdin) != NULL) {

        // find the size of this line
        int size = 0;
        while ((line[size] != '\n') && (line[size] != '\0')) {
            // not the end yet
            size = size + 1;
        }

        // now print in reverse
        int j = size - 1;
        while (j >= 0) {
            printf("%c", line[j]);
            j = j - 1;
        }
        printf("\n");
    }

    return 0;
}
