
#include "tracker.h"

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
	int result;

	Board * board = readMatrixEntry();

	print(board);

	result = checkBoardSolution(board);

	printResult(result);

	freeBoard(board);

	return 0;
}