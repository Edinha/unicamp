#include "reading.h"

/* Implementação das funções */

void readInt(int * i) {
	scanf("%d ", i);
}

void readChar(char * c) {
	scanf("%c ", c);
}

int readInitialList(List ** list) {
	int listSize, 
		actual, 
		requests, 
		i;

	readInt(&listSize);
	readInt(&requests);

	for (i = 0; i < listSize; i++) {
		readInt(&actual);
		insert(actual, list);
	}

	// Reinicializa o custo da lista para as inserções iniciais
	(*list)->allCosts = 0;

	return requests;
}

void readRequests(List ** list, int requests) {
	int actual, i;
	char operation;

	for (i = 0; i < requests; i++) {
		readChar(&operation);
		readInt(&actual);

		applyOperation(list, operation, actual);
	}
}

void applyOperation(List ** list, char operation, int actual) {
	switch (operation) {
		case INSERT: 
			insert(actual, list);
			break;
		case FIND:
			find(actual, list);
			break;
		case REMOVE:
			removeList(actual, list);
			break;
		default:
			break;
	}
}

void printList(List ** list) {
	Node * actual = (*list)->first;

	printf("%d\n", (*list)->allCosts);
	
	for (; actual != NULL; actual = actual->next) {
		printf("%d ", actual->key);
	}

	printf("\n");
}
