/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readAllClientRequests(Tree * ingredients) {
	String ingredientName;
	int clockTime,
		oldClockTime,
		sequential,
		overflowTimeTotal = 0,
		overflowTimeIngredient = 0,
		cookingTime = 0;

	Client * client = NULL;
	Queue * waitingQueue = createQueue();

	sequential = 1;
	while (scanf("%d", &clockTime) == 1) {
		client = createClient(sequential);

		// Mais de um pedido ao mesmo tempo, adicionar tempo de forno
		if (oldClockTime == clockTime) {
			cookingTime++;
		}

		while (scanf("%*[ ]%[^ \r\n]", ingredientName) == 1) {
			// TODO ver alocação das porções de ingredientes
			overflowTimeIngredient = availabilityOfIngredient(ingredients, ingredientName, clockTime + cookingTime, &client->portions);

			if (overflowTimeIngredient > overflowTimeTotal) {
				overflowTimeTotal = overflowTimeIngredient;
			}

			memset(ingredientName, 0, MAX_STRING_SIZE);
		}

		overflow(&client, clockTime, overflowTimeTotal + cookingTime);

		if (client->cookTime <= clockTime + cookingTime) {
			printOrder(client);
			freeClientReffilingPortions(&client);
		} else {
			queue(&waitingQueue, client);
			client = dequeue(&waitingQueue);

			if (client->cookTime <= clockTime + cookingTime) {
				printOrder(client);
				freeClientReffilingPortions(&client);
			} else {
				headQueue(&waitingQueue, client);
			}
		}

		overflowTimeTotal = 0;
		oldClockTime = clockTime;
		sequential++;
	}

	// TODO see cooking time of clients int this loop for personal reasons
	while ( !emptyQueue(&waitingQueue) ) {
		client = dequeue(&waitingQueue);
		printOrder(client);
		freeClientReffilingPortions(&client);
	}

	freeQueue(&waitingQueue);
}

void printOrder(Client * client) {
	printf("%d ", client->sequential);
}