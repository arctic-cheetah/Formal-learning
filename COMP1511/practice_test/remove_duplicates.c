#include <stdio.h>
#include <string.h>

int remove_duplicates (int length, int source[length], int destination[length]);


int main () {
	int length = 6;
	int source[] = {1, 2, 5, 5, 5, 5};
	int destination[length];
	int duplicates = remove_duplicates (length, source, destination);
	
	for (int i = 0; i < duplicates; i++) {
		printf("%d", destination[i]);
	}
	printf("\n");
	
	printf("The number of duplicates are: %d\n", duplicates);
	
	return 0;
}


int remove_duplicates (int length, int source[length], int destination[]) {
	int duplicate = 0;
	int numCount = 0;
	int i = 0;
	while (i < length) {	
		int j = 0;
		while (destination[j] != '\0') {
			if (source[i] == destination[j]) {
				duplicate++;
				break;
			}
			j++;
		}
		if (source[i] != destination[j]) {
			destination[numCount] = source[i];
			numCount++;
		}
		i++;
	}
	
	return duplicate;
}





































