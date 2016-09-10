#ifndef READING_H
#define READING_H

#include "list.h"
#include <stdio.h>

/* Define as operações de entrada do sistema para seus caractéres */
#define INSERT 'i'
#define FIND 'a'
#define REMOVE 'r'

/* Lê um número inteiro da entrada */
void readInt(int*);

/* Lê um char da entrada */
void readChar(char*);

/* Ler a lista inicial da entrada e retorna o número de requisições */
int readInitialList(List**);

/* Lê todas as request e as aplica */
void readRequests(List**, int);

/* Aplica uma operação a listagem de acordo com as requisições lidas */
void applyOperation(List**, char, int);

/* Escreve a listagem na tela */
void printList(List**);

#endif