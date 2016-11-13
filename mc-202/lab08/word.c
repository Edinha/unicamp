/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementacao dos metodos */

Word* createWord(String id) {
	Word * word = malloc(sizeof(Word));
	word->hash = ZERO_INIT;
	word->count = ZERO_INIT;
	strcpy(word->id, id);
	return word;
}

void raise(Word ** word) {
	(*word)->count++;
}

int compare(Word * first, Word * second) {
	return strcmp(first->id, second->id);
}

void freeWord(Word ** word) {
	free(*word);
}