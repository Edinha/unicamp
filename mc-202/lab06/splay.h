/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef SPLAY_H
#define SPLAY_H

/* Esse arquivo contera as definicoes para as funcoes de splay tree */

#include "balancer.h"

/* Metodo recursivo que aplica rotacoes nos nos para trazer buscado para a raiz */
NodeTree* splay(NodeTree*, String);

/* Metodo de busca a ser chamado a partir de um ponteiro de arvore e uma chave, retornando o no procurado */
NodeTree* search(Tree*, String);

/* Insere a partir do nó de árvore parametrizado a chave */
NodeTree* insert(NodeTree*, String);

/* Avalia as condições do ingrediente armazenado na árvore e retorna o tempo de espera a mais caso haja */
int availabilityOfIngredient(Tree*, String, int);

#endif