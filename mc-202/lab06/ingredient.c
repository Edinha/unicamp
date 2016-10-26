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
		ingredient->portions[i].unfrozen = INITIAL_UNFROZEN_CLOCK;
		ingredient->portions[i].state = READY;
		ingredient->portions[i].lifespan = INITIAL_PORTIONS_LIFESPAN;
	}

	return ingredient;
}

int compare(Ingredient * ingredient, String name) {
	return strcmp(ingredient->name, name);
}

void refill(Portion * portion, int clockTime) {
	portion->state = FROZEN;
	portion->lifespan = clockTime + UNFROZEN_COOLDOWN;
}

void unfrozenIfPossible(Portion * portion, int clockTime) {
	if (isFrozen(portion) && portion->lifespan < clockTime) {
		portion->state = READY;
	}
}

int isFrozen(Portion * portion) {
	return (portion->state == FROZEN);
}

void freeIngredient(Ingredient ** ingredient) {
	free(*ingredient);
}