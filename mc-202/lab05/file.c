/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "file.h"

/* Implementação dos métodos */

File* createFile(String name) {
	return baseFile(name, INITIAL_COUNT);
}

File* copy(File * file) {
	return baseFile(file->name, file->count);
}

File* baseFile(String filename, int count) {
	File * f = malloc(sizeof(File));
	f->count = count;
	strcpy(f->name, filename);
	return f;
}

void increase(File ** file) {
	(*file)->count++;
}

int compareFiles(File * first, File * second) {
	return strcmp(first->name, second->name);
}

int isPrefixExpression(File * file, String expression) {
	int i;

	// Itera sobre a string da expressão, pegando cada caractér
	for (i = 0; expression[i] != STRING_END; i++) {
		// Caso tenha chego a letra da regex sem haverem letras maiores ou menores,
		// a expressão é um prefixo do nome do arquivo.
		if (expression[i] == REGEX_LETTER) {
			return EQUALS;
		}

		// Caso for o final do nome do arquivo, é menor do que a expressão em tamanho
		if (file->name[i] == STRING_END) {
			return LESSER;
		}

		// Caso a letra atual seja menor do que a atual da expressão, retorna flag de menor
		if (file->name[i] < expression[i]) {
			return LESSER;
		}

		// Caso a letra atual seja maior do que a atual da expressão, retorna flag de maior
		if (file->name[i] > expression[i]) {
			return HIGHER;
		}
	}

	// Caso tenha passado completamente pelo for, a expressão é exatamente igual ao nome do arquivo
	return EQUALS;
}

void printFilename(File * file) {
	int i;
	for (i = 0; i < file->count; i++) {
		printf("%s\n", file->name);
	}
}

void freeFile(File ** file) {
	free(*file);
}