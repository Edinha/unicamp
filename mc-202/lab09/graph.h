/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef GRAPH_H
#define GRAPH_H

/* Esse arquivo contém as definições para a funções de percorrer o grafo implícito que é a imagem
 * a partir de uma algoritmo de busca em largura, encontra o menor caminho entre duas regiões
 */

#include "heap.h"

/* Define a quantidade de vizinhos de um vértice do grafo */
#define MAX_NEIGHBOURS 4

/* Define constantes dos pesos que uma aresta pode possuir */
#define SAME_COLOR 0
#define DIFFERENT_COLOR 1

/* Visita toda a regiao branca inicial a partir de uma posicao */
void flood(Heap*, Image*, Position);

/* Retorna uma posição branca de começo para o algortimo */
Position findWhiteStarter(Image*);

/* Retorna o inteiro representando a distância do menor caminho entre as duas regiões brancas da imagem */
int minimumWay(Image*, Heap*);

#endif