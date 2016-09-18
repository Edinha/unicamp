/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef BUILDER_H
#define BUILDER_H

#include "doll.h"

/* Serão aqui descritas as definições das funções de montagem da relação entre as
 * bonecas da entrada, incubando suas filhas de acordo com a pilha montada
 */

/* Monta a pilha de bonecas a partir do vetor de entrada e retorna aquela que incuba todas */
Doll* incubateEntryDolls (int**, int);

/* Método que verifica se o número é negativo, indicando começo de nova boneca */
bool isStartOfNewDoll (int);

#endif
