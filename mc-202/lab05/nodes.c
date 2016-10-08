/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "nodes.h"

/* Implementação dos métodos */

NodeTree* createNodeTree(File * file) {
	NodeTree * node = malloc(sizeof(NodeTree));
	node->file = file;
	node->left = node->right = NULL;
	return node;
}

NodeList* createNodeList(File * file) {
	NodeList * node = malloc(sizeof(NodeList));
	node->file = file;
	node->next = NULL;
	return node;
}

NodeTree* minValue(NodeTree * root) {
	NodeTree * current;

	while (current->left) {
		current = current->left;
	}

	return current;
}

void freeNodeTree(NodeTree ** node) {
	if (!node) {
		return;
	}

	freeNodeTree(&(*node)->left);
	freeNodeTree(&(*node)->right);
	freeFile(&(*node)->file);
	free(*node);
}

void freeNodeList(NodeList ** node) {
	if (!node) {
		return;
	}

	freeNodeList(&(*node)->next);
	freeFile(&(*node)->file);
	free(*node);
}