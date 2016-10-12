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
	list->head = NULL;
	return list;
}

NodeTree* createNodeTree(File * file) {
	NodeTree * node = malloc(sizeof(NodeTree));
	node->height = 1;
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
	NodeTree * current = root;
	while (current->left) {
		current = current->left;
	}

	return current;
}

void insertFileList(List ** list, File * file) {
	NodeList * newNode = createNodeList(file);
	newNode->next = (*list)->head;
	(*list)->head = newNode;
}

int empty(List * list) {
	return !list->head;
}

int height(NodeTree * root) {
	if (!root) {
		return 0;
	}

	return root->height;
}

int factor(NodeTree * root) {
	if (!root) {
		return 0;
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

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
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