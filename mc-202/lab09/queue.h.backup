/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef QUEUE_H
#define QUEUE_H

/* Esse arquivo contém as definições de uma fila de posicoes para o programa
 * Usada para implementar o algoritmo de encontrar caminhos no grafo
 */

#include "position.h"

/* Define a estrutura de nó da Fila, com sua posicao e referencia para o proximo elemento */
typedef
	struct NodeQueue {
		int count;
		Position position;
		struct NodeQueue * next;
	} NodeQueue;

/* Define a estrutura de fila, com o ponteiro para o nó inicial */
typedef
	struct {
		NodeQueue * head, * tail;
	} Queue;

/* Inicializa um novo ponteiro de nó para a fila de posicoes */
NodeQueue* createNodeQueue(int, Position);

/* Inicializa um novo ponteiro de fila */
Queue* createQueue();

/* Enfileira uma posicao na fila */
void queue(Queue**, int, Position);

/* Desenfileira uma posicao da fila */
Position dequeue(Queue**, int*);

/* Retorna verdadeiro caso a lista esteja vazia */
int isEmpty(Queue**);

/* Libera o ponteiro de nos de fila recursivamente */
void freeNodeQueue(NodeQueue**);

/* Libera o ponteiro de fila */
void freeQueue(Queue**);

#endif