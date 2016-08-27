#include <stdio.h>
#include <stdlib.h>

#define A_FILE "matrizA.txt"
#define B_FILE "matrizB.txt"

#define SUCESS 1
#define ERROR 0;
#define ERROR_MSG "As matrizes nao seguem as propriedades necessarias para realizar a multiplicacao."

typedef 
	struct {
		int xDim, yDim;
	} Dimensions;

void readIntFile(FILE * file, int * i) {
	fscanf(file, "%d ", i);
} 

void allocateMatrix(int *** matrix, Dimensions dim) {
	int i;

	*matrix = malloc(sizeof(int*) * dim.xDim);
	for (i = 0; i < dim.xDim; i++) {
		(*matrix)[i] = malloc(sizeof(int) * dim.yDim);
	}
}

Dimensions readMatrixFromFile(char fileName[], int *** matrix) {
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
			printf("%d ", (*matrix)[i][j]);
		}

		printf("\n");
	}

	fclose(file);
	printf("End of %s \n", fileName);
	return dim;
}

char validMatrixDimensions(Dimensions a, Dimensions b) {
	if (a.xDim != b.yDim) {
		printf(ERROR_MSG);
		return ERROR;
	}

	return SUCESS;
}

void freeMatrix(int *** matrix, int y) {
	for (int i = 0; i < y; i++) {
		free((*matrix)[i]);
	}

	free(*matrix);
}

int main() {
	int ** matrixA = NULL,
		** matrixB = NULL,
		** result = NULL;

	Dimensions dimA, dimB, dimResult;

	dimA = readMatrixFromFile(A_FILE, &matrixA);
	dimB = readMatrixFromFile(B_FILE, &matrixB);

	if (validMatrixDimensions(dimA, dimB)) {
		dimResult.xDim = dimA.yDim;
		dimResult.yDim = dimB.xDim;
		
		allocateMatrix(&result, dimResult);
		freeMatrix(&result, dimResult.xDim);
	}

	freeMatrix(&matrixA, dimA.xDim);
	freeMatrix(&matrixB, dimB.xDim);

	return 0;
}
