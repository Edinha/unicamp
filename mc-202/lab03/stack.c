/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "stack.h"

/* Implementação dos métodos */

void initStack (Stack ** stack) {
	(*stack) = malloc(sizeof(Stack));
	(*stack)->head = NULL;
}

Node * createNode(void * value) {
	Node * node = malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	return node;
}

void push (void * value, Stack ** stack) {
	Node * new = createNode(value);
	new->next = (*stack)->head;
	(*stack)->head = new;
}

void * pop (Stack ** stack) {
	if (empty(stack)) {
		return NULL;
	}

	Node * oldHead = (*stack)->head;
	void * value = oldHead->value;

	(*stack)->head = (*stack)->head->next;
	free(oldHead);
	return value;
}

void* peek (Stack ** stack) {
	if (empty(stack)) {
		return NULL;
	}

	return (*stack)->head->value;
}

bool empty (Stack ** stack) {
	return (*stack)->head == NULL;
}
