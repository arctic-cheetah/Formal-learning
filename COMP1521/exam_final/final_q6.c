#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

    FILE *f1 = fopen(argv[1], "r");

    int bitSetOne = 0;
    int c = 0;
    while ((c = fgetc(f1)) != EOF) {
        //Check for bits set to 1
        for (int i = 0; i < 8; i +=1) {
            if ((c >> i) & 1) {
                bitSetOne +=1;
            }
        }
    }

    printf("%s has %d bits set\n", argv[1], bitSetOne);
    fclose(f1);
}
