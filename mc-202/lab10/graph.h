/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef GRAPH_H
#define GRAPH_H

#define NO_WAY "erro\n"

#include "heap.h"
#include "reading.h"

/* Esse arquivo conterá as definições para funções relacionadas ao grafo, como busca pelo menor
 * caminho, criação de vértices e aresta.
 */

/* Monta um grafo a partir da entrada */
HashTable* buildGraph();

/* Encontra o menor caminho entre duas palavras parametrizadas */
void minimumWay(HashTable*, String, String);

// TODO print way
void printWay();

#endif