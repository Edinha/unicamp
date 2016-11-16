/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

int isEmptyString(String s) {
	return (s[0] == '\0');
}

void readEntryText(HashTable * table, unsigned long wordCount) {
	for (unsigned long i = 0; i < wordCount;) {
		String actual;
		clearString(actual);
		readString(actual);

		// TODO create word and alocate on table, using the older one to do the job

		if (!isEmptyString(actual)) {
			i++;
		}
	}
}

void readGame(HashTable * table) {
	int roundCount,
		playerCount;

	readInt(&roundCount);
	readInt(&playerCount);

	Player * players = createPlayers(playerCount);

	for (int i = 0; i < roundCount; i++) {
		applyPlay(table, players, playerCount);
		printRound(i, players);
	}

	free(players);
}

// TODO
/* Printa a situação atual do jogo */
void printRound(int round, Player * players) {

}