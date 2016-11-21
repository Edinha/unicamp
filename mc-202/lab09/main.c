/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Graph * graph = buildGraph(image);

	int response = minimumWay(graph, image);

	// TODO printf the response here

	printf("%d\n", response);

	freeImage(&image);

	freeGraph(&graph);

	return 0;
}
