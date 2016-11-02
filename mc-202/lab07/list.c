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
	(*list)->tail->next = node;
	(*list)->tail = node;
}

int findNextAppearance(List ** list, int position) {
	if (!(*list)) {
		return -1;
	}

	NodeList * node = (*list)->head;

	for (; node ;) {
		if (node->appearance > position) {
			return node->appearance;
		}

		(*list)->head = (*list)->head->next;
		free(node);
		node = (*list)->head;
	}

	return -1;
}

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
	free(*node);
}

void freeList(List ** list) {
	if (!(*list)) {
		return;
	}

	freeNodeList(&(*list)->head);
	free(*list);
}