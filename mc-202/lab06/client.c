/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "client.h"

/* Implementação dos métodos  */

Client * createClient(int sequential) {
	Client * client = malloc(sizeof(Client));
	client->sequential = sequential;
	client->cookTime = 0;
	client->portions = createList();
	return client;
}

void overflow(Client ** client, int cookTime) {
	if ((*client)->cookTime < cookTime) {
		(*client)->cookTime = cookTime;
	}
}

void freeClientReffilingPortions(Client ** client) {
	freeList(&(*client)->portions, (*client)->cookTime);
	free(*client);
}