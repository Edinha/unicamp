/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef PLAYER_H
#define PLAYER_H

/* Esse arquivo conterá as definições para a estrutura de jogador do programa, que manterá sua pontuação durante o jogo,
 * além de contem as constantes para acertos e erros;
 */

#include "word.h"

/* Definindo constantes de multiplicação em caso de acerto ou erro */
#define MISS_BASE_SCORE -10
#define HIT_BASE_SCORE 100

/* Define a estrutura de jogador */
typedef
	struct {
		unsigned long score;
	} Player;

/* Inicializa um jogador com uma pontuação */
Player createPlayer();

/* Aumenta a pontuação do jogador de acordo com a contagem parametrizada */
void hit(Player*, int);

/* Diminue a pontuação do jogador de acordo com a contagem parametrizada */
void miss(Player*, int);

#endif