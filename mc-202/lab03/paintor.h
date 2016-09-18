/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef PAINTOR_H
#define PAINTOR_H

#include "doll.h"

/* Definições para a pintura de cores das bonecas de acordo com o números
 * da boneca e de quantas bonecas azuis existem dentro dela.
 */

/* Método retorna a quantida de bonecas azuis diretamente filhas a ele */
int blueCounter (Doll**);

/* Método que define a cor das bonecas recursivamente */
void defineColorForDolls (Doll**);

/* Define a cor das bonecas da listagem inteiror da boneca */
void defineColorForInnerDolls (Doll**);

/* Retorna a cor de acordo com o M e N parametrizados */
Color getColor (int, int);

void printDolls (Doll* );

#endif