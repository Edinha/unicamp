/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

/* Esse arquivo conterá as definições para a estrutura de nós de lista, guardando
 * A próxima aparição do elemento (inteiro) e o próximo nó
 */

#define NO_NEXT_APPEARANCE -1

typedef
	struct NodeList {
		int appearance;
		struct NodeList * next;
	} NodeList;

typedef
	struct {
		NodeList * head,
				 * tail;
	} List;

/* Inicializa um ponteiro para a lista */
List* createList();

/* Cria um nó de lista a partir de um inteiro */
NodeList* createNodeList(int);

/* Insere o próximo inteiro na lista */
void insertList(List**, int);

/* Encontra a próxima aparição do cache a partir de uma posição, retorna -1 caso não haja */
int findNextAppearance(List**, int);

/* Libera recursivamente os nós da lista */
void freeNodeList(NodeList**);

/* Libera o ponteiro de lista */
void freeList(List**);

#endif