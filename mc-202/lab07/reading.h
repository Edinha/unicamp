/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include "heap.h"

/* Esse arquivo conterá as definições para as funcoes de leitura do programa
 */

/* Le uma entrada de um inteiro e armazena no ponteiro parametrizado */
void readInt(int*);

/* Le a primeira linha da entrada nas variaveis parametrizadas */
void readFirstLine(int*, int*);

/* Le as entradas e as aplica no heap */
void readEntry();

/* Printa a resposta a partir da contagem */
void printResponse();

#endif