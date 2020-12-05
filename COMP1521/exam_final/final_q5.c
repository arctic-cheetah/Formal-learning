#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (int argc, char **argv) {
    int n = strtol(argv[1], NULL, 10);

    FILE *f1 = fopen(argv[2], "r");
    //Get the file size
    fseek(f1, 0, SEEK_END);
    int FileSize = ftell(f1);
    fseek(f1, 0, SEEK_SET);

    FILE *copyFile = fopen(argv[3], "w");

    //Get the limit to copy
    int limit = FileSize - n;
    if (limit > 0) {
        int c = 0;
        int i = 0;
        while ((c = fgetc(f1)) != EOF && i < limit) {
            fputc(c, copyFile);
            i +=1;
        }
    }
    //Copy nothing if the limit is negative
    fclose(copyFile);
    fclose(f1);
}
