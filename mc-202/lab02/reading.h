#ifndef READING_H
#define READING_H

#include "list.h"

/* Define as operações de entrada do sistema para seus caractéres */
#define INSERT 'i'
#define FIND 'a'
#define REMOVE 'r'

typedef
	struct {
		int key;
		char operation;
	} Request;

/* Lê um número inteiro da entrada */
void readInt(int*);

/* Lê um char da entrada */
void readChar(char*);

/* Ler a lista inicial da entrada e retorna o número de requisições */
int readInitialList(List**);

/* Inicializa o ponteiro de requisições da entrada */
void initRequests(Request**, int);

/* Lê uma única linha de requisição e retorna seu valor */
Request readRequest();

/* Lê todas as requisições da entrada no ponteiro parametrizado */
void readRequests(Request**, int);

/* Aplica todas requisições a listagem */
void applyRequests(List**, Request**, int);

/* Escreve a listagem e seu custo após as operações na tela */
void printList(List**);

#endif