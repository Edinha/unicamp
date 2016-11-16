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
	Word * oldWord = NULL;
	Continuation * continuation = NULL;

	for (unsigned long i = 0; i < wordCount;) {
		String actual;
		clearString(actual);
		readString(actual);

		// Caso seja uma String vazia, continua o for sem contar como uma palavra do texto
		if (isEmptyString(actual)) {
			continue;
		}

		// TODO create word and alocate on table, using the older one to do the job
		Word * word = insert(table, actual);

		if (oldWord) {
			continuation = createContinuation(word);
			insertList(&oldWord->continuations, continuation);
		}

		oldWord = word;
		i++;
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