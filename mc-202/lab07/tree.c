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

	if (!comparison) {
		insertList(&root->cache->appearances, cache->priority);
		cache->number = INVALID_NUMBER_INIT;
		return root;
	}

	if (comparison > 0) {
		root->left = insertTree(root->left, cache);
	} else if (comparison < 0) {
		root->right = insertTree(root->right, cache);
	}

	updateHeight(&root);

	return insertRotationCases(root, cache);
}

Cache * look(NodeTree * root, Cache * cache) {
	if (!root) {
		return NULL;
	}

	int comparison = compareNumber(root->cache, cache);

	if (!comparison) {
		return root->cache;
	}

	if (comparison > 0) {
		return look(root->left, cache);
	}

	return look(root->right, cache);
}