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

void insert(Heap * heap, int cacheElement) {
	if (isFull(heap)) {
		// TODO remover o ultimo lugar do cache em prioridade e alocar mais novo
	}

	// TODO shift up some stuff
}

void shiftDown(Heap * heap, int position) {
	int higher = position,
		comparison,
		child;

	// TODO change later for function pointer maybe
	// int (*functions) = {&left, &right};

	child = left(position);
	comparison = compare(heap->data[higher], heap->data[child]);

	if (exists(heap, child) && comparison == LESSER) {
		higher = child;
	}

	child = right(position);
	comparison = compare(heap->data[higher], heap->data[child]);

	if (exists(heap, child) && comparison == LESSER) {
		higher = child;
	}

	if (higher != position) {
		exchange(heap, higher, position);
		shiftDown(heap, higher);
	}
}

void shiftUp(Heap * heap, int position) {
	int parentPos = parent(position),
		comparison = compare(heap->data[parentPos], heap->data[position]);

	if (exists(heap, parentPos) && comparison == LESSER) {
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