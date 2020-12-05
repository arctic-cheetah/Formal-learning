#include <stdio.h>
#include <stdlib.h>

int *array (void) {
    int size = 0;
    scanf("%d", &size);
    return (int *)calloc(size, sizeof(int));
}

int main () {
    printf("Enter the size of the array: ");
    int *numbers = array();
    printf("Success\n");
    free(numbers);
    return 0;
}
