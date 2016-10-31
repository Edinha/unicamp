/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "cache.h"

/* Implementacao dos metodos */

SearchElement * createSearchElement(Cache * cache, int position) {
	SearchElement * element = malloc(sizeof(SearchElement));
	element->cache = cache;
	element->position = position;
	return element;
}

Cache createCache(int number, int priority) {
	Cache cache;
	cache.number = number;
	cache.priority = priority;
	return cache;
}

int compare(Cache first, Cache second) {
	if (first.priority < second.priority) {
		return LESSER;
	}

	return GREATER;
}

int sameNumber(Cache first, Cache second) {
	return (first.number == second.number);
}

void emptyInit(Cache * cache) {
	cache->number = INVALID_NUMBER_INIT;
	cache->priority = ZERO_INIT;
}

void updatePriority(Cache * cache, int newPriority) {
	cache->priority = newPriority;
}

void freeSearchElement(SearchElement ** element) {
	free(*element);
}