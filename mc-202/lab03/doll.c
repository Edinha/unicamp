/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "doll.h"

/* Implementação dos métodos */

/* Método para inicializar a boneca de matrioshka */
void initDoll (Doll ** doll) {
	(*doll) = malloc(sizeof(Doll));
	(*doll)->size = 0;
	(*doll)->color = NO_COLOR;
	(*doll)->innerDolls = malloc(sizeof(List));
	(*doll)->innerDolls->first = NULL;
	(*doll)->innerDolls->count = 0;
}

/* Adiciona uma boneca como filha da outra */
void incubate (Doll * child, List ** innerDolls) {
	void * value = (void*) (child);
	Node * new = createNode(value);

	new->next = (*innerDolls)->first;
	(*innerDolls)->first = new;
	(*innerDolls)->count++;
}

/* Método faz recursivamente o free para liberar todas as bonecas e suas filhas */
void freeDolls (Doll * doll) {
	if (doll == NULL) {
		return;
	}

	Node * n = doll->innerDolls->first;
	if (n == NULL) {
		free(doll);
		return;
	}

	for (; n != NULL; n = n->next) {
		freeDolls((Doll*) n->value);
	}

	free(doll);
}