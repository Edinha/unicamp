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

	// TODO please kill me, look at this method
	int nextCmp = -1, previousCmp = -1;

	if (first->next) {
		if (!second->next) {
			nextCmp =  0;
		} else {
			nextCmp = compareWords(first->next, second->next);
		}
	} else {
		if (second->next) {
			nextCmp = 0;
		}
	}

	if (first->previous) {
		if (!second->previous) {
			previousCmp = 0;
		} else {
			previousCmp = compareWords(first->previous, second->previous);
		}
	} else {
		if (second->previous) {
			previousCmp = 0;
		}
	}

	return nextCmp && previousCmp;
	// Certain to work but slow as f..
	// int nextEquals = !compare(first->next->id, second->next->id),
	// 	previousEquals = !compare(first->previous->id, second->previous->id);

	// return nextEquals && previousEquals;
}

Adjacency* find(List ** adjacencies, Word * previous, Word * next) {
	if (!adjacencies || !(*adjacencies)) {
		return NULL;
	}

	Word * looked = NULL;
	Adjacency * adjacency = NULL;
	NodeList * node = (*adjacencies)->head;

	if (!previous && !next) {
		return NULL;
	}

	// Faz a busca apenas comparando os próximos como não há anterior
	if (!previous) {
		for (; node ; node = node->next) {
			looked = node->adjacency->next;
			// TODO count adjacencies on other nodes on this if
			if (looked && compareWords(looked, next)) {
				return node->adjacency;
			}
		}

		return NULL;
	}

	// TODO maybe function pointers for this
	if (!next) {
		for (; node ; node = node->next) {
			looked = node->adjacency->previous;
			if (looked && compareWords(looked, previous)) {
				return node->adjacency;
			}
		}

		return NULL;
	}

	adjacency = createAdjacency(next, previous);

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