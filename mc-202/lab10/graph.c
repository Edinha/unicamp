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
	unsigned long distance;
	Continuation * continuation;

	Word * init = search(table, start),
		 * finish = search(table, end);

	// Inicializa a primeira palavra e a aloca na heap
	init->distance = ZERO_INIT;
	store(heap, init);

	// Enquanto a heap não está vazia, recupera o elemento de maior prioridade e avança na busca
	while (!isEmptyHeap(heap)) {

		Word * actual = retrieve(heap);

		// Para todos os vizinhos, calcula a distância até eles e a atualiza caso for menor do que a atual
		for (int i = ZERO_INIT; i < actual->size; i++) {
			continuation = actual->continuations[i];
			distance = actual->distance + continuation->weight;

			if (distance < continuation->word->distance) {
				continuation->word->parent = actual;
				continuation->word->distance = distance;
				store(heap, continuation->word);
			}
		}
	}

	printWay(init, finish);
}