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

/* Define os retornos para a comparação de duas posições */
#define GREATER 1
#define LESSER -1

/* Define uma estrutura de posição dentro da imagem */
typedef
	struct {
		int x, y, distance;
	} Position;

/* Retorna caso a posição esteja dentro da imagem */
bool isValidPosition(Position*, Image*);

/* Retorna verdadeiro caso a posição da imagem possua a cor branca (Constanste WHITE) */
bool isWhitePosition(Position*, Image*);

/* Compara as distâncias de duas posições, retornando GREATER caso primeira maior que segunda ou LESSER caso contrário*/
int compare(Position, Position);

/* Retorna a posição logo acima */
Position up(Position);

/* Retorna a posição logo abaixo */
Position down(Position);

/* Retorna a posição logo a esquerda */
Position left(Position);

/* Retorna a posição logo a direita */
Position right(Position);

#endif