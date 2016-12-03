/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementação dos métodos */

Word* createWord(String id, int size) {
	Word * word = malloc(sizeof(Word));
	strcpy(word->id, id);

	word->size = size;
	word->continuations = malloc(size * sizeof(Continuation*));
	for(int i = 0; i < size; i++) {
		word->continuations[i] = NULL;
	}

	return word;
}

Continuation* createContinuation(Word * word, long weight) {
	Continuation * continuation = malloc(sizeof(Continuation));
	continuation->word = word;
	continuation->weight = weight;
	return continuation;
}

int compare(String first, String second) {
	return strcmp(first, second);
}

int compareWords(Word * first, Word * second) {
	return compare(first->id, second->id);
}

void alocateSequence(Word * tail, Word * head, long weight) {
	Continuation * continuation = NULL;

	for (int i = 0; i < tail->size; i++) {
		continuation = tail->continuations[i];

		if (!continuation) {
			tail->continuations[i] = createContinuation(head, weight);
			tail->size++;
			return;
		}

		if (!compareWords(continuation->word, head)) {
			heavify(continuation);
			return;
		}
	}
}

void heavify(Continuation * continuation) {
	continuation->weight--;
	if (continuation->weight < ZERO_INIT) {
		continuation->weight = ZERO_INIT;
	}
}

void freeWord(Word ** word) {
	for (int i = 0; i < (*word)->size; i++) {
		if ((*word)->continuations[i]) {
			free((*word)->continuations[i]);
		}
	}

	free((*word)->continuations);
	free(*word);
}