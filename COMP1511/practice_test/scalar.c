#include <stdio.h>

#define MAX_ROW 3
#define MAX_COL 3

void scalar_multiply(int rows, int columns, int matrix[rows][columns],  int scalar);
void print_array(int rows, int columns, int matrix[rows][columns]);



int main () {
	int scalar = 5;
	int matrix[MAX_ROW][MAX_COL] ={ {1, 1, 1}, 
									{1, 1, 1},
	 								{1, 1, 1} };
	scalar_multiply(MAX_ROW, MAX_COL, matrix, scalar);
	print_array(MAX_ROW, MAX_COL, matrix);
}

void scalar_multiply(int rows, int columns, int matrix[rows][columns],  int scalar) {
	for (int k = 0; k < rows; k++) {
		for (int j = 0; j < columns; j++) {
			matrix[k][j] = matrix[k][j] * scalar;
		}
	
	}
}

void print_array(int rows, int columns, int matrix[rows][columns]) {
	for (int k = 0; k < rows; k++) {
		for (int j = 0; j < columns; j++) {
			printf("%d ", matrix[k][j]);
		}
		printf("\n");
	}
	
}
































