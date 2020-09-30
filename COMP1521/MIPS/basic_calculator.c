//A C program that implements a basic calculator which does subtraction,
//multiplication and addition

#include <stdio.h>

int main () {
    int i = 0;
    int j = 0;
    char myChar;
    printf("Enter the first number: ");
    scanf("%d", &i);

    printf("Enter an operation: ");
    scanf(" %c", &myChar);

    printf("Enter the second number: ");
    scanf("%d", &j);
    if (myChar == '+') {
        printf("%d + %d = %d ",i, j, i + j);
    }
    if (myChar == '-') {
        printf("%d - %d = %d ",i, j, i - j);
    }
    if (myChar == '*') {
        printf("%d * %d = %d ",i, j, i * j);
    }
    //Will need to implement a an int to float conversion
    if (myChar == '/') {
        double myNum = (double) i / (double) j;
        printf("%d / %d = %lf ",i, j, myNum);
    }
    printf("\n");
}
