/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Esse arquivo conterá as definições para a estrutura de ingredientes da pizzaria
 * Bem como funções de comparação e criação de ingredientes
 */

#define PORTION_MAX_COUNT 2
#define INITIAL_UNFROZEN_CLOCK 0
#define INITIAL_PORTIONS_LIFESPAN -2
#define UNFROZEN_COOLDOWN 2

/* Definição de uma String */
typedef char String[100];

/* Definição do estado da porção */
typedef
	enum {
		FROZEN,
		READY
	} State;

/* Define uma estrutura para porção. guardando o tempo até descongelamento e tempo de vida do ingrediente*/
typedef
	struct {
		State state;
		int unfrozen,
			lifespan;
	} Portion;

/* Define os ingredientes e suas porções disponíveis */
typedef
	struct {
		String name;
		Portion portions[PORTION_MAX_COUNT];
	} Ingredient;

/* Cria um ponteiro para um ingrediente a partir do nome */
Ingredient* createIngredient(String);

/* Compara o nome do ingrediente com uma String parametrizado, retornando 0 caso sejam iguais,
 * maior do que 0 caso ingrediente tenha nome maior e menor do que 0 caso contrário.
 */
int compare(Ingredient*, String);

/* Reabastece uma porção do ingrediente a partir do horário parametrizado */
void refill(Portion*, int);

/* Muda o estado da porção de congelado para pronto caso já seja hora */
void unfrozenIfPossible(Portion*, int);

/* Retorna verdadeiro caso o estado da porção seja congelado */
int isFrozen(Portion*);

/* Libera espaço de um ingrediente */
void freeIngredient(Ingredient**);

#endif