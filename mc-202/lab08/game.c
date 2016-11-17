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
		score,
		hasHit;

	Word * word;
	String actual;
	Continuation * continuation;
	unsigned long oldScores[playerCount];

	backup(oldScores, players, playerCount);

	readInt(&phraseCount);
	clearString(actual);
	readString(actual);

	/* Aloca o começo da frase e inicializa a variável de miníma ocorrência */
	word = search(table, actual);
	minimum = table->size;

	// Leitura da frase da rodada e procura na tabela
	for (j = 1; j < phraseCount; j++) {
		clearString(actual);
		readString(actual);

		/* Encontra a continuação para a sentença base, atualizando
		 * a contagem com o minímo de aparições das palavras subsequentes a fim
		 * de obter-se o número de vezes que a frase completa e na ordem aparece */
		continuation = find(word->continuations, actual);
		minimum = min(minimum, continuation->count);

		word = continuation->word;
	}

	hasHit = NO_HIT;

	// Leitura de cada palpite do jogador para essa rodada
	for (j = 0; j < playerCount; j++) {
		clearString(actual);
		readString(actual);

		// Encontra a continuação a partir do palpite do jogador
		continuation = find(word->continuations, actual);

		/* Para marcar a pontuação, é preciso encontrar o mínimo número de vezes em que
		 * acontece a sequência entre a frase base e o palpite do jogador, por isso o
		 * uso da função min em ambos os casos de acerto ou erro */

		// Caso a continuação exista, marca pontos para o jogador e atualiza a variável dizendo que houve um acerto
		if (continuation) {
			score = min(minimum, continuation->count);
			hit(&players[j], score);
			hasHit = HIT;
		} else {
			// Caso contrário, ocorreu um erro
			score = min(word->afterCount, minimum);
			miss(&players[j], score);
		}
	}

	// Caso ninguém tenha acertado, volta o placar para como era no começo da rodada
	if (!hasHit) {
		restore(oldScores, players, playerCount);
	}
}