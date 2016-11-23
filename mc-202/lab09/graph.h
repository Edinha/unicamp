/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#ifndef GRAPH_H
#define GRAPH_H

/* Esse arquivo contém as definições para a funções de percorrer o grafo implícito que é a imagem
 * a partir de uma algoritmo de busca em largura, encontra o menor caminho entre duas regiões
 */

#include "position.h"

/* Retorna uma posição branca de começo para o algortimo */
Position findWhiteStarter(Image*);

/* Retorna o inteiro representando a distância do menor caminho entre as duas regiões brancas da imagem */
int minimumWay(Image*);

#endif