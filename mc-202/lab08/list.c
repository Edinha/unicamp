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
	int nextCmp = -1, previousCmp = -1;

	// Faz uma comparação entre todas as possibilidades de adjacência para dizer se os pares são iguais
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
}

int find(List ** adjacencies, Word * previous, Word * next) {
	int count = ZERO_INIT;

	if (!adjacencies || !(*adjacencies)) {
		return ZERO_INIT;
	}

	Word * looked = NULL;
	Adjacency * adjacency = NULL;
	NodeList * node = (*adjacencies)->head;

	if (!previous && !next) {
		return ZERO_INIT;
	}

	// Faz a busca apenas comparando os próximos como não há anterior
	if (!previous) {
		for (; node ; node = node->next) {
			looked = node->adjacency->next;
			if (looked && compareWords(looked, next)) {
				count++;
			}
		}

		return count;
	}

	// Faz a busca apenas comparando os anteriores como não há próximo
	if (!next) {
		for (; node ; node = node->next) {
			looked = node->adjacency->previous;
			if (looked && compareWords(looked, previous)) {
				return node->adjacency->count;
			}
		}

		return ZERO_INIT;
	}

	adjacency = createAdjacency(next, previous);

	// Faz a busca pela adjacência completa
	for (; node ; node = node->next) {
		if (equals(node->adjacency, adjacency)) {
			count = node->adjacency->count;
			break;
		}
	}

	freeAdjacency(&adjacency);
	return count;
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