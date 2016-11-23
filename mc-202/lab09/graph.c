/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

/* Implementação dos métodos */
Position findWhiteStarter(Image * image) {
	Position starter;

	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
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
	// TODO heap logic here...

	int j, colorChange;

	Position (*sides[MAX_NEIGHBOURS]) (Position) = {&up, &down, &left, &right};

	Position actual = findWhiteStarter(image);
	actual.distance = ZERO_INIT;

	visit(actual, image);
	store(heap, actual);

	for (;;) {
		// TODO logic of store neighbours and bla bla bla

		actual = retrieve(heap);

		if (isWhitePosition(&actual, image) && actual.distance) {
			return actual.distance;
		}

		for (j = 0; j < MAX_NEIGHBOURS; j++) {
			Position sideway = (*sides[j]) (actual);
			colorChange = SAME_COLOR;

			if (!isValidPosition(&sideway, image)) {
				continue;
			}

			if (isAlreadyVisited(sideway, image)) {
				continue;
			}

			visit(sideway, image);

			if (color(actual, image) != color(sideway, image)) {
				colorChange = DIFFERENT_COLOR;
			}

			sideway.distance = actual.distance + colorChange;
			store(heap, sideway);
		}
	}

	return INVALID_INIT;
}