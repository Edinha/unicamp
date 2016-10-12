/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "balancer.h"

/* Implementação dos métodos */

NodeTree * insertRotationCases(NodeTree * root, File * file) {
	int comparison,
		balanceFactor;

	balanceFactor = factor(root);

	if (root->left) {
		comparison = compareFiles(root->left->file, file);

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
		comparison = compareFiles(root->right->file, file);

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

NodeTree * deleteRotationCases(NodeTree * root) {
	int simbilingFactor,
		balanceFactor;

	balanceFactor = factor(root);

	if (root->left) {
		simbilingFactor = factor(root->left);

		// Fator maior que 1, desbalanceado para a esquerda
		if (balanceFactor > 1) {
			// A esquerda possui desbalanceamento para a esquerda, rotacionar a direita
			if (simbilingFactor >= 0) {
				return rightRotate(root);
			}

			// A esquerda possui desbalanceamento para a direita, dupla rotação esquerda-direita
			if (simbilingFactor < 0) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
		}
	}

	if (root->right) {
		simbilingFactor = factor(root->right);

		// Fator menor que -1, desbalanceado para a direita
		if (balanceFactor < -1) {
			// A direita possui desbalanceamento para a direita, rotacionar a esquerda
			if (simbilingFactor <= 0) {
				return leftRotate(root);
			}

			// A direita possui desbalanceamento para a esquerda, dupla rotação direita-esquerda
			if (simbilingFactor > 0) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}
	}

	return root;
}

NodeTree * rightRotate(NodeTree * root) {
	NodeTree * x = root->left,
			 * temp = x->right;

	x->right = root;
	root->left = temp;

	updateHeight(&x);
	updateHeight(&root);

	return x;
}

NodeTree * leftRotate(NodeTree * root) {
	NodeTree * x = root->right,
			 * temp = x->left;

	x->left = root;
	root->right = temp;

	updateHeight(&x);
	updateHeight(&root);

	return x;
}