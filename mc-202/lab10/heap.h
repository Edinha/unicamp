/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef HEAP_H
#define HEAP_H

#include "word.h"

/* Esse arquivo conterá as definições para a estrutura de min heap do programa, fazendo
 * a ordem de prioridade para a distância que uma palavra esta do comeco da frase
 */

/* Definicoes para retorno da comparacao entre elementos do heap */
#define LESSER -1
#define GREATER 1
#define CHILD_SIDE_COUNT 2

/* Define a estrutura do elemento do heap, com a distancia e a palavra enfileirada */
typedef
	struct {
		unsigned long distance;
		Word * word;
	} HeapElement;

typedef
	struct {
		HeapElement * data;
		int maxSize,
			actualSize;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho máximo para o vetor */
Heap* createHeap(int);

/* Inicializa um elemento do heap */
HeapElement createHeapElement(Word*, unsigned long);

/* Retorna o pai de uma posição parametrizada */
int parent(int);

/* Retorna a esquerda de uma posição parametrizada */
int leftChild(int);

/* Retorna a direita de uma posição parametrizada */
int rightChild(int);

/* Compara dois elementos da heap */
int compareElement(HeapElement, HeapElement);

/* Retorna verdadeiro caso o heap esteja vazio e falso caso contrario */
bool isEmptyHeap(Heap*);

/* Retorna veradeiro caso a posição esteja dentro do espectro do heap e falso caso contrário */
bool validHeapPosition(Heap*, int);

/* Insere na heap a palavra atual com sua distância */
void store(Heap*, Word*, unsigned long);

/* Retira a palavra de menor distância da heap */
HeapElement retrieve(Heap*);

/* Conserta o heap subindo os elementos fora de ordem */
void shiftUp(Heap*, int);

/* Conserta a heap descendo os elementos fora de ordem */
void shiftDown(Heap*, int);

/* Troca os valores dos caches a partir das posições parametrizadas */
void exchange(Heap*, int, int);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif