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

	// Inicializa o vetor de posições com elementos vazios
	heap->data = malloc(size * sizeof(Position));
	for (int i = ZERO_INIT; i < size; i++) {
		heap->data[i].x = INVALID_INIT;
		heap->data[i].y = INVALID_INIT;
		heap->data[i].distance = INVALID_INIT;
	}

	return heap;
}

int isFull(Heap * heap) {
	return (heap->actualSize == heap->maxSize);
}

int parent(int position) {
	return (position - 1) / 2;
}

int leftChild(int position) {
	return (position * 2);
}

int rightChild(int position) {
	return (position * 2 + 1);
}

bool validHeapPosition(Heap * heap, int position) {
	if (position > heap->actualSize) {
		return false;
	}

	return true;
}

void store(Heap * heap, Position pos) {
	heap->data[heap->actualSize] = pos;
	heap->actualSize++;
	shiftUp(heap, heap->actualSize - 1);
}

Position retrieve(Heap * heap) {
	Position pos = heap->data[0];
	heap->actualSize--;
	heap->data[0] = heap->data[heap->actualSize];
	shiftDown(heap, heap->actualSize - 1);

	return pos;
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

	if (comparison == GREATER) {
		exchange(heap, parentPos, position);
		shiftUp(heap, parentPos);
	}
}

void shiftDown(Heap * heap, int position) {
	int minimum = position,
		child,
		comparison;

	int (*childs[CHILD_SIDE_COUNT]) (int) = {&rightChild, &leftChild};

	// Para cada uma dos lados, gera a comparação com a posição atual
	for (int i = 0; i < CHILD_SIDE_COUNT; i++) {
		child = (*childs[i]) (position);
		comparison = compare(heap->data[child], heap->data[minimum]);

		// Caso seja menor do que a posição de menor até agora encontrada, atualiza com o menor possível
		if (validHeapPosition(heap, child) && comparison == LESSER) {
			minimum = child;
		}
	}

	if (minimum != position) {
		exchange(heap, minimum, position);
		shiftDown(heap, minimum);
	}
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