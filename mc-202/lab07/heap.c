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
	heap->data = malloc(size * sizeof(Cache*));
	for (int i = ZERO_INIT; i < size; i++) {
		heap->data[i] = NULL;
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

void recreateHeap(Heap * heap, int progress) {
	for (int i = parent(heap->actualSize - 1); i >= 0; i--) {
		updatePriority(heap->data[i], progress);
		shiftDown(heap, i);
	}
}

int insert(Heap * heap, Tree * tree, int cacheNumber, int progress) {
	// TODO again...

	Cache * searched;

	searched = search(tree->root, cacheNumber);
	updatePriority(searched, progress);

	if (searched->heapPosition != INVALID_NUMBER_INIT) {
		return NO_CACHE_CHANGE;
	}

	searched->heapPosition = ZERO_INIT;

	if (!isFull(heap)) {
		heap->actualSize++;
	} else {
		recreateHeap(heap, progress);
	}

	heap->data[heap->actualSize - 1] = searched;
	shiftUp(heap, heap->actualSize - 1);

	return CACHE_CHANGED;
}

void shiftDown(Heap * heap, int position) {
	int higher = position,
		comparison,
		child, i;

	/* A partir das funções de esquera ou direita, decide qual lado possui o maior elemento para ser
		trocado com a raiz no rebalanceamento do heap */

	int (*functions[2]) (int) = {&left, &right};

	for (i = ZERO_INIT; i < 2; i++) {
		int (*side) (int) = functions[i];

		child = side(position);

		if (exists(heap, child)) {
			comparison = compare(heap->data[higher], heap->data[child]);

			if (comparison == GREATER) {
				higher = child;
			}
		}
	}

	// Caso tenha sido encontrado um maior, é trocad com a posição atual e continua a recursão
	if (higher != position) {
		exchange(heap, higher, position);
		shiftDown(heap, higher);
	}
}

void shiftUp(Heap * heap, int position) {
	int comparison,
		parentPos = parent(position);

	// Compara a posição atual com seu pai e os troca caso o pai seja menor do que o filho

	if (exists(heap, parentPos) && parentPos != position) {
		comparison = compare(heap->data[parentPos], heap->data[position]);

		if (comparison == GREATER) {
			exchange(heap, parentPos, position);
			shiftUp(heap, parentPos);
		}
	}
}

void exchange(Heap * heap, int first, int second) {
	Cache * tmp = heap->data[first];
	heap->data[first] = heap->data[second];
	heap->data[second] = tmp;
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}