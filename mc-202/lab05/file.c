/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "file.h"

/* Implementação dos métodos */

File* createFile(string name) {
	File * f = malloc(sizeof(File));
	f->count = INITIAL_COUNT;
	strcpy(f->name, name);
	return f;
}

void increase(File ** file) {
	(*file)->count++;
}

void decrease(File ** file) {
	(*file)->count--;
}