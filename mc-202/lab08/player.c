/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "player.h"

/* Implementação dos métodos */

Player initPlayer() {
	Player player;
	player.score = ZERO_INIT;
	return player;
}

Player* createPlayers(int playerCount) {
	Player * players = malloc(playerCount * sizeof(Player));

	for (int i = 0; i < playerCount; i++) {
		players[i] = initPlayer();
	}

	return players;
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

void backup(unsigned long oldScores[], Player * players, int size) {
	for (int i = 0; i < size; i++) {
		oldScores[i] = players[i].score;
	}
}

void restore(unsigned long oldScores[], Player * players, int size) {
	for (int i = 0; i < size; i++) {
		players[i].score = oldScores[i];
	}
}
