/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Heap * heap = createHeap(image->width * image->height);

	int response = minimumWay(image, heap);

	printf("Maria deve memorizar %d regioes.\n", response);

	freeImage(&image);

	freeHeap(&heap);

	return 0;
}
