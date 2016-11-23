/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Heap * heap = createHeap(image->width * image->height);

	// TODO call method for solve and print response here
	int response = minimumWay(image, heap);

	printf("%d\n", response);

	freeImage(&image);

	freeHeap(&heap);

	return 0;
}
