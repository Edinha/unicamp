/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

/* Esse arquivo conterá as definições para a estrutura de cache do programa, com
 * as informações sobre a prioriade do cache e seu número de identificação
 */

#define ZERO_INIT 0
#define INVALID_NUMBER_INIT -1

#define LESSER -1
#define EQUALS 0
#define GREATER 1

/* Define a estrutura de um dado de cache do heap */
typedef
	struct {
		int number,
			priority;
	} Cache;

/* Define a estrutura de um elemento de busca, que retorna o cache buscado a partir do número e sua posição no heap */
typedef
	struct {
		int position;
		Cache * cache;
	} SearchElement;

/* Inicializa um ponteiro para retorno de elemento de busca */
SearchElement* createSearchElement(Cache*, int);

/* Inicializa um elemento de cache a partir de seu número e de sua prioridade na entrada */
Cache createCache(int, int);

/* Compara dois caches, retornando LESSER caso primeiro menor e GREATER caso primeiro maior */
int compare(Cache, Cache);

/* Retorna verdadeiro caso os caches tenham o mesmo número, falso caso contrário */
int sameNumber(Cache, Cache);

/* Compara os números de dois caches, retornando LESSER, GREATER ou EQUALS de acordo com a relação do primeiro com o segundo */
int compareNumber(Cache*, Cache*);

/* Inicializa um cache vazio */
void emptyInit(Cache*);

/* Remove a prioridade do ponteiro de cache */
void updatePriority(Cache*, int);

/* Libera um ponteiro de elemento de busca */
void freeSearchElement(SearchElement**);

#endif