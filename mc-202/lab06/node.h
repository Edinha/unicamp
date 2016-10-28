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
		// TODO maybe useless
		//int height;

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

typedef
	struct NodeList {
		Portion * portion;
		struct NodeList * next;
	} NodeList;

typedef
	struct{
		NodeList * head;
	} List;

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

/* Remove o cliente da fila */
Client* dequeue(Queue**);

/* Libera o ponteiro de nó de Fila recursivamente */
void freeQueueElement(QueueElement**);

/* Libera o ponteiro de Fila */
void freeQueue(Queue**);

/* Inicializa um ponteiro para o nó da Lista */
NodeList* createNodeList(Portion*);

/* Insere no começo da lista */
void insertList(List**, Portion*);

/* Libera o ponteiro de nó de Lista recursivamente */
void freeNodeList(NodeList**);

/* Libera o ponteiro de Lista */
void freeList(List**);

#endif