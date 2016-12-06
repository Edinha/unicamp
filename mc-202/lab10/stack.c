/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "stack.h"

/* Implementacao dos metodos */

Stack* createStack() {
	Stack * stack = malloc(sizeof(Stack));
	stack->head = NULL;
	return stack;
}

bool isEmptyStack(Stack * stack) {
	return (stack->head->next == NULL);
}

void push(Stack * stack, Word * word) {
	StackElement * element = malloc(sizeof(StackElement));
	element->word = word;
	element->next = stack->head;
	stack->head = element;
}

Word* pop(Stack * stack) {
	StackElement * element = stack->head;
	Word * word = element->word;

	stack->head = stack->head->next;
	free(element);
	element = NULL;

	return word;
}

void freeStackElement(StackElement ** element) {
	if (!(*element)) {
		return;
	}

	freeStackElement(&(*element)->next);
	free(*element);
}

void freeStack(Stack ** stack) {
	freeStackElement(&(*stack)->head);
	free(*stack);
}