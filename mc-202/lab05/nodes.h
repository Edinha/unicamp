/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef NODES_H
#define NODES_H

#include "file.h"

/* Esse arquivo conterá as definições para as estrutura de nós do programa
 * usadas na implementaçãod de árvores e listas
 */

typedef
	struct NodeTree {
		File * file;
		struct NodeTree * left;
		struct NodeTree * right;
	} NodeTree;


typedef
	struct {
		NodeTree * root;
	} Tree;

typedef
	struct NodeList {
		File * file;
		struct NodeList * next;
	} NodeList;

typedef
	struct {
		NodeList * head;
	} List;

/* Inicializa um ponteiro para a árvore */
Tree* createTree();

/* Inicializa um ponteiro para lista */
List* createList();

/* Cria um nó da árvore a partir da informação de um arquivo */
NodeTree* createNodeTree(File*);

/* Cria um nó da lista a partir da informação de um arquivo */
NodeList* createNodeList(File*);

/* Pega a extrema esquerda da árvore parametrizada */
NodeTree* minValue(NodeTree*);

/* Insere um valor de file na lista */
void insertFileList(List**, File*);

/* Retorna zero caso a lista tenha elementos e diferente de zero caso esteja vazia */
int empty(List*);

/* Libera recursivamente os nós de uma árvore */
void freeNodeTree(NodeTree**);

/* Libera recursivamente os nós de uma lista */
void freeNodeList(NodeList**);

/* Libera o ponteiro de árvore */
void freeTree(Tree**);

/* Libera o ponteiro de lista */
void freeList(List**);

#endif