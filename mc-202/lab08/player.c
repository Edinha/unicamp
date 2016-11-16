/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "player.h"

/* Implementação dos métodos */

Player createPlayer() {
	Player player;
	player.score = ZERO_INIT;
	return player;
}

void hit(Player * player, int count) {
	player->score += HIT_BASE_SCORE * count;
}

void miss(Player * player, int count) {
	player->score -= MISS_BASE_SCORE * count;

	if (player->score < 0) {
		player->score = ZERO_INIT;
	}
}