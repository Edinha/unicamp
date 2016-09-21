/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "builder.h"

/* Implementação dos métodos */

/* Método retorna NULL caso a entrada esteja malformada */
Doll * incubateEntryDolls (int ** dollsNumbers, int size) {
	int i, actualSize, popedSize;

	Stack * numbers,
		  * dolls;

	Doll * parent,
		 * children;

	initStack(&numbers);
	initStack(&dolls);

	for (i = 0; i < size; i++) {
		actualSize = (*dollsNumbers)[i];

		// Se for o começo de uma nova boneca, empilhe suas informações
		if (isStartOfNewDoll(actualSize)) {
			Doll * actual;
			initDoll(&actual);

			actual->number = -actualSize;
			push((void*) &actual->number, &numbers);
			push((void*) actual, &dolls);

		} else {
			/* Se for o final de uma nova boneca, desempilhe suas informações e valide a entrada antes
			 * de finalmente incubar as bonecas de acordo com a entrada */

			popedSize = * ((int*) pop(&numbers));
			children = (Doll*) pop(&dolls);
			parent = (Doll*) peek(&dolls);

			// Caso o último desempilhado não corresponda em par com o atual, a entrada está malformada
			if (popedSize != actualSize) {
				return freeAll(parent, children, &numbers, &dolls);
			}

			// Caso parent NULL, a filha é teoricamente a boneca mais externa possível
			if (parent == NULL) {
				parent = children;
			} else {
				// Senão, é preciso incubar uma na outra
				incubate(children, &parent->innerDolls);
			}
		}

		// Caso acabem os números mas não é o final da leitura, a entrada está malformada
		if (empty(&numbers) && i < (size - 1)) {
			return freeAll(parent, NULL, &numbers, &dolls);
		}
	}

	// Caso após todo o algorimo ainda sobrarem números, a entrada está malformada
	if (!empty(&numbers)) {
		return freeAll(parent, children, &numbers, &dolls);
	}

	freeStack(&numbers);
	freeStack(&dolls);

	return parent;
}

bool isStartOfNewDoll (int number) {
	return (number < 0);
}

Doll * freeAll (Doll * parent, Doll * children, Stack ** numbers, Stack ** dolls) {
	freeDolls(parent);
	freeDolls(children);
	freeStack(numbers);
	freeStack(dolls);
	return NULL;
}