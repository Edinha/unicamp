/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "client.h"

/* Implementação dos métodos  */

Client * createClient(int sequential) {
	Client * client = malloc(sizeof(Client));
	client->sequential = sequential;
	client->cookTime = client->overflowTime = 0;
	client->portions = createList();
	return client;
}

void overflow(Client ** client, int cookTime, int overflowTime) {
	if ((*client)->cookTime < cookTime) {
		(*client)->cookTime = cookTime + overflowTime;
		(*client)->overflowTime = overflowTime;
	}
}

void freeClientReffilingPortions(Client ** client) {
	freeList(&(*client)->portions, (*client)->cookTime - (*client)->overflowTime);
	free(*client);
}