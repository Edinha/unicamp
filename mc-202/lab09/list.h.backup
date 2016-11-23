/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#ifndef LIST_H
#define LIST_H

/* Esse arquivo contém as definições de uma estrutura de lista para o programa
 * O intuíto da lista é armazenar as possibilidades de contagem de regiões encontradas
 * pelo algoritmo de grafo, para futuro encontro da menor entre elas.
 */

#include "image.h"

/* Define a estrutura de nó da lista, com a informação de contagem e do próximo */
typedef
	struct NodeList {
		int count;
		struct NodeList * next;
	} NodeList;

/* Define a estrutura de lista, com o ponteiro para o nó inicial */
typedef
	struct {
		NodeList * head;
	} List;

/* Inicializa um novo ponteiro de nó para a lista de possibilidades de caminho */
NodeList* createNodeList(int);

/* Inicializa um novo ponteiro de lista */
List* createList();

/* Insere na lista o inteiro parametrizado */
void insert(List**, int);

/* Libera o ponteiro de lista recursivamente */
void freeNodeList(NodeList**);

/* Libera o ponteiro de lista */
void freeList(List**);

#endif