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
		emptyInit(&heap->data[i]);
	}

	return heap;
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

int exists(Heap * heap, int position) {
	return (position < heap->actualSize);
}

int insert(Heap * heap, int cacheElement) {
	Cache newCache = createCache(cacheElement);

	SearchElement * searched = search(heap, newCache);
	if (searched) {
		higher(searched->cache);
		shiftUp(heap, searched->position);
		freeSearchElement(&searched);
		return NO_CACHE_CHANGE;
	}

	if (isFull(heap)) {
		heap->data[heap->actualSize] = newCache;
	}

	heap->data[heap->actualSize] = newCache;
	shiftUp(heap, heap->actualSize);
	heap->actualSize++;

	return CACHE_CHANGED;
}

SearchElement * search(Heap * heap, Cache searched) {
	int i, comparison;
	for (i = 0; i < heap->actualSize; i++) {
		comparison = compare(heap->data[i], searched);

		if (!comparison) {
			return createSearchElement(&heap->data[i], i);
		}

		if (comparison == LESSER) {
			return NULL;
		}
	}

	return NULL;
}

void shiftDown(Heap * heap, int position) {
	int higher = position,
		comparison,
		child, i;

	int (*functions[2]) (int) = {&left, &right};

	for (i = 0; i < 2; i++) {
		int (*side) (int) = functions[i];

		child = side(position);
		comparison = compare(heap->data[higher], heap->data[child]);

		if (exists(heap, child) && comparison == LESSER) {
			higher = child;
		}
	}

	if (higher != position) {
		exchange(heap, higher, position);
		shiftDown(heap, higher);
	}
}

void shiftUp(Heap * heap, int position) {
	int parentPos = parent(position),
		comparison = compare(heap->data[parentPos], heap->data[position]);

	if (exists(heap, parentPos) && comparison <= EQUALS) {
		exchange(heap, parentPos, position);
		shiftUp(heap, parentPos);
	}
}

void exchange(Heap * heap, int first, int second) {
	Cache tmp = heap->data[first];
	heap->data[first] = heap->data[second];
	heap->data[second] = tmp;
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}