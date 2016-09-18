/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "colored.h"

/* Implementação dos métodos */

int insertColoredDollOnList (Doll * doll, List ** list) {
	Colored * newColored = createColored(doll),
			* colored;

	Node * newNode = createNode((void*) newColored),
		 * actual,
		 * previous;

	if (blank(list)) {
		(*list)->first = newNode;
		return SUCESS_COLORING;
	}

	previous = (*list)->first;
	colored = (Colored*) previous->value;

	if (colored->number > newColored->number) {
		newNode->next = previous;
		(*list)->first = newNode;
		return SUCESS_COLORING;
	}

	if (sameNumberDifferentColor(colored, newColored)) {
		return ERROR_COLORING;
	}

	for (actual = previous->next; actual != NULL;) {
		colored = (Colored*) actual->value;

		// TODO validate already existing
		if (sameNumberDifferentColor(colored, newColored)) {
			return ERROR_COLORING;
		}

		if (colored->number == newColored->number) {
			return SUCESS_COLORING;
		}

		if (colored->number > newColored->number) {
			break;
		}

		previous = actual;
		actual = actual->next;
	}

	newNode->next = actual;
	previous->next = newNode;

	return SUCESS_COLORING;
}

Colored * createColored (Doll * doll) {
	Colored * colored = malloc(sizeof(Colored));
	colored->number = doll->number;
	colored->color = doll->color;
	return colored;
}

bool sameNumberDifferentColor (Colored * colored, Colored * new) {
	if (colored->number != new->number) {
		return false;
	}

	if (colored->color == new->color) {
		return false;
	}

	return true;
}

void response (List ** list) {
	Node * actual;
	Colored * colored;
	printf("%s", SUCESS_MESSAGE);

	for (actual = (*list)->first; actual != NULL; actual = actual->next) {
		colored = (Colored*) actual->value;
		printf("%d: ", colored->number);

		switch (colored->color) {
			case RED:
				printf("vermelho\n");
				break;
			case BLUE:
				printf("azul\n");
				break;
			default:
				break;
		}
	}
}

// TODO Delete
void printDolls (Doll * doll) {
	printf("\n\nNumber: %d Color: %d", doll->number, doll->color);
	Doll * a = (Doll*) doll->innerDolls->first->value;
	printf("\n\nNumber: %d Color: %d", a->number, a->color);
	Doll * b = (Doll*) a->innerDolls->first->next->value;
	printf("\n\nNumber: %d Color: %d", b->number, b->color);
}