/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "list.h"

/* Implementação dos métodos de node.c */

List * createList() {
	List * list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

NodeList * createNodeList(Portion * portion) {
	NodeList * node = malloc(sizeof(NodeList));
	node->portion = portion;
	node->next = NULL;
	return node;
}

void insertList(List ** list, Portion * portion) {
	NodeList * newNode = createNodeList(portion);
	newNode->next = (*list)->head;
	(*list)->head = newNode;
}

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
	free(*node);
}

void freeList(List ** list) {
	freeNodeList(&(*list)->head);
	free(*list);
}