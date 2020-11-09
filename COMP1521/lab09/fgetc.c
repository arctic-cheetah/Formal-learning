#include <stdio.h>

int main () {
	int c;
	while ((c = fgetc(stdin)) != EOF) {
		fputc(c, stdout);
	}
}
