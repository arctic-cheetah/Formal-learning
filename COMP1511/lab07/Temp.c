#include <stdio.h>

int main(int argc, char *argv[]) {
	int i = 0;
	printf("Well actually %s says there's no such thing as ", argv[0]);
	
	while (i < argc){
		fputs(argv[i], stdout);
		printf(" ");
		i++;
	}
	printf("\n");
	
}
