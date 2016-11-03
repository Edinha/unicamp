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
	if (!list || !(*list)) {
		return NO_NEXT_APPEARANCE;
	}

	/* Percorre a lista até encontrar uma apariçõ que esteja a frente da posição parametrizada
	 * Não sendo encontrada, retorna NO_NEXT_APPEARANCE */

	NodeList * node = (*list)->head;

	for (; node ;) {
		if (node->appearance > position) {
			return node->appearance;
		}

		(*list)->head = (*list)->head->next;
		free(node);
		node = (*list)->head;
	}

	return NO_NEXT_APPEARANCE;
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