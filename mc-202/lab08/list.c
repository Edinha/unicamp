/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "list.h"

/* Implementação dos métodos */

Continuation* createContinuation(Word * word) {
	Continuation * continuation = malloc(sizeof(Continuation));
	continuation->count = ZERO_INIT;
	continuation->word = word;
	return continuation;
}

void raise(Continuation ** continuation) {
	(*continuation)->count++;
}

int equals(Continuation * first, Continuation * second) {
	return !compare(first->word->id, second->word->id);
}

void freeContinuation(Continuation ** continuation) {
	free(*continuation);
}

List* createList() {
	List * list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

NodeList* createNodeList(Continuation * continuation) {
	NodeList * node = malloc(sizeof(NodeList));
	node->continuation = continuation;
	node->next = NULL;
	return node;
}

void insertList(List ** list, Continuation * continuation) {

	if (!(*list)->head) {
		(*list)->head = createNodeList(continuation);
		return;
	}

	NodeList * node = (*list)->head;

	for (;;) {
		if (equals(node->continuation, continuation)) {
			freeContinuation(&continuation);
			raise(&node->continuation);
			return;
		}

		if (!node->next) {
			node->next = createNodeList(continuation);
			return;
		}

		node = node->next;
	}
}

Continuation* find(List * list, String id) {
	if (!list) {
		return NULL;
	}

	NodeList * node = list->head;
	Continuation * continuation = NULL;

	for (; node ; node = node->next) {
		continuation = node->continuation;
		if (!compare(continuation->word->id, id)) {
			return continuation;
		}
	}

	return NULL;
}

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
	freeContinuation(&(*node)->continuation);
	free(*node);
}

void freeList(List ** list) {
	if (!list || !(*list)) {
		return;
	}

	freeNodeList(&(*list)->head);
	free(*list);
}