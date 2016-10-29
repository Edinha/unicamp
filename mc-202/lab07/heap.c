/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "heap.h"

/* Implementacao dos metodos */

Heap * createHeap(int size) {
	Heap * heap = malloc(sizeof(Heap));
	heap->maxSize = size;
	heap->actualSize = ZERO_INIT;

	heap->data = malloc(size * sizeof(Cache));
	for (int i = 0; i < size; i++) {
		heap->data[i].number = INVALID_NUMBER_INIT;
		heap->data[i].priority = ZERO_INIT;
	}

	return heap;
}

Cache createCache(int number) {
	Cache cache;
	cache.number = number;
	cache.priority = ZERO_INIT;
	return cache;
}

int isFull(Heap * heap) {
	return (heap->actualSize == heap->maxSize);
}

int left(int position) {
	return (position * 2) + 1;
}

int right(int position) {
	return (position * 2) + 2;
}

int parent(int position) {
	return (position - 1) / 2;
}

int positionExists(Heap * heap, int position) {
	return (position < heap->actualSize);
}

void insert(Heap * heap, int cacheElement) {
	Cache cache = createCache(cacheElement);

	if (isFull(heap)) {
		// TODO remover o ultimo lugar do cache em prioridade
	}

	add(heap, cache, 0);
}

void add(Heap * heap, Cache cache, int position) {

}

void higher(Cache * cache) {

}

void lower(Cache * cache) {

}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}