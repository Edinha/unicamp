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

void readEntryText(HashTable * table) {

	for (unsigned long i = 0; i < table->size; i++) {
		String actual;
		clearString(actual);

		readString(actual);
		// TODO create word and alocate on table, using the older one to do the job

		printf("%lu : %s \n", i, actual);
	}

	scanf("\n");
}

// TODO
/* Lê as jogadas da entrada e calcula os pontos */
void readPlays(HashTable * table) {

}

// TODO
/* Printa a situação atual do jogo */
void printRound() {

}