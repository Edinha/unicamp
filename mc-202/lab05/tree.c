/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tree.h"

/* Implementação dos métodos */

Tree* createTree() {
	Tree * tree = malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

void insertFile(Tree * tree, File * file) {
	tree->root = insert(tree->root, file);
}

// TODO change to AVL insert maybe
NodeTree* insert(NodeTree * root, File * file) {

	if (!root) {
		root = createNodeTree(file);
		return root;
	}

	int comparison = compareFiles(root->file, file);

	if (comparison == 0) {
		increase(&root->file);
		return root;
	}

	if (comparison > 0) {
		root->left = insert(root->left, file);
		return root;
	}

	root->right = insert(root->right, file);
	return root;
}

// TODO, dont know how its gonna work though
NodeTree * remove(NodeTree * root, String expression) {
	if (!root) {
		return root;
	}

	int comparison = isPrefixExpression(root->file, expression);
	if (comparison > 0) {
		root->left = remove(root->left, expression);
		return root;
	}

	if (comparison < 0) {
		root->right = remove(root->right, expression);
		return root;
	}

	NodeTree * temp = NULL;

	// Casos de nó com apenas um filho
	if (!root->left) {
		temp = root->right;
	}

	if (!root->right) {
		temp = root->left;
	}

	if (temp) {
		freeNodeTree(&root);
		return temp;
	}

	// Caso de nós com os dois filhos
	temp = minValue(root->right);
	root->file = temp->file;
	root->right = remove(root->right, temp->file->name);

	return root;
}

void freeTree(Tree ** tree) {
	freeNodeTree(&(*tree)->root);
	free(*tree);
}