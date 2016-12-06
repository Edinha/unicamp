/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#define ERROR_MESSAGE "erro\n"

#include "table.h"
#include "stack.h"

/* Esse arquivo conterá as definições para as funções de leitura do programa */

/* Lê uma entrada inteira do programa */
void readInt(int*);

/* Lê uma entrada inteira do programa */
void readLong(unsigned long*);

/* Lê uma entrada de String do texto */
void readString(String);

/* Retorna caso o char seja o final de uma String */
int isStringEnd(char);

/* Inicializa a String prestes a ser lida */
void clearString(String);

/* Printa a mensagem de erro caso nao haja caminho */
void printError();

/* A partir da ultima e primeira palavras da busca, printa o caminho a partir de uma pilha ou erro caso o caminho não exista */
void printWay(Word*, Word*);

#endif