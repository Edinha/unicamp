/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "list.h"

/* Implementação dos métodos */

NodeList* createNodeList(int count) {
	NodeList * node = malloc(sizeof(NodeList));
	node->count = count;
	node->next = NULL;
	return node;
}

List* createList() {
	List * list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

void insert(List ** list, int count) {
	if (!list || !(*list)) {
		return;
	}

	if (!(*list)->head) {
		(*list)->head = createNodeList(count);
		return;
	}

	NodeList * node = (*list)->head;

	for (;; node = node->next) {
		if (node->count == count) {
			return;
		}

		if (!node->next) {
			node->next = createNodeList(count);
			return;
		}
	}
}

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
	free(*node);
}

void freeList(List ** list) {
	if (!list || !(*list)) {
		return;
	}

	freeNodeList(&(*list)->head);
	free(*list);
}
