/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "word.h"

/* Esse arquivo conterá as definições para a estrutura de tabela de espalamento (hash table).
 * Com as funcoes de hash, insercao e busca a partir de chaves String.
 */

/* Define o número primo para cálculo do hash e o multiplicador de tamanho da tabela */
#define PRIME 5831
#define SIZE_MULTIPLIER 3

/* Define a estrutura de hash table, com o vetor para ponteiros de palavras e seu tamanho */
typedef
	struct {
		Word ** data;
		unsigned long size;
		int wordCount;
	} HashTable;

/* Inicializa uma hash table a partir de um tamanho */
HashTable* createHashTable(unsigned long);

/* Insere na hash table uma nova palavra, alterando-a com os valores necessários */
Word* insert(HashTable*, String);

/* Retorna o ponteiro de palavra da hash table a partir de uma String */
Word* search(HashTable*, String);

/* Calcula o numero de hash a partir de uma String de entrada */
unsigned long hash(String);

/* Libera um ponteiro de hash table */
void freeHashTable(HashTable**);

#endif