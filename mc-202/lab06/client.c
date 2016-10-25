/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

/* Implementacao dos metodos */

#include "client.h"

Client * createClient(int sequential) {
	Client * client = malloc(sizeof(Client));
	client->sequential = sequential;
	return client;
}

void freeClient(Client ** client) {
	free(*client);
}