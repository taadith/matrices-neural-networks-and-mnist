#include "matrix.h"
#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

//checks dimensions for matrix operations:
//'operation' value is 0 for addition/subtraction
//'operation' value is 1 for multiplication
int checkDimensions(Matrix* a, Matrix* b, int operation) {
	if (!operation)
		return ((a -> rows) == (b -> rows)) && ((a -> cols) == (b -> cols));
	return (a -> cols == b -> rows);
}
Matrix* add(Matrix *a, Matrix *b) {
	if (checkDimensions(a,b,0)) {
		Matrix *matrixSum = newMatrix(a -> rows, b -> cols);
		for (int i = 0; i < a -> rows; i++) {
			for (int j = 0; j < a -> cols; j++) {
				matrixSum -> entries[i][j] = a -> entries[i][j] + b -> entries[i][j];
			}
		}
		return matrixSum;
	}
	else {
		printf("ERROR:\nDimension mismatch between matrices a (%dx%d) and b (%dx%d)\n\n",a -> rows, a -> cols, b -> rows, b -> cols);
		exit(1);
	}
}

Matrix* subtract(Matrix* a, Matrix* b) {
	if (checkDimensions(a,b,0)) {
		Matrix *matrixDiff = newMatrix(a -> rows, a -> cols);
		for (int i = 0; i < a -> rows; i++) {
			for (int j = 0; j < a -> cols; j++) {
				matrixDiff -> entries[i][j] = a -> entries[i][j] - b -> entries[i][j];
			}
		}
		return matrixDiff;
	} else {
		printf("ERROR:\nDimension mismatch between matrices a (%dx%d) and b (%dx%d)\n\n",a -> rows, a -> cols, b -> rows, b -> cols);
		exit(1);
	}
}


Matrix* multiply(Matrix* a, Matrix *b) {
	if (checkDimensions(a,b,1)) {
		Matrix *matrixProduct = newMatrix(a -> rows, b -> cols);
		fillMatrix(matrixProduct,0);
		for (int m = 0; m < a -> rows; m++) {
			for (int n = 0; n < a -> cols; n++) {
				for (int k = 0; k < b -> cols; k++) {
					matrixProduct -> entries[m][k] += a -> entries[m][n] * b -> entries[n][k];
				}
			}
		}
		return matrixProduct;
	} else {
		printf("ERROR:\nDimension mismatch between matrix a's column value (%d) and matrix b's row value (%d)",a -> cols, b -> rows);
		exit(1);
	}
}

int main() {
	Matrix *m1 = loadMatrix("matrix1-3x2.txt");
	
	Matrix *m2 = loadMatrix("matrix2-2x4.txt");
	
	printMatrix(multiply(m1,m2));
	
	
	freeMatrix(m2);
	freeMatrix(m1);
	return 0; 
}