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

void minimumWay(HashTable * table, Heap * heap, String start, String end) {

	Word * actual = search(table, start);
	Continuation * continuation = NULL;

	store(heap, actual, ZERO_INIT);
	actual->visited = true;

	for (;;) {

		// Caso o heap esteja vazio, nao existe caminho entre as duas palavras parametrizadas
		if (isEmptyHeap(heap)) {
			printError();
			return;
		}

		HeapElement element = retrieve(heap);
		actual = element.word;

		for (int i = ZERO_INIT; i < actual->size; i++) {
			continuation = actual->continuations[i];
			continuation->word->parent = actual;

			// Caso a palavra ja tenha sido visitada, continua a busca sem visita-la novamente
			if (continuation->word->visited) {
				continue;
			}

			// Caso a continucao seja igual a palavra final, um caminho foi encontrado
			if (!compare(continuation->word->id, end)) {
				printWay(continuation->word);
				return;
			}

			// Aloca a palavra subsequente na heap para continuar a busca em largura
			store(heap, continuation->word, continuation->weight + element.distance);
			continuation->word->visited = true;
		}
	}

	freeHeap(&heap);
}