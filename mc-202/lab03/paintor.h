/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef PAINTOR_H
#define PAINTOR_H

#include "doll.h"
#include "colored.h"

/* Definições para a pintura de cores das bonecas de acordo com o números
 * da boneca e de quantas bonecas azuis existem dentro dela.
 * Define também a estrutura que guardará o resultado das pinturas de acordo com o
 * número da boneca.
 */

/* Método retorna a quantida de bonecas azuis diretamente filhas a ele */
int blueCounter (Doll**);

/* Método que define a cor das bonecas recursivamente */
int defineColorForDolls (Doll**, List**);

/* Define a cor das bonecas da listagem inteiror da boneca */
int defineColorForInnerDolls (Doll**, List**);

/* Retorna a cor de acordo com o M e N parametrizados */
Color getColor (int, int);

#endif