/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "paintor.h"

/* Implementação dos métodos */

// TODO check if all numbers and colors match

int blueCounter (Doll ** doll) {
	int counter = 0;
	Node * actual = (*doll)->innerDolls->first;
	Doll * inner;

	for (; actual != NULL; actual = actual->next) {
		inner = (Doll*) actual->value;
		if (inner->color == BLUE) {
			counter++;
		}
	}

	return counter;
}

void defineColorForDolls (Doll ** doll) {
	if (doll == NULL) {
		return;
	}

	if ((*doll) == NULL) {
		return;
	}

	if (blank(&(*doll)->innerDolls)) {
		(*doll)->color = getColor((*doll)->number, 0);
		return;
	}

	// TODO get color from the inner Dolls
	defineColorForInnerDolls(doll);
}

void defineColorForInnerDolls (Doll ** doll) {
	Node * actual = (*doll)->innerDolls->first;
	Doll * inner;

	for (; actual != NULL; actual = actual->next) {
		inner = (Doll*) actual->value;
		defineColorForDolls(&inner);
	}

	(*doll)->color = getColor((*doll)->number, blueCounter(doll));
}

Color getColor (int m, int n) {
	int sum = m + n;

	if (sum % 2 == 0) {
		return BLUE;
	}

	return RED;
}

// TODO Delete
void printDolls (Doll * doll) {
	printf("\n\nNumber: %d Color: %d", doll->number, doll->color);
	Doll * a = (Doll*) doll->innerDolls->first->value;
	printf("\n\nNumber: %d Color: %d", a->number, a->color);
	Doll * b = (Doll*) a->innerDolls->first->next->value;
	printf("\n\nNumber: %d Color: %d", b->number, b->color);
}