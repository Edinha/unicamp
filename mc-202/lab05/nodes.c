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

List* createList() {
	List * list = malloc(sizeof(List));
	list->head = list->tail = NULL;
	return list;
}

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

void insertFileList(List * list, File * file) {
	NodeList * newNode = createNodeList(file);

	if (!list->head) {
		list->head = list->tail = newNode;
		return;
	}

	list->tail->next = newNode;
	list->tail = newNode;
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

void freeTree(Tree ** tree) {
	freeNodeTree(&(*tree)->root);
	free(*tree);
}

void freeList(List ** list) {
	freeNodeList(&(*list)->head);
	free(*list);
}