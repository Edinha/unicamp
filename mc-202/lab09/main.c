/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Graph * graph = buildGraph(image);

	// TODO free graph pointer and remove printf
	printf("%d", graph->size);

	freeImage(&image);

	return 0;
}
