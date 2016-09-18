/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

// TODO DELETE
void printEntry (int * dollsNumbers, int arraySize) {
	printf("%d\n", arraySize);
	for (int i = 0; i < arraySize; i++) {
		printf("%d ", dollsNumbers[i]);
	}
}

void readInt (int * i) {
	scanf("%d ", i);
}

void initNumbers (int ** dollsNumbers, int arraySize) {
	int i;
	for (i = 0; i < arraySize; i++) {
		(*dollsNumbers)[i] = 0;
	}
}

int readArrayFromFile (int ** dollsNumbers) {
	int i, arraySize;

	readInt(&arraySize);

	(*dollsNumbers) = malloc(arraySize * sizeof(int));
	initNumbers(dollsNumbers, arraySize);

	for (i = 0; i < arraySize; i++) {
		readInt(&(*dollsNumbers)[i]);
	}

	return arraySize;
}

/* Método que criará a relação entre as bonecas da entrada */
void createDollsRelation () {
	int * dollsNumbers;
	int arraySize = readArrayFromFile(&dollsNumbers);

	printEntry(dollsNumbers, arraySize);
	Doll * external = incubateEntryDolls(&dollsNumbers, arraySize);
	Doll * children = (Doll*) external->innerDolls->first->value;

	printf("\n\n%d", children->size);
	free(dollsNumbers);
}

Doll* incubateEntryDolls (int ** dollsNumbers, int size) {
	int i, actualSize;
	Stack * numbers,
		  * dolls;

	Doll * parent,
		 * children;

	initStack(&numbers);
	initStack(&dolls);

	for (i = 0; i < size; i++) {
		actualSize = (*dollsNumbers)[i];

		if (isStartOfNewDoll(actualSize)) {
			Doll * actual;
			initDoll(&actual);

			actual->size = -actualSize;
			push((void*) &actual->size, &numbers);
			push((void*) actual, &dolls);
		} else {
			if (empty(&numbers)) {
				return NULL;
			}

			actualSize = * ((int*) pop(&numbers));
			children = (Doll*) pop(&dolls);
			parent = (Doll*) peek(&dolls);

			if (parent == NULL) {
				if (children->size != actualSize) {
					return NULL;
				}

				parent = children;
				break;
			}

			incubate(children, &parent->innerDolls);
		}
	}

	if (!empty(&numbers)) {
		return NULL;
	}

	return parent;
}

bool isStartOfNewDoll (int number) {
	return (number < 0);
}
