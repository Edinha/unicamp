/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "client.h"

/* Implementação dos métodos  */

Client * createClient(int sequential) {
	Client * client = malloc(sizeof(Client));
	client->sequential = sequential;
	client->overflow = 0;
	return client;
}

void overflow(Client ** client, int overflow) {
	(*client)->overflow += overflow;
}

void freeClient(Client ** client) {
	free(*client);
}