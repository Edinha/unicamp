/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "commander.h"

/* Implementação dos métodos */

void ls(Tree * directory, String expression) {
	List * list = similar(directory, expression, LS);

	if (empty(list)) {
		printf(EMPTY_MESSAGE);
	}

	freeList(&list);
}

void rm(Tree * directory, String expression) {
	List * list = similar(directory, expression, RM);
	NodeList * n = list->head;

	if (empty(list)) {
		printf(EMPTY_MESSAGE);
	}

	for (; n ; n = n->next) {
		directory->root = delete(directory->root, n->file->name);
	}

	freeList(&list);
}

void touch(Tree * directory, String filename) {
	File * file = createFile(filename);
	insertFile(directory, file);
}

List* similar(Tree * directory, String expression, String operation) {
	List * list = createList();
	similarExpression(directory->root, expression, &list, operation);
	return list;
}

void similarExpression(NodeTree * root, String expression, List ** list, String operation) {
	if (!root) {
		return;
	}

	int comparison = isPrefixExpression(root->file, expression);

	if (!comparison) {
		similarExpression(root->left, expression, list, operation);

		insertFileList(list, root->file);

		// Caso seja operação de lista, imprime o nome dos arquivos
		if (!strcmp(operation, LS)) {
			printFilename(root->file);
		}

		similarExpression(root->right, expression, list, operation);
		return;
	}

	if (comparison > 0) {
		similarExpression(root->left, expression, list, operation);
		return;
	}

	similarExpression(root->right, expression, list, operation);
}