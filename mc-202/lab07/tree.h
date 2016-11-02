/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef TREE_H
#define TREE_H

#include "balancer.h"

/* Esse arquivo conterá as definições para funções de árvore do programa
 * como inserir, remover e balancear uma árvore
 */

/* Insere um arquivo na estrutura */
void insertSearchElement(Tree*, SearchElement*);

/* Recursivo para inserir um nó em uma árvore */
NodeTree* insertTree(NodeTree*, SearchElement*);

/* Remove um nó da árvore */
NodeTree* delete(NodeTree*, Cache*);

/* Procura pelo elemento de busca na árvore a partir de um cache */
SearchElement* look(NodeTree*, Cache*);

#endif