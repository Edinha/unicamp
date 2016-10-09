/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "commander.h"

/* Implementação dos métodos */

// TODO method to list all tree nodes with expression
void ls(Tree * directory, String expression) {
	List * list = similar(directory, expression);
	NodeList * n = list->head;
	int count;

	for (; n ; n = n->next) {
		count = n->file->count;
		for (; count > 0; count--) {
			printf("%s\n", n->file->name);
		}
	}

	freeList(&list);
}

// TODO method to remove all tree nodes with expression
void rm(Tree * directory, String expression) {
	List * list = similar(directory, expression);
	NodeList * n = list->head;

	for (; n ; n = n->next) {
		delete(directory->root, n->file->name);
	}

	freeList(&list);
}

void touch(Tree * directory, String filename) {
	File * file = createFile(filename);
	insertFile(directory, file);
}

List* similar(Tree * directory, String expression) {
	List * list = createList();
	similarExpression(directory->root, expression, list);
	return list;
}

void similarExpression(NodeTree * root, String expression, List * list) {
	if (!root) {
		return;
	}

	if (isPrefixExpression(root->file, expression)) {
		insertFileList(list, root->file);
	}

	similarExpression(root->left, expression, list);
	similarExpression(root->right, expression, list);
}