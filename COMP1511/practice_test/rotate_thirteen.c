// Perform the ROT13 algorithm on a string
// Completed by
//  ... (z0000000)
// Completed on 2019-??-??

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256

// Add your own #defines here

void rotate_thirteen(char *string);
char rotate_one(char c);
void rotate_thirteen(char *string);
int strings_equal(char *string1, char *string2);

// Add your own function prototypes here

int main(int argc, char *argv[]) {
    // Example tests
    char test_a[MAX_LENGTH] = "Hello, world!";
    rotate_thirteen(test_a);
    //printf("%s\n", test_a);
    
    assert(strings_equal("Uryyb, jbeyq!", test_a));

    char test_b[MAX_LENGTH] = "abcdefghijklmnopqrstuvwxyz";
    rotate_thirteen(test_b);
    assert(strings_equal("nopqrstuvwxyzabcdefghijklm", test_b));

    char test_c[MAX_LENGTH] = "The quick brown fox jumped over the lazy dog.";
    rotate_thirteen(test_c);
    assert(strings_equal("Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.", test_c));

    // Add your own tests here

    printf("All tests passed. You are awesome!\n");
	
    return 0;
}

void rotate_thirteen(char *string) {
	int k = 0;
	int c = 0;
    while (string[k] != '\0') {
    	if ('A' <= string[k] && string[k] <= 'Z') {
    		c = string[k];
    		c = c - 65;
    		c = c + 13;
    		c = c % 26;
    		c = c + 65;
    		string[k] = c;
    		
    	}
    	else if ('a' <= string[k] && string[k] <= 'z') {
    		c = string[k];
    		c = c - 97;
    		c = c + 13;
    		c = c % 26;
    		c = c + 97;
    		string[k] = c;
    	}
    	k++;
    }
}

char rotate_one(char c) {
    // Use your code from the rotate_one exercise up here
    return 0;
}

int strings_equal(char *string1, char *string2) {
    int i = 0;
    int j = 0;
    
    while (string1[i] != '\0' || string2[j] != '\0') {
		if (string1[i] != string2[j]) {
			return 0;
		}
	   	if (string1[i] == '\0' && string2[j] != '\0') {
			return 0;
		}
		if (string1[i] != '\0' && string2[j] == '\0') {
			return 0;
		}
		
    	i++;
    	j++;
    }
    if (string1[i] == string2[j]) {
		return 1;
	}
	else {
		return 0;
	}
    
}











































