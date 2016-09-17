/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

void readInt (int * i) {
	scanf("%d ", i);
}

 int readArrayFromFile (int ** dollsSize) {
	int arraySize;

	readInt(&arraySize);

	return arraySize;
 }

 /* Método que criará a relação entre as bonecas da entrada */
 void createDollsRelation () {
	 int * dollsSizes;
	 int arraySize = readArrayFromFile(&dollsSizes);

	 printf("%d", arraySize);
 }
