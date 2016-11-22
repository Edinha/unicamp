/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "queue.h"

/* Implementacao dos metodos */

NodeQueue* createNodeQueue(int count, Position position) {
	NodeQueue * node = malloc(sizeof(NodeQueue));
	node->count = count;
	node->position = position;
	node->next = NULL;
	return node;
}

Queue* createQueue() {
	Queue * queue = malloc(sizeof(Queue));
	queue->head = queue->head = NULL;
	return queue;
}

void queue(Queue ** queue, int count, Position position) {
	NodeQueue * node = createNodeQueue(count, position);

	if (!(*queue)->head) {
		(*queue)->head = (*queue)->tail = node;
		return;
	}

	(*queue)->tail->next = node;
	(*queue)->tail = (*queue)->tail->next;
}

Position dequeue(Queue ** queue, int * count) {
	NodeQueue * node = (*queue)->head;
	Position position = node->position;

	*count = node->count;

	(*queue)->head = (*queue)->head->next;
	free(node);
	return position;
}

int isEmpty(Queue ** queue) {
	return ((*queue)->head == NULL);
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