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

int insert(Heap * heap, Cache newCache) {
	SearchElement * searched = search(heap, newCache);

	/* Caso o elemento tenha sido encontrado, altera sua prioridade e conserta o heap após alteração,
		retornando que o vetor de cache não teve alterações */
	if (searched) {
		updatePriority(searched->cache, newCache.priority);
		shiftUp(heap, searched->position);
		freeSearchElement(&searched);
		return NO_CACHE_CHANGE;
	}

	// Caso o heap não esteja cheio, é possível aumentar seu tamanho
	if (!isFull(heap)) {
		heap->actualSize++;
	}

	// TODO maybe change this to put new element on 0 and former 0 on last position of heap and rebalance

	// Coloca o novo elemento na última posição possível, conserta o heap e retorna que houve alterações
	heap->data[heap->actualSize - 1] = newCache;
	shiftUp(heap, heap->actualSize - 1);

	return CACHE_CHANGED;
}

SearchElement * search(Heap * heap, Cache searched) {
	for (int i = ZERO_INIT; i < heap->actualSize; i++) {
		if (sameNumber(heap->data[i], searched)) {
			return createSearchElement(&heap->data[i], i);
		}
	}

	return NULL;
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
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}