/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

#ifndef LIST_H
#define LIST_H

/* Esse arquivo conterá as definições para a estrutura de nós de lista, guardando
 * A adjacência da palavra em questão (anterior e próxima);
 */

/* Define uma estrutura de adjacência para a palavra, com seu ponteiro para anterior e próximo */
typedef
	struct {
		int count;
		Word * next, * previous;
	} Adjacency;

typedef
	struct NodeList {
		Adjacency * adjacency;
		struct NodeList * next;
	} NodeList;

typedef
	struct {
		NodeList * head;
	} List;

/* Inicializa um ponteiro de adjacência para a palavra */
Adjacency* createAdjacency(Word*, Word* );

/* Auemnta a contagem para a adjacência de palavra */
void raise(Adjacency**);

/* Compara duas adjacências retornando verdadeiro caso ambas as palavras apontadas sejam iguais */
int equals(Adjacency*, Adjacency*);

/* Procura pela lista uma adjacência que possua ambas as palavras anterior e próxima. Caso a anterior parametrizada seja nula, procura apenas nas próximas */
Adjacency* find(List**, Word*, Word*);

/* Libera um ponteiro de adjacência */
void freeAdjacency(Adjacency**);

/* Inicializa um ponteiro para a lista */
List* createList();

/* Cria um nó de lista a partir de uma continuacao para a palavra */
NodeList* createNodeList(Adjacency*);

/* Insere a próxima adjacência na lista */
void addAdjacency(List**, Adjacency*);

/* Libera recursivamente os nós da lista */
void freeNodeList(NodeList**);

/* Libera o ponteiro de lista */
void freeList(List**);

#endif