#include <stdio.h>
#include <stdlib.h>

#define A_FILE "matrizA.txt"
#define B_FILE "matrizB.txt"

#define SUCESS 1
#define ERROR 0;

typedef 
	struct {
		int xDim, yDim;
	} Dimensions;

void readIntFile (FILE * file, int * i) {
	fscanf(file, "%d ", i);
} 

void allocateMatrix (int *** matrix, Dimensions dim) {
	int i, j;

	*matrix = malloc(sizeof(int*) * dim.xDim);
	for (i = 0; i < dim.xDim; i++) {
		(*matrix)[i] = malloc(sizeof(int) * dim.yDim);
		for (j = 0; j < dim.yDim; j++) {
			(*matrix)[i][j] = 0;
		}
	}
}

Dimensions readMatrixFromFile (char fileName[], int *** matrix) {
	FILE * file;
	int i, j;
	Dimensions dim;

	file = fopen(fileName, "r");

	readIntFile(file, &dim.xDim);
	readIntFile(file, &dim.yDim);

	allocateMatrix(matrix, dim);

	for (i = 0; i < dim.xDim; i++) {
		for (j = 0; j < dim.yDim; j++) {
			readIntFile(file, &(*matrix)[i][j]);
		}
	}

	fclose(file);
	return dim;
}

char validMatrixDimensions (Dimensions a, Dimensions b) {
	if (a.yDim != b.xDim) {
		printf("As matrizes nao seguem as propriedades necessarias para realizar a multiplicacao.");
		return ERROR;
	}

	return SUCESS;
}

void freeMatrix (int *** matrix, int y) {
	for (int i = 0; i < y; i++) {
		free((*matrix)[i]);
	}

	free(*matrix);
}

void multiplyMatrix (int ** matrixA, Dimensions dimA, int ** matrixB, Dimensions dimB, int *** result, Dimensions dimResult) {
	int i, j, row;

	for (row = 0; row < dimResult.xDim; row++) {
		for (i = 0; i < dimB.yDim; i++) {
			for (j = 0; j < dimA.yDim; j++) {
				(*result)[row][i] += matrixA[row][j] * matrixB[j][i];
			}
		}
	}
}

void printResult (int *** result, Dimensions dimResult) {
	int i,j;

	printf("%d %d\n", dimResult.xDim, dimResult.yDim);
	for (i = 0; i < dimResult.xDim; i++) {
		for (j = 0; j < dimResult.yDim; j++) {
			printf("%d ", (*result)[i][j]);
		}

		printf("\n");
	}
}

int main() {
	int ** matrixA = NULL,
		** matrixB = NULL,
		** result = NULL;

	Dimensions dimA, dimB, dimResult;

	dimA = readMatrixFromFile(A_FILE, &matrixA);
	dimB = readMatrixFromFile(B_FILE, &matrixB);

	if (validMatrixDimensions(dimA, dimB)) {
		dimResult.xDim = dimA.xDim;
		dimResult.yDim = dimB.yDim;
		
		allocateMatrix(&result, dimResult);

		multiplyMatrix(matrixA, dimA, matrixB, dimB, &result, dimResult);
		printResult(&result, dimResult);

		freeMatrix(&result, dimResult.xDim);
	}

	freeMatrix(&matrixA, dimA.xDim);
	freeMatrix(&matrixB, dimB.xDim);

	return 0;
}
