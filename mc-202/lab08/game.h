/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef GAME_H
#define GAME_H

/* Esse arquivo conterá as definições para as funções para controle de pontuação do jogo, bem como a mecânica
 * de rodadas e estado do jogo
 */

#include "table.h"
#include "player.h"

#define HIT 1
#define NO_HIT 0

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

/* Aplica uma rodada do jogo a partir dos palpites dos jogadores */
void applyPlay(HashTable*, Player*, int);

#endif