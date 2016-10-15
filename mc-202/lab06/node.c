/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "node.h"

/* Implementação dos métodos de node.c */

Tree* createTree() {
	Tree * tree = malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

NodeTree* createNodeTree(Ingredient * ingredient) {
	NodeTree * node = malloc(sizeof(NodeTree));
	node->ingredient = ingredient;
	node->left = node->right = NULL;
	// node->height = INITIAL_COUNT;
	return node;
}

void freeNodeTree(NodeTree ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeTree(&(*node)->left);
	freeNodeTree(&(*node)->right);
	freeIngredient(&(*node)->ingredient);
	free(*node);
}

void freeTree(Tree ** tree) {
	freeNodeTree(&(*tree)->root);
	free(*tree);
}

// int height(NodeTree * root) {
// 	if (!root) {
// 		return EMPTY_COUNT;
// 	}

// 	return root->height;
// }

// int factor(NodeTree * root) {
// 	if (!root) {
// 		return EMPTY_COUNT;
// 	}

// 	return height(root->left) - height(root->right);
// }

// int max(int a, int b) {
// 	return (a > b) ? a : b;
// }

// void updateHeight(NodeTree ** node) {
// 	if (!(*node)) {
// 		return;
// 	}

// 	(*node)->height = max(height((*node)->left), height((*node)->right)) + 1;
// }

// NodeTree* minValue(NodeTree * root) {
// 	NodeTree * current = root;
// 	while (current->left) {
// 		current = current->left;
// 	}

// 	return current;
// }