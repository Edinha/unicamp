/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementação dos métodos */

Word* createWord(String id) {
	Word * word = malloc(sizeof(Word));
	word->hash = ZERO_INIT;
	word->continuation = NULL;
	strcpy(word->id, id);
	return word;
}

int compare(String first, String second) {
	return strcmp(first, second);
}

int compareWords(Word * first, Word * second) {
	return (first->hash == second->hash);
}

void freeContinuation(Continuation ** continuation) {
	if (!(*continuation)) {
		return;
	}

	freeContinuation(&(*continuation)->next);
	free(*continuation);
}

void freeWord(Word ** word) {
	freeContinuation(&(*word)->continuation);
	free(*word);
}