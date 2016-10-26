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

List * createList() {
	List * list = malloc(sizeof(List));
	list->head = list->tail = NULL;
	return list;
}

NodeList * createNodeList(Client * client) {
	NodeList * node = malloc(sizeof(NodeList));
	node->client = client;
	node->next = NULL;
	return node;
}

void insertTail(List ** list, Client * client) {
	NodeList * newNode = createNodeList(client);

	if (!(*list)->head) {
		(*list)->head = newNode;
		(*list)->tail = newNode;
		return;
	}

	(*list)->tail->next = newNode;
	(*list)->tail = (*list)->tail->next;
}

void insertHead(List ** list, Client * client) {
	NodeList * newNode = createNodeList(client);
	newNode->next = (*list)->head;
	(*list)->head = newNode;
}

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
	freeClient(&(*node)->client);
	free(*node);
}

void freeList(List ** list) {
	freeNodeList(&(*list)->head);
	free(*list);
}