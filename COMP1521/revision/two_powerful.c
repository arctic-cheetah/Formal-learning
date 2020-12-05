#include <stdio.h>

void two(int i, int upperBound);

int main(void) {
    printf("Enter a size: ");
    int upperBound = 0;
    scanf("%d", &upperBound);
    two(1, upperBound);
}

void two(int i, int upperBound) {
    if (i < upperBound) {
        two(2 * i, upperBound);
    }
    printf("%d\n", i);
}
