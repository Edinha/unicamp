/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef DOLL_H
#define DOLL_H

#include "stack.h"

/* Definições para a estrutura de cada boneca da entrada.
 * Ela conterá seu valor de tamanho, uma indentificação de sua cor e
 * uma lista de bonecas que estão dentro dela
 */

typedef
	enum {
		RED, BLUE, NO_COLOR
	} Color;

typedef
	struct {
		int count;
		Node * first;
	} List;

typedef
	struct {
		int size;
		Color color;
		List * innerDolls;
	} Doll;

/* Método para inicializar a boneca de matrioshka */
void initDoll (Doll**);

/* Método que coloca a primeira boneca no interior da lista */
void incubate (Doll*, List**);

/* Ḿétodo que irá liberar a memória das dolls */
void freeDolls (Doll*);

#endif