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

	int pos = vertexPos(image->width, actual);

	// Caso o vértice já tenha sido visitado
	if (graph->vertexes[pos]->visited) {
		return;
	}

	graph->vertexes[pos]->visited = VISITED;

	// Caso seja uma casa branca, insere a contagem nas posibilidades e retorna
	if (isWhitePosition(&actual, image)) {
		insert(possibilities, count);
		return;
	}

	// TODO logic for go to all sides
	Position (*sides[MAX_NEIGHBOURS]) (Position) = {&up, &down, &left, &right};

	for (int i = 0; i < MAX_NEIGHBOURS; i++) {
		Position sideway = (*sides[i]) (actual);

		int colorChange = SAME_COLOR,
			sidewayPos = vertexPos(image->width, sideway);

		if (graph->vertexes[pos]->pixel != graph->vertexes[sidewayPos]->pixel) {
			colorChange = DIFFERENT_COLOR;
		}

		doSomeRecursion(graph, image, possibilities, sideway, count + colorChange);
	}
}

void queueThis(Graph * graph) {
	int count = 0,
		colorChange,
		sidewayPos,
		pos,
		i;

	Position actual, sideway;
	List * list = createList();
	Queue * path = createQueue();

	// Procura uma posição branca dentre os vértices do grafo
	for (i = 0; i < graph->size / 2; i++) {
		actual = graph->vertexes[i]->position;
		if (graph->vertexes[i]->pixel == WHITE) {
			break;
		}

		pos = graph->size - i - 1;
		actual = graph->vertexes[pos]->position;
		if (graph->vertexes[pos]->pixel == WHITE) {
			break;
		}
	}

	queue(&path, count, actual);

	while (!isEmpty(&path)) {
		// A partir da fila, retira o elemento que entrou primeiro e aplica a logica de
		// encontrar regiao branca para ele

		actual = dequeue(&path, &count);
		pos = vertexPos(graph->width, actual);

		// Casos onde a posição não é válida para continuação da busca
		// Não está dentro da imagem ou já foi visitada pelo algoritmo
		if (!isValid(graph, &actual) || graph->vertexes[pos]->visited) {
			continue;
		}

		// Caso seja um vértice branco, adiciona a contagem atual na lista
		if (graph->vertexes[pos]->pixel == WHITE) {
			insert(&list, count);
		}

		// Marca a posição atual como visitada
		graph->vertexes[pos]->visited = VISITED;

		// Para cada um dos vizinhos, o avalia e o realoca na fila para continuar a busca
		for (i = 0; i < MAX_NEIGHBOURS; i++) {
			colorChange = SAME_COLOR;

			sideway = graph->vertexes[pos]->neighbours[i];
			sidewayPos = vertexPos(graph->width, sideway);

			if (!graph->vertexes[sidewayPos]->visited) {
				if (graph->vertexes[pos]->pixel != graph->vertexes[sidewayPos]->pixel) {
					colorChange = DIFFERENT_COLOR;
				}

				queue(&path, count + colorChange, sideway);
			}
		}
	}

	// TODO print the response for the least of the list

	freeList(&list);
	freeQueue(&path);
}

Graph* buildGraph(Image * image) {
	Graph * graph = malloc(sizeof(Graph));

	graph->size = image->width * image->height;
	graph->width = image->width;
	graph->height = image->height;
	graph->vertexes = malloc(graph->size * sizeof(Vertex*));

	Position actual, adjacency;
	Position (*sides[MAX_NEIGHBOURS]) (Position) = {&up, &down, &left, &right};

	int pos;
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			actual.x = i;
			actual.y = j;

			pos = vertexPos(graph->width, actual);

			graph->vertexes[pos] = malloc(sizeof(Vertex));
			graph->vertexes[pos]->pixel = image->pixels[i][j];
			graph->vertexes[pos]->visited = NOT_VISITED;

			graph->vertexes[pos]->position = actual;

			// Para cada um dos lados de adjacência ao pixel, aloca a vizinhança do vértice atual
			for (int k = 0; k < MAX_NEIGHBOURS; k++) {
				adjacency = (*sides[k])(actual);
				graph->vertexes[pos]->neighbours[k] = adjacency;
			}
		}
	}

	return graph;
}

int vertexPos(int width, Position position) {
	return position.x + (width * position.y);
}

bool isValid(Graph * graph, Position * position) {
	if (position->x >= graph->height || position->x < 0) {
		return false;
	}

	if (position->y >= graph->width || position->y < 0) {
		return false;
	}

	return true;
}

int minimumWay(Graph * graph, Image * image) {
	// TODO make all the shit happen in here
	List * list = createList();

	Position actual;

	// TODO find a white block for starters
	actual.x = 0; actual.y = 0;

	doSomeRecursion(graph, image, &list, actual, 0);

	freeList(&list);

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