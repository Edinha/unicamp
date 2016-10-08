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

// TODO this will receive also the motherfucking tree and the printing functions
void readAllCommands() {

}