/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "list.h"

/* Implementação dos métodos */

Adjacency* createAdjacency(Word * next, Word * previous) {
	Adjacency * a = malloc(sizeof(Adjacency));
	a->count = COUNT_INIT;
	a->next = next;
	a->previous = previous;
	return a;
}

void raise(Adjacency ** adjacency) {
	(*adjacency)->count++;
}

int equals(Adjacency * first, Adjacency * second) {
	// Maybe compare pointers of words is the way... or maybe they hashs

	int nextEquals = !compare(first->next->id, second->next->id),
		previousEquals = !compare(first->previous->id, second->previous->id);

	return nextEquals && previousEquals;
}

void freeAdjacency(Adjacency ** a) {
	free(*a);
}

List* createList() {
	List * list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

NodeList* createNodeList(Adjacency * adjacency) {
	NodeList * node = malloc(sizeof(NodeList));
	node->adjacency = adjacency;
	node->next = NULL;
	return node;
}

void addAdjacency(List ** list, Adjacency * adjacency) {
	if (!(*list)->head) {
		(*list)->head = createNodeList(adjacency);
		return;
	}

	NodeList * node = (*list)->head;

	for (;;) {
		if (equals(node->adjacency, adjacency)) {
			freeAdjacency(&adjacency);
			raise(&node->adjacency);
			return;
		}

		if (!node->next) {
			node->next = createNodeList(adjacency);
			return;
		}

		node = node->next;
	}
}

// // TODO will fix this in a mean way
// Adjacency* find(List * list, String id) {
// 	if (!list) {
// 		return NULL;
// 	}

// 	NodeList * node = list->head;
// 	Continuation * continuation = NULL;

// 	for (; node ; node = node->next) {
// 		continuation = node->continuation;
// 		if (!compare(continuation->word->id, id)) {
// 			return continuation;
// 		}
// 	}

// 	return NULL;
// }

void freeNodeList(NodeList ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeList(&(*node)->next);
	freeAdjacency(&(*node)->adjacency);
	free(*node);
}

void freeList(List ** list) {
	if (!list || !(*list)) {
		return;
	}

	freeNodeList(&(*list)->head);
	free(*list);
}