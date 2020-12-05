#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char **argv) {

    FILE *f1 = fopen(argv[1], "r");

    int c = 0;
    int numASCII = 0;
    while ((c = fgetc(f1)) != EOF) {
        if (isascii(c)) {
            numASCII +=1;
        }
    }
    printf("%s contains %d ASCII bytes\n", argv[1], numASCII);
    fclose(f1);
    return 0;
}
