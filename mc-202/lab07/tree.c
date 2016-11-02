/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tree.h"

/* Implementação dos métodos */

void insertSearchElement(Tree * tree, SearchElement * element) {
	tree->root = insertTree(tree->root, element);
}

NodeTree* insertTree(NodeTree * root, SearchElement * element) {
	if (!root) {
		return createNodeTree(element);
	}

	int comparison = compareNumber(root->element->cache, element->cache);

	if (!comparison) {
		// TODO still to be seen
		return root;
	}

	if (comparison > 0) {
		root->left = insertTree(root->left, element);
	} else if (comparison < 0) {
		root->right = insertTree(root->right, element);
	}

	updateHeight(&root);

	return insertRotationCases(root, element);
}

NodeTree* delete(NodeTree * root, Cache * cache) {
	if (!root) {
		return root;
	}

	int comparison = compareNumber(root->element->cache, cache);

	if (comparison > 0) {
		root->left = delete(root->left, cache);
		return root;
	}

	if (comparison < 0) {
		root->right = delete(root->right, cache);
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
		// TODO later the removal of search elements on root
		// freeFile(&root->file);
		// free(root);
		return temp;
	}

	// Caso de nós com os dois filhos
	temp = minValue(root->right);

	// TODO free and copy value from beyond temp
	// freeFile(&root->file);
	// root->file = copy(temp->file);

	root->right = delete(root->right, temp->element->cache);

	updateHeight(&root);

	return deleteRotationCases(root);
}

SearchElement * look(NodeTree * root, Cache * cache) {
	if (!root) {
		return NULL;
	}

	int comparison = compareNumber(root->element->cache, cache);

	if (!comparison) {
		return root->element;
	}

	if (comparison > 0) {
		return look(root->left, cache);
	}

	return look(root->right, cache);
}