/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef NODE_H
#define NODE_H

#include "client.h"

/* Esse arquivo conterá as definições para a estrutura de nós do programa
 * usadas na implementação da base estrutural da árvore splay e da lista de clientes
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

/* Definição da lista de clientes */

typedef
	struct NodeList {
		Client * client;
		struct NodeList * next;
	} NodeList;

typedef
	struct {
		NodeList * head,
				 * tail;
	} List;

/* Inicializa um ponteiro para a árvore */
Tree* createTree();

/* Cria um nó da árvore a partir da informação de um arquivo */
NodeTree* createNodeTree(Ingredient*);

/* Libera recursivamente os nós de uma árvore */
void freeNodeTree(NodeTree**);

/* Libera o ponteiro de árvore */
void freeTree(Tree**);

/* Inicializa um ponteiro de lista */
List* createList();

/* Inicializa um ponteiro para o nó da lista */
NodeList* createNodeList(Client*);

/* Insere o cliente no final da lista */
void insertTail(List**, Client*);

/* Insere o cliente no começo da lista */
void insertHead(List**, Client*);

/* Libera o ponteiro de nó de lista recursivamente */
void freeNodeList(NodeList**);

/* Libera o ponteiro de lista */
void freeList(List**);

#endif