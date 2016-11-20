/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementação dos métodos */

void doSomeRecursion(Graph * graph, Image * image, List ** possibilities, Position actual, int count) {

	if (!isValidPosition(&actual, image)) {
		return;
	}

	int pos = actual.x * graph->width + actual.y;

	// Caso o vértice já tenha sido visitado
	if (graph->vertexes[pos]->visited) {
		return;
	}

	// Caso seja uma casa branca, insere a contagem nas posibilidades e retorna
	if (isWhitePosition(&actual, image)) {
		insert(possibilities, count);
		graph->vertexes[pos]->visited = VISITED;
		return;
	}

	// TODO logic for go to all sides

}

Graph* buildGraph(Image * image) {
	Graph * graph = malloc(sizeof(Graph));

	graph->size = image->width * image->height;
	graph->width = image->width;

	graph->vertexes = malloc(graph->size * sizeof(Vertex*));

	int pos;
	Position actual, adjacency;
	Position (*sides[MAX_NEIGHBOURS]) (Position) = {&up, &down, &left, &right};

	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			pos = (i * graph->width + j);

			graph->vertexes[pos] = malloc(sizeof(Vertex));
			graph->vertexes[pos]->pixel = image->pixels[i][j];
			graph->vertexes[pos]->visited = NOT_VISITED;

			graph->vertexes[pos]->position.x = i;
			graph->vertexes[pos]->position.y = j;

			actual.x = i;
			actual.y = j;

			// Para cada um dos lados de adjacência ao pixel, aloca a vizinhança do vértice atual
			for (int k = 0; k < MAX_NEIGHBOURS; k++) {
				adjacency = (*sides[k])(actual);
				graph->vertexes[pos]->neighbours[k] = adjacency;
			}
		}
	}

	return graph;
}

int minimumWay(Image * image) {
	// TODO make all the shit happen in here
	return 0;
}

void freeGraph(Graph ** graph) {
	if (!graph || !(*graph)) {
		return;
	}

	for (int i = 0; i < (*graph)->size; i++) {
		free((*graph)->vertexes[i]);
	}

	free((*graph)->vertexes);
	free((*graph));
}