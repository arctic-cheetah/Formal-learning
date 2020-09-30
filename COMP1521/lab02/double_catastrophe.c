#include <stdio.h>
#include <math.h>

int main(void) {

    long double x = 0.000000011;
    long double y = (1 - cosl(x)) / (x * x);

    // correct answer y = ~0.5
    // prints y = 0.917540
    printf("y = %Lf\n", y);

    // division of similar approximate value
    // produces large error
    // sometimes called catastrophic cancellation
    printf("%Lg\n", 1 - cosl(x)); // prints  1.11022e-16
    printf("%Lg\n", x * x); // prints 1.21e-16
    return 0;
}
