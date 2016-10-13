/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tree.h"

/* Implementação dos métodos */

void insertFile(Tree * tree, File * file) {
	tree->root = insert(tree->root, file);
}

NodeTree* insert(NodeTree * root, File * file) {
	if (!root) {
		return createNodeTree(file);
	}

	int comparison = compareFiles(root->file, file);

	if (!comparison) {
		// Caso nomes iguais, aumenta a contagem do nó
		increase(&root->file);
		freeFile(&file);
		return root;
	}

	if (comparison > 0) {
		root->left = insert(root->left, file);
	} else if (comparison < 0) {
		root->right = insert(root->right, file);
	}

	updateHeight(&root);

	return insertRotationCases(root, file);
}

NodeTree* delete(NodeTree * root, String expression) {
	if (!root) {
		return root;
	}

	int comparison = isPrefixExpression(root->file, expression);

	if (comparison > 0) {
		root->left = delete(root->left, expression);
		return root;
	}

	if (comparison < 0) {
		root->right = delete(root->right, expression);
		return root;
	}

	NodeTree * temp = NULL;
	int changed = 0;

	// Casos de nó com apenas um filho
	if (!root->left) {
		temp = root->right;
		changed = 1;
	}

	if (!root->right) {
		temp = root->left;
		changed = 1;
	}

	/* Caso um dos filhos seja nulo, é possível remover root
	 * e ficar apenas com temp na recursão */
	if (changed) {
		freeFile(&root->file);
		free(root);
		return temp;
	}

	// Caso de nós com os dois filhos
	temp = minValue(root->right);

	// Copia o arquivo de temp para raiz atual da recursão, elimidando ponteiro antigo
	freeFile(&root->file);
	root->file = copy(temp->file);

	root->right = delete(root->right, temp->file->name);

	updateHeight(&root);

	return deleteRotationCases(root);
}