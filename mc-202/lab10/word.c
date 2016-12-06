/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementação dos métodos */

Word* createWord(String id, int size) {
	Word * word = malloc(sizeof(Word));
	strcpy(word->id, id);

	word->size = ZERO_INIT;
	word->continuations = malloc(size * sizeof(Continuation*));
	for(int i = ZERO_INIT; i < size; i++) {
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

	for (int i = ZERO_INIT; i < tail->size; i++) {
		continuation = tail->continuations[i];

		if (!compareWords(continuation->word, head)) {
			heavify(continuation);
			return;
		}
	}

	tail->continuations[tail->size] = createContinuation(head, weight);
	tail->size++;
}

void heavify(Continuation * continuation) {
	continuation->weight--;

	// Caso seja menor do que zero, volta o peso da aresta para zero
	if (continuation->weight < ZERO_INIT) {
		continuation->weight = ZERO_INIT;
	}
}

void freeWord(Word ** word) {
	for (int i = ZERO_INIT; i < (*word)->size; i++) {
		free((*word)->continuations[i]);
	}

	free((*word)->continuations);
	free(*word);
}