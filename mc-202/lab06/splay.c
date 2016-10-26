/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

/* Implementacao dos metodos */

#include "splay.h"

NodeTree * splay(NodeTree * root, String key) {
	if (!root) {
		return root;
	}

	int cmp = compare(root->ingredient, key);

	if (!cmp) {
		return root;
	}

	if (cmp > 0) {
		if (!root->left) {
			return root;
		}

		cmp = compare(root->left->ingredient, key);

		if (cmp > 0) {
			root->left->left = splay(root->left->left, key);
			root = rightRotate(root);
		} else {
			root->left->right = splay(root->left->right, key);
			if (root->left->right) {
				root->left = leftRotate(root->left);
			}
		}

		return !root->left ? root: rightRotate(root);
	} else {
		if (!root->right) {
			return root;
		}

		cmp = compare(root->right->ingredient, key);

		if (cmp > 0) {
			root->right->left = splay(root->right->left, key);
			if (!root->right->left) {
				root->right = rightRotate(root->right);
			}
		} else {
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		return !root->right ? root: leftRotate(root);
	}
}

NodeTree * search(Tree * tree, String key) {
	return splay(tree->root, key);
}

NodeTree * insert(NodeTree * root, String key) {
	int cmp;
	Ingredient * i = createIngredient(key);

	if (!root) {
		return createNodeTree(i);
	}

	root = splay(root, key);
	cmp = compare(root->ingredient, key);

	if (!cmp) {
		freeIngredient(&i);
		return root;
	}

	NodeTree * newNode = createNodeTree(i);

	if (cmp > 0) {
		newNode->right = root;
		newNode->left = root->left;
		root->left = NULL;
	} else {
		newNode->left = root;
		newNode->right = root->right;
		root->right = NULL;
	}

	return newNode;
}

void insertTree(Tree * tree, String key) {
	tree->root = insert(tree->root, key);
}