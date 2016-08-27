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

void allocateMatrix(int ** matrix, Dimensions dim) {
    int i;
    
    matrix = malloc(sizeof(int*) * dim.xDim);
    
    for (i = 0; i < dim.yDim; i++) {
        matrix[i] = malloc(sizeof(int) * dim.yDim);
    }
}

Dimensions readMatrixFromFile(char fileName[], int ** matrix) {
    FILE * file;
    int i, j;
    Dimensions dim;

    file = fopen(fileName, "r");

    readIntFile(file, &dim.xDim);
    readIntFile(file, &dim.yDim);

    allocateMatrix(matrix, dim);

    for (i = 0; i < dim.xDim; i++) {
        for (j = 0; j < dim.yDim; j++) {
            readIntFile(file, &matrix[i][j]);
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }

    fclose(file);

    return dim;
}

char validMatrixDimensions(Dimensions a, Dimensions b) {
    if (a.xDim != b.yDim) {
        printf(ERROR_MSG);
        return ERROR;
    }

    return SUCESS;
}


/*void multiplyMatrix(int * matrixA, Dimensions dimA, int * matrixB, Dimensions dimB, int * result) {
        // TODO magic
    for (i = 0; i < dim.xDim; i++) {
        for (j = 0; j < dim.yDim; j++) {
        }
    }

}*/

void freeMatrix(int ** matrix, int y) {
    for (; y >= 0; y--) {
        free(matrix[y]);
    }

    free(matrix);
}

int main() {
    int ** matrixA,
        ** matrixB,
        ** result;

    Dimensions dimA, 
               dimB,
               dimResult;

    dimA = readMatrixFromFile(A_FILE, matrixA);
    dimB = readMatrixFromFile(B_FILE, matrixB);

    if (validMatrixDimensions(dimA, dimB)) {
        dimResult.xDim = dimA.yDim;
        dimResult.yDim = dimB.xDim;
        allocateMatrix(result, dimResult);
        //multiplyMatrix(matrixA, dimA, matrixB, dimB, result);
        
        freeMatrix(result, dimResult.yDim);
    }

    freeMatrix(matrixA, dimA.yDim);
    freeMatrix(matrixB, dimB.yDim);
        
    return 0;
}
