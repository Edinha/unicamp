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

/* Lê um inteiro no parâmetro passado */
void readInt (int*);

/* Lê o vetor de entrada do arquivo, bem como seu tamanho e o retorna */
int readArrayFromFile (int**);

/* Método que criará a relação entre as bonecas da entrada */
void createDollsRelation ();

/* Método que verifica se o número é negativo, indicando começo de nova boneca */
bool isStartOfNewDoll (int);

#endif
