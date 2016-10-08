/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tree.h"

/* Implementação dos métodos */

NodeTree* createNodeTree(File * file) {
	NodeTree * node = malloc(sizeof(NodeTree));
	node->file = file;
	node->left = node->right = NULL;
	return node;
}

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
void remove(NodeTree * root, String expression) {

}

// TODO free the motherfucking tree