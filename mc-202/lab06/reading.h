/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

/* Esse arquivo conterá as funções de leitura do programa */

#include "splay.h"

/* Lê toda a entrada e os armazena em clientes esperando por pizzas */
void readAllClientRequests(Tree*);

/* Printa o sequencial do cliente atual */
void printOrder(Client*);

#endif