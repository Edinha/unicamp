/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef HEAP_H
#define HEAP_H

#include "position.h"

/* Esse arquivo conterá as definições para a estrutura de min heap do programa, fazendo
 * a ordem de prioridade para a distância que uma posição está do começo
 */

#define ZERO_INIT 0
#define INVALID_INIT -1
#define CHILD_SIDE_COUNT 2

typedef
	struct {
		Position * data;
		int maxSize,
			actualSize;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho máximo para o vetor */
Heap* createHeap(int);

/* Retorna verdadeiro caso o tamanho atual seja igual ao maximo */
int isFull(Heap*);

/* Retorna o pai de uma posição parametrizada */
int parent(int);

/* Retorna a esquerda de uma posição parametrizada */
int leftChild(int);

/* Retorna a direita de uma posição parametrizada */
int rightChild(int);

/* Retorna veradeiro caso a posição esteja dentro do espectro do heap e falso caso contrário */
bool validHeapPosition(Heap*, int);

/* Insere na heap a posição atual com sua distância */
void push(Heap*, Position);

/* Retira a posição de menor distância da heap */
Position pop(Heap*);

/* Conserta o heap subindo os elementos fora de ordem */
void shiftUp(Heap*, int);

/* Conserta a heap descendo os elementos fora de ordem */
void shiftDown(Heap*, int);

/* Troca os valores dos caches a partir das posições parametrizadas */
void exchange(Heap*, int, int);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif