/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

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
void createDollsRelation (Doll ** external) {
	int * dollsNumbers;
	int arraySize = readArrayFromFile(&dollsNumbers);

	*external = incubateEntryDolls(&dollsNumbers, arraySize);

	free(dollsNumbers);
}