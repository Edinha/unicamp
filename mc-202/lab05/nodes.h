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
	struct NodeList {
		File * file;
		struct NodeList * next;
	} NodeList;

/* Cria um nó da árvore a partir da informação de um arquivo */
NodeTree* createNodeTree(File*);

/* Cria um nó da lista a partir da informação de um arquivo */
NodeList* createNodeList(File*);

/* Pega a extrema esquerda da árvore parametrizada */
NodeTree* minValue(NodeTree*);

/* Libera recursivamente os nós de uma árvore */
void freeNodeTree(NodeTree**);

/* Libera recursivamente os nós de uma lista */
void freeNodeList(NodeList**);

#endif