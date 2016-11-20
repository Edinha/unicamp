/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#ifndef GRAPH_H
#define GRAPH_H

/* Esse arquivo contém as definições de uma estrutura para o grafo de localizações possíveis.
 * Os vértices serão os pixels da imagem marcando sua posição na imagem.
 * As arestas ligando dois vértices representam sua adjacência, os dois verticais (cima e baixo),
 * como também as horizontais (esquerda e direita). O peso entre duas arestas é definido como :
 * 		- Peso 1 caso as cores entre eles forem diferentes
 * 		- Peso 0 caso a cor entre eles seja igual
 */

#include "list.h"
#include "position.h"

/* Define o máximo de vizinhança entre dois vértices (cima, baixo, esquerda, direita) */
#define MAX_NEIGHBOURS 4

#define VISITED 1
#define NOT_VISITED 0

/* Define a estrutura de um vértice, com a indicação de visitado, sua posição e a posição de seus vizinhos */
typedef
	struct {
		int pixel,
			visited;

		Position position,
				 neighbours[MAX_NEIGHBOURS];
	} Vertex;

typedef
	struct {
		int size, width;
		Vertex ** vertexes;
	} Graph;

/* Define constantes dos pesos que uma aresta pode possuir */
#define SAME_COLOR 0
#define DIFFERENT_COLOR 1

/* A partir de uma image, constroe um grafo */
Graph* buildGraph(Image*);

/* Encontra o caminho pela imagem que liga as duas regiões brancas passando pelo menor número de cores */
int minimumWay(Image*);

#endif