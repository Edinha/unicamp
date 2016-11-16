/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

int main() {
	unsigned long size;

	readLongInt(&size);

	// TODO review this motherfucker
	// size = (2.4 * size) % 1;

	HashTable * table = createHashTable(size);

	readEntryText(table);

	freeHashTable(&table);

	return 0;
}
