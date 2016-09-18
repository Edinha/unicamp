/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "paintor.h"

/* Implementação dos métodos */

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

int defineColorForDolls (Doll ** doll, List ** numbersByColor) {
	if (doll == NULL) {
		return ERROR_COLORING;
	}

	if ((*doll) == NULL) {
		return ERROR_COLORING;
	}

	if (blank(&(*doll)->innerDolls)) {
		(*doll)->color = getColor((*doll)->number, 0);
		return insertColoredDollOnList (*doll, numbersByColor);
	}

	return defineColorForInnerDolls(doll, numbersByColor);
}

int defineColorForInnerDolls (Doll ** doll, List ** numbersByColor) {
	Node * actual = (*doll)->innerDolls->first;
	Doll * inner;
	int coloringStatus;

	for (; actual != NULL; actual = actual->next) {
		inner = (Doll*) actual->value;
		coloringStatus = defineColorForDolls(&inner, numbersByColor);
		if (coloringStatus == ERROR_COLORING) {
			return ERROR_COLORING;
		}
	}

	(*doll)->color = getColor((*doll)->number, blueCounter(doll));

	return insertColoredDollOnList(*doll, numbersByColor);
}

Color getColor (int m, int n) {
	int sum = m + n;

	if (sum % 2 == 0) {
		return BLUE;
	}

	return RED;
}