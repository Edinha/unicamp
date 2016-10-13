/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "nodes.h"

/* Implementação dos métodos */

Tree* createTree() {
	Tree * tree = malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

NodeTree* createNodeTree(File * file) {
	NodeTree * node = malloc(sizeof(NodeTree));
	node->file = file;
	node->left = node->right = NULL;
	node->height = INITIAL_COUNT;
	return node;
}

NodeTree* minValue(NodeTree * root) {
	NodeTree * current = root;
	while (current->left) {
		current = current->left;
	}

	return current;
}

int height(NodeTree * root) {
	if (!root) {
		return EMPTY_COUNT;
	}

	return root->height;
}

int factor(NodeTree * root) {
	if (!root) {
		return EMPTY_COUNT;
	}

	return height(root->left) - height(root->right);
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void updateHeight(NodeTree ** node) {
	if (!(*node)) {
		return;
	}

	(*node)->height = max(height((*node)->left), height((*node)->right)) + 1;
}

void freeNodeTree(NodeTree ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeTree(&(*node)->left);
	freeNodeTree(&(*node)->right);
	freeFile(&(*node)->file);
	free(*node);
}

void freeTree(Tree ** tree) {
	freeNodeTree(&(*tree)->root);
	free(*tree);
}