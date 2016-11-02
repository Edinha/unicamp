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
	heap->data = malloc(size * sizeof(Cache));
	for (int i = ZERO_INIT; i < size; i++) {
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

int insert(Heap * heap, Tree * tree, Cache newCache) {
	Cache * removed, * inserted;

	inserted = look(tree->root, &newCache);

	// Caso o elemento exista na heap
	if (inserted->heapPosition > INVALID_NUMBER_INIT) {
		updatePriority(&heap->data[inserted->heapPosition], newCache.priority);
		shiftUp(heap, inserted->heapPosition);

		return NO_CACHE_CHANGE;
	}

	// Se o heap não estiver cheio, aumente seu tamanho para inserção
	if (!isFull(heap)) {
		heap->actualSize++;
	}

	// Procura pelo elemento de menor prioridade no heap e o remove
	removed = look(tree->root, &heap->data[heap->actualSize - 1]);
	if (removed) {
		removed->heapPosition = INVALID_NUMBER_INIT;
	}

	heap->data[heap->actualSize - 1] = newCache;
	shiftUp(heap, heap->actualSize - 1);

	// Coloca a flag para dizer que o elemento está na heap
	inserted->heapPosition = ZERO_INIT;

	return CACHE_CHANGED;
}

void shiftUp(Heap * heap, int position) {
	int comparison,
		parentPos = parent(position);

	// Compara a posição atual com seu pai e os troca caso o pai seja menor do que o filho

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

	heap->data[first].heapPosition = first;
	heap->data[second].heapPosition = second;
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}