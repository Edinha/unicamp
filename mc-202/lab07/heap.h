/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef HEAP_H
#define HEAP_H

#include "cache.h"

/* Esse arquivo conterá as definições para a estrutura de max heap do programa, fazendo
 * a ordem de prioridade para o cache do programa
 */

typedef
	struct {
		Cache * data;
		int maxSize,
			actualSize;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho maximo para o vetor */
Heap* createHeap(int);

/* Retorna verdadeiro caso o tamanho atual seja igual ao maximo */
int isFull(Heap*);

/* Retorna a esquerda de uma posicao parametrizada */
int left(int);

/* Retorna a direita de uma posicao parametrizada */
int right(int);

/* Retorna o pai de uma posicao parametrizada */
int parent(int);

/* Retorna verdadeiro caso a posicao inteira exista no heap */
int exists(Heap*, int);

/* Insere na heap o elemento, aumentando sua prioridade caso ele esteja contido no heap */
void insert(Heap*, int);

/* Conserta o heap descendo os elementos fora de ordem */
void shiftDown(Heap*, int);

/* Conserta o heap subindo os elementos fora de ordem */
void shiftUp(Heap*, int);

/* Troca os valores dos caches a partir das posicoes parametrizadas */
void exchange(Heap*, int, int);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif