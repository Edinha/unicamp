/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef BALANCER_H
#define BALANCER_H

#include "node.h"

/* Esse arquivo conterá as definições para funções de rotação da árvore splay,
 * em zig, zag e zig-zag em sua implementação.
 */

/* Realiza a rotação a direita do nó */
NodeTree* rightRotate(NodeTree*);

/* Realiza a rotação a esquerda do nó */
NodeTree* leftRotate(NodeTree*);

#endif