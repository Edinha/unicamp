/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef CLIENT_H
#define CLIENT_H

/* Esse arquivo conterá as definições para a estrutura de clientes do sistema
 * guardando seu numero sequencial e tambem os ingredientes de sua pizza
 */

#include "ingredient.h"

typedef
	struct {
		int sequential;

	} Client;

/* Cria um ponteiro para um cliente a partir do nome */
Client* createClient(int);

/* Libera espaço de um Cliente */
void freeClient(Client**);

#endif