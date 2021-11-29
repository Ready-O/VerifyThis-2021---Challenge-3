#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evencmp (const void * a, const void * b) {
	return ( *(int*)a > *(int*)b );
}

int oddcmp (const void *a, const void *b) {
	return ( *(int*)a < *(int*)b );
}

void even_sort(int *row, int row_length)
{
	qsort(row, row_length, sizeof(int), evencmp);
}

void odd_sort(int *row, int row_length)
{
	qsort(row, row_length, sizeof(int), oddcmp);
}

void print_matrix(int **matrix, int n_rows, int n_cols)
{
	printf("-------------------\n");
	for(int i = 0; i < n_rows; i++) {
		for(int j = 0; j < n_cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("-------------------\n");
}

void matrixcpy(int **m1, int **m2, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m1[i][j] = m2[i][j];
		}
	}
}

void snake_step(int **matrix, int N) {
	for(int i = 0; i < N; i++) {
		if(i % 2 == 0) even_sort(matrix[i], N);
		else odd_sort(matrix[i], N);
	}
}

void colsort_step(int **matrix, int N) {
	int tmp;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			for (int k = i+1; k < N; k++) {
				if (matrix[i][j] > matrix[k][j]) {
					tmp = matrix[i][j];
					matrix[i][j] = matrix[k][j];
					matrix[k][j] = tmp;
				}
			}
		}
	}
}

int is_sorted(int **m1, int **m2, int N1, int N2) {
	if(N1 != N2) return 0;
	for(int i = 0; i < N1; i++) {
		for(int j = 0; j < N1; j++) {
			if(m1[i][j] != m2[i][j]) return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	int N = 3;
	
	int **matrix;
	int **previous_step_matrix;

	matrix = malloc(N * sizeof(int*));
        for(int i = 0; i < N; i++) { 
                matrix[i] = malloc(N * sizeof(int));
        }

	previous_step_matrix = malloc(N * sizeof(int*));
        for(int i = 0; i < N; i++) {
                previous_step_matrix[i] = malloc(N * sizeof(int));
		for (int j = 0; j < N; j++) {
			previous_step_matrix[i][j] = 0;
		}
        }

	matrix[0][0] = 7;
	matrix[0][1] = 5;
	matrix[0][2] = 2;
	matrix[1][0] = 1;
	matrix[1][1] = 3;
	matrix[1][2] = 9;
	matrix[2][0] = 8;
	matrix[2][1] = 4;
	matrix[2][2] = 6;

	print_matrix(matrix, N, N);

	int i = 0;
	while (!is_sorted(matrix, previous_step_matrix, N, N)) {
		matrixcpy(previous_step_matrix, matrix, N);
		if(i % 2 == 0) snake_step(matrix, N);
		else colsort_step(matrix, N);
		i++;
	}

	print_matrix(matrix, N, N);

	return 0;
}
