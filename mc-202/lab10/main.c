/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	int count;
	String start, end;

	HashTable * graph = buildGraph();
	Heap * heap = createHeap(graph->wordCount);

	readInt(&count);

	for (int i = ZERO_INIT; i < count; i++) {
		readString(start);
		readString(end);

		// Inicializa as estruturas para a busca atual
		heap->actualSize = ZERO_INIT;
		initializeSearch(graph);

		minimumWay(graph, heap, start, end);
	}

	freeHeap(&heap);
	freeHashTable(&graph);

	return 0;
}
