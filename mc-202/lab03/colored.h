/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef COLORED_H
#define COLORED_H

#include "doll.h"

/* Define a estrutura que guardará o resultado das pinturas de acordo com o
 * número da boneca e validará a entrada para manter esses conjuntos iguais.
 */

#define ERROR_COLORING 1
#define SUCESS_COLORING 0
#define SUCESS_MESSAGE "sequencia valida pode ser colorida\n"

typedef
	struct {
		int number;
		Color color;
	} Colored;

int insertColoredDollOnList (Doll*, List**);

/* Cria uma relação de cor e número a partir da boneca em parâmetro */
Colored * createColored (Doll*);

/* Verifica se as duas estruturas possuem o mesmo número e cores diferentes para invalidar
 * a pintura das bonecas
 */
bool sameNumberDifferentColor (Colored*, Colored*);

/* Imprime a resposta do programa */
void response (List**);

#endif