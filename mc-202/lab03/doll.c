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
	initStack(&(*doll)->innerDolls);
}

/* Empilha a boneca filha na pai */
void incubate (Doll ** child, Doll ** parent) {
	void * value = (void*) (*child);
	push(value, &(*parent)->innerDolls);
}
