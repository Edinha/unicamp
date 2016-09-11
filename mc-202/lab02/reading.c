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
		transpositionAux,
		i;

	readInt(&listSize);
	readInt(&requests);

	// Tira o valor da transposição da lista para a lista inicial não ser transposta quando inserida
	transpositionAux = (*list)->transpositionValue;
	(*list)->transpositionValue = NO_TRANSPOSITION;

	for (i = 0; i < listSize; i++) {
		readInt(&actual);
		insert(actual, list);
	}

	// Volta o valor da transposição da lista ao original
	(*list)->transpositionValue = transpositionAux;

	// Reinicializa o custo da lista para as inserções iniciais
	(*list)->allCosts = 0;

	return requests;
}

void initRequests(Request ** requests, int size) {
	*requests = malloc(sizeof(Request) * size);
	for (int i = 0; i < size; i++) {
		(*requests)[i].key = 0;
		(*requests)[i].operation = '\0';
	}
}

Request readRequest() {
	Request request;
	readChar(&request.operation);
	readInt(&request.key);
	return request;
}

void readRequests(Request ** requests, int size) {
	for (int i = 0; i < size; i++) {
		(*requests)[i] = readRequest();
	}
}

void applyRequests(List ** list, Request ** requests, int size) {
	int i;
	Request request;
	
	for (i = 0; i < size; i++) {
		request = (*requests)[i];

		switch (request.operation) {
			case INSERT: 
				insert(request.key, list);
				break;
			case FIND:
				find(request.key, list);
				break;
			case REMOVE:
				removeList(request.key, list);
				break;
			default:
				break;
		}
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
