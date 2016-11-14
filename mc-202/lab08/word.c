/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementacao dos metodos */

Word* createWord(String id) {
	Word * word = malloc(sizeof(Word));
	word->hash = ZERO_INIT;
	strcpy(word->id, id);
	return word;
}

Continuation* createContinuation(Word * word) {
	Continuation * continuation = malloc(sizeof(Continuation));
	continuation->count = ZERO_INIT;
	continuation->next = word;
	return continuation;
}

void raise(Continuation ** continuation) {
	(*continuation)->count++;
}

int compare(String first, String second) {
	return strcmp(first, second);
}

void freeContinuation(Continuation ** continuation) {
	free(*continuation);
}

void freeWord(Word ** word) {
	free(*word);
}