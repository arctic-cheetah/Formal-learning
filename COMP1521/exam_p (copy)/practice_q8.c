#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

//Functions that check the type of encoding for UTF8 the first byte
int isTwoByteUTF (int c) {
    return (c >> 5) == 0x6;
}

int isThreeByteUTF (int c) {
    return (c >> 4) == 14;
}
int isFourByteUTF (int c) {
    return (c >> 3) == 0x1E;
}

int isByteGood (int c) {
    return (c >> 6) == 2;
}



int main (int argc, char **argv) {

    FILE *f1 = fopen(argv[1], "r");

    int UTF8count = 0;
    int c = 0;
    int isPrematureEOF = 0;
    int wrongUTF = 0;

    //Cases:
    //Reached EOF and successfully reads all UTF8 chars

    //Reads an incorrect UT8 char

    //UTF8 char is read, but ends prematurely due to EOF
    
    while ((c = fgetc(f1)) != EOF) {
        //Check if the first byte is UTF
        if (!(c >> 7)) {
            UTF8count +=1;
        }
        else if (isTwoByteUTF(c)) {
            c = fgetc(f1);
            //Check for EOF
            if (c == EOF) {
                isPrematureEOF = 1;
                break;
            }
            //invalid byte
            if (isByteGood(c) == 0) {
                wrongUTF = 1;
                break;
            }
            //Good byte
            UTF8count +=1;
        }
        else if (isThreeByteUTF(c)) {
            //Check each byte
            //invalid byte
            c = fgetc(f1);
            //Check for EOF
            if (c == EOF) {
                isPrematureEOF = 1;
                break;
            }
            //invalid byte
            if (isByteGood(c) == 0) {
                wrongUTF = 1;
                break;
            }
            ///Check the second byte
            c = fgetc(f1);
            if (c == EOF) {
                isPrematureEOF = 1;
                break;
            }
            if (isByteGood(c) == 0) {
                wrongUTF = 1;
                break;
            }
            //Good byte
            UTF8count +=1;
        }
        else if (isFourByteUTF(c)) {
            ///Check the first byte
            c = fgetc(f1);
            if (c == EOF) {
                isPrematureEOF = 1;
                break;
            }
            if (isByteGood(c) == 0) {
                wrongUTF = 1;
                break;
            }
            ///Check the second byte
            c = fgetc(f1);
            if (c == EOF) {
                isPrematureEOF = 1;
                break;
            }
            if (isByteGood(c) == 0) {
                wrongUTF = 1;
                break;
            }
            //Check the third byte
            c = fgetc(f1);
            if (c == EOF) {
                isPrematureEOF = 1;
                break;
            }
            if (isByteGood(c) == 0) {
                wrongUTF = 1;
                break;
            }
            //Good byte
            UTF8count +=1;
        }

    }

    if (isPrematureEOF || wrongUTF) {
        printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n", argv[1], UTF8count);
    }
    else {
        printf("%s: %d UTF-8 characters\n", argv[1], UTF8count);
    }
    return 0;
}
