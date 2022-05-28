#pragma once

typedef struct {
	double **entries;
	int rows;
	int cols;
} Matrix;

//creates a matrix and allocates it on heap
Matrix* newMatrix(int row, int col);

//sets all matrix entries of 'm' to value of 'n'
void fillMatrix(Matrix *m, int n);

//frees up matrix 'm' from heap
void freeMatrix(Matrix *m);

void printMatrix(Matrix *m);

//creates a deep copy of the matrix 'm'
Matrix* copyMatrix(Matrix *m);

//saves the matrix 'm' to a text file 'stringFile'
void saveMatrix(Matrix*m, char* stringFile);

//creates a matrix from a text file 'stringFile'
Matrix* loadMatrix(char* stringFile);

//pulls from a random distribution of min of (-1)/ sqrt(n) and max of 1/sqrt(n)
void randomizeMatrix(Matrix *m, int n);

//expects an M x 1 matrix 'm' and returns the index containing the max value of 'm'
int argMaxOfMatrix(Matrix* m);

//flattens matrix to column vector if 'axis' is 0 OR to the row vector if 'axis' is 1
Matrix* flattenMatrix(Matrix* m, int axis);
