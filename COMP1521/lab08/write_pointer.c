#include <stdio.h>

int main(void) {
    int array[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    int *p = &array[5];

    FILE *f = fopen("array.save", "w");
    if (f == NULL) {
        perror("array.save");
        return 1;
    }

    if (fwrite(array, 1, sizeof array, f) != sizeof array) {
        perror("array.save");
        return 1;
    }

    if (fwrite(&p, 1, sizeof p, f) != sizeof p) {
        perror("array.save");
        return 1;
    }

    fclose(f);

    printf("p         = %p\n", p);
    printf("&array[5] = %p\n", &array[5]);
    printf("array[5]  = %d\n", array[5]);
    printf("*p        = %d\n", *p);
    return 0;
}
