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

void printError() {
	printf(ERROR_MESSAGE);
}

void printWay(Word * word) {
	Stack * stack = createStack();

	// Retorna todo o caminho pelos pais e empilha as palavras
	while (word) {
		push(stack, word);
		word = word->parent;
	}

	// Desempilha as palavras e as printa na ordem correta
	while (!isEmptyStack(stack)) {
		word = pop(stack);
		printf("%s ", word->id);
	}

	word = pop(stack);
	printf("%s\n", word->id);
	freeStack(&stack);
}