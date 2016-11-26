/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementação dos métodos */

Word* createWord(String id, int size) {
	Word * word = malloc(sizeof(Word));
	strcpy(word->id, id);

	word->last = ZERO_INIT;
	word->continuations = malloc(size * sizeof(Word*));
	for(int i = 0; i < size; i++) {
		word->continuations[i] = NULL;
	}

	return word;
}

int compare(String first, String second) {
	return strcmp(first, second);
}

int compareWords(Word * first, Word * second) {
	return compare(first->id, second->id);
}

void freeWord(Word ** word) {
	free((*word)->continuations);
	free(*word);
}