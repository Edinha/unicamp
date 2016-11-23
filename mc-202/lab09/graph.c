/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementação dos métodos */

Position findWhiteStarter(Image * image) {
	Position starter;

	int i, j;
	for (i = 0; i < image->height; i++) {
		for (j = 0; j < image->width; j++) {
			starter.x = i;
			starter.y = j;

			if (isWhitePosition(&starter, image)) {
				return starter;
			}
		}
	}

	return starter;
}

int minimumWay(Image * image, Heap * heap) {
	int i, colorChange;

	// Vetor de ponteiro de funções com todas as cardinalidades (arestas) de um vértice qualquer
	Position (*sides[MAX_NEIGHBOURS]) (Position) = {&up, &down, &left, &right};

	Position actual = findWhiteStarter(image);
	actual.distance = ZERO_INIT;

	// Marcaa posição atual como visitidada e aloca na heap como a primeira a ser avaliada
	visit(actual, image);
	store(heap, actual);

	for (;;) {

		// Recupera da fila de prioridade uma posição a ser avaliada
		actual = retrieve(heap);

		// Para cada um dos seus vizinhos, pega a posição vizinha
		for (i = 0; i < MAX_NEIGHBOURS; i++) {
			Position sideway = (*sides[i]) (actual);

			// Caso não seja válida ou já foi visitada, ignora a posição
			if (!isValidPosition(&sideway, image)) {
				continue;
			}

			if (isAlreadyVisited(sideway, image)) {
				continue;
			}

			// Caso o vizinho seja um pixel branco e não estamos na região inicial (distância zero), encontramos a resposta
			if (isWhitePosition(&sideway, image) && actual.distance) {
				return actual.distance;
			}

			// Inicializa a variável para mudança de cor como vazia, caso a cor mude para a vizinhança,
			// aumenta seu valor para aumentar a distância entre o vértice atual e este vizinho
			colorChange = SAME_COLOR;
			if (color(actual, image) != color(sideway, image)) {
				colorChange = DIFFERENT_COLOR;
			}

			// Atualiza a distância da vizinha e aloca sua posição na fila de prioridade
			sideway.distance = actual.distance + colorChange;
			visit(sideway, image);
			store(heap, sideway);
		}
	}

	return INVALID_INIT;
}