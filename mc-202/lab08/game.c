/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

int isStringEnd(char c) {
	return (c == ' ') || (c == '\n');
}

void clearString(String s) {
	memset(s, 0, MAX_WORD_SIZE);
}

void readString(String s) {
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

void applyPlay(HashTable * table, Player * players, int playerCount) {
	int j, phraseCount;

	readInt(&phraseCount);

	// Leitura da frase da rodada e procura na tabela
	for (j = 0; j < phraseCount; j++) {
		String actual;
		clearString(actual);
		readString(actual);

		// TODO look for word on table and get the next occurence of some stuff
	}

	// Leitura de cada palpite do jogador para essa rodada
	for (j = 0; j < playerCount; j++) {
		String actual;
		clearString(actual);
		readString(actual);

		// TODO check the hit or miss of participants
	}

}