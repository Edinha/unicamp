/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tracker.h"

/* Implementação dos métodos */

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

int tracePossibilities(Element * elements, Board * board, int pos) {
	int i;

	if (pos == board->size) {
		return isPossiblePrefix(elements, board->size);
	}

	// Caso o prefixo atual seja inválido, retornar como error
	if (!isPossiblePrefix(elements, pos)) {
		return ERROR;
	}

	for (i = 0; i < board->size; i++) {
		elements[pos].index = i;
		elements[pos].letter = board->matrix[pos][i];

		// Chama a recursão avancando com a posição, e caso obtenha sucesso, o retorna
		if (tracePossibilities(elements, board, pos + 1)) {
			return SUCESS;
		}
	}

	return ERROR;
}

int checkBoardSolution(Board * board) {
	/* Aloca uma vetor local para elementos do tamanho do tabuleiro e retorna as
	 * a primeira chamada do backtracking para o posição 0 */

	Element elements[board->size];
	return tracePossibilities(elements, board, 0);
}

void printResult (int result) {
	if (result) {
		printf("Tem solucao.\n");
	} else {
		printf("Sem solucao.\n");
	}
}