/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementacao dos metodos */

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

	table = createHashTable(wordCount);

	// Para cada frase do texto, le as palavras e as aloca
	for (unsigned long i = ZERO_INIT; i < phraseCounter; i++) {
		readInt(&count);
		readString(id);

		previous = insert(table, id);

		// Faz a contagem de palavras de cada frase e aloca a sequencia
		for (int i = COUNT_INIT; i < count; i++) {
			readString(id);

			next = insert(table, id);
			alocateSequence(previous, next, edgeSizeDelimiter - 1);

			previous = next;
		}
	}

	return table;
}

void minimumWay(HashTable * table, Heap * heap, String start, String end) {

	int i;
	Word * actual, * init;
	Continuation * continuation;

	unsigned long distance;

	init = search(table, start);
	init->distance = ZERO_INIT;
	decreasePriority(heap, init);

	// Enquanto existem elementos na heap, recupera o de menor prioridade
	while (!isEmptyHeap(heap)) {

		actual = retrieve(heap);

		// Para cada um dos vizinhos dele, altera a distância para o nó caso o caminho seja menor do que
		// o já previamente encontrado pelo algoritmo
		for (i = ZERO_INIT; i < actual->size; i++) {
			continuation = actual->continuations[i];
			distance = actual->distance + continuation->weight;

			if (distance < continuation->word->distance) {
				continuation->word->parent = actual;
				continuation->word->distance = distance;
				decreasePriority(heap, continuation->word);
			}
		}

	}

	actual = search(table, end);

	printWay(init, actual);
}