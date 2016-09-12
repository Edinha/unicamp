/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

/* Definições dos métodos de transposição */
#define MTF 0
#define TR 1
#define NO_TRANSPOSITION -1

/* Definições para a estruturação da lista simples
 * O nó contém sua chave inteira e seu ponteiro para o próximo
 * a lista contém o primeiro elemento e um inteiro com todos os custos
 * de acesso na referente lista.
 */
typedef
	struct Node {
		int key;
		struct Node * next;
	} Node;

typedef
	struct {
		Node * first;
		int allCosts, transpositionValue;
	} List;

/* Inicializa um nó com o valor parametrizado */
Node * createNode(int);

/* Inicializa a lista alocando as memórias necessárias */
void init(List**, int);

/* Insere a chave inteira na lista */
void insert(int, List**);

/* Encontra a chave inteira na lista */
void find(int, List**);

/* Remove a chave inteira da lista */
void removeList(int, List**);

/* Copiar os valores de uma lista para a outra */
void copy(List**, List**);

/* Faz a transposição na lista entre os dois nós parametrizados */
void transposition(Node**, Node**);

/* Faz a transposição na para o primeiro da lista */
void transpositionListFirst(List**, Node**, Node**);

/* Libera o espaço da memória dos nós de uma lista com estratégia recursiva */
void freeNodes(Node*);

/* Libera o espaço da memória da lista */
void freeList(List**);

#endif