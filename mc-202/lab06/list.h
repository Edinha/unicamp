/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef LIST_H
#define LIST_H

#include "ingredient.h"

/* Esse arquivo conterá as definições para a estrutura de lista do programa */

/* Definições dos ponteiros de nó de listas de porções */
typedef
	struct NodeList {
		Portion * portion;
		struct NodeList * next;
	} NodeList;

typedef
	struct {
		NodeList * head;
	} List;

/* Inicializa um ponteiro de lista */
List* createList();

/* Inicializa um ponteiro para o nó da Lista */
NodeList* createNodeList(Portion*);

/* Insere no começo da lista */
void insertList(List**, Portion*);

/* Libera o ponteiro de nó de Lista recursivamente */
void freeNodeList(NodeList**, int);

/* Libera o ponteiro de Lista */
void freeList(List**, int);

#endif