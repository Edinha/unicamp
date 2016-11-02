/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readInt(int * i) {
	scanf("%d ", i);
}

void readFirstLine(int * maxSize, int * accesses) {
	scanf("%d %*d %d", maxSize, accesses);
}

void readEntry() {
	int maxSize,
		accesses,
		cacheAccessCount,
		actualElement;

	readFirstLine(&maxSize, &accesses);

	Heap * heap = createHeap(maxSize);
	Tree * tree = createTree();
	int * entries = malloc(accesses * sizeof(int));

	// Lê todas as entradas de acessos, criando uma árvore com os possíveis elementos de cache
	for (int i = ZERO_INIT; i < accesses; i++) {
		readInt(&actualElement);
		Cache newCache = createCache(actualElement, i);
		entries[i] = actualElement;
		tree->root = insertTree(tree->root, &newCache);
	}

	cacheAccessCount = ZERO_INIT;
	for (int i = ZERO_INIT; i < accesses; i++) {
		// TODO do somenthing with the entries array and cache access count
		Cache newCache = createCache(entries[i], i);
		cacheAccessCount += insert(heap, tree, newCache);
	}

	printResponse(cacheAccessCount);

	freeHeap(&heap);
	freeTree(&tree);
}

void printResponse(int count) {
	printf("%d\n", count);
}