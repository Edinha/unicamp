/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "position.h"

/* Implementação dos métodos */

// TODO remove this, replace logic later

bool isValidPosition(Position * position, Image * image) {
	if (position->x >= image->width || position->x < 0) {
		return false;
	}

	if (position->y >= image->height || position->y < 0) {
		return false;
	}

	return true;
}

bool isWhitePosition(Position * position, Image * image) {
	return (image->pixels[position->x][position->y] == WHITE);
}

Position up(Position position) {
	position.y--;
	return position;
}

Position down(Position position) {
	position.y++;
	return position;
}

Position left(Position position) {
	position.x--;
	return position;
}

Position right(Position position) {
	position.x++;
	return position;
}