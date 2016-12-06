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
#define EQUALS 0
#define LESSER -1
#define GREATER 1
#define CHILD_SIDE_COUNT 2

/* Define a estutura para a heap, com o vetor de ponteiros de palavras e controladores inteiros para o tamanho */
typedef
	struct {
		Word ** data;
		int maxSize,
			actualSize;
	} Heap;

/* Inicializa um ponteiro de heap a partir de um tamanho máximo para o vetor */
Heap* createHeap(int);

/* Retorna o pai de uma posição parametrizada */
int parent(int);

/* Retorna a esquerda de uma posição parametrizada */
int leftChild(int);

/* Retorna a direita de uma posição parametrizada */
int rightChild(int);

/* Compara dois elementos da heap por suas distâncias */
int compareDistance(Word*, Word*);

/* Retorna verdadeiro caso o heap esteja vazio e falso caso contrario */
bool isEmptyHeap(Heap*);

/* Retorna veradeiro caso a posição esteja dentro do espectro do heap e falso caso contrário */
bool validHeapPosition(Heap*, int);

/* Insere na heap a palavra atual com sua distância */
void store(Heap*, Word*);

/* Retira a palavra de menor distância da heap */
Word* retrieve(Heap*);

/* Conserta o heap subindo os elementos fora de ordem */
void shiftUp(Heap*, int);

/* Conserta a heap descendo os elementos fora de ordem */
void shiftDown(Heap*, int);

/* Rebalanceia o heap para cima, decrementando a prioridade da palavra parametrizada */
void decreasePriority(Heap*, Word*);

/* Troca os valores dos caches a partir das posições parametrizadas */
void exchange(Heap*, int, int);

/* Libera um ponteiro de heap */
void freeHeap(Heap**);

#endif