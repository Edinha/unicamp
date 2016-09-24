
#include "reading.h"

// TODO DELETE
void print(Board * board) {
    printf("%d\n", board->size);
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) { 
            printf("%c", board->matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {

    Board * board = readMatrixEntry();

    print(board);

    freeBoard(board);

    return 0;
}