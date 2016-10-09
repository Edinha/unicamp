/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#include "reading.h"

/*  Implementação dos métodos */

void readString(String s, int type) {
	if (type) {
		scanf("%[^\x20]s", s);
		scanf(" ");
	} else {
		scanf("%[^\n]s", s);
	}
}

void readCommand(String command) {
	readString(command, 1);
}

void readFilename(String filename) {
	readString(filename, 0);
}

void readAllCommands(Tree * directory) {
	String command, filename;
	for (;;) {
		readCommand(command);
		readFilename(filename);

		// TODO decide when to break this infinite for

		decideCommandAction(directory, command, filename);
	}
}

void decideCommandAction(Tree * directory, String command, String filename) {
	void (*function) (Tree*, String);

	if (!strcmp(command, TOUCH)) {
		function = &touch;
	} else if (!strcmp(command, RM)) {
		function = &rm;
	} else 	if (!strcmp(command, LS)) {
		function = &ls;
	}

	(*function) (directory, filename);
}