/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementacao dos metodos */

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
	Cache newCache;

	cacheAccessCount = ZERO_INIT;

	for (int i = 0; i < accesses; i++) {
		readInt(&actualElement);
		newCache = createCache(actualElement, i);
		cacheAccessCount += insert(heap, newCache);
	}

	printResponse(cacheAccessCount);

	freeHeap(&heap);
}

void printResponse(int count) {
	printf("%d\n", count);
}