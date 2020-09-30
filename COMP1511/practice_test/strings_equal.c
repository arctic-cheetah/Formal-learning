// String Equality
// Created by
//  ... (z0000000)
// Created on 2019-??-??

#include <stdio.h>
#include <assert.h>

int strings_equal(char *string1, char *string2);

int main(int argc, char *argv[]) {

    // Some simple assert-based tests.
    // You probably want to write some more.
    assert(strings_equal("", "") == 1);
    assert(strings_equal(" ", "") == 0);
    assert(strings_equal("", " ") == 0);
    assert(strings_equal(" ", " ") == 1);
    assert(strings_equal("\n", "\n") == 1);
    assert(strings_equal("This is 17 bytes.", "") == 0);
    assert(strings_equal("", "This is 17 bytes.") == 0);
    assert(strings_equal("This is 17 bytes.", "This is 17 bytes.") == 1);
    assert(strings_equal("Here are 18 bytes!", "This is 17 bytes.") == 0);
    assert(strings_equal("hello", "hell") == 0);
    printf("All tests passed.  You are awesome!\n");

    return 0;
}


// Takes two strings, and if they are the same,
// returns 1, or 0 otherwise.
int strings_equal(char *string1, char *string2) {
    int k = 0;
    int j = 0;
    //Consider if first characters are unequal
    
    while (string1[k] != '\0' || string2[j] != '\0') {
    	if (string1[k] != string2[j]) {
    		return 0;
    	}
 		if (string1[k] != '\0' && string2[j] == '\0') {
			return 0;
		}
		if (string1[k] == '\0' && string2[j] != '\0') {
			return 0;
		}
    	j++;
    	k++;
    }
    //Consider if either of strings have ended early
    
    if (string1[k] == string2[j]) {
		return 1;
	}
	else {
		return 0;
	}
	
}
















































