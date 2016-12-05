/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementacao dos metodos */

// TODO delete
void print(HashTable * table) {
	Word * word;
	for (unsigned long i = ZERO_INIT; i < table->size; i++) {
		word = table->data[i];
		if (word) {
			for (int i = ZERO_INIT; i < word->size; i++) {
				Continuation * c = word->continuations[i];
				printf("%s -> %s (%ld)\n", word->id, c->word->id, c->weight);
			}
		}
	}
}

HashTable* buildGraph() {
	HashTable * table;

	int count;
	unsigned long wordCount, edgeSizeDelimiter, phraseCounter;

	String id;
	Word * next,
		 * previous;

	readLong(&wordCount);
	readLong(&edgeSizeDelimiter);
	readLong(&phraseCounter);

	table = createHashTable(wordCount, edgeSizeDelimiter);

	// Para cada frase do texto, le as palavras e as aloca
	for (unsigned long i = ZERO_INIT; i < phraseCounter; i++) {
		readInt(&count);
		readString(id);

		previous = insert(table, id);

		// Faz a contagem de palavras de cada frase e aloca a sequencia
		for (int i = COUNT_INIT; i < count; i++) {
			readString(id);

			next = insert(table, id);
			alocateSequence(previous, next, table->edgeSizeDelimiter - 1);

			previous = next;
		}
	}

	return table;
}

void minimumWay(HashTable * table, String start, String end) {
	// TODO find in hash table a way for it

	Heap * heap = createHeap(table->wordCount);

	Word * actual = search(table, start);

	Continuation * continuation = NULL;

	store(heap, actual, ZERO_INIT);

	for (;;) {
		HeapElement element = retrieve(heap);
		actual = element.word;

		for (int i = ZERO_INIT; i < actual->size; i++) {
			continuation = actual->continuations[i];

			// Caso a continucao seja igual a palavra final, um caminho foi encontrado
			if (!compare(continuation->word->id, end)) {
				break;
			}

			// TODO visited flag for word
			// TODO alocate continuation on heap
		}
	}

	freeHeap(&heap);
}

void printWay() {
	// TODO print with a stack all of this
}