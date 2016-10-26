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

	List * waitingList = createList();

	sequential = 1;
	while (scanf("%d", &clockTime) == 1) {
		Client * client = createClient(sequential);

		while (scanf("%*[ ]%[^ \r\n]", ingredientName) == 1) {
			// TODO fazer algo com esses ingredientes da massa aqui

			overflowTime = availabilityOfIngredient(ingredients, ingredientName, clockTime);


			if (overflowTime) {
				overflow(&client, overflowTime);
				insertTail(&waitingList, client);
				// TODO retirar alguém da lista de espera para assar
			} else {

			}
		}

		sequential++;
	}
}