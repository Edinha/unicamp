/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#include "reading.h"

/*  Implementação dos métodos */

void readAllCommands(Tree * directory) {
	String command, filename;

	// Leitura até o final do arquivo
	while (scanf("%[^\x20]s", command) != EOF) {
		scanf(" ");
		scanf("%[^\n]s", filename);
		scanf("\n");

		// TODO remove once it worked
		// printf("%s %s\n", command, filename);
		decideCommandAction(directory, command, filename);
	}
}

void decideCommandAction(Tree * directory, String command, String filename) {
	void (*function) (Tree*, String);

	// Coloca o ponteiro de função de acordo com a comparação na string
	if (!strcmp(command, TOUCH)) {
		function = &touch;
	} else if (!strcmp(command, RM)) {
		function = &rm;
	} else if (!strcmp(command, LS)) {
		function = &ls;
	}

	(*function) (directory, filename);
}