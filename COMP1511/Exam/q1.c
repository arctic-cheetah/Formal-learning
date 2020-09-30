#include <stdio.h>
#include <stdlib.h>


# define TEST_ARRAY_SIZE 9

int mixed(int length, int array[]);

// This is a simple main function which could be used
// to test your mixed function.
// It will not be marked.
// Only your mixed function will be marked.


int main(void) {
    int test_array[TEST_ARRAY_SIZE] = {16, 12, 8, 3, 6, 12};

    int result = mixed(TEST_ARRAY_SIZE, test_array);
    printf("%d\n", result);

    return 0;
}


// mixed should return 1 if array contains both even and odd numbers
// mixed should return 0 otherwise
int mixed(int length, int array[]) {
    int k = 0;
    int odd = 0;
    int even = 0;
    //Case if array is of size 1
    if (length == 1) {
    	return 0;
    }
    while (k < length) {
    	if (array[k] % 2 == 0) {
    		even = 1;
    	}
    	else {
    		odd = 1;
    	}
    	k++;
    }
    //Check if odd and even are true
    if (odd == 1 && even == 1) {
    	return 1;
    }
    else {
    	return 0;
    }
}


































