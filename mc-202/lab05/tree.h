/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef TREE_H
#define TREE_H

#include "file.h"
#include "nodes.h"

/* Esse arquivo conterá as definições para a estrutura de árvore do programa
 * que guardará os arquivos em seus nós e se manterá balanceada
 */

typedef
	struct {
		NodeTree * root;
	} Tree;

/* Inicializa um ponteiro para a árvore */
Tree* createTree();

/* Insere um arquivo na estrutura */
void insertFile(Tree*, File*);

/* Recursivo para inserir um nó em uma árvore */
NodeTree* insert(NodeTree*, File*);

/* Remove um nó da árvore */
NodeTree* delete(NodeTree*, String);

#endif