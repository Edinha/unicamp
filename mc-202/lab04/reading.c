/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readInt(int * i) {
	scanf("%d ", i);
}

void readChar(char * c) {
	scanf(" %c", c);
}

void readArray(char * letters, int size) {
	int i = 0;
	for (; i < size; i++) {
		readChar(&letters[i]);
	}
}

Board* readMatrixEntry() {
	int i;
	Board * board = malloc(sizeof(Board));

	readInt(&board->size);

	board->matrix = malloc(board->size * sizeof(char*));

	for (i = 0; i < board->size; i++) {
		board->matrix[i] = malloc(board->size * sizeof(char));
		readArray(board->matrix[i], board->size);
	}

	return board;
}

void freeBoard(Board * board) {
	int i;
	for (i = 0; i < board->size; i++) {
		free(board->matrix[i]);
		board->matrix[i] = NULL;
	}

	free(board->matrix);
	board->matrix = NULL;
	free(board);
	board = NULL;
}