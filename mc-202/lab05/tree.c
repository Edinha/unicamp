/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tree.h"

/* Implementação dos métodos */

void insertFile(Tree * tree, File * file) {
	tree->root = insert(tree->root, file);
}

// TODO change to AVL insert maybe
NodeTree* insert(NodeTree * root, File * file) {
	if (!root) {
		return createNodeTree(file);
	}

	int balanceFactor,
		comparison = compareFiles(root->file, file);

	if (comparison > 0) {
		root->left = insert(root->left, file);
	} else if (comparison < 0) {
		root->right = insert(root->right, file);
	} else {
		// Caso nomes iguais, aumenta a contagem do nó
		increase(&root->file);
		freeFile(&file);
		return root;
	}

	updateHeight(&root);

	return insertRotationCases(root, file);
}

// TODO, dont know how its gonna work though
NodeTree* delete(NodeTree * root, String expression) {
	if (!root) {
		return root;
	}

	int balanceFactor,
		comparison = isPrefixExpression(root->file, expression);

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
	freeFile(&root->file);
	root->file = createFile(temp->file->name);
	root->right = delete(root->right, temp->file->name);

	if (!root) {
		return root;
	}

	updateHeight(&root);

	return deleteRotationCases(root);
}