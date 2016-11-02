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

	Cache * newCache;

	Heap * heap = createHeap(maxSize);
	Tree * tree = createTree();
	int * entries = malloc(accesses * sizeof(int));

	// Lê todas as entradas de acessos, criando uma árvore com os possíveis elementos de cache
	for (int i = ZERO_INIT; i < accesses; i++) {
		readInt(&actualElement);
		newCache = createCache(actualElement, i, 1);
		entries[i] = actualElement;
		tree->root = insertTree(tree->root, newCache);

		if (newCache->number == INVALID_NUMBER_INIT) {
			freeCache(&newCache);
		}
	}

	// A partir de todas as entradas, insere os elementos no cache e soma o retorno
	// dessa operação repetidamente

	cacheAccessCount = ZERO_INIT;
	for (int i = ZERO_INIT; i < accesses; i++) {
		newCache = createCache(entries[i], i, 0);
		cacheAccessCount += insert(heap, tree, *newCache);
		freeCache(&newCache);
	}

	printResponse(cacheAccessCount);

	freeHeap(&heap);
	freeTree(&tree);
	free(entries);
}

void printResponse(int count) {
	printf("%d\n", count);
}