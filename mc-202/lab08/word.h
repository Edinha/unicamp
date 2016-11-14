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

/* Define uma estrutura para a continuacao de uma palavra no texto */
typedef
	struct {
		int count;
		Word * next;
	} Continuation;

/* Define a estrutura de palavra da tabela */
	struct Word {
		int hash;
		String id;
		 // TODO list of continuation pointers for word
	};

/* Inicializa uma palavra a partir de uma string */
Word* createWord(String);

/* Inicializa um ponteiro de continuacao para a palavra */
Continuation* createContinuation(Word*);

/* Auemnta a contagem para uma continuacao de palavra */
void raise(Continuation**);

/* Compara duas palavras com retornando igual(0) maior(1) ou menor(-1) */
int compare(String, String);

/* Libera um ponteiro de continuacao */
void freeContinuation(Continuation**);

/* Libera um ponteiro de palavra */
void freeWord(Word**);

#endif