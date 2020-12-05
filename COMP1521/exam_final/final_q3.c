#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getEndPtr (char *environ) {
    while (*environ != 0) {
        environ +=1;
    }
    return environ;
}

int main (int argc, char **argv) {
    char *e1 = getenv(argv[1]);
    char *e2 = getenv(argv[2]);

    int len1 = 0;
    int len2 = 0;
    //Check if env is NULL
    if (e1 == NULL && e2 != NULL) {
        len1 = 42;
        len2 = strtol(e2, NULL, 10);
    }
    else if (e2 == NULL && e1 != NULL) {
        len1 = strtol(e1, NULL, 10);
        len2 = 42;
    }
    else if (e1 == NULL && e2 == NULL) {
        printf("1\n");
        return 0;
    }
    else {
        len1 = strtol(e1, NULL, 10);
        len2 = strtol(e2, NULL, 10);
    }

    int diff = len1 - len2;

    if (-10 < diff && diff < 10) {
        printf("1\n");
        return 0;
    }
    else {
        printf("0\n");
        return 0;
    }

    return 0;
}
