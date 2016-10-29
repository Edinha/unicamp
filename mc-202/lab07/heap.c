/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "heap.h"

/* Implementacao dos metodos */

Heap * createHeap(int size) {
	Heap * heap = malloc(sizeof(Heap));
	heap->data = malloc(size * sizeof(Cache));
	heap->size = 0;
	return heap;
}

void insert(Heap * heap, int cacheElement) {

}

void higher(Cache * cache) {

}

void lower(Cache * cache) {

}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}