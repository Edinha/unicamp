/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "queue.h"

/* Implementacao dos metodos */

NodeQueue* createNodeQueue(Position position) {
	NodeQueue * node = malloc(sizeof(NodeQueue));
	node->position = position;
	node->next = NULL;
	return node;
}

Queue* createQueue() {
	Queue * queue = malloc(sizeof(Queue));
	queue->head = queue->head = NULL;
	return queue;
}

void queue(Queue ** queue, Position position) {
	NodeQueue * node = createNodeQueue(position);

	if (!(*queue)->head) {
		(*queue)->head = (*queue)->tail = node;
		return;
	}

	(*queue)->tail->next = node;
	(*queue)->tail = (*queue)->tail->next;
}

Position dequeue(Queue ** queue) {
	NodeQueue * node = (*queue)->head;
	Position position = node->position;

	(*queue)->head = (*queue)->head->next;
	free(node);
	return position;
}

void freeNodeQueue(NodeQueue ** node) {
	if (!(*node)) {
		return;
	}

	freeNodeQueue(&(*node)->next);
	free(*node);
}

void freeQueue(Queue ** queue) {
	freeNodeQueue(&(*queue)->head);
	free(*queue);
}