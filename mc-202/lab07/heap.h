/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef HEAP_H
#define HEAP_H

#include "tree.h"
#include "list.h"

/* Esse arquivo conterá as definições para a estrutura de max heap do programa, fazendo
 * a ordem de prioridade para o cache do programa
 */

/* Definindo o inteiro a ser somado quando há alterações no cache */
#define CACHE_CHANGED 1
#define NO_CACHE_CHANGE 0

typedef
	struct {
		Cache * data;
		int maxSize,
			actualSize;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho máximo para o vetor */
Heap* createHeap(int);

/* Retorna verdadeiro caso o tamanho atual seja igual ao maximo */
int isFull(Heap*);

/* Retorna a esquerda de uma posição parametrizada */
int left(int);

/* Retorna a direita de uma posição parametrizada */
int right(int);

/* Retorna o pai de uma posição parametrizada */
int parent(int);

/* Retorna verdadeiro caso a posição exista no heap */
int exists(Heap*, int);

/* Insere na heap o elemento de cache parametrizado, caso exista atualiza seu valor, retornando caso haja mudanças no heap */
int insert(Heap*, Tree*, Cache);

/* Conserta o heap subindo os elementos fora de ordem */
void shiftUp(Heap*, int);

/* Troca os valores dos caches a partir das posições parametrizadas */
void exchange(Heap*, int, int);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif