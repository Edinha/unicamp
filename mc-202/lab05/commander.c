/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "commander.h"

/* Implementação dos métodos */

void ls(Tree * directory, String expression) {
	List * list = similar(directory, expression, 1);

	if (empty(list)) {
		printf(EMPTY_MESSAGE);
	}

	freeList(&list);
}

void rm(Tree * directory, String expression) {
	List * list = similar(directory, expression, 0);
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

List* similar(Tree * directory, String expression, int isLsOperation) {
	List * list = createList();
	similarExpression(directory->root, expression, &list, isLsOperation);
	return list;
}

void similarExpression(NodeTree * root, String expression, List ** list, int isLsOperation) {
	if (!root) {
		return;
	}

	int comparison = isPrefixExpression(root->file, expression);

	if (!comparison) {
		similarExpression(root->left, expression, list, isLsOperation);

		// TODO passing in open tests, but grande.in explodes this list, dont know ua
		insertFileList(list, root->file);

		// Caso seja operação de lista, imprime o nome dos arquivos
		if (isLsOperation) {
			printFilename(root->file);
		}

		similarExpression(root->right, expression, list, isLsOperation);

	} else if (comparison > 0) {
		similarExpression(root->left, expression, list, isLsOperation);
	} else {
		similarExpression(root->right, expression, list, isLsOperation);
	}
}