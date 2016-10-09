/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef TREE_H
#define TREE_H

#include "file.h"
#include "nodes.h"

/* Esse arquivo conterá as definições para funções de árvore do programa
 * como inserir, remover e balancear uma árvore
 */

/* Insere um arquivo na estrutura */
void insertFile(Tree*, File*);

/* Recursivo para inserir um nó em uma árvore */
NodeTree* insert(NodeTree*, File*);

/* Remove um nó da árvore */
NodeTree* delete(NodeTree*, String);

#endif