/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef TREE_H
#define TREE_H

#include "balancer.h"

/* Esse arquivo conterá as definições para funções de árvore do programa
 * como inserir e buscar em uma árvore AVL
 */

/* Insere um cache na estrutura */
void insertCache(Tree*, Cache*);

/* Recursivo para inserir um nó em uma árvore */
NodeTree* insertTree(NodeTree*, Cache*);

/* Procura pelo elemento de busca na árvore a partir de um número de cache */
Cache* search(NodeTree*, int);

#endif