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
	heap->data = malloc(size * sizeof(Word*));
	for (int i = ZERO_INIT; i < size; i++) {
		heap->data[i] = NULL;
	}

	return heap;
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

int compareDistance(Word * first, Word * second) {
	if (first->distance > second->distance) {
		return GREATER;
	}

	if (first->distance == second->distance) {
		return EQUALS;
	}

	return LESSER;
}

bool isEmptyHeap(Heap * heap) {
	return (heap->actualSize == ZERO_INIT);
}

bool validHeapPosition(Heap * heap, int position) {
	if (position >= heap->actualSize) {
		return false;
	}

	return true;
}

void store(Heap * heap, Word * word) {
	heap->data[heap->actualSize] = word;
	heap->actualSize++;
	shiftUp(heap, heap->actualSize - 1);
}

Word* retrieve(Heap * heap) {
	Word * word = heap->data[0];
	heap->actualSize--;

	// Altera os valores para as palavras trocadas ao recuperar um elemento da heap
	heap->data[0] = heap->data[heap->actualSize];
	heap->data[heap->actualSize] = NULL;
	shiftDown(heap, 0);

	return word;
}

void shiftUp(Heap * heap, int position) {
	int comparison,
		parentPos = parent(position);

	// Caso seja a raiz, não possue pai
	if (!position || !validHeapPosition(heap, position)) {
		return;
	}

	// Compara a posição atual com seu pai e os troca caso o pai seja menor do que o filho
	comparison = compareDistance(heap->data[parentPos], heap->data[position]);

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
	for (int i = ZERO_INIT; i < CHILD_SIDE_COUNT; i++) {
		child = (*childs[i]) (position);

		// Caso seja uma posição não contida no heap, pula a comparação
		if (!validHeapPosition(heap, child)) {
			continue;
		}

		comparison = compareDistance(heap->data[child], heap->data[minimum]);

		// Caso seja menor do que a posição de menor até agora encontrada, atualiza com o menor possível
		if (comparison == LESSER) {
			minimum = child;
		}
	}

	// Caso o mínimo tenha mudado, é preciso continuar descendo a partir do filho menor
	if (minimum != position) {
		exchange(heap, minimum, position);
		shiftDown(heap, minimum);
	}
}

void exchange(Heap * heap, int first, int second) {
	Word * tmp = heap->data[first];
	heap->data[first] = heap->data[second];
	heap->data[second] = tmp;
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}