/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef NODES_H
#define NODES_H

#include "cache.h"

/* Esse arquivo conterá as definições para a estrutura de nós usadas na implementação da
 * base estrutural da árvore AVL
 */

/* Define valores para contagem de altura */
#define EMPTY_COUNT 0
#define INITIAL_COUNT 1

typedef
	struct NodeTree {
		int height;
		Cache * cache;
		struct NodeTree * left;
		struct NodeTree * right;
	} NodeTree;

typedef
	struct {
		NodeTree * root;
	} Tree;

/* Inicializa um ponteiro para a árvore */
Tree* createTree();

/* Cria um nó da árvore a partir da informação de um cache */
NodeTree* createNodeTree(Cache*);

/* Retorna a altura de um nó da árvore */
int height(NodeTree* root);

/* Retorna o fator de balanceamento da árvore */
int factor(NodeTree*);

/* Retorna o máximo valor entre dois inteiros */
int max(int, int);

/* Atualiza o valor da altura de um nó */
void updateHeight(NodeTree**);

/* Libera recursivamente os nós de uma árvore */
void freeNodeTree(NodeTree**);

/* Libera o ponteiro de árvore */
void freeTree(Tree**);

#endif