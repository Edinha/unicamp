/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementação dos métodos */

void doSomeRecursion(Image * image, List ** possibilities, Position actual, int count) {

	if (!isValidPosition(&actual, image)) {
		return;
	}

	if (isWhitePosition(&actual, image)) {
		insert(possibilities, count);
		return;
	}

	Position adjacency;


	// TODO do logic for all 4 adjacencies, maybe function pointers should do it here ...
	int colorChange = SAME_COLOR;
	adjacency = up(actual);

	if (color(image, adjacency) != color(image, actual)) {
		colorChange = DIFFERENT_COLOR;
	}

	doSomeRecursion(image, possibilities, adjacency, count + colorChange);

}

int minimumWay(Image * image) {
	// TODO make all the shit happen in here
	return 0;
}