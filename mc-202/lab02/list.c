#include "list.h"
#include <stdlib.h>

/* Implementação dos métodos da lista */

Node * createNode(int key) {
	Node * node = malloc(sizeof(Node));
	node->key = key;
	node->next = NULL;
	return node;
}

void init(List * list) {
	list = malloc(sizeof(List));
	list->first = NULL;
	list->allCosts = 0;
}

void insert(int key, List * list, int transpositionValue) {
	Node * new = createNode(key), 
		 * actual;
	
	int cost = 0;

	if (list->first == NULL) {
		list->first = new;
		list->allCosts++;
		return;
	}

	for (actual = list->first; actual->next != NULL; cost++) {
		actual = actual->next;
	}

	actual->next = new;
	list->allCosts += cost;

	if (transpositionValue == TR) {
		transposition(&actual, &actual->next);
	}
}

void find(int key, List * list, int transpositionValue) {
	Node * actual,
		 * previous;

	int cost = 0;

	previous = NULL;
	actual = list->first;

	for (; actual != NULL; cost++) {
		if (actual->key == key) {
			break;
		}

		previous = actual;
		actual = actual->next;
	}

	if (transpositionValue == TR) {
		transposition(&previous, &actual);
	} else if (transpositionValue == MTF) {
		transposition(&list->first, &actual);
	}

	list->allCosts += cost;
}

void remove(int key, List * list) {
	Node * actual,
		 * previous;

	int cost = 0;

	if (list->first->key == key) {
		actual = list->first;
		list->first = actual->next;
		free(actual);
		list->allCosts++;
		return;
	}

	previous = list->first;
	actual = previous->next;
	cost++;

	for (; actual != NULL; cost++) {
		if (actual->key == key) {
			previous->next = actual->next;
			free(actual);
			break;
		}

		previous = actual;
		actual = actual->next;
	}

	list->allCosts += cost;
}

void transposition(Node ** previous, Node ** actual) {
	int aux = (*previous)->key;
	(*previous)->key = (*actual)->key;
	(*actual)->key = aux;
}
