/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readAllClientRequests(Tree * ingredients) {
	String ingredientName;
	int clockTime,
		sequential,
		overflowTimeTotal = 0,
		overflowTimeIngredient = 0;

	Queue * waitingQueue = createQueue();

	sequential = 1;
	while (scanf("%d", &clockTime) == 1) {
		Client * client = createClient(sequential);

		while (scanf("%*[ ]%[^ \r\n]", ingredientName) == 1) {
			// TODO ver alocação das porções de ingredientes
			overflowTimeIngredient = availabilityOfIngredient(ingredients, ingredientName, clockTime, &client->portions);

			if (overflowTimeIngredient > overflowTimeTotal) {
				overflowTimeTotal = overflowTimeIngredient;
			}
		}

		if (overflowTimeTotal) {
			overflow(&client, overflowTimeTotal);
			queue(&waitingQueue, client);

			// TODO retirar alguém da Queue de espera para assar
			// Client * otherClient = dequeue(&waitingQueue);
		} else {
			// TODO fry this client pizza
		}

		sequential++;
	}
}

void printOrder(Client * client) {
	printf("%d ", client->sequential);
}