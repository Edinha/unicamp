/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "commander.h"

/* Implementação dos métodos */

int ls(Tree * directory, String expression) {
	return similar(directory, expression, 1);
}

int rm(Tree * directory, String expression) {
	return similar(directory, expression, 0);
}

int touch(Tree * directory, String filename) {
	File * file = createFile(filename);
	insertFile(directory, file);
	return FOUND;
}

int similar(Tree * directory, String expression, int isLsOperation) {
	int found = NOT_FOUND;
	similarExpression(directory->root, expression, directory, isLsOperation, &found);
	return found;
}

void similarExpression(NodeTree * root, String expression, Tree * directory, int isLsOperation, int * found) {
	if (!root) {
		return;
	}

	int comparison = isPrefixExpression(root->file, expression);

	if (!comparison) {
		similarExpression(root->left, expression, directory, isLsOperation, found);

		// Caso seja operação de lista, imprime o nome dos arquivos
		if (isLsOperation) {
			printFilename(root->file);
		}

		similarExpression(root->right, expression, directory, isLsOperation, found);

		// Caso a operação seja remoção, aplica após o percorrimento das sub-árvores
		if (!isLsOperation) {
			directory->root = delete(directory->root, root->file->name);
		}

		// Atualiza o valor do ponteiro para encontrado
		*found = FOUND;

	} else if (comparison > 0) {
		similarExpression(root->left, expression, directory, isLsOperation, found);
	} else {
		similarExpression(root->right, expression, directory, isLsOperation, found);
	}
}