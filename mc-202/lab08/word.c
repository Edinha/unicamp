/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementacao dos metodos */

Word* createWord(String id) {
	Word * word = malloc(sizeof(Word));
	word->continuations = createList();
	word->hash = ZERO_INIT;
	strcpy(word->id, id);
	return word;
}

int compare(String first, String second) {
	return strcmp(first, second);
}

int compareWord(Word * first, Word * second) {
	return compare(first->id, second->id);
}

void freeWord(Word ** word) {
	freeList(&(*word)->continuations);
	free(*word);
}