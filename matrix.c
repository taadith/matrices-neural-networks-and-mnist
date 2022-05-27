#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

//creates a matrix and allocates it on heap
Matrix* createMatrix(int row, int col) {
	//initializing matrix and allocating on heap
	Matrix *matrix = malloc(sizeof(Matrix));
	
	//defining rows and cols of matrix
	matrix -> rows = row;
	matrix -> cols = col;
	
	//initializing and allocating matrix's rows on heap 
	matrix -> entries = malloc(row * sizeof(double*));
	
	//initializing and allocating matrix's cols on heap
	for (int i = 0; i < row; i++) {
		matrix -> entries[i] = malloc(col * sizeof(double));
	}
	
	return matrix;
}

//sets all matrix entries of 'm' to value of 'n'
void fillMatrix(Matrix *m, int n) {
	for (int i = 0; i < (m -> rows); i++) {
		for (int j = 0; j < (m -> cols); j++) {
			m -> entries[i][j] = n;
		}
	}
}

//frees up matrix 'm' from heap
void freeMatrix(Matrix *m) {
	for (int i = 0; i < (m -> rows); i++) {
		free(m -> entries[i]);
	}
	free(m);
	m = NULL;
}

void printMatrix(Matrix *m) {
	printf("Rows: %d, Columns: %d\n", m -> rows, m -> cols);
	for (int i = 0; i < m -> rows; i++) {
		for (int j = 0; j < m -> cols; j++) {
			printf("%1.3f ", m -> entries[i][j]);
		}
		printf("\n\n");
	}
}

//creates a deep copy of the matrix 'm'
Matrix * copyMatrix(Matrix* m) {
	Matrix* mat = createMatrix(m -> rows, m -> cols);
	
	for (int i = 0; i < m-> rows; i++ ) {
		for (int j = 0; i < m -> cols; j++) {
			mat -> entries[i][j] = m -> entries[i][j];
		}
	}
	
	return mat;
}

//saves the matrix 'm' to a text file 'stringFile'
void saveMatrix(Matrix *m, char* stringFile) {
	FILE* file = fopen(stringFile, "w");
	fprintf(file, "%d\n", m -> rows);
	fprintf(file, "%d\n", m -> cols);
	
	for (int i = 0; i < m -> rows; i++) {
		for (int j = 0; j < m -> cols; j++) {
			fprintf(file, "%.6f\n", m -> entries[i][j]);
		}
	}
	
	printf("Successfully saved matrix to %s\n\n", stringFile);
	fclose(file);
}

//creates a matrix from a text file 'stringFile'
Matrix* loadMatrix(char* stringFile) {
	FILE* file = fopen(stringFile, "r");
	
	char entry[MAXCHAR];
	
	fgets(entry, MAXCHAR, file);
	int rows = atoi(entry);
	
	fgets(entry, MAXCHAR, file);
	int cols = atoi(entry);
	
	Matrix *m = createMatrix(rows,cols);
	for (int i = 0; i < m -> rows; i++) {
		for (int j = 0; j < m -> cols; j++) {
			fgets(entry, MAXCHAR, file);
			m -> entries[i][j] = strtod(entry,NULL);
		}
	}
	
	printf("Successfully loaded matrix from %s\n\n", stringFile);
	fclose(file);
	
	return m;
}

double uniformDistribution(double low, double high) {
	double diff = high - low;
	int scale = 10000;
	int scaledDiff = (int) (diff*scale);
	return low + (1.0 * (rand() % scaledDiff) / scale);
}

//pulls from a random distribution of min of (-1)/ sqrt(n) and max of 1/sqrt(n)
void randomizeMatrix(Matrix *m, int n) {
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	
	for (int i = 0; i < m -> rows; i++) {
		for (int j = 0; j < m -> cols; j++) {
			m -> entries[i][j] = uniformDistribution(min,max);
		}
	}
	
}

//expects an M x 1 matrix 'm' and returns the index containing the max value of 'm'
int argMaxOfMatrix(Matrix* m) {
	double maxScore = 0;
	int maxIndex = 0;
	for (int i = 0; i < m -> rows; i++) {
		if (m -> entries[i][0] > maxScore) {
			maxScore = m -> entries[i][0];
			maxIndex = i;
		}
	}
	
	return maxIndex;
}

int main() { 
	Matrix *m = createMatrix(2,2);
	fillMatrix(m,1);
	printMatrix(m);
	
	saveMatrix(m,"matrix_example.txt");
	Matrix *m1 = loadMatrix("matrix_example.txt");
	printMatrix(m1);
	
	remove("matrix_example.txt");
	
	freeMatrix(m);
	freeMatrix(m1);
	
	return 0; 
}

