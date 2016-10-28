/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef CLIENT_H
#define CLIENT_H

#include "list.h"

/* Esse arquivo conterá as definições para a estrutura de clientes que fizeram pedidos
 * guardando seu número de ordem e o tempo a mais de espera que ele terá dado os ingredientes
 * de sua pizza
 */

/* Define da estrutura de cliente, guardando seu número sequencial da ordem de entrada
 * bem como seu tempo a mais de espera dados seus ingredientes
 */
typedef
	struct {
		List * portions;
		int cookTime,
			sequential,
			overflowTime;
	} Client;

/* Cria um ponteiro para um cliente a partir do sequencial */
Client* createClient(int);

/* Aumenta o tempo de forno do cliente dado */
void overflow(Client**, int, int);

/* Libera espaço de um client */
void freeClientReffilingPortions(Client**);

#endif