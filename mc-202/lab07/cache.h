/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef CACHE_H
#define CACHE_H

#include "list.h"

/* Esse arquivo conterá as definições para a estrutura de cache do programa, com
 * as informações sobre a prioriade do cache e seu número de identificação
 */

#define ZERO_INIT 0
#define INVALID_NUMBER_INIT -1

#define LESSER -1
#define EQUALS 0
#define GREATER 1

#define IS_CACHED 1
#define NOT_CACHED 0

/* Define a estrutura de um dado de cache do heap */
typedef
	struct {
		List * appearances;
		int number,
			priority,
			isCached;
	} Cache;

/* Inicializa um elemento de cache a partir de seu número e de sua prioridade na entrada */
Cache* createCache(int, int);

/* Compara dois caches, retornando LESSER caso primeiro menor e GREATER caso primeiro maior em sua prioridade */
int compare(Cache*, Cache*);

/* Compara os números de dois caches, retornando LESSER, GREATER ou EQUALS de acordo com a relação do primeiro com o segundo cache */
int compareNumber(Cache*, Cache*);

/* Altera a prioridade do cache para a próxima aparição do elemento a partir da posição parametrizada */
void updatePriority(Cache*, int);

/* Libera memória para um ponteiro de cache */
void freeCache(Cache**);

#endif