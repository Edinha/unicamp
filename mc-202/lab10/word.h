/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Esse arquivo conterá as definições para a estrutura de palavra da tabela,
 * representativa dos vértices do grafo
 */

#define ZERO_INIT 0
#define COUNT_INIT 1
#define MAX_WORD_SIZE 50

typedef char String[MAX_WORD_SIZE];
typedef struct Word Word;

typedef
	struct {
		long weight;
		Word * word;
	} Continuation;

/* Define a estrutura de palavra da tabela, com sua identificação, vetor de continuações e a última posição de alocação */
	struct Word {
		String id;

		int size;
		Continuation ** continuations;
	};

/* Inicializa uma palavra a partir de uma string e de um tamanho para o vetor de continuações */
Word* createWord(String, int);

/* Inicializa uma continuação de palavra */
Continuation* createContinuation(Word*, long);

/* Compara duas palavras com retornando igual(0) maior(1) ou menor(-1) */
int compare(String, String);

/* Compara duas palavras a partir de seus ids */
int compareWords(Word*, Word*);

/* Aloca a segunda palavra como continuação da primeira */
void alocateSequence(Word*, Word*, long);

/* Diminue o peso da aresta conforme aparições */
void heavify(Continuation*);

/* Libera um ponteiro de palavra */
void freeWord(Word**);

#endif