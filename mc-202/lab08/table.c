/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "table.h"

/* Implementacao dos metodos */

HashTable* createHashTable(unsigned long size) {
	HashTable * table = malloc(sizeof(HashTable));
	table->size = size;

	table->data = malloc(size * sizeof(Word*));
	for (unsigned long i = 0; i < size; i++) {
		table->data[i] = NULL;
	}

	return table;
}

void insert(HashTable * table, Word * word) {
	// TODO calculate hash for element and positionate it on data

	int position = hash(word->id) % table->size;

	while (table->data[position] != NULL) {
		position = (position + 1) % table->size;
	}

	table->data[position] = word;
}

unsigned long hash(String id) {
	int c;
	unsigned long key = PRIME;

	while ((c = *id++)) {
		key = ((key << 5)) + c;
	}

	return key;
}

Word* search(String id) {
	// TODO search for the man
	return NULL;
}

void freeHashTable(HashTable ** table) {
	// Maybe free all words on table ...
	free((*table)->data);
	free(*table);
}