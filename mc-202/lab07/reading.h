/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include "heap.h"

/* Esse arquivo conterá as definições para as funções de leitura do programa */

/* Lê uma entrada de um inteiro e armazena no ponteiro parametrizado */
void readInt(int*);

/* Lê a primeira linha da entrada nas variáveis parametrizadas */
void readFirstLine(int*, int*);

/* Lê as entradas e as aplica no heap alocado dentro da função */
void readEntry();

/* Printa a resposta a partir da contagem */
void printResponse(int);

#endif