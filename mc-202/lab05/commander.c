/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "commander.h"

/* Implementação dos métodos */
void ls(Tree * directory, String expression) {
	// TODO method to list all tree nodes with expression
}

void rm(Tree * directory, String expression) {
	// TODO method to remove all tree nodes with expression
}

void touch(Tree * directory, String filename) {
	File * file = createFile(filename);
	insertFile(directory, file);
}