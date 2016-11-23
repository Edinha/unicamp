/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Heap * heap = createHeap(image->width * image->height);

	int response = minimumWay(image, heap);

	// TODO Print the right message for Marie
	printf("%d\n", response);

	freeImage(&image);

	freeHeap(&heap);

	return 0;
}
