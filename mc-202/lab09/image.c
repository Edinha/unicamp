/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "image.h"

Image* readImage() {
	Image * img;
	char peek;
	int i, j, r, g, b;

	img = malloc(sizeof(Image));
	scanf("P3 ");

	while((peek = getchar()) == '#') {
		scanf("%*[^\r\n]%*[\r\n]");
	}

	ungetc(peek, stdin);
	scanf("%d %d %*d", &img->width, &img->height);
	img->pixels = malloc(sizeof(int*) * img->height);
	img->path = malloc(sizeof(int*) * img->height);

	for (i = 0; i < img->height; i++) {
		img->pixels[i] = malloc(sizeof(int) * img->width);
		img->path[i] = malloc(sizeof(int) * img->width);
		for (j = 0; j < img->width; j++) {
			scanf("%d%d%d", &r, &g, &b);
			img->pixels[i][j] = (r << RED_MASK) + (g << GREEN_MASK) + b;
			img->path[i][j] = NOT_VISITED;
		}
	}

	return img;
}

void freeImage(Image ** img) {
	for (int i = 0; i < (*img)->height; i++) {
		free((*img)->pixels[i]);
		free((*img)->path[i]);
	}

	free((*img)->pixels);
	free((*img)->path);
	free((*img));
}