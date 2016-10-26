/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readAllClientRequests(Tree * ingredients) {
	String ingredientName;
	int sequential,
		clockTime,
		overflowTime;

	// List * waitingList = createList();

	sequential = 1;
	while (scanf("%d", &clockTime) == 1) {
		Client * client = createClient(sequential);

		while (scanf("%*[ ]%[^ \r\n]", ingredientName) == 1) {
			// TODO fazer algo com esses ingredientes da massa aqui
			availabilityOfIngredient(ingredients, ingredientName, clockTime, &overflowTime);

			// TODO caso os ingredientes não estejam prontos ainda, inserir na lista de espera
			// insertHead(&list, client, overflow);
			overflow(&client, overflowTime);
		}

		sequential++;
	}
}