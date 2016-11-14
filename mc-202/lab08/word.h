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
#define MAX_WORD_SIZE 50

typedef char String[MAX_WORD_SIZE];
typedef struct Word Word;

#include "list.h"

/* Define a estrutura de palavra da tabela */
	struct Word {
		int hash;
		String id;
		List continuations;
	};

/* Inicializa uma palavra a partir de uma string */
Word* createWord(String);

/* Compara duas palavras com retornando igual(0) maior(1) ou menor(-1) */
int compare(String, String);

/* Libera um ponteiro de palavra */
void freeWord(Word**);

#endif