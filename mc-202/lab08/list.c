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

	return (compareWords(first->next, second->next) && compareWords(first->previous, second->previous));
	// return (first->next->hash == second->next->hash) && (first->previous->hash == second->previous->hash);

	// Certain to work but slow as f..
	// int nextEquals = !compare(first->next->id, second->next->id),
	// 	previousEquals = !compare(first->previous->id, second->previous->id);

	// return nextEquals && previousEquals;
}

Adjacency* find(List ** adjacencies, Word * previous, Word * next) {
	if (!adjacencies || !(*adjacencies)) {
		return NULL;
	}

	NodeList * node = (*adjacencies)->head;

	// Faz a busca apenas comparando os próximos como não há anterior
	if (!previous) {
		for (; node ; node = node->next) {
			if (compareWords(node->adjacency->next, next)) {
				return node->adjacency;
			}
		}

		return NULL;
	}

	Adjacency * adjacency = createAdjacency(next, previous);

	// Faz a busca pela adjacência completa
	for (; node ; node = node->next) {
		if (equals(node->adjacency, adjacency)) {
			freeAdjacency(&adjacency);
			return node->adjacency;
		}
	}

	freeAdjacency(&adjacency);
	return NULL;
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