/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

/* Esse arquivo conterá as definições para a estrutura de max heap do programa, fazendo
 * a ordem de prioridade para o cache do programa
 */

#define ZERO_INIT 0
#define INVALID_NUMBER_INIT -1

/* Define a estrutura de um dado de cache do heap */
typedef
	struct {
		int number,
			priority;
	} Cache;

typedef
	struct {
		Cache * data;
		int maxSize,
			actualSize;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho maximo para o vetor */
Heap* createHeap(int);

/* Inicializa um elemento de cache a partir de seu numero */
Cache createCache(int);

/* Retorna verdadeiro caso o tamanho atual seja igual ao maximo */
int isFull(Heap*);

/* Retorna a esquerda de uma posicao parametrizada */
int left(int);

/* Retorna a direita de uma posicao parametrizada */
int right(int);

/* Retorna o pai de uma posicao parametrizada */
int parent(int);

/* Retorna verdadeiro caso a posicao inteira exista no heap */
int positionExists(Heap*, int);

/* Insere na heap o elemento, aumentando sua prioridade caso ele esteja contido no heap */
void insert(Heap*, int);

/* Adiciona recursivamente um elemento de cache ao heap a partir de uma posicao */
void add(Heap*, Cache, int);

/* Aumenta a prioridade de um elemento de cache */
void higher(Cache*);

/* Diminue a prioridade de um elemento de cache */
void lower(Cache*);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif