/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

#ifndef LIST_H
#define LIST_H

/* Esse arquivo conterá as definições para a estrutura de nós de lista, guardando
 * A próxima aparição da palavra e sua contagem
 */

/* Define uma estrutura para a continuacao de uma palavra no texto */
typedef
	struct {
		int count;
		Word * word;
	} Continuation;

typedef
	struct NodeList {
		Continuation * continuation;
		struct NodeList * next;
	} NodeList;

typedef
	struct {
		NodeList * head;
	} List;

/* Inicializa um ponteiro de continuacao para a palavra */
Continuation* createContinuation(Word*);

/* Auemnta a contagem para uma continuacao de palavra */
void raise(Continuation**);

/* Retorna a comparacao entre duas continuacoes de palavras */
int equals(Continuation*, Continuation*);

/* Libera um ponteiro de continuacao */
void freeContinuation(Continuation**);

/* Inicializa um ponteiro para a lista */
List* createList();

/* Cria um nó de lista a partir de uma continuacao para a palavra */
NodeList* createNodeList(Continuation*);

/* Insere o próximo inteiro na lista */
void insertList(List**, Continuation*);

/* Libera recursivamente os nós da lista */
void freeNodeList(NodeList**);

/* Libera o ponteiro de lista */
void freeList(List**);

#endif