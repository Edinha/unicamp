/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "table.h"

/* Implementacao dos metodos */

HashTable* createHashTable(unsigned long wordCount) {
	HashTable * table = malloc(sizeof(HashTable));
	table->size = SIZE_MULTIPLIER * wordCount;

	table->data = malloc(table->size * sizeof(Word*));
	for (unsigned long i = 0; i < table->size; i++) {
		table->data[i] = NULL;
	}

	return table;
}

void insert(HashTable * table, Word * word) {
	unsigned long position = hash(word->id) % table->size;

	while (table->data[position] != NULL) {
		position = (position + 1) % table->size;

		// Caso a palavra já exista na tabela, não a coloca denovo
		if (!compareWord(table->data[position], word)) {
			freeWord(&word);
			return;
		}
	}

	word->hash = position;
	table->data[position] = word;
}

Word* search(HashTable * table, String id) {
	unsigned long position = hash(id) % table->size;

	while (table->data[position] != NULL) {
		if (!compare(table->data[position]->id, id)) {
			return table->data[position];
		}

		position = (position + 1) % table->size;
	}

	return NULL;
}

unsigned long hash(String id) {
	char c;
	unsigned long key = PRIME;

	// Enquanto existem caractéres na string, aplica a função
	while ((c = *id++)) {
		key = ((key << 5)) + c;
	}

	return key;
}

void freeHashTable(HashTable ** table) {
	for (unsigned long i = 0; i < (*table)->size; i++) {
		if ((*table)->data[i]) {
			freeWord(&(*table)->data[i]);
		}
	}

	free((*table)->data);
	free(*table);
}