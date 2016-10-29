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

/* Define a estrutura de um dado de cache do heap */
typedef
	struct {
		int number,
			priority;
	} Cache;

typedef
	struct {
		int size;
		Cache * data;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho maximo para o vetor */
Heap* createHeap(int);

/* Insere na heap o elemento, aumentando sua prioridade caso ele esteja contido no heap */
void insert(Heap*, int);

/* Aumenta a prioridade de um elemento de cache */
void higher(Cache*);

/* Diminue a prioridade de um elemento de cache */
void lower(Cache*);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif