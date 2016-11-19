/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#ifndef POSITION_H
#define POSITION_H

/* Esse arquivo contém as definições de uma estrutura para a posição de andamento do algoritmo de caminhos.
 * A partir de coordenadas cartesianas para identificação.
 */

#include "image.h"

/* Define uma estrutura de posição dentro da imagem */
typedef
	struct {
		int x, y;
	} Position;

/* Retorna caso a posição esteja dentro da imagem */
bool isValidPosition(Position*, Image*);

/* Retorna verdadeiro caso a posição da imagem possua a cor branca (Constanste WHITE) */
bool isWhitePosition(Position*, Image*);

/* Atualiza o ponteiro de posição para acima */
void up(Position*);

/* Atualiza o ponteiro de posição para abaixo */
void down(Position*);

/* Atualiza o ponteiro de posição para a sua esquerda */
void left(Position*);

/* Atualiza o ponteiro de posição para a sua direita */
void right(Position*);

#endif