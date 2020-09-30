// copy all of the values in source1 which are also found in source2 into destination
// return the number of elements copied into destination

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1023

int common_elements(int length, int source1[length], int source2[length], int destination[length]);

int main () {
	int length = 6;
	printf("Enter the length of the array: ");
	while (scanf("%d", &length) != EOF ) {
		int array1[MAX_LENGTH];
		int array2[MAX_LENGTH];
		int destination[length];
		printf("Enter %d values for the first array\n", length);
		for (int i = 0; i < length; i++) {
			scanf("%d", &array1[i]);
		}
		printf("Enter %d values for the second array\n", length);
		for (int i = 0; i < length; i++) {
			scanf("%d", &array2[i]);
		}
		
		//while ()
		
		int lengthDestination = common_elements(length, array1, array2, destination);
		printf("There are %d common elements, they are: ", lengthDestination);
		for (int i = 0; i < lengthDestination; i++) {
			printf("%d ", destination[i]);
		}
		printf("\n");
	}
	
	
}

//Takes in two arrays and finds the common elements between those two arrays
//and returns an array with the common elements
int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    
    int sameCount = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (source1[i] == source2[j]) {
				destination[sameCount] = source1[i]; 
				sameCount++;
				break;
			}
		
		}
	
	}
    
    return sameCount;
}

// You may optionally add a main function to test your common_elements function.
// It will not be marked.
// Only your common_elements function will be marked.



































































