/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef NODE_H
#define NODE_H

#include "ingredient.h"

/* Esse arquivo conterá as definições para a estrutura de nós do programa
 * usadas na implementação da base estrutural da árvore splay
 */

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

/* Inicializa um ponteiro para a árvore */
Tree* createTree();

/* Cria um nó da árvore a partir da informação de um arquivo */
NodeTree* createNodeTree(Ingredient*);

/* Libera recursivamente os nós de uma árvore */
void freeNodeTree(NodeTree**);

/* Libera o ponteiro de árvore */
void freeTree(Tree**);

// TODO delete if its proven unnecessary methods
// /* Retorna a altura de um nó da árvore */
// int height(NodeTree* root);

// /* Retorna o fator de balanceamento da árvore */
// int factor(NodeTree*);

// /* Retorna o máximo valor entre dois inteiros */
// int max(int, int);

// /* Atualiza o valor da altura de um nó */
// void updateHeight(NodeTree**);

// /* Pega a extrema esquerda da árvore parametrizada */
// NodeTree* minValue(NodeTree*);

#endif