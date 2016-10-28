/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "node.h"

/* Implementação dos métodos de node.c */

Tree* createTree() {
	Tree * tree = malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

NodeTree* createNodeTree(Ingredient * ingredient) {
	NodeTree * node = malloc(sizeof(NodeTree));
	node->ingredient = ingredient;
	node->left = node->right = NULL;
	return node;
}

void freeNodeTree(NodeTree ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeTree(&(*node)->left);
	freeNodeTree(&(*node)->right);
	freeIngredient(&(*node)->ingredient);
	free(*node);
}

void freeTree(Tree ** tree) {
	freeNodeTree(&(*tree)->root);
	free(*tree);
}

Queue * createQueue() {
	Queue * Queue = malloc(sizeof(Queue));
	Queue->head = Queue->tail = NULL;
	return Queue;
}

QueueElement * createQueueElement(Client * client) {
	QueueElement * element = malloc(sizeof(QueueElement));
	element->client = client;
	element->next = NULL;
	return element;
}

void queue(Queue ** queue, Client * client) {
	QueueElement * element = createQueueElement(client);

	if (!(*queue)->head) {
		(*queue)->head = (*queue)->tail = element;
		return;
	}

	(*queue)->tail->next = element;
	(*queue)->tail = (*queue)->tail->next;
}

void headQueue(Queue ** queue, Client * client) {
	QueueElement * element = createQueueElement(client);
	element->next = (*queue)->head;
	(*queue)->head = element;
}

Client * dequeue(Queue ** queue) {
	QueueElement * oldStart = (*queue)->head;
	Client * client = oldStart->client;
	(*queue)->head = oldStart->next;
	free(oldStart);
	return client;
}

int emptyQueue(Queue ** queue) {
	return !(*queue)->head;
}

void freeQueueElement(QueueElement ** node) {
	if (!(*node)) {
		return;
	}

	freeQueueElement(&(*node)->next);
	freeClientReffilingPortions(&(*node)->client);
	free(*node);
}

void freeQueue(Queue ** queue) {
	freeQueueElement(&(*queue)->head);
	free(*queue);
}