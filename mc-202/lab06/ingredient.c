/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "ingredient.h"

/* Implementação dos métodos de ingredient.h */

Ingredient * createIngredient(String name) {
	Ingredient * ingredient = malloc(sizeof(Ingredient));
	strcpy(ingredient->name, name);

	for (int i = 0; i < PORTION_MAX_COUNT; i++) {
		ingredient->portions[i].unfrozen = 0;
		ingredient->portions[i].state = READY;
	}

	return ingredient;
}

int compare(Ingredient * ingredient, String name) {
	return strcmp(ingredient->name, name);
}

void freeIngredient(Ingredient ** ingredient) {
	free(*ingredient);
}