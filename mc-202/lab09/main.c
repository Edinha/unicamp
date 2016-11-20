/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Graph * graph = buildGraph(image);

	freeImage(&image);

	// TODO find a white spot for start and then the answer

	freeGraph(&graph);

	return 0;
}
