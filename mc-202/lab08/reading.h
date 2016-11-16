/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

/* Esse arquivo conterá as definições para as funções de leitura do programa, e consequentemente a montagem do hash
 * e aplicação do jogo
 */

#include "table.h"
#include "player.h"

/* Verifica se o final de uma palavra é espaço vazio ou pulo de linha */
int isStringEnd(char);

/* Limpa o conteúdo de uma variável String */
void clearString(String);

/* Lê uma String de entrada do programa */
void readString(String);

/* Lê um inteiro do programa */
void readInt(int*);

/* Lê um número grande do programa */
void readLongInt(unsigned long*);

/* Monta a hash table a partir da leitura do texto */
void readEntryText(HashTable*);

// TODO
/* Lê as jogadas da entrada e calcula os pontos */
void readPlays(HashTable*);

// TODO
/* Printa a situação atual do jogo */
void printRound();

#endif