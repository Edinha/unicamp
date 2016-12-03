/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readInt(int * i) {
	scanf("%d ", i);
}

void readLong(unsigned long * ul) {
	scanf("%lu ", ul);
}

int isStringEnd(char c) {
	return (c == ' ') || (c == '\n');
}

void clearString(String s) {
	memset(s, 0, MAX_WORD_SIZE);
}

void readString(String s) {
	clearString(s);

	char c;
	for (int i = 0; ; i++) {
		scanf("%c", &c);
		if (isStringEnd(c)) {
			break;
		}

		s[i] = c;
	}
}