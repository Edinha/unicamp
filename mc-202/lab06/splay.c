/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

/* Implementacao dos metodos */

#include "splay.h"

NodeTree * splay(NodeTree * root, String key) {
	if (!root) {
		return root;
	}

	int cmp = compare(root->ingredient, key);

	if (!cmp) {
		return root;
	}

	if (cmp > 0) {
		if (!root->left) {
			return root;
		}

		cmp = compare(root->left->ingredient, key);

		if (cmp > 0) {
			root->left->left = splay(root->left->left, key);
			root = rightRotate(root);
		} else {
			root->left->right = splay(root->left->right, key);
			if (root->left->right) {
				root->left = leftRotate(root->left);
			}
		}

		return !root->left ? root: rightRotate(root);
	} else {
		if (!root->right) {
			return root;
		}

		cmp = compare(root->right->ingredient, key);

		if (cmp > 0) {
			root->right->left = splay(root->right->left, key);
			if (!root->right->left) {
				root->right = rightRotate(root->right);
			}
		} else {
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		return !root->right ? root: leftRotate(root);
	}
}

NodeTree * search(Tree * tree, String key) {
	return splay(tree->root, key);
}

NodeTree * insert(NodeTree * root, String key) {
	int cmp;

	Ingredient * ingredient = createIngredient(key);
	NodeTree * newNode = createNodeTree(ingredient);

	if (!root) {
		return newNode;
	}

	root = splay(root, key);
	cmp = compare(root->ingredient, key);

	if (!cmp) {
		freeNodeTree(&newNode);
		return root;
	}

	if (cmp > 0) {
		newNode->right = root;
		newNode->left = root->left;
		root->left = NULL;
	} else {
		newNode->left = root;
		newNode->right = root->right;
		root->right = NULL;
	}

	return newNode;
}

int availabilityOfIngredient(Tree * tree, String key, int clockTime, List ** portions) {
	int untilUnfrozenTime,
		overflowTime = UNFROZEN_COOLDOWN;

	Portion * frozenPortion = NULL;
	Ingredient * ingredient;

	// Pega o ingrediente da raiz que acaba de ser retornado
	tree->root = insert(tree->root, key);
	ingredient = tree->root->ingredient;

	for (int i = 0; i < PORTION_MAX_COUNT; i++) {
		Portion * portion = ingredient->portions[i];

		freezeIfPossible(portion, clockTime);
		unfrozenIfPossible(portion, clockTime);

		// Caso esteja alocada em alguma pizza, não pode ser utilizada a porção
		if (isAlocated(portion)) {
			continue;
		}

		if (isReady(portion)) {
			alocate(portion);
			insertList(portions, portion);
			return 0;
		}

		untilUnfrozenTime = portion->lifespan - clockTime;
		if (untilUnfrozenTime <= overflowTime) {
			overflowTime = untilUnfrozenTime;
			frozenPortion = portion;
		}
	}

	if (frozenPortion) {
		alocate(frozenPortion);
		insertList(portions, frozenPortion);
	}

	tree->root->ingredient = ingredient;

	return overflowTime;
}