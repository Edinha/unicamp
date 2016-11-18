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
	Word * previousWord = NULL,
		 * previousToPreviousWord = NULL;

	Adjacency * adjacency = NULL;

	for (unsigned long i = 0; i < wordCount; i++) {
		String actual;
		clearString(actual);
		readString(actual);

		// Caso seja uma String vazia, continua o for sem contar como uma palavra do texto
		if (isEmptyString(actual)) {
			continue;
		}

		// Insere a mais nova palavra na tabela e a aloca suas adjacências
		Word * word = insert(table, actual);

		// Caso já se tenham passado duas palavras, pode começar a montar as adjacências
		if (previousWord && previousToPreviousWord) {
			adjacency = createAdjacency(word, previousToPreviousWord);
			addAdjacency(&previousWord->adjacencies, adjacency);
			// TODO count some stuff maybe ?
		}

		if (previousWord) {
			previousToPreviousWord = previousWord;
		}

		previousWord = word;
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
		printRound(players, playerCount, i);
	}

	free(players);
}

void printRound(Player * players, int playerCount, int round) {
	printf("Rodada");

	// Printa espaço caso o número tenha duas casas
	round++;
	if ((round / 10) > 1) {
		printf(" ");
	}

	printf("%2d:", round);

	for (int i = 0; i < playerCount; i++) {
		printf(" %4lu", players[i].score);
	}

	printf("\n");
}