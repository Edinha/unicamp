/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef READING_H
#define READING_H

/* Esse arquivo conterá as definições para as funções de leitura do programa, e consequentemente a montagem do hash
 * e aplicação do jogo
 */

#include "game.h"

/* Retorna verdadeiro caso a String seja vazia */
int isEmptyString(String);

/* Monta a hash table a partir da leitura do texto */
void readEntryText(HashTable*, unsigned long);

/* Faz a leitura de entradas para jogadores a aplica loop do jogo */
void readGame(HashTable*);

/* Printa a situação atual do jogo */
void printRound(int, Player*);

#endif