/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef STACK_H
#define STACK_H

#include "word.h"

/* Esse arquivo conterá as definições para a estrutura de pilha do programa, utilizada para reverter a ordem
 * da frase de saida, pois o algoritmo de busca em largura devolve o caminho de tras para frente
 */

/* Define a estrutura de um elemento da pilha, com a palavra e o ponteiro para o proximo */
typedef
	struct StackElement {
		Word * word;
		struct StackElement * next;
	} StackElement;

/* Define a estrutura de pilha, com o comeco e o fim da mesma */
typedef
	struct {
		StackElement * head;
	} Stack;

/* Inicializa um ponteiro de pilha */
Stack* createStack();

/* Retorna verdadeiro caso a pilha esteja vazia e falso caso contrario */
bool isEmptyStack(Stack*);

/* Empilha uma palavra */
void push(Stack*, Word*);

/* Desempilha uma palavra */
Word* pop(Stack*);

/* Libera recursivamente os elementos da pilha */
void freeStackElement(StackElement**);

/* Libera um ponteiro de pilha */
void freeStack(Stack**);

#endif