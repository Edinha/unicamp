/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

int main() {
	unsigned long wordCount;

	readLongInt(&wordCount);

	HashTable * table = createHashTable(wordCount);

	readEntryText(table, wordCount);

	readPlays(table);

	freeHashTable(&table);

	return 0;
}
