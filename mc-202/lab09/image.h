/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */
#ifndef IMAGE_H
#define IMAGE_H

/* Esse arquivo contém as definições de uma imagem da entrada do problema, com
 * as funções de leitura e armazenamento dos pixels */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Define constantes para cores em hexadecimal */
#define BLACK 0
#define WHITE 0xFFFFFF

/* Define as máscaras de conversão para transformar números de RGB para hexa */
#define RED_MASK 16
#define GREEN_MASK 8

/* Define a estrutura de imagem, com altura, largura e a matrix de pixels de entrada */
typedef
	struct {
		int width, height;
		int ** pixels;
	} Image;

// função presume que não ocorrem erros e que
// máximo valor de valor de um canal de cor é 255
Image* readImage() ;

/* Libera o ponteiro de imagem */
void freeImage(Image**);

#endif