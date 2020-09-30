// A demo of using command line arguments
// This program will start an argument with you
// It will take whatever you say and refuse to agree

// Marc Chee (cs1511@cse.unsw.edu.au)
// Edited March 2020

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 1;
    printf("Well actually %s says there's no such thing as ", argv[0]);
    while (i < argc) { // have written i - 1 words from argv to stdout
        fputs(argv[i], stdout);
        printf(" ");
        i++;
    }
    printf("%d \n %d \n", i, argc);
    //printf("\n");
    return 0;
}
