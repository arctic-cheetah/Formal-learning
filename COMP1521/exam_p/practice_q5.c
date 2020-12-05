#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv) {
    char *v1 = getenv(argv[1]);
    char *v2 = getenv(argv[2]);

    if (v1 == NULL || v2 == NULL) {
        printf("0\n");
    }
    else if (strcmp(v1, v2) == 0) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
    
    return 0;
}
