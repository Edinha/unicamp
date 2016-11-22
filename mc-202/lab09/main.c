/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "graph.h"

int main() {

	Image * image = readImage();

	Graph * graph = buildGraph(image);

	freeImage(&image);

	// TODO call method for solve and print response here
	int response = minimumWay(graph, image);

	printf("%d\n", response);

	freeGraph(&graph);

	return 0;
}
