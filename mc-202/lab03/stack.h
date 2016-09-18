/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Definições da estrutura de pilha utilizada pelo programa
 * Cada elemento da pilha é definido como um nó, que possue seu valor armazenado
 * e uma referência para seu próximo elemento.
 * A pilha por sua vez possue a referência para o ó do topo (o último inserido).
 */

typedef
	struct Node {
		void * value;
		struct Node * next;
	} Node;

typedef
	struct {
		Node * head;
	} Stack;

/* Método que inicializa a pilha */
void initStack (Stack**);

/* Método que cria um novo elemento para a pilha */
Node * createNode(void*);

/* Método de empilhar um inteiro na pilha */
void push (void*, Stack**);

/* Método de desempilhar um inteiro do topo da pilha */
void* pop (Stack**);

#endif
