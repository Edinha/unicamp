/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tracker.h"

int main() {
	int result;

	Board * board = readMatrixEntry();

	result = checkBoardSolution(board);

	printResult(result);

	freeBoard(board);

	return 0;
}