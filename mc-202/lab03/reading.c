/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

void readInt (int * i) {
	scanf("%d ", i);
}

int readArrayFromFile (int ** dollsSizes) {
	int i, arraySize;

	readInt(&arraySize);

	(*dollsSizes) = malloc(arraySize * sizeof(int));

	for (i = 0; i < arraySize; i++) {
		readInt(&(*dollsSizes)[i]);
	}

	return arraySize;
}

/* Método que criará a relação entre as bonecas da entrada */
void createDollsRelation () {
	int * dollsSizes;
	int arraySize = readArrayFromFile(&dollsSizes);

	printf("%d\n", arraySize);

	for (int i = 0; i < arraySize; i++) {
		printf("%d ", dollsSizes[i]);
	}

	free(dollsSizes);
}

bool isStartOfNewDoll (int number) {
	return (number < 0);
}
