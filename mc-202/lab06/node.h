/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef NODE_H
#define NODE_H

#include "client.h"

/* Esse arquivo conterá as definições para a estrutura de nós do programa
 * usadas na implementação da base estrutural da árvore splay e da Fila de clientes
 */

/* Definição da árvore splay */
typedef
	struct NodeTree {
		Ingredient * ingredient;
		struct NodeTree * left;
		struct NodeTree * right;
	} NodeTree;

typedef
	struct {
		NodeTree * root;
	} Tree;

/* Definição da Fila de clientes */
typedef
	struct QueueElement {
		Client * client;
		struct QueueElement * next;
	} QueueElement;

typedef
	struct {
		QueueElement * head, * tail;
	} Queue;

/* Inicializa um ponteiro para a árvore */
Tree* createTree();

/* Cria um nó da árvore a partir da informação de um arquivo */
NodeTree* createNodeTree(Ingredient*);

/* Libera recursivamente os nós de uma árvore */
void freeNodeTree(NodeTree**);

/* Libera o ponteiro de árvore */
void freeTree(Tree**);

/* Inicializa um ponteiro de Fila */
Queue* createQueue();

/* Inicializa um ponteiro para o nó da Fila */
QueueElement* createQueueElement(Client*);

/* Insere o cliente no final da Queue */
void queue(Queue**, Client*);

/* Insere no começo da fila, "furando" a fila já existente */
void headQueue(Queue**, Client*);

/* Remove o cliente da fila */
Client* dequeue(Queue**);

/* Retorna verdadeiro caso a fila esteja vazia, falso caso contrário */
int emptyQueue(Queue**);

/* Libera o ponteiro de nó de Fila recursivamente */
void freeQueueElement(QueueElement**);

/* Libera o ponteiro de Fila */
void freeQueue(Queue**);

#endif