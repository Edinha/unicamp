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

int insert(Heap * heap, Cache newCache) {
	SearchElement * searched = search(heap, newCache);

	if (searched) {
		updatePriority(searched->cache, newCache.priority);
		shiftUp(heap, searched->position);
		freeSearchElement(&searched);
		return NO_CACHE_CHANGE;
	}

	if (!isFull(heap)) {
		heap->actualSize++;
	}

	heap->data[heap->actualSize - 1] = newCache;
	shiftUp(heap, heap->actualSize - 1);

	return CACHE_CHANGED;
}

SearchElement * search(Heap * heap, Cache searched) {
	for (int i = 0; i < heap->actualSize; i++) {
		if (sameNumber(heap->data[i], searched)) {
			return createSearchElement(&heap->data[i], i);
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

		if (exists(heap, child)) {
			comparison = compare(heap->data[higher], heap->data[child]);

			if (comparison == LESSER) {
				higher = child;
			}
		}
	}

	if (higher != position) {
		exchange(heap, higher, position);
		shiftDown(heap, higher);
	}
}

void shiftUp(Heap * heap, int position) {
	int comparison,
		parentPos = parent(position);

	if (exists(heap, parentPos) && parentPos != position) {
		comparison = compare(heap->data[parentPos], heap->data[position]);

		if (comparison == LESSER) {
			exchange(heap, parentPos, position);
			shiftUp(heap, parentPos);
		}
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