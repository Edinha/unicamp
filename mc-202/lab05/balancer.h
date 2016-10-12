/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef BALANCER_H
#define BALANCER_H

#include "file.h"
#include "nodes.h"

/* Esse arquivo conterá as definições para funções de balanceamento e
 * rotação da árvore
 */

/* Verifica e aplica os casos de rotação da árvore para o método de insert */
NodeTree* insertRotationCases(NodeTree*, File*);

/* Verifica e aplica os casos de rotação da árvore para o método de insert */
NodeTree* deleteRotationCases(NodeTree*);

/* Realiza a rotação a direita do nó */
NodeTree* rightRotate(NodeTree*);

/* Realiza a rotação a esquerda do nó */
NodeTree* leftRotate(NodeTree*);

#endif