/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "heap.h"

/* Implementação dos métodos */

Heap * createHeap(int size) {
	Heap * heap = malloc(sizeof(Heap));
	heap->maxSize = size;
	heap->actualSize = ZERO_INIT;

	// Inicializa o vetor de cache com elementos vazios
	heap->data = malloc(size * sizeof(Position));
	for (int i = ZERO_INIT; i < size; i++) {
		heap->data[i].x = ZERO_INIT;
		heap->data[i].y = ZERO_INIT;
		heap->data[i].distance = ZERO_INIT;
	}

	return heap;
}

int isFull(Heap * heap) {
	return (heap->actualSize == heap->maxSize);
}

int parent(int position) {
	return (position - 1) / 2;
}

void push(Heap * heap, Position pos) {
	heap->data[heap->actualSize] = pos;
	heap->actualSize++;
	shiftUp(heap, heap->actualSize - 1);
}

void shiftUp(Heap * heap, int position) {
	int comparison,
		parentPos = parent(position);

	// Caso seja a raiz, não possue pai
	if (!position) {
		return;
	}

	// Compara a posição atual com seu pai e os troca caso o pai seja menor do que o filho
	comparison = compare(heap->data[parentPos], heap->data[position]);

	if (comparison == LESSER) {
		exchange(heap, parentPos, position);
		shiftUp(heap, parentPos);
	}
}

// TODO remove the first element and shift down stuff

Position pop(Heap * heap) {
	Position pos = heap->data[0];
	heap->actualSize--;
	heap->data[0] = heap->data[heap->actualSize];
	shiftDown(heap, heap->actualSize - 1);

	return pos;
}

void shiftDown(Heap * heap, int position) {
	// TODO shift down this guy
}

void exchange(Heap * heap, int first, int second) {
	Position tmp = heap->data[first];
	heap->data[first] = heap->data[second];
	heap->data[second] = tmp;
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}