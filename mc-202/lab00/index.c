#include <stdio.h>
#include <stdlib.h>

#define A_FILE "matrizA.txt"
#define B_FILE "matrizB.txt"

#define SUCESS 1
#define ERROR 0;

#define INVALID_DIMENSION -1

// Struct utilizada para representar as dimensões das matrizes no programa
typedef 
	struct {
		int xDim, yDim;
	} Dimensions;

// Lê um número do arquivo de texto
void readIntFile (FILE * file, int * i) {
	fscanf(file, "%d ", i);
}

void printError() {
	printf("As matrizes nao seguem as propriedades necessarias para realizar a multiplicacao.");
}

// Faz a alocação dinâmica de uma matriz passada por parâmetro, dada suas dimensões
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

// Lê uma matriz do arquivo de entrada, de acordo com o nome passado por parâmetro
Dimensions readMatrixFromFile (char fileName[], int *** matrix) {
	FILE * file;
	Dimensions dim;
	int i, j;

	file = fopen(fileName, "r");
	if (file == NULL) {
		printError();
		return dim;
	}

	// Lê as dimensões da primeira linha
	readIntFile(file, &dim.xDim);
	readIntFile(file, &dim.yDim);

	allocateMatrix(matrix, dim);

	// Repete o processo de leitura para as dimensões da matriz
	for (i = 0; i < dim.xDim; i++) {
		for (j = 0; j < dim.yDim; j++) {
			readIntFile(file, &(*matrix)[i][j]);
		}
	}

	fclose(file);
	return dim;
}

/* Retorna as dimensões da matriz do resultado da multiplicação entre elas, e retorna
 * a dimensão x do resultado com valor inválido (-1) caso não haja como multiplicar as 
 * matrizes em questão
 */
Dimensions getResultDimensions(Dimensions a, Dimensions b) {
	Dimensions result;
	result.xDim = INVALID_DIMENSION;

	if (a.yDim == b.xDim) {
		result.xDim = a.xDim;
		result.yDim = b.yDim;
	} else 	if (a.xDim == b.yDim) {
		result.xDim = b.xDim;
		result.yDim = a.yDim;
	}

	return result;
}

// Valida se as dimensões são possível de ser multiplicadas e printa a resposta 
// caso não seja possível
char validMatrixDimensions (Dimensions result) {
	if (result.xDim == INVALID_DIMENSION) {
		printError();
		return ERROR;
	}

	return SUCESS;
}

// Libera a alocação da matriz em questão
void freeMatrix (int *** matrix, int y) {
	for (int i = 0; i < y; i++) {
		free((*matrix)[i]);
	}

	free(*matrix);
}

// Multiplica a matriz 
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

/* Printa o resultado no formato :
 * Primeira linha com as dimensões m e n
 * Printa m linhas de n números contento o resultado
 * da multiplicação das matrizes de entrada
*/

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
	dimResult = getResultDimensions(dimA, dimB);

	if (validMatrixDimensions(dimResult)) {
		allocateMatrix(&result, dimResult);

		multiplyMatrix(matrixA, dimA, matrixB, dimB, &result, dimResult);
		printResult(&result, dimResult);

		freeMatrix(&result, dimResult.xDim);
	}

	freeMatrix(&matrixA, dimA.xDim);
	freeMatrix(&matrixB, dimB.xDim);

	return 0;
}
