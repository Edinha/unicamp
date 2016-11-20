/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementação dos métodos */

void doSomeRecursion(Image * image, List ** possibilities, Position actual, int count) {

	if (!isValidPosition(&actual, image)) {
		return;
	}

	if (isWhitePosition(&actual, image)) {
		insert(possibilities, count);
		return;
	}

	// TODO check if already visited

	Position adjacency;


	// TODO do logic for all 4 adjacencies, maybe function pointers should do it here ...
	int colorChange = SAME_COLOR;
	adjacency = up(actual);

	if (color(image, adjacency) != color(image, actual)) {
		colorChange = DIFFERENT_COLOR;
	}

	doSomeRecursion(image, possibilities, adjacency, count + colorChange);

}

Graph* buildGraph(Image * image) {
	Graph * graph = malloc(sizeof(Graph));
	graph->size = image->width * image->height;
	graph->width = image->width;

	graph->vertexes = malloc(graph->size * sizeof(Vertex*));

	int pos;
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			pos = (i * graph->width + j);

			graph->vertexes[pos] = malloc(sizeof(Vertex));
			graph->vertexes[pos]->pixel = image->pixels[i][j];
			graph->vertexes[pos]->xPos = i;
			graph->vertexes[pos]->yPos = j;
			graph->vertexes[pos]->visited = NOT_VISITED;

			// TODO alocate neighbourhood here, function pointers for this to happen
			for (int k = 0; k < MAX_NEIGHBOURS; k++) {
			}
		}
	}

	return graph;
}

int minimumWay(Image * image) {
	// TODO make all the shit happen in here
	return 0;
}