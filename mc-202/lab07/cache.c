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

Cache createCache(int number) {
	Cache cache;
	cache.number = number;
	cache.priority = ZERO_INIT;
	return cache;
}

int compare(Cache first, Cache second) {
	if (first.priority < second.priority) {
		return LESSER;
	}

	if (first.priority > second.priority) {
		return GREATER;
	}

	return EQUALS;
}

void emptyInit(Cache * cache) {
	cache->number = INVALID_NUMBER_INIT;
	cache->priority = ZERO_INIT;
}

void higher(Cache * cache) {
	cache->priority++;
}

void lower(Cache * cache) {
	cache->priority--;
}

void freeSearchElement(SearchElement ** element) {
	free(*element);
}