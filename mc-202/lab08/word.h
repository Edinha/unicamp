/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Esse arquivo conterá as definições para a estrutura de palavra da tabela, com as informacoes
 * sobre a contagem de aparicoes, a listagem de palavras subsequentes e seu hash
 */

#define ZERO_INIT 0
#define COUNT_INIT 1
#define MAX_WORD_SIZE 50

typedef char String[MAX_WORD_SIZE];
typedef struct Word Word;

#include "list.h"

/* Define a estrutura de palavra da tabela */
	struct Word {
		String id;
		List * adjacencies;
		unsigned long hash, afterCount;
	};

/* Inicializa uma palavra a partir de uma string */
Word* createWord(String);

/* Compara duas palavras com retornando igual(0) maior(1) ou menor(-1) */
int compare(String, String);

/* Compara duas palavras a partir de seus hashs armazenados */
int compareWords(Word*, Word*);

/* Incrementa a contagem de continuações que vem logo após a palavra parametrizada */
void raiseAfterCount(Word**);

/* Libera um ponteiro de palavra */
void freeWord(Word**);

#endif