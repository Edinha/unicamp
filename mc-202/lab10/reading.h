/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include "table.h"

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

#endif