/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "image.h"

int main() {

	Image * image = readImage();

	// TODO call method for solve and print response here
	int response = 0; //minimumWay(graph, image);

	printf("%d\n", response);

	freeImage(&image);

	return 0;
}
