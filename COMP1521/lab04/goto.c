#include <stdio.h>
//aaron
int main(void) {
    int x;
    int y;
    printf("Enter a number: ");
    scanf("%d", &x);

    branch:
        if (x > 46340) goto else1;
        y = x * x;
        printf("%d\n", y);
        goto end;
    else1:
        printf("square too big for 32 bits\n");
    end:

    return 0;
}
