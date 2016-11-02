/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "list.h"

/* Implementação dos métodos */
List * createList() {
	List * list = malloc(sizeof(List));
	list->head = list->tail = NULL;
	return list;
}

NodeList * createNodeList(int appearance) {
	NodeList * node = malloc(sizeof(NodeList));
	node->appearance = appearance;
	node->next = NULL;
	return node;
}

void insertList(List ** list, int appearance) {
	NodeList * node = createNodeList(appearance);

	if (!(*list)->head) {
		(*list)->head = (*list)->tail = node;
		return;
	}

	(*list)->tail->next = node;
	(*list)->tail = node;
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