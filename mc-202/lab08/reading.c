/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

int isStringEnd(char c) {
	return (c == ' ') || (c == '\n');
}

int isEmptyString(String s) {
	return (s[0] == '\0');
}

void clearString(String s) {
	memset(s, 0, MAX_WORD_SIZE);
}

void readString(String s) {
	// TODO maybe a better way scanf(" %[^ ]", s);
	char c;
	for (int i = 0; ; i++) {
		scanf("%c", &c);

		if (isStringEnd(c)) {
			break;
		}

		s[i] = c;
	}
}

void readInt(int * i) {
	scanf("%d ", i);
}

void readLongInt(unsigned long * ul) {
	scanf("%lu ", ul);
}

void readEntryText(HashTable * table, unsigned long wordCount) {
	for (unsigned long i = 0; i < wordCount;) {
		String actual;
		clearString(actual);
		readString(actual);

		// TODO create word and alocate on table, using the older one to do the job

		// TODO remove printf
		printf("%lu : %s \n", i, actual);

		if (!isEmptyString(actual)) {
			i++;
		}
	}
}

// TODO
/* Lê as jogadas da entrada e calcula os pontos */
void readPlays(HashTable * table) {
	int roundCount,
		playerCount,
		phraseCount;

	int i, j;

	readInt(&roundCount);
	readInt(&playerCount);

	// TODO remove printf
	printf("%d %d\n", roundCount, playerCount);

	Player * players = createPlayers(playerCount);

	for (i = 0; i < roundCount; i++) {
		// TODO make logic for each play

		readInt(&phraseCount);

		// TODO remove printf
		printf("%d ", phraseCount);

		// Leitura da frase da rodada e procura na tabela
		for (j = 0; j < phraseCount; j++) {
			String actual;
			clearString(actual);
			readString(actual);

			// TODO remove printf
			printf("%s ", actual);

			// TODO look for word on table and get the next occurence of some stuff
		}

		printf("\n");

		// Leitura de cada palpite do jogador para essa rodada
		for (j = 0; j < playerCount; j++) {
			String actual;
			clearString(actual);
			readString(actual);

			// TODO remove printf
			printf("%s\n", actual);

			// TODO check the hit or miss of participants
		}

		printf("\n");

		printRound(i, players);
	}

	free(players);
}

// TODO
/* Printa a situação atual do jogo */
void printRound(int round, Player * players) {

}