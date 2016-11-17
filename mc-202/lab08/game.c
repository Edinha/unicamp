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

int min(int a, int b) {
	return (a > b) ? b : a;
}

void applyPlay(HashTable * table, Player * players, int playerCount) {
	int j, phraseCount,
		minimum,
		score;

	Continuation * continuation;

	readInt(&phraseCount);

	String actual;
	clearString(actual);
	readString(actual);

	Word * word = search(table, actual);
	minimum = table->size;

	// Leitura da frase da rodada e procura na tabela
	for (j = 1; j < phraseCount; j++) {
		clearString(actual);
		readString(actual);

		/* Encontra a continuação para a sentença base, atualizando
		 * a contagem com o minímo de aparições das palavras subsequentes */
		continuation = find(word->continuations, actual);
		minimum = min(minimum, continuation->count);

		// TODO continuation here should never be null, but who knows...
		word = continuation->word;
	}

	// Leitura de cada palpite do jogador para essa rodada
	for (j = 0; j < playerCount; j++) {
		// TODO check the hit or miss of participants
		clearString(actual);
		readString(actual);

		continuation = find(word->continuations, actual);
		if (continuation) {
			// TODO gain some points
			score = min(minimum, continuation->count);
			hit(&players[j], score);
		} else {
			// TODO lose points if all of them lose too
		}
	}

}