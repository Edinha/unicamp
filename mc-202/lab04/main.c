
#include "tracker.h"

int main() {
	int result;

	Board * board = readMatrixEntry();

	result = checkBoardSolution(board);

	printResult(result);

	freeBoard(board);

	return 0;
}