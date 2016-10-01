#include "tracker.h"

int isPossiblePrefix(Element * prefix, int size) {
	int i;

	Element actual,
			last = prefix[size - 1];

	for (i = 0; i < size - 1; i++) {
		actual = prefix[i];

		// Está na mesma linha
		if (last.index == actual.index) {
			return ERROR;
		}

		// Está na diagonal
		if ((size - 1) - i == abs(last.index - actual.index)) {
			return ERROR;
		}

		// Possue a mesma letra, não é possível no sudoku
		if (last.letter == actual.letter) {
			return ERROR;
		}
	}

	return SUCESS;
}

Element* initElements(int size) {
	Element * elements = malloc(size * sizeof(Element));
	return elements;
}

Element createElement(int index, char letter) {
	Element e;
	e.index = index;
	e.letter = letter;
	return e;
}

int tracePossibilities(Element * elements, char ** letters, int size, int pos) {
	int i;
	Element actual;

	if (pos == size) {
		// TODO make some return here is possible
		return isPossiblePrefix(elements, size);
	}

	for (i = 0; i < size; i++) {
		actual = createElement(i, letters[pos][i]);
		elements[pos] = actual;

		if (!isPossiblePrefix(elements, pos)) {
			return ERROR;
		}

		if (tracePossibilities(elements, letters, size, pos + 1)) {
			return SUCESS;
		}
	}

	return ERROR;
}

int checkBoardSolution(Board * board) {
	Element * elements = initElements(board->size);
	int result = tracePossibilities(elements, board->matrix, board->size, 0);

	free(elements);

	return result;
}

void printResult (int result) {
	if (result) {
		printf("Tem solucao.\n");
	} else {
		printf("Sem solucao.\n");
	}
}