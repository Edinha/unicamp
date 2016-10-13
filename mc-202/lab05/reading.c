/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#include "reading.h"

/*  Implementação dos métodos */

void readAllCommands(Tree * directory) {
	String command, filename;

	// Leitura até o final do arquivo (EOF)
	while (scanf("%[^\x20]s", command) != EOF) {
		scanf(" ");
		scanf("%[^\n]s", filename);
		scanf("\n");

		decideCommandAction(directory, command, filename);
	}
}

void decideCommandAction(Tree * directory, String command, String filename) {
	int (*function) (Tree*, String);
	int found;

	// Coloca o ponteiro de função de acordo com a comparação com as constantes de commandos
	if (!strcmp(command, TOUCH)) {
		function = &touch;
	} else if (!strcmp(command, RM)) {
		function = &rm;
	} else if (!strcmp(command, LS)) {
		function = &ls;
	}

	found = (*function) (directory, filename);

	// Caso não tenha sido encontrado, mensagem de não existência é printada
	if (found == NOT_FOUND) {
		printf(EMPTY_MESSAGE);
	}
}