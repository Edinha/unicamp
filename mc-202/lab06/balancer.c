/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "balancer.h"

/* Implementação dos métodos */

NodeTree * rightRotate(NodeTree * root) {
	if (!root || !root->left) {
		return root;
	}

	NodeTree * x = root->left;
	root->left = x->right;
	x->right = root;
	return x;
}

NodeTree * leftRotate(NodeTree * root) {
	if (!root || !root->right) {
		return root;
	}

	NodeTree * x = root->right;
	root->right = x->left;
	x->left = root;
	return x;
}