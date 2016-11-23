/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "position.h"

/* Implementação dos métodos */

bool isValidPosition(Position * position, Image * image) {
	if (position->x >= image->height || position->x < 0) {
		return false;
	}

	if (position->y >= image->width || position->y < 0) {
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