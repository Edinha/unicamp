/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "file.h"

/* Implementação dos métodos */

File* createFile(String name) {
	File * f = malloc(sizeof(File));
	f->count = INITIAL_COUNT;
	strcpy(f->name, name);
	return f;
}

void increase(File ** file) {
	(*file)->count++;
}

int compareFiles(File * first, File * second) {
	return strcmp(first->name, second->name);
}

// int isPrefixExpression(File * file, String expression)

void freeFile(File ** file) {
	free((*file)->name);
	free((*file));
}