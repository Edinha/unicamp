/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

#include "doll.h"

/* Serão aqui descritas as definições das funções de leitura do programa, bem como
 * definições de constantes importantes para o fluxo.
 */

#define ERROR_MESSAGE "sequencia invalida ou nao pode colorir\n"

/* Lê um inteiro no parâmetro passado */
void readInt (int*);

/* Lê o vetor de entrada do arquivo, bem como seu tamanho e o retorna */
int readArrayFromFile (int**);

/* Método que criará a relação entre as bonecas da entrada e retornará caso aconteca erro de leitura */
void createDollsRelation (Doll**);

/* Método que verifica se o número é negativo, indicando começo de nova boneca */
bool isStartOfNewDoll (int);

/* Monta a pilha de bonecas a partir do vetor de entrada e retorna aquela que incuba todas */
Doll* incubateEntryDolls (int**, int);

#endif
