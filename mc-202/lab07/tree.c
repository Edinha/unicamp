/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "tree.h"

/* Implementação dos métodos */

void insertCache(Tree * tree, Cache * cache) {
	tree->root = insertTree(tree->root, cache);
}

NodeTree * insertTree(NodeTree * root, Cache * cache) {
	if (!root) {
		return createNodeTree(cache);
	}

	int comparison = compareNumber(root->cache, cache);

	// Caso o cache já esteja na árvore, marca o ponteiro do parâmetro para ser desalocado
	if (!comparison) {
		insertList(&root->cache->appearances, cache->priority);
		cache->number = INVALID_NUMBER_INIT;
		return root;
	}

	if (comparison < 0) {
		root->left = insertTree(root->left, cache);
	} else {
		root->right = insertTree(root->right, cache);
	}

	updateHeight(&root);

	return insertRotationCases(root, cache);
}

Cache * search(NodeTree * root, int number) {
	if (!root) {
		return NULL;
	}

	if (root->cache->number == number) {
		return root->cache;
	}

	if (root->cache->number < number) {
		return search(root->left, number);
	}

	return search(root->right, number);
}