/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "balancer.h"

/* Implementação dos métodos */

NodeTree * insertRotationCases(NodeTree * root, Cache * cache) {
	int comparison,
		balanceFactor;

	balanceFactor = factor(root);

	if (root->left) {
		comparison = compareNumber(root->left->cache, cache);

		// Fator maior que 1, desbalanceado para a esquerda
		if (balanceFactor > 1) {
			// Caso em que o nome do arquivo é menor, rotação a direita
			if (comparison > 0) {
				return rightRotate(root);
			}

			// Caso em que o nome do arquivo é maior, dupla rotação esquerda-direita
			if (comparison < 0) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
		}
	}

	if (root->right) {
		comparison = compareNumber(root->right->cache, cache);

		// Fator menor que -1, desbalanceado para a direita
		if (balanceFactor < -1) {
			// Caso em que o nome do arquivo é maior, rotação a esquerda
			if (comparison < 0) {
				return leftRotate(root);
			}

			// Caso em que o nome do arquivo é menor, dupla rotação direita-esquerda
			if (comparison > 0) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}
	}

	return root;
}

NodeTree * rightRotate(NodeTree * root) {
	if (!root) {
		return root;
	}

	if (!root->left) {
		return root;
	}

	NodeTree * x = root->left,
			 * temp = x->right;

	x->right = root;
	root->left = temp;

	updateHeight(&x);
	updateHeight(&root);

	return x;
}

NodeTree * leftRotate(NodeTree * root) {
	if (!root) {
		return root;
	}

	if (!root->right) {
		return root;
	}

	NodeTree * x = root->right,
			 * temp = x->left;

	x->left = root;
	root->right = temp;

	updateHeight(&x);
	updateHeight(&root);

	return x;
}